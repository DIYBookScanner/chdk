#include "platform.h"
#include "lolevel.h"

//These functions now are part of platform/a495/lib.c
/*
char *hook_raw_image_addr()
{
	return (char*) 0x10E52420; // Ok, ROM:FFCE9A44
}

long hook_raw_size()
{
	return 0xEC04F0;           // "CRAW BUFF SIZE"
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	return (void*)0x10361000; // "BmpDDev.c", 0xFFCD1DD4
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*)0x10648CC0;  // "VRAM Address" sub_FFCA6830
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x2540+0x54)); // sub_FFC528C0 / sub_FFC53554?
}

char *camera_jpeg_count_str()
{
	return (char*)0x7486C;  // "9999"
}
*/
