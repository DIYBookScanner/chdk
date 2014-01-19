#define PARAM_FILE_COUNTER      0x3a
#define PARAM_EXPOSURE_COUNTER  0x02

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
	{  9, 288,  "2.8" },
	{ 10, 320,  "3.2" },
	{ 11, 352,  "3.5" },
	{ 12, 384,  "4.0" },
	{ 13, 416,  "4.5" },
	{ 14, 448,  "5.0" },
	{ 15, 480,  "5.6" },
	{ 16, 512,  "6.3" },
	{ 17, 544,  "7.1" },
	{ 18, 576,  "8.0" },
	{ 19, 608,  "9.0" },
	{ 20, 640, "10.0" },
	{ 21, 672, "11.0" },
	{ 22, 704, "13.0" },
	{ 23, 736, "14.0" },
	{ 24, 768, "16.0" },
};

const ShutterSpeed shutter_speeds_table[] = {
	{ -18, -576, "60", 60000000 },
	{ -17, -544, "50", 50000000 },
	{ -16, -512, "40", 40000000 },
	{ -15, -480, "30", 30000000 },
	{ -14, -448, "25", 25000000 },
	{ -13, -416, "20", 20000000 },
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
	{  36, 1152, "1/4000",  250 },
};

const ISOTable iso_table[] = {
//	{ -1,    1,    "HI", -1},
	{  0,    0, " Auto", -1},
	{  1,  100,   "100", -1},
	{  2,  125,   "125", -1},
	{  3,  160,   "160", -1},
	{  4,  200,   "200", -1},
	{  5,  250,   "250", -1},
	{  6,  320,   "320", -1},
	{  7,  400,   "400", -1},
	{  8,  500,   "500", -1},
	{  9,  640,   "640", -1},
	{ 10,  800,   "800", -1},
	{ 11, 1000,  "1000", -1},
	{ 12, 1250,  "1250", -1},
	{ 13, 1600,  "1600", -1},
	{ 14, 2000,  "2000", -1},
	{ 15, 2500,  "2500", -1},
	{ 16, 3200,  "3200", -1},
	{ 17, 4000,  "4000", -1},
	{ 18, 5000,  "5000", -1},
	{ 19, 6400,  "6400", -1},
	{ 20, 8000,  "8000", -1},
	{ 21,10000, "10000", -1},
	{ 22,12800, "12800", -1},
};          

/*
http://www.usa.canon.com/cusa/consumer/products/cameras/digital_cameras/powershot_g1_x#Specifications
Shooting Modes
	C1, C2, M, Av, Tv, P, Auto, SCN, Creative Filters, Movie

SCN Scene Modes:
    Movie Digest, Portrait, Landscape, Kids & Pets, Sports, Smart Shutter, High-Speed Burst HQ, 
    Handheld Night Scene, Beach, Underwater, Foliage, Snow, Fireworks, Stitch Assist
    
Creative Filters:
    High Dynamic Range, Nostalgic, Fish-eye Effect, Miniature Effect, Toy Camera Effect, 
    Monochrome, Super Vivid, Poster Effect, Color Accent, Color Swap

Movie Modes:
	Standard, iFrame Movie

Smart Shutter Modes:
	Smile, Wink Self-timer, Face Self-timer
*/
// G1X modelist table found @0xff09ab04 (firmware 1.00f)
const CapturemodeMap modemap[] = {
	{ MODE_M,                  32769  },
	{ MODE_AV,                 32770  },
	{ MODE_TV,                 32771  },
	{ MODE_P,                  32772  },
	{ MODE_AUTO,               32768  },

    { MODE_SCN_HIGHSPEED_BURST,16393  },
    { MODE_VIDEO_MOVIE_DIGEST, 16950  },
    { MODE_PORTRAIT,           16400  },
	{ MODE_LANDSCAPE,          16399  },
    { MODE_SCN_KIDS_PETS,      16403  },
	{ MODE_NIGHT_SCENE,        16942  },
	{ MODE_SCN_BEACH,          16408  },
	{ MODE_SCN_FOLIAGE,        16406  },
	{ MODE_SCN_SNOW,           16407  },
	{ MODE_SCN_FIREWORK,       16409  },
	{ MODE_SCN_UNDERWATER,     16410  },
	{ MODE_SCN_SPORT,          16903  },
	{ MODE_SCN_STITCH,         16909  },

	{ MODE_SCN_NOSTALGIC,       8742  },
	{ MODE_SCN_FISHEYE,         8748  },
	{ MODE_SCN_MINIATURE,       8749  },
	{ MODE_SCN_HDR,             8751  },
	{ MODE_SCN_TOY_CAMERA,      8752  },
	{ MODE_SCN_MONOCHROME,      8755  },
	{ MODE_SCN_SUPER_VIVID,     8743  },
	{ MODE_SCN_POSTER_EFFECT,   8744  },
	{ MODE_SCN_COLOR_ACCENT,    8734  },
	{ MODE_SCN_COLOR_SWAP,      8735  },

	{ MODE_SCN_SMART_SHUTTER,  16938  },
    { MODE_SCN_FACE_SELF_TIMER,16937  },
    { MODE_SCN_WINK_SELF_TIMER,16939  },

    { MODE_VIDEO_IFRAME_MOVIE,  2629  },
//    { MODE_VIDEO_SUPER_SLOW,    2627  },
	{ MODE_VIDEO_STD,           2622  },
};

#include "../generic/shooting.c"

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
// G1X uses date to name directory
void get_target_dir_name(char *out)
{
	extern void _GetImageFolder(char*,int,int,int);
	_GetImageFolder(out,get_file_next_counter(),0x400,time(NULL));
}
#else
long get_target_dir_num() {
	long n;
	
	n = get_file_next_counter();
	n = (n>>18)&0x3FF;
	return n;
}
#endif

int circle_of_confusion = 16;   // calculated at http://www.dofmaster.com/digital_coc.html
