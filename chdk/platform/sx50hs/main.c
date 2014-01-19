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

int screen_opened(void) {
	return (physw_status[2] & 0x00000200);
}

int screen_rotated(void) {
	return !(physw_status[2] & 0x00000100);
}


// Focus length table in firmware @ 0xfff4d5c4
#define NUM_FL      201 // 0 - 200, entries in firmware
#define NUM_DATA    1   // 1 int value each entry
extern int focus_len_table[NUM_FL*NUM_DATA];

#define CF_EFL      240
#define CF_EFL_DIV  43

// 4.3       24       ( 24/  4.3) * 43 = 240  (min FL)
// 215      1200      (1200/215) * 43 = 240  (max FL)

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
	return 6450;
}

long get_vbatt_max()
{
	return 8200;
}

