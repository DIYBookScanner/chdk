#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
	_ScreenLock();
    _RefreshPhysicalScreen(1);
}

void shutdown()
{
    volatile long *p = (void*)0xc022001c; // from task_by (not really complete)
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


#define LED_PR 0xc0220130 // green? LED, other (red?) is 0xc0220134

void debug_led(int state) //mix orange instead of the boring green
{
    volatile long *p=(void*)LED_PR;
    if (state)
        p[0]=p[1]=0x46;
    else
        p[0]=p[1]=0x44;
}

int get_flash_params_count(void){
 return 0x7a;
}

//TODO ixus110
/*
D10 has 3 led values
0/0 - Upper indicator Green
1/1 - Upper indicator Orange
2/9 - AF
10-11 appears to also drive AF, but using the same codepath as non AF leds (no assert on invalid)
note, LEDDrive returns 3 on invalid params otherwise 0
second param 0 = solid on, 1 = off, 2-7 blink patterns
2: continuous ~1 blink/sec
3: continuous fast blink
4: continuous medium blink (2/sec ?) 
5: burst of 3? fast blinks
6: continuous slow blinks
7: if led was off 1 very fast blink. depends on previous state
8: no obvious effect, but returns 0 for AF
>8: If used with AF ASSERT!! LEDDrv.c Line 215, otherwise returns 3
*/
void camera_set_led(int led, int state, int bright) {
 static char led_table[]={0,1,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}


extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();

int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?960:_GetVRAMHPixelsSize();
}

int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}
/*
int vid_get_viewport_fullscreen_height() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_SCN_STITCH) {
        return 240;
    }
    return vid_get_viewport_height_proper();
}
int vid_get_viewport_fullscreen_width() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && (m&MODE_SHOOTING_MASK) == MODE_SCN_STITCH) {
        return 960;
    }
    return vid_get_viewport_width_proper();
}*/

// Physical width of viewport row in bytes, needs to be implemented for wide displays
int vid_get_viewport_byte_width() {
    return 960 * 6 / 4;
} 


long vid_get_viewport_height()
{
    return 240;
}
/*
[0x4610] 0 when wide screen, 1 when 4:3 with side bars
*/
int vid_get_viewport_width() // based on: http://chdk.setepontos.com/index.php?topic=5045.msg94252#msg94252
{
    int modegot = mode_get();
    if( (modegot & MODE_MASK) == MODE_PLAY ) {
        return 480;
    }
    // if widescreen, photo and video modes
    if( ( ( shooting_get_prop(PROPCASE_RESOLUTION) == 8 ) && ( !MODE_IS_VIDEO(modegot) ) ) ||
        ( ( MODE_IS_VIDEO(modegot) ) && ( shooting_get_prop(PROPCASE_VIDEO_RESOLUTION) == 4 ) ) )
        return 480;
    else
        return 360;
} 

int vid_get_viewport_display_xoffset()
{
    int modegot = mode_get();
    if( (modegot & MODE_MASK) == MODE_PLAY ) {
        return 0;
    }
    // if widescreen, photo and video modes
    if( ( ( shooting_get_prop(PROPCASE_RESOLUTION) == 8 ) && ( !MODE_IS_VIDEO(modegot) ) ) ||
        ( ( MODE_IS_VIDEO(modegot) ) && ( shooting_get_prop(PROPCASE_VIDEO_RESOLUTION) == 4 ) ) )
        return 0;
    else
        return 60;
} 

//int vid_get_viewport_height_proper()            { return 240; }
int vid_get_viewport_fullscreen_height()        { return 240; }
int vid_get_viewport_buffer_width_proper()      { return 960; }
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }
int vid_get_aspect_ratio()                      { return 1; } 


void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern int** palette_buffer_ptr;
    return (palette_buffer_ptr[active_palette_buffer]+0x3);
}

#ifdef CAM_LOAD_CUSTOM_COLORS
// Function to load CHDK custom colors into active Canon palette
 
void load_chdk_palette() {

        extern int active_palette_buffer;
        // Only load for the standard record and playback palettes
        if ((active_palette_buffer == 0) || (active_palette_buffer == 2))
        {
                int *pal = (int*)vid_get_bitmap_active_palette();
                if (pal[CHDK_COLOR_BASE+0] != 0x33ADF62)
                {
                
                        pal[CHDK_COLOR_BASE+0]  = 0x33ADF62;  // Red
                        pal[CHDK_COLOR_BASE+1]  = 0x326EA40;  // Dark Red
                        pal[CHDK_COLOR_BASE+2]  = 0x34CD57F;  // Light Red
                        pal[CHDK_COLOR_BASE+3]  = 0x373BFAE;  // Green
                        pal[CHDK_COLOR_BASE+4]  = 0x34BD6CA;  // Dark Green
                        pal[CHDK_COLOR_BASE+5]  = 0x395AB95;  // Light Green
                        pal[CHDK_COLOR_BASE+6]  = 0x34766F0;  // Blue
                        pal[CHDK_COLOR_BASE+7]  = 0x31250F3;  // Dark Blue
                        pal[CHDK_COLOR_BASE+8]  = 0x37F408F;  // Cyan
                        pal[CHDK_COLOR_BASE+9]  = 0x3512D5B;  // Magenta
                        pal[CHDK_COLOR_BASE+10] = 0x3A9A917;  // Yellow
                        pal[CHDK_COLOR_BASE+11] = 0x3819137;  // Dark Yellow
                        pal[CHDK_COLOR_BASE+12] = 0x3DED115;  // Light Yellow

                        extern char palette_control;
                        palette_control = 1;
                        vid_bitmap_refresh();
        }
    }
}
#endif
