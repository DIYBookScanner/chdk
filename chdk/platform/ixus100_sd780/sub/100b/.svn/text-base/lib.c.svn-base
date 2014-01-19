#include "platform.h"

//SD780 - Search for "CRAW BUFF SIZE"
long hook_raw_size()
{
//	RealRom:FF8E6224                 LDR     R1, =0x424AD900
//	RealRom:FF8E6228                 MOV     R2, #0xFF0
//	RealRom:FF8E622C                 LDR     R3, =0xBE8
//	RealRom:FF8E6230                 STMFA   SP, {R1,R2}
//	RealRom:FF8E6234                 ADR     R0, aCrwaddressLxCr ; " CrwAddress %lx, CrwSize H %ld V %ld\r"

	//( 0x11CA240 * 8bits ) / 0xFF0 / 0xBE8 == C bits == 12 bit RAW
//4080x3048
    return 0x11CA240;
}

//VERIFY_SD780 - - Search for "A/%08x.CRW" and find nearby the hex value found for hook_raw_size.
//VERIFY_SD780 - - Above this is the second value...only value????
char *hook_raw_image_addr()
{
	//VERIFY_SD780 ImgProcBuf 0x2968+0x18????
	return (char*)0x424AD900;
// 	return (char*) (*(int*)(0x5520 + 0x18)? 0x42CFB780 : 0x40EBAFA0);  //SD990 has this...
}


//VERIFY_SD780 - - Search for ; LOCATION: LiveImage.c:0 - First LDR
//VERIFY_SD780 - - Find the **fb lower in function.
//VERIFY_SD780 - Original location 0xFF8B02F4
//VERIFY_SD780 - Have doubts...
void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x43EC;
    unsigned char buff = *((unsigned char*)0x4244);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}


//SD780 - - Search for ; LOCATION: BmpDDev.c:138 - First LDR
//SD780 - Search ShowBlackChart FF83DAE4
void *vid_get_bitmap_fb()
{
    return (void*)0x403F1000;
}


//SD780 - - Search for "VRAM Address"
void *vid_get_viewport_fb()
{
    return (void *)0x415F3570;
    //VRAM Size = 0x7E900
}

//VERIFY_SD780 - - Search for "ADR     R1, _sub_.*__SlideEffect.c" RE on.
//VERIFY_SD780 - - Go two jumps up.
//VERIFY_SD780 - - Could be 0x64/0x68/0x54...
void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x26F4 + 0x58));
}

//VERIFY_SD780 - - Check resolutions again.
int vid_get_viewport_width()
{
	return 360; // viewport is still 360, even though live view is 720 (960?)
	//return 720;
}

//VERIFY_SD780 - - Check resolutions again.
long vid_get_viewport_height()
{
    return 240;
}

//SD780 - - Search for "9999"
char *camera_jpeg_count_str()
{
    return (char *)0x33110;
}
// PTP display stuff - untested
int vid_get_palette_type() { return 3; }
int vid_get_palette_size() { return 256*4; } // sub_FF8C99C8, 0x400

void *vid_get_bitmap_active_buffer()
{
    return (void*)(*(int*)(0x4cb8+0x14)); //"Add: %p Width : %ld Hight : %ld", sub_FF8C9A74
}

// not verified
// reyalp note - sub_FF8C9A74 indicates could be 960x270
//int vid_get_viewport_fullscreen_height() { return 240; }

// commented for now, protocol changes needed to handle correctly
#if 0
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:*(int*)0x43bc; // GetVRAMHPixelSize
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?270:*(int*)(0x43bc+4); // GetVRAMVPixelSize
}
#endif

