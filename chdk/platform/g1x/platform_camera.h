// Camera - G1X - platform_camera.h

// This file contains the various settings values specific to the G1X camera.
// This file is referenced via the 'include/camera.h' file and should not be loaded directly.

// If adding a new settings value put a suitable default in 'include/camera.h',
// along with documentation on what the setting does and how to determine the correct value.
// If the setting should not have a default value then add it in 'include/camera.h'
// using the '#undef' directive along with appropriate documentation.

// Override any default values with your camera specific values in this file. Try and avoid
// having override values that are the same as the default value.

// When overriding a setting value there are two cases:
// 1. If removing the value, because it does not apply to your camera, use the '#undef' directive.
// 2. If changing the value it is best to use an '#undef' directive to remove the default value
//    followed by a '#define' to set the new value.

// When porting CHDK to a new camera, check the documentation in 'include/camera.h'
// for information on each setting. If the default values are correct for your camera then
// don't override them again in here.

    #define CAM_PROPSET                         4
    #define CAM_DRYOS                           1
    #define CAM_DRYOS_2_3_R39                   1
    #define CAM_DRYOS_2_3_R47                   1

    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1   // Draw pixels on active bitmap buffer only. Requires active_bitmap_buffer location in stubs_min.S or stubs_entry.S.

    #undef  CAM_AF_LED
    #define CAM_AF_LED                          3   // Index of AF led in camera_set_led function

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                    0x40000000 // Found @0xff02ac74

    #define CAM_HAS_ND_FILTER                   1
    #define CAM_HAS_NATIVE_ND_FILTER            1   // Camera has built-in ND filter with Canon menu support for enable/disable
    #define CAM_SWIVEL_SCREEN                   1

    #define CAM_ADJUSTABLE_ALT_BUTTON           1
    #define CAM_ALT_BUTTON_NAMES                { "Shrtcut", "Video", "Meter", "AE Lock", "Erase" }
    #define CAM_ALT_BUTTON_OPTIONS              { KEY_PRINT, KEY_VIDEO, KEY_DISPLAY, KEY_AE_LOCK, KEY_ERASE }
    #define CAM_DISP_BUTTON_NAME                "METER"

    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON                1
    #define CAM_VIDEO_QUALITY_ONLY              1
    #define CAM_BRACKETING                      1
    #undef  CAM_VIDEO_CONTROL                       // Crashes camera if enabled
    #define CAM_HAS_JOGDIAL                     1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_SHOW_OSD_IN_SHOOT_MENU          1

    #undef DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                     2   // use .CR2 

    #undef  CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH                10

    #undef  CAM_MARKET_ISO_BASE
    #define CAM_MARKET_ISO_BASE                 200 // Override base 'market' ISO value
    #define CAM_MIN_ISO_OVERRIDE                100 // Defines min market (non-zero) ISO override value - lower value may crash if flash used [0 = AUTO, so always allowed]

    // bayer sensor pattern
    #define cam_CFAPattern                      0x02010100 // Red  Green  Green  Blue

    #define CAM_DNG_LENS_INFO                   { 151,10, 604,10, 28,10, 58,10 }    // See comments in camera.h

    //From G1 X native RAW file as converted to DNG by Adobe convertor
    #define cam_CalibrationIlluminant1          17      // Standard Light A
    #define CAM_COLORMATRIX1    \
      8138, 10000,  -2281, 10000,   -659, 10000, \
     -3453, 10000,  11006, 10000,   2816, 10000, \
      -297, 10000,   1118, 10000,   6471, 10000
    #define cam_CalibrationIlluminant2          21      // D65
    #define CAM_COLORMATRIX2    \
      7378, 10000,  -1255, 10000,  -1043, 10000, \
     -4088, 10000,  12251, 10000,   2048, 10000, \
      -876, 10000,   1946, 10000,   5805, 10000
    #define CAM_CAMERACALIBRATION1    \
     10102, 10000,      0, 10000,      0, 10000, \
         0, 10000,  10000, 10000,      0, 10000, \
         0, 10000,  00000, 10000,  10233, 10000
    #define CAM_CAMERACALIBRATION2    \
     10102, 10000,      0, 10000,      0, 10000, \
         0, 10000,  10000, 10000,      0, 10000, \
         0, 10000,  00000, 10000,  10233, 10000
    #define CAM_FORWARDMATRIX1    \
      7310, 10000,    833, 10000,   1500, 10000, \
      2013, 10000,   8875, 10000,   -888, 10000, \
        34, 10000,  -4122, 10000,  12339, 10000
    #define CAM_FORWARDMATRIX2    \
      7010, 10000,   1653, 10000,    980, 10000, \
      2351, 10000,   9551, 10000,  -1902, 10000, \
       177, 10000,  -2144, 10000,  10218, 10000

    // Sensor size, DNG image size & cropping
    #define CAM_RAW_ROWPIX                      4496    // Found @0xff190c98
    #define CAM_RAW_ROWS                        3366    // Found @0xff190ca4
    #define CAM_JPEG_WIDTH                      4400
    #define CAM_JPEG_HEIGHT                     3308
    #define CAM_ACTIVE_AREA_X1                  80
    #define CAM_ACTIVE_AREA_Y1                  52
    #define CAM_ACTIVE_AREA_X2                  4484
    #define CAM_ACTIVE_AREA_Y2                  3364

    // camera name
    #define PARAM_CAMERA_NAME                   4       // parameter number for GetParameterData - Camera Model name
    #define PARAM_OWNER_NAME                    7       // parameter number for GetParameterData - Owner name
    #define PARAM_ARTIST_NAME                   157     // parameter number for GetParameterData - Artist name
    #define PARAM_COPYRIGHT                     158     // parameter number for GetParameterData - Copyright
    #define PARAM_DISPLAY_MODE1                 59      // param number for LCD display mode when camera in playback
    #define PARAM_DISPLAY_MODE2                 62      // param number for LCD display mode when camera in record view hold mode
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL           14

    #define CAM_EXT_TV_RANGE                    1
    #undef CAM_EXT_AV_RANGE
    #define CAM_EXT_AV_RANGE                    0       // G1X can't go below F/16 so set this to 0
    #define CAM_QUALITY_OVERRIDE                1
    #define CAM_REAR_CURTAIN                    1

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION          1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_WIDTH                    960     // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT                   270     // Actual height of bitmap screen in rows

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE                  13
  
    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN 2

    #define CAM_DATE_FOLDER_NAMING              1

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX     1       // enable fix for camera crash at startup when opening the conf / font files
                                                        // see http://chdk.setepontos.com/index.php?topic=6179.0

    #undef  CAM_KEY_PRESS_DELAY
    #define CAM_KEY_PRESS_DELAY                 60      // delay after a press

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE      1       // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                        // Used to enabled bracketing in custom timer, required on many recent cameras
                                                        // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define CAM_AV_OVERRIDE_IRIS_FIX            1       // for cameras that require _MoveIrisWithAv function to override Av in bracketing.

    #define CAM_DISABLE_RAW_IN_HQ_BURST         1       // For cameras with 'HQ Burst' mode that does not work with raw define this
    #define CAM_DISABLE_RAW_IN_HANDHELD_NIGHT_SCN 1     // For cameras with 'HandHeld Night Scene' mode that does not work with raw define this
    #define  CAM_HAS_MOVIE_DIGEST_MODE          1       // Changes the values in the 'movie_status' variable if the camera has this mode

    #define CAM_LOAD_CUSTOM_COLORS              1       // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                     0xA8    // Start color index for CHDK colors loaded into camera palette.

    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID                     0x202   // Levent ID for USB control. Changed in DryOS R49 so needs to be overridable.
 
//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_HAS_CMOS                        1

    #undef  CAMERA_MIN_DIST
    #define CAMERA_MIN_DIST                     275     // Override min subject distance
    #undef  CAMERA_MAX_DIST
    #define CAMERA_MAX_DIST                     660067  // Override max subject distance

    // Define shortcut overrides where defaults are not suitable
    #define SHORTCUT_TOGGLE_ZEBRA           KEY_ERASE   // On camera Shutter Half Press + Up = switch MF on/off

    #define CAM_HAS_FILEWRITETASK_HOOK          1   // file write hook for remote capture etc

//----------------------------------------------------------
