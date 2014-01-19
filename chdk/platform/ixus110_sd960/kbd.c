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

static KeyMap keymap[];

// OK, ixus110
#define KEYS_MASK0 (0x00000000)
static int keys_mask1=0x0000F000;
#define KEYS_MASK2 (0x4EEF)
static int set_fake_key=0;

#define SD_READONLY_FLAG    0x00020000 // Found @0xffaeeb8c, levent 0x90a
#define SD_READONLY_IDX     2
#define USB_MASK            0x00080000 // Found @0xffaeeba4, levent 0x902
#define USB_IDX             2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
    long usb_physw[3];
    usb_physw[USB_IDX] = 0;
    _kbd_read_keys_r2(usb_physw);
    return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}
/*
battery door switch, 0: door open
forcing to one allows camera to run with door open.
Informational only for now,
making the camera boot with door open requires some ugly changes in boot.c
see http://chdk.setepontos.com/index.php?topic=5744.0
found via GetBatteryCoverClose (which looks in a table that tells it the physw word and bit)
#define BATDOOR_MASK (?)
*/

void kbd_fetch_data(long*);

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

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task()
{
    mykbd_task_proceed();

    _ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{

    asm volatile(
                "STMFD   SP!, {R1-R5,LR}\n"
                "MOV     R4, #0\n"
                "BL      my_kbd_read_keys\n"
                   "B     _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}

extern void _GetKbdState(long*);
long get_jogdial_direction();
volatile int jogdial_stopped=0;
void enable_extra_button(short);

void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _kbd_pwr_on();
    
    _GetKbdState(kbd_new_state);
    _kbd_read_keys_r2(kbd_new_state);
    //kbd_fetch_data(kbd_new_state);

    if (kbd_process() == 0) {
        // leave it alone...
        physw_status[0] = kbd_new_state[0];
        physw_status[1] = kbd_new_state[1];
        physw_status[2] = kbd_new_state[2];
        jogdial_stopped=0;
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
        physw_status[1] = (kbd_new_state[1] & (~keys_mask1)) | (kbd_mod_state[1] & keys_mask1);
        physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);
        if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run) {
            jogdial_stopped=1;
            get_jogdial_direction();
        }
        else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
            jogdial_stopped=0; 
    }
    //_kbd_read_keys_r2(physw_status);


    usb_remote_key() ;

    if (conf.remote_enable) {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
    } else {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
    }
    
// hide battery door status
//    physw_status[2] |= BATDOOR_MASK;

    _kbd_pwr_off();
    
    if (set_fake_key & 0x10000000) {
        enable_extra_button((short)(set_fake_key & 0xffff));
        set_fake_key=0;
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
  kbd_mod_state[1] |= keys_mask1;
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

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
    { 1, KEY_POWER           ,0x00000001 }, // Found @0xffaeea90, levent 0x600
    { 1, KEY_ZOOM_OUT        ,0x00002000 }, // Found @0xffaeeab4, levent 0x03
    { 1, KEY_ZOOM_IN         ,0x00004000 }, // Found @0xffaeeac0, levent 0x02
    { 1, KEY_SHOOT_FULL      ,0x00009000 }, // Found @0xffaeeacc, levent 0x01
    { 1, KEY_SHOOT_FULL_ONLY ,0x00008000 }, // Found @0xffaeeacc, levent 0x01
    { 1, KEY_SHOOT_HALF      ,0x00001000 }, // Found @0xffaeeaa8, levent 0x00
    { 2, KEY_LEFT            ,0x00000020 }, // Found @0xffaeeb14, levent 0x06
    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffaeeb20, levent 0x07
    { 2, KEY_DOWN            ,0x00000080 }, // Found @0xffaeeb2c, levent 0x05
    { 2, KEY_UP              ,0x00000200 }, // Found @0xffaeeb44, levent 0x04
    { 2, KEY_SET             ,0x00000400 }, // Found @0xffaeeb50, levent 0x08
    { 2, KEY_MENU            ,0x00000800 }, // Found @0xffaeeb5c, levent 0x09
    { 2, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffaeeb68, levent 0x601
    { 2, KEY_PRINT           ,0x00004000 },
    { 0, 0                   ,0x00000000 }, // placeholder for the fake key
//    { 2, KEY_LEFT_SOFT       ,0x00000001 },
//    { 2, KEY_RIGHT_SOFT      ,0x00000002 },
//    { 2, KEY_DOWN_SOFT       ,0x00000004 },
//    { 2, KEY_UP_SOFT         ,0x00000008 },
    { 0, 0, 0 }
};

void enable_extra_button(short key) {
/*
 * enable or disable the additional "fake" button
 * in this case, the power button will be re-mapped in ALT mode
 * called from the kbd task
 * beware: the "placeholder" in keymap[] is directly addressed here
 * the placeholder has to be the last entry before the terminating { 0, 0, 0 }, if it is ever set to { 0, 0, 0 }
 */
    if (key) {
        keys_mask1=0x0000F001;
        keymap[14].grp=1;
        keymap[14].canonkey=0x00000001;
        keymap[14].hackkey=key;
    }
    else {
        keys_mask1=0x0000F000;
        keymap[14].grp=0;
        keymap[14].canonkey=0;
        keymap[14].hackkey=0;
    }
}

void kbd_set_extra_button(short key) { // called by core
    set_fake_key=key|0x10000000;    
}

void kbd_fetch_data(long *dst)
{
    // OK, GetKbdState
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
}

static int new_jogdial=0, old_jogdial=0;

int Get_JogDial(void){
 return (*(int*)0xC0240104)>>16; // OK, ixus110
}

long get_jogdial_direction(void) { 
 old_jogdial=new_jogdial;
 new_jogdial=Get_JogDial();
 if (old_jogdial<new_jogdial) return JOGDIAL_LEFT; 
 else if (old_jogdial>new_jogdial) return JOGDIAL_RIGHT;
 else return 0;
}
