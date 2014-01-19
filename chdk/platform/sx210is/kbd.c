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

static long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static KeyMap keymap[];

#define DELAY_TIMEOUT 10000

#define KEYS_MASK0 (0x00802182)     // physw_status[0]
//#define KEYS_MASK1 (0x000FC005)

//#define KEYS_MASK1 (0x000FCF05)
// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK1 (0x000FFC05)
#define KEYS_MASK2 (0x00000000)  // physw_status[2]

#define NEW_SS (0x2000)

#define SD_READONLY_FLAG    0x00020000 // Found @0xffb65924, levent 0x90a
#define SD_READONLY_IDX     2
#define USB_MASK            0x00080000 // Found @0xffb6592c, levent 0x902
#define USB_IDX             2

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif


extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}


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
void my_kbd_read_keys() {
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    //kbd_prev_state[2] = kbd_new_state[2];   // nothing to override

    // The following three lines replace the call to kbd_fetch_data()
    kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    //kbd_new_state[2] = physw_status[2];

  /*static char osd_buf[64];
        sprintf(osd_buf, "1:%8x  ", physw_status[0]);
        draw_txt_string(28, 10, osd_buf, conf.osd_color);

        sprintf(osd_buf, "2:%8x  ", physw_status[1]);
        draw_txt_string(28, 11, osd_buf, conf.osd_color);

        sprintf(osd_buf, "3:%8x  ", physw_status[2]);
        draw_txt_string(28, 12, osd_buf, conf.osd_color);*/



    if (kbd_process() == 0) {
        // we read keyboard state with _kbd_read_keys()

        jogdial_stopped=0;
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        //physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);

        if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run) {
            jogdial_stopped=1;
            get_jogdial_direction();
        }
        else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
            jogdial_stopped=0;
    }

	usb_remote_key() ;

    if (conf.remote_enable) {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);   // override USB and SD-Card Readonly Bits
    }
    else
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;   // override SD-Card Readonly Bit
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
        //return JOGDIAL_LEFT;
        return JOGDIAL_RIGHT;
    } else if (old_jogdial>new_jogdial) {
        return JOGDIAL_LEFT;
        //return JOGDIAL_RIGHT;
    } else {
        return 0;
    }
}

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}

static KeyMap keymap[] = {

		//play button doesn't alter anything here...????

		//door open a19b -> 219b
		//power b -> 3
	{ 0, KEY_SHOOT_FULL	, 0x00002002 },
	{ 0, KEY_SHOOT_FULL_ONLY	, 0x00000002 },  //   b ->    9
	{ 0, KEY_SHOOT_HALF	, 0x00002000 },  //a19b -> 819b
	{ 0, KEY_UP		    , 0x00000080 },  // 9b -> 1b
	{ 0, KEY_DOWN		, 0x00000100 },  // 19b -> 09b
	{ 0, KEY_PLAYBACK	, 0x00800000 }, // Found @0xffb6586c, levent 0x601 

//                             0x000FC005   #1 Mask
//	{ 1, KEY_UP		         , 0x00000400 },  // fff -> bff
//	{ 1, KEY_DOWN		     , 0x00000800 },  // fff -> 7ff
	{ 1, KEY_LEFT		     , 0x00008000 },  // ffff -> efff --> 6fff (hard)  test ef3f ->633f
	{ 1, KEY_RIGHT		     , 0x00004000 },  // ffff -> dfff --> 9fff (hard)  test df3f ->d73f  -> f7ff -> ffff was 4000
//	{ 1, KEY_UP_SOFT         , 0x00000400 },  // fff -> bff     //Must add to keyboard.h for use
//	{ 1, KEY_DOWN_SOFT	     , 0x00000800 },  // fff -> 7ff     //Must add to keyboard.h for use
//	{ 1, KEY_LEFT_SOFT	     , 0x00001000 },  // ffff -> efff   //Must add to keyboard.h for use
//	{ 1, KEY_RIGHT_SOFT	     , 0x00002000 },  // ffff -> dfff   //Must add to keyboard.h for use
	{ 1, KEY_SET		     , 0x00010000 },  // ASM1989 tested (JH) - fffff -> effff
//	{ 1, KEY_ZOOM_IN_FASTER  , 0x00000008 },  // f -> 3 (fast) (ORd in with normal)   //Must add to keyboard.h for use
//	{ 1, KEY_ZOOM_OUT_FASTER , 0x00000002 },  // f -> c (fast) (ORd in with normal)   //Must add to keyboard.h for use
	{ 1, KEY_ZOOM_IN         , 0x00000004 },  // f -> b (slow)
	{ 1, KEY_ZOOM_OUT        , 0x00000001 },  // f -> e (slow)
	{ 1, KEY_MENU		     , 0x00040000 },  // ASM1989 tested (JH) - fffff -> bffff
	{ 1, KEY_DISPLAY         , 0x00020000 },  // ASM1989 tested (JH) - fffff -> dffff
	{ 1, KEY_PRINT		     , 0x00080000 },  // ASM1989 tested (JH) - fffff -> 7ffff
	{ 1, KEY_VIDEO		     , 0x00080000 },
     	{ 0, 0, 0 }
};
/*
In Review mode   physw_status      0      1      2
iddle   <>   880a19b   <>   fff3f   <>   400000


hard press
right   <>   880a19b   <>   fd73f   <>   400000
left   <>   880a19b   <>   f633f   <>   400000
up   <>   880a11b   <>   feb3f   <>   400000
down   <>   880a09b   <>   fe73f   <>   400000


iddle Manual   <>   880a19b   <>   fff3f   <>   400000
iddle AV   <>   880a19b   <>   fff1f   <>   400000
iddle TV   <>   880a19b   <>   fff5f   <>   400000
iddle P   <>   880a19b   <>   fffdf   <>   400000
iddle auto   <>   880a19b   <>   fffff   <>   400000
iddle heart   <>   880a19b   <>   fff7f   <>   400000
iddle portriat   <>   880a19b   <>   ffe7f   <>   400000
iddle landscap   <>   880a19b   <>   ffeff   <>   400000
iddle mountain   <>   880a19b   <>   ffe9f   <>   400000
iddle dog   <>   880a19b   <>   ffcdf   <>   400000
iddle fireworks   <>   880a19b   <>   ffddf   <>   400000
iddle SCN   <>   880a19b   <>   ffdff   <>   400000
iddle video   <>   880a19b   <>   ffddf   <>   400000
iddle none   <>   880a19b   <>   ffebf   <>   400000
*/

