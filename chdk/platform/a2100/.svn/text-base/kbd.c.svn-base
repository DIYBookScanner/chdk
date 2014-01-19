/*
###########################################################
###########################################################
#############[ FINISHED ] #################################
###########################################################
###########################################################
*/


#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"

// changed for A2100IS
#define LED_PWR 0xC0220014      // A2100IS Green - power led 
#define LED_DP 0xC0220018		// A2100IS Blue - Direct Print led 
#define LED_AF 0xC022000C		// A2100IS Red - AutoFocus led 
#define DELAY 5000000

/* 
// #define KEYS_MASK0 (0x00000000)
// #define KEYS_MASK1 (0x11111111)
// #define KEYS_MASK2 (0x00000001) 

// PS2_orig: 0x7f1424eb
// PS2_mod:  0x  1404eb
// MSK: 0x07000000
// DFF: 0x7f002000


// originally:
// PS1: 0x3000{1,9,d}882
// PS2: 0x7f{1,0}424eb
// PS3: 0x224f3e

//aftermod:
// #define KEYS_MASK1 (0x07000000)
// #define KEYS_MASK2 (0x00000F48) 
// PS1: 0x30001882
// PS2: 0x{_,1}404eb
// PS3: 0x20400c

// on PWR_BTN press PS3: 	0x20404c
// on SHOOT HALF press PS3:	0x204008
// on SHOOT FULL press PS3:	0x204000
// on PLAY press PS3: 		0x20408c

// #define KEYS_MASK0 (0x00000003)
// #define KEYS_MASK1 (0x000FFE18)
// #define KEYS_MASK2 (0x00000000) 


// #define KEYS_MASK0 (0x00000000)
// #define KEYS_MASK1 (0x7000000)
// #define KEYS_MASK2 (0xF48) 



orig:
PS1: 0x30001882
PS2: 0x7f0424eb
PS3: 0x224f3e
							 0x7f0424eb
Disp btn pressed:		PS2: 0x7b0424eb
Menu btn pressed:		PS2: 0x7d0424eb
DP btn   pressed:		PS2: 0x770424eb
FUNC set pressed:		PS2: 0x7e0424eb

// with commented functions:
PS1: 0x20000102
PS2: 0x7f0025a3
PS3: 0x224f3e

// with custom reader:
PS1: 0x30001882
PS2: 0x1404eb
PS3: 0x22400c

PS2df: 0x7EF02000
PS3df:	  f32	

  1000000000000000000000000
 10000000000000000000000000
100000000000000000000000000
111000000000000000000000000

KEY_MASK1=7000000
KEY_MASK2=F3C
       10000
      100000
   100000000
  1000000000
 10000000000
100000000000
        1100
        1000
         100 
111100111100 = F3C
*/

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;


long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static long alt_mode_key_mask = 0x08000000;	// Key Print on A2100

extern void _GetKbdState(long*);
extern void usb_remote_key( void ) ;



#define SD_READONLY_FLAG    0x00020000 // Found @0xffe7172c, levent 0x90a
#define SD_READONLY_IDX     2
#define USB_MASK            0x00040000 // Found @0xffe71738, levent 0x902
#define USB_IDX             2

extern void usb_remote_key( void ) ;
int get_usb_bit() {
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}



#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x1F000000)
#define KEYS_MASK2 (0xF3C) 
/*
PS2: 0xFF1424EB

On "Smile" PS2: 0xEF1424EB
on DP		PS2:0xF71424EB
@0xffe71624, levent 0x08 0x1010238, 8, 1,


PS3 normal:	  0x204f3f
PS3 on PLAY	: 0x204fbf



  { 1, KEY_PRINT         ,0x08000000 }, // Found manually
/*/
static KeyMap keymap[] = {
   { 1, KEY_SET             ,0x01000000 }, // Found @0xffe71624, levent 0x08 0x1010238, 8, 1,
   { 1, KEY_MENU            ,0x02000000 }, // Found @0xffe71630, levent 0x09
   { 1, KEY_DISPLAY         ,0x04000000 }, // Found @0xffe7163c, levent 0x0a 0x101023A, 0xA, 1
   { 1, KEY_PRINT           ,0x08000000 }, // Found manually
   { 1, KEY_FACE            ,0x10000000 }, // Found manually
   { 2, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffe716b4, levent 0x02
   { 2, KEY_ZOOM_OUT        ,0x00000020 }, // Found @0xffe716c0, levent 0x03 0x1010245, 3, 1
   { 2, KEY_UP              ,0x00000100 }, // Found @0xffe716e4, levent 0x04 0x1010248, 4, 1,
   { 2, KEY_DOWN            ,0x00000200 }, // Found @0xffe716f0, levent 0x05 0x1010249, 5, 1
   { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xffe716fc, levent 0x07
   { 2, KEY_LEFT            ,0x00000800 }, // Found @0xffe71708, levent 0x06
   { 2, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xffe716a8, levent 0x01
   { 2, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xffe716a8, levent 0x01
   { 2, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xffe7169c, levent 0x00
   { 0, 0, 0 }
};

long __attribute__((naked)) wrap_kbd_p1_f() ;

static void __attribute__((noinline)) mykbd_task_proceed() {
int counter;
	while (physw_run){
		_SleepTask(10) ;  //	*((int*)(0x1c30+0x14)));
/*
		// asm volatile (
		// "LDR R5, =0xC0220018\n"
		// "MOV R6, #0x46\n"
		// "STR R6,[R5]\n"
		// );
		// counter = 2000000; while (counter--) { asm("nop\n nop\n"); };
		// asm volatile (
		// "LDR R5, =0xC0220018\n"
		// "MOV R6, #0x44\n"
		// "STR R6,[R5]\n"
		// );
		// counter = 2000000; while (counter--) { asm("nop\n nop\n"); };
*/
		
		 if (wrap_kbd_p1_f() == 1){ // autorepeat ?
			_kbd_p2_f();
		 }
	}
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task() {
// volatile long *p1 = (void*)LED_PWR;
// volatile long *p2 = (void*)LED_DP;
// int counter;	
// // DEBUG: blink led
// counter = DELAY; *p1 = 0x46;*p2 = 0x46;  while (counter--) { asm("nop\n nop\n"); };
// counter = DELAY; *p1 = 0x44;*p2 = 0x44;  while (counter--) { asm("nop\n nop\n"); }; 


     mykbd_task_proceed();

    _ExitTask();
}

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
	asm volatile(
		"STMFD   SP!, {R1-R5,LR}\n"
		"MOV     R4, #0\n"
	//	"BL      _kbd_read_keys \n"
		"BL		my_kbd_read_keys\n" // replaced temporary
		"B       _kbd_p1_f_cont\n"
	);
	return 0; // shut up the compiler
}

volatile int jogdial_stopped=0;

void kbd_fetch_data(long *dst){
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;// | 0x7EF02000;
    dst[2] = *mmio2;// | 0xf32;
//  dst[2] = *mmio2;
}

void my_kbd_read_keys() {
	
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	
	// Get the state of the buttons on the top of the G10. Like On/off, shoot, zoom, etc.
	// but none of the backside buttons, like cursor, menu, display,etc..
	   
		_kbd_pwr_on();  // i.e. kbd_pwr_on	ROM:FFC11A28                 BL      _sub_FFC30B94__PhySwGpio.c__0 ; LOCATION: PhySwGpio.c:0
	
	_GetKbdState(kbd_new_state); //empty without it
	

	/* Get the rest of the buttons */
	// NSTUB(kbd_read_keys                           ,0xffc11a0c) //109
	// NSTUB(kbd_read_keys_r2                        ,0xffc304dc) //109
	_kbd_read_keys_r2(kbd_new_state); // without this PS3 is almost empty: PS3: 0x400c

	//kbd_new_state[0] |=0x00008000;  /// disable the battery door switch
		
	if (kbd_process() == 0){

		// leave it alone... pass key strokes to the camera
         
		  physw_status[0] = kbd_new_state[0];
          physw_status[1] = kbd_new_state[1];
          physw_status[2] = kbd_new_state[2];
        
	//	 jogdial_stopped=0;

	} else {
		// override keys .. don't let them get to the camera or override them as on to trick the camera
		
		physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);

		// if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run)
		// {
			// jogdial_stopped=1;
			// get_jogdial_direction();
		// }
		// else if (jogdial_stopped && camera_info.state.state_kbd_script_run) jogdial_stopped=0;
	}
	
//	_kbd_pwr_off();
	usb_remote_key() ;

	if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
	}

}


void kbd_set_alt_mode_key_mask(long key)
{
	int i;
	for (i=0; keymap[i].hackkey; ++i) {
		if (keymap[i].hackkey == key) {
			alt_mode_key_mask = keymap[i].canonkey;
			return;
		}
	}
}


void kbd_key_press(long key)
{
	int i;

	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key)
		{
			kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
			return;
		}
	}
}

void kbd_key_release(long key)
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
			kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
			return;
		}
	}
}

void kbd_key_release_all()
{
	kbd_mod_state[0] |= KEYS_MASK0;
	kbd_mod_state[1] |= KEYS_MASK1;
	kbd_mod_state[2] |= KEYS_MASK2;
}

long kbd_is_key_pressed(long key)
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
			return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
		}
	}
	return 0;
}

long kbd_is_key_clicked(long key)
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
			return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
			       ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
		}
	}
	return 0;
}

long kbd_get_pressed_key()
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0){
			return keymap[i].hackkey;
		}
	}
	return 0;
}

long kbd_get_clicked_key()
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
		    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
			return keymap[i].hackkey;
		}
	}
	return 0;
}


// static int new_jogdial=0, old_jogdial=0;

// int Get_JogDial(void){
 // return (*(int*)0xC0240104)>>16;		// G10 okay
// }

// long get_jogdial_direction(void) {
 // old_jogdial=new_jogdial;
 // new_jogdial=Get_JogDial();
 // if (old_jogdial>new_jogdial) return JOGDIAL_LEFT;
 // else if (old_jogdial<new_jogdial) return JOGDIAL_RIGHT;
 // else return 0;
// }
