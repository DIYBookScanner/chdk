#ifndef AUTOISO_H
#define AUTOISO_H

// CHDK AUTO ISO code

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------

extern void shooting_set_autoiso(int iso_mode);
extern int live_histogram_read_y(unsigned short *buf);

//-------------------------------------------------------------------
#endif
