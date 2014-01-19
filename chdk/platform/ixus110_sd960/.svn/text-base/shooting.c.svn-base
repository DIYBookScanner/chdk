#define PARAM_FILE_COUNTER      0x38 // OK

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND filter.
// aperture_sizes_table[].id is just a serial number.
const ApertureSize aperture_sizes_table[] = { // PROPCASE 23
    {  9, 290, "2.8" }, // wide angle
    { 10, 307, "3.2" },
    { 11, 325, "3.2" },
    { 12, 347, "3.5" },
    { 13, 367, "3.5" },
    { 14, 389, "4.0" },
    { 15, 413, "4.5" },
    { 16, 443, "5.0" },
    { 17, 470, "5.6" },
    { 18, 494, "5.8" }, // max. opt. zoom
// The rest are the same physical apertures as above, but with ND:
    { 19, 481, "5.6" }, // wide angle
    { 20, 498, "6.3" },
    { 21, 516, "6.3" },
    { 22, 538, "7.1" },
    { 23, 558, "7.1" },
    { 24, 580, "8.0" },
    { 25, 604, "9.0" },
    { 26, 634, "10" },
    { 27, 661, "11" },
    { 28, 685, "11" }, // max. opt. zoom
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
    {  32, 1021, "1/1600",  625 },
};

const ISOTable iso_table[] = {
    { -1,     1,    "HI", -1},
    {  0,     0,  "Auto", -1},
    {  1,    80,    "80", -1},
    {  2,   100,   "100", -1},
    {  3,   200,   "200", -1},
    {  4,   400,   "400", -1},
    {  5,   800,   "800", -1},
    {  6,  1600,  "1600", -1},
};          


const CapturemodeMap modemap[] = {
    { MODE_SCN_LONG_SHUTTER,   32774 },
    { MODE_P,                  32772 },
    { MODE_SCN_STITCH,         33290 }, // SCN, either direction
    { MODE_SCN_COLOR_ACCENT,   33307 },
    { MODE_SCN_COLOR_SWAP,     33308 },
    { MODE_SCN_ISO_3200,       32797 },
    { MODE_AUTO,               32768 }, 
    { MODE_SCN_FOLIAGE,        32787 },
    { MODE_SCN_SUNSET,         32786 },
    { MODE_SCN_PORTRAIT,       32781 },
    { MODE_SCN_NIGHT_SNAPSHOT, 32779 },
    { MODE_SCN_SNOW,           32788 },
    { MODE_SCN_BEACH,          32789 },
    { MODE_SCN_INDOOR,         32785 },
    { MODE_SCN_UNDERWATER,     32791 },
    { MODE_SCN_AQUARIUM,       32792 },
    { MODE_SCN_KIDS_PETS,      32784 },
    { MODE_SCN_FIREWORK,       32790 },
    { MODE_VIDEO_COLOR_ACCENT, 2599  },
    { MODE_VIDEO_STD,          2601  },
    { MODE_VIDEO_COLOR_SWAP,   2600  },
    { MODE_DIGITAL_MACRO,      33288 },
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

long get_target_dir_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>18)&0x3FF;
    return n;
}

// http://www.dofmaster.com/digital_coc.html
int circle_of_confusion = 5;

// not used ? -> CAM_DRAW_EXPOSITION
