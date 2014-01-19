#include "platform.h"
#include "lolevel.h"

#define LED_AF		0xC022000C
#define LED_ORANGE	0xC0220010
#define LED_GREEN	0xC0220014


extern int enabled_refresh_physical_screen;
void vid_bitmap_refresh()
{
    enabled_refresh_physical_screen=1;
	*(int*)0x829C=3;
	_RefreshPhysicalScreen(1);
	//_ScreenUnLock();
}


void shutdown()
{

/*
ROM:FFC0CD8C                 LDR     R1, =0xC0220000
ROM:FFC0CD90                 MOV     R0, #0x44
ROM:FFC0CD94                 STR     R0, [R1,#0x54]
ROM:FFC0CD98                 STR     R0, [R1,#0x4C]


C0220000+54+4C=0xC02200A0

*/

	volatile long *p = (void*)0xC02200A0;    
	
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
// *(int*)LED_AF=state ? 0x46 : 0x44;
 *(int*)LED_GREEN=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[5]={0,1,9,10,11};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 132;	// at 0xFFD39830, DebugAssert if param_id >= 132
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x876, 1);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x877, 1);  // RotateJogDialLeft
}
