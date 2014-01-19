#include "camera_info.h"
#include "gui.h"
#include "gui_draw.h"
#include "meminfo.h"
#include "module_load.h"
#include "simple_module.h"

// =========  MODULE INIT =================

static int running = 0;

extern int basic_module_init();

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

int _run()
{
    basic_module_init();

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
         0, 0, _module_can_unload, _module_exit_alt, _run
    }
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Module Inspector",// Module name
    (int32_t)"Show list of loaded modules",

    &_librun.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/

/*************** GUI MODULE *******************/

#include "gui_mbox.h"
#include "keyboard.h"
#include "stdlib.h"

void gui_module_menu_kbd_process();
int gui_module_kbd_process();
void gui_module_draw();

gui_handler GUI_MODE_MODULE_INSPECTOR = 
/*GUI_MODE_MODULE_INSPECTOR*/   { GUI_MODE_MODULE, gui_module_draw, gui_module_kbd_process, gui_module_menu_kbd_process, 0 };

int modinspect_redraw;
gui_handler *modinspect_old_guimode;

static void modinspect_unload_cb(unsigned int btn)
{
    if (btn==MBOX_BTN_YES)
    {
        running = 0;
        module_exit_alt();
        gui_set_mode(modinspect_old_guimode);	// if core gui - return to it
    }
    modinspect_redraw=2;
}

int gui_module_kbd_process()
{
    switch (kbd_get_autoclicked_key())
    {
    case KEY_SET:
        modinspect_redraw = 2;
        break;
    case KEY_DISPLAY:
        gui_mbox_init( (int)"Module Inspector", (int)"Unload all modules?",
            MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, modinspect_unload_cb);
        break;
    }
    return 0;
}

//-------------------------------------------------------------------

int basic_module_init()
{
    running = 1;
    modinspect_redraw = 2;
    modinspect_old_guimode = gui_set_mode(&GUI_MODE_MODULE_INSPECTOR);
    return 1;
}

void gui_module_menu_kbd_process()
{
    running = 0;
    gui_set_mode(modinspect_old_guimode);
}

static void gui_mem_info(char *typ, cam_meminfo *meminfo, int showidx)
{
    char txt[50];
    sprintf(txt,"%-5s: %08x-%08x: %d",typ,meminfo->start_address, meminfo->end_address, meminfo->total_size);
    draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH, 5+showidx,  txt,       MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
	sprintf(txt,"alloc: now=%d(%d) max=%d", meminfo->allocated_size, meminfo->allocated_count, meminfo->allocated_peak);
    draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH, 6+showidx,  txt,       MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
	sprintf(txt,"free:  now=%d(%d) max=%d", meminfo->free_size, meminfo->free_block_count, meminfo->free_block_max_size);
    draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH, 7+showidx,  txt,       MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
}

void gui_module_draw()
{
    int idx, showidx;

    if (modinspect_redraw) {

    	draw_filled_rect(0, 0, camera_screen.width-1, camera_screen.height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
        draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH+5, 0,  "*** Module Inspector ***", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH, 2,  "Idx Name         Addr       Size", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

		showidx=0;
		for ( idx=0; idx<MAX_NUM_LOADED_MODULES; idx++)
		{
            module_entry* mod = module_get_adr(idx);;
			if (mod == 0) continue;

			char txt[50];
		    sprintf(txt,"%02d: %-12s %08x - %d bytes", idx, mod->modulename, (unsigned)mod->hdr, mod->hdr->reloc_start);
        	draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH, 3+showidx, txt, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
			showidx++;
		}

        draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH+1, 4+showidx,  "SET-redraw, DISP-unload_all, MENU-exit",       MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

    	cam_meminfo meminfo;

        // Display Canon heap memory info
        // amount of data displayed may vary depending on GetMemInfo implementation
        memset(&meminfo,0,sizeof(meminfo));
        GetMemInfo(&meminfo);
        gui_mem_info("MEM", &meminfo, showidx);
        showidx += 3;

        // Display ARAM memory info (only if enabled)
        memset(&meminfo,0,sizeof(meminfo));
        if (GetARamInfo(&meminfo))
        {
            gui_mem_info("ARAM", &meminfo, showidx);
            showidx += 3;
		}

        // Display EXMEM memory info (only if enabled)
        memset(&meminfo,0,sizeof(meminfo));
        if (GetExMemInfo(&meminfo))
        {
            gui_mem_info("EXMEM", &meminfo, showidx);
		}
	}

	modinspect_redraw = 0;
}

