#include "stdlib.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "touchscreen.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_osd.h"


typedef struct {
    short grp;
    short hackkey;
    long canonkey;
    short   x1, y1, x2, y2;
    short   redraw;
    char    *nm, *nm2;
    int     min_gui_mode, max_gui_mode, cam_mode_mask;
    int     *conf_val;
    const char* (*chg_val)(int,int);
    int     *conf_disable;
} KeyMap;

static long kbd_new_state[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long touch_panel_state;

extern void _GetKbdState(long*);

//#define DELAY_TIMEOUT 10000
// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0         (0x00000000) //Logic OR of group 0 Keymap values
#define KEYS_MASK1         (0x2F000000) //Logic OR of group 1 Keymap values
#define KEYS_MASK2         (0x00000000) //Logic OR of group 2 Keymap values

#define SD_READONLY_FLAG    0x00008000 // Found @0xff5ac30c, levent 0x20a
#define SD_READONLY_IDX     0
#define USB_MASK            0x40000000 // Found @0xff5ac38c, levent 0x202
#define USB_IDX             2

extern void usb_remote_key( void ) ;
int get_usb_bit()
{
        long usb_physw[3];
        usb_physw[USB_IDX] = 0;
        _kbd_read_keys_r2(usb_physw);
        return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

#define TS_KEY_TOGGLE_RAW   200
#define TS_KEY_TOGGLE_ZEBRA 201
#define TS_KEY_TOGGLE_HISTO 202
#define TS_KEY_TOGGLE_OSD   203
#define TS_KEY_TOGGLE_OVRD  204
#define TS_KEY_TOGGLE_EDGE  205
#define TS_KEY_TOGGLE_ND    206
#define TS_KEY_TOGGLE_EV    207
#define TS_KEY_TOGGLE_TV_DN 208
#define TS_KEY_TOGGLE_TV_UP 209
#define TS_KEY_TOGGLE_AV_DN 210
#define TS_KEY_TOGGLE_AV_UP 211
#define TS_KEY_TOGGLE_SV_DN 212
#define TS_KEY_TOGGLE_SV_UP 213
#define TS_KEY_PLAYBACK     214
#define TS_KEY_POWER        215

#define TS_UP_DN_BUTTON     300
#define TS_PG_DN            301
#define TS_PG_UP            302

#define TS_XL   2
#define TS_W    55
#define TS_YT   1
#define TS_H    44
#define TS_XR   (480-TS_W-2)
#define LB(x,n) TS_XL+x*TS_W, TS_YT+n*TS_H, TS_XL+(x+1)*TS_W, TS_YT+n*TS_H+TS_H
#define RB(x,n) TS_XR-x*TS_W, TS_YT+n*TS_H, TS_XR+TS_W-x*TS_W, TS_YT+n*TS_H+TS_H
#define RBW(x,n) TS_XR-TS_W-x*TS_W, TS_YT+n*TS_H, TS_XR+TS_W-x*TS_W, TS_YT+n*TS_H+TS_H

extern const char* gui_on_off_enum(int change, int arg);
extern const char* gui_histo_show_enum(int change, int arg);
extern const char* gui_nd_filter_state_enum(int change, int arg);
extern const char* gui_override_disable_enum(int change, int arg);

#define MODE_VID    0x400

int video_ael;
int tv_video;
int av_video;
int sv_video;
int tv_min_video;
extern short cds_gain_value;

void set_tv_video(int x)
{
    if (video_ael)
    {
        if (x < tv_min_video) x = tv_min_video;
        if (x > 1152) x = 1152;
        if (tv_video != x)
        {
            tv_video = x;
            tv_video = _SetAE_ShutterSpeed((short*)&tv_video);
        }
    }
}

void set_av_video(int x)
{
    if (video_ael)
    {
        if (x < 200) x = 200;
        if (x > 576) x = 576;
        if (av_video != x)
        {
            av_video = x;
            shooting_set_av96_direct(av_video,1);
            extern int _MoveIrisWithAv(short*);
            _MoveIrisWithAv((short*)&av_video);
            _GetPropertyCase(PROPCASE_AV,&av_video,2);
        }
    }
}

void set_sv_video(int x)
{
    if (video_ael)
    {
        if (x < 0) x = 0;
        if (x > 768) x = 768;
        sv_video = x;

        extern int _SetCDSGain(short*);
        _SetCDSGain((short*)&sv_video);

        extern int _GetCdsGainValue();
        sv_video = _GetCdsGainValue();
    }
}

void set_ev_video_avail(int x)
{
    if (video_ael == x) return;
    video_ael = x;
    if (x)
    {
        av_video = tv_video = 0;

        _ExpCtrlTool_StopContiAE(0,0);

        _GetPropertyCase(PROPCASE_TV,&tv_video,2);
        _GetPropertyCase(PROPCASE_AV,&av_video,2);
        sv_video = cds_gain_value;

        if ((mode_get()&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED) tv_min_video=577;  // 1/60
        else tv_min_video=441;  //480; //1/30
    }
    else
        _ExpCtrlTool_StartContiAE(0,0);
}

const char* ts_video_nd(int change, int arg)
{
    const char *rv = gui_nd_filter_state_enum(change, arg);
    if (change && video_ael)
    {
        shooting_set_nd_filter_state(*(int*)arg,1);
    }
    return rv;
}

const char* ts_video_ev(int change, int arg)
{
    if (change)
    {
        set_ev_video_avail(!video_ael);
        // force ND off unless AEL enabled
        shooting_set_nd_filter_state((video_ael)?conf.nd_filter_state:2,1);
    }
    return gui_on_off_enum(0, arg);
}

static char ev_tv[15];

const char* ts_video_tv_dn(int change, int arg)
{
    if (change)
    {
        set_tv_video(tv_video - 32);
    }
    sprintf(ev_tv,"%4d",tv_video);
    return ev_tv;
}

const char* ts_video_tv_up(int change, int arg)
{
    if (change)
    {
        set_tv_video(tv_video + 32);
    }
    sprintf(ev_tv,"%4d",tv_video);
    return ev_tv;
}

static char ev_av[15];

const char* ts_video_av_dn(int change, int arg)
{
    if (change)
    {
        set_av_video(av_video - 32);
    }
    sprintf(ev_av,"%4d",av_video);
    return ev_av;
}

const char* ts_video_av_up(int change, int arg)
{
    if (change)
    {
        set_av_video(av_video + 32);
    }
    sprintf(ev_av,"%4d",av_video);
    return ev_av;
}

static char ev_sv[15];

const char* ts_video_sv_dn(int change, int arg)
{
    if (change)
    {
        set_sv_video(sv_video - 32);
    }
    sprintf(ev_sv,"%4d",sv_video);
    return ev_sv;
}

const char* ts_video_sv_up(int change, int arg)
{
    if (change)
    {
        set_sv_video(sv_video + 32);
    }
    sprintf(ev_sv,"%4d",sv_video);
    return ev_sv;
}

static char debug_pg[15];

const char* ts_pg_dn(int change, int arg)
{
    if (change)
    {
        if ((*(int*)arg) > 0) (*(int*)arg)--;
    }
    sprintf(debug_pg,"%4d",(*(int*)arg));
    return debug_pg;
}

const char* ts_pg_up(int change, int arg)
{
    if (change)
    {
        (*(int*)arg)++;
    }
    sprintf(debug_pg,"%4d",(*(int*)arg));
    return debug_pg;
}

static KeyMap keymap[] = {
    // Order IS important. kbd_get_pressed_key will walk down this table
    // and take the first matching mask. Notice that KEY_SHOOT_HALF is
    // always pressed if KEY_SHOOT_FULL is. --MarcusSt
//  { 1, TOUCH_SCREEN       , 0x00000008 },  // Touch screen panel
//    { 1, KEY_POWER           ,0x00800000 }, // Found @0xff5ac2f0, levent 0x100
    { 1, KEY_PLAYBACK        ,0x01000000 }, // Found @0xff5ac2f8, levent 0x101
    { 1, KEY_SHOOT_FULL      ,0x06000000 }, // Found @0xff5ac308, levent 0x01
    { 1, KEY_SHOOT_FULL_ONLY ,0x04000000 }, // Found @0xff5ac308, levent 0x01
    { 1, KEY_SHOOT_HALF      ,0x02000000 }, // Found @0xff5ac300, levent 0x00
    { 1, KEY_ZOOM_OUT        ,0x08000000 }, // Found @0xff5ac310, levent 0x03
    { 1, KEY_ZOOM_IN         ,0x20000000 }, // Found @0xff5ac318, levent 0x02

    { 3, KEY_PRINT          , 0x00000001, LB(0,1), 0, "CHDK",  0,    GUI_MODE_NONE,      100, MODE_REC|MODE_PLAY|MODE_VID }, // virtual touch screen key

    //{ 3, TS_PG_DN, 0x40000000, RB(2,0), 0, "Pg -", 2, GUI_MODE_NONE, GUI_MODE_ALT, MODE_REC|MODE_PLAY|MODE_VID, &conf.debug_propcase_page, ts_pg_dn },
    //{ 3, TS_PG_UP, 0x80000000, RB(1,0), 0, "Pg +", 2, GUI_MODE_NONE, GUI_MODE_ALT, MODE_REC|MODE_PLAY|MODE_VID, &conf.debug_propcase_page, ts_pg_up },

    { 3, TS_KEY_TOGGLE_EV   , 0x00008000, RB(0,2), 2, "AEL",       0,GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &video_ael, ts_video_ev,   &conf.touchscreen_disable_video_controls },
    { 3, TS_UP_DN_BUTTON    , 0,         RBW(0,4), 2, " - Tv %s +",0,GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &tv_video, ts_video_tv_dn, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_TV_DN, 0x00010000, RB(1,4), 2, 0,  0,         GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &tv_video, ts_video_tv_dn, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_TV_UP, 0x00020000, RB(0,4), 2, 0,  0,         GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &tv_video, ts_video_tv_up, &conf.touchscreen_disable_video_controls },
    { 3, TS_UP_DN_BUTTON    , 0,         RBW(2,4), 2, " - Av %s +",0,GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &av_video, ts_video_av_dn, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_AV_DN, 0x00040000, RB(3,4), 2, 0,  0,         GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &av_video, ts_video_av_dn, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_AV_UP, 0x00080000, RB(2,4), 2, 0,  0,         GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &av_video, ts_video_av_up, &conf.touchscreen_disable_video_controls },
    { 3, TS_UP_DN_BUTTON    , 0,         RBW(4,4), 2, " - Sv %s +",0,GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &sv_video, ts_video_sv_dn, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_SV_DN, 0x00100000, RB(5,4), 2, 0,  0,         GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &sv_video, ts_video_sv_dn, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_SV_UP, 0x00200000, RB(4,4), 2, 0,  0,         GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &sv_video, ts_video_sv_up, &conf.touchscreen_disable_video_controls },
    { 3, TS_KEY_TOGGLE_ND   , 0x00004000, LB(0,4), 2, "ND",    0,    GUI_MODE_NONE, GUI_MODE_NONE, MODE_VID, &conf.nd_filter_state, ts_video_nd, &conf.touchscreen_disable_video_controls },

    { 3, KEY_MENU            , 0x00000002, LB(0,2), 0, "Menu",  0, GUI_MODE_ALT, 100, MODE_REC|MODE_PLAY },
    { 3, KEY_SET            , 0x00000004, LB(0,3), 0, "Set",   0, GUI_MODE_ALT, 100, MODE_REC|MODE_PLAY },

    { 3, TS_KEY_TOGGLE_RAW  , 0x00000100, RB(1,1), 1, "RAW",   0, GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC|MODE_PLAY, &conf.save_raw, gui_on_off_enum, &conf.touchscreen_disable_shortcut_controls },
    { 3, TS_KEY_TOGGLE_OSD  , 0x00000200, RB(1,2), 1, "OSD",   0, GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC|MODE_PLAY, &conf.show_osd, gui_on_off_enum, &conf.touchscreen_disable_shortcut_controls },
    { 3, TS_KEY_TOGGLE_OVRD , 0x00000400, RB(1,3), 1, "OvrDis",0, GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC|MODE_PLAY, &conf.override_disable, gui_override_disable_enum, &conf.touchscreen_disable_shortcut_controls },
    { 3, TS_KEY_TOGGLE_ZEBRA, 0x00000800, RB(2,1), 1, "Zebra", 0, GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC|MODE_PLAY, &conf.zebra_draw, gui_on_off_enum, &conf.touchscreen_disable_shortcut_controls },
    { 3, TS_KEY_TOGGLE_HISTO, 0x00001000, RB(2,2), 1, "Hist",  0, GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC|MODE_PLAY, &conf.show_histo, gui_histo_show_enum, &conf.touchscreen_disable_shortcut_controls },
    { 3, TS_KEY_TOGGLE_EDGE , 0x00002000, RB(2,3), 1, "Edge",  0, GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC|MODE_PLAY, &conf.edge_overlay_enable, gui_on_off_enum, &conf.touchscreen_disable_shortcut_controls },

#if defined(TS_PLAY_POWER_HACK) 
    { 3, TS_KEY_PLAYBACK    , 0x00400000, LB(1,0), 0, "PLAY",  0,    GUI_MODE_ALT,       GUI_MODE_ALT,  MODE_REC|MODE_PLAY, &playbutton_hack, simulate_playback_press, 0 }, 
    { 3, TS_KEY_POWER       , 0x00800000, LB(3,0), 0, "OFF",   0,    GUI_MODE_ALT,       GUI_MODE_ALT,  MODE_REC|MODE_PLAY, &playbutton_hack, simulate_power_press, 0 }, 
#endif
#ifdef OPT_DEBUGGING
    { 3, KEY_DISPLAY        , 0x00000008, LB(0,4), 0, "Debug", 0,    GUI_MODE_ALT,       GUI_MODE_ALT,  MODE_REC|MODE_PLAY },
#endif
    { 3, KEY_DISPLAY        , 0x00000008, LB(0,4), 0, "Back",  0,    GUI_MODE_MENU,      GUI_MODE_MENU, MODE_REC|MODE_PLAY },
    { 3, KEY_DISPLAY        , 0x00000008, LB(0,4), 0, "Disp",  0,    GUI_MODE_MENU+1,    100,           MODE_REC|MODE_PLAY },
    { 3, KEY_UP             , 0x00000010, RB(0,1), 0, "Up",    0,    GUI_MODE_MENU,      100,           MODE_REC|MODE_PLAY },
    { 3, KEY_LEFT           , 0x00000020, RB(0,2), 0, "Left",  0,    GUI_MODE_MENU,      100,           MODE_REC|MODE_PLAY },
    { 3, KEY_RIGHT          , 0x00000040, RB(0,3), 0, "Right", 0,    GUI_MODE_MENU,      100,           MODE_REC|MODE_PLAY },
    { 3, KEY_DOWN           , 0x00000080, RB(0,4), 0, "Down",  0,    GUI_MODE_MENU,      100,           MODE_REC|MODE_PLAY },

    { 3, KEY_UP             , 0x00000010, RB(0,1), 0, "Man",   "Focus",  GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC, &conf.subj_dist_override_koef, 0, &conf.touchscreen_disable_shortcut_controls },
    { 3, KEY_DISPLAY        , 0x00000008, RB(0,2), 0, "Max",   "Dist",   GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC, 0, 0, &conf.touchscreen_disable_shortcut_controls },
    { 3, KEY_DOWN           , 0x00000080, RB(0,3), 0, "Hyper", "Dist",   GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC, 0, 0, &conf.touchscreen_disable_shortcut_controls },
    { 3, KEY_LEFT           , 0x00000020, RB(2,4), 0, "- Foc.","Factor", GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC, 0, 0, &conf.touchscreen_disable_shortcut_controls },
    { 3, KEY_RIGHT          , 0x00000040, RB(1,4), 0, "+ Foc.","Factor", GUI_MODE_ALT, GUI_MODE_ALT, MODE_REC, 0, 0, &conf.touchscreen_disable_shortcut_controls },

    { 0, 0, 0 }
};

static int is_button_displayed(int b, int guiMode, int camMode)
{
    return (
            (keymap[b].grp == 3) && 
            (guiMode >= keymap[b].min_gui_mode) && 
            (guiMode <= keymap[b].max_gui_mode) && 
            (camMode & keymap[b].cam_mode_mask) &&
            ((keymap[b].conf_disable == 0) || (*keymap[b].conf_disable == 0))
           );
}

static int is_button_active(int b, int guiMode, int camMode)
{
    return (is_button_displayed(b, guiMode, camMode) && keymap[b].canonkey);
}

int show_virtual_buttons()
{
    extern char canon_play_menu_active;
    return (canon_menu_active==(int)&canon_menu_active-4) && (canon_shoot_menu_active==0) && (canon_play_menu_active == 0);
}


// Test a pixel value of the CHDK on-screen button to see if it may have been erased
static int draw_test_pixel(coord x, coord y, color c)
{
    extern char* bitmap_buffer[];
    extern int active_bitmap_buffer;
    return (bitmap_buffer[active_bitmap_buffer][y * camera_screen.buffer_width + ASPECT_XCORRECTION(x)] == c);
}
//int ts_proc_cnt = 0;
//int ts_redraw_cnt = 0;
//int ts_check_cnt = 0;

// Called from hooked touch panel task (boot.c)
// Return 0 to allow touch event to pass onto firmware, 1 to block event from firmware.
int chdk_process_touch()
{
    //ts_check_cnt++;

    // If in canon menu, let the firmware have all the touch events.
    if (!show_virtual_buttons()) return 0;

    int guiMode = gui_get_mode();
    int camMode = (movie_status==VIDEO_RECORD_IN_PROGRESS) ? MODE_VID : (mode_get() & MODE_MASK);

    // Touch co-ordinate
    unsigned short tx, ty;
    tx = ((touch_screen_x & 0x7FFF) >> 2) ^ 0x3FF; //ixus240.101a @ loc_ff069d58
    ty = ((touch_screen_y & 0x7FFF) >> 2) ^ 0x3FF;


    // map touch coordinates to screen (try&error values)
    tx = (tx - 190) * 0.74;
    ty = (ty - 330) * 0.65;

    // Search for CHDK on screen buttons matching co-ordinate
    int i;
    for (i=0; keymap[i].hackkey; i++)
    {
        if ((tx >= keymap[i].x1) && (tx < keymap[i].x2) && (ty >= keymap[i].y1) && (ty < keymap[i].y2) && is_button_active(i,guiMode,camMode))
        {
            touch_panel_state &= ~keymap[i].canonkey;
        }
   }
    // If in alt mode (or about to enter alt mode) set the touch koords to 0x0 to block it from firmware
    if((guiMode != 0) || (((touch_panel_state & 1) == 0) && ((kbd_mod_state[3] & 1) != 0)))
    {
        touch_screen_x=touch_screen_y=0 ^ 0x3FF;
    }
    // let the firmware handle a touch press
    // otherwise it wont set touch_screen_active to 1
    return 0;

    // If in alt mode (or about to enter alt mode) block event from firmware
//    return (guiMode != 0) || (((touch_panel_state & 1) == 0) && ((kbd_mod_state[3] & 1) != 0));
}

int redraw_buttons = 1;
int print_key_index = -1;

void virtual_buttons()
{
    int guiMode = gui_get_mode();
    char buf[30];

    // If shooting or in any Canon menus then don't display any CHDK buttons
    if (((guiMode == 0) && camera_info.state.is_shutter_half_press) || !show_virtual_buttons()) return;

//    if(print_key_index == -1)
//    {
//        // need to find index of print key to check boarders in next step
//        int i;
//        for (i=0; keymap[i].hackkey != KEY_PRINT; i++);
//        print_key_index = i;
//    }

    // Check if border of CHDK button is corrupted, force redraw if so
//    if(print_key_index != -1 && !draw_test_pixel(keymap[print_key_index].x1+1, keymap[print_key_index].y1+1, (guiMode)?COLOR_GREEN:COLOR_WHITE)) redraw_buttons = 1;
    if (!draw_test_pixel(0, 80, (guiMode)?COLOR_GREEN:COLOR_WHITE)) redraw_buttons = 1;

    if (redraw_buttons)
    {
        //ts_redraw_cnt++;

        int i, x1, y1, x2, y2, ofst;
        int camMode = (movie_status==VIDEO_RECORD_IN_PROGRESS) ? MODE_VID : (mode_get() & MODE_MASK);

        //color c1 = MAKE_COLOR((camMode&MODE_VID)?COLOR_TRANSPARENT:COLOR_BLACK, COLOR_WHITE);
        //color c2 = MAKE_COLOR((camMode&MODE_VID)?COLOR_TRANSPARENT:COLOR_RED, (camMode&MODE_VID)?COLOR_RED:COLOR_WHITE);
        color c1 = MAKE_COLOR((camMode&MODE_VID)?COLOR_TRANSPARENT:COLOR_BLACK, COLOR_WHITE);
        color c2 = MAKE_COLOR((camMode&MODE_VID)?COLOR_TRANSPARENT:COLOR_BLACK, COLOR_GREEN);

        for (i=0; keymap[i].hackkey; i++)
        {
            if (is_button_displayed(i, guiMode, camMode) && keymap[i].nm)
            {
                x1 = keymap[i].x1;
                x2 = keymap[i].x2;
                y1 = keymap[i].y1;
                y2 = keymap[i].y2;

                color cl = c1;
                if (guiMode && (keymap[i].hackkey == KEY_PRINT)) cl = c2;
                if (keymap[i].conf_val && *keymap[i].conf_val) cl = c2;

                draw_filled_round_rect_thick(x1, y1, x2, y2, cl, 3);

                ofst = 16;
                if (keymap[i].hackkey == TS_UP_DN_BUTTON)
                {
                    draw_string(x1+4, y1+ofst, buf, cl);
                }
                else
                {
                    if (keymap[i].conf_val && keymap[i].chg_val)
                    {
                        ofst = 7;
                        strcpy(buf,(char*)keymap[i].chg_val(0,(int)keymap[i].conf_val));
                        buf[6] = 0;
                        draw_string(x1+4, y1+25, buf, cl);
                    }
                    else if (keymap[i].nm2)
                    {
                        ofst = 7;
                        draw_string(x1+4, y1+25, keymap[i].nm2, cl);
                    }
                    draw_string(x1+4, y1+ofst, keymap[i].nm, cl);
                }
            }
        }
    }

    redraw_buttons = 0;
}

int ts_process_touch()
{
    int rv = 0, i;

    if (touch_panel_state != 0xFFFFFFFF)
    {
        int guiMode = gui_get_mode();
        int camMode = (movie_status==VIDEO_RECORD_IN_PROGRESS) ? MODE_VID : (mode_get() & MODE_MASK);

        //ts_proc_cnt++;

        for (i=0; keymap[i].hackkey; i++)
        {
            if (is_button_active(i, guiMode, camMode))
            {
                if (kbd_is_key_clicked(keymap[i].hackkey))
                {
                    if (keymap[i].conf_val && keymap[i].chg_val)
                    {
                        keymap[i].chg_val(1,(int)keymap[i].conf_val);
                        rv = keymap[i].redraw & 1;
                    }
                    if (keymap[i].redraw & 2) redraw_buttons = 1;
                }
            }
        }
    }

    return rv;
}

long __attribute__((naked)) wrap_kbd_p1_f() ;


static void __attribute__((noinline)) mykbd_task_proceed()
{
    while (physw_run) {
        _SleepTask(physw_sleep_delay);

        if (wrap_kbd_p1_f() == 1) {   // autorepeat ?
            _kbd_p2_f();
        }
    }
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline))
mykbd_task()
{
    mykbd_task_proceed();

    _ExitTask();
}

long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
    asm volatile(
        "STMFD   SP!, {R1-R7,LR}\n"
        "MOV     R5, #0\n"
        //"BL      _kbd_read_keys \n"
        "BL        my_kbd_read_keys\n"
        "B       _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}

void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];
    kbd_prev_state[3] = kbd_new_state[3];

    _GetKbdState(kbd_new_state);
    _kbd_read_keys_r2(kbd_new_state);
    if (touch_screen_active == 1)               // Touch screen activated?
    {
        kbd_new_state[3] = touch_panel_state;               // Yes, use virtual button state
    }
    else
    {
        kbd_new_state[3] = touch_panel_state = 0xFFFFFFFF;  // No, clear out virtual button state
    }

    if (kbd_process() == 0) {
        // leave it alone...
        // we read keyboard state with _kbd_read_keys()
        physw_status[0] = kbd_new_state[0];
        physw_status[1] = kbd_new_state[1];
        physw_status[2] = kbd_new_state[2];
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) | (kbd_mod_state[0] & KEYS_MASK0);
        physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
        physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) | (kbd_mod_state[2] & KEYS_MASK2);
    }
    physw_status[SD_READONLY_IDX] = physw_status[SD_READONLY_IDX] & ~SD_READONLY_FLAG;

    usb_remote_key() ;

    if (conf.remote_enable) {
        physw_status[USB_IDX] = physw_status[USB_IDX] & ~USB_MASK;
    }
}


/****************/

void kbd_key_press(long key)
{
    int i;

    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key)
        {
            kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key) {
            kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release_all()
{
    kbd_mod_state[0] |= KEYS_MASK0;
    kbd_mod_state[1] |= KEYS_MASK1;
    kbd_mod_state[2] |= KEYS_MASK2;
    kbd_mod_state[3] = 0xFFFFFFFF;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++)
    {
        if ((keymap[i].hackkey == key) && keymap[i].canonkey)
        {
            return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++)
    {
        if ((keymap[i].hackkey == key) && keymap[i].canonkey)
        {
            return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
            ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++)
    {
        if (keymap[i].canonkey && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0))
        {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++)
    {
        if (keymap[i].canonkey &&
            ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
            ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0))
        {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

