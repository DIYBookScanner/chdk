#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "conf.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"

#include "gui_hexbox.h"
#include "module_def.h"

//-------------------------------------------------------------------
int gui_hexbox_kbd_process();
void gui_module_menu_kbd_process();
void gui_hexbox_draw();

gui_handler GUI_MODE_HEXBOX =
    /*GUI_MODE_HEXBOX*/ { GUI_MODE_MODULE, gui_hexbox_draw, gui_hexbox_kbd_process, gui_module_menu_kbd_process, 0 };

static gui_handler *gui_hexbox_mode_old; // stored previous gui_mode
static int running = 0;
static int currpos = 7; // editing cursor position
static int hexbox_to_draw;
static int *num_to_edit;
static int num_backup;
static int hexbox_flags;
static char box_title[64];
static char box_helpline[64];
static int w, h, x, y;
static int offs_title, offs_num;

//-------------------------------------------------------
int hexbox_init(int *num, char *title, int flags)
{
    running = 1;

    gui_hexbox_mode_old = gui_set_mode( &GUI_MODE_HEXBOX );
    
    num_to_edit = num;
    num_backup = *num;
    hexbox_flags = flags;
    strncpy(box_title, title, 63);
    box_title[63] = 0;

    sprintf(box_helpline,"\x18\x19\x1b\x1a [SET]:%s [MENU]:%s",lang_str(LANG_MBOX_BTN_OK),lang_str(LANG_MBOX_BTN_CANCEL));
    int btl = strlen(box_title);
    int hll = strlen(box_helpline);
    if (btl < hll) btl = hll;
    w = ( btl + 4) * FONT_WIDTH;

    if (w > camera_screen.width - 4 * FONT_WIDTH) {
        w = camera_screen.width - 4 * FONT_WIDTH;
        box_title[(w/FONT_WIDTH - 4 < 63)?w/FONT_WIDTH - 4:63] = 0; // shorten the title
    }
    h = FONT_HEIGHT * 5;
    x = (camera_screen.width - w) >> 1;
    y = ((camera_screen.height - h)>>5)<<4;

    offs_title = ((camera_screen.width - strlen(box_title)*FONT_WIDTH)>>1)/FONT_WIDTH;
    offs_num = ((camera_screen.width - (10+6+1)*FONT_WIDTH)>>1)/FONT_WIDTH; // "0x12345678 4095M+"

    hexbox_to_draw = 1;

    return 1;
}

//-------------------------------------------------------

void edit_hex_digit(unsigned int* addr, int digsel, int increment) {
/*
 * addr: address of the 32bit integer under edit
 * digsel: selected digit (MSD=0, LSD=7)
 * increment: only the sign matters, or selected digit is zeroed if 0
*/
    register unsigned int a,b;
    a=( (*addr)&(0xf<<((7-digsel)*4)) )>>((7-digsel)*4);
    b=0xffffffff^(0xf<<((7-digsel)*4));
    if (increment<0) {
        if((digsel!=7)||!(hexbox_flags&HEXBOX_FLAG_WALIGN)) {
            if (a>0) {a-=1;} else {a=0xf;}
        }
        else {
            if (a>3) {a-=4;} else {a=0xc;}
        }
    }
    else if (increment>0) {
        if((digsel!=7)||!(hexbox_flags&HEXBOX_FLAG_WALIGN)) {
            if (a<0xf) {a+=1;} else {a=0;}
        }
        else {
            if (a<=0x8) {a+=4;} else {a=0;}
        }
    }
    else {
        a=0;
    }
    *addr=(a<<((7-digsel)*4))|( *addr&b );
}

void gui_hexbox_draw_hex32(unsigned int hexnum, int digit, unsigned int posx, unsigned int posy) {
/*
 * draws unsigned 32 bit hex integer
 * digit: digit under edit (0..7), -1 when not edited
 * posx: x position, posy: y position
*/
    char buf[12];
    digit += 2; // due to '0x'
    sprintf(buf, "0x%08X", hexnum);
    draw_txt_string(posx,posy, buf,  MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
    if ( (digit>=2)&&(digit<10) ) {
        draw_txt_char( posx+digit, posy, buf[digit], MAKE_COLOR(COLOR_RED, COLOR_WHITE));
    }
}

void gui_hexbox_draw_hint(unsigned int hexnum, unsigned int posx, unsigned int posy) {
/*
 * show a decimal hint about the entered value
*/
    char buf[12];
    if (hexnum > 1024*1024) {
        sprintf(buf, "%4dM%s", hexnum>>20, ((hexnum&0xfffff)>0)?"+":" " );
    }
    else if (hexnum > 1024) {
        sprintf(buf, "%4dk%s", hexnum>>10, ((hexnum&0x3ff)>0)?"+":" " );
    }
    else {
        sprintf(buf, "%4d  ", hexnum);
    }
    draw_txt_string(posx,posy, buf,  MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
}

//-------------------------------------------------------

void gui_hexbox_draw()
{
    switch (hexbox_to_draw) {
        case 1:
            draw_rect_shadow(x-3, y-3, x+w+5, y+h+5, COLOR_BLACK, 3);
            draw_filled_rect_thick(x-4, y-4, x+w+4, y+h+4, MAKE_COLOR(COLOR_GREY, COLOR_WHITE), 3);
            draw_filled_rect(x-2, y-2, x+w+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            draw_txt_string(offs_title, y/FONT_HEIGHT, box_title,  MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            draw_txt_string(x/FONT_WIDTH+2, y/FONT_HEIGHT+4, box_helpline,  MAKE_COLOR(COLOR_GREY, COLOR_WHITE));

            // fall through
        case 2:
            gui_hexbox_draw_hex32(*num_to_edit, currpos, offs_num, y / FONT_HEIGHT + 2);
            gui_hexbox_draw_hint(*num_to_edit, offs_num + 10 + 1, y / FONT_HEIGHT + 2);
            hexbox_to_draw = 0;
            break;
    }
}

//-------------------------------------------------------

int gui_hexbox_kbd_process()
{
    int need_redraw = 1;
    switch (kbd_get_autoclicked_key() | get_jogdial_direction()) {
        case KEY_UP:
        case JOGDIAL_RIGHT:
            edit_hex_digit((unsigned int*)num_to_edit, currpos, 1);
            break;
        case KEY_DOWN:
        case JOGDIAL_LEFT:
            edit_hex_digit((unsigned int*)num_to_edit, currpos, -1);
            break;
        case KEY_LEFT:
        //case KEY_ZOOM_OUT:
            currpos -= 1;
            break;
        case KEY_RIGHT:
        //case KEY_ZOOM_IN:
            currpos += 1;
            break;
        case KEY_SET:
            need_redraw = 0;
            gui_set_mode(gui_hexbox_mode_old);
            running = 0; // editing done
            break;
        case KEY_SHOOT_HALF:
            edit_hex_digit((unsigned int*)num_to_edit, currpos, 0); // zero current digit only
            break;
        case KEY_DISPLAY:
            *num_to_edit = 0; // zero the whole number
            currpos = 7;
            break;
        default:
            need_redraw = 0;
    }
    if (currpos > 7) currpos = 0;
    if (currpos < 0) currpos = 7;

    if (need_redraw) hexbox_to_draw = 2;
    return 0;
}

//-------------------------------------------------------

void gui_module_menu_kbd_process()
{
    *num_to_edit = num_backup; // edit cancelled
    running = 0;
    gui_default_kbd_process_menu_btn();
}


//==================================================

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    // free allocated resource, if any

    return 0;
}

int _module_can_unload()
{
    return running == 0;
}

int _module_exit_alt()
{
    *num_to_edit = num_backup; // edit cancelled
    running = 0;
    return 0;
}

/******************** Module Information structure ******************/

libhexbox_sym _libhexbox =
{
    {
         0, _module_unloader, _module_can_unload, _module_exit_alt, 0
    },

    hexbox_init,
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    GUI_HEXBOX_VERSION,          // Module version

    ANY_CHDK_BRANCH, 0,         // Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,       // Specify platform dependency

    (int32_t)"Hex number editor",// Module name
    0,

    &_libhexbox.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
