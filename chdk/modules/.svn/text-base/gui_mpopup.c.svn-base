#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"

#include "gui_mpopup.h"
#include "module_def.h"

/*
	History:	1.1 - make possible call next mpopup in callback [multilevel mpopups]
				1.2 - allow to use MPOPUP_CANCEL item in the list
*/

int gui_mpopup_kbd_process();
void gui_mpopup_kbd_process_menu_btn();
void gui_mpopup_draw();

gui_handler GUI_MODE_MPOPUP_MODULE = 
    /*GUI_MODE_MPOPUP*/ { GUI_MODE_MPOPUP, gui_mpopup_draw, gui_mpopup_kbd_process, gui_mpopup_kbd_process_menu_btn, GUI_MODE_FLAG_NORESTORE_ON_SWITCH };

// Simple popup menu. No title, no separators, only processing items

//-------------------------------------------------------------------
static gui_handler              *gui_mpopup_mode_old;
static int                      running = 0;
static char                     mpopup_to_draw;

#define MAX_ACTIONS             10

struct mpopup_item* actions;

static int                      mpopup_actions[MAX_ACTIONS];    // Content of raised popupmenu
static int                      mpopup_actions_num;             // Num of items in raised popupmenu
static int                      mpopup_actions_active;          // Idx of current item (cursor)
static coord                    mpopup_actions_x, mpopup_actions_y;    // top-left coord of window
static unsigned int             mpopup_actions_w;               // width of window

typedef void (*mpopup_on_select_t)(unsigned int btn);
static mpopup_on_select_t mpopup_on_select;

//-------------------------------------------------------------------
void gui_mpopup_init(struct mpopup_item* popup_actions, const unsigned int flags, void (*on_select)(unsigned int actn)) 
{
    int i;

    running++;

    mpopup_actions_num = 0;
    actions = popup_actions;
    for (i=0; actions[i].flag && mpopup_actions_num<MAX_ACTIONS; ++i) {
        if (flags & MPOPUP_MASK & actions[i].flag)
            mpopup_actions[mpopup_actions_num++] = i;
		else if ( actions[i].flag==MPOPUP_CANCEL )
			mpopup_actions[mpopup_actions_num++] = i;
    }
    if (mpopup_actions_num == 0) {
        on_select(MPOPUP_CANCEL);
		return;
	}

    mpopup_actions_active = 0;

    mpopup_to_draw = 1;
    mpopup_on_select = on_select;
    gui_mpopup_mode_old = gui_set_mode(&GUI_MODE_MPOPUP_MODULE);
}

//-------------------------------------------------------------------
unsigned int gui_mpopup_result() {
    return actions[mpopup_actions[mpopup_actions_active]].flag;
}

//-------------------------------------------------------------------
static void gui_mpopup_draw_actions() {
    int i;
    coord y = mpopup_actions_y;
    color cl;

    for (i=0; i<mpopup_actions_num; ++i) {
        cl = MAKE_COLOR((mpopup_actions_active==i)?COLOR_RED:COLOR_GREY, (mpopup_actions_active==i)?COLOR_RED:COLOR_GREY);
        draw_filled_rect(mpopup_actions_x, y, mpopup_actions_x+mpopup_actions_w*FONT_WIDTH, y+FONT_HEIGHT-1, cl);
        cl = MAKE_COLOR((mpopup_actions_active==i)?COLOR_RED:COLOR_GREY, COLOR_WHITE);
        draw_string(mpopup_actions_x+FONT_WIDTH, y, lang_str(actions[mpopup_actions[i]].text), cl);
        y+=FONT_HEIGHT;
    }
}

//-------------------------------------------------------------------
void gui_mpopup_draw() {
    if (mpopup_to_draw) {
        int i;
        coord x=0, y=0;
        unsigned int w, h;

        w = 0;
        for (i=0; i<mpopup_actions_num; ++i) {
            h=strlen(lang_str(actions[mpopup_actions[i]].text));
            if (h > w) w=h;
        }
        w+=2;
        h = mpopup_actions_num;
    
        x = (camera_screen.width - w*FONT_WIDTH) / 2;
        y = (camera_screen.height - h*FONT_HEIGHT) / 2;
        draw_rect_shadow(x-3, y-3, x+w*FONT_WIDTH+5, y+h*FONT_HEIGHT+4, COLOR_BLACK, 3); //shadow
        draw_filled_rect_thick(x-4, y-4, x+w*FONT_WIDTH+4, y+h*FONT_HEIGHT+3, MAKE_COLOR(COLOR_GREY, COLOR_WHITE), 3); // main box
    
        mpopup_actions_x = x;
        mpopup_actions_y = y;
        mpopup_actions_w = w;

        gui_mpopup_draw_actions();
        mpopup_to_draw = 0;
    }
}

//-------------------------------------------------------------------
void exit_mpopup(int action)
{
    gui_set_mode(gui_mpopup_mode_old);

	mpopup_on_select_t on_select = mpopup_on_select;	// this could be reinited in callback
	mpopup_on_select=0;
    if (on_select) 
        on_select(action);

    running--;
}

//-------------------------------------------------------------------
void gui_mpopup_kbd_process_menu_btn()
{
	exit_mpopup(MPOPUP_CANCEL);		
}

int gui_mpopup_kbd_process()
{
    switch (kbd_get_clicked_key() | get_jogdial_direction()) {
    case JOGDIAL_LEFT:
    case KEY_UP:
        if (mpopup_actions_active > 0) --mpopup_actions_active;
        else mpopup_actions_active = mpopup_actions_num-1;
        gui_mpopup_draw_actions();
        break;
    case JOGDIAL_RIGHT:
    case KEY_DOWN:
        if (mpopup_actions_active < mpopup_actions_num-1) ++mpopup_actions_active;
        else mpopup_actions_active = 0;
        gui_mpopup_draw_actions();
        break;
    case KEY_LEFT:
        gui_mpopup_kbd_process_menu_btn();
        break;
    case KEY_SET:
		exit_mpopup(actions[mpopup_actions[mpopup_actions_active]].flag);		
        break;
    }
    return 0;
}

//-------------------------------------------------------------------

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    if (mpopup_on_select) 
        mpopup_on_select(MPOPUP_CANCEL);

    return 0;
}

int _module_can_unload()
{
    return running == 0;
}

int _module_exit_alt()
{
	exit_mpopup(MPOPUP_CANCEL);		
    running = 0;
    return 0;
}

/******************** Module Information structure ******************/

libmpopup_sym _libmpopup =
{
    {
         0, _module_unloader, _module_can_unload, _module_exit_alt, 0
    },

    gui_mpopup_init
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    GUI_MPOPUP_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Popup menu module",   // Module name
    0,

    &_libmpopup.base,

    ANY_VERSION,                // CONF version
    ANY_VERSION,                // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
