#include "platform.h"
#include "lolevel.h"

// only two LEDs in A495 - the same in a800
#define LED_PR 0xC0220088  // green LED
#define LED_AF 0xC0220080  // orange AF LED - não sei


void shutdown()
{
    volatile long *p = (void*)LED_PR;    // Green LED

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
    *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
    long val = state ? 0x46 : 0x44;
    switch ( led )
    {
    default:
        *(int*)LED_PR = val;
    }
}

void vid_bitmap_refresh()// as ixus220 instead of a495
{
 	extern int full_screen_refresh;
	extern void _ScreenLock(); // wrapper function for screen lock
	extern void _ScreenUnlock(); // wrapper function for screen unlock

	full_screen_refresh |= 3; //found in ScreenUnlock
	_ScreenLock();	
	_ScreenUnlock();
}


// Near "PropertyTableManagerCore.c" ROM:FFD2ED94
int get_flash_params_count(void) {
 return 0xa0; 
 }              // Found @0xffd3af20 de stub_entry.S

/*void vid_turn_off_updates()
{
    extern void _LockAndRefresh();   // wrapper function for screen lock

    _LockAndRefresh();
}

void vid_turn_on_updates()
{
    extern void _UnlockAndRefresh();   // wrapper function for screen unlock

    //_RefreshPhysicalScreen(1);
    _UnlockAndRefresh();
}*/
