#include "platform.h"

char *hook_raw_image_addr()     {return (char*) 0x420B7FC0;} //Search for BJPEG BUFF
char *hook_alt_raw_image_addr() {return (char*) 0x420B7FC0;} //Search for BJPEG BUFF

/*Auto generated for a2400 100e*/
void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff852df0
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2960+0x54)); } // Found @0xff867a78 & 0xff867ab0
char *camera_jpeg_count_str()    { return (char*)0x000b1ebc; }             // Found @0xff9ce53c
long hook_raw_size()             { return 0x01794300; }                    // Found @0xffae2e98
