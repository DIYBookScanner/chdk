#ifndef SCRIPT_H
#define SCRIPT_H

// CHDK Script interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------
// Current stage of script processing

enum {	SCRIPT_STATE_INACTIVE=0,  // 0 - script is inactive now
		SCRIPT_STATE_RAN,	      // 1 - script works now
		SCRIPT_STATE_INTERRUPTED, // 2 - shutter button was pressed, cancel script
};

//-------------------------------------------------------------------
#define SCRIPT_NUM_PARAMS           26

//-------------------------------------------------------------------

extern char script_title[36];

//-------------------------------------------------------------------

extern void script_load(const char *fn);
extern void save_params_values(int enforce);

extern void script_console_add_line(long str_id);
extern void script_print_screen_statement(int val);
//-------------------------------------------------------------------

extern void script_get_alt_text(char *buf);
extern void script_set_terminate_key(int key, const char *keyname);

extern int script_is_running();
extern long script_stack_start();
extern long script_start_gui( int autostart );
// for kbd_task kbd_process only, check if terminate has been requirested by another task
extern void script_check_terminate(void);
// request and wait for script terminate from other task
extern void script_wait_terminate(void);
extern void script_end();
//-------------------------------------------------------------------

#endif
