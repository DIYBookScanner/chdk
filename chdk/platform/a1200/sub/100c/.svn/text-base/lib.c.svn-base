#include "platform.h"

// autofound in stubs_entry.S

void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff85b414
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2970+0x58)); } // Found @0xff870968 & 0xff8709a0
char *camera_jpeg_count_str()    { return (char*)0x000b3b14; }             // Found @0xff9f76c4
long hook_raw_size()             { return 0x011e4ee0; }                    // Found @0xffb1c030
int  get_flash_params_count(void) { return 0xa0; }                          // Found @0xff98e87c


char *hook_raw_image_addr() {

        // if (*((int*)(0x2B68 + 0xC)) != 0)
        //      return (char*) 0x46000000;
        // else
        //      return (char*) 0x421316C0;

    return (char*)  0x41BDED00; //  instruction @ 0xffb1bfd8  -> data @0xffb1c0b8
}

char *hook_alt_raw_image_addr() {

        // if (*((int*)(0x2B68 + 0xC)) != 0)
        //      return (char*) 0x46000000;
        // else
        //      return (char*) 0x421316C0;

    return (char*) 0x41BDED00 ; //  instruction @ 0xffb1bfd8  -> data @0xffb1c0b8
}

void vid_bitmap_refresh() {

    extern int full_screen_refresh;
    extern void _LockAndRefresh();      // wrapper function for screen lock
    extern void _UnlockAndRefresh();    // wrapper function for screen unlock

    full_screen_refresh |= 3;
    _LockAndRefresh();
    _UnlockAndRefresh();
}

/*
 * Note copied from SX110 IS
 * GetBatteryTemperature usually will get back temperature of battery compartment/batteries. GetBatteryTemperature is implemented in Canon's firmware for SX120IS.
 * Firmware entry point is identified (0xFFC394D8) but function is not usable. Camera will crash if Canon's GetBatteryTemperature is called by CHDK.
 * To avoid a crash Canon's GetBatteryTemperature must not called. As long CHDK general code do not distinguish between cameras that support or don't support GetBatteryTemperature,
 * this function will be implemented as specific CHDK-code. It returns always with -99 (which means -99° Celsius or -146° Fahrenheit).
 * Original entry point in Canon's firmware is disabled (in stubs_entry.S).
 * */

int _GetBatteryTemperature()
{
      return -99;
}
