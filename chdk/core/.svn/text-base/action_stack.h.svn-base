#ifndef _ACTION_STACK_H
#define _ACTION_STACK_H

// CHDK Script action handler

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

// Action stack processing function
typedef int (*action_func)(void);

// Action stack ID
typedef unsigned long AS_ID;

int action_stack_AS_SHOOT(void);

AS_ID action_stack_create(action_func proc_func);

long action_top(int n);
void action_push(long p);
void action_push_delay(long msec);
void action_push_press(long key);
void action_push_release(long key);
void action_push_click(long key);
void action_push_shoot(int retry);
long action_pop_func(int nParam);
void action_push_func(action_func f);

void action_wait_for_click(int timeout);

void action_stack_process_all();
int  action_stack_is_finished(AS_ID comp_id);
void action_stack_kill(AS_ID comp_id);

#endif // _ACTION_STACK_H

