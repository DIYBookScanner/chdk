#include "stdlib.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "../../core/gui_draw.h"

void keys_new();
typedef struct {
    short grp;
    short hackkey;
    long canonkey;
} KeyMap;

static long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static KeyMap keymap[];
extern void _GetKbdState(long*);

#ifdef CAM_HAS_GPS
extern int Taste_Funktion;
extern int Taste_Taste;
extern int Taste_Druck;
extern int Taste_press;
#endif

// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0 (0x000FFC0F)     // physw_status[0] was 7FC05
#define KEYS_MASK1 (0x00200000)
#define KEYS_MASK2 (0x00002182)  

#define NEW_SS (0x2000)

#define SD_READONLY_FLAG (0x20000)
#define SD_READONLY_IDX     2

#define USB_MASK (0x4000000)
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

    { 0, KEY_ZOOM_OUT        , 0x00000003 },
    { 0, KEY_ZOOM_OUT        , 0x00000001 },
    { 0, KEY_ZOOM_OUT        , 0x00000002 },
    { 0, KEY_ZOOM_IN         , 0x0000000C },
    { 0, KEY_ZOOM_IN         , 0x00000004 },
    { 0, KEY_ZOOM_IN         , 0x00000008 },
    { 0, KEY_UP_SOFT         , 0x00000400 },
    { 0, KEY_DISPLAY         , 0x00000800 },
    { 0, KEY_UP              , 0x00001000 },
    { 0, KEY_RIGHT_SOFT      , 0x00002000 },
    { 0, KEY_RIGHT           , 0x00006000 },
    { 0, KEY_DOWN_SOFT       , 0x00008000 },
    { 0, KEY_SET             , 0x00010000 },
    { 0, KEY_DOWN            , 0x00020000 },
    { 0, KEY_MENU            , 0x00040000 },
    { 0, KEY_VIDEO           , 0x00080000 },

    { 1, KEY_PRINT           , 0x00200000 }, // playback = alt button
    { 1, KEY_PLAYBACK        , 0x00200000 },

    { 2, KEY_LEFT_SOFT       , 0x00000080 },
    { 2, KEY_LEFT            , 0x00000100 },
    { 2, KEY_SHOOT_FULL      , 0x00002002 },
    { 2, KEY_SHOOT_FULL_ONLY , 0x00000002 },
    { 2, KEY_SHOOT_HALF      , 0x00002000 },

    { 0, 0, 0 }
};

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}

void my_blinkk(void) {
	int i;
	while(1) {
		*((volatile int *) 0xC0220130) = 0x46; // Turn on LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC0220130) = 0x44; // Turn off LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC0220130) = 0x46; // Turn on LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC0220130) = 0x44; // Turn off LED
		for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
	}
}

volatile int jogdial_stopped=0;

extern long __attribute__((naked)) wrap_kbd_p1_f();


static void __attribute__((noinline)) mykbd_task_proceed() {
	
	while (physw_run) {
        _SleepTask(*((int*)(0x1c44 +0x8))); //  @FF0248AC

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

// copied from g12 and sx30, thx to philmoz
// Pointer to stack location where jogdial task records previous and current
// jogdial positions

extern short* jog_position;

void jogdial_control(int n)
{
    if (jogdial_stopped && !n)
    {
        // If re-enabling jogdial set the task code current & previous positions to the actual
        // dial positions so that the change won't get processed by the firmware
        jog_position[0] = jog_position[2] = (*(short*)0xC0240106);  // Rear dial
    }
    jogdial_stopped = n;
}

// like SX110
void my_kbd_read_keys() {
		

    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2]; 

	_GetKbdState( kbd_new_state );
	_kbd_read_keys_r2( kbd_new_state);

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
//    kbd_new_state[0] = physw_status[0];  //sx220 changed from physw_status[0]
 //   kbd_new_state[2] = physw_status[2];
 //   kbd_new_state[3] = physw_status[3]; //sx220 added

    if (kbd_process() == 0) {
	// we read keyboard state with _kbd_read_keys()
		physw_status[0] = kbd_new_state[0];
		physw_status[1] = kbd_new_state[1];
		physw_status[2] = kbd_new_state[2];		
		jogdial_control(0);
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]); 
        physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]); 
        physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);

        if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run) {
            jogdial_control(1);
            get_jogdial_direction();
        }
        else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
            jogdial_control(0);
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
			if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)
                return 1;
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

///
int Get_JogDial(void) {
	return (*(int*)0xC0240104)>>16;     // 0xC0240000 + 0x104
}

static int new_jogdial=0, old_jogdial=0;

long get_jogdial_direction(void) {
	old_jogdial=new_jogdial;
    new_jogdial=Get_JogDial();

    if (old_jogdial<new_jogdial) {
        return JOGDIAL_RIGHT;
    } else if (old_jogdial>new_jogdial) {
        return JOGDIAL_LEFT;
    } else {
        return 0;
    }
}
