// Camera - G10 - platform_camera.h

// This file contains the various settings values specific to the G10 camera.
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
    #define CAM_DRYOS_2_3_R31               1    // note : structure used by stat changes in R39

    #define CAM_PROPSET                     2

    #define CAM_CAN_SD_OVER_IN_AF_LOCK      1   // Camera allows subject distance (focus) override when in AF Lock mode
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_HAS_ND_FILTER               1
    #define CAM_HAS_NATIVE_ND_FILTER        1   // Camera has built-in ND filter with Canon menu support for enable/disable

    #define CAM_HAS_HI_ISO_AUTO_MODE        1
 
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION      10

    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Print", "Disp",  "AE Lock", "Jump" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_DISPLAY, KEY_AE_LOCK, KEY_METERING}

    #define CAM_RAW_ROWPIX                  4480    // G10 auto found @0xffacde38
    #define CAM_RAW_ROWS                    3348    // G10 auto found @0xffacde3c

    #define CAM_JPEG_WIDTH                  4416    // taken from G10 jpg header info
    #define CAM_JPEG_HEIGHT                 3312    // "

    #define CAM_ACTIVE_AREA_X1              12      // calibrated with G10 RAW picture converted with rawconvert.exe (rawconvert -12to8 -pgm -w=4480 -h=3348 g10.crw g10.pgm)
    #define CAM_ACTIVE_AREA_Y1              12      // "
    #define CAM_ACTIVE_AREA_X2              4440    // "
    #define CAM_ACTIVE_AREA_Y2              3334    // "

    #undef  CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH            10

    #define CAM_QUALITY_OVERRIDE            1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_RESET_AEL_AFTER_VIDEO_AF    1   // Cam needs AE Lock state reset after AF in video recording
    #define CAM_HAS_JOGDIAL                 1

    #define CAM_BRACKETING                  1
    #define CAM_MULTIPART                   1
    #define CAM_EXT_TV_RANGE                1
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000  // G10 auto found @0xff828844
  
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1

    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData
    #define PARAM_DISPLAY_MODE1             57      // param number for LCD display mode when camera in playback
    #define PARAM_DISPLAY_MODE2             58      // param number for LCD display mode when camera in record view hold mode

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE             16

    #define CAM_LOAD_CUSTOM_COLORS         1      // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                0xB3   // Start color index for CHDK colors loaded into camera palette.


    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #undef  CAM_USES_ASPECT_CORRECTION   
    #define CAM_USES_ASPECT_CORRECTION      1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    #undef  EDGE_HMARGIN 
    #define EDGE_HMARGIN 28

    #define CAM_DNG_LENS_INFO               { 61,10, 305,10, 28,10, 45,10 } // See comments in camera.h
    // G10 pattern
    #define cam_CFAPattern                  0x01000201   // 0x01000201 = Green Blue Red Green    
                                                        // 0x02010100 = Red  Green  Green  Blue   

    // G10 color - values from dcraw for G10 Canon RAW files
    #define cam_CalibrationIlluminant1      17 // standard light A   
    #define CAM_COLORMATRIX1 \
        11093,  1000000,    -3906,  1000000,    -1028,  1000000, \
        -5047,  1000000,    12492,  1000000,     2879,  1000000, \
        -1003,  1000000,     1750,  1000000,     5561,  1000000

    // zebra 
    #define CAM_ZEBRA_NOBUF                 1

    #define CAM_USE_ALT_SET_ZOOM_POINT      1   // Define to use the alternate code in lens_set_zoom_point()

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1       // enable fix for camera crash at startup when opening the conf / font files
                                                    // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1       // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                    // Used to enabled bracketing in custom timer, required on many recent cameras
                                                    // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define REMOTE_SYNC_STATUS_LED 	0xC02200DC		// specifies an LED that turns on while camera waits for USB remote to sync

    #undef  CAM_AF_LED
    #define CAM_AF_LED                      5       // Index of AF led in camera_set_led function


//----------------------------------------------------------

