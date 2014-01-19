// TODO this holds and exposure count of some kind, but it only updates when rebooting or switching to play!
#define PARAM_FILE_COUNTER      0x1

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND filter.
// aperture_sizes_table[].id is just a serial number.
// note av96 varies continously with zoom, the following values are just representative
const ApertureSize aperture_sizes_table[] = { // PROPCASE 23
    {  9, 328, "3.2" },
    { 10, 331, "3.5" }, 
    { 11, 379, "4.0" }, 
    { 12, 425, "4.5" },
    { 13, 463, "5.0" },
    { 14, 474, "5.6" },
    { 15, 502, "6.3" },
    { 16, 541, "6.9" },

// The rest are the same physical apertures as above, but with ND:
    { 17, 604, "9.0" },
    { 18, 613, "10.0" },
    { 19, 657, "11.0" },
    { 20, 687, "13.0" },
    { 21, 710, "14.0" },
    { 22, 750, "16.0" },
    { 23, 790, "18.0" },
    { 24, 817, "20.0" },
};

// OLD copied comment!
// TODO copied from 850
// Another set of "mock" values, which can probably
// be derived from the table found at FFB4E258 in FW.
// At the moment, I see no reason to amend it.
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
    {  32, 1021, "1/1600",  625 },
};

const ISOTable iso_table[] = {
//    { -1,     1,    "HI", -1},
    {  0,     0,  "Auto", -1},
    {  1,    80,    "80", -1}, // note, camera does not support 89
    {  2,   100,   "100", -1},
    {  3,   200,   "200", -1},
    {  4,   400,   "400", -1},
    {  5,   800,   "800", -1},
    {  6,  1600,  "1600", -1},
};          

/*
http://www.usa.canon.com/cusa/consumer/products/cameras/digital_cameras/powershot_elph_130_is#Specifications

Shooting Modes
	Auto, P, Portrait, Smart shutter (Smile, Wink self timer, Face Self timer),
    Low light, Fisheye Effect, Miniature Effect, Toy Camera Effect, Monochrome,
    Super Vivid, Poster Effect, Color Accent, Color Swap, Snow, Fireworks, 
    Long Shutter, Stitch assist
	Movie
		1280 x 720 (25 fps), 640 x 480 (30 fps) 
        

canon mode list FF61C088 in 100a

NOTE elph130 does not have "scene" modes, but the distinction is meaningless for chdk
*/
const CapturemodeMap modemap[] = {
    { MODE_LONG_SHUTTER,        32774 },
    { MODE_P,                   32772 },
    { MODE_STITCH,              33293 }, // either direction
    { MODE_MINIATURE,           33330 },
    { MODE_FISHEYE,             33329 },
    { MODE_SCN_TOY_CAMERA,      33333 }, // not really a SCN mode
    { MODE_LOWLIGHT,            32807 },
    { MODE_COLOR_ACCENT,        33315 },
    { MODE_COLOR_SWAP,          33316 },
    { MODE_SCN_MONOCHROME,      33336 },
    { MODE_SUPER_VIVID,         33324 },
    { MODE_POSTER_EFFECT,       33325 },
    { MODE_PORTRAIT,            32787 },
    { MODE_SNOW,                32795 },
    { MODE_FIREWORK,            32797 },
    { MODE_AUTO,                32768 },
    { MODE_SCN_FACE_SELF_TIMER, 33326 },
    { MODE_SMART_SHUTTER,       33327 },
    { MODE_SCN_WINK_SELF_TIMER, 33328 },
// TODO video
};

#include "../generic/shooting.c"

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    return get_exposure_counter();
}
#if defined(CAM_DATE_FOLDER_NAMING)
// ELPH130 camera uses date to name directory
// TODO currently returns something like A/DCIM/101___09/ETC_0112.TMP
// may need different params
void get_target_dir_name(char *out)
{
    static char buf[32];
    extern void _GetImageFolder(char*,int,int,int);
    _GetImageFolder(buf,get_file_next_counter(),CAM_DATE_FOLDER_NAMING,time(NULL));
    strncpy(out,buf,15);
    out[15] = 0;
}
#else
long get_target_dir_num() 
{
    return 0;
}
#endif

// TODO
int circle_of_confusion = 6;

