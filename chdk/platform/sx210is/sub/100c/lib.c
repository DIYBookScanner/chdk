#include "platform.h"

/*
*********************
SX200IS
**********************
note sensor size for camera.h is from  //ASM1989 08.20.2010
@ FFB2FC6C
0x14D2400  = 21832704

21832704 / 12 * 8 = 14555136
---
                              |
@ FFB2F7C0                    |
0x1140 by 0xCE0 =             |
44416 * 3296  = 14555136  ---
*/

char *hook_raw_image_addr()   //ASM1989 08.20.2010
{
	//found at FFB2FB2C

	//ROM:FFB2FB2C                 LDR     R6, =0x41DB3B80
	//..
	//ROM:FFB2FB7C                 MOV     R1, R6
	//ROM:FFB2FB80                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"

	return (char*)(0x41DB3B80);

	//Testing
	//return (char*) (*(int*)(0x3310+0x18) ? 0x43289400 : 0x415D7CC0);   //0x3310 at FF880698 others at FF86AA48

}

long hook_raw_size() //ASM1989 08.20.2010
{
	//found at FFB2FC6C
			//ROM:FFB2FC6C dword_FFB2FC6C  DCD 0x14D2400           ; DATA XREF: sub_FFB2FAD8+B0r
			//ROM:FFB2FC70 aCrawBuffSizeP  DCB "CRAW BUFF SIZE  %p",0 ; DATA XREF: sub_FFB2FAD8+B4o

	return 0x14D2400;
}



// Live picture buffer (shoot not pressed) //ASM1989 08.20.2010
void *vid_get_viewport_live_fb()
{


    return 0x0;
/*
    void **fb=(void **)0x2180;                               // 0x2150 or 0x2180 (old SX200) ???? What for SX210
    unsigned char buff = *((unsigned char*)0x2058);          // found at FF84FA18 (guess work)
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];*/


}



// OSD buffer  //ASM1989 08.20.2010
void *vid_get_bitmap_fb()
{
	return (void*)0x40431000;                              // found at FF85BE50 and FFA7DC10
}



// Live picture buffer (shoot half-pressed) //ASM1989 08.20.2010
void *vid_get_viewport_fb()
{
	return (void*)0x40547700;                              // found by search for VRAM Address @FFB2C7B4
}



// Histo etc. when in play mode maybe ?  //ASM1989 08.20.2010
void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x30B8+0x58));                  // found at FF8743DC  and FF8750CC (0x58 at FF875104)
}

//ASM1989 08.20.2010
// found at FF91CD90                 LDR     R1, =0x10E     - height 270
// found at FF91CD94                 MOV     R0, #0x3C0   - width 960

//try to solve screen sizes using sx30 code

/*

long vid_get_bitmap_screen_width()
{
//    return SCREENX;  // -------------------------------------yes, the buffer is greater, and de
//	return 320;


	//return ((mode_get()&MODE_MASK) == MODE_VIDEO_STD ||(mode_get()&MODE_MASK) == MODE_PLAY)?480:320;
	return 480; // as in sd980


}

long vid_get_bitmap_screen_height()
{
//    return SCREENY;  // ---- yes, the buffer is also greater,
                     //   seems a 16/9 buffer (i.e. 480x270) but duplicating pixels at x : (480x2)x270
	return 240;
}


int vid_get_viewport_width()
{
    //return ((mode_get()&MODE_MASK) == MODE_VIDEO_STD ||(mode_get()&MODE_MASK) == MODE_PLAY)?480:320;
    return 480; // as in sd980
    //return 360;                                               // stays at 360 as IN SD990
}

long vid_get_viewport_height()
{
    return 240;
}




long vid_get_bitmap_buffer_width() { return 960; }

long vid_get_bitmap_buffer_height() { return 270; }

*/


//ASM1989 08.20.2010
char *camera_jpeg_count_str()
{
 return (void*)0xA05DC;                                      // found at FFA0E708
}
