#ifndef GUI_OSD_H
#define GUI_OSD_H

// CHDK OSD interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------
#define ZOOM_SHOW_X                     0
#define ZOOM_SHOW_FL                    1
#define ZOOM_SHOW_EFL                   2

#define DOF_DONT_SHOW                   0
#define DOF_SHOW_IN_DOF                 1
#define DOF_SHOW_IN_DOF_EX              2
#define DOF_SHOW_IN_MISC                3
#define DOF_SHOW_IN_MISC_EX             4

//-------------------------------------------------------------------
extern void gui_draw_osd_elements(int is_osd_edit, int is_zebra);
extern void gui_osd_draw_clock(int x, int y, color cl, int is_osd_edit);
extern void gui_draw_debug_vals_osd();
extern void gui_update_debug_page();

extern void gui_draw_osd();
extern void gui_kbd_shortcuts();

extern gui_handler defaultGuiHandler;

//------------------------------------------------------------------- 

#define DEBUG_DISPLAY_NONE 0
#define DEBUG_DISPLAY_PROPS 1
#define DEBUG_DISPLAY_PARAMS 2
#define DEBUG_DISPLAY_TASKS 3

//-------------------------------------------------------------------

extern void MakeAFScan(void);

extern void EnterToCompensationEVF(void);
extern void ExitFromCompensationEVF(void);

extern int canon_menu_active;
extern char canon_shoot_menu_active;

//-------------------------------------------------------------------

#endif
