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

static KeyMap keymap[];

// no keys in 0 or 1
#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x77FE)

#define SD_READONLY_FLAG    0x02000000 // Found @0xff4fbaf0, levent 0x20a
#define SD_READONLY_IDX     2
#define USB_MASK            0x10000000 // Found @0xff4fbb00, levent 0x202
#define USB_IDX             2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}

void kbd_fetch_data(long*);

long __attribute__((naked)) wrap_kbd_p1_f() ;

static void __attribute__((noinline)) mykbd_task_proceed()
{
	while (physw_run){ 
		_SleepTask(physw_sleep_delay); // =0x1DEC + 8 @FF030F14

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
                "STMFD   SP!, {R1-R7,LR}\n"
                "MOV     R5, #0\n"
                "BL      my_kbd_read_keys\n"
               	"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}


void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    //_kbd_pwr_on();

    kbd_fetch_data(kbd_new_state);

    if (kbd_process() == 0){
        // leave it alone...
        physw_status[0] = kbd_new_state[0];
        physw_status[1] = kbd_new_state[1];
        physw_status[2] = kbd_new_state[2];
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |
        (kbd_mod_state[0] & KEYS_MASK0);

        physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
        (kbd_mod_state[1] & KEYS_MASK1);

        physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |
        (kbd_mod_state[2] & KEYS_MASK2);
    }
    _kbd_read_keys_r2(physw_status);


	usb_remote_key() ;

	if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
	}
	
    //_kbd_pwr_off();
}

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
	    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

// TODO probably want enable this
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

// from sig finder
static KeyMap keymap[] = {
//    { 2, KEY_POWER           ,0x00000001 }, // Found @0xff4fba60, levent 0x100
    { 2, KEY_PLAYBACK        ,0x00000002 }, // Found @0xff4fba68, levent 0x101
//    { 2, KEY_PRINT           ,0x00000002 }, // default alt
    { 2, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xff4fba78, levent 0x01
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xff4fba78, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xff4fba70, levent 0x00
    { 2, KEY_ZOOM_IN         ,0x00000010 },
    { 2, KEY_ZOOM_OUT        ,0x00000040 },
    { 2, KEY_UP              ,0x00000080 },
    { 2, KEY_DOWN            ,0x00000100 },
    { 2, KEY_RIGHT           ,0x00000200 },
    { 2, KEY_LEFT            ,0x00000400 }, 
    { 2, KEY_SET             ,0x00001000 },
    { 2, KEY_MENU            ,0x00002000 },
    { 2, KEY_VIDEO           ,0x00004000 },
    { 0, 0, 0 }
};
// NOTE auto/manual switch is 0x8000 in word index 2 (auto = on)

void kbd_fetch_data(long *dst)
{
	// FF0907A0 GetKbdState
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
}
