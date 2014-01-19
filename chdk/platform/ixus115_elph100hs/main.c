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


// Focus length table
#define NUM_FL    10   // number of entries in focal length table
#define NUM_DATA  3    // 3 words in each entry, first is FL

extern int focus_len_table[NUM_FL*NUM_DATA];
// Focal length range is 5.0 - 28,0 mm, 20 - 112 in 35-mm equivalent according to Canon's publisehd specs

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 5.0       20       (  20 / 5.0)  * 50 = 200  (min FL)
// 28.0      112      ( 112 / 28.0) * 50 = 200  (max FL)

// So, CF_EFL = 20/5.0*10000=40000 (check : 112/28.0*10000=40000)
// divide by 10 to avoid overflow in get_effective_focal_length()
#define CF_EFL      200
#define CF_EFL_DIV  50


const int zoom_points = NUM_FL ;

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
	return 3280;  // min observed was 3.408, then it died
}

long get_vbatt_max()
{
	return 4057;  // fresh from change (actual was 4.127)
}
