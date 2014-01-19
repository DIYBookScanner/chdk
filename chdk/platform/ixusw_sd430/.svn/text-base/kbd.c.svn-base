#include "lolevel.h"
#include "platform.h"
#include "conf.h"
#include "core.h"
#include "keyboard.h"

#define KEY_MASK 0x2FFE

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x80000000)


typedef struct {
    long hackkey;
    long canonkey;
} KeyMap;


static long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state = KEY_MASK;
long debug_kbd_state_diff;

static KeyMap keymap[];

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

#define USB_MASK 0x400000
#define USB_IDX  0

//TO DO
extern void usb_remote_key( void ) ;
int get_usb_bit()
{
    register long usb_physw;
    usb_physw = *(long*)0xc0220200; //can be read directly (the usb bit doesn't need kbd_power_on or so)
    return(( usb_physw & USB_MASK)==USB_MASK);
}


long __attribute__((naked)) wrap_kbd_p1_f() ;



static void __attribute__((noinline)) hook_kbd_task_proceed()
{
    while (physw_run){
        _SleepTask(5);

        if (wrap_kbd_p1_f() == 1) // Readout key state via camera function
        {
        _kbd_p2_f();
        }
    }
}

void __attribute__((naked,noinline)) mykbd_task()
{
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *  function arguments destroyed;
     *  function CAN NOT return properly;
     *  MUST NOT call or use stack variables before stack
     *  is setup properly;
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

    hook_kbd_task_proceed();

    /* function can be modified to restore SP here...
     */

    _ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
    //found @ 0xff829c94
    asm volatile(
        "STMFD   SP!, {R4-R7,LR}\n"
        "SUB     SP, SP, #0xC\n"
                "BL      _kbd_read_keys\n"
                "BL      hook_kbd_handle_keys\n"
                "B       _kbd_p1_f_cont\n"        // Continue original function execution
    );
    return 0; // shut up the compiler
}


#define IN(base, value) ((value < base + 20) && (value > base - 20))

/**
 * Handles and forwards key settings to key processing routines
 */
void hook_kbd_handle_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    kbd_new_state[2] = physw_status[2];

    if (kbd_process() == 0){
        // leave it alone...
    } else {
        // override keys
        physw_status[2] = (physw_status[2] & (~KEY_MASK)) | (kbd_mod_state & KEY_MASK);
    }

    usb_remote_key();
    if (conf.remote_enable) {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~USB_MASK;
    }

    // Drop SD readonly status
    physw_status[1] = physw_status[1] & ~SD_READONLY_FLAG;
}

void kbd_key_press(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state |= keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release_all()
{
    kbd_mod_state |= KEY_MASK;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            return ((kbd_new_state[2] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            return ((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
            ((kbd_new_state[2] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if ((kbd_new_state[2] & keymap[i].canonkey) == 0){
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
            ((kbd_new_state[2] & keymap[i].canonkey) == 0)){
            return keymap[i].hackkey;
        }
    }
    return 0;
}

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


static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
    {KEY_UP,                0x00000020 },
    {KEY_DOWN,              0x00000040 },
    {KEY_LEFT,              0x00000080 },
    {KEY_RIGHT,             0x00000100 },
    {KEY_SET,               0x00000200 },
    {KEY_SHOOT_FULL,        0x00000006 },
    {KEY_SHOOT_FULL_ONLY,   0x00000004 },
    {KEY_SHOOT_HALF,        0x00000002 },
    {KEY_ZOOM_IN,           0x00000008 },
    {KEY_ZOOM_OUT,          0x00000010 },
    {KEY_MENU,              0x00000400 },
    {KEY_DISPLAY,           0x00000800 },
    {KEY_PRINT,             0x00002000 },
    { 0, 0 }
};


void kbd_set_alt_mode_key_mask(long key)
{
    return;
}
