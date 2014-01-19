#ifndef CAMERA_INFO_H
#define CAMERA_INFO_H

// CHDK camera info interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//==========================================================

#include "stdlib.h"

//==========================================================
// Data Structure to store camera specific information
// Used by modules to ensure module code is platform independent

typedef struct {
	_version_t api_version;     // version of this structure

    int bits_per_pixel;
    int black_level;
    int white_level;
    int raw_rows, raw_rowpix, raw_rowlen, raw_size;
    union                       // DNG JPEG info
    {
        struct
        {
            int x, y;           // DNG JPEG top left corner
            int width, height;  // DNG JPEG size
        } jpeg;
        struct
        {
            int origin[2];
            int size[2];
        } crop;
    };
    union                       // DNG active sensor area (Y1, X1, Y2, X2)
    {
        struct
        {
            int y1, x1, y2, x2;
        } active_area;
        int dng_active_area[4];
    };
    int lens_info[8];           // DNG Lens Info
    int exposure_bias[2];       // DNG Exposure Bias
    int cfa_pattern;
    int calibration_illuminant1;
    int color_matrix1[18];      // DNG Color Matrix
    int calibration_illuminant2;
    int color_matrix2[18];      // DNG Color Matrix 2
    int has_calibration1;
    int camera_calibration1[18];// DNG Camera Calibration Matrix 1
    int has_calibration2;
    int camera_calibration2[18];// DNG Camera Calibration Matrix 2
    int has_forwardmatrix1;
    int forward_matrix1[18];    // DNG Camera Forward Matrix 1
    int has_forwardmatrix2;
    int forward_matrix2[18];    // DNG Camera Forward Matrix 1
    int dng_badpixel_value_limit;
} _cam_sensor;

extern _cam_sensor camera_sensor;

typedef struct 
{
	_version_t api_version; 			                // version of this structure

    int     width, height, size;                        // Size of bitmap screen in CHDK co-ordinates
    int     physical_width;                             // Actual width of bitmap screen in pixels
    int     buffer_width, buffer_height, buffer_size;   // Physical size of bitmap screen
    int     edge_hmargin, ts_button_border;             // margin and touch-screen adjustment values
    int     zebra_nobuf, zebra_aspect_adjust;           // zebra feature settings
    int     has_variable_aspect;                        // zebra feature settings
    int     menu_border_width;                          // Width of border on each side of CHDK menu
} _cam_screen;

extern _cam_screen camera_screen;

typedef struct
{
    unsigned int    tick_count;         // tick count of last call to function
    unsigned int    last, min, max, sum, count;
} time_counter;

typedef struct
{
	_version_t api_version; 			// version of this structure

    // Canon PARAMS indexes
    struct
    {
        int camera_name;
        int owner_name;
        int artist_name;
        int copyright;
    } params;
    // Canon PROPCASE indexes
    struct
    {
        int propset;
        int gps;
        int orientation_sensor;
        int tv;
        int av;
        int min_av;
        int ev_correction_1;
        int ev_correction_2;
        int flash_mode;
        int flash_fire;
        int metering_mode;
        int wb_adj;
        int aspect_ratio;
        int shooting;
        int resolution;
        int quality;
    } props;
    int rombaseaddr, maxramaddr, memisosize;
    int cam_uncached_bit, exmem;
    int text_start, data_start, bss_start, bss_end;     // Link values (used for debug)
    int tick_count_offset;      // get_tick_count value at which the clock ticks over 1 second
    char* platform;
    char* platformsub;
    char* chdk_ver;
    char* build_number;
    char* chdk_dng_ver;
    char* build_svnrev;
    char* build_date;
    char* build_time;
    char* os;
    int cam_ev_in_video;            // Can CHDK can change exposure in video mode?
    int cam_has_nd_filter;
    int cam_has_iris_diaphragm;
    int cam_has_video_button, cam_has_zoom_lever;
    int cam_has_manual_focus;
    int cam_has_multipart;
    int cam_remote_sync_status_led;
    int cam_key_press_delay, cam_key_release_delay;
    int cam_af_led;
    // Miscellaneous variables to record state information
    // Used to control communication between various tasks and modules
    struct
    {
        int     edge_state_draw;            // Current state of overlay (Live/Frozen/Pano)
        int     is_shutter_half_press;      // State of Shutter Half Press button
        int     auto_started;               // Set to 1 if script auto-started
        int     user_menu_has_changed;      // not saved to config file, used to tell code that file needs to be saved
        int     kbd_last_clicked;           // For scripts
        long    kbd_last_clicked_time;      // For scripts
        long    kbd_last_checked_time;      // For scripts
        long    shutter_open_time;          // For DNG EXIF creation
        long    shutter_open_tick_count;    // For DNG EXIF creation
        int     state_shooting_progress;    // Holds current state when still image being processed
        int     state_kbd_script_run;       // Script execution state
        int     osd_title_line;             // Display state of CHDK OSD title line

        int     gui_mode;                   // Current GUI mode (from gui_get_mode())
        int     gui_mode_none;              // Current GUI mode == GUI_MODE_NONE
        int     gui_mode_alt;               // Current GUI mode == GUI_MODE_ALT

        int     mode;                       // Camera mode info
        int     mode_shooting;              // Camera shooting mode
        int     mode_video;                 // Are we in camera video mode
        int     mode_rec;                   // Are we in camera record mode (still image)
        int     mode_rec_or_review;         // Are we in camera record mode (still image) or review hold & OSD displayed in review hold
        int     mode_play;                  // Are we in camera playback mode
        int     mode_photo;                 // Are we in camera photo mode (playback or not video and not stitch)
                                            //  - why is some functionality disabled in MODE_STITCH; but not MODE_SCN_STICH (e.g. bracketing) ?????
    } state;

    // Performance counters
    struct
    {
        unsigned int    md_detect_tick;     // Tick count of last motion detection
        int             md_af_tuning;       // Flag to enable/disable the Motion Detect tuning code using the AF LED
        int             af_led_on;          // Counter to time AF led turn on (for AF LED MD tuning)
        time_counter    af_led;             // Counters for AF led MD timing
        int             md_af_on_flag;      // Flag to turn on AF led after MD detects motion (to calculate delay from detect to capture)
        unsigned int    md_af_on_delay;     // How long after MD triggers to wait before turning on AF led
        unsigned int    md_af_on_time;      // How long to leave AF led on for
    } perf;
} _cam_info;

extern _cam_info camera_info;

extern void camera_info_init();

//==========================================================

#endif /* CAMERA_INFO_H */
