#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x367D0;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCB4C5C;
}

char *hook_raw_image_addr()
{
    return (char*)0x1058EBD4;
}

long hook_raw_size()
{
    return 0x644C40;
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0x10670d50;
    void **fb=(void **)0x52EC;
    unsigned char buff = *((unsigned char*)0x52FC);
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
    return (void*)0x103C79A0;
}

void *vid_get_viewport_fb()
{
    return (void*)0x10559570;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x7279c);
}

long vid_get_viewport_height()
{
    return 240;
}

long vid_is_bitmap_shown()
{
    return 1;
}

char *camera_jpeg_count_str()
{
    return (char*)0x80A90;
}

// PTP display stuff, untested, adapted from ewavr chdkcam patch
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)(0x724E0); // GetPaletteFromPhysicalScreen
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x6A58);
}

// values from chdkcam patch
// commented for now, protocol changes needed to handle correctly
// note, play mode may be 704, needs to be tested
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x35F20;// VRAM DataSize
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)(0x35F20+4); // VRAM DataSize     
}
#endif
