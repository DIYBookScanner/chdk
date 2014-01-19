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
extern void _GetKbdState(long*);

// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0 (0x80000000) //Logic OR of group 0 Keymap values
#define KEYS_MASK1 (0xF8800001) //Logic OR of group 1 Keymap values
#define KEYS_MASK2 (0x000030C9) //Logic OR of group 2 Keymap values

#define SD_READONLY_FLAG    0x02000000 // Found @0xffba4b8c, levent 0x20a
#define SD_READONLY_IDX     2
#define USB_MASK            0x10000000 // Found @0xffba4b9c, levent 0x202
#define USB_IDX             2

extern void usb_remote_key() ;
int get_usb_bit() {
    long usb_physw[3];
    usb_physw[USB_IDX] = 0;
    _kbd_read_keys_r2(usb_physw);
    return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

static KeyMap keymap[] = {
    // Order IS important. kbd_get_pressed_key will walk down this table
    // and take the first matching mask. Notice that KEY_SHOOT_HALF is
    // always pressed if KEY_SHOOT_FULL is. --MarcusSt
    { 0, KEY_DISPLAY         ,0x80000000 }, // Found @0xffba4ac4, levent 0x0a
    { 1, KEY_DOWN            ,0x80000000 }, // Found @0xffba4b0c, levent 0x05
    { 1, KEY_UP              ,0x40000000 }, // Found @0xffba4b04, levent 0x04
    { 1, KEY_SHOOT_FULL      ,0x30000000 }, // Found @0xffba4afc, levent 0x01
    { 1, KEY_SHOOT_FULL_ONLY ,0x20000000 }, // Found @0xffba4afc, levent 0x01
    { 1, KEY_SHOOT_HALF      ,0x10000000 }, // Found @0xffba4af4, levent 0x00
    { 1, KEY_ERASE           ,0x08000000 },
    { 1, KEY_MENU            ,0x00800000 }, // Found @0xffba4ae4, levent 0x09
    { 1, KEY_SET             ,0x00000001 }, // Found @0xffba4acc, levent 0x08
    { 2, KEY_PRINT           ,0x00000008 }, // Key PLAYBACK for ALT menu
    { 2, KEY_LEFT            ,0x00002000 }, // Found @0xffba4b4c, levent 0x06
    { 2, KEY_RIGHT           ,0x00001000 }, // Found @0xffba4b44, levent 0x07
    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffba4b34, levent 0x02
    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffba4b2c, levent 0x03
    { 2, KEY_POWER           ,0x00000020 }, // Found @0xffba4b24, levent 0x100
    { 2, KEY_PLAYBACK        ,0x00000008 }, // Found @0xffba4b1c, levent 0x101
    { 2, KEY_VIDEO           ,0x00000001 },
    { 0, 0, 0 }
};

// NOP
void kbd_set_alt_mode_key_mask(long key)
{
}

volatile int jogdial_stopped=0;

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {

    //sx160 100a @ 0xff829238
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

// Pointer to stack location where jogdial task records previous and current
// jogdial positions
extern short* jog_position;
extern short rear_dial_position, front_dial_position;

void jogdial_control(int n) {
    if (jogdial_stopped && !n) {
        // If re-enabling jogdial set the task code current & previous positions to the actual
        // dial positions so that the change won't get processed by the firmware
        jog_position[0] = jog_position[2] = rear_dial_position;   // Rear dial
        jog_position[1] = jog_position[3] = front_dial_position;  // Front dial

    }
    jogdial_stopped = n;
}

void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _GetKbdState(kbd_new_state);
    _kbd_read_keys_r2( kbd_new_state);

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

        if ((jogdial_stopped==0) && !camera_info.state.state_kbd_script_run)
        {
            jogdial_control(1);
            get_jogdial_direction();
        }
        else if (jogdial_stopped && camera_info.state.state_kbd_script_run)
            jogdial_control(0);
    }

    usb_remote_key();

    if (conf.remote_enable) {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
    } else {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
    }
}

void kbd_key_press(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key)
        {
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
    return 0;
}
#endif

static short new_jogdial = 0, old_jogdial = 0, new_frontdial = 0, old_frontdial = 0;

long get_jogdial_direction(void)
{
    old_jogdial = new_jogdial;
    new_jogdial = rear_dial_position;

    old_frontdial = new_frontdial;
    new_frontdial = front_dial_position;

    if      (old_jogdial > new_jogdial)     return JOGDIAL_LEFT;
    else if (old_jogdial < new_jogdial)     return JOGDIAL_RIGHT;
    else if (old_frontdial > new_frontdial) return FRONTDIAL_LEFT;
    else if (old_frontdial < new_frontdial) return FRONTDIAL_RIGHT;
    else                                    return 0;
}
