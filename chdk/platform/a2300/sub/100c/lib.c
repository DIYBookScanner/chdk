#include "platform.h"

char *hook_raw_image_addr()     {return (char*) 0x420B7FC0;} //Search for BJPEG BUFF 
char *hook_alt_raw_image_addr() {return (char*) 0x420B7FC0;} //Search for BJPEG BUFF

/*Auto generated for a2300 100c*/
void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff852ebc
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2970+0x54)); } // Found @0xff867dc0 & 0xff867df8
char *camera_jpeg_count_str()    { return (char*)0x000b376c; }             // Found @0xff9c90a8
long hook_raw_size()             { return 0x01794300; }                    // Found @0xffae0c8c
int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff9858b0
