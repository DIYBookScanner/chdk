#include "platform.h"


char *hook_raw_image_addr()
{
    if (*((int*)(0x3F58 + 0xc)) != 0)       //0x3F58 ( @FF07B02C ) +0xC (@FF07B0A4 )
    {
        return (char*) 0x46000000;  //@FF066A14
    }
    else
    {
        return (char*) 0x413591F0;  //@FF37FB7C
    }
}

char *hook_alt_raw_image_addr()
{
    if (*((int*)(0x3F58 + 0xc)) == 0)
        return (char*) 0x46000000;
    else
        return (char*) 0x413591F0;
}

long hook_raw_size()
{
    return 0x123EAF0;
}

void *vid_get_viewport_live_fb()
{
    return (void*)(void*)(*(int*)(0x225C));
}

void *vid_get_bitmap_fb()
{
    return (void*)0x40471000;
}

void *vid_get_viewport_fb()
{
    return (void*)0x405D7980;
}


void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x3CD0+0x58));

}

char *camera_jpeg_count_str()
{
     return (void*)0xCE488;
}

char *camera_jpeg_current_filename()
{
	 return (void*)0xCA818;
}

char * camera_jpeg_current_latitude()
{
	return (void*)0xCA890;
}

char * camera_jpeg_current_longitude()
{
	return (void*)0xCA8AC;
}

char * camera_jpeg_current_height()
{
	return (void*)0xCA668;
}
