#ifndef GUI_DRAW_H
#define GUI_DRAW_H

#include "conf.h"       // load OSD_pos & OSD_scale

//-------------------------------------------------------------------

// Common colors that are the same in all palettes
#define COLOR_TRANSPARENT               0x00
#define COLOR_BLACK                     0xFF

//-------------------------------------------------------------------

// For CHDK core code use #define versions of color values
// For module and platform independent code use the module_colors[X] version (see below)
#ifndef CHDK_MODULE_CODE

// Moved from gui_bench.c, gui_debug.c, gui_calendar.c, gui_reversi.c & gui_sokoban.c so it can be overridden
// Default value is white in SX30 & G12 palette making white text hard to read
#define SCREEN_COLOR                    0xF7

#include "camera.h"     // ensure the camera definition is loaded

//-------------------------------------------------------------------

#if CAM_BITMAP_PALETTE==1

// Default palette used unless overridden - see list of cameras using each palette below

    #define COLOR_WHITE                 0x11
    #define COLOR_RED                   0x22
    #define COLOR_GREY                  0x3F
    #define COLOR_GREEN                 0x55
    #define COLOR_BLUE_LT               0xDD
    #define COLOR_BLUE                  0xDF
    #define COLOR_YELLOW                0xEE
    #define COLOR_BG                    0x44
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0xD4
    #define COLOR_SPLASH_RED            0x2E
    #define COLOR_SPLASH_PINK           0x21
    #define COLOR_SPLASH_GREY           0x1F
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              0x66
    #define COLOR_HISTO_RB_PLAY         0xE2
    #define COLOR_HISTO_B_PLAY          0xCC
    #define COLOR_HISTO_BG_PLAY         0x99
    #define COLOR_HISTO_RG_PLAY         0x66

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#if defined(CAMERA_ixus70_sd1000) || defined(CAMERA_ixus75_sd750)
    #define COLOR_ICON_REC_RED          0x88
    #define COLOR_ICON_REC_RED_DK       0x83
    #define COLOR_ICON_REC_RED_LT       0x81
    #define COLOR_ICON_REC_GREEN        0x55
    #define COLOR_ICON_REC_GREEN_DK     0x53
    #define COLOR_ICON_REC_GREEN_LT     0x51
    #define COLOR_ICON_REC_YELLOW       0x66
    #define COLOR_ICON_REC_YELLOW_DK    0x36
    #define COLOR_ICON_REC_YELLOW_LT    0x61
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x33
    #define COLOR_ICON_REC_GREY_LT      0x11
#endif
#if defined (CAMERA_a610)
    #define COLOR_ICON_REC_RED          0x22
    #define COLOR_ICON_REC_RED_DK       0x2F
    #define COLOR_ICON_REC_RED_LT       0x26
    #define COLOR_ICON_REC_GREEN        0x5F
    #define COLOR_ICON_REC_GREEN_DK     0x25
    #define COLOR_ICON_REC_GREEN_LT     0x51
    #define COLOR_ICON_REC_YELLOW       0x9F
    #define COLOR_ICON_REC_YELLOW_DK    0x9F
    #define COLOR_ICON_REC_YELLOW_LT    0x99
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x33
    #define COLOR_ICON_REC_GREY_LT      0x13
#endif

#elif CAM_BITMAP_PALETTE==2

// Used by :- IXUS95_SD1200, IXUS980_SD990

    #define COLOR_WHITE                 0xD3
    #define COLOR_RED                   0x64
    #define COLOR_GREY                  0x12
    #define COLOR_GREEN                 0xC4
    #define COLOR_BLUE_LT               0x6A
    #define COLOR_BLUE                  0x87
    #define COLOR_YELLOW                0x44
    #define COLOR_BG                    0x22
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0x22
    #define COLOR_SPLASH_RED            0x58
    #define COLOR_SPLASH_PINK           0x4C
    #define COLOR_SPLASH_GREY           0x16
    // many of these probably wrong on this cam
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              0x66
    #define COLOR_HISTO_RB_PLAY         0xE2
    #define COLOR_HISTO_B_PLAY          0xCC
    #define COLOR_HISTO_BG_PLAY         0x99
    #define COLOR_HISTO_RG_PLAY         0x66
    #undef SCREEN_COLOR
    #define SCREEN_COLOR                0x15    // try for a dark color in both record and play mode

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#if defined (CAMERA_g10)
    #define COLOR_ICON_REC_RED          0x5F
    #define COLOR_ICON_REC_RED_DK       0x69
    #define COLOR_ICON_REC_RED_LT       0x55
    #define COLOR_ICON_REC_GREEN        0x80
    #define COLOR_ICON_REC_GREEN_DK     0x87
    #define COLOR_ICON_REC_GREEN_LT     0x79
    #define COLOR_ICON_REC_YELLOW       0x40
    #define COLOR_ICON_REC_YELLOW_DK    0x47
    #define COLOR_ICON_REC_YELLOW_LT    0x3D
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x15
    #define COLOR_ICON_REC_GREY_LT      0x08
    #define COLOR_ICON_PLY_RED          COLOR_ICON_REC_RED
    #define COLOR_ICON_PLY_RED_DK       COLOR_ICON_REC_RED_DK
    #define COLOR_ICON_PLY_RED_LT       COLOR_ICON_REC_RED_LT
    #define COLOR_ICON_PLY_GREEN        0xCD
    #define COLOR_ICON_PLY_GREEN_DK     0xD2
    #define COLOR_ICON_PLY_GREEN_LT     0xC4
    #define COLOR_ICON_PLY_YELLOW       COLOR_ICON_REC_YELLOW
    #define COLOR_ICON_PLY_YELLOW_DK    COLOR_ICON_REC_YELLOW_DK
    #define COLOR_ICON_PLY_YELLOW_LT    COLOR_ICON_REC_YELLOW_LT
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT
#endif

#elif CAM_BITMAP_PALETTE==3

// Used by : 

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x2B
    #define COLOR_GREY                  0x17
    #define COLOR_GREEN                 0x99
    #define COLOR_BLUE_LT               0x2D
    #define COLOR_BLUE                  0x3B
    #define COLOR_YELLOW                0x9A
    #define COLOR_BG                    0x81
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                COLOR_GREY
    #define COLOR_SPLASH_RED            0x29
    #define COLOR_SPLASH_PINK           0x1E
    #define COLOR_SPLASH_GREY           0x16
    // colors for blended histo
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_HISTO_R
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_HISTO_G
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_BLACK // there isn't purplish on this cam I guess
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_B_PLAY          COLOR_HISTO_B
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#if defined (CAMERA_ixus120_sd940)
    #define COLOR_ICON_REC_RED          0xE7
    #define COLOR_ICON_REC_RED_DK       0xEA
    #define COLOR_ICON_REC_RED_LT       0xE3
    #define COLOR_ICON_REC_GREEN        0x7F
    #define COLOR_ICON_REC_GREEN_DK     0x86
    #define COLOR_ICON_REC_GREEN_LT     0x78
    #define COLOR_ICON_REC_YELLOW       0x92
    #define COLOR_ICON_REC_YELLOW_DK    0x87
    #define COLOR_ICON_REC_YELLOW_LT    0xA9
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x1A
    #define COLOR_ICON_REC_GREY_LT      0x11
    #define COLOR_ICON_PLY_RED          0x15
    #define COLOR_ICON_PLY_RED_DK       COLOR_SPLASH_PINK
    #define COLOR_ICON_PLY_RED_LT       0x2c
    #define COLOR_ICON_PLY_GREEN        0x9E
    #define COLOR_ICON_PLY_GREEN_DK     0x9E
    #define COLOR_ICON_PLY_GREEN_LT     0x9E
    #define COLOR_ICON_PLY_YELLOW       0xCC
    #define COLOR_ICON_PLY_YELLOW_DK    0xCD
    #define COLOR_ICON_PLY_YELLOW_LT    0xCB
    #define COLOR_ICON_PLY_GREY         COLOR_GREY
    #define COLOR_ICON_PLY_GREY_DK      0x1A
    #define COLOR_ICON_PLY_GREY_LT      0x11
#endif

#elif CAM_BITMAP_PALETTE==4

// Used by :- G11, S90, SX120IS

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x2B
    #define COLOR_GREY                  0x17
    #define COLOR_GREEN                 0x99
    #define COLOR_BLUE_LT               0xA9
    #define COLOR_BLUE                  0xA1
    #define COLOR_YELLOW                0x9A
    #define COLOR_BG                    0x61
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                COLOR_GREY
    #define COLOR_SPLASH_RED            0x29
    #define COLOR_SPLASH_PINK           0x1E
    #define COLOR_SPLASH_GREY           0x16
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_HISTO_R
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_HISTO_G
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_BLACK // there isn't purplish on this cam I guess
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_B_PLAY          COLOR_HISTO_B
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#if defined (CAMERA_sx120is)
    #define COLOR_ICON_REC_RED          0x1E
    #define COLOR_ICON_REC_RED_DK       0xA0
    #define COLOR_ICON_REC_RED_LT       0x26
    #define COLOR_ICON_REC_GREEN        0x47
    #define COLOR_ICON_REC_GREEN_DK     0x4A
    #define COLOR_ICON_REC_GREEN_LT     0x44
    #define COLOR_ICON_REC_YELLOW       0x69
    #define COLOR_ICON_REC_YELLOW_DK    0x9A
    #define COLOR_ICON_REC_YELLOW_LT    0x78
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x10
    #define COLOR_ICON_REC_GREY_LT      0x19
    #define COLOR_ICON_PLY_RED          0x27
    #define COLOR_ICON_PLY_RED_DK       0x2C
    #define COLOR_ICON_PLY_RED_LT       0x20
    #define COLOR_ICON_PLY_GREEN        0xCB
    #define COLOR_ICON_PLY_GREEN_DK     0xCB
    #define COLOR_ICON_PLY_GREEN_LT     0xCB
    #define COLOR_ICON_PLY_YELLOW       0xBE
    #define COLOR_ICON_PLY_YELLOW_DK    0x76
    #define COLOR_ICON_PLY_YELLOW_LT    0x5A
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT
#endif

#elif CAM_BITMAP_PALETTE==5

// Used by :- D10, IXUS100_SD780

    #define COLOR_WHITE                 0xD3
    #define COLOR_RED                   0x6A
    #define COLOR_GREY                  0x12
    #define COLOR_GREEN                 0xBF
    #define COLOR_BLUE_LT               0x7C
    #define COLOR_BLUE                  0x90
    #define COLOR_YELLOW                0x53
    #define COLOR_BG                    0x22
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0x22
    #define COLOR_SPLASH_RED            0x72
    #define COLOR_SPLASH_PINK           0x5C
    #define COLOR_SPLASH_GREY           0x16
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              0x72
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_B_PLAY          COLOR_HISTO_B
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW
    #undef SCREEN_COLOR
    #define SCREEN_COLOR                0x1D

#elif CAM_BITMAP_PALETTE==6

// Used by :- SX20

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x2B
    #define COLOR_GREY                  0x0F
    #define COLOR_GREEN                 0xA9
    #define COLOR_BLUE_LT               0x2D
    #define COLOR_BLUE                  0x3B
    #define COLOR_YELLOW                0x8B
    #define COLOR_BG                    0xFE
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                COLOR_BG
    #define COLOR_SPLASH_RED            COLOR_RED
    #define COLOR_SPLASH_PINK           0xEA
    #define COLOR_SPLASH_GREY           0x16
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_RED
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_B_PLAY          COLOR_HISTO_B
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
    #define COLOR_ICON_REC_RED          0x2C
    #define COLOR_ICON_REC_RED_DK       0x91
    #define COLOR_ICON_REC_RED_LT       0x26
    #define COLOR_ICON_REC_GREEN        0xB0
    #define COLOR_ICON_REC_GREEN_DK     0xB7
    #define COLOR_ICON_REC_GREEN_LT     0xA9
    #define COLOR_ICON_REC_YELLOW       0xDB
    #define COLOR_ICON_REC_YELLOW_DK    0xD9
    #define COLOR_ICON_REC_YELLOW_LT    0xDD
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x11
    #define COLOR_ICON_REC_GREY_LT      0x10
    #define COLOR_ICON_PLY_RED          0x25
    #define COLOR_ICON_PLY_RED_DK       0x2C
    #define COLOR_ICON_PLY_RED_LT       0x1E
    #define COLOR_ICON_PLY_GREEN        0xA5
    #define COLOR_ICON_PLY_GREEN_DK     0xAC
    #define COLOR_ICON_PLY_GREEN_LT     0x9E
    #define COLOR_ICON_PLY_YELLOW       0x75
    #define COLOR_ICON_PLY_YELLOW_DK    0x7A
    #define COLOR_ICON_PLY_YELLOW_LT    0x71
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT

#elif CAM_BITMAP_PALETTE==7

// Used by :- SX130IS

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x1e
    #define COLOR_GREY                  0x1a
    #define COLOR_GREEN                 0x17
    #define COLOR_BLUE_LT               0x10
    #define COLOR_BLUE                  0x14
    #define COLOR_YELLOW                0x60
    #define COLOR_BG                    0x62
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           0x0e
    #define COLOR_SELECTED_FG           COLOR_BLACK
    #define COLOR_ALT_BG                COLOR_BG
    #define COLOR_SPLASH_RED            COLOR_RED
    #define COLOR_SPLASH_PINK           0x1e        // Orange
    #define COLOR_SPLASH_GREY           0x16
    #define COLOR_HISTO_R               0x66
    #define COLOR_HISTO_R_PLAY          0xA0
    #define COLOR_HISTO_B               0x61
    #define COLOR_HISTO_B_PLAY          0xA2
    #define COLOR_HISTO_G               0x5F
    #define COLOR_HISTO_G_PLAY          0xA1
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_RED
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         0x80
    #undef SCREEN_COLOR
    #define SCREEN_COLOR                0x1D

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#if defined(CAMERA_sx130is)
    #define COLOR_ICON_REC_RED          0x66
    #define COLOR_ICON_REC_RED_DK       0x66
    #define COLOR_ICON_REC_RED_LT       0x66
    #define COLOR_ICON_REC_GREEN        0x6B
    #define COLOR_ICON_REC_GREEN_DK     0x6B
    #define COLOR_ICON_REC_GREEN_LT     0x69
    #define COLOR_ICON_REC_YELLOW       0x60
    #define COLOR_ICON_REC_YELLOW_DK    0x45
    #define COLOR_ICON_REC_YELLOW_LT    0x6C
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x19
    #define COLOR_ICON_REC_GREY_LT      0x10
    #define COLOR_ICON_PLY_RED          0xA0
    #define COLOR_ICON_PLY_RED_DK       0xA0
    #define COLOR_ICON_PLY_RED_LT       0xA0
    #define COLOR_ICON_PLY_GREEN        0xA1
    #define COLOR_ICON_PLY_GREEN_DK     0xA1
    #define COLOR_ICON_PLY_GREEN_LT     0xA1
    #define COLOR_ICON_PLY_YELLOW       0x6A
    #define COLOR_ICON_PLY_YELLOW_DK    0x6F
    #define COLOR_ICON_PLY_YELLOW_LT    0x63
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT
#endif

#elif CAM_BITMAP_PALETTE==8

// Used by :- A490, A495

    #define COLOR_WHITE                 0x11
    #define COLOR_RED                   0x2F
    #define COLOR_GREY                  0x1F
    #define COLOR_GREEN                 0xFC
    #define COLOR_BLUE_LT               0xEE
    #define COLOR_BLUE                  0xEF
    #define COLOR_YELLOW                0xDD
    #define COLOR_BG                    0x0F
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0x20
    #define COLOR_SPLASH_RED            0x22
    #define COLOR_SPLASH_PINK           0x24
    #define COLOR_SPLASH_GREY           0x1F
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              0x66
    #define COLOR_HISTO_RB_PLAY         0xE2
    #define COLOR_HISTO_B_PLAY          0xCC
    #define COLOR_HISTO_BG_PLAY         0x99
    #define COLOR_HISTO_RG_PLAY         0x66

#elif CAM_BITMAP_PALETTE==9

// Used by :- S95

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x66
    #define COLOR_GREY                  0x6D
    #define COLOR_GREEN                 0x69
    #define COLOR_BLUE_LT               0x68
    #define COLOR_BLUE                  0x67
    #define COLOR_YELLOW                0x60
    #define COLOR_BG                    0x20
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0x20
    #define COLOR_SPLASH_RED            COLOR_RED
    #define COLOR_SPLASH_PINK           COLOR_GREY
    #define COLOR_SPLASH_GREY           0xDE
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_RED
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_B_PLAY          COLOR_HISTO_B
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW

#elif CAM_BITMAP_PALETTE==10

// Used by :- IXUS220_ELPH300HS, IXUS230_ELPH310HS

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x9f
    #define COLOR_GREY                  0x1a
    #define COLOR_GREY_LIGHT            0x0B
    #define COLOR_GREY_DARK             0x19
    #define COLOR_GREEN                 0xa0
    #define COLOR_BLUE_LT               0x96
    #define COLOR_BLUE                  0xa1
    #define COLOR_YELLOW                0x92
    #define COLOR_BG                    0x4B
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           0x0e
    #define COLOR_SELECTED_FG           COLOR_BLACK
    #define COLOR_ALT_BG                COLOR_BG
    #define COLOR_SPLASH_RED            COLOR_RED
    #define COLOR_SPLASH_PINK           0x1e    // Orange
    #define COLOR_SPLASH_GREY           0x16
    #define COLOR_HISTO_R               0x6C
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               0x6D
    #define COLOR_HISTO_B_PLAY          COLOR_BLUE
    #define COLOR_HISTO_G               0x90
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              0x52    //COLOR_BLUE_LT
    #define COLOR_HISTO_RG              0x51    //COLOR_YELLOW
    #define COLOR_HISTO_RB              0x3D    //COLOR_RED
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW
    #undef SCREEN_COLOR
    #define SCREEN_COLOR                0x1D

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
    #define COLOR_ICON_REC_RED          0x3D
    #define COLOR_ICON_REC_RED_DK       0x6C
    #define COLOR_ICON_REC_RED_LT       0x1E
    #define COLOR_ICON_REC_GREEN        0x90
    #define COLOR_ICON_REC_GREEN_DK     0x5A
    #define COLOR_ICON_REC_GREEN_LT     0x59
    #define COLOR_ICON_REC_YELLOW       0x2D
    #define COLOR_ICON_REC_YELLOW_DK    0x1E
    #define COLOR_ICON_REC_YELLOW_LT    0x20
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x1A
    #define COLOR_ICON_REC_GREY_LT      0x11
    #define COLOR_ICON_PLY_RED          0x9F
    #define COLOR_ICON_PLY_RED_DK       0x9F
    #define COLOR_ICON_PLY_RED_LT       0x1E
    #define COLOR_ICON_PLY_GREEN        0xA0
    #define COLOR_ICON_PLY_GREEN_DK     0xA0
    #define COLOR_ICON_PLY_GREEN_LT     0x9E
    #define COLOR_ICON_PLY_YELLOW       0x55
    #define COLOR_ICON_PLY_YELLOW_DK    0x55
    #define COLOR_ICON_PLY_YELLOW_LT    0x4C
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT

#elif CAM_BITMAP_PALETTE==11

// Used by :- IXUS300_SD4000

    // pallete changes almost completely depenting on mode and if canon menu is active or not
    // playback, playback with menu, photo record mode, photo record mode with menu, ...
    #define COLOR_WHITE                 0x01    // always the same
    #define COLOR_RED                   0x1E    // always the same, bright orange (red is only available in record more without menu)
    #define COLOR_GREY                  0x16    // always the same
    #define COLOR_GREEN                 0x9F    // playback only, without menu
    #define COLOR_BLUE_LT               0x0C    // playback: light brown
    #define COLOR_BLUE                  0x12    // playback: dark brown (almost like sh.t)
    #define COLOR_YELLOW                0x90    // playback only, without menu
    #define COLOR_BG                    0x1D    // greyisch
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED    // always the same, light grey
    #define COLOR_SELECTED_FG           COLOR_BLACK
    #define COLOR_ALT_BG                COLOR_BG
    #define COLOR_SPLASH_RED            COLOR_RED
    #define COLOR_SPLASH_PINK           COLOR_BLUE
    #define COLOR_SPLASH_GREY           0x16    // darker grey
    // colors for blended histo
    #define COLOR_HISTO_R               0x66    // record only, without menu
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               0x3C
    #define COLOR_HISTO_B_PLAY          0x50    // playback without menu dont have blue at all, bright Orange
    #define COLOR_HISTO_G               0x6B
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_RED
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW

#elif CAM_BITMAP_PALETTE==12

// Used by :- A1100

    #define COLOR_WHITE                 0x0A
    #define COLOR_RED                   0x6B
    #define COLOR_GREY                  0x17
    #define COLOR_GREEN                 0x96
    #define COLOR_BLUE_LT               0x79
    #define COLOR_BLUE                  0x8A
    #define COLOR_YELLOW                0x54
    #define COLOR_BG                    0x1F
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0x87
    #define COLOR_SPLASH_RED            0x60
    #define COLOR_SPLASH_PINK           0xBD
    #define COLOR_SPLASH_GREY           0x16
    // colors for blended histo
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              0x66
    #define COLOR_HISTO_RB_PLAY         0xE2
    #define COLOR_HISTO_B_PLAY          0xCC
    #define COLOR_HISTO_BG_PLAY         0x99
    #define COLOR_HISTO_RG_PLAY         0x66
    #undef SCREEN_COLOR
    #define SCREEN_COLOR                0x1D

#elif CAM_BITMAP_PALETTE==13

// Used by :- G12, IXUS310_ELPH500HS, SX30, SX40HS, SX200IS, SX220HS, SX230HS, SX240HS, SX260HS,
//            A810, A1300, A2300, A3400, A4000, S100

    #define COLOR_WHITE                 0x01
    #define COLOR_GREY_DK               0x1a
    #define COLOR_GREY                  0x16
    #define COLOR_GREY_LT               0x0E
    #undef SCREEN_COLOR
    #define SCREEN_COLOR                0x1D

    // CHDK colors loaded into these locations in the camera palette by load_chdk_palette()
    #define COLOR_RED                   (CHDK_COLOR_BASE+0)
    #define COLOR_RED_DK                (CHDK_COLOR_BASE+1)
    #define COLOR_RED_LT                (CHDK_COLOR_BASE+2)
    #define COLOR_GREEN                 (CHDK_COLOR_BASE+3)
    #define COLOR_GREEN_DK              (CHDK_COLOR_BASE+4)
    #define COLOR_GREEN_LT              (CHDK_COLOR_BASE+5)
    #define COLOR_BLUE                  (CHDK_COLOR_BASE+6)
    #define COLOR_BLUE_DK               (CHDK_COLOR_BASE+7)
    #define COLOR_BLUE_LT               (CHDK_COLOR_BASE+8)
    #define COLOR_MAGENTA               (CHDK_COLOR_BASE+9)
    #define COLOR_YELLOW                (CHDK_COLOR_BASE+10)
    #define COLOR_YELLOW_DK             (CHDK_COLOR_BASE+11)
    #define COLOR_YELLOW_LT             (CHDK_COLOR_BASE+12)

    #define COLOR_CYAN                  COLOR_BLUE_LT
    #define COLOR_BG                    COLOR_GREY_DK
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_GREY_LT
    #define COLOR_SELECTED_FG           COLOR_BLACK
    #define COLOR_ALT_BG                COLOR_BG
    #define COLOR_SPLASH_RED            COLOR_RED_DK
    #define COLOR_SPLASH_PINK           COLOR_RED_LT
    #define COLOR_SPLASH_GREY           COLOR_GREY_LT
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_B_PLAY          COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_CYAN
    #define COLOR_HISTO_BG_PLAY         COLOR_CYAN
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_MAGENTA
    #define COLOR_HISTO_RB_PLAY         COLOR_MAGENTA

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
    #define COLOR_ICON_REC_RED          COLOR_RED
    #define COLOR_ICON_REC_RED_DK       COLOR_RED_DK
    #define COLOR_ICON_REC_RED_LT       COLOR_RED_LT
    #define COLOR_ICON_REC_GREEN        COLOR_GREEN
    #define COLOR_ICON_REC_GREEN_DK     COLOR_GREEN_DK
    #define COLOR_ICON_REC_GREEN_LT     COLOR_GREEN_LT
    #define COLOR_ICON_REC_YELLOW       COLOR_YELLOW
    #define COLOR_ICON_REC_YELLOW_DK    COLOR_YELLOW_DK
    #define COLOR_ICON_REC_YELLOW_LT    COLOR_YELLOW_LT
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      COLOR_GREY_DK
    #define COLOR_ICON_REC_GREY_LT      COLOR_GREY_LT

#if defined (CAMERA_sx200is)
    #undef COLOR_BG
    #define COLOR_BG                    (CHDK_COLOR_BASE+13) // Transparent Grey
    #undef COLOR_ALT_BG
    #define COLOR_ALT_BG                COLOR_BG
#endif

#elif CAM_BITMAP_PALETTE==14

// Used by :- A3000IS

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x22
    #define COLOR_GREY                  0xF3
    #define COLOR_GREEN                 0xcF
    #define COLOR_BLUE_LT               0x61
    #define COLOR_BLUE                  0xE7
    #define COLOR_YELLOW                0xDD
    #define COLOR_BG                    0x0F
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_GREY
    #define COLOR_ALT_BG                0xf0
    #define COLOR_SPLASH_RED            COLOR_RED
    #define COLOR_SPLASH_PINK           0x4E
    #define COLOR_SPLASH_GREY           0x6F
    #define COLOR_HISTO_R               COLOR_RED
    #define COLOR_HISTO_R_PLAY          COLOR_RED
    #define COLOR_HISTO_B               COLOR_BLUE
    #define COLOR_HISTO_G               COLOR_GREEN
    #define COLOR_HISTO_G_PLAY          COLOR_GREEN
    #define COLOR_HISTO_BG              COLOR_BLUE_LT
    #define COLOR_HISTO_RG              COLOR_YELLOW
    #define COLOR_HISTO_RB              COLOR_RED
    #define COLOR_HISTO_RB_PLAY         COLOR_HISTO_RB
    #define COLOR_HISTO_B_PLAY          COLOR_HISTO_B
    #define COLOR_HISTO_BG_PLAY         COLOR_BLUE_LT
    #define COLOR_HISTO_RG_PLAY         COLOR_YELLOW

#elif CAM_BITMAP_PALETTE==15

// Used by :- A3300IS

// Default Canon colors that are the same in record and play modes
#define COLOR_WHITE         0x01
#define COLOR_GREY_DK       0x1C  
#define COLOR_GREY          0x10
#define COLOR_GREY_LT       0x08
#undef SCREEN_COLOR
#define SCREEN_COLOR        0x1C

#ifdef CHDK_COLOR_BASE
    // CHDK colors loaded into these locations in the camera palette by load_chdk_palette()
    #define COLOR_RED           0x1E  // use Canon's red else get white behind startup spalsh
    #define COLOR_RED_DK        (CHDK_COLOR_BASE+1)
    #define COLOR_RED_LT        (CHDK_COLOR_BASE+2)
    #define COLOR_GREEN         (CHDK_COLOR_BASE+3)
    #define COLOR_GREEN_DK      (CHDK_COLOR_BASE+4)
    #define COLOR_GREEN_LT      (CHDK_COLOR_BASE+5)
    #define COLOR_BLUE          (CHDK_COLOR_BASE+6)
    #define COLOR_BLUE_DK       (CHDK_COLOR_BASE+7)
    #define COLOR_BLUE_LT       (CHDK_COLOR_BASE+8)
    #define COLOR_MAGENTA       (CHDK_COLOR_BASE+9)
    #define COLOR_YELLOW        (CHDK_COLOR_BASE+10)
    #define COLOR_YELLOW_DK     (CHDK_COLOR_BASE+11)
    #define COLOR_YELLOW_LT     (CHDK_COLOR_BASE+12)
#else
    #define COLOR_RED_LT        0x1E
    #define COLOR_RED           0x1E
    #define COLOR_RED_DK        0x1E
    #define COLOR_GREEN_LT      0x0E
    #define COLOR_GREEN         0x0E
    #define COLOR_GREEN_DK      0x0E
    #define COLOR_BLUE_LT       0x14
    #define COLOR_BLUE          0x14
    #define COLOR_BLUE_DK       0x14
    #define COLOR_YELLOW_LT     0x08
    #define COLOR_YELLOW        0x08
    #define COLOR_YELLOW_DK     0x08
#endif	// CHDK_COLOR_BASE

#define COLOR_BG            COLOR_GREY
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_GREY_DK
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        COLOR_BG

#define COLOR_SPLASH_RED    COLOR_RED
#define COLOR_SPLASH_PINK   COLOR_RED
#define COLOR_SPLASH_GREY   COLOR_GREY

#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_RED
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_B_PLAY  COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_GREEN
#define COLOR_HISTO_BG      COLOR_BLUE
#define COLOR_HISTO_BG_PLAY COLOR_BLUE
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#define COLOR_HISTO_RB      COLOR_RED
#define COLOR_HISTO_RB_PLAY COLOR_RED

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#define	COLOR_ICON_REC_RED		COLOR_RED
#define	COLOR_ICON_REC_RED_DK		COLOR_RED_DK
#define	COLOR_ICON_REC_RED_LT		COLOR_RED_LT
#define	COLOR_ICON_REC_GREEN		COLOR_GREEN
#define	COLOR_ICON_REC_GREEN_DK		COLOR_GREEN_DK
#define	COLOR_ICON_REC_GREEN_LT		COLOR_GREEN_LT
#define	COLOR_ICON_REC_YELLOW		COLOR_YELLOW
#define	COLOR_ICON_REC_YELLOW_DK	COLOR_YELLOW_DK
#define	COLOR_ICON_REC_YELLOW_LT	COLOR_YELLOW_LT
#define	COLOR_ICON_REC_GREY		COLOR_GREY
#define	COLOR_ICON_REC_GREY_DK		COLOR_GREY_DK
#define	COLOR_ICON_REC_GREY_LT		COLOR_GREY_LT
//

#elif CAM_BITMAP_PALETTE==16

// Used by :- A1200, G10, IXUS120_SD940

// Default Canon colors that are the same in record and play modes
#define COLOR_WHITE         0x01
#define COLOR_GREY_DK       0x1C  
#define COLOR_GREY          0x1A
#define COLOR_GREY_LT       0x16
#undef SCREEN_COLOR
#define SCREEN_COLOR        0x1D

#define COLOR_RED           (CHDK_COLOR_BASE+0)  
#define COLOR_RED_DK        (CHDK_COLOR_BASE+1)
#define COLOR_RED_LT        (CHDK_COLOR_BASE+2)
#define COLOR_GREEN         (CHDK_COLOR_BASE+3)
#define COLOR_GREEN_DK      (CHDK_COLOR_BASE+4)
#define COLOR_GREEN_LT      (CHDK_COLOR_BASE+5)
#define COLOR_BLUE          (CHDK_COLOR_BASE+6)
#define COLOR_BLUE_DK       (CHDK_COLOR_BASE+7)
#define COLOR_BLUE_LT       (CHDK_COLOR_BASE+8)
#define COLOR_MAGENTA       (CHDK_COLOR_BASE+9)
#define COLOR_YELLOW        (CHDK_COLOR_BASE+10)
#define COLOR_YELLOW_DK     (CHDK_COLOR_BASE+11)
#define COLOR_YELLOW_LT     (CHDK_COLOR_BASE+12)

#define COLOR_BG            COLOR_GREY
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_BLUE_DK  
#define COLOR_SELECTED_FG   COLOR_YELLOW
#define COLOR_ALT_BG        COLOR_BG
#define COLOR_SPLASH_RED    COLOR_RED
#define COLOR_SPLASH_PINK   COLOR_RED_LT
#define COLOR_SPLASH_GREY   COLOR_GREY
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_RED
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_B_PLAY  COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_GREEN
#define COLOR_HISTO_BG      COLOR_BLUE
#define COLOR_HISTO_BG_PLAY COLOR_BLUE
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#define COLOR_HISTO_RB      COLOR_RED
#define COLOR_HISTO_RB_PLAY COLOR_RED

#define	COLOR_ICON_REC_RED		COLOR_RED
#define	COLOR_ICON_REC_RED_DK		COLOR_RED_DK
#define	COLOR_ICON_REC_RED_LT		COLOR_RED_LT
#define	COLOR_ICON_REC_GREEN		COLOR_GREEN
#define	COLOR_ICON_REC_GREEN_DK		COLOR_GREEN_DK
#define	COLOR_ICON_REC_GREEN_LT		COLOR_GREEN_LT
#define	COLOR_ICON_REC_YELLOW		COLOR_YELLOW
#define	COLOR_ICON_REC_YELLOW_DK	COLOR_YELLOW_DK
#define	COLOR_ICON_REC_YELLOW_LT	COLOR_YELLOW_LT
#define	COLOR_ICON_REC_GREY		COLOR_GREY
#define	COLOR_ICON_REC_GREY_DK		COLOR_GREY_DK
#define	COLOR_ICON_REC_GREY_LT		COLOR_GREY_LT

#elif CAM_BITMAP_PALETTE==17 // used in A3100 + A3150^M
    #define COLOR_WHITE                 0x11
    #define COLOR_RED                   0x22
    #define COLOR_BLUE                  0x00
    #define COLOR_GREY                  0x66
    #define COLOR_GREEN                 0xcc
    #define COLOR_BLUE_LT               0x4e
    #define COLOR_YELLOW                0x2d
    #define COLOR_SPLASH_RED            0x22
    #define COLOR_SPLASH_PINK           0x24
    #define COLOR_SPLASH_GREY           0x66
    #define COLOR_BG                    0x37
    #define COLOR_FG                    COLOR_WHITE
    #define COLOR_SELECTED_BG           COLOR_RED
    #define COLOR_SELECTED_FG           COLOR_WHITE
    #define COLOR_ALT_BG                0xD4

    #define COLOR_HISTO_R              0x02
    #define COLOR_HISTO_G              0x0c
    #define COLOR_HISTO_B              0xe3
    #define COLOR_HISTO_R_PLAY         0x02
    #define COLOR_HISTO_G_PLAY         0x0c
    #define COLOR_HISTO_B_PLAY         0x00
    #define COLOR_HISTO_RB             0xf0 //32
    #define COLOR_HISTO_RG             0xf0 //0b
    #define COLOR_HISTO_RG_PLAY        0xf0 //09
    #define COLOR_HISTO_RB_PLAY        0xf0 //09
    #define COLOR_HISTO_BG_PLAY        0xf0 //00
    #define COLOR_HISTO_BG             0xf0 //0e

    #define COLOR_ICON_REC_RED         0x62
    #define COLOR_ICON_REC_RED_DK      0x72
    #define COLOR_ICON_REC_RED_LT      0x52
    #define COLOR_ICON_REC_GREEN       0xc6
    #define COLOR_ICON_REC_GREEN_DK    0xc7
    #define COLOR_ICON_REC_GREEN_LT    0xc5
    #define COLOR_ICON_REC_YELLOW      0x9d
    #define COLOR_ICON_REC_YELLOW_DK    0x9c
    #define COLOR_ICON_REC_YELLOW_LT    0x8d
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x77
    #define COLOR_ICON_REC_GREY_LT      0x55

#else
    #error CAM_BITMAP_PALETTE not defined
#endif	// CAM_BITMAP_PALETTE

// Define default icon colors if not already defined above
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
#if !defined(COLOR_ICON_REC_RED)        // Record mode colors
    #define COLOR_ICON_REC_RED          0x22
    #define COLOR_ICON_REC_RED_DK       0x2F
    #define COLOR_ICON_REC_RED_LT       0x26
    #define COLOR_ICON_REC_GREEN        0x5F
    #define COLOR_ICON_REC_GREEN_DK     0x25
    #define COLOR_ICON_REC_GREEN_LT     0x51
    #define COLOR_ICON_REC_YELLOW       0x6F
    #define COLOR_ICON_REC_YELLOW_DK    0x6F
    #define COLOR_ICON_REC_YELLOW_LT    0x66
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x33
    #define COLOR_ICON_REC_GREY_LT      0x13
#endif
#if !defined(COLOR_ICON_PLY_RED)        // Playback mode colors
    #define COLOR_ICON_PLY_RED          COLOR_ICON_REC_RED
    #define COLOR_ICON_PLY_RED_DK       COLOR_ICON_REC_RED_DK
    #define COLOR_ICON_PLY_RED_LT       COLOR_ICON_REC_RED_LT
    #define COLOR_ICON_PLY_GREEN        COLOR_ICON_REC_GREEN
    #define COLOR_ICON_PLY_GREEN_DK     COLOR_ICON_REC_GREEN_DK
    #define COLOR_ICON_PLY_GREEN_LT     COLOR_ICON_REC_GREEN_LT
    #define COLOR_ICON_PLY_YELLOW       COLOR_ICON_REC_YELLOW
    #define COLOR_ICON_PLY_YELLOW_DK    COLOR_ICON_REC_YELLOW_DK
    #define COLOR_ICON_PLY_YELLOW_LT    COLOR_ICON_REC_YELLOW_LT
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT
#endif

#else

// Module & platform independent code color settings

extern  const unsigned char const module_colors[];

#define SCREEN_COLOR        (module_colors[0])
#define COLOR_WHITE         (module_colors[1])
#define COLOR_RED           (module_colors[2])
#define COLOR_GREY          (module_colors[3])
#define COLOR_GREEN         (module_colors[4])
#define COLOR_BLUE_LT       (module_colors[5])
#define COLOR_BLUE          (module_colors[6])
#define COLOR_YELLOW        (module_colors[7])
#define COLOR_BG            (module_colors[8])
#define COLOR_FG            (module_colors[9])
#define COLOR_SELECTED_BG   (module_colors[10])
#define COLOR_SELECTED_FG   (module_colors[11])
#define COLOR_ALT_BG        (module_colors[12])
#define COLOR_SPLASH_RED    (module_colors[13])
#define COLOR_SPLASH_PINK   (module_colors[14])
#define COLOR_SPLASH_GREY   (module_colors[15])
#define COLOR_HISTO_R       (module_colors[16])
#define COLOR_HISTO_R_PLAY  (module_colors[17])
#define COLOR_HISTO_B       (module_colors[18])
#define COLOR_HISTO_G       (module_colors[19])
#define COLOR_HISTO_G_PLAY  (module_colors[20])
#define COLOR_HISTO_BG      (module_colors[21])
#define COLOR_HISTO_RG      (module_colors[22])
#define COLOR_HISTO_RB      (module_colors[23])
#define COLOR_HISTO_RB_PLAY (module_colors[24])
#define COLOR_HISTO_B_PLAY  (module_colors[25])
#define COLOR_HISTO_BG_PLAY (module_colors[26])
#define COLOR_HISTO_RG_PLAY (module_colors[27])

#endif  // CHDK_MODULE_CODE

//-------------------------------------------------------------------

#define FONT_WIDTH                      8
#define FONT_HEIGHT                     16

//-------------------------------------------------------------------
extern void draw_init();
extern void draw_set_draw_proc(void (*pixel_proc)(unsigned int offset, color cl));

extern void draw_set_guard();
extern int draw_test_guard();

extern color draw_get_pixel(coord x, coord y);

extern void draw_pixel(coord x, coord y, color cl);

extern void draw_line(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_hline(coord x, coord y, int len, color cl);
extern void draw_vline(coord x, coord y, int len, color cl);

// draw frame
extern void draw_rect(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness);
extern void draw_rect_shadow(coord x1, coord y1, coord x2, coord y2, color cl, int thickness);
extern void draw_round_rect(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_round_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness);
// color: hi_byte - BG; lo_byte - FG
extern void draw_filled_rect(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_filled_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness);
extern void draw_filled_round_rect(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_filled_round_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness);

extern void draw_char(coord x, coord y, const char ch, color cl);
extern void draw_string(coord x, coord y, const char *s, color cl);
extern void draw_char_scaled(coord x, coord y, const char ch, color cl, int xsize, int ysize);
extern void draw_string_scaled(coord x, coord y, const char *s, color cl, int xsize, int ysize);
extern void draw_osd_string(OSD_pos pos, int xo, int yo, char *s, color c, OSD_scale scale);

extern void draw_txt_rect(coord col, coord row, unsigned int length, unsigned int height, color cl);
extern void draw_txt_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl);
extern void draw_txt_filled_rect(coord col, coord row, unsigned int length, unsigned int height, color cl);
extern void draw_txt_filled_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl);
extern void draw_txt_string(coord col, coord row, const char *str, color cl);
extern void draw_txt_char(coord col, coord row, const char ch, color cl);

extern void draw_restore();

extern void draw_fill(coord x, coord y, color cl_fill, color cl_bound);
extern void draw_circle(coord x, coord y, const unsigned int r, color cl);
extern void draw_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl);
extern void draw_filled_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl);

extern void draw_get_icon_colors();
extern color icon_green[3], icon_red[3], icon_yellow[3], icon_grey[3];

//-------------------------------------------------------------------

#define NUM_SCRIPT_COLORS   18
extern const unsigned char const script_colors[NUM_SCRIPT_COLORS][2];

//-------------------------------------------------------------------
#endif
