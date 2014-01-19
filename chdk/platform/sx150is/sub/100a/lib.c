/*
*********************
SX150IS 100.a firmware
**********************
*/

#include "platform.h"

char *hook_raw_image_addr()
{
/*
ROM:FFB4FFE8                 LDR     R5, =0x4159DBE0
ROM:FFB4FFEC                 LDR     R4, =0x409DC9F0
ROM:FFB4FFF0                 LDR     R6, =0x41D65F00  <<<<<<<<<<<<<<<
ROM:FFB50008                 ADR     R0, aJpegBuffPLx ; "JPEG BUFF       %p ( %lx )"
ROM:FFB50020                 BL      sub_FF950780
ROM:FFB50024                 MOV     R1, R5
ROM:FFB50028                 ADR     R0, aImgVramBuffP ; "IMG VRAM BUFF   %p"
ROM:FFB5002C                 BL      sub_FF950780
ROM:FFB50030                 MOV     R1, R4
ROM:FFB50034                 ADR     R0, aThumVramBuffP ; "THUM VRAM BUFF  %p"
ROM:FFB50038                 BL      sub_FF950780
ROM:FFB5003C                 MOV     R1, R6
ROM:FFB50040                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"
ROM:FFB50044                 BL      sub_FF950780
ROM:FFB50048                 LDR     R1, =0x14EB7E0
ROM:FFB5004C                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
*/
	return (char*)(0x41D65F00);
}

/*
ROM:FFB50048                 LDR     R1, =0x14EB7E0  <<<<<<<<<<<<<<<
ROM:FFB5004C                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
*/
long hook_raw_size()
{
		return 0x014eb7e0;
}



// Live picture buffer (shoot not pressed)
void *vid_get_viewport_live_fb()
{


    return 0x0;

}




void *vid_get_bitmap_fb()
{
/*
ROM:FF92A878 sub_FF92A878                            ; CODE XREF: sub_FFA2DAC0+48p
ROM:FF92A878                 STMFD   SP!, {R4-R8,LR}
ROM:FF92A87C                 LDR     R8, =0x5D88
ROM:FF92A880                 MOV     R4, R0
ROM:FF92A884                 LDR     R0, [R8,#0x10]
ROM:FF92A888                 MOV     R5, R1
ROM:FF92A88C                 CMP     R0, #1
ROM:FF92A890                 MOV     R6, R2
ROM:FF92A894                 MOV     R7, R3
ROM:FF92A898                 MOVEQ   R1, #0x18C
ROM:FF92A89C                 ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
ROM:FF92A8A0                 BLEQ    sub_FF81EDBC
ROM:FF92A8A4                 CMP     R4, #0
ROM:FF92A8A8                 CMPNE   R5, #0
ROM:FF92A8AC                 CMPNE   R6, #0
ROM:FF92A8B0                 CMPNE   R7, #0
ROM:FF92A8B4                 LDREQ   R1, =0x18F
ROM:FF92A8B8                 ADREQ   R0, aBmpddev_c  ; "BmpDDev.c"
ROM:FF92A8BC                 BLEQ    sub_FF81EDBC
ROM:FF92A8C0                 MOV     R0, #0x2D0   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Height  0x2D0 dec 720
ROM:FF92A8C4                 MOV     R1, #0xF0    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Width  0xF0   dec 240
ROM:FF92A8C8                 STR     R0, [R4]
ROM:FF92A8CC                 STR     R1, [R5]
ROM:FF92A8D0                 STR     R0, [R6]
ROM:FF92A8D4                 LDR     R0, =0x403F1000 <<<<<<<<<<<<<<<<<
ROM:FF92A8D8                 STR     R0, [R7]
ROM:FF92A8DC                 MOV     R0, #1
ROM:FF92A8E0                 STR     R0, [R8,#0x10]
ROM:FF92A8E4                 MOV     R0, #0
ROM:FF92A8E8                 LDMFD   SP!, {R4-R8,PC}
ROM:FF92A8E8 ; End of function sub_FF92A878
*/
	return (void*)0x403f1000;
}


// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
/*
ROM:FFB4D218 loc_FFB4D218                            ; CODE XREF: sub_FFB4D1DC+28j
ROM:FFB4D218                 MOV     R2, R7
ROM:FFB4D21C                 MOV     R1, R6
ROM:FFB4D220                 MOV     R0, R5
ROM:FFB4D224                 BL      sub_FF855380
ROM:FFB4D228                 LDR     R1, =0x40546B80  <<<<<<<<<<<<<<<<<<<
ROM:FFB4D22C                 LDR     R0, =0x3F480
ROM:FFB4D230                 STR     R1, [R4]
ROM:FFB4D234                 STR     R0, [R4,#4]
ROM:FFB4D238                 ADR     R0, aVramAddressP ; "VRAM Address  : %p\r"
ROM:FFB4D23C                 BL      sub_FF950780
ROM:FFB4D240                 LDR     R1, [R4,#4]
ROM:FFB4D244                 ADR     R0, aVramSize0xX ; "VRAM Size     : 0x%x\r"
ROM:FFB4D248                 BL      sub_FF950780
ROM:FFB4D24C                 MOV     R0, #0
ROM:FFB4D250                 LDMFD   SP!, {R4-R8,PC}
ROM:FFB4D250 ; End of function sub_FFB4D1DC
*/


	return (void*)0x40546B80;
}

// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d()
{

/*
ROM:FF8780C4 ; =============== S U B R O U T I N E =======================================
ROM:FF8780C4
ROM:FF8780C4
ROM:FF8780C4 sub_FF8780C4                            ; CODE XREF: sub_FF889880+1BCp
ROM:FF8780C4                                         ; sub_FF889A5C+90p ...
ROM:FF8780C4                 STMFD   SP!, {R1-R7,LR}
ROM:FF8780C8                 LDR     R5, =0x2710
ROM:FF8780CC                 LDR     R4, =0x2BA8   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF8780D0                 LDR     R3, =0x6D1
ROM:FF8780D4                 LDR     R2, =aImageplayer_c ; "ImagePlayer.c"
ROM:FF8780D8                 LDR     R0, [R4,#0x4C]
ROM:FF8780DC                 MOV     R1, R5
ROM:FF8780E0                 BL      sub_FF83AB9C
ROM:FF8780E4                 MOV     R0, #1
ROM:FF8780E8                 BL      sub_FF8772A8
ROM:FF8780EC                 CMN     R0, #1
ROM:FF8780F0                 BEQ     loc_FF8781C0
ROM:FF8780F4                 LDR     R6, =0x382F4
ROM:FF8780F8                 ADD     R1, R0, R0,LSL#2
ROM:FF8780FC                 LDR     R0, [R6,R1,LSL#2]
ROM:FF878100                 ADD     R12, R6, R1,LSL#2
ROM:FF878104                 STR     R0, [R4,#0x58]   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FF878108                 LDR     R1, [R12,#0xC]
ROM:FF87810C                 LDR     R2, =sub_FF8779C4
ROM:FF878110                 MOV     R3, #0
ROM:FF878114                 STMEA   SP, {R1-R3}
ROM:FF878118                 MOV     R2, #0
ROM:FF87811C                 LDR     R3, [R12,#8]
ROM:FF878120                 MOV     R1, R2
ROM:FF878124                 BL      sub_FF92C098
ROM:FF878128                 TST     R0, #1
ROM:FF87812C                 LDRNE   R1, =0x6F7
ROM:FF878130                 LDRNE   R0, =aImageplayer_c ; "ImagePlayer.c"
*/

    return (void*)(*(int*) (0x2BA8+0x58));
}

char *camera_jpeg_count_str()
/*
ROM:FFA1EA90 ; jumptable FFA1E9E8 entry 2
ROM:FFA1EA90                 LDR     R0, =0x270F
ROM:FFA1EA94                 CMP     R1, R0
ROM:FFA1EA98                 BCC     loc_FFA1EAAC
ROM:FFA1EA9C                 LDR     R0, =0xBA380  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ROM:FFA1EAA0                 ADR     R1, a9999       ; "9999"
ROM:FFA1EAA4                 BL      sprintf
ROM:FFA1EAA8                 B       loc_FFA1EABC
*/
{
 return (char*)0x000ba380;
}

int vid_get_viewport_width()
{
    return 360;
}

long vid_get_viewport_height()
{
    return 240;
}


//Copied from S95 section  END

/*
//  NEW NEW NEW
//  Need checking

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}
*/

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


