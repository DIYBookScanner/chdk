#include "platform.h"

void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xffc43628
void *vid_get_viewport_fb()      { return (void*)0x40507700; }             // Found @0xffe780c8
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2670+0x58)); } // Found @0xffc571f4 & 0xffc57228
char *camera_jpeg_count_str()    { return (char*)0x00077fdc; }             // Found @0xffd83ba4
long hook_raw_size()             { return 0x011e4ee0; }                    // Found @0xffe7b480
int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd40034

char *hook_raw_image_addr()
{
	//ffe7b424: 	e59f60dc 	ldr	r6, [pc, #220]	; ffe7b508: (41d64ecc)  *"...AJPEG BUFF       %p ( %lx )"
	return (char*)(0x41d64ecc);
}

void *vid_get_viewport_live_fb() //TODO:
{
  return (void*)vid_get_viewport_fb();
}
