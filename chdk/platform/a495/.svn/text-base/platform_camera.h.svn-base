// Camera - a495 - platform_camera.h

// This file contains the various settings values specific to the a495 camera.
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

    #define CAM_PROPSET                     3
    #define CAM_DRYOS                       1
    #define CAM_DRYOS_2_3_R39               1

    #define CAM_RAW_ROWPIX                  3720
    #define CAM_RAW_ROWS                    2772

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON                    // Camera does not have Erase button
    #undef  CAM_HAS_DISP_BUTTON                     // Camera does not have DISP button
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #undef  CAM_HAS_IS
    #define CAM_MULTIPART                   1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_REAR_CURTAIN                1
    #undef  DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                 2   // use .CR2
    #define CAM_EXT_TV_RANGE                1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_CAN_MUTE_MICROPHONE         1
    #define CAM_EV_IN_VIDEO                 1
    #define CAM_QUALITY_OVERRIDE            1

    #undef CAM_DEFAULT_ALT_BUTTON
    #define CAM_DEFAULT_ALT_BUTTON          KEY_PLAYBACK

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              8

    #define CAM_DNG_LENS_INFO               { 66,10, 216,10, 30,10, 58,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1      1   // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #define CAM_ACTIVE_AREA_X1              6
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              3690
    #define CAM_ACTIVE_AREA_Y2              2772

    // camera name
    #define PARAM_CAMERA_NAME               4   // parameter number for GetParameterData to get camera name
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1   // enable workaround for camera crash at startup when opening the conf / font files
                                                // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DATE_FOLDER_NAMING          0x100 //Value found in the last function, which is called in GetImageFolder. (first compare)

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define CAM_HAS_FILEWRITETASK_HOOK       1

    #define CAM_HAS_ZOOM_LEVER               1    // Camera has dedicated zoom buttons
    #define CAM_NEED_SET_ZOOM_DELAY          150  // Define to add a delay after setting the zoom position
    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS  1    // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom
    #define CAM_USE_ALT_SET_ZOOM_POINT       1    // Define to use the alternate code in lens_set_zoom_point()
    #define CAM_USE_ALT_PT_MoveOpticalZoomAt 1    // Define to use the PT_MoveOpticalZoomAt() function in lens_set_zoom_point()

    #undef  CAM_AF_LED
    #define CAM_AF_LED                       1   // Index of AF led in camera_set_led function

    #define REMOTE_SYNC_STATUS_LED  0xC0220088    // specifies an LED that turns on while camera waits for USB remote to sync

//----------------------------------------------------------
