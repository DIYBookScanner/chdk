#ifndef MODES_H
#define MODES_H

// CHDK Camera Mode interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

/******************************************************************/

typedef struct {
    unsigned short hackmode;   // platform independent mode values from MODE_xxx enum
    unsigned short canonmode;  // PROPCASE_SHOOTING_MODE value
} CapturemodeMap;

/******************************************************************/

#define MODE_SHOOTING_MASK      0x00FF

#define MODE_MASK               0x0300
#define MODE_REC                0x0100
#define MODE_PLAY               0x0200

#define MODE_SCREEN_MASK        0x0C00
#define MODE_SCREEN_OPENED      0x0400
#define MODE_SCREEN_ROTATED     0x0800

/* capture mode constants. These are in their own header for easier sed processing*/
#include "modelist.h"

// converted large macro to function in platform/generic/shooting.c (philmoz July 2011)
extern int mode_is_video(int);
#define MODE_IS_VIDEO(m)    mode_is_video(m)

extern int mode_get();

/******************************************************************/

#endif
