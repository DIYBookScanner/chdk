#include "platform.h"

char *hook_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at 0xFFB9AE28 used in sub_FF883610
	// checks [0x2E30 + 0xc] --> defines which buffer is active

	if (*((int*)0x2E3C) != 0)		// [0x2E30+0xC] look at routine starting at FF883610
		return (char*) 0x46000000; 	// these two addresses found in table FFB9AE28 (used in FF883610)
	else
		return (char*) 0x413391A0;	//

}

char *hook_alt_raw_image_addr()
{

	if (*((int*)0x2E3C) == 0)		//0x3F04 - unknown
		return (char*) 0x46000000;
	else
		return (char*) 0x413391A0;

}

long hook_raw_size()
{
	//FFB59920 dword_FFB59920  DCD 0x123EAF0
	return 0x123EAF0;

}

void *vid_get_viewport_live_fb()
{
	if ((mode_get()&MODE_MASK) == MODE_REC)
		return (void*)((void*)(*(int*)(0x2358))-vid_get_viewport_xoffset()*3);	//0x2258
	return (void*)(void*)(*(int*)(0x2358));

  	// Found by searching RAM locations that referenced 0x405D7980 0x405C6B80 (viewport buffer)
	// and also changed to the other buffer addresses over time. Then used each here
	// and selected value that gave the fastest Motion Detect response using http://dataghost.com/chdk/md_meter.html.
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	//elph100
	//FF92668C                 LDR     R0, =0x40471000
	return (void*)0x40471000;
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	//elph100

		if ((mode_get()&MODE_MASK) == MODE_REC)
		return (void*)(0x405C6B80-vid_get_viewport_xoffset()*3);   //return (void*)(0x405C6B80-vid_get_viewport_xoffset()*3)

	return (void*)0x405C6B80;  					                   // found by search for VRAM Address @FFB56360 (near to "VRAM Address")

}

void *vid_get_viewport_fb_d()
{
	//FF876518 dword_FF876518  DCD 0x3C70
	//FF877298                 STR     R12, [R5,#0x58]
	return (void*)(*(int*)(0x2BA0+0x58));

}

char *camera_jpeg_count_str()
{
	//FFA2629C         LDR     R0, =0xBB3A8 (near to "9999")
	return (void*)0xBB3A8;

}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x5AC4+0x18)); //found @ loc_ff9267ac ixus115 101b
}

