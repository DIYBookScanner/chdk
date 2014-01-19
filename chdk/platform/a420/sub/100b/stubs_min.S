#include "stubs_asm.h"

DEF(physw_status, 0xF838) //a420 ok
DEF(physw_run,  0x1FAC) //a420 i think ok
DEF(zoom_busy, 0x7CAA8) //a420 ok
DEF(focus_busy, 0x7CDC0) //a420 ok
DEF(FlashParamsTable,0xFFD3ADB0) //a420
DEF(canon_menu_active,0x7D54) //a420 ok
DEF(canon_ev_corr_menu_active, 0xD1C0) //a420 unsure... a430: 0xd5d8 @ffeb0cd0, a420 @ffea189c
DEF(canon_shoot_menu_active,0x7375) // a420, may be wrong (0x7374+1)
DEF(recreview_hold, 0x7A148) // a420 @FFD6DEC4
DEF(movie_status, 0x7207C) // a420 0xFFD1BE54, has to be ok
DEF(zoom_status, 0x7228) // a420 ok (in moveopticaltotele)
DEF(some_f_for_dng, 0x8884) // a420 found @ffe06f0c
DEF(some_flag_for_af_scan, 0x726C8) // a420 @FFD269B8
DEF(levent_table, 0xFFD31BA0) // a420 @ffd346d4
DEF(playrec_mode, 0x6108) // a420 @ffd2ed68, has to be ok
DEF(sys_mempart_id, 0xD230) // a420 @ffe9c88c, has to be ok

