// Camera - A3300 - platform_camera.h

// This file contains the various settings values specific to the A3300 camera.
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
    //
    #define CAM_DRYOS                       1
    #define CAM_PROPSET                     4
    #define CAM_DRYOS_2_3_R39               1
    #define CAM_DRYOS_2_3_R47               1

    #define CAM_RAW_ROWPIX                  4704    // Found @0xFFB213A0   a3300is
    #define CAM_RAW_ROWS                    3504    // Found @0xFFB21398  a3300is

    #define CAM_ADJUSTABLE_ALT_BUTTON 1
    #define CAM_ALT_BUTTON_NAMES            { "Print", "Face", "Disp"}
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_FACE, KEY_DISPLAY }

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000  // Found @0xff83a6a8   a3300is

    #define CAM_JPEG_WIDTH                  4608    // a3300is   @FFB213A0
    #define CAM_JPEG_HEIGHT                 3456    // a3300is   @FFB213A8

    #define CAM_ACTIVE_AREA_X1              16
    #define CAM_ACTIVE_AREA_Y1              26
    #define CAM_ACTIVE_AREA_X2              4640
    #define CAM_ACTIVE_AREA_Y2              3486

    #define DNG_VERT_RLE_BADPIXELS          1
    #define CAM_DNG_LENS_INFO               { 50,10, 250,10, 28,10, 59,10 } // See comments in camera.h   a3300is

    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define cam_CFAPattern                  0x02010100  // Red  Green  Green  Blue

    #define CAM_COLORMATRIX1                             \
    827547, 1000000, -290458, 1000000, -126086, 1000000, \
    -12829, 1000000,  530507, 1000000,   50537, 1000000, \
      5181, 1000000,   48183, 1000000,  245014, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1       //camera uses the modified graphics primitives to map screens an viewports to buffers more sized

	#undef  CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

    #define CAM_QUALITY_OVERRIDE            1

    #define CAM_ZEBRA_NOBUF                 1

    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #undef  CAM_HAS_ERASE_BUTTON    

    #define CAM_HAS_ND_FILTER               1

    #define CAM_VIDEO_QUALITY_ONLY          1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_CAN_MUTE_MICROPHONE         1

    #define CAM_DATE_FOLDER_NAMING          1

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1

    #define CAM_EXT_TV_RANGE                1

    #define CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE  1

    #undef  CAM_HAS_IRIS_DIAPHRAGM

    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_VIDEO_CONTROL

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              15      // palette number reserved for A3300 in core/gui_draw.h

    #define CHDK_COLOR_BASE                 0xE2    // Start color index for CHDK colors loaded into camera palette. Kosy chose a place Canon doesn't seem to use.
    #define CAM_LOAD_CUSTOM_COLORS	    	  1       // Enable loading CHDK colors into the camera palette memory/hardware	

    // Define shortcut overrides where defaults are not suitable
    // a3300 has no erase button, so make DISP button the toggle_raw and Alt +/- shortcuts.
    //Alt mode
    // NOTE both of these conflict with adjustable alt
    #define SHORTCUT_TOGGLE_RAW          KEY_DISPLAY
    #define SHORTCUT_MF_TOGGLE           KEY_FACE
