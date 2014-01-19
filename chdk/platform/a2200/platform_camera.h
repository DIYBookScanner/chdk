// Camera - A2200 - platform_camera.h

// This file contains the various settings values specific to the A2200 camera.
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
    #define CAM_DRYOS			1
	#define CAM_PROPSET			4
	#define CAM_DRYOS_2_3_R39	1		// Defined for cameras with DryOS version R39 or higher
	#define CAM_DRYOS_2_3_R47	1		// Defined for cameras with DryOS version R47 or higher

    #define CAM_RAW_ROWPIX		4416		// Found @0xff937b24
	#define CAM_RAW_ROWS		3296		// Found @0xff937b2c
	
	#undef  CAM_UNCACHED_BIT
	#define CAM_UNCACHED_BIT	0x40000000	// Found @0xff83a6a8
	
    #define CAM_JPEG_WIDTH		4320
	#define CAM_JPEG_HEIGHT		3240
	#define CAM_ACTIVE_AREA_X1	16
	#define CAM_ACTIVE_AREA_Y1	29
	#define CAM_ACTIVE_AREA_X2	4352
	#define CAM_ACTIVE_AREA_Y2	3275
	
	#define	CAM_DNG_LENS_INFO	{ 50,10, 200,10, 27,10, 56,10 } // See comments in camera.h
	
	// Almost sure values
	//
	#undef	CAM_SENSOR_BITS_PER_PIXEL
	#define	CAM_SENSOR_BITS_PER_PIXEL	12
	
	#define	cam_CFAPattern		0x01000201	// Green  Blue  Red  Green
//	#define	cam_CFAPattern		0x02010100	// Red  Green  Green  Blue
	
	#define CAM_COLORMATRIX1                             \
	827547, 1000000, -290458, 1000000, -126086, 1000000, \
	-12829, 1000000,  530507, 1000000,   50537, 1000000, \
	  5181, 1000000,   48183, 1000000,  245014, 1000000
	
	#define cam_CalibrationIlluminant1	1	// Daylight
	
	#undef CAM_SCREEN_WIDTH
	#define CAM_SCREEN_WIDTH	360
    #undef CAM_SCREEN_HEIGHT
    #define CAM_SCREEN_HEIGHT	240
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH	720
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_HEIGHT	240
	
	#undef 	CAM_USES_ASPECT_CORRECTION
	#define	CAM_USES_ASPECT_CORRECTION	1	//camera uses the modified graphics primitives to map screens an viewports to buffers more sized
	
	#define	CAM_ZEBRA_NOBUF 1
	
	#define PARAM_CAMERA_NAME	4		// parameter number for GetParameterData
    
    #define CAM_HAS_ND_FILTER	1
	
	#define CAM_EXT_TV_RANGE	1
	
	#define	CAM_VIDEO_QUALITY_ONLY		1
	
	#define	DNG_VERT_RLE_BADPIXELS		1
	
	#define	CAM_DATE_FOLDER_NAMING		1
	
	#define CAM_DRIVE_MODE_FROM_TIMER_MODE 1
	
	#define	CAM_STARTUP_CRASH_FILE_OPEN_FIX	1
	
	#undef  CAM_HAS_IRIS_DIAPHRAGM
	
	#undef  CAM_HAS_ERASE_BUTTON
	
    #undef  CAM_HAS_IS                              // Camera does not have an image stabilizer

	#undef  CAM_HAS_MANUAL_FOCUS
	
	#undef  CAM_VIDEO_CONTROL
	
	#undef	CAM_BITMAP_PALETTE
	#define	CAM_BITMAP_PALETTE	13

	#define CAM_LOAD_CUSTOM_COLORS          1       // Enable loading CHDK colors into the camera palette memory/hardware
	#define CHDK_COLOR_BASE                 0xA2    // Start color index for CHDK colors loaded into camera palette.
	
	//#define CAM_CAN_SD_OVER_IN_AF_LOCK      1   // Camera allows subject distance (focus) override when in AF Lock mode
	#undef  CAM_CAN_SD_OVER_NOT_IN_MF
	#define CAM_CAN_SD_OVER_IN_AF_LOCK_ONLY 1		//exact meaning: SD override works in AF lock or movie mode
	
	#define CAM_SHOW_OSD_IN_SHOOT_MENU	1

    #define  CAM_ADJUSTABLE_ALT_BUTTON      1    // ALT-button can be set from menu
    #define CAM_ALT_BUTTON_NAMES            { "Playback", "Face", "Disp" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PLAYBACK, KEY_FACE, KEY_DISPLAY }
	
	// Not sure values
	//
	//#undef  CAM_USE_ZOOM_FOR_MF
	//#define	CAM_AF_SCAN_DURING_VIDEO_RECORD	1
	#define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1
    #define CAM_HAS_ZOOM_LEVER               1    // Camera has dedicated zoom buttons
    #define CAM_USE_ZOOM_FOR_MF              1    // Zoom lever can be used for manual focus adjustments
    #define CAM_NEED_SET_ZOOM_DELAY          300  // Define to add a delay after setting the zoom position
    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS  1    // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoo
    #define CAM_CAN_MUTE_MICROPHONE          1

    #define CAM_HAS_FILEWRITETASK_HOOK       1
