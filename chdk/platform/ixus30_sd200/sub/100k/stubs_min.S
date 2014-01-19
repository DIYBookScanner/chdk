#include "stubs_asm.h"

DEF(led_table, 0xBBA4) //@ffa62cc0
DEF(physw_status, 0x11738) //@ff830044 +0x10 (?)
DEF(canon_menu_active,0x7CE8) //@ff9d3098, OK
DEF(focus_len_table, 0xffd792e8)

//should be ok
DEF(zoom_busy, 0x6e1b0) //@ffa50594
DEF(zoom_status, 0x70a4) //@ff9965b0
        
//a bit unsure but might be ok
DEF(focus_busy, 0x6E408) //@ffa5ed68
DEF(movie_status, 0x67088) //@ff9363b8
DEF(FlashParamsTable, 0xff957ef4) //for sure

DEF(sys_mempart_id, 0xF39C) // @FFAC48C0
DEF(levent_table, 0xff9512ac) //should be ok

DEF(physw_run, 0x20e4) //just a feeling...
DEF(playrec_mode, 0x590C) // it's in "MenuIn", but not sure if this is what we need (0=pb mode, 1=rec mode, 2=review mode in rec)
DEF(recreview_hold, 0x6b7fc) //should be ok (found by comparing a410's code to this one, verified with debug display)

//FIXME: wrong!
DEF(canon_shoot_menu_active,0x68F1) //WRONG


