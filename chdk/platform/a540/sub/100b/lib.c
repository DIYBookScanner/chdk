#include "platform.h"
#include "keyboard.h"
#include "stdlib.h"

char *hook_raw_image_addr()
{
    return (char*)0x105B8AC0; // OK (find on ".crw")
    
}

long hook_raw_size()
{
    return 0x75A8F0; // OK (find on ".crw")
}

/*
YUV buffer created in jpeg processing for < full size jpeg
not currently used, kept for future reference
*/
#if 0
/*
buffer that holds the uncompressed yuv source of the fresh jpeg
not used for L or W picture size
*/
char *hook_yuv_shooting_buf_addr() {
    return (char*)0x105599A0; // based on proximity to viewport_fb in ROM table at FFEF8370, by comparison to a410
}

/*
via sub_FFCA2CC8, after EnableEngineClocks
note these update during shooting, may hold incorrect values after resolution changes
invalid for L or Wide (continues to hold previous value)
*/
int hook_yuv_shooting_buf_width() {
    if (shooting_get_resolution() !=0 && shooting_get_resolution() !=8)
        return *(int*)0x33394; //FFCB1D50
    return 0;
}

int hook_yuv_shooting_buf_height() {
    if (shooting_get_resolution() !=0 && shooting_get_resolution() !=8)
        return *(int*)0x33398; //FFCB1D54
    return 0;
}
#endif

void *vid_get_bitmap_fb()
{
    return (void*)0x103C79A0; // OK (find in _CreatePhysicalVram)
}

void *vid_get_viewport_fb()
{
    return (void*)0x105F17A0; // OK (find on "VRAM Address  : %p")
}

void *vid_get_viewport_fb_d()
{
// from ewavr 
  int x=(*(int*)0x63AD0); // found in sub_FFD25770
  return (void *)x;
// if we start camera in PB mode with movie on display, this pointer will be NULL
// _fb isn't valid data, but at least it doesn't crash
//  return (void*) (x ? (void *)x : vid_get_viewport_fb()) ;
}

extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();

// for testing only, to simulate cameras with variable aspect
// MODE_PORTRAIT uses 1:1 ( 528x240 ) and MODE_LANDSCAPE 16:9 (704x180)
// no need to implement this on other cameras unless you are doing development
//#define FAKE_ASPECT 1

int vid_get_viewport_width_proper() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 704;
    }
#ifdef FAKE_ASPECT
    // fake 1:1 mode
    if((m&MODE_SHOOTING_MASK) == MODE_PORTRAIT) {
        return 528;
    }
#endif
    // return hard coded width since mode doesn't update at the same time as GetVRAMHPixelsSize
    if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        return 352;
    }
    return _GetVRAMHPixelsSize();
}

int vid_get_viewport_width() {
    return vid_get_viewport_width_proper()>>1;
}

int vid_get_viewport_height_proper() {
    int m = mode_get();
    // TODO not correct if TV out connected
    if((m&MODE_MASK) == MODE_PLAY) {
        return 240;
    }
#ifdef FAKE_ASPECT
    // fake 16:9 mode
    if((m&MODE_SHOOTING_MASK) == MODE_LANDSCAPE) {
        return 180; 
    }
#endif
    // return hard coded width since mode doesn't update at the same time as GetVRAMHPixelsSize
    if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        return 120; 
    }
    return _GetVRAMVPixelsSize();
}

long vid_get_viewport_height() {
    return vid_get_viewport_height_proper();
}

// the following aren't used, kept for informational purposes
#if 0
int review_fullscreen_mode(){ //from 710 added
 char r;
 get_parameter_data(53, &r, 1);
 return  r==0;
}

int postreview_fullscreen_mode(){ //from 710 added
 char r;
 get_parameter_data(54, &r, 1);
 return  r==0;
}


static int file_size_table[3][5]={{3110,2562,1666,1057,288},
				  {1954,1441, 928, 608,176},
				  {960,  736, 480, 320,112}};  // in KB   // from 710 added
				  	
				  
long raw_shoot_avail(){ // from 710 added
 long jpegs,size,quality;
 jpegs=atoi((char*)0x6E8D0); // orig.0x7BD98 find -> a9999
 get_property_case(23, (void *)&quality, 4);
 get_property_case(24, (void *)&size, 4);
 if ((size>4) || (quality>2)) return 0; 
 return (file_size_table[quality][size]*jpegs)/(file_size_table[quality][size]+(hook_raw_size()>>10));
}


int mf_slider_active() // from 710 added
{
 return *(long*)0x6C8B0==0x100; // orig.0x798F0  found in "ControlSwitcher.c"
}
#endif

void *vid_get_viewport_live_fb() // from 710 added
{
    void **fb=(void **)0x5288;
    unsigned char buff = *((unsigned char*)0x5298);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}


char *camera_jpeg_count_str()
{
    return (char*)0x6E8D0 ; // from 700 added orig. 0x78688
}

// PTP display stuff
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x634E0; // GetPaletteFromPhysicalScreen
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x5ED0); // FFD23420 DisplayPhysicalScreenWithYUVPalette
}

int vid_get_viewport_fullscreen_height() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && ((m&MODE_SHOOTING_MASK) == MODE_STITCH
#ifdef FAKE_ASPECT
         || (m&MODE_SHOOTING_MASK) == MODE_LANDSCAPE
#endif
         )) {
        return 240;
    }
    return vid_get_viewport_height_proper();
}
int vid_get_viewport_fullscreen_width() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && ((m&MODE_SHOOTING_MASK) == MODE_STITCH
#ifdef FAKE_ASPECT
         || (m&MODE_SHOOTING_MASK) == MODE_PORTRAIT
#endif
    )) {
        return 704;
    }
    return vid_get_viewport_width_proper();
}

int vid_get_viewport_display_xoffset() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 0;
    } else if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
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
#ifdef FAKE_ASPECT
    } else if((m&MODE_SHOOTING_MASK) == MODE_PORTRAIT) {
        return 44;
#endif
    }
    return 0;
}

#ifdef FAKE_ASPECT
int vid_get_viewport_xoffset() {
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_PORTRAIT) {
       return 44;
    }
    return 0;
}
#endif

int vid_get_viewport_display_yoffset() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 0;
    }
#ifdef FAKE_ASPECT
    if((m&MODE_SHOOTING_MASK) == MODE_LANDSCAPE) {
       return 30;
    }
#endif
    return ((m&MODE_SHOOTING_MASK) == MODE_STITCH)?60:0; // window is 120, centered in 240 screen
}

#ifdef FAKE_ASPECT
int vid_get_viewport_yoffset() {
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_LANDSCAPE) {
       return 30;
    }
    return 0;
}
#endif
