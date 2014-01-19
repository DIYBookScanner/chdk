#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x3F960;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCC6640;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10400000+0x164000+0xBF0);
}

long hook_raw_size()
{
    return 0x8CAE10;
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0x10670ee0;
    void **fb=(void **)0x522C;
    unsigned char buff = *((unsigned char*)0x523C);
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
    return (void*)0x1055A7E0; //0x105f25e0;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x70854);
}

long vid_get_viewport_height()
{
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}
char *camera_jpeg_count_str()
{
    return (char*)0x7BD98;
}

// PTP display stuff, untested, adapted from ewavr chdkcam patch
// reyalp - type guessed
int vid_get_palette_type() { return 2; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x70250; // GetPaletteFromPhysicalScreen
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x5FB0);
}

// values from chdkcam patch
// commented for now, protocol changes needed to handle correctly
// note, play mode may be 704, needs to be tested
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x3EED0; // VRAM DataSize
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)0x3EED4; // VRAM DataSize
}
#endif
