/*===================================================================================================================================================

	USB Remote : Shooting Control Modules

		- shooting control modules monitor the state of the "virtual switch" variable and take
		  appropriate action according to the logic defined for that mode
		- all interface to the physical camera is performed by these modules
		- the active control module is selected from a menu entry in the USB Remote menu
		- to add a control module, create a new function here, add string to gui_USB_control_modes[]
		  in gui.c and add ptr below to stucture (*usb_control_module[10])(int)
 ===================================================================================================================================================*/

#include "camera_info.h"
#include "stdlib.h"
#include "clock.h"
#include "shooting.h"
#include "keyboard.h"
#include "conf.h"
#include "action_stack.h"
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
	Control Module :  Playback
		- does right & left key presses in playback mode to allow scrolling through images in LCD
		- most useful with stereo photography to allow sync'd review of multiple cameras
  ---------------------------------------------------------------------------------------------------*/

 void usb_playback_module()
 {
	static int time_stamp = 0 ;
	static int direction = 0 ;		// 0 = left button,  1 = right button
	int i, current_time ;

	current_time = get_tick_count();

	switch( logic_module_state )
	{
		case LM_RESET :
			logic_module_state = LM_RELEASE ;
			break ;

		case LM_RELEASE :
			i =  get_usb_power(LM_PULSE_COUNT) ;
			switch( i )
			{
				case PLAYBACK_REVERSE :
					direction = direction ? 0 : 1 ;		 // fall through to next case
				case PLAYBACK_NEXT :
					if ( direction ) kbd_key_press(KEY_LEFT);
					else  kbd_key_press(KEY_RIGHT);
					logic_module_state = LM_KEY_PRESS ;
					time_stamp = current_time ;
					break ;
			
				case PLAYBACK_LEFT :
					direction = 0 ;
					break ;
					
				case PLAYBACK_RIGHT :
					direction = 1 ;
					break ;				

				default :
					break ;
			}
			break ;

		case LM_KEY_PRESS :	
			if( (current_time - time_stamp) > REMOTE_CLICK_TIME )
			{
				if ( direction ) kbd_key_release(KEY_LEFT);
				else  kbd_key_release(KEY_RIGHT);			
				logic_module_state = LM_RELEASE ;
			}
			break ;

		default :
			break ;
	}
}

/*---------------------------------------------------------------------------------------------------
	Control Module :  Shoot Normal
		- module to activate camera's half press key on virtual half press and full press key on virtual full press
		- implements sync as follows :
			1) one press switch - starts a full shoot on half press so that sync happens on "full press"
			2) two press switch - does half press action, starts shoot on full press, sync will happen when full press released
			3) CA-1 - does half press action, starts shoot on full press - sync happens at end of CA-1 150 mSec pulse
  ---------------------------------------------------------------------------------------------------*/

void usb_shoot_module_normal()
{
	static AS_ID usb_remote_stack_name = 0;

	if ( conf.synch_enable == 0  )			// handle key presses differently if in sync mode
	{
		switch( logic_module_state )
		{
			case LM_RESET :
				kbd_key_release(KEY_SHOOT_FULL);
				kbd_key_release(KEY_SHOOT_HALF);
				logic_module_state = LM_RELEASE ;
				break ;

			case LM_RELEASE :
				switch ( virtual_remote_state )
				{
					case REMOTE_RELEASE :
						break ;

					case REMOTE_HALF_PRESS :
						kbd_key_press(KEY_SHOOT_HALF);
						logic_module_state = LM_HALF_PRESS ;
						break ;

					case REMOTE_FULL_PRESS:
						kbd_key_press(KEY_SHOOT_HALF);
						kbd_key_press(KEY_SHOOT_FULL);
						logic_module_state = LM_FULL_PRESS ;
						break ;

					default :
						debug_error(INVALID_STATE) ;
						break ;
				}
				break ;

			case LM_HALF_PRESS :
				switch ( virtual_remote_state )
				{
					case REMOTE_RELEASE :
						kbd_key_release(KEY_SHOOT_HALF);
						logic_module_state = LM_RELEASE ;
						break ;

					case REMOTE_HALF_PRESS :
						break ;

					case REMOTE_FULL_PRESS:
						kbd_key_press(KEY_SHOOT_FULL);
						logic_module_state = LM_FULL_PRESS ;
						break ;

					default :
						debug_error(INVALID_STATE) ;
						break ;
				}
				break ;


			case LM_FULL_PRESS :
				switch ( virtual_remote_state )
				{
					case REMOTE_RELEASE :
						kbd_key_release(KEY_SHOOT_FULL);
						kbd_key_release(KEY_SHOOT_HALF);
						logic_module_state = LM_RELEASE ;
						break ;

					case REMOTE_HALF_PRESS:
						kbd_key_release(KEY_SHOOT_FULL);
						logic_module_state = LM_HALF_PRESS ;
						break ;

					case REMOTE_FULL_PRESS:
						break ;

					default :
						debug_error(INVALID_STATE) ;
						break ;
				}
				break ;

			default :
				debug_error(INVALID_STATE) ;
				break ;

		}
	}
	else					// syncable remote mode
	{
		switch( logic_module_state )
		{
			case LM_RESET :
				logic_module_state = LM_RELEASE ;
				break ;

			case LM_RELEASE :
				switch ( virtual_remote_state )
				{
					case REMOTE_HALF_PRESS :
						switch ( switch_type)
						{
							case SW_ONE_PRESS :
								usb_remote_stack_name = action_stack_create(&action_stack_AS_SHOOT);
								usb_sync_wait = 1;
								logic_module_state = LM_HALF_PRESS ;
								break ;

							case SW_TWO_PRESS :
							case SW_RICOH_CA1 :
								kbd_key_press(KEY_SHOOT_HALF);
								logic_module_state = LM_HALF_PRESS ;
								break ;

							default :
								break ;
						}
						break ;

					case REMOTE_RELEASE :
					case REMOTE_FULL_PRESS:
						break ;
					default :
						debug_error(INVALID_STATE) ;
						break ;
				}
				break ;

			case LM_HALF_PRESS :
				switch ( virtual_remote_state )
				{
					case REMOTE_FULL_PRESS:
						switch ( switch_type)
						{
							case SW_ONE_PRESS :
								logic_module_state = LM_FULL_PRESS ;
								break ;

							case SW_TWO_PRESS :
							case SW_RICOH_CA1 :
								usb_sync_wait = 1;
								kbd_key_press(KEY_SHOOT_FULL);
								logic_module_state = LM_FULL_PRESS ;
								break ;

							default :
								break ;
						}
						break ;
					case REMOTE_RELEASE :
						switch ( switch_type)
						{
							case SW_ONE_PRESS :
								if( action_stack_is_finished(usb_remote_stack_name) )
								{
									logic_module_state = LM_RELEASE ;
								}
								break ;

							case SW_TWO_PRESS :
							case SW_RICOH_CA1 :
								kbd_key_release(KEY_SHOOT_HALF);
								logic_module_state = LM_RELEASE ;
								break ;

							default :
								break ;
						}
						break ;

					case REMOTE_HALF_PRESS :
						break ;
					default :
						debug_error(INVALID_STATE) ;
						break ;
				}
				break ;

			case LM_FULL_PRESS :
				switch ( virtual_remote_state )
				{
					case REMOTE_RELEASE :
						switch ( switch_type)
						{
							case SW_ONE_PRESS :
								if( action_stack_is_finished(usb_remote_stack_name) )
								{
									logic_module_state = LM_RELEASE ;
								}
								break ;

							case SW_TWO_PRESS :
							case SW_RICOH_CA1 :
								usb_sync_wait = 0;
								logic_module_state = LM_RELEASE ;
								kbd_key_release(KEY_SHOOT_FULL);
								kbd_key_release(KEY_SHOOT_HALF);
								break ;

							default :
								break ;
						}
						break ;

					case REMOTE_HALF_PRESS :
					case REMOTE_FULL_PRESS:
						break ;

					default :
						debug_error(INVALID_STATE) ;
						break ;
				}
				break ;

			default :
				debug_error(INVALID_STATE) ;
				break ;
		}
	}

};

/*---------------------------------------------------------------------------------------------------
	Control Module :  Shoot Quick
		- module to launch "shoot()" on leading edge of either virtual HALF_PRESS or FULL_PRESS
		- does not support sync
  ---------------------------------------------------------------------------------------------------*/

 void usb_shoot_module_quick()
{
	static AS_ID usb_remote_stack_name = 0;

	switch( logic_module_state )
	{
		case LM_RESET :
			logic_module_state = LM_RELEASE ;
			break ;

		case LM_RELEASE :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:
					usb_remote_stack_name = action_stack_create(&action_stack_AS_SHOOT);
					logic_module_state = LM_FULL_PRESS ;
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break ;

		case LM_FULL_PRESS :
			if (( virtual_remote_state == REMOTE_RELEASE ) && action_stack_is_finished(usb_remote_stack_name) )
			{
				logic_module_state = LM_RELEASE ;
			}
			break ;

		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

}

/*---------------------------------------------------------------------------------------------------
	Control Module :  Shoot Burst
		- module to launch "shoot()" continuously while virtual HALF_PRESSED is true
		- refocus & exposure set on each shot - another mode could be added to lock those on first shot
		- virtual FULL_PRESS is ignored
  ---------------------------------------------------------------------------------------------------*/

void usb_shoot_module_burst()
{
	static AS_ID usb_remote_stack_name = 0;

	switch( logic_module_state )
	{
		case LM_RESET :
			logic_module_state = LM_RELEASE ;
			break ;

		case LM_RELEASE :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:
					usb_remote_stack_name = action_stack_create(&action_stack_AS_SHOOT);
					logic_module_state = LM_HALF_PRESS ;
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break ;

		case LM_HALF_PRESS :
			if( action_stack_is_finished(usb_remote_stack_name) )
			{
				logic_module_state = LM_RELEASE ;
			}
			break ;

		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

}

/*---------------------------------------------------------------------------------------------------
	Control Module :  Shoot Zoom
		- module to allow zoom action to be synced between two camera
		- works with Pulse Count input device
			- 1 pulse  = zoom in
			- 2 pulses = zoom out
			- 3 pulses = shoot
			- 4 pulses = zoom full in
			- 5 pulses = zoom full out
  ---------------------------------------------------------------------------------------------------*/

void usb_shoot_module_zoom()
{
	static AS_ID usb_remote_stack_name = 0;

	switch( logic_module_state )
	{
		case LM_RESET :
			logic_module_state = LM_RELEASE ;
			break ;

		case LM_RELEASE :
			switch( get_usb_power(LM_PULSE_COUNT) )
			{
				case ZOOM_STEP_OUT :
					shooting_set_zoom_rel(1) ;
					break ;

				case ZOOM_STEP_IN :
					shooting_set_zoom_rel(-1) ;
					break ;

				case ZOOM_SHOOT :
					logic_module_state = LM_FULL_PRESS ;
					usb_remote_stack_name = action_stack_create(&action_stack_AS_SHOOT);
					break ;

				case ZOOM_FULL_OUT :
					shooting_set_zoom(zoom_points) ;
					break ;

				case ZOOM_FULL_IN :
					shooting_set_zoom(0) ;
					break ;

				default :
					break ;
			}
			break ;

		case LM_FULL_PRESS :
			if( action_stack_is_finished(usb_remote_stack_name) )
			{
				logic_module_state = LM_RELEASE ;
			}
			break ;

		default :
			break ;
	}
};

/*---------------------------------------------------------------------------------------------------
	Control Module :  Shoot Bracketing
		- module to allow bracketing shots without using camera's timer or continuous modes
		- focus & exposure on each half press - shoots on full press
		- times out in 5 seconds after the last full press
  ---------------------------------------------------------------------------------------------------*/
extern void bracketing_step() ;
extern void bracketing_reset() ;

void usb_bracketing_done()
{
	bracketing_reset() ;
	bracketing_timeout = 0 ;
}


void usb_shoot_module_bracketing()
{
	int current_time ;

	current_time = get_tick_count() ;

	switch( logic_module_state )
	{
		case LM_RESET :
			logic_module_state = LM_RELEASE ;
			break ;

		case LM_RELEASE :
			if (( bracketing_timeout ) && ( current_time > bracketing_timeout ) ) usb_bracketing_done() ;

			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:					// Note : need a half-press to setup bracketing step
					kbd_key_press(KEY_SHOOT_HALF);
					logic_module_state = LM_HALF_PRESS ;
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break ;
             
		case LM_HALF_PRESS :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					kbd_key_release(KEY_SHOOT_HALF);
					logic_module_state = LM_RELEASE ;
				 	usb_bracketing_done() ;
					break ;

				case REMOTE_HALF_PRESS :
					break ;

				case REMOTE_FULL_PRESS:
					if ( shooting_in_progress() )
					{
						kbd_key_press(KEY_SHOOT_FULL);
						logic_module_state = LM_FULL_PRESS ;
						bracketing_timeout = current_time + BRACKETING_TIMEOUT ;
					}
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break ;


		case LM_FULL_PRESS :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					kbd_key_release(KEY_SHOOT_FULL_ONLY);
					kbd_key_release(KEY_SHOOT_HALF);
					logic_module_state = LM_RELEASE ;
					bracketing_step(SET_LATER) ;
					break ;

				case REMOTE_HALF_PRESS :
					kbd_key_release(KEY_SHOOT_FULL_ONLY);
					logic_module_state = LM_HALF_PRESS ;
					bracketing_step(SET_LATER) ;
					break ;

				case REMOTE_FULL_PRESS:
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break ;

		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

}

 /*---------------------------------------------------------------------------------------------------
	Control Module :  Video
		- starts video (with sync if selected) on press,  stops on next press
  ---------------------------------------------------------------------------------------------------*/

void usb_video_module_normal()
{
    int usb_video_button = (camera_info.cam_has_video_button) ? KEY_VIDEO : KEY_SHOOT_FULL;

	switch( logic_module_state )
	{
		case LM_RESET :
			logic_module_state = LM_RELEASE ;
			break ;

		case LM_RELEASE :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:
					kbd_key_press(usb_video_button);
					logic_module_state = LM_START_RECORD ;
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break ;

		case LM_START_RECORD:
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					logic_module_state = LM_RECORDING ;
					kbd_key_release(usb_video_button);
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break;

		case LM_RECORDING :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:
					kbd_key_press(usb_video_button);
					logic_module_state = LM_STOP_RECORDING ;
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break;

		case LM_STOP_RECORDING :
			switch ( virtual_remote_state )
			{
				case REMOTE_RELEASE :
					logic_module_state = LM_RELEASE ;
					kbd_key_release(usb_video_button);
					break ;

				case REMOTE_HALF_PRESS :
				case REMOTE_FULL_PRESS:
					break ;

				default :
					debug_error(INVALID_STATE) ;
					break ;
			}
			break;


		default :
			debug_error(INVALID_STATE) ;
			break ;

	}

};


 /*===================================================================================================

    Control Module Jump Tables

  ===================================================================================================*/

void usb_null_module(int i) {  } ;						// module that does nothing - useful for unused entries in jump table


// play mode jump table for control logic modules - must match gui_USB_control_modes[] in gui.c

void (*usb_module_play[NUM_USB_MODULES])() =
	{
				usb_null_module ,				// [   None]
				usb_playback_module ,			// [ Normal]
				usb_playback_module ,			// [  Quick]
				usb_playback_module ,			// [  Burst]
				usb_playback_module ,			// [Bracket]
				usb_playback_module ,			// [   Zoom]
				usb_playback_module ,			// [  Video]
				usb_playback_module ,			// <- insert new playback module here - update NUM_USB_MODULES if necessary
				usb_playback_module ,			//  --
				usb_null_module					//  -- 
	};


// shooting mode jump table for control logic modules - must match gui_USB_control_modes[] in gui.c

void (*usb_module_shoot[NUM_USB_MODULES])() =
	{
				usb_null_module ,				// [   None]
				usb_shoot_module_normal ,		// [ Normal]
				usb_shoot_module_quick ,		// [  Quick]
				usb_shoot_module_burst ,		// [  Burst]
				usb_shoot_module_bracketing ,	// [Bracket]
				usb_shoot_module_zoom ,			// [   Zoom]
				usb_video_module_normal ,		// [  Video] note : cameras with video button come through here when filming
				usb_null_module,				// <- insert new shoot module here - update NUM_USB_MODULES if necessary
				usb_null_module,				// --
				usb_null_module					// --
	};


// video mode jump table for control logic modules - must match gui_USB_control_modes[] in gui.c

void (*usb_module_video[NUM_USB_MODULES])() =
	{
				usb_null_module ,				// [   None]
				usb_video_module_normal ,		// [ Normal]
				usb_video_module_normal ,		// [  Quick]
				usb_null_module ,				// [  Burst]
				usb_null_module ,				// [Bracket]
				usb_null_module ,				// [   Zoom]
				usb_video_module_normal ,		// [  Video]
				usb_null_module ,				// <- insert new video module here - update NUM_USB_MODULES if necessary
				usb_null_module ,				// --
				usb_null_module 				// --
		};
