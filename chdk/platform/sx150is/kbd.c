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

static KeyMap keymap[];

volatile int jogdial_stopped=0;


#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x0000F000)
#define KEYS_MASK2 (0x00007F50)

#define SD_READONLY_FLAG    (0x20000) // Found @0xffb90df0, levent 0x20a
#define SD_READONLY_IDX     2

#define USB_MASK              (0x00040000) // Found @0xffb90df8, levent 0x202
#define USB_IDX             2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

extern void _platformsub_kbd_fetch_data(long*);
extern void _GetKbdState(long* buffer);

static KeyMap keymap[] = {
	// Order IS important. kbd_get_pressed_key will walk down this table  
	// and take the first matching mask. Notice that KEY_SHOOT_HALF is  
	// always pressed if KEY_SHOOT_FULL is. --MarcusSt
    { 2, KEY_VIDEO     , 0x00000010 },
    { 2, KEY_PRINT     , 0x00000040 }, // playback
    { 2, KEY_PLAYBACK  , 0x00000040 }, // alias so script can use it TODO not clear if wee need PRINT version
	{ 2, KEY_UP        , 0x00000100 },
	{ 2, KEY_DOWN      , 0x00000200 },
	{ 2, KEY_RIGHT     , 0x00000400 },
	{ 2, KEY_LEFT      , 0x00000800 },
	{ 2, KEY_SET       , 0x00001000 },
	{ 2, KEY_MENU      , 0x00002000 },
	{ 2, KEY_DISPLAY   , 0x00004000 },
	{ 2, KEY_ERASE     , 0x00008000 },
	{ 1, KEY_ZOOM_IN   , 0x00004000 },
	{ 1, KEY_ZOOM_OUT  , 0x00008000 },
	{ 1, KEY_SHOOT_FULL, 0x00003000 },
    { 1, KEY_SHOOT_FULL_ONLY, 0x00002000 },
	{ 1, KEY_SHOOT_HALF, 0x00001000 },
	{ 0, 0, 0 }
};

void kbd_fetch_data(long*);

long __attribute__((naked)) wrap_kbd_p1_f() ;


static void __attribute__((noinline)) mykbd_task_proceed()
{

	/* Initialize our own kbd_new_state[] array with the
	   current physical status.
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


void __attribute__((naked,noinline))
mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf)
{
	
	mykbd_task_proceed();
    /* function can be modified to restore SP here...
     */
    _ExitTask();

}

long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
	// Modified to reflect sx150 code @FF8345D0
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
	static long i=0;

	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	_GetKbdState(kbd_new_state);

	if (kbd_process() == 0) {
		// leave it alone...
		physw_status[0] = kbd_new_state[0];
		physw_status[1] = kbd_new_state[1];
		physw_status[2] = kbd_new_state[2];
		jogdial_stopped=0;
	}
	else {
		// override keys
		physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);
		if (!jogdial_stopped && !camera_info.state.state_kbd_script_run) {
			jogdial_stopped=1;
			get_jogdial_direction();
		}
		else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
			jogdial_stopped=0;
	}

	_kbd_read_keys_r2(physw_status);

	usb_remote_key() ;

	if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
	}

}

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
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


long kbd_use_zoom_as_mf() {
	return 0;
}



int Get_JogDial(void) {
 return (*(int*)0xC0240104)>>16;
}



long get_jogdial_direction(void) {
	static int new_jogdial = 0;
	int old_jogdial = 0;

	old_jogdial = new_jogdial;
	new_jogdial = Get_JogDial();

	if (old_jogdial < new_jogdial)
		return JOGDIAL_LEFT;
	else if (old_jogdial > new_jogdial)
		return JOGDIAL_RIGHT;
	else
		return 0;
}
