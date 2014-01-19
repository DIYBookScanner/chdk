#include "platform.h"

char *hook_raw_image_addr()
{
  return (char*) 0x41F723E0; // with help of SD980 (sub_FF8B8514)
}

long hook_raw_size()
{
  return 0x11CA240; // FF867B38
}

void *vid_get_viewport_live_fb() // found in sub_FF84DDB8
{
  void **fb=(void **)0x222C;
  unsigned char buff = *((unsigned char*)0x206C);
  if (buff == 0) buff = 2;  else buff--;    
  return fb[buff];
}

void *vid_get_bitmap_fb()
{
  return (void*)0x403F1000; // sub_FF90A358 
}

void *vid_get_viewport_fb()
{
  return (void*)0x41020120; // sub_FF8CB908
}

void *vid_get_viewport_fb_d()
{
  return (void*)(*(int*)(0x2A30+0x58)); // sub_FF8718D0
}

int vid_get_viewport_width()
{
  return 360;
}

long vid_get_viewport_height()
{
  return 240;
}

char *camera_jpeg_count_str()
{
  return (char*)0x72DB0; // loc_FF9F71B0
}
