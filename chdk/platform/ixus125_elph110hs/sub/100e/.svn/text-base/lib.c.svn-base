#include "platform.h"

char *hook_raw_image_addr()
{
    // Appears to be two raw buffers (this returns active buffer)
    // Addresses below found in table at FF42793C used in sub_FF0D4478
    // [0x2EA0 + 0xC] --> defines which buffer is active
	
    if (*((int*)(0x2EA0 + 0xC)) != 0)       //loc_ff06c884: 0x2EA0 (@FF06C888 ) + 0xC (@FF06C8B4)
        return (char*) 0x4A7ECA00;
    else
        return (char*) 0x44000000;          
}

char *hook_alt_raw_image_addr() {
    if (*((int*)(0x2EA0 + 0xC)) == 0)
        return (char*) 0x4A7ECA00;
    else
        return (char*) 0x44000000;
}

//Found by finsig ixus125 100e
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff0448b8
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2bd8+0x54)); } // Found @0xff05e4c8 & 0xff05e500
char *camera_jpeg_count_str()    { return (char*)0x000c7158; }             // Found @0xff2391e8
long hook_raw_size()             { return 0x0180fde0; }                    // Found @0xff3ab130
int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff1cb504
