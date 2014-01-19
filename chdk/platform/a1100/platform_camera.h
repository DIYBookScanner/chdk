// Camera - a1100 - platform_camera.h

// This file contains the various settings values specific to the a1100 camera.
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

    #define CAM_RAW_ROWPIX                  4104   
    #define CAM_RAW_ROWS                    3048   

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_MULTIPART                   1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_REAR_CURTAIN                1
    #undef  DEFAULT_RAW_EXT 
    #define DEFAULT_RAW_EXT                 2  // use .CR2 
    #undef  CAM_EXT_TV_RANGE
    #undef  CAM_AF_SCAN_DURING_VIDEO_RECORD
    #undef  CAM_CAN_MUTE_MICROPHONE
    #undef  CAM_EV_IN_VIDEO

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000 // Found @0xffc16e84

    #define CAM_QUALITY_OVERRIDE            1

    // color
    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              12

    #define CAM_DNG_LENS_INFO               { 62,10, 248,10, 27,10, 56,10 } // See comments in camera.h

    // pattern
    #define cam_CFAPattern                  0x01000201  // GBRG               
    #define CAM_COLORMATRIX1                               \
     793137,  1000000, -271722, 1000000, -113158, 1000000, \
     -55013,  1000000,  541027, 1000000,   32394, 1000000, \
      21921,  1000000,   71395, 1000000,  181847, 1000000

    #define cam_CalibrationIlluminant1      1   // Daylight 
    // cropping
    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
    #define CAM_ACTIVE_AREA_X1              20
    #define CAM_ACTIVE_AREA_Y1              24
    #define CAM_ACTIVE_AREA_X2              4020 
    #define CAM_ACTIVE_AREA_Y2              3024

    // camera name
    #define PARAM_CAMERA_NAME               4   // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #undef  CAM_USES_ASPECT_CORRECTION   
    #define CAM_USES_ASPECT_CORRECTION      1   //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH            10

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1

	#define REMOTE_SYNC_STATUS_LED 	0xC02200CC		// specifies an LED that turns on while camera waits for USB remote to sync
//----------------------------------------------------------

