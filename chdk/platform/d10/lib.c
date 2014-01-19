#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
	_ScreenLock();
    _RefreshPhysicalScreen(1);
}

void shutdown()
{
    volatile long *p = (void*)0xc0220014; // from task_by (not really complete)
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


#define LED_PR 0xc0220134 // red LED, no DP

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

int get_flash_params_count(void){
 return 122; //  sub_FF95A4BC, similar to SD990
}

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
