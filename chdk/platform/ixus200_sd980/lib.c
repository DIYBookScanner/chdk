#include "platform.h"
#include "lolevel.h"

extern int enabled_refresh_physical_screen;
void vid_bitmap_refresh()
{
	enabled_refresh_physical_screen=1;
	*(int*)0x1B2DC=3;//this is set somewhere in a function called by RefreshPhysicalScreen, should be easy to find

	_RefreshPhysicalScreen(1);
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

void ubasic_set_led(int led, int state, int bright) {
 static char led_table[5]={4,5,7,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[5]={4,5,7,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void) 
{ 
	return 0x84;                           // Found @0xff979b5c
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}
