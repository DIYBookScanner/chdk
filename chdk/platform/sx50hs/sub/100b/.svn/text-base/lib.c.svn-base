#include "platform.h"

char *hook_raw_image_addr()
{
	// [0x3B14 + 0xC] --> defines which buffer is active

    if (*((int*)(0x3B14 + 0xC)) != 0)       //SX50: 0x3B14 (@FF08A0B0 ) + 0xC (@FF08A0DC)
        return (char*) 0x4ADB23C0;
    else
        return (char*) 0x44000000;
}

char *hook_alt_raw_image_addr()
{
    if (*((int*)(0x3B14 + 0xC)) == 0)
        return (char*) 0x4ADB23C0;
    else
        return (char*) 0x44000000;
}

long hook_raw_size() {
    return 0x124AB50;                       //SX50 @FF43302C
}

void *vid_get_viewport_fb_d() {
    return (void*)(*(int*)(0x3650+0x54));   //SX50 @FF074F14 & FF074F4C
}

char *camera_jpeg_count_str() {
     return (void*)0x110A74;                 //SX50 @FF28EE48
}

char *camera_jpeg_current_filename() {
     return (void*)0x111450;                 //SX50 @FF2ADF80
}



