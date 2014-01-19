// Camera - a590 - platform_camera.h

// This file contains the various settings values specific to the a590 camera.
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

    #define CAM_HAS_HI_ISO_AUTO_MODE        1

    #define CAM_CAN_MUTE_MICROPHONE         1
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Print", "Display" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_DISPLAY }
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    //#define CAM_EV_IN_VIDEO               1      // not working on 101b!!!
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF

    #define CAM_DNG_LENS_INFO               { 58,10, 232,10, 26,10, 55,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                              \
     726857, 1000000, -176454, 1000000, -124118, 1000000, \
     -71340, 1000000,  592001, 1000000,   75622, 1000000, \
      63222, 1000000,   50547, 1000000,  219582, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3264
    #define CAM_JPEG_HEIGHT                 2448
    #define CAM_ACTIVE_AREA_X1              12
    #define CAM_ACTIVE_AREA_Y1              10

    #define CAM_ACTIVE_AREA_X2              3300
    #define CAM_ACTIVE_AREA_Y2              2480

    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #define CAM_EXT_TV_RANGE                1
    #define CAM_MULTIPART                   1
    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1       // enable fix for camera crash at startup when opening the conf / font files see http://chdk.setepontos.com/index.php?topic=6179.0

    #undef  CAMERA_MIN_DIST
    #define CAMERA_MIN_DIST                 51     // Override min subject distance

    #define CAM_HAS_FILEWRITETASK_HOOK       1

    #define REMOTE_SYNC_STATUS_LED  0xC02200C4      // specifies an LED that turns on while camera waits for USB remote to sync

    // Define shortcut overrides where defaults are not suitable
    // Shutter Half Press + Down = AFL
    //Half press shoot button    
    #define SHORTCUT_DISABLE_OVERRIDES   KEY_DISPLAY

//----------------------------------------------------------

