#include "platform.h"
#include "lolevel.h"

char *hook_raw_image_addr()
{
	return (char*) 0x10e59860;  // a800 1.00b at ffe7307C 
}

void *vid_get_viewport_live_fb()   // Live picture buffer (shoot not pressed)
{
	return (void*)0;
}

// OSD buffer
long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe72ff4
void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3fafc
void *vid_get_viewport_fb()      { return (void*)0x1068c2e0; }             // Found @0xffe6fb54
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2588+0x54)); } // Found @0xffc543b8 & 0xffc543f0
long vid_get_bitmap_screen_width() { return 360; }
long vid_get_bitmap_screen_height() { return 240; }
long vid_get_viewport_height() { return 240; }
long vid_get_bitmap_buffer_width() { return 360; }
long vid_get_bitmap_buffer_height() { return 240; }

char *camera_jpeg_count_str()    { return (char*)0x00088994; }             // Found @0xffd810bc

//int get_flash_params_count(void) { return 0xa0; }                          // Found @0xffd3af20

/*
Note copied from SX110 IS
GetBatteryTemperature usually will get back temperature of battery compartment/batteries. GetBatteryTemperature is implemented in Canon's firmware for SX120IS.
Firmware entry point is identified (0xFFC394D8) but function is not usable. Camera will crash if Canon's GetBatteryTemperature is called by CHDK.
To avoid a crash Canon's GetBatteryTemperature must not called. As long CHDK general code do not distinguish between cameras that support or don't support GetBatteryTemperature, 
this function will be implemented as specific CHDK-code. It returns always with -99 (which means -99° Celsius or -146° Fahrenheit).
Original entry point in Canon's firmware is disabled (in stubs_entry.S).
*/

int _GetBatteryTemperature()
{
      return -99;
}
