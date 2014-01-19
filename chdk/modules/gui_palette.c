#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "conf.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"

#include "gui_palette.h"
#include "module_def.h"

void gui_module_menu_kbd_process();
int gui_palette_kbd_process();
void gui_palette_draw();

gui_handler GUI_MODE_PALETTE_MODULE = 
/*GUI_MODE_PALETTE*/    { GUI_MODE_PALETTE, gui_palette_draw, gui_palette_kbd_process, gui_module_menu_kbd_process, 0 };

//-------------------------------------------------------------------
static int running = 0;
static color cl;
static int palette_mode;
static void (*palette_on_select)(color clr);
static int gui_palette_redraw;

//-------------------------------------------------------------------
void gui_palette_init(int mode, color st_color, void (*on_select)(color clr))
{
    running = 1;
    cl = st_color;
    palette_mode = mode;
    palette_on_select = on_select;
    gui_palette_redraw = 1;
    gui_set_mode(&GUI_MODE_PALETTE_MODULE);
}

//-------------------------------------------------------------------
int gui_palette_kbd_process() {
    switch (kbd_get_autoclicked_key())
    {
        case KEY_DOWN:
            cl = (((cl+16)&0xf0)|(cl&0x0f));
            gui_palette_redraw = 1;
            break;
        case KEY_UP:
            cl = (((cl-16)&0xf0)|(cl&0x0f));
            gui_palette_redraw = 1;
            break;
        case KEY_LEFT:
            cl = ((cl&0xf0)|((cl-1)&0x0f));
            gui_palette_redraw = 1;
            break;
        case KEY_RIGHT:
            cl = ((cl&0xf0)|((cl+1)&0x0f));
            gui_palette_redraw = 1;
            break;
        case KEY_SET:
            if (palette_mode == PALETTE_MODE_SELECT)
            {
                if (palette_on_select) 
                    palette_on_select(cl);
                gui_module_menu_kbd_process();
            }
            break;
    }
    return 0;
}

//-------------------------------------------------------------------
#define CELL_SIZE           13
#define BORDER_SIZE         8
#define CELL_ZOOM           6
#define DISP_LEFT           BORDER_SIZE
#define DISP_RIGHT          (BORDER_SIZE + CELL_SIZE * 16)
#define DISP_TOP            (FONT_HEIGHT + BORDER_SIZE)
#define DISP_BOTTOM         (FONT_HEIGHT + BORDER_SIZE + CELL_SIZE * 16)

void gui_palette_draw() {
    unsigned int x, y, xl, xr;
    color c;
    static char buf[64];

    xl = camera_screen.ts_button_border;
    xr = camera_screen.width - camera_screen.ts_button_border;

    if (gui_palette_redraw)
    {
        // Draw top text line - current color + instructions
        draw_filled_rect(xl, 0, xr, FONT_HEIGHT-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
        draw_string(xr-29*FONT_WIDTH, 0, "    Use \x18\x19\x1b\x1a to change color ", MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
        sprintf(buf, " %s: 0x%02hX", lang_str(LANG_PALETTE_TEXT_COLOR), (unsigned char)cl);
        draw_string(xl, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

        // Draw Palette color boxes
        c = COLOR_BLACK;
        for (y=DISP_TOP; y<DISP_BOTTOM; y+=CELL_SIZE)
        {
            for (x=DISP_LEFT; x<DISP_RIGHT; x+=CELL_SIZE, c+=MAKE_COLOR(1,0))
            {
                draw_filled_rect(xl+x, y, xl+x+CELL_SIZE, y+CELL_SIZE, c);
            }
        }

        // Draw gray borders
        draw_rect_thick(xl, DISP_TOP-BORDER_SIZE, xr-1, camera_screen.height-1, COLOR_GREY, BORDER_SIZE); // outer border
        draw_filled_rect(xl+DISP_RIGHT+1, DISP_TOP, xl+DISP_RIGHT+BORDER_SIZE, DISP_BOTTOM, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //middle

        // Co-ordinate of selected color
        y = DISP_TOP + ((cl>>4)&0x0F) * CELL_SIZE;
        x = DISP_LEFT + (cl&0x0F) * CELL_SIZE;

        // Highlight selected color
        draw_filled_rect_thick(xl+x-CELL_ZOOM, y-CELL_ZOOM, xl+x+CELL_SIZE+CELL_ZOOM, y+CELL_SIZE+CELL_ZOOM, MAKE_COLOR(cl, COLOR_RED), 2);

        // Fill 'sample' area with selected color
        draw_filled_rect(xl+DISP_RIGHT+BORDER_SIZE+1, DISP_TOP, xr-BORDER_SIZE-1, DISP_BOTTOM, MAKE_COLOR(cl, COLOR_WHITE));

        gui_palette_redraw = 0;
    }
}

void gui_module_menu_kbd_process()
{
    running = 0;
    gui_default_kbd_process_menu_btn();
}

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
**************************************************************/

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

libpalette_sym _libpalette =
{
    {
         0, 0, _module_can_unload, _module_exit_alt, 0
    },

    gui_palette_init
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    GUI_PALETTE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Palette",					// Module name
    0,

    &_libpalette.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
