#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x37334; // found in taskcreate_ImageSensorTask
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCAE220; //
}

char *hook_raw_image_addr()
{
    return (char*)0x10570FF0;  // @ffca81cc, 0x10400000+0x17000+0xff0
}

long hook_raw_size()
{
    return 0x3FCB40;   //@ffca81d8, 0x3fc000+0xb40
}

/*
YUV buffer created in jpeg processing for < full size jpeg
not currently used, kept for future reference
*/
#if 0
char *hook_yuv_shooting_buf_addr() { //buffer that holds the uncompressed yuv source of the fresh jpeg
    return (char*)0x10553180; //not used for L picture size
}

int hook_yuv_shooting_buf_width() {
    if (shooting_get_resolution()) //invalid for L picture size
        return *(int*)0x3716c; //@ffca2d08, ... inside DvlpSeqTask
    return 0;
}

int hook_yuv_shooting_buf_height() {
    if (shooting_get_resolution()) //invalid for L picture size
        return *(int*)0x37170; //@ffca2d0c, ... inside DvlpSeqTask
    return 0;
}
#endif

int vid_get_viewport_width_proper() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 720; //no tv-out
    }
    // return hard coded width since mode doesn't update at the same time as GetVRAMHPixelsSize
    if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        return 360;
    }
    return *(int*)0x36a98;
}

int vid_get_viewport_height_proper() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 240; //no tv-out
    }
    // return hard coded width since mode doesn't update at the same time as GetVRAMHPixelsSize
    if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        return 120; 
    }
    return *(int*)0x36a9c;
}

void *vid_get_viewport_live_fb() // from a540
{
       void **fb=(void **)0x4FF4; //@ffc90d90
       unsigned char buff = *((unsigned char*)0x5004); //@ffc90d64
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
    return (void*)0x103C79A0; // same as in a430, a420
}

void *vid_get_viewport_fb()//
{
    return (void*)0x105EAF80; // @ffd08f18
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x73280); // @ffd0c96c
}

int vid_get_viewport_width() {
    return vid_get_viewport_width_proper()>>1;
}

long vid_get_viewport_height()
{
    return vid_get_viewport_height_proper();
}

char *camera_jpeg_count_str()
{
    return (char*)0x7F9F0; // @ffdd479c
} 

int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x73028; // GetPaletteFromPhysicalScreen
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x6694); // @ffd0a170 DisplayPhysicalScreenWithYUVPalette
}

int vid_get_viewport_fullscreen_height() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && ((m&MODE_SHOOTING_MASK) == MODE_STITCH)) {
        return 240;
    }
    return vid_get_viewport_height_proper();
}

int vid_get_viewport_fullscreen_width() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && ((m&MODE_SHOOTING_MASK) == MODE_STITCH)) {
        return 720;
    }
    return vid_get_viewport_width_proper();
}

int vid_get_viewport_display_xoffset() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 0;
    } else if((m&MODE_SHOOTING_MASK) == MODE_STITCH) { // checked visually, OK
        short dir=0;
        short seq=0;
        get_property_case(PROPCASE_STITCH_DIRECTION,&dir,sizeof(dir));
        get_property_case(PROPCASE_STITCH_SEQUENCE,&seq,sizeof(seq));
        // overall stitch window is 3/4 screen width, centered
        // live part is 1/2, so margin is either 1/8th or 3/8th
        if(dir==0) {
            return seq?132:44;
        } else {
            return seq?44:132;
        }
    }
    return 0;
}

int vid_get_viewport_display_yoffset() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 0;
    }
    return ((m&MODE_SHOOTING_MASK) == MODE_STITCH)?60:0; // window is 120, centered in 240 screen
}
