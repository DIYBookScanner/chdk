#include "platform.h"

//To do: 1) test raw related functions.
//       2) test vieport functions.

char *hook_raw_image_addr()
{
    return (char*)(0x1058edd4); //Found @ 0xff92480c
}

long hook_raw_size()
{
    return 0x644C40; //TODO: 2672*1968*1.25 ??
}

void *vid_get_viewport_live_fb() //from ixus65
{
    void **fb=(void **)0x5564; // ixusw @ 0xff8aa7f8
    unsigned char buff = *((unsigned char*)0x5574);
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
    return (void*)0x103c79a0; // found by srsa_4c
}

void *vid_get_viewport_fb()
{
    return (void*)0x105f1570; // found @ 0xff928e08 by comparison to ixus55 100b
}

void *vid_get_viewport_fb_d()
{
 return (void*)(*(int*)0x84150); //found @ 0xff92aed0 by comparison to ixus55 100b
}

long vid_get_viewport_height()
{
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}
char *camera_jpeg_count_str()
{
    return (char*)0xa220; //found @ 0xffa4a96c near to "9999". Check this!!!
}

// TODO: PTP display
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

void *vid_get_bitmap_active_palette() {
    return (void *)0x84050; // Check this!! found @ 0xff929448 by comparison to ixus700 101a
}
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x6cbc); //0x6cc4?? Check this!!! found @ 0xff92945c by comparison to ixus700 101a
}


