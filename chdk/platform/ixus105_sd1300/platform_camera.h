// Camera - ixus105_sd1300 - platform_camera.h

// This file contains the various settings values specific to the ixus105_sd1300 camera.
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


    #define CAM_DRYOS         1
    #define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
    #define CAM_RAW_ROWPIX    4104 // Found @0xffcf4dc4
    #define CAM_RAW_ROWS      3048 // Found @0xffcf4dd0
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT  0x40000000 // Found @0xffc29e80
    #define CAM_PROPSET                 3
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_EXT_TV_RANGE            1
    #define CAM_HAS_ND_FILTER           1

    // pattern
    #define cam_CFAPattern 0x01000201 // Green Blue Red Green
    // color
    #define CAM_COLORMATRIX1                               \
      14052, 10000, -5229, 10000, -1156, 10000, \
      -1325, 10000,  9420, 10000,  2252, 10000, \
       -498, 10000,  1957, 10000,  4116, 10000

    #define cam_CalibrationIlluminant1 1 // Daylight  // TODO:
    // cropping
    #define CAM_JPEG_WIDTH  4000
    #define CAM_JPEG_HEIGHT 3000
    #define CAM_ACTIVE_AREA_X1 8
    #define CAM_ACTIVE_AREA_Y1 22
    #define CAM_ACTIVE_AREA_X2 4024
    #define CAM_ACTIVE_AREA_Y2 3028

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12

    #undef  CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1

    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Display", "Playback" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_DISPLAY, KEY_PLAYBACK }

    #define  CAM_STARTUP_CRASH_FILE_OPEN_FIX      1

//-------------------
    #undef  CAM_VIDEO_CONTROL
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO   1
    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS 1   // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom in gui_std_kbd_process()
    #define CAM_QUALITY_OVERRIDE            1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
