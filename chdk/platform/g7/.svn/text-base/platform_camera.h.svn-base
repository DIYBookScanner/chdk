// Camera - g7 - platform_camera.h

// This file contains the various settings values specific to the g7 camera.
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

    #define CAM_RAW_ROWPIX                  3736    // for 10 MP
    #define CAM_RAW_ROWS                    2772    // for 10 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Print", "FE" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_MICROPHONE }
    #define CAM_MULTIPART                   1
    #define CAM_HAS_ND_FILTER               1
    #define CAM_HAS_HI_ISO_AUTO_MODE        1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL                 1

    #define CAM_DNG_LENS_INFO               { 74,10, 444,10, 28,10, 48,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                              \
     575419, 1000000, -185557, 1000000,  -77898, 1000000, \
    -213702, 1000000,  733569, 1000000,   81514, 1000000, \
     -24604, 1000000,  131906, 1000000,  280378, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #define CAM_ACTIVE_AREA_X1              14
    #define CAM_ACTIVE_AREA_Y1              8
    #define CAM_ACTIVE_AREA_X2              3682
    #define CAM_ACTIVE_AREA_Y2              2764
    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData
    #define CAM_BRACKETING                  1
    #define DNG_EXT_FROM                    ".DPS"
	
	#define REMOTE_SYNC_STATUS_LED 	0xc022006C		// specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_USB_EVENTID_VXWORKS             0x1085 // LogicalEvent ID for ConnectUSBCable, needed to enable USB mode switch
                                                       // NOTE switching back to play reportedly does not work on this camera
	
//----------------------------------------------------------

