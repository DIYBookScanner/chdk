/*
###########################################################
###########################################################
#############[ FINISHED ] #################################
###########################################################
###########################################################
*/ 

#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()    // G10 : ixus980_sd990 version seems to work well
{
	_ScreenLock();
    _RefreshPhysicalScreen(1);
}

// converted to A2100
void shutdown()    // G10 sub_FF829EC8
{
	volatile long *p = (void*)0xC0220084;    // G10 @ 0xFF829EE4,0xFF829EE8 & 0xFF829EEC 
											// A2100IS: C0220000 + 84 @0xFFC18434
	
	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");
	
	*p = 0x44;  // power off.
	
	while(1);
}


void debug_led(int state)
{
#define LED_AF 0xC022000C		// A2100IS Red - AutoFocus led
  *(int*)LED_AF=state ? 0x46 : 0x44;
}

/*
// G10 has 8 led values - tested with uBasic  set_led n, 1   (no brightness control implemented)
// #  Index   LED
// 1   0      Upper indicator Green
// 2   1      Upper indicator Orange
// 3   2      Lower indicator Yellow
// 4   3      Power LED Green
// 5   8      Blue print button LED
// 6   9      AF Assist Lamp
//     10     "
//     11     "
// 7   14     ISO LED
// 8   15     EV LED
*/
// converted to A2100
void camera_set_led(int led, int state, int bright) {
 static char led_table[3]={3,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

// int get_flash_params_count(void){
 // return 0x78 ;		// G10 per SD990 & finsig2 - _sub_FF971C10__PropertyTableManagerCore.c__6 value at 0xff971c50 in 1.02a
 // // found in GetParameterData
// }

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
// int vid_get_viewport_yscale() {
	// return 2;               // G10 viewport is 480 pixels high
// }
