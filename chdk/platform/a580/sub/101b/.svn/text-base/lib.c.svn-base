#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0;
}

void *hook_raw_ret_addr()
{
    return (void*)0;
}

char *hook_raw_image_addr()
{
    return (char*)0x10F341C0; //found at 0xFFC77400, OK
}

long hook_raw_size()
{
    return 0x009e6fc4;		// Corrected! from 0x009dcce0 (from stubs_entry.S)
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0;//0x10670ee0;
    void **fb=(void **)0x6AA8; //0xFFCA0CC4
    unsigned char buff = *((unsigned char*)0x1FE8);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;		// OK!
}

void *vid_get_viewport_fb()
{
    return (void*)0x10659E80;		// OK!
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x5050 + 0x48);  // may be...
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x00048AE0;		// OK!
}
