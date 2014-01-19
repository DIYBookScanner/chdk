#ifndef VIEWPORT_H
#define VIEWPORT_H

// CHDK Viewport & screen buffer interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

/******************************************************************/

extern long vid_is_bitmap_shown();
extern void *vid_get_bitmap_fb();

extern void *vid_get_viewport_fb();
extern void *vid_get_viewport_fb_d();
extern void *vid_get_viewport_live_fb();

extern void vid_bitmap_refresh();
extern void vid_turn_off_updates();
extern void vid_turn_on_updates();

// These define the viewport dimensions both physically and in terms of the CHDK co-ordinate system
// CHDK works in a 360x240 screen dimension / co-ordinate system
extern long vid_get_viewport_height();          // Viewport height in CHDK screen pixels 
extern int vid_get_viewport_width();            // Viewport width in CHDK screen pixels
extern int vid_get_viewport_xoffset();          // X offset of viewport edge relative to the viewport buffer (in CHDK screen pixels)
extern int vid_get_viewport_yoffset();          // Y offset of viewport top relative to the viewport buffer (in CHDK screen pixels)
extern int vid_get_viewport_display_xoffset();  // X offset of viewport edge relative to LCD screen (in CHDK screen pixels)
extern int vid_get_viewport_display_yoffset();  // Y offset of viewport top relative to LCD screen (in CHDK screen pixels)
extern int vid_get_viewport_byte_width();       // Physical width of viewport row in bytes
extern int vid_get_viewport_yscale();           // Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
extern int vid_get_viewport_image_offset();     // Byte offset from start of viewport memory to first displayed pixel
extern int vid_get_viewport_row_offset();       // Difference between physical width of viewport and displayed width (in bytes)


// PTP Live View functions
// These functions return actual size/offset in pixels of the viewport and bitmap buffers
extern int vid_get_viewport_display_xoffset_proper();   // X Offset (for variable image size)
extern int vid_get_viewport_display_yoffset_proper();   // Y Offset (for variable image size)
extern int vid_get_viewport_width_proper();             // Visible viewport width (for variable image size)
extern int vid_get_viewport_height_proper();            // Visible viewport height (for variable image size)
extern int vid_get_viewport_fullscreen_width();            // Width of screen in buffer pixels
extern int vid_get_viewport_fullscreen_height();           // Height of screen in buffer pixels
extern int vid_get_viewport_buffer_width_proper();      // Physical viewport buffer width in pixels
extern int vid_get_palette_type();                      // Palette type (0 - 3)
extern int vid_get_palette_size();                      // Palette size (in bytes)
extern int vid_get_aspect_ratio();                      // LCD aspect ratio (0 = 4:3 or 1 = 16:9)

extern void *vid_get_viewport_active_buffer();          // Return active live viewport memory address
extern void *vid_get_bitmap_active_buffer();            // Return current active bitmap memory address
extern void *vid_get_bitmap_active_palette();           // Return current palette memory address

/******************************************************************/

#endif
