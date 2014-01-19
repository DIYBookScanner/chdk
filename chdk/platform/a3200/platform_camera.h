// Camera - A3200 - platform_camera.h

// This file contains the various settings values specific to the A3200 camera.
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

    // Sure values
    #define CAM_DRYOS                       1
    #define CAM_PROPSET                     4
    #define CAM_DRYOS_2_3_R39               1
    #define CAM_DRYOS_2_3_R47               1

    #define CAM_RAW_ROWPIX    				4416 // a3200 Found @0xff93a144
	#define CAM_RAW_ROWS      				3296 // a3200 Found @0xff93a14c

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000  // a3200 Found @0xff83a6c0  

    #define CAM_JPEG_WIDTH                  4320    // a3200 from dpreview
    #define CAM_JPEG_HEIGHT                 3240    // a3200 from dpreview

//loc_ffb20c48:
//ffb20c48:       e3a00d45        mov     r0, #4416       ; 0x1140
//ffb20c4c:       e5810000        str     r0, [r1]
//ffb20c50:       e3a00ece        mov     r0, #3296       ; 0xce0
    #define CAM_ACTIVE_AREA_X1              96		// 
    #define CAM_ACTIVE_AREA_Y1              56		//
    #define CAM_ACTIVE_AREA_X2              4416	//	a3200 found @ffb20c48
    #define CAM_ACTIVE_AREA_Y2              3296	//	a3200 found @ffb20c50

    #define DNG_VERT_RLE_BADPIXELS          1
    #define CAM_DNG_LENS_INFO               { 50,10, 250,10, 28,10, 59,10 } // See comments in camera.h   a3300is

    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #undef  CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    #define cam_CFAPattern                  0x02010100  // Red  Green  Green  Blue

    #define CAM_COLORMATRIX1                             \
    827547, 1000000, -290458, 1000000, -126086, 1000000, \
    -12829, 1000000,  530507, 1000000,   50537, 1000000, \
      5181, 1000000,   48183, 1000000,  245014, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1       // camera uses the modified graphics primitives to map screens an viewports to buffers more sized

    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_QUALITY_OVERRIDE            1
    #define CAM_CAN_MUTE_MICROPHONE         1

    #define CAM_ZEBRA_NOBUF                 1		// ??

    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #define CAM_HAS_ND_FILTER               1       //

    #define CAM_VIDEO_QUALITY_ONLY          1       //

    #define CAM_DATE_FOLDER_NAMING          1       // ??

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1       // ??

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1       // ??

    #define CAM_EXT_TV_RANGE                1

    #define CAM_CHDK_HAS_EXT_VIDEO_TIME     1
    #define CAM_HAS_MOVIE_DIGEST_MODE       1       // no, it doesn't, but movie_status is 6 in movie mode idle

    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #undef  CAM_HAS_ERASE_BUTTON

    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_VIDEO_CONTROL

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              16      //

    #define CHDK_COLOR_BASE                 0xE0    // Start color index for CHDK colors loaded into camera palette.
    #define CAM_LOAD_CUSTOM_COLORS

    #define CAM_HAS_ZOOM_LEVER               1    // Camera has dedicated zoom buttons
    #define CAM_USE_ZOOM_FOR_MF              1    // Zoom lever can be used for manual focus adjustments    
    #define CAM_NEED_SET_ZOOM_DELAY          300  // Define to add a delay after setting the zoom position
    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS  1    // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoo

    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Playback", "Face", "Disp"}
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PLAYBACK, KEY_FACE, KEY_DISPLAY }

    #define CAM_HAS_FILEWRITETASK_HOOK       1

    // Define shortcut overrides where defaults are not suitable
    // a3200 has no erase button, so make DISP button the toggle_raw and Alt +/- shortcuts.
    //Alt mode
    // NOTE both of these conflict with adjustable alt
    #define SHORTCUT_TOGGLE_RAW          KEY_DISPLAY
    #define SHORTCUT_MF_TOGGLE           KEY_FACE
