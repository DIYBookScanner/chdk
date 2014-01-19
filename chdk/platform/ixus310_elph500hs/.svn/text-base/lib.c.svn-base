#include "platform.h"
#include "lolevel.h"


extern  int     active_raw_buffer;
extern  char*   raw_buffers[];

char *hook_raw_image_addr()
{
    return raw_buffers[active_raw_buffer*3];
}

char *hook_alt_raw_image_addr()
{
    return raw_buffers[(active_raw_buffer^1)*3];
}


char *camera_jpeg_count_str()
{
    extern char jpeg_count_str[];
	return jpeg_count_str;
}


void vid_bitmap_refresh()
{
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}


void shutdown()
{
	volatile long *p = (void*)0xC022001C;    
	
	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");
	
	*p = 0x44;  // power off.
	
	while(1);
}

#define LED_PR 0xC0220110	// Power Indicator

void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

// IXUS 310 has 2 led values
// 0/7 - Power LED (Green)
// 1/11 - AF Assist Lamp
void camera_set_led(int led, int state, int bright) {
 static char led_table[2]={7,11};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0xA0;	// found in GetParameterData
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

// Defined in stubs_min.S
extern char active_viewport_buffer;
extern void* viewport_buffers[];

void *vid_get_viewport_fb()
{
    // Return first viewport buffer - for case when vid_get_viewport_live_fb not defined
    // Offset the return value because the viewport is left justified instead of centered on this camera
    return viewport_buffers[0];
}

void *vid_get_viewport_live_fb()
{
    if (camera_info.state.mode_video || (movie_status==VIDEO_RECORD_IN_PROGRESS))
        return viewport_buffers[0];     // Video only seems to use the first viewport buffer.

    // Hopefully return the most recently used viewport buffer so that motion detect, histogram, zebra and edge overly are using current image data
    // Offset the return value because the viewport is left justified instead of centered on this camera
    return viewport_buffers[(active_viewport_buffer-1)&3];
}

void *vid_get_viewport_fb_d()
{
    extern char *viewport_fb_d;
	return viewport_fb_d;
}

// Defined in stubs_min.S
extern int active_bitmap_buffer;
extern char* bitmap_buffer[];

void *vid_get_bitmap_fb()
{
    // Return first bitmap buffer address
    return bitmap_buffer[0];
}

// Physical width of viewport row in bytes
int vid_get_viewport_byte_width() {
	return 960 * 6 / 4;     // IXUS 310 - wide screen LCD is 960 pixels wide, each group of 4 pixels uses 6 bytes (UYVYYY)
}

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int vid_get_viewport_yscale() {
	return 2;               // IXUS 310 viewport is 480 pixels high
}

int vid_get_viewport_width()
{
	if (camera_info.state.mode_play)
    {
        return 480;
    }
    extern int _GetVRAMHPixelsSize();
    return _GetVRAMHPixelsSize() >> 1;
}

int vid_get_viewport_display_xoffset()
{
	if (camera_info.state.mode_play)
    {
        return 0;
    }
    else 
    {
        // viewport width offset table for each image size
	    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	    static long vp_w[5] = { 60, 0, 36, 104 };				// should all be even values for edge overlay
	    return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

long vid_get_viewport_height(){ return 240; }

// Functions for PTP Live View system

int vid_get_viewport_width_proper()             { return vid_get_viewport_width() * 2; }
int vid_get_viewport_display_xoffset_proper()   { return vid_get_viewport_display_xoffset() * 2; }
int vid_get_viewport_height_proper()            { return 480; }
int vid_get_viewport_buffer_width_proper()      { return 960; }
int vid_get_viewport_fullscreen_height()        { return 480; }
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }
int vid_get_aspect_ratio()                      { return 1; }

void *vid_get_bitmap_active_buffer()
{
    return bitmap_buffer[active_bitmap_buffer];
}

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern char* palette_buffer[];
    return (palette_buffer[active_palette_buffer]+8);
}

// Function to load CHDK custom colors into active Canon palette
void load_chdk_palette()
{
    extern int active_palette_buffer;
    // Only load for the standard record and playback palettes
    if ((active_palette_buffer == 0) || (active_palette_buffer == 16))
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
