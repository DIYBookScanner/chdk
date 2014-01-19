/*
###########################################################
###########################################################
#############[ FINISHED ] #################################
###########################################################
###########################################################
*/ 


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





// from sd950, zoom steps and sensor size same
//static const int fl_tbl[] = {7700, 9572, 11454, 13683, 16293, 19548, 23495, 28500};

// A2100 
static const int fl_tbl[] = {6400, 6800, 7600, 8800, 10500, 12300, 14100, 18500, 21200, 27100, 30700, 35100, 38400}; 


#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
// sd950 uses wrong value
// #define CF_EFL 60869
// ewavr
// SD990 focal length range is 7,7 - 28,5 mm, 36 - 133 in 35-mm equivalent.
// So, CF_EFL = 36/7.7*10000=46753 or 133/28.5*10000=46666.

// A2100 :: 6x optical zoom lens 36-216mm (35mm equiv), 6.4 - 38.4mm
// CF_EFL = 36/6,4*10000=56250            or     216/38,4*10000= 56250
#define CF_EFL 56250 // split the difference

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp) {
    if (zp<0) return fl_tbl[0];
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1];
    else return fl_tbl[zp];
}

int get_zoom_x(int zp) {
    if (zp<1) return 10;
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
    else return fl_tbl[zp]*10/fl_tbl[0];
}


// A1100 High and Low Levels

long get_vbatt_min()
{
	return 2200;
}

long get_vbatt_max()
{
	return 3150;
}

