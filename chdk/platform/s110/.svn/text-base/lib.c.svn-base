#include "platform.h"
#include "lolevel.h"

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

#define LED_PR 0xC022C30C

void debug_led(int state)
{
    volatile long *p = (void*)LED_PR;
    if (state)
        *p = *p | 0x21;
    else
        *p = (*p & 0xFFFFFFDF) | 0x1;
}


// S110 led values:
// 4 AF Assist Lamp
// 8 Wi-Fi LED
void camera_set_led(int led, int state, int bright) {
 static char led_table[2] = {4, 8};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void) { return 0xa6; }                          // Found @0xf8278320

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x871, 1);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x872, 1);  // RotateJogDialLeft
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

/* TODO: currently using sigfinder's data 
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
    return viewport_buffers[(active_viewport_buffer-1)&7];
}
*/

void *vid_get_viewport_live_fb()
{
    return vid_get_viewport_fb();
}

// Defined in stubs_min.S
extern int active_bitmap_buffer;
extern char* bitmap_buffer[];

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int vid_get_viewport_yscale() {
	return 2;
}

int vid_get_viewport_width()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 360;
    }
    extern int _GetVRAMHPixelsSize();
    return _GetVRAMHPixelsSize() >> 1;
}

// viewport width offset table for each image size
// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
static long vp_xo[5] = { 0, 0, 0, 44, 72 };				// should all be even values for edge overlay

int vid_get_viewport_xoffset()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else if (shooting_get_prop(PROPCASE_SHOOTING_MODE) == MODE_STITCH) // Stitch mode
    {
        return 0;
    }
    else
    {
        return vp_xo[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

int vid_get_viewport_display_xoffset()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else if (shooting_get_prop(PROPCASE_SHOOTING_MODE) == MODE_STITCH)
    {
        if (shooting_get_prop(PROPCASE_STITCH_DIRECTION) == 0)      // Direction check
            if (shooting_get_prop(PROPCASE_STITCH_SEQUENCE) == 0)   // Shot already taken?
                return 40;
            else
                return 140;
        else
            if (shooting_get_prop(PROPCASE_STITCH_SEQUENCE) == 0)   // Shot already taken?
                return 140;
            else
                return 40;
    }
    else
    {
        return vp_xo[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

long vid_get_viewport_height()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 240;
    }
    extern int _GetVRAMVPixelsSize();
    return _GetVRAMVPixelsSize() >> 1;
}

static int vp_yoffset(int stitch)
{
    // viewport height offset table for each image size
    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
    static long vp_yo[5] = { 0, 30, 13, 0, 0 };

    int m = mode_get();
    if ((m & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else if (shooting_get_prop(PROPCASE_SHOOTING_MODE) == MODE_STITCH)
    {
        return stitch;
    }
    else if (mode_is_video(m) || movie_status == VIDEO_RECORD_IN_PROGRESS)
    {
        return 30;
    }
    else
    {
	    return vp_yo[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

int vid_get_viewport_yoffset()
{
    return vp_yoffset(0);
}

int vid_get_viewport_display_yoffset()
{
    return vp_yoffset(72);
}

// Functions for PTP Live View system
int vid_get_viewport_display_xoffset_proper()   { return vid_get_viewport_display_xoffset() * 2; }
int vid_get_viewport_display_yoffset_proper()   { return vid_get_viewport_display_yoffset() * 2; }
int vid_get_viewport_width_proper()             { return vid_get_viewport_width() * 2; }
int vid_get_viewport_height_proper()            { return vid_get_viewport_height() * 2; }
int vid_get_viewport_fullscreen_height()        { return 480; }
int vid_get_palette_type()                      { return 5; }
int vid_get_palette_size()                      { return 256 * 4; }

void *vid_get_bitmap_active_buffer()
{
    return bitmap_buffer[active_bitmap_buffer];
}

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern char* palette_buffer[];
    return (palette_buffer[active_palette_buffer]+4);
}

// Function to load CHDK custom colors into active Canon palette
void load_chdk_palette()
{
    extern int active_palette_buffer;
    // Only load for the standard record and playback palettes
    if ((active_palette_buffer == 0) || (active_palette_buffer == 5) || (active_palette_buffer == 6))
    {
        int *pal = (int*)vid_get_bitmap_active_palette();
        if (pal[CHDK_COLOR_BASE+0] != 0x3F3ADF62)
        {
            pal[CHDK_COLOR_BASE+0]  = 0x3F3ADF62;  // Red
            pal[CHDK_COLOR_BASE+1]  = 0x3F26EA40;  // Dark Red
            pal[CHDK_COLOR_BASE+2]  = 0x3F4CD57F;  // Light Red
            pal[CHDK_COLOR_BASE+3]  = 0x3F73BFAE;  // Green
            pal[CHDK_COLOR_BASE+4]  = 0x3F4BD6CA;  // Dark Green
            pal[CHDK_COLOR_BASE+5]  = 0x3F95AB95;  // Light Green
            pal[CHDK_COLOR_BASE+6]  = 0x3F4766F0;  // Blue
            pal[CHDK_COLOR_BASE+7]  = 0x3F1250F3;  // Dark Blue
            pal[CHDK_COLOR_BASE+8]  = 0x3F7F408F;  // Cyan
            pal[CHDK_COLOR_BASE+9]  = 0x3F512D5B;  // Magenta
            pal[CHDK_COLOR_BASE+10] = 0x3FA9A917;  // Yellow
            pal[CHDK_COLOR_BASE+11] = 0x3F819137;  // Dark Yellow
            pal[CHDK_COLOR_BASE+12] = 0x3FDED115;  // Light Yellow

            extern char palette_control;
            palette_control = 1;
            vid_bitmap_refresh();
        }
    }
}

