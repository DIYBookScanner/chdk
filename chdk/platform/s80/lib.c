#include "platform.h"
#include "lolevel.h"

void shutdown()
{
    volatile long *p = (void*)0xc02200dc;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x46;		// should this be 0x46 or 0x44?

    while(1);
}


#define LED_PR  0xc0220084
#define LED_AF	0xc022008c

void debug_led(int state)
{
    volatile long *p = (void*)LED_PR;
    //volatile long *p = (void*)LED_AF;

    if (state) {
	p[0]=0x47;
    }
    else {
	p[0]=0x44;
    }
}

void camera_set_led(int led, int state, int bright)
{
/*
0 upper green
1 upper orange (red?)
2 lower orange
4 power green
5 power orange
8 blue (print)
9..11 af
*/
 struct led_control led_c;

 led_c.led_num=led%16;
 led_c.action=state<=1 ? !state : state;
 led_c.brightness=bright;
 led_c.blink_count=255;
 _PostLEDMessage(&led_c);
}
 

int get_flash_params_count(void){
 return 94; // @FF96AD60
}

/*
int Get_JogDial(void){
 return (*(int*)0xC0220304)>>16;
}
*/


void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}

//---------------------------------------------------------

int vid_get_viewport_width() {
    return vid_get_viewport_width_proper()>>1;
}

long vid_get_viewport_height()
{
    return vid_get_viewport_height_proper();
}

int vid_get_palette_type() { return 1; }
int vid_get_palette_size() { return 16*4; }

int vid_get_viewport_fullscreen_height() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && ((m&MODE_SHOOTING_MASK) == MODE_STITCH)) {
        return 240;
    }
    return vid_get_viewport_height_proper();
}

int vid_get_viewport_fullscreen_width() {
    // except for stitch, always full screen
    int m = mode_get();
    if((m&MODE_MASK) != MODE_PLAY && ((m&MODE_SHOOTING_MASK) == MODE_STITCH)) {
        return 720;
    }
    return vid_get_viewport_width_proper();
}

int vid_get_viewport_display_xoffset() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 0;
    } else if((m&MODE_SHOOTING_MASK) == MODE_STITCH) {
        short dir=0;
        short seq=0;
        get_property_case(PROPCASE_STITCH_DIRECTION,&dir,sizeof(dir));
        get_property_case(PROPCASE_STITCH_SEQUENCE,&seq,sizeof(seq));
        // overall stitch window is 3/4 screen width, centered
        // live part is 1/2, so margin is either 1/8th or 3/8th
        if(dir==0) {
            return seq?132:44;
        } else {
            return seq?44:132;
        }
    }
    return 0;
}

int vid_get_viewport_display_yoffset() {
    int m = mode_get();
    if((m&MODE_MASK) == MODE_PLAY) {
        return 0;
    }
    return ((m&MODE_SHOOTING_MASK) == MODE_STITCH)?60:0; // window is 120, centered in 240 screen
}

/*
int switch_mode_usb(int mode) // not working
{
    if ( mode == 0 ) {
        levent_set_play();
    } else if ( mode == 1 ) {
        levent_set_record();
    } else return 0;
    return 1;
}
*/