#include "simple_module.h"

// =========  MODULE INIT =================

static int running = 0;

void gui_module_menu_kbd_process()
{
    running = 0;
    gui_default_kbd_process_menu_btn();
}

/***************** BEGIN OF AUXILARY PART *********************
ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
**************************************************************/

int _run()
{
    running = 1;
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

libsimple_sym _librun =
{
    {
        0,
        0,
        _module_can_unload,
        _module_exit_alt,
        _run
    }
};

/*************** END OF AUXILARY PART *******************/
