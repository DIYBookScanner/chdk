#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
	_ScreenLock();
    _RefreshPhysicalScreen(1);
}

void shutdown()
{
    volatile long *p = (void*)0xc022001C; // from task_by (not really complete)

    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");

    *p = 0x44;

    while(1);
}


#define LED_PR 0xC0220128

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

int get_flash_params_count(void){
 return 120; // ? _sub_FF962AB8__PropertyTableManagerCore_c__6, similar to s5is
}

// based on SX10, values found by experiment
void camera_set_led(int led, int state, int bright) {
 static char led_table[]={0, // green
                          1, // orange, right
						  2, // yellow, left
						  3, // power
						  // 4,5,6,7,
						  8, // blue
						  9 // af
						  };
 if((unsigned)led < sizeof(led_table))
  _LEDDrive(led_table[led], state<=1 ? !state : state);
// _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

// from sx10
void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 1);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 1);  // RotateJogDialLeft
}


void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern char** palette_buffer_ptr;
    return palette_buffer_ptr[active_palette_buffer]+12;
}

void load_chdk_palette()
{
    int i ;
    extern char** palette_buffer_ptr;
    extern int active_palette_buffer;

    if ((active_palette_buffer == 0) || (active_palette_buffer == 1) || (active_palette_buffer == 5) || (active_palette_buffer == 7))
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

            // extern char palette_control;
            // palette_control = 1;
            vid_bitmap_refresh();
        }
    }
}

