#include "platform.h"
#include "lolevel.h"

void shutdown() // method taken from the ixus140_elph130 port
{
    extern void _TurnOffE1(void);
    _TurnOffE1();
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
 return 0xa0;	// Found @0xff9941e4
}

long vid_get_viewport_height()
{
	return 240;
}

void vid_bitmap_refresh() {
	
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}

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

int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }
