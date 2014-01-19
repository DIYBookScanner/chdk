// Camera - a2100 - platform_camera.h

// This file contains the various settings values specific to the a2100 camera.
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

    #define CAM_DRYOS                       1
    #define CAM_DRYOS_2_3_R31               1  

//----------------------------------------------------------
// left as test

#undef CAM_USE_ZOOM_FOR_MF   //      1           // Zoom lever can be used for manual focus adjustments
#define CAM_VIDEO_CONTROL           1           // pause / unpause video recordings



#undef  CAM_SWIVEL_SCREEN                       // Camera has rotated LCD screen

#undef  CAM_MULTIPART                           // Camera supports SD-card multipartitioning

#define CAM_HAS_ZOOM_LEVER          1           // Camera has dedicated zoom buttons
#define  CAM_DRAW_EXPOSITION        1             // Output expo-pair on screen (for cameras which (sometimes) don't do that)
#undef CAM_HAS_ERASE_BUTTON       // 1           // Camera has dedicated erase button
#undef CAM_HAS_IRIS_DIAPHRAGM  //    1           // Camera has real diaphragm mechanism (http://en.wikipedia.org/wiki/Diaphragm_%28optics%29)
#define CAM_HAS_ND_FILTER           1            // Camera has build-in ND filter
#undef CAM_HAS_MANUAL_FOCUS    //    1           // Camera has manual focus mode
#undef CAM_HAS_USER_TV_MODES     //  1           // Camera has tv-priority or manual modes with ability to set tv value

//#undef  CAM_SHOW_OSD_IN_SHOOT_MENU              // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode

#define CAM_HAS_IS                  1           // Camera has image stabilizer

#undef  CAM_CONSOLE_LOG_ENABLED                 // Development: internal camera stdout -> A/stdout.txt
#define  CAM_CAN_MUTE_MICROPHONE	0                 // Camera has function to mute microphone

#undef CAM_MENU_BORDERWIDTH
#define CAM_MENU_BORDERWIDTH        10          // Defines the width of the border on each side of the CHDK menu. The CHDK menu will have this
                                                // many pixels left blank to the on each side. Should not be less than 10 to allow room for the
                                                // scroll bar on the right.

#define  CAM_AF_SCAN_DURING_VIDEO_RECORD   0      // CHDK can make single AF scan during video record
#define  CAM_EV_IN_VIDEO             0            // CHDK can change exposure in video mode

#define  CAM_REAR_CURTAIN           1             // Camera do not have front/rear curtain flash sync in menu
//#undef  CAM_BRACKETING                          // Cameras that have bracketing (focus & ev) in original firmware already, most likely s- & g-series (propcase for digic III not found yet!)
#define  CAM_EXT_TV_RANGE			1            // CHDK can make exposure time longer than 64s

    #undef  CAM_UNCACHED_BIT
	#define CAM_UNCACHED_BIT  0x40000000 // Found @0xffc16e84

	#undef CAM_SENSOR_BITS_PER_PIXEL
#define CAM_SENSOR_BITS_PER_PIXEL   12          // Bits per pixel. 10 is standard, 12 is supported except for curves
#undef CAM_BITMAP_PALETTE
#define CAM_BITMAP_PALETTE          10           // which color set is used for this camera

// Older cameras had a screen/bitmap buffer that was 360 pixels wide (or 480 for wide screen models)
// CHDK was built around this 360 pixel wide display model
// Newer cameras have a 720 pixel wide bitmap (960 for wide screen cameras)
// To accomadate this the CHDK co-ordinate system assumes a 360/480 wide buffer and the
// pixel drawing routines draw every pixel twice to scale the image up to the actual buffer size
// Define CAM_USES_ASPECT_CORRECTION with a value of 1 to enable this scaled display
    #undef  CAM_USES_ASPECT_CORRECTION   
    #define CAM_USES_ASPECT_CORRECTION      1   //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                720 // Actual width of bitmap screen in bytes

	
#define CAM_QUALITY_OVERRIDE                1     // define this in platform_camera.h to enable 'Super Fine' JPEG compression mode
                                                // used to allow super fine JPEG option on cameras where this has been removed
                                                // from the Canon menu. Note: may not actually work on all cameras.


// RAW & DNG related values
    #undef  DEFAULT_RAW_EXT 
    #define DEFAULT_RAW_EXT                 2  // use .CR2            // extension to use for raw (see raw_exts in conf.c)
    #define CAM_JPEG_WIDTH                  4000
    #define CAM_JPEG_HEIGHT                 3000
	
    #define CAM_ACTIVE_AREA_X1              20
    #define CAM_ACTIVE_AREA_Y1              24
    #define CAM_ACTIVE_AREA_X2              4020 
    #define CAM_ACTIVE_AREA_Y2              3024
	
    #define cam_CFAPattern                  0x01000201  // GBRG                            // Camera Bayer sensor data layout (DNG colors are messed up if not correct - should be either 0x01000201 = [Green Blue Red Green]  or 0x02010100 = [Red  Green  Green  Blue]

    #define CAM_COLORMATRIX1                               \
     793137,  1000000, -271722, 1000000, -113158, 1000000, \
     -55013,  1000000,  541027, 1000000,   32394, 1000000, \
      21921,  1000000,   71395, 1000000,  181847, 1000000                        // DNG color profile matrix
    #define cam_CalibrationIlluminant1      1   // Daylight               // DNG color profile illuminant - set it to 17 for standard light A

//A2100 36-216mm (35mm equiv), F3.2 - F5.9, 
//#undef  CAM_DNG_LENS_INFO                       // Define this to include camera lens information in DNG files
                                                // Value should be an array of 4 DNG 'RATIONAL' values specifying
                                                //   - min focal length in mm
                                                //   - max focal length in mm
                                                //   - max aperture at min focal length
                                                //   - max aperture at max focal length
                                                // E.G - SX30 = { 43,10, 1505,10, 27,10, 58,10 }
                                                //            = 4.3 - 150.5mm, f/2.7 - f.5.8
                                                // Each pair of integers is one 'RATIONAL' value (numerator,denominator)

#define CAM_DNG_LENS_INFO               { 360,10, 2160,10, 32,10, 59,10 } // See comments in camera.h												
												
												
												
												
#define  PARAM_CAMERA_NAME                  4      // parameter number for GetParameterData to get camera name


//#undef CAM_DRIVE_MODE_FROM_TIMER_MODE            // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                 // Used to enabled bracketing in custom timer, required on many recent cameras
                                                 // see http://chdk.setepontos.com/index.php/topic,3994.405.html

//#undef CAM_LOAD_CUSTOM_COLORS                   // Define to enable loading CHDK custom colors into the camera color palette
                                                // requires load_chdk_palette() and vid_get_bitmap_active_palette() to be defined
                                                // correctly for the camera along with
//#undef CAM_USE_COLORED_ICONS                    // If the color palette contains enough shades of red, green, yellow and grey
                                                // defined then enable this use the better icons (from CHDK-DE). See gui_batt.c
                                                // and gui_space.c.

//#define CAM_USB_EVENTID         0x902           // Levent ID for USB control. Changed to 0x202 in DryOS R49 so needs to be overridable.








#define CAM_DRYOS         1
#define CAM_PROPSET		2
#define CAM_RAW_ROWPIX    4104 // Found @0xffcc7c70
#define CAM_RAW_ROWS      3048 // Found @0xffcc7c78

	#define REMOTE_SYNC_STATUS_LED 	0xC022000C		// specifies an LED that turns on while camera waits for USB remote to sync
