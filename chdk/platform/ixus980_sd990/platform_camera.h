// Camera - ixus980_sd990 - platform_camera.h

// This file contains the various settings values specific to the ixus980_sd990 camera.
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

    #define CAM_PROPSET                     2       // all values checked so far match propset 2
    #define CAM_DRYOS                       1

    #define CAM_RAW_ROWPIX                  4480    // 14.7 MP 12bpp
    #define CAM_RAW_ROWS                    3348

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART                   1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #define CAM_HAS_HI_ISO_AUTO_MODE        1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  CAM_VIDEO_CONTROL
    #undef  CAM_UNCACHED_BIT                        // shut up compiler
    #define CAM_UNCACHED_BIT                0x40000000
    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              2

    #define CAM_HAS_JOGDIAL                 1
//  #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_VIDEO_QUALITY_ONLY          1
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_DNG_LENS_INFO               { 77,10, 285,10, 28,10, 58,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x01000201 // Green  Blue  Red  Green
    // color preliminary
    #define CAM_COLORMATRIX1                              \
     837237, 1000000, -290137, 1000000, -128156, 1000000, \
    -127762, 1000000,  643909, 1000000,   52973, 1000000, \
       4446, 1000000,   88354, 1000000,  224246, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  4416
    #define CAM_JPEG_HEIGHT                 3312
    #define CAM_ACTIVE_AREA_X1              12
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              4444
    #define CAM_ACTIVE_AREA_Y2              3324
    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData sd990: OK

   // copied from DavidBs D10 stuff
    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

//  #define DNG_EXT_FROM                    ".CR2"

	#define REMOTE_SYNC_STATUS_LED 	0xc02200BC		// specifies an LED that turns on while camera waits for USB remote to sync

//----------------------------------------------------------

