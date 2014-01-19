#include "platform.h"

char *hook_raw_image_addr()     {return (char*) 0x420B7FC0;}   //Found @0xffae1e14 A4000IS 100c  Search for BJPEG BUFF 
char *hook_alt_raw_image_addr() {return (char*) 0x420B7FC0;}   //Found @0xffae1e14 A4000IS 100c  Search for BJPEG BUFF 

/*Auto generated for A4000IS 101a*/
void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff852d80
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2960+0x54)); } // Found @0xff867a04 & 0xff867a3c
char *camera_jpeg_count_str()    { return (char*)0x000b1abc; }             // Found @0xff9cd838
long hook_raw_size()             { return 0x01794300; }                    // Found @0xffae1e74
int get_flash_params_count(void) { return 0xa6; }                        // Found @0xff989b60
