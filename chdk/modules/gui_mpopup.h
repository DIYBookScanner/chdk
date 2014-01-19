#ifndef GUI_MPOPUP_H
#define GUI_MPOPUP_H

#include "flt.h"

//-------------------------------------------------------------------

#define MPOPUP_MASK             0x7FFF
#define MPOPUP_CANCEL           0x8000

struct mpopup_item {
        unsigned int            flag;
        int                     text;
};

//-------------------------------------------------------------------

typedef struct
{
    base_interface_t    base;

    void (*show_popup)(struct mpopup_item* popup_actions, const unsigned int flags, void (*on_select)(unsigned int actn));
} libmpopup_sym;

//-------------------------------------------------------------------
extern libmpopup_sym* libmpopup;

//-------------------------------------------------------------------
#endif
