#include "platform.h"

extern  int     active_raw_buffer;
extern  char*   raw_buffers[];

char *hook_raw_image_addr()
{
    return raw_buffers[active_raw_buffer*3];
}

char *hook_alt_raw_image_addr()
{
    return raw_buffers[(active_raw_buffer^1)*3];
}

char *camera_jpeg_count_str()
{
    extern char jpeg_count_str[];
    return jpeg_count_str;
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

// Defined in stubs_min.S
extern char active_viewport_buffer;
extern void* viewport_buffers[];


void *vid_get_viewport_fb()
{
    // Return first viewport buffer - for case when vid_get_viewport_live_fb not defined
    return viewport_buffers[0];
}

// Live picture buffer (shoot not pressed) //ASM1989  keept like sx210
void *vid_get_viewport_live_fb()
{
    if (MODE_IS_VIDEO(mode_get()))
        return viewport_buffers[0];     // Video only seems to use the first viewport buffer.

    // Hopefully return the most recently used viewport buffer so that motion detect, histogram, zebra and edge overly are using current image data
    return viewport_buffers[(active_viewport_buffer-1)&3];
}

void *vid_get_viewport_fb_d()
{
    extern char *viewport_fb_d;
    return viewport_fb_d;
}


// OSD buffer  //ASM1989 ixsu1000
void *vid_get_bitmap_fb()
{
	return (void*)0x40471000;                              // found at FFA97414
}


//TODO: Liveview is not working
// begin 16:9 support

// Physical width of viewport row in bytes
int vid_get_viewport_byte_width() {
    return 960 * 6 / 4;     // IXUS 1000 - wide screen LCD is 960 pixels wide, each group of 4 pixels uses 6 bytes (UYVYYY)
}

int vid_get_viewport_width()
{
    if (movie_status > 1){return 480;}
    if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1 ) // on 16:9 shoot mode its 1.switch to video is 100
        return 480;
    else
       return 360;
}

int vid_get_viewport_display_xoffset()
{
    if (movie_status > 1){return 0;}
    if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1  || ((mode_get()&MODE_MASK)== 100 ))
       return 0;
    else
       return 60;
}

// end 16:9 support

long vid_get_viewport_height()
{
    return 240;
}
