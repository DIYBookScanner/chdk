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

extern void _GetKbdState(long*);

#define DELAY_TIMEOUT 10000

#define KEYS_MASK0			(0x05000000|0x00800000)
#define KEYS_MASK1			(0x00000001|0x00000002|0x00000003|0x00001000|0x00002000|0x00004000|0x00008000|0x00010000|0x00020000|0x00040000|0x00080000)
#define KEYS_MASK2			(0x00000000)

#define SD_READONLY_FLAG	0x00020000 // Found @0xffb56264 (1.00B), levent 0x90a
#define SD_READONLY_IDX		2

#define USB_MASK			0x04000000 // Found @0xffb5628c (1.00B), levent 0x902
#define USB_IDX				2

extern void usb_remote_key( void ) ;
int get_usb_bit()
{
        long usb_physw[3];
        usb_physw[USB_IDX] = 0;
        _kbd_read_keys_r2(usb_physw);
        return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

static KeyMap keymap[] = {
	
	/* tiny bug: key order matters. see kbd_get_pressed_key() */
    { 0, KEY_PLAYBACK        ,0x01000000 }, // Found @0xffb561dc, levent 0x601	
	{ 0, KEY_MENU            ,0x04000000 }, // Found @0xffb561e4 (1.00B), levent 0x09
	{ 0, KEY_FACE            ,0x00800000 },
	{ 1, KEY_UP              ,0x00001000 }, // Found @0xffb56214 (1.00B), levent 0x04
	{ 1, KEY_RIGHT           ,0x00002000 }, // Found @0xffb5621c (1.00B), levent 0x07
	{ 1, KEY_DOWN            ,0x00004000 }, // Found @0xffb56224 (1.00B), levent 0x05
	{ 1, KEY_LEFT            ,0x00008000 }, // Found @0xffb5622c (1.00B), levent 0x06
	{ 1, KEY_ZOOM_OUT        ,0x00010000 }, // Found @0xffb56234 (1.00B), levent 0x03
	{ 1, KEY_ZOOM_IN         ,0x00020000 }, // Found @0xffb5623c (1.00B), levent 0x02
	{ 1, KEY_SET             ,0x00040000 }, // Found @0xffb56244 (1.00B), levent 0x08
	{ 1, KEY_DISPLAY         ,0x00080000 }, // Found @0xffb5624c (1.00B), levent 0x0a
	{ 1, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb5620c (1.00B), levent 0x01
	{ 1, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb5620c (1.00B), levent 0x01
	{ 1, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb56204 (1.00B), levent 0x00
//    { 0, KEY_POWER           ,0x02000000 }, // Found @0xffb561e4 (1.00D), levent 0x600
	{ 0, 0, 0 }
};

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
	
	//FF8346D4
	asm volatile(
		"STMFD	SP!, {R1-R7,LR} \n"
		"MOV	R5, #0 \n"
		//"BL		_kbd_read_keys \n"
		"BL		my_kbd_read_keys \n"	// pached
		"B		_kbd_p1_f_cont \n"
	);
	
	return 0; // shut up the compiler
}

static void __attribute__((noinline)) mykbd_task_proceed() {
	
	while (physw_run) {
		_SleepTask(physw_sleep_delay);
		
		if (wrap_kbd_p1_f() == 1) {   // autorepeat ?
			_kbd_p2_f();
		}
	}
}

void __attribute__((naked,noinline)) mykbd_task() {
	
	mykbd_task_proceed();

	_ExitTask();
}

// NOP
void kbd_set_alt_mode_key_mask(long key) {
}

void my_kbd_read_keys() {

	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	_GetKbdState(kbd_new_state);
	_kbd_read_keys_r2(kbd_new_state);
	
	if (kbd_process() == 0) {
		// we read keyboard state with _kbd_read_keys()
		physw_status[0] = kbd_new_state[0];
		physw_status[1] = kbd_new_state[1];
		physw_status[2] = kbd_new_state[2];
	} else {
		// override keys
		physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]); 
		physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]); 
		physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);
	}

        usb_remote_key() ;

        if (conf.remote_enable) {
                physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
        } else {
                physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
        }

}


void kbd_key_press(long key) {
	
	int i;
	
	for (i=0;keymap[i].hackkey;i++) {
		if (keymap[i].hackkey == key) {
			kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
			return;
		}
	}
}

void kbd_key_release(long key) {
	
	int i;
	
	for (i=0;keymap[i].hackkey;i++) {
		if (keymap[i].hackkey == key) {
			kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
			return;
		}
	}
}

void kbd_key_release_all() {

	kbd_mod_state[0] |= KEYS_MASK0;
	kbd_mod_state[1] |= KEYS_MASK1;
	kbd_mod_state[2] |= KEYS_MASK2;
}

long kbd_is_key_pressed(long key) {
	
	int i;
	
	for (i=0;keymap[i].hackkey;i++) {
		if (keymap[i].hackkey == key) {
			return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
		}
	}
	return 0;
}

long kbd_is_key_clicked(long key) {
	
	int i;
	
	for (i=0;keymap[i].hackkey;i++) {
		if (keymap[i].hackkey == key) {
			return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
			((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
		}
	}
	return 0;
}

long kbd_get_pressed_key() {
	
	int i;
	
	for (i=0;keymap[i].hackkey;i++) {
		if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) {
			return keymap[i].hackkey;
		}
	}
	return 0;
}

long kbd_get_clicked_key() {
	
	int i;
	
	for (i=0;keymap[i].hackkey;i++) {
		if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
		((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
			return keymap[i].hackkey;
		}
	}
	return 0;
}

#ifdef CAM_USE_ZOOM_FOR_MF
long kbd_use_zoom_as_mf() {

	static long v;
	static long zoom_key_pressed = 0;
	
	if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
		get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
		if (v) {
			kbd_key_release_all();
			kbd_key_press(KEY_RIGHT);
			zoom_key_pressed = KEY_ZOOM_IN;
			return 1;
		}
	} else {
		if (zoom_key_pressed==KEY_ZOOM_IN) {
			kbd_key_release(KEY_RIGHT);
			zoom_key_pressed = 0;
			return 1;
		}
	}
	
	if (kbd_is_key_pressed(KEY_ZOOM_OUT) && (mode_get()&MODE_MASK) == MODE_REC) {
		get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
		if (v) {
			kbd_key_release_all();
			kbd_key_press(KEY_LEFT);
			zoom_key_pressed = KEY_ZOOM_OUT;
			return 1;
		}
	} else {
		if (zoom_key_pressed==KEY_ZOOM_OUT) {
			kbd_key_release(KEY_LEFT);
			zoom_key_pressed = 0;
			return 1;
		}
	}

	return 0;
}
#endif


