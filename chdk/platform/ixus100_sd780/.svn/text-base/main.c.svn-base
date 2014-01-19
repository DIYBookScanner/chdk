#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"


extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup()
{
    long *bss = &link_bss_start;

   // sanity check (pointless with automemiso)
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
	started();
	shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
	*bss++ = 0;

    boot();
}


// TODO setting the DP button as a shortcut to movie in canon menu
// gives a value of (current mode)+1024 while movie is recording, unless
// already in movie mode
static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_AUTO,               32768 },
    { MODE_M,                  32769 },
    { MODE_P,                  32772 },
    { MODE_PORTRAIT,           0x800D },
    { MODE_NIGHT_SNAPSHOT,     0x800B },
    { MODE_SCN_KIDS_PETS,      0x8010 },
    { MODE_SCN_INDOOR,         0x8011 },
    { MODE_SCN_SUNSET,         0x4012 },
    { MODE_SCN_FOLIAGE,        0x4013 },
    { MODE_SCN_SNOW,           0x4014 },
    { MODE_SCN_BEACH,          0x4015 },
    { MODE_SCN_FIREWORK,       0x4016 },
    { MODE_SCN_NIGHT_SCENE,    0x4006 }, //AKA Long Shutter --- unclear, 13-Mar-2010/fe50 
    { MODE_SCN_UNDERWATER,     0x4017 },
    { MODE_SCN_AQUARIUM,       0x4018 },
    { MODE_SCN_ISO_3200,       0x401D },
    { MODE_DIGITAL_MACRO,      0x4208 },
    { MODE_SCN_COLOR_ACCENT,   0x421B },
    { MODE_SCN_COLOR_SWAP,     0x421C },
    { MODE_STITCH,             0x420A },
//    { MODE_QUICK,              33312 },

    { MODE_VIDEO_STD,          0xA29  },
    { MODE_VIDEO_COLOR_ACCENT, 0xA27  },
    { MODE_VIDEO_COLOR_SWAP,   0xA28  },
};


#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

// Focus length table in firmware @0xfffe2a8c
#define NUM_FL      7   // 0 - 6, entries in firmware
#define NUM_DATA    3   // 3 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 5.9       33       ( 33/ 5.9) * 59 = 330  (min FL)
// 17.9      100      (100/17.9) * 59 = 329.6  (max FL)
#define CF_EFL      330
#define	CF_EFL_DIV  59

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/CF_EFL_DIV;
}

int get_focal_length(int zp) {
    if (zp < 0) zp = 0;
    else if (zp >= NUM_FL) zp = NUM_FL-1;
    return focus_len_table[zp*NUM_DATA];
}

int get_zoom_x(int zp) {
    return get_focal_length(zp)*10/focus_len_table[0];
}

/*
physw_ bit OK
*/
//VERIFY_SD780 this was mode_get() previously
int mode_get2() {
    int mode, i, t=0xFF;
    mode  = (physw_status[1] & 0x00000001)?MODE_REC:MODE_PLAY;

    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    //draw_txt_string(20, 11, osd_buf, conf.osd_color);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}

//VERIFY_SD780 min observed
long get_vbatt_min()
{
    return 3375; // hnikesch on forum
}

//VERIFY_SD780 max observed
long get_vbatt_max()
{
    return 4125; // fresh off charger slightly greater
}

#if CAM_CONSOLE_LOG_ENABLED

#define DEV_HDR_WRITE_OFFSET (0x14C/4)

typedef int DEV_HDR;

int (*_tyWriteOrig)(DEV_HDR *hdr, char *buf, int len);


int hook_tyWriteOrig(DEV_HDR *hdr, char *buf, int len)
{
	// Slow, but stable writes
	FILE *fd = fopen("A/stdout.txt", "a");
	if (fd) {
	    fwrite(buf, 1, len, fd);
	    fclose(fd);
	}

    return _tyWriteOrig(hdr, buf, len);

}

void cam_console_init()
{
    DEV_HDR *DRV_struct;

    DRV_struct = _iosDevFind("/tyCo/0", 0);

    _tyWriteOrig = (void*)DRV_struct[DEV_HDR_WRITE_OFFSET];

	FILE *fd = fopen("A/chdklog.txt", "a");
	if (fd) {
	    // can't be used with "Fut" API
	    //fprintf(fd, "DRV_struct: %x, _tyWriteOrig: %x\n", DRV_struct, _tyWriteOrig);
	    char buf[256];
	    int buflen = sprintf(buf, "DRV_struct: %x, _tyWriteOrig: %x\n", DRV_struct, _tyWriteOrig);
	    fwrite(buf, 1, buflen, fd);
	}

	FILE *fdout = fopen("A/stdout.txt", "r");
	if (fdout)
	{
        DRV_struct[DEV_HDR_WRITE_OFFSET] = (int)hook_tyWriteOrig;
        fclose(fdout);
	    // fprintf(fd, "tyWrite replaced, camera log enabled\n");
	    fwrite("tyWrite replaced, camera log enabled\n", 1, sizeof("tyWrite replaced, camera log enabled\n"), fd);
    }

	if (fd)
	{
	    fclose(fd);
	}

}

#endif
