// Camera - s80 - platform_camera.h

// This file contains the various settings values specific to the s2is camera.
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

    #define CAM_PROPSET                         1
    #define CAM_ADJUSTABLE_ALT_BUTTON           1
    #define CAM_ALT_BUTTON_NAMES                { "Shrtcut", "Display", "Timer", "Jump" }
    #define CAM_ALT_BUTTON_OPTIONS              { KEY_PRINT, KEY_DISPLAY, KEY_MICROPHONE, KEY_EXPO_CORR }
    #define CAM_RAW_ROWPIX                      3344   // @FF8B49E0 (100g)
    #define CAM_RAW_ROWS                        2484   // @FF8B49E0 (100g)

    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #define CAM_CAN_SD_OVER_IN_AF_LOCK_ONLY     1 // SD override when AF locked or video mode
    #undef  CAM_HAS_MANUAL_FOCUS                  // needed, SD override is misbehaving in MF

    #undef  CAM_HAS_IS    
    #define CAM_CAN_MUTE_MICROPHONE             1
    #define CAM_EV_IN_VIDEO                     1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU          1
    #define CAM_HAS_ERASE_BUTTON                1
    #define CAM_HAS_JOGDIAL                     1
    //#undef CAM_AF_SCAN_DURING_VIDEO_RECORD        // always crashes
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU         1

    #define CAM_DNG_LENS_INFO                   { 58,10, 207,10, 28,10, 53,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                    \
     15265, 10000, -6193, 10000, -1558, 10000,  \
     -4125, 10000, 12116, 10000,  2010, 10000,  \
     -888,  10000,  1639, 10000,  5220, 10000

    #define cam_CalibrationIlluminant1          17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH                      3264
    #define CAM_JPEG_HEIGHT                     2448
    #define CAM_ACTIVE_AREA_X1                  8
    #define CAM_ACTIVE_AREA_Y1                  2
    #define CAM_ACTIVE_AREA_X2                  3296
    #define CAM_ACTIVE_AREA_Y2                  2482
    // camera name
    #define PARAM_CAMERA_NAME                   3 // parameter number for GetParameterData
    #define DNG_EXT_FROM                        ".DPS"
    #define CAM_EXT_TV_RANGE                    1

    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1
    #undef  CAM_AF_LED
    #define CAM_AF_LED                          9   // Index of AF led in camera_set_led function

	// "real" to "market" conversion definitions
	#define SV96_MARKET_OFFSET          20          // market-real sv96 conversion value

	// Conversion values for pow(2,-20/96) 'market' to 'real', and pow(2,20/96) 'real' to 'market'
	// Uses integer arithmetic to avoid floating point calculations. Values choses to get as close
	// to the desired multiplication factor as possible within normal ISO range.
	#define ISO_MARKET_TO_REAL_MULT     3545
	#define ISO_MARKET_TO_REAL_SHIFT    12
	#define ISO_MARKET_TO_REAL_ROUND    2048
	#define ISO_REAL_TO_MARKET_MULT     9465
	#define ISO_REAL_TO_MARKET_SHIFT    13
	#define ISO_REAL_TO_MARKET_ROUND    4096
