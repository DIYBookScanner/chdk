#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;


long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static long alt_mode_key_mask = 0x00000200;	// default to G10 Print Key

extern void _GetKbdState(long*);
extern void usb_remote_key( void ) ;

#define LED_ISO  (void*) 0xC02200D0 // G10 ISO select dial LED
#define LED_DP   (void*) 0xC02200D4	// G10 direct print button LED
#define LED_ECL  (void*) 0xC02200D8 // G10 exposure compensation dial LED
#define LED_PWR  (void*) 0xC02200DC	// G10 power LED

#define SD_READONLY_FLAG 	0x00020000 		// Found @0xffb0f940, levent 0x90a
#define SD_READONLY_IDX     2         
#define USB_MASK            0x00040000	// Found @0xffb0f94c, levent 0x902
#define USB_IDX             2    

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

#define KEYS_MASK0 (0x00000003)
#define KEYS_MASK1 (0x000FFE18)
#define KEYS_MASK2 (0x00000000) 

static KeyMap keymap[] = {
    { 0, KEY_SHOOT_FULL  ,0x00000003 }, // Found @0xffb0f7c0, levent 0x01
    { 0, KEY_SHOOT_FULL_ONLY, 0x00000002 },	 // http://chdk.setepontos.com/index.php?topic=1444.msg70223#msg70223
    { 0, KEY_SHOOT_HALF  ,0x00000001 }, // Found @0xffb0f7b4, levent 0x00
	
    { 1, KEY_ZOOM_OUT    ,0x00000008 }, // Found @0xffb0f82c, levent 0x03
    { 1, KEY_ZOOM_IN     ,0x00000010 }, // Found @0xffb0f838, levent 0x02
	{ 1, KEY_PRINT		, 0x00000200 },	//
    { 1, KEY_LEFT        ,0x00000400 }, // Found @0xffb0f880, levent 0x06
    { 1, KEY_SET         ,0x00000800 }, // Found @0xffb0f88c, levent 0x08
    { 1, KEY_RIGHT       ,0x00001000 }, // Found @0xffb0f898, levent 0x07
    { 1, KEY_DOWN        ,0x00002000 }, // Found @0xffb0f8a4, levent 0x05
    { 1, KEY_UP          ,0x00004000 }, // Found @0xffb0f8b0, levent 0x04
	{ 1, KEY_METERING	, 0x00008000 },	//
	{ 1, KEY_ERASE		, 0x00010000 },	//
    { 1, KEY_DISPLAY     ,0x00020000 }, // Found @0xffb0f8d4, levent 0x0a
    { 1, KEY_MENU        ,0x00040000 }, // Found @0xffb0f8e0, levent 0x09
	{ 1, KEY_AE_LOCK	, 0x00080000 }, //

/*	
	{ 0, KEY_PWR_PLAYBACK	, 0x80000000 },	// inverted
	{ 0, KEY_PWR_SHOOT		, 0x40000000 }, // inverted
	{ 0, KEY_BATTERY_DOOR	, 0x00008000 }, // inverted
*/	
    { 0, 0, 0 }
};

long __attribute__((naked)) wrap_kbd_p1_f() ;

static void __attribute__((noinline)) mykbd_task_proceed()
{
	while (physw_run){
		_SleepTask(10) ;  //	*((int*)(0x1c30+0x14)));


		if (wrap_kbd_p1_f() == 1){ // autorepeat ?
			_kbd_p2_f();
		}
	}
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline))
mykbd_task()
{
    mykbd_task_proceed();

    _ExitTask();
}

long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
	asm volatile(
		"STMFD   SP!, {R1-R5,LR}\n"
		"MOV     R4, #0\n"
		//"BL      _kbd_read_keys \n"
		"BL		my_kbd_read_keys\n"
		"B       _kbd_p1_f_cont\n"
	);
	return 0; // shut up the compiler
}

volatile int jogdial_stopped=0;

void my_kbd_read_keys()
{

	
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];
	
	// Get the state of the buttons on the top of the G10. Like On/off, shoot, zoom, etc.
	// but none of the backside buttons, like cursor, menu, display,etc..
	   
	_GetKbdState(kbd_new_state);
	
	/* Get the rest of the buttons */
	
	_kbd_read_keys_r2(kbd_new_state);

	kbd_new_state[0] |=0x00008000;  /// disable the battery door switch
	
	if (kbd_process() == 0){

		// leave it alone... pass key strokes to the camera
         
		  physw_status[0] = kbd_new_state[0];
          physw_status[1] = kbd_new_state[1];
          physw_status[2] = kbd_new_state[2];
        
		 jogdial_stopped=0;

	} else {
		// override keys .. don't let them get to the camera or override them as on to trick the camera
		
		physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);

		if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run)
		{
			jogdial_stopped=1;
			get_jogdial_direction();
		}
		else if (jogdial_stopped && camera_info.state.state_kbd_script_run) jogdial_stopped=0;
	}
	
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

static int new_jogdial=0, old_jogdial=0;

int Get_JogDial(void){
 return (*(int*)0xC0240104)>>16;		// G10 okay
}

long get_jogdial_direction(void) {
 old_jogdial=new_jogdial;
 new_jogdial=Get_JogDial();
 if (old_jogdial<new_jogdial) return JOGDIAL_LEFT;
 else if (old_jogdial>new_jogdial) return JOGDIAL_RIGHT;
 else return 0;
}
