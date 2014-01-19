#include "platform.h"

/*
note sensor size for camera.h is from 
@ FFE68804
0xED09F0 = 15534576
15534576/12 * 8 - 10356384  ---
                              |
@ FFE6857C                    |
0xE90 and 0xADA =             |
3728  *  2778   = 10356384  ---
*/

char *hook_raw_image_addr()
{
// 0x4110C564 at FFC3D108 and FFC3CE4C
// 0x414EF7E0 at FFE6888C and FFE687A8; search for "CRAW BUFF"
// FFE687A8      LDR     R6, =0x414EF7E0
// ...
// FFE687F8      MOV     R1, R6
// FFE687FC      ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"
// 0x2b24 at FFC51140 and 0x53A4+0x18 at 0xFFC518D4
//	return (char*) (*(int*)(0x2B24+0x18) ? 0x4110C564 : 0x414EF7E0);
	return (char*)(0x414EF7E0);	
}

long hook_raw_size()
{
//ROM:FFE68804         LDR     R1, =0xED09F0
//ROM:FFE68808         ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
//ROM:FFE6880C         BL      sub_FFCE4CB4
    return 0xED09F0;
}


void *vid_get_viewport_live_fb()
{
   void **fb=(void **)0x217C; //FFC27234, look also at FFC26C8C
   unsigned char buff = *((unsigned char*)0x1FD0); //FFC27230, look also at FFC26C3C
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
    return (void*)0x403F1000;	// FFDE8EB0 and FFDE8C78; search for "Faexe Error"
}

void *vid_get_viewport_fb()
{
    return (void*)0x40768620;	// FFE662E4 and FFE660B4; search for "VRAM Address" in DCB section
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x2904+0x58));	// 0x2904 at FFC46988; 0x58 at FFC471EC
}

int vid_get_viewport_width()
{
    return 360;
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
// Found at ROM:FFD83ECC and ROM:FFD83D88 - search for "ShotsTime.c" and "9999"
    return (void*)0x52C6C;
}


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


