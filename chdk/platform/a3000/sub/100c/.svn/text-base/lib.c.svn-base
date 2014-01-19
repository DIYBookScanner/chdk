#include "platform.h"
char *hook_raw_image_addr()
{
	return (char*) 0x10E59860;
}
long hook_raw_size()
{
	return 0xEC04F0;
}

// Live picture buffer (shoot not pressed)
void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0xFFE9856C;
    unsigned char buff = *((unsigned char*)0x4290);
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	return (void*)0x10361000;
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*) 0x10650100;
}

void *vid_get_viewport_fb_d() 
{                  
	return (void*)(*(int*)(0x2620+0x54));
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
 return (void*)0x75120;
}
