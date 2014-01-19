// Camera - IXUS110_SD960 - platform_camera.h

// This file contains the various settings values specific to the IXUS110_SD960 camera.
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

    #define CAM_PROPSET                     2
    #define CAM_DRYOS                       1

    #define CAM_RAW_ROWPIX                  4080 // Found @0xff8eb014
    #define CAM_RAW_ROWS                    3048 // Found @0xff8eb018

    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART                   1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1

    // TODO
    #undef  CAM_HAS_MANUAL_FOCUS
    #define CAM_CAN_SD_OVER_NOT_IN_MF       1       // Camera allows subject distance (focus) override when not in manual focus mode
    #define CAM_CAN_SD_OVERRIDE             1       // Camera allows to do subject distance override
    #define CAM_USE_ZOOM_FOR_MF             1
    
    //#define CAM_EV_IN_VIDEO                 1

    // long shutter is acutally user TV, may work ?
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1

    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY          1

    #define CAM_EXT_TV_RANGE                1

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000

    #undef  CAM_BITMAP_PALETTE

    #define CAM_BITMAP_PALETTE              13
    #define CAM_LOAD_CUSTOM_COLORS          1       // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                 0xd0    // Starting color index for CHDK colors loaded into camera palette.
    
    #define CAM_QUALITY_OVERRIDE            1
    #undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1

    #define CAM_HAS_JOGDIAL                 1
    #define CAM_FEATURE_FEATHER             1

    #define CAM_DNG_LENS_INFO               { 50,10, 200,10, 28,10, 58,10 } // See comments in camera.h

    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                             \
     764117, 1000000, -223884, 1000000, -116036, 1000000, \
     -35875, 1000000,  582534, 1000000,   32982, 1000000, \
      10441, 1000000,   64164, 1000000,  198520, 1000000 
    #define cam_CalibrationIlluminant1      1

    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
    #define CAM_ACTIVE_AREA_X1              24       //
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              4056    //
    #define CAM_ACTIVE_AREA_Y2              3036    //

    // camera name OK
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    //aspect correction
    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized

    #undef CAM_SCREEN_WIDTH
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_SCREEN_WIDTH                480 // Width of bitmap screen in CHDK co-ordinates
    #define CAM_BITMAP_WIDTH                960 // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT               270 // Actual height of bitmap screen in rows

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html
	#define REMOTE_SYNC_STATUS_LED 	0xc0220134		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_OPTIONAL_EXTRA_BUTTON       1   // allow the Power button to be remapped in ALT mode
    #define CAM_EXTRA_BUTTON_NAMES          { "OFF", "Display" }
    #define CAM_EXTRA_BUTTON_OPTIONS        { 0, KEY_DISPLAY }
//----------------------------------------------------------
