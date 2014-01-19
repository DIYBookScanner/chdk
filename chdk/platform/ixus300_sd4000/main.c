#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"


extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup() {
    long *bss = &link_bss_start;

    //debug_led(1);
    //debug_led(0);

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)) {
        started();
        shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
        *bss++ = 0;

    //debug_led(1);
    //debug_led(0);

    boot();
}

// Focus length table in firmware @0xfffe9718 
#define NUM_FL      64  // 0 - 63, entries in firmware
#define NUM_DATA    3   // 3 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 4.9       28       ( 28/ 4.9) * 49 = 280  (min FL)
// 18.6      105      (105/18.6) * 49 = 276.6  (max FL)
#define CF_EFL      280
#define	CF_EFL_DIV  49

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

/*
int rec_switch_state(void) {
    return (physw_status[1] & 0x02000000);
}
*/

// Battery default min. Voltage
long get_vbatt_min() {
    return 3200;    // ToDo: use real value, this is just a guess
}

// Battery default max. Voltage
long get_vbatt_max() {
    return 4100;    // ToDo: use real value, this is just a guess
}

// NEXT: platform/ixus300_sd4000/sub/100d/boot.c boot()
