#include "platform.h"		

int get_flash_params_count(void) {
	
	return 0xA0;				// Found @0xFF98E5AC
}

char *camera_jpeg_count_str() {
	
	return (char*)0x000B3B14;	// Found @0xFF9F71C8
}	

char *hook_raw_image_addr() {
	
		return (char*) 0x421316C0;
}		

char *hook_alt_raw_image_addr()	{
	
		return (char*) 0x421316C0;
}

long hook_raw_size() {
	
	return 0x014d2400;			// Found @0xFFB1A7D4
}			

void *vid_get_bitmap_fb() {
	
	return (void*)0x403F1000;	// Found @0xFF85B81C
}	
	
void *vid_get_viewport_live_fb() {
	
	return (void*)(*(int*)(0x20D0+0x138));		//FF850C88 + FF850CD8
	// and selected value that gave the fastest Motion Detect response using http://dataghost.com/chdk/md_meter.html.
}

void *vid_get_viewport_fb() {
	
	return (void*)0x40546B80;	// Found @0xFFB17310
}		
		
void *vid_get_viewport_fb_d() {
	
	return (void*)(*(int*)(0x29A0+0x58));     // FF870CB0 +  FF870D38
}

void vid_bitmap_refresh() {
	
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}
