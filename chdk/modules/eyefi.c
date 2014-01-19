/*
* Based on work by Dave Hansen <dave@sr71.net>
* original licensing:
* This software may be redistributed and/or modified under the terms of
 * the GNU General Public License ("GPL") version 2 as published by the
 * Free Software Foundation.
 */
#include <gui.h>
#include <console.h>
#define EINVAL 1000
#define log(x) console_add_line(x)
#define Sleep(x) msleep(x)
#include <assert.h>
#include <string.h>
#include "eyefi.h"

static int running=0;
static unsigned char *eyefi_buf=NULL;
static unsigned int eyefi_cmd,eyefi_cmd1=0;
static char eyefi_path[]="A/EyeFi/";
static char *eyefi_status[]={
	"not scanning",
	"locating network",
	"verifying network_key",
	"waiting for DHCP",
	"testing conn. to server",
	"success"
};

int atoh(char c)
{
	char lc = tolower(c);
	if ((c >= '0') && (c <= '9'))
		return c - '0';
	else if ((lc >= 'a') && (lc <= 'z'))
		return (lc - 'a') + 10;
	//debug_printf(5, "non-hex character: '%c'/'%c'\n", c, lc);
	return -1;
}

/*
 * Take a string like "0ab1" and make it
 * a series of bytes: { 0x0a, 0xb1 }
 *
 * @len is the strlen() of the ascii
 *
 * Destroys the original string.
 */
char *convert_ascii_to_hex(char *ascii)
{
	int i;
	char *hex;
	int len = strlen(ascii);

	// Make it just as long as the ASCII password, even though it
	// will only end up half as long
	//hex = strdup(ascii);
	
	hex=malloc(strlen(ascii));
	strcpy(hex,ascii);
	if (len%2) {
		/*fprintf(stderr, "%s() must be even number of bytes: %d\n",
		__func__, len);
		exit(2);*/
		return NULL;
	}
	for (i=0; i < len; i+=2) {
		int high = atoh(ascii[i]);
		int low  = atoh(ascii[i+1]);
		u8 byte = (high<<4 | low);
		if (high < 0 || low < 0) {
			//fprintf(stderr, "unable to parse hex string: '%s'\n", ascii);
			return NULL;
		}
		//debug_printf(6, "high: %02x low: %02x, both: %02x\n", high, low, byte);
		hex[i/2] = byte;
	}
	for (i=len/2; i < len; i++)
		hex[i] = '\0';
	return hex;
}

int hex_only(char *str)
{
	int i;

	for (i = 0; i < strlen(str); i++) {
		if (((str[i] >= 'a') && str[i] <= 'f') ||
		    ((str[i] >= 'A') && str[i] <= 'F') ||
		    ((str[i] >= '0') && str[i] <= '9')) {
			continue;
		}
		return 0;
	}
	return 1;
}

int make_network_key(struct network_key *key, char *essid, char *pass)
{
	char *hex_pass;
	int pass_len = strlen(pass);
	memset(key, 0, sizeof(*key));

	//eyefi_printf(" interpreting passphrase as ");
	switch (pass_len) {
		case WPA_KEY_BYTES*2:
			if (hex_only(pass)) {
				//eyefi_printf("hex WPA");
				hex_pass = convert_ascii_to_hex(pass);
				if (!hex_pass)
					return -EINVAL;
				key->len = pass_len/2;
			memcpy(&key->wpa.key[0], hex_pass, key->len);
				free(hex_pass);
				break;
			}
		case WEP_KEY_BYTES*2:
		case WEP_40_KEY_BYTES*2:
			if (hex_only(pass)) {
				//eyefi_printf("hex WEP");
				hex_pass = convert_ascii_to_hex(pass);
				if (!hex_pass)
					return -EINVAL;
				key->len = pass_len/2;
				memcpy(&key->wep.key[0], hex_pass, key->len);
				free(hex_pass);
				break;
			}
		default:
			//eyefi_printf("ASCII WPA");
		        pbkdf2_sha1(pass, essid, strlen(essid), 4096,
				    &key->wpa.key[0], WPA_KEY_BYTES);
			key->len = WPA_KEY_BYTES;
			break;
	}
	char s[80];
	sprintf(s," key (%d bytes)", key->len);
	console_add_line(s);
	//assert(key->len != 0);
	return 0;
}

#define O_BINARY 0

static int eyefi_writeFile(const char *filename) {
	char path[80];
	int fd,bytesWritten;

	strcpy(path,eyefi_path);
	strcat(path,filename);
	fd=open(path,O_RDWR|O_CREAT|O_BINARY,0600);
	if (fd<0) {
		log("Cannot write eyefi file");
		return 0;
	}
	bytesWritten=write(fd,eyefi_buf,EYEFI_BUF_SIZE);
	close(fd);
	return bytesWritten==EYEFI_BUF_SIZE;
}

static int eyefi_readFile(const char *filename) {
	char path[80];
	int fd,bytesRead;

	strcpy(path,eyefi_path);
	strcat(path,filename);
	fd=open(path,O_RDONLY|O_BINARY,0777);

	if (fd<0) {
		log("Cannot read eyefi file");
		return 0;
	}
	memset(eyefi_buf,0,EYEFI_BUF_SIZE);
	bytesRead=read(fd,eyefi_buf,EYEFI_BUF_SIZE);
	close(fd);
	return bytesRead==EYEFI_BUF_SIZE;
}

int eyefi_init() {
	if (eyefi_buf==NULL) {
		eyefi_buf=(unsigned char*)malloc(EYEFI_BUF_SIZE);
		if (eyefi_buf==NULL) {
			log("Cannot allocate memory for Eyefi buffer");
			return 0;
		}
	}
	running=1;
	return 1;
}

void eyefi_close() {
	if (eyefi_buf!=NULL) {
		free(eyefi_buf);
		eyefi_buf=NULL;
	}
	running=0;
}

struct param {
	union {
		struct {
			unsigned char subcommand;
			unsigned char bytes;
			unsigned char args[32];
		} __attribute__((packed)) config;
		struct {
			unsigned char length;
			char SSID[32];
			struct network_key key;
		} __attribute__((packed)) network;
	};
} __attribute__((packed));

static int eyefi_sendCommandParam(unsigned char cmd,struct param *param) {
	int i;

	if (!eyefi_readFile("RSPC")) return 0;
	eyefi_cmd=eyefi_buf[3]+(eyefi_buf[2]<<8)+(eyefi_buf[1]<<16)+(eyefi_buf[0]<<24);

	memset(eyefi_buf,0,EYEFI_BUF_SIZE);
	eyefi_buf[0]=cmd;
	if (param)
		memcpy(eyefi_buf+1,param,sizeof *param);
	if (cmd=='a') {
		char s[128];
		sprintf(s,"%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
			eyefi_buf[0],eyefi_buf[1],eyefi_buf[2],eyefi_buf[3],eyefi_buf[4],eyefi_buf[5],eyefi_buf[6],eyefi_buf[7],
			eyefi_buf[8],eyefi_buf[9],eyefi_buf[10],eyefi_buf[11],eyefi_buf[12],eyefi_buf[13],eyefi_buf[14],eyefi_buf[15]);
		console_add_line(s);
	}
	if (!eyefi_writeFile("REQM")) return -1;
	
	eyefi_cmd++;
	memset(eyefi_buf,0,EYEFI_BUF_SIZE);
	eyefi_buf[0]=(unsigned char)(eyefi_cmd>>24);
	eyefi_buf[1]=(unsigned char)(eyefi_cmd>>16);
	eyefi_buf[2]=(unsigned char)(eyefi_cmd>>8);
	eyefi_buf[3]=(unsigned char)eyefi_cmd;
	if (!eyefi_writeFile("REQC")) return -2;

	for (i=0;i<20 && eyefi_cmd!=eyefi_cmd1;i++) {
		memset(eyefi_buf,0,EYEFI_BUF_SIZE);
		if (!eyefi_readFile("RSPC")) return -3;
		eyefi_cmd1=eyefi_buf[3]+(eyefi_buf[2]<<8)+(eyefi_buf[1]<<16)+(eyefi_buf[0]<<24);
		//printf("\tcmd:%X (%02X %02X %02X %02X)\n",eyefi_cmd1,eyefi_buf[0],eyefi_buf[1],eyefi_buf[2],eyefi_buf[3]);
		Sleep(250);
	}
	
	if (eyefi_cmd!=eyefi_cmd1) return -4;

	if (!eyefi_readFile("RSPM")) return -5;
	
	return 1;
}

static int eyefi_sendCommand(unsigned char cmd) {
	return eyefi_sendCommandParam(cmd,NULL);
}

struct eyefi_net {
	char name[32];
	unsigned char strength,type;
};

int eyefi_getAvailableNetworks() {
	return eyefi_sendCommand('g');
}

int eyefi_getConfiguredNetworks() {
	return eyefi_sendCommand('l');
}

int eyefi_getNetworkStatus() {
	return eyefi_sendCommand('s');
}

int eyefi_deleteNetwork(char *SSID) {
	struct param param;
	memset(&param,0,sizeof param);
	param.network.length=(unsigned char)strlen(SSID);
	strcpy(param.network.SSID,SSID);
	return eyefi_sendCommandParam('d',&param);
}

int eyefi_testNetwork(char *SSID,char *pwd) {
	struct param param;
	memset(&param,0,sizeof param);
	param.network.length=(unsigned char)strlen(SSID);
	strcpy(param.network.SSID,SSID);
	make_network_key(&param.network.key,SSID,pwd);
	return eyefi_sendCommandParam('t',&param);
}

int eyefi_enableWlan(int enable) {
	struct param param;
	memset(&param,0,sizeof param);
	param.config.subcommand=EYEFI_WLAN_DISABLE;
	param.config.bytes=1;
	param.config.args[0]=(unsigned char)enable;
	eyefi_sendCommandParam('O',&param);
	return 1;
}

int eyefi_wlanEnabled(int *pEnabled) {
	struct param param;
	memset(&param,0,sizeof param);
	param.config.subcommand=EYEFI_WLAN_DISABLE;
	param.config.bytes=0;
	eyefi_sendCommandParam('o',&param);
	*pEnabled=eyefi_buf[1];
	return 1;
}

int eyefi_addNetwork(char *SSID,char *pwd) {
	struct param param;
	memset(&param,0,sizeof param);
	param.network.length=(unsigned char)strlen(SSID);
	strcpy(param.network.SSID,SSID);
	make_network_key(&param.network.key,SSID,pwd);
	return eyefi_sendCommandParam('a',&param);
}

char *eyefi_statusName(int n) {
	if (n<0 || n>=sizeof eyefi_status/sizeof *eyefi_status)
		return NULL;
	return eyefi_status[n];
}

unsigned char *eyefi_getBuf() {
	return eyefi_buf;
}

int basic_module_init() {
    return 1;
}


int _module_unloader() {
	eyefi_close();
	return 0;
}

int _module_can_unload() {
    return running == 0;
}



// =========  MODULE INIT =================

libeyefi_sym _libeyefi =
{
    {
         0, _module_unloader, _module_can_unload, 0, 0
    },

	eyefi_init,
	eyefi_close,
	eyefi_getAvailableNetworks,
	eyefi_getConfiguredNetworks,
	eyefi_getNetworkStatus,
	eyefi_deleteNetwork,
	eyefi_testNetwork,
	eyefi_addNetwork,
	eyefi_enableWlan,
	eyefi_wlanEnabled,
	eyefi_getBuf,
	eyefi_statusName
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"EYEFI",// Module name
    (int32_t)"Handle Eyefi SD cards",

    &_libeyefi.base,

    ANY_VERSION,                // CONF version
    ANY_VERSION,                // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
