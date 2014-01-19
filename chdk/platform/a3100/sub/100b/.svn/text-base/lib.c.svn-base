#include "platform.h"

char *hook_raw_image_addr()
{
/*
ROM:FFCEDBC4                 LDR     R2, =0xE88
ROM:FFCEDBC8                 LDR     R1, =0x10E59860
ROM:FFCEDBCC                 SUB     R3, R2, #0x3B4
ROM:FFCEDBD0                 ADR     R0, aCrwaddressLxCr ; " CrwAddress %lx, CrwSize H %ld V %ld\r"
sss 
*/ 
	return (char*) 0x110B7260; // @ffaadcf4
}




// Found @0xffaadd50
long hook_raw_size()
{
	return 0x011ca240;
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	return (void*)0x103e1000;
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*) 0x106f3bc0;
}

void *vid_get_viewport_fb_d() 
{                  
	return (void*)(*(int*)(0x2630+0x54));
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
 return (void*)0x00076b3c;
}
