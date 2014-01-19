#include "keyboard.h"
#include "conf.h"
#include "platform.h"
#include "../generic/wrappers.c"

extern int rec_mode_active(void);

long lens_get_focus_pos()
{
//    static long v=65535;
//    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run|| shooting_get_common_focus_mode())?v=_GetFocusLensSubjectDistance():v;
    if (rec_mode_active())
        return _GetFocusLensSubjectDistance();
    else
        return 65535;
}

long lens_get_focus_pos_from_lens()
{
//    static long v=MAX_DIST;
//    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run  || shooting_get_common_focus_mode())?v=_GetFocusLensSubjectDistanceFromLens():v;
    if (rec_mode_active())
        return _GetFocusLensSubjectDistanceFromLens();
    else
        return MAX_DIST;
}


long lens_get_target_distance()
{
//    static long v=65535;
//    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run|| shooting_get_common_focus_mode())?v=_GetCurrentTargetDistance():v;
    if (rec_mode_active())
        return _GetCurrentTargetDistance();
    else
        return 65535;
}

