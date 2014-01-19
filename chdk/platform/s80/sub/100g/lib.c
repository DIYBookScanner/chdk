#include "platform.h"
#include "lolevel.h"
#include "debug_led.h"

char *hook_raw_image_addr()
{
    return (char*)0x1056B960;       // aA08x_crw, followed sd30
}

long hook_raw_size()
{
    return 0x9E6F10;                // aA08x_crw, followed sd30
}

void *vid_get_viewport_live_fb()
{
/*
0x5364: 0x105f2c4c: 1st regular buffer
0x5368: 0x1067262c: 2nd regular buffer
0x536c: 0x106f200c: 3rd regular buffer
0x5370: 0x1055ae4c: used when half-shooting, otherwise one of the play mode buffers
0x5374: 0x107719ec: 1st HD movie buffer (1024x768, Y411) OR the "MF point zoom" buffers (triple, 360x120)
0x5378: 0x108919ec: 2nd
*/
       void **fb=(void **)0x5364; //@FF8AB03C
       unsigned char buff = *((unsigned char*)0x537c); //@FF8AB010
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
   return (void*)0x103C79A0;        // seems to be the same as a620 and sd30
}

void *vid_get_viewport_fb()
{
    return (void*) 0x105F2C4C;  //s80
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x72fdc); //s80
}

int vid_get_viewport_width_proper() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 720; //no tv-out
    }
    // return hard coded width since mode doesn't update at the same time as GetVRAMHPixelsSize
    if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        return 360;
    }
    return *(int*)0x36630; // hopefully
}

int vid_get_viewport_height_proper() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 240; //no tv-out
    }
    // return hard coded width since mode doesn't update at the same time as GetVRAMHPixelsSize
    if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        return 120; 
    }
    return *(int*)0x36634; // hopefully
}

char *camera_jpeg_count_str()
{
    return (char*)0x81c70;
}

void *vid_get_bitmap_active_palette() {
    return (void *)0x72cf8; // GetPaletteFromPhysicalScreen
}

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)0x6adc); // @FF92A7D0 DisplayPhysicalScreenWithYUVPalette
}

volatile char* bitmap_buffer[2] = { (char*)0x103c79a0,  (char*)(0x103c79a0 + 0x15180) };


extern void _orig_MoveFocusLensToDistance(short *dist);

void my_MoveFocusLensToDistance(short *dist)
{
/*
    Any use of the original MoveFocusLensToDistance fails with an assert due to a "speed limit" check.
    However, with disabled check, the use of MoveFocusLensToDistance seems to cause 
    focus miscalibration (when used in AF and MF), which only goes away with power cycling...
*/
    int shmode;
    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &shmode, 4);
    if ((shmode == 19) && (movie_status != 4)) return; // only allow during recording when in movie mode
    int speedlimitflag = *(int*)0xb23c;
    *(int*)0xb23c = 0;
    _orig_MoveFocusLensToDistance(dist);
    *(int*)0xb23c = speedlimitflag;
}

extern void _orig_MakeAFScan(void);

void my_MakeAFScan(int *a, int b)
{
    _orig_MakeAFScan();
// wbinteg suspend -> crashes in BrtMsrTask instead
// +brtmsr -> locks up, crashes after 1 minute timeout
/*    static int handle_wbinteg = 0, handle_brtmsr = 0;

    if (handle_wbinteg == 0) { handle_wbinteg = _taskNameToId("tWBIntegTa"); }
    if (handle_brtmsr == 0) { handle_brtmsr = _taskNameToId("tBrtMsrTas"); }
    if (handle_wbinteg && handle_brtmsr)
    {
        debug_led(1);
        _taskSuspend(handle_wbinteg);
        _taskSuspend(handle_brtmsr);
        _orig_MakeAFScan();
        while (zoom_busy || focus_busy) _SleepTask(10);
        _SleepTask(100);
        _taskResume(handle_brtmsr);
        _taskResume(handle_wbinteg);
        debug_led(0);
    }*/
}
