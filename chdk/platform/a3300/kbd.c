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

// button and mode dial codes
// physw [0]
#define BTN_Play	(0x00002000)

// physw [2]
#define BTN_Up		(0x00000001)
#define BTN_Down	(0x00000002)
#define BTN_Left	(0x00000004)
#define BTN_Right	(0x00000008)
#define BTN_Set		(0x00000010)
#define BTN_Disp	(0x00000020)
#define BTN_Face	(0x00000040)
#define BTN_Menu	(0x00000080)

// the MODE dial is in Gray code
// the following are informational, not used
/*
#define DIAL_Movie	(0x00000600)
#define DIAL_Discreet	(0x00000200)
#define DIAL_FishEye	(0x00000000)
#define DIAL_Scene	(0x00000100)
#define DIAL_Easy	(0x00000300)
#define DIAL_Auto	(0x00000700)
#define DIAL_Live	(0x00000500)
#define DIAL_Program	(0x00000400)
*/

#define BTN_ShootHalf	(0x00001000)
#define BTN_ShootFull	(0x00002000)
#define BTN_ZoomWide	(0x00004000)
#define BTN_ZoomTele	(0x00008000)

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

extern void _GetKbdState(long*);

// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0 (BTN_Play)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 ( \
            BTN_Up      |\
            BTN_Down    |\
            BTN_Left    |\
            BTN_Right   |\
            BTN_Set     |\
            BTN_Disp    |\
            BTN_Face    |\
            BTN_Menu    |\
            BTN_ShootHalf   |\
            BTN_ShootFull   |\
            BTN_ZoomWide    |\
            BTN_ZoomTele     \
           )

#define LED_AF 0xC02200F4

#define SD_READONLY_FLAG (0x00020000)
#define SD_READONLY_IDX     2

#define USB_MASK (0x04000000)
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
    { 0, KEY_PRINT           ,BTN_Play }, 
    { 2, KEY_SHOOT_FULL      ,BTN_ShootFull | BTN_ShootHalf }, // Found @0xffb5dc9c, levent 0x01
    { 2, KEY_SHOOT_HALF      ,BTN_ShootHalf }, // Found @0xffb5dc94, levent 0x00
    { 2, KEY_SHOOT_FULL_ONLY ,BTN_ShootFull }, // Found @0xffb5dc9c, levent 0x01
    { 2, KEY_FACE            ,BTN_Face }, // 
    { 2, KEY_UP              ,BTN_Up }, // Found @0xffb5dc3c, levent 0x04
    { 2, KEY_DOWN            ,BTN_Down }, // Found @0xffb5dc44, levent 0x05
    { 2, KEY_LEFT            ,BTN_Left }, // Found @0xffb5dc4c, levent 0x06
    { 2, KEY_RIGHT           ,BTN_Right }, // Found @0xffb5dc54, levent 0x07
    { 2, KEY_SET             ,BTN_Set }, // Found @0xffb5dc5c, levent 0x08
    { 2, KEY_DISPLAY         ,BTN_Disp }, // Found @0xffb5dc64, levent 0x0a
    { 2, KEY_MENU            ,BTN_Menu }, // Found @0xffb5dc74, levent 0x09
    { 2, KEY_ZOOM_OUT        ,BTN_ZoomWide }, // Found @0xffb5dca4, levent 0x03
    { 2, KEY_ZOOM_IN         ,BTN_ZoomTele }, // Found @0xffb5dcac, levent 0x02
    { 0, 0, 0 }
};

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}


extern long __attribute__((naked)) wrap_kbd_p1_f() {
	

	asm volatile(
		"STMFD	SP!, {R1-R7,LR} \n"
		"MOV	R5, #0 \n"
		//"BL		_kbd_read_keys \n"
		"BL		my_kbd_read_keys \n"	// pacthed
		"B		_kbd_p1_f_cont \n"
	);
	return 0; // shut up the compiler
}
	
	
static void __attribute__((noinline)) mykbd_task_proceed() {
	
	while (physw_run) {
        _SleepTask(*((int*)(0x1C30 + 0x8))); //  @FF834160 + FF834168

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
