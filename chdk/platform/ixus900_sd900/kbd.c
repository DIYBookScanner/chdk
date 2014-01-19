#include "lolevel.h"
#include "platform.h"
#include "conf.h"
#include "core.h"
#include "keyboard.h"

typedef struct {
    short grp;
    long hackkey;
    long canonkey;
} KeyMap;

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static KeyMap keymap[];

#define USB_MASK (0x40000)
#define USB_IDX  2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0xc0000000)   // (0xc0800000)
#define KEYS_MASK2 (0x0ffc)

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#ifndef MALLOCD_STACK
    static char kbd_stack[NEW_SS];
#endif

long __attribute__((naked)) wrap_kbd_p1_f();

static void __attribute__((noinline)) mykbd_task_proceed() {
    while(physw_run) {
        _SleepTask(10);
        if(wrap_kbd_p1_f() == 1) {    // Readout key state via camera function
            _kbd_p2_f();
        }
    }
}

void __attribute__((naked,noinline)) mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf) {
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     * function arguments destroyed;
     * function CAN NOT return properly;
     * MUST NOT call or use stack variables before stack
     * is setup properly;
     */

    register int i;
    register long *newstack;

    #ifndef MALLOCD_STACK
        newstack = (void*)kbd_stack;
    #else
        newstack = malloc(NEW_SS);
    #endif

    for(i=0; i<NEW_SS/4; i++)
        newstack[i]=0xdededede;

    asm volatile(
        "MOV     SP, %0\n"
        :: "r"(((char*)newstack)+NEW_SS)
        : "memory"
    );

    //debug_led(1);
    mykbd_task_proceed();
    //debug_led(0);

    // function can be modified to restore SP here...
    _ExitTask();
}

// ROM:FF827F58
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
    asm volatile(
        "STMFD   SP!, {R4-R7,LR}\n"
        "SUB     SP, SP, #0xC\n"
        "BL      _kbd_read_keys\n"   // replacement for kbd_fetch_data()
        "BL      my_kbd_read_keys\n"
        "B       _kbd_p1_f_cont\n"
    );
    return 0;   // shut up the compiler
}

// ToDo: required?
#if CAM_FEATURE_FEATHER
    extern int touch_keys_angle;
    extern int * touch_keys_sema;
    int touch_keys_sema_stored;
#endif

void my_kbd_read_keys() {
    //kbd_prev_state[0] = kbd_new_state[0];   // nothing to override
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    //kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    kbd_new_state[2] = physw_status[2];

    #if CAM_FEATURE_FEATHER
        static int taskFeatherID = 0;
        extern int taskNameToId(char*);
        if (taskFeatherID == 0) {
            taskFeatherID = _taskNameToId("tFeather");
            //printf("taskFeatherID:%x\n", taskFeatherID);
        }
    #endif

    if(kbd_process() == 0) {
        // nothing to override
        #if CAM_FEATURE_FEATHER
            _taskResume(taskFeatherID);   // resume Feather Task
        #endif
    } else {
        // override keys
        //physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
        physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
        physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);

        #if CAM_FEATURE_FEATHER
            _taskSuspend(taskFeatherID);   // suspend Feather Task (disable canon firmware "Touch Icons" display which overdraw CHDK)
            //if (kbd_mod_state != KEY_MASK) {
            //    _taskResume(taskFeatherID);
            //}
        #endif
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
    for(i=0; keymap[i].hackkey; i++) {
        if(keymap[i].hackkey == key) {
            //kbd_mod_state &= ~keymap[i].canonkey;
            kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key) {
    int i;
    for(i=0; keymap[i].hackkey; i++) {
        if(keymap[i].hackkey == key) {
            //kbd_mod_state |= keymap[i].canonkey;
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
    for(i=0; keymap[i].hackkey; i++) {
        if(keymap[i].hackkey == key) {
            return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key) {
    int i;
    for(i=0; keymap[i].hackkey; i++) {
        if(keymap[i].hackkey == key) {
            return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key() {
    int i;
    for(i=0; keymap[i].hackkey; i++) {
        if((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key() {
    int i;
    for(i=0; keymap[i].hackkey; i++) {
        if(((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_use_zoom_as_mf() {
    static long v;
    static long zoom_key_pressed = 0;

    if(kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if(v) {
            kbd_key_release_all();
            kbd_key_press(KEY_RIGHT);
            zoom_key_pressed = KEY_ZOOM_IN;
            return 1;
        }
    } else {
        if(zoom_key_pressed==KEY_ZOOM_IN) {
            kbd_key_release(KEY_RIGHT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    if(kbd_is_key_pressed(KEY_ZOOM_OUT) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if(v) {
            kbd_key_release_all();
            kbd_key_press(KEY_LEFT);
            zoom_key_pressed = KEY_ZOOM_OUT;
            return 1;
        }
    } else {
        if(zoom_key_pressed==KEY_ZOOM_OUT) {
            kbd_key_release(KEY_LEFT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    return 0;
}

// ROM:FF82882C ?
static KeyMap keymap[] = {
    // tiny bug: key order matters. see kbd_get_pressed_key() for example
    {2, KEY_UP            , 0x00000010},
    {2, KEY_DOWN          , 0x00000020},
    {2, KEY_LEFT          , 0x00000080},
    {2, KEY_RIGHT         , 0x00000040},
    {2, KEY_SET           , 0x00000100},
    {1, KEY_SHOOT_FULL    , 0xC0000000},
    {1, KEY_SHOOT_FULL_ONLY, 0x80000000},
    {1, KEY_SHOOT_HALF    , 0x40000000},
    {2, KEY_ZOOM_IN       , 0x00000004},
    {2, KEY_ZOOM_OUT      , 0x00000008},
    {2, KEY_MENU          , 0x00000200},
    {2, KEY_DISPLAY       , 0x00000400},
    {2, KEY_PRINT         , 0x00000800},
    //{2, KEY_DUMMY         , 0x00000800},
    {0, 0, 0}
};
