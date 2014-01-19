// Camera - ixus200_sd980 - platform_camera.h

// This file contains the various settings values specific to the a495 camera.
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

    #define CAM_DRYOS_2_3_R39               1//stat is different, as well as some other functions
    #define CAM_PROPSET                     3
    #define CAM_DRYOS                       1

    #define CAM_RAW_ROWPIX                  4080 // from calcs see 100C lib.c
    #define CAM_RAW_ROWS                    3048 //  "     "    "    "    "

    #define CAM_HAS_VIDEO_BUTTON            1
    #define CAM_VIDEO_QUALITY_ONLY          1
    #define CAM_BRACKETING                  1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART                   1
    #define CAM_HAS_JOGDIAL                 1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT                0x40000000
    #define CAM_HAS_ND_FILTER               1

    #define CAM_DNG_LENS_INFO               { 43,10, 215,10, 28,10, 59,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1      1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
    #define CAM_ACTIVE_AREA_X1              20
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              4056
    #define CAM_ACTIVE_AREA_Y2              3038
    // camera name
    #define PARAM_CAMERA_NAME               4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_EXT_TV_RANGE                1

    #define  CAM_SHOW_OSD_IN_SHOOT_MENU     1

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_SCREEN_WIDTH
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_SCREEN_WIDTH                480 // Width of bitmap screen in CHDK co-ordinates
    #define CAM_BITMAP_WIDTH                960 // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT               270 // Actual height of bitmap screen in rows

    #undef EDGE_HMARGIN
    #define EDGE_HMARGIN                    20

    #define CAM_ZEBRA_NOBUF                 1
   
    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1     // enable workaround for camera crash at startup when opening the conf / font files
                                                    // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DATE_FOLDER_NAMING          0x100 //Value found in the last function, which is called in GetImageFolder. (first compare)

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define CAM_HAS_FILEWRITETASK_HOOK      1

	#define REMOTE_SYNC_STATUS_LED 	0xC0220130		// specifies an LED that turns on while camera waits for USB remote to sync
  
//----------------------------------------------------------
