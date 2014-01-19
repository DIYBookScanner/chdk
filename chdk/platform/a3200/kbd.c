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

extern void _GetKbdState(long*);

// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0 (0x00002000) //Logic OR of group 0 Keymap values
#define KEYS_MASK1 (0x00000000) //Logic OR of group 1 Keymap values
#define KEYS_MASK2 (0x0000F0FF) //Logic OR of group 2 Keymap values

#define SD_READONLY_FLAG    0x00020000 // Found @0xffb5d574, levent 0x90a
#define USB_MASK            0x04000000 // Found @0xffb5d594, levent 0x902
#define USB_FLAG            0x04000000 // ?? Found @0xff3bcf44 a3300, levent 0x902
#define USB_IDX 2
#define SD_READONLY_IDX     2

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
	// always pressed if KEY_SHOOT_FULL is. --MarcusSt
    { 0, KEY_PLAYBACK        ,0x00002000 }, // Found @0xffb5d4cc, levent 0x601
//    { 0, KEY_POWER           ,0x00004000 }, // Found @0xffb5d4d4, levent 0x600
    { 2, KEY_SHOOT_FULL      ,0x00003000 }, // Found @0xffb5d544, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00001000 }, // Found @0xffb5d53c, levent 0x00
    { 2, KEY_SHOOT_FULL_ONLY ,0x00002000 }, // Found @0xffb5d544, levent 0x01
    { 2, KEY_FACE            ,0x00000040 }, //
    { 2, KEY_UP              ,0x00000001 }, // Found @0xffb5d4e4, levent 0x04
    { 2, KEY_DOWN            ,0x00000002 }, // Found @0xffb5d4ec, levent 0x05
    { 2, KEY_LEFT            ,0x00000004 }, // Found @0xffb5d4f4, levent 0x06
    { 2, KEY_RIGHT           ,0x00000008 }, // Found @0xffb5d4fc, levent 0x07
    { 2, KEY_SET             ,0x00000010 }, // Found @0xffb5d504, levent 0x08
    { 2, KEY_DISPLAY         ,0x00000020 }, // Found @0xffb5d50c, levent 0x0a
    { 2, KEY_MENU            ,0x00000080 }, // Found @0xffb5d51c, levent 0x09
    { 2, KEY_ZOOM_OUT        ,0x00004000 }, // Found @0xffb5d54c, levent 0x03
    { 2, KEY_ZOOM_IN         ,0x00008000 }, // Found @0xffb5d554, levent 0x02    
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
	//"BL	_kbd_read_keys \n"
	"BL	my_kbd_read_keys \n"	// patched
	"B	_kbd_p1_f_cont \n"
	);
	return 0; // shut up the compiler
}
	
	
static void __attribute__((noinline)) mykbd_task_proceed() {
	
	while (physw_run) {
        _SleepTask(*((int*)(0x1C30 + 0x8))); //  @FF83410C + FF834114

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
        physw_status[2] = physw_status[2] & ~(SD_READONLY_FLAG | USB_MASK);   // override USB and SD-Card Readonly Bits
    }
   
    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;   // override SD-Card Readonly Bit
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

