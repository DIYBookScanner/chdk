#ifndef EDGE_OVERLAY_H
#define EDGE_OVERLAY_H

#include "flt.h"

// if you change this, remember to change the mkdir in main too
#define EDGE_SAVE_DIR "A/CHDK/EDGE"

typedef struct
{
    base_interface_t    base;

	void (*edge_overlay)();
    void (*load_edge_overlay)(const char* fn);
    void (*save_edge_overlay)(void);
} libedgeovr_sym;

extern libedgeovr_sym* libedgeovr;
extern void module_restore_edge(void **buf, int *state);
extern void module_save_edge(void* buf, int state);

#endif
