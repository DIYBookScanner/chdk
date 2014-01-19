#include "platform.h"

char *hook_raw_image_addr()
{
return (char*)0x10A87B58; //ixus40 value seems ok
}

long hook_raw_size()
{
    return 0x3ff520; //@ff915f30, ixus40 value is ok
}

// buffer of live picture when shoot button is not pressed
void *vid_get_viewport_live_fb()
{
//there seem to be 3 buffers:
//pointer -> buffer
//0x52E4  -> 0x109CBD20
//0x52F0  -> 0x10A6A760
//0x52FC  -> 0x10B02560
//above buffer _addresses_ are the same in ixus30, ixus40

//suspicious code @ff8a4250, it's kind of like @ffc8e724 in A410...
void **fb=(void **)0x3204; //@ff8a4254
unsigned char buff = *((unsigned char*)0x3214); //@ff8a4250
if (buff == 0) {
    buff = 2;
}
else {
    buff--;
}
return fb[buff]; 
//above is experimental, the following works for sure
//return (void*)0x10B02560;
}

/**
 * OSD screen
  */
void *vid_get_bitmap_fb()
{
/*
@6b6b0 108ceb20 @8e2ac? @afb88 @b187c
@6b6b4 108E3CA0 (108ceb20+(360*240)) @afb8c
*/
    return (void*) 0x108CEB20; //@ff9279d0, same as in ixus40
    //return (void*) *(long*) (*(int*)0x6b6d0 == 1)?0x6b6b0:0x6b6b4; //experiment... no go...inspired by routine @ff96862c
}

/**
 * IMG viewport in 'rec' mode
 */
// buffer of live picture when shoot button is (half-)pressed.
void *vid_get_viewport_fb()
{
    return (void*)0x10B02560; //todo
}

/**
 * IMG viewport in 'play' mode
 */
// buffer of picture in play mode
void *vid_get_viewport_fb_d()
{
	//return (void*)(*(int*)0x66820); //not really good either...
	return (void*)0x109CBD20; //sort of works...
	//return (void*)0x10a6a760; //
	//return (void*)0x112fc960; //the last full view of the picture, not affected by zoom (!)
}

long vid_get_viewport_height()
{
/*
In replay mode, the viewport height is:
 576 pixel (PAL output setting, TV-out in use)
 480 pixel (NTSC output setting, TV-out in use)
 240 pixel (no tv-out)
In rec mode, it's really only 240...
In 640x480 movie mode, the viewport is 720x480
Conclusion: expect correct results only when the height is 240
*/
//    return ((mode_get()&MODE_MASK) == MODE_PLAY)?576:240;
    return 240;
}

int vid_get_viewport_width() //in both rec and play modes, 352 while tv-out is active
{
    return 360;
}

int vid_get_viewport_buffer_width()
{
    return 360;
}

char *camera_jpeg_count_str()
{
    return "0000"; //TODO
}
