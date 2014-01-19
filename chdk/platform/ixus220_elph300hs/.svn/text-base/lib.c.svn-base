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
 return 0xA0;  //@FF1B33A0 in GetParameterData
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

int vid_get_viewport_buffer_width() { return 360; }

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


// Functions for PTP Live View system
// 256 entry palette based on 100c @ 0xff929a6c
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }

void *vid_get_bitmap_active_palette() {
        extern int active_palette_buffer;
        extern char* palette_buffer[];
        return (palette_buffer[active_palette_buffer]+8);
}

extern int active_bitmap_buffer;
extern char* bitmap_buffer[];

void *vid_get_bitmap_active_buffer() {
    return bitmap_buffer[active_bitmap_buffer];
}
