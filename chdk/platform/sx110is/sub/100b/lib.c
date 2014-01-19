#include "platform.h"

char *hook_raw_image_addr()
{
//found 0x11A34C40 at 0xFFC3C948 and 0x10805040 at FFC7D80C
// not for sure: 53A4 at 0xFFC51A60 and 0x53A4+0x18 at 0xFFC518D4
	return (char*) (*(int*)(0x53A4+0x18) ? 0x11A34C40 : 0x10805040);	
}

long hook_raw_size()
{
   //      ROM:FFE60BB4                 LDR     R1, =0xEC04F0
   return 0xEC04F0;
}


void *vid_get_viewport_live_fb()
{
   void **fb=(void **)0x21a0; //ROM:FFC285D0 dword_FFC285D0  DCD 0x21A0, look also at ROM:FFC27FF0
   unsigned char buff = *((unsigned char*)0x2014); //ROM:FFC285C8 dword_FFC285C8  DCD 0x2014    , look also at ROM:FFC27FA0
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;		// found at some addresses e.g. 0xffc32078 or 0xFFDD97B8 , guided by sx100 an a720 and sx10
}

void *vid_get_viewport_fb()
{
    return (void*)0x10659DE0; // found at some addresses e.g. 0xffe5ea50 , guided by sx100 and a720 ans sx10
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x5114);   //0x50C0 + 0x54, 0x50C0 found at 0xFFC45E78 and look at 0xffc46568/0xFFC46594
}

// note this appears to be 216 in rec mode 
long vid_get_viewport_height()
{
    return vid_get_viewport_height_proper();
}
char *camera_jpeg_count_str()
{
	// Found at ROM:FFD84BC0	
 return (void*)0x45E58;
}

extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();
// normally 720, others unknown
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:_GetVRAMHPixelsSize();
}
// playback seems to be 240, rec 216 (?!), varies with digital zoom
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}
// this camera does not have stitch, so always fullscreen
int vid_get_viewport_fullscreen_width() {
    return vid_get_viewport_width_proper();
}
int vid_get_viewport_fullscreen_height() {
    return vid_get_viewport_height_proper();
}

//this camera uses a 16 entry VUYA palette. The alpha values all appear to be 0 or 3
int vid_get_palette_type() { return 4; }
int vid_get_palette_size() { return 16*4; } // from sub_FFCD28D4
void *vid_get_bitmap_active_palette() {
    return (void *)*(unsigned int*)(0x7BCC+0x20);  // sub_FFCD28D4, via sub_FFD8B650 two refs to "Palette Class."
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x7BCC+0xC)); //"Add: %p Width : %ld Hight : %ld", sub_FFCD2998
}

