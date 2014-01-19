#include "platform.h"

char *hook_raw_image_addr()
{
 return (char*) (*(int*)0x5684 ? 0x11F6B740 : 0x108057C0);
 //  return (char*)0x108057C0;
}
char *hook_alt_raw_image_addr()
{
 return (char*) (*(int*)0x5684 ? 0x108057C0 : 0x11F6B740);
}

long hook_raw_size()
{
    return 0xEE9710;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
}

void *vid_get_bitmap_fb()       
{
    return (void*)0x10361000;
}

void *vid_get_viewport_fb()
{
    return (void*)0x1065A560;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x53E8);  // 0x53A0 + 0x48
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x5CB38;
}

// PTP display stuff, untested, adapted from ewavr chdkcam patch
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x4536C; // sub_FFCCB3A4
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0xCAC4); //SaveBmpVRAMData()->sub_FFCCB464
}

// values from chdkcam patch
// commented for now, protocol changes needed to handle correctly
// note, play mode may be 704, needs to be tested
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x21A8; // VRAM DataSize
}
int vid_get_viewport_height_proper() {
     return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)(0x21A8+4); // VRAM DataSize
}
#endif

