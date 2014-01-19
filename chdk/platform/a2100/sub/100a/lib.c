// A2100IS 1.00A
/*
###########################################################
###########################################################
#############[ FINISHED !!!! ]#############################
###########################################################
###########################################################
*/

#include "platform.h"

/*
G10 sensor size from code at sub_FFACDE4C = (4480*3348)*(12/8) = 0x1574D00 = 22498560

0x1180 = 4480	// raw sensor size  @ 0xFFACDE4C
0xD14 =  3348	// 					@ 0xFFACDE50
0x1140 = 4416	// jpeg size 
0xCF0 =  3312	//
*/

void *vid_get_bitmap_fb()        { return (void*)0x403f1000; } // Found @0xffc2c5cc
void *vid_get_viewport_fb()      { return (void*)0x4076fcc0; } // Found @0xffe441f8
char *camera_jpeg_count_str()    { return (char*)0x0002f55c; } // Found @0xffd60580
long hook_raw_size()             { return 0x011e4ee0; }        // Found @0xffe46760
int get_flash_params_count(void) { return 0x7a; }              // Found @0xffd1cfec

// fixed!
char *hook_raw_image_addr()
{
// 
// ROM:FFE4670C                 LDR     R4, =0x40CED8C0

return (char*)0x4139E56C; // seach on CRAW BUF

	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FFC4AA5C
	// used in ROM:FFC4AA5C                 EXPORT _sub_FFC4AA5C__SsImgProcBuf.c__0
	// checks [0x2848 + 0x1C] --> defines which buffer is active
	
	//ROM:FFC4A2A0 ; LOCATION: SsImgProcBuf.c:0
	// ROM:FFC4A2A4                 LDR     R4, =0x2848
	// ROM:FFC4A2A8                 LDR     R0, [R4,#0x18]

//ROM:FFC4A334                 LDR     R0, =0x40E166C0
//ROM:FFCC7C74                 LDR     R1, =0x4139E56C - found by aCrwaddressLxCr tag
	// if (*((int*)0x2860) != 0)
		// return (char*)0x40E166C0;			// G10 @ 0xFFB101AC
	// else
		// return (char*)0x4139E56C;			// G10 searched for aCrwaddressLxCr or for aCrawBuffP 0xFFACDE48
		
		
}

// char *hook_alt_raw_image_addr()
// {
	// // Appears to be two raw buffers (this returns active buffer)
	// // Addresses below found in table at FFB1017C , ref at FFBBAD50
	// // used in _sub_FF86837C__SsImgProcBuf.c__0 
	// // checks [0x555C + 0x18] --> defines which buffer is active
// //ROM:FFC4A334                 LDR     R0, =0x40E166C0
// //ROM:FFCC7C74                 LDR     R1, =0x4139E56C - found by aCrwaddressLxCr tag
	// if (*((int*)0x2860) == 0)
		// return (char*) 0x40E166C0;			// G10 @ 0xFFB101AC
	// else
		// return (char*)0x4139E56C;			// G10 searched for aCrwaddressLxCr or for aCrawBuffP 0xFFACDE48
// }


// long hook_raw_size()
// { 
	// return 0x01574d00;         				// G10 autofound @0xffad712c - search CRAW BUF SIZE
// }

// char *camera_jpeg_count_str()
// {
	// return (char*)0x0004c95c; 				// G10 autofound @0xff9cccdc
// } 

// void *vid_get_bitmap_fb()
// {
	// return (void*)0x40471000; 				// G10 autofound @0xff846a4c DispCon_ShowBitmapColorBar 
// }

// void *vid_get_viewport_fb()
// {
	// return (void*)0x40816dc0;  				// G10 autofound @0xffad4d70 -  search on VRAM Address
// }

void *vid_get_viewport_fb_d()				// G10 found
{
//ac: ROM:FFC3FAEC                 LDR     R8, =0x2628
//ac: ROM:FFC3FB1C                 LDREQ   R0, [R8,#0x1C] 
	return (void*)(*(int*)(0x2628+0x58)); 	// @FF85ADD8 & FF85AE28 (comp S95, G11 - search for aImageplayer_c)
}											// @FF85B864 & FF85B89C

void *vid_get_viewport_live_fb()			// G10 @ FF83A41C routine - match with IXUS980_SD990
{	

//ac: Unknown how to find these values
    void **fb=(void **)0x2710;  // 0xFFC243F8 - ? ; also, may be FFC241D8                 LDR     R1, =0x1F34
    unsigned char buff = *((unsigned char*)0x1EC8);  // 0xFFC24228
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}
