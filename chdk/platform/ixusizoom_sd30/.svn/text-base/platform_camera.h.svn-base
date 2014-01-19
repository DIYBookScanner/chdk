// Camera - ixusizoom_sd30 - platform_camera.h

// This file contains the various settings values specific to the ixusizoom_sd30 camera.
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

    #define CAM_PROPSET                     1

    #define CAM_RAW_ROWPIX                  2672    // for 5 MP
    #define CAM_RAW_ROWS                    1968    // for 5 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  CAM_HAS_IS
    //#define CAM_CONSOLE_LOG_ENABLED       1
    #undef  CAM_VIDEO_CONTROL
	
//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync

    // Keyboard repeat and initial delays
    #undef  KBD_REPEAT_DELAY
    #define KBD_REPEAT_DELAY                140
    #undef  KBD_INITIAL_DELAY
    #define KBD_INITIAL_DELAY               300

	// "real" to "market" conversion definitions
	#define SV96_MARKET_OFFSET          0           // market-real sv96 conversion value

	// Conversion values for 'no' conversion required
	// Uses integer arithmetic to avoid floating point calculations. Values choses to get as close
	// to the desired multiplication factor as possible within normal ISO range.
	#define ISO_MARKET_TO_REAL_MULT     2
	#define ISO_MARKET_TO_REAL_SHIFT    1
	#define ISO_MARKET_TO_REAL_ROUND    0
	#define ISO_REAL_TO_MARKET_MULT     2
	#define ISO_REAL_TO_MARKET_SHIFT    1
	#define ISO_REAL_TO_MARKET_ROUND    0
	
//----------------------------------------------------------

