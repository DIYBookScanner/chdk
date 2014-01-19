#include "platform.h"
#include "lolevel.h"

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
	return 119; // Found at ROM:FF972F9C (S5IS 1.01b) => ROM:FF93D3E4
}

void camera_set_led(int led, int state, int bright) { 
        struct led_control led_c; 
        char convert_table[11]={0,1,2,3,0,2,3,1,8,10,10};  // s3 to a710 (and a720) convert table

        //char convert_table[6]={0,1,2,3,8,10};  // Test a720, values 0-5 are valid

        // 0 gr  
        // 1 red 
        // 2 yel 
        // 3 pw  
        // 8 dp  
        // 9 af  

        led_c.led_num=convert_table[led%11]; 
        led_c.action=state<=1 ? !state : state; 
        led_c.brightness=bright; 
        led_c.blink_count=255; 
        _PostLEDMessage(&led_c); 
} 

void vid_bitmap_refresh() //as used in other models
{
        extern int enabled_refresh_physical_screen;
        enabled_refresh_physical_screen=1;
        _RefreshPhysicalScreen(1);
}
