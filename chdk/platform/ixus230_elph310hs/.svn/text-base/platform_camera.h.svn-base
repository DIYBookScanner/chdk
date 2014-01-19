// Camera - sx230hs - platform_camera.h

// This file contains the various settings values specific to the SX230HS camera.
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
#define CAM_PROPSET				        4
#define CAM_DRYOS_2_3_R39               1 // Defined for cameras with DryOS version R39 or higher
#define CAM_DRYOS_2_3_R47               1 // Defined for cameras with DryOS version R47 or higher

#define CAM_AV_OVERRIDE_IRIS_FIX		1
#undef  CAM_KEY_PRESS_DELAY
#define CAM_KEY_PRESS_DELAY             60      // delay after a press
#define CAM_ADJUSTABLE_ALT_BUTTON		1
#define CAM_ALT_BUTTON_NAMES            { "Playback", "Display", "Video" }
#define CAM_ALT_BUTTON_OPTIONS          { KEY_PLAYBACK, KEY_DISPLAY, KEY_VIDEO }

#define	CAM_DATE_FOLDER_NAMING		    1
#define CAM_HAS_ND_FILTER		        1 // verify
#define CAM_HAS_VIDEO_BUTTON			1
#define CAM_VIDEO_QUALITY_ONLY                  1
#define CAM_SHOW_OSD_IN_SHOOT_MENU              1
#define CAM_QUALITY_OVERRIDE                    1 // enable 'Super Fine' JPEG compression mode
#define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1
#define CAM_DRIVE_MODE_FROM_TIMER_MODE	        1

#define PARAM_DISPLAY_MODE1                     59  // param number for LCD display mode when camera in playback
#define PARAM_DISPLAY_MODE2                     60  // param number for LCD display mode when camera in record view hold mode

#define CAM_DISABLE_RAW_IN_LOW_LIGHT_MODE	1 // verify

#undef CAM_CAN_SD_OVER_NOT_IN_MF
#undef CAM_VIDEO_CONTROL
#undef CAM_HAS_JOGDIAL
#undef CAM_USE_ZOOM_FOR_MF
#undef CAM_HAS_ERASE_BUTTON
#undef CAM_HAS_IRIS_DIAPHRAGM
#undef CAM_HAS_MANUAL_FOCUS
#undef CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO

#undef CAM_USES_ASPECT_CORRECTION
#define CAM_USES_ASPECT_CORRECTION      1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized

#undef CAM_BITMAP_WIDTH
#undef CAM_BITMAP_HEIGHT
#define CAM_BITMAP_WIDTH                960 // Actual width of bitmap screen in bytes
#define CAM_BITMAP_HEIGHT               270 // Actual height of bitmap screen in rows

#undef  CAM_UNCACHED_BIT
#define CAM_UNCACHED_BIT                0x40000000 // Found @0xff02be50

#undef  CAM_SENSOR_BITS_PER_PIXEL
#define CAM_SENSOR_BITS_PER_PIXEL       12 // Look into

#undef CAM_BITMAP_PALETTE
#define CAM_BITMAP_PALETTE              10

#undef EDGE_HMARGIN
#define EDGE_HMARGIN                    10 // Look into

#define CAM_EXT_TV_RANGE                1

#define CAM_CHDK_HAS_EXT_VIDEO_TIME     1

// RAW & DNG related values
#define CAM_RAW_ROWPIX                  4168 // Found @0xff14d678
#define CAM_RAW_ROWS                    3060 // Found @0xff14d684
#define CAM_JPEG_WIDTH                  4000
#define CAM_JPEG_HEIGHT                 3000
#define CAM_ACTIVE_AREA_X1	            96 // Update
#define CAM_ACTIVE_AREA_Y1	            24 // Update
#define CAM_ACTIVE_AREA_X2	            4168 // Update 
#define CAM_ACTIVE_AREA_Y2	            3060 // Update
#define cam_CFAPattern                  0x02010100 // Camera Bayer sensor data layout: Red  Green  Green  Blue
#define CAM_COLORMATRIX1	\
	544808, 1000000, -174047, 1000000, -80399, 1000000, \
	-75055, 1000000, 440444, 1000000, 11367, 1000000, \
	-5801, 1000000, 71589, 1000000, 118914, 1000000 // Look into updating

#define cam_CalibrationIlluminant1 1 // Look into updating

#define PARAM_CAMERA_NAME           4 // parameter number for GetParameterData
//#define DNG_VERT_RLE_BADPIXELS	    1 // verify
#define CAM_DNG_LENS_INFO       { 50,10, 400,10, 30,10, 59,10 } // See comments in camera.h // 5.0 - 40.0

#define REMOTE_SYNC_STATUS_LED 	0xC0220130		// specifies an LED that turns on while camera waits for USB remote to sync
#define CAM_HAS_CMOS                   1

