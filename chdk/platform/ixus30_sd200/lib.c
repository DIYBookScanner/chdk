#include "platform.h"
#include "lolevel.h"
#include "levent.h"
#define PARAM_FILE_COUNTER      0x2A

extern void _sub_FF821D04(long mem, long *data);
extern long _GetPropertyCase_orig(long opt_id, void *buf, long bufsize);
extern long _SetPropertyCase_orig(long opt_id, void *buf, long bufsize);
extern long _GetParameterData_orig(long id, void *buf, long size);
extern long _SetParameterData_orig(long id, void *buf, long size);
extern void _SetAFBeamBrightness(long val);
extern void _SetAFBeamOff();
extern unsigned long _time_orig(unsigned long *timer);

//looks like there is no strobechargecompletet flag ?!
//do it in my own way. found some code to get the eventflag
//at 0xFF941A14. copied the call there in my own c-code
//looking at sd400 asm showed that flash info is (val>>20)&1
//seems correct here as well..
long IsStrobeChargeCompleted_my(){ //look at ff9417d0
    volatile long *p = (void*)0x675BC; //
    long l;
    _sub_FF821D04(*p, &l); //same
    return (l>>20)&1;
}

static unsigned long bootuptime = 0;

unsigned long time_my(unsigned long *timer) {
/*
the original "time" function doesn't seem to work correctly
chdk's clock display runs at around 1/7 speed with it (the display is only correct right after bootup)
this hack provides a replacement using GetSystemTime (which incements every 1ms, I guess),
but it will be off by a few seconds.
There might be a fault in this chdk port somewhere...
*/
unsigned long timer2; //unsigned long *timer will be NULL when called from chdk
    _GetSystemTime((long*)&timer2);
    if (bootuptime == 0) {
        bootuptime = _time_orig((unsigned long*)0)-(timer2)/1000;
    }
    return bootuptime+(timer2)/1000;
}

//workaround
//strange, on my cam the propcase_shooting (205)
//has always a strange value... is this on every sd300 ?
//(mine was once damaged by water on the circuit board)
//or is it just at a different location ?! fixme


//data handler for propcase_shooting workaround:
//i think this should be done with a semaphore... for now it should work
volatile long shooting_status_=0;

// volatile long shbuf[100];
// volatile long shbufi=0;

void set_shooting_status(long l){
//     if (shbufi<100){
//         if (shbuf[shbufi] != l){
//             shbufi++;
//             shbuf[shbufi] = l;
//         }
//     }
    
    //shooting_status_=l;
    //return;
     switch(l){
         case(0x0): 
             //picture mode: focussing
             shooting_status_=1;
             break;
         case(0x1): 
             //picture mode: charge flash & do snapshot
             shooting_status_=1;
             break;
         case(0x2): 
             //picture mode: maybe stitch assist related
             shooting_status_=0;
             break;
         case(0x3): 
             //picture mode: idle
             shooting_status_=0;
             break;
         case(0x6): 
             //video mode: focus & rec
             shooting_status_=1;
             break;
         case(0x7): 
             //video mode: idle
             shooting_status_=0;
             break;
         case (0xb):
             //idle in play mode ?!
             shooting_status_=0;
             break;
             
         default:
             shooting_status_=0;
             break;
     }
}


void GetPropertyCase_my(long cse, void *ptr, long len){
    if (cse == PROPCASE_SHOOTING){
        if (len==sizeof(long)){
            *(long*)ptr = shooting_status_;
        }else if (len==sizeof(short)){
            *(short*)ptr = shooting_status_;
        }else{
            //??? FIXME
        }
    }else{
        _GetPropertyCase_orig(cse, ptr, len);
    }
}

void SetPropertyCase_my(long cse, void *ptr, long len){
/*
PROPCASE_SV_MARKET, PROPCASE_SV, PROPCASE_DELTA_SV -> lower ISO values cause crash
*/
    if (cse == PROPCASE_SHOOTING){
        //do nothing
    }else{
        _SetPropertyCase_orig(cse, ptr, len);
    }
}

void GetParameterData_my(long param, void *ptr, long len){
    _GetParameterData_orig(param&0xfff, ptr, len); //need to work around chdk's hardcoded 0x4000
}

void SetParameterData_my(long param, void *ptr, long len){
    _SetParameterData_orig(param&0xfff, ptr, len); //need to work around chdk's hardcoded 0x4000
}

void shutdown()
{
    volatile long *p = (void*)0xc022002c;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x46;

    while(1);
}

// typedef unsigned short  color;
// void mydebug(long l){
//     //"ldr r0, =3\nbl mydebug\nLDMFD   SP!, {R0}\n"
//     char buf[100];
//     sprintf(buf,"dbg=%ld",l);
// 
// #define MAKE_COLOR(bg, fg)        ((color)((((char)(bg))<<8)|((char)(fg))))
// 
//     draw_txt_string(2, 2, buf, MAKE_COLOR(0xD4, 10));
//     msleep(100);
// }

void dummy_nop(){
}


#define LED_PR 0xc0220088 //?
#define LED_BRIGHTNESS  200
#define LED_GREEN       4
#define LED_YELLOW      5
#define LED_ORANGE      7
#define LED_BLUE        8
#define LED_AF_BEAM     9
#define LED_TIMER       10

//sd300:
//0xBC24 --> 0x00000000
//0xBC28 --> 0xC02200D8 = green  (pair)
//0xBC2C --> 0xC02200DC = orange (pair)
//0xBC30 --> 0xC02200E0 = yellow
//0xBC34 --> 0xC02200E8 = green power led
//0xBC38 --> 0x00000000
//0xBC3C --> 0x00000000
//0xBC40 --> 0x00000000
//0xBC44 --> 0x00000000
//0xBC48 --> 0xC02200E4 = blue
//0xBC4C --> 0xC02200EC = af beam 
//0xBC50 --> 0x00000000
    
//LED stuff verified as working: 30.07.2008
static void led_on(const int led, const int brightness)
{
    if (led < 4 || led > 10 || led == 6) return;
    //on sd400 the led stuff works like this: 
    //led_addr = led_table + (led * 0x40)
    //
    //if (mem(led_addr) == 0){
    //  mem(led_addr + 4) = 0x46; //=ON
    //}else if (mem(led_addr) == 1){
    //  af_led_sub(led_addr)
    //}
    //
    //ok on sd300 something like ledUniqueOn doesnt seem
    //to exist. so build our own lib:
    
    volatile long *p; 
    switch(led){
        case (LED_GREEN) : p=(void*)0xc02200D8; break;
        case (LED_ORANGE): p=(void*)0xc02200DC; break;
        case (LED_YELLOW): p=(void*)0xc02200E0; break;
        case (LED_BLUE)  : p=(void*)0xc02200E4; break;
        case (LED_AF_BEAM): p=(void*)0xc02200EC; break;
        default: return;
    }
    
    if (led == LED_AF_BEAM){
        _SetAFBeamBrightness(brightness);
    }else{
        *p=0x46;
    }
}

//LED stuff verified as working: 30.07.2008
static void led_off(const int led)
{
   if (led < 4 || led > 10 || led == 6) return;
       
    volatile long *p; 
    switch(led){
        case (LED_GREEN) : p=(void*)0xc02200D8; break;
        case (LED_ORANGE): p=(void*)0xc02200DC; break;
        case (LED_YELLOW): p=(void*)0xc02200E0; break;
        case (LED_BLUE)  : p=(void*)0xc02200E4; break;
        case (LED_AF_BEAM): p=(void*)0xc02200EC; break;
        default: return;
    }
    
    if (led == LED_AF_BEAM){
        _SetAFBeamOff();
    }else{
        *p=0x44;
    }
 
}

void debug_led(int state)
{
    if (state)
        led_on(LED_BLUE, LED_BRIGHTNESS);
    else
        led_off(LED_BLUE);
}

int get_flash_params_count(void){
 return 70;
}

void set_led(int led, int state)
{
    if (state)
        led_on(led, LED_BRIGHTNESS);
    else
        led_off(led);
}
void camera_set_led(int led, int state, int bright)
{
	if (state) {
		if (bright > LED_BRIGHTNESS) bright = LED_BRIGHTNESS;
		if (led == 6) {
	        led_on(4, bright);
		    led_on(5, bright);
		} else
			led_on(led, bright);
	}
    else
		if (led == 6) {
	        led_off(4);
		    led_off(5);
		} else
        led_off(led);
}

/*
int switch_mode_usb(int mode)
{
    if ( mode == 0 ) {
        //extern void _EnterToPlayFromRec();
        //_EnterToPlayFromRec();
        //levent_post_to_ui_by_name("ModeLeverPlay");
        levent_post_to_ui_by_name("ConnectUSBCable");
    } else if ( mode == 1 ) {
        //extern void _EnterToRecFromPlay();
        //_EnterToRecFromPlay(); ineffective
        //levent_post_to_ui_by_name("ModeLeverStillRec"); mode switch but bad state, no USB
        levent_post_to_ui_by_name("DisconnectUSBCable"); crash
    } else return 0;
    return 1;
}
*/
