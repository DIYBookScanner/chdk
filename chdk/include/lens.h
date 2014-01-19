#ifndef LENS_H
#define LENS_H

// CHDK Lens focus & zoom interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

long lens_get_zoom_pos();
void lens_set_zoom_pos(long newpos);
long lens_get_zoom_point();
void lens_set_zoom_point(long newpt);
void lens_set_zoom_speed(long newspd); //for S-series
long lens_get_focus_pos();
long lens_get_focus_pos_from_lens();
void lens_set_focus_pos(long newpos);
long lens_get_target_distance();

void DoAFLock(void);
void UnlockAF(void);

#endif

