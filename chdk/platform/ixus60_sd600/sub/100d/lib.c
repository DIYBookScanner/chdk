#include "platform.h"

char *hook_raw_image_addr()
{
    // ( found on aA08x_crw)
    return (char*)0x105B8AC0;   // same as sd630, found at 0xFF8CA0AC
}

long hook_raw_size()
{
    // 0x644C00 + 0x40 (found on aA08x_crw)
    return 0x75A8F0;    // same as sd630, found at 0xFF8CA0B4
}

/**
 * OSD screen
 */
void *vid_get_bitmap_fb()
{
    // (found on aBmpddev_c)
    return (void*)0x103C79A0;   // same as sd630, found at 0xFF935518
}

void *vid_get_viewport_live_fb() // from ixus65
{
       void **fb=(void **)0x5284; // @ 0xff8a6d24 for 100d
       unsigned char buff = *((unsigned char*)0x5294); // @ 0xff8a6d20 for 100d
       if (buff == 0) {
           buff = 2;
       }
       else {
           buff--;
       }
       return fb[buff];
}

/**
 * IMG viewport in 'rec' mode
 */
void *vid_get_viewport_fb()
{
    return (void*)0x105f17a0;   // @ 0xffac8ee8 for 100d
}

/**
 * IMG viewport in 'play' mode
 */
void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x6db8c); // @ 0xff938920 for 100d
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x79158; // @ 0xffa5f3f4 for 100d
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x5ea0); // in sub_ff935598 DisplayPhysicalScreenWithYUVPalette for 100d
}

void *vid_get_bitmap_active_palette() {
    return (void *)0x6d4a8; // found also in sub_ff935598 for 100d
}

int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

// note: buffers change dimensions when TV-out is active or in movie mode, these may not be handled
// stitch mode is not supported
int vid_get_viewport_width_proper()  { return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x3ced0;} //sub_ff8a9594 for 100d
int vid_get_viewport_height_proper() { return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)(0x3ced0+4);} //"VRAM DataSize H : %04ld, V : %04ld"
