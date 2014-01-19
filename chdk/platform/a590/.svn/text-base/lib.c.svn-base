#include "platform.h"

extern void my_debug_led();
void shutdown()
{

    volatile long *p = (void*)0xc02200a0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;
	
	while(1);
}


#define LED_PR 0xc02200C4

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

#define LED_AF 0xc0220080

int get_flash_params_count(void){
 return 114;
}

long vid_get_viewport_height()
{
    return 240;
}

// PTP display stuff
// TODO type may not be correct
int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();

// assumed 720, might be 704 ?
int vid_get_viewport_width_proper() { 
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?720:_GetVRAMHPixelsSize();
}
int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}

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
        return 720;
    }
    return vid_get_viewport_width_proper();
}

