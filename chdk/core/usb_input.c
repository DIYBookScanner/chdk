/*===================================================================================================================================================

	USB Remote : Input Device Driver Modules

		-	device driver modules are responsible for monitoring the state of USB power and translating
			that into a "virtual switch" state
		-	the "virtual switch" state is monitored by the current control logic module for processing - there is no response expected back from the module
		-	the active device driver module is selected from a menu entry in the USB Remote menu
		-	to add a device driver, create a new function here, add name string to gui_USB_switch_types[]
			in gui.c and add ptr below to structure (*usb_driver[10])()

  ===================================================================================================================================================*/

#include "camera_info.h"
#include "stdlib.h"
#include "clock.h"
#include "conf.h"
#include "usb_remote.h"

/*===================================================================================================
    Variables
  ===================================================================================================*/

extern enum SWITCH_TYPE	 switch_type ;
extern enum CONTROL_MODULE  control_module  ;
extern enum VIRTUAL_REMOTE_STATE  virtual_remote_state;
extern enum DRIVER_STATE  driver_state;
extern enum LOGIC_MODULE_STATE logic_module_state ;
extern enum USB_STATE  usb_state ;
extern enum CAMERA_MODE  camera_mode ;


/*===================================================================================================
	Debug and error handling
  ===================================================================================================*/

#ifdef USB_REMOTE_DEBUGGING

extern int debug_errors[] ;
extern void debug_error(int ) ;

#else

extern void debug_error(int ) ;

#endif



/*---------------------------------------------------------------------------------------------------
	Device Driver :  "one press" switch
		-  goes to HALF_PRESS when USB power applied and then pulses FULL_PRESS when USB power removed
  ---------------------------------------------------------------------------------------------------*/
void usb_one_press_switch(int usb_state)
{
	static int time_stamp = 0 ;
	int current_time ;

	current_time = get_tick_count();

	switch( driver_state )
	{
		case SW_RESET :
			virtual_remote_state = REMOTE_RELEASE ;
			driver_state = SW_IDLE ;
			break ;

		case SW_IDLE :
			virtual_remote_state = REMOTE_RELEASE ;
			if ( usb_state == USB_POWER_ON )
			{
				driver_state = SW_POWER_CONNECT ;
				time_stamp = current_time ;
			}
			break ;

		case SW_POWER_CONNECT :
			if ( usb_state == USB_POWER_ON )
			{
				if ( current_time - time_stamp > DEBOUNCE_TIME )   // debounce
				{
					driver_state = SW_POWER_ON ;
					virtual_remote_state = REMOTE_HALF_PRESS ;
					time_stamp = current_time ;
				}
			}
			else
			{
				driver_state = SW_IDLE ;
			}
			break ;

		case SW_POWER_ON :
			if ( usb_state != USB_POWER_ON )
			{
				if ( current_time - time_stamp > DEBOUNCE_TIME ) // debounce
				{
					driver_state = SW_POWER_DISCONNECT ;
					virtual_remote_state = REMOTE_FULL_PRESS ;
					time_stamp = current_time ;
				}
			}
			break ;

		case SW_POWER_DISCONNECT :
			if ( current_time - time_stamp > FULL_PRESS_PULSE_TIME )
			{
				driver_state = SW_IDLE ;
				virtual_remote_state = REMOTE_RELEASE ;
			}
			break ;

		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

};


/*---------------------------------------------------------------------------------------------------
	Device Driver :  "two press" switch
	-  goes to HALF_PRESS when USB power applied and then FULL_PRESS if USB power removed and quickly reapplied
  ---------------------------------------------------------------------------------------------------*/

void usb_two_press_switch(int usb_state)
{
	static int time_stamp = 0 ;
	int current_time ;

	current_time = get_tick_count() ;

	switch( driver_state )
	{
		case SW_RESET :
			virtual_remote_state = REMOTE_RELEASE ;
			driver_state = SW_IDLE ;
			break ;

		case SW_IDLE :
			if ( usb_state == USB_POWER_ON )
			{
				driver_state = SW_POWER_CONNECT ;
				time_stamp = current_time ;
			}
			break ;

		case SW_POWER_CONNECT :
			if ( usb_state == USB_POWER_ON )
			{
				if ( current_time - time_stamp > DEBOUNCE_TIME )   // debounce
				{
					driver_state = SW_POWER_ON ;
					virtual_remote_state = REMOTE_HALF_PRESS ;
					time_stamp = current_time ;
				}
			}
			else
			{
				driver_state = SW_IDLE ;
			}
			break ;

		case SW_POWER_ON :
			if ( usb_state == USB_POWER_OFF )
			{
				if ( current_time - time_stamp > DEBOUNCE_TIME ) // debounce
				{
					driver_state = SW_POWER_DISCONNECT ;
					time_stamp = current_time ;
				}
			}
			break ;

		case SW_POWER_DISCONNECT :
			if ( usb_state == USB_POWER_ON )
			{
				if ( current_time - time_stamp > DEBOUNCE_TIME )   // debounce
				{
					driver_state = SW_FULL_PRESS_ACTIVE;
					virtual_remote_state = REMOTE_FULL_PRESS ;
					time_stamp = current_time ;
				}
			}
			else
			{
				if ( current_time - time_stamp > MAX_FULL_PRESS_DELAY )	// timeout if no second press
				{
					virtual_remote_state =  REMOTE_RELEASE ;
					driver_state = SW_IDLE ;
				}
			}
			break ;


		case SW_FULL_PRESS_ACTIVE :
			if ( usb_state == USB_POWER_OFF )
			{
				virtual_remote_state = REMOTE_RELEASE ;
				driver_state = SW_IDLE ;
			}
			break ;

		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

} ;
/*---------------------------------------------------------------------------------------------------
	Device Driver :   Ricoh CA-1 switch
		- measures USB pulse widths to detect RICOH CA-1 half press, full press and cancel sequences
		  and sets virtual switch state appropriately
  ---------------------------------------------------------------------------------------------------*/

#define CA1_MAX_SHORT_PULSE_TIME 30
#define CA1_MAX_GAP_TIME 50

/*

  |30|30|30| ms
 _/~~\_____________   half-press   100

 _/~~~~~~~~~~~~~~\_   full-press   111

 _/~~\__/~~\_______   release      101

*/

void usb_ricoh_ca1_switch(int usb_state)
{
	static int time_stamp = 0 ;
	int current_time ;

	current_time = get_tick_count() ;

	switch( driver_state )
	{
		case SW_RESET :
			virtual_remote_state = REMOTE_RELEASE ;
			driver_state = SW_IDLE ;
			break ;

		case SW_IDLE :											// wait for USB power to be applied
			if ( usb_state == USB_POWER_ON )
			{
				driver_state = SW_CA1_1XX ;
				time_stamp = current_time ;
			}
			break ;
			
		case SW_CA1_1XX :										// decide between CA-1  30 mSec / 150 mSec pulse
			if ( usb_state == USB_POWER_OFF )
			{
				driver_state = SW_CA1_10X ;
				time_stamp = current_time ;
			}	
			else if ( current_time - time_stamp > CA1_MAX_SHORT_PULSE_TIME )
			{
				driver_state = SW_CA1_11 ;						// we can set FULL_PRESS either here or wait for USB_POWER_OFF
				virtual_remote_state = REMOTE_FULL_PRESS ;		// note : setting FULL_PRESS here means that we can use the end of the current 150 mSec pulse for synch
			}			
			break ;				
		
		case SW_CA1_10X :			
			if ( usb_state == USB_POWER_ON) 					// is the CA-1 30 mSec pulse followed by another one ?
			{
				driver_state = SW_CA1_101 ;			
			}	
			else if ( current_time - time_stamp > CA1_MAX_GAP_TIME)	
			{
				driver_state = SW_CA1_100 ;
			}
			break ;

		case SW_CA1_101 :										// CA-1 release
			if ( usb_state == USB_POWER_OFF ) 					// wait for end of pulse
			{
				driver_state = SW_IDLE ;
				virtual_remote_state = REMOTE_RELEASE ;
			}
			break ;

		case SW_CA1_100 :										// CA-1 half-press
			driver_state = SW_IDLE ;
			virtual_remote_state = REMOTE_HALF_PRESS ;
			break ;

		case SW_CA1_11 : 										// CA-1 full press
		
			if ( usb_state == USB_POWER_OFF ) 
			{
				driver_state = SW_IDLE ;						// this is always followed by the release pulse
				virtual_remote_state = REMOTE_RELEASE ;			// so we can set the state already here
			}
			break ;

		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

} ;


 /*===================================================================================================

    Input Driver Jump Table

   ===================================================================================================*/


void usb_null_driver(int i) { return ; } ;

void (*usb_driver[NUM_USB_INPUT_DRV])(int) = 					 // jump table for input drivers - must match gui_USB_switch_types[] in gui.c
	{
			usb_null_driver ,
			usb_one_press_switch ,
			usb_two_press_switch ,
			usb_ricoh_ca1_switch ,
			usb_null_driver										// <- insert new devices here - update NUM_USB_INPUT_DRV if necessary
	};
