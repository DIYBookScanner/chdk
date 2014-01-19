#include "platform.h"
#include "raw_buffer.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"
#include "console.h"
#include "math.h"
#include "modules.h"
#include "shot_histogram.h"
#include "gui_lang.h"
#include "gui_mbox.h"
#include "cachebit.h"
#include "remotecap_core.h"
#include "ptp.h" // for remotecap constants
#include "script_api.h" // for script hook

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
//#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "%s%04d%s"
#define RAW_BRACKETING_FILENAME "%s%04d_%02d%s" 

//-------------------------------------------------------------------
#define RAW_DEVELOP_OFF     0
#define RAW_DEVELOP_RAW     1
#define RAW_DEVELOP_DNG     2

static char fn[64];
static int develop_raw = RAW_DEVELOP_OFF;

//-------------------------------------------------------------------
void raw_prepare_develop(const char* filename, int prompt)
{
    develop_raw = RAW_DEVELOP_OFF;
    if (filename)
    {
        struct stat st;
        if ((stat(filename,&st) != 0) || (st.st_size < camera_sensor.raw_size))
            return;
        if (prompt)
            gui_mbox_init((int)"", LANG_RAW_DEVELOP_MESSAGE, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
        if (st.st_size == camera_sensor.raw_size)
            develop_raw = RAW_DEVELOP_RAW;
        else
            develop_raw = RAW_DEVELOP_DNG;
        strcpy(fn,filename);
    }
}

//-------------------------------------------------------------------
void patch_bad_pixels(void);
//-------------------------------------------------------------------

char* get_raw_image_addr(void) {
    char *r=hook_raw_image_addr();
    if (!conf.raw_cache) return r;
    else return ADR_TO_CACHED(r);
}

char* get_alt_raw_image_addr(void) {    // return inactive buffer for cameras with multiple RAW buffers (otherwise return active buffer)
    char *r=hook_alt_raw_image_addr();
    if (!conf.raw_cache) return r;
    else return ADR_TO_CACHED(r);
}
//-------------------------------------------------------------------

/*
create a new raw file and return the file descriptor from open
name and 
create directories as need
should only be called in raw hook
modifies global fn
*/
static int raw_create_time; // time raw file was opened, for time stamp
static int raw_br_counter;  // bracketing counter for raw suffix
int raw_createfile(void)
{
    int fd;
    char dir[32];

    raw_create_time = time(NULL);

    mkdir_if_not_exist("A/DCIM");
    if (conf.raw_in_dir)
        get_target_dir_name(dir);
    else
        sprintf(dir, RAW_TARGET_DIRECTORY, 100);

    mkdir_if_not_exist(dir);

    sprintf(fn, "%s/", dir);
    if(raw_br_counter && conf.bracketing_add_raw_suffix && (shooting_get_drive_mode()!=1)) {
        sprintf(fn+strlen(fn), 
                RAW_BRACKETING_FILENAME,
                img_prefixes[conf.raw_prefix],
                get_target_file_num(),
                raw_br_counter,
                conf.dng_raw&&conf.raw_dng_ext ? ".DNG" : img_exts[conf.raw_ext]);
    } else {
        sprintf(fn+strlen(fn),
                RAW_TARGET_FILENAME,
                img_prefixes[conf.raw_prefix],
                get_target_file_num(),
                conf.dng_raw&&conf.raw_dng_ext ? ".DNG" : img_exts[conf.raw_ext]);
    }
    fd = open(fn, O_WRONLY|O_CREAT, 0777);

    return fd;
}

/*
close filed opened by raw_createfile, set timestamp
*/
void raw_closefile(int fd)
{
    if(fd < 0) {
        return;
    }

    struct utimbuf t;
    t.actime = t.modtime = raw_create_time;
    close(fd);
    utime(fn, &t);

}

// Set in raw_savefile and used in get_raw_pixel & set_raw_pixel (for performance)
// Don't call set/get_raw_pixel until this value is initialised
static char *rawadr;    // Pointer to current raw image buffer

// handle actual raw / dng saving to SD
// returns 1 on successful save, otherwise 0
static int raw_savefile(char *rawadr, char *altrawadr) {
    int ret = 0;
    started();
    int timer=get_tick_count();
    if (conf.dng_raw)
    {
        ret = libdng->write_dng(rawadr, altrawadr);
    }
    else 
    {
        int fd = raw_createfile();
        if(fd >= 0) {
            // Write active RAW buffer
            write(fd, ADR_TO_UNCACHED(rawadr), camera_sensor.raw_size);
            ret = 1;
            raw_closefile(fd);
        }
    }

    if (conf.raw_timer) {
        char txt[30];
        timer=get_tick_count()-timer;
        sprintf(txt, "saving time=%d", timer);
        console_add_line(txt);
    }

    finished();
    return ret;
}

// processing done when raw hook runs available
void raw_process(void)
{
    // Get pointers to RAW buffers (will be the same on cameras that don't have two or more buffers)
    rawadr = get_raw_image_addr();
    char *altrawadr = get_alt_raw_image_addr();

    if ((conf.save_raw && conf.dng_raw && is_raw_enabled()) 
        || (remotecap_get_target() & PTP_CHDK_CAPTURE_DNGHDR))
    {                             
        libdng->capture_data_for_exif();
	}
    if (camera_info.state.state_kbd_script_run && shot_histogram_isenabled()) build_shot_histogram();

    libscriptapi->shoot_hook(SCRIPT_SHOOT_HOOK_RAW);

    // count/save badpixels if requested
    if (libdng->raw_init_badpixel_bin())
    {
        return;
    }

    if (develop_raw != RAW_DEVELOP_OFF)
    {
        started();
        if (develop_raw == RAW_DEVELOP_DNG)
        {
            libdng->load_dng_to_rawbuffer(fn, rawadr);
        }
        else
        {
            int fd = open(fn, O_RDONLY, 0777);
            if (fd >= 0) {
                read(fd, rawadr, camera_sensor.raw_size);
                close(fd);
            }
        }
#ifdef OPT_CURVES
        if (conf.curve_enable)
            libcurves->curve_apply();
#endif
        finished();
        develop_raw = RAW_DEVELOP_OFF;
        return;
    }

    if (conf.bad_pixel_removal) patch_bad_pixels();

    shooting_bracketing();

    if (conf.tv_bracket_value || conf.av_bracket_value || conf.iso_bracket_value || conf.subj_dist_bracket_value)
    {
        if (camera_info.state.state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)
            raw_br_counter = 1;
        else
            raw_br_counter++;
    }
    else
        raw_br_counter=0;

    // if any remote cap targets, skip local raw
    if (remotecap_get_target())
    {
        camera_info.state.state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;
        remotecap_raw_available(rawadr);
    }
    else if (!(conf.raw_save_first_only && camera_info.state.state_shooting_progress == SHOOTING_PROGRESS_PROCESSING))
    {
        camera_info.state.state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

        if (conf.save_raw && is_raw_enabled())
        {
            raw_savefile(rawadr,altrawadr);
        }
    }

#ifdef OPT_CURVES
    if (conf.curve_enable)
        libcurves->curve_apply();
#endif
}

//-------------------------------------------------------------------

void set_raw_pixel(unsigned int x, unsigned int y, unsigned short value) {
#if CAM_SENSOR_BITS_PER_PIXEL==10
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*10;
    switch (x%8) {
        case 0: addr[0]=(addr[0]&0x3F)|(value<<6); addr[1]=value>>2;                  break;
        case 1: addr[0]=(addr[0]&0xC0)|(value>>4); addr[3]=(addr[3]&0x0F)|(value<<4); break;
        case 2: addr[2]=(addr[2]&0x03)|(value<<2); addr[3]=(addr[3]&0xF0)|(value>>6); break;
        case 3: addr[2]=(addr[2]&0xFC)|(value>>8); addr[5]=value;                     break;
        case 4: addr[4]=value>>2;                  addr[7]=(addr[7]&0x3F)|(value<<6); break;
        case 5: addr[6]=(addr[6]&0x0F)|(value<<4); addr[7]=(addr[7]&0xC0)|(value>>4); break;
        case 6: addr[6]=(addr[6]&0xF0)|(value>>6); addr[9]=(addr[9]&0x03)|(value<<2); break;
        case 7: addr[8]=value;                     addr[9]=(addr[9]&0xFC)|(value>>8); break;
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==12
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/4)*6;
    switch (x%4) {
        case 0: addr[0] = (addr[0]&0x0F) | (unsigned char)(value << 4);  addr[1] = (unsigned char)(value >> 4);  break;
        case 1: addr[0] = (addr[0]&0xF0) | (unsigned char)(value >> 8);  addr[3] = (unsigned char)value;         break;
        case 2: addr[2] = (unsigned char)(value >> 4);  addr[5] = (addr[5]&0x0F) | (unsigned char)(value << 4);  break;
        case 3: addr[4] = (unsigned char)value; addr[5] = (addr[5]&0xF0) | (unsigned char)(value >> 8);  break;
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==14
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*14;
    switch (x%8) {
        case 0: addr[ 0]=(addr[0]&0x03)|(value<< 2); addr[ 1]=value>>6;                                                         break;
        case 1: addr[ 0]=(addr[0]&0xFC)|(value>>12); addr[ 2]=(addr[ 2]&0x0F)|(value<< 4); addr[ 3]=value>>4;                   break;
        case 2: addr[ 2]=(addr[2]&0xF0)|(value>>10); addr[ 4]=(addr[ 4]&0x3F)|(value<< 6); addr[ 5]=value>>2;                   break;
        case 3: addr[ 4]=(addr[4]&0xC0)|(value>> 8); addr[ 7]=value;                                                            break;
        case 4: addr[ 6]=value>>6;                   addr[ 9]=(addr[ 9]&0x03)|(value<< 2);                                      break;
        case 5: addr[ 8]=value>>4;                   addr[ 9]=(addr[ 9]&0xFC)|(value>>12); addr[11]=(addr[11]&0x0F)|(value<<4); break;
        case 6: addr[10]=value>>2;                   addr[11]=(addr[11]&0xF0)|(value>>10); addr[13]=(addr[13]&0x3F)|(value<<6); break;
        case 7: addr[12]=value;                      addr[13]=(addr[13]&0xC0)|(value>> 8);                                      break;
    }
#else 
    #error define set_raw_pixel for sensor bit depth
#endif
}

//-------------------------------------------------------------------
unsigned short get_raw_pixel(unsigned int x,unsigned  int y) {
#if CAM_SENSOR_BITS_PER_PIXEL==10
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*10;
    switch (x%8) {
        case 0: return ((0x3fc&(((unsigned short)addr[1])<<2)) | (addr[0] >> 6));
        case 1: return ((0x3f0&(((unsigned short)addr[0])<<4)) | (addr[3] >> 4));
        case 2: return ((0x3c0&(((unsigned short)addr[3])<<6)) | (addr[2] >> 2));
        case 3: return ((0x300&(((unsigned short)addr[2])<<8)) | (addr[5]));
        case 4: return ((0x3fc&(((unsigned short)addr[4])<<2)) | (addr[7] >> 6));
        case 5: return ((0x3f0&(((unsigned short)addr[7])<<4)) | (addr[6] >> 4));
        case 6: return ((0x3c0&(((unsigned short)addr[6])<<6)) | (addr[9] >> 2));
        case 7: return ((0x300&(((unsigned short)addr[9])<<8)) | (addr[8]));
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==12
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/4)*6;
    switch (x%4) {
        case 0: return ((unsigned short)(addr[1])        << 4) | (addr[0] >> 4);
        case 1: return ((unsigned short)(addr[0] & 0x0F) << 8) | (addr[3]);
        case 2: return ((unsigned short)(addr[2])        << 4) | (addr[5] >> 4);
        case 3: return ((unsigned short)(addr[5] & 0x0F) << 8) | (addr[4]);
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==14
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*14;
    switch (x%8) {
        case 0: return ((unsigned short)(addr[ 1])        <<  6) | (addr[ 0] >> 2);
        case 1: return ((unsigned short)(addr[ 0] & 0x03) << 12) | (addr[ 3] << 4) | (addr[ 2] >> 4);
        case 2: return ((unsigned short)(addr[ 2] & 0x0F) << 10) | (addr[ 5] << 2) | (addr[ 4] >> 6);
        case 3: return ((unsigned short)(addr[ 4] & 0x3F) <<  8) | (addr[ 7]);
        case 4: return ((unsigned short)(addr[ 6])        <<  6) | (addr[ 9] >> 2);
        case 5: return ((unsigned short)(addr[ 9] & 0x03) << 12) | (addr[ 8] << 4) | (addr[11] >> 4);
        case 6: return ((unsigned short)(addr[11] & 0x0F) << 10) | (addr[10] << 2) | (addr[13] >> 6);
        case 7: return ((unsigned short)(addr[13] & 0x3F) <<  8) | (addr[12]);
    }
#else 
    #error define get_raw_pixel for sensor bit depth
#endif
    return 0;
}

//-------------------------------------------------------------------
void patch_bad_pixel(unsigned int x,unsigned  int y) {
    int sum=0;
    int nzero=0;
    int i,j;
    int val;
    if ((x>=2) && (x<camera_sensor.raw_rowpix-2) && (y>=2) && (y<camera_sensor.raw_rows-2)) {
        if ((conf.bad_pixel_removal==1) || (conf.save_raw && conf.dng_raw)) {  // interpolation or DNG saving
            for (i=-2; i<=2; i+=2)
                for (j=-2; j<=2; j+=2)
                    if ((i!=0) && (j!=0)) {
                        val=get_raw_pixel(x+i, y+j);
                        if (val) {sum+=val; nzero++;}
                    }
                if (nzero) set_raw_pixel(x,y,sum/nzero);
        } else if (conf.bad_pixel_removal==2)  // or this makes RAW converter (internal/external)
            set_raw_pixel(x,y,0);
    }
}

struct point{
    int x;
    int y;
    struct point *next;
} *pixel_list=NULL;

void patch_bad_pixels(void) {
    struct point *pixel=pixel_list;
    while (pixel) {
        patch_bad_pixel((*pixel).x,(*pixel).y);
        pixel=(*pixel).next;
    }
}

int make_pixel_list(char * ptr, int size) {
    int x,y;
    struct point *pixel;
    char *endptr;

    if ( size <=0 ) return 0;

    while(*ptr) {
        while (*ptr==' ' || *ptr=='\t') ++ptr;    // whitespaces
        x=strtol(ptr, &endptr, 0);
        if (endptr != ptr) {
            ptr = endptr;
            if (*ptr++==',') {
                while (*ptr==' ' || *ptr=='\t') ++ptr;    // whitespaces
                if (*ptr!='\n' && *ptr!='\r') {
                    y=strtol(ptr, &endptr, 0);
                    if (endptr != ptr) {
                        ptr = endptr;
                        pixel=malloc(sizeof(struct point));
                        if (pixel) {
                            (*pixel).x=x;
                            (*pixel).y=y;
                            (*pixel).next=pixel_list;
                            pixel_list=pixel;
                        }
                    }
                }
            }
        }
        while (*ptr && *ptr!='\n') ++ptr;    // unless end of line
        if (*ptr) ++ptr;
    }
    return 0;
}
