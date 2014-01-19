#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x440C0; 
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFD4CBD8; 
}

char *hook_raw_image_addr()
{
    return (char*)(0x10800000+0x41000+0x260);      
}

long hook_raw_size()
{
    return 0x63FF60;       // "CRAW BUF","WBIntegPrm.c" -  1/3" 5 MPix -  (2664*1968*10/8=0x63FF60)  
}

void *vid_get_viewport_live_fb() //@ffd630f8
{
    void **fb=(void **)0x6028;
    unsigned char buff = *((unsigned char*)0x6038);
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
    return (void*)0x10361000;  //(0x10360000 + 0x1000)
}

void *vid_get_viewport_fb()
{
    return (void*)0x10E81260; //0x10558D30
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x6D048);
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x10F70;
} 

// PTP display stuff
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x45af8;  // sub_ffdbb11c, (marked by 2 adjacent bmpddev.c asserts, just like in A410)
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x8dc8)); //sub_ffdbb11c, fed into 0xc0f140d4
}

extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();
// normally 720, goes to 360 for stitch, 320x240 video, max digital zoom
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:_GetVRAMHPixelsSize();
}
// varies from 62 - 240 with digital zoom, 120 in stitch
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}

int vid_get_viewport_fullscreen_height() {
    // except for stitch, always full screen
    return vid_get_viewport_height_proper();
}
int vid_get_viewport_fullscreen_width() {
    // except for stitch, always full screen
    return vid_get_viewport_width_proper();
}
int vid_get_viewport_display_xoffset_proper() {
    return 0;
}
int vid_get_viewport_display_yoffset_proper() {
    return 0;
}
