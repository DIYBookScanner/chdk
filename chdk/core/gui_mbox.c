#include "camera_info.h"
#include "stdlib.h"
#include "lang.h"
#include "modes.h"
#include "keyboard.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_mbox.h"

//-------------------------------------------------------------------
void gui_mbox_draw();
int gui_mbox_kbd_process();

static gui_handler mboxGuiHandler = { GUI_MODE_MBOX, gui_mbox_draw, gui_mbox_kbd_process, 0, GUI_MODE_FLAG_NORESTORE_ON_SWITCH };

static gui_handler      *gui_mbox_mode_old;
static const char*      mbox_title;
static const char*      mbox_msg;
static char             mbox_to_draw;
static unsigned int     mbox_flags;
#define MAX_LINES       8
#define MAX_WIDTH       35
#define SPACING_TITLE   4
#define SPACING_BTN     4
static struct {
        unsigned int    flag;
        int             text;
} buttons[] = {
        { MBOX_BTN_OK,      LANG_MBOX_BTN_OK    },
        { MBOX_BTN_YES,     LANG_MBOX_BTN_YES   },
        { MBOX_BTN_NO,      LANG_MBOX_BTN_NO    },
        { MBOX_BTN_CANCEL,  LANG_MBOX_BTN_CANCEL}
};
#define BUTTON_SIZE     6
#define BUTTONSNUM      (sizeof(buttons)/sizeof(buttons[0]))
#define MAX_BUTTONS     3
static int      mbox_buttons[MAX_BUTTONS], mbox_buttons_num, mbox_button_active;
static coord    mbox_buttons_x, mbox_buttons_y;
#define BUTTON_SEP      18
static void (*mbox_on_select)(unsigned int btn);

//-------------------------------------------------------------------
void gui_mbox_init(int title, int msg, const unsigned int flags, void (*on_select)(unsigned int btn))
{
    int i;

    mbox_buttons_num = 0;
    for (i=0; i<BUTTONSNUM && mbox_buttons_num<MAX_BUTTONS; ++i)
    {
        if (flags & MBOX_BTN_MASK & buttons[i].flag)
            mbox_buttons[mbox_buttons_num++] = i;
    }
    if (mbox_buttons_num == 0)
        mbox_buttons[mbox_buttons_num++] = 0; // Add button "Ok" if there is no buttons

    switch (flags & MBOX_DEF_MASK)
    {
        case MBOX_DEF_BTN2:
            mbox_button_active = 1;
            break;
        case MBOX_DEF_BTN3:
            mbox_button_active = 2;
            break;
        case MBOX_DEF_BTN1:
        default:
            mbox_button_active = 0;
            break;
    }

    mbox_title = lang_str(title);
    mbox_msg = lang_str(msg);
    mbox_to_draw = 3;
    mbox_flags = flags;
    mbox_on_select = on_select;

    gui_mbox_mode_old = gui_set_mode(&mboxGuiHandler);
}

//-------------------------------------------------------------------
static void gui_mbox_draw_buttons()
{
    int i;
    coord x = mbox_buttons_x;
    color cl;

    for (i=0; i<mbox_buttons_num; ++i)
    {
        cl = MAKE_COLOR((mbox_button_active==i)?COLOR_RED:COLOR_BLACK, COLOR_WHITE);
        draw_rect(x-1, mbox_buttons_y-1, x+BUTTON_SIZE*FONT_WIDTH+3, mbox_buttons_y+FONT_HEIGHT+3, COLOR_BLACK); //shadow
        draw_filled_rect(x-2, mbox_buttons_y-2, x+BUTTON_SIZE*FONT_WIDTH+2, mbox_buttons_y+FONT_HEIGHT+2, cl);
        draw_string(x+(((BUTTON_SIZE-strlen(lang_str(buttons[mbox_buttons[i]].text)))*FONT_WIDTH)>>1), mbox_buttons_y, lang_str(buttons[mbox_buttons[i]].text), cl);
        x += BUTTON_SIZE*FONT_WIDTH+BUTTON_SEP;
    }
}

//-------------------------------------------------------------------
void gui_mbox_draw()
{
    if (mbox_to_draw & 1)
    {
        char c[MAX_LINES][MAX_WIDTH+1];
        const char *p=mbox_msg;
        coord x=0, y=0, d;
        unsigned int w, h=0, l=0, bw=(mbox_buttons_num*BUTTON_SIZE*FONT_WIDTH+(mbox_buttons_num-1)*BUTTON_SEP);

        w = strlen(mbox_title);
        if (w > MAX_WIDTH) w = MAX_WIDTH;
        while (*p)
        {
            if (*p == '\n')
            {
                c[h++][l] = 0;
                l=0;
                if (h == MAX_LINES) break;
            }
            else
            {
                if (l < MAX_WIDTH)
                {
                    c[h][l++]=*p;
                    if (l > w) w = l;
                }
            }
            ++p;
        }
        w+=2;
        if (h<MAX_LINES)
            c[h++][l] = 0;
        if (bw+BUTTON_SEP>w*FONT_WIDTH) 
            w=(bw+BUTTON_SEP)/FONT_WIDTH+1;
    
        x = (camera_screen.width - w * FONT_WIDTH) >> 1;
        y = (camera_screen.height - (h+2) * FONT_HEIGHT) >> 1;
        draw_rect_shadow(x-3, y-3, x+w*FONT_WIDTH+5, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+8, COLOR_BLACK, 3); //shadow
        draw_filled_rect_thick(x-4, y-4, x+w*FONT_WIDTH+4, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+7, MAKE_COLOR(COLOR_GREY, COLOR_WHITE), 3); // main box
        draw_filled_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title
    
        l = strlen(mbox_title);
        draw_string(x+((w-l)>>1)*FONT_WIDTH, y, mbox_title, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
        y+=FONT_HEIGHT+2+SPACING_TITLE;
    
        mbox_buttons_x = x+((w*FONT_WIDTH-bw)>>1);
        mbox_buttons_y = y+h*FONT_HEIGHT+SPACING_BTN;

        while (h)
        {
            l = strlen(c[--h]);
            switch (mbox_flags & MBOX_TEXT_MASK)
            {
                case MBOX_TEXT_CENTER:  d = ((w-l)>>1)*FONT_WIDTH; break;
                case MBOX_TEXT_RIGHT:   d = (w-l-1)*FONT_WIDTH; break;
                case MBOX_TEXT_LEFT:
                default:                d = FONT_WIDTH; break;
            }
            draw_string(x+d, y+h*FONT_HEIGHT, c[h], MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // text
        }
    }

    if (mbox_to_draw & 2)
    {
        gui_mbox_draw_buttons();
    }

    mbox_to_draw = 0;
}

//-------------------------------------------------------------------
int gui_mbox_kbd_process()
{
    switch (kbd_get_clicked_key() | get_jogdial_direction())
    {
    case JOGDIAL_LEFT:
    case KEY_LEFT:
        if (--mbox_button_active < 0) mbox_button_active = mbox_buttons_num - 1;
        mbox_to_draw = 2;
        break;
    case JOGDIAL_RIGHT:
    case KEY_RIGHT:
        if (++mbox_button_active >= mbox_buttons_num) mbox_button_active = 0;
        mbox_to_draw = 2;
        break;
    case KEY_SET:
        gui_set_mode(gui_mbox_mode_old);
        if (mbox_flags & MBOX_FUNC_RESTORE)
            gui_set_need_restore();
        if (mbox_on_select) 
            mbox_on_select(buttons[mbox_buttons[mbox_button_active]].flag);
        break;
    }
    return 0;
}

//-------------------------------------------------------------------

void gui_browser_progress_show(const char* msg, const unsigned int perc)
{
    coord x=60, y=100;
    unsigned int w=240, h=40, len;

    draw_rect_shadow(x+1, y+1, x+w+1, y+h+1, COLOR_BLACK, 3); //shadow
    draw_filled_rect(x, y, x+w, y+h, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // main box
    len = strlen(msg);
    draw_string(x+((w-len*FONT_WIDTH)>>1), y+2, msg, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); //title text
    draw_filled_rect(x+10, y+4+FONT_HEIGHT, x+w-10, y+h-10, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); // progress rect
    draw_filled_rect(x+11, y+5+FONT_HEIGHT, x+11+(w-22)*perc/100, y+h-11, MAKE_COLOR(COLOR_RED, COLOR_RED)); // progress bar
}
