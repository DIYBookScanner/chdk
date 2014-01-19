#include "platform.h"

/*
*********************
SX200IS
**********************
note sensor size for camera.h is from 
@ FFAC8D6C
0x11CA240 = 18653760
18653760/12 * 8 - 12435840 ---
                              |
@ FFAC8A40                    |
0xFF0 and 0xBE8 =             |
4080  *  3048  = 12435840  ---
*/

char *hook_raw_image_addr()
{
	//found at FFAC8D10
	//ROM:FFAC8D10                 LDR     R6, =0x424B41C0
	//...
	//ROM:FFAC8D60                 MOV     R1, R6
	//ROM:FFAC8D64                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"

	return (char*)(0x424B41C0);
}

long hook_raw_size()
{
	//found at FFAC8D6C
	//ROM:FFAC8D6C                 LDR     R1, =0x11CA240
	//ROM:FFAC8D70                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
	//ROM:FFAC8D74                 BL      sub_FF9037E8

	return 0x11CA240;
}

// Live picture buffer (shoot not pressed)
void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x2180;                               // 0x2150 or 0x2180 (suggested by ADamb)
    unsigned char buff = *((unsigned char*)0x1FD8);          // found at FF838090
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	return (void*)0x403F1000;                              // found at FF842AC4 and FFA2BED4
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*)0x415F9E20;                              // found by search for VRAM Address @FFAC67F0
}

// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d() 
{
//	return (void*)(*(int*)(0x2950+0x50));                  // found at FF858A84 and FF859398 (0x58 at FF8594F0)
	return (void*)(*(int*)(0x2950+0x58));                  // suggested by ADamb
}


int vid_get_viewport_width()
{
    return 360;                                               // stays at 360 as IN SD990
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
 return (void*)0x5408C;                                      // found at FF9C1F28
}

// PTP display stuff
int vid_get_palette_type() { return 3; }
int vid_get_palette_size() { return 256*4; }

/*void *vid_get_bitmap_active_palette() // used from load_chdk_palette
{
    return (void *)*(unsigned int*)(0x5744+0x28);  //FF8E6198, FF8E6230
}*/

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x5744+0x14)); //"Add: %p Width : %ld Hight : %ld", FF8E62DC
}

extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();

int vid_get_viewport_fullscreen_width() {
    int mode = mode_get()&MODE_MASK;
    int mode_shoot = mode_get()&MODE_SHOOTING_MASK;
    return ((mode == MODE_PLAY) ||
        (mode != MODE_PLAY && mode_shoot == MODE_SCN_STITCH))?720:_GetVRAMHPixelsSize();
}

int vid_get_viewport_fullscreen_height() {
    int mode = mode_get()&MODE_MASK;
    int mode_shoot = mode_get()&MODE_SHOOTING_MASK;
    return ((mode == MODE_PLAY) ||
        (mode != MODE_PLAY && mode_shoot == MODE_SCN_STITCH))?240:_GetVRAMVPixelsSize();
}

int vid_get_viewport_display_xoffset_proper() {
    int val=0;
    int mode = mode_get()&MODE_MASK;
    int mode_shoot = mode_get()&MODE_SHOOTING_MASK;
    if(mode != MODE_PLAY && mode_shoot == MODE_SCN_STITCH) {
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
    int mode = mode_get()&MODE_MASK;
    int mode_shoot = mode_get()&MODE_SHOOTING_MASK;
    return (mode != MODE_PLAY && mode_shoot == MODE_SCN_STITCH)?70:0; // window is 120, not centered
}
