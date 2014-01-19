#ifndef SCRIPT_API_H
#define SCRIPT_API_H

#include "flt.h"

// Return values from 'script_run'
#define SCRIPT_RUN_ENDED        0
#define SCRIPT_RUN_RUNNING      1
#define SCRIPT_RUN_ERROR        -1

enum {
    SCRIPT_SHOOT_HOOK_PRESHOOT=0,
    SCRIPT_SHOOT_HOOK_SHOOT,
    SCRIPT_SHOOT_HOOK_RAW,
    SCRIPT_NUM_SHOOT_HOOKS,
};
// Module interface for script languages (Lua and uBasic)
typedef struct
{
    base_interface_t    base;

    int     (*script_start)( char const* script, int is_ptp ); // initialize and load script
    int     (*script_run)( void );          // run script timeslice
    void    (*script_reset)(void);
    void    (*set_variable)(int varnum, int value);
    void    (*set_as_ret)(int as_ret);      // save 'return' value from action stack code (e.g. motion detect, shoot)
    int     (*run_restore)( void );         // run the "restore" function at the end of a script
    void    (*shoot_hook)(int hook);        // run a hook in the shooting process, called from hooked task
} libscriptapi_sym;

extern libscriptapi_sym* libscriptapi;
extern void module_set_script_lang( const char* script_file );

#endif
