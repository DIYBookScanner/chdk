#include "platform.h"

char *hook_raw_image_addr()
{
    return (char*)0x105B8AC0;
}

long hook_raw_size()
{
    return 0x75A8F0;
}

/**
 * OSD screen
 */
void *vid_get_bitmap_fb()
{
    return (void*)0x103C79A0;
}

void *vid_get_viewport_live_fb() // from a420
{
       void **fb=(void **)0x52c8; // ixus65, @ 0xff8a7b94
       unsigned char buff = *((unsigned char*)0x52d8);
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
    return (void*)0x105f17a0; //ixus65, the first of the 3 buffers
}

/**
 * IMG viewport in 'play' mode
 */
void *vid_get_viewport_fb_d()
{
    //return (void*)0x104AFCA0;
    int x=(*(int*)0x6dd4c);
    return (void*) (x ? x : 0x105599a0) ; //ixus65, still incorrect when a stopped movie is displayed
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x79358;
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x5ee4); // sub_ff93606c DisplayPhysicalScreenWithYUVPalette
}

void *vid_get_bitmap_active_palette() {
    return (void *)0x6d6b0; // found also in sub_ff93606c
}

int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

int vid_get_viewport_width_proper()  { return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x3d0e8;} //sub_ff8aa408
int vid_get_viewport_height_proper() { return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:*(int*)0x3d0ec;} //"VRAM DataSize H : %04ld, V : %04ld"

int movie_status = 0;
