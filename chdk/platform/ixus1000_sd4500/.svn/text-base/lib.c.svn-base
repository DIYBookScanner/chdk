#include "platform.h"
#include "lolevel.h"

/*
void vid_bitmap_refresh() //ASM1989
{
 extern int enabled_refresh_physical_screen;
 enabled_refresh_physical_screen=1;
 *(int*)0x9D08=3;//this is set somewhere in a function called by RefreshPhysicalScreen, should be easy to find
 _RefreshPhysicalScreen(1);
}

*/
/*
void shooting_set_iso_real(short iso, short is_now)
{
    long iso2=iso;
if ((mode_get()&MODE_MASK) != MODE_PLAY){
	if (iso>0){ _SetPropertyCase(PROPCASE_ISO_MODE, &iso2, sizeof(iso2));
	//_SetPropertyCase(PROPCASE_SV_MARKET, &iso2, sizeof(iso2));
    }
}
}
*/

void vid_bitmap_refresh()
{
	extern int enabled_refresh_physical_screen;
	extern int full_screen_refresh;

	// i've tried refreshphysical screen (screen unlock) and that caused the canon and
	// function menu to not display at all. This seems to work and is called in a similar
	// way in other places where original OSD should be refreshed.
	extern void _LockAndRefresh(); // wrapper function for screen lock
	extern void _UnlockAndRefresh(); // wrapper function for screen unlock

	_LockAndRefresh();

	enabled_refresh_physical_screen=1;
	full_screen_refresh=3; //found in ScreenUnlock underneath a CameraLog.c call sub_FFA02598

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

#define LED_PR 0xC0220138    // -> 0xC0223030 maybe front led ASM1989 ixus1000  found at  FF929BDC


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
 _PostLogicalEventForNotPowerType(0x877, 1);  // RotateJogDialRight  old 874
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x876, 1);  // RotateJogDialLeft  old 875
}
