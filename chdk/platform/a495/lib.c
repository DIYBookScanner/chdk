#include "platform.h"
#include "lolevel.h"

char *hook_raw_image_addr()
{
    return (char*) 0x10E52420;
}

/*long hook_raw_size() {
    //CAM_RAW_ROWS * ((CAM_RAW_ROWPIX*CAM_SENSOR_BITS_PER_PIXEL)/8)
    return 0x00ec04f0;
}*/

// only two LEDs in A495:
#define LED_PR 0xC0220088  // green LED
#define LED_AF 0xC0220080  // orange AF LED


void shutdown()
{
    volatile long *p = (void*)LED_PR;    // Green LED

    asm(
        "MRS     R1, CPSR\n"
        "AND     R0, R1, #0x80\n"
        "ORR     R1, R1, #0x80\n"
        "MSR     CPSR_cf, R1\n"
        :::"r1","r0");

    *p = 0x44;  // power off.

    while(1);
}


void debug_led(int state)
{
    *(int*)LED_PR=state ? 0x46 : 0x44;
}

// A495 has 2 led values
// 0/7 - Power LED Green
// 1/9 - AF LED Orange
void camera_set_led(int led, int state, int bright) {
    static char led_table[2]={7,9};
    if(state<=1) _LEDDrive(led_table[led%sizeof(led_table)], (!state)&1);
}

char *camera_jpeg_count_str()
{
    extern char jpeg_count_str[];
    return jpeg_count_str;
}


void vid_bitmap_refresh() {
    extern int enabled_refresh_physical_screen;
    extern int full_screen_refresh;

    // asm1989: i've tried refreshphysical screen (screen unlock) and that caused the canon and
    // function menu to not display at all. This seems to work and is called in a similar
    // way in other places where original OSD should be refreshed.
    extern void _ScreenLock();
    extern void _ScreenUnlock();

    _ScreenLock();

    enabled_refresh_physical_screen=1;
    full_screen_refresh=3;   // found in ScreenUnlock underneath a CameraLog.c call

    _ScreenUnlock();
}


int get_flash_params_count(void){
    return 0x94;  //found by finsig
}


// This camera crashes if GetBatteryTemperature is called, override auto detected stub
int _GetBatteryTemperature()
{
      return -99;
}

// Functions for PTP Live View system

void *vid_get_bitmap_active_palette() {
        return (void*)(*(int*)(0x4970+0x20));  //Found @ 0xffcd1e80 a495 100f
}

// 64 entry palette based on 100f 0xffcd1e80
int vid_get_palette_type()                      { return 4; }
int vid_get_palette_size()                      { return 16*4; }

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x4970+0xC)); //found @ 0xffcd1f3c a495 100f
}


// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

// Defined in stubs_min.S
extern char active_viewport_buffer;
extern void* viewport_buffers[];

void *vid_get_viewport_fb()
{
    // Return first viewport buffer - for case when vid_get_viewport_live_fb not defined
    return viewport_buffers[0];
}

void *vid_get_viewport_live_fb()
{
    if (MODE_IS_VIDEO(mode_get()) || is_video_recording())
        return viewport_buffers[0];     // Video only seems to use the first viewport buffer.

    // Hopefully return the most recently used viewport buffer so that motion detect, histogram, zebra and edge overly are using current image data
    return viewport_buffers[(active_viewport_buffer)&3];
}

void *vid_get_viewport_fb_d()
{
    extern char *viewport_fb_d;
    return viewport_fb_d;
}

void *vid_get_bitmap_fb(){
    return (void*)0x10361000; // Found @0xffc3f020
}

int vid_get_viewport_yoffset() {
    return 0;
}

extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();

int vid_get_viewport_width() {
    return 360;
}

int vid_get_viewport_width_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:_GetVRAMHPixelsSize();
}

long vid_get_viewport_height() {
    return 240;
}

int vid_get_viewport_height_proper() {
    int m = mode_get();
    // special case: W resolution
    if ((m&MODE_MASK) != MODE_PLAY && shooting_get_prop(PROPCASE_RESOLUTION) == 8) {
        return 240;
    }
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}

int vid_get_viewport_fullscreen_height() {
    int m = mode_get();
    // special case: W resolution
    if ((m&MODE_MASK) != MODE_PLAY && shooting_get_prop(PROPCASE_RESOLUTION) == 8) {
        return 120;
    }
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}

int vid_get_viewport_display_xoffset_proper()   { return vid_get_viewport_display_xoffset(); }
int vid_get_viewport_display_yoffset_proper()   { return vid_get_viewport_display_yoffset(); }

