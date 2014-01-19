#define PARAM_FILE_COUNTER      0x3b		// OK
#define PARAM_EXPOSURE_COUNTER  0x02		// OK

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
	{  9, 200, "2.0" },
	{ 10, 224, "2.2" },
	{ 11, 256, "2.5" },
	{ 12, 288, "2.8" },
	{ 13, 320, "3.2" },
	{ 14, 352, "3.5" },
	{ 15, 384, "4.0" },
	{ 16, 416, "4.5" },
	{ 17, 448, "5.0" },
	{ 18, 480, "5.6" },
	{ 19, 512, "6.3" },
	{ 20, 544, "7.1" },
	{ 21, 576, "8.0" },
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
	{  36, 1152, "1/4000",  250 },
};

const ISOTable iso_table[] = {
//	{ -1,    1,   "HI", -1},
	{  0,    0, "Auto", -1},
	{  1,  100,  "100", -1},
	{  2,  200,  "200", -1},
	{  3,  400,  "400", -1},
	{  4,  800,  "800", -1},
	{  5, 1600, "1600", -1},
	{  6, 3200, "3200", -1},
};          

/*
http://www.usa.canon.com/cusa/consumer/products/cameras/digital_cameras/powershot_elph_500_hs#Specifications
Shooting Modes
    P, Auto, Av, Tv, Movie Digest, Portrait, Kids & Pets, Smart Shutter, 
    High-speed Burst, Best Image Selection, Handheld Night Scene, Low Light, 
    Fish-eye Effect, Miniature Effect, Toy Camera Effect, Creative Light Effect, 
    Monochrome, Super Vivid, Poster Effect, Color Accent, Color Swap, 
    Beach, Foliage, Snow, Fireworks, Movie

Smart Shutter Modes:
    Smile, Wink Self-timer, Face Self-Timer

Movie Modes:
    Standard, iFrame Movie, Super Slow Motion Movie, Miniature Effect for Movies (Videos are recorded by pressing the movie button)

Photo Effects
    My colors Off, Vivid, Neutral, Sepia, Black & White, Positive Film, 
    Lighter Skin, Darker Skin, Vivid Blue, Vivid Green, Vivid Red, 
    Custom Color adjustment of contrast, sharpness, saturation, red, green, blue and skin tone are available
*/
// IXUS 310 HS modelist table found @0xff4ce6f0 (firmware 1.00a)
const CapturemodeMap modemap[] = {
	{ MODE_TV,                  32771 },
	{ MODE_AV,                  32770 },
	{ MODE_P,                   32772 },
	{ MODE_AUTO,                32768 },

    { MODE_PORTRAIT,            32783 },
    { MODE_KIDS_PETS,           32786 },
    { MODE_SCN_SMART_SHUTTER,   33321 },
    { MODE_SCN_WINK_SELF_TIMER, 33322 },
    { MODE_SCN_FACE_SELF_TIMER, 33320 },
    { MODE_SCN_HIGHSPEED_BURST, 33288 },
    { MODE_SCN_BEST_IMAGE,      33289 },
    { MODE_NIGHT_SCENE,         33325 },
    { MODE_LOWLIGHT,            32801 },
    { MODE_SCN_FISHEYE,         33323 },
    { MODE_SCN_MINIATURE,       33324 },
    { MODE_SCN_TOY_CAMERA,      33327 },
    { MODE_SCN_CREATIVE_EFFECT, 33297 },
    { MODE_SCN_MONOCHROME,      33330 },
    { MODE_SCN_SUPER_VIVID,     33318 },
    { MODE_SCN_POSTER_EFFECT,   33319 },
    { MODE_COLOR_ACCENT,        33309 },
    { MODE_COLOR_SWAP,          33310 },
    { MODE_SCN_BEACH,           32791 },
    { MODE_SCN_FOLIAGE,         32789 },
    { MODE_SCN_SNOW,            32790 },
    { MODE_SCN_FIREWORK,        32792 },

    { MODE_VIDEO_MOVIE_DIGEST,  33333 },
    { MODE_VIDEO_IFRAME_MOVIE,   2628 },
    { MODE_VIDEO_SUPER_SLOW,     2626 },
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
// IXUS 310 HS uses date to name directory
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

int circle_of_confusion = 5;   // calculated at http://www.dofmaster.com/digital_coc.html
