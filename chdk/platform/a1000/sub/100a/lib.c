#include "platform.h"

char *hook_raw_image_addr()
{
	// Found 0x11B96B80 at ROM:FFC377A0
	// Found 0x107D58E0 at ROM:FFC756CC
	// 0x51C0 + 0x18 found at ROM:FFC4C504	
	return (char*) (*(int*)(0x51C0+0x18) ? 0x11B96B80 : 0x107D58E0);
}

long hook_raw_size()
{
    // Found at: FFE45D1C
	return 0xEC04F0;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x6A68;  // at: ROM:FFC9FF3C
    unsigned char buff = *((unsigned char*)0x68DC);	// at: ROM:FFC9FF34
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x10361000; 
}

void *vid_get_viewport_fb()
{
	return (void*)0x10659DE0;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)0x4f3c); // 0x4EE8 + 0x54 
}

long vid_get_bitmap_width()
{
	return 360;
}

long vid_get_bitmap_height()
{
	return 240;
}

long vid_get_bitmap_screen_width()
{
	return 360;
}

long vid_get_bitmap_screen_height()
{
	return 240;
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
	return (char*)0x4506C;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
