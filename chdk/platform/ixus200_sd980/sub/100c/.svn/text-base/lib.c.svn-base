#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*)0x421E1120;
}

long hook_raw_size()
{
	return 0x11CA240;
}

void *vid_get_viewport_live_fb()//found in sub_FF8E0788
{
    void **fb=(void **)0x5014;
    unsigned char buff = *((unsigned char*)0x4E5C);
    if (buff == 0) buff = 2;  else buff--;
//    return fb[buff];
	if ((mode_get()&MODE_MASK) == MODE_REC)
		return (void*)(fb[buff]-vid_get_viewport_xoffset()*3);
	return (void*)fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x40431000;
}

void *vid_get_viewport_fb()
{
//	return (void*)0x408CB700;
	if ((mode_get()&MODE_MASK) == MODE_REC)
		return (void*)(0x408CB700-vid_get_viewport_xoffset()*3);
	return (void*)0x408CB700;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x28F0+0x58));
}


long vid_get_bitmap_screen_width()   { return 480; }
long vid_get_bitmap_screen_height()  { return 240; }
long vid_get_bitmap_buffer_width()   { return 960; }
long vid_get_bitmap_buffer_height()  { return 270; }


long vid_get_viewport_height()       { return 240; }

// Physical width of viewport row in bytes
int vid_get_viewport_byte_width() {
	return 960 * 6 / 4;     // IXUS 200 - wide screen LCD is 960 pixels wide, each group of 4 pixels uses 6 bytes (UYVYYY)
}

int vid_get_viewport_width()
{
    if (shooting_get_prop(PROPCASE_RESOLUTION) == 8)	// widescreen (16:9) image size
		return 480;
    else
        return 360;
}

int vid_get_viewport_xoffset()
{
	if (shooting_get_prop(PROPCASE_RESOLUTION) == 8)	// widescreen (16:9) image size
	   return 0;
	else
       return 60;
}

char *camera_jpeg_count_str()    
{ 
	return (char*)0x00084ca4;              // Found @0xff9e8aa8
}

//only for cameras with a touchscreen
short get_touch_click_x()
{
	return *(short*)(0x258C+6);
}

short get_touch_click_y()
{
	return *(short*)(0x258C+8);
}
