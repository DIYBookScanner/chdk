#ifndef SCRIPT_SHOOT_HOOKS_H
#define SCRIPT_SHOOT_HOOKS_H

// CHDK Script shoot hooks interface 

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

// initialize, when script is loaded or unloaded
void script_shoot_hooks_reset(void);
// enable hooking with specified timeout, 0 to disable
void script_shoot_hook_set(int hook,int timeout);
// called from hooked task, returns when hook is released or times out
void script_shoot_hook_run(int hook);
// returns true when hooked task in hook_run
int script_shoot_hook_ready(int hook);
// called from script to allow hook_run to return
void script_shoot_hook_continue(int hook);
// return number of times hook has been called for this script
int script_shoot_hook_count(int hook);

extern const char* shoot_hook_names[];
#endif

