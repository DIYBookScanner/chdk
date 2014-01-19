#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"


typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;


long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static long alt_mode_key_mask = 0x00000800;

extern void _platformsub_kbd_fetch_data(long*);

     

#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x20000000)
#define KEYS_MASK2 (0x00000FFF)

static KeyMap keymap[] = {
//	{ grp,       hackkey, canonkey  }
    { 1, KEY_PLAYBACK        ,0x20000000 }, // Found @0xffad9820, levent 0x601
    { 2, KEY_PRINT			, 0x00000800 }, // Face Key, default Alt key
    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffad98bc, levent 0x0a
    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffad9850, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffad9844, levent 0x00
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffad9850, levent 0x01
    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffad985c, levent 0x02
    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffad9868, levent 0x03
    { 2, KEY_UP              ,0x00000010 }, // Found @0xffad9874, levent 0x04
    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffad9880, levent 0x05
    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffad988c, levent 0x07
    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffad9898, levent 0x06
    { 2, KEY_SET             ,0x00000100 }, // Found @0xffad98a4, levent 0x08
    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffad98b0, levent 0x09
	{ 0, 0, 0 }
};



#define SD_READONLY_FLAG (0x20000)

#define USB_MASK (0x40000)
#define USB_IDX   2    

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
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



long __attribute__((naked)) wrap_kbd_p1_f() ;


static void __attribute__((noinline)) mykbd_task_proceed()
{
	/* Initialize our own kbd_new_state[] array with the
	   current physical status. (inspired by the S90 port)
	   */
	kbd_new_state[0] = physw_status[0];
	kbd_new_state[1] = physw_status[1];
	kbd_new_state[2] = physw_status[2];
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

	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];
	
	asm volatile(
        "BL      _kbd_read_keys\n"
	);
	
	//_platformsub_kbd_fetch_data(kbd_new_state);
	kbd_new_state[0] = physw_status[0];
	kbd_new_state[1] = physw_status[1];
	kbd_new_state[2] = physw_status[2];
	
	if (kbd_process() == 0){
		physw_status[0] = kbd_new_state[0]; //!!
		physw_status[1] = kbd_new_state[1]; // !!
		physw_status[2] = kbd_new_state[2];  // !! 		
		// leave it alone...
	} else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        physw_status[2] = ((kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]));
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
