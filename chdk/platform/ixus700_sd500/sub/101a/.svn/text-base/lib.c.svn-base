#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x2F490;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D8BDC;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10400000+0x160000+0x3A80);
}

long hook_raw_size()
{
    return 0x8CAE10;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
    // from ewavr chdkcam code, needs to be tested
#if 0
    void **fb=(void **)0x317C;
    unsigned char buff = *((unsigned char*)0x318C);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
#endif
}

void *vid_get_bitmap_fb()
{
    return (void*)0x103CEB20;
}

void *vid_get_viewport_fb()
{
//    return (void*)0x104B6C20;
//    return (void*)0x10559670;
    return (void*)0x105F1470;
}

void *vid_get_viewport_fb_d()
{
//    return (void*)(*(int*)0x5BAEC);
 return (void*)0x104B6C20;
}

long vid_get_viewport_height()
{
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}
char *camera_jpeg_count_str()
{
    return (char*)0x75BB8;
}

// PTP display stuff, untested, adapted from ewavr chdkcam patch
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x6E758; // GetPaletteFromPhysicalScreen
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x50F4);
}
// TODO value of vid_getviewport_height_proper needs to be checked in play, rec, and the different video modes
//int vid_get_viewport_fullscreen_height()               { return 240; }

// values from chdkcam patch
// commented for now, protocol changes needed to handle correctly
// note, play mode may be 704, needs to be tested
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x2E158; // VRAM DataSize
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)0x2E15C; // VRAM DataSize
}
#endif

