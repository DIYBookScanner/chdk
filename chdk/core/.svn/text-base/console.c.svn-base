#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "console.h"
#include "clock.h"
#include "keyboard.h"
#include "gui.h"
#include "gui_draw.h"

#define MAX_CONSOLE_LINES       14
#define MAX_CONSOLE_HISTORY     30
#define MAX_CONSOLE_LINE_LENGTH 44

// Static buffer for console output
// Latest entry is always console_buf[console_cur_line]
static char console_buf[MAX_CONSOLE_HISTORY][MAX_CONSOLE_LINE_LENGTH+1];

static int console_max_lines;           // total number of lines in console
static int console_num_lines;           // number of valid lines
static int console_cur_line = 0;        // current line for new text
static int console_line_length = 0;     // current console width
static int console_x;                   // screen X position
static int console_y;                   // screen Y position
static int console_autoredraw = 1;
static long console_last_modified;
int console_displayed = 0;

static void console_init(int num_lines, int line_length, int x_pos, int y_pos)
{
    console_max_lines = num_lines;
    console_line_length = line_length;
    console_y = y_pos;
    console_x = x_pos;

    console_num_lines = 0;
    console_last_modified = 0;
}

static int console_is_inited()
{
    return (console_line_length > 0);
}

static void console_ensure_inited()
{
    if (!console_is_inited())
        console_init(5, 25, 0, MAX_CONSOLE_LINES - 5);
}

static void console_start_line()
{
    // increase line count
    if (console_num_lines < console_max_lines)
        console_num_lines++;
    // move current line and clear content
    if (++console_cur_line >= MAX_CONSOLE_HISTORY)
        console_cur_line = 0;
    console_buf[console_cur_line][0] = 0;
}

void console_close()
{
    console_line_length = 0;
    console_autoredraw = 1;
}

void console_clear()
{
    console_num_lines = 0;
    
    if (console_autoredraw)
        console_redraw();
}

void console_draw()
{
    char buf[MAX_CONSOLE_LINE_LENGTH+1];

    console_ensure_inited();

    long t = get_tick_count();
    if (t <= console_last_modified + (conf.console_timeout*1000))
    {
        int y = (console_y + console_max_lines - 1) * FONT_HEIGHT;
        int x = console_x * FONT_WIDTH + camera_screen.ts_button_border;

        int c, i;
        for (c = 0, i = console_cur_line; c < console_num_lines; ++c, --i)
        {
            if (i < 0) i = MAX_CONSOLE_HISTORY-1;
            strncpy(buf,console_buf[i],console_line_length);
            buf[console_line_length] = 0;
            draw_string(x, y - c * FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));

            int l = strlen(buf);
            if (l < console_line_length)
                draw_filled_rect(x + l * FONT_WIDTH, y - c * FONT_HEIGHT,
                                 x + console_line_length * FONT_WIDTH - 1, y - c * FONT_HEIGHT + FONT_HEIGHT - 1,
                                 MAKE_COLOR(COLOR_BG, COLOR_BG));

            console_displayed = 1;
        }
    }
    else if (console_displayed)
    {
        gui_set_need_restore();
        console_displayed = 0;
    }
}

void console_add_line(const char *str)
{
	// Set console_autoredraw to -1 to stop script print statements from being displayed on screen
	// Can be used to send script output to a file (using print_screen function); but not have it displayed
	// on the LCD.
    if (console_autoredraw == -1)
	    return;

    console_ensure_inited();
    console_start_line();
    
    do
    {
        char *cur = console_buf[console_cur_line];
        int curlen = strlen(cur);
        int left = console_line_length - curlen;
        if (strlen(str) > left)
        {
            strncpy(cur + curlen, str, left);
            cur[console_line_length] = 0;
            console_start_line();
            str += left;
        }
        else
        {
            strcat(cur, str);
            break;
        }
    } while(1);
    
    console_last_modified = get_tick_count();
}

void console_set_layout(int x1, int y1, int x2, int y2) //untere linke Ecke(x1,y1), obere reche Ecke(x2,y2) - lower left corner (x1,y1), upper right corner(x2,y2)
{
    int i;

    // Swap co-ords so x1 < x2 & y1 < y2
    if (x1 > x2) { i = x1; x1 = x2; x2 = i; }
    if (y1 > y2) { i = y1; y1 = y2; y2 = i; }

    // Limit values to screen range (TODO: add error message if out of range)
    if (x1 < 0) x1 = 0;
    if (x1 > MAX_CONSOLE_LINE_LENGTH) x1 = MAX_CONSOLE_LINE_LENGTH;
    if (x2 < 0) x2 = 0;
    if (x2 > MAX_CONSOLE_LINE_LENGTH) x2 = MAX_CONSOLE_LINE_LENGTH;

    if (y1 < 0) y1 = 0;
    if (y1 > MAX_CONSOLE_LINES) y1 = MAX_CONSOLE_LINES;
    if (y2 < 0) y2 = 0;
    if (y2 > MAX_CONSOLE_LINES) y2 = MAX_CONSOLE_LINES;

    //Adjust for new size if needed
    console_line_length = x2 - x1;
    console_max_lines = y2 - y1;

    // If number of lines in console has reduced and old console has too many lines
    if (console_num_lines > console_max_lines)
        console_num_lines = console_max_lines;
        
    console_x = x1;
    console_y = MAX_CONSOLE_LINES - y2;

    if (console_autoredraw)
        console_redraw();
}

void console_set_autoredraw(int val)
{
	console_autoredraw = val;
}

void console_redraw()
{
    gui_set_need_restore();
	console_last_modified = get_tick_count();
}

//-------------------------------------------------------------------

static void gui_console_draw();
static int gui_console_kbd_process();

static gui_handler mboxGuiHandler = { GUI_MODE_MBOX, gui_console_draw, gui_console_kbd_process, 0, 0 };

static gui_handler	    *gui_console_mode_old;

static int  console_redraw_flag;
static int  console_scroll;

#define MAX_CONSOLE_DISP_LINES  12

//-------------------------------------------------------------------
void display_console()
{
    console_redraw_flag = 1;
    console_scroll = 0;
    gui_console_mode_old = gui_set_mode(&mboxGuiHandler);
}

//-------------------------------------------------------------------
static void gui_console_draw()
{
    if (console_redraw_flag)
    {
        coord x=0, y=0;
        int w, h, l;

        w = MAX_CONSOLE_LINE_LENGTH;
        h = MAX_CONSOLE_DISP_LINES;

        x = (camera_screen.width - w * FONT_WIDTH) >> 1;
        y = (camera_screen.height - (h+1) * FONT_HEIGHT) >> 1;

        draw_filled_rect_thick(x-3, y-3, x+w*FONT_WIDTH+3, y+(h+1)*FONT_HEIGHT+2, MAKE_COLOR(COLOR_BG, COLOR_WHITE), 1); // main box
        draw_filled_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+1, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title

        char *t = "Console - press SET to close";
        l = strlen(t);
        draw_string(x+((w-l)>>1)*FONT_WIDTH, y, t, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
        y += FONT_HEIGHT + 2;

        int c, i;
        for (c = h-1, i = console_cur_line-console_scroll; c >= 0; --c, --i)
        {
            if (i < 0) i += MAX_CONSOLE_HISTORY;

            draw_string(x-1, y + c * FONT_HEIGHT, console_buf[i], MAKE_COLOR(COLOR_BG, COLOR_FG));

            int l = strlen(console_buf[i]);
            if (l < w)
                draw_filled_rect(x + l * FONT_WIDTH, y + c * FONT_HEIGHT,
                                 x + w * FONT_WIDTH - 1, y + c * FONT_HEIGHT + FONT_HEIGHT - 1,
                                 MAKE_COLOR(COLOR_BG, COLOR_BG));
        }

        draw_filled_rect(x+w*FONT_WIDTH, y+((MAX_CONSOLE_HISTORY-console_scroll-h)*(h*FONT_HEIGHT))/MAX_CONSOLE_HISTORY, 
                         x+w*FONT_WIDTH+2, y+((MAX_CONSOLE_HISTORY-console_scroll)*(h*FONT_HEIGHT))/MAX_CONSOLE_HISTORY-1, 
                         MAKE_COLOR(COLOR_RED, COLOR_RED));

        console_redraw_flag = 0;
    }
}

//-------------------------------------------------------------------
static int gui_console_kbd_process()
{
    switch (kbd_get_clicked_key() | get_jogdial_direction())
    {
    case JOGDIAL_LEFT:
    case KEY_UP:
        if (console_scroll < (MAX_CONSOLE_HISTORY-MAX_CONSOLE_DISP_LINES))
        {
            console_scroll++;
            console_redraw_flag = 1;
        }
        break;
    case JOGDIAL_RIGHT:
    case KEY_DOWN:
        if (console_scroll > 0)
        {
            console_scroll--;
            console_redraw_flag = 1;
        }
        break;
    case KEY_SET:
        gui_set_mode(gui_console_mode_old);
        break;
    }
    return 0;
}
