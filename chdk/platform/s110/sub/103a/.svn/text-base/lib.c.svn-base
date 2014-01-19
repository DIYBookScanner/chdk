#include "platform.h"

char *hook_raw_image_addr()
{
	if (*((int*)(0x3F3C + 0xC)) != 0) // 0x3F3C (@F80C5EF8) + 0xC (@F80C5F28)
        return (char*) 0x4ad65bc0;
    else
        return (char*) 0x44000000;
}

char *hook_alt_raw_image_addr()
{
    if (*((int*)(0x3F3C + 0xC)) == 0) // 0x3F3C (@F80C5EF8) + 0xC (@F80C5F28)
        return (char*) 0x4ad65bc0;
    else
        return (char*) 0x44000000;
}

char *camera_jpeg_current_filename() {
     return (void*)0x1ADE4C;                 // @F83401D4
}

void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xf8074fa0
void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xf8519358
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3838+0x54)); } // Found @0xf8095da8 & 0xf8095de0
char *camera_jpeg_count_str()    { return (char*)0x001ad150; }             // Found @0xf8319350
long hook_raw_size()             { return 0x01297380; }                    // Found @0xf851acf4

