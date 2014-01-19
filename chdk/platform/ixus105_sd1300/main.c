#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"


extern long link_bss_start;
extern long link_bss_end;
extern void boot();

long get_sensor_width()
{
    return 6160;          // 1/2.3"
}

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

static const struct {
	int zp, fl;
} fl_tbl[] = {
  {   0,   5000},
  {   1,   6000},
  {   2,   7000},
  {   3,   8000},
  {   4,   9500},
  {   5,   10900},
  {   6,   12800},
  {   7,   15000},
  {   8,   17300},
  {   9,   20000},
};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
// ixus105 focal lenght range 5.0 - 20 mm (35 mm equivalent: 28 - 112 mm)(1/2.3" Type CCD, Scale Factor To 35 mm Equivalent: 5.6)
// 28/5*10000=56666
// 112/20*10000=56666

#define CF_EFL 56666

const int zoom_points = NUM_FL;

static const int fov_tbl[] = {63,54,48,42,36,32,27,23,20,18};
static const int mav_tbl[] = {294,311,348,371,393,418,445,474,500};  // min Av 
static const int xav_tbl[] = {582,599,636,659,681,706,733,762,788};  // max Av 

int get_mav(int zp)
{
 return mav_tbl[zp];
}

int get_xav(int zp)
{
 return xav_tbl[zp];
}

int get_fov(int zp)
{
 if (zp<0) return fov_tbl[0];
 else if (zp>NUM_FL-1) return fov_tbl[NUM_FL-1];
 else return fov_tbl[zp];
}

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp) {
	int i;

	if (zp<fl_tbl[0].zp)
		return fl_tbl[0].fl;
	else if (zp>fl_tbl[NUM_FL-1].zp)
		return fl_tbl[NUM_FL-1].fl;
	else 
		for (i=1; i<NUM_FL; ++i) {
			if (zp==fl_tbl[i-1].zp) 
				return fl_tbl[i-1].fl;
			else if (zp==fl_tbl[i].zp) 
				return fl_tbl[i].fl;
			else if (zp<fl_tbl[i].zp)
				return fl_tbl[i-1].fl+(zp-fl_tbl[i-1].zp)*(fl_tbl[i].fl-fl_tbl[i-1].fl)/(fl_tbl[i].zp-fl_tbl[i-1].zp);
		}
	return fl_tbl[NUM_FL-1].fl;
}

int get_zoom_x(int zp) {
	return get_focal_length(zp)*10/fl_tbl[0].fl;
}

long get_vbatt_min()
{
    return 3000;
}

long get_vbatt_max()
{
    return 4100;
}

