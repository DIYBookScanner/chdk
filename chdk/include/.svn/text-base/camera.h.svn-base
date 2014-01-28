// camera.h

#ifdef CHDK_MODULE_CODE
#error camera.h cannot be #included in module code (did you mean camera_info.h).
#endif

// This file contains the default values for various settings that may change across camera models.
// Setting values specific to each camera model can be found in the platform/XXX/platform_camera.h file for camera.

// If adding a new settings value put a suitable default value in here, along with documentation on
// what the setting does and how to determine the correct value.
// If the setting should not have a default value then add it here using the '#undef' directive
// along with appropriate documentation.

#ifndef CAMERA_H
#define CAMERA_H

//==========================================================
// Camera-dependent settings
//==========================================================

//----------------------------------------------------------
// Default values
//----------------------------------------------------------

    #undef  CAM_DRYOS                           // Camera is DryOS-based
    #undef  CAM_PROPSET                         // Camera's properties group (the generation)
    #define CAM_FLASHPARAMS_VERSION         3   // flash parameters structure version (every camera from 2005 on is version 3)
    #undef  CAM_DRYOS_2_3_R31                   // Define for cameras with DryOS release R31 or greater -> G10
    #undef  CAM_DRYOS_2_3_R39                   // Define for cameras with DryOS release R39 or greater
    #undef  CAM_DRYOS_2_3_R47                   // Define for cameras with DryOS release R47 or greater -> Cameras can boot from FAT32

    #undef  CAM_HAS_CMOS                        // Camera has CMOS sensor
    #undef  CAM_SWIVEL_SCREEN                   // Camera has rotated LCD screen
    #define CAM_USE_ZOOM_FOR_MF             1   // Zoom lever can be used for manual focus adjustments
    #define CAM_DEFAULT_ALT_BUTTON  KEY_PRINT   // alt button for cameras without adjustable alt
                                                // redefine if not print to avoid need for KEY_PRINT alias in keymap
    #undef  CAM_ADJUSTABLE_ALT_BUTTON           // ALT-button can be set from menu, must set next two values as well
    #undef  CAM_ALT_BUTTON_NAMES                // Define the list of names for the ALT button   - e.g. { "Print", "Display" }
    #undef  CAM_ALT_BUTTON_OPTIONS              // Define the list of options for the ALT button - e.g. { KEY_PRINT, KEY_DISPLAY }
    #define CAM_REMOTE                      1   // Camera supports USB-remote
    #undef  CAM_REMOTE_USES_PRECISION_SYNC      // Disable experimental USB remote  precision sync patch
    #undef  GPIO_VSYNC_CURRENT                  // USB remote precision sync : might be 0xC0F070C8 or 0xC0F07008 (http://chdk.setepontos.com/index.php?topic=8312.msg104027#msg104027)
    #undef  CAM_MULTIPART                       // Camera supports SD-card multipartitioning
    #define CAM_HAS_ZOOM_LEVER              1   // Camera has dedicated zoom buttons
    #undef  CAM_DRAW_EXPOSITION                 // Output expo-pair on screen (for cameras which (sometimes) don't do that)
    #define CAM_HAS_ERASE_BUTTON            1   // Camera has dedicated erase button
    #define CAM_HAS_DISP_BUTTON             1   // Camera has dedicated DISP button
    #define CAM_HAS_IRIS_DIAPHRAGM          1   // Camera has real diaphragm mechanism (http://en.wikipedia.org/wiki/Diaphragm_%28optics%29)
    #undef  CAM_HAS_ND_FILTER                   // Camera has build-in ND filter
    #undef  CAM_HAS_NATIVE_ND_FILTER            // Camera has built-in ND filter with Canon menu support for enable/disable
    #define CAM_CAN_SD_OVER_NOT_IN_MF       1   // Camera allows subject distance (focus) override when not in manual focus mode
    #undef  CAM_CAN_SD_OVER_IN_AF_LOCK          // Camera allows subject distance (focus) override when in AF Lock mode
    #undef  CAM_CAN_SD_OVER_IN_AF_LOCK_ONLY     // Camera allows subject distance (focus) override only when in AF Lock mode OR in movie mode
    #define CAM_CAN_SD_OVERRIDE             1   // Camera allows to do subject distance override
    #define CAM_HAS_MANUAL_FOCUS            1   // Camera has manual focus mode
    #define CAM_HAS_USER_TV_MODES           1   // Camera has tv-priority or manual modes with ability to set tv value
    #undef  CAM_SHOW_OSD_IN_SHOOT_MENU          // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1 // Camera can unlock optical zoom in video (if it is locked)
    #undef  CAM_FEATURE_FEATHER                 // Cameras with "feather" or touch wheel.
    #define CAM_HAS_IS                      1   // Camera has image stabilizer
    #undef  CAM_HAS_JOGDIAL                     // Camera has a "jog dial"

    #undef  CAM_CONSOLE_LOG_ENABLED             // Development: internal camera stdout -> A/stdout.txt
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU     1   // In CHDK for this camera realized adjustable video compression
    #undef  CAM_CAN_MUTE_MICROPHONE             // Camera has function to mute microphone

    #define CAM_EMUL_KEYPRESS_DELAY         40  // Delay to interpret <alt>-button press as longpress
    #define CAM_EMUL_KEYPRESS_DURATION      5   // Length of keypress emulation

    #define CAM_MENU_BORDERWIDTH            30  // Defines the width of the border on each side of the CHDK menu. The CHDK menu will have this
                                                // many pixels left blank to the on each side. Should not be less than 10 to allow room for the
                                                // scroll bar on the right.

    #undef  CAM_TOUCHSCREEN_UI                  // Define to enable touch screen U/I (e.g. IXUS 310 HS)
    #define CAM_TS_BUTTON_BORDER            0   // Define this to leave a border on each side of the OSD display for touch screen buttons.
                                                // Used on the IXUS 310 to stop the OSD from overlapping the on screen buttons on each side
    #define CAM_DISP_ALT_TEXT               1   // Display the '<ALT>' message at the bottom of the screen in ALT mode (IXUS 310 changes button color instead)

    #undef  CAM_AF_SCAN_DURING_VIDEO_RECORD     // CHDK can make single AF scan during video record
    #undef  CAM_RESET_AEL_AFTER_VIDEO_AF        // Cam needs AE Lock state reset after AF in video recording
    #undef  CAM_HAS_VIDEO_BUTTON                // Camera can take stills in video mode, and vice versa
    #undef  CAM_EV_IN_VIDEO                     // CHDK can change exposure in video mode
    #define CAM_VIDEO_CONTROL               1   // pause / unpause video recordings
    #undef  CAM_VIDEO_QUALITY_ONLY              // Override Video Bitrate is not supported
    #undef  CAM_CHDK_HAS_EXT_VIDEO_TIME         // Camera can override time limit of video record -> sx220/230
    #undef  CAM_HAS_MOVIE_DIGEST_MODE           // The values in the 'movie_status' variable change if the camera has this mode (see is_video_recording())
    #undef  CAM_HAS_SPORTS_MODE                 // Define to enable the RAW exception override control for SPORTS mode (s3is, sx30, sx40, etc)

    #undef  CAM_REAR_CURTAIN                    // Camera do not have front/rear curtain flash sync in menu
    #undef  CAM_BRACKETING                      // Cameras that have bracketing (focus & ev) in original firmware already, most likely s- & g-series (propcase for digic III not found yet!)
    #undef  CAM_EXT_TV_RANGE                    // CHDK can make exposure time longer than 64s
    #define CAM_EXT_AV_RANGE                6   // Number of 1/3 stop increments to extend the Av range beyond the Canon default smallest aperture
                                                //  override in platform_camera.h for cameras with different range (e.g. G1X can't go below F/16 so set this to 0)
    #define CAM_CHDK_PTP                    1   // include CHDK PTP support

    #undef  CAM_HAS_FILEWRITETASK_HOOK          // FileWriteTask hook is available (local file write can be prevented)
    #undef  CAM_FILEWRITETASK_SEEKS             // Camera's FileWriteTask can do Lseek() - DryOS r50 or higher, the define could also be CAM_DRYOS_2_3_R50

    #define CAM_UNCACHED_BIT                0x10000000 // bit indicating the uncached memory

    #define CAM_SENSOR_BITS_PER_PIXEL       10  // Bits per pixel. 10 is standard, 12 is supported except for curves
    #define CAM_WHITE_LEVEL                 ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)      // 10bpp = 1023 ((1<<10)-1), 12bpp = 4095 ((1<<12)-1)
    #define CAM_BLACK_LEVEL                 ((1<<(CAM_SENSOR_BITS_PER_PIXEL-5))-1)  // 10bpp = 31 ((1<<5)-1),    12bpp = 127 ((1<<7)-1)

    #define CAM_BITMAP_PALETTE              1   // which color set is used for this camera

    // Older cameras had a screen/bitmap buffer that was 360 pixels wide (or 480 for wide screen models)
    // CHDK was built around this 360 pixel wide display model
    // Newer cameras have a 720 pixel wide bitmap (960 for wide screen cameras)
    // To accomadate this the CHDK co-ordinate system assumes a 360/480 wide buffer and the
    // pixel drawing routines draw every pixel twice to scale the image up to the actual buffer size
    // Define CAM_USES_ASPECT_CORRECTION with a value of 1 to enable this scaled display
    #define CAM_USES_ASPECT_CORRECTION      0
    #define CAM_SCREEN_WIDTH                360 // Width of bitmap screen in CHDK co-ordinates (360 or 480)
    #define CAM_SCREEN_HEIGHT               240 // Height of bitmap screen in CHDK co-ordinates (always 240 on all cameras so far)
    #define CAM_BITMAP_WIDTH                360 // Actual width of bitmap screen in bytes (may be larger than displayed area)
    #define CAM_BITMAP_HEIGHT               240 // Actual height of bitmap screen in rows (240 or 270)

    #define EDGE_HMARGIN                    0   // define sup and inf screen margins on edge overlay without overlay.  Necessary to save memory buffer space. sx200is needs values other than 0

    #undef CAM_QUALITY_OVERRIDE                 // define this in platform_camera.h to enable 'Super Fine' JPEG compression mode
                                                // used to allow super fine JPEG option on cameras where this has been removed
                                                // from the Canon menu. Note: may not actually work on all cameras.

    #undef  CAM_ZEBRA_NOBUF                     // zebra draws directly on bitmap buffer.
    #undef  CAM_HAS_VARIABLE_ASPECT             // can switch between 16:9 and 4:3 (used by zebra code)
    
    #undef  CAM_DATE_FOLDER_NAMING              // set if camera uses date based folder naming (Option "Create Folder" in Canon Menu) and get_target_dir_name is implemented
    
    #define CAM_KEY_PRESS_DELAY             30  // delay after a press - TODO can we combine this with above ?
    #define CAM_KEY_RELEASE_DELAY           30  // delay after a release - TODO do we really need to wait after release ?

    #undef  CAM_STARTUP_CRASH_FILE_OPEN_FIX     // enable fix for camera intermittently crash at startup when opening the conf / font files
                                                // Some cameras throw "ASSERT!! FsIoNotify.c Line xxx    Task name: SpyTask" in ROMLOG
                                                // NOTE enabled for all DRYOS below
    
    // RAW & DNG related values
    #define DEFAULT_RAW_EXT                 1   // extension to use for raw (see raw_exts in conf.c)
    #define DNG_BADPIXEL_VALUE_LIMIT        0   // Max value of 'bad' pixel - this value or lower is considered a defective pixel on the sensor
    #undef  CAM_RAW_ROWPIX                      // Number of pixels in RAW row (physical size of the sensor Note : as of July 2011, this value can be found in stub_entry.S for dryos cameras)
    #undef  CAM_RAW_ROWS                        // Number of rows in RAW (physical size of the sensor       Note : as of July 2011, this value can be found in stub_entry.S for dryos cameras)
    #undef  CAM_JPEG_WIDTH                      // Default crop size (width) stored in DNG (to match camera JPEG size. From dimensions of the largest size jpeg your camera produces)
    #undef  CAM_JPEG_HEIGHT                     // Default crop size (height) stored in DNG (to match camera JPEG size. From dimensions of the largest size jpeg your camera produces)
    #undef  CAM_ACTIVE_AREA_X1                  // Define usable area of the sensor - needs to be divisible by 4 - calibrate using a CHDK RAW image converted with rawconvert.exe (eg :rawconvert -12to8 -pgm -w=4480 -h=3348 photo.crw photo.pgm)
    #undef  CAM_ACTIVE_AREA_Y1                  // Define usable area of the sensor - needs to be divisible by 2 - "
    #undef  CAM_ACTIVE_AREA_X2                  // Define usable area of the sensor - needs to be divisible by 4 - "
    #undef  CAM_ACTIVE_AREA_Y2                  // Define usable area of the sensor - needs to be divisible by 2 = "
    #undef  cam_CFAPattern                      // Camera Bayer sensor data layout (DNG colors are messed up if not correct)
                                                //   should be 0x01000201 = [Green Blue Red Green], 0x02010100 = [Red Green Green Blue] or 0x01020001 = [Green Red Blue Green]
    #undef  CAM_COLORMATRIX1                    // DNG color profile matrix
    #undef  cam_CalibrationIlluminant1          // DNG color profile illuminant - set it to 17 for standard light A
    #undef  CAM_COLORMATRIX2                    // DNG color profile matrix 2
    #undef  cam_CalibrationIlluminant2          // DNG color profile illuminant 2 - set it to 21 for D65
    #undef  CAM_CAMERACALIBRATION1              // DNG camera calibration matrix 1
    #undef  CAM_CAMERACALIBRATION2              // DNG camera calibration matrix 2
    #undef  CAM_FORWARDMATRIX1                  // DNG camera forward matrix 1
    #undef  CAM_FORWARDMATRIX2                  // DNG camera forward matrix 2
    #undef  CAM_DNG_EXPOSURE_BIAS               // Specify DNG exposure bias value (to override default of -0.5 in the dng.c code)
    #undef  DNG_EXT_FROM                        // Extension in the cameras known extensions to replace with .DNG to allow DNG
                                                // files to be transfered over standard PTP. Only applicable to older cameras

    #undef  CAM_DNG_LENS_INFO                   // Define this to include camera lens information in DNG files
                                                // Value should be an array of 4 DNG 'RATIONAL' values specifying
                                                //   - min focal length in mm
                                                //   - max focal length in mm
                                                //   - max aperture at min focal length
                                                //   - max aperture at max focal length
                                                // E.G - SX30 = { 43,10, 1505,10, 27,10, 58,10 }
                                                //            = 4.3 - 150.5mm, f/2.7 - f.5.8
                                                // Each pair of integers is one 'RATIONAL' value (numerator,denominator)

    #undef  PARAM_CAMERA_NAME                   // parameter number for GetParameterData to get camera name
    #undef  PARAM_OWNER_NAME                    // parameter number for GetParameterData to get owner name
    #undef  PARAM_ARTIST_NAME                   // parameter number for GetParameterData to get artist name
    #undef  PARAM_COPYRIGHT                     // parameter number for GetParameterData to get copyright
    #undef  PARAM_DISPLAY_MODE1                 // param number for LCD display mode when camera in playback
    #undef  PARAM_DISPLAY_MODE2                 // param number for LCD display mode when camera in record view hold mode
    #define PARAMETER_DATA_FLAG     0x4000      // Added to 'id' value in calls to _GetParameterData & _SetParameterData
                                                // Override if not needed or different value needed

    #undef  CAM_NO_MEMPARTINFO                  // VXWORKS camera does not have memPartInfoGet, fall back to memPartFindMax

    #undef  CAM_DRIVE_MODE_FROM_TIMER_MODE      // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #undef  CAM_AV_OVERRIDE_IRIS_FIX            // for cameras that require _MoveIrisWithAv function to override Av (for bracketing).

    #undef  CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE   // For cameras with 'low light' mode that does not work with raw define this
    #undef  CAM_DISABLE_RAW_IN_ISO_3200         // For cameras that don't have valid raw in ISO3200 mode (different from low light)
    #undef  CAM_DISABLE_RAW_IN_AUTO             // For cameras that don't have valid raw in AUTO mode
    #undef  CAM_DISABLE_RAW_IN_HQ_BURST         // For cameras with 'HQ Burst' mode that does not work with raw define this
    #undef  CAM_DISABLE_RAW_IN_HANDHELD_NIGHT_SCN // For cameras with 'HandHeld Night Scene' mode that does not work with raw define this
    #undef  CAM_ISO_LIMIT_IN_HQ_BURST           // Defines max 'market' ISO override value for HQ Burst mode (higher values crash camera)
    #undef  CAM_MIN_ISO_OVERRIDE                // Defines min 'market' (non-zero) ISO override value - lower value may crash if flash used [0 = AUTO, so always allowed]
    
    #undef  CAM_HAS_GPS                         // for cameras with GPS reseiver: includes the GPS coordinates in in DNG file

    #undef  CHDK_COLOR_BASE                     // Start color index for CHDK colors loaded into camera palette.

    #undef  CAM_LOAD_CUSTOM_COLORS              // Define to enable loading CHDK custom colors into the camera color palette
                                                // requires load_chdk_palette() and vid_get_bitmap_active_palette() to be defined
                                                // correctly for the camera along with

    #define CAM_USB_EVENTID         0x902       // event ID for USB control. Changed to 0x202 in DryOS R49 so needs to be overridable.
                                                // For DryOS only. These are "control events", and don't have the same IDs as "logical events"

    #undef CAM_USB_EVENTID_VXWORKS              // For vxworks cameras that need additional code to unlock mode switching
                                                // this is the logical event "ConnectUSBCable", usually 0x1085
                                                // different from CAM_USB_EVENTID since it should be undefined on most cameras

    #undef  CAM_NEED_SET_ZOOM_DELAY             // Define to add a delay after setting the zoom position before resetting the focus position in shooting_set_zoom 

    #undef  CAM_USE_ALT_SET_ZOOM_POINT          // Define to use the alternate code in lens_set_zoom_point()
    #undef  CAM_USE_ALT_PT_MoveOpticalZoomAt    // Define to use the PT_MoveOpticalZoomAt() function in lens_set_zoom_point()
    #undef  CAM_USE_OPTICAL_MAX_ZOOM_STATUS     // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom in gui_std_kbd_process()

    #define CAM_MARKET_ISO_BASE             100 // Base 'market' ISO value (SX40 & G1X use 200)
    #undef  CAM_HAS_HI_ISO_AUTO_MODE            // Define if camera has 'HI ISO Auto' mode (as well as Auto ISO mode), needed for adjustment in user auto ISO menu 

    #define CAMERA_MIN_DIST         0           // Define min distance that can be set in _MoveFocusLensToDistance (allow override - e.g. G12 min dist = 1)
    #define CAMERA_MAX_DIST         65535       // Define max distance that can be set in _MoveFocusLensToDistance (allow override for superzooms - SX30/SX40)

    #undef  DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   // Draw pixels on active bitmap buffer only.
                                                // Requires bitmap_buffer & active_bitmap_buffer location in stubs_min.S or stubs_entry.S.

    #undef  CAM_ZOOM_ASSIST_BUTTON_CONTROL      // Activate menu option to enable/disable the zoom assist button on the SX30/SX40
                                                // For other cameras, requires additional support code in kbd.c (see the SX30 or SX40 version)

    #undef  CAM_MISSING_RAND                    // Define this if srand()/rand() functions not found in firmware (a810/a2300)
    #undef  MKDIR_RETURN_ONE_ON_SUCCESS         // Define this if mkdir() return 1 on success, 0 on fail (a810/a1300)

    #undef  CAM_OPTIONAL_EXTRA_BUTTON           // extra button (remapped, for use in ALT mode) can be set from menu, must set next two values as well
    #undef  CAM_EXTRA_BUTTON_NAMES              // Define the list of names for the extra button   - e.g. { "Off", "Display" }
    #undef  CAM_EXTRA_BUTTON_OPTIONS            // Define the list of button constants for the extra button, starting with 0 - e.g. { 0, KEY_DISPLAY }

    #define CAM_AF_LED                      -1  // ***** NOTE ***** Need to override this in platform_camera.h with correct value
                                                // Defines 'led' Index value for camera_set_led function to control the AutoFocus assist LED
                                                // Used for the Motion Detect & Live View buffer testing

    #undef CAM_FILE_COUNTER_IS_VAR              // file counter is variable file_counter_var in stubs, not a param

    // Keyboard repeat and initial delays (override in platform_camera.h if needed)
    #define KBD_REPEAT_DELAY                175
    #define KBD_INITIAL_DELAY               500

//----------------------------------------------------------
// Overridden values for each camera
//----------------------------------------------------------

// Include the settings file for the camera model currently being compiled.
#include "platform_camera.h"

// default to startup crash fix on for DryOS
// TODO remove from individual camera.h files when verified OK, 
// defined check is just to avoid warning, can't turn it off on platform_camera.h!
#if defined(CAM_DRYOS) && !defined(CAM_STARTUP_CRASH_FILE_OPEN_FIX)
    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1
#endif

//==========================================================
// END of Camera-dependent settings
//==========================================================

// For newer cameras where the screen bitmap is double the width we need to scale
// the CHDK horizontal (X) co-ordinates
#if CAM_USES_ASPECT_CORRECTION
    #define ASPECT_XCORRECTION(x)   ((x)<<1)    // See comments for CAM_USES_ASPECT_CORRECTION above
#else
    #define ASPECT_XCORRECTION(x)   (x)         // See comments for CAM_USES_ASPECT_CORRECTION above
#endif

// curves only work in 10bpp for now
#if CAM_SENSOR_BITS_PER_PIXEL != 10
    #undef OPT_CURVES
#endif

#ifndef OPT_PTP
    #undef CAM_CHDK_PTP
#endif

// Define default video AF scan buttons if not already defined in platform_camera.h
#if CAM_AF_SCAN_DURING_VIDEO_RECORD
    #ifndef CAM_VIDEO_AF_BUTTON_NAMES
        #define CAM_VIDEO_AF_BUTTON_NAMES   { "", "Shutter", "Set" }
        #define CAM_VIDEO_AF_BUTTON_OPTIONS { 0, KEY_SHOOT_HALF, KEY_SET }
    #endif
#endif

// Define default value for DISP button name in shortcut text unless aready set in platform_camera.h
// e.g. G1X uses Meter button as DISP in CHDK
#ifndef CAM_DISP_BUTTON_NAME
    #define CAM_DISP_BUTTON_NAME            "DISP"
#endif

//------------------------------------------------------------------- 
// Keyboard / Button shortcuts - define in platform_camera.h
// if the default values are not suitable
// Default values are set below if not overridden
//------------------------------------------------------------------

// For models without ZOOM_LEVER  (#if !CAM_HAS_ZOOM_LEVER)
// SHORTCUT_SET_INFINITY is not used
// KEY_DISPLAY is used for gui_subj_dist_override_koef_enum;
// KEY_LEFT/KEY_RIGHT is used for gui_subj_dist_override_value_enum (because of no separate ZOOM_IN/OUT)

// Define keyboard / button shortcut values not already set above

//Alt mode
#if !defined(SHORTCUT_TOGGLE_RAW)
    #if CAM_HAS_ERASE_BUTTON
        #define SHORTCUT_TOGGLE_RAW         KEY_ERASE
    #else
        #define SHORTCUT_TOGGLE_RAW         KEY_DISPLAY
    #endif
#endif
#if !defined(CAM_HAS_MANUAL_FOCUS) && !defined(SHORTCUT_MF_TOGGLE)
    #if CAM_HAS_ERASE_BUTTON
        #define SHORTCUT_MF_TOGGLE          KEY_DISPLAY
    #else
        #define SHORTCUT_MF_TOGGLE          KEY_UP
    #endif
#endif

//Half press shoot button    
#if !defined(SHORTCUT_TOGGLE_HISTO)
    #if CAM_HAS_ERASE_BUTTON
        #define SHORTCUT_TOGGLE_HISTO       KEY_UP
    #else
        #define SHORTCUT_TOGGLE_HISTO       KEY_MENU
    #endif
#endif
#if !defined(SHORTCUT_TOGGLE_ZEBRA)
    #define SHORTCUT_TOGGLE_ZEBRA       KEY_LEFT
#endif
#if !defined(SHORTCUT_TOGGLE_OSD)
    #define SHORTCUT_TOGGLE_OSD         KEY_RIGHT
#endif
#if !defined(SHORTCUT_DISABLE_OVERRIDES)
    #define SHORTCUT_DISABLE_OVERRIDES  KEY_DOWN
#endif

//Alt mode & Manual mode  
#if !defined(SHORTCUT_SET_INFINITY)
    #if CAM_HAS_ERASE_BUTTON
        #define SHORTCUT_SET_INFINITY       KEY_UP
    #else
        #define SHORTCUT_SET_INFINITY       KEY_DISPLAY
    #endif
#endif
#if !defined(SHORTCUT_SET_HYPERFOCAL)
    #define SHORTCUT_SET_HYPERFOCAL     KEY_DOWN
#endif

#if CAM_HAS_ZOOM_LEVER
    #define SHORTCUT_SD_SUB KEY_ZOOM_OUT
    #define SHORTCUT_SD_ADD KEY_ZOOM_IN
#endif

//==========================================================
#include "camera_info.h"
//==========================================================

#endif /* CAMERA_H */
