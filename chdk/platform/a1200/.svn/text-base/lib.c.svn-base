#include "platform.h"
#include "lolevel.h"

#define LED_GR     0xC0220014
#define LED_OR     0xC0220010
#define LED_AF     0xC022000C

void shutdown() {

    volatile long *p = (void*)LED_AF;

    asm(
        "MRS     R1, CPSR\n"
        "AND     R0, R1, #0x80\n"
        "ORR     R1, R1, #0x80\n"
        "MSR     CPSR_cf, R1\n"
        :::"r1","r0");

    *p = 0x44;  // power off.

    while(1);
}

void debug_led(int state) {

    *(int*)LED_OR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {

    static char led_table[3]={0,1,9};
    _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int vid_get_viewport_width() {

    // viewport width table for each image size
    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
    //static long vp_w[4] = { 360, 360, 360, 360 };
    //return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    return(360);
}

long vid_get_viewport_height() {

    // viewport height table for each image size
    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
    // static long vp_h[4] = { 240, 240, 240, 240 };
    // return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    return( 240 );
}

int vid_get_viewport_xoffset() {

    // viewport width offset table for each image size
    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
    //static long vp_w[4] = { 0, 0, 0, 0 };               // should all be even values for edge overlay
    //return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    return( 0 ) ;
}

int vid_get_viewport_yoffset() {

    // viewport height offset table for each image size
    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
    // static long vp_h[4] = { 0, 0, 0, 0 };
    // return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    return ( 0 ) ;
}

extern char active_viewport_buffer;
extern void* viewport_buffers[];

void *vid_get_viewport_fb()
{
    // Return first viewport buffer - for case when vid_get_viewport_live_fb not defined
    return viewport_buffers[0];
}

void *vid_get_viewport_live_fb()
{
    if (MODE_IS_VIDEO(mode_get()))
        return viewport_buffers[0];     // Video only seems to use the first viewport buffer.

   // Hopefully return the most recently used viewport buffer so that motion detect, histogram, zebra and edge overly are using current image data
    return viewport_buffers[(active_viewport_buffer-1)&3];
}

// Functions for PTP Live View system
// 256 entry palette based on 100b sub_FF909B0C
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }
   
// Function to load CHDK custom colors into active Canon palette

void *vid_get_bitmap_active_palette() {
        extern int active_palette_buffer;
        extern char* palette_buffer[];
        return (palette_buffer[active_palette_buffer]+8);
}

void load_chdk_palette() {

        extern int active_palette_buffer;
        // Only load for the standard record and playback palettes
        if ((active_palette_buffer == 0) || (active_palette_buffer == 4))
        {
                int *pal = (int*)vid_get_bitmap_active_palette();
                if (pal[CHDK_COLOR_BASE+0] != 0x33ADF62)
                {
                        pal[CHDK_COLOR_BASE+0]  = 0x33ADF62;  // Red
                        pal[CHDK_COLOR_BASE+1]  = 0x326EA40;  // Dark Red
                        pal[CHDK_COLOR_BASE+2]  = 0x34CD57F;  // Light Red
                        pal[CHDK_COLOR_BASE+3]  = 0x373BFAE;  // Green
                        pal[CHDK_COLOR_BASE+4]  = 0x34BD6CA;  // Dark Green
                        pal[CHDK_COLOR_BASE+5]  = 0x395AB95;  // Light Green
                        pal[CHDK_COLOR_BASE+6]  = 0x34766F0;  // Blue
                        pal[CHDK_COLOR_BASE+7]  = 0x31250F3;  // Dark Blue
                        pal[CHDK_COLOR_BASE+8]  = 0x37F408F;  // Cyan
                        pal[CHDK_COLOR_BASE+9]  = 0x3512D5B;  // Magenta
                        pal[CHDK_COLOR_BASE+10] = 0x3A9A917;  // Yellow
                        pal[CHDK_COLOR_BASE+11] = 0x3819137;  // Dark Yellow
                        pal[CHDK_COLOR_BASE+12] = 0x3DED115;  // Light Yellow

                        extern char palette_control;
                        palette_control = 1;
                        vid_bitmap_refresh();
        }
    }
}
