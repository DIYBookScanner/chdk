#include "platform.h"
//----------------------A3100IS--------------------------
/*
0xE88 and AD4 =              
3720  *  2772  =  10311840 

*/ 

char *hook_raw_image_addr()
{
/*
ROM:FFCEDBC4                 LDR     R2, =0xE88
ROM:FFCEDBC8                 LDR     R1, =0x10E59860
ROM:FFCEDBCC                 SUB     R3, R2, #0x3B4
ROM:FFCEDBD0                 ADR     R0, aCrwaddressLxCr ; " CrwAddress %lx, CrwSize H %ld V %ld\r"
sss 
*/ 
	return (char*) 0x10E59860; // A3000 @FFE659E0
}

long hook_raw_size()
{
	//Near to "CRAW BUFF SIZE  %p"
	return 0xEC04F0; // A3000 @FFE65A3C
}

// Live picture buffer (shoot not pressed)
void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0xFFE9856C;
    unsigned char buff = *((unsigned char*)0x4290);          // found near string "TgTask"
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	return (void*)0x10361000;       // found under "BmpDDev.c"
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*) 0x10650100; 
}

void *vid_get_viewport_fb_d() 
{                  
	return (void*)(*(int*)(0x2620+0x54));    // found at FFC52DD8 and  (0x48 at FFC52DE0)
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
 return (void*)0x75120;    // found at FFD7BD90 search string: a9999
}
