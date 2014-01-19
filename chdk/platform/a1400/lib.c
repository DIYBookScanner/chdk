#include "platform.h"
#include "lolevel.h"


char *camera_jpeg_count_str()
{
    extern char jpeg_count_str[];
    return jpeg_count_str;
}

#define LED_PR 0xC0220120
void shutdown()
{
    extern void _TurnOffE1(void);
    _TurnOffE1();
    while(1);
}

void debug_led(int state)
{
    // using power LED, which defaults to on
    // for debugging turn LED off if state is 1 and on for state = 0
     *(int*)LED_PR=state ? 0x46 : 0x44;
}

// A1400 has three 'lights' - Power (Green) LED, Orange LED and AF assist lamp
// Green Led = first entry in table (led 0)
// Orange Led = first entry in table (led 0)
// AF Assist Lamp = second entry in table (led 1)
void camera_set_led(int led, int state, int bright) {
    static char led_table[3]={0,1,4};
    if(state<=1) _LEDDrive(led_table[led%sizeof(led_table)], (!state)&1);
}

int get_flash_params_count(void){ return 0x91; }
char *hook_raw_image_addr()      {return (char*) 0x420e5c30;}   //Found @0xffb16a34 a1400 100b
long hook_raw_size()             { return 0x01794300; }         //Found @0xffb16a8c a1400 100b

int vid_get_viewport_width()     { return 360;  }
long vid_get_viewport_height()   { return 240;  }


// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.
void *vid_get_bitmap_fb()        { return (void*)0x40431000; }   // Found @0xff85ce98
void *vid_get_viewport_fb()      { return (void*)0x40586b80; }   // Found @0xffb1511c

void *vid_get_viewport_fb_d()
{
    extern char *viewport_fb_d;
    return viewport_fb_d;
}

//To do
void *vid_get_viewport_live_fb()
{
    extern char active_viewport_buffer;
    extern void* viewport_buffers[];

    if (MODE_IS_VIDEO(mode_get()) || is_video_recording())
        return viewport_buffers[0];     // Video only seems to use the first viewport buffer.

    // Hopefully return the most recently used viewport buffer so that motion detect, histogram, zebra and edge overly are using current image data
    // verified -1 gives best response
    return viewport_buffers[(active_viewport_buffer-1)&3];
}


void vid_bitmap_refresh()
{
    extern int full_screen_refresh;
    extern void _ScreenLock();
    extern void _ScreenUnlock();

    full_screen_refresh |= 3;
    _ScreenLock();
    _ScreenUnlock();
}

void *vid_get_bitmap_active_palette() // from ixus140_elph130
{
    extern int active_palette_buffer;
    extern int** palette_buffer_ptr;
    int *p = palette_buffer_ptr[active_palette_buffer];
    // active_palette_buffer can point at null when
    // func and menu are opened for the first time
    if(!p) {
        p = palette_buffer_ptr[0]; // rec mode buffer appears to always be initialized
    }
    return (p+1);
}

#ifdef CAM_LOAD_CUSTOM_COLORS
// Function to load CHDK custom colors into active Canon palette

void load_chdk_palette() {

    extern int active_palette_buffer;
    // Only load for the standard record and playback palettes
    if ((active_palette_buffer == 0) || (active_palette_buffer == 5))
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
#endif

// Functions for PTP Live View system
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x5AE0+0x18)); //found @ loc_FF92292C a1400 100b
}
