// Camera - S110 - platform_camera.h

// This file contains the various settings values specific to the S110 camera.
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

    #define CAM_PROPSET                         5
    #define CAM_DRYOS         1
    #define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
    #define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher

    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1   // Draw pixels on active bitmap buffer only. Requires active_bitmap_buffer location in stubs_min.S or stubs_entry.S.

    #undef  CAM_AF_LED
    #define CAM_AF_LED                          0 // Index of AF led in camera_set_led function

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                    0x40000000 // Found @0xf8039b1c

    #define CAM_HAS_ND_FILTER                   1
    #define CAM_HAS_NATIVE_ND_FILTER            1   // Camera has built-in ND filter with Canon menu support for enable/disable

    #define CAM_ADJUSTABLE_ALT_BUTTON           1
    #define CAM_ALT_BUTTON_NAMES            { "Playback", "Video", "Display" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_VIDEO, KEY_DISPLAY }

    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON                1
    #define CAM_VIDEO_QUALITY_ONLY              1
    #define CAM_BRACKETING                      1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_HAS_JOGDIAL                     1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_SHOW_OSD_IN_SHOOT_MENU          1

    #undef DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                     2   // use .CR2 

    #undef  CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH                10

    #define CAM_DNG_LENS_INFO               { 52,10, 260,10, 20,10, 59,10 }

    // From S110 native RAW file as converted to DNG using Adobe DNG Converter
    // http://www.adobe.com/support/downloads/product.jsp?product=106&platform=Windows
    // Matrices from converted DNG's EXIF data
    #define cam_CalibrationIlluminant1          17      // Standard Light A
    #define cam_CalibrationIlluminant2          21      // D65
    #define CAM_COLORMATRIX1    \
      9063, 10000,  -4110, 10000,    240, 10000, \
     -2713, 10000,   9326, 10000,   3987, 10000, \
       140, 10000,    247, 10000,   4262, 10000
    #define CAM_COLORMATRIX2    \
      8039, 10000,  -2643, 10000,   -654, 10000, \
     -3783, 10000,  11230, 10000,   2930, 10000, \
      -206, 10000,    690, 10000,   4194, 10000
    #define CAM_CAMERACALIBRATION1    \
     10099, 10000,      0, 10000,      0, 10000, \
         0, 10000,  10000, 10000,      0, 10000, \
         0, 10000,      0, 10000,   9551, 10000
    #define CAM_CAMERACALIBRATION2    \
     10099, 10000,      0, 10000,      0, 10000, \
         0, 10000,  10000, 10000,      0, 10000, \
         0, 10000,      0, 10000,   9551, 10000
    #define CAM_FORWARDMATRIX1    \
      6336, 10000,   2874, 10000,    433, 10000, \
      1716, 10000,  10221, 10000,  -1937, 10000, \
      -769, 10000,  -2436, 10000,  11483, 10000
    #define CAM_FORWARDMATRIX2    \
      6304, 10000,   4163, 10000,   -825, 10000, \
      2185, 10000,  11354, 10000,  -3539, 10000, \
       -54, 10000,  -1114, 10000,   9419, 10000
    #define CAM_DNG_EXPOSURE_BIAS -3,4 // EXIF: Baseline Exposure

    #define CAM_RAW_ROWPIX    4160 // Found @0xf81fdae4
    #define CAM_RAW_ROWS      3124 // Found @0xf81fdaec

    #define CAM_JPEG_WIDTH                      4034
    #define CAM_JPEG_HEIGHT                     3040
    // S110 native RAW converted to DNG's EXIF data: Active Area
    #define CAM_ACTIVE_AREA_X1                  104
    #define CAM_ACTIVE_AREA_Y1                  11
    #define CAM_ACTIVE_AREA_X2                  4152
    #define CAM_ACTIVE_AREA_Y2                  3059
    // S110 native RAW converted to DNG's EXIF data: CFA Pattern
    #define cam_CFAPattern                      0x02010100 // [Red,Green][Green,Blue]

    #define PARAM_CAMERA_NAME                   4       // parameter number for GetParameterData - Camera Model name
    #define PARAM_OWNER_NAME                    7       // parameter number for GetParameterData - Owner name
    #define PARAM_DISPLAY_MODE1                 59      // param number for LCD display mode when camera in playback
    #define PARAM_DISPLAY_MODE2                 62      // param number for LCD display mode when camera in record view hold mode
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL           12

    #define CAM_EXT_TV_RANGE                    1
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
    #define CAM_HAS_MOVIE_DIGEST_MODE           1       // Changes the values in the 'movie_status' variable if the camera has this mode

    #define CAM_LOAD_CUSTOM_COLORS              1       // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                     0xAF    // Start color index for CHDK colors loaded into camera palette.

    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID                     0x202   // Levent ID for USB control. Changed in DryOS R49 so needs to be overridable.
 
//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_HAS_CMOS                        1

    #undef  CAMERA_MIN_DIST
    #define CAMERA_MIN_DIST                     74 // Override min subject distance
    #undef  CAMERA_MAX_DIST
    #define CAMERA_MAX_DIST                     131579  // Override max subject distance

    #define MKDIR_RETURN_ONE_ON_SUCCESS         1       // mkdir() return 1 on success, 0 on fail.

    // Define shortcut overrides where defaults are not suitable
    #define SHORTCUT_TOGGLE_ZEBRA           KEY_ERASE   // On camera Shutter Half Press + Up = switch MF on/off

    #define CAM_HAS_FILEWRITETASK_HOOK                  1
    #define CAM_FILEWRITETASK_SEEKS                     1

//----------------------------------------------------------
