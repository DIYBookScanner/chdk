#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "math.h"
#include "modes.h"
#include "viewport.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_osd.h"
#include "shooting.h"
#include "histogram.h"

//-------------------------------------------------------------------

#define HISTOGRAM_IDLE_STAGE        6

// Indexes into the various arrays for calculating the histogram channels
#define HISTO_R                     0       // Red channel
#define HISTO_G                     1       // Green channel
#define HISTO_B                     2       // Blue channel
#define HISTO_RGB                   3       // Combined Red, Green and Blue
#define HISTO_Y                     4       // Luminance (Y) from viewport

// Define type of transform to be done to scale the histogram to fit the available height
#define HISTO_MODE_LINEAR           0
#define HISTO_MODE_LOG              1

// Display modes
#define OSD_HISTO_LAYOUT_A          0       // A - RGB
#define OSD_HISTO_LAYOUT_Y          1
#define OSD_HISTO_LAYOUT_A_Y        2
#define OSD_HISTO_LAYOUT_R_G_B      3
#define OSD_HISTO_LAYOUT_A_yrgb     4
#define OSD_HISTO_LAYOUT_Y_argb     5
#define OSD_HISTO_LAYOUT_BLEND      6
#define OSD_HISTO_LAYOUT_BLEND_Y    7

// Define how many viewport blocks to step in each loop iteration. Each block is 6 bytes (UYVYYY) or 4 image pixels
#define	HISTO_STEP_SIZE	6

static unsigned char histogram[5][HISTO_WIDTH];             // RGBYG
static unsigned short *histogram_proc[5] = { 0,0,0,0,0 };   // RGBYG (unsigned short is large enough provided HISTO_STEP_SIZE >= 3)
unsigned int histo_max[5], histo_max_center[5];             // RGBYG
static float histo_max_center_invw[5];                      // RGBYG

static long histo_magnification;
static long under_exposed;
static long over_exposed;

static long histogram_stage=0;

//-------------------------------------------------------------------
// Histogram calculation functions

// Clip value to byte range (for YUV -> RGB conversion)
static int clip(int v)
{
    if (v<0) v=0;
    else if (v>255) v=255;
    return v;
}

// Transform functions
static float identity(float x)      { return x; }
static float logarithmic(float x)   { return log(x); }

static void histogram_alloc()
{
    // Allocate arrays to store counts during processing
    // Each possible value is counted so the array sizes are set to 256, then these are summed to
    // convert down to desired width of 128.
    // This is faster than scaling each value as it is counted
    if (histogram_proc[0] == 0)
    {
        histogram_proc[0] = malloc(5 * 256 * sizeof(unsigned short));
        histogram_proc[1] = histogram_proc[0] + 256;
        histogram_proc[2] = histogram_proc[1] + 256;
        histogram_proc[3] = histogram_proc[2] + 256;
        histogram_proc[4] = histogram_proc[3] + 256;
    }
}

void histogram_process()
{
    static unsigned char *img;
    static int viewport_size, viewport_width, viewport_row_offset;

    register int x, i, hi;
    int y, v, u, c;
    float (*histogram_transform)(float);
    unsigned int histo_fill[5];
    int histo_main;

    long exposition_thresh = camera_screen.size / 500;

    // Select transform function
    switch (conf.histo_mode)
    {
        case HISTO_MODE_LOG: 
            histogram_transform = logarithmic; 
            break;
        case HISTO_MODE_LINEAR: 
        default:
            histogram_transform = identity; 
            break;
    }

    // Select which calculated histogram channel determines magnification / scaling
    if (conf.histo_layout == OSD_HISTO_LAYOUT_Y || conf.histo_layout == OSD_HISTO_LAYOUT_Y_argb)
        histo_main = HISTO_Y;
    else
        histo_main = HISTO_RGB;

    histogram_alloc();

    // This function is called in the main spytask loop roughly every 20msec
    // To avoid hogging all the CPU it performs it's work in stages controlled by histogram-stage
    // Stage  Function
    //   0      Initialize global variables used in next stages
    //   1,2,3  Count number of values for a third of the viewport image at each stage
    //   4      Calculate max values, over and under exposure setting
    //   5      Calculate the histogram display values
    switch (histogram_stage)
    {
        case 0:
            img=vid_get_viewport_active_buffer();
            if (!img) return;

            img += vid_get_viewport_image_offset();		// offset into viewport for when image size != viewport size (e.g. 16:9 image on 4:3 LCD)
            viewport_size = vid_get_viewport_height() * vid_get_viewport_byte_width() * vid_get_viewport_yscale();
            viewport_width = vid_get_viewport_width();
            viewport_row_offset = vid_get_viewport_row_offset();
            for (c=0; c<5; ++c) {
                memset(histogram_proc[c],0,256*sizeof(unsigned short));
                histo_max[c] = histo_max_center[c] = 0;
            }

            histogram_stage=1;
            break;

        case 1:
        case 2:
        case 3:
            x = 0;  // count how many blocks we have done on the current row (to skip unused buffer space at end of each row)
            for (i=(histogram_stage-1)*6; i<viewport_size; i+=HISTO_STEP_SIZE*6) {
                y = img[i+1];
                u = *(signed char*)(&img[i]);
                //if (u&0x00000080) u|=0xFFFFFF00;  // Compiler should handle the unsigned -> signed conversion
                v = *(signed char*)(&img[i+2]);
                //if (v&0x00000080) v|=0xFFFFFF00;  // Compiler should handle the unsigned -> signed conversion

                ++histogram_proc[HISTO_Y][y];                       // Y
                hi = clip(((y<<12)          + v*5743 + 2048)>>12);  // R
                ++histogram_proc[HISTO_R][hi];
                hi = clip(((y<<12) - u*1411 - v*2925 + 2048)>>12);  // G
                ++histogram_proc[HISTO_G][hi];
                hi = clip(((y<<12) + u*7258          + 2048)>>12);  // B
                ++histogram_proc[HISTO_B][hi];

                // Handle case where viewport memory buffer is wider than the actual buffer.
                x += HISTO_STEP_SIZE * 2;	// viewport width is measured in blocks of three bytes each even though the data is stored in six byte chunks !
                if (x == viewport_width)
                {
                    i += viewport_row_offset;
                    x = 0;
                }
            }

            ++histogram_stage;
            break;

        case 4:
            for (i=0, c=0; i<HISTO_WIDTH; ++i, c+=2) { // G
                // Merge each pair of values into a single value (for width = 128)
                // Warning: this is optimised for HISTO_WIDTH = 128, don't change the width unless you re-write this code as well.
                histogram_proc[HISTO_Y][i] = histogram_proc[HISTO_Y][c] + histogram_proc[HISTO_Y][c+1];
                histogram_proc[HISTO_R][i] = histogram_proc[HISTO_R][c] + histogram_proc[HISTO_R][c+1];
                histogram_proc[HISTO_G][i] = histogram_proc[HISTO_G][c] + histogram_proc[HISTO_G][c+1];
                histogram_proc[HISTO_B][i] = histogram_proc[HISTO_B][c] + histogram_proc[HISTO_B][c+1];
                // Calc combined RGB totals
                histogram_proc[HISTO_RGB][i] = histogram_proc[HISTO_R][i] + histogram_proc[HISTO_G][i] + histogram_proc[HISTO_B][i];
            }

            // calculate maximums
            for (c=0; c<5; ++c) {
                for (i=0; i<HISTO_WIDTH; ++i) {
                    if (histo_max[c]<histogram_proc[c][i])
                        histo_max[c]=histogram_proc[c][i];
                    if (histo_max_center[c]<histogram_proc[c][i] && i>=conf.histo_ignore_boundary && i<HISTO_WIDTH-conf.histo_ignore_boundary)
                        histo_max_center[c]=histogram_proc[c][i];
                }

                if (histo_max_center[c] > 0) {
                    histo_max_center_invw[c] = ((float)HISTO_HEIGHT)/histogram_transform((float)histo_max_center[c]);
                } else if (histo_max[c] > 0) {
                    histo_max_center_invw[c] = ((float)HISTO_HEIGHT)/histogram_transform((float)histo_max[c]);
                } else {
                    histo_max_center_invw[c] = 0.0f;
                }
            }

            if (histo_max[HISTO_RGB] > 0) { // over- / under- expos
                under_exposed = (histogram_proc[HISTO_RGB][0]*8
                                +histogram_proc[HISTO_RGB][1]*4
                                +histogram_proc[HISTO_RGB][2]) > exposition_thresh;

                over_exposed  = (histogram_proc[HISTO_RGB][HISTO_WIDTH-3]
                                +histogram_proc[HISTO_RGB][HISTO_WIDTH-2]*4
                                +histogram_proc[HISTO_RGB][HISTO_WIDTH-1]*8) > exposition_thresh;
            } else {
                over_exposed = 0;
                under_exposed = 1;
            }

            histogram_stage=5;
            break;

        case 5:
            for (c=0; c<5; ++c) {
                histo_fill[c]=0;
                for (i=0; i<HISTO_WIDTH; ++i) {
                    histogram[c][i] = (histogram_transform((float)histogram_proc[c][i]))*histo_max_center_invw[c];
                    if (histogram[c][i] > HISTO_HEIGHT)
                        histogram[c][i] = HISTO_HEIGHT;
                    histo_fill[c]+=histogram[c][i];
                }
            }

            histo_magnification = 0;
            if (conf.histo_auto_ajust) {
                if (histo_fill[histo_main] < (HISTO_HEIGHT*HISTO_WIDTH)/5) { // try to ajust if average level is less than 20%
                    histo_magnification = (20*HISTO_HEIGHT*HISTO_WIDTH) / histo_fill[histo_main];
                    for (c=0; c<5; ++c) {
                        for (i=0;i<HISTO_WIDTH;i++) {
                            histogram[c][i] = histogram[c][i] * histo_magnification / 100;
                            if (histogram[c][i] > HISTO_HEIGHT)
                                histogram[c][i] = HISTO_HEIGHT;
                        }
                    }
                }
            }

            histogram_stage=0;
            break;
    }

}

//-------------------------------------------------------------------
// Histogram display functions

static void gui_osd_draw_single_histo(int hist, coord x, coord y, int small) {
    register unsigned int i, v, threshold;
    register color cl, cl_over, cl_bg = BG_COLOR(conf.histo_color);
    coord w=HISTO_WIDTH, h=HISTO_HEIGHT;

    switch (hist) 
    {
        case HISTO_R: 
            cl=(camera_info.state.mode_rec)?COLOR_HISTO_R:COLOR_HISTO_R_PLAY;
            break;
        case HISTO_G: 
            cl=(camera_info.state.mode_rec)?COLOR_HISTO_G:COLOR_HISTO_G_PLAY;
            break;
        case HISTO_B:
            cl=(camera_info.state.mode_rec)?COLOR_HISTO_B:COLOR_HISTO_B_PLAY;
            break;
        case HISTO_RGB:
        case HISTO_Y:
        default:
            cl=conf.histo_color; 
            break;
    }

    if (small) {
        h>>=1; w>>=1;
        for (i=0; i<w; ++i) {
            threshold = (histogram[hist][i<<1]+histogram[hist][(i<<1)+1])>>2;

            for (v=1; v<h-1; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?BG_COLOR(conf.histo_color2):cl;
            for (; v<h; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    } else {
        for (i=0; i<w; ++i) {
            threshold = histogram[hist][i];

            for (v=1; v<h-3; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?BG_COLOR(conf.histo_color2):cl;
            for (; v<h; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    }

    draw_rect(x, y, x+1+w, y+h, FG_COLOR(conf.histo_color2));
    //Vertical Lines
    if (conf.histo_show_ev_grid) for (i=1;i<=4;i++) draw_line(x+(1+w)*i/5, y, x+(1+w)*i/5, y+h, FG_COLOR(conf.histo_color2));
}

//-------------------------------------------------------------------
static void gui_osd_draw_blended_histo(coord x, coord y) {
    register unsigned int i, v, red, grn, blu, sel;
    color cls[] = {
        BG_COLOR(conf.histo_color),
        (camera_info.state.mode_rec)?COLOR_HISTO_B:COLOR_HISTO_B_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_G:COLOR_HISTO_G_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_BG:COLOR_HISTO_BG_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_R:COLOR_HISTO_R_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_RB:COLOR_HISTO_RB_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_RG:COLOR_HISTO_RG_PLAY,
        COLOR_WHITE
    };

    for (i=0; i<HISTO_WIDTH; ++i) {
        red = histogram[HISTO_R][i];
        grn = histogram[HISTO_G][i];
        blu = histogram[HISTO_B][i];

        for (v=1; v<HISTO_HEIGHT; ++v) {
            sel = 0;

            if (v < red) sel = 4;
            if (v < grn) sel |= 2;
            if (v < blu) sel |= 1;

            draw_pixel(x+1+i, y+HISTO_HEIGHT-v, cls[sel]);
        }
    }

    draw_rect(x, y, x+1+HISTO_WIDTH, y+HISTO_HEIGHT, FG_COLOR(conf.histo_color2));
    //Vertical lines
    if (conf.histo_show_ev_grid) for (i=1;i<=4;i++) draw_line(x+(1+HISTO_WIDTH)*i/5, y, x+(1+HISTO_WIDTH)*i/5, y+HISTO_HEIGHT, FG_COLOR(conf.histo_color2));

}

//-------------------------------------------------------------------
void gui_osd_draw_histo(int is_osd_edit)
{
    if (is_osd_edit ||
        ((camera_info.state.mode_play || !camera_info.state.mode_video) &&
         (
          ((conf.show_histo==SHOW_HALF) && camera_info.state.is_shutter_half_press) ||
          ((conf.show_histo==SHOW_ALWAYS) && (recreview_hold==0))
         )
        )
       )
    {
        switch (conf.histo_layout)
        {
            case OSD_HISTO_LAYOUT_Y:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
            case OSD_HISTO_LAYOUT_A_Y:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
            case OSD_HISTO_LAYOUT_R_G_B:
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT*2, 0);
                break;
            case OSD_HISTO_LAYOUT_A_yrgb:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
            case OSD_HISTO_LAYOUT_Y_argb:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
            case OSD_HISTO_LAYOUT_BLEND:
                gui_osd_draw_blended_histo(conf.histo_pos.x, conf.histo_pos.y);
                break;
            case OSD_HISTO_LAYOUT_BLEND_Y:
                gui_osd_draw_blended_histo(conf.histo_pos.x, conf.histo_pos.y);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
            case OSD_HISTO_LAYOUT_A:
            default:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
        }

        if (conf.histo_layout != OSD_HISTO_LAYOUT_R_G_B) {
            if (under_exposed && conf.show_overexp) {
                draw_filled_ellipse(conf.histo_pos.x+5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(BG_COLOR(conf.histo_color2), BG_COLOR(conf.histo_color2)));
            }

            if (over_exposed && conf.show_overexp) {
                draw_filled_ellipse(conf.histo_pos.x+HISTO_WIDTH-5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(BG_COLOR(conf.histo_color2), BG_COLOR(conf.histo_color2)));
            }
        }
        if ((conf.show_overexp ) && camera_info.state.is_shutter_half_press && (under_exposed || over_exposed))
            draw_string(conf.histo_pos.x+HISTO_WIDTH-FONT_WIDTH*3, conf.histo_pos.y-FONT_HEIGHT, "EXP", conf.histo_color);
        if (conf.histo_auto_ajust){
            if (histo_magnification) {
                char osd_buf[64];
                sprintf(osd_buf, " %d.%02dx ", histo_magnification/100, histo_magnification%100);
                draw_string(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, osd_buf, conf.histo_color);
            } else if (is_osd_edit){
                draw_string(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, " 9.99x ", conf.histo_color);
            } else {
                draw_filled_rect(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, conf.histo_pos.x+8*FONT_WIDTH, conf.histo_pos.y-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
            }
        }
    }
}


// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    return 0;
}

int _module_can_unload()
{
    return conf.show_histo == 0;
}

/******************** Module Information structure ******************/

libhisto_sym _libhisto =
{
    {
         0, _module_unloader, _module_can_unload, 0, 0
    },

    histogram_process,
    gui_osd_draw_histo
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    HISTO_VERSION,				// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Histogram Overlay (dll)",// Module name
    (int32_t)"Histogram Overlay",

    &_libhisto.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
