// Camera - g12 - platform_camera.h

// This file contains the various settings values specific to the g12 camera.
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

    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1   // Draw pixels on active bitmap buffer only.

    #undef  CAM_AF_LED
    #define CAM_AF_LED                          4   // Index of AF led in camera_set_led function

    #define CAM_SWIVEL_SCREEN                   1

    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION          10

    #define CAM_ADJUSTABLE_ALT_BUTTON           1
    #define CAM_ALT_BUTTON_NAMES                { "Print", "Disp",  "AE Lock", "Jump" }
    #define CAM_ALT_BUTTON_OPTIONS              { KEY_PRINT, KEY_DISPLAY, KEY_AE_LOCK, KEY_METERING}

    #define CAM_AF_SCAN_DURING_VIDEO_RECORD     1
    #define CAM_RESET_AEL_AFTER_VIDEO_AF        1   // Cam needs AE Lock state reset after AF in video recording
    #define CAM_VIDEO_AF_BUTTON_NAMES           { "", "Shutter", "Set", "AE Lock" }
    #define CAM_VIDEO_AF_BUTTON_OPTIONS         { 0, KEY_SHOOT_HALF, KEY_SET, KEY_AE_LOCK }

    #define CAM_MULTIPART                       1
    #define CAM_HAS_JOGDIAL                     1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #define CAM_HAS_ND_FILTER                   1
    #define CAM_HAS_NATIVE_ND_FILTER            1   // Camera has built-in ND filter with Canon menu support for enable/disable

    #define CAM_BRACKETING                      1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY              1
    #define CAM_EXT_TV_RANGE                    1
    #define CAM_QUALITY_OVERRIDE                1
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                    0x40000000  // S90 @FF8875FC(via ExMem.FreeCacheable)
    #define CAM_SHOW_OSD_IN_SHOOT_MENU          1

    #undef DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                     2   // use .CR2 

    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	            10

    // camera name
    #define PARAM_CAMERA_NAME                   4   // parameter number for GetParameterData - Camera Model name
    #define PARAM_OWNER_NAME                    7   // parameter number for GetParameterData - Owner name
    #define PARAM_DISPLAY_MODE1                 59  // param number for LCD display mode when camera in playback
    #define PARAM_DISPLAY_MODE2                 62  // param number for LCD display mode when camera in record view hold mode
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL           12

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE                  13

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION          1   //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_WIDTH                    960 // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT                   270 // Actual height of bitmap screen in rows

    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN                        2

    #define CAM_MIN_ISO_OVERRIDE                80  // Defines min market (non-zero) ISO override value - lower value may crash if flash used [0 = AUTO, so always allowed]

    // bayer sensor pattern
    #define cam_CFAPattern                      0x02010100  // Red  Green  Green  Blue

    #define CAM_DNG_EXPOSURE_BIAS               0,1     // Specify DNG exposure bias value to 0 (to override default of -0.5 in the dng.c code)

    #define	CAM_DNG_LENS_INFO                   { 61,10, 305,10, 28,10, 45,10 }	// See comments in camera.h

    // From dcraw
    #define CAM_COLORMATRIX1                    \
      13244, 10000, -5501, 10000, -1248, 10000, \
      -1508, 10000,  9858, 10000,  1935, 10000, \
       -270, 10000,  1083, 10000,  4366, 10000

    #define cam_CalibrationIlluminant1          17  // Standard Light A

    // Sensor size, DNG image size & cropping
    #define CAM_RAW_ROWPIX                      3744
    #define CAM_RAW_ROWS                        2784
    #define CAM_JPEG_WIDTH                      3684
    #define CAM_JPEG_HEIGHT                     2760
    #define CAM_ACTIVE_AREA_X1                  52
    #define CAM_ACTIVE_AREA_Y1                  12
    #define CAM_ACTIVE_AREA_X2                  (CAM_RAW_ROWPIX-8)
    #define CAM_ACTIVE_AREA_Y2                  (CAM_RAW_ROWS-12)

    #define CAM_DATE_FOLDER_NAMING              0x400 //Value found in the last function, which is called in GetImageFolder. (first compare)

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX     1   // enable fix for camera crash at startup when opening the conf / font files see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE      1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                    // Used to enabled bracketing in custom timer, required on many recent cameras
                                                    // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define CAM_AV_OVERRIDE_IRIS_FIX            1   // for cameras that require _MoveIrisWithAv function to override Av.

    #define CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE   1   // For cameras with 'low light' mode that does now work with raw define this

    #define CAM_LOAD_CUSTOM_COLORS              1   // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                     0xB3// Start color index for CHDK colors loaded into camera palette.

//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_USE_ALT_SET_ZOOM_POINT          1   // Define to use the alternate code in lens_set_zoom_point()
    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS     1   // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom in gui_std_kbd_process()

    #undef  CAMERA_MIN_DIST
    #define CAMERA_MIN_DIST                     68      // Override min subject distance
    #undef  CAMERA_MAX_DIST
    #define CAMERA_MAX_DIST                     258065  // Override max subject distance

    // Define shortcut overrides where defaults are not suitable
    #define SHORTCUT_TOGGLE_HISTO               KEY_ERASE   // On camera Shutter Half Press + Up = switch MF on/off

    #define CAM_HAS_FILEWRITETASK_HOOK          1   // file write hook for remote capture etc

//----------------------------------------------------------
