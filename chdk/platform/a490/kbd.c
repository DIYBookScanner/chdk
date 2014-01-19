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


static long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

extern void _platformsub_kbd_fetch_data(long*);

#define KEYS_MASK0 (0x00020000)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x017001f4)
#define KEYS_INV2 (0x01700000)
/*
the 4 button states residing in the upper half of physw_status[2] seem to be inverted
to handle these correctly, their value needs to be inverted:
- when reading from physw_status[2] to the state variables
- when writing to physw_status[2] from the state variables
KEYS_INV2 should be used for that
SD_READONLY_FLAG and USB_MASK are not affected by this

when idle, physw_status[2] looks like: "000001000000000xxxxx000111110100"
                         KEYS_MASK2 is "00000001011100000000000111110100"
*/

#define SD_READONLY_FLAG (0x40000)
#define USB_MASK (0x80000)
#define USB_IDX 2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
    * for example
    */

    //{ 0, KEY_DISPLAY  , 0x00020000 }, // Playback
    { 0, KEY_PRINT      , 0x00020000 }, // Playback

    { 2, KEY_SHOOT_FULL , 0x00000030 }, // 0x00000010 (KEY_SHOOT_HALF) + 0x00000020 (KEY_SHOOT_FULL_ONLY)
    { 2, KEY_SHOOT_FULL_ONLY, 0x00000020 },
    { 2, KEY_SHOOT_HALF , 0x00000010 },
    
    { 2, KEY_UP         , 0x00100000 },
    { 2, KEY_DOWN       , 0x00200000 },
    { 2, KEY_LEFT       , 0x00400000 },
    { 2, KEY_RIGHT      , 0x00000004 },
    { 2, KEY_SET        , 0x00000100 },
    { 2, KEY_ZOOM_IN    , 0x00000080 },
    { 2, KEY_ZOOM_OUT   , 0x00000040 },
    { 2, KEY_MENU       , 0x01000000 },
    { 0, 0, 0 }
};


long __attribute__((naked)) wrap_kbd_p1_f() ;


static void __attribute__((noinline)) mykbd_task_proceed()
{
	/* Initialize our own kbd_new_state[] array with the
	   current physical status. (inspired by the S90 port)
	   */
	kbd_new_state[0] = physw_status[0];
	kbd_new_state[1] = physw_status[1];
	kbd_new_state[2] = physw_status[2] ^ KEYS_INV2;
	while (physw_run){
		_SleepTask(10);
		
		if (wrap_kbd_p1_f() == 1){ // autorepeat ?
			_kbd_p2_f();
		}
	}
}

void __attribute__((naked,noinline)) mykbd_task()
{
	mykbd_task_proceed();
	_ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
	asm volatile(
			"STMFD   SP!, {R1-R5,LR}\n"
			"MOV     R4, #0\n"
			//"BL      _kbd_read_keys\n"       // replaces kbd_fetch_data()
			"BL      my_kbd_read_keys\n"     // +
			"B       _kbd_p1_f_cont\n"       // continue
	);
	
	return 0; // shut up the compiler
}


void my_kbd_read_keys()
{
	// If script are running, replace PRINT button with DISPLAY
	if (camera_info.state.state_kbd_script_run) {
		int i;
		for (i=0; keymap[i].hackkey; i++) {
			if (keymap[i].hackkey == KEY_PRINT) {
				keymap[i].hackkey = KEY_DISPLAY;
				break;
			}
		}
	} else {
		int i;
		for (i=0; keymap[i].hackkey; i++) {
			if (keymap[i].hackkey == KEY_DISPLAY) {
				keymap[i].hackkey = KEY_PRINT;
				break;
			}
		}
	}
	
	kbd_prev_state[0] = kbd_new_state[0];
	//kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];
	
	asm volatile(
        "BL      _kbd_read_keys\n"
	);
	
	//_platformsub_kbd_fetch_data(kbd_new_state);
	kbd_new_state[0] = physw_status[0];
	kbd_new_state[1] = physw_status[1];
	kbd_new_state[2] = physw_status[2] ^ KEYS_INV2;
	
	if (kbd_process() == 0){
		// leave it alone...
	} else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        //physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        physw_status[2] = ((kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2])) ^ KEYS_INV2;
	}
	
	//_kbd_read_keys_r2(physw_status);

	usb_remote_key() ;
	
	if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
	}
}




/****************/

void kbd_key_press(long key)
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
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
		if (kbd_is_key_pressed(keymap[i].hackkey)) {
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


long kbd_use_zoom_as_mf() {
	return 0;
}
