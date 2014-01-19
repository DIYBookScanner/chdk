#ifndef GUI_FSELECT_H
#define GUI_FSELECT_H

#include "flt.h"

typedef struct
{
    base_interface_t    base;

    void (*file_select)(int title, const char* prev_dir, const char* default_dir, void (*on_select)(const char *fn));
} libfselect_sym;

//-------------------------------------------------------------------
extern libfselect_sym* libfselect;

//-------------------------------------------------------------------
#endif
