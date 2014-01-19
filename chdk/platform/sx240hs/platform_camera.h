// Camera - sx240hs - platform_camera.h

// This file contains the various settings values specific to the SX240HS camera.
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

    #define CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE   1
    #define DNG_VERT_RLE_BADPIXELS              1
    #define CAM_AV_OVERRIDE_IRIS_FIX            1
    #define CAM_HAS_ND_FILTER                   1 // Camera has built-in ND filter (in addition to iris)
    #undef  CAM_KEY_PRESS_DELAY
    #define CAM_KEY_PRESS_DELAY                 60      // delay after a press
    #define CAM_ADJUSTABLE_ALT_BUTTON       	1
    #define CAM_ALT_BUTTON_NAMES            	{ "Playback", "Video", "Display" }
    #define CAM_ALT_BUTTON_OPTIONS          	{ KEY_PRINT, KEY_VIDEO, KEY_DISPLAY }
    #define CAM_DRIVE_MODE_FROM_TIMER_MODE      1

    #define CAM_DRYOS_2_3_R39                   1
    #define CAM_DRYOS_2_3_R47                   1
    #define CAM_PROPSET                         5
    #define CAM_DATE_FOLDER_NAMING              1
    #define CAM_DRYOS                           1
    #define CAM_RAW_ROWPIX                      4176        //ASM1989 FINSIG  Found @0xff17db40
    #define CAM_RAW_ROWS                        3060        // Found @0xff17db4c
    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1           // Draw pixels on active bitmap buffer only.

    #define CAM_HAS_CMOS                        1

    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON                1
    #define CAM_VIDEO_QUALITY_ONLY              1

    #undef  CAM_VIDEO_CONTROL

    #define CAM_HAS_JOGDIAL                     1
    #undef  CAM_USE_ZOOM_FOR_MF

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                    0x40000000

    #define CAM_DNG_LENS_INFO                   { 45,10,900,10,35,10,68,10 } // See comments in camera.h  -> finsig finds the focus_len_table address at 0xfff4bcf0.This is using DNG_LENS_INFO defined as { 45,10, 900,10, 35,10, 68,10 },
    #define cam_CFAPattern                      0x02010100

    #define CAM_COLORMATRIX1                            \
    544808, 1000000, -174047, 1000000, -80399, 1000000, \
    -75055, 1000000,  440444, 1000000,  11367, 1000000, \
     -5801, 1000000,   71589, 1000000, 118914, 1000000

    #define cam_CalibrationIlluminant1          17

    #define CAM_JPEG_WIDTH                      4000
    #define CAM_JPEG_HEIGHT                     3000

    #define CAM_ACTIVE_AREA_X1                  96
    #define CAM_ACTIVE_AREA_Y1                  24
    #define CAM_ACTIVE_AREA_X2                  4176
    #define CAM_ACTIVE_AREA_Y2                  3060

    #define PARAM_CAMERA_NAME                   4
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL           12

    #define CAM_EXT_TV_RANGE                    1

    #undef  CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE                  13
    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_SHOW_OSD_IN_SHOOT_MENU          1

    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION          1           //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef  CAM_BITMAP_WIDTH
    #undef  CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_WIDTH                    960         // Actual width of bitmap screen in bytes
    #define CAM_BITMAP_HEIGHT                   270         // Actual height of bitmap screen in rows
    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN                        10

    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX     1           // enable workaround for camera crash at startup when opening the conf / font files
                                                            // see http://chdk.setepontos.com/index.php?topic=6179.0

    #define CAM_HAS_FILEWRITETASK_HOOK          1
    #define CAM_FILEWRITETASK_SEEKS             1

    #define CAM_ZEBRA_NOBUF                     1

    #define CAM_QUALITY_OVERRIDE                1

    #undef  CAMERA_MIN_DIST
    #define CAMERA_MIN_DIST                     100         // Override min subject distance
    #undef  CAMERA_MAX_DIST
    #define CAMERA_MAX_DIST                     1550000     // Override max subject distance; manually checked up to 1550388, with MF max 1369863 (double step)

//    #define CAM_HAS_GPS                         1           // Only valid for sx260

    #define CAM_USE_SUNRISE                     1

    #define CAM_CHDK_HAS_EXT_VIDEO_TIME         1

    #define CAM_LOAD_CUSTOM_COLORS              1           // Enable loading CHDK colors into the camera palette memory/hardware
    #define CHDK_COLOR_BASE                     0xA8        // Start color index for CHDK colors loaded into camera palette.

    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID                     0x202       // Levent ID for USB control. Changed in DryOS R49, R50 so needs to be overridable.

    #define CAM_HAS_MOVIE_DIGEST_MODE           1 

    #define CAM_USE_ALT_SET_ZOOM_POINT          1           // Define to use the alternate code in lens_set_zoom_point()
    #define CAM_USE_ALT_PT_MoveOpticalZoomAt    1           // Define to use the PT_MoveOpticalZoomAt() function in lens_set_zoom_point()

    #define MKDIR_RETURN_ONE_ON_SUCCESS         1    // mkdir() return 1 on success, 0 on fail.

    #define CAM_DISABLE_RAW_IN_AUTO             1 // For cameras that don't have valid raw in AUTO mode

    #undef  REMOTE_SYNC_STATUS_LED
//  #define REMOTE_SYNC_STATUS_LED              0xC022C30C  // TODO specifies an LED that turns on while camera waits for USB remote to sync
//----------------------------------------------------------
