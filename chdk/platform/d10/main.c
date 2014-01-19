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
D10 from exif
1/2.3 in sensor 

6.2/34	f2.8
7.2 	f3.2
8.3 	f3.2
9.7		f3.5
11.6	f4.0
14.3	f4.5
18.6/104 f4.9

CF_EFL ~54800-56000
*/

// Focus length table in firmware @0xfffe2a8c
#define NUM_FL      7   // 0 - 6, entries in firmware
#define NUM_DATA    3   // 3 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 6.2       35       ( 35/ 6.2) * 62 = 350  (min FL)
// 18.6      105      (105/18.6) * 62 = 350  (max FL)
#define CF_EFL      350
#define	CF_EFL_DIV  62

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

// uses NB-6L, similar specs to NB-5L, copied from sd990 below 
// canon icon blinking at ~3.47, still running at <3.38
long get_vbatt_min()
{
    return 3425; // hnikesch on forum
}

long get_vbatt_max()
{
    return 4000; // fresh off charger slightly greater
}
