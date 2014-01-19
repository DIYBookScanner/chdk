#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"

/*-----------------------------------------------------------------------------
	kbd.c

	In this file we have to define the key which toggles the <ALT> mode.
	
	e.g. in this file KEY_VIDEO is used to activate/deactivate <ALT> mode.
	line 35: alt_mode_key_mask = 0x00004000
	line 62: { 2, KEY_PRINT		     ,0x00004000 },  //KEY_VIDEO for ALT menu
	
------------------------------------------------------------------------------*/

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static long alt_mode_key_mask = 0x00000400; // KEY_PLAYBACK

extern void _GetKbdState(long*);


#define KEYS_MASK0 (0x00000400|0X00000004)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 0x000047FF

#define NEW_SS (0x2000)

#define SD_READONLY_FLAG (0x00020000)
#define SD_READONLY_REG 2


#define USB_MASK (0x04000000)
#define USB_IDX  2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

static KeyMap keymap[] = {
	/* tiny bug: key order matters. see kbd_get_pressed_key() */

    { 2, KEY_PRINT           ,0x00000400 }, // KEY_PLAYBACK for ALT menu
    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xff3a8018, levent 0x01
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xff3a8018, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xff3a8010, levent 0x00
    { 2, KEY_MENU            ,0x00000001 }, // Found @0xff3a7fd0, levent 0x09
    { 2, KEY_SET             ,0x00000002 }, // Found @0xff3a7fd8, levent 0x08
    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xff3a7fe0, levent 0x02
    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xff3a7fe8, levent 0x03
    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xff3a7ff0, levent 0x06
    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xff3a7ff8, levent 0x07
    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xff3a8000, levent 0x05
	{ 2, KEY_DISPLAY         ,0x00000040 },
    { 2, KEY_UP              ,0x00000080 }, // Found @0xff3a8008, levent 0x04
    { 2, KEY_PLAYBACK        ,0x00000400 }, // Found @0xff3a7ff0, levent 0x101
//    { 2, KEY_POWER           ,0x00000800 }, // Found @0xff3a7ff8, levent 0x100
    { 2, KEY_VIDEO           ,0x00004000 }, // Found @0xff3a8008, levent 0x19
    { 0, 0, 0 }
};


long __attribute__((naked)) wrap_kbd_p1_f() ;

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


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
	asm volatile(
        "STMFD   SP!, {R1-R7,LR}\n"
        "MOV     R5, #0\n"	
		"BL      my_kbd_read_keys\n"

		"B       _kbd_p1_f_cont\n" // address is automatically taken from stubs_entry.S
	);

	 return 0; // shut up the compiler
}

void my_kbd_read_keys()
{
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	_GetKbdState(kbd_new_state);

	/* Get the rest of the buttons */
	
	_kbd_read_keys_r2(kbd_new_state);
	
	kbd_new_state[2] |=0x00008000;  /// disable the battery door switch


	if (kbd_process() == 0) {
		// leave it alone...
		physw_status[0] = kbd_new_state[0];
		physw_status[1] = kbd_new_state[1];
		physw_status[2] = kbd_new_state[2];

		physw_status[0] |= alt_mode_key_mask;  /// disable the ALT mode button

	}
	else {
		// override keys

		physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |(kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |(kbd_mod_state[2] & KEYS_MASK2);
	}
	
	// useful for further debugging: print keypress values on display
		// char osd_buf[64];
        // extern long physw_status[3];
        // sprintf(osd_buf, "1:%8x  ", physw_status[0]);
        // draw_txt_string(8, 10, osd_buf, conf.osd_color);

        // sprintf(osd_buf, "2:%8x  ", physw_status[1]);
        // draw_txt_string(8, 11, osd_buf, conf.osd_color);

        // sprintf(osd_buf, "3:%8x  ", physw_status[2]);
        // draw_txt_string(8, 12, osd_buf, conf.osd_color);
		
		
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

long kbd_use_zoom_as_mf() {
	return 0;
}
