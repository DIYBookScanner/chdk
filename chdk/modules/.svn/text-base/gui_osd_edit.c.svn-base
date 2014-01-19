#include "camera_info.h"
#include "keyboard.h"
#include "histogram.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_usb.h"
#include "gui_space.h"
#include "gui_osd.h"

#include "module_def.h"
#include "simple_module.h"

//-------------------------------------------------------------------
typedef struct {
    int         title;
    OSD_pos     *pos;
    OSD_pos     size;
    OSD_scale   *scale;
} OSD_elem;

static OSD_elem osd[]={
    {LANG_OSD_LAYOUT_EDITOR_CLOCK,      &conf.clock_pos,        {5*FONT_WIDTH, FONT_HEIGHT},    &conf.clock_scale       },
    {LANG_OSD_LAYOUT_EDITOR_TEMP,       &conf.temp_pos,         {9*FONT_WIDTH, FONT_HEIGHT},    &conf.temp_scale        },
    {LANG_OSD_LAYOUT_EDITOR_RAW,        &conf.mode_raw_pos,     {7*FONT_WIDTH, FONT_HEIGHT},    &conf.mode_raw_scale    },
    {LANG_OSD_LAYOUT_EDITOR_BAT_ICON,   &conf.batt_icon_pos,    {28, 12},                       &conf.batt_icon_scale   },
    {LANG_OSD_LAYOUT_EDITOR_BAT_TEXT,   &conf.batt_txt_pos,     {5*FONT_WIDTH, FONT_HEIGHT},    &conf.batt_txt_scale    },
    {LANG_OSD_LAYOUT_EDITOR_SPACE_ICON, &conf.space_icon_pos,   {23, 15},                       &conf.space_icon_scale  },
    {LANG_OSD_LAYOUT_EDITOR_SPACE_TEXT, &conf.space_txt_pos,    {5*FONT_WIDTH, FONT_HEIGHT},    &conf.space_txt_scale   },
    {LANG_OSD_LAYOUT_EDITOR_SPACE_ICON, &conf.space_ver_pos,    {3, 50},                        &conf.space_ver_scale   },
    {LANG_OSD_LAYOUT_EDITOR_SPACE_ICON, &conf.space_hor_pos,    {50, 3},                        &conf.space_hor_scale   },
    {LANG_OSD_LAYOUT_EDITOR_USB_INFO,   &conf.usb_info_pos,     {31, 14},                       &conf.usb_info_scale    },  
    {LANG_OSD_LAYOUT_EDITOR_EV,         &conf.mode_ev_pos,      {12*FONT_WIDTH, FONT_HEIGHT},   &conf.mode_ev_scale     },
    {LANG_OSD_LAYOUT_EDITOR_EV_VIDEO,   &conf.ev_video_pos,     {70, 24},                       &conf.ev_video_scale    },
    {LANG_OSD_LAYOUT_EDITOR_VIDEO,      &conf.mode_video_pos,   {9*FONT_WIDTH, 4*FONT_HEIGHT},  &conf.mode_video_scale  },
    {LANG_OSD_LAYOUT_EDITOR_DOF_CALC,   &conf.dof_pos,          {23*FONT_WIDTH, 2*FONT_HEIGHT}, &conf.dof_scale         },
    {LANG_OSD_LAYOUT_EDITOR_HISTO,      &conf.histo_pos,        {HISTO_WIDTH+2, HISTO_HEIGHT},  &conf.histo_scale       },
    {LANG_OSD_LAYOUT_EDITOR_STATES,     &conf.mode_state_pos,   {12*FONT_WIDTH, 4*FONT_HEIGHT}, &conf.mode_state_scale  },
    {LANG_OSD_LAYOUT_EDITOR_MISC,       &conf.values_pos,       {9*FONT_WIDTH, 9*FONT_HEIGHT},  &conf.values_scale      },
    {0}
};

static int osd_to_draw;
static int curr_item;
static int step;

//-------------------------------------------------------------------
void gui_osd_draw()
{
    char osd_buf[64];

    if (osd_to_draw)
    {
        int i;
        draw_restore();
        libhisto->gui_osd_draw_histo(1);
        gui_draw_osd_elements(1,0);
        int xscale = osd[curr_item].scale->x ;
        if ( xscale == 0) xscale = 1 ;
        int yscale = osd[curr_item].scale->y ;
        if ( yscale == 0) yscale = 1 ;
        for (i=1; i<=2; ++i)
        {
            draw_rect((osd[curr_item].pos->x>=i)?osd[curr_item].pos->x-i:0, (osd[curr_item].pos->y>=i)?osd[curr_item].pos->y-i:0, 
                      (osd[curr_item].pos->x+(osd[curr_item].size.x)*xscale)+i-1, 
                      (osd[curr_item].pos->y+(osd[curr_item].size.y)*yscale)+i-1,
                      COLOR_GREEN);
        }
        sprintf(osd_buf, " %s:  x:%d y:%d s:%d f:%d:%d ", lang_str(osd[curr_item].title), osd[curr_item].pos->x, osd[curr_item].pos->y, step, xscale, yscale);
        draw_string(0, (osd[curr_item].pos->x<strlen(osd_buf)*FONT_WIDTH+4 && osd[curr_item].pos->y<FONT_HEIGHT+4)?camera_screen.height-FONT_HEIGHT:0,
                    osd_buf, MAKE_COLOR(COLOR_RED, COLOR_WHITE));
        osd_to_draw = 0;
    }
}

void osd_font_scale(int dir)   // -1=smaller only, 0=grow & wrap,  1=larger only
{
    int xscale, yscale ;

    xscale = osd[curr_item].scale->x ;
    yscale = osd[curr_item].scale->y ;
    switch ((xscale<<4)+yscale)
    {
        case 0x11 :
            if ( dir>=0) { xscale=2; yscale=1 ; }
            break ;
        case 0x21 :
            if ( dir>=0) { xscale=2; yscale=2; } else { xscale=1; yscale=1; }
            break ;
        case 0x22 :
            if ( dir>=0) { xscale=3; yscale=2; } else { xscale=2; yscale=1; }
            break ;
        case 0x32 :
            if ( dir>=0) { xscale=4; yscale=2; } else { xscale=2; yscale=2; }
            break ;
        case 0x42 :
            if ( dir>=0) { xscale=3; yscale=3; } else { xscale=3; yscale=2; }
            break ;
        case 0x33 :
            if ( dir>=0) { xscale=4; yscale=4; } else { xscale=4; yscale=2; }
            break ;
        case 0x44 :
            if      ( dir == -1) { xscale=3; yscale=3; }
        else if ( dir ==  0) { xscale=1; yscale=1; }
            break ;
        default :
            xscale=0; yscale=0 ;
            break ;
    }
    osd[curr_item].scale->x = xscale ;
    osd[curr_item].scale->y = yscale ;
    osd_to_draw = 1;
}

//-------------------------------------------------------------------
int gui_osd_kbd_process()
{
    switch (kbd_get_autoclicked_key())
    {
    case KEY_LEFT:
        if (osd[curr_item].pos->x > 0)
        {
            osd[curr_item].pos->x-=(osd[curr_item].pos->x>=step)?step:osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_RIGHT:
        if (osd[curr_item].pos->x < camera_screen.width-osd[curr_item].size.x)
        {
            osd[curr_item].pos->x+=(camera_screen.width-osd[curr_item].size.x-osd[curr_item].pos->x>step)?step:camera_screen.width-osd[curr_item].size.x-osd[curr_item].pos->x;
            osd_to_draw = 1;
        } else
            osd[curr_item].pos->x = camera_screen.width-osd[curr_item].size.x;
        break;
    case KEY_UP:
        if (osd[curr_item].pos->y > 0)
        {
            osd[curr_item].pos->y-=(osd[curr_item].pos->y>=step)?step:osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_DOWN:
        if (osd[curr_item].pos->y < camera_screen.height-osd[curr_item].size.y)
        {
            osd[curr_item].pos->y+=(camera_screen.height-osd[curr_item].size.y-osd[curr_item].pos->y>step)?step:camera_screen.height-osd[curr_item].size.y-osd[curr_item].pos->y;
            osd_to_draw = 1;
        } else
            osd[curr_item].pos->y = camera_screen.height-osd[curr_item].size.y;
        break;
    case KEY_SET:
        ++curr_item;
        if ((osd[curr_item].title == LANG_OSD_LAYOUT_EDITOR_EV_VIDEO) && !camera_info.cam_ev_in_video) curr_item++;
        if (!osd[curr_item].pos) 
            curr_item = 0;
        osd_to_draw = 1;
        break;
    case KEY_DISPLAY:
        step=(step==1)?10:1;
        osd_to_draw = 1;
        break;
    case KEY_SHOOT_HALF:
        osd_font_scale(0) ;
        break;
    case KEY_ZOOM_IN:
        osd_font_scale(1) ;
        break;
    case KEY_ZOOM_OUT:
        osd_font_scale(-1) ;
        break;
    }
    return 0;
}

static int running = 0;

void gui_osd_menu_kbd_process()
{
    running = 0;
    gui_default_kbd_process_menu_btn();
}

//-------------------------------------------------------------------

gui_handler layoutGuiHandler =
{
    // THIS IS OSD LAYOUT EDITOR
    GUI_MODE_OSD, gui_osd_draw, gui_osd_kbd_process, gui_osd_menu_kbd_process, GUI_MODE_FLAG_NODRAWRESTORE
};

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
**************************************************************/

int _run()
{
    running = 1;

    osd_to_draw = 1;
    curr_item = 0;
    step = 10;

    gui_set_mode(&layoutGuiHandler);

    return 0;
}

int _module_can_unload()
{
    return running == 0;
}

int _module_exit_alt()
{
    running = 0;
    return 0;
}

/******************** Module Information structure ******************/

libsimple_sym _librun =
{
    {
         0, 0, _module_can_unload, _module_exit_alt, _run
    }
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"OSD Editor",		// Module name
    0,

    &_librun.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
