#include "platform.h"
#include "lolevel.h"


void vid_bitmap_refresh()
{
 	extern int full_screen_refresh;
	extern void _LockAndRefresh(); // wrapper function for screen lock
	extern void _UnlockAndRefresh(); // wrapper function for screen unlock

	full_screen_refresh |= 3; //found in ScreenUnlock
	_LockAndRefresh();
	_UnlockAndRefresh();
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

#define LED_PR 0xC0220130 //elph100


void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
	static char led_table[2]={0,9};
	_LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
	return 0xa0;  //@FF9ADCAC near to "BIC     R4, R4, #0x8000" & "PropertyTableManagerCore.c" or 0x80
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.


int vid_get_viewport_width()
{
	// viewport width table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_w[4] = { 360, 360, 360, 270 };//{ 360, 480, 360, 272 };
	return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_xoffset()
{
	// viewport width offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_w[4] = {0, 0, 0, 44};//{ 60, 0, 36, 104 };				// should all be even values for edge overlay
	return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

long vid_get_viewport_height()
{
	// viewport height table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_h[4] = { 240, 180, 214, 240};//{ 240, 240, 240, 240 };
	return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_yoffset()
{
	// viewport height offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1
	static long vp_h[4] = { 0, 30, 13, 0 };
	return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

// Functions for PTP Live View system
// 256 entry palette based on 100b sub_FF926708 ixus115 101a
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }

void *vid_get_bitmap_active_palette() {
        extern int active_palette_buffer;
        extern char* palette_buffer[];
        return (palette_buffer[active_palette_buffer]+8);
}

#ifdef CAM_LOAD_CUSTOM_COLORS
// Function to load CHDK custom colors into active Canon palette
 
void load_chdk_palette() {

        extern int active_palette_buffer;
        // Only load for the standard record (0) and playback (4) palettes
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

/*          // completely transparent palette for special use
            int n;
            if (pal[0] != 0) {
                for (n=0; n<256; n++) {
                    pal[n] = 0;
                }
                extern char palette_control;
                palette_control = 1;
                vid_bitmap_refresh();
            }
*/
        }
}
#endif

// following routines help preventing the "invisible af lock" caused by the movie af scan hack

static int af_locked_in_movierec = 0;

void makeafscan_hack(int *a, int b) {
    _DoAFLock();
    af_locked_in_movierec = 1;
}

void state_check_for_movie_af() {
    if ((movie_status != VIDEO_RECORD_IN_PROGRESS) && af_locked_in_movierec) {
        af_locked_in_movierec = 0;
        _UnlockAF();
    }
}
