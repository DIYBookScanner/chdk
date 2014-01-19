#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"   //ASM1989 debuging
#include "platform.h"//ASM1989 debuging
//#define PARAM_FILE_COUNTER      0x02  // with 02 worked changin the script but??

#define PARAM_FILE_COUNTER      0x3A

#define PARAM_EXPOSURE_COUNTER  0x02

#include "platform.h"
#include "stdlib.h"
//No zoom 3.1 3.5 4.0 4.5 5.0 5.6 6.3 7.1 8.0
//maz zoom 5.9 7.1 8.0
 //ASM1989 sx210 values
const ApertureSize aperture_sizes_table[] = {
	{  9, 343, "3.4" },
    { 10, 352, "3.5" },
	{ 11, 384, "4.0" },
	{ 12, 416, "4.5" },
	{ 13, 448, "5.0" },
	{ 14, 480, "5.6" },
	{ 15, 512, "6.3" },
	{ 16, 544, "7.1" },
	{ 17, 576, "8.0" }
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
	{   1,   32, "0.8",  800000 },
	{   2,   64, "0.6",  600000 },
	{   3,   96, "0.5",  500000 },
	{   4,  128, "0.4",  400000 },
	{   5,  160, "0.3",  300000 },
	{   6,  192, "1/4",  250000 },
	{   7,  224, "1/5",  200000 },
	{   8,  256, "1/6",  166667 },
	{   9,  288, "1/8",  125000 },
	{  10,  320, "1/10", 100000 },
	{  11,  352, "1/13",  76923 },
	{  12,  384, "1/15",  66667 },
	{  13,  416, "1/20",  50000 },
	{  14,  448, "1/25",  40000 },
	{  15,  480, "1/30",  33333 },
	{  16,  512, "1/40",  25000 },
	{  17,  544, "1/50",  20000 },
	{  18,  576, "1/60",  16667 },
	{  19,  608, "1/80",  12500 },
	{  20,  640, "1/100", 10000 },
	{  21,  672, "1/125",  8000 },
	{  22,  704, "1/160",  6250 },
	{  23,  736, "1/200",  5000 },
	{  24,  768, "1/250",  4000 },
	{  25,  800, "1/320",  3125 },
	{  26,  832, "1/400",  2500 },
	{  27,  864, "1/500",  2000 },
	{  28,  896, "1/640",  1563 },
	{  29,  928, "1/800",  1250 },
	{  30,  960, "1/1000", 1000 },
	{  31,  992, "1/1250",  800 },
	{  32, 1024, "1/1600",  625 },
	{  33, 1056, "1/2000",  500 },
	{  34, 1088, "1/2500",  400 },
	{  35, 1120, "1/3200",  313 },
};


//BerndR 11.03.10
const ISOTable iso_table[] = {
   { -1,    1,   "HI", -1},
   {  0,    0, "Auto", -1},
   {  1,  125 , "125", -1},
   {  2,  200,  "200", -1},
   {  3,  400,  "400", -1},
   {  4,  800,  "800", -1},
   {  5, 1600, "1600", -1},
   {  6, 3200, "3200", -1},
};

/*
http://www.usa.canon.com/cusa/consumer/products/cameras/digital_cameras/powershot_sd4500_is#Specifications
Shooting Modes
Auto, P, Portrait, Kids&Pets, Smart Shutter, High-speed Burst, Best Image Selection, Handheld Night Scene, Low Light, Super Vivid, Poster Effect, Color Accent, Color Swap, Fish-eye Effect, Miniature Effect, Beach, Foliage, Snow, Fireworks, Long Shutter, Stitch Assist, Movie
*/
const CapturemodeMap modemap[] = {
    { MODE_AUTO,                32768  },
    { MODE_P,                   32772  },
    { MODE_PORTRAIT,            32783  },
    { MODE_KIDS_PETS,           32786  },
    { MODE_SMART_SHUTTER,       33321  },
    { MODE_HIGHSPEED_BURST,     33288  },
    { MODE_BEST_IMAGE,          33289  },
    { MODE_NIGHT_SCENE,         33325  }, // NOTE handheld night scene
    { MODE_LOWLIGHT,            32801  },
    { MODE_SUPER_VIVID,         33318  },
    { MODE_POSTER_EFFECT,       33319  },
    { MODE_COLOR_ACCENT,        33309  },
    { MODE_COLOR_SWAP,          33310  },
    { MODE_FISHEYE,             33323  },
    { MODE_MINIATURE,           33324  },
    { MODE_BEACH,               32791  },
    { MODE_FOLIAGE,             32789  },
    { MODE_SNOW,                32790  },
    { MODE_FIREWORK,            32792  },
    { MODE_LONG_SHUTTER,        32774  },
    { MODE_STITCH,              33292  },
    { MODE_VIDEO_STD,           2614  },
    { MODE_VIDEO_SUPER_SLOW,    2619  },
    { MODE_VIDEO_MINIATURE,     2620  },
    { MODE_VIDEO_COLOR_ACCENT,  2612  },
    { MODE_VIDEO_COLOR_SWAP,    2613  },
};

#include "../generic/shooting.c"

long get_file_next_counter() {
	return get_file_counter();
}

long get_target_file_num() {
	long n;


	n = get_file_next_counter();

    n = (n>>4)&0x3FFF;

    //n+=22;
	return n;
}
/*
long get_target_dir_num() {
	long n;

	n = get_file_next_counter();

	n = (n>>18)&0x3FF;

	//n+=22;
	//n=n/1000;
	//n+=101;
	return n;
}*/


#if defined(CAM_DATE_FOLDER_NAMING)
// SX30 uses date to name directory
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

int circle_of_confusion = 5;



// not used ? -> CAM_DRAW_EXPOSITION
/*
char* shooting_get_tv_str()
{
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));	// 262 for DiGiC III
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id >= tvv)
	    return (char*)shutter_speeds_table[i].name;
    }
    return (void*)"?";
}

char* shooting_get_av_str()
{
    short int avv;
    long i;
    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));	// 23 for DiGiC III
    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == avv)
	    return (char*)aperture_sizes_table[i].name;
    }
    return (char*) "?";
}

char* shooting_get_iso_str()
{
    short int isov;
    long i;
    _GetPropertyCase(PROPCASE_ISO_MODE, &isov, sizeof(isov));
    for (i=0;i<ISO_SIZE;i++){
   if (iso_table[i].prop_id == isov)
       return (char*)iso_table[i].name;
    }
    return (char*) "?";
}

*/
