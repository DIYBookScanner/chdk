#include "platform.h"

char *hook_raw_image_addr() 
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FF45507C used in sub_FF0DDA6C
	// [0x3188 + 0xC] --> defines which buffer is active

    if (*((int*)(0x3188 + 0xC)) != 0)       //loc_ff07154c: 0x3188 (@FF071550 ) + 0xC (@FF07157C)
        return (char*) 0x4ADB54A0;          
    else
        return (char*) 0x44000000;          
}

char *hook_alt_raw_image_addr() {
    if (*((int*)(0x3188 + 0xC)) == 0)
        return (char*) 0x4ADB54A0;
    else
        return (char*) 0x44000000;
}

long hook_raw_size() {
    return 0x1247A60;                       //asm1989 @FF3E64AC   Finsing confirmed Diferent than the sx230 !! was 123EAF0
}

void *vid_get_viewport_fb_d() {
    return (void*)(*(int*)(0x2ec0+0x54));   //Found @0xff062d0c & 0xff062d44
}

char *camera_jpeg_count_str() {
     return (void*)0xDD3B4;                 //asm1989 @FF26FE14  CONFIRMED finsig serch for "9999"  sx230: 0xCE488
}

char *camera_jpeg_current_filename() {
     return (void*)0xD922C;                 //RAM dump, @ FF22FADC serach for  "%03d-%04d"  sx230:0xCA818
}

#ifdef CAM_HAS_GPS
char * camera_jpeg_current_latitude() {     //RAM dump
    return (void*)0xD92A4;
}

char * camera_jpeg_current_longitude() {    //RAM dump
    return (void*)0xD92C0;
}

char * camera_jpeg_current_height() {       //RAM dump
    return (void*)0xD909C;
}
#endif