// Camera - sx120is - platform_camera.h

// This file contains the various settings values specific to the sx120is camera.
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

    #define CAM_PROPSET                     3
    #define CAM_DRYOS                       1
    //#define CAM_DRYOS_2_3_R39               1 // Don't define this - even though cam is R39 is still needs old CHDK code

    #define CAM_RAW_ROWPIX                  3728    // see platform/sub/*/lib.c
    #define CAM_RAW_ROWS                    2778

    #define CAM_CAN_MUTE_MICROPHONE         1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      0
    #define CAM_REAR_CURTAIN                1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART                   1
    #define CAM_HAS_JOGDIAL                 1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT                        // shut up compiler
    #define CAM_UNCACHED_BIT                0x40000000
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12
    #undef  CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL                 128     // black level set to 128 per reports on the forum
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #define CAM_DNG_LENS_INFO               { 60,10, 600,10, 28,10, 43,10 } // See comments in camera.h

    #define cam_CFAPattern                  0x01000201 // Green  Blue  Red  Green

    #define CAM_COLORMATRIX1                              \
     728616, 1000000, -224281, 1000000, -104767, 1000000, \
       4176, 1000000,  440179, 1000000,   45782, 1000000, \
      26983, 1000000,   68443, 1000000,  186465, 1000000

    #define CAM_ACTIVE_AREA_X1              12
    #define CAM_ACTIVE_AREA_Y1              10
    #define CAM_ACTIVE_AREA_X2              3664
    #define CAM_ACTIVE_AREA_Y2              2768
    #define cam_CalibrationIlluminant1      1       // Daylight
    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              4

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    #define CAM_EXT_TV_RANGE                1
    #define CAM_QUALITY_OVERRIDE            1

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define CAM_DATE_FOLDER_NAMING          0x100 //Value found in the last function, which is called in GetImageFolder. (first compare)

//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync
	
//----------------------------------------------------------

