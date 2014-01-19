#include "platform.h"

char *hook_raw_image_addr()   
{
		return (char*) 0x4207DB20;		//Found at FFB217F0 a3300is
	
}

char *hook_alt_raw_image_addr() 
{
		return (char*) 0x4207DB20;		//Found at FFB217F0
}

long hook_raw_size()
{
	return 0x01794300; // Found @0xffb21768  a3300is
}

char *camera_jpeg_count_str()
{
	 return (void*)0xb40d4;   // Found @0xff9fd850   a3300is                                 
}


void *vid_get_bitmap_fb()
{	
	return (void*)0x403f1000; // Found @0xff85b880 a3300is
}	                           


void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x29A0+0x58));     // FF8708C8 +  FF870DE0  a3300is         
}



void *vid_get_viewport_live_fb()
{
	return (void*)(*(int*)(0x20D0+0x138));		//FF850CE8 + FF850D38	a3300is
}

                 
void *vid_get_viewport_fb()
{	
	return (void*)0x40546b80;       // Found @0xffb1e2ac   a3300is          
}

void vid_bitmap_refresh() {
	
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}
