#ifndef GUI_USB_H
#define GUI_USB_H

// CHDK USB status OSD interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------

extern void gui_usb_draw_osd(int is_osd_edit);

//-------------------------------------------------------------------
#endif
