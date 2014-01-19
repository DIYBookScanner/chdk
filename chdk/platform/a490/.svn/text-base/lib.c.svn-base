#include "platform.h"
#include "lolevel.h"

// only two LEDs in A490:
#define LED_PR 0xC0220088  // green LED
#define LED_AF 0xC0220080  // orange AF LED


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

void vid_bitmap_refresh() {
    extern int enabled_refresh_physical_screen;
    extern int full_screen_refresh;

    // asm1989: i've tried refreshphysical screen (screen unlock) and that caused the canon and
    // function menu to not display at all. This seems to work and is called in a similar
    // way in other places where original OSD should be refreshed.
    extern void _ScreenLock();   // wrapper function for screen lock
    extern void _ScreenUnlock();   // wrapper function for screen unlock

    _ScreenLock();

    enabled_refresh_physical_screen=1;
    full_screen_refresh=3;   // found in ScreenUnlock underneath a CameraLog.c call

    _ScreenUnlock();
}

// Near "PropertyTableManagerCore.c" ROM:FFD2EBD8
int get_flash_params_count(void){
    return 0x74;
}


// This camera crashes if GetBatteryTemperature is called, override auto detected stub
int _GetBatteryTemperature()
{
      return -99;
}

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
