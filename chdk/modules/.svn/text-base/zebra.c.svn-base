#include "camera_info.h"
#include "conf.h"
#include "keyboard.h"
#include "modes.h"
#include "viewport.h"
#include "properties.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_osd.h"
#include "gui_batt.h"
#include "gui_space.h"
#include "histogram.h"

#include "zebra.h"
#include "gui_grid.h"
#include "module_def.h"

//-------------------------------------------------------------------

// Notes on Zebra implementation.

// The zebra code examines the Y (luminance) values of the camera
// viewport to look for overexposed or underexposed pixels. The
// range of low and high values that determine over and under
// exposure is set with the 'zebra_over' and 'zebra_under' settings.

// There is an RGB mode controlled by zebra_multichannel that
// converts the viewport data from YUV to RGB and looks for exposure
// problems in each channel.

// Over and underexposed pixels are displayed on the bitmap screen
// using the zebra_color setting - foregound color is used of over
// exposure and background for under exposure.

// The code tries to allocate a memory buffer that is the same dimensions
// as the bitmap screen. The zebra display is written to this buffer
// and when done the buffer is copied into the camera bitmap screen memory.
// If the code can't allocate a memory buffer it writes the zebra data
// directly to the camera bitmap screen memory. Allocation of the memory
// buffer can also be overridden by setting CAM_ZEBRA_NOBUF in
// platform_camera.h. The code here uses the equivalent setting from
// camera_screen.zebra_nobuf for module platform indepedance.

// There are two variations of the basic zebra code to cater for
// different camera generations. Older cameras have a 360 byte wide
// bitmap screen (or 480 for wide screen cameras). This matches the
// CHDK virtual screen size so over and under exposed pixels are set
// in the bitmap image buffer directly.
// Newer cameras have a 720 (or 960) byte wide bitmap screen and the
// zebra code write two bytes (pixels) into the buffer for every
// over or underexposed pixel. Again the buffer is copied to the
// camera bitmap memory when done.

// Determining which code path is done with the CAM_USES_ASPECT_CORRECTION
// value in platform_camera.h (accessed via camera_screen.zebra_aspect_adjust).
// If CAM_USES_ASPECT_CORRECTION is not defined (or 0) the older code
// is used that assumes the bitmap screen is 360 bytes wide.
// Defining CAM_USES_ASPECT_CORRECTION as 1 will use the newer code.

// Another difference is that the old code path saves the top and bottom
// of the Canon OSD from the bitmap screen memory and overlays this on
// top of the zebra buffer. The new code version does not do this. The
// size of the strips saved is defined by ZFIX_TOP and ZFIX_BOTTOM.

// The final element comes from cameras that can capture images in
// different aspect ratios. Canon cameras all have a 4:3 ratio sensor
// but many can capture an image in different sizes - e.g. 1:1, 3:2 and 16:9.
// When these alternate ratios are selected the camera displays black
// bars at the top and bottom or left and right edges of the image in
// the viewport. The zebra code attempts to cater for this and not
// display underexposure indicators in these unused areas. The size
// and position of the black bars is also dependant on the aspect ratio
// of the camera LCD. Cameras with 4:3 LCD screens will show a 16:9 image
// with bars above and below. Cameras with 16:9 LCD screens will show
// a 4:3 image with bars to the left and right.

// For older cameras (that do not define CAM_USES_ASPECT_CORRECTION) the 
// aspect ratio is controlled by the CAM_HAS_VARIABLE_ASPECT value
// in platform_camera.h (camera_screen.has_variable_aspect). Defining
// this value tells the code that the camera has a 16:9 LCD but can
// also display a 4:3 image with black bars on the left and right.
// The value of the PROPCASE_ASPECT_RATIO property determines which
// image size if displayed. The code cannot handle other combinations
// of LCD size and image ratio.

// For newer cameras the code can handle any combination of LCD size
// and image aspect ratio provided the vid_get_viewport_height(), 
// vid_get_viewport_width(), vid_get_viewport_image_offset(),
// vid_get_viewport_row_offset(), vid_get_viewport_display_xoffset(),
// and vid_get_viewport_display_yoffset() functions have been correctly
// implemented for the camera.

// philmoz. Jan 2012.

//-------------------------------------------------------------------

// Height (in pixels) of half-shoot Canon OSD area of the screen buffer, for restore during 
// Zebra draw, to limit RAM usage of zebra. Only these border areas are stored in RAM.
// Only top and bottom are restored, not left & right.
#define ZFIX_TOP    29
#define ZFIX_BOTTOM 30

static unsigned char *img_buf, *scr_buf;
static unsigned char *cur_buf_top, *cur_buf_bot;
static int timer = 0;
static unsigned char *buf = NULL;
static int buffer_size;
static color cl_under, cl_over;

unsigned char clip8(signed short x){ if (x<0) x=0; else if (x>255) x=255; return x; }

//-------------------------------------------------------------------
// free and NULL zebra buffers. free(NULL) is always OK.
static void gui_osd_zebra_free()
{
    if (buf != scr_buf) free(buf);
    buf = NULL;

    free(cur_buf_top);
    cur_buf_top = NULL;

    free(cur_buf_bot);
    cur_buf_bot = NULL;
}

// prepare zebra resources, or free them
// returns 1 if zebra should be drawn
static int gui_osd_zebra_init(int show)
{
    cl_under = BG_COLOR(conf.zebra_color);
    cl_over = FG_COLOR(conf.zebra_color);

    if (show)
    {
        if (!buf)
        {
            timer = 0;
            // Determine bitmap buffer size. If physical buffer is taller than displayed height then ignore bottom strip - (used to be ZEBRA_HMARGIN0).
            buffer_size = camera_screen.buffer_size - (camera_screen.buffer_height - camera_screen.height) * camera_screen.buffer_width;
            scr_buf = vid_get_bitmap_fb();
            if (camera_screen.zebra_nobuf == 0)
            {
                buf = malloc(buffer_size);
                //if (!buf) draw_txt_string(0, 14, "Warn: No space to allocate zebra buffer: restart camera", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            }
            if (!buf)
            {
                buf = scr_buf;  //without new buffer: directly into screen buffer: we got some flickering in OSD and histogram but it's usable
            }
            if (camera_screen.zebra_aspect_adjust)
            {
                cur_buf_top = cur_buf_bot = 0;
            }
            else
            {
                cur_buf_top = malloc(camera_screen.buffer_width * ZFIX_TOP); 
                cur_buf_bot = malloc(camera_screen.buffer_width * ZFIX_BOTTOM); 
                // cleanup and disable zebra if any mallocs failed
                if (!cur_buf_top || !cur_buf_bot)
                    gui_osd_zebra_free();
                if (cur_buf_top) memset(cur_buf_top,0,camera_screen.buffer_width * ZFIX_TOP);
                if (cur_buf_bot) memset(cur_buf_bot,0,camera_screen.buffer_width * ZFIX_BOTTOM);
            }
            // in variable aspect, the borders would never be cleared
            if (camera_screen.has_variable_aspect)
                memset(buf,0,buffer_size);
        }
    }
    else {
        if (buf) // if zebra was previously on, restore
            gui_set_need_restore();

        gui_osd_zebra_free();
    }
    return (buf != NULL);
}

//-------------------------------------------------------------------
// Override for standard drawing function to draw OSD elements
// into the zebra memory buffer instead of the camera screen.
static void draw_pixel_buffered(unsigned int offset, color cl)
{
    buf[offset] = cl;
}

//-------------------------------------------------------------------
int draw_guard_pixel() {
    unsigned char* buffer1 = vid_get_bitmap_fb()+camera_screen.buffer_size/2;
    unsigned char* buffer2 = buffer1+camera_screen.buffer_size;
    int has_disappeared=0;

    if(*buffer1!=COLOR_GREEN) has_disappeared=1;
    if(*buffer2!=COLOR_GREEN) has_disappeared=2;
    *buffer1 = *buffer2 = COLOR_GREEN;
    return has_disappeared;
}

//-------------------------------------------------------------------
static void gui_osd_draw_zebra_osd() {
    switch (conf.zebra_draw_osd) {
        case ZEBRA_DRAW_NONE:
            break;
        case ZEBRA_DRAW_OSD:
            if (conf.show_osd) {
                draw_set_draw_proc(draw_pixel_buffered);
                gui_draw_osd_elements(0,1);
                draw_set_draw_proc(NULL);
            }
            /* no break here */
        case ZEBRA_DRAW_HISTO:
        default:
            draw_set_draw_proc(draw_pixel_buffered);
            libhisto->gui_osd_draw_histo(0);
            draw_set_draw_proc(NULL);
            break;
    }
}

//-------------------------------------------------------------------
static void disp_zebra()
{
    // draw CHDK osd and histogram to buf[] (if enabled in config)
    gui_osd_draw_zebra_osd();

    // copy buf[] to both display buffers
    if (buf != scr_buf)
        memcpy(scr_buf, buf, buffer_size);
    memcpy(scr_buf+camera_screen.buffer_size, buf, buffer_size);
}

//-------------------------------------------------------------------
// CHDK uses a virtual screen size of 360 x 240 pixels (480x240 for wide screen models)
// This function calculates the Zebra overlay for cameras where the screen buffer width
// is not equivalent to the CHDK virtual screen width. Newer cameras have a 720
// pixel wide screen (960 for wide screen models).
static int draw_zebra_aspect_adjust(int mrec, unsigned int f, color *cls)
{
    unsigned int v, s, x, y, over;
    static int need_restore=0;
    int viewport_height;
    int viewport_width; 
    int viewport_image_offset;  // for when viewport memory buffer is wider than viewport
    int viewport_row_offset;    // for when viewport memory buffer is wider than viewport
    int viewport_xoffset;	    // used when image size != viewport size
    int viewport_yoffset;	    // used when image size != viewport size
    int zebra_drawn=0;

    viewport_height = vid_get_viewport_height();
    viewport_width = vid_get_viewport_width(); 
    viewport_image_offset = vid_get_viewport_image_offset(); 
    viewport_row_offset = vid_get_viewport_row_offset(); 
    viewport_xoffset = vid_get_viewport_display_xoffset();
    viewport_yoffset = vid_get_viewport_display_yoffset();

    // if not in no-zebra phase of blink mode zebra, draw zebra to buf[]
    if (f) {
        if (viewport_yoffset > 0) { // clear top & bottom areas of buffer if image height if smaller than viewport
            memset(buf, COLOR_TRANSPARENT, viewport_yoffset*camera_screen.buffer_width);
            memset(buf+(viewport_yoffset+viewport_height)*camera_screen.buffer_width, COLOR_TRANSPARENT, viewport_yoffset*camera_screen.buffer_width);
        }
        int step_x, step_v, sy, sx;
        over = 255-conf.zebra_over;
        if (conf.zebra_multichannel) {step_x=2; step_v=6;} else {step_x=1; step_v=3;}
        for (y=viewport_yoffset, v=viewport_image_offset; y<viewport_yoffset+viewport_height; ++y) {
            sy = y*camera_screen.buffer_width;
            sx = viewport_xoffset;
            if (viewport_xoffset > 0) { // clear left & right areas of buffer if image width if smaller than viewport
                memset(buf+sy, COLOR_TRANSPARENT, sx*2);
                memset(buf+sy+(sx+viewport_width)*2, COLOR_TRANSPARENT, sx*2);
            }
            for (x=viewport_xoffset; x<viewport_xoffset+viewport_width; x+=step_x, sx+=step_x, v+=step_v) {
                register int yy;
                yy = img_buf[v+1];
                s = sy + sx*2;

                if (conf.zebra_multichannel) {
                    register int uu, vv;
                    int sel;
                    uu = (signed char)img_buf[v];
                    vv = (signed char)img_buf[v+2];
                    sel=0;
                    if (!((conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) && (y-x-timer)&f)) {
                        if (clip8(((yy<<12) +           vv*5743 + 2048)>>12)>over) sel  = 4; // R
                        if (clip8(((yy<<12) - uu*1411 - vv*2925 + 2048)>>12)>over) sel |= 2; // G
                        if (clip8(((yy<<12) + uu*7258           + 2048)>>12)>over) sel |= 1; // B
                    }
                    buf[s] = buf[s+1] = cls[sel];
                    buf[s+2] = buf[s+3] = cls[sel];
                }
                else if (((conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) && (y-x-timer)&f))
                    buf[s] = buf[s+1] = COLOR_TRANSPARENT;
                else 
                    buf[s] = buf[s+1] = (yy>over)?cl_over:(yy<conf.zebra_under)?cl_under:COLOR_TRANSPARENT;

                if (buf[s] != COLOR_TRANSPARENT && !zebra_drawn) 
                    zebra_drawn = 1;
            }
            // adjust for cases where buffer is wider than viewport (e.g. on G12)
            v += viewport_row_offset;
        }
        if (!zebra_drawn) f=0;
    }
    // if blink mode is in no-zebra phase OR if there was no over/underexposed pixels to draw zebra on
    if (!f) {
        // if zebra was drawn during previous call of this function
        if (need_restore) {
            if (conf.zebra_restore_screen || conf.zebra_restore_osd) {
                gui_set_need_restore();
            } else {  // clear buf[] of zebra, only leave Canon OSD
                if (!mrec) { // Not REC mode
                    // No Canon OSD restore, fill buf[] with transparent color:
                    memset(buf, COLOR_TRANSPARENT, buffer_size);
                }
                disp_zebra();
            }
            need_restore=0;
        }
        return !(conf.zebra_restore_screen && conf.zebra_restore_osd);
        // if zebra was drawn
    } else {
        disp_zebra();

        need_restore=1;
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------
// Get the current Canon OSD pixel value for the top or bottom strip
static unsigned char get_cur_buf(unsigned int idx) {
    unsigned int a;

    a=camera_screen.buffer_size - camera_screen.buffer_width * ZFIX_BOTTOM;

    if (idx < camera_screen.buffer_width * ZFIX_TOP) return(cur_buf_top[idx]);
    if (idx >= a && idx < camera_screen.buffer_size) return(cur_buf_bot[idx - a]);
    return (COLOR_TRANSPARENT);
}

//-------------------------------------------------------------------
// This function calculates the Zebra overlay for cameras where the screen buffer width
// is equivalent to the CHDK virtual screen width. For older cameras where the screen
// width is 360 pixels (or 480 for wide screen).
static int draw_zebra_no_aspect_adjust(int mrec, unsigned int f, color *cls) {
    unsigned int v, s, x, y, over;
    static int need_restore=0;
    int viewport_height;
    int zebra_drawn=0;

    unsigned bWide = 1; // if wide (16:9) or standard (4:3) aspect ratio (but 1 in cameras that only have 4:3)
    unsigned aspOffset = 0; // offset to add to x-coord (or buffer address) when drawing zebra

    if (camera_screen.has_variable_aspect && camera_info.props.aspect_ratio)
    {
        if (shooting_get_prop(camera_info.props.aspect_ratio) == 0) // standard requires x-shift to overlay drawing
        {
            bWide = 0;
            //aspOffset = (camera_screen.width - (camera_screen.width * 12 / 16)) / 2; // = actual calculation, simplified below
            aspOffset = camera_screen.width / 8; // half of the difference in width between equal height 16:9 and 4:3 screens, = black bar width
        }
    }

    viewport_height = vid_get_viewport_height();

    // if not in no-zebra phase of blink mode zebra, draw zebra to buf[]
    if (f) {
        int step_x, step_v;
        over = 255-conf.zebra_over;
        if (conf.zebra_multichannel) {step_x=2; step_v=6;} else {step_x=1; step_v=3;}
        s = aspOffset;
        for (y=1, v=0; y<=viewport_height; ++y) {
            for (x=0; x<camera_screen.width; x+=step_x, s+=step_x, v+=step_v) {
                register int yy, uu, vv;
                int sel;

                if (!bWide && (x + aspOffset >= camera_screen.width - aspOffset)) continue; // do not draw "outside screen" 

                yy = img_buf[v+1];
                if (conf.zebra_multichannel) {
                    uu = (signed char)img_buf[v];
                    vv = (signed char)img_buf[v+2];
                    sel=0;
                    if (!((conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) && (y-x-timer)&f)) {
                        if (clip8(((yy<<12) +           vv*5743 + 2048)>>12)>over) sel  = 4; // R
                        if (clip8(((yy<<12) - uu*1411 - vv*2925 + 2048)>>12)>over) sel |= 2; // G
                        if (clip8(((yy<<12) + uu*7258           + 2048)>>12)>over) sel |= 1; // B
                    }
                    buf[s]=buf[s+1]=cls[sel];
                }
                else if (((conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) && (y-x-timer)&f)) buf[s]=COLOR_TRANSPARENT;
                else buf[s]=(yy>over)?cl_over:(yy<conf.zebra_under)?cl_under:COLOR_TRANSPARENT;
                if (buf[s] != COLOR_TRANSPARENT && !zebra_drawn) zebra_drawn = 1;
                if (mrec) {
                    // draw Canon OSD to buf[] if in REC mode
                    if(get_cur_buf(s)!=COLOR_TRANSPARENT) buf[s]=get_cur_buf(s); 
                    if(conf.zebra_multichannel && get_cur_buf(s+1)!=COLOR_TRANSPARENT) buf[s+1]=get_cur_buf(s+1); 
                }
            }
            s+=camera_screen.buffer_width-camera_screen.width;
            if (y*camera_screen.height/viewport_height == (s+camera_screen.buffer_width)/camera_screen.buffer_width) {
                memcpy(buf+s, buf+s-camera_screen.buffer_width, camera_screen.buffer_width);
                s+=camera_screen.buffer_width;
            }
        }
        if (!zebra_drawn) f=0;
    }
    // if blink mode is in no-zebra phase OR if there was no over/underexposed pixels to draw zebra on
    if (!f) {
        // if zebra was drawn during previous call of this function
        if (need_restore) {
            if (conf.zebra_restore_screen || conf.zebra_restore_osd) {
                gui_set_need_restore();
            } else {  // clear buf[] of zebra, only leave Canon OSD
                if (mrec) { // REC mode
                    // copy rescued Canon OSD to buf[] top/bottom parts and fill center with transparent color:
                    memcpy(buf, cur_buf_top, camera_screen.buffer_width * ZFIX_TOP);
                    memcpy(buf + buffer_size - camera_screen.buffer_width * ZFIX_BOTTOM, cur_buf_bot, camera_screen.buffer_width * ZFIX_BOTTOM);
                    for (s = camera_screen.buffer_width*ZFIX_TOP; s < buffer_size-camera_screen.buffer_width*ZFIX_BOTTOM; s++) {
                        buf[s]=COLOR_TRANSPARENT;
                    }
                } else { // Not REC mode
                    // No Canon OSD restore, fill buf[] with transparent color:
                    memset(buf, COLOR_TRANSPARENT, buffer_size);
                }
                disp_zebra();
            }
            need_restore=0;
        }
        return !(conf.zebra_restore_screen && conf.zebra_restore_osd);
        // if zebra was drawn
    } else {
        disp_zebra();

        need_restore=1;
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------
int gui_osd_draw_zebra(int show)
{
    unsigned int f;

    if (!gui_osd_zebra_init(show))
        return 0;

    color cls[] = {
        COLOR_TRANSPARENT,
        (camera_info.state.mode_rec)?COLOR_HISTO_B:COLOR_HISTO_B_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_G:COLOR_HISTO_G_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_BG:COLOR_HISTO_BG_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_R:COLOR_HISTO_R_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_RB:COLOR_HISTO_RB_PLAY,
        (camera_info.state.mode_rec)?COLOR_HISTO_RG:COLOR_HISTO_RG_PLAY,
        COLOR_BLACK
    };

    img_buf = vid_get_viewport_active_buffer();
    if (!img_buf) return 0;

    if (timer==0)
    {
        draw_guard_pixel();
        timer = 1;
        return 0;
    }

    if (timer==1)
    {
        int ready;
        static int n=0;
        if (!camera_info.state.mode_rec) ready=1;
        else get_property_case(camera_info.props.shooting, &ready, 4);
        n=draw_guard_pixel(); // will be 0 in PLAY mode, should be 1 or 2 in REC mode.
        if(!ready) return 0;
        if (cur_buf_top)
        {
            // rescue Canon OSD from scr_buf to cur_buf_top and _bot:
            if (n==1) {
                memcpy(cur_buf_top, scr_buf, camera_screen.buffer_width*ZFIX_TOP);
                memcpy(cur_buf_bot, scr_buf + camera_screen.buffer_size - camera_screen.buffer_width*ZFIX_BOTTOM, camera_screen.buffer_width*ZFIX_BOTTOM);
            }
            else {
                memcpy(cur_buf_top, scr_buf + camera_screen.buffer_size, camera_screen.buffer_width*ZFIX_TOP);
                memcpy(cur_buf_bot, scr_buf + 2*camera_screen.buffer_size - camera_screen.buffer_width*ZFIX_BOTTOM, camera_screen.buffer_width*ZFIX_BOTTOM);
            }
        }
    }
    ++timer;

    switch (conf.zebra_mode)
    {
        case ZEBRA_MODE_ZEBRA_1:    f = 4;          break;
        case ZEBRA_MODE_ZEBRA_2:    f = 8;          break;
        case ZEBRA_MODE_SOLID:      f = 1;          break;
        case ZEBRA_MODE_BLINKED_1:  f = timer&1;    break;
        case ZEBRA_MODE_BLINKED_3:  f = timer&4;    break;
        case ZEBRA_MODE_BLINKED_2:  
        default:                    f = timer&2;    break;
    }

    if (camera_screen.zebra_aspect_adjust)
        return draw_zebra_aspect_adjust(camera_info.state.mode_rec,f,cls);    // For newer cameras with 720/960 pixel wide screen
    else
        return draw_zebra_no_aspect_adjust(camera_info.state.mode_rec,f,cls); // For older cameras with 360/480 pixel wide screen
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
    gui_osd_zebra_free();
    return 0;
}

int _module_can_unload()
{
    return conf.zebra_draw == 0;
}

/******************** Module Information structure ******************/

libzebra_sym _libzebra =
{
    {
         0, _module_unloader, _module_can_unload, 0, 0
    },

    gui_osd_draw_zebra
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    ZEBRA_VERSION,				// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Zebra Overlay (dll)",// Module name
    (int32_t)"Zebra Overlay",

    &_libzebra.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
