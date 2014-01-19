#ifndef HEXBOX_H
#define HEXBOX_H

#include "flt.h"

// enforce word alignment
#define HEXBOX_FLAG_WALIGN 0x10

//#define HEXBOX_FLAG_DECIMAL 0x20

typedef struct
{
    base_interface_t    base;

    int (*hexbox_init)(int *num, char *title, int flags);
} libhexbox_sym;

extern libhexbox_sym* libhexbox;

#endif
