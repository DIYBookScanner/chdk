#include "platform.h"
#include "touchscreen.h"
#include "conf.h"
#include "font.h"
#include "lang.h"
#include "fileutil.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_user_menu.h"
#include "gui_mbox.h"
#include "gui_hexbox.h"
#include "gui_osd.h"
#include "console.h"
#include "raw.h"
#include "modules.h"
#include "levent.h"
#include "callfunc.h"
#ifdef CAM_HAS_GPS
#include "gps.h"
#endif
#include "usb_remote.h"
#include "module_load.h"
#include "clock.h"
#include "eyefi.h"

// splash screen time
#if defined(OPT_EXPIRE_TEST)
#warning OPT_EXPIRE_TEST enabled
#define SPLASH_TIME 40  // Displays for 3.2 seconds
#else
#define SPLASH_TIME 20  // Displays for 1.6 seconds
                        // gui_redraw called every 4th loop of core_spytask which has 20ms delay per loop = (4*20) * 20 = 1600ms
#endif

//-------------------------------------------------------------------
// forward declarations
extern void schedule_memdump();

//-------------------------------------------------------------------

// for memory info, duplicated from lowlevel
extern const char _start,_end;

#ifdef OPT_DEBUGGING
#ifndef CAM_DRYOS
    int debug_tasklist_start;
#endif
    int debug_display_direction=1;
#endif

//-------------------------------------------------------------------

int script_run_on_alt_flag ;

int gui_user_menu_flag;

static char buf[256];

//-------------------------------------------------------------------
// Menu definitions 
//-------------------------------------------------------------------

//-------------------------------------------------------------------

/*
common code for "enum" menu items that just take a list of string values and don't require any special setters
would be better to have another menu item type that does this by default
save memory by eliminating dupe code
*/
void gui_enum_value_change(int *value, int change, unsigned num_items) {
    *value+=change;
    if (*value<0)
        *value = num_items-1;
    else if (*value>=num_items)
        *value = 0;
}

static const char* gui_change_simple_enum(int* value, int change, const char** items, unsigned num_items) {
    gui_enum_value_change(value, change, num_items);
    return items[*value];
}

const char* gui_change_enum2(const CMenuItem *menu_item, int change)
{
    const char** items = (const char**)menu_item->arg;
    gui_enum_value_change(menu_item->value, change, menu_item->opt_len);
    return items[*menu_item->value];
}

//-------------------------------------------------------------------

static const char* gui_bracket_values_modes[] = { "Off", "1/3 Ev","2/3 Ev", "1 Ev", "1 1/3Ev", "1 2/3Ev", "2 Ev", "2 1/3Ev", "2 2/3Ev", "3 Ev", "3 1/3Ev", "3 2/3Ev", "4 Ev" };
static const char* gui_bracket_type_modes[] =   { "+/-", "-", "+", "-/+" };

#if CAM_CAN_SD_OVERRIDE
static CMenuItem sd_bracket[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.subj_dist_bracket_value,  MENU_MINMAX(0, 30000) ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.subj_dist_bracket_koef,   0 ),
};
#endif

static CMenuItem iso_bracket[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.iso_bracket_value,        MENU_MINMAX(0, 10000) ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.iso_bracket_koef,         0 ),
};

static CMenuItem bracketing_in_continuous_submenu_items[] = {
    MENU_ENUM2  (0x63,LANG_MENU_TV_BRACKET_VALUE,           &conf.tv_bracket_value,         gui_bracket_values_modes ),
#if CAM_HAS_IRIS_DIAPHRAGM
    MENU_ENUM2  (0x62,LANG_MENU_AV_BRACKET_VALUE,           &conf.av_bracket_value,         gui_bracket_values_modes ),
#endif
#if CAM_CAN_SD_OVERRIDE
    MENU_ITEM   (0x5e,LANG_MENU_SUBJ_DIST_BRACKET_VALUE,    MENUITEM_STATE_VAL_PAIR,        &sd_bracket,                        100 ),
#endif
    MENU_ITEM   (0x74,LANG_MENU_ISO_BRACKET_VALUE,          MENUITEM_STATE_VAL_PAIR,        &iso_bracket,                       10 ),
    MENU_ENUM2  (0x60,LANG_MENU_BRACKET_TYPE,               &conf.bracket_type,             gui_bracket_type_modes ),
    MENU_ITEM   (0x5b,LANG_MENU_CLEAR_BRACKET_VALUES,       MENUITEM_BOOL,                  &conf.clear_bracket,                0 ),
    MENU_ITEM   (0x5c,LANG_MENU_BRACKETING_ADD_RAW_SUFFIX,  MENUITEM_BOOL,                  &conf.bracketing_add_raw_suffix,    0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                    0,                                  0 ),
    {0}
};
static CMenu bracketing_in_continuous_submenu = {0x2c,LANG_MENU_BRACKET_IN_CONTINUOUS_TITLE, bracketing_in_continuous_submenu_items };

//-------------------------------------------------------------------

const char* gui_USB_switch_types[] = { "None","OnePush", "TwoPush", "CA-1" };								// note : make sure # of entries less than NUM_USB_INPUT_DRV in usb_remote.c
const char* gui_USB_control_modes[] = { "None", "Normal", "Quick", "Burst", "Bracket","Zoom", "Video" }; 	// note : make sure # of entries less than NUM_USB_MODULES in usb_remote.c

#ifndef CAM_REMOTE_USES_PRECISION_SYNC
static CMenuItem synch_delay[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_INT|MENUITEM_F_UNSIGNED,   &conf.synch_delay_value,        0 ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                      &conf.synch_delay_enable,       0 ),
};
#endif

static CMenuItem remote_submenu_items[] = {
    MENU_ITEM   (0x71,LANG_MENU_REMOTE_ENABLE,              MENUITEM_BOOL,                  &conf.remote_enable, 0),
    MENU_ENUM2  (0x5f,LANG_MENU_REMOTE_DEVICE,  	        &conf.remote_switch_type,       gui_USB_switch_types ),
    MENU_ENUM2  (0x5f,LANG_MENU_REMOTE_LOGIC,  	            &conf.remote_control_mode,      gui_USB_control_modes ),	
    MENU_ITEM   (0x0, LANG_MENU_REMOTE_OPTIONS,             MENUITEM_SEPARATOR,             0, 0 ), 
    MENU_ITEM   (0x5c,LANG_MENU_SYNCH_ENABLE,               MENUITEM_BOOL,                  &conf.synch_enable, 0),
 #ifndef CAM_REMOTE_USES_PRECISION_SYNC
    MENU_ITEM   (0x5e,LANG_MENU_SYNCH_DELAY_VALUE,          MENUITEM_STATE_VAL_PAIR,        &synch_delay,                       10 ),
 #endif
    MENU_ITEM   (0x5c,LANG_MENU_SCRIPT_START_ENABLE,        MENUITEM_BOOL,                  &conf.remote_enable_scripts, 0),
    MENU_ITEM   (0x2c,LANG_MENU_BRACKET_IN_CONTINUOUS,	    MENUITEM_SUBMENU,               &bracketing_in_continuous_submenu,  0 ),    
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP, 0, 0),
    {0}
};
static CMenu remote_submenu = {0x86,LANG_MENU_REMOTE_PARAM_TITLE, remote_submenu_items };

//-------------------------------------------------------------------

static const char* gui_autoiso_shutter_modes[] = { "Auto", "1/8s", "1/15s", "1/30s", "1/60s", "1/125s", "1/250s", "1/500s", "1/1000s" };

static const char* gui_autoiso2_shutter_modes[] = { "Off", "1/4s", "1/6s", "1/8s", "1/12s", "1/15s", "1/20s", "1/25s", "1/30s",  
                 	                                "1/40s", "1/50s", "1/60s", "1/80s", "1/100s", "1/125s", "1/160s", "1/250s", "1/500s", "1/1000s"}; 

static const char* gui_overexp_ev_modes[] = { "Off", "-1/3 Ev", "-2/3 Ev", "-1 Ev", "-1 1/3Ev", "-1 2/3Ev", "-2 Ev" };

static CMenuItem autoiso_submenu_items[] = {
    MENU_ITEM   (0x5c,LANG_MENU_AUTOISO_ENABLED,            MENUITEM_BOOL,                                      &conf.autoiso_enable,           0 ),
    MENU_ENUM2	(0x5f,LANG_MENU_AUTOISO_MIN_SHUTTER,        &conf.autoiso_shutter_enum,                         gui_autoiso_shutter_modes ),
    MENU_ITEM   (0x5f,LANG_MENU_AUTOISO_USER_FACTOR,        MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_user_factor,      MENU_MINMAX(1, 8) ),

#if CAM_HAS_IS
    MENU_ITEM   (0x5f,LANG_MENU_AUTOISO_IS_FACTOR,          MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_is_factor,        MENU_MINMAX(1, 8) ),
#endif

    MENU_ITEM   (0x5f,LANG_MENU_AUTOISO_MIN_ISO,            MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_min_iso,          MENU_MINMAX(10, 200) ),
    MENU_ITEM	(0x5f,LANG_MENU_AUTOISO_MAX_ISO_AUTO,       MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_max_iso_auto,     MENU_MINMAX(10, 3200) ),

#if CAM_HAS_HI_ISO_AUTO_MODE
    MENU_ITEM   (0x5f,LANG_MENU_AUTOISO_MAX_ISO_HI,         MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_max_iso_hi,       MENU_MINMAX(200, 3200) ),
#endif

    MENU_ENUM2  (0x5f,LANG_MENU_AUTOISO_MIN_SHUTTER2,       &conf.autoiso2_shutter_enum,                        gui_autoiso2_shutter_modes ), 
    MENU_ITEM	(0x5f,LANG_MENU_AUTOISO_MAX_ISO2,           MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso2_max_iso_auto,	MENU_MINMAX(100, 3200) ),

    MENU_ENUM2	(0x5f,LANG_MENU_AUTOISO_OVEREXP_EV,        &conf.overexp_ev_enum, gui_overexp_ev_modes ),
    MENU_ITEM	(0x57,LANG_MENU_ZEBRA_OVER,                MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso2_over,    		MENU_MINMAX(0, 32) ),
    MENU_ITEM	(0x5f,LANG_MENU_AUTOISO_OVEREXP_THRES,     MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.overexp_threshold, 	MENU_MINMAX(1, 20) ),

    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,    0,                                                              0 ),
    {0}
};

static CMenu autoiso_submenu = {0x2d,LANG_MENU_AUTOISO_TITLE, autoiso_submenu_items };

//-------------------------------------------------------------------
#if OPT_EXPIRE_TEST

static int exp_text_width, exp_text_height;

static const char *exp_text[] =
{
    "  Test version expired  ",
    "Please post feedback to:",
    "  chdk.setepontos.com   ",
    "Your comments are needed",
    "to finish this port.    ",
    "Thanks                  "
};

#define EXP_TEXT_WIDTH   32
#define EXP_TEXT_HEIGHT  6
int get_expire_days_left(void) {
    time_t ts = time(NULL);
    if(ts > OPT_EXPIRE_TEST) {
        return 0;
    }
    return (OPT_EXPIRE_TEST - ts)/(60*60*24);
}

void do_expire_check() {
    if(get_expire_days_left()) {
        return;
    }
    static int in_splash = SPLASH_TIME;


    if(in_splash)
    {
        in_splash--;
        return;
    }

    color cl;
    if (camera_info.state.gui_mode_alt) {
        cl=MAKE_COLOR(COLOR_RED, COLOR_WHITE);
        gui_reset_alt_helper(); // replace the helper with nag screen
    } else if (camera_info.state.gui_mode_none) {
        cl=MAKE_COLOR(COLOR_TRANSPARENT, COLOR_WHITE);
    } else {
        return;
    }
    coord x, y;
    exp_text_width  = EXP_TEXT_WIDTH * FONT_HEIGHT + 8;
    exp_text_height = EXP_TEXT_HEIGHT * FONT_WIDTH + 10;

    x = (camera_screen.width-exp_text_width)>>1;
    y = ((camera_screen.height-exp_text_height)>>1) - 60;

    int i;
    for (i=0; i<EXP_TEXT_HEIGHT; i++)
    {
        draw_string(x+((exp_text_width-strlen(exp_text[i])*FONT_WIDTH)>>1), y+i*FONT_HEIGHT+4, exp_text[i], cl);
        // outside of alt, just show the "expired" line
        if (!camera_info.state.gui_mode_alt) {
            break;
        }
    }
}

void do_expire_splash(int x,int y) {
    static char under_dev_text[64];
    int days_left = get_expire_days_left();
    color cl = MAKE_COLOR(COLOR_RED, COLOR_WHITE);
    if(days_left) {
        sprintf(under_dev_text, "TEST BUILD %d DAYS LEFT",days_left);
    } else {
        sprintf(under_dev_text, "TEST BUILD EXPIRED!");
    }
    draw_string(x-((strlen(under_dev_text)*FONT_WIDTH)>>1), y, under_dev_text, cl);
}

#endif

#ifdef OPT_DEBUGGING

static void gui_compare_props(int arg)
{
	#define NUM_PROPS 512
	// never freed, but not allocated unless prop compare is used once
	static int *props = NULL;
	char buf[64];
	int i;
	int p;
	int c;

	if( props )
	{ // we have previous data set! do a comparison
		c = 0;
		for( i = 0; i < NUM_PROPS; ++i )
		{
			p = shooting_get_prop(i);
			if( props[i] != p )
			{
				++c;
				sprintf(buf,"%4d is %8d was %8d",i,p,props[i]);
				draw_string(16,16*c,buf,MAKE_COLOR(COLOR_BLACK,COLOR_YELLOW));
			}
			props[i] = p;
			if( c == 12 )
			{
				++c;
				sprintf(buf,"%s","Waiting 15 Seconds");
				draw_string(16,16*c,buf,MAKE_COLOR(COLOR_BLACK,COLOR_YELLOW));
				msleep(15000);
				c = 0;
			}
		}
		++c;
		sprintf(buf,"%s","Press <ALT> to leave");
		draw_string(16,16*c,buf,MAKE_COLOR(COLOR_BLACK,COLOR_YELLOW));
	}
	else
	{
	// no previous data was set so we save the data initially
		props = (int *)malloc(NUM_PROPS*sizeof(int));
		if(props) {
			for( i = 0; i < NUM_PROPS; ++i )
			{
				props[i] = shooting_get_prop(i);
			}
		}
	}
}

// Save camera romlog to A/ROMLOG.LOG file
static void save_romlog(int arg)
{
    extern unsigned _ExecuteEventProcedure(const char *name,...);

    if (stat("A/ROMLOG.LOG",0)    == 0) remove("A/ROMLOG.LOG");
    if (stat("A/RomLogErr.txt",0) == 0) remove("A/RomLogErr.txt");

    unsigned args[3];
    args[0] = (unsigned)"SystemEventInit";
    if (call_func_ptr(_ExecuteEventProcedure,args,1) == -1)
    {
        args[0] = (unsigned)"System.Create";
        if (call_func_ptr(_ExecuteEventProcedure,args,1) == -1)
        {
            gui_mbox_init(LANG_ERROR, LANG_SAVE_ROMLOG_INIT_ERROR, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
            return;
        }
    }

    args[0] = (unsigned)"GetLogToFile";
    args[1] = (unsigned)"A/ROMLOG.LOG";
    args[2] = 1;
    if (call_func_ptr(_ExecuteEventProcedure,args,3) == -1)
    {
        gui_mbox_init(LANG_ERROR, LANG_SAVE_ROMLOG_FAIL, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
    }
    else
    {
        gui_mbox_init(LANG_INFORMATION, LANG_SAVE_ROMLOG_OK, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
    }
}

static const char* gui_debug_shortcut_modes[] =             { "None", "DmpRAM", "Page", "CmpProps"};
#ifdef CAM_DRYOS
static const char* gui_debug_display_modes[] =              { "None", "Props", "Params" };
#else
static const char* gui_debug_display_modes[] =              { "None", "Props", "Params", "Tasks"};
#endif

extern volatile int memdmp_delay; // from core/main.c

static void gui_menu_edit_hexa_value(int val) {
    if (val == 1) {
        libhexbox->hexbox_init( &conf.memdmp_start, lang_str(LANG_MENU_DEBUG_MEMDMP_START), HEXBOX_FLAG_WALIGN );
    }
    else if (val == 2) {
        libhexbox->hexbox_init( &conf.memdmp_size, lang_str(LANG_MENU_DEBUG_MEMDMP_SIZE), HEXBOX_FLAG_WALIGN );
    }
}

static CMenuItem memdmp_submenu_items[] = {
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_MEMDMP_START,         MENUITEM_PROC,                  gui_menu_edit_hexa_value,           1),
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_MEMDMP_SIZE,          MENUITEM_PROC,                  gui_menu_edit_hexa_value,           2),
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_MEMDMP_DELAY,         MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &memdmp_delay, MENU_MINMAX(0, 10)   ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                    0,                                  0 ),
    {0}
};

static CMenu memdmp_submenu = {0x2a,LANG_MENU_DEBUG_MEMDMP, memdmp_submenu_items };

static CMenuItem debug_submenu_items[] = {
    MENU_ENUM2  (0x5c,LANG_MENU_DEBUG_DISPLAY,              &conf.debug_display,            gui_debug_display_modes ),
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_PROPCASE_PAGE,        MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &conf.debug_propcase_page, MENU_MINMAX(0, 128) ),
#ifndef CAM_DRYOS
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_TASKLIST_START,       MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &debug_tasklist_start, MENU_MINMAX(0, 63) ),
#endif
    MENU_ITEM   (0x5c,LANG_MENU_DEBUG_SHOW_MISC_VALS,       MENUITEM_BOOL,                  &conf.debug_misc_vals_show,         0 ),
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_MEMORY_BROWSER,       MENUITEM_PROC,                  module_run,             "memview.flt" ),
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_BENCHMARK,            MENUITEM_PROC,                  module_run,             "benchm.flt" ),
    MENU_ENUM2  (0x5c,LANG_MENU_DEBUG_SHORTCUT_ACTION,      &conf.debug_shortcut_action,    gui_debug_shortcut_modes ),
    MENU_ITEM   (0x2a,LANG_MENU_DEBUG_MEMDMP,               MENUITEM_SUBMENU,               &memdmp_submenu,                    0 ),
    MENU_ITEM   (0x2a,LANG_SAVE_ROMLOG,                     MENUITEM_PROC,                  save_romlog,                        0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                    0,                                  0 ),
    {0}
};

static CMenu debug_submenu = {0x2a,LANG_MENU_DEBUG_TITLE, debug_submenu_items };

#endif

//-------------------------------------------------------------------

#ifdef CAM_HAS_GPS

// forward reference
static CMenuItem gps_submenu_items[];

int exit_gpx_record=1;
int exit_gps_kompass=1;
int exit_gps_navi=1;

static void gpx_start_stop(int arg)
{
    int i = 0;
    while( gps_submenu_items[i].value != (int*)gpx_start_stop ) i++;    //find entry
    if( gps_submenu_items[i].text == LANG_MENU_GPS_TRACK_START ) {  //toggle text
        gps_submenu_items[i].text = LANG_MENU_GPS_TRACK_STOP;
		exit_gpx_record = 0;
		init_gpx_record_task();

    } else {
        gps_submenu_items[i].text = LANG_MENU_GPS_TRACK_START;
		exit_gpx_record = 1;
    }
}

static void show_kompass(int arg)
{
    int i = 0;
    while( gps_submenu_items[i].value != (int*)show_kompass ) i++;    //find entry
    if( gps_submenu_items[i].text == LANG_MENU_GPS_KOMPASS_SHOW ) {  //toggle text
        gps_submenu_items[i].text = LANG_MENU_GPS_KOMPASS_HIDE;
		exit_gps_kompass = 0;
		init_gps_kompass_task();

    } else {
        gps_submenu_items[i].text = LANG_MENU_GPS_KOMPASS_SHOW;
		exit_gps_kompass = 1;
    }
}

static void show_navi(int arg)
{
    int i = 0;
    while( gps_submenu_items[i].value != (int*)show_navi ) i++;    //find entry
    if( gps_submenu_items[i].text == LANG_MENU_GPS_NAVI_SHOW ) {  //toggle text
        gps_submenu_items[i].text = LANG_MENU_GPS_NAVI_HIDE;
		exit_gpx_record = 0;
		exit_gps_navi = 0;
		exit_gps_kompass = 0;
		init_gps_trackback_task();

    } else {
        gps_submenu_items[i].text = LANG_MENU_GPS_NAVI_SHOW;
		exit_gps_navi = 1;
		exit_gps_kompass = 1;
		exit_gpx_record = 1;
    }
}

static void navigate_home(int arg)
{
	int i = 0;
    while( gps_submenu_items[i].value != (int*)navigate_home ) i++;    //find entry
    if( gps_submenu_items[i].text == LANG_MENU_GPS_NAVI_HOME ) {  //toggle text
        gps_submenu_items[i].text = LANG_MENU_GPS_NAVI_HOME_END;
		exit_gpx_record = 0;
		exit_gps_navi = 0;
		exit_gps_kompass = 0;
		gps_navigate_home();

    } else {
        gps_submenu_items[i].text = LANG_MENU_GPS_NAVI_HOME;
		exit_gps_navi = 1;
		exit_gps_kompass = 1;
		exit_gpx_record = 1;
    }
}

static void mark_timezone(int arg)
{
    write_timezone();
}

static void mark_home(int arg)
{
    write_home();
}

static CMenuItem gps_logging_items[] = {
    MENU_ITEM	(0x2a,LANG_MENU_GPS_TRACK_TIME,				MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_track_time, 		MENU_MINMAX(1, 60) ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_TRACK_SYMBOL,			MENUITEM_BOOL,  									&conf.gps_track_symbol,		0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_REC_PLAY_SET_1,			MENUITEM_BOOL,          							&conf.gps_rec_play_set_1,	0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_REC_PLAY_TIME_1,		MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_rec_play_time_1,	MENU_MINMAX(1, 60) ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_PLAY_DARK_SET_1,		MENUITEM_BOOL,          							&conf.gps_play_dark_set_1,	0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_PLAY_DARK_TIME_1,		MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_play_dark_time_1,	MENU_MINMAX(1, 60) ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                        				0,							0 ),
    {0}
};

static CMenu gps_logging_submenu = {0x86,LANG_MENU_GPS_LOGGING, gps_logging_items };

static CMenuItem gps_tagging_items[] = {
    MENU_ITEM	(0x5c,LANG_MENU_GPS_WAYPOINT_SAVE,          MENUITEM_BOOL,          		                    &conf.gps_waypoint_save,	0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM   (0x2a,LANG_MENU_GPS_WAIT_FOR_SIGNAL,		MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_wait_for_signal,	MENU_MINMAX(1, 599) ),
    MENU_ITEM   (0x2a,LANG_MENU_GPS_WAIT_FOR_SIGNAL_TIME,	MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_wait_for_signal_time,	MENU_MINMAX(1, 60) ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_REC_PLAY_SET,			MENUITEM_BOOL,          							&conf.gps_rec_play_set,		0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_REC_PLAY_TIME,			MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_rec_play_time,	MENU_MINMAX(1, 60) ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_PLAY_DARK_SET,			MENUITEM_BOOL,          							&conf.gps_play_dark_set,	0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_PLAY_DARK_TIME,			MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_play_dark_time,	MENU_MINMAX(1, 60) ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x5c,LANG_MENU_GPS_COUNTDOWN,          	MENUITEM_BOOL,          							&conf.gps_countdown	,		0 ),
//    MENU_ITEM	(0x5c,LANG_MENU_GPS_COUNTDOWN_BLINK,      	MENUITEM_BOOL,          							&conf.gps_countdown_blink,	0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                        				0,							0 ),
    {0}
};

static CMenu gps_tagging_submenu = {0x86,LANG_MENU_GPS_TAGGING, gps_tagging_items };

static CMenuItem gps_navigation_items[] = {
    MENU_ITEM	(0x2a,LANG_MENU_GPS_KOMPASS_SMOOTH,			MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_kompass_smooth,	MENU_MINMAX(1, 40) ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_KOMPASS_TIME,			MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_kompass_time, 	MENU_MINMAX(1, 60) ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_NAVI_TIME,				MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_navi_time,		MENU_MINMAX(1, 60) ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_MARK_HOME,              MENUITEM_PROC,          		(int*)mark_home,					0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                        				0,							0 ),
    {0}
};

static CMenu gps_navigation_submenu = {0x86,LANG_MENU_GPS_NAVIGATION, gps_navigation_items };

static const char* gui_gps_sat_fix[] =                  { "immer", "2D", "3D", "2D/3D" };

static CMenuItem gps_values_items[] = {
    MENU_ITEM	(0x2a,LANG_MENU_GPS_BATT,					MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,	&conf.gps_batt,				MENU_MINMAX(0, 99) ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_BATT_WARNING,			MENUITEM_BOOL,  									&conf.gps_batt_warn,		0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_BEEP_WARNING,			MENUITEM_BOOL,  									&conf.gps_beep_warn,		0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ENUM2  (0x69,LANG_MENU_GPS_2D_3D_FIX,				&conf.gps_2D_3D_fix,   								gui_gps_sat_fix ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_SYMBOL_SHOW,			MENUITEM_BOOL,  									&conf.gps_show_symbol,		0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,									0,							0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_TEST_TIMEZONE,			MENUITEM_BOOL,  									&conf.gps_test_timezone,	0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_MARK_TIMEZONE,          MENUITEM_PROC,          		                    (int*)mark_timezone,		0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,				                    0,							0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                        				0,							0 ),
    {0}
};

static CMenu gps_values_submenu = {0x86,LANG_MENU_GPS_VALUES, gps_values_items };

static CMenuItem gps_submenu_items[] = {
    MENU_ITEM	(0x2a,LANG_MENU_GPS_ON_OFF,					MENUITEM_BOOL,  				&conf.gps_on_off,					0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,				0,									0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_KOMPASS_SHOW,           MENUITEM_PROC,  				(int*)show_kompass,					0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_NAVI_SHOW,              MENUITEM_PROC,          		(int*)show_navi,					0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_NAVI_HOME,              MENUITEM_PROC,          		(int*)navigate_home,				0 ),
    MENU_ITEM	(0x2a,LANG_MENU_GPS_TRACK_START,            MENUITEM_PROC,          		(int*)gpx_start_stop,				0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,				0,									0 ),
    MENU_ITEM   (0x2a,LANG_MENU_GPS_VALUES,               	MENUITEM_SUBMENU,               &gps_values_submenu,            	0 ),
    MENU_ITEM   (0x2a,LANG_MENU_GPS_LOGGING,               	MENUITEM_SUBMENU,               &gps_logging_submenu,            	0 ),
    MENU_ITEM   (0x2a,LANG_MENU_GPS_TAGGING,               	MENUITEM_SUBMENU,               &gps_tagging_submenu,            	0 ),
    MENU_ITEM   (0x2a,LANG_MENU_GPS_NAVIGATION,            	MENUITEM_SUBMENU,               &gps_navigation_submenu,            0 ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,				0,									0 ),
    MENU_ITEM	(0x51,LANG_MENU_BACK,                       MENUITEM_UP, 					0,                                  0 ),
    {0}
};

static CMenu gps_submenu = {0x2a,LANG_MENU_GPS, gps_submenu_items };

#endif

//-------------------------------------------------------------------

static void gui_draw_read_selected(const char *fn)
{
    if (fn)
    {
		libtxtread->read_file(fn);
    }
}

static void gui_draw_read(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_TEXT_FILE, conf.reader_file, "A/CHDK/BOOKS", gui_draw_read_selected);
}

static void gui_draw_read_last(int arg)
{
    if (stat(conf.reader_file,0) == 0)
        gui_draw_read_selected(conf.reader_file);
    else
        gui_draw_read(arg);
}

static void gui_draw_rbf_selected(const char *fn)
{
    if (fn) {
        strcpy(conf.reader_rbf_file, fn);
    }
}

static void gui_draw_load_rbf(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_FONT_FILE, conf.reader_rbf_file, "A/CHDK/FONTS", gui_draw_rbf_selected);
}

static const char* gui_reader_codepage_cps[] = { "Win1251", "DOS"};
static CMenuItem reader_submenu_items[] = {
    MENU_ITEM(0x35,LANG_MENU_READ_OPEN_NEW,           MENUITEM_PROC,    gui_draw_read, 0 ),
    MENU_ITEM(0x35,LANG_MENU_READ_OPEN_LAST,          MENUITEM_PROC,    gui_draw_read_last, 0 ),
    MENU_ITEM(0x35,LANG_MENU_READ_SELECT_FONT,        MENUITEM_PROC,    gui_draw_load_rbf, 0 ),
    MENU_ENUM2(0x5f,LANG_MENU_READ_CODEPAGE,          &conf.reader_codepage, gui_reader_codepage_cps ),
    MENU_ITEM(0x5c,LANG_MENU_READ_WORD_WRAP,          MENUITEM_BOOL,    &conf.reader_wrap_by_words, 0 ),
    MENU_ITEM(0x5c,LANG_MENU_READ_AUTOSCROLL,         MENUITEM_BOOL,    &conf.reader_autoscroll, 0 ),
    MENU_ITEM(0x5f,LANG_MENU_READ_AUTOSCROLL_DELAY,   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.reader_autoscroll_delay, MENU_MINMAX(0, 60) ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                    MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu reader_submenu = {0x37,LANG_MENU_READ_TITLE, reader_submenu_items };

//-------------------------------------------------------------------

static CMenuItem games_submenu_items[] = {
    MENU_ITEM(0x38,LANG_MENU_GAMES_REVERSI,           MENUITEM_PROC,  module_run, "reversi.flt" ),
    MENU_ITEM(0x38,LANG_MENU_GAMES_SOKOBAN,           MENUITEM_PROC,  module_run, "sokoban.flt" ),
    MENU_ITEM(0x38,LANG_MENU_GAMES_CONNECT4,          MENUITEM_PROC,  module_run, "4wins.flt" ),
    MENU_ITEM(0x38,LANG_MENU_GAMES_MASTERMIND,        MENUITEM_PROC,  module_run, "mastmind.flt" ),
    MENU_ITEM(0x38,"Snake" ,                          MENUITEM_PROC,  module_run, "snake.flt" ),
    MENU_ITEM(0x38,"Tetris",                          MENUITEM_PROC,  module_run, "tetris.flt" ),
	MENU_ITEM(0x38,"Sudoku",						  MENUITEM_PROC,  module_run, "sudoku.flt" ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                    MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu games_submenu = {0x38,LANG_MENU_GAMES_TITLE, games_submenu_items };

//-------------------------------------------------------------------

static void gui_menuproc_mkbootdisk(int arg)
{
    mark_filesystem_bootable();
    gui_mbox_init(LANG_INFORMATION, LANG_CONSOLE_TEXT_FINISHED, MBOX_BTN_OK|MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, NULL);
}

#if CAM_MULTIPART

static void card_break_proc(unsigned int btn)
{
    if (btn==MBOX_BTN_YES) create_partitions();
}

static void gui_menuproc_break_card(int arg)
{
    gui_mbox_init(LANG_WARNING, LANG_PARTITIONS_CREATE_WARNING, MBOX_BTN_YES_NO|MBOX_DEF_BTN2|MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, card_break_proc);
}

static char* partitions_enum=NULL;

static const char* gui_menuproc_swap_partitions_enum(int change, int arg)
{
    int new_partition;
    int partition_count = get_part_count();
    char vBuf[16];
    if(partitions_enum)
    {
      free(partitions_enum);
      partitions_enum=NULL;
    }
    new_partition= get_active_partition()+change;
    if( new_partition <=0)
    {
      new_partition = partition_count;
    }
    else if( new_partition > partition_count)
    {
      new_partition = 1;
    }  
    sprintf(vBuf,"%d/%d",new_partition, partition_count);
    partitions_enum=malloc((strlen(vBuf)+1)*sizeof(char));
    strcpy(partitions_enum,vBuf);

    if(change != 0)
    {
      swap_partitions(new_partition);
    }
    return partitions_enum;
}

#endif

static CMenuItem sdcard_submenu_items[] = {
    MENU_ITEM   (0x33,LANG_MENU_DEBUG_MAKE_BOOTABLE,        MENUITEM_PROC,                  gui_menuproc_mkbootdisk, 0 ),
#if CAM_MULTIPART
    MENU_ITEM   (0x33,LANG_MENU_DEBUG_CREATE_MULTIPART ,    MENUITEM_PROC,                  gui_menuproc_break_card,            0 ),
    MENU_ITEM   (0x33,LANG_MENU_DEBUG_SWAP_PART,            MENUITEM_ENUM,                  gui_menuproc_swap_partitions_enum,  0 ),
#endif
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                    0,                                  0 ),
    {0},
};

static CMenu sdcard_submenu = {0x33,LANG_SD_CARD, sdcard_submenu_items };

//-------------------------------------------------------------------

static void gui_delete_module_log_callback(unsigned int btn)
{
    if (btn == MBOX_BTN_YES)
        module_log_clear();
}

static void gui_delete_module_log(int arg)
{
    gui_mbox_init(LANG_WARNING, LANG_MENU_DELETE_MODULE_LOG, MBOX_BTN_YES_NO|MBOX_DEF_BTN2|MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, gui_delete_module_log_callback);
}

static CMenuItem module_submenu_items[] = {
    MENU_ITEM   (0x80,LANG_MENU_MODULE_INSPECTOR,           MENUITEM_PROC,                  module_run, "modinsp.flt" ),
    MENU_ITEM   (0x5c,LANG_MENU_MODULE_LOGGING,             MENUITEM_BOOL,                  &conf.module_logging, 0 ),
    MENU_ITEM   (0x2b,LANG_MENU_DELETE_MODULE_LOG,          MENUITEM_PROC,                  gui_delete_module_log, 0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                    0, 0 ),
    {0},
};

static CMenu module_submenu = {0x28,LANG_MENU_MODULES, module_submenu_items };

//-------------------------------------------------------------------

static void gui_draw_fselect(int arg)
{
    libfselect->file_select(LANG_STR_FILE_BROWSER, "A", "A", NULL);
}

static void gui_show_build_info(int arg)
{
    static char comp[64];

#ifdef __GNUC__
# ifndef __GNUC_PATCHLEVEL__
# define __GNUC_PATCHLEVEL 0
# endif
    sprintf(comp, "GCC %d.%d.%d", __GNUC__ ,__GNUC_MINOR__,__GNUC_PATCHLEVEL__ );
#else
    sprintf(comp, "UNKNOWN" );
#endif
    sprintf(buf, lang_str(LANG_MSG_BUILD_INFO_TEXT), camera_info.chdk_ver, camera_info.build_number, camera_info.build_svnrev, camera_info.build_date, camera_info.build_time, camera_info.platform, camera_info.platformsub, comp);
    gui_mbox_init(LANG_MSG_BUILD_INFO_TITLE, (int)buf, MBOX_FUNC_RESTORE|MBOX_TEXT_LEFT, NULL);
}

static void gui_show_memory_info(int arg)
{
    sprintf(buf, lang_str(LANG_MSG_MEMORY_INFO_TEXT), core_get_free_memory(), camera_info.memisosize, &_start, &_end);
    gui_mbox_init(LANG_MSG_MEMORY_INFO_TITLE, (int)buf, MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
}

#if !defined(OPT_FORCE_LUA_CALL_NATIVE)
static void lua_native_call_warning(unsigned int btn)
{
    if (btn==MBOX_BTN_NO)
        conf.script_allow_lua_native_calls = 0;
}

static void gui_lua_native_call_warning()
{
    if (conf.script_allow_lua_native_calls)
        gui_mbox_init(LANG_WARNING, LANG_MENU_LUA_NATIVE_CALLS_WARNING, MBOX_BTN_YES_NO|MBOX_DEF_BTN2|MBOX_TEXT_CENTER, lua_native_call_warning);
}
#endif

//-------------------------------------------------------------------

static struct mpopup_item popup_eyefi[32];
static char eyefi_selectedNetwork[65];
static char eyefi_password[65];

static void confirm_add_network_cb(unsigned int btn) {
	int n,i;
	char s[80];
	
	if (btn==MBOX_BTN_YES) {
		n=libeyefi->testNetwork(eyefi_selectedNetwork,eyefi_password);
		gui_browser_progress_show("testing network",5);
		for (i=0;i<30;i++) {
			msleep(10);			
			n=libeyefi->getNetworkStatus();
			sprintf(s,"%d %d",n,libeyefi->getBuf()[0]);
			console_add_line(s);
			if (libeyefi->getBuf()[0]==0) {
				gui_set_need_restore();
				gui_mbox_init(LANG_FAILED,LANG_WRONG_PASSWORD,MBOX_BTN_OK,NULL);
				libeyefi->close();
				return;
			}
			if (libeyefi->getBuf()[0]<=EYEFI_SUCCESS) {
				gui_browser_progress_show(libeyefi->statusName(libeyefi->getBuf()[0]),(libeyefi->getBuf()[0]*100)/(EYEFI_SUCCESS+1));
				if (libeyefi->getBuf()[0]==EYEFI_SUCCESS)
					break;
			}
			else
				gui_browser_progress_show("????",50);
		}
	}

	if (libeyefi->getBuf()[0]!=EYEFI_SUCCESS) {
		gui_set_need_restore();
		gui_mbox_init(LANG_FAILED,LANG_WRONG_PASSWORD,MBOX_BTN_OK,NULL);
		libeyefi->close();
		return;
	}
	
	gui_browser_progress_show("adding network",95);
	n=libeyefi->addNetwork(eyefi_selectedNetwork,eyefi_password);
	if (n>0)
		gui_mbox_init(LANG_SUCCESS,LANG_NETWORK_ADDED,MBOX_BTN_OK,NULL);
	else
		gui_mbox_init(LANG_FAILED,LANG_PROBLEM_ADDING_NETWORK,MBOX_BTN_OK,NULL);
	gui_set_need_restore();
	libeyefi->close();
}

static void password_cb(const char *str) {
	if (str==NULL) {
		libeyefi->close();
		return;
	}
	strncpy(eyefi_password,str,sizeof eyefi_password-1);
	gui_mbox_init(LANG_ADD_NETWORK,LANG_TEST_NETWORK,MBOX_BTN_YES_NO|MBOX_DEF_BTN1,confirm_add_network_cb);
}

static void select_available_network_cb(unsigned nSelected) {
	unsigned flag=1;
	int i,n;

	if (nSelected==MPOPUP_CANCEL) {
		libeyefi->close();
		gui_set_need_restore();
		return;
	}
	
	struct scanned_net *p=(struct scanned_net*)(libeyefi->getBuf()+1);
	n=libeyefi->getBuf()[0];
	for (i=0;i<n && i<32;i++,p++) {
		if (nSelected==flag) break;
		flag<<=1;
	}
	
	if (nSelected!=flag) {
		libeyefi->close();
		gui_mbox_init(LANG_ADD_NETWORK,LANG_CANNOT_FIND_NETWORK,MBOX_BTN_YES_NO|MBOX_DEF_BTN2,NULL);
		return;
	}
	
	strcpy(eyefi_selectedNetwork,p->essid);
	libtextbox->textbox_init((int)p->essid,LANG_PASSWORD,eyefi_password,32,password_cb, NULL);
}

static void gui_menuproc_eyefi_available_networks()
{
	unsigned flag=1,flags=0;
	int i,n;
	
	if (libeyefi->init()<=0) {
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NOT_ENOUGH_MEMORY,MBOX_BTN_OK,NULL);
		return;
	}
	
	if (libeyefi->getAvailableNetworks()<=0) {
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NO_EYEFI_CARD_FOUND,MBOX_BTN_OK,NULL);
		libeyefi->close();
		return;
	}
	
	memset(eyefi_selectedNetwork,0,sizeof eyefi_selectedNetwork);
	struct scanned_net *p=(struct scanned_net*)(libeyefi->getBuf()+1);
	n=libeyefi->getBuf()[0];
	
	if (n==0) {
		gui_mbox_init(LANG_ADD_NETWORK,LANG_CANNOT_FIND_NETWORK,MBOX_BTN_OK,NULL);
		libeyefi->close();
		return;
	}
	
	for (i=0;i<n && i<31;i++,p++) {
		popup_eyefi[i].text=(int)&(p->essid);
		popup_eyefi[i].flag=flag;
		flags|=flag;
		flag<<=1;
	}
	
	libmpopup->show_popup(popup_eyefi,flags,select_available_network_cb);
}

static void confirm_delete_network_cb(unsigned int btn) {
	if (btn==MBOX_BTN_YES) {
		int n=libeyefi->deleteNetwork(eyefi_selectedNetwork);
		gui_mbox_init(LANG_SUCCESS,n<=0?LANG_CANNOT_DELETE_NETWORK:LANG_NETWORK_DELETED,MBOX_BTN_OK,NULL);
	}
	libeyefi->close();
	gui_set_need_restore();
}

static void select_configured_network_cb(unsigned nSelected) {
	unsigned flag=1;
	int i;

	if (nSelected==MPOPUP_CANCEL) {
		libeyefi->close();
		gui_set_need_restore();
		return;
	}
	
	int n=libeyefi->getBuf()[0];
	for (i=0;i<n && i<32;i++) {
		if (nSelected==flag) break;
		flag<<=1;
	}
	
	static char s[80];
	if (nSelected!=flag) {
		libeyefi->close();
		gui_mbox_init(LANG_POPUP_DELETE,LANG_CANNOT_FIND_NETWORK,MBOX_BTN_YES_NO|MBOX_DEF_BTN2,confirm_delete_network_cb);
		return;
	}
	
	strcpy(eyefi_selectedNetwork,(char*)libeyefi->getBuf()+1+32*i);

	sprintf(s,"Delete \"%s\"?",eyefi_selectedNetwork);
	gui_mbox_init(LANG_POPUP_DELETE,(int)s/*LANG_ARE_YOU_SURE*/,MBOX_BTN_YES_NO|MBOX_DEF_BTN2,confirm_delete_network_cb);
}

static void gui_menuproc_eyefi_configured_networks()
{
	unsigned flag=1,flags=0;
	int i,n;
	if (libeyefi->init()<=0) {
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NOT_ENOUGH_MEMORY,MBOX_BTN_OK,NULL);
		return;
	}
	
	if (libeyefi->getConfiguredNetworks()<=0) {
		libeyefi->close();
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NO_EYEFI_CARD_FOUND,MBOX_BTN_OK,NULL);
		return;
	}

	memset(eyefi_selectedNetwork,0,sizeof eyefi_selectedNetwork);
	n=libeyefi->getBuf()[0];
	for (i=0;i<n && i<31;i++) {
		popup_eyefi[i].text=(int)(libeyefi->getBuf()+1+32*i);
		popup_eyefi[i].flag=flag;
		flags|=flag;
		flag<<=1;
	}
	
	libmpopup->show_popup(popup_eyefi,flags,select_configured_network_cb);
}

static void gui_menuproc_eyefi_wlan_off() {
	if (libeyefi->init()<=0) {
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NOT_ENOUGH_MEMORY,MBOX_BTN_OK,NULL);
		return;
	}

	int n=libeyefi->enableWlan(0);
	libeyefi->close();
	if (n<=0)
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NOT_ENOUGH_MEMORY,MBOX_BTN_OK,NULL);
	else
		gui_mbox_init(LANG_SUCCESS,LANG_EYEFI_WLAN_TURNED_OFF,MBOX_BTN_OK,NULL);
}

static void gui_menuproc_eyefi_wlan_on() {
	if (libeyefi->init()<=0) {
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NOT_ENOUGH_MEMORY,MBOX_BTN_OK,NULL);
		return;
	}
	
	int n=libeyefi->enableWlan(1);
	libeyefi->close();
	if (n<=0)
		gui_mbox_init(LANG_ERROR_INITIALIZING_EYEFI,LANG_NOT_ENOUGH_MEMORY,MBOX_BTN_OK,NULL);
	else
		gui_mbox_init(LANG_SUCCESS,LANG_EYEFI_WLAN_TURNED_ON,MBOX_BTN_OK,NULL);
}

static CMenuItem eyefi_submenu_items[] = {
    MENU_ITEM   (0x5c,LANG_MENU_EYEFI_AVAILABLE_NETWORKS,       MENUITEM_PROC,          gui_menuproc_eyefi_available_networks,         0 ),
    MENU_ITEM   (0x5c,LANG_MENU_EYEFI_CONFIGURED_NETWORKS,       MENUITEM_PROC,          gui_menuproc_eyefi_configured_networks,         0 ),
    MENU_ITEM   (0x5c,LANG_FORCE_EYEFI_WLAN_OFF,       MENUITEM_PROC,          gui_menuproc_eyefi_wlan_off,         0 ),
    MENU_ITEM   (0x5c,LANG_FORCE_EYEFI_WLAN_ON,       MENUITEM_PROC,          gui_menuproc_eyefi_wlan_on,         0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                                  0 ),
    {0}
};

static CMenu eyefi_submenu = {0x21,LANG_MENU_EYEFI_TITLE, eyefi_submenu_items };

//-------------------------------------------------------------------

static const char* gui_console_show_enum[]={ "ALT", "Always" };

static void gui_console_clear(int arg)
{
    console_close();
    gui_mbox_init(LANG_MENU_CONSOLE_CLEAR, LANG_MENU_CONSOLE_RESET, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}

static void gui_console_show(int arg)
{
    void display_console();
    display_console();
}

static CMenuItem console_settings_submenu_items[] = {
    MENU_ENUM2(0x5f,LANG_MENU_CONSOLE_SHOWIN,       &conf.console_show,         gui_console_show_enum ),
    MENU_ITEM(0x58,LANG_MENU_CONSOLE_TIMEOUT,       MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.console_timeout, MENU_MINMAX(3, 30) ),
    MENU_ITEM(0x35,LANG_MENU_CONSOLE_SHOW,          MENUITEM_PROC,              gui_console_show, 0 ),
    MENU_ITEM(0x35,LANG_MENU_CONSOLE_CLEAR,         MENUITEM_PROC,              gui_console_clear, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                  MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu console_settings_submenu = {0x28,LANG_MENU_CONSOLE_SETTINGS, console_settings_submenu_items };

static CMenuItem misc_submenu_items[] = {
    MENU_ITEM   (0x35,LANG_MENU_MISC_FILE_BROWSER,          MENUITEM_PROC,                  gui_draw_fselect,                   0 ),
    MENU_ITEM   (0x28,LANG_MENU_MODULES,                    MENUITEM_SUBMENU,               &module_submenu,                    0 ),
    MENU_ITEM   (0x36,LANG_MENU_MISC_CALENDAR,              MENUITEM_PROC,                  module_run, "calend.flt" ),
    MENU_ITEM   (0x37,LANG_MENU_MISC_TEXT_READER,           MENUITEM_SUBMENU,               &reader_submenu,                    0 ),
    MENU_ITEM   (0x38,LANG_MENU_MISC_GAMES,                 MENUITEM_SUBMENU,               &games_submenu,                     0 ),
    MENU_ITEM   (0x28,LANG_MENU_CONSOLE_SETTINGS,           MENUITEM_SUBMENU,               &console_settings_submenu, 0 ),
#if CAM_SWIVEL_SCREEN
    MENU_ITEM   (0x5c,LANG_MENU_MISC_FLASHLIGHT,            MENUITEM_BOOL,                  &conf.flashlight, 0 ),
#endif
    MENU_ITEM   (0x80,LANG_MENU_MISC_BUILD_INFO,            MENUITEM_PROC,                  gui_show_build_info, 0 ),
    MENU_ITEM   (0x80,LANG_MENU_MISC_MEMORY_INFO,           MENUITEM_PROC,                  gui_show_memory_info, 0 ),
#if !defined(OPT_FORCE_LUA_CALL_NATIVE)
    MENU_ITEM   (0x5c,LANG_MENU_ENABLE_LUA_NATIVE_CALLS,    MENUITEM_BOOL|MENUITEM_ARG_CALLBACK, &conf.script_allow_lua_native_calls, (int)gui_lua_native_call_warning ),
#endif
    MENU_ITEM   (0x33,LANG_SD_CARD,                         MENUITEM_SUBMENU,               &sdcard_submenu,                    0 ),
    MENU_ITEM   (0x2f,LANG_EYEFI,                           MENUITEM_SUBMENU,               &eyefi_submenu,                     0 ),
#ifdef OPT_DEBUGGING
    MENU_ITEM   (0x2a,LANG_MENU_MAIN_DEBUG,                 MENUITEM_SUBMENU,               &debug_submenu,                     0 ),
#endif
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                    0,                                  0 ),
    {0},
};

static CMenu misc_submenu = {0x29,LANG_MENU_MISC_TITLE, misc_submenu_items };

//-------------------------------------------------------------------

static void cb_perc()
{
    conf.batt_volts_show=0;
}

static void cb_volts()
{
    conf.batt_perc_show=0;
}

static void cb_batt_max()
{
    if (conf.batt_volts_max < conf.batt_volts_min + 25)
        conf.batt_volts_min = conf.batt_volts_max - 25;
}

static void cb_batt_min()
{
    if (conf.batt_volts_min > conf.batt_volts_max - 25)
        conf.batt_volts_max = conf.batt_volts_min + 25;
}

static CMenuItem battery_submenu_items[] = {
    MENU_ITEM   (0x66,LANG_MENU_BATT_VOLT_MAX,              MENUITEM_INT|MENUITEM_ARG_CALLBACK,     &conf.batt_volts_max,   (int)cb_batt_max ),
    MENU_ITEM   (0x67,LANG_MENU_BATT_VOLT_MIN,              MENUITEM_INT|MENUITEM_ARG_CALLBACK,     &conf.batt_volts_min,   (int)cb_batt_min ),
    MENU_ITEM   (0x0 ,(int)"",                              MENUITEM_SEPARATOR,                     0,                      0 ),
    MENU_ITEM   (0x73,LANG_MENU_BATT_SHOW_PERCENT,          MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_perc_show,   (int)cb_perc ),
    MENU_ITEM   (0x73,LANG_MENU_BATT_SHOW_VOLTS,            MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_volts_show,  (int)cb_volts ),
    MENU_ITEM   (0x32,LANG_MENU_BATT_SHOW_ICON,             MENUITEM_BOOL,                          &conf.batt_icon_show,   0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                            0,                      0 ),
    {0}
};

static CMenu battery_submenu = {0x32,LANG_MENU_BATT_TITLE, battery_submenu_items };

//-------------------------------------------------------------------

void cb_space_perc()
{
    conf.space_mb_show=0;
}

void cb_space_mb()
{
    conf.space_perc_show=0;
}

static const char* gui_space_bar_modes[] =                  { "Don't", "Horizontal", "Vertical"};
static const char* gui_space_bar_size_modes[] =             { "1/4", "1/2", "1"};
static const char* gui_space_bar_width_modes[] =            { "1", "2", "3","4","5","6","7","8","9","10"};
static const char* gui_space_warn_type_modes[] =            { "Percent", "MB", "Don't"};

static CMenuItem space_submenu_items[] = {
    MENU_ITEM   (0x5c,LANG_MENU_SPACE_SHOW_ICON,            MENUITEM_BOOL,                          &conf.space_icon_show,  0 ),
    MENU_ENUM2  (0x69,LANG_MENU_SPACE_SHOW_BAR,             &conf.space_bar_show,                   gui_space_bar_modes ),
    MENU_ENUM2  (0x6a,LANG_MENU_SPACE_BAR_SIZE,             &conf.space_bar_size,                   gui_space_bar_size_modes ),
    MENU_ENUM2  (0x6b,LANG_MENU_SPACE_BAR_WIDTH,            &conf.space_bar_width,                  gui_space_bar_width_modes ),
    MENU_ITEM   (0x5c,LANG_MENU_SPACE_SHOW_PERCENT,         MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.space_perc_show, (int)cb_space_perc ),
    MENU_ITEM   (0x5c,LANG_MENU_SPACE_SHOW_MB,              MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.space_mb_show,   (int)cb_space_mb ),
#if CAM_MULTIPART
    MENU_ITEM   (0x5c,LANG_MENU_SHOW_PARTITION_NR,          MENUITEM_BOOL,                          &conf.show_partition_nr, 0 ),
#endif
    MENU_ENUM2  (0x5f,LANG_MENU_SPACE_WARN_TYPE,            &conf.space_warn_type,                  gui_space_warn_type_modes ),
    MENU_ITEM   (0x58,LANG_MENU_SPACE_WARN_PERCENT,         MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &conf.space_perc_warn,    MENU_MINMAX(1, 99) ),
    MENU_ITEM   (0x58,LANG_MENU_SPACE_WARN_MB,              MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &conf.space_mb_warn,      MENU_MINMAX(1, 4000) ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,            0,                      0 ),
    {0}
};

static CMenu space_submenu = {0x33,LANG_MENU_OSD_SPACE_PARAMS_TITLE, space_submenu_items};

//-------------------------------------------------------------------

static const char* gui_dof_show_value_modes[] =             { "Don't", "Separate", "+Separate", "In Misc", "+In Misc" };

static CMenuItem dof_submenu_items[] = {
    MENU_ENUM2  (0x5f,LANG_MENU_OSD_SHOW_DOF_CALC,          &conf.show_dof,     gui_dof_show_value_modes ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_SUBJ_DIST_AS_NEAR_LIMIT,MENUITEM_BOOL,      &conf.dof_subj_dist_as_near_limit,  0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_USE_EXIF_SUBJ_DIST,     MENUITEM_BOOL,      &conf.dof_use_exif_subj_dist,       0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_SUBJ_DIST_IN_MISC,      MENUITEM_BOOL,      &conf.dof_subj_dist_in_misc,        0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_NEAR_LIMIT_IN_MISC,     MENUITEM_BOOL,      &conf.dof_near_limit_in_misc,       0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_FAR_LIMIT_IN_MISC,      MENUITEM_BOOL,      &conf.dof_far_limit_in_misc,        0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_HYPERFOCAL_IN_MISC,     MENUITEM_BOOL,      &conf.dof_hyperfocal_in_misc,       0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DOF_DEPTH_LIMIT_IN_MISC,    MENUITEM_BOOL,      &conf.dof_depth_in_misc,            0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                                  0 ),
    {0}
};

static CMenu dof_submenu = {0x31,LANG_MENU_DOF_TITLE, dof_submenu_items };

//-------------------------------------------------------------------

static const char* gui_zoom_value_modes[] =                 { "X", "FL", "EFL" };
static const char* gui_show_values_modes[] =                { "Don't", "Always", "Shoot" };

static CMenuItem values_submenu_items[] = {
    MENU_ENUM2  (0x5f,LANG_MENU_OSD_SHOW_MISC_VALUES,       &conf.show_values,  gui_show_values_modes ),
    MENU_ITEM   (0x5c,LANG_MENU_SHOW_VALUES_IN_VIDEO,       MENUITEM_BOOL,      &conf.show_values_in_video,                 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_ZOOM,           MENUITEM_BOOL,      &conf.values_show_zoom,                     0 ),
    MENU_ENUM2  (0x5f,LANG_MENU_OSD_ZOOM_VALUE,             &conf.zoom_value,   gui_zoom_value_modes ),
    MENU_ITEM   (0x60,LANG_MENU_OSD_ZOOM_SCALE,             MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zoom_scale,   MENU_MINMAX(0, 1000) ),
    MENU_ITEM   (0x62,LANG_MENU_VALUES_SHOW_REAL_APERTURE,  MENUITEM_BOOL,      &conf.values_show_real_aperture,            0 ),
    MENU_ITEM   (0x74,LANG_MENU_VALUES_SHOW_REAL_ISO,       MENUITEM_BOOL,      &conf.values_show_real_iso,                 0 ),
    MENU_ITEM   (0x74,LANG_MENU_VALUES_SHOW_MARKET_ISO,     MENUITEM_BOOL,      &conf.values_show_market_iso,               0 ),
    MENU_ITEM   (0x2d,LANG_MENU_SHOW_ISO_ONLY_IN_AUTOISO_MODE, MENUITEM_BOOL,   &conf.values_show_iso_only_in_autoiso_mode, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_EV_SETED,       MENUITEM_BOOL,      &conf.values_show_ev_seted,                 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_EV_MEASURED,    MENUITEM_BOOL,      &conf.values_show_ev_measured,              0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_BV_SETED,       MENUITEM_BOOL,      &conf.values_show_bv_seted,                 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_BV_MEASURED,    MENUITEM_BOOL,      &conf.values_show_bv_measured,              0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_OVEREXPOSURE,   MENUITEM_BOOL,      &conf.values_show_overexposure,             0 ),
    MENU_ITEM   (0x5c,LANG_MENU_SHOW_CANON_OVEREXPOSURE,    MENUITEM_BOOL,      &conf.values_show_canon_overexposure,       0 ),
    MENU_ITEM   (0x5c,LANG_MENU_VALUES_SHOW_LUMINANCE,      MENUITEM_BOOL,      &conf.values_show_luminance,                0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                                          0 ),
    {0}
};

static CMenu values_submenu = {0x28,LANG_MENU_OSD_VALUES_TITLE, values_submenu_items };

//-------------------------------------------------------------------

static const char* gui_show_clock_modes[]=                  { "Don't", "Normal", "Seconds"};
static const char* gui_clock_format_modes[] =               { "24h", "12h"};
static const char* gui_clock_indicator_modes[] =            { "PM", "P", "."};
static const char* gui_clock_halfpress_modes[] =            { "Full", "Seconds", "Don't"};

static CMenuItem clock_submenu_items[] = {
    MENU_ENUM2  (0x5f,LANG_MENU_OSD_SHOW_CLOCK,             &conf.show_clock,       gui_show_clock_modes ),
    MENU_ENUM2  (0x6d,LANG_MENU_OSD_CLOCK_FORMAT,           &conf.clock_format,     gui_clock_format_modes ),
    MENU_ENUM2  (0x6c,LANG_MENU_OSD_CLOCK_INDICATOR,        &conf.clock_indicator,  gui_clock_indicator_modes ),
    MENU_ENUM2  (0x6e,LANG_MENU_OSD_CLOCK_HALFPRESS,        &conf.clock_halfpress,  gui_clock_halfpress_modes ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,            0,                              0 ),
    {0}
};

static CMenu clock_submenu = {0x34,LANG_MENU_OSD_CLOCK_PARAMS_TITLE, clock_submenu_items };

//-------------------------------------------------------------------

#if !CAM_VIDEO_QUALITY_ONLY
const char* gui_video_bitrate_enum(int change, int arg)
{
    static const char *modes[]={ "0.25x", "0.5x","0.75x", "1x", "1.25x", "1.5x", "1.75x", "2x", "2.5x", "3x"};
	gui_enum_value_change(&conf.video_bitrate,change,sizeof(modes)/sizeof(modes[0]));

    if (change)
        shooting_video_bitrate_change(conf.video_bitrate);

    return modes[conf.video_bitrate];
}
#endif
 
#if CAM_AF_SCAN_DURING_VIDEO_RECORD
static const char* gui_video_af_key_enum(int change, int arg)
{
    static const char* names[] = CAM_VIDEO_AF_BUTTON_NAMES; 
    static const int keys[] = CAM_VIDEO_AF_BUTTON_OPTIONS; 
    int i; 
 
    for (i=0; i<sizeof(names)/sizeof(names[0]); ++i) { 
        if (conf.video_af_key==keys[i]) { 
            break; 
        } 
    } 
 
    i+=change; 
    if (i<0) 
        i=(sizeof(names)/sizeof(names[0]))-1; 
    else if (i>=(sizeof(names)/sizeof(names[0]))) 
        i=0; 
 
    conf.video_af_key = keys[i]; 
    return names[i]; 
}
#endif

static const char* gui_show_movie_time_modes[] =            { "Don't", "hh:mm:ss", "KB/s","both"};
#if !CAM_VIDEO_QUALITY_ONLY
    static const char* gui_video_mode_modes[] =             { "Bitrate", "Quality"};
#else
    static const char* gui_video_mode_modes[] =             { "Default", "Quality"};
#endif

static CMenuItem video_submenu_items[] = {
#if CAM_CHDK_HAS_EXT_VIDEO_MENU
    MENU_ENUM2  (0x23,LANG_MENU_VIDEO_MODE,                 &conf.video_mode,       gui_video_mode_modes ),
#if !CAM_VIDEO_QUALITY_ONLY
    MENU_ITEM   (0x5e,LANG_MENU_VIDEO_BITRATE,              MENUITEM_ENUM,          gui_video_bitrate_enum,             0 ),
#endif
    MENU_ITEM   (0x60,LANG_MENU_VIDEO_QUALITY,              MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.video_quality, MENU_MINMAX(1, 99) ),
#if CAM_CHDK_HAS_EXT_VIDEO_TIME
    MENU_ITEM   (0x5c,LANG_MENU_VIDEO_EXT_TIME,             MENUITEM_BOOL,          &conf.ext_video_time,               0 ),
#endif
    MENU_ITEM   (0x5c,LANG_MENU_CLEAR_VIDEO_VALUES,         MENUITEM_BOOL,          &conf.clear_video,                  0 ),
#endif
#if CAM_VIDEO_CONTROL
    MENU_ITEM   (0x5c,LANG_MENU_FAST_SWITCH_VIDEO,          MENUITEM_BOOL,          &conf.fast_movie_control,           0 ),
#endif
#if CAM_CHDK_HAS_EXT_VIDEO_MENU
    MENU_ITEM   (0x5c,LANG_MENU_FAST_SWITCH_QUALITY_VIDEO,  MENUITEM_BOOL,          &conf.fast_movie_quality_control,   0 ),
#endif
#if CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    MENU_ITEM   (0x5c,LANG_MENU_OPTICAL_ZOOM_IN_VIDEO,      MENUITEM_BOOL,          &conf.unlock_optical_zoom_for_video, 0 ),
#endif
#if CAM_CAN_MUTE_MICROPHONE
    MENU_ITEM   (0x83,LANG_MENU_MUTE_ON_ZOOM,               MENUITEM_BOOL,          &conf.mute_on_zoom,                 0 ),
#endif
#if CAM_AF_SCAN_DURING_VIDEO_RECORD
    MENU_ITEM   (0x82,LANG_MENU_VIDEO_AF_KEY,               MENUITEM_ENUM,          gui_video_af_key_enum,              0 ),
#endif
    MENU_ENUM2  (0x5c,LANG_MENU_OSD_SHOW_VIDEO_TIME,        &conf.show_movie_time,  gui_show_movie_time_modes ),
    MENU_ITEM   (0x60,LANG_MENU_OSD_SHOW_VIDEO_REFRESH,     MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.show_movie_refresh,   MENU_MINMAX(1, 20) ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,            0,                                  0 ),
    {0}
};

static CMenu video_submenu = {0x23,LANG_MENU_VIDEO_PARAM_TITLE, video_submenu_items };

//-------------------------------------------------------------------
// "Extra Photo Operations" Menu

static const char* tv_override[]={
#ifdef CAM_EXT_TV_RANGE
    // add very long time exposures as approximately powers of 2, adding 15 exposures
    "2048","1625","1290","1024","812","645","512","406","322","256","203","161","128","101","80",
#endif
    "64","50.8", "40.3", "32", "25.4","20","16", "12.7", "10","8", "6.3","5","4","3.2", "2.5","2", 
    "1.6", "1.3", "1", "0.8", "0.6", "0.5", "0.4", "0.3", "1/4", "1/5", "1/6", "1/8", "1/10", "1/13", 
    "1/15", "1/20", "1/25", "1/30", "1/40", "1/50", "1/60", "1/80", "1/100", "1/125", "1/160", "1/200", 
    "1/250", "1/320", "1/400", "1/500", "1/640","1/800", "1/1000", "1/1250", "1/1600","1/2000","1/2500",
    "1/3200","1/4000", "1/5000", "1/6400", "1/8000", "1/10000", "1/12500", "1/16000", "1/20000", "1/25000", 
    "1/32000", "1/40000", "1/50000", "1/64000","1/80000", "1/100k"
};

const char* gui_tv_override_value_enum(int change, int arg)
{
    gui_enum_value_change(&conf.tv_override_value,change,sizeof(tv_override)/sizeof(tv_override[0]));
    return tv_override[conf.tv_override_value]; 
}

static const char* gui_tv_enum_type_enum(int change, int arg)
{
#ifdef CAM_EXT_TV_RANGE
    static const char* modes[ ]= { "Ev Step", "ShrtExp", "LongExp" };
#else
    static const char* modes[ ]= { "Ev Step", "ShrtExp" };
#endif

    gui_enum_value_change(&conf.tv_enum_type,change,sizeof(modes)/sizeof(modes[0]));
    if (change)
    {
        void set_tv_override_menu();
        set_tv_override_menu();
    }
    return modes[conf.tv_enum_type]; 
}

#if CAM_HAS_IRIS_DIAPHRAGM
const char* gui_av_override_enum(int change, int arg)
{
    conf.av_override_value+=change;
    if (conf.av_override_value<0) conf.av_override_value=shooting_get_aperture_sizes_table_size()+CAM_EXT_AV_RANGE-1;
    else if (conf.av_override_value>shooting_get_aperture_sizes_table_size()+CAM_EXT_AV_RANGE-1) conf.av_override_value=0;

    short prop_id = shooting_get_aperture_from_av96(shooting_get_av96_override_value())/10;
    sprintf(buf, "%d.%02d", (int)prop_id/100, (int)prop_id%100 );
    return buf;
}
#endif

const char* gui_subj_dist_override_value_enum(int change, int arg)
{
    static char buf[9];

    if (conf.subj_dist_override_koef == SD_OVERRIDE_INFINITY)  // Infinity selected
        strcpy(buf,"   Inf.");
    else
    {
        // Increment / decrement the SD value, wrapping around from MIN_DIST to MAX_DIST
        conf.subj_dist_override_value += (change/**koef*/);
        if (conf.subj_dist_override_value < MIN_DIST)
            conf.subj_dist_override_value = MAX_DIST;
        else if (conf.subj_dist_override_value > MAX_DIST)
            conf.subj_dist_override_value = MIN_DIST;
        sprintf(buf, "%7d", shooting_get_subject_distance_override_value());
    }

    return buf; 
}

const char* gui_subj_dist_override_koef_enum(int change, int arg)
{
    static const char* modes[] = { "Off", "On", "Inf" };
	const char *rv = gui_change_simple_enum(&conf.subj_dist_override_koef,change,modes,sizeof(modes)/sizeof(modes[0]));
    return rv;
}

#if defined(OPT_CURVES)

static const char* gui_conf_curve_enum(int change, int arg) {
    static const char* modes[]={ "None", "Custom", "+1EV", "+2EV", "Auto DR" };

    gui_enum_value_change(&conf.curve_enable,change,sizeof(modes)/sizeof(modes[0]));

	if (change)
        libcurves->curve_init_mode();
    return modes[conf.curve_enable];
}

static void gui_load_curve_selected(const char *fn)
{
	if (fn) {
		// TODO we could sanity check here, but curve_set_type should fail gracefullish
		strcpy(conf.curve_file,fn);
		if (conf.curve_enable == 1)
            libcurves->curve_init_mode();
	}
}

static void gui_load_curve(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_CURVE_FILE, conf.curve_file, CURVE_DIR, gui_load_curve_selected);
}

static CMenuItem curve_submenu_items[] = {
    MENU_ITEM(0x5f,LANG_MENU_CURVE_ENABLE,        MENUITEM_ENUM,      gui_conf_curve_enum, &conf.curve_enable ),
    MENU_ITEM(0x35,LANG_MENU_CURVE_LOAD,          MENUITEM_PROC,      gui_load_curve, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu curve_submenu = {0x85,LANG_MENU_CURVE_PARAM_TITLE, curve_submenu_items };

#endif

// Display & edit an int value as a decimal.
// Value ranges from 0 - 100000; but display shows as 0.00000 - 1.00000
const char* gui_decimal_enum(int change, int arg)
{
    int *v = (int*)arg;

    *v += change;
    if (*v < 0) *v = 0;
    if (*v > 100000) *v = 100000;

    sprintf(buf, "%01d.%05d", (int)(*v / 100000), (int)(*v % 100000));

    return buf;
}

// Modify and display a value as H:MM:SS
// For storing a value as a number of seconds internally; but displaying as a time value
const char* gui_hhmss_enum(int change, int arg)
{
    int *v = (int*)arg;

    int h, m, s;
    h = *v / 3600;
    m = (*v % 3600) / 60;
    s = *v % 60;

    switch (change)
    {
    case 1:
    case -1:
        s += change;
        if (s < 0) s = 59;
        if (s > 59) s = 0;
        break;
    case 10:
    case -10:
        m += change / 10;
        if (m < 0) m = 59;
        if (m > 59) m = 0;
        break;
    default:
        h += change /100;
        if (h < 0) h = 1;
        if (h > 1) h = 0;
        break;
    }
    *v = (h * 3600) + (m * 60) + s;

    sprintf(buf, "%1d:%02d:%02d", h, m, s);

    return buf;
}

static const char* gui_override_disable_modes[] =           { "No", "Yes" };
#if CAM_HAS_ND_FILTER
static const char* gui_nd_filter_state_modes[] =            { "Off", "In", "Out" };
#endif
static const char* gui_fast_ev_step_modes[] =               { "1/6 Ev","1/3 Ev","1/2 Ev", "2/3 Ev","5/6 Ev","1 Ev","1 1/6Ev","1 1/3Ev","1 1/2Ev", "1 2/3Ev","1 5/6Ev","2 Ev","2 1/6Ev","2 1/3Ev","2 1/2Ev", "2 2/3Ev","2 5/6Ev","3 Ev","3 1/6Ev","3 1/3Ev","3 1/2Ev", "3 2/3Ev","3 5/6Ev","4 Ev"};
#if CAM_QUALITY_OVERRIDE
static const char* gui_fast_image_quality_modes[] =         { "Sup.Fine", "Fine", "Normal", "Off" };
#endif

const char* gui_flash_power_modes_enum(int change, int arg)
{
    static const char* modes[] = { "Min", "Med", "Max" };
	const char *rv = gui_change_simple_enum(&conf.flash_video_override_power,change,modes,sizeof(modes)/sizeof(modes[0]));
    return rv;
}

const char* gui_flash_exp_comp_modes_enum(int change, int arg)
{
    static const char* modes[] = { "-3", "-2.6", "-2.3", "-2", "-1.6", "-1.3", "-1", "-2/3", "-1/3", "0", "+1/3", "+2/3", "+1", "+1.3", "+1.6", "+2", "+2.3", "+2.6", "+3" };
	const char *rv = gui_change_simple_enum(&conf.flash_exp_comp,change,modes,sizeof(modes)/sizeof(modes[0]));
    return rv;
}

static void cb_change_flash_power()
{
    if (conf.flash_manual_override) conf.flash_enable_exp_comp = 0;
}

static void cb_change_flash_exp_comp()
{
    if (conf.flash_enable_exp_comp) conf.flash_manual_override = 0;
}

static CMenuItem tv_override_evstep[2] = {
    MENU_ITEM   (0, LANG_MENU_OVERRIDE_TV_VALUE,  MENUITEM_ENUM,            gui_tv_override_value_enum,         0 ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.tv_override_enabled,          0 ),
};

#ifdef CAM_EXT_TV_RANGE
static CMenuItem tv_override_long_exp[2] = {
    MENU_ITEM   (0, LANG_MENU_OVERRIDE_TV_LONG_EXP,  MENUITEM_ENUM|MENUITEM_HHMMSS, gui_hhmss_enum,             &conf.tv_override_long_exp ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.tv_override_enabled,          0 ),
};
#endif

static CMenuItem tv_override_short_exp[2] = {
    MENU_ITEM   (0, LANG_MENU_OVERRIDE_TV_SHORT_EXP, MENUITEM_ENUM|MENUITEM_DECIMAL, gui_decimal_enum,          &conf.tv_override_short_exp ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.tv_override_enabled,          0 ),
};

static CMenuItem iso_override_items[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.iso_override_value,           MENU_MINMAX(0, 10000) ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.iso_override_koef,            0),
};

static CMenuItem fast_ev_switch[2] = {
    MENU_ENUM2  (0, 0,                                                      &conf.fast_ev_step,                 gui_fast_ev_step_modes ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.fast_ev,                      0 ),
};

static CMenuItem manual_flash[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_ENUM,                                      gui_flash_power_modes_enum,         0 ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,                &conf.flash_manual_override,        (int)cb_change_flash_power ),
};

static CMenuItem flash_exp_comp[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_ENUM,                                      gui_flash_exp_comp_modes_enum,      0 ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,                &conf.flash_enable_exp_comp,        (int)cb_change_flash_exp_comp ),
};

#if CAM_HAS_IRIS_DIAPHRAGM
static CMenuItem av_override_items[2] = {
    MENU_ITEM   (0, 0,  MENUITEM_ENUM,                                      gui_av_override_enum,               0 ),
    MENU_ITEM   (0, 0,  MENUITEM_BOOL,                                      &conf.av_override_enabled,          0 ),
};
#endif

#if CAM_CAN_SD_OVERRIDE
static CMenuItem sd_override_items[2] = {
    MENU_ITEM   (0, 0,   MENUITEM_ENUM|MENUITEM_SD_INT,                     gui_subj_dist_override_value_enum,  MAX_DIST ),
    MENU_ITEM   (0, 0,   MENUITEM_ENUM,                                     gui_subj_dist_override_koef_enum,   0 ),
};
#endif

static const char* gui_raw_nr_modes[] =                     { "Auto", "Off", "On"};

static CMenuItem operation_submenu_items[] = {
    MENU_ENUM2  (0x5f,LANG_MENU_OVERRIDE_DISABLE,           &conf.override_disable, gui_override_disable_modes ),
    MENU_ITEM   (0x5c,LANG_MENU_OVERRIDE_DISABLE_ALL,       MENUITEM_BOOL,          &conf.override_disable_all,         0 ),
    MENU_ITEM   (0x59,LANG_MENU_TV_ENUM_TYPE,               MENUITEM_ENUM,          gui_tv_enum_type_enum,              0 ),
    MENU_ITEM   (0x61,LANG_MENU_OVERRIDE_TV_VALUE,          MENUITEM_STATE_VAL_PAIR,&tv_override_evstep,                0 ),
#if CAM_HAS_IRIS_DIAPHRAGM
    MENU_ITEM   (0x62,LANG_MENU_OVERRIDE_AV_VALUE,          MENUITEM_STATE_VAL_PAIR,&av_override_items,                 0 ),
#endif
    MENU_ITEM   (0x74,LANG_MENU_OVERRIDE_ISO_VALUE,         MENUITEM_STATE_VAL_PAIR,&iso_override_items,                10 ),
#if CAM_CAN_SD_OVERRIDE
    MENU_ITEM   (0x5e,LANG_MENU_OVERRIDE_SUBJ_DIST_VALUE,   MENUITEM_STATE_VAL_PAIR,&sd_override_items,                 0 ),
#endif
    MENU_ITEM   (0x5c,LANG_MENU_MISC_FAST_EV,               MENUITEM_STATE_VAL_PAIR,&fast_ev_switch,                    0 ),
    MENU_ITEM   (0x5c, LANG_MENU_FLASH_EXP_COMP,            MENUITEM_STATE_VAL_PAIR,&flash_exp_comp,                    0 ),
    MENU_ITEM   (0x5c, LANG_MENU_FLASH_MANUAL_OVERRIDE,     MENUITEM_STATE_VAL_PAIR,&manual_flash,                      0 ),
#if CAM_HAS_VIDEO_BUTTON
    MENU_ITEM   (0x5c, LANG_MENU_FLASH_VIDEO_OVERRIDE,      MENUITEM_BOOL,          &conf.flash_video_override,         0 ),
#endif
#if CAM_REAR_CURTAIN
    MENU_ITEM   (0x5c, LANG_MENU_REAR_CURTAIN,              MENUITEM_BOOL,          &conf.flash_sync_curtain,           0 ),
#endif
#if CAM_HAS_ND_FILTER
    MENU_ENUM2  (0x5f,LANG_MENU_OVERRIDE_ND_FILTER,         &conf.nd_filter_state,  gui_nd_filter_state_modes ),
#endif
    MENU_ENUM2  (0x5f,LANG_MENU_RAW_NOISE_REDUCTION,        &conf.raw_nr,       gui_raw_nr_modes ), // Dark Frame Subtraction - despite label has nothing to do with RAW
#if CAM_QUALITY_OVERRIDE
    MENU_ENUM2  (0x5c,LANG_MENU_MISC_IMAGE_QUALITY,         &conf.fast_image_quality, gui_fast_image_quality_modes ),
#endif
    MENU_ITEM   (0x2c,LANG_MENU_BRACKET_IN_CONTINUOUS,      MENUITEM_SUBMENU,       &bracketing_in_continuous_submenu,  0 ),
    MENU_ITEM   (0x2d,LANG_MENU_AUTOISO,                    MENUITEM_SUBMENU,       &autoiso_submenu,                   0 ),
#ifdef OPT_CURVES
    MENU_ITEM   (0x85,LANG_MENU_CURVE_PARAM,                MENUITEM_SUBMENU,       &curve_submenu,                     0 ),
#endif
    MENU_ITEM   (0x5b,LANG_MENU_CLEAR_OVERRIDE_VALUES,      MENUITEM_BOOL,          &conf.clear_override,               0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                                  0 ),
    {0}
};

static CMenu operation_submenu = {0x21,LANG_MENU_OPERATION_PARAM_TITLE, operation_submenu_items };

void set_tv_override_menu()
{
    CMenuItem *mi = find_mnu(&operation_submenu,LANG_MENU_OVERRIDE_TV_VALUE);
    switch (conf.tv_enum_type)
    {
    case 0:     // Ev Step
        mi->value = (int*)(&tv_override_evstep);
        mi->arg = 1;
        break;
    case 1:     // Short exposure
        mi->value = (int*)(&tv_override_short_exp);
        mi->arg = 100;
        break;
#ifdef CAM_EXT_TV_RANGE
    case 2:     // Long exposure
        mi->value = (int*)(&tv_override_long_exp);
        mi->arg = 1;
        break;
#endif
    }
}

//-------------------------------------------------------------------

static void gui_load_edge_selected( const char* fn )
{
    if (fn)
        libedgeovr->load_edge_overlay(fn);
}

static void gui_menuproc_edge_save(int arg)
{
    libedgeovr->save_edge_overlay();
}

static void gui_menuproc_edge_load(int arg)
{
    libfselect->file_select(LANG_MENU_EDGE_LOAD, EDGE_SAVE_DIR, EDGE_SAVE_DIR, gui_load_edge_selected);
}

static const char* gui_edge_pano_modes[] =                  { "Off", "Right", "Down", "Left", "Up", "Free" };
static CMenuItem edge_overlay_submenu_items[] = {
    MENU_ITEM   (0x5c,LANG_MENU_EDGE_OVERLAY_ENABLE,        MENUITEM_BOOL,          &conf.edge_overlay_enable,  0 ),
    MENU_ITEM   (0x5c,LANG_MENU_EDGE_FILTER,                MENUITEM_BOOL,          &conf.edge_overlay_filter,  0 ),
    MENU_ENUM2  (0x5f,LANG_MENU_EDGE_PANO,                  &conf.edge_overlay_pano, gui_edge_pano_modes ),
    MENU_ITEM   (0x5e,LANG_MENU_EDGE_PANO_OVERLAP,          MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.edge_overlay_pano_overlap, MENU_MINMAX(0, 100) ),
    MENU_ITEM   (0x5c,LANG_MENU_EDGE_SHOW,                  MENUITEM_BOOL,          &conf.edge_overlay_show,    0 ),
    MENU_ITEM   (0x5e,LANG_MENU_EDGE_OVERLAY_TRESH,         MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.edge_overlay_thresh, MENU_MINMAX(0, 255) ),
    MENU_ITEM   (0x5c,LANG_MENU_EDGE_PLAY,                  MENUITEM_BOOL,          &conf.edge_overlay_play,    0 ), //does not work on cams like s-series, which dont have a real "hardware" play/rec switch, need a workaround, probably another button
    MENU_ITEM   (0x33,LANG_MENU_EDGE_SAVE,                  MENUITEM_PROC,          gui_menuproc_edge_save,     0 ),
    MENU_ITEM   (0x5c,LANG_MENU_EDGE_ZOOM,                  MENUITEM_BOOL,          &conf.edge_overlay_zoom,    0 ),
    MENU_ITEM   (0x33,LANG_MENU_EDGE_LOAD,                  MENUITEM_PROC,          gui_menuproc_edge_load,     0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,            0,                          0 ),
    {0}
};

static CMenu edge_overlay_submenu = {0x7f,LANG_MENU_EDGE_OVERLAY_TITLE, edge_overlay_submenu_items };

//-------------------------------------------------------------------

static void gui_grid_lines_load_selected(const char *fn)
{
    if (fn)
        libgrids->grid_lines_load(fn);
}

static void gui_grid_lines_load(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_GRID_FILE, conf.grid_lines_file, "A/CHDK/GRIDS", gui_grid_lines_load_selected);
}

static CMenuItem grid_submenu_items[] = {
    MENU_ITEM(0x2f,LANG_MENU_SHOW_GRID,         MENUITEM_BOOL,		&conf.show_grid_lines, 0 ),
    MENU_ITEM(0x35,LANG_MENU_GRID_LOAD,         MENUITEM_PROC,		gui_grid_lines_load, 0 ),
    MENU_ITEM(0x0,LANG_MENU_GRID_CURRENT,       MENUITEM_SEPARATOR, 0, 0 ),
    MENU_ITEM(0x0,(int)conf.grid_title,         MENUITEM_TEXT,      0, 0 ),
    MENU_ITEM(0x0,(int)"",                      MENUITEM_SEPARATOR, 0, 0 ),
    MENU_ITEM(0x5c,LANG_MENU_GRID_FORCE_COLOR,  MENUITEM_BOOL,      &conf.grid_force_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_GRID_COLOR_LINE,   MENUITEM_COLOR_FG,  &conf.grid_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_GRID_COLOR_FILL,   MENUITEM_COLOR_BG,  &conf.grid_color, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,              MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu grid_submenu = {0x2f,LANG_MENU_GRID_TITLE, grid_submenu_items };

//-------------------------------------------------------------------

static void gui_menu_run_palette(int arg)
{
    libpalette->show_palette(PALETTE_MODE_DEFAULT, 0, NULL);
}

static CMenuItem visual_submenu_items[] = {
    MENU_ITEM(0x65,LANG_MENU_MISC_PALETTE,            MENUITEM_PROC,      gui_menu_run_palette, 0 ),
    MENU_ITEM(0x0,LANG_MENU_VIS_COLORS,               MENUITEM_SEPARATOR, 0, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_OSD_TEXT,            MENUITEM_COLOR_FG,  &conf.osd_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_OSD_BKG,             MENUITEM_COLOR_BG,  &conf.osd_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_OSD_WARNING,         MENUITEM_COLOR_FG,  &conf.osd_color_warn, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_OSD_WARNING_BKG,     MENUITEM_COLOR_BG,  &conf.osd_color_warn, 0 ),
    MENU_ITEM(0x65,LANG_MENU_EDGE_OVERLAY_COLOR,      MENUITEM_COLOR_FG,  &conf.edge_overlay_color,   0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_HISTO,               MENUITEM_COLOR_FG,  &conf.histo_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_HISTO_BKG,           MENUITEM_COLOR_BG,  &conf.histo_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_HISTO_BORDER,        MENUITEM_COLOR_FG,  &conf.histo_color2, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_HISTO_MARKERS,       MENUITEM_COLOR_BG,  &conf.histo_color2, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_ZEBRA_UNDER,         MENUITEM_COLOR_BG,  &conf.zebra_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_ZEBRA_OVER,          MENUITEM_COLOR_FG,  &conf.zebra_color, 0 ),
    //MENU_ITEM(0x65,LANG_MENU_VIS_BATT_ICON,           MENUITEM_COLOR_FG,  &conf.batt_icon_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_SPACE_ICON,          MENUITEM_COLOR_FG,  &conf.space_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_SPACE_ICON_BKG,      MENUITEM_COLOR_BG,  &conf.space_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_TEXT,           MENUITEM_COLOR_FG,  &conf.menu_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_BKG,            MENUITEM_COLOR_BG,  &conf.menu_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_TITLE_TEXT,     MENUITEM_COLOR_FG,  &conf.menu_title_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_TITLE_BKG,      MENUITEM_COLOR_BG,  &conf.menu_title_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_CURSOR_TEXT,    MENUITEM_COLOR_FG,  &conf.menu_cursor_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_CURSOR_BKG,     MENUITEM_COLOR_BG,  &conf.menu_cursor_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_SYMBOL_TEXT,    MENUITEM_COLOR_FG,  &conf.menu_symbol_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_MENU_SYMBOL_BKG,     MENUITEM_COLOR_BG,  &conf.menu_symbol_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_READER_TEXT,         MENUITEM_COLOR_FG,  &conf.reader_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_READER_BKG,          MENUITEM_COLOR_BG,  &conf.reader_color, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_OSD_OVERRIDE,         MENUITEM_COLOR_FG,  &conf.osd_color_override, 0 ),
    MENU_ITEM(0x65,LANG_MENU_VIS_OSD_OVERRIDE_BKG,     MENUITEM_COLOR_BG,  &conf.osd_color_override, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                    MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu visual_submenu = {0x28,LANG_MENU_VIS_TITLE, visual_submenu_items };

//-------------------------------------------------------------------

static CMenuItem raw_state_submenu_items[] = {
    MENU_ITEM   (0x5c,LANG_MENU_OSD_SHOW_RAW_STATE,         MENUITEM_BOOL,      &conf.show_raw_state,       0 ),
    MENU_ITEM   (0x5c,LANG_MENU_OSD_SHOW_REMAINING_RAW,     MENUITEM_BOOL,      &conf.show_remaining_raw,   0 ),
    MENU_ITEM   (0x60,LANG_MENU_OSD_RAW_TRESHOLD,           MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.remaining_raw_treshold,   MENU_MINMAX(0, 200) ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                          0 ),
    {0}
};

static CMenu raw_state_submenu = {0x24,LANG_MENU_OSD_RAW_STATE_PARAMS_TITLE, raw_state_submenu_items };

//-------------------------------------------------------------------

#ifdef  CAM_TOUCHSCREEN_UI

static const char* gui_touchscreen_disable_modes[]=         { "Enable", "Disable" };

static CMenuItem touchscreen_submenu_items[] = {
    MENU_ENUM2  (0x5f,LANG_MENU_TS_VIDEO_AE_DISABLE,        &conf.touchscreen_disable_video_controls,    gui_touchscreen_disable_modes ),
    MENU_ENUM2  (0x5f,LANG_MENU_TS_ALT_SHORTCUTS_DISABLE,   &conf.touchscreen_disable_shortcut_controls, gui_touchscreen_disable_modes ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0, 0 ),
    {0}
};

static CMenu touchscreen_submenu = {0x28,LANG_MENU_TOUCHSCREEN_VALUES, touchscreen_submenu_items };

#endif

//-------------------------------------------------------------------

#ifdef CAM_HAS_CMOS
    static const char* gui_temp_mode_modes[] =              { "Off", "Optical", "CMOS", "Battery", "all" };
#else
    static const char* gui_temp_mode_modes[] =              { "Off", "Optical", "CCD", "Battery", "all" };
#endif
static const char* gui_hide_osd_modes[] =                   { "Don't", "In Playback", "On Disp Press", "Both" };
static const char* gui_show_usb_info_modes[] =              { "Off", "Icon", "Text" };

static CMenuItem osd_submenu_items[] = {
    MENU_ITEM(0x5c,LANG_MENU_OSD_SHOW,              MENUITEM_BOOL,          &conf.show_osd, 0 ),
    MENU_ENUM2(0x5c,LANG_MENU_OSD_HIDE_PLAYBACK,                            &conf.hide_osd, gui_hide_osd_modes ),
    MENU_ITEM(0x5f,LANG_MENU_OSD_SHOW_STATES,       MENUITEM_BOOL,          &conf.show_state, 0 ),
    MENU_ENUM2(0x5f,LANG_MENU_OSD_SHOW_TEMP,                                &conf.show_temp, gui_temp_mode_modes ),
    MENU_ITEM(0x59,LANG_MENU_OSD_TEMP_FAHRENHEIT,   MENUITEM_BOOL,          &conf.temperature_unit, 0 ),
    MENU_ENUM2(0x71,LANG_MENU_USB_SHOW_INFO,                                &conf.usb_info_enable, gui_show_usb_info_modes ),
    MENU_ITEM(0x22,LANG_MENU_OSD_VALUES,  	    	MENUITEM_SUBMENU,       &values_submenu, 0 ),
    MENU_ITEM(0x31,LANG_MENU_OSD_DOF_CALC,          MENUITEM_SUBMENU,       &dof_submenu, 0 ),
    MENU_ITEM(0x24,LANG_MENU_OSD_RAW_STATE_PARAMS,  MENUITEM_SUBMENU,       &raw_state_submenu, 0 ),
    MENU_ITEM(0x32,LANG_MENU_OSD_BATT_PARAMS,       MENUITEM_SUBMENU,       &battery_submenu, 0 ),
    MENU_ITEM(0x33,LANG_MENU_OSD_SPACE_PARAMS,      MENUITEM_SUBMENU,       &space_submenu, 0 ),
    MENU_ITEM(0x34,LANG_MENU_OSD_CLOCK_PARAMS,	 	MENUITEM_SUBMENU,       &clock_submenu, 0 ),
    MENU_ITEM(0x59,LANG_MENU_OSD_SHOW_IN_REVIEW,    MENUITEM_BOOL,          &conf.show_osd_in_review, 0 ),
#ifdef  CAM_TOUCHSCREEN_UI
    MENU_ITEM   (0x22,LANG_MENU_TOUCHSCREEN_VALUES,         MENUITEM_SUBMENU,   &touchscreen_submenu,       0 ),
#endif
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP, 0,                                 0 ),
    {0}
};

static CMenu osd_submenu = {0x22,LANG_MENU_OSD_TITLE, osd_submenu_items };

//-------------------------------------------------------------------

static const char* gui_histo_show_modes[] =                 { "Don't", "Always", "Shoot" };
static const char* gui_histo_view_modes[]={ "RGB", "Y", "RGB Y",  "R G B", "RGB all", "Y all", "Blend", "Blend Y"};
static const char* gui_histo_transform_modes[]={ "Linear", "Log" };

static CMenuItem histo_submenu_items[] = {
    MENU_ENUM2(0x5f,LANG_MENU_HISTO_SHOW,             &conf.show_histo,     gui_histo_show_modes ),
    MENU_ENUM2(0x6f,LANG_MENU_HISTO_LAYOUT,           &conf.histo_layout,   gui_histo_view_modes ),
    MENU_ENUM2(0x5f,LANG_MENU_HISTO_MODE,             &conf.histo_mode,     gui_histo_transform_modes ),
    MENU_ITEM(0x5c,LANG_MENU_HISTO_EXP,               MENUITEM_BOOL,       &conf.show_overexp, 0 ),
    MENU_ITEM(0x70,LANG_MENU_HISTO_IGNORE_PEAKS,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.histo_ignore_boundary,   MENU_MINMAX(0, 32) ),
    MENU_ITEM(0x5c,LANG_MENU_HISTO_MAGNIFY,           MENUITEM_BOOL,       &conf.histo_auto_ajust, 0 ),
    MENU_ITEM(0x5c,LANG_MENU_HISTO_SHOW_EV_GRID,      MENUITEM_BOOL,       &conf.histo_show_ev_grid, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                    MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu histo_submenu = {0x25,LANG_MENU_HISTO_TITLE, histo_submenu_items };

//-------------------------------------------------------------------

static CMenuItem raw_exceptions_submenu_items[] = {
#if defined CAM_HAS_VIDEO_BUTTON
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_VIDEO,          MENUITEM_BOOL,      &conf.save_raw_in_video,        0 ),
#endif
#if defined(CAM_HAS_SPORTS_MODE)
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_SPORTS,         MENUITEM_BOOL,      &conf.save_raw_in_sports,       0 ),
#endif
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_BURST,          MENUITEM_BOOL,      &conf.save_raw_in_burst,        0 ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_TIMER,          MENUITEM_BOOL,      &conf.save_raw_in_timer,        0 ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_EDGEOVERLAY,    MENUITEM_BOOL,      &conf.save_raw_in_edgeoverlay,  0 ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_AUTO,           MENUITEM_BOOL,      &conf.save_raw_in_auto,         0 ),
#if CAM_BRACKETING
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_EV_BRACKETING,  MENUITEM_BOOL,      &conf.save_raw_in_ev_bracketing, 0 ),
#endif
    MENU_ITEM   (0x5c,LANG_MENU_RAW_WARN,                   MENUITEM_BOOL,      &conf.raw_exceptions_warn,      0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                              0 ),
    {0}
};

static CMenu raw_exceptions_submenu = {0x59,LANG_MENU_OSD_RAW_EXCEPTIONS_PARAMS_TITLE, raw_exceptions_submenu_items };

//-------------------------------------------------------------------

static void cb_change_dng()
{
    int old=conf.dng_version;
    conf_change_dng();
    if ((old==1) && (conf.dng_version==0)) gui_mbox_init(LANG_ERROR, LANG_CANNOT_OPEN_BADPIXEL_FILE, MBOX_BTN_OK|MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, NULL);
}

static void cb_change_save_raw()
{
    conf.save_raw = !conf.save_raw;
    cb_change_dng();
    gui_set_need_restore();
}

static const char* gui_dng_version(int change, int arg)
{
    static const char* modes[]={ "1.3", "1.1" };

    gui_enum_value_change(&conf.dng_version,change,sizeof(modes)/sizeof(modes[0]));
    cb_change_dng();

    return modes[conf.dng_version];
}

static void gui_menuproc_badpixel_create(int arg)
{
    libdng->create_badpixel_bin();
}

static void raw_fselect_cb(const char * filename)
{
    raw_prepare_develop(filename, 1);
}

static void gui_raw_develop(int arg)
{
    libfselect->file_select(LANG_RAW_DEVELOP_SELECT_FILE, "A/DCIM", "A", raw_fselect_cb);
}
    
static const char* gui_bad_pixel_enum(int change, int arg)
{ 
    int modes[]={LANG_MENU_BAD_PIXEL_OFF, LANG_MENU_BAD_PIXEL_INTERPOLATION, LANG_MENU_BAD_PIXEL_RAW_CONVERTER};
    
    return lang_str((int)gui_change_simple_enum(&conf.bad_pixel_removal,change,(const char**)modes,sizeof(modes)/sizeof(modes[0])));
}

#if defined (DNG_EXT_FROM)
extern void cb_change_dng_usb_ext();
#endif

static CMenuItem raw_submenu_items[] = {
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE,                   MENUITEM_BOOL | MENUITEM_ARG_CALLBACK, &conf.save_raw, (int)cb_change_dng ),
    MENU_ITEM   (0x59,LANG_MENU_OSD_RAW_EXCEPTIONS_PARAMS,	MENUITEM_SUBMENU,   &raw_exceptions_submenu, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_FIRST_ONLY,             MENUITEM_BOOL,      &conf.raw_save_first_only, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_SAVE_IN_DIR,            MENUITEM_BOOL,      &conf.raw_in_dir, 0 ),
    MENU_ENUM2a (0x5f,LANG_MENU_RAW_PREFIX,                 &conf.raw_prefix,   img_prefixes, NUM_IMG_PREFIXES ),
    MENU_ENUM2a (0x5f,LANG_MENU_RAW_EXTENSION,              &conf.raw_ext,      img_exts, NUM_IMG_EXTS ),
    MENU_ENUM2a (0x5f,LANG_MENU_SUB_PREFIX,                 &conf.sub_batch_prefix, img_prefixes, NUM_IMG_PREFIXES ),
    MENU_ENUM2a (0x5f,LANG_MENU_SUB_EXTENSION,              &conf.sub_batch_ext, img_exts, NUM_IMG_EXTS ),
//  MENU_ITEM   (0x60,LANG_MENU_SUB_IN_DARK_VALUE,          MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.sub_in_dark_value, MENU_MINMAX(0, 1023) ),
//  MENU_ITEM   (0x60,LANG_MENU_SUB_OUT_DARK_VALUE,         MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.sub_out_dark_value, MENU_MINMAX(0, 1023) ),
    MENU_ITEM   (0x2a,LANG_MENU_RAW_DEVELOP,                MENUITEM_PROC,      gui_raw_develop, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_BAD_PIXEL_REMOVAL,          MENUITEM_ENUM,      gui_bad_pixel_enum, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_CACHED,                 MENUITEM_BOOL,      &conf.raw_cache,            0 ),
#ifdef OPT_DEBUGGING
    MENU_ITEM   (0x5c,LANG_MENU_RAW_TIMER,                  MENUITEM_BOOL,      &conf.raw_timer,            0 ),
#endif
    MENU_ITEM   (0x0 ,(int)"DNG",                           MENUITEM_SEPARATOR,	0,							0 ),
    MENU_ITEM   (0x5c,LANG_MENU_DNG_FORMAT,                 MENUITEM_BOOL | MENUITEM_ARG_CALLBACK, &conf.dng_raw , (int)cb_change_dng ),
    MENU_ITEM   (0x5c,LANG_MENU_RAW_DNG_EXT,                MENUITEM_BOOL,      &conf.raw_dng_ext, 0 ),
    MENU_ITEM   (0x5f,LANG_MENU_DNG_VERSION,                MENUITEM_ENUM,      gui_dng_version, 0),
    MENU_ITEM   (0x2a,LANG_MENU_BADPIXEL_CREATE,            MENUITEM_PROC,      gui_menuproc_badpixel_create, 0 ),
#if defined (DNG_EXT_FROM)
    MENU_ITEM   (0x71,LANG_MENU_DNG_VIA_USB,                MENUITEM_BOOL | MENUITEM_ARG_CALLBACK, &conf.dng_usb_ext , (int)cb_change_dng_usb_ext ),
#endif
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,        0,                          0 ),
    {0}
};

static CMenu raw_submenu = {0x24,LANG_MENU_RAW_TITLE, raw_submenu_items };

//-------------------------------------------------------------------

void cb_zebra_restore_screen()
{
    if (!conf.zebra_restore_screen)
        conf.zebra_restore_osd = 0;
}

void cb_zebra_restore_osd()
{
    if (conf.zebra_restore_osd)
        conf.zebra_restore_screen = 1;
}

static const char* gui_zebra_mode_modes[] = { "Blink 1", "Blink 2", "Blink 3", "Solid", "Zebra 1", "Zebra 2" };
static const char* gui_zebra_draw_osd_modes[] = { "Nothing", "Histo", "OSD" };

static CMenuItem zebra_submenu_items[] = {
    MENU_ITEM(0x5c,LANG_MENU_ZEBRA_DRAW,              MENUITEM_BOOL,                            &conf.zebra_draw, 0 ),
    MENU_ENUM2(0x5f,LANG_MENU_ZEBRA_MODE,             &conf.zebra_mode, gui_zebra_mode_modes ),
    MENU_ITEM(0x58,LANG_MENU_ZEBRA_UNDER,             MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zebra_under,   MENU_MINMAX(0, 32) ),
    MENU_ITEM(0x57,LANG_MENU_ZEBRA_OVER,              MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zebra_over,    MENU_MINMAX(0, 32) ),
    MENU_ITEM(0x28,LANG_MENU_ZEBRA_RESTORE_SCREEN,    MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,      &conf.zebra_restore_screen,     cb_zebra_restore_screen ),
    MENU_ITEM(0x5c,LANG_MENU_ZEBRA_RESTORE_OSD,       MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,      &conf.zebra_restore_osd,        cb_zebra_restore_osd ),
    MENU_ENUM2(0x5f,LANG_MENU_ZEBRA_DRAW_OVER,        &conf.zebra_draw_osd, gui_zebra_draw_osd_modes ),
    MENU_ITEM(0x5c,LANG_MENU_ZEBRA_MULTICHANNEL,      MENUITEM_BOOL,                            &conf.zebra_multichannel, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                    MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu zebra_submenu = {0x26,LANG_MENU_ZEBRA_TITLE, zebra_submenu_items };

//-------------------------------------------------------------------

static void gui_draw_lang_selected(const char *fn)
{
    if (fn) {
        strcpy(conf.lang_file, fn);
        lang_load_from_file(conf.lang_file);
        gui_menu_init(NULL);
    }
}

static void gui_draw_load_lang(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_LANG_FILE, conf.lang_file, "A/CHDK/LANG", gui_draw_lang_selected);
}

static const char* gui_font_enum(int change, int arg)
{
    static const char* fonts[]={ "Win1250", "Win1251", "Win1252", "Win1253", "Win1254", "Win1257"};

    gui_enum_value_change(&conf.font_cp,change,sizeof(fonts)/sizeof(fonts[0]));

    if (change != 0) {
        font_set(conf.font_cp);
        rbf_load_from_file(conf.menu_rbf_file, FONT_CP_WIN);
        gui_menu_init(NULL);
    }

    return fonts[conf.font_cp];
}

static void gui_draw_menu_rbf_selected(const char *fn)
{
    if (fn) {
        strcpy(conf.menu_rbf_file, fn);
        rbf_load_from_file(conf.menu_rbf_file, FONT_CP_WIN);
        gui_menu_init(NULL);
    }
}

static void gui_draw_load_menu_rbf(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_FONT_FILE, conf.menu_rbf_file, "A/CHDK/FONTS", gui_draw_menu_rbf_selected);
}

static void gui_draw_symbol_rbf_selected(const char *fn)
{
    if (fn) {
        strcpy(conf.menu_symbol_rbf_file, fn);
        if(!rbf_load_symbol(conf.menu_symbol_rbf_file)) conf.menu_symbol_enable=0;		//AKA
        gui_menu_init(NULL);
    }
}

static void gui_draw_load_symbol_rbf(int arg)
{
    libfselect->file_select(LANG_STR_SELECT_SYMBOL_FILE, conf.menu_symbol_rbf_file, "A/CHDK/SYMBOLS", gui_draw_symbol_rbf_selected);
}

static void gui_menuproc_reset_files(int arg)
{
    conf.lang_file[0] = 0;
    strcpy(conf.menu_symbol_rbf_file,DEFAULT_SYMBOL_FILE);
    conf.menu_rbf_file[0] = 0;
    conf_save();
    gui_mbox_init(LANG_INFORMATION, LANG_MENU_RESTART_CAMERA, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}

static const char* gui_text_box_charmap[] = { "Default", "German", "Russian" };

static CMenuItem menu_font_submenu_items[] = {
    MENU_ITEM(0x35,LANG_MENU_VIS_LANG,                MENUITEM_PROC,      gui_draw_load_lang, 0 ),
    MENU_ITEM(0x5f,LANG_MENU_VIS_OSD_FONT,            MENUITEM_ENUM,      gui_font_enum, &conf.font_cp ),
    MENU_ITEM(0x35,LANG_MENU_VIS_MENU_FONT,           MENUITEM_PROC,      gui_draw_load_menu_rbf, 0 ),
    MENU_ITEM(0x64,LANG_MENU_VIS_SYMBOL,              MENUITEM_BOOL,      &conf.menu_symbol_enable, 0 ),
    MENU_ITEM(0x35,LANG_MENU_VIS_MENU_SYMBOL_FONT,    MENUITEM_PROC,      gui_draw_load_symbol_rbf, 0 ),
    MENU_ENUM2(0x5f,LANG_MENU_VIS_CHARMAP,            &conf.tbox_char_map, gui_text_box_charmap ),
    MENU_ITEM(0x80,LANG_MENU_RESET_FILES,             MENUITEM_PROC, 	  gui_menuproc_reset_files, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                    MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu menu_font_submenu = {0x28,LANG_MENU_FONT_SETTINGS, menu_font_submenu_items };

//-------------------------------------------------------------------

static const char* gui_user_menu_show_enum(int change, int arg)
{
    static const char* modes[]={ "Off", "On", "On Direct" };

    void set_usermenu_state();
    set_usermenu_state();

    return gui_change_simple_enum(&conf.user_menu_enable,change,modes,sizeof(modes)/sizeof(modes[0]));
}

static CMenuItem menu_settings_submenu_items[] = {
    MENU_ITEM(0x5f,LANG_MENU_USER_MENU_ENABLE,		MENUITEM_ENUM,          gui_user_menu_show_enum, 0 ),
    MENU_ITEM(0x5c,LANG_MENU_USER_MENU_AS_ROOT,     MENUITEM_BOOL,          &conf.user_menu_as_root, 0 ),
    MENU_ITEM(0x72,LANG_MENU_USER_MENU_EDIT,        MENUITEM_PROC,          module_run, "useredit.flt" ),
    MENU_ITEM(0x81,LANG_MENU_VIS_MENU_CENTER,       MENUITEM_BOOL,	        &conf.menu_center, 0 ),
    MENU_ITEM(0x81,LANG_MENU_SELECT_FIRST_ENTRY,    MENUITEM_BOOL,	        &conf.menu_select_first_entry, 0 ),
    MENU_ITEM(0x5c,LANG_MENU_SHOW_ALT_HELP,         MENUITEM_BOOL,          &conf.show_alt_helper, 0 ),
    MENU_ITEM(0x58,LANG_MENU_SHOW_ALT_HELP_DELAY,   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.show_alt_helper_delay, MENU_MINMAX(0, 10) ),
    MENU_ITEM(0x28,LANG_MENU_FONT_SETTINGS,         MENUITEM_SUBMENU,       &menu_font_submenu, 0 ),
    MENU_ITEM(0x51,LANG_MENU_BACK,                  MENUITEM_UP, 0, 0 ),
    {0}
};

static CMenu menu_settings_submenu = {0x28,LANG_MENU_MENU_SETTINGS, menu_settings_submenu_items };

//-------------------------------------------------------------------

#if CAM_ADJUSTABLE_ALT_BUTTON

const char* gui_alt_mode_button_enum(int change, int arg)
{
#if defined(CAM_ALT_BUTTON_NAMES) && defined(CAM_ALT_BUTTON_OPTIONS)
    static const char* names[] = CAM_ALT_BUTTON_NAMES;
    static const int keys[] = CAM_ALT_BUTTON_OPTIONS;
#else
#error Make sure CAM_ALT_BUTTON_NAMES and CAM_ALT_BUTTON_OPTIONS are defined in platform_camera.h
#endif
    int i;

    for (i=0; i<sizeof(names)/sizeof(names[0]); ++i) {
        if (conf.alt_mode_button==keys[i]) {
            break;
        }
    }

    i+=change;
    if (i<0)
        i=(sizeof(names)/sizeof(names[0]))-1;
    else if (i>=(sizeof(names)/sizeof(names[0])))
        i=0;

    conf.alt_mode_button = keys[i];
    kbd_set_alt_mode_key_mask(conf.alt_mode_button);
    return names[i];
}
#endif

#if CAM_OPTIONAL_EXTRA_BUTTON
static const char* gui_extra_button_enum(int change, int arg)
{
#if defined(CAM_EXTRA_BUTTON_NAMES) && defined(CAM_EXTRA_BUTTON_OPTIONS)
    static const char* names[] = CAM_EXTRA_BUTTON_NAMES;
    static const int keys[] = CAM_EXTRA_BUTTON_OPTIONS;
#else
#error Make sure CAM_EXTRA_BUTTON_NAMES and CAM_EXTRA_BUTTON_OPTIONS are defined in platform_camera.h
#endif
    int i;

    for (i=0; i<sizeof(names)/sizeof(names[0]); ++i) {
        if (conf.extra_button==keys[i]) {
            break;
        }
    }

    i+=change;
    if (i<0)
        i=(sizeof(names)/sizeof(names[0]))-1;
    else if (i>=(sizeof(names)/sizeof(names[0])))
        i=0;

    conf.extra_button = keys[i];
    kbd_set_extra_button((short)conf.extra_button);
    return names[i];
}
#endif //CAM_OPTIONAL_EXTRA_BUTTON

static const char* gui_alt_power_enum(int change, int arg)
{
// Script option is retained even if scripting is disabled, otherwise conf values will change
// Equivalent to ALT
    static const char* modes[]={ "Never", "Alt", "Script", "Always" };

    gui_enum_value_change(&conf.alt_prevent_shutdown,change,sizeof(modes)/sizeof(modes[0]));
        
    return modes[conf.alt_prevent_shutdown];
}

static void gui_menuproc_reset_selected(unsigned int btn)
{
    if (btn==MBOX_BTN_YES)
        conf_load_defaults();
}

static void gui_menuproc_reset(int arg)
{
    gui_mbox_init(LANG_MSG_RESET_OPTIONS_TITLE, 
                  LANG_MSG_RESET_OPTIONS_TEXT,
                  MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, gui_menuproc_reset_selected);
}

static CMenuItem chdk_settings_menu_items[] = {
    MENU_ITEM   (0x22,LANG_MENU_MAIN_OSD_PARAM,             MENUITEM_SUBMENU,   &osd_submenu, 0 ),
    MENU_ITEM   (0x72,LANG_MENU_OSD_LAYOUT_EDITOR,          MENUITEM_PROC,      module_run, "_osd_le.flt" ),
    MENU_ITEM   (0x28,LANG_MENU_MAIN_VISUAL_PARAM,          MENUITEM_SUBMENU,   &visual_submenu, 0 ),
    MENU_ITEM   (0x28,LANG_MENU_MENU_SETTINGS,              MENUITEM_SUBMENU,   &menu_settings_submenu, 0 ),
    MENU_ITEM   (0x2f,LANG_MENU_OSD_GRID_PARAMS,            MENUITEM_SUBMENU,   &grid_submenu, 0 ),
#ifdef CAM_HAS_GPS
    MENU_ITEM	(0x2a,LANG_MENU_GPS,                        MENUITEM_SUBMENU,	&gps_submenu,		0 ),
#endif
#if CAM_REMOTE
    MENU_ITEM   (0x86,LANG_MENU_REMOTE_PARAM,               MENUITEM_SUBMENU,   &remote_submenu, 0 ),
#endif
    MENU_ITEM   (0x5c,LANG_MENU_MISC_ENABLE_SHORTCUTS,      MENUITEM_BOOL,      &conf.enable_shortcuts, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_MISC_SHOW_SPLASH,           MENUITEM_BOOL,      &conf.splash_show, 0 ),
    MENU_ITEM   (0x5c,LANG_MENU_MISC_START_SOUND,           MENUITEM_BOOL,      &conf.start_sound, 0 ),
#if CAM_USE_ZOOM_FOR_MF
    MENU_ITEM   (0x59,LANG_MENU_MISC_ZOOM_FOR_MF,           MENUITEM_BOOL,      &conf.use_zoom_mf, 0 ),
#endif
#if CAM_ADJUSTABLE_ALT_BUTTON
    MENU_ITEM   (0x22,LANG_MENU_MISC_ALT_BUTTON,            MENUITEM_ENUM,      gui_alt_mode_button_enum, 0 ),
#endif
#if CAM_OPTIONAL_EXTRA_BUTTON
    MENU_ITEM   (0x22,LANG_MENU_MISC_EXTRA_BUTTON,          MENUITEM_ENUM,      gui_extra_button_enum, 0 ),
#endif
#if defined(CAM_ZOOM_ASSIST_BUTTON_CONTROL)
    MENU_ITEM   (0x5c,LANG_MENU_MISC_ZOOM_ASSIST,           MENUITEM_BOOL,      &conf.zoom_assist_button_disable, 0 ),
#endif
    MENU_ITEM   (0x5d,LANG_MENU_MISC_DISABLE_LCD_OFF,       MENUITEM_ENUM,      gui_alt_power_enum, 0 ),
    MENU_ITEM   (0x2b,LANG_MENU_MAIN_RESET_OPTIONS,         MENUITEM_PROC,      gui_menuproc_reset, 0 ),
    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP, 0, 0 ),
    {0}
};

CMenu chdk_settings_menu = {0x20,LANG_MENU_CHDK_SETTINGS, chdk_settings_menu_items };

//-------------------------------------------------------------------

extern CMenu script_submenu;

static CMenuItem root_menu_items[] = {
    MENU_ITEM   (0x21,LANG_MENU_OPERATION_PARAM,            MENUITEM_SUBMENU,   &operation_submenu, 0 ),
    MENU_ITEM   (0x23,LANG_MENU_VIDEO_PARAM,                MENUITEM_SUBMENU,   &video_submenu,     0 ),
    MENU_ITEM   (0x24,LANG_MENU_MAIN_RAW_PARAM,             MENUITEM_SUBMENU,   &raw_submenu,       0 ),
    MENU_ITEM   (0x7f,LANG_MENU_EDGE_OVERLAY,               MENUITEM_SUBMENU,   &edge_overlay_submenu, 0 ),
    MENU_ITEM   (0x25,LANG_MENU_MAIN_HISTO_PARAM,           MENUITEM_SUBMENU,   &histo_submenu, 0 ),
    MENU_ITEM   (0x26,LANG_MENU_MAIN_ZEBRA_PARAM,           MENUITEM_SUBMENU,   &zebra_submenu,     0 ),
    MENU_ITEM   (0x27,LANG_MENU_MAIN_SCRIPT_PARAM,          MENUITEM_SUBMENU,   &script_submenu,    0 ),
    MENU_ITEM   (0x22,LANG_MENU_CHDK_SETTINGS,              MENUITEM_SUBMENU,   &chdk_settings_menu, 0 ),
    MENU_ITEM   (0x29,LANG_MENU_MAIN_MISC,                  MENUITEM_SUBMENU,   &misc_submenu,      0 ),
    MENU_ITEM   (0x2e,LANG_MENU_USER_MENU,  	    	    MENUITEM_SUBMENU,   &user_submenu, 0 ),
    {0}
};

CMenu root_menu = {0x20,LANG_MENU_MAIN_TITLE, root_menu_items };

// Set visibility of User Menu in root menu based on user menu state
// Note this hack requires the User Menu entry to be the last one in the root_menu_items array above. 
void set_usermenu_state()
{
    int i; 
    for (i=0; root_menu_items[i].symbol != 0; i++) 
    { 
        if (root_menu_items[i].value == (int*)&user_submenu) 
        { 
            if (conf.user_menu_enable) 
                root_menu_items[i].text = LANG_MENU_USER_MENU;  // Enable user menu option in root menu 
            else 
                root_menu_items[i].text = 0;                    // Disable user menu option in root menu 
            return; 
        } 
    } 
}

//-------------------------------------------------------------------

const char* gui_on_off_enum(int change, int *conf_val)
{
    static const char* modes[]={ "Off", "On"};
    return gui_change_simple_enum(conf_val,change,modes,sizeof(modes)/sizeof(modes[0]));
}

#ifdef  CAM_TOUCHSCREEN_UI

const char* gui_override_disable_enum(int change, int arg)
{
    return gui_change_simple_enum(&conf.override_disable,change,gui_override_disable_modes,sizeof(gui_override_disable_modes)/sizeof(gui_override_disable_modes[0]));
}

const char* gui_nd_filter_state_enum(int change, int arg)
{
    return gui_change_simple_enum(&conf.nd_filter_state,change,gui_nd_filter_state_modes,sizeof(gui_nd_filter_state_modes)/sizeof(gui_nd_filter_state_modes[0]));
}

const char* gui_histo_show_enum(int change, int arg)
{
    return gui_change_simple_enum(&conf.show_histo,change,gui_histo_show_modes,sizeof(gui_histo_show_modes)/sizeof(gui_histo_show_modes[0]));
}

#endif

//-------------------------------------------------------------------
// Splash screen handling


#if defined(VER_CHDK)
#define LOGO_WIDTH  149
#define LOGO_HEIGHT 84
#else
#define LOGO_WIDTH  169
#define LOGO_HEIGHT 74
#endif

static int gui_splash;
static char *logo = NULL;
static int logo_size, logo_text_width, logo_text_height;

static const char *text[] =
{
    "CHDK Version '" HDK_VERSION " " BUILD_NUMBER "-" BUILD_SVNREV "'" , 
    "Build: " __DATE__ " " __TIME__ ,
    "Camera: " PLATFORM " - " PLATFORMSUB
};

static const color logo_colors[8] = 
{
    COLOR_BLACK,
    COLOR_SPLASH_RED,
    COLOR_RED,
    COLOR_GREY,
    COLOR_SPLASH_GREY,
    COLOR_SPLASH_PINK,
    COLOR_TRANSPARENT,
    COLOR_WHITE
};

static void init_splash()
{
    gui_splash = (conf.splash_show) ? SPLASH_TIME : 0;

    if (gui_splash)
    {
#if defined(VER_CHDK)
        const char *logo_name="A/CHDK/DATA/logo.dat";
#else   // CHDK-DE
        const char *logo_name="A/CHDK/DATA/logo_de.dat";
#endif
        struct stat st;
        if (stat(logo_name,&st) == 0)
        {
            logo_size = st.st_size;
            logo = malloc(logo_size);
            if (logo)
            {
                FILE *fd = fopen(logo_name, "rb");
                if (fd)
                {
                    fread(logo,1,logo_size,fd);
                    fclose(fd);
                }
                else
                {
                    free(logo);
                    logo = NULL;
                }
            }
        }

        logo_text_height = sizeof(text)/sizeof(text[0]);
        logo_text_width = 0;

        int i;
        for (i=0; i<logo_text_height; ++i)
        {
            int l = strlen(text[i]);
            if (l > logo_text_width) logo_text_width = l;
        }

        logo_text_width = logo_text_width * FONT_WIDTH + 10;
        logo_text_height = logo_text_height * FONT_HEIGHT + 8;
    }
}

static void gui_draw_splash()
{
    coord x, y;
    int i;
    color cl = MAKE_COLOR(COLOR_RED, COLOR_WHITE);

    x = (camera_screen.width-logo_text_width)>>1; 
    y = ((camera_screen.height-logo_text_height)>>1) + 20;

    draw_filled_round_rect(x, y, x+logo_text_width, y+logo_text_height, MAKE_COLOR(COLOR_RED, COLOR_RED));
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i)
    {
        draw_string(x+((logo_text_width-strlen(text[i])*FONT_WIDTH)>>1), y+i*FONT_HEIGHT+4, text[i], cl);
    }

#if OPT_EXPIRE_TEST
    do_expire_splash(x+((logo_text_width)>>1),y+(i+1)*FONT_HEIGHT+4);
#endif

    if (logo)
    {
        int pos;
        int mx = 0;
        int my = 0;
        int offset_x = (camera_screen.width-LOGO_WIDTH)>>1;
        int offset_y = ((camera_screen.height-LOGO_HEIGHT)>>1) - 42;
        for (pos=0; pos<logo_size; pos++)
        {
            char data = logo[pos];
            color c = logo_colors[(data>>5) & 0x07];
            for (i=0; i<(data&0x1F)+1; i++)
            {
                if (c!=0x00)
                {
                    draw_pixel(offset_x+mx,offset_y+my,c);
                }
                if (mx == LOGO_WIDTH)
                {
                    mx = 0;
                    my++;
                }
                else
                {
                    mx++;
                }     
            }
        }
    }
}

static void gui_handle_splash(int force_redraw)
{
    if (gui_splash)
    {
        if (camera_info.state.gui_mode_none || camera_info.state.gui_mode_alt)
            if (force_redraw || (gui_splash == SPLASH_TIME))
                gui_draw_splash();

        if (--gui_splash == 0)
        {
            if (camera_info.state.gui_mode_none || camera_info.state.gui_mode_alt)
                gui_set_need_restore();
            free(logo);
            logo = NULL;
        }
    }
}

//-------------------------------------------------------------------
static gui_handler *gui_mode=0;	// current gui mode. pointer to gui_handler structure

static int gui_osd_need_restore = 0;    // Set when screen needs to be erase and redrawn
static int gui_mode_need_redraw = 0;    // Set if current mode needs to redraw itself

//-------------------------------------------------------------------

void gui_set_need_restore()
{
    gui_osd_need_restore = 1;
}

void gui_cancel_need_restore()
{
    gui_osd_need_restore = 0;
    gui_mode_need_redraw = 0;
}

void gui_set_need_redraw()
{
    gui_mode_need_redraw = 1;
}

//-------------------------------------------------------------------
void gui_init()
{
    set_tv_override_menu();

    gui_set_mode(&defaultGuiHandler);
    if (conf.start_sound > 0)
    {
        play_sound(4);
    }

    init_splash();

    draw_init();

    process_file( "A/CHDK/badpixel", make_pixel_list, 1 );
    process_file( "A/CHDK/badpixel.txt", make_pixel_list, 1 );
}

//-------------------------------------------------------------------
gui_mode_t gui_get_mode() { return gui_mode->mode; }

//-------------------------------------------------------------------
// Set new GUI mode, returns old mode
gui_handler* gui_set_mode(gui_handler *mode) 
{
    // Set up gui mode & state variables
    camera_info.state.gui_mode = mode->mode;
    camera_info.state.gui_mode_none = (camera_info.state.gui_mode == GUI_MODE_NONE);
    camera_info.state.gui_mode_alt = (camera_info.state.gui_mode == GUI_MODE_ALT);
	
	if ( gui_mode == mode )
		return gui_mode;

#ifdef CAM_TOUCHSCREEN_UI
    if (((gui_mode->mode == GUI_MODE_NONE) != (mode->mode == GUI_MODE_NONE)) || // Change from GUI_MODE_NONE to any other or vice-versa
        ((gui_mode->mode >  GUI_MODE_MENU) != (mode->mode >  GUI_MODE_MENU)))   // Switch in & out of menu mode
        redraw_buttons = 1;
#endif

    set_usermenu_state();

    gui_handler *old_mode = gui_mode;
    gui_mode = mode;

    gui_osd_need_restore = 0;

    // Flag for screen erase/redraw unless mode is marked not to (e.g. menu box popup)
    if (((gui_mode->flags & (GUI_MODE_FLAG_NODRAWRESTORE|GUI_MODE_FLAG_NORESTORE_ON_SWITCH)) == 0) &&
        ((old_mode->flags & GUI_MODE_FLAG_NORESTORE_ON_SWITCH) == 0))
        gui_set_need_restore();
    // If old mode did not erase screen on exit then force current mode to redraw itself (e.g. exit menu popup back to file select)
    if ((old_mode->flags & (GUI_MODE_FLAG_NORESTORE_ON_SWITCH)) != 0)
        gui_set_need_redraw();

#ifdef CAM_DISP_ALT_TEXT
    if (camera_info.state.gui_mode_alt)
        gui_reset_alt_helper();
#endif

    return old_mode;
}

//-------------------------------------------------------------------

#ifdef CAM_DISP_ALT_TEXT

static int is_menu_shortcut = 0;

static char* gui_shortcut_text(int button)
{
    switch (button)
    {
    case KEY_DISPLAY:
        return CAM_DISP_BUTTON_NAME;
    case KEY_UP:
        return "UP";
    case KEY_DOWN:
        return "DOWN";
    case KEY_LEFT:
        return "LEFT";
    case KEY_RIGHT:
        return "RIGHT";
    case KEY_ERASE:
        return "ERASE";
    case KEY_MENU:
        is_menu_shortcut = 1;
        return "MENU*";
    default:
        return "?";
    }
}

static int shortcut_text(int x, int y, int button, int func_str, const char *state, color col)
{
    buf[0] = 0;
    if (state)
    {
        sprintf(buf,"%-5s %20s",gui_shortcut_text(button),lang_str(func_str));
        buf[26] = 0;
        sprintf(buf+strlen(buf)," [%6s",state);
        buf[34] = 0;
        strcat(buf,"]");
    }
    else if (button)
    {
        sprintf(buf,"%-5s %29s",gui_shortcut_text(button),lang_str(func_str));
    }
    else
    {
        sprintf(buf,"%-35s",lang_str(func_str));
    }
    buf[35] = 0;
    draw_string(x, y, buf, col);
    return y + FONT_HEIGHT;
}

static int gui_helper_displayat = 0;

void gui_reset_alt_helper()
{
    gui_helper_displayat = get_tick_count() + (conf.show_alt_helper_delay * 1000);
}

static void gui_draw_alt_helper()
{
    if ((camera_info.state.state_kbd_script_run != 0) || (console_displayed != 0))
    {
        if (gui_helper_displayat <= get_tick_count())
            gui_set_need_restore();
        gui_reset_alt_helper();
    }

    if ((conf.show_alt_helper == 0) || (gui_helper_displayat > get_tick_count()))
    {
        gui_draw_osd();
        return;
    }

    is_menu_shortcut = 0;

    int y = FONT_HEIGHT;
    int x = ((CAM_SCREEN_WIDTH/2)-(FONT_WIDTH*35/2));

    sprintf(buf,lang_str(LANG_HELP_HEADER),
            lang_str(LANG_HELP_ALT_SHORTCUTS),
            (conf.user_menu_enable && conf.user_menu_as_root)?lang_str(LANG_HELP_USER_MENU):lang_str(LANG_HELP_CHDK_MENU)); 
    buf[35] = 0;
    draw_string(x, y, buf, MAKE_COLOR(COLOR_FG, COLOR_ALT_BG));
    y += FONT_HEIGHT;

    if (conf.user_menu_enable)
    {
        sprintf(buf,lang_str(LANG_HELP_HEADER),
                lang_str(LANG_HELP_HALF_PRESS),
                (conf.user_menu_enable && conf.user_menu_as_root)?lang_str(LANG_HELP_CHDK_MENU):lang_str(LANG_HELP_USER_MENU)); 
        buf[35] = 0;
        draw_string(x, y, buf, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
        y += FONT_HEIGHT;
    }

    draw_string(x, y, lang_str(LANG_HELP_SCRIPTS), MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
    y += FONT_HEIGHT;

#if !defined(CAM_HAS_MANUAL_FOCUS) && defined(SHORTCUT_MF_TOGGLE)
    y = shortcut_text(x, y, SHORTCUT_MF_TOGGLE,LANG_HELP_MANUAL_FOCUS,gui_on_off_enum(0,&conf.subj_dist_override_koef), MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
#endif

    if (shooting_get_common_focus_mode())           // Check in manual focus mode
    {
        sprintf(buf,lang_str(LANG_HELP_FOCUS),gui_shortcut_text(SHORTCUT_SET_INFINITY),gui_shortcut_text(SHORTCUT_SET_HYPERFOCAL));
        draw_string(x, y, buf, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
        y += FONT_HEIGHT;
    }

#if !CAM_HAS_ERASE_BUTTON && CAM_CAN_SD_OVERRIDE
#ifdef OPT_DEBUGGING
    if (conf.debug_shortcut_action)
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_RAW,LANG_MENU_DEBUG_SHORTCUT_ACTION,gui_debug_shortcut_modes[conf.debug_shortcut_action], MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
    else
#endif
    if (shooting_get_common_focus_mode())           // Check in manual focus mode
    {
#if CAM_HAS_ZOOM_LEVER
        if (SHORTCUT_TOGGLE_RAW != SHORTCUT_SET_INFINITY)
            y = shortcut_text(x, y, SHORTCUT_TOGGLE_RAW, LANG_HELP_INF_FOCUS, 0, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
#else
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_RAW, LANG_HELP_CHG_FOCUS_FACTOR, 0, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
#endif
    }
    else
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_RAW,LANG_MENU_RAW_SAVE,(conf.save_raw?(conf.dng_raw?"DNG":"RAW"):"Off"), MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
#else
#ifdef OPT_DEBUGGING
    if (conf.debug_shortcut_action)
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_RAW,LANG_MENU_DEBUG_SHORTCUT_ACTION,gui_debug_shortcut_modes[conf.debug_shortcut_action], MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
    else
#endif
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_RAW,LANG_MENU_RAW_SAVE,(conf.save_raw?(conf.dng_raw?"DNG":"RAW"):"Off"), MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
#endif

    y = shortcut_text(x, y, 0 ,LANG_HELP_HALF_PRESS, 0, MAKE_COLOR(COLOR_FG, COLOR_ALT_BG));

    if ( conf.enable_shortcuts)
    {
        y = shortcut_text(x, y, SHORTCUT_DISABLE_OVERRIDES,LANG_MENU_OVERRIDE_DISABLE,gui_override_disable_modes[conf.override_disable], MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_HISTO,LANG_MENU_HISTO_SHOW,gui_histo_show_modes[conf.show_histo], MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_ZEBRA,LANG_MENU_ZEBRA_DRAW,gui_on_off_enum(0,&conf.zebra_draw), MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
        y = shortcut_text(x, y, SHORTCUT_TOGGLE_OSD,LANG_MENU_OSD_SHOW,gui_on_off_enum(0,&conf.show_osd), MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
    }
    else
    {
        y = shortcut_text(x, y, 0,LANG_HELP_SHORTCUTS_DISABLED, 0, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
    }

    if (conf.hide_osd == 0)
        y = shortcut_text(x, y, KEY_DISPLAY, LANG_HELP_HIDE_OSD, 0, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));

    if (is_menu_shortcut)
        y = shortcut_text(x, y, 0 ,LANG_HELP_NOT_ALT, 0, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
}

#endif

//-------------------------------------------------------------------

void gui_chdk_draw()
{
    static int clear_for_title = 1;

#ifdef CAM_DISP_ALT_TEXT
    gui_draw_alt_helper();
#else
    gui_draw_osd();
#endif

    if (camera_info.state.osd_title_line) 
    {
#ifdef CAM_DISP_ALT_TEXT
        script_get_alt_text(buf);
        draw_string(((CAM_SCREEN_WIDTH/2)-(FONT_WIDTH*strlen(buf)/2)), (CAM_SCREEN_HEIGHT-FONT_HEIGHT), buf, MAKE_COLOR(COLOR_RED, COLOR_WHITE));
#endif     

        if (camera_info.state.mode_rec || camera_info.state.mode_play)
        {
            draw_txt_string(CAM_TS_BUTTON_BORDER/FONT_WIDTH, 14, script_title, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
        }
        clear_for_title = 1;   
    }
    else if (clear_for_title)
    {
        draw_restore() ;
        clear_for_title = 0;
    }

    console_draw();
}

//-------------------------------------------------------------------
static void gui_debug_shortcut(void) 
{
#ifdef OPT_DEBUGGING
    static int lastcall = -1;
    int t=get_tick_count();
    if ( lastcall != -1) {
        if (t-lastcall <= 400)
            debug_display_direction = -debug_display_direction;
    }
    lastcall=t;
    switch(conf.debug_shortcut_action) {
            case 1:
                schedule_memdump();
                break;
            case 2:
                gui_update_debug_page();
                break;
            case 3:
                gui_compare_props(1);
                break;
    }
#endif
}

//-------------------------------------------------------------------
// Handler for Menu button press default - enter Menu mode
void gui_default_kbd_process_menu_btn()
{
    gui_set_mode(&menuGuiHandler);
}

// Change SD override factor, direction = 1 to increase, -1 to decrease
// Only applies if camera has a Zoom lever
#if CAM_HAS_ZOOM_LEVER
static void sd_override_koef(int direction)
{
    if (direction > 0)
    {
        if (conf.subj_dist_override_koef==SD_OVERRIDE_OFF)
        {
            conf.subj_dist_override_koef = SD_OVERRIDE_ON;
            menu_set_increment_factor(1);
        }
        else if (menu_get_increment_factor() < menu_calc_max_increment_factor(MAX_DIST))
        {
            menu_set_increment_factor(menu_get_increment_factor() * 10);
        }
        else
        {
            conf.subj_dist_override_koef = SD_OVERRIDE_INFINITY;
        }
    }
    else if (direction < 0)
    {
        if (conf.subj_dist_override_koef==SD_OVERRIDE_INFINITY)
        {
            conf.subj_dist_override_koef = SD_OVERRIDE_ON;
            menu_set_increment_factor(menu_calc_max_increment_factor(MAX_DIST));
        }
        else if (menu_get_increment_factor() > 1)
        {
            menu_set_increment_factor(menu_get_increment_factor() / 10);
        }
        else
        {
            conf.subj_dist_override_koef = SD_OVERRIDE_OFF;
        }
    }
    shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
}
#endif

// Change SD override by factor amount, direction = 1 to increase (zoom in), -1 to decrease (zoom out)
static void sd_override(int direction)
{
    if (conf.subj_dist_override_koef == SD_OVERRIDE_ON)
    {
        gui_subj_dist_override_value_enum(direction*menu_get_increment_factor(),0);
        shooting_set_focus(shooting_get_subject_distance_override_value(),SET_NOW);
    }
}

static int alt_mode_script_run()
{
    int remote_script_start_ready = 0;

    // Start the current script if script_start is enabled, we are in <ALT> mode and there is a pulse longer than 100mSec on USB port
    if (conf.remote_enable && conf.remote_enable_scripts && get_usb_power(SINGLE_PULSE) > 5)
        remote_script_start_ready=1;

    // Start a script if the shutter button pressed in <ALT> mode (kdb_blocked) or USB remote sequence not running
    //  or if script start on <ALT> enabled and this is the first pass through <ALT> mode
    if ( kbd_is_key_clicked(KEY_SHOOT_FULL) || remote_script_start_ready || script_run_on_alt_flag ) 
    {
        script_run_on_alt_flag = 0 ;
        script_start_gui(0);
        return 1;
    }

    return 0;
}

// Main button processing for CHDK Alt mode (not in MENU mode)
// This needs to be cleaned up, re-organised and commented !!!!
int gui_chdk_kbd_process()
{
    if (alt_mode_script_run()) return 0;

    // Process Shutter Half Press + BUTTON shortcuts
    gui_kbd_shortcuts();
    if (camera_info.state.is_shutter_half_press) return 0;

    int reset_helper = 0;

#if !CAM_HAS_ERASE_BUTTON && CAM_CAN_SD_OVERRIDE        // ALT RAW toggle kbd processing if camera has SD override but no erase button
    if (kbd_is_key_clicked(SHORTCUT_TOGGLE_RAW))
    {
        if (conf.debug_shortcut_action > 0)
        {
            gui_debug_shortcut();
        }
        // Check in manual focus mode
        else if (!shooting_get_common_focus_mode())
        {
            // Not manual focus mode so just update RAW save setting
            cb_change_save_raw();
        }
        else
        {
            // In manual focus mode so update shooting distance
#if CAM_HAS_ZOOM_LEVER
            conf.subj_dist_override_value=MAX_DIST;
            shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
#else
            gui_subj_dist_override_koef_enum(1,0);
#endif
            reset_helper = 1;
        }
    }
#else                                                   // ALT RAW toggle kbd processing if can't SD override or has erase button
    if (kbd_is_key_clicked(SHORTCUT_TOGGLE_RAW))
    {
        if (conf.debug_shortcut_action > 0)
        {
            gui_debug_shortcut();
        }
        else
        {
            // Change RAW save state
            cb_change_save_raw();
        }
    }
#endif
    else if (kbd_is_key_clicked(KEY_SET))
    {
        gui_menu_init(&script_submenu);
        gui_default_kbd_process_menu_btn();
    }
#if CAM_CAN_SD_OVERRIDE                                 // ALT button processing if camera has SD override
    else
    {
#if !CAM_HAS_MANUAL_FOCUS
        if (kbd_is_key_clicked(SHORTCUT_MF_TOGGLE))     // Camera does not have manual focus
        {
            if (conf.subj_dist_override_koef>SD_OVERRIDE_OFF)
                conf.subj_dist_override_koef=SD_OVERRIDE_OFF;
            else conf.subj_dist_override_koef=SD_OVERRIDE_ON;
            reset_helper = 1;
        }
        else
#endif
        if (shooting_get_common_focus_mode())           // Check in manual focus mode
        {
#if CAM_HAS_ZOOM_LEVER                                  // Camera has zoom lever, use left & right to change factor,up to set infinity
            if (kbd_is_key_clicked(KEY_RIGHT))
            {
                sd_override_koef(1);
                reset_helper = 1;
            }
            else if (kbd_is_key_clicked(KEY_LEFT))
            {
                sd_override_koef(-1);
                reset_helper = 1;
            }
            else if (kbd_is_key_clicked(SHORTCUT_SET_INFINITY))
            {
                conf.subj_dist_override_value=MAX_DIST;
                shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
                reset_helper = 1;
            }
            else
#endif
            if (kbd_is_key_clicked(SHORTCUT_SET_HYPERFOCAL))    // Set hyperfocal distance if down pressed
            {
                if ((camera_info.state.mode_shooting==MODE_M) || (camera_info.state.mode_shooting==MODE_AV))
                    conf.subj_dist_override_value=(int)shooting_get_hyperfocal_distance_1e3_f(shooting_get_aperture_from_av96(shooting_get_user_av96()),get_focal_length(lens_get_zoom_point()))/1000;
                else conf.subj_dist_override_value=(int)shooting_get_hyperfocal_distance();
                shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
                reset_helper = 1;
            }
            else
            {
                switch (kbd_get_autoclicked_key())
                {
#if CAM_HAS_ZOOM_LEVER
                case KEY_ZOOM_IN:
#else
                case KEY_RIGHT:
#endif
                    sd_override(1);
                    reset_helper = 1;
                    break;
#if CAM_HAS_ZOOM_LEVER
                case KEY_ZOOM_OUT:
#else
                case KEY_LEFT:
#endif
                    sd_override(-1);
                    reset_helper = 1;
                    break;
                }
            }
        }
    }
#endif

    if (reset_helper)
    {
        gui_set_need_restore();
#ifdef CAM_DISP_ALT_TEXT
        gui_reset_alt_helper();
#endif
    }

    return 0;
}

//-------------------------------------------------------------------
// Handler for Menu button press in CHDK Alt mode (not in Menu mode)
// Enter main menu or user menu based on configuration
void gui_chdk_kbd_process_menu_btn()
{
    if (conf.user_menu_enable &&
        ((conf.user_menu_as_root && !camera_info.state.is_shutter_half_press) ||
         (!conf.user_menu_as_root && camera_info.state.is_shutter_half_press)))
        gui_menu_init(&user_submenu);
    else
        gui_menu_init(&root_menu);

    gui_default_kbd_process_menu_btn();
}

//-------------------------------------------------------------------
// GUI handler for <ALT> mode
gui_handler altGuiHandler = { GUI_MODE_ALT, gui_chdk_draw, gui_chdk_kbd_process, gui_chdk_kbd_process_menu_btn, 0, };

//-------------------------------------------------------------------
// Main GUI redraw function, perform common initialisation then calls the redraw handler for the mode
void gui_redraw()
{
    int flag_gui_enforce_redraw = 0;

    if (!draw_test_guard() && (!camera_info.state.gui_mode_none || gui_splash))     // Attempt to detect screen erase in <Alt> mode, redraw if needed
    {
        draw_set_guard();
        flag_gui_enforce_redraw = 1;
#ifdef CAM_TOUCHSCREEN_UI
        redraw_buttons = 1;
#endif
    }

#ifdef CAM_TOUCHSCREEN_UI
    extern void virtual_buttons();
    virtual_buttons();
#endif

    // Erase screen if needed
    if (gui_osd_need_restore)
    {
        draw_restore();
        gui_osd_need_restore = 0;
        flag_gui_enforce_redraw = 1;
    }

    // Force mode redraw if needed
    if (gui_mode_need_redraw)
    {
        gui_mode_need_redraw = 0;
	    flag_gui_enforce_redraw = 1;
    }

#ifdef OPT_EXPIRE_TEST
    do_expire_check();
#endif

    gui_handle_splash(flag_gui_enforce_redraw);

// DEBUG: uncomment if you want debug values always on top
//gui_draw_debug_vals_osd();

    // Call redraw handler
    if (gui_mode->redraw)
        gui_mode->redraw(flag_gui_enforce_redraw);
}

//-------------------------------------------------------------------
// Main kbd processing for GUI modes
// Return:
//          0 = normal
//          1 = block buttons pressed from Camera firmware
int gui_kbd_process()
{
    if (gui_mode)
    {
        // Call menu button handler if menu button pressed
        if (gui_mode->kbd_process_menu_btn)
        {
            if (kbd_is_key_clicked(KEY_MENU))
            {
                gui_mode->kbd_process_menu_btn();
                return 0;
            }
        }

        // Call mode handler for other buttons
        if (gui_mode->kbd_process) return gui_mode->kbd_process();
    }
    return 0;
}

//------------------------------------------------------------------- 
static int gui_current_alt_state = ALT_MODE_NORMAL;

// Called from the KBD task code to change ALT mode state
void gui_set_alt_mode_state(int new_state)
{
    gui_current_alt_state = new_state;
}

// Called from the GUI task code to set the ALT mode state
void gui_activate_alt_mode()
{
    extern gui_handler scriptGuiHandler;

    switch (gui_current_alt_state)
    {
    case ALT_MODE_ENTER:
        
	    if (camera_info.state.state_kbd_script_run)
	        gui_set_mode(&scriptGuiHandler);
		else
	        gui_set_mode(&altGuiHandler);

        conf_update_prevent_shutdown();
        
        vid_turn_off_updates();

        // If user menu set to start automatically when <ALT> mode entered 
        // then enter user menu mode, unless a script was paused by exiting 
        // <ALT> mode when the script was running.
	    gui_user_menu_flag = 0;
	    if ((conf.user_menu_enable == 2) && !camera_info.state.state_kbd_script_run) {
		    gui_menu_init(&user_submenu);
		    gui_set_mode(&menuGuiHandler);
		    gui_user_menu_flag = 1;
	    }
        break;

    case ALT_MODE_LEAVE:
        conf_save();

        // Unload all modules which are marked as safe to unload, or loaded for menus
        module_exit_alt();

        rbf_set_codepage(FONT_CP_WIN);
        vid_turn_on_updates();
        gui_set_mode(&defaultGuiHandler);

	    conf_update_prevent_shutdown();
        break;
    }

    // Reset to stable state
    gui_current_alt_state = ALT_MODE_NORMAL;
}
