// Camera - ixus130_sd1400 - platform_camera.h

// This file contains the various settings values specific to the ixus130 camera.
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

    #define CAM_PROPSET                 3
    #define CAM_DRYOS                   1
    #define CAM_DRYOS_2_3_R39           1

    #define CAM_RAW_ROWPIX              4416		// 14 MP 12bpp
    #define CAM_RAW_ROWS                3296		// 

    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

    #define CAM_HAS_ZOOM_LEVER          1

    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU            1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD       1
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU           1

    #define CAM_HAS_IS                  1
    #undef CAM_HAS_JOGDIAL

    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY      1

    #define CAM_EXT_TV_RANGE            1

    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000

    #define CAM_MAKE                    "Canon"

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE          5

    #undef  CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH            960 // Actual width of bitmap screen in bytes

    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_HEIGHT           270 // Actual height of bitmap screen in rows

    #define CAM_ZEBRA_NOBUF             1

    #define CAM_QUALITY_OVERRIDE        1
    #undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #undef CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127

    #define CAM_DNG_LENS_INFO   { 50,10, 200,10, 28,10, 59,10 } // See comments in camera.h

    #define cam_CFAPattern              0x02010100		// Red  Green  Green  Blue

    #define CAM_COLORMATRIX1 510370, 1000000, -68998, 1000000,  -86859, 1000000, \
                            -279980, 1000000, 766686, 1000000,   67944, 1000000, \
                             -14382, 1000000, 113688, 1000000,  239853, 1000000

    #define cam_CalibrationIlluminant1  17			// Standard Light A

    #define CAM_ACTIVE_AREA_X1          48
    #define CAM_ACTIVE_AREA_Y1          28
    #define CAM_ACTIVE_AREA_X2          4416-48
    #define CAM_ACTIVE_AREA_Y2          3296-28

    #undef CAM_USES_ASPECT_CORRECTION   
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 

    // cropping
    #define CAM_JPEG_WIDTH              4320
    #define CAM_JPEG_HEIGHT             3240
    // camera name
    #define PARAM_CAMERA_NAME           4			// parameter number for GetParameterData sd990: OK
    #define CAM_DATE_FOLDER_NAMING      1

   #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1  

