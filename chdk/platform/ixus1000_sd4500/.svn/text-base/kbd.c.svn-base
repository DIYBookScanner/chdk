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


#define KEYS_MASK0 (0x00000000)     // physw_status[0]
//#define KEYS_MASK1 (0x000FC005)

//#define KEYS_MASK1 (0x000FCF05)
// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
//#define KEYS_MASK1 (0x000EFC8A)

#define KEYS_MASK1 (0x400 | 0x20000 | 0x8000 | 0x800 | 0x1000 | 0x8 | 0x2 |0x10000 |0x80 | \
                   0x2000 | 0x4000  | 0x80000 | 0x40000 ) // the soft press key codes

#define KEYS_MASK2 (0x00002002 | 0x100)  // physw_status[2]

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)
#define USB_MASK (0x80000)
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

    { 2, KEY_SHOOT_FULL      ,0x00002002 }, // Found @0xffb8d554, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00002000 }, // Found @0xffb8d56c, levent 0x00
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb8d554, levent 0x01
//    { 2, KEY_POWER           ,0x00000008 }, // Found @0xffb8d55c, levent 0x600
    { 2, KEY_PLAYBACK        ,0x00000100 }, // Found @0xffb8d564, levent 0x601

    { 1, KEY_VIDEO           ,0x00000080 }, // Found @0xffb8d4e4, levent 0x12
    { 1, KEY_UP              ,0x00000400 }, // Found @0xffb8d4fc, levent 0x04
    { 1, KEY_RIGHT           ,0x00000800 }, // Found @0xffb8d504, levent 0x07
    { 1, KEY_SET             ,0x00001000 }, // Found @0xffb8d50c, levent 0x08
    { 1, KEY_LEFT            ,0x00008000 }, // Found @0xffb8d524, levent 0x06
    { 1, KEY_MENU            ,0x00010000 }, // Found @0xffb8d52c, levent 0x09
    { 1, KEY_DOWN            ,0x00020000 }, // Found @0xffb8d534, levent 0x05

//   { 1, KEY_UP_SOFT         , 0x00000400 },  //
//   { 1, KEY_DOWN_SOFT        , 0x00000800 },  //
//   { 1, KEY_LEFT_SOFT        , 0x00001000 },  //
//   { 1, KEY_RIGHT_SOFT        , 0x00002000 },  //
//   { 1, KEY_ZOOM_IN_FASTER  , 0x00000008 },  //
//   { 1, KEY_ZOOM_OUT_FASTER , 0x00000002 },  //

    { 1, KEY_ZOOM_IN         , 0x00000008 },  //
    { 1, KEY_ZOOM_OUT        , 0x00000002 },  //
    { 0, 0, 0 }
};


volatile int jogdial_stopped=0;

long __attribute__((naked)) wrap_kbd_p1_f();

static void __attribute__((noinline)) mykbd_task_proceed() {
    while (physw_run) {
        _SleepTask(10);

        if (wrap_kbd_p1_f() == 1) {   // autorepeat ?
            _kbd_p2_f();
        }
    }
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task() {
	register int i;
	register long *newstack;

#ifndef MALLOCD_STACK
	newstack = (void*)kbd_stack;
#else
	newstack = malloc(NEW_SS);
#endif

	for (i=0;i<NEW_SS/4;i++)
		newstack[i]=0xdededede;

	asm volatile (
		"MOV	SP, %0"
		:: "r"(((char*)newstack)+NEW_SS)
		: "memory"
	);



	mykbd_task_proceed();

/* function can be modified to restore SP here...
	 */

	_ExitTask();
}

// ROM:FF83484C, like SX110
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
    asm volatile(
                "STMFD   SP!, {R1-R5,LR}\n"
                "MOV     R4, #0\n"
                "BL      _kbd_read_keys\n"       // replaces kbd_fetch_data()
                "BL      my_kbd_read_keys\n"     // +
                "B       _kbd_p1_f_cont\n"       // continue at ROM:FF834858
    );
    return 0;   // shut up the compiler
}

// like SX110
// int kbd_debug1;
 extern int keyb_stopusb;
void my_kbd_read_keys() {
    //kbd_prev_state[0] = kbd_new_state[0];// nothing to override
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    // The following three lines replace the call to kbd_fetch_data()
    //kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    kbd_new_state[2] = physw_status[2];

    if (kbd_process() == 0) {
        // we read keyboard state with _kbd_read_keys()

        jogdial_stopped=0;
    } else {
        // override keys
    //    physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);
        //physw_status[2] = physw_status[2] & 0x0fff7ffff;
        if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run) {
            jogdial_stopped=1;
            get_jogdial_direction();
        }
        else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
            jogdial_stopped=0;
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
        if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
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

int Get_JogDial(void) {
    return (*(int*)0xC0240104)>>16;     // 0xC0240000 + 0x104
}

static int new_jogdial=0, old_jogdial=0;

long get_jogdial_direction(void) {
    old_jogdial=new_jogdial;
    new_jogdial=Get_JogDial();

    if (old_jogdial<new_jogdial) {
        return JOGDIAL_LEFT;
    } else if (old_jogdial>new_jogdial) {
        return JOGDIAL_RIGHT;
    } else {
        return 0;
    }
}

