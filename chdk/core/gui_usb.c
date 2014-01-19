#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "gui_draw.h"
#include "gui_usb.h"

//-------------------------------------------------------------------
void gui_usb_draw_icon() {
    register coord xx, yy;

    xx = conf.usb_info_pos.x;
    yy = conf.usb_info_pos.y;

    color cl1 = COLOR_BG;
    color cl2 = COLOR_GREY;
    color cl3 = COLOR_YELLOW;

    // usb icon
    draw_filled_round_rect(xx+3, yy+11, xx+29, yy+14, MAKE_COLOR(cl1, cl1));
    draw_filled_round_rect(xx,   yy,    xx+31, yy+11, MAKE_COLOR(cl1, cl1));
    
    draw_filled_rect(xx+2,       yy+1,  xx+29, yy+2,  MAKE_COLOR(cl2, cl2));
    
    draw_filled_rect(xx+1,       yy+2,  xx+2,  yy+8,  MAKE_COLOR(cl2, cl2));
    draw_filled_rect(xx+29,      yy+2,  xx+30, yy+8,  MAKE_COLOR(cl2, cl2));
    
    draw_filled_rect(xx+5,       yy+5,  xx+26, yy+8,  MAKE_COLOR(cl2, cl2));
    
    draw_filled_rect(xx+7,       yy+7,  xx+9,  yy+8,  MAKE_COLOR(cl3, cl3));
    draw_filled_rect(xx+12,      yy+7,  xx+14, yy+8,  MAKE_COLOR(cl3, cl3));
    draw_filled_rect(xx+17,      yy+7,  xx+19, yy+8,  MAKE_COLOR(cl3, cl3));
    draw_filled_rect(xx+22,      yy+7,  xx+24, yy+8,  MAKE_COLOR(cl3, cl3));
    
    draw_filled_rect(xx+2,       yy+9,  xx+3,  yy+10, MAKE_COLOR(cl2, cl2));
    draw_filled_rect(xx+28,      yy+9,  xx+29, yy+10, MAKE_COLOR(cl2, cl2));
    
    draw_filled_rect(xx+3,       yy+11, xx+4,  yy+12, MAKE_COLOR(cl2, cl2));
    draw_filled_rect(xx+27,      yy+11, xx+28, yy+12, MAKE_COLOR(cl2, cl2));
    
    draw_filled_rect(xx+5,       yy+12, xx+26, yy+13, MAKE_COLOR(cl2, cl2));
}
//-------------------------------------------------------------------
static void gui_usb_draw_text(){
    color cl = conf.osd_color;
    draw_string(conf.usb_info_pos.x, conf.usb_info_pos.y, "<USB>", cl);
}
//--------------------------------------------------------------------
void gui_usb_draw_osd(int is_osd_edit)
{
    if ((conf.usb_info_enable == 1 && conf.remote_enable) || is_osd_edit)
        gui_usb_draw_icon();
    else if ((conf.usb_info_enable == 2 && conf.remote_enable) || is_osd_edit)
        gui_usb_draw_text();
}
