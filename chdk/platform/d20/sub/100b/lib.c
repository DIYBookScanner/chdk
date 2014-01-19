#include "platform.h"

/*
// camera has two raw buffers, see platform lib.c
char *hook_raw_image_addr()     {return (char*) 0x4138AE00;}   //Found @0xff363310 d20 100b Search on JPEG BUFF
*/

char *camera_jpeg_current_filename() {
     return (void*)0xBD06C;                 //0xFF1E2E88 search for  "%03d-%04d"
}

#ifdef CAM_HAS_GPS
char * camera_jpeg_current_latitude() {     //it is camera_jpeg_current_filename + 0x78
    return (void*)0xBD0E4;
}

char * camera_jpeg_current_longitude() {    //it is camera_jpeg_current_filename + 0x94
    return (void*)0xBD100;
}

char * camera_jpeg_current_height() {       //it is camera_jpeg_current_filename + 0x190
    return (void*)0xBD1FC;
}
#endif


//Found by finsig d20 100b
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2c80+0x54)); } // Found @0xff05f434 & 0xff05f46c
char *camera_jpeg_count_str()    { return (char*)0x000c0a08; }             // Found @0xff21bf70
long hook_raw_size()             { return 0x0123eaf0; }                    // Found @0xff363368


