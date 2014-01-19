#ifndef BACKLIGHT_H
#define BACKLIGHT_H

// CHDK LCD backlight interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

void TurnOnBackLight(void);
void TurnOffBackLight(void);
void TurnOnDisplay(void);
void TurnOffDisplay(void);

#endif
