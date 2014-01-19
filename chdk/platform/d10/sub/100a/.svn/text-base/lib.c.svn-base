#include "platform.h"

char *hook_raw_image_addr()
{
    return (char*)0x41643DEC; // seach on CRAW BUF
// if multi buffer,
// (0x2AEC + 0x8) ??? sub_FF86274C__SsImgProcBuf_c__0 and table FFAD6A24
}

long hook_raw_size()
{
    return 0x11E4EE0; // CRAW BUF SIZE 4104*3048, like g9, ixus960
}

void *vid_get_viewport_live_fb()
{
	// from sub_FF837020 (similar to sd990 sub_FF839850), via sub_FF8EC2DC ref to table at FFAE28FC
    void **fb=(void **)0x210C;
    unsigned char buff = *((unsigned char*)0x1F74);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
	// d10 adds this extra value.  Didn't ever see the value change from zero, may be wrong
    return fb[buff] + *(int *)(0x1F74 + 0xd4); 
}

void *vid_get_bitmap_fb()       
{
    return (void*)0x403F1000; //  DispCon_ShowBitmapColorBar
}

void *vid_get_viewport_fb()
{
    return (void *)0x40A05158; // search on VRAM Address
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x2884 + 0x54));  // sub_FF8584AC, similar callers to sd990, 3rd, 4th functions following "HFILYUV"
}

int vid_get_viewport_width()
{
	return 360;
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char *)0x525E4; // search on "9999" done
}


// PTP display stuff
int vid_get_palette_type() { return 3; }
int vid_get_palette_size() { return 256*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)*(unsigned int*)(0x5164+0x28);  // sub_FF8DE674, via sub_FF9B390C two refs to "Palette Class."
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x5164+0x14)); //"Add: %p Width : %ld Hight : %ld", sub_FF8DE720
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
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_SCN_STITCH) {
        return 240;
    }
    return vid_get_viewport_height_proper();
}
int vid_get_viewport_fullscreen_width() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_SCN_STITCH) {
        return 720;
    }
    return vid_get_viewport_width_proper();
}
int vid_get_viewport_display_xoffset_proper() {
    int val=0;
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_SCN_STITCH) {
        short dir=0;
        short seq=0;
        get_property_case(PROPCASE_STITCH_DIRECTION,&dir,sizeof(dir));
        get_property_case(PROPCASE_STITCH_SEQUENCE,&seq,sizeof(seq));
        // overall stitch window is 3/4 screen width, centered
        // live part is 1/2, so margin is either 1/8th or 3/8th
        if(dir==0) {
            val = seq?270:90;
        } else {
            val = seq?90:270;
        }
    }
    return val;
}
int vid_get_viewport_display_yoffset_proper() {
    int m = mode_get();
    return ((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_SCN_STITCH)?60:0; // window is 120, centered in 240 screen
}
