#include "platform.h"

char *hook_raw_image_addr()
{
	if (*((int*)(0x38fc + 0xC)) != 0) //G15: 0x38fc (@FF089C38 ) + 0xC (@FF089C64)
        return (char*) 0x4ad65bc0;
    else
        return (char*) 0x44000000;
}

char *hook_alt_raw_image_addr()
{
    if (*((int*)(0x38fc + 0xC)) == 0)
        return (char*) 0x4ad65bc0;
    else
        return (char*) 0x44000000;
}

char *camera_jpeg_current_filename() {
     return (void*)0xe7a48;                 // @FF2A3110
}

void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff057d44
void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xff430de4
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3530+0x54)); } // Found @0xff0760cc & 0xff076104
char *camera_jpeg_count_str()    { return (char*)0x000e7034; }             // Found @0xff2830a8
long hook_raw_size()             { return 0x01297380; }                    // Found @0xff432780
