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

#define KEYS_MASK0 (0x0000000C)		// physw_status[0]
					// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK1 (0x00000000)		// physw_status[1], override 0xF0 (keys) + 0xF00 (feather)
#define KEYS_MASK2 (0x000003FD)		// physw_status[2]

#define SD_READONLY_FLAG (0x20000)  // SD-Card Lock Status (locked / unlocked)
#define SD_READONLY_IDX     2  
#define USB_MASK (0x80000)          // USB-Power (triggered around 3,5V)
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
    { 2, KEY_UP         , 0x00000080 },
    { 2, KEY_DOWN       , 0x00000040 },
    { 2, KEY_LEFT       , 0x00000010 },
    { 2, KEY_RIGHT      , 0x00000020 },
    { 0, KEY_SET        , 0x00000004 },
    { 2, KEY_SHOOT_FULL , 0x00000300 },   // 0x00000200(KEY_SHOOT_FULL) + 0x00000100 (KEY_SHOOT_HALF)
    { 2, KEY_SHOOT_FULL_ONLY , 0x00000200 }, 
    { 2, KEY_SHOOT_HALF , 0x00000100 },
    { 2, KEY_ZOOM_IN    , 0x00000004 },
    { 2, KEY_ZOOM_OUT   , 0x00000008 },
    { 2, KEY_MENU       , 0x00000001 },
    { 0, KEY_PRINT      , 0x00000008 },   // ALT Key workaround: KEY_DISP(8) (camera has no print key)
    { 0, 0, 0 }
};


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
    mykbd_task_proceed();
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
    kbd_prev_state[2] = kbd_new_state[2]; 

   // Get the state of the buttons on the top of the G10. Like On/off, shoot, zoom, etc.
   // but none of the backside buttons, like cursor, menu, display,etc..

     _GetKbdState(kbd_new_state);

   /* Get the rest of the buttons */

    _kbd_read_keys_r2(kbd_new_state);

    if (kbd_process() == 0) {

          physw_status[0] = kbd_new_state[0];
          physw_status[1] = kbd_new_state[1];
          physw_status[2] = kbd_new_state[2];

    } else {
   
          physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
          physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
          physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);   
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

