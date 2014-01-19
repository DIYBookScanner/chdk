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

//debug_led(1);
    boot();
}

// Focus length table in firmware @0xfffe297c
#define NUM_FL      15  // 0 - 14, entries in firmware
#define NUM_DATA    3   // 3 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 6.4       36       ( 36/ 6.4) * 64 = 360  (min FL)
// 38.4      216      (216/38.4) * 64 = 360  (max FL)
#define CF_EFL      360
#define	CF_EFL_DIV  64

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
    return 2300;
}

long get_vbatt_max()
{
    return 2550;
}
