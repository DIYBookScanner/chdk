#include "stubs_asm.h"

//Found by firmware comparison with ixus55 100b port. Not tested
DEF(physw_run,          0x000021d0)     // From PhySw sub_ff829c00 (0x21D4 - 0x4)
DEF(physw_status,       0x00019d30)     // See GpioStatus below
DEF(zoom_busy,          0x00097fb8)     // Found in sub_ffb6499c near to "ZoomLens"
DEF(focus_busy,         0x000982d0)     // Found in sub_ffb74704 near to "FocusLensController"
DEF(FlashParamsTable,   0xff9670d0)     // Found in sub_ff96723c near to "PropertyTable.c"

// The names below could be found automatically
// by looking up the strings with the same names as these variables
// and function 'ShowPhySwStatus' which is also symbolic
DEF(NotifyMask,         0x00019d00)
DEF(SwitchMask,         0x00019d10)
DEF(InvertData,         0x00019d20)
DEF(GpioStatus,         0x00019d30)     // This is the real name for 'physw_status'
DEF(SwitchStatus,       0x00019d40)


DEF(zoom_status,        0x00008458)     //Found in sub_ff9a8918 near to "_MoveOpticalToTele"
DEF(levent_table,       0xff95ec74)
DEF(canon_menu_active,  0x0000926c)     //Found in sub_ffa04484
DEF(canon_shoot_menu_active,0x8560+1)   //Found in sub_ff9b0a8c
DEF(recreview_hold,     0x00091be4)     //Found in sub_ff9a34ac
DEF(some_f_for_dng,     0x0000a36c)     //Found in sub_ffa4e010 by comparison to ixus65 100a
DEF(second_ext_for_dng, 0x0000a390)     //some_f_for_dng + 0x24?
DEF(sys_mempart_id,        0x17448)     //found by srsa_4c
DEF(playrec_mode,           0x7214)     //found @ 0xff95be78 by comparison to ixus65
DEF(movie_status,       0x00085434)     //found @ 0xff94845c by comparison to ixus55

//To do:
