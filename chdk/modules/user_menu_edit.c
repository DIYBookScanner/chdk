#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "keyboard.h"
#include "font.h"
#include "lang.h"
#include "fileutil.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_user_menu.h"
#include "gui_lang.h"
#include "gui_mbox.h"
#include "gui_mpopup.h"
#include "gui_fselect.h"

#include "module_load.h"
#include "module_def.h"

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
static int          len_bool, len_space;

static int running = 0;
static gui_handler *gui_mode_old; // stored previous gui_mode

//-------------------------------------------------------------------
static int validrow(int n)
{
    if (((curr_menu->menu[n].type & MENUITEM_MASK) != MENUITEM_SEPARATOR) &&
        ((curr_menu->menu[n].type & MENUITEM_SCRIPT_PARAM) != MENUITEM_SCRIPT_PARAM) &&
        ((curr_menu->menu[n].type & MENUITEM_TEXT) != MENUITEM_TEXT) &&
        (curr_menu->menu[n].text != LANG_MENU_USER_MENU) &&
        (curr_menu->menu[n].text != LANG_MENU_MAIN_TITLE))
        return 1;
    return 0;
}

static int gui_menu_disp_rows()
{
    int n, m;
    // Count the numer of rows in current menu
    for(n = 0, m = 0; curr_menu->menu[n].text; n++)
        if (validrow(n)) m++;
    return m;
}

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

//-------------------------------------------------------------------
static int inUserMenu(int n)
{
    int i;
    for (i=1; user_submenu.menu[i].text != 0; i++)
    {
        if (user_submenu.menu[i].text == curr_menu->menu[n].text)
            return 1;
    }
    return 0;
}

//-------------------------------------------------------------------
static CMenuItem mod_menu_item;
static char msgbuf[200];

void add_usermenu_item(unsigned int btn)
{
    gui_menu_erase_and_redraw();
    if (btn == MBOX_BTN_YES)
    {
        int i;

        /*
         * Insert new Item at end of existing entries
         */
        CMenuItem *items = (CMenuItem*)user_submenu.menu;

        for (i = 1; i < USER_MENU_ITEMS + 1; i++)
        {
            if (!items[i].text)
            {
                items[i] = mod_menu_item;
                camera_info.state.user_menu_has_changed = 1;
                return;
            }
        }
        gui_mbox_init(LANG_MENU_USER_MENU, LANG_USER_MENU_FULL, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
    }
}

static void add_usermenu()
{
    if (!inUserMenu(gui_menu_curr_item) && (curr_menu->menu[gui_menu_curr_item].text != LANG_MENU_BACK))
    {
        mod_menu_item = curr_menu->menu[gui_menu_curr_item];
        sprintf(msgbuf, lang_str(LANG_USER_MENU_ADD), lang_str(mod_menu_item.text));
        gui_mbox_init(LANG_INFORMATION, (int)msgbuf, MBOX_BTN_YES_NO|MBOX_DEF_BTN1|MBOX_TEXT_CENTER, add_usermenu_item);
    }
}

static void del_usermenu_item(unsigned int btn)
{
    gui_menu_erase_and_redraw();
    if (btn == MBOX_BTN_YES)
    {
        int i, c;

        /*
         * Delete user menu entry by sliding all the lower valid/existing entries up.
         */
        CMenuItem *items = (CMenuItem*)user_submenu.menu;

        for (c = 1; c < USER_MENU_ITEMS + 1; c++)
        {
            if (items[c].text == mod_menu_item.text)
            {
                for (i = c; items[i].text; i++)
                {
                    items[i] = items[i+1];

                    if (conf.user_menu_vars.items[i-1].script_file)
                        free(conf.user_menu_vars.items[i-1].script_file);
                    conf.user_menu_vars.items[i-1].script_file = conf.user_menu_vars.items[i].script_file;
                    conf.user_menu_vars.items[i].script_file = 0;

                    if (conf.user_menu_vars.items[i-1].script_title)
                        free(conf.user_menu_vars.items[i-1].script_title);
                    conf.user_menu_vars.items[i-1].script_title = conf.user_menu_vars.items[i].script_title;
                    conf.user_menu_vars.items[i].script_title = 0;
                }

                camera_info.state.user_menu_has_changed = 1;

                if (curr_menu->title == LANG_MENU_USER_MENU)
                {
                    if (gui_menu_curr_item >= gui_menu_rows())
                        gui_menu_curr_item--;
                }

                return;
            }
        }
    }
}

static void del_usermenu()
{
    if (inUserMenu(gui_menu_curr_item))
    {
        mod_menu_item = curr_menu->menu[gui_menu_curr_item];
        sprintf(msgbuf, lang_str(LANG_USER_MENU_DEL), lang_str(mod_menu_item.text));
        gui_mbox_init(LANG_INFORMATION, (int)msgbuf, MBOX_BTN_YES_NO|MBOX_DEF_BTN1|MBOX_TEXT_CENTER, del_usermenu_item);
    }
}

static void move_usermenu_item(int* cur_menu_item_indx, int dir)
{
    int src_index, dst_index ;
    char *tbuff;

    src_index = *cur_menu_item_indx ;
    dst_index = *cur_menu_item_indx + dir;    
        
    // Move current user menu item up (dir = -1) or down (dir = 1)
    CMenuItem *items = (CMenuItem*)user_submenu.menu;
        
    CMenuItem tmp_menu_item = items[dst_index];
    items[dst_index] = items[src_index];
    items[src_index] = tmp_menu_item;
    
    src_index--; dst_index--;
   
    tbuff = conf.user_menu_vars.items[dst_index].script_file;
    conf.user_menu_vars.items[dst_index].script_file = conf.user_menu_vars.items[src_index].script_file;    
    conf.user_menu_vars.items[src_index].script_file = tbuff;
            
    tbuff = conf.user_menu_vars.items[dst_index].script_title;
    conf.user_menu_vars.items[dst_index].script_title = conf.user_menu_vars.items[src_index].script_title;    
    conf.user_menu_vars.items[src_index].script_title = tbuff;
        
    *cur_menu_item_indx += dir;

    gui_menu_erase_and_redraw();
    camera_info.state.user_menu_has_changed = 1;
}

static void move_usermenu_item_up(int* cur_menu_item_indx)
{
    /*
     * Move entry up
     */
    if (*cur_menu_item_indx > 1)
        move_usermenu_item(cur_menu_item_indx, -1);
}

static void move_usermenu_item_down(int* cur_menu_item_indx)
{
    // don't allow moving link to main menu
    if (*cur_menu_item_indx == 0)
        return;

    /*
     * Move entry down below next entry if next entry is not empty
     */
    if((*cur_menu_item_indx < (USER_MENU_ITEMS)) && (user_submenu.menu[*cur_menu_item_indx +1].text))
        move_usermenu_item(cur_menu_item_indx, 1);
}

static void add_extern_to_user_menu(const char* fname, char* title, char sym, short type, int* func)
{
    int i;
    /*
     * Insert script/module info at end of existing entries
     */
    CMenuItem *items = (CMenuItem*)user_submenu.menu;
    gui_menu_erase_and_redraw();

    for(i = 1; i < USER_MENU_ITEMS + 1; i++)
    {
        if (!items[i].text)   // insert script/module title & full filename in next available spot 
        {
            if (conf.user_menu_vars.items[i-1].script_file == 0)
                conf.user_menu_vars.items[i-1].script_file = malloc(CONF_STR_LEN);
            strcpy(conf.user_menu_vars.items[i-1].script_file, fname);
            if (conf.user_menu_vars.items[i-1].script_title == 0)
                conf.user_menu_vars.items[i-1].script_title = malloc(CONF_STR_LEN);
            strcpy(conf.user_menu_vars.items[i-1].script_title, title);

            items[i].symbol = sym;
            items[i].opt_len = 0;
            items[i].type = type;
            items[i].text = (int) conf.user_menu_vars.items[i-1].script_title;
            items[i].value = func;
            items[i].arg = (int) conf.user_menu_vars.items[i-1].script_file;
            
            sprintf(msgbuf,lang_str(LANG_USER_MENU_ITEM_ADDED), lang_str(items[i].text));
            gui_mbox_init(LANG_MENU_USER_MENU, (int)msgbuf, MBOX_BTN_OK|MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, NULL);
            camera_info.state.user_menu_has_changed = 1;
            return;
        }
    }
    gui_mbox_init(LANG_MENU_USER_MENU, LANG_USER_MENU_FULL, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}

static void add_script_to_user_menu(const char* fname, char* title)
{
    add_extern_to_user_menu(fname, title, 0x35, MENUITEM_PROC, (int*)gui_load_user_menu_script);
}

static void add_module_to_user_menu(const char* fname, char* title)
{
    add_extern_to_user_menu(fname, title, 0x28, MENUITEM_PROC|MENUITEM_USER_MODULE, (int*)module_run);
}

//-------------------------------------------------------------------
static void gui_menu_set_curr_menu(CMenu *menu_ptr, int top_item, int curr_item)
{
    curr_menu = menu_ptr;
    gui_menu_top_item = top_item;
    gui_menu_curr_item = curr_item;
    while (!validrow(gui_menu_curr_item))
    {
        ++gui_menu_curr_item;
    }
}

//-------------------------------------------------------------------
static void gui_init(CMenu *menu_ptr) {

    if (menu_ptr) {
        gui_menu_set_curr_menu(menu_ptr, 0, 0);
        gui_menu_stack_ptr = 0;
    }

    num_lines = camera_screen.height/rbf_font_height()-1;
    x = camera_screen.menu_border_width;
    w = camera_screen.width-x-x;
    len_bool = rbf_str_width("\x95");
    len_space = rbf_char_width(' ');

    gui_menu_redraw=2;
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
}

//-------------------------------------------------------------------
// Helper functions for gui_uedit_kbd_process
//  common code blocks extracted to try and make it easier to understand

// Open a sub-menu
void gui_activate_sub_menu(CMenu *sub_menu)
{
    // push current menu on stack
    gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
    gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
    gui_menu_stack[gui_menu_stack_ptr].toppos = gui_menu_top_item;

    gui_menu_set_curr_menu(sub_menu, 0, 0);

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

// Move up / down in menu, adjusting scroll position if needed
//   increment = -1 to move up, 1 to move down
static void gui_menu_updown(int increment)
{
    int c, j;

    if (count == 0) return;

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
        } while (!validrow(gui_menu_curr_item));

        // Redraw menu if needed
        if (gui_menu_redraw == 0) gui_menu_redraw=1;
    }
}

//-------------------------------------------------------------------
// Draw menu scroll bar if needed, and title bar
static void gui_draw_initial()
{ 
    count = gui_menu_disp_rows();

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

    rbf_draw_menu_header(x, y-rbf_font_height(), w+wplus, (conf.menu_symbol_enable)?curr_menu->symbol:0, lang_str(curr_menu->title), MAKE_COLOR(COLOR_RED,COLOR_WHITE));
}

//-------------------------------------------------------------------

// Local variables used by menu draw functions
static int imenu, yy, xx, symbol_width;
static color cl, cl_symbol;

// Common code extracted from gui_draw for displaying the symbol on the left
static void gui_draw_symbol(int num_symbols)
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

// Common code extracted from gui_draw for displaying an int, enum or bool value on the right
static void gui_draw_value()
{
    gui_draw_symbol(1);
    xx += rbf_draw_string_len(xx, yy, w-len_space*4, lang_str(curr_menu->menu[imenu].text), cl);
}

// Common code extracted from gui_draw for displaying a text menu string
static void gui_draw_text(char *str, int num_symbols)
{
    gui_draw_symbol(num_symbols);
    xx += rbf_draw_string_len(xx, yy, w-len_space-len_space-symbol_width, str, cl);
    if ((num_symbols == 2) && conf.menu_symbol_enable)
        xx += rbf_draw_symbol(xx, yy, 0x52, cl_symbol);
    rbf_draw_char(xx, yy, ' ', cl);
}

// Common code extracted from gui_draw for displaying an int or enum that can be enabled/disabled
static void gui_draw_state_value(CMenuItem *c)
{
    const char *ch = "";

    int text = curr_menu->menu[imenu].text;
    if (c[0].text != 0)
        text = c[0].text;

    int wid = w-len_space-len_space;

    gui_draw_symbol(1);
    xx += rbf_draw_string_len(xx, yy, wid, lang_str(text), cl);
}

//-------------------------------------------------------------------
static void gui_draw(int enforce_redraw)
{
    int i, j;
    const char *ch = "";

	if ( enforce_redraw )
		gui_menu_redraw = 2;

    if (gui_menu_redraw)
    {
        if (gui_menu_redraw==2)
            gui_draw_initial();

        gui_menu_redraw=0;

        for (imenu=gui_menu_top_item, i=0, yy=y; curr_menu->menu[imenu].text && i<num_lines; ++imenu)
        {
            if (validrow(imenu))
            {
                cl = (gui_menu_curr_item==imenu)?conf.menu_cursor_color:conf.menu_color;
                if (inUserMenu(imenu) && (curr_menu->title != LANG_MENU_USER_MENU))
                    cl = MAKE_COLOR(BG_COLOR(cl),COLOR_GREEN);
                cl_symbol = (gui_menu_curr_item==imenu)?MAKE_COLOR(BG_COLOR(cl),FG_COLOR(conf.menu_symbol_color)):conf.menu_symbol_color;

                xx = x;

                switch (curr_menu->menu[imenu].type & MENUITEM_MASK)
                {
                case MENUITEM_STATE_VAL_PAIR:
                    gui_draw_state_value((CMenuItem*)(curr_menu->menu[imenu].value));
                    break;
                case MENUITEM_BOOL:
                case MENUITEM_INT:
                case MENUITEM_ENUM:
                case MENUITEM_ENUM2:
                    gui_draw_value();
                    break;
                case MENUITEM_SUBMENU_PROC:
                case MENUITEM_SUBMENU:
                    sprintf(msgbuf, "%s%s", lang_str(curr_menu->menu[imenu].text),(conf.menu_symbol_enable)?"":" ->");
                    gui_draw_text(msgbuf,2);
                    break;
                case MENUITEM_UP:
                    sprintf(msgbuf, "%s%s", (conf.menu_symbol_enable)?"":"<- ", lang_str(curr_menu->menu[imenu].text));
                    gui_draw_text(msgbuf,1);
                    break;
                case MENUITEM_PROC:
                    gui_draw_text(lang_str(curr_menu->menu[imenu].text),1);
                    break;
                case MENUITEM_COLOR_FG:
                case MENUITEM_COLOR_BG:
                    gui_draw_symbol(1);
                    xx+=rbf_draw_string_len(xx, yy, w-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                    break;
                }

                yy += rbf_font_height();
                i++;
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
static void gui_uedit_kbd_process_menu_btn()
{
    if (curr_menu->title == LANG_MENU_USER_MENU)
    {
        running = 0;
        gui_set_mode(gui_mode_old);
    }
    else
    {
        gui_menu_erase_and_redraw();
        gui_init(&user_submenu);
    }
}

//-------------------------------------------------------------------
#define UEDIT_MENU      1
#define UEDIT_SCRIPT    2
#define UEDIT_MODULE    4
#define UEDIT_REMOVE    8

static struct mpopup_item popup_uedit[]= {
        { UEDIT_MENU,           LANG_USER_MENU_ITEMS },
        { UEDIT_SCRIPT,         LANG_MENU_USER_MENU_SCRIPT_ADD },
        { UEDIT_MODULE,         LANG_MENU_USER_MENU_MODULE_ADD },
        { UEDIT_REMOVE,         LANG_MENU_USER_MENU_REMOVE },
        { 0,                    0 },
};

const char* skip_whitespace(const char* p)  { while (*p==' ' || *p=='\t') p++; return p; }                                  // Skip past whitespace
const char* skip_toeol(const char* p)       { while (*p && *p!='\r' && *p!='\n') p++; return p; }                           // Skip to end of line
const char* skip_eol(const char *p)         { p = skip_toeol(p); if (*p == '\r') p++; if (*p == '\n') p++; return p; }      // Skip past end of line

static int chk_ext(char *ext, char *tst)
{
    if (ext && (strlen(ext) == strlen(tst)+1))
    {
        int i;
        for (i=0; i<strlen(tst); i++)
            if (toupper(ext[i+1]) != toupper(tst[i]))
                return 0;
        return 1;
    }
    return 0;
}

static void gui_uedit_script_selected(const char *fn)
{
    if (fn)
    {
        char *ext = strrchr(fn,'.');
        if (chk_ext(ext,"lua") || chk_ext(ext,"bas"))
        {
            char* buf;

            buf = load_file(fn, 0, 1);

            if (buf)
            {
                char script_title[36];
                register const char *ptr = buf;
                char *c;

                // Build title

                c=strrchr(fn, '/');
                strncpy(script_title, (c)?c+1:fn, sizeof(script_title));
                script_title[sizeof(script_title)-1]=0;

                while (ptr[0])
                {
                    ptr = skip_whitespace(ptr);
                    if (ptr[0]=='@') {
                        if (strncmp("@title", ptr, 6)==0)
                        {
                            ptr = ptr + 6;
                            register int i=0;

                            ptr = skip_whitespace(ptr);
                            while (i<(sizeof(script_title)-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n')
                            {
                                script_title[i]=ptr[i];
                                ++i;
                            }
                            script_title[i]=0;
                            break;
                        }
                    }
                    ptr = skip_eol(ptr);
                }

                add_script_to_user_menu(fn, script_title);
                free(buf);
            }
        }
    }
}

static void gui_uedit_module_selected(const char *fn)
{
    if (fn)
    {
        char *ext = strrchr(fn,'.');
        if (chk_ext(ext,"flt"))
        {
            _version_t v = ANY_VERSION;
            struct flat_hdr* mod = module_preload(fn, v);
            if (mod > 0)
            {
                if (mod->_module_info->lib->run != 0)   // Simple Module?
                {
                    char *n;
                    if (mod->_module_info->moduleName < 0)
                        n = lang_str(-mod->_module_info->moduleName);
                    else
                        n = (char*)mod->_module_info->moduleName;
                    add_module_to_user_menu(fn, n);
                    free(mod);
                }
                else
                {
                    sprintf(msgbuf, lang_str(LANG_MODULE_NOT_SIMPLE), fn);
                    gui_mbox_init(LANG_ERROR, (int)msgbuf, MBOX_BTN_OK|MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, NULL);
                }
            }
        }
    }
}
static void uedit_set(unsigned int actn)
{
    switch (actn)
    {
        case UEDIT_MENU:
            gui_init(&root_menu);
            break;
        case UEDIT_SCRIPT:
            libfselect->file_select(LANG_MENU_USER_MENU_SCRIPT_ADD, conf.script_file, "A/CHDK/SCRIPTS", gui_uedit_script_selected);
            break;
        case UEDIT_MODULE:
            libfselect->file_select(LANG_MENU_USER_MENU_MODULE_ADD, "A/CHDK/MODULES", "A/CHDK/MODULES", gui_uedit_module_selected);
            break;
        case UEDIT_REMOVE:
            del_usermenu();
            break;
    }
    gui_menu_erase_and_redraw();
}

// Process button presses when in GUI_MODE_MENU mode
static int gui_uedit_kbd_process() {

    switch (kbd_get_autoclicked_key() | get_jogdial_direction())
    {
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
            if (curr_menu->title == LANG_MENU_USER_MENU)
            {
                move_usermenu_item_up(&gui_menu_curr_item);
            }
            else
            {
                del_usermenu();
            }
            break;
        case KEY_SHOOT_HALF:
        case KEY_ERASE:
            del_usermenu();
            break;
        case FRONTDIAL_RIGHT:
        case KEY_RIGHT:
            if (curr_menu->title == LANG_MENU_USER_MENU)
            {
                move_usermenu_item_down(&gui_menu_curr_item);
            }
            else
            {
                add_usermenu();
            }
            break;
        case KEY_SET:
            if (curr_menu->title == LANG_MENU_USER_MENU)
            {
                libmpopup->show_popup( popup_uedit, UEDIT_MENU|UEDIT_SCRIPT|UEDIT_MODULE|UEDIT_REMOVE, uedit_set);
            }
            else
            {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)
                {
                    case MENUITEM_UP:
                        gui_menu_back();
                        break;
                    case MENUITEM_SUBMENU:
                        select_sub_menu();
                        break;
                }
            }
            break;
        case KEY_DISPLAY:
            gui_menu_back();
            break;
    }

    return 0;
}

//-------------------------------------------------------------------
// GUI handler for menus
static gui_handler ueditGuiHandler = { GUI_MODE_MODULE, gui_draw, gui_uedit_kbd_process, gui_uedit_kbd_process_menu_btn, 0 };
//-------------------------------------------------------------------


// =========  MODULE INIT =================
#include "simple_module.h"

int _run()
{
    running = 1;
    gui_menu_redraw = 2;
    gui_init(&user_submenu);
    gui_mode_old = gui_set_mode(&ueditGuiHandler);

    return 0;
}

int _module_can_unload()
{
    return running == 0;
}

int _module_exit_alt()
{
    running = 0;
    return 0;
}

int _module_unload()
{
    conf_save();
    return 0;
}

libsimple_sym _librun =
{
    {
        0,
        _module_unload,
        _module_can_unload,
        _module_exit_alt,
        _run
    }
};

/******************** Module Information structure ******************/

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    -LANG_MENU_USER_MENU_EDIT,	// Module name
    0,

    &_librun.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
