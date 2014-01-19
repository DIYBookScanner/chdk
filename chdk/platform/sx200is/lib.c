#include "platform.h"
#include "lolevel.h"

//from ixus870_sd880
void vid_bitmap_refresh()
{
 extern int enabled_refresh_physical_screen; // screen lock counter
 int old_val = enabled_refresh_physical_screen;
 if ( old_val == 0 )
 {
   _ScreenLock(); // make sure code is called at least once
 } else {
   enabled_refresh_physical_screen=1; // forces actual redraw
 }
 _RefreshPhysicalScreen(1); // unlock/refresh

 // restore original situation
 if ( old_val > 0 )
 {
   _ScreenLock();
   enabled_refresh_physical_screen = old_val;
 }
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

#define LED_PR 0xC0220138

void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[5]={4,5,7,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 120; 
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 1);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 1);  // RotateJogDialLeft
}

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern int** palette_buffer_ptr;
    return (palette_buffer_ptr[active_palette_buffer]+0x3);
}

// Function to load CHDK custom colors into active Canon palette
void load_chdk_palette()
{
    extern int active_palette_buffer;
    // Only load for the standard record and playback palettes
    if ((active_palette_buffer == 0) || (active_palette_buffer == 2) || (active_palette_buffer == 3))
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
            pal[CHDK_COLOR_BASE+13] = 0x00A0000;  // Transparent Light Grey
//          pal[CHDK_COLOR_BASE+13] = 0x10A0000;  // Transparent Grey
//          pal[CHDK_COLOR_BASE+13] = 0x2190000;  // Transparent Dark Grey

            extern char palette_control;
            palette_control = 1;
            vid_bitmap_refresh();
        }
    }
}
