#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "modes.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_mbox.h"

#include "module_def.h"
#include "simple_module.h"

//-------------------------------------------------------------------

typedef struct
{
    int sokoban_level;
} SokobanConf;

SokobanConf sconf;

static ConfInfo conf_info[] = {
    CONF_INFO( 1, sconf.sokoban_level,          CONF_DEF_VALUE, i:0),
    {0,0,0,0,{0}}
};

void gui_module_menu_kbd_process();
int gui_sokoban_kbd_process();
void gui_sokoban_draw();

gui_handler GUI_MODE_SOKOBAN = 
    /*GUI_MODE_SOKOBAN*/    { GUI_MODE_MODULE, gui_sokoban_draw, gui_sokoban_kbd_process, gui_module_menu_kbd_process, GUI_MODE_FLAG_NODRAWRESTORE };

//-------------------------------------------------------------------
#define FIELD_WIDTH             15
#define FIELD_HEIGHT            15

#define WALL_COLOR_1            COLOR_GREY
#define WALL_COLOR_2            COLOR_BLACK
#define BOX_COLOR_1             COLOR_RED
#define BOX_COLOR_2             COLOR_BLACK
#define BOX_COLOR_3             COLOR_YELLOW
#define PLACE_COLOR_1           COLOR_BLUE
#define PLACE_COLOR_2           COLOR_BLACK
#define PLAYER_COLOR_1          COLOR_GREEN
#define PLAYER_COLOR_2          COLOR_BLACK

#define MARKER_WALL             '#'
#define MARKER_BOX              '$'
#define MARKER_PLACE            '.'
#define MARKER_BOX_PLACE        '*'
#define MARKER_PLAYER           '@'
#define MARKER_PLAYER_PLACE     '+'
#define MARKER_EMPTY            '_' // was space
#define MARKER_LINE_END        '\n' // was |
#define MARKER_LEVEL_END        '!'

#define LEVEL_CHARS "#$.*@+_"

#define UNDO_SIZE               1000

//-------------------------------------------------------------------
static const char *level_file_name="A/CHDK/GAMES/SOKOBAN.LEV";
#define MAX_LEVELS 200
static unsigned short level_start_list[MAX_LEVELS];
static unsigned char level_length_list[MAX_LEVELS];
static unsigned num_levels;

static int need_redraw;
static int need_redraw_all;
static int  moves;
static char field[FIELD_HEIGHT][FIELD_WIDTH];

static int cell_size;
static int xPl, yPl;

static int undo[UNDO_SIZE/10];
static int undo_begin, undo_end, undo_curr;

//-------------------------------------------------------------------
static void sokoban_undo_add(int dx, int dy, int box) {
    int offs, bits, value;

    value = ((box)?1:0)<<2;
    if (dx) {
        value |= ((dx<0)?1:0)<<1;
    } else {
        value |= (((dy<0)?1:0)<<1)|1;
    }
    
    offs = undo_curr/10;
    bits = (undo_curr%10)*3;
    undo[offs] &= ~(7<<bits);
    undo[offs] |= (value&7)<<bits;

    if (++undo_curr==UNDO_SIZE) undo_curr=0;
    if (undo_curr==undo_begin) {
        if (++undo_begin==UNDO_SIZE) undo_begin=0;
    }
    undo_end=undo_curr;
} 

//-------------------------------------------------------------------
static void sokoban_undo() {
    int dx=0, dy=0, value;
    
    if (undo_curr!=undo_begin) {
        if (undo_curr==0) undo_curr=UNDO_SIZE;
        --undo_curr;
        
        value = (undo[undo_curr/10]>>((undo_curr%10)*3))&7;
        if (value&1) dy=1; else dx=1;
        if (value&2) {dy=-dy; dx=-dx;}

        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        if (value&4) {
            field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
            field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
        }
        xPl-=dx; yPl-=dy;
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
        --moves;
    }
}

//-------------------------------------------------------------------
static void sokoban_redo() {
    int dx=0, dy=0, value;
    
    if (undo_curr!=undo_end) {
        value = (undo[undo_curr/10]>>((undo_curr%10)*3))&7;
        if (value&1) dy=1; else dx=1;
        if (value&2) {dy=-dy; dx=-dx;}

        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        xPl+=dx; yPl+=dy;
        if (value&4) {
            field[yPl][xPl]=(field[yPl][xPl]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
            field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
        }
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
        ++moves;

        ++undo_curr;
        if (undo_curr==UNDO_SIZE) undo_curr=0;
    }
}

//-------------------------------------------------------------------
static void sokoban_undo_reset() {
    undo_begin=undo_end=undo_curr=0;
}

//-------------------------------------------------------------------
static void sokoban_set_level(int lvl) {
    int x=0, y, w=0, h=0;
    const char *p;
    char *buf;
    FILE *fd;    
    int start,len;

    len=level_length_list[lvl];
    start=level_start_list[lvl];
    fd=fopen(level_file_name,"rb");
    if(!fd) {
        num_levels=0;
        return;
    }

    buf=malloc(len+1);
    if(!buf) {
        fclose(fd);
        return;
    }

    if(fseek(fd,start,SEEK_SET) != 0) {
        fclose(fd);
        free(buf);
        return;
    }
    fread(buf,1,len,fd);
    buf[len]=0;
    fclose(fd);

    p=buf;

    // determine dimensions
    while (*p) {
      if (*p==MARKER_LINE_END) {
          ++h;
          if (x>w) w=x;
          x=0;
      } else {
          ++x;
      }
      ++p;
    }
    if (x>w) w=x;
    h-=1; //the last line didn't previously have an end marker

    // clear field
    for (y=0; y<FIELD_HEIGHT; ++y)
        for (x=0; x<FIELD_WIDTH; ++x)
            field[y][x]=MARKER_EMPTY;
    
    // place maze at the center
    p=buf;
    for (y=(FIELD_HEIGHT-h)/2; y<FIELD_HEIGHT; ++y, ++p) {
        for (x=(FIELD_WIDTH-w)/2; x<FIELD_WIDTH && *p && *p!=MARKER_LINE_END; ++x, ++p) {
            field[y][x]=*p;
            if (field[y][x] == MARKER_PLAYER || field[y][x] == MARKER_PLAYER_PLACE) {
              xPl = x; yPl = y;
            }
        }
        if (!*p || (*p == MARKER_LINE_END && !*(p+1))) break;
    }
    
    free(buf);
    sconf.sokoban_level = lvl;
    moves = 0;
    sokoban_undo_reset();
}

//-------------------------------------------------------------------
static int sokoban_finished() {
    int x, y;

    for (y=0; y<FIELD_HEIGHT; ++y)
        for (x=0; x<FIELD_WIDTH; ++x)
            if (field[y][x]==MARKER_BOX) 
                return 0;
    return 1;
}

//-------------------------------------------------------------------
static void sokoban_next_level() {
    if (++sconf.sokoban_level >= num_levels) sconf.sokoban_level = 0;
    sokoban_set_level(sconf.sokoban_level);
    need_redraw_all = 1;
}

//-------------------------------------------------------------------
static int sokoban_move(int dx, int dy) {
    switch (field[yPl+dy][xPl+dx]) {
        case MARKER_WALL:
            return 0;
            break;
        case MARKER_BOX:
        case MARKER_BOX_PLACE:
            if (field[yPl+dy*2][xPl+dx*2]==MARKER_WALL || field[yPl+dy*2][xPl+dx*2]==MARKER_BOX || field[yPl+dy*2][xPl+dx*2]==MARKER_BOX_PLACE)
                return 0;
            break;
        case MARKER_PLACE:
        case MARKER_EMPTY:
            break;
    }
    field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
    xPl+=dx; yPl+=dy;
    if (field[yPl][xPl]==MARKER_BOX || field[yPl][xPl]==MARKER_BOX_PLACE) {
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
        sokoban_undo_add(dx, dy, 1);
    } else {
        sokoban_undo_add(dx, dy, 0);
    }
    field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
    return 1;
}

//-------------------------------------------------------------------
static void sokoban_draw_box(int x, int y, color cl) {
    draw_filled_rect(camera_screen.ts_button_border+x*cell_size, y*cell_size, camera_screen.ts_button_border+x*cell_size+cell_size-1, y*cell_size+cell_size-1, cl);
    draw_line(camera_screen.ts_button_border+x*cell_size+2, y*cell_size, camera_screen.ts_button_border+x*cell_size+2, y*cell_size+cell_size-1, cl);
    draw_line(camera_screen.ts_button_border+x*cell_size+cell_size-1-2, y*cell_size, camera_screen.ts_button_border+x*cell_size+cell_size-1-2, y*cell_size+cell_size-1, cl);
    draw_line(camera_screen.ts_button_border+x*cell_size+2, y*cell_size+2, camera_screen.ts_button_border+x*cell_size+cell_size-1-2, y*cell_size+2, cl);
    draw_line(camera_screen.ts_button_border+x*cell_size+2, y*cell_size+cell_size-1-2, camera_screen.ts_button_border+x*cell_size+cell_size-1-2, y*cell_size+cell_size-1-2, cl);
}

//-------------------------------------------------------------------
int gui_sokoban_init() {
    /* first time through, load the file and make an index
     if would could tell when the user left sokoban, 
     we could avoid this and malloc all the data structures
     unfortunately, gui_mode gets set all over the place */
    if(!num_levels) {
        char *buf,*p;
        FILE *fd;    
        struct stat st;

        if (stat((char *)level_file_name,&st) != 0 || st.st_size==0) 
            return 0;

        fd=fopen(level_file_name,"rb");
        if(!fd) 
            return 0;

        buf=malloc(st.st_size+1);
        if(!buf) {
            fclose(fd);
            return 0;
        }

        fread(buf,1,st.st_size,fd);
        buf[st.st_size]=0;
        fclose(fd);
        p = buf;
        do {
            // skip to the first level char
            p = strpbrk(p,LEVEL_CHARS);
            // found a level char, store the start
            if (p) {
                unsigned pos = p - buf;
                if ( pos > 65535 ) {
                    break;
                }
                level_start_list[num_levels] = (unsigned short)pos;
                p=strchr(p,MARKER_LEVEL_END);
                // found the end char, store the end
                if(p) {
                    unsigned len = p - (buf + level_start_list[num_levels]);
                    // bail on invalid level
                    if ( len > 255 ) {
                        break;
                    }
                    level_length_list[num_levels] = (unsigned char)len;
                    ++num_levels;
                }
            }
        } while(p && num_levels < MAX_LEVELS);
        free(buf);
    }
    if(!num_levels) {
        return 0;
    }
    else if(sconf.sokoban_level >= num_levels) {
        sconf.sokoban_level = 0;
    }
    cell_size = camera_screen.height/FIELD_HEIGHT;
    sokoban_set_level(sconf.sokoban_level);
	// if the file is no longer readable, set_level will set this
    if(!num_levels) {
        return 0;
    }
    need_redraw_all = 1;

    gui_set_mode(&GUI_MODE_SOKOBAN);
    return 1;
}

//-------------------------------------------------------------------
int gui_sokoban_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
        case KEY_UP:
            moves+=sokoban_move(0, -1);
            need_redraw = 1;
            break;
        case KEY_DOWN:
            moves+=sokoban_move(0, +1);
            need_redraw = 1;
            break;
        case KEY_LEFT:
            moves+=sokoban_move(-1, 0);
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            moves+=sokoban_move(+1, 0);
            need_redraw = 1;
            break;
        case KEY_SET:
            if (moves == 0) {
                sokoban_next_level();
            }
            break;
        case KEY_ZOOM_OUT:
            sokoban_undo();
            need_redraw = 1;
            break;
        case KEY_ZOOM_IN:
            sokoban_redo();
            need_redraw = 1;
            break;
        case KEY_ERASE:
        case KEY_DISPLAY:
            sokoban_set_level(sconf.sokoban_level);
            need_redraw_all = 1;
            break;
    }
    return 0;
}

//-------------------------------------------------------------------
void gui_sokoban_draw() {
    int y, x;
    static char str[16];

    if (need_redraw_all) {
        draw_filled_rect(0, 0, camera_screen.width-1, camera_screen.height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
        need_redraw_all = 0;
        need_redraw = 1;
    }

    if (need_redraw) {
        need_redraw = 0;
        for (y=0; y<FIELD_HEIGHT; ++y) {
            for (x=0; x<FIELD_WIDTH; ++x) {
                switch (field[y][x]) {
                    case MARKER_WALL:
                        draw_filled_rect(camera_screen.ts_button_border+x*cell_size, y*cell_size, camera_screen.ts_button_border+x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(WALL_COLOR_1, WALL_COLOR_2));
                        break;
                    case MARKER_BOX:
                        sokoban_draw_box(x, y, MAKE_COLOR(BOX_COLOR_1, BOX_COLOR_2));
                        break;
                    case MARKER_PLACE:
                        draw_filled_rect(camera_screen.ts_button_border+x*cell_size, y*cell_size, camera_screen.ts_button_border+x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        draw_filled_rect(camera_screen.ts_button_border+x*cell_size+4, y*cell_size+4, camera_screen.ts_button_border+x*cell_size+cell_size-1-4, y*cell_size+cell_size-1-4, MAKE_COLOR(PLACE_COLOR_1, PLACE_COLOR_2));
                        break;
                    case MARKER_BOX_PLACE:
                        sokoban_draw_box(x, y, MAKE_COLOR(BOX_COLOR_3, BOX_COLOR_2));
                        break;
                    case MARKER_PLAYER:
                    case MARKER_PLAYER_PLACE:
                        draw_filled_rect(camera_screen.ts_button_border+x*cell_size, y*cell_size, camera_screen.ts_button_border+x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        draw_filled_ellipse(camera_screen.ts_button_border+x*cell_size+(cell_size>>1)-1, y*cell_size+(cell_size>>1)-1, (cell_size>>1)-3, (cell_size>>1)-3, MAKE_COLOR(PLAYER_COLOR_1, PLAYER_COLOR_2));
                        break;
                    case MARKER_EMPTY:
                    default:
                        draw_filled_rect(camera_screen.ts_button_border+x*cell_size, y*cell_size, camera_screen.ts_button_border+x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        break;
                }
            }
        }

        draw_line(camera_screen.ts_button_border+cell_size*FIELD_WIDTH, 0, camera_screen.ts_button_border+cell_size*FIELD_WIDTH, camera_screen.height-1, COLOR_WHITE);
        draw_line(camera_screen.ts_button_border+cell_size*FIELD_WIDTH+1, 0, camera_screen.ts_button_border+cell_size*FIELD_WIDTH+1, camera_screen.height-1, COLOR_BLACK);

        sprintf(str, "%s: %-6d", lang_str(LANG_SOKOBAN_TEXT_LEVEL), sconf.sokoban_level+1);
        draw_string(camera_screen.ts_button_border+cell_size*FIELD_WIDTH+2, 8, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        sprintf(str, "%s: %-6d", lang_str(LANG_SOKOBAN_TEXT_MOVES), moves);
        draw_string(camera_screen.ts_button_border+cell_size*FIELD_WIDTH+2, 8+FONT_HEIGHT, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

        //draw_filled_rect(cell_size*FIELD_WIDTH+2, 8+FONT_HEIGHT*2, camera_screen.width-1, camera_screen.height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));

        if (sokoban_finished()) {
            gui_mbox_init(LANG_SOKOBAN_MSG_FINISH_TITLE, LANG_SOKOBAN_MSG_FINISH_TEXT, MBOX_TEXT_CENTER, NULL);
            sokoban_next_level();
        }
    }

    sprintf(str, "Batt:%3d%%", get_batt_perc());
    draw_txt_string((camera_screen.width-camera_screen.ts_button_border)/FONT_WIDTH-2-9, camera_screen.height/FONT_HEIGHT-1, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
}


static int running = 0;

void gui_module_menu_kbd_process()
{
    running = 0;
	gui_default_kbd_process_menu_btn();
}

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

int _run()
{
    if (!camera_info.state.mode_play)
    {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE, MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, 0);
    }
    else
    {
        running = 1;
        gui_sokoban_init();
    }

    return 0;
}

//---------------------------------------------------------
// PURPOSE:   Perform on-load initialisation
// RETURN VALUE: 1 error, 0 ok
//---------------------------------------------------------
int _module_loader( unsigned int* chdk_export_list )
{
    sconf.sokoban_level = 0;
    config_restore(&conf_info[0], "A/CHDK/MODULES/CFG/sokoban.cfg", 0);
    return 0;
}

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    config_save(&conf_info[0], "A/CHDK/MODULES/CFG/sokoban.cfg", 99000);
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

libsimple_sym _librun =
{
    {
         0, _module_unloader, _module_can_unload, _module_exit_alt, _run
    }
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    -LANG_MENU_GAMES_SOKOBAN,	// Module name
    (int32_t)"Game",

    &_librun.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
