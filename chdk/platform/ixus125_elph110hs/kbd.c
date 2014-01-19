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

static long last_kbd_key = 0;

extern void _GetKbdState(long*);

// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0 (0x00000F4F)     //Logic OR of group 0 Keymap values
#define KEYS_MASK1 (0x00F00000)     //Logic OR of group 1 Keymap values
#define KEYS_MASK2 (0x00000000)     //Logic OR of group 2 Keymap values

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags
#define SD_READONLY_FLAG    0x02000000 // Found @0xff413814, levent 0x20a IXUS125 100e
#define SD_READONLY_IDX     1
#define USB_MASK            0x40000000 // Found @0xff41384c, levent 0x202 IXUS125 100e
#define USB_IDX             2

extern void usb_remote_key( void ) ;

int get_usb_bit()
{
        long usb_physw[3];
        usb_physw[USB_IDX] = 0;
        _kbd_read_keys_r2(usb_physw);
        return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

static KeyMap keymap[] = {
	// Order IS important. kbd_get_pressed_key will walk down this table  
	// and take the first matching mask. Notice that KEY_SHOOT_HALF is  
	// always pressed if KEY_SHOOT_FULL is.
    { 0, KEY_ZOOM_IN         ,0x00000008 }, // Found @0xff4137ac, levent 0x02
    { 0, KEY_ZOOM_OUT        ,0x00000004 }, // Found @0xff4137a4, levent 0x03
    { 0, KEY_SET             ,0x00000002 }, // Found @0xff41379c, levent 0x08
    { 0, KEY_MENU            ,0x00000001 }, // Found @0xff413794, levent 0x09
    { 0, KEY_VIDEO           ,0x00000040 }, // Found @0xff4137bc, levent 0x1a
    { 0, KEY_RIGHT           ,0x00000200 }, // Found @0xff4137cc, levent 0x07
    { 0, KEY_UP              ,0x00000100 }, // Found @0xff4137c4, levent 0x04
    { 0, KEY_LEFT            ,0x00000400 }, // Found @0xff4137d4, levent 0x06    
    { 0, KEY_DOWN            ,0x00000800 }, // Found @0xff4137dc, levent 0x05
    { 1, KEY_PRINT           ,0x00800000 }, // KEY_PLAYBACK as ALT 
    { 1, KEY_PLAYBACK        ,0x00800000 }, // Found @0xff413804, levent 0x101    
    { 1, KEY_POWER           ,0x00400000 }, // Found @0xff4137fc, levent 0x100    
    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xff4137f4, levent 0x01
    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xff4137f4, levent 0x01
    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xff4137ec, levent 0x00
    { 0, 0, 0 }
};

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
	
	//ixus125 100d @0xFF01E89C
	asm volatile(
		"STMFD	SP!, {R1-R7,LR} \n"
		"MOV	R5, #0 \n"
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

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task() {
    mykbd_task_proceed();

// function can be modified to restore SP here...
    _ExitTask();
}

void my_kbd_read_keys() {
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _GetKbdState( kbd_new_state );
    _kbd_read_keys_r2( kbd_new_state);

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

    physw_status[SD_READONLY_IDX] = physw_status[SD_READONLY_IDX] & ~SD_READONLY_FLAG;
    if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~USB_MASK;
    }
}

void kbd_key_press(long key) {
    int i;

    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key) {
   int i;

    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key){
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
        if (keymap[i].hackkey == key){
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
