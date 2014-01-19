#ifndef GUI_PALETTE_H
#define GUI_PALETTE_H

#include "flt.h"

//-------------------------------------------------------------------

#define PALETTE_MODE_DEFAULT    0
#define PALETTE_MODE_SELECT     1

//-------------------------------------------------------------------

typedef struct
{
    base_interface_t    base;

    void (*show_palette)(int mode, color st_color, void (*on_select)(color clr));
} libpalette_sym;

//-------------------------------------------------------------------
extern libpalette_sym* libpalette;

//-------------------------------------------------------------------
#endif
