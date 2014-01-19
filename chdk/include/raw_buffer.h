#ifndef RAW_BUFFER_H
#define RAW_BUFFER_H

// CHDK Raw buffer interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

extern char *hook_raw_image_addr();
extern char *hook_alt_raw_image_addr();

#endif
