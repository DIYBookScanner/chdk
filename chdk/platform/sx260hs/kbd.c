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
static int alt_mode_led=0;
extern void _GetKbdState(long*);

#ifdef CAM_HAS_GPS
extern int Taste_Funktion;
extern int Taste_Taste;
//extern int Taste_Taste_0;
//extern int Taste_Taste_1;
extern int Taste_Druck;
extern int Taste_press;
//extern int kbd_blocked;
#endif

// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x3F800000)     // SX 260 ASm1989
#define KEYS_MASK2 (0x00001FE0)     // SX 260 ASm1989

//ASM1989 Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
#define SD_READONLY_FLAG    0x00080000 // Found @0xff441628, levent 0x20a
#define SD_READONLY_IDX     2
#define USB_MASK            0x10000000 // Found @0xff441660, levent 0x202
#define USB_IDX             2

extern void usb_remote_key( int ) ;
int get_usb_bit() {
    long usb_physw[3];
    usb_physw[USB_IDX] = 0;
    _kbd_read_keys_r2(usb_physw);
    return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

// Using Finsig
static KeyMap keymap[] = {
    { 1, KEY_PRINT           ,0x00800000 }, // KEY_PLAYBACK as ALT 
    { 1, KEY_PLAYBACK        ,0x00800000 }, // Found @0xff441578, levent 0x101
    { 1, KEY_SHOOT_FULL      ,0x03000000 }, // Found @0xff441588, levent 0x01
    { 1, KEY_SHOOT_FULL_ONLY ,0x02000000 }, // Found @0xff441588, levent 0x01
    { 1, KEY_SHOOT_HALF      ,0x01000000 }, // Found @0xff441580, levent 0x00
    { 1, KEY_ZOOM_OUT        ,0x0C000000 }, // Asm1989 Manual stuff
    { 1, KEY_ZOOM_OUT        ,0x04000000 },
    { 1, KEY_ZOOM_OUT        ,0x08000000 },
    { 1, KEY_ZOOM_IN         ,0x30000000 },
    { 1, KEY_ZOOM_IN         ,0x10000000 },
    { 1, KEY_ZOOM_IN         ,0x20000000 },
    { 2, KEY_VIDEO           ,0x00000020 }, // Found @0xff4415d8, levent 0x1a
    { 2, KEY_MENU            ,0x00000040 }, // Found @0xff4415e0, levent 0x09
    { 2, KEY_DISPLAY         ,0x00000080 }, // Found @0xff4415e8, levent 0x0a
    { 2, KEY_UP              ,0x00000100 }, // Found @0xff4415f0, levent 0x04
    { 2, KEY_DOWN            ,0x00000200 }, // Found @0xff4415f8, levent 0x05
    { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xff441600, levent 0x07
    { 2, KEY_LEFT            ,0x00000800 }, // Found @0xff441608, levent 0x06
    { 2, KEY_SET             ,0x00001000 }, // Found @0xff441610, levent 0x08
    { 0, 0, 0 }
};

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}

void my_blinkk(void) {
    int i;
    while(1) {
        *((volatile int *) 0xC0220130) = 0x46;  // Turn on LED
        for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

        *((volatile int *) 0xC0220130) = 0x44;  // Turn off LED
        for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

        *((volatile int *) 0xC0220130) = 0x46;  // Turn on LED
        for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

        *((volatile int *) 0xC0220130) = 0x44;  // Turn off LED
        for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
    }
}

volatile int jogdial_stopped=0;

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {

    asm volatile(
                "STMFD   SP!, {R1-R7,LR}\n"
                "MOV     R5, #0\n"
                "BL      my_kbd_read_keys\n"
                "B       _kbd_p1_f_cont\n"
    );

    return 0;
}

static void __attribute__((noinline)) mykbd_task_proceed() {
    while (physw_run) {
        _SleepTask(physw_sleep_delay);

        if (wrap_kbd_p1_f() == 1) {             // autorepeat ?
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

void jogdial_control(int n) {
    if (jogdial_stopped && !n) {
        // If re-enabling jogdial set the task code current & previous positions to the actual
        // dial positions so that the change won't get processed by the firmware
        jog_position[0] = jog_position[2] = (*(short*)0xC0240106);  //TODO SX230 CODE  Rear dial
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

    usb_remote_key(physw_status[USB_IDX]) ;

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
    return (*(int*)0xC0240104)>>16;     //TODO SX230 CODE 0xC0240000 + 0x104
}

static int new_jogdial = 0, old_jogdial = 0;

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
