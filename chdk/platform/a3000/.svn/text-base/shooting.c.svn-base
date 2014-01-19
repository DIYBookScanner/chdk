#define PARAM_FILE_COUNTER      0x3A 
#define PARAM_EXPOSURE_COUNTER  0x02

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND8 filter.
// aperture_sizes_table[].id is just a serial number.
const ApertureSize aperture_sizes_table[] = { // PROPCASE 23 at different zoom steps
    {  9, 274, "2.7" }, 
    { 10, 297, "2.8" }, 
    { 11, 321, "3.2" },
    { 12, 349, "3.5" },
    { 13, 379, "4.0" },
    { 14, 413, "4.5" },
    { 15, 447, "5.0" },
    { 16, 483, "5.6" },
	/* With ND Filter*/
	{ 17, 562, "8.0" },
	{ 18, 585, "8.0" },
	{ 19, 609, "9.0" },
	{ 20, 637, "10.0" },
	{ 21, 667, "11.0" },
	{ 22, 701, "13.0" },
	{ 23, 735, "14.0" },
};

const ShutterSpeed shutter_speeds_table[] = {
    { -12, -384, "15", 15000000 },
    { -11, -352, "13", 13000000 },
    { -10, -320, "10", 10000000 },
    {  -9, -288, "8",   8000000 },
    {  -8, -256, "6",   6000000 },
    {  -7, -224, "5",   5000000 },
    {  -6, -192, "4",   4000000 },
    {  -5, -160, "3.2", 3200000 },
    {  -4, -128, "2.5", 2500000 },
    {  -3,  -96, "2",   2000000 },
    {  -2,  -64, "1.6", 1600000 },
    {  -1,  -32, "1.3", 1300000 },
    {   0,    0, "1",   1000000 },
    {   1,   31, "0.8",  800000 },
    {   2,   71, "0.6",  600000 },
    {   3,   87, "0.5",  500000 },
    {   4,  128, "0.4",  400000 }, //not checked for A3000
    {   5,  147, "0.3",  300000 },
    {   6,  178, "1/4",  250000 },
    {   7,  224, "1/5",  200000 }, //not checked for A3000
    {   8,  250, "1/6",  166667 },
    {   9,  291, "1/8",  125000 },
    {  10,  334, "1/10", 100000 },
    {  11,  359, "1/13",  76923 },
    {  12,  376, "1/15",  66667 },
    {  13,  421, "1/20",  50000 },
    {  14,  448, "1/25",  40000 }, //not checked for A3000
    {  15,  480, "1/30",  33333 },
    {  16,  525, "1/40",  25000 },
    {  17,  529, "1/50",  20000 },
    {  18,  574, "1/60",  16667 },
    {  19,  615, "1/80",  12500 },
    {  20,  652, "1/100", 10000 },
    {  21,  672, "1/125",  8000 }, //not checked for A3000
    {  22,  702, "1/160",  6250 },
    {  23,  736, "1/200",  5000 }, //not checked for A3000
    {  24,  761, "1/250",  4000 },
    {  25,  815, "1/320",  3125 },
    {  26,  827, "1/400",  2500 },
    {  27,  864, "1/500",  2000 },
    {  28,  906, "1/640",  1563 },
    {  29,  915, "1/800",  1250 },
    {  30,  971, "1/1000", 1000 },
    {  31,  992, "1/1250",  800 }, //not checked for A3000
    {  32, 1024, "1/1600",  625 }  //not checked for A3000
};

const ISOTable iso_table[] = {
    {  0,     0,  "Auto", -1},
    {  1,   100,   "100", -1},
    {  2,   200,   "200", -1},
    {  3,   400,   "400", -1},
    {  4,   800,   "800", -1},
    {  5,  1600,  "1600", -1}
};        

const CapturemodeMap modemap[] = { // prop 49
	{ MODE_AUTO,               32768  },
	{ MODE_P,                  32772  },
	{ MODE_EASY,               33314  },
	{ MODE_PORTRAIT,           32783  },
	{ MODE_LANDSCAPE,	       32782  },
	{ MODE_NIGHT_SCENE,        32781  },
	{ MODE_KIDS_PETS,          32786  },
	{ MODE_INDOOR,     	       32787  },
	{ MODE_SCN_FACE_SELF_TIMER,16936  },
	{ MODE_SCN_LOWLIGHT,  	   16417  },
	{ MODE_SCN_SUPER_VIVID,	   16934  },
	{ MODE_SCN_POSTER_EFFECT,  16935  },
	{ MODE_SCN_BEACH,          16407  },
	{ MODE_SCN_FOLIAGE,		   16405  },
	{ MODE_SCN_SNOW,           16406  },
    { MODE_SCN_FIREWORK,	   16408  },
    { MODE_SCN_LONG_SHUTTER,   16390  }
};


#include "../generic/shooting.c"

const int dof_tbl[] = {6200, 7780, 9410, 11370, 13790, 16770, 20180, 24800};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>4)&0x3FFF;
    return n;
}

#if defined(CAM_DATE_FOLDER_NAMING)
void get_target_dir_name(char *out)
{
	extern void _GetImageFolder(char*,int,int,int);
	out[0] = 'A';
	_GetImageFolder(out+1,get_file_next_counter(),0x400,time(NULL));
}
#else
long get_target_dir_num() {
	long n;
	
	n = get_file_next_counter();
	n = (n>>18)&0x3FF;
	return n;
}
#endif


int circle_of_confusion = 5; // per http://www.dofmaster.com/digital_coc.html

