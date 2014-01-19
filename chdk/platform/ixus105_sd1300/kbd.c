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

extern void _GetKbdState(long*);

#define KEYS_MASK0 (0x00000700)
#define KEYS_MASK1 (0x38000000)
#define KEYS_MASK2 (0x00005C0B)

#define SD_READONLY_FLAG    0x00020000 // Found @0xffea7b60, levent 0x90a
#define SD_READONLY_IDX     2
#define USB_MASK            0x00040000 // Found @0xffea7b6c, levent 0x902
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
    { 0, KEY_PLAYBACK        ,0x00000100 }, // Found @0xffea7a88, levent 0x601
    { 0, KEY_PRINT           ,0x00000100 }, // ALT menu on PLAYBACK button
    { 0, KEY_POWER           ,0x00000200 }, // Found @0xffea7a94, levent 0x600
    { 0, KEY_MENU            ,0x00000400 }, // Found @0xffea7aa0, levent 0x09
    { 1, KEY_LEFT            ,0x08000000 }, // Found @0xffea7adc, levent 0x06
    { 1, KEY_ZOOM_OUT        ,0x10000000 }, // Found @0xffea7ae8, levent 0x03
    { 1, KEY_ZOOM_IN         ,0x20000000 }, // Found @0xffea7af4, levent 0x02
    { 2, KEY_SET             ,0x00000001 }, // Found @0xffea7b00, levent 0x08
    { 2, KEY_DOWN            ,0x00000002 }, // Found @0xffea7b0c, levent 0x05
    { 2, KEY_DISPLAY         ,0x00000008 }, // Found @0xffea7b18, levent 0x0a
    { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xffea7b24, levent 0x07
    { 2, KEY_UP              ,0x00000800 }, // Found @0xffea7b30, levent 0x04
    { 2, KEY_SHOOT_FULL      ,0x00005000 }, // Found @0xffea7b3c, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00004000 }, // Found @0xffea7b48, levent 0x00
    { 2, KEY_SHOOT_FULL_ONLY ,0x00001000 }, // Found @0xffea7b3c, levent 0x01
    { 0, 0, 0 }
};

long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
	asm volatile(
		"STMFD   SP!, {R1-R5,LR}\n"
		"MOV     R4, #0\n"
		"BL      my_kbd_read_keys\n"
		"B       _kbd_p1_f_cont\n"
	);
	return 0; // shut up the compiler
}

static void __attribute__((noinline)) mykbd_task_proceed()
{
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

void my_kbd_read_keys()
{
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	_GetKbdState(kbd_new_state);

	if (kbd_process() == 0){
        // leave it alone...
        physw_status[0] = kbd_new_state[0];
        physw_status[1] = kbd_new_state[1];
        physw_status[2] = kbd_new_state[2];
	} else {
		// override keys
	 	physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);
	}

	_kbd_read_keys_r2(physw_status);

	usb_remote_key();

	if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
	}

}



/****************/

void kbd_set_alt_mode_key_mask(long key)
{
    // not needed
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

long kbd_use_zoom_as_mf() {
 return 0;
}
