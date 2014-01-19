#include "platform.h"

char *hook_raw_image_addr()
{
    return (char*)0x424ad900; // CRAW BUF
}

long hook_raw_size()
{
    return 0x11ca240; // CRAW BUF SIZE
}

void *vid_get_viewport_live_fb()
{
/*
the addresses seem to be the right ones, but ptp liveview is jerky...
*/
    void **fb=(void **)0x479c; //@ff8b443c ixus110 101d
    unsigned char buff = *((unsigned char*)0x45f4); //@ff8b4640 ixus110 101d
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff]; 
    // d10 adds this extra value.  Didn't ever see the value change from zero, may be wrong
    //return fb[buff] + *(int *)(0x1F74 + 0xd4); 
}

void *vid_get_bitmap_fb()       
{
    //return (void*)0x40DAB300; //  after DispCon_ShowBlackChart??
    return (void*)0x403f1000;
}

void *vid_get_viewport_fb()
{
    return (void *)0x415f3570; // search on VRAM Address
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x2764 + 0x58));  // @ff855004, ff855030
}

char *camera_jpeg_count_str()
{
    return (char *)0x35278; // search on "9999" done
}


// PTP display stuff

/*
void *vid_get_bitmap_active_palette() { // not usable for color replacement (ROM address?)
    return (void *)*(unsigned int*)(0x5068+0x28);  // sub_FF8CE1B4
}
*/
void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x5068+0x14)); //"Add: %p Width : %ld Hight : %ld", sub_FF8CE2F8
}
