#include "stubs_asm.h"

DEF(physw_status, 0x11958)  // ok
DEF(physw_run, 0x1FB0)      // ok

DEF(zoom_busy, 0x8274C)     // ok
DEF(focus_busy, 0x82AF8)    // (based on the a410 port)

DEF(movie_status, 0x740DC) // @FF9499C0

DEF(some_flag_for_af_scan, 0x748F0) // sub_FF9554A0, seems equal to sub_ffd45b04 in a540
DEF(parameter_for_af_scan, 0x748E8) // sub_FF9554A0

DEF(zoom_status, 0x81A8)    // _ZoomState

DEF(some_f_for_dng, 0xa094) // equivalent to the a410 port, was: 0x9B4C ??
DEF(second_ext_for_dng, 0xA0B8) // .THM

DEF(canon_shoot_menu_active,0x8325)  // indirectly found: 0x8328 in "taskcreate_DSITask", search for 0x8328-4, compare with a known one
DEF(canon_menu_active,0x917C)  // after "StartRecModeMenu", LDR R4, =0x9054
DEF(playrec_mode, 0x7044)  // in the first called f-n in task_SsStartupTask ok
DEF(recreview_hold, 0x7f4ec)  // (based on the a410 port)

DEF(levent_table, 0xFF96122C)
DEF(FlashParamsTable, 0xFF96ABDC)
DEF(focus_len_table, 0xfffe41f4)

DEF(sys_mempart_id, 0xf230) // memShow

DEF(active_bitmap_buffer, 0x7f3c0)
