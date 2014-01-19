// Camera - a800 - platform_camera.h

// This file contains the various settings values specific to the a800 camera.
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

    #define CAM_PROPSET                     4  //processor DIGIC III, but release date (Phil) and properties like PROPCASE_OPTICAL_ZOOM_POSITION, PROPCASE_SHOOTING,PROPCASE_IS_FLASH_READY as propset4.h
    #define CAM_DRYOS                       1
    #define CAM_DRYOS_2_3_R39 				1 // Defined for cameras with DryOS version R39 or higher
	#define CAM_DRYOS_2_3_R47 				1 // Defined for cameras with DryOS version R47 or higher

    #define CAM_RAW_ROWPIX                  3720 //do stub_entry.S
    #define CAM_RAW_ROWS                    2772 //do stub_entry.S
	#undef  CAM_UNCACHED_BIT
	#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc29904

	
    #undef  CAM_USE_ZOOM_FOR_MF  //zoom with buton and not lever
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #undef  CAM_HAS_IS
    #undef  CAM_VIDEO_CONTROL
    #define CAM_REAR_CURTAIN                1
    #undef  DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                 2   // use .CR2
    #define CAM_EXT_TV_RANGE                1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_CAN_MUTE_MICROPHONE         1
    #define CAM_EV_IN_VIDEO                 1
	#define CAM_QUALITY_OVERRIDE            1

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              8

    #define CAM_DNG_LENS_INFO               { 66,10, 216,10, 30,10, 58,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x01000201 // Green Blue Red Green
    // color

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1      1   // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #define CAM_ACTIVE_AREA_X1              6
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              3690
    #define CAM_ACTIVE_AREA_Y2              2772

    // camera name
    #define PARAM_CAMERA_NAME               4   // parameter number for GetParameterData to get camera name
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

	#define CAM_STARTUP_CRASH_FILE_OPEN_FIX    1     // enable workaround for camera crash at startup when opening the conf / font files
                                                    // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DATE_FOLDER_NAMING          0x100 //Value found in the last function, which is called in GetImageFolder. (first compare)

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE      // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html

    #define CAM_USE_OPTICAL_MAX_ZOOM_STATUS 1   // Use ZOOM_OPTICAL_MAX to reset zoom_status when switching from digital to optical zoom in gui_std_kbd_process()

//----------------------------------------------------------
