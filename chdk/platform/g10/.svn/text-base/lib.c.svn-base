#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()    // G10 : ixus980_sd990 version seems to work well
{
	_ScreenLock();
    _RefreshPhysicalScreen(1);
}


void shutdown()    // G10 sub_FF829EC8
{
	volatile long *p = (void*)0xC022001C;    // G10 @ 0xFF829EE4,0xFF829EE8 & 0xFF829EEC 
	
	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");
	
	*p = 0x44;  // power off.
	
	while(1);
}


// 0xC02200D0  G10 ISO select dial LED
// 0xC02200D4  G10 direct print button LED
// 0xC02200D8  G10 exposure compensation dial LED
// 0xC02200DC  G10 power LED
// 0xC0220130  G10 Upper Indicator Orange (looks yellow if both upper indicators lit)
// 0xC0220134  G10 Upper Indicator Green
// 0xC0220138  G10 Lower Indicator Yellow
#define LED_PR 	0xC02200D4	//  G10 direct print button LED

void debug_led(int state)
{
  *(int*)LED_PR=state ? 0x46 : 0x44;
}

// G10 has 8 led values - tested with uBasic  set_led n, 1   (no brightness control implemented)
// set_led led_table  LED
// ======= =========  =====================
//   0         0      Upper indicator Green
//   1         1      Upper indicator Orange
//   2         2      Lower indicator Yellow
//   3         3      Power LED Green
//   4         8      Blue print button LED
//   5         9      AF Assist Lamp (also index 9&10)
//   6         14     ISO LED
//   7         15     EV LED

void camera_set_led(int led, int state, int bright) {
 static char led_table[8]={0,1,2,3,8,9,14,15};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0x78 ;		// G10 per SD990 & finsig2 - _sub_FF971C10__PropertyTableManagerCore.c__6 value at 0xff971c50 in 1.02a
 // found in GetParameterData
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x86E, 1);  // RotateJogDialRight (G10 1.02A table @ FFB43EEC)
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x86F, 1);  // RotateJogDialLeft (G10 1.02A table @ FFB43EF8)
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

int vid_get_viewport_width()
{
	return 360 ;   //  G10
}

long vid_get_viewport_height()
{
   return 240;    //  G10
}

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int vid_get_viewport_yscale() {
	return 2;               // G10 viewport is 480 pixels high
}

// looks like 256 byte from sub_FF8F3270
int vid_get_palette_type() { return 3; }
int vid_get_palette_size() { return 256*4; }

// TODO actual value probably varies in some cases
int vid_get_viewport_height_proper() { return 480; }
int vid_get_viewport_fullscreen_height() { return 480; }

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern char** palette_buffer_ptr;
    return palette_buffer_ptr[active_palette_buffer]+16;
}

void load_chdk_palette()
{
    extern char** palette_buffer_ptr;
    extern int active_palette_buffer;

    if ((active_palette_buffer == 0) || (active_palette_buffer == 1))
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

            // extern char palette_control;
            // palette_control = 1;
            vid_bitmap_refresh();
        }
    }
}

