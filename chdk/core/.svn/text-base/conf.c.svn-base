#include "platform.h"
#include "conf.h"
#include "histogram.h"
#include "font.h"
#include "raw.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_osd.h"
#include "gui_lang.h"
#include "gui_menu.h"
#include "gui_user_menu.h"
#include "core.h"
#include "fileutil.h"
#include "lang.h"

#include "modules.h"
#include "module_def.h"

//-------------------------------------------------------------------
Conf conf = {CONF_VERSION};

// reyalp: putting these in conf, since the conf values are lookups for them
// prefixes and extentions available for raw images (index with conf.raw_prefix etc)
const char* img_prefixes[NUM_IMG_PREFIXES]={ "IMG_", "CRW_", "SND_" /*, "AUT_", "ETC_","SDR_", "MVI_", "MRK_"*/};
const char* img_exts[NUM_IMG_EXTS]={ ".JPG", ".CRW", ".CR2", ".THM", ".WAV"/*, ".AVI", ".MRK"*/};

//-------------------------------------------------------------------

void conf_change_dng(void)
{
    if (conf.save_raw && conf.dng_raw && conf.dng_version)
    {
        if (!libdng->badpixel_list_loaded_b()) libdng->load_bad_pixels_list_b("A/CHDK/badpixel.bin");
        if (!libdng->badpixel_list_loaded_b()) conf.dng_version=0;
    }
}

#if defined (DNG_EXT_FROM)
void cb_change_dng_usb_ext()
{
    extern void change_ext_to_dng(void);
    extern void change_ext_to_default(void);
    if (conf.dng_usb_ext)
        change_ext_to_dng();
    else
        change_ext_to_default();
}
#endif

/*
update the prevent display off/prevent shutdown based on current state
doesn't really belong in conf but not clear where else it should go
*/
void conf_update_prevent_shutdown(void) {
    if(conf.alt_prevent_shutdown == ALT_PREVENT_SHUTDOWN_ALWAYS 
        || (conf.alt_prevent_shutdown == ALT_PREVENT_SHUTDOWN_ALT && !camera_info.state.gui_mode_none)
        || (conf.alt_prevent_shutdown == ALT_PREVENT_SHUTDOWN_ALT_SCRIPT && camera_info.state.state_kbd_script_run)) {
        disable_shutdown();
    } else {
        enable_shutdown();
    }
}

//-------------------------------------------------------------------
void clear_values()
{	

#if CAM_ADJUSTABLE_ALT_BUTTON
    extern const char* gui_alt_mode_button_enum(int change, int arg);
    gui_alt_mode_button_enum(0,0); // will reset if not in list of valid alt buttons
#else
    conf.alt_mode_button = CAM_DEFAULT_ALT_BUTTON; // if not adjustable, force to default
#endif

    if (conf.platformid != PLATFORMID) // the following config entries will be resetted if you switch the camera using the same cfg
    {
        conf.fast_ev = 0;
        conf.fast_movie_control = 0;
        conf.fast_movie_quality_control = 0;
        conf.zoom_scale = 100;
        conf.platformid = PLATFORMID;
        conf.flash_video_override = 0;
    }

    if (conf.clear_override)
    {
        conf.av_override_enabled=0;
        conf.tv_override_enabled=0;
        conf.subj_dist_override_koef=SD_OVERRIDE_OFF;
        conf.iso_override_koef=0;
        conf.nd_filter_state=0;
    }
    if (conf.clear_bracket)
    {
        conf.av_bracket_value=0;
        conf.tv_bracket_value=0;
        conf.iso_bracket_koef=0;
        conf.subj_dist_bracket_koef=0;
    }
    if (conf.clear_video)
    {
        conf.video_mode = 0;
#if CAM_CHDK_HAS_EXT_VIDEO_TIME
        conf.ext_video_time=0;
#endif
        conf.video_quality = VIDEO_DEFAULT_QUALITY;
        conf.video_bitrate = VIDEO_DEFAULT_BITRATE;
        shooting_video_bitrate_change(conf.video_bitrate);
    }
    //conf.edge_overlay_pano = 0; // reset it because otherwise this feature cant be used at startup (when buffer is empty) - needs workaround other than this!
}

//-------------------------------------------------------------------
static ConfInfo user_menu_conf_info[] = {
    CONF_INFO(  1, conf.user_menu_vars,         CONF_STRUCT_PTR,i:0),
    CONF_INFO(  2, conf.user_menu_as_root,      CONF_DEF_VALUE, i:0),
    CONF_INFO(  3, conf.user_menu_enable,       CONF_DEF_VALUE, i:0),

    {0,0,0,0,{0}}
};

void user_menu_conf_info_func(unsigned short id)
{
    switch (id)
    {
    case 1: 
        user_menu_restore(); 
        break;
    }
}

static ConfInfo osd_conf_info[] = {
/* !!! Do NOT change ID for items defined already! Append a new one at the end! !!! */

    CONF_INFO(  1, conf.show_osd,                               CONF_DEF_VALUE, i:1),
    CONF_INFO(  2, conf.show_osd_in_review,                     CONF_DEF_VALUE, i:0),
    CONF_INFO(  3, conf.override_disable,                       CONF_DEF_VALUE, i:0),
    CONF_INFO(  4, conf.override_disable_all,                   CONF_DEF_VALUE, i:1),
    CONF_INFO(  5, conf.hide_osd,                               CONF_DEF_VALUE, i:1),

    CONF_INFO2( 20, conf.histo_pos,                             CONF_OSD_POS,   45,CAM_SCREEN_HEIGHT-HISTO_HEIGHT-40),
    CONF_INFO2( 21, conf.dof_pos,                               CONF_OSD_POS,   90,45),
    CONF_INFO2( 22, conf.batt_icon_pos,                         CONF_OSD_POS,   178,0),
    CONF_INFO2( 23, conf.batt_txt_pos,                          CONF_OSD_POS,   178,FONT_HEIGHT),
    CONF_INFO2( 24, conf.mode_state_pos,                        CONF_OSD_POS,   35,0),
    CONF_INFO2( 25, conf.values_pos,                            CONF_OSD_POS,   CAM_SCREEN_WIDTH-9*FONT_WIDTH,30),
    CONF_INFO2( 26, conf.clock_pos,                             CONF_OSD_POS,   CAM_SCREEN_WIDTH-5*FONT_WIDTH-2,0),
    CONF_INFO2( 27, conf.space_icon_pos,                        CONF_OSD_POS,   CAM_SCREEN_WIDTH-100,0),
    CONF_INFO2( 28, conf.space_txt_pos,                         CONF_OSD_POS,   128,0),
    CONF_INFO2( 29, conf.mode_raw_pos,                          CONF_OSD_POS,   CAM_SCREEN_WIDTH-7*FONT_WIDTH-2,CAM_SCREEN_HEIGHT-3*FONT_HEIGHT-2),
    CONF_INFO2( 30, conf.space_ver_pos,                         CONF_OSD_POS,   CAM_SCREEN_WIDTH-7,0),
    CONF_INFO2( 31, conf.space_hor_pos,                         CONF_OSD_POS,   0,CAM_SCREEN_HEIGHT-7),   
    CONF_INFO2( 32, conf.mode_video_pos,                        CONF_OSD_POS,   CAM_SCREEN_WIDTH-25*FONT_WIDTH-2,CAM_SCREEN_HEIGHT-6*FONT_HEIGHT-2),
    CONF_INFO2( 33, conf.mode_ev_pos,                           CONF_OSD_POS,   CAM_SCREEN_WIDTH-40*FONT_WIDTH-2,CAM_SCREEN_HEIGHT-8*FONT_HEIGHT-2),
    CONF_INFO2( 34, conf.temp_pos,                              CONF_OSD_POS,   CAM_SCREEN_WIDTH-9*FONT_WIDTH-2,FONT_HEIGHT),
    CONF_INFO2( 35, conf.ev_video_pos,                          CONF_OSD_POS,   18,80),
    CONF_INFO2( 36, conf.usb_info_pos,                          CONF_OSD_POS,   95,0),

    CONF_INFO( 50, conf.histo_color,                            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_WHITE)),
    CONF_INFO( 51, conf.histo_color2,                           CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_WHITE)),
    CONF_INFO( 52, conf.osd_color,                              CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG)),
    CONF_INFO( 53, conf.osd_color_warn,                         CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_RED)),
    CONF_INFO( 54, conf.osd_color_override,                     CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_RED)),
    CONF_INFO( 55, conf.menu_color,                             CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG)),
    CONF_INFO( 56, conf.menu_title_color,                       CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_WHITE, COLOR_BLACK)),
    CONF_INFO( 57, conf.menu_cursor_color,                      CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG)),
    CONF_INFO( 58, conf.menu_symbol_color,                      CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG)),
    CONF_INFO( 59, conf.reader_color,                           CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_GREY, COLOR_WHITE)),
    CONF_INFO( 60, conf.grid_color,                             CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG)),
    CONF_INFO( 61, conf.space_color,                            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG)),
    CONF_INFO( 62, conf.zebra_color,                            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_RED)),
    CONF_INFO( 63, conf.edge_overlay_color,                     CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_RED)),

    CONF_INFO( 80, conf.show_clock,                             CONF_DEF_VALUE, i:2),
    CONF_INFO( 81, conf.clock_format,                           CONF_DEF_VALUE, i:0),
    CONF_INFO( 82, conf.clock_indicator,                        CONF_DEF_VALUE, i:0),
    CONF_INFO( 83, conf.clock_halfpress,                        CONF_DEF_VALUE, i:1),

    CONF_INFO( 90, conf.show_state,                             CONF_DEF_VALUE, i:1),

    CONF_INFO(100, conf.batt_volts_max,                         CONF_FUNC_PTR,  func:get_vbatt_max),
    CONF_INFO(101, conf.batt_volts_min,                         CONF_FUNC_PTR,  func:get_vbatt_min),
    CONF_INFO(102, conf.batt_perc_show,                         CONF_DEF_VALUE, i:1),
    CONF_INFO(103, conf.batt_volts_show,                        CONF_DEF_VALUE, i:0),
    CONF_INFO(104, conf.batt_icon_show,                         CONF_DEF_VALUE, i:1),

    CONF_INFO(110, conf.reader_file,                            CONF_CHAR_PTR,  ptr:"A/CHDK/BOOKS/README.TXT"),
    CONF_INFO(111, conf.reader_pos,                             CONF_DEF_VALUE, i:0),
    CONF_INFO(112, conf.reader_autoscroll,                      CONF_DEF_VALUE, i:0),
    CONF_INFO(113, conf.reader_autoscroll_delay,                CONF_DEF_VALUE, i:5),
    CONF_INFO(114, conf.reader_rbf_file,                        CONF_CHAR_PTR,  ptr:""),
    CONF_INFO(115, conf.reader_codepage,                        CONF_DEF_VALUE, i:FONT_CP_WIN),
    CONF_INFO(116, conf.reader_wrap_by_words,                   CONF_DEF_VALUE, i:1),

    CONF_INFO(120, conf.splash_show,                            CONF_DEF_VALUE, i:1),
   	CONF_INFO(121, conf.start_sound,                            CONF_DEF_VALUE, i:0),

    CONF_INFO(130, conf.menu_symbol_enable,                     CONF_DEF_VALUE, i:1),
    CONF_INFO(131, conf.menu_rbf_file,                          CONF_CHAR_PTR,  ptr:""),
    CONF_INFO(132, conf.menu_symbol_rbf_file,                   CONF_CHAR_PTR,  ptr:DEFAULT_SYMBOL_FILE),
    CONF_INFO(133, conf.menu_select_first_entry,                CONF_DEF_VALUE, i:1),
    CONF_INFO(134, conf.menu_center,                            CONF_DEF_VALUE, i:1),
    CONF_INFO(135, conf.lang_file,                              CONF_CHAR_PTR,  ptr:""),
    CONF_INFO(136, conf.font_cp,                                CONF_DEF_VALUE, i:FONT_CP_WIN_1252),
    CONF_INFO(137, conf.tbox_char_map,                          CONF_DEF_VALUE, i:0),

    CONF_INFO(140, conf.show_grid_lines,                        CONF_DEF_VALUE, i:0),
    CONF_INFO(141, conf.grid_lines_file,                        CONF_CHAR_PTR,  ptr:""),
    CONF_INFO(142, conf.grid_force_color,                       CONF_DEF_VALUE, i:0),

    CONF_INFO(150, conf.show_dof,                               CONF_DEF_VALUE, i:DOF_DONT_SHOW),
    CONF_INFO(151, conf.dof_subj_dist_as_near_limit,            CONF_DEF_VALUE, i:0),
    CONF_INFO(152, conf.dof_use_exif_subj_dist,                 CONF_DEF_VALUE, i:0),
    CONF_INFO(153, conf.dof_subj_dist_in_misc,                  CONF_DEF_VALUE, i:1),
    CONF_INFO(154, conf.dof_near_limit_in_misc,                 CONF_DEF_VALUE, i:1),
    CONF_INFO(155, conf.dof_far_limit_in_misc,                  CONF_DEF_VALUE, i:1),
    CONF_INFO(156, conf.dof_hyperfocal_in_misc,                 CONF_DEF_VALUE, i:1),
    CONF_INFO(157, conf.dof_depth_in_misc,                      CONF_DEF_VALUE, i:0),

    CONF_INFO(160, conf.show_values,                            CONF_DEF_VALUE, i:0),
    CONF_INFO(161, conf.values_show_in_review,                  CONF_DEF_VALUE, i:0),
    CONF_INFO(162, conf.values_show_zoom,                       CONF_DEF_VALUE, i:1),
    CONF_INFO(163, conf.values_show_real_aperture,              CONF_DEF_VALUE, i:0),
    CONF_INFO(164, conf.values_show_real_iso,                   CONF_DEF_VALUE, i:1),
    CONF_INFO(165, conf.values_show_market_iso,                 CONF_DEF_VALUE, i:0),
    CONF_INFO(166, conf.values_show_iso_only_in_autoiso_mode,   CONF_DEF_VALUE, i:0),
    CONF_INFO(167, conf.values_show_ev_seted,                   CONF_DEF_VALUE, i:0),
    CONF_INFO(168, conf.values_show_ev_measured,                CONF_DEF_VALUE, i:0),
    CONF_INFO(169, conf.values_show_bv_measured,                CONF_DEF_VALUE, i:0),
    CONF_INFO(170, conf.values_show_bv_seted,                   CONF_DEF_VALUE, i:0),
    CONF_INFO(171, conf.values_show_overexposure,               CONF_DEF_VALUE, i:0),
    CONF_INFO(172, conf.values_show_luminance,                  CONF_DEF_VALUE, i:0),
    CONF_INFO(173, conf.values_show_canon_overexposure,         CONF_DEF_VALUE, i:0),
    CONF_INFO(174, conf.show_values_in_video,                   CONF_DEF_VALUE, i:0),
    CONF_INFO(175, conf.zoom_value,                             CONF_DEF_VALUE, i:ZOOM_SHOW_X),
    CONF_INFO(176, conf.zoom_scale,                             CONF_DEF_VALUE, i:100), 
    
    CONF_INFO(180, conf.space_icon_show,                        CONF_DEF_VALUE, i:0),
    CONF_INFO(181, conf.space_perc_show,                        CONF_DEF_VALUE, i:0),
    CONF_INFO(182, conf.space_mb_show,                          CONF_DEF_VALUE, i:1),
    CONF_INFO(183, conf.space_bar_show,                         CONF_DEF_VALUE, i:1), 
    CONF_INFO(184, conf.space_bar_size,                         CONF_DEF_VALUE, i:1), 
    CONF_INFO(185, conf.space_bar_width,                        CONF_DEF_VALUE, i:2), 
    CONF_INFO(186, conf.space_perc_warn,                        CONF_DEF_VALUE, i:10),
    CONF_INFO(187, conf.space_mb_warn,                          CONF_DEF_VALUE, i:20),
    CONF_INFO(188, conf.space_warn_type,                        CONF_DEF_VALUE, i:0),
    CONF_INFO(189, conf.show_partition_nr,                      CONF_DEF_VALUE, i:0),

    CONF_INFO(200, conf.show_remaining_raw,                     CONF_DEF_VALUE, i:1),
    CONF_INFO(201, conf.show_raw_state,                         CONF_DEF_VALUE, i:1),
    CONF_INFO(202, conf.remaining_raw_treshold,                 CONF_DEF_VALUE, i:0),
    CONF_INFO(203, conf.raw_exceptions_warn,                    CONF_DEF_VALUE, i:1),

    CONF_INFO(210, conf.show_movie_time,                        CONF_DEF_VALUE, i:3),
    CONF_INFO(211, conf.show_movie_refresh,                     CONF_DEF_VALUE, i:1),

    CONF_INFO(220, conf.show_temp,                              CONF_DEF_VALUE, i:1),
    CONF_INFO(221, conf.temperature_unit,                       CONF_DEF_VALUE, i:0),

    CONF_INFO(230, conf.debug_shortcut_action,                  CONF_DEF_VALUE, i:0), // backwards compatible
   	CONF_INFO(231, conf.debug_display,                          CONF_DEF_VALUE, i:0),
    CONF_INFO(232, conf.debug_propcase_page,                    CONF_DEF_VALUE, i:0),
	CONF_INFO(233, conf.debug_misc_vals_show,                   CONF_DEF_VALUE, i:0),
    CONF_INFO(234, conf.mem_view_addr_init,                     CONF_DEF_VALUE, i:0x1000),

    // Touch screen U/I overrides
    CONF_INFO(240, conf.touchscreen_disable_video_controls,     CONF_DEF_VALUE, i:0),
    CONF_INFO(241, conf.touchscreen_disable_shortcut_controls,  CONF_DEF_VALUE, i:0),

    CONF_INFO(250, conf.usb_info_enable,                        CONF_DEF_VALUE, i:0),

    CONF_INFO(260, conf.show_alt_helper,                        CONF_DEF_VALUE, i:1),
    CONF_INFO(261, conf.show_alt_helper_delay,                  CONF_DEF_VALUE, i:3),
    CONF_INFO(262, conf.enable_shortcuts,                       CONF_DEF_VALUE, i:1),
    CONF_INFO(263, conf.extra_button,                           CONF_DEF_VALUE, i:0),

    // Console settings
    CONF_INFO(270, conf.console_show,                           CONF_DEF_VALUE, i:0),
    CONF_INFO(271, conf.console_timeout,                        CONF_DEF_VALUE, i:3),
 
    // OSD element scaling factor 
    CONF_INFO2( 280, conf.histo_scale,                             CONF_OSD_POS, 0,0  ),  // 0=no scale, 1=scale  (0 for future expansion)
    CONF_INFO2( 281, conf.dof_scale,                               CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 282, conf.batt_icon_scale,                         CONF_OSD_POS, 0,0  ),
    CONF_INFO2( 283, conf.batt_txt_scale,                          CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 284, conf.mode_state_scale,                        CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 285, conf.values_scale,                            CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 286, conf.clock_scale,                             CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 287, conf.space_icon_scale,                        CONF_OSD_POS, 0,0  ),
    CONF_INFO2( 288, conf.space_txt_scale,                         CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 289, conf.mode_raw_scale,                          CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 290, conf.space_ver_scale,                         CONF_OSD_POS, 0,0  ),
    CONF_INFO2( 291, conf.space_hor_scale,                         CONF_OSD_POS, 0,0  ),   
    CONF_INFO2( 292, conf.mode_video_scale,                        CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 293, conf.mode_ev_scale,                           CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 294, conf.temp_scale,                              CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 295, conf.ev_video_scale,                          CONF_OSD_POS, 1,1  ),
    CONF_INFO2( 296, conf.usb_info_scale,                          CONF_OSD_POS, 0,0  ),

    {0,0,0,0,{0}}
};

void osd_conf_info_func(unsigned short id)
{
    switch (id)
    {
    case 131: 
        rbf_load_from_file(conf.menu_rbf_file, FONT_CP_WIN);
        break;
    case 132: 
        if (!rbf_load_symbol(conf.menu_symbol_rbf_file))
            conf.menu_symbol_enable=0;
        break;
    case 135: 
        gui_lang_init(); 
        break;
    case 136:
        font_init();
        font_set(conf.font_cp);
        break;
#if CAM_OPTIONAL_EXTRA_BUTTON
    case 263: 
        kbd_set_extra_button((short)conf.extra_button);
        break;
#endif
    }
}

static ConfInfo conf_info[] = {
/* !!! Do NOT change ID for items defined already! Append a new one at the end! !!! */

    CONF_INFO(  1, conf.platformid,                             CONF_DEF_VALUE, i:PLATFORMID),

    CONF_INFO(  2, conf.fast_image_quality,                     CONF_DEF_VALUE, i:3),

    CONF_INFO(  3, conf.nd_filter_state,                        CONF_DEF_VALUE, i:0),

    CONF_INFO( 20, conf.save_raw,                               CONF_DEF_VALUE, i:0),
    CONF_INFO( 21, conf.raw_in_dir,                             CONF_DEF_VALUE, i:0),
    CONF_INFO( 22, conf.raw_prefix,                             CONF_DEF_VALUE, i:RAW_PREFIX_CRW),
    CONF_INFO( 23, conf.raw_ext,                                CONF_DEF_VALUE, i:DEFAULT_RAW_EXT),
    CONF_INFO( 24, conf.raw_save_first_only,                    CONF_DEF_VALUE, i:0),
    CONF_INFO( 25, conf.save_raw_in_video,                      CONF_DEF_VALUE, i:1),
    CONF_INFO( 26, conf.save_raw_in_sports,                     CONF_DEF_VALUE, i:0),
    CONF_INFO( 27, conf.save_raw_in_burst,                      CONF_DEF_VALUE, i:0),
    CONF_INFO( 28, conf.save_raw_in_ev_bracketing,              CONF_DEF_VALUE, i:0),
    CONF_INFO( 29, conf.save_raw_in_timer,                      CONF_DEF_VALUE, i:0),
    CONF_INFO( 30, conf.raw_cache,                              CONF_DEF_VALUE, i:1),
    CONF_INFO( 31, conf.save_raw_in_edgeoverlay,                CONF_DEF_VALUE, i:0),
    CONF_INFO( 32, conf.save_raw_in_auto,                       CONF_DEF_VALUE, i:0),
    CONF_INFO( 33, conf.bad_pixel_removal,                      CONF_DEF_VALUE, i:0),
    CONF_INFO( 34, conf.raw_timer,                              CONF_DEF_VALUE, i:0),
    CONF_INFO( 35, conf.raw_dng_ext,                            CONF_DEF_VALUE, i:1),
    CONF_INFO( 36, conf.dng_raw,                                CONF_DEF_VALUE, i:1),
    CONF_INFO( 37, conf.dng_version,                            CONF_DEF_VALUE, i:0),
    CONF_INFO( 38, conf.dng_usb_ext,                            CONF_DEF_VALUE, i:0),
    CONF_INFO( 39, conf.raw_nr,                                 CONF_DEF_VALUE, i:NOISE_REDUCTION_AUTO_CANON),
    CONF_INFO( 40, conf.bracketing_add_raw_suffix,              CONF_DEF_VALUE, i:0),			
    CONF_INFO( 41, conf.sub_batch_prefix,                       CONF_DEF_VALUE, i:RAW_PREFIX_SND), // SND_
    CONF_INFO( 42, conf.sub_batch_ext,                          CONF_DEF_VALUE, i:DEFAULT_RAW_EXT), // .CRW

    CONF_INFO( 50, conf.script_shoot_delay,                     CONF_DEF_VALUE, i:0),
    CONF_INFO( 51, conf.script_vars,                            CONF_INT_PTR,   i:0),
    CONF_INFO( 52, conf.script_param_set,                       CONF_DEF_VALUE, i:0),
    CONF_INFO( 53, conf.script_startup,                         CONF_DEF_VALUE, i:SCRIPT_AUTOSTART_NONE),
    CONF_INFO( 54, conf.script_file,                            CONF_CHAR_PTR,  ptr:""),
    CONF_INFO( 55, conf.script_param_save,                      CONF_DEF_VALUE, i:1),

    CONF_INFO( 60, conf.show_histo,                             CONF_DEF_VALUE, i:0),
    CONF_INFO( 61, conf.show_overexp,                           CONF_DEF_VALUE, i:1),
    CONF_INFO( 62, conf.histo_mode,                             CONF_DEF_VALUE, i:0),
    CONF_INFO( 63, conf.histo_auto_ajust,                       CONF_DEF_VALUE, i:1),
    CONF_INFO( 64, conf.histo_ignore_boundary,                  CONF_DEF_VALUE, i:4),
    CONF_INFO( 65, conf.histo_layout,                           CONF_DEF_VALUE, i:0),
    CONF_INFO( 66, conf.histo_show_ev_grid,                     CONF_DEF_VALUE, i:0),

    CONF_INFO( 70, conf.zebra_draw,                             CONF_DEF_VALUE, i:0),
    CONF_INFO( 71, conf.zebra_mode,                             CONF_DEF_VALUE, i:ZEBRA_MODE_BLINKED_2),
    CONF_INFO( 72, conf.zebra_restore_screen,                   CONF_DEF_VALUE, i:1),
    CONF_INFO( 73, conf.zebra_restore_osd,                      CONF_DEF_VALUE, i:1),
    CONF_INFO( 74, conf.zebra_over,                             CONF_DEF_VALUE, i:1),
    CONF_INFO( 75, conf.zebra_under,                            CONF_DEF_VALUE, i:0),
    CONF_INFO( 76, conf.zebra_draw_osd,                         CONF_DEF_VALUE, i:ZEBRA_DRAW_HISTO),
    CONF_INFO( 77, conf.zebra_multichannel,                     CONF_DEF_VALUE, i:0),

    CONF_INFO( 80, conf.video_mode,                             CONF_DEF_VALUE, i:0),
    CONF_INFO( 81, conf.video_quality,                          CONF_DEF_VALUE, i:VIDEO_DEFAULT_QUALITY),
    CONF_INFO( 82, conf.video_bitrate,                          CONF_DEF_VALUE, i:VIDEO_DEFAULT_BITRATE),
    CONF_INFO( 83, conf.clear_video,                            CONF_DEF_VALUE, i:0),
    CONF_INFO( 84, conf.mute_on_zoom,                           CONF_DEF_VALUE, i:0), 
    CONF_INFO( 85, conf.video_af_key,                           CONF_DEF_VALUE, i:0),
    CONF_INFO( 86, conf.unlock_optical_zoom_for_video,          CONF_DEF_VALUE, i:1), 
    CONF_INFO( 87, conf.fast_ev,                                CONF_DEF_VALUE, i:0),
    CONF_INFO( 88, conf.fast_ev_step,                           CONF_DEF_VALUE, i:1),
    CONF_INFO( 89, conf.fast_movie_control,                     CONF_DEF_VALUE, i:0),
    CONF_INFO( 90, conf.fast_movie_quality_control,             CONF_DEF_VALUE, i:0),
    CONF_INFO( 91, conf.ext_video_time,                         CONF_DEF_VALUE, i:0),

    CONF_INFO(100, conf.clear_override,                         CONF_DEF_VALUE, i:1),
    
    CONF_INFO(110, conf.tv_override_enabled,                    CONF_DEF_VALUE, i:0),
    CONF_INFO(111, conf.tv_enum_type,                           CONF_DEF_VALUE, i:TV_OVERRIDE_EV_STEP),
    CONF_INFO(112, conf.tv_override_value,                      CONF_DEF_VALUE, i:0),
    CONF_INFO(113, conf.tv_override_long_exp,                   CONF_DEF_VALUE, i:0),
    CONF_INFO(114, conf.tv_override_short_exp,                  CONF_DEF_VALUE, i:0),

    CONF_INFO(120, conf.av_override_enabled,                    CONF_DEF_VALUE, i:0),
    CONF_INFO(121, conf.av_override_value,                      CONF_DEF_VALUE, i:0),

    CONF_INFO(130, conf.iso_override_value,                     CONF_DEF_VALUE, i:0),
    CONF_INFO(131, conf.iso_override_koef,                      CONF_DEF_VALUE, i:0),
    
    CONF_INFO(140, conf.subj_dist_override_value,               CONF_DEF_VALUE, i:0),
    CONF_INFO(141, conf.subj_dist_override_koef,                CONF_DEF_VALUE, i:SD_OVERRIDE_OFF),
    
    CONF_INFO(150, conf.tv_bracket_value,                       CONF_DEF_VALUE, i:0),
    CONF_INFO(151, conf.av_bracket_value,                       CONF_DEF_VALUE, i:0),
    CONF_INFO(152, conf.iso_bracket_value,                      CONF_DEF_VALUE, i:0),
    CONF_INFO(153, conf.iso_bracket_koef,                       CONF_DEF_VALUE, i:0),
    CONF_INFO(154, conf.subj_dist_bracket_value,                CONF_DEF_VALUE, i:0),
    CONF_INFO(155, conf.subj_dist_bracket_koef,                 CONF_DEF_VALUE, i:0),
    CONF_INFO(156, conf.bracket_type,                           CONF_DEF_VALUE, i:0),
    CONF_INFO(157, conf.clear_bracket,                          CONF_DEF_VALUE, i:1),
    
    CONF_INFO(160, conf.autoiso_enable,                         CONF_DEF_VALUE, i:0),
    CONF_INFO(161, conf.autoiso_shutter_enum,                   CONF_DEF_VALUE, i:5), // 5='1/125'
    CONF_INFO(162, conf.autoiso_user_factor,                    CONF_DEF_VALUE, i:5),
    CONF_INFO(163, conf.autoiso_is_factor,                      CONF_DEF_VALUE, i:2),
    CONF_INFO(164, conf.autoiso_max_iso_hi,                     CONF_DEF_VALUE, i:550),
    CONF_INFO(165, conf.autoiso_max_iso_auto,                   CONF_DEF_VALUE, i:320),
    CONF_INFO(166, conf.autoiso_min_iso,                        CONF_DEF_VALUE, i:50),

    // AutoISO2
    CONF_INFO(170, conf.autoiso2_shutter_enum,                  CONF_DEF_VALUE, i:0), // 0="off" 6='1/20'
    CONF_INFO(171, conf.autoiso2_max_iso_auto,                  CONF_DEF_VALUE, i:600),
    CONF_INFO(172, conf.autoiso2_over,                          CONF_DEF_VALUE, i:1),
    CONF_INFO(173, conf.overexp_threshold,                      CONF_DEF_VALUE, i:5),
    CONF_INFO(174, conf.overexp_ev_enum,                        CONF_DEF_VALUE, i:0), // 0="off"

    CONF_INFO(180, conf.curve_file,                             CONF_CHAR_PTR,  ptr:""),
    CONF_INFO(181, conf.curve_enable,                           CONF_DEF_VALUE, i:0),

    CONF_INFO(190, conf.edge_overlay_enable,                    CONF_DEF_VALUE, i:0),
    CONF_INFO(191, conf.edge_overlay_thresh,                    CONF_DEF_VALUE, i:60),
    CONF_INFO(192, conf.edge_overlay_play,                      CONF_DEF_VALUE, i:0),
    CONF_INFO(193, conf.edge_overlay_pano,                      CONF_DEF_VALUE, i:0),
    CONF_INFO(194, conf.edge_overlay_zoom,                      CONF_DEF_VALUE, i:1),
	CONF_INFO(195, conf.edge_overlay_filter,                    CONF_DEF_VALUE, i:0),
	CONF_INFO(196, conf.edge_overlay_show,                      CONF_DEF_VALUE, i:0),
    CONF_INFO(197, conf.edge_overlay_pano_overlap,              CONF_DEF_VALUE, i:30),
    
    CONF_INFO(200, conf.remote_enable,                          CONF_DEF_VALUE, i:0),
    CONF_INFO(201, conf.synch_enable,                           CONF_DEF_VALUE, i:0),
    CONF_INFO(202, conf.synch_delay_enable,                     CONF_DEF_VALUE, i:0),
    CONF_INFO(203, conf.synch_delay_value,                      CONF_DEF_VALUE, i:100),
	CONF_INFO(204, conf.remote_switch_type,                     CONF_DEF_VALUE, i:0),
	CONF_INFO(205, conf.remote_control_mode,                    CONF_DEF_VALUE, i:0),
	CONF_INFO(206, conf.remote_enable_scripts,                  CONF_DEF_VALUE, i:0),
    CONF_INFO(207, conf.ricoh_ca1_mode,                         CONF_DEF_VALUE, i:0),

    CONF_INFO(210, conf.flash_sync_curtain,                     CONF_DEF_VALUE, i:0),
    CONF_INFO(211, conf.flash_video_override,                   CONF_DEF_VALUE, i:0),
    CONF_INFO(212, conf.flash_video_override_power,             CONF_DEF_VALUE, i:0),
    CONF_INFO(213, conf.flash_manual_override,                  CONF_DEF_VALUE, i:0),
    CONF_INFO(214, conf.flash_exp_comp,                         CONF_DEF_VALUE, i:9),
    CONF_INFO(215, conf.flash_enable_exp_comp,                  CONF_DEF_VALUE, i:0),

    CONF_INFO(220, conf.alt_mode_button,                        CONF_DEF_VALUE, i:KEY_PRINT),
    CONF_INFO(221, conf.alt_prevent_shutdown,                   CONF_DEF_VALUE, i:ALT_PREVENT_SHUTDOWN_ALT),
    CONF_INFO(222, conf.use_zoom_mf,                            CONF_DEF_VALUE, i:0),
    CONF_INFO(223, conf.zoom_assist_button_disable,             CONF_DEF_VALUE, i:0),
    CONF_INFO(224, conf.debug_lua_restart_on_error,             CONF_DEF_VALUE, i:0),
    CONF_INFO(225, conf.module_logging,                         CONF_DEF_VALUE, i:0),
    CONF_INFO(226, conf.flashlight,                             CONF_DEF_VALUE, i:0),

    CONF_INFO(230, conf.memdmp_start,                           CONF_DEF_VALUE, i:0),
    CONF_INFO(231, conf.memdmp_size,                            CONF_DEF_VALUE, i:0),

    CONF_INFO(999, conf.script_allow_lua_native_calls,          CONF_DEF_VALUE, i:0),

    {0,0,0,0,{0}}
};

void conf_info_func(unsigned short id)
{
    switch (id)
    {
    case  20:
    case  36: 
    case  37: 
        conf_change_dng(); 
        break;
#if defined (DNG_EXT_FROM)
    case  38: 
        {
        extern void save_ext_for_dng(void);
        save_ext_for_dng();
        cb_change_dng_usb_ext();
        }
        break;
#endif 
    case  54:
        script_load(conf.script_file);
        break;
    case  82: 
        shooting_video_bitrate_change(conf.video_bitrate);
        break;
    case 220:
#if CAM_ADJUSTABLE_ALT_BUTTON
        kbd_set_alt_mode_key_mask(conf.alt_mode_button);
#else
        conf.alt_mode_button = KEY_PRINT;
#endif
        break;
    case 221: 
        conf_update_prevent_shutdown(); 
        break;
    }
}

#ifdef CAM_HAS_GPS
static ConfInfo gps_conf_info[] = {
    // GPS
    CONF_INFO(  1, conf.gps_record,                 CONF_DEF_VALUE,     i:0),
    CONF_INFO(  2, conf.gps_navi_show,              CONF_DEF_VALUE,     i:0),
    CONF_INFO(  3, conf.gps_kompass_show,           CONF_DEF_VALUE,     i:0),
    CONF_INFO(  4, conf.gps_coordinates_show,       CONF_DEF_VALUE,     i:0),
    CONF_INFO(  5, conf.gps_height_show,            CONF_DEF_VALUE,     i:0),
    CONF_INFO(  6, conf.gps_waypoint_save,          CONF_DEF_VALUE,     i:0),
    CONF_INFO(  7, conf.gps_track_time,             CONF_DEF_VALUE,     i:1),
    CONF_INFO(  8, conf.gps_kompass_hide,           CONF_DEF_VALUE,     i:0),

    CONF_INFO(  9, conf.gps_wait_for_signal,        CONF_DEF_VALUE,     i:300),
    CONF_INFO( 10, conf.gps_kompass_time,           CONF_DEF_VALUE,     i:1),
    CONF_INFO( 11, conf.gps_navi_time,              CONF_DEF_VALUE,     i:1),
    CONF_INFO( 12, conf.gps_wait_for_signal_time,   CONF_DEF_VALUE,     i:5),
    CONF_INFO( 13, conf.gps_kompass_smooth,         CONF_DEF_VALUE,     i:7),
    CONF_INFO( 14, conf.gps_batt,                   CONF_DEF_VALUE,     i:25),
    CONF_INFO( 15, conf.gps_countdown,              CONF_DEF_VALUE,     i:0),
    CONF_INFO( 16, conf.gps_2D_3D_fix,              CONF_DEF_VALUE,     i:2),
    CONF_INFO( 17, conf.gps_countdown_blink,        CONF_DEF_VALUE,     i:1),
    
    CONF_INFO( 18, conf.gps_rec_play_set,           CONF_DEF_VALUE,     i:0),
    CONF_INFO( 19, conf.gps_play_dark_set,          CONF_DEF_VALUE,     i:0),
    CONF_INFO( 20, conf.gps_rec_play_time,          CONF_DEF_VALUE,     i:30),
    CONF_INFO( 21, conf.gps_play_dark_time,         CONF_DEF_VALUE,     i:45),

    CONF_INFO( 22, conf.gps_rec_play_set_1,         CONF_DEF_VALUE,     i:0),
    CONF_INFO( 23, conf.gps_play_dark_set_1,        CONF_DEF_VALUE,     i:0),
    CONF_INFO( 24, conf.gps_rec_play_time_1,        CONF_DEF_VALUE,     i:10),
    CONF_INFO( 25, conf.gps_play_dark_time_1,       CONF_DEF_VALUE,     i:15),
    CONF_INFO( 26, conf.gps_show_symbol,            CONF_DEF_VALUE,     i:0),
    CONF_INFO( 27, conf.gps_batt_warn,              CONF_DEF_VALUE,     i:0),
    CONF_INFO( 28, conf.gps_track_symbol,           CONF_DEF_VALUE,     i:0),
    CONF_INFO( 29, conf.gps_test_timezone,          CONF_DEF_VALUE,     i:0),
    CONF_INFO( 30, conf.gps_beep_warn,              CONF_DEF_VALUE,     i:0),
    CONF_INFO( 31, conf.gps_on_off,                 CONF_DEF_VALUE,     i:0),

    {0,0,0,0,{0}}
};
#endif

//-------------------------------------------------------------------
// ID offsets for ConfInfo mapping from Lua libraries
#define CONF_CORE   1000
#define CONF_OSD    2000
#define CONF_USER   3000
#define CONF_GPS    4000

#define CONF_FILE           "A/CHDK/CCHDK4.CFG"
#define OSD_CONF_FILE       "A/CHDK/OSD__4.CFG"
#define USER_MENU_CONF_FILE "A/CHDK/UMENU4.CFG"
#define GPS_CONF_FILE       "A/CHDK/GPS__4.CFG"
#define CONF_MAGICK_VALUE   (0x33204741)

typedef struct
{
    int         start_id, end_id;
    ConfInfo    *ci;
    char        *filename;
    void        (*info_func)(unsigned short id);
} confinfo_handler;

static const confinfo_handler confinfo_handlers[] = {
    { CONF_CORE, CONF_CORE+999, conf_info,           CONF_FILE,           conf_info_func },
    { CONF_OSD,  CONF_OSD +999, osd_conf_info,       OSD_CONF_FILE,       osd_conf_info_func },
    { CONF_USER, CONF_USER+999, user_menu_conf_info, USER_MENU_CONF_FILE, user_menu_conf_info_func },
#ifdef CAM_HAS_GPS
    { CONF_GPS,  CONF_GPS +999, gps_conf_info,       GPS_CONF_FILE,       0 },
#endif
    { 0,0,0,0,0 }
};

// mapping table to convert previous version (1.2) ConfInfo ID's to new version
static short conf_map_1_2[] =
{
    0,
    2001, // 1 conf.show_osd
    1020, // 2 conf.save_raw
    1050, // 3 conf.script_shoot_delay
    1060, // 4 conf.show_histo
    1051, // 5 conf.script_vars
    1052, // 6 conf.script_param_set
    2150, // 7 conf.show_dof
    2100, // 8 conf.batt_volts_max
    2101, // 9 conf.batt_volts_min
    0,
    2102, // 11 conf.batt_perc_show
    2103, // 12 conf.batt_volts_show
    2104, // 13 conf.batt_icon_show
    2090, // 14 conf.show_state
    2160, // 15 conf.show_values
    1061, // 16 conf.show_overexp
    1062, // 17 conf.histo_mode
    1063, // 18 conf.histo_auto_ajust
    1064, // 19 conf.histo_ignore_boundary
    1065, // 20 conf.histo_layout
    2020, // 21 conf.histo_pos
    2021, // 22 conf.dof_pos
    2022, // 23 conf.batt_icon_pos
    2023, // 24 conf.batt_txt_pos
    2024, // 25 conf.mode_state_pos
    2025, // 26 conf.values_pos
    2050, // 27 conf.histo_color
    2052, // 28 conf.osd_color
    0,
    2055, // 30 conf.menu_color
    2059, // 31 conf.reader_color
    1207, // 32 conf.ricoh_ca1_mode
    1226, // 33 conf.flashlight
    2230, // 34 conf.debug_shortcut_action
    1021, // 35 conf.raw_in_dir
    1022, // 36 conf.raw_prefix
    1023, // 37 conf.raw_ext
    2110, // 38 conf.reader_file
    2111, // 39 conf.reader_pos
    0,
    2080, // 41 conf.show_clock
    2026, // 42 conf.clock_pos
    2112, // 43 conf.reader_autoscroll
    2113, // 44 conf.reader_autoscroll_delay
    2114, // 45 conf.reader_rbf_file
    2115, // 46 conf.reader_codepage
    2120, // 47 conf.splash_show
    2051, // 48 conf.histo_color2
    1070, // 49 conf.zebra_draw
    1071, // 50 conf.zebra_mode
    1072, // 51 conf.zebra_restore_screen
    1073, // 52 conf.zebra_restore_osd
    1074, // 53 conf.zebra_over
    1075, // 54 conf.zebra_under
    2062, // 55 conf.zebra_color
    1076, // 56 conf.zebra_draw_osd
    3002, // 57 conf.user_menu_as_root
    2175, // 58 conf.zoom_value
    1222, // 59 conf.use_zoom_mf
    1024, // 60 conf.raw_save_first_only
    2116, // 61 conf.reader_wrap_by_words
    2130, // 62 conf.menu_symbol_enable
    1220, // 63 conf.alt_mode_button
    2135, // 64 conf.lang_file
    2136, // 65 conf.font_cp
    2131, // 66 conf.menu_rbf_file
    1221, // 67 conf.alt_prevent_shutdown
    2140, // 68 conf.show_grid_lines
    2141, // 69 conf.grid_lines_file
    1039, // 70 conf.raw_nr
    2142, // 71 conf.grid_force_color
    2060, // 72 conf.grid_color
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    2151, // 80 conf.dof_subj_dist_as_near_limit
    2152, // 81 conf.dof_use_exif_subj_dist
    2153, // 82 conf.dof_subj_dist_in_misc
    2154, // 83 conf.dof_near_limit_in_misc
    2155, // 84 conf.dof_far_limit_in_misc
    2156, // 85 conf.dof_hyperfocal_in_misc
    2157, // 86 conf.dof_depth_in_misc
    2161, // 87 conf.values_show_in_review
    2162, // 88 conf.values_show_zoom
    2163, // 89 conf.values_show_real_aperture
    2164, // 90 conf.values_show_real_iso
    2165, // 91 conf.values_show_market_iso
    2166, // 92 conf.values_show_iso_only_in_autoiso_mode
    2167, // 93 conf.values_show_ev_seted
    2168, // 94 conf.values_show_ev_measured
    2169, // 95 conf.values_show_bv_measured
    2170, // 96 conf.values_show_bv_seted
    2171, // 97 conf.values_show_overexposure
    2172, // 98 conf.values_show_luminance
    1080, // 99 conf.video_mode
    1081, // 100 conf.video_quality
    1082, // 101 conf.video_bitrate
    1112, // 102 conf.tv_override_value
    1110, // 103 conf.tv_override_enabled
    1121, // 104 conf.av_override_value
    1130, // 105 conf.iso_override_value
    1131, // 106 conf.iso_override_koef
    1140, // 107 conf.subj_dist_override_value
    1141, // 108 conf.subj_dist_override_koef
    1150, // 109 conf.tv_bracket_value
    1151, // 110 conf.av_bracket_value
    1152, // 111 conf.iso_bracket_value
    1153, // 112 conf.iso_bracket_koef
    1154, // 113 conf.subj_dist_bracket_value
    1155, // 114 conf.subj_dist_bracket_koef
    1156, // 115 conf.bracket_type
    1113, // 116 conf.tv_override_long_exp
    1114, // 117 conf.tv_override_short_exp
    1120, // 118 conf.av_override_enabled
    1999, // 119 conf.script_allow_lua_native_calls
    1053, // 120 conf.script_startup
    1200, // 121 conf.remote_enable
    2173, // 122 conf.values_show_canon_overexposure
    1100, // 123 conf.clear_override
    2002, // 124 conf.show_osd_in_review
    0,
    1157, // 126 conf.clear_bracket
    1077, // 127 conf.zebra_multichannel
    1003, // 128 conf.nd_filter_state
    1066, // 129 conf.histo_show_ev_grid
    2053, // 130 conf.osd_color_warn
    2061, // 131 conf.space_color
    2180, // 132 conf.space_icon_show
    2027, // 133 conf.space_icon_pos
    2181, // 134 conf.space_perc_show
    2182, // 135 conf.space_mb_show
    2028, // 136 conf.space_txt_pos
    2200, // 137 conf.show_remaining_raw
    2029, // 138 conf.mode_raw_pos
    2201, // 139 conf.show_raw_state
    2174, // 140 conf.show_values_in_video
    1111, // 141 conf.tv_enum_type
    3003, // 142 conf.user_menu_enable
    3001, // 143 conf.user_menu_vars
    2176, // 144 conf.zoom_scale
    2183, // 145 conf.space_bar_show
    2184, // 146 conf.space_bar_size
    2030, // 147 conf.space_ver_pos
    2031, // 148 conf.space_hor_pos
    2185, // 149 conf.space_bar_width
    2186, // 150 conf.space_perc_warn
    2187, // 151 conf.space_mb_warn
    2188, // 152 conf.space_warn_type
    2202, // 153 conf.remaining_raw_treshold
    1086, // 154 conf.unlock_optical_zoom_for_video
    2081, // 155 conf.clock_format
    2082, // 156 conf.clock_indicator
    2083, // 157 conf.clock_halfpress
    1160, // 158 conf.autoiso_enable
    1161, // 159 conf.autoiso_shutter_enum
    1162, // 160 conf.autoiso_user_factor
    1163, // 161 conf.autoiso_is_factor
    1164, // 162 conf.autoiso_max_iso_hi
    1165, // 163 conf.autoiso_max_iso_auto
    1166, // 164 conf.autoiso_min_iso
    2056, // 165 conf.menu_title_color
    2057, // 166 conf.menu_cursor_color
    2134, // 167 conf.menu_center
    1084, // 168 conf.mute_on_zoom
    1033, // 169 conf.bad_pixel_removal
    1085, // 170 conf.video_af_key
    2054, // 171 conf.osd_color_override
    2003, // 172 conf.override_disable
    2004, // 173 conf.override_disable_all
    2005, // 174 conf.hide_osd
    1025, // 175 conf.save_raw_in_video
    2210, // 176 conf.show_movie_time
    2211, // 177 conf.show_movie_refresh
    2032, // 178 conf.mode_video_pos
    1083, // 179 conf.clear_video
    1087, // 180 conf.fast_ev
    1088, // 181 conf.fast_ev_step
    2033, // 182 conf.mode_ev_pos
    2132, // 183 conf.menu_symbol_rbf_file
    2058, // 184 conf.menu_symbol_color
    1180, // 185 conf.curve_file
    1181, // 186 conf.curve_enable
    1190, // 187 conf.edge_overlay_enable
    1191, // 188 conf.edge_overlay_thresh
    2063, // 189 conf.edge_overlay_color
    1201, // 190 conf.synch_enable
    1202, // 191 conf.synch_delay_enable
    1203, // 192 conf.synch_delay_value
    0,
    1054, // 194 conf.script_file
    2234, // 195 conf.mem_view_addr_init
    1026, // 196 conf.save_raw_in_sports
    1027, // 197 conf.save_raw_in_burst
    1028, // 198 conf.save_raw_in_ev_bracketing
    1029, // 199 conf.save_raw_in_timer
    2203, // 200 conf.raw_exceptions_warn
    2133, // 201 conf.menu_select_first_entry
    1089, // 202 conf.fast_movie_control
    2220, // 203 conf.show_temp
    2034, // 204 conf.temp_pos
    1090, // 205 conf.fast_movie_quality_control
    0,
    0,
    2121, // 208 conf.start_sound
    1041, // 209 conf.sub_batch_prefix
    1042, // 210 conf.sub_batch_ext
    0,
    0,
    2231, // 213 conf.debug_display
    1055, // 214 conf.script_param_save
    2035, // 215 conf.ev_video_pos
    0,
    0,
    0,
    1040, // 219 conf.bracketing_add_raw_suffix
    2221, // 220 conf.temperature_unit
    0,
    1192, // 222 conf.edge_overlay_play
    1193, // 223 conf.edge_overlay_pano
    1194, // 224 conf.edge_overlay_zoom
    1030, // 225 conf.raw_cache
    1036, // 226 conf.dng_raw
    1210, // 227 conf.flash_sync_curtain
    1034, // 228 conf.raw_timer
    1001, // 229 conf.platformid
    1031, // 230 conf.save_raw_in_edgeoverlay
    1032, // 231 conf.save_raw_in_auto
    1211, // 232 conf.flash_video_override
    1212, // 233 conf.flash_video_override_power
    1035, // 234 conf.raw_dng_ext
    1038, // 235 conf.dng_usb_ext
    1213, // 236 conf.flash_manual_override
    1002, // 237 conf.fast_image_quality
    1224, // 238 conf.debug_lua_restart_on_error
    2232, // 239 conf.debug_propcase_page
    2233, // 240 conf.debug_misc_vals_show
    1195, // 241 conf.edge_overlay_filter
    1196, // 242 conf.edge_overlay_show
    1197, // 243 conf.edge_overlay_pano_overlap
    2240, // 244 conf.touchscreen_disable_video_controls
    2241, // 245 conf.touchscreen_disable_shortcut_controls
    2250, // 246 conf.usb_info_enable
    2036, // 247 conf.usb_info_pos
    1204, // 248 conf.remote_switch_type
    1205, // 249 conf.remote_control_mode
    1206, // 250 conf.remote_enable_scripts
    2189, // 251 conf.show_partition_nr
    1091, // 252 conf.ext_video_time
    4001, // 253 conf.gps_record
    4002, // 254 conf.gps_navi_show
    4003, // 255 conf.gps_kompass_show
    4004, // 256 conf.gps_coordinates_show
    4005, // 257 conf.gps_height_show
    4006, // 258 conf.gps_waypoint_save
    4007, // 259 conf.gps_track_time
    4008, // 260 conf.gps_kompass_hide
    4009, // 261 conf.gps_wait_for_signal
    4010, // 262 conf.gps_kompass_time
    4011, // 263 conf.gps_navi_time
    4012, // 264 conf.gps_wait_for_signal_time
    4013, // 265 conf.gps_kompass_smooth
    4014, // 266 conf.gps_batt
    4015, // 267 conf.gps_countdown
    4016, // 268 conf.gps_2D_3D_fix
    4017, // 269 conf.gps_countdown_blink
    4018, // 270 conf.gps_rec_play_set
    4019, // 271 conf.gps_play_dark_set
    4020, // 272 conf.gps_rec_play_time
    4021, // 273 conf.gps_play_dark_time
    4022, // 274 conf.gps_rec_play_set_1
    4023, // 275 conf.gps_play_dark_set_1
    4024, // 276 conf.gps_rec_play_time_1
    4025, // 277 conf.gps_play_dark_time_1
    4026, // 278 conf.gps_show_symbol
    4027, // 279 conf.gps_batt_warn
    4029, // 280 conf.gps_test_timezone
    4030, // 281 conf.gps_beep_warn
    4031, // 282 conf.gps_on_off
    1170, // 283 conf.autoiso2_shutter_enum
    1171, // 284 conf.autoiso2_max_iso_auto
    1172, // 285 conf.autoiso2_over
    1173, // 286 conf.overexp_threshold
    1174, // 287 conf.overexp_ev_enum
    1223, // 288 conf.zoom_assist_button_disable
    1037, // 289 conf.dng_version
    2137, // 290 conf.tbox_char_map
    2260, // 291 conf.show_alt_helper
    2261, // 292 conf.show_alt_helper_delay
    2263, // 293 conf.extra_button
    1225, // 294 conf.module_logging
    2262, // 295 conf.enable_shortcuts
    2270, // 296 conf.console_show
    2271, // 297 conf.console_timeout
    1230, // 298 conf.memdmp_start
    1231, // 299 conf.memdmp_size
    1214, // 300 conf.flash_exp_comp
    1215, // 301 conf.flash_enable_exp_comp
};

//-------------------------------------------------------------------
// make hash of memory block
unsigned int memhash31(unsigned char *mem, int len)
{
	unsigned hash=0;
	for (; len > 0; mem++, len-- )
		hash = *mem ^ (hash<<6) ^ (hash>>25);
	return hash;
}

static void config_update_last_saved(ConfInfo *ci)
{
    int i;
    for (i=0; ci[i].id > 0; ++i)
    {
        switch (ci[i].type)
        {
            case CONF_OSD_POS:
            case CONF_DEF_VALUE:
            case CONF_FUNC_PTR:
                switch (ci[i].size)
                {
                    case sizeof(int):
                        ci[i].last_saved = (unsigned int)*((int*)ci[i].var);
                        break;
                    case sizeof(short):
                        ci[i].last_saved = (unsigned int)*((short*)ci[i].var);
                        break;
                    case sizeof(char):
                        ci[i].last_saved = (unsigned int)*((char*)ci[i].var);
                        break;
                }
                break;
            case CONF_INT_PTR:
                ci[i].last_saved = memhash31((unsigned char*)ci[i].var, ci[i].size);
                break;
            case CONF_CHAR_PTR:
                ci[i].last_saved = lang_strhash31((int)ci[i].var);
                break;
        }
    }
}

static int config_has_changed(ConfInfo *ci)
{
    int i;
    for (i=0; ci[i].id > 0; ++i)
    {
        switch (ci[i].type)
        {
            case CONF_OSD_POS:
            case CONF_DEF_VALUE:
            case CONF_FUNC_PTR:
                switch (ci[i].size)
                {
                    case sizeof(int):
                        if (ci[i].last_saved != (unsigned int)*((int*)ci[i].var))
                            return 1;
                        break;
                    case sizeof(short):
                        if (ci[i].last_saved != (unsigned int)*((short*)ci[i].var))
                            return 1;
                        break;
                    case sizeof(char):
                        if (ci[i].last_saved != (unsigned int)*((char*)ci[i].var))
                            return 1;
                        break;
                }
                break;
            case CONF_INT_PTR:
                if (ci[i].last_saved != memhash31((unsigned char*)ci[i].var, ci[i].size))
                    return 1;
                break;
            case CONF_CHAR_PTR:
                if (ci[i].last_saved != lang_strhash31((int)ci[i].var))
                    return 1;
                break;
        }
    }

    return 0;
}

//-------------------------------------------------------------------
static void config_load_defaults(ConfInfo *ci, void (*info_func)(unsigned short id))
{
    register int i;

    for (i=0; ci[i].id > 0; ++i) {
        switch (ci[i].type) {
            case CONF_OSD_POS:
            case CONF_DEF_VALUE:
                memcpy(ci[i].var, &(ci[i].i), ci[i].size);
                break;
            case CONF_INT_PTR:
                memset(ci[i].var, 0, ci[i].size);
                break;
            case CONF_FUNC_PTR:
                *((int*)ci[i].var) = ci[i].func();
                break;
            case CONF_CHAR_PTR:
                memcpy(ci[i].var, ci[i].ptr, ci[i].size);
                break;
        }
        if (info_func) info_func(ci[i].id);
    }
}

void conf_load_defaults()
{
    int i;
    for (i=0; confinfo_handlers[i].ci != 0; i++)
        config_load_defaults(confinfo_handlers[i].ci, confinfo_handlers[i].info_func);
}

//-------------------------------------------------------------------

// Structure for saved conf info (allows for changes to ConfInfo without affecting saved configurations
typedef struct
{
    unsigned short id;
    unsigned short size;
} ConfInfoSave;

void config_save(ConfInfo *ci, const char *filename, int config_base)
{
// if Lua native calls are forced on, don't save state to config file since user did not select it
#if defined(OPT_FORCE_LUA_CALL_NATIVE)
    conf.script_allow_lua_native_calls = 0;
#endif

    register int i;
    
    for (i=0; ci[i].id > 0; i++);   // Find # of items

    int size = 2 * sizeof(int) + i * sizeof(ConfInfoSave);

    for (i=0; ci[i].id > 0; i++)
    {
        if (ci[i].type == CONF_STRUCT_PTR)
        {
            tVarArrayConfig *cfg = (tVarArrayConfig*)(ci[i].var);
            size += cfg->saved_size();
        }
        else
        {
            size += ci[i].size;
        }
    }

    char *buf = umalloc(size);
    char *p = buf;

    int fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0777); 
    if (fd >= 0)
    {
        int t = CONF_MAGICK_VALUE;
        memcpy(p, &t, sizeof(t));
        p += sizeof(t);

        t = config_base;
        memcpy(p, &t, sizeof(t));
        p += sizeof(t);

        for (i=0; ci[i].id > 0; ++i)
        {
            ((ConfInfoSave*)p)->id   = ci[i].id;
            ((ConfInfoSave*)p)->size = ci[i].size;
            p += sizeof(ConfInfoSave);
            if (ci[i].type == CONF_STRUCT_PTR)
            {
                tVarArrayConfig *cfg = (tVarArrayConfig*)(ci[i].var);
                p = cfg->save(p);
            }
            else
            {
                memcpy(p, ci[i].var, ci[i].size);
                // Clear out unused space after string config item value
                if ((ci[i].size == CONF_STR_LEN) && (strlen(ci[i].var) < CONF_STR_LEN))
                    memset(p+strlen(ci[i].var), 0, CONF_STR_LEN-strlen(ci[i].var));
                p += ci[i].size;
            }
        }

        write(fd, buf, p-buf);
        close(fd);
    }
    ufree(buf);

// if Lua native calls are forced on, re-enable native calls
#if defined(OPT_FORCE_LUA_CALL_NATIVE)
    conf.script_allow_lua_native_calls = 1;
#endif
}

void conf_save()
{
    int i;
    for (i=0; confinfo_handlers[i].ci != 0; i++)
    {
        if (config_has_changed(confinfo_handlers[i].ci) || ((confinfo_handlers[i].start_id == CONF_USER) && camera_info.state.user_menu_has_changed))
        {
            if (confinfo_handlers[i].start_id == CONF_USER)
        		user_menu_save();

            config_save(confinfo_handlers[i].ci, confinfo_handlers[i].filename, confinfo_handlers[i].start_id);
            config_update_last_saved(confinfo_handlers[i].ci);

            if (confinfo_handlers[i].start_id == CONF_CORE)
                save_params_values(0);
        }
    }
}

int save_config_file(int config_base, const char *filename)
{
    int i;
    for (i=0; confinfo_handlers[i].ci != 0; i++)
    {
        if ((config_base >= confinfo_handlers[i].start_id) && (config_base <= confinfo_handlers[i].end_id))
        {
            config_save(confinfo_handlers[i].ci, (filename != 0) ? filename : confinfo_handlers[i].filename, confinfo_handlers[i].start_id);
            if (filename == 0)  // Reset 'last_saved' values after saving default file
                config_update_last_saved(confinfo_handlers[i].ci);
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------
void config_restore(ConfInfo *ci, const char *filename, void (*info_func)(unsigned short id))
{
    int rcnt, i, offs;
    unsigned short id, size;

    char* buf = load_file(filename, &rcnt, 0);

    if (buf)
    {
        if (*(int*)buf == CONF_MAGICK_VALUE)
        {
            offs = 2 * sizeof(int);
            while (1)
            {
                if (offs + sizeof(short) > rcnt)
                    break;
                id = *((short*)(buf + offs));
                offs += sizeof(short);

                if (offs + sizeof(short) > rcnt)
                    break;
                size = *((short*)(buf + offs));
                offs += sizeof(short);

                for (i=0; ci[i].id > 0; ++i)
                {
                    if (ci[i].id==id && ci[i].size==size)
                    {
                        if (offs + size <= rcnt)
                        {
                            if (ci[i].type == CONF_STRUCT_PTR)
                            {
                                tVarArrayConfig *cfg = (tVarArrayConfig*)(ci[i].var);
                                size = cfg->load(buf+offs);
                            }
                            else
                            {
                                memcpy(ci[i].var, buf+offs, size);
                            }
                            if (info_func) info_func(ci[i].id);
                        }
                        break;
                    }
                }

                offs += size;
            }
        }
        free(buf);
    }
}

// Try loading old config file
static int config_restore_1_2(const char *filename)
{
    int rv = 0;
    int rcnt, i, offs;
    unsigned short id, size;

    char* buf = load_file(filename, &rcnt, 0);

    if (buf)
    {
        if (*(int*)buf == CONF_MAGICK_VALUE)
        {
            rv = 1;
            offs = sizeof(int);
            while (1)
            {
                if (offs + sizeof(short) > rcnt)
                    break;
                id = conf_map_1_2[*((short*)(buf + offs))];
                offs += sizeof(short);

                if (offs + sizeof(short) > rcnt)
                    break;
                size = *((short*)(buf + offs));
                offs += sizeof(short);

                ConfInfo *ci = 0;
                void (*info_func)(unsigned short id) = 0;
                for (i=0; confinfo_handlers[i].ci != 0; i++)
                {
                    if ((id >= confinfo_handlers[i].start_id) && (id <= confinfo_handlers[i].end_id))
                    {
                        ci = confinfo_handlers[i].ci;
                        info_func = confinfo_handlers[i].info_func;
                        id -= confinfo_handlers[i].start_id;
                        break;
                    }
                }

                if (ci != 0)
                {
                    for (i=0; ci[i].id > 0; ++i)
                    {
                        if (ci[i].id==id && ci[i].size==size)
                        {
                            if (offs + size <= rcnt)
                            {
                                if (ci[i].type == CONF_STRUCT_PTR)
                                {
                                    tVarArrayConfig *cfg = (tVarArrayConfig*)(ci[i].var);
                                    size = cfg->load(buf+offs);
                                }
                                else
                                {
                                    memcpy(ci[i].var, buf+offs, size);
                                }
                                if (info_func) info_func(ci[i].id);
                            }
                            break;
                        }
                    }
                }

                offs += size;
            }
        }
        free(buf);
    }

    return rv;
}

void conf_restore()
{
    int i;
    int old_config_loaded = 0;

    // init some defaults values
    init_user_menu(USER_MENU_ITEMS);

    // Load all defaults first, in case we end up loading old file
    conf_load_defaults();

    // Check if CORE config file exists, if not try loading old (1.2) file
    if (stat(confinfo_handlers[0].filename,0) != 0)
        old_config_loaded = config_restore_1_2("A/CHDK/CCHDK3.CFG");

    // Load all new files (that exist)
    for (i=0; confinfo_handlers[i].ci != 0; i++)
    {
        config_restore(confinfo_handlers[i].ci, confinfo_handlers[i].filename, confinfo_handlers[i].info_func);
        if (old_config_loaded == 0)
            config_update_last_saved(confinfo_handlers[i].ci);
    }

    // clear any "clear on restart" values
    clear_values();

// Enable Lua native calls if builder wants them forced on
#if defined(OPT_FORCE_LUA_CALL_NATIVE)
    conf.script_allow_lua_native_calls = 1;
#endif

// If curves not compiled in force option off
#if !defined(OPT_CURVES)
    conf.curve_enable = 0;
#endif
}

int load_config_file(int config_base, const char *filename)
{
    int i;
    for (i=0; confinfo_handlers[i].ci != 0; i++)
    {
        if ((config_base >= confinfo_handlers[i].start_id) && (config_base <= confinfo_handlers[i].end_id))
        {
            config_restore(confinfo_handlers[i].ci, (filename != 0) ? filename : confinfo_handlers[i].filename, confinfo_handlers[i].info_func);
            if (filename == 0)  // Reset 'last_saved' values if loading default file
                config_update_last_saved(confinfo_handlers[i].ci);
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------
static int getValue(ConfInfo *ci, unsigned short id, tConfigVal* configVal)
{
    unsigned short i;
    int ret = CONF_EMPTY;
    OSD_pos* pos;
    
    if( id==0 )
    {
        configVal->numb = 0;
        for ( i=0; ci[i].id > 0; ++i )
            if ( configVal->numb<ci[i].id )
                configVal->numb = ci[i].id;
        ret = CONF_VALUE;
    }
    else
    {
        for( i=0; ci[i].id > 0; ++i ) {
            if( ci[i].id==id ) {
                switch( ci[i].type ) {
                    case CONF_VALUE:
                    case CONF_FUNC_PTR:
                        switch( ci[i].size ) {
                            case sizeof(int):
                                configVal->numb = *(int*)ci[i].var;
                                ret = CONF_VALUE;
                            break;
                            case sizeof(short):
                                configVal->numb = *(short*)ci[i].var;
                                ret = CONF_VALUE;
                            break;
                            case sizeof(char):
                                configVal->numb = *(char*)ci[i].var;
                                ret = CONF_VALUE;
                            break;
                        }
                        configVal->pInt = (int*)ci[i].var;
                    break;
                    case CONF_INT_PTR:
                        configVal->numb = ci[i].size/sizeof(int);
                        configVal->pInt = (int*)ci[i].var;
                        ret = CONF_INT_PTR;
                    break;
                    case CONF_CHAR_PTR:
                        configVal->str = ci[i].var;
                        ret = CONF_CHAR_PTR;
                    break;
                    case CONF_OSD_POS:
                        pos = (OSD_pos*)ci[i].var;
                        configVal->pos.x = pos->x;
                        configVal->pos.y = pos->y;
                        ret = CONF_OSD_POS;
                        configVal->pInt = (int*)ci[i].var;
                    break;
                }
                break;
            }
        }
    }
    return ret;
}

int conf_getValue(unsigned short id, tConfigVal* configVal)
{
    int i;

    if (id < CONF_CORE)
        id = conf_map_1_2[id];  // Convert old ID to new ID

    for (i=0; confinfo_handlers[i].ci != 0; i++)
        if ((id >= confinfo_handlers[i].start_id) && (id <= confinfo_handlers[i].end_id))
            return getValue(confinfo_handlers[i].ci, id - confinfo_handlers[i].start_id, configVal);

    return CONF_EMPTY;
}

//-------------------------------------------------------------------
static int config_autosave = 1;

static int setValue(ConfInfo *ci, unsigned short id, tConfigVal configVal)
{
    unsigned short i;
    int ret = CONF_EMPTY, len, len2;
    OSD_pos* pos;
    
    // Don't allow scripts to enable Lua native calls.
    if (id == 999) return ret;

    for ( i=0; ci[i].id > 0; ++i )
    {
        if( ci[i].id==id )
        {
            switch( ci[i].type ) {
                case CONF_VALUE:
                case CONF_FUNC_PTR:
                    if( configVal.isNumb ) {
                        switch( ci[i].size ) {
                            case sizeof(int):
                                *(int*)ci[i].var = (int)configVal.numb;
                                ret = CONF_VALUE;
                            break;
                            case sizeof(short):
                                *(short*)ci[i].var = (short)configVal.numb;
                                ret = CONF_VALUE;
                            break;
                            case sizeof(char):
                                *(char*)ci[i].var = (char)configVal.numb;
                                ret = CONF_VALUE;
                            break;
                        }
                    }
                break;
                case CONF_INT_PTR:
                    if( configVal.isPInt ) {
                        len = ci[i].size;
                        len2 = configVal.numb*sizeof(int);
                        if( len2<len ) len = len2;
                        memcpy(ci[i].var, configVal.pInt, len);
                        ret = CONF_INT_PTR;
                    }
                break;
                case CONF_CHAR_PTR:
                    if( configVal.isStr ) {
                        len = strlen(configVal.str);
                        if( len>0 && len<CONF_STR_LEN) {
                            strncpy(ci[i].var, configVal.str ,len+1);
                        }
                        ret = CONF_CHAR_PTR;
                    }
                break;
                case CONF_OSD_POS:
                    if( configVal.isPos ) {
                        pos = (OSD_pos*)ci[i].var;
                        pos->x = configVal.pos.x;
                        pos->y = configVal.pos.y;
                        ret = CONF_OSD_POS;
                    }
                break;
            }
            break;
        }
    }

    if ((ret!=CONF_EMPTY) && (config_autosave))
        conf_save();

    return ret;
}

int conf_setValue(unsigned short id, tConfigVal configVal)
{
    int i;

    if (id < CONF_CORE)
        id = conf_map_1_2[id];  // Convert old ID to new ID

    for (i=0; confinfo_handlers[i].ci != 0; i++)
        if ((id >= confinfo_handlers[i].start_id) && (id <= confinfo_handlers[i].end_id))
            return setValue(confinfo_handlers[i].ci, id - confinfo_handlers[i].start_id, configVal);

    return CONF_EMPTY;
}

void conf_setAutosave(int n)
{
    config_autosave = (n == 0) ? 0 : 1;
}

//-------------------------------------------------------------------
// Common code extracted from raw.c (raw_savefile) and gui_osd.c (gui_osd_draw_raw_info)
// returns 0 if RAW save is disabled due to mode settings, etc, return 1 if RAW save OK
/*
is raw disabled by exceptions
*/
int is_raw_exception() {
    int m = camera_info.state.mode_shooting;
    // NOTE: the conf.save_raw_in variables are negative logic
    //       1 = disable saving raw in this mode, 0 = allow saving raw
    //       variables should be named conf.disable_save_raw_in_XXX
    return (
        (is_video_recording() && conf.save_raw_in_video) ||                                 // True is movie mode and save_raw_in_video is disabled
        (shooting_get_resolution()==5) ||                                                   // True if Canon RAW enabled, for cams that treat it as a resolution setting (g9, g10, s90, sx1? not g12, g1x)
        ((m==MODE_SPORTS) && conf.save_raw_in_sports) ||                                    // True if sports mode and save_raw_in_sports is disabled
        ((m==MODE_AUTO) && conf.save_raw_in_auto) ||                                        // True if auto mode and save_raw_in_auto is disabled
        (conf.edge_overlay_enable && conf.save_raw_in_edgeoverlay) ||                       // True if edge overlay on and save_raw_in_edgeoverlay is disabled
        ((shooting_get_drive_mode()==1) && conf.save_raw_in_burst && !(m==MODE_SPORTS)) ||  // True if drive mode is continuous and save_raw_in_burst is disabled and not sports mode
        ((shooting_get_drive_mode()>=2) && conf.save_raw_in_timer) ||                       // True if drive mode is timer and save_raw_in_timer is disabled
        ((shooting_get_prop(PROPCASE_BRACKET_MODE)==1) && conf.save_raw_in_ev_bracketing)   // True if bracketing enabled and save_raw_in_ev_bracketing is disabled
    );
}

/*
is raw possible (i.e. valid raw buffer exists in current mode)
TODO this might be better as a platform lib.c function rather than a bunch of camera.h ifdefs
*/
int is_raw_possible() {
    int m = camera_info.state.mode_shooting;
    return !(0   // Return false if any of these tests are true
#ifdef CAM_DISABLE_RAW_IN_AUTO
       || (m == MODE_AUTO)                   // some cameras don't have valid raw in auto mode
#endif
#ifdef CAM_DISABLE_RAW_IN_ISO_3200
       || (m == MODE_SCN_ISO_3200)           // some cameras don't have valid raw in ISO3200 binned mode, not the same as low light
#endif
#ifdef CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE
       || (shooting_get_resolution()==7)     // True if shooting resolution is 'low light'
#endif
#if defined(CAM_DISABLE_RAW_IN_HQ_BURST)
       || (m == MODE_SCN_HIGHSPEED_BURST)    // True if HQ Burst mode (SX40HS corrupts JPEG images if RAW enabled in this mode)
#endif
#if defined(CAM_DISABLE_RAW_IN_HANDHELD_NIGHT_SCN)
       || (m == MODE_NIGHT_SCENE)            // True if HandHeld Night Scene (SX40HS corrupts JPEG images if RAW enabled in this mode)
#endif
    );
}

int is_raw_enabled()
{
    return is_raw_possible() && !is_raw_exception();
}

//-------------------------------------------------------------------
