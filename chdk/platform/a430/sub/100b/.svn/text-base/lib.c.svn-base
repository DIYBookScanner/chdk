#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x34EA4; // found in taskcreate_ImageSensorTask
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCB30B0; // ok
}

char *hook_raw_image_addr()
{
    return (char*)0x10577E28;  // ok
}

long hook_raw_size()
{
    return 0x4FEED0;       // ?? "CRAW BUF","WBIntegPrm.c" -  1/3" 4 MPix -  (2272*1704*10/8=0x49D7C0)
}

void *vid_get_viewport_live_fb() // from a540
{
       void **fb=(void **)0x5264; // 0xFFC8F1EC
       unsigned char buff = *((unsigned char*)0x5274);
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
    return (void*)0x103C79A0; // OK (find in _CreatePhysicalVram)
}

void *vid_get_viewport_fb()
{
    return (void*)0x105F2830; // OK (find on "VRAM Address  : %p")
}

void *vid_get_viewport_fb_d()
{
    int x=(*(int*)0x71AB0); // @ffd0f29c
    return (x) ? (void*)x : vid_get_viewport_fb();
}

long vid_get_viewport_height()
{
    // return ((mode_get()&MODE_MASK) == MODE_PLAY) ? 240 : 230;
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x7C588;
} 

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x5EAC); // sub_ffd0cae8 DisplayPhysicalScreenWithYUVPalette
}

void *vid_get_bitmap_active_palette() {
    return (void *)0x714a8; // found also in sub_ffd0cae8
}

int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }
