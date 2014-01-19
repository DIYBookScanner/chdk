#ifndef TEMPERATURE_H
#define TEMPERATURE_H

// CHDK Firmware temp sensor interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

int get_ccd_temp();
int get_optical_temp();
int get_battery_temp();

#endif

