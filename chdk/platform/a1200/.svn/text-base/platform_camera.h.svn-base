// Camera - A1200 - platform_camera.h

// This file contains the various settings values specific to the A1200 camera.
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

    #define CAM_DRYOS                       1
    #define CAM_PROPSET                     4

    #define CAM_DRYOS_2_3_R31               1       // Define for cameras with DryOS release R31 or greater -> G10
    #define CAM_DRYOS_2_3_R39               1       // Defined for cameras with DryOS version R39 or higher
    #define CAM_DRYOS_2_3_R47               1       // Defined for cameras with DryOS version R47 or higher

    #define CAM_RAW_ROWPIX                  4104    // Found @0xff937e98
    #define CAM_RAW_ROWS                    3048    // Found @0xff937ea4

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000  // Found @0xff83a2e0

    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
    #define CAM_ACTIVE_AREA_X1              0
    #define CAM_ACTIVE_AREA_Y1              10
    #define CAM_ACTIVE_AREA_X2              4072
    #define CAM_ACTIVE_AREA_Y2              3040

    #undef  CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH            10

    #define CAM_DNG_LENS_INFO   { 50,10, 200,10, 28,10, 59,10 } // See comments in camera.h

    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define cam_CFAPattern                  0x01000201  // Green  Blue  Red  Green
//  #define cam_CFAPattern                  0x02010100  // Red  Green  Green  Blue

    #define CAM_COLORMATRIX1                             \
    827547, 1000000, -290458, 1000000, -126086, 1000000, \
    -12829, 1000000,  530507, 1000000,   50537, 1000000, \
      5181, 1000000,   48183, 1000000,  245014, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight

    #define CAM_ZEBRA_NOBUF                 1

    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #define CAM_HAS_ND_FILTER               1

    #define CAM_EXT_TV_RANGE                1

    #define CAM_VIDEO_QUALITY_ONLY          1

    #define DNG_VERT_RLE_BADPIXELS          1

    #define CAM_DATE_FOLDER_NAMING          1

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1

    #undef  CAM_HAS_IRIS_DIAPHRAGM

    #undef  CAM_HAS_ERASE_BUTTON

    #undef  CAM_HAS_IS                              // Camera does not have an image stabilizer

    #undef  CAM_HAS_MANUAL_FOCUS

    #undef  CAM_VIDEO_CONTROL

    #define CAM_CHDK_HAS_EXT_VIDEO_TIME         1

    #define CAM_CAN_MUTE_MICROPHONE         1

    #define CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE   1   // For cameras with 'low light' mode that does now work with raw define this

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              16
    #define CAM_LOAD_CUSTOM_COLORS          1       // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                 0x9F    // Start color index for CHDK colors loaded into camera palette
                                                    // Note: overloads Canon RED for proper logo display

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720   // Actual width of bitmap screen in bytes

    #define  CAM_ADJUSTABLE_ALT_BUTTON      1    // ALT-button can be set from menu
    #define CAM_ALT_BUTTON_NAMES            { "Playback", "Face", "Disp" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PLAYBACK, KEY_FACE, KEY_DISPLAY }


    #define CAM_HAS_ZOOM_LEVER               1    // Camera has dedicated zoom buttons
    #define CAM_USE_ZOOM_FOR_MF              1    // Zoom lever can be used for manual focus adjustments
    #define CAM_NEED_SET_ZOOM_DELAY          300  // Define to add a delay after setting the zoom position
    #define CAM_USE_ALT_SET_ZOOM_POINT       1    // Define to use the alternate code in lens_set_zoom_point()
    #define CAM_USE_ALT_PT_MoveOpticalZoomAt 1    // Define to use the PT_MoveOpticalZoomAt() function in lens_set_zoom_point()
    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS  1    // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoo

    #define CAM_CAN_SD_OVERRIDE              1    // SD override enable
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF             // no SD override unless in manual focus mode
    #undef  CAM_CAN_SD_OVER_IN_AF_LOCK            // SD override when AF locked only
    #define CAM_CAN_SD_OVER_IN_AF_LOCK_ONLY  1    // SD override when AF locked or video mode

    #undef  CAM_AF_LED                            // AF Lamp index for camera_set_led()
    #define CAM_AF_LED                       2    //

    #define CAM_REMOTE_USES_PRECISION_SYNC   1    // USB remote precision sync patch works with this camera
    #define GPIO_VSYNC_CURRENT               0xC0F070C8  // vsync current status register used by USB remote precision sync

