// Camera - SX150IS - platform_camera.h

// This file contains the various settings values specific to the SX150IS camera.
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

    #define CAM_PROPSET                                 4
    #define CAM_DRYOS                                   1
    #define CAM_DRYOS_2_3_R39                           1
    #define CAM_DRYOS_2_3_R47                           1 // Defined for cameras with DryOS version R47 or higher

    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON                        1
    #define CAM_VIDEO_QUALITY_ONLY                      1
    #define CAM_BRACKETING                              1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_HAS_JOGDIAL                             1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                            0x40000000

    #define CAM_ADJUSTABLE_ALT_BUTTON           1
    #define CAM_ALT_BUTTON_NAMES                { "Playback", "Video", "Display" }
    #define CAM_ALT_BUTTON_OPTIONS              { KEY_PRINT, KEY_VIDEO, KEY_DISPLAY }

    #define CAM_DNG_LENS_INFO                           { 50,10, 600,10, 34,10, 56,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                              0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                               \
      1301431, 1000000,  -469837, 1000000, -102652, 1000000, \
      -200195, 1000000,   961551, 1000000,  238645, 1000000, \
       -16441, 1000000,   142319, 1000000,  375979, 1000000
    #define cam_CalibrationIlluminant1                  1 // Daylight
 
    // Sensor size, DNG image size & cropping
    #define CAM_RAW_ROWPIX                  4464
    #define CAM_RAW_ROWS                    3276
    #define CAM_JPEG_WIDTH                  4368
    #define CAM_JPEG_HEIGHT                 3254
    #define CAM_ACTIVE_AREA_X1              24
    #define CAM_ACTIVE_AREA_Y1              10
    #define CAM_ACTIVE_AREA_X2              (CAM_RAW_ROWPIX-72)
    #define CAM_ACTIVE_AREA_Y2              (CAM_RAW_ROWS-12)

    // camera name
    #define PARAM_CAMERA_NAME                           4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL                   12

    #define CAM_EXT_TV_RANGE                            1
    #define CAM_QUALITY_OVERRIDE                        1

    // copied from the SX200 which has the same video buffer size
    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION                  1 //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes
 
    #define CAM_ZEBRA_NOBUF                             1

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE                          7

    //#undef EDGE_HMARGIN
    //#define EDGE_HMARGIN                              28

    #define CAM_DATE_FOLDER_NAMING                      1

    // Menu width like in g11 and s90
    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH                        10
    // CR2 accesible through USB
    #undef DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                             2

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX             1 // enable fix for camera crash at startup when opening the conf / font files
                                                          // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE              1 // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                          // Used to enabled bracketing in custom timer, required on many recent cameras
                                                          // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID                             0x202 // Levent ID for USB control. Changed in DryOS R49 so needs to be overridable.

    #define REMOTE_SYNC_STATUS_LED                      0xC0220014		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_USE_ALT_SET_ZOOM_POINT                  1   // Define to use the alternate code in lens_set_zoom_point()
    #define CAM_USE_ALT_PT_MoveOpticalZoomAt            1   // Define to use the PT_MoveOpticalZoomAt() function in lens_set_zoom_point()

	
//----------------------------------------------------------
