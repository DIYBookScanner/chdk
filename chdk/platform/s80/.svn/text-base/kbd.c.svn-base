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
static long alt_mode_key_mask = 0x00000000;

#define KEYS_MASK0 (0x0000C000)	// state[0] mask
#define KEYS_MASK1 (0x3C3E0033) // state[1] mask
#define KEYS_MASK2 (0x00000000) // ????

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)
#define SD_READONLY_REG 2
#define USB_MASK (0x20)
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

extern void _platformsub_kbd_fetch_data(long*);
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

void __attribute__((naked,noinline))
mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf)
{
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *	function arguments destroyed;
     *	function CAN NOT return properly;
     *	MUST NOT call or use stack variables before stack
     *	is setup properly;
     *
     */

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


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
    asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "SUB     SP, SP, #0xC\n"
                "BL      my_kbd_read_keys\n"
                "B       _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}

//scrollwheel:
//[0xc0240204] >> 16: 16 bit counter
//[0xc0240404] >> 16: another -"- (reverse?)
//0x11a70, 72, 74, 76: halfwords storing the above counter values
//0x11a70, 0x11a72: [0xc0240404] >> 16
//0x11a74, 0x11a76: [0xc0240204] >> 16
long get_jogdial_direction(void) {
    static int new_jogdial=0, old_jogdial=0;
    
    old_jogdial=new_jogdial;
    new_jogdial=(*(int*)0xC0240404)>>16;
    if (old_jogdial<new_jogdial) return JOGDIAL_LEFT; 
    else if (old_jogdial>new_jogdial) return JOGDIAL_RIGHT;
    else return 0;
}

volatile int jogdial_stopped=0;

void my_kbd_read_keys()
{

    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _platformsub_kbd_fetch_data(kbd_new_state);

    if (kbd_process() == 0){
        // leave it alone...
        physw_status[0] = kbd_new_state[0];
        physw_status[1] = kbd_new_state[1];
        physw_status[2] = kbd_new_state[2];
        physw_status[1] |= alt_mode_key_mask;
        jogdial_stopped=0;
        
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |
                (kbd_mod_state[0] & KEYS_MASK0);
        physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
                (kbd_mod_state[1] & KEYS_MASK1);
        physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |
                (kbd_mod_state[2] & KEYS_MASK2);

        if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run) {
            jogdial_stopped=1;
            get_jogdial_direction();
        }
        else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
            jogdial_stopped=0;

    }

    _kbd_read_keys_r2(physw_status);

    usb_remote_key() ;

    if (conf.remote_enable) {
        physw_status[SD_READONLY_REG] = physw_status[SD_READONLY_REG] & ~(SD_READONLY_FLAG | USB_MASK);
    }
    else
        physw_status[SD_READONLY_REG] = physw_status[SD_READONLY_REG] & ~SD_READONLY_FLAG;
}

/****************/

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
 // kbd_mod_state[2] |= KEYS_MASK2;
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
    static long v;
    static long zoom_key_pressed = 0;

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && kbd_is_key_pressed(KEY_MF) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_MF);
            kbd_key_press(KEY_UP);
            zoom_key_pressed = KEY_ZOOM_IN;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_IN) {
            kbd_key_release(KEY_UP);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    if (kbd_is_key_pressed(KEY_ZOOM_OUT) && kbd_is_key_pressed(KEY_MF) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_MF);
            kbd_key_press(KEY_DOWN);
            zoom_key_pressed = KEY_ZOOM_OUT;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_OUT) {
            kbd_key_release(KEY_DOWN);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    return 0;
}
static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
        { 1, KEY_UP		, 0x00040000 },
        { 1, KEY_DOWN		, 0x00100000 },
        { 1, KEY_LEFT		, 0x00020000 },
        { 1, KEY_RIGHT		, 0x00080000 }, // ok
        { 1, KEY_SET		, 0x00200000 }, // ok
        { 0, KEY_SHOOT_FULL	, 0x0000C000 }, // org
        { 0, KEY_SHOOT_FULL_ONLY	, 0x00008000 }, //
        { 0, KEY_SHOOT_HALF	, 0x00004000 }, // ?? org
        { 1, KEY_ZOOM_IN	, 0x00000001 }, // ok
        { 1, KEY_ZOOM_OUT	, 0x00000002 }, // ok
        { 1, KEY_MENU		, 0x08000000 }, // ok
        { 1, KEY_DISPLAY	, 0x10000000 }, // ok
        { 1, KEY_PRINT		, 0x00000010 }, // ok
        { 1, KEY_ERASE		, 0x20000000 }, // ok
        { 1, KEY_EXPO_CORR	, 0x04000000 }, // ok
        { 1, KEY_ISO		, 0x00040000 }, // up
        { 1, KEY_FLASH		, 0x00080000 }, // right
        { 1, KEY_MF		, 0x00100000 }, // down
        { 1, KEY_MACRO		, 0x00020000 }, // left
        { 1, KEY_MICROPHONE     , 0x00000020 }, //
        { 0, 0, 0 }
};

