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


#define DELAY_TIMEOUT 10000

#define KEYS_MASK0 (0x00020000)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x2E0003f0)
#define KEYS_INV2  (0x2E000000) //higher  1=pressed (MENU,UP,DOWN,LEFT) =>INTRODUCED
/*
the 4 button states residing in the upper half of physw_status[2] seem to be inverted
to handle these correctly, their value needs to be inverted:
- when reading from physw_status[2] to the state variables
- when writing to physw_status[2] from the state variables
KEYS_INV2 should be used for that
SD_READONLY_FLAG and USB_MASK are not affected by this
 
when idle, physw_status[2] looks like: ""
                         KEYS_MASK2 is "00101110000000000000001111110000"
*/

static long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
extern void _platformsub_kbd_fetch_data(long*);

//Original #define SD_READONLY_FLAG (0x40000)
//Original #define USB_MASK (0x80000)
//Original #define USB_REG 2
#define SD_READONLY_FLAG    0x00020000 // Found @0xffe9db68, levent 0x90a
#define SD_READONLY_IDX     2
#define USB_MASK            0x01000000 // Found @0xffe9db88, levent 0x902
#define USB_IDX             2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
static KeyMap keymap[] = {
    { 0, KEY_PRINT           ,0x00020000 }, // Playback => ALT Mode
    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffe9db40, levent 0x03
    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffe9db48, levent 0x02
    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe9db50, levent 0x08
    { 2, KEY_RIGHT           ,0x00000200 }, // Found @0xffe9db58, levent 0x07
    { 2, KEY_UP              ,0x02000000 }, // Found @0xffe9db90, levent 0x04
    { 2, KEY_DOWN            ,0x04000000 }, // Found @0xffe9db98, levent 0x05
    { 2, KEY_LEFT            ,0x08000000 }, // Found @0xffe9dba0, levent 0x06
    { 2, KEY_MENU            ,0x20000000 }, // Found @0xffe9dbb0, levent 0x09
    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe9db38, levent 0x01
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe9db38, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe9db30, levent 0x00
//    { 2, KEY_MODE            ,0x10000000 }, // OSD
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
			"STMFD   SP!, {R1-R7,LR}\n"	// anterior "STMFD   SP!, {R1-R7,LR}\n"
			"MOV     R5, #0\n" // anterior "MOV     R4, #0\n"
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

	if (kbd_process() == 0){//core\kbd.c =>pode simular outras teclas (kbd_key_press/release)
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
