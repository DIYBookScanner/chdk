// Camera - ixus95_sd1200 - platform_camera.h

// This file contains the various settings values specific to the ixus95_sd1200 camera.
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

    #define CAM_RAW_ROWPIX                  3720
    #define CAM_RAW_ROWS                    2772

    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART                   1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES

    #undef  CAM_DEFAULT_ALT_BUTTON
    #define CAM_DEFAULT_ALT_BUTTON          KEY_PLAYBACK

    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY          1

    #define CAM_EXT_TV_RANGE                1

    #undef  CAM_UNCACHED_BIT                        // shut up compiler
    #define CAM_UNCACHED_BIT                0x40000000

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              2

    #define CAM_QUALITY_OVERRIDE            1
	#undef   CAM_SENSOR_BITS_PER_PIXEL
	#define  CAM_SENSOR_BITS_PER_PIXEL   12

    #define CAM_DNG_LENS_INFO               { 62,10, 186,10, 28,10, 49,10 } // See comments in camera.h
	// pattern
    #define  cam_CFAPattern                 0x02010100      // Red  Green  Green  Blue

    // color preliminary
    // from para in forum
    #define  CAM_COLORMATRIX1                              \
     1484685, 1000000, -530958, 1000000, -208054, 1000000, \
      143142, 1000000,  793552, 1000000,   83907, 1000000, \
      146290, 1000000,  -44679, 1000000,  430414, 1000000

    #define  cam_CalibrationIlluminant1     1       // Daylight

    // cropping
    #define  CAM_JPEG_WIDTH                 3648
    #define  CAM_JPEG_HEIGHT                2736
    #define  CAM_ACTIVE_AREA_X1             8
    #define  CAM_ACTIVE_AREA_Y1             12
    #define  CAM_ACTIVE_AREA_X2             3692
    #define  CAM_ACTIVE_AREA_Y2             2772

    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    // camera has little free memory
    #define CAM_ZEBRA_NOBUF                 1

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html
	#define REMOTE_SYNC_STATUS_LED 	0xC0220138		// specifies an LED that turns on while camera waits for USB remote to sync

//    #define CAM_HAS_FILEWRITETASK_HOOK       1
//----------------------------------------------------------

