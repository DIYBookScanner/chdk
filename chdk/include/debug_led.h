#ifndef DEBUG_LED_H
#define DEBUG_LED_H

// CHDK LED debug interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

extern void debug_led(int state);
#define started() debug_led(1)
#define finished() debug_led(0)

void camera_set_led(int led, int state, int bright);

#endif

