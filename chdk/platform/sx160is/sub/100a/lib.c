#include "platform.h"

char *hook_raw_image_addr() {
    return (char*) 0x420F6420; //Found @0xffb5a2f4  search for "BJPEG BUFF"
}

char *hook_alt_raw_image_addr() {
    return (char*) 0x420F6420; //Found @0xffb5a2f4  search for "BJPEG BUFF"
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
