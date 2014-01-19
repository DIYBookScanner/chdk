#include "platform.h"

/*
*********************
IXUS1000IS
**********************
note sensor size for camera.h is from  //ASM1989
@ FFB500D4         -> SX210: FFB2FC6C
0xF32880 = 15935616						sx210-> 0x14D2400  = 21832704

15935616 / 12 * 8 = 10623744 				sx210 -> 21832704 / 12 * 8 = 14555136
---
                              |
@ FFB4FC20     -> SX210: FFB2F7C0                    |
=0xEE8  x 0xAE0						-> SX210  -> 0x1140 by 0xCE0 =             |
3816 x 2784 =   10623744                sx210 ->  4416 * 3296  = 14555136  ---
*/

char *hook_raw_image_addr()   //ASM1989  DONE FOR IXUS 1000
{
	if (*((int*)0x34D0) != 0)    //  34C4 + C  ->   FF885154  ->FF885180   (ixus 1000)
		return (char*)(0x46000000);	// at FFB8ECF4  pointed at aSsimgprocbuf_c DCB "SsImgProcBuf.c",0
	else
		return (char*) 0x4132CD20;	// found at[search CRAW BUF]
} 

char *hook_alt_raw_image_addr()
{
	// Appears to be two raw buffers (this returns inactive buffer)
	// Addresses below found in table at FFB9922C, ref at FF88883C
	// used in _sub_FF888630__SsImgProcBuf.c__0 
	// checks [0x36a0 + 0xc] --> defines which buffer is active

	if (*((int*)0x34D0) == 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x4132CD20;	
} 

long hook_raw_size() //ASM1989 ixus1000
{
	//found at FFB4FFF4
			//ROM:FFB4FFF4                 LDR     R1, =0xF32880
			//ROM:FFB4FFF8                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"


	return 0xF32880;
}



// Live picture buffer (shoot not pressed) //ASM1989  keept like sx210
void *vid_get_viewport_live_fb()
{


    return 0x0;
/*
  //sx210 code left
    void **fb=(void **)0x2180;                               // 0x2150 or 0x2180 (old SX200) ???? What for SX210
    unsigned char buff = *((unsigned char*)0x2058);          // found at FF84FA18 (guess work)
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];*/


}



// OSD buffer  //ASM1989 ixsu1000
void *vid_get_bitmap_fb()
{
	return (void*)0x40471000;                              // found at FFA97414
}



// Live picture buffer (shoot half-pressed) //ASM1989 ixus1000
void *vid_get_viewport_fb()
{
	return (void*)0x40587700;                              // found by search for VRAM Address @FFB4CB2C
}


// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d()
{

	return (void*)(*(int*)(0x3230+0x58));                  // found at FF877D10  (0x58 atFF877D48)
}

// begin 16:9 support

// Physical width of viewport row in bytes
int vid_get_viewport_byte_width() {
	return 960 * 6 / 4;     // IXUS 1000 - wide screen LCD is 960 pixels wide, each group of 4 pixels uses 6 bytes (UYVYYY)
}

int vid_get_viewport_width()
{
    extern int kbd_debug1;
    //kbd_debug1 = mode_get();
    if (movie_status > 1){return 480;}
    if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1 )	// on 16:9 shoot mode its 1.switch to video is 100
		return 480; 
    else
       return 360; 
}

int vid_get_viewport_display_xoffset()
{
    if (movie_status > 1){return 0;}
	if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1  || ((mode_get()&MODE_MASK)== 100 ))	
	   return 0;
	else
       return 60;
}

// end 16:9 support

long vid_get_viewport_height()
{
    return 240;
}


char *camera_jpeg_count_str()
{
 return (void*)0xB7E00;                                      // found at FFA23818
}
