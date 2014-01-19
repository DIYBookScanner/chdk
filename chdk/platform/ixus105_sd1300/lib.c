#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
/*  NOTE: This was the old method, i think the new one performs better
    extern int enabled_refresh_physical_screen;
    enabled_refresh_physical_screen=1;
    _RefreshPhysicalScreen(1);
*/
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}

void shutdown()
{
    volatile long *p = (void*)0xc022001C;

    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");

    *p = 0x44;

    while(1);
}


#define LED_PR 0xC0220108

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

void camera_set_led(int led, int state, int bright)
{
  static char led_table[7]={0,0,1,1,1,9,9};
 if(led >=4 && led <= 10)
  _LEDDrive(led_table[(led-4)%sizeof(led_table)], state<=1 ? !state : state);
}

long vid_get_viewport_height()
{
   return 240;
}

// Functions for PTP Live View system
// 256 entry palette based on 100b 
// sub_FFCD6110  <- Called for a function with 2 ref to **"Palette Class.
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }

void *vid_get_bitmap_active_buffer()
{   //found @loc_ffcd61b4 ixus105 100b ->Called before *"..<GetBmpVramInfo> Add
    return (void*)(*(int*)(0x4AD0+0x18)); 
}
