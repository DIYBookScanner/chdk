#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"

extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup()
{
    long *bss = &link_bss_start;

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
        started();
        shutdown();
    }
    // initialize .bss senment
    while (bss<&link_bss_end)
        *bss++ = 0;
    boot();
}

#define NUM_FL      127 // 0 - 126, entries in firmware
#define NUM_DATA    2   // 2 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 5.0       28       ( 28/ 5.0) * 50 = 280  (min FL)
// 80.0      448      (448/80.0) * 50 = 280  (max FL)
#define CF_EFL      280
#define	CF_EFL_DIV  50

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/CF_EFL_DIV;
}

int get_focal_length(int zp) {
    if (zp < 0) zp = 0;
    else if (zp >= NUM_FL) zp = NUM_FL-1;
    return focus_len_table[zp*NUM_DATA];
}

int get_zoom_x(int zp) {
    return get_focal_length(zp)*10/focus_len_table[0];
}

long get_vbatt_min()
{
    return 2200; // Camera shutdown
}

long get_vbatt_max()
{
    return 2700; // Fully charged
}
