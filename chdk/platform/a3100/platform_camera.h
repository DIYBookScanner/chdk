// Camera - A3100 - platform_camera.h

// This file contains the various settings values specific to the A3100 camera.
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


    ////////////////////////////////
    // Sure values
    ////////////////////////////////
    #define CAM_PROPSET                     3
    #define CAM_DRYOS                       1
    #define CAM_DRYOS_2_3_R39               1

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT  0x10000000 // Found @0xff8397e8

    #define CAM_RAW_ROWPIX                  4080
    #define CAM_RAW_ROWS                    3048
    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
    #define PARAM_CAMERA_NAME               4 // parameter number for GetParameterData

    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_MULTIPART                   1
    #undef  CAM_VIDEO_CONTROL
    #undef  CAM_USE_ZOOM_FOR_MF

    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_DNG_LENS_INFO               { 62,10, 248,10, 27,10, 56,10 } // See comments in camera.h

    #define cam_CFAPattern               0x02010100 // Red  Green  Green  Blue  // 0x01000201 // Green Blue Red Green

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1      1

    #define CAM_ACTIVE_AREA_X1              20
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              4056
    #define CAM_ACTIVE_AREA_Y2              3038

    #undef  CAM_HAS_MANUAL_FOCUS
    #define CAM_EXT_TV_RANGE                1

    #define CAM_QUALITY_OVERRIDE            1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
    #define CAM_DATE_FOLDER_NAMING          0x100   // Camera uses date for naming image folders


   #define CAM_STARTUP_CRASH_FILE_OPEN_FIX    1     // enable workaround for camera crash at startup when opening the conf / font files

    #define REMOTE_SYNC_STATUS_LED 	0xC0220010		// specifies the power led as the LED that turns on while camera waits for USB remote to sync

    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS 1   // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom in gui_std_kbd_process()
    
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Playback", "Print", "Disp" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PLAYBACK, KEY_PRINT, KEY_DISPLAY }

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              17


