#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "keyboard.h"
#include "font.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_user_menu.h"
#include "gui_lang.h"

#include "gui_palette.h"

//-------------------------------------------------------------------
#define MENUSTACK_MAXDEPTH  4

//-------------------------------------------------------------------
typedef struct {
    CMenu       *menu;
    int         curpos;
    int         toppos;
} CMenuStacked;

//-------------------------------------------------------------------

static CMenu        *curr_menu;
static CMenuStacked gui_menu_stack[MENUSTACK_MAXDEPTH];
static unsigned int gui_menu_stack_ptr;
static int          gui_menu_curr_item;
static int          gui_menu_top_item;
static int          gui_menu_redraw;

static int          count;
static int          x, y;
static int          w, wplus, num_lines;
static int          len_bool, len_int, len_enum, len_space, len_br1, len_br2, cl_rect;
static int          int_incr = 1;
static unsigned char *item_color;

//-------------------------------------------------------------------
// Functions to access increment factor from other code
// Used for quick SD override in ALT mode without entering menu

int menu_get_increment_factor()
{
    return int_incr;
}

void menu_set_increment_factor(int n)
{
    int_incr = n;
}

// Generate display string for int_incr value
char *menu_increment_factor_string()
{
    static char buf[8];
    buf[0] = 0;
    if (int_incr >= 1000000)
        sprintf(buf, "±%dM",int_incr/1000000);
    else if (int_incr >= 1000)
        sprintf(buf, "±%dK",int_incr/1000);
    else
        sprintf(buf, "±%d",int_incr);
    return buf;
}

// Given a maximum value for a int menu item, calculate the largest int_incr value
int menu_calc_max_increment_factor(int max_value)
{
    int max = 1;
    while (max_value/10 != 0)
    {
        max *= 10;
        max_value /= 10;
    }
    return max;
}

//-------------------------------------------------------------------
// Adjust the int_incr value up or down - adjust limits based on current
// menu item type and settings

#define MAX(a,b)    ((a>=b)?a:b)

static int increment_factor()
{
    // Increase int_incr
    // Returns 1 if value changed.

    // Get info about the current menu item
    int item_flags = curr_menu->menu[gui_menu_curr_item].type;
    int item_type = item_flags & MENUITEM_MASK;
    int item_arg = curr_menu->menu[gui_menu_curr_item].arg;
    int item_val = *(curr_menu->menu[gui_menu_curr_item].value);
    // If state / value menu pair get info from value entry
    if (item_type == MENUITEM_STATE_VAL_PAIR)
    {
        CMenuItem *c = (CMenuItem*)(curr_menu->menu[gui_menu_curr_item].value);
        item_flags = c[0].type;
        item_type = item_flags & MENUITEM_MASK;
        item_arg = c[0].arg;
        item_val = *(c[0].value);
    }

    // Calculate max allowed value for int_incr
    // Default is 10000 for positive int values, 1000 for negative values or 1 otherwise
    int max = ((item_type == MENUITEM_INT) || (item_flags & MENUITEM_DECIMAL)) ? ((item_val<0)?1000:10000) : 1;

    // If an int value has a defined MIN / MAX range then adjust int_incr max to fit the range
    int vmax = 0;
    if ( item_flags & MENUITEM_F_MINMAX )
    {
        if ( item_flags & MENUITEM_F_UNSIGNED )
        {
            vmax = MAX(MENU_MIN_UNSIGNED(item_arg),MENU_MAX_UNSIGNED(item_arg));
        }
        else
        {
            vmax = MAX(abs(MENU_MIN_SIGNED(item_arg)),abs(MENU_MAX_SIGNED(item_arg)));
        }
    }

    // Default for SD type (item_arg holds max allowed value)
    if (item_flags & MENUITEM_SD_INT)
    {
        vmax = item_arg;
    }

    // If a max value has been set adjust accordingly
    if (vmax > 0)
    {
        max = menu_calc_max_increment_factor(vmax);
    }

    // Default for HH:MM:SS type
    if (item_flags & MENUITEM_HHMMSS)
    {
        max = 100;
    }

    // Adjust value
    if (int_incr < max)
    {
        int_incr *= 10;
        return 1;
    }
    if (int_incr > max)
    {
        int_incr = max;
        return 1;
    }

    return 0;
}

static int decrement_factor()
{
    // Decrease int_incr
    // Returns 1 if value changed.

    if (int_incr > 1)
    {
        int_incr /= 10;
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------
static void gui_menu_set_curr_menu(CMenu *menu_ptr, int top_item, int curr_item) {
    curr_menu = menu_ptr;
    gui_menu_top_item = top_item;
    gui_menu_curr_item = curr_item;
}

//-------------------------------------------------------------------
void gui_menu_init(CMenu *menu_ptr) {

    if (menu_ptr) {
        if (conf.menu_select_first_entry)
            gui_menu_set_curr_menu(menu_ptr, 0, 0);
        else 
            gui_menu_set_curr_menu(menu_ptr, 0, -1);
        gui_menu_stack_ptr = 0;
    }

    num_lines = camera_screen.height/rbf_font_height()-1;
    x = camera_screen.menu_border_width;
    w = camera_screen.width-x-x;
    len_bool = rbf_str_width("\x95");
    len_int = rbf_str_width("99999");
    len_enum = rbf_str_width("WUBfS3a");
    len_space = rbf_char_width(' ');
    len_br1 = rbf_char_width('[');
    len_br2 = rbf_char_width(']');
    cl_rect = rbf_font_height() - 4;
    int_incr = 1;

    gui_menu_redraw=2;
}

//-------------------------------------------------------------------
static int gui_menu_rows()
{
    int n;
    // Count the numer of rows in current menu
    for(n = 0; curr_menu->menu[n].text; n++);
    return n;
}

//-------------------------------------------------------------------
// Full screen erase and redraw of menu
static void gui_menu_erase_and_redraw()
{
    gui_menu_redraw = 2;
    gui_set_need_restore();
}
void gui_menu_cancel_redraw()
{
    gui_menu_redraw = 0;
    gui_cancel_need_restore();
}

//-------------------------------------------------------------------
// Function passed to gui_palette_init
// This is called when a new color is selected to update the menu / config value
static void gui_menu_color_selected(color clr)
{
    *item_color = FG_COLOR(clr);
    gui_menu_erase_and_redraw();
}

//-------------------------------------------------------------------
// Return to previous menu on stack
static void gui_menu_back() {
    if (gui_menu_stack_ptr > 0)
    {
        gui_menu_stack_ptr--;
        gui_menu_set_curr_menu(gui_menu_stack[gui_menu_stack_ptr].menu, gui_menu_stack[gui_menu_stack_ptr].toppos, gui_menu_stack[gui_menu_stack_ptr].curpos);
        gui_menu_erase_and_redraw();
    }
    else
    {
        // 'Back' selected; but no menu to go back to
        // Occurs when script menu opened using 'Func/Set' button
        // Return to normal <ALT> mode.
        gui_set_mode(&altGuiHandler);
    }
}

//-------------------------------------------------------------------
// Helper functions for gui_menu_kbd_process
//  common code blocks extracted to try and make it easier to understand

// After updating a value check for callback and on_change functions and call if necessary
static void do_callback(const CMenuItem *mi)
{
    if ((mi->type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && mi->arg)
    {
        ((void (*)())(mi->arg))();
    }
}

// Update an 'int' value, direction = 1 for increment, -1 for decrement
static void update_int_value(const CMenuItem *mi, int direction)
{
    // do update
    *(mi->value) += int_incr * direction;

    // Limit new value to defined bounds
    if ( mi->type & MENUITEM_F_UNSIGNED)
    {
        if (*(mi->value) < 0) 
            *(mi->value) = 0;

        if ( mi->type & MENUITEM_F_MIN)
        {
            if (*(mi->value) < MENU_MIN_UNSIGNED(mi->arg)) 
                *(mi->value) = MENU_MIN_UNSIGNED(mi->arg);
        }
    }
    else
    {
        if (*(mi->value) < -9999) 
            *(mi->value) = -9999;

        if ( mi->type & MENUITEM_F_MIN)
        {
            if (*(mi->value) < MENU_MIN_SIGNED(mi->arg)) 
                *(mi->value) = MENU_MIN_SIGNED(mi->arg);
        }
    }

    if (*(mi->value) > 99999) 
        *(mi->value) = 99999;

    if ( mi->type & MENUITEM_F_UNSIGNED)
    {
        if ( mi->type & MENUITEM_F_MAX)
        {
            if (*(mi->value) > MENU_MAX_UNSIGNED(mi->arg)) 
                *(mi->value) = MENU_MAX_UNSIGNED(mi->arg);
        }
    }
    else
    {
        if ( mi->type & MENUITEM_F_MAX)
        {
            if (*(mi->value) > MENU_MAX_SIGNED(mi->arg)) 
                *(mi->value) = MENU_MAX_SIGNED(mi->arg);
        }
    }

    // execute custom callback and on_change functions
    do_callback(mi);

    // force menu redraw
    gui_menu_redraw=1;
}

// Update a 'bool' value
static void update_bool_value(const CMenuItem *mi)
{
    // update value
    *(mi->value) = !(*(mi->value));

    // execute custom callback and on_change functions
    do_callback(mi);

    // force menu redraw
    gui_menu_redraw=1;
}

// Update an 'enum' value, direction = 1 for increment, -1 for decrement
static void update_enum_value(const CMenuItem *mi, int direction)
{
    // update value
    if (mi->value)
    {
        if (mi->type & (MENUITEM_DECIMAL | MENUITEM_SD_INT | MENUITEM_HHMMSS))
            direction *= int_incr;
        if ((mi->type & MENUITEM_MASK) == MENUITEM_ENUM)
        {
            ((const char* (*)(int change, int arg))(mi->value))(direction, mi->arg);
        }
        else
        {
            extern const char* gui_change_enum2(const CMenuItem *menu_item, int change);
            gui_change_enum2(mi, direction);
        }
    }

    // force menu redraw
    gui_menu_redraw=1;
}

// Open a sub-menu
void gui_activate_sub_menu(CMenu *sub_menu)
{
    // push current menu on stack
    gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
    gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
    gui_menu_stack[gui_menu_stack_ptr].toppos = gui_menu_top_item;

    // Select first item in menu, (or none)
    if (conf.menu_select_first_entry)
    {
        gui_menu_set_curr_menu(sub_menu, 0, 0);
        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_TEXT || (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_SEPARATOR)
        {
            //++gui_menu_top_item;
            ++gui_menu_curr_item;
        }
    }
    else 
        gui_menu_set_curr_menu(sub_menu, 0, -1);

    gui_menu_stack_ptr++;

    // FIXME check on stack overrun;
    if (gui_menu_stack_ptr > MENUSTACK_MAXDEPTH)
    {
        draw_txt_string(0, 0, "E1", MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
        gui_menu_stack_ptr = 0;
    }

    // Force full redraw
    gui_menu_erase_and_redraw();
}

// Open a sub-menu
static void select_sub_menu()
{
    gui_activate_sub_menu((CMenu*)(curr_menu->menu[gui_menu_curr_item].value));
}

// Call a function to process a menu item (may be a sub-menu loaded via a module)
static void select_proc()
{
    if (curr_menu->menu[gui_menu_curr_item].value)
    {
        ((void (*)(int arg))(curr_menu->menu[gui_menu_curr_item].value))(curr_menu->menu[gui_menu_curr_item].arg);
        //gui_menu_set_curr_menu(curr_menu, 0, 0); // restore this if it causes problems
        gui_menu_redraw=2;
    }
}

// Move up / down in menu, adjusting scroll position if needed
//   increment = -1 to move up, 1 to move down
static void gui_menu_updown(int increment)
{
    int c, j;

    // Determine number of rows to move (1 or 4)
    if (camera_info.state.is_shutter_half_press || kbd_is_key_pressed(KEY_ZOOM_IN) || kbd_is_key_pressed(KEY_ZOOM_OUT)) c=4; else c=1;

    for (j = 0; j < c; ++j)
    {
        do
        {
            // Move to next or previous row
            gui_menu_curr_item += increment;

            if (gui_menu_curr_item < 0)                                     // Off top, move to bottom
            {
                gui_menu_curr_item = gui_menu_rows() - 1;
                gui_menu_top_item = gui_menu_curr_item - num_lines + 1;
            }
            else if (gui_menu_curr_item >= gui_menu_rows())                 // Off bottom, move to top
            {
                gui_menu_curr_item = gui_menu_top_item = 0;
            }
            else if (increment == 1)                                        // Still in menu, if moving down adjust scroll if needed
            {
                if (gui_menu_curr_item - gui_menu_top_item >= num_lines - 1)
                {
                    gui_menu_top_item = gui_menu_curr_item - num_lines + 2;
                    if (gui_menu_top_item + num_lines > gui_menu_rows()) gui_menu_top_item = gui_menu_rows() - num_lines;
                }
            }
            else                                                            // Still in menu, and moving up, adjust scroll
            {
                if (gui_menu_curr_item == gui_menu_top_item) 
                    --gui_menu_top_item;
            }

            // Check in case scroll moved off top of menu
            if (gui_menu_top_item < 0) gui_menu_top_item = 0;
        } while ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_TEXT || 
                 (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_SEPARATOR);

        // Reset amount to increment integer values by
        int_incr = 1;
        if (((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) == MENUITEM_STATE_VAL_PAIR) &&
            (curr_menu->menu[gui_menu_curr_item].arg > 0))
            int_incr = curr_menu->menu[gui_menu_curr_item].arg;

        // Redraw menu if needed
        if (gui_menu_redraw == 0) gui_menu_redraw=1;
    }
}

//-------------------------------------------------------------------
// Process button presses when in GUI_MODE_MENU mode
int gui_menu_kbd_process() {

    switch (kbd_get_autoclicked_key() | get_jogdial_direction())
    {
        case KEY_ERASE:
        case KEY_SHOOT_HALF:
            if (!increment_factor())
                int_incr = 1;
            gui_menu_redraw=1;
            break;
        case JOGDIAL_LEFT:
        case KEY_UP:
            gui_menu_updown(-1);
            break;
        case JOGDIAL_RIGHT:
        case KEY_DOWN: 
            gui_menu_updown(1);
            break;
        case FRONTDIAL_LEFT:
        case KEY_LEFT:
            if (gui_menu_curr_item >= 0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) {
                    case MENUITEM_INT:
                        update_int_value(&curr_menu->menu[gui_menu_curr_item],-1);
                        break;
                    case MENUITEM_BOOL:
                        update_bool_value(&curr_menu->menu[gui_menu_curr_item]);
                        break;
                    case MENUITEM_ENUM:
                    case MENUITEM_ENUM2:
                        update_enum_value(&curr_menu->menu[gui_menu_curr_item],-1);
                        break;
                    case MENUITEM_UP:
                        gui_menu_back();
                        break;
                    case MENUITEM_STATE_VAL_PAIR:
                        {
                            CMenuItem *c = (CMenuItem*)(curr_menu->menu[gui_menu_curr_item].value);
                            if (*(c[1].value) == 0)
                                update_bool_value(&c[1]);
                            switch (c[0].type & MENUITEM_MASK)
                            {
                                case MENUITEM_INT:
                                    update_int_value(&c[0],-1);
                                    break;
                                case MENUITEM_ENUM:
                                case MENUITEM_ENUM2:
                                    update_enum_value(&c[0],-1);
                                    break;
                            }
                        }
                        break;
                }
            } else {
                gui_menu_back();
            }
            break;
        case FRONTDIAL_RIGHT:
        case KEY_RIGHT:
            if (gui_menu_curr_item >= 0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK){
                    case MENUITEM_INT:
                        update_int_value(&curr_menu->menu[gui_menu_curr_item],1);
                        break;
                    case MENUITEM_BOOL:
                        update_bool_value(&curr_menu->menu[gui_menu_curr_item]);
                        break;
                    case MENUITEM_ENUM:
                    case MENUITEM_ENUM2:
                        update_enum_value(&curr_menu->menu[gui_menu_curr_item],1);
                        break;
                    case MENUITEM_SUBMENU_PROC:
                        select_proc();
                        break;
                    case MENUITEM_SUBMENU:
                        select_sub_menu();
                        break;
                    case MENUITEM_STATE_VAL_PAIR:
                        {
                            CMenuItem *c = (CMenuItem*)(curr_menu->menu[gui_menu_curr_item].value);
                            if (*(c[1].value) == 0)
                                update_bool_value(&c[1]);
                            switch (c[0].type & MENUITEM_MASK)
                            {
                                case MENUITEM_INT:
                                    update_int_value(&c[0],1);
                                    break;
                                case MENUITEM_ENUM:
                                case MENUITEM_ENUM2:
                                    update_enum_value(&c[0],1);
                                    break;
                            }
                        }
                        break;
                }
            }
            break;
        case KEY_SET:
            if (gui_menu_curr_item >= 0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK){
                    case MENUITEM_INT:
                        if (camera_info.state.is_shutter_half_press)
                        {
                            *(curr_menu->menu[gui_menu_curr_item].value) = 0;
                            gui_menu_redraw=1;
                        }
                        break;
                    case MENUITEM_BOOL:
                        update_bool_value(&curr_menu->menu[gui_menu_curr_item]);
                        break;
                    case MENUITEM_SUBMENU_PROC:
                    case MENUITEM_PROC:
                        select_proc();
                        break;
                    case MENUITEM_SUBMENU:
                        select_sub_menu();
                        break;
                    case MENUITEM_UP:
                        gui_menu_back();
                        break;
                    case MENUITEM_COLOR_FG:
                    case MENUITEM_COLOR_BG:
                        item_color=((unsigned char*)(curr_menu->menu[gui_menu_curr_item].value)) + (((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?1:0);
                        libpalette->show_palette(PALETTE_MODE_SELECT, FG_COLOR(*item_color), gui_menu_color_selected);
                        gui_menu_redraw=2;
                        break;
                    case MENUITEM_ENUM:
                    case MENUITEM_ENUM2:
                        update_enum_value(&curr_menu->menu[gui_menu_curr_item],1);
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_STATE_VAL_PAIR:
                        {
                            CMenuItem *c = (CMenuItem*)(curr_menu->menu[gui_menu_curr_item].value);
                            if ((c[1].type & MENUITEM_MASK) == MENUITEM_ENUM)
                                update_enum_value(&c[1],1);
                            else
                                update_bool_value(&c[1]);
                        }
                        break;
                }
            }
            break;

        case KEY_ZOOM_IN:
            if (decrement_factor())
                gui_menu_redraw = 1;
            break;

        case KEY_ZOOM_OUT:
            if (increment_factor())
                gui_menu_redraw = 1;
            break;

        case KEY_DISPLAY:
            if (camera_info.cam_has_zoom_lever)
            {
                gui_menu_back();
            }
            else
            {
                // For cams without zoom lever, DISP adjusts increment factor
                if (!increment_factor())
                    int_incr = 1;
                gui_menu_redraw=1;
            }
            break;
    }

    return 0;
}

//-------------------------------------------------------------------
// Draw menu scroll bar if needed, and title bar
void gui_menu_draw_initial()
{ 
    count = gui_menu_rows();

    if (count > num_lines)
    {
        y = ((camera_screen.height-(num_lines-1)*rbf_font_height())>>1);
        wplus = 8; 
        // scrollbar background 
        draw_filled_rect((x+w), y, (x+w)+wplus, y+num_lines*rbf_font_height()-1, MAKE_COLOR(BG_COLOR(conf.menu_color), BG_COLOR(conf.menu_color))); 
    }
    else
    {
        wplus = 0;
        if (conf.menu_center)
        {
            y = (camera_screen.height-(count-1)*rbf_font_height())>>1; 
        }
        else
        {
            y = ((camera_screen.height-(num_lines-1)*rbf_font_height())>>1);  
        }
    }

    rbf_draw_menu_header(x, y-rbf_font_height(), w+wplus, (conf.menu_symbol_enable)?curr_menu->symbol:0, lang_str(curr_menu->title), conf.menu_title_color);
}

//-------------------------------------------------------------------

// Local variables used by menu draw functions
static int imenu, yy, xx, symbol_width;
static color cl, cl_symbol;

// Common code extracted from gui_menu_draw for displaying the symbol on the left
static void gui_menu_draw_symbol(int num_symbols)
{
    if (conf.menu_symbol_enable)
    {
        xx += rbf_draw_char(xx, yy, ' ', cl_symbol);
        xx += symbol_width = rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
        symbol_width = (symbol_width * num_symbols) + len_space;
    }
    else
    {
        symbol_width = 0;
    }

    xx += rbf_draw_char(xx, yy, ' ', cl);
}

static void gui_set_int_cursor(int offset)
{
    if (gui_menu_curr_item==imenu)
    {
        int n = int_incr;
        while (n > 1)
        {
            n /= 10;
            offset--;
        }
        rbf_enable_cursor(offset,offset);
    }
}

// Common code extracted from gui_menu_draw for displaying an int, enum or bool value on the right
static void gui_menu_draw_value(const char *str, int len_str)
{
    gui_menu_draw_symbol(1);
    xx += rbf_draw_string_len(xx, yy, w-len_space-len_space-len_br1-len_str-len_br2-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
    xx += rbf_draw_string(xx, yy, " [", cl);
    if (gui_menu_curr_item==imenu)
    {
        if (len_str == len_int)
            gui_set_int_cursor(4);
        else if (curr_menu->menu[imenu].type & MENUITEM_SD_INT)
            gui_set_int_cursor(6);
        else
            rbf_enable_cursor(0,6);
    }
    xx += rbf_draw_string_right_len(xx, yy, len_str, str, cl);
    rbf_disable_cursor();
    rbf_draw_string(xx, yy, "] ", cl);
}

// Common code extracted from gui_menu_draw for displaying a text menu string
static void gui_menu_draw_text(char *str, int num_symbols)
{
    gui_menu_draw_symbol(num_symbols);
    xx += rbf_draw_string_len(xx, yy, w-len_space-len_space-symbol_width, str, cl);
    if ((num_symbols == 2) && conf.menu_symbol_enable)
        xx += rbf_draw_symbol(xx, yy, 0x52, cl_symbol);
    rbf_draw_char(xx, yy, ' ', cl);
}

// Calculate how many display digits required to accomodate current int_incr value
static int factor_disp_len()
{
    int l = 0;
    if (gui_menu_curr_item==imenu)
    {
        l = -1;
        int n = int_incr;
        while (n > 0)
        {
            l++;
            n /= 10;
        }
    }
    return l;
}

static char tbuf[64];

// Convert an int value to a display string, adjust position of '-' for negative values to
// not clash with int_incr 'cursor' position
static void get_int_disp_string(int value)
{
    sprintf(tbuf, "%5d", value);
    if (value < 0)
    {
        int spos, cpos;
        for (spos=0; spos<5; spos++) if (tbuf[spos] == '-') break;
        cpos = 4 - factor_disp_len();
        if (cpos <= spos)
        {
            tbuf[spos] = ' ';
            tbuf[cpos-1] = '-';
        }
    }
}

// Common code extracted from gui_menu_draw for displaying an int or enum that can be enabled/disabled
static void gui_menu_draw_state_value(CMenuItem *c)
{
    const char *ch = "";

    int text = curr_menu->menu[imenu].text;
    if (c[0].text != 0)
        text = c[0].text;

    int wid = w-len_space-len_space-len_br1-len_enum-len_br2-len_space-symbol_width-len_br1-len_br2;
    if ((c[1].type & MENUITEM_MASK) == MENUITEM_ENUM)
        wid -= len_space*3;
    else
        wid -= len_bool;

    gui_menu_draw_symbol(1);
    xx += rbf_draw_string_len(xx, yy, wid, lang_str(text), cl);
    xx += rbf_draw_string(xx, yy, " [", cl);
    if ((c[1].type & MENUITEM_MASK) == MENUITEM_ENUM)
        xx += rbf_draw_string_len(xx, yy, len_space*3, ((const char* (*)(int change, int arg))(c[1].value))(0, c[1].arg), cl);
    else
        xx += rbf_draw_string_len(xx, yy, len_bool, (*(c[1].value))?"\x95":"", cl);
    xx += rbf_draw_string(xx, yy, "][", cl);

    switch (c[0].type & MENUITEM_MASK)
    {
    case MENUITEM_INT:
        get_int_disp_string(*(c[0].value));
        gui_set_int_cursor(4);
        ch = tbuf;
        break;
    case MENUITEM_ENUM:
        if (c[0].value)
            ch = ((const char* (*)(int change, int arg))(c[0].value))(0, c[0].arg);
        if ((c[0].type & MENUITEM_HHMMSS) && (gui_menu_curr_item==imenu))
        {
            switch (int_incr)
            {
            case 1:
                rbf_enable_cursor(5,6);
                break;
            case 10:
                rbf_enable_cursor(2,3);
                break;
            default:
                rbf_enable_cursor(0,0);
                break;
            }
        }
        else if (c[0].type & MENUITEM_DECIMAL)
        {
            gui_set_int_cursor(6);
        }
        else if (c[0].type & MENUITEM_SD_INT)
        {
            if (isdigit(ch[strlen(ch)-1]))
                gui_set_int_cursor(6);
        }
        else if (gui_menu_curr_item==imenu)
        {
            rbf_enable_cursor(0,6);
        }
        break;
    case MENUITEM_ENUM2:
        if (c[0].value)
        {
            extern const char* gui_change_enum2(const CMenuItem *menu_item, int change);
            ch = gui_change_enum2(c, 0);
            if (gui_menu_curr_item==imenu)
                rbf_enable_cursor(0,6);
        }
        break;
    }

    xx += rbf_draw_string_right_len(xx, yy, len_enum, ch, cl);
    rbf_disable_cursor();
    rbf_draw_string(xx, yy, "] ", cl);
}

//-------------------------------------------------------------------
void gui_menu_draw(int enforce_redraw)
{
    int i, j;
    const char *ch = "";

	if ( enforce_redraw )
		gui_menu_redraw = 2;

    if (gui_menu_redraw)
    {
        if (gui_menu_redraw==2)
            gui_menu_draw_initial();

        gui_menu_redraw=0;

        for (imenu=gui_menu_top_item, i=0, yy=y; curr_menu->menu[imenu].text && i<num_lines; ++imenu, ++i, yy+=rbf_font_height())
        {
            cl = (gui_menu_curr_item==imenu)?conf.menu_cursor_color:conf.menu_color;
            /*
            * When cursor is over a symbol, force symbol background color to be the menu cursor color but
            * keep the symbol color user defined.
            * old method was to set the symbol color to the symbol background color when the cursor highlighted it.
            * This method allows the user to have any symbol color and background color they want with the restriction
            * that the symbol background color will match the rest of the line when the cursor highlights it.
            * It creates a nice consistent look expecially when the symbol color matches the menu text color.
            * without this mod, there is no way to ever make the symbol color match the color of the rest of text menu line
            * when the cursor highlights a line.
            */
            cl_symbol = (gui_menu_curr_item==imenu)?MAKE_COLOR(BG_COLOR(cl),FG_COLOR(conf.menu_symbol_color)):conf.menu_symbol_color; //color 8Bit=Hintergrund 8Bit=Vordergrund

            xx = x;

            switch (curr_menu->menu[imenu].type & MENUITEM_MASK)
            {
            case MENUITEM_STATE_VAL_PAIR:
                gui_menu_draw_state_value((CMenuItem*)(curr_menu->menu[imenu].value));
                break;
            case MENUITEM_BOOL:
                gui_menu_draw_value((*(curr_menu->menu[imenu].value))?"\x95":" ", len_bool);
                break;
            case MENUITEM_INT:
                get_int_disp_string(*(curr_menu->menu[imenu].value));
                gui_menu_draw_value(tbuf, len_int);
                break;
            case MENUITEM_SUBMENU_PROC:
            case MENUITEM_SUBMENU:
                sprintf(tbuf, "%s%s", lang_str(curr_menu->menu[imenu].text),(conf.menu_symbol_enable)?"":" ->");
                gui_menu_draw_text(tbuf,2);
                break;
            case MENUITEM_UP:
                sprintf(tbuf, "%s%s", (conf.menu_symbol_enable)?"":"<- ", lang_str(curr_menu->menu[imenu].text));
                gui_menu_draw_text(tbuf,1);
                break;
            case MENUITEM_PROC:
            case MENUITEM_TEXT:
                gui_menu_draw_text(lang_str(curr_menu->menu[imenu].text),1);
                break;
            case MENUITEM_SEPARATOR:
                rbf_draw_char(x, yy, ' ', cl);

                if (lang_str(curr_menu->menu[imenu].text)[0])
                    sprintf(tbuf," %s ",lang_str(curr_menu->menu[imenu].text));
                else
                    tbuf[0] = 0;

                j = rbf_str_width(tbuf);
                xx += ((w - j) >> 1);

                if (xx > (x + len_space))
                {
                    draw_filled_rect(x+len_space, yy, xx-1, yy+rbf_font_height()/2-1, MAKE_COLOR(BG_COLOR(cl), BG_COLOR(cl)));
                    draw_line(x+len_space, yy+rbf_font_height()/2, xx-1, yy+rbf_font_height()/2, cl);
                    draw_filled_rect(x+len_space, yy+rbf_font_height()/2+1, xx-1, yy+rbf_font_height()-1, MAKE_COLOR(BG_COLOR(cl), BG_COLOR(cl)));
                }
                else
                {
                    xx = x;
                }

                if (j) xx += rbf_draw_clipped_string(xx, yy, tbuf, cl, 0, w);

                if (xx < (x+w-len_space))
                {
                    draw_filled_rect(xx, yy, x+w-len_space-1, yy+rbf_font_height()/2-1, MAKE_COLOR(BG_COLOR(cl), BG_COLOR(cl)));
                    draw_line(xx, yy+rbf_font_height()/2, x+w-1-len_space, yy+rbf_font_height()/2, cl);
                    draw_filled_rect(xx, yy+rbf_font_height()/2+1, x+w-len_space-1, yy+rbf_font_height()-1, MAKE_COLOR(BG_COLOR(cl), BG_COLOR(cl)));
                }

                rbf_draw_char(x+w-len_space, yy, ' ', cl);
                break;
            case MENUITEM_COLOR_FG:
            case MENUITEM_COLOR_BG:
                gui_menu_draw_symbol(1);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                draw_filled_round_rect(x+w-1-cl_rect-2-len_space, yy+2, x+w-1-2-len_space, yy+rbf_font_height()-1-2, 
                    MAKE_COLOR(((*(curr_menu->menu[imenu].value))>>(((curr_menu->menu[imenu].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?8:0))&0xFF, 
                               ((*(curr_menu->menu[imenu].value))>>(((curr_menu->menu[imenu].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?8:0))&0xFF));
                break;
            case MENUITEM_ENUM:
                if (curr_menu->menu[imenu].value)
                    ch = ((const char* (*)(int change, int arg))(curr_menu->menu[imenu].value))(0, curr_menu->menu[imenu].arg);
                gui_menu_draw_value(ch, len_enum);
                break;
            case MENUITEM_ENUM2:
                if (curr_menu->menu[imenu].value)
                {
                    extern const char* gui_change_enum2(const CMenuItem *menu_item, int change);
                    ch = gui_change_enum2(&curr_menu->menu[imenu], 0);
                }
                gui_menu_draw_value(ch, len_enum);
                break;
            }
        }

        // scrollbar
        if (count > num_lines)
        {
            i = num_lines*rbf_font_height()-1 -1;           // full height
            j = i*num_lines/count;                          // bar height
            if (j<20) j=20;
            i = (i-j)*((gui_menu_curr_item<0)?0:gui_menu_curr_item)/(count-1);   // top pos
            draw_filled_round_rect((x+w)+2, y+1,   (x+w)+6, y+1+i,                             MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_round_rect((x+w)+2, y+i+j, (x+w)+6, y+num_lines*rbf_font_height()-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_round_rect((x+w)+2, y+1+i, (x+w)+6, y+i+j,                             MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
        }
    }
}

//-------------------------------------------------------------------
// Menu button handler for Menu mode
void gui_menu_kbd_process_menu_btn()
{
    extern int gui_user_menu_flag;

    conf_save();

    if ( gui_user_menu_flag )
    {
        gui_set_mode(&menuGuiHandler);
        gui_user_menu_flag = 0;
        gui_menu_init(&root_menu);
    }
    else
        gui_set_mode(&altGuiHandler);
}

//-------------------------------------------------------------------
// GUI handler for menus
gui_handler menuGuiHandler = { GUI_MODE_MENU, gui_menu_draw, gui_menu_kbd_process, gui_menu_kbd_process_menu_btn, 0 };
//-------------------------------------------------------------------
