#ifndef USB_REMOTE_H
#define USB_REMOTE_H

// CHDK USB Remote Switch interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

// Functions.
extern int handle_usb_remote();
extern void wait_until_remote_button_is_released(void);

/*===================================================================================================
    Static Variables & #defines
  ===================================================================================================*/

extern int usb_remote_active;
extern int usb_sync_wait;
extern int bracketing_timeout;

#undef USB_REMOTE_DEBUGGING
//#define USB_REMOTE_DEBUGGING 1
#undef USB_REMOTE_RECORD 
//#define USB_REMOTE_RECORD 1

#define NUM_USB_INPUT_DRV 5
#define NUM_USB_MODULES 10

enum {
		INVALID_STATE ,
		INVALID_DEVICE ,
		INVALID_MODULE
	} ;


enum  SWITCH_TYPE {							// USB remote switch types
	SW_NONE = 0 ,
	SW_ONE_PRESS ,
	SW_TWO_PRESS ,
	SW_RICOH_CA1 
}  ;

enum CONTROL_MODULE {						// USB remote control modes
	RMT_NONE  = 0 ,
	RMT_HALF_PRESS_FULL_PRESS ,
	RMT_AUTO_1 ,
	RMT_AUTO_2 ,
	RMT_CONTINUOUS ,
	RMT_ZOOM ,
	RMT_BRACKETING
} ;

enum VIRTUAL_REMOTE_STATE {					// state of Virtual USB remote switch
	REMOTE_RESET = 0 ,
    REMOTE_RELEASE,
    REMOTE_HALF_PRESS,
    REMOTE_FULL_PRESS
} ;

enum DRIVER_STATE {								// state variable for drivers
	SW_RESET = 0 ,
    SW_IDLE,
    SW_POWER_CONNECT,
    SW_POWER_ON,
	SW_POWER_DISCONNECT,
	SW_FULL_PRESS_ACTIVE ,
	SW_SHORT_PRESS ,
	SW_CANCEL_PULSE ,
	SW_HALF_PRESS,
	SW_FULL_PRESS ,
	SW_FULL_PRESS_RESET,
	SW_PRESS ,
	SW_RELEASE ,
	SW_CANCEL,

	SW_CA1_1XX,
	SW_CA1_10X,
	SW_CA1_100,
	SW_CA1_101,
	SW_CA1_11

} ;

enum  LOGIC_MODULE_STATE {								// remote control mode states
	LM_RESET = 0 ,
    LM_RELEASE,
	LM_HALF_PRESS,
	LM_FULL_PRESS,
	LM_START_RECORD ,
	LM_RECORDING ,
	LM_STOP_RECORDING ,
	LM_KEY_PRESS
} ;

enum USB_STATE {								// values returned from get_usb_power(USB_STATE)
	USB_POWER_OFF,
	USB_POWER_ON
} ;

enum CAMERA_MODE {								// camera mode  = 0 in picture record mode, 1 in playback mode, 2 when modedial is set to videomode AND camera is in record mode
	CAMERA_MODE_SHOOTING ,
	CAMERA_MODE_PLAYBACK ,
	CAMERA_MODE_VIDEO
} ;

enum  ZOOM_MODE {
	ZOOM_STEP_OUT  = 1,
	ZOOM_STEP_IN ,
	ZOOM_SHOOT ,
	ZOOM_FULL_OUT ,
	ZOOM_FULL_IN
} ;

enum  PLAYBACK_MODE {    				// playback scroll through pix - looks at pulse counts so 0 = NOP
	PLAYBACK_NEXT =1  ,	
	PLAYBACK_REVERSE ,
	PLAYBACK_LEFT ,
	PLAYBACK_RIGHT
} ;


enum GET_USB_PWR {						// input parameter for get_usb_power() 
	SINGLE_PULSE,
	USB_STATE ,
	BUFFERED_PULSE ,
	PULSE_COUNT,
	LM_PULSE_COUNT,
	CLEAR_USB_REGISTERS
} ;

// USB remote processing status

#define RMT_DISABLED 0
#define RMT_ENABLED 1

// timing parameters

#define REMOTE_CLICK_TIME 100
#define DEBOUNCE_TIME 10
#define FULL_PRESS_PULSE_TIME 1000
#define MAX_FULL_PRESS_DELAY 1000
#define CA1_MIN_HALFPRESS_TIME 10
#define CA1_MAX_HALFPRESS_TIME 50
#define CA1_CANCEL_PULSE_TIME 100
#define CA1_MIN_FULLPRESS_TIME 100
#define CA1_MAX_FULLPRESS_TIME 300
#define CA1_FULL_WAIT_PRESS_TIMEOUT 30000

#define DELAY_TIMEOUT 10000

#define BRACKETING_TIMEOUT 10000

#endif
