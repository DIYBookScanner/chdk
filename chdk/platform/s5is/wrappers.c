#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run  || shooting_get_focus_mode())?v=_GetFocusLensSubjectDistance():v;
//	return _GetFocusLensSubjectDistance();
}

long lens_get_focus_pos_from_lens()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run  || shooting_get_focus_mode())?v=_GetFocusLensSubjectDistanceFromLens():v;
//	return _GetFocusLensSubjectDistanceFromLens(); 
}

long lens_get_target_distance()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run  || shooting_get_focus_mode())?v=_GetCurrentTargetDistance():v;
//	return _GetCurrentTargetDistance();
}
