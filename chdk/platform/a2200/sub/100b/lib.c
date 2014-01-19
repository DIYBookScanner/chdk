#include "platform.h"		

int get_flash_params_count(void) {
	
	return 0xA0;				// Found @0xFF98E5AC
}

char *camera_jpeg_count_str() {
	
	return (char*)0x000B3B14;	// Found @0xFF9F71C8
}	

char *hook_raw_image_addr() {
	
	//if (*((int*)(0x2B68 + 0xC)) != 0)	// Found @0xFF87A198 + @0XFF87A1C4
	//	return (char*) 0x46000000;
	//else
	//	return (char*) 0x421316C0;
		
	return (char*)0x421316C0;	// Found @0xFFB1A77C
}		

char *hook_alt_raw_image_addr()	{
	
	//if (*((int*)(0x2B68 + 0xC)) != 0)	// Found @0xFF87A198 + @0XFF87A1C4
	//	return (char*) 0x46000000;
	//else
	//	return (char*) 0x421316C0;
		
	return (char*)0x421316C0;	// Found @0xFFB1A77C
}

long hook_raw_size() {
	
	return 0x014d2400;			// Found @0xFFB1A7D4
}			

void *vid_get_bitmap_fb() {
	
	return (void*)0x403F1000;	// Found @0xFF85B81C
}	
	
void *vid_get_viewport_live_fb() {
	
	//if ((mode_get()&MODE_MASK) == MODE_REC)
	//	return (void*)((void*)(*(int*)(0x2144))-vid_get_viewport_xoffset()*3);
	
	return (void*)(void*)(*(int*)(0x2144));	// Possible addresses (20F0, 2144, 221C)
	
  	// Found by searching RAM locations that referenced 0x40546B80 (viewport buffer)
	// and also changed to the other buffer addresses over time. Then used each here
	// and selected value that gave the fastest Motion Detect response using http://dataghost.com/chdk/md_meter.html.
}

void *vid_get_viewport_fb() {
	
	//if ((mode_get()&MODE_MASK) == MODE_REC)
	//	return (void*)(0x40546B80-vid_get_viewport_xoffset()*3);
		
	return (void*)0x40546B80;	// Found @0xFFB17310
}		
		
void *vid_get_viewport_fb_d() {
	

	return (void*)(*(int*)(0x29a0+0x58));	// Found @0xff871344 & 0xff87137c
}		

void vid_bitmap_refresh() {
	
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}
