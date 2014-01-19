// Camera - s95 - platform_camera.h

// This file contains the various settings values specific to the s95 camera.
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

    #define CAM_DRYOS_2_3_R39               1
    #define CAM_PROPSET                     4
    #define CAM_DRYOS                       1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_RAW_ROWPIX                  3744
    #define CAM_RAW_ROWS                    2784
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION      10
    #undef  CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH            10
    #define CAM_QUALITY_OVERRIDE            1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL                 1
    #undef  CAM_HAS_ERASE_BUTTON

    #define CAM_BRACKETING                  1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY          1
    #define CAM_MULTIPART                   1
    #define CAM_EXT_TV_RANGE                1
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000  // S94 100E @FF89100C
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1

    // camera name
    #define PARAM_CAMERA_NAME               4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_WIDTH                960 // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT               270 // Actual height of bitmap screen in rows

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              9

    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN                    28

    #define CAM_DNG_LENS_INFO               { 60,10, 225,10, 20,10, 49,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                          \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
      -1991, 1000000, 10719, 1000000,  1273, 1000000, \
      -1158, 1000000,  1929, 1000000,  3581, 1000000
    #define cam_CalibrationIlluminant1      17 // Standard Light A

    // DNG image area taken from sample images posted by whim
    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #define CAM_ACTIVE_AREA_X1              64
    #define CAM_ACTIVE_AREA_Y1              22
    #define CAM_ACTIVE_AREA_X2              3728
    #define CAM_ACTIVE_AREA_Y2              2762

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1   // enable workaround for camera crash at startup when opening the conf / font files
                                                // see http://chdk.setepontos.com/index.php?topic=6179.0

    // todo - we may need this to save memory
    //#define CAM_ZEBRA_NOBUF                 1
    #define CAM_DATE_FOLDER_NAMING          0x400 //Value found in the last function, which is called in GetImageFolder. (first compare)

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html
	#define REMOTE_SYNC_STATUS_LED 	0xc0220130		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS 1   // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom in gui_std_kbd_process()
											
//----------------------------------------------------------
