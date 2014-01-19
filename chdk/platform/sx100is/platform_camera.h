// Camera - sx100is - platform_camera.h

// This file contains the various settings values specific to the sx100is camera.
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

    #define CAM_RAW_ROWPIX                  3336    // for new 8 MP
    #define CAM_RAW_ROWS                    2480    // for new 8 MP

    #define CAM_CAN_MUTE_MICROPHONE         1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Print", "Face" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_FACE }
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_REAR_CURTAIN                1
    #define CAM_HAS_JOGDIAL                 1
    #define CAM_HAS_HI_ISO_AUTO_MODE        1

    #define CAM_DNG_LENS_INFO               { 60,10, 600,10, 28,10, 43,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                              \
     656793, 1000000, -168702, 1000000, -108030, 1000000, \
      -2711, 1000000,  661538, 1000000,   37919, 1000000, \
      77255, 1000000,   48834, 1000000,  241797, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3264
    #define CAM_JPEG_HEIGHT                 2448
    #define CAM_ACTIVE_AREA_X1              10
    #define CAM_ACTIVE_AREA_Y1              8
    #define CAM_ACTIVE_AREA_X2              3302
    #define CAM_ACTIVE_AREA_Y2              2474
    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #define DNG_EXT_FROM                    ".CR2"
    #define CAM_MULTIPART                   1
    #define CAM_EXT_TV_RANGE                1
	
//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync
	
//----------------------------------------------------------

