#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "conf.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_mbox.h"

#include "gui_tbox.h"
#include "module_def.h"

//-------------------------------------------------------------------
int gui_tbox_kbd_process();
void gui_tbox_kbd_process_menu_btn();
void gui_tbox_draw();

gui_handler GUI_MODE_TBOX =
    /*GUI_MODE_TBOX*/ { GUI_MODE_MODULE, gui_tbox_draw, gui_tbox_kbd_process, gui_tbox_kbd_process_menu_btn, 0 };

static gui_handler *gui_tbox_mode_old; // stored previous gui_mode
static int running = 0;

static int gui_tbox_redraw;
static char text_limit_reached;
static unsigned int tbox_width; //width of the 'window'

static const char*  tbox_title;
static const char*  tbox_msg;
static char         cursor_to_draw;

// height of prompt
#define MAX_LINES              6
#define MAX_WIDTH              40
#define MIN_WIDTH              28
#define SPACING_TITLE          4
#define SPACING_BTN            4
#define SPACING_BELOW_TEXT     10
#define BUTTON_SEP             18
#define BUTTON_SIZE            6

// max possible charsets
#define MAX_CHARSET            10

#define MAX_TEXT_WIDTH         (MAX_WIDTH-2)

#define RESET_CHAR             lastKey = '\0'; curchar = -1; curgroup = -1;

#define MAX_MSG_LENGH           20  //max length of hardcoded messages (>navigate cursor<, text limit reached)

typedef void (*tbox_on_select_t)(const char* newstr);
tbox_on_select_t tbox_on_select = 0;

static coord    tbox_buttons_x, tbox_buttons_y;

typedef char    *cmap[][4];

// Char maps
cmap tbox_chars_default = 
    {
        {"ABCDEF","GHIJKL","MNOPQRS","TUVWXYZ"},
        {"abcdef","ghijkl","mnopqrs","tuvwxyz"},
        {"123","456","789","0+-=/"},
        {".,:;?!","@#$%^&£","()[]{}","<>\"'`~_"},
        {0}
    };

cmap tbox_chars_german = 
    {
        {"ABCDEF","GHIJKL","MNOPQRS","TUVWXYZ"},
        {"abcdef","ghijkl","mnopqrs","tuvwxyz"},
        {"123","456","789","0+-=/"},
        {".,:;?!","@#$%^&£","()[]{}","<>\"'`~_"},
        {"ÄÖÜ","äöüß","€§µ","°²³"},
        {0}
    };

cmap tbox_chars_russian =
    {
        {"ABCDEF","GKLHIJ","MNOPQRS","TUVWXYZ"},
        {"abcdef","ghijkl","mnopqrs","tuvwxyz"},
        {"ÀÁÂÃÄÅÆ","ÇÈÉÊËÌÍ","ÎÏÐÑÒÓÔ","ÕÖ×ØÙÛÜÝÞß"},
        {"àáâãäåæ","çèéêëìí","îïðñòóô","õö÷øùûüýþÿ"},
        {"123","456","789","0+-="},
        {" .:,",";/\\","'\"*","#%&"},
        {0}
    };

cmap *charmaps[] = { &tbox_chars_default, &tbox_chars_german, &tbox_chars_russian };

int lines = 0;                  // num of valid lines in active charmap

int tbox_button_active, line;
int curchar;                    // idx of current entered char in current tmap
int curgroup;
int cursor;
char lastKey;                   // Last pressed key (Left, Right, Up, Down)
char Mode;                      // K=keyboard, T=textnavigate, B=button

char text_buf[MAX_TEXT_SIZE+1]; // Default buffer if not supplied by caller
char *text = 0;                 // Entered text
int maxlen, offset;
coord text_offset_x, text_offset_y, key_offset_x;

//-------------------------------------------------------
static char *map_chars(int line, int group)
{
    return (*charmaps[conf.tbox_char_map])[line][group];
}

//-------------------------------------------------------
int textbox_init(int title, int msg, const char* defaultstr, unsigned int maxsize, void (*on_select)(const char* newstr), char *input_buffer)
{
    running = 1;

    if (input_buffer)
        text = input_buffer;
    else
    {
        if (maxsize > MAX_TEXT_SIZE) maxsize = MAX_TEXT_SIZE;
        text = text_buf;
    }

    for (lines=0; map_chars(lines,0) && lines<MAX_CHARSET; lines++);

    memset(text, '\0', sizeof(char)*(maxsize+1));

    if ( defaultstr )
        strncpy(text, defaultstr, maxsize);

    tbox_button_active = 0;

    tbox_title = lang_str(title);
    tbox_msg = lang_str(msg);
    tbox_on_select = on_select;

    Mode = 'K';
    line = 0;
    RESET_CHAR
    cursor = -1;
    maxlen = maxsize;
    offset = 0;

    gui_tbox_redraw = 2;
    gui_tbox_mode_old = gui_set_mode( &GUI_MODE_TBOX );

    return 1;
}


static void gui_tbox_draw_buttons() {
    coord x = tbox_buttons_x;
    color cl;

    cl = MAKE_COLOR((tbox_button_active==0)?COLOR_RED:COLOR_BLACK, COLOR_WHITE);
    draw_rect(x-1, tbox_buttons_y+FONT_HEIGHT-1, x+BUTTON_SIZE*FONT_WIDTH+3, tbox_buttons_y+2*FONT_HEIGHT+3, COLOR_BLACK); //shadow
    draw_filled_rect(x-2, tbox_buttons_y-2+FONT_HEIGHT, x+BUTTON_SIZE*FONT_WIDTH+2, tbox_buttons_y+2*FONT_HEIGHT+2, cl);
    draw_string(x+(((BUTTON_SIZE-strlen(lang_str(LANG_MBOX_BTN_OK)))*FONT_WIDTH)>>1), tbox_buttons_y+FONT_HEIGHT, lang_str(LANG_MBOX_BTN_OK), cl);
    x+=BUTTON_SIZE*FONT_WIDTH+BUTTON_SEP;

    cl = MAKE_COLOR((tbox_button_active==1)?COLOR_RED:COLOR_BLACK, COLOR_WHITE);
    draw_rect(x-1, tbox_buttons_y+FONT_HEIGHT-1, x+BUTTON_SIZE*FONT_WIDTH+3, tbox_buttons_y+2*FONT_HEIGHT+3, COLOR_BLACK); //shadow
    draw_filled_rect(x-2, tbox_buttons_y-2+FONT_HEIGHT, x+BUTTON_SIZE*FONT_WIDTH+2, tbox_buttons_y+2*FONT_HEIGHT+2, cl);
    draw_string(x+(((BUTTON_SIZE-strlen(lang_str(LANG_MBOX_BTN_CANCEL)))*FONT_WIDTH)>>1), tbox_buttons_y+FONT_HEIGHT, lang_str(LANG_MBOX_BTN_CANCEL), cl);
    x+=BUTTON_SIZE*FONT_WIDTH+BUTTON_SEP;
}

void gui_tbox_draw()
{
    if ((gui_tbox_redraw && !text_limit_reached) || gui_tbox_redraw == 2) {
        if (gui_tbox_redraw==2) {
            text_limit_reached = 0;
            char c[MAX_LINES][MAX_WIDTH+1];        // PROMPT PARSED
            const char *p=tbox_msg;
            coord x=0, y=0;
            unsigned int h=0, l=0, bw=(2*BUTTON_SIZE*FONT_WIDTH+BUTTON_SEP);

            memset(c,0,sizeof(c));

            tbox_width =strlen(tbox_title);
            if (tbox_width > MAX_WIDTH) tbox_width = MAX_WIDTH;
            while (*p) {
                if (*p == '\n') {
                    c[h++][l] = 0;
                    l=0;
                    if (h == MAX_LINES) break;
                } else {
                    if (l < MAX_WIDTH) {
                        c[h][l++]=*p;
                        if (l > tbox_width) tbox_width = l;
                    }
                }
                ++p;
            }
            tbox_width+=2;
            if (h<MAX_LINES)
                c[h++][l] = 0;
            if (bw+BUTTON_SEP>tbox_width*FONT_WIDTH)
                tbox_width=(bw+BUTTON_SEP)/FONT_WIDTH+1;
             if (tbox_width<MIN_WIDTH)
                 tbox_width=MIN_WIDTH; // keyboard length
            if (tbox_width<MAX_MSG_LENGH)
                tbox_width=MAX_MSG_LENGH; // max message length
            if (tbox_width<maxlen) {
                if (maxlen < MAX_TEXT_WIDTH)
                    tbox_width=maxlen+2; // text length
                else
					tbox_width=((MAX_TEXT_WIDTH+2)>tbox_width)?MAX_TEXT_WIDTH+2:tbox_width;
            }
            
            key_offset_x=(camera_screen.width - tbox_width*FONT_WIDTH)>>1;
            
            h += 2;

            x = (camera_screen.width - tbox_width * FONT_WIDTH) >> 1;
            y = (camera_screen.height - (h+4) * FONT_HEIGHT-SPACING_BELOW_TEXT) >> 1;
            draw_rect_shadow(x-3, y-3, x+tbox_width*FONT_WIDTH+5, y+(h+4)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+12, COLOR_BLACK, 3); //shadow
            draw_filled_rect_thick(x-4, y-4, x+tbox_width*FONT_WIDTH+4, y+(h+4)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+11, MAKE_COLOR(COLOR_GREY, COLOR_WHITE), 3); // main box
            draw_filled_rect(x-2, y-2, x+tbox_width*FONT_WIDTH+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title

            l = strlen(tbox_title);
            draw_string(x+((tbox_width-l)>>1)*FONT_WIDTH, y, tbox_title, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
            y+=FONT_HEIGHT+2+SPACING_TITLE;

            tbox_buttons_x = x+((tbox_width*FONT_WIDTH-bw)>>1);

            text_offset_x = x+((tbox_width-((maxlen<MAX_TEXT_WIDTH)?maxlen:MAX_TEXT_WIDTH))>>1)*FONT_WIDTH;
            text_offset_y = y+(h-2)*FONT_HEIGHT+SPACING_BELOW_TEXT;

            tbox_buttons_y = text_offset_y+FONT_HEIGHT+SPACING_BELOW_TEXT; // on place of symbol line

            // draw prompt
            while (h) {
                l = strlen(c[--h]);
                draw_string(x+(((tbox_width-l)>>1)*FONT_WIDTH), y+h*FONT_HEIGHT, c[h], MAKE_COLOR(COLOR_GREY, COLOR_WHITE));
            }

            if ( Mode == 'B' )
                gui_tbox_draw_buttons();
        }

        // draw edit field
        int i;
        for (i=offset; (i-offset)<((maxlen<MAX_TEXT_WIDTH)?maxlen:MAX_TEXT_WIDTH); i++) {
            draw_char(text_offset_x+(i-offset)*FONT_WIDTH, text_offset_y, (i<strlen(text))?text[i]:' ', MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
        }
        
        // draw long text marker
        if ((strlen(text)-offset)>MAX_TEXT_WIDTH) draw_char(text_offset_x+MAX_TEXT_WIDTH*FONT_WIDTH, text_offset_y, '\20', MAKE_COLOR(COLOR_GREY, COLOR_RED));
        else draw_char(text_offset_x+MAX_TEXT_WIDTH*FONT_WIDTH, text_offset_y, ' ', MAKE_COLOR(COLOR_GREY, COLOR_GREY));
        if (offset>0) draw_char(text_offset_x-FONT_WIDTH, text_offset_y, '\21', MAKE_COLOR(COLOR_GREY, COLOR_RED));
        else draw_char(text_offset_x-FONT_WIDTH, text_offset_y, ' ', MAKE_COLOR(COLOR_GREY, COLOR_GREY));

        // symbol line
        if ( Mode== 'T' )
        {
            //rect clears any previous message
            draw_filled_rect(key_offset_x+((tbox_width-MAX_MSG_LENGH)>>1)*FONT_WIDTH, tbox_buttons_y, 
                             key_offset_x+((tbox_width+MAX_MSG_LENGH)>>1)*FONT_WIDTH, tbox_buttons_y+3*FONT_HEIGHT, MAKE_COLOR(COLOR_GREY,COLOR_GREY));
            draw_string(key_offset_x+((tbox_width-17)>>1)*FONT_WIDTH, tbox_buttons_y+FONT_HEIGHT, ">navigate cursor<", MAKE_COLOR(COLOR_GREY, COLOR_WHITE));
        }
        else if ( Mode == 'K' )
        {
            // draw keyboard
            char ch;
            color cl;

            // clean previous symbols line
            draw_filled_rect(key_offset_x, tbox_buttons_y, key_offset_x+(tbox_width-1)*FONT_WIDTH, tbox_buttons_y+3*FONT_HEIGHT, MAKE_COLOR(COLOR_GREY, COLOR_GREY));

            // draw current symbols line
            int x, group;

            for (group = 0; group < 4; group++)
            {
                char *tstr = map_chars(line,group);

                int y = tbox_buttons_y;
                int l = strlen(tstr);

                switch (group) {
                    case 0:
                        x=key_offset_x+4*FONT_WIDTH;
                        y=tbox_buttons_y+FONT_HEIGHT;
                        break;
                    case 1:
                        x=key_offset_x+(((tbox_width-l)*FONT_WIDTH)>>1);
                        y=tbox_buttons_y;
                        break;
                    case 2:
                        x=key_offset_x+(tbox_width-l-4)*FONT_WIDTH;
                        y=tbox_buttons_y+FONT_HEIGHT;
                        break;
                    case 3:
                        x=key_offset_x+(((tbox_width-l)*FONT_WIDTH)>>1);
                        y=tbox_buttons_y+2*FONT_HEIGHT;
                        break;
                }

                for(i = 0; tstr[i] != '\0'; i++, x += FONT_WIDTH) {
                    ch = tstr[i];

                    if ( (i != curchar) || (group != curgroup) )
                        cl = MAKE_COLOR(COLOR_GREY, COLOR_WHITE);
                    else if ( ch != ' ' )
                        cl = MAKE_COLOR(COLOR_GREY, COLOR_RED);
                    else
                        cl = MAKE_COLOR(COLOR_RED,COLOR_GREY);    // "space" is special color case (inverted)

                    draw_char(x, y, ch, cl);
                }
            }
        }
        gui_tbox_redraw = 0;
    }
    if (text_limit_reached) {
        // clean max_keyboard_length chars long field
        if (text_limit_reached%4 == 0)
            draw_filled_rect(key_offset_x+3, tbox_buttons_y, 
                             key_offset_x+tbox_width*FONT_WIDTH-3, tbox_buttons_y+3*FONT_HEIGHT, MAKE_COLOR(COLOR_GREY, COLOR_GREY));
        draw_string(key_offset_x+((tbox_width-18)>>1)*FONT_WIDTH, tbox_buttons_y+FONT_HEIGHT, "text limit reached", MAKE_COLOR(COLOR_GREY, COLOR_RED));
        text_limit_reached--;
    }
    if (cursor_to_draw) {
        draw_line(text_offset_x+(1+cursor-offset)*FONT_WIDTH, text_offset_y+1, text_offset_x+(1+cursor-offset)*FONT_WIDTH, text_offset_y+FONT_HEIGHT-3, MAKE_COLOR(COLOR_GREY, COLOR_YELLOW));
        cursor_to_draw = 0;
    }
    else {
        draw_line(text_offset_x+(1+cursor-offset)*FONT_WIDTH, text_offset_y+1, text_offset_x+(1+cursor-offset)*FONT_WIDTH, text_offset_y+FONT_HEIGHT-3, MAKE_COLOR(COLOR_GREY, COLOR_GREY));
        cursor_to_draw = 1;
    }
}

static void tbox_move_cursor(int direction)
{
    draw_line(text_offset_x+(1+cursor-offset)*FONT_WIDTH, text_offset_y+1, text_offset_x+(1+cursor-offset)*FONT_WIDTH, text_offset_y+FONT_HEIGHT-3, COLOR_BLACK);
    if (direction<0) {
        if (cursor >= 0) {
            cursor--;
            if (maxlen>MAX_TEXT_WIDTH && offset != 0 && cursor<offset)
                offset--;
        }
    }

    if (direction>0) {
        if (cursor < (maxlen-1)) {
            cursor++;
            if (maxlen>MAX_TEXT_WIDTH && (cursor-offset)>=MAX_TEXT_WIDTH)
                offset++;
        }
    }
    gui_tbox_redraw = 1;
}

static void tbox_move_text(int direction) {
    int i;
    if (direction<0) {
        //This loop moves all characters on the right of the cursor one place left
        for (i=cursor; i<strlen(text); i++) {
            text[i]=text[i+1];
        }
    }

    if (direction>0) {
        //This loop moves all characters on the right of the cursor one place right
        for (i=(strlen(text) < maxlen-1)?strlen(text):maxlen-1; i>cursor; i--) {
            text[i]=text[i-1];
        }
    }
    gui_tbox_redraw = 1;
}

static void tbox_keyboard_key(char curKey, int subgroup)
{
    if (curKey == 'b') {
        if (cursor >= 0) {
            tbox_move_text(-1);
            if (strlen(text)>=MAX_TEXT_WIDTH && (cursor-offset)>=MAX_TEXT_WIDTH-1) offset--;
            tbox_move_cursor(-1);
            RESET_CHAR
        }
    }
    else if (lastKey == curKey) {
        curchar++;
        curgroup = subgroup;
        char *tstr = map_chars(line,subgroup);
        if (tstr[curchar] == 0) curchar = 0;
        text[cursor] = tstr[curchar];
    }
    else if (curKey == 's') {
        if (strlen(text)<maxlen) {
            if (text[cursor+1] != '\0') tbox_move_text(1); //check wheter cursor is at the end of the string
            tbox_move_cursor(1);
            text[cursor] = ' ';
            RESET_CHAR
        }
        else {
            text_limit_reached = 8;
            RESET_CHAR
        }
    }
    else if (curKey == 'O') {
        RESET_CHAR
    }
    else {
        if (strlen(text)<maxlen) {
            curchar = 0; curgroup = subgroup;
            if (cursor < (maxlen-1)) {
                if (text[cursor+1] != '\0') tbox_move_text(1); //check wheter cursor is at the end of the string
                tbox_move_cursor(1);
            }
            lastKey = curKey;
            char *tstr = map_chars(line,subgroup);
            text[cursor] = tstr[curchar];
        }
        else { 
            text_limit_reached = 8;
            RESET_CHAR
        }
    }
    gui_tbox_redraw = 1;
}

void gui_tbox_kbd_process_menu_btn()
{
    switch (Mode)
    {
    case 'K':
        Mode = 'T';
        break;
    case 'T':
        Mode = 'B';
        break;
    default: // Mode == 'B'
        Mode = 'K';
        break;
    }
    gui_tbox_redraw=2;
}

int gui_tbox_kbd_process()
{
    if (Mode == 'K') {
        switch (kbd_get_autoclicked_key() | get_jogdial_direction()) {
            case KEY_SHOOT_HALF:
                line = (line+1)%lines;
                RESET_CHAR
                gui_tbox_redraw = 1;
                break;
            case KEY_UP:
                tbox_keyboard_key('U',1);
                break;
            case KEY_DOWN:
                tbox_keyboard_key('D',3);
                break;
            case KEY_LEFT:
                tbox_keyboard_key('L',0);
                break;
            case KEY_RIGHT:
                tbox_keyboard_key('R',2);
                break;
            case KEY_SET:
                tbox_keyboard_key('O',0);
                break;
            case KEY_ZOOM_IN:
            case KEY_DISPLAY:
                tbox_keyboard_key('s',0); //space
                break;
            case KEY_ZOOM_OUT:
                tbox_keyboard_key('b',0); //backspace
                break;
            case JOGDIAL_LEFT:
                tbox_move_cursor(-1);
                RESET_CHAR
                break;
            case JOGDIAL_RIGHT:
                if (text[cursor+1] != '\0') tbox_move_cursor(1);
                RESET_CHAR
                break;
        }
    }
    else if (Mode == 'T') {
        switch (kbd_get_autoclicked_key() | get_jogdial_direction()) {
            case JOGDIAL_LEFT:
            case KEY_LEFT:
                tbox_move_cursor(-1);
                RESET_CHAR
                break;
            case JOGDIAL_RIGHT:
            case KEY_RIGHT:
                if (text[cursor+1] != '\0') tbox_move_cursor(1);
                RESET_CHAR
                break;
            case KEY_SHOOT_HALF:
                tbox_keyboard_key('b',0);   //backspace - for non-zoom cameras?
                break;
            case KEY_DISPLAY:
                tbox_keyboard_key('s',0);   //space            -,,-
                break;
            case KEY_ZOOM_IN:
                if (offset<(strlen(text)-MAX_TEXT_WIDTH)) {
                    offset++;
                    if ((cursor+1)<offset) cursor++;
                    gui_tbox_redraw = 1;
                }
                break;
            case KEY_ZOOM_OUT:
                if (offset > 0) {
                    offset--;
                    if ((cursor-offset)>=MAX_TEXT_WIDTH) cursor--;
                    gui_tbox_redraw = 1;
                }
                break;
        }
    }
    else { // Mode == 'B'
        switch (kbd_get_autoclicked_key() | get_jogdial_direction()) {
            case JOGDIAL_LEFT:
            case KEY_LEFT:
                if (tbox_button_active > 0) tbox_button_active = 0;
                else tbox_button_active = 1;
                gui_tbox_draw_buttons();
                break;
            case JOGDIAL_RIGHT:
            case KEY_RIGHT:
                if (tbox_button_active <= 0) tbox_button_active = 1;
                else tbox_button_active = 0;
                gui_tbox_draw_buttons();
                break;
            case KEY_SET:
                gui_set_mode(gui_tbox_mode_old);
                if (tbox_on_select) {
                    if (tbox_button_active == 0)
                        tbox_on_select(text);   // ok
                    else {
                        tbox_on_select(0);      // cancel
                    }
                    tbox_on_select = 0;         // Prevent unloader from calling this function again
                }
                running = 0;
                break;
        }
    }
    return 0;
}


//==================================================

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    // clean allocated resource
    if (tbox_on_select)
    {
        tbox_on_select(0);      // notify callback about exit as cancel
        tbox_on_select = 0;     // prevent calling twice in the (unlikely) event of the unload called twice
    }

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

/******************** Module Information structure ******************/

libtextbox_sym _libtextbox =
{
    {
         0, _module_unloader, _module_can_unload, _module_exit_alt, 0
    },

    textbox_init,
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    GUI_TBOX_VERSION,           // Module version

    ANY_CHDK_BRANCH, 0,         // Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,       // Specify platform dependency

    (int32_t)"Virtual keyboard",// Module name
    0,

    &_libtextbox.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
