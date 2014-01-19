#include "camera.h"
#include "conf.h"
#include "keyboard.h"
#include "action_stack.h"
#include "lang.h"
#include "gui.h"
#include "gui_lang.h"
#include "console.h"
#include "usb_remote.h"
#include "clock.h"
#include "debug_led.h"

//-------------------------------------------------------------------
// Keyboard auto repeat

static long last_kbd_key = 0;
static long last_kbd_time = 0;
static long press_count = 0;

long kbd_get_autoclicked_key()
{
	register long key, t;

	key=kbd_get_clicked_key();
	if (key && (key != last_kbd_key))
    {
		last_kbd_key = key;
		press_count = 0;
		last_kbd_time = get_tick_count();
		return key;
	}
    else
    {
		if (last_kbd_key && kbd_is_key_pressed(last_kbd_key))
        {
			t = get_tick_count();
			if (t-last_kbd_time > ((press_count) ? KBD_REPEAT_DELAY : KBD_INITIAL_DELAY))
            {
				++press_count;
				last_kbd_time = t;
				return last_kbd_key;
			}
            else
            {
				return 0;
			}
		}
        else
        {
			last_kbd_key = 0;
			return 0;
		}
	}
}

//-------------------------------------------------------------------

static int kbd_blocked;

int kbd_is_blocked()
{
    return kbd_blocked;
}

void enter_alt()
{
    get_usb_power(CLEAR_USB_REGISTERS);         // Prevent previous USB remote pulse from starting script.
    kbd_blocked = 1;
    gui_set_alt_mode_state(ALT_MODE_ENTER);
}

void exit_alt()
{
    kbd_blocked = 0;
    gui_set_alt_mode_state(ALT_MODE_LEAVE);
}

//-------------------------------------------------------------------
// Core keyboard handler
long kbd_process()
{
    static int key_pressed;

    if (camera_info.perf.md_af_tuning)
    {
        switch (camera_info.perf.md_af_on_flag)
        {
        case 1:
            if (get_tick_count() >= (camera_info.perf.md_detect_tick + camera_info.perf.md_af_on_delay))
            {
                camera_info.perf.md_af_on_flag = 2;
                camera_set_led(camera_info.cam_af_led,1,200);
            }
            break;
        case 2:
            if (get_tick_count() >= (camera_info.perf.md_detect_tick + camera_info.perf.md_af_on_delay + camera_info.perf.md_af_on_time))
            {
                camera_info.perf.md_af_on_flag = 0;
                camera_set_led(camera_info.cam_af_led,0,0);
            }
            break;
        }
    }

    // check for & process non-keyboard script terminate
    script_check_terminate();

    // Reset keyboard auto repeat if no buttons pressed
    if (kbd_get_pressed_key() == 0)
        last_kbd_key = 0;

    // Set clicked key for scripts.
    if (kbd_get_clicked_key())
    {
        camera_info.state.kbd_last_clicked = kbd_get_clicked_key();
        camera_info.state.kbd_last_clicked_time = get_tick_count();
    }

    // Set Shutter Half Press state for GUI task.
    camera_info.state.is_shutter_half_press = kbd_is_key_pressed(KEY_SHOOT_HALF);

	// Alternative keyboard mode stated/exited by pressing print key.
	// While running Alt. mode shoot key will start a script execution.

	// alt-mode switch and delay emulation
 
	if ( key_pressed  && !usb_remote_active ) 
	{
        if (kbd_is_key_pressed(conf.alt_mode_button)
                || ((key_pressed >= CAM_EMUL_KEYPRESS_DELAY)
                && (key_pressed < CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION)))
        {
            if (key_pressed <= CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION) 
                key_pressed++;
            if (key_pressed == CAM_EMUL_KEYPRESS_DELAY) 
                kbd_key_press(conf.alt_mode_button);
            else if (key_pressed == CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION) 
                kbd_key_release(conf.alt_mode_button);
            return 1;
        } 
        else if (kbd_get_pressed_key() == 0)
        {
            if (key_pressed < CAM_EMUL_KEYPRESS_DELAY)
            {
                if (!kbd_blocked)
                {
                    // if start script on alt set, flag to run it
                    if(conf.script_startup==SCRIPT_AUTOSTART_ALT) script_run_on_alt_flag = 1;
                    enter_alt();
                }
                else
                    exit_alt();
            }
            key_pressed = 0;
            return 1;
        }
        return 1;
    }
       
    // auto iso shift
    if (camera_info.state.is_shutter_half_press && kbd_is_key_pressed(conf.alt_mode_button)) 
        return 0;

    if (kbd_is_key_pressed(conf.alt_mode_button)) 
	{
        key_pressed = 1;
        kbd_key_release_all();          
        return 1;
    }

#ifdef CAM_TOUCHSCREEN_UI
    extern int ts_process_touch();
    if (ts_process_touch())
    {
        gui_set_need_restore();
    }
#endif

    // deals with the rest

    if ( !kbd_blocked || usb_remote_active ) 
	{
		kbd_blocked = handle_usb_remote();
	}

    if (gui_kbd_process())
        return 1;

    action_stack_process_all();

    // Check if a PTP script needs to be started
    //  do this after action_stack_process_all so new script is not run until next timeslice
    extern void start_ptp_script();
    start_ptp_script();

    return kbd_blocked;
}
