#include "camera_info.h"
#include "conf.h"
#include "lang.h"
#include "gui_lang.h"

//-------------------------------------------------------------------
// String list now is generated automatically from .lng files
// Please add new lines directly to english.lng and please try to keep ids serial
#include "lang_str.h"

//-------------------------------------------------------------------
void gui_lang_init() {
    // this function do init and then map preparsed
    lang_map_preparsed_from_mem( gui_lang_default, GUI_LANG_ITEMS );

    if (conf.lang_file && *conf.lang_file) {
        lang_load_from_file(conf.lang_file);
    }
}

//-------------------------------------------------------------------
