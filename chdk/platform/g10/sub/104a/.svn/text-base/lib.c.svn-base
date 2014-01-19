#include "platform.h"

/*
G10 sensor size from code at sub_FFACDE4C = (4480*3348)*(12/8) = 0x1574D00 = 22498560

0x1180 = 4480	// raw sensor size  @ 0xFFACDE4C
0xD14 =  3348	// 					@ 0xFFACDE50
0x1140 = 4416	// jpeg size 
0xCF0 =  3312	//
*/

char *hook_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FFB1017C , ref at FFBBAD50
	// used in _sub_FF86837C__SsImgProcBuf.c__0 
	// checks [0x555C + 0x18] --> defines which buffer is active

	if (*((int*)0x5574) != 0)
		return (char*)0x43164D80;			// G10 @ 0xFFB101AC
	else
		return (char*)0x413245A0;			// G10 searched for aCrwaddressLxCr or for aCrawBuffP 0xFFACDE48
}

char *hook_alt_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FFB1017C , ref at FFBBAD50
	// used in _sub_FF86837C__SsImgProcBuf.c__0 
	// checks [0x555C + 0x18] --> defines which buffer is active

	if (*((int*)0x5574) == 0)
		return (char*) 0x43164D80;			// G10 @ 0xFFB101AC
	else
		return (char*)0x413245A0;			// G10 searched for aCrwaddressLxCr or for aCrawBuffP 0xFFACDE48
}


long hook_raw_size()
{ 
	return 0x01574d00;         				// G10 autofound @0xffad712c - search CRAW BUF SIZE
}

char *camera_jpeg_count_str()
{
	return (char*)0x0004c95c; 				// G10 autofound @0xff9cccdc
} 

void *vid_get_bitmap_fb()
{
	return (void*)0x40471000; 				// G10 autofound @0xff846a4c DispCon_ShowBitmapColorBar 
}

void *vid_get_viewport_fb()
{
	return (void*)0x40816dc0;  				// G10 autofound @0xffad4d70 -  search on VRAM Address
}

void *vid_get_viewport_fb_d()				// G10 found
{
	return (void*)(*(int*)(0x524C+0x54)); 	// @FF85ADD8 & FF85AE28 (comp S95, G11 - search for aImageplayer_c)
}											// @FF85B864 & FF85B89C

void *vid_get_viewport_live_fb()	// G10 @ FF83A41C routine - match with IXUS980_SD990
{	
    void **fb=(void **)0x2298;
    unsigned char buff = *((unsigned char*)0x20FC);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

// ptp
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x8034+0x14)); // sub_FF8F331C via "Add: %p Width : %ld Hight : %ld", 
}

