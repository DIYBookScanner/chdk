#ifndef GUI_H
#define GUI_H

// CHDK Gui interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

// Module ID's for specific modules that we need to be able to detect
// use GUI_MODE_MODULE for generic module modes (e.g.games)
enum Gui_Mode_ {
    GUI_MODE_NONE = 0,
    GUI_MODE_ALT,
    GUI_MODE_MENU,
    GUI_MODE_SCRIPT,
    GUI_MODE_MBOX,
    GUI_MODE_OSD,       // OSD editor
    GUI_MODE_PALETTE,
    GUI_MODE_FSELECT,
    GUI_MODE_MPOPUP,
    GUI_MODE_MODULE,    // generic module
};

typedef unsigned int gui_mode_t;

// States for flag to control entering / leaving ALT mode
// Set in KBD task code and activated in GUI task - reduces conflicts
// arising from tasks performin actions that should be done by the
// other task (e.g. screen erase)
enum ALT_Mode_State {
    ALT_MODE_NORMAL = 0,    // don't change ALT mode
    ALT_MODE_ENTER,         // enter ALT mode
    ALT_MODE_LEAVE,         // leave ALT mode
};

extern void gui_set_alt_mode_state(int);    // Called from KBD task to tell GUI task what state to set
extern void gui_activate_alt_mode();        // Called from GUI task to set ALT mode

#define GUI_MODE_MAGICNUM	0xd36c1559

// Specific behaviour of gui mode
#define GUI_MODE_FLAG_NODRAWRESTORE       1
#define GUI_MODE_FLAG_NORESTORE_ON_SWITCH 2

// Structure to store gui redraw and kbd process handlers for each mode
typedef struct
{
    // Gui_Mode enum value
    int mode;

	// Called to redraw screen. Argument is GUI_REDRAWFLAG_* set
    void (*redraw)(int);

	// Main button handler for mode
    // Return:
    //          0 = normal button handling
    //          1 = force buttons pressed to be blocked from Camera firmware
    int (*kbd_process)(void);

	// Menu button handler for mode
    void (*kbd_process_menu_btn)(void);

	int flags;
} gui_handler;

extern int script_run_on_alt_flag ;

extern gui_handler altGuiHandler;

extern int gui_kbd_process();
extern void gui_default_kbd_process_menu_btn();

extern void gui_redraw();
extern void gui_set_need_restore();
extern void gui_cancel_need_restore();

extern gui_mode_t gui_get_mode();
extern gui_handler* gui_set_mode(gui_handler *mode);
extern void gui_reset_alt_helper();

extern void gui_enum_value_change(int *value, int change, unsigned num_items);
extern const char* gui_subj_dist_override_value_enum(int change, int arg);
extern const char* gui_subj_dist_override_koef_enum(int change, int arg);
extern const char* gui_tv_override_value_enum(int change, int arg);
extern const char* gui_hhmss_enum(int change, int arg);
extern const char* gui_flash_power_modes_enum(int change, int arg);
extern const char* gui_flash_exp_comp_modes_enum(int change, int arg);

//------------------------------------------------------------------- 

#endif
