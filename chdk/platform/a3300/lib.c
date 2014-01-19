#include "platform.h"
#include "lolevel.h"

void shutdown()
{
	volatile long *p = (void*)0xC02200F4;

	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");

	*p = 0x44;  // power off.

	while(1);
}

#define LED_PR 0xC02200F0


void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[2]={0,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0xa0;	// Found @0xff994830  a3300is
}

long vid_get_viewport_height()
{
	return 240;
}


//Have to disable here and add to /sub for 100a 
//cause 100d crashes when in shoot mode trying to access Alt menu.
//Re-Added in /SUB/100a
//---------------------------------------------------------------
/*void vid_bitmap_refresh() {
	
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}*/

void *vid_get_bitmap_active_palette() {
	extern int active_palette_buffer;
	extern char* palette_buffer[];
	return (palette_buffer[active_palette_buffer]+8);
}

#ifdef CAM_LOAD_CUSTOM_COLORS
// Function to load CHDK custom colors into active Canon palette
void load_chdk_palette() {
	
	extern int active_palette_buffer;
	// Only load for the standard record and playback palettes
	if ((active_palette_buffer == 0) || (active_palette_buffer == 4))
	{
		int *pal = (int*)vid_get_bitmap_active_palette();
		if (pal[CHDK_COLOR_BASE+1] != 0x326EA40)	  // see if CHDK palette already loaded -- if not, load it
		{
		//	pal[CHDK_COLOR_BASE+0]  = 0x33ADF62;  // Red -- We'll use Canon's red because otherwise during boot we get white behind splash
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

