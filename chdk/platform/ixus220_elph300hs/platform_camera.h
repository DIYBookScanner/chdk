// Camera - sx220hs - platform_camera.h

// This file contains the various settings values specific to the SX220HS camera.
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

    #define CAM_DRYOS_2_3_R47               1
    #define CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE   1
    #define DNG_VERT_RLE_BADPIXELS          1
    #define CAM_AV_OVERRIDE_IRIS_FIX        1       // for cameras that require _MoveIrisWithAv function to override Av.
    #undef  CAM_KEY_PRESS_DELAY
    #define CAM_KEY_PRESS_DELAY             60      // delay after a press
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Video", "Display", "Playback", "Video" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_DISPLAY, KEY_PLAYBACK, KEY_VIDEO }
    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1

    #define CAM_DRYOS_2_3_R39               1
    #define CAM_PROPSET                     4
    #define CAM_DATE_FOLDER_NAMING          1
    #define CAM_DRYOS                       1
    #define CAM_RAW_ROWPIX                  4168
    #define CAM_RAW_ROWS                    3060    // actual size from fw 12754080pix at FF375484 -> 19131120/12*8
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #define CAM_CAN_SD_OVER_IN_AF_LOCK      1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON            1
    #define CAM_VIDEO_QUALITY_ONLY          1
    #undef  CAM_VIDEO_CONTROL
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT                        // shut up compiler
    #define CAM_UNCACHED_BIT                0x40000000

    #undef  DNG_BADPIXEL_VALUE_LIMIT
    #define DNG_BADPIXEL_VALUE_LIMIT        16      // Camera sensor apparently has bad pixels with value > 0 & <=16

    #define CAM_DNG_LENS_INFO               { 43,10, 215,10, 27,10, 59,10 } // See comments in camera.h
    #define cam_CFAPattern  0x02010100
  
    #define CAM_COLORMATRIX1    \
    544808, 1000000, -174047, 1000000, -80399, 1000000, \
    -75055, 1000000,  440444, 1000000,  11367, 1000000, \
     -5801, 1000000,   71589, 1000000, 118914, 1000000
    
    #define cam_CalibrationIlluminant1      1
   
    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
    #define CAM_ACTIVE_AREA_X1              120
    #define CAM_ACTIVE_AREA_Y1              36
    #define CAM_ACTIVE_AREA_X2              4136
    #define CAM_ACTIVE_AREA_Y2              3040
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12
    #define CAM_EXT_TV_RANGE                1
    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              10
    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_WIDTH                960 // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT               270 // Actual height of bitmap screen in rows

    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN                    10

    #define CAM_ZEBRA_NOBUF                 1

    #define CAM_QUALITY_OVERRIDE            1

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1

    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #undef  CAM_HAS_MANUAL_FOCUS
    
    #define CAM_USE_ALT_SET_ZOOM_POINT      1   // Define to use the alternate code in lens_set_zoom_point()
    #define CAM_USE_ALT_PT_MoveOpticalZoomAt 1  // Define to use the PT_MoveOpticalZoomAt() function in lens_set_zoom_point()

    #define CAM_HAS_CMOS                    1
	
	#define REMOTE_SYNC_STATUS_LED 	0xC0220130		// specifies an LED that turns on while camera waits for USB remote to sync
	
//----------------------------------------------------------
