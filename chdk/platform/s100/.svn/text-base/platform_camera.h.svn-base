// Camera - s100 - platform_camera.h

// This file contains the various settings values specific to the s100 camera.
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

    #define CAM_DRYOS         1
    #define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
    #define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
    #define CAM_RAW_ROWPIX    4160 // Found @0xff190f44
    #define CAM_RAW_ROWS      3124 // Found @0xff190f4c
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02bd84
    #define CAM_PROPSET                     4
    #define CAM_DRYOS                       1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH            10
    #define CAM_QUALITY_OVERRIDE            1
    #define CAM_HAS_JOGDIAL                 1
    #define CAM_HAS_ERASE_BUTTON            1
    #undef  CAM_KEY_PRESS_DELAY
    #define CAM_KEY_PRESS_DELAY             60      // delay after a press

    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Playback", "Video" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_VIDEO }
    #define CAM_DISP_BUTTON_NAME            "Video"
    #define CAM_BRACKETING                  1
    #define CAM_HAS_VIDEO_BUTTON            1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY          1
    #define CAM_EXT_TV_RANGE                1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1

    // camera name
    #define PARAM_CAMERA_NAME               4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION      1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_BITMAP_WIDTH
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_WIDTH                960 // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT               270 // Actual height of bitmap screen in rows

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE              13
    #define CAM_LOAD_CUSTOM_COLORS          1   // Enable loading CHDK colors into the camera palette memory
    #define CHDK_COLOR_BASE                 0xA8// Start color index for CHDK colors loaded into camera palette.

    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN                    2

    #define CAM_DNG_LENS_INFO               { 52,10, 260,10, 20,10, 59,10 }

    // From G15 native RAW file as converted to DNG using Adobe DNG Converter
    // http://www.adobe.com/support/downloads/product.jsp?product=106&platform=Windows
    // Matrices from converted DNG's EXIF data
    #define cam_CFAPattern                  0x02010100 // = [Red,Green][Green,Blue]
    #define cam_CalibrationIlluminant1          17      // Standard Light A
    #define cam_CalibrationIlluminant2          21      // D65
    #define CAM_COLORMATRIX1    \
      9188, 10000,  -3882, 10000,   -248, 10000, \
     -2564, 10000,   9818, 10000,   3218, 10000, \
       349, 10000,    317, 10000,   4547, 10000
    #define CAM_COLORMATRIX2    \
      7968, 10000,  -2565, 10000,   -636, 10000, \
     -2873, 10000,  10697, 10000,   2513, 10000, \
       180, 10000,    667, 10000,   4211, 10000
    #define CAM_FORWARDMATRIX1    \
      6196, 10000,   2430, 10000,   1018, 10000, \
      1505, 10000,   9964, 10000,  -1470, 10000, \
     -1633, 10000,  -3155, 10000,  13040, 10000
    #define CAM_FORWARDMATRIX2    \
      6242, 10000,   4092, 10000,   -691, 10000, \
       188, 10000,  11431, 10000,  -3312, 10000, \
      -420, 10000,  -1341, 10000,  10012, 10000
    #define CAM_DNG_EXPOSURE_BIAS 0,1

    #define CAM_JPEG_WIDTH                  4048
    #define CAM_JPEG_HEIGHT                 3048
    // S100 native RAW converted to DNG's EXIF data: Active Area
    #define CAM_ACTIVE_AREA_X1              104
    #define CAM_ACTIVE_AREA_Y1              11
    #define CAM_ACTIVE_AREA_X2              4152
    #define CAM_ACTIVE_AREA_Y2              3059

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1   // enable workaround for camera crash at startup when opening the conf / font files
                                                // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_DATE_FOLDER_NAMING                      1
    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html
    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID         0x202 // Levent ID for USB control. Changed in DryOS R49 so needs to be overridable.

	#define REMOTE_SYNC_STATUS_LED 	0xC022C30C // specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_HAS_GPS                     1

    #undef CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #undef CAM_AF_SCAN_DURING_VIDEO_RECORD

//----------------------------------------------------------
