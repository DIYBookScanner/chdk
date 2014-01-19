#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
 	extern int full_screen_refresh;
	extern void _ScreenLock(); // wrapper function for screen lock
	extern void _ScreenUnlock(); // wrapper function for screen unlock

	full_screen_refresh |= 3; //found in ScreenUnlock
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

#define LED_PR 0xC0220130

void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[2]={0,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0x9F;  //@FF1B4C5C in GetParameterData
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
    if (MODE_IS_VIDEO(mode_get()) || (movie_status==VIDEO_RECORD_IN_PROGRESS))
        return viewport_buffers[0];     // Video only seems to use the first viewport buffer.

    // Hopefully return the most recently used viewport buffer so that motion detect, histogram, zebra and edge overly are using current image data
    // Offset the return value because the viewport is left justified instead of centered on this camera
    return viewport_buffers[(active_viewport_buffer-1)&3];
}

long vid_get_bitmap_screen_width() { return 360; }
long vid_get_bitmap_screen_height() { return 240; }
long vid_get_bitmap_buffer_width() { return 960; }
long vid_get_bitmap_buffer_height() { return 270; }

int vid_get_viewport_buffer_width() { return 360; }

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int vid_get_viewport_yscale() {
	return 2;               // ixus230/ixus3310 viewport is 480 pixels high
}

int vid_get_viewport_width()
{
	// viewport width table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_w[5] = { 360, 360, 360, 272 };
	return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_xoffset()
{
	// viewport width offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_w[5] = { 0, 0, 0, 44 };				// should all be even values for edge overlay
	return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

long vid_get_viewport_height()
{
	// viewport height table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_h[5] = { 240, 180, 214, 240 };
	return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_yoffset()
{
	// viewport height offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_h[5] = { 0, 30, 13, 0 };
	return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_display_xoffset()
{
	if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else 
    {
        // viewport width offset table for each image size
	    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
        static long vp_w[5] = { 0, 0, 0, 0 };    // should all be even values for edge overlay
	    return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

// Functions for PTP Live View system

int vid_get_viewport_width_proper()             { return vid_get_viewport_width() * 2; }
int vid_get_viewport_display_xoffset_proper()   { return vid_get_viewport_display_xoffset() * 2; }
int vid_get_viewport_height_proper()            { return 480; }
int vid_get_viewport_buffer_width_proper()      { return 960; }
int vid_get_viewport_fullscreen_height()        { return 480; }
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }
int vid_get_aspect_ratio()                      { return 1; }

// Defined in stubs_entry.S
extern int active_bitmap_buffer;
extern char* bitmap_buffer[];

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
