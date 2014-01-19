#include "platform.h"

/*  OK FOR 100F
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
	//found at FFB4FF90

	//ROM:FFB4FF90                 LDR     R6, =0x4132CD20
	//..
	//ROM:FFB4FFE8                 MOV     R1, R6
    //ROM:FFB4FFEC                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"

	//GOOD ONE
	//return (char*)(0x4132CD20);
//NO: 44CF6800 ni 420F85B2 ni 46DCB892 ni 433FCF80


	if (*((int*)0x34D0) != 0)    //  34C4 + C  ->   FF885154  ->FF885180   (ixus 1000)
		return (char*)(0x46000000);	// found by dumping all memory and searching for raw image bytes at FFB8ECF4  pointed at aSsimgprocbuf_c DCB "SsImgProcBuf.c",0
	else
		return (char*) 0x4132CD20;	// found at[search CRAW BUF]



	//return (char*)(0x4132CD20);

	//Testing  this is SX210 code and addresses keept for if its needed in this cam
	//return (char*) (*(int*)(0x3310+0x18) ? 0x43289400 : 0x415D7CC0);   //0x3310 at FF880698 others at FF86AA48

	//testing the other raw method FAILS
//	return (char*) (*(int*)(0x34C4+0x18) ? 0x47209000 : 0x44A345C4);   //0x34C4 at FF885B94  others at FF86C7D4



}

//WITH this buffer all white: 0x44CF6800


/*
sensor size for ixus100:

@FFB4FC24 = 0xEE8 = 3816	// raw sensor size
@FFB4FC2C = 0xAE0 = 2784

@FFB4FC34 = 0xE40 = 3648	// cropped size = JPG SIZE
@FFB4FC3C = 0xab0 = 2736
*/

//Testing Sx30 style
/*
char *hook_raw_image_addr()
{

	if (*((int*)0x34D0) != 0)
		return (char*) 0x44CF6800;	// found by dumping all memory and searching for raw image bytes
	else
		return (char*) 0x4132CD20;	// found at (0xFFB59F40) [search CRAW BUF]
}

char *hook_alt_raw_image_addr()
{
	if (*((int*)0x34D0) == 0)
		return (char*) 0x44CF6800;	// found by dumping all memory and searching for raw image bytes
	else
		return (char*) 0x4132CD20;	// found at (0xFFB59F40) [search CRAW BUF]
}
*/

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
