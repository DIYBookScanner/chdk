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

#ifdef CAM_HAS_GPS
extern int Taste_Funktion;
extern int Taste_Taste;
extern int Taste_Druck;
extern int Taste_press;
#endif

#define KEYS_MASK0 (0x000181EF)
#define KEYS_MASK1 (0x00B00000)
#define KEYS_MASK2 (0x00000000)

#define SD_READONLY_FLAG    0x00000800 // Found @0xff4537fc, levent 0x20a
#define SD_READONLY_IDX     2
#define USB_MASK            0x10000000 // Found @0xff45383c, levent 0x202
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
    { 0, KEY_ERASE           ,0x00000001 },
    { 0, KEY_DOWN            ,0x00000002 }, // Found @0xff45373c, levent 0x05
    { 0, KEY_LEFT            ,0x00000004 }, // Found @0xff453744, levent 0x06
    { 0, KEY_MENU            ,0x00000008 }, // Found @0xff45374c, levent 0x09
    { 0, KEY_SET             ,0x00000020 }, // Found @0xff45375c, levent 0x08
    { 0, KEY_UP              ,0x00000040 }, // Found @0xff453764, levent 0x04
    { 0, KEY_RIGHT           ,0x00000080 }, // Found @0xff45376c, levent 0x07
    { 0, KEY_ZOOM_OUT        ,0x00008000 }, // Found @0xff4537ac, levent 0x03
    { 0, KEY_ZOOM_IN         ,0x00010000 }, // Found @0xff4537b4, levent 0x02
    { 0, KEY_DISPLAY         ,0x00000100 }, // VIDEO button is used as DISPLAY button
    { 0, KEY_VIDEO           ,0x00000100 },

    { 1, KEY_PRINT           ,0x00800000 }, // ALT menu on PLAYBACK button
    { 1, KEY_PLAYBACK        ,0x00800000 },
    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xff4537dc, levent 0x01
    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xff4537dc, levent 0x01
    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xff4537d4, levent 0x00

    { 0, 0, 0 }
};

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
	asm volatile(
        "STMFD   SP!, {R1-R7,LR}\n"  
        "MOV     R5, #0\n"					
        "BL      my_kbd_read_keys\n"
        "B       _kbd_p1_f_cont\n"
    );
	
	return 0;
}

static void __attribute__((noinline)) mykbd_task_proceed()
{
	while (physw_run){
		_SleepTask(physw_sleep_delay);

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

// Set to 1 to disable jogdial events from being processed in firmware
volatile int jogdial_stopped=0;
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
extern short* jog_position;
extern short rear_dial_position;

void jogdial_control(int n)
{
    if (jogdial_stopped && !n)
    {
        // If re-enabling jogdial set the task code current & previous positions to the actual
        // dial positions so that the change won't get processed by the firmware
        jog_position[0] = jog_position[2] = rear_dial_position;
    }
    jogdial_stopped = n;
}

void my_kbd_read_keys()
{
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	_GetKbdState(kbd_new_state);
	_kbd_read_keys_r2(kbd_new_state);

#ifdef CAM_HAS_GPS
	if (Taste_Funktion != 0)
	{
		if (Taste_Taste == kbd_get_pressed_key())
		{
			Taste_Druck=1;
			kbd_key_release(Taste_Taste);
			kbd_key_press(0);
			Taste_Funktion=0;
			Taste_Taste=0;
			msleep(1000);
			}
	}
#endif

	if (kbd_process() == 0){
        // leave it alone...
        physw_status[0] = kbd_new_state[0];
        physw_status[1] = kbd_new_state[1];
        physw_status[2] = kbd_new_state[2];
        jogdial_control(0);

	} else {
		// override keys
	 	physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);

		if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run)
		{
			jogdial_control(1);
			get_jogdial_direction();
		}
		else if (jogdial_stopped && camera_info.state.state_kbd_script_run) jogdial_control(0);
	}

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


static short new_jogdial=0, old_jogdial=0;

long get_jogdial_direction(void)
{
    old_jogdial = new_jogdial;
    new_jogdial = rear_dial_position;
    if (old_jogdial < new_jogdial) return JOGDIAL_LEFT;
    else if (old_jogdial > new_jogdial) return JOGDIAL_RIGHT;
    else return 0;
}
