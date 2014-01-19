#include "platform.h"

char *hook_raw_image_addr()
{
    return (char*)0x10F06B20; //found at 0xFFD82C10 (100e)
}

void *vid_get_viewport_fb()
{
	 return (void*)0x10659D50; // found at 0xFFE2B904 (100e)
}

long vid_get_viewport_height()
{
    return 240;
}

void *vid_get_bitmap_fb()  //OSD buffer     
{
    return (void*)0x10361000; //found at 0xFFCC2F24 (100e)
}

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

// print led (blue)
#define LED_PR 0xc0220084

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
 return 115;
}
