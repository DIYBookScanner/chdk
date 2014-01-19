#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*) (*(int*)(0x574C+0x18) ? 0x435627D8 : 0x41B724C0);
}

long hook_raw_size()
{
	return 0x1076D90;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x2300;
    unsigned char buff = *((unsigned char*)0x2130); // sub_FF839FC8
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x40471000; 
}

void *vid_get_viewport_fb()
{
	return (void*)0x46443400;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x53C8+0x58)); 
}

// default is same as bitmap
/*
int vid_get_viewport_width()
{
	return 480;
}
*/
long vid_get_viewport_height()
{
	return 270;
}

char *camera_jpeg_count_str()
{
	return (char*)0x5CED4;
}

// PTP display stuff, untested, adapted from ewavr chdkcam patch
// reyalp - type probably wrong, chdkcam patch suggests opposite order from a540 (e.g. vuya)
int vid_get_palette_type() { return 2; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void*)(*(unsigned int*)(0x8D10+0x20)); // sub_FF903BBC
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x8D10+0x0C)); //"Add: %p Width : %ld Hight : %ld", sub_FF903C80
}
// TODO value of vid_get_viewport_height_proper needs to be checked in play, rec, and the different video modes
//int vid_get_viewport_fullscreen_height()               { return 270; }

// values from chdkcam patch
// commented for now, protocol changes needed to handle correctly
// note, play mode may be 704, needs to be tested
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?960:*(int*)0x22D0; // VRAM DataSize
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)(0x22D0+4); // VRAM DataSize
}
#endif

