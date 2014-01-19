#ifndef GUI_MENU_H
#define GUI_MENU_H

//-------------------------------------------------------------------
#define MENUITEM_MASK           0x000f
#define MENUITEM_BOOL           1
#define MENUITEM_INT            2
#define MENUITEM_SUBMENU        3
#define MENUITEM_PROC           4
#define MENUITEM_UP             5
#define MENUITEM_TEXT           6
#define MENUITEM_SEPARATOR      7
#define MENUITEM_ENUM           8
#define MENUITEM_COLOR_BG       9
#define MENUITEM_COLOR_FG       10
#define MENUITEM_ENUM2          11
#define MENUITEM_SUBMENU_PROC   12
#define MENUITEM_STATE_VAL_PAIR 13  // value is a pointer to a 2 element CMenuItem array
                                    // used for config values that have an on/off state as well as an adjustable value (e.g. ISO override, etc)
                                    // the first element is the value control, the second is the on/off state control

// Flags, which describe limits of F_INT value
#define MENUITEM_F_MASK         0x00f0
#define MENUITEM_F_UNSIGNED     0x0010
#define MENUITEM_F_MIN          0x0020
#define MENUITEM_F_MAX          0x0040
#define MENUITEM_F_MINMAX       0x0060

// Value, which specify specific kind of argument
#define MENUITEM_ARG_MASK       0x0300
// menuitem.arg contain ptr to callback function
#define MENUITEM_ARG_CALLBACK   0x0100

// Module added to User Menu
#define MENUITEM_USER_MODULE    0x0400

#define MENUITEM_HHMMSS         0x1000  // Display / edit value as H:MM:SS
#define MENUITEM_DECIMAL        0x2000  // Display / edit value as 0.xxxxx
#define MENUITEM_SD_INT         0x4000  // Subject Distance Value is potentially a 7 digit int (0-9999999) instead of a 5 digit int (0-99999)
#define MENUITEM_SCRIPT_PARAM   0x8000  // Script Parameter Menu Item

#define MENU_MINMAX(min, max)   (((max)<<16)|(min&0xFFFF))
#define MENU_MIN_UNSIGNED(arg)  ((unsigned short)(arg & 0xFFFF))
#define MENU_MAX_UNSIGNED(arg)  ((unsigned short)((arg>>16) & 0xFFFF))
#define MENU_MIN_SIGNED(arg)    ((short)(arg & 0xFFFF))
#define MENU_MAX_SIGNED(arg)    ((short)((arg>>16) & 0xFFFF))

//-------------------------------------------------------------------
typedef struct {
    char                symbol;     // menuitem icon symbol
    char                opt_len;    // ENUM2 num of elements 
    short               type;       // MENUITEM_MASKS
    int                 text;       // Text
    int                 *value;     // pointer to binded variable
                                    //   exceptions: _PROC = pointer to processing func
                                    //               _ENUM = pointer to processing func
    int                 arg;        // additional argument
                                    //     by default type is controled by _ARG_MASK and by _F_MINMAX
                                    //     for ENUM2 - pointer to string list
} CMenuItem;

typedef struct {
    char                symbol;
    int                 title;
    const CMenuItem     *menu;
} CMenu;

// Menu item constructor macros
#define MENU_ITEM(sym, txt, typ, val, arg)  { (char)sym, 0, (short)typ, (int)txt, (int*)val, (int)arg }
#define MENU_ENUM2(sym, txt, val, arg)      { (char)sym, sizeof(arg)/sizeof(arg[0]), MENUITEM_ENUM2, (int)txt, (int*)val, (int)arg }
#define MENU_ENUM2a(sym, txt, val, arg, num){ (char)sym, (char)num, MENUITEM_ENUM2, (int)txt, (int*)val, (int)arg }

//-------------------------------------------------------------------
extern void gui_menu_init(CMenu *menu_ptr);
extern void gui_menu_cancel_redraw();
extern int gui_menu_kbd_process();
extern void gui_menu_draw(int enforce_redraw);
extern void gui_menu_force_redraw();
extern int menu_get_increment_factor();
extern void menu_set_increment_factor(int n);
extern char *menu_increment_factor_string();
extern int menu_calc_max_increment_factor(int max_value);
//-------------------------------------------------------------------

extern gui_handler menuGuiHandler;

//-------------------------------------------------------------------
extern  CMenu   root_menu;									// defined in gui.c

enum { FLAG_FIND_RECURSIVE = 0x01 };
extern CMenuItem* find_mnu(CMenu *curr_menu, int itemid );  // defined in gui_user_menu.c


//-------------------------------------------------------------------
#endif
