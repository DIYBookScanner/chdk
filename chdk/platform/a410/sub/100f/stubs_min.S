#include "stubs_asm.h"

DEF(physw_status, 0x11F28) //
DEF(physw_run,  0x1FB0) //
DEF(zoom_busy, 0x80278) //
DEF(focus_busy, 0x80590) //
DEF(FlashParamsTable,0xFFD3BC1C) //
DEF(canon_menu_active,0x8720) //
//DEF(canon_ev_corr_menu_active, 0xD1C0) //missing from A610, so leave it out
// a430: DEF(canon_shoot_menu_active,0x7605) // (0x7608 - 0x4 + 0x1) found in "taskcreate_DSITask"
DEF(canon_shoot_menu_active,0x7A11) // 0x7a14 - 3 (???)
DEF(recreview_hold, 0x7D958) //
DEF(movie_status, 0x73ED4) // just a guess... @ffd1d208
DEF(zoom_status, 0x790C) // (in moveopticaltotele)
DEF(some_f_for_dng, 0x9464) // @ffdd743c
DEF(parameter_for_af_scan, 0x745D0) // @ffd27d28
DEF(some_flag_for_af_scan, 0x745D8) // @ffd27d5c
DEF(levent_table, 0xFFD32D98) // recognized it :)
DEF(playrec_mode, 0x6A08) // @MenuIn
DEF(sys_mempart_id, 0xF960) // unsure @calloc

