#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*) (*(int*)(0x55CC+0x18) ? 0x424F1948 : 0x40F65B18);
}

long hook_raw_size()
{
	return 0xEC04F0;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x227C;
    unsigned char buff = *((unsigned char*)0x20D0); // sub_FF839DD8
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x403B1000; 
}

void *vid_get_viewport_fb()
{
	return (void*)0x4070D9D0;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x5260+0x58)); 
}

long vid_get_viewport_height()
{
	return 240;
}

char *camera_jpeg_count_str()
{
	return (char*)0x4C138;
}

// PTP display stuff, untested, adapted from ewavr chdkcam patch
// reyalp - type probably wrong, looks like 2 with opposite order
int vid_get_palette_type() { return 2; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)*(unsigned int*)(0x8378+0x20);  // sub_FF8F3A10
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x8378+0x0C)); //"Add: %p Width : %ld Hight : %ld", sub_FF8F3AD4
}

// values from chdkcam patch
// commented for now, protocol changes needed to handle correctly
// note, play mode may be 704, needs to be tested
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x224C; // VRAM DataSize
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)(0x224C+4); // VRAM DataSize
}
#endif

