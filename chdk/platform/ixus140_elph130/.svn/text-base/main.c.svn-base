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

    // sanity check (pointless with automemiso)
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
	started();
	shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
	*bss++ = 0;


    boot();
}

/*
1/2.3 sensor 
*/

// Focus length table in firmware @FFF4A3E0
#define NUM_FL      101 // 101 zoom steps
#define NUM_DATA    2   // 2 words each entry, FL in MM*1000, 100
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 5         28       ( 28/5) * 60 = 336  (min FL)
// 40        224      (224/40) * 60 = 336  (max FL)
#define CF_EFL      336
#define	CF_EFL_DIV  60

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

// uses NB-11L, should be similar to other single cell li-ion
long get_vbatt_min()
{
    return 3250; // shutdown is around 3.1
}

long get_vbatt_max()
{
    return 4000;
}
