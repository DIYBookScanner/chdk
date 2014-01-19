
#define PARAM_FILE_COUNTER      0x3B   /* a1200 ok */
#define PARAM_EXPOSURE_COUNTER  0x02   /* a1200 ok */

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {    // A1200 propcase_av 23
    {  9, 295, "2.8" },
    { 10, 319, "3.2" },
    { 11, 338, "3.5" },
    { 12, 366, "3.5" },
    { 13, 393, "4.0" },
    { 14, 423, "4.5" },
    { 15, 456, "5.0" },
    { 16, 501, "5.9" },
  // the rest are the same physical apertures as above, but with ND forced in by setting fireworks scene mode
        { 17, 572, "8.0" },
        { 18, 596, "9.0" },
        { 19, 615, "10.0" },
        { 20, 643, "10.0" },
        { 21, 670, "11.0" },
        { 22, 700, "13.0" },
        { 22, 733, "14.0" },
        { 23, 778, "17.0" },
};

const ShutterSpeed shutter_speeds_table[] = {   // A1200 propcase_tv 266
    { -12, -384, "15", 15000000 },  //65152
    { -11, -352, "13", 13000000 },  //65184
    { -10, -320, "10", 10000000 },  //65216
    {  -9, -288, "8",   8000000 },  //65248
    {  -8, -256, "6",   6000000 },  //65280
    {  -7, -224, "5",   5000000 },  //65312
    {  -6, -192, "4",   4000000 },  //65344
    {  -5, -160, "3.2", 3200000 },  //65376
    {  -4, -128, "2.5", 2500000 },  //65408
    {  -3,  -96, "2",   2000000 },  //65440
    {  -2,  -64, "1.6", 1600000 },  //
    {  -1,  -32, "1.3", 1300000 },  //
    {   0,    0, "1",   1000000 },  //
    {   1,   32, "0.8",  800000 },  //
    {   2,   64, "0.6",  600000 },  //
    {   3,   96, "0.5",  500000 },  //
    {   4,  128, "0.4",  400000 },  //
    {   5,  160, "0.3",  300000 },  //
    {   6,  192, "1/4",  250000 },  //
    {   7,  224, "1/5",  200000 },  //
    {   8,  256, "1/6",  166667 },  //
    {   9,  288, "1/8",  125000 },  //
    {  10,  320, "1/10", 100000 },  //
    {  11,  352, "1/13",  76923 },  //
    {  12,  384, "1/15",  66667 },  //
    {  13,  412, "1/20",  50000 },  //
    {  14,  448, "1/25",  40000 },  //
    {  15,  480, "1/30",  33333 },  //
    {  16,  512, "1/40",  25000 },  //
    {  17,  544, "1/50",  20000 },  //
    {  18,  576, "1/60",  16667 },  //
    {  19,  608, "1/80",  12500 },  //
    {  20,  640, "1/100", 10000 },  //
    {  21,  672, "1/125",  8000 },  //
    {  22,  704, "1/160",  6250 },  //
    {  23,  736, "1/200",  5000 },  //
    {  24,  768, "1/250",  4000 },  //
    {  25,  800, "1/320",  3125 },  //
    {  26,  832, "1/400",  2500 },  //
    {  27,  864, "1/500",  2000 },  //
    {  28,  896, "1/640",  1563 },  //
    {  29,  928, "1/800",  1250 },  //
    {  30,  960, "1/1000", 1000 },  //
    {  31,  992, "1/1250",  800 },  //
    {  32, 1024, "1/1600",  625 },  //
};

const ISOTable iso_table[] = {      // a1200 propcase_iso_mode 149
    {  0,    0, "Auto", -1},
    {  1,   80,   "80", -1},
    {  2,  100,  "100", -1},
    {  3,  200,  "200", -1},
    {  4,  400,  "400", -1},
    {  5,  800,  "800", -1},
    {  6, 1600, "1600", -1},
};

const CapturemodeMap modemap[] = {              // a1200 ok
    { MODE_P,               32772 },
    { MODE_LIVE,                33332 },
    { MODE_AUTO,                32768 },
    { MODE_EASY,                33314 },
    { MODE_DISCREET,            32817 },
    { MODE_BLUR_REDUCTION,          16435 },
    { MODE_SCN_PORTRAIT,            16399 },
    { MODE_SCN_LANDSCAPE,           16398 },
    { MODE_SCN_KIDS_PETS,           16402 },
    { MODE_SCN_LOWLIGHT,            16417 },
    { MODE_SCN_BEACH,           16407 },
    { MODE_SCN_FOLIAGE,         16405 },
    { MODE_SCN_SNOW,            16406 },
    { MODE_SCN_FIREWORK,            16408 },
    { MODE_SCN_LONG_SHUTTER,        16390 },
    { MODE_SCN_FACE_SELF_TIMER,     16936 },
    { MODE_SCN_SMART_SHUTTER,       16937 },
    { MODE_SCN_WINK_SELF_TIMER,     16938 },
    { MODE_SCN_FISHEYE,         8747 },
    { MODE_SCN_MINIATURE,           8748 },
    { MODE_SCN_TOY_CAMERA,          8751 },
    { MODE_SCN_MONOCHROME,          8754 },
    { MODE_SCN_SUPER_VIVID,         8742 },
    { MODE_SCN_POSTER_EFFECT,       8743 },
    { MODE_VIDEO_STD,           2621 },
    { MODE_VIDEO_MINIATURE,         2627 },
} ;

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
void get_target_dir_name(char *out) {

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

int circle_of_confusion = 5;
