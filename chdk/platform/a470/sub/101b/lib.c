#include "platform.h"

void *vid_get_viewport_live_fb()
{
    return (void*)0; // Fast MD not implemented
}

void *vid_get_viewport_fb_d()
{
    //return (void*)(*(int*)0x5228);  // same as 100e, eg FFC44B58
	// http://chdk.setepontos.com/index.php/topic,2361.msg27125.html#msg27125
	// sub_FFC45328
	return (void*)(*(int*)(0x5080+0x4C));  //might wanna check this, found above ImagePlayer.c
}

char *camera_jpeg_count_str()
{
    return (char*)0x49A00; // found above a9999
}
