#include "platform.h"

char *hook_raw_image_addr()     {return (char*) 0x420B7FC0;}   //Found @0xffae0ef4 a810
char *hook_alt_raw_image_addr() {return (char*) 0x420B7FC0;}   //Found @0xffae0ef4 a810

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x2274;
    unsigned char buff = *((unsigned char*)0x2094);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

/*
 * Note copied from SX110 IS
 * GetBatteryTemperature usually will get back temperature of battery compartment/batteries. GetBatteryTemperature is implemented in Canon's firmware for SX120IS.
 * Firmware entry point is identified (0xFFC394D8) but function is not usable. Camera will crash if Canon's GetBatteryTemperature is called by CHDK.
 * To avoid a crash Canon's GetBatteryTemperature must not called. As long CHDK general code do not distinguish between cameras that support or don't support GetBatteryTemperature,
 * this function will be implemented as specific CHDK-code. It returns always with -99 (which means -99° Celsius or -146° Fahrenheit).
 * Original entry point in Canon's firmware is disabled (in stubs_entry.S).
 * */
int _GetBatteryTemperature()     { return -99;}

/*Auto generated for a810*/
void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff8521ac
void *vid_get_viewport_fb()      { return (void*)0x40566b80; }             // Found @0xffadf4cc
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2950+0x54)); } // Found @0xff867ad4 & 0xff867b0c
char *camera_jpeg_count_str()    { return (char*)0x000b3b6c; }             // Found @0xff9c9308
long hook_raw_size()             { return 0x01794300; }                    // Found @0xffae2300
int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff985714
