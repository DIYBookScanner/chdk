#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"

extern long link_bss_start;
extern long link_bss_end;
extern void boot();

void startup() {
	
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

//static const int fl_tbl[] = {5000, 6400, 7400, 9100, 10900, 13000, 15700, 20000};
//#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))

// Focus length table in firmware @FFFE2A98 (1.00B)
#define NUM_FL 8
extern int focus_len_table[NUM_FL*3];

// A2200 focal length range is 5 - 20 mm (28 - 112 mm with lense), so CF_EFL = 28/5*10000=56000
#define CF_EFL 56000

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
	
    return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp) {
	
	if (zp < 0) zp = 0;
	else if (zp >= NUM_FL) zp = NUM_FL-1;
	return focus_len_table[zp*3];
}

int get_zoom_x(int zp) {
	
	return get_focal_length(zp)*10/focus_len_table[0];
}

long get_vbatt_min() {
	
	return 3000;	// Measured on the battery without load (3350)
}

long get_vbatt_max() {
	
	return 4150;	// Measured on the battery (4170)
}

