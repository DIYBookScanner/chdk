#include "camera_info.h"
#include "conf.h"
#include "keyboard.h"
#include "modes.h"
#include "viewport.h"
#include "shooting.h"
#include "stdlib.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "bitvector.h"

#include "edgeoverlay.h"
#include "module_def.h"

//-------------------------------------------------------------------

// the way we save edge overlays on their own...
#define EDGE_FILE_PREFIX "EDG_"
#define EDGE_FILE_FORMAT EDGE_FILE_PREFIX "%04d.edg"
#define EDGE_SLICES     2

// steps for up/down/left/right moving the overlay in ALT mode
#define XINC 6
#define YINC 2

typedef enum _edge_fsm_state
{
    EDGE_LIVE = 0,
    EDGE_FROZEN
} edge_fsm_state_t;

static edge_fsm_state_t fsm_state = EDGE_LIVE;
static bit_vector_t* edgebuf = NULL;
static int xoffset = 0, yoffset = 0;
static unsigned char* smbuf = NULL;

static int slice = 0;           // the current slice of the frame we are calculating/drawing
static int slice_height;        // the height of a single slice

static int viewport_byte_width; // width in bytes of one viewport line ??
static int viewport_yscale;     // Y multiplier (for cameras with 480 pixel high viewports)
static int viewport_height;     // height of visible / used area of viewport
static int viewport_width;      // width of visible / used area of viewport (in 3 byte units)
static int viewport_xoffset;	// used when image size != viewport size (e.g. wide screen image on 4:3 LCD)
static int viewport_yoffset;	// used when image size != viewport size (e.g. wide screen image on 4:3 LCD)

static void get_viewport_size()
{
    viewport_height = vid_get_viewport_height()-camera_screen.edge_hmargin*2; //don't trace bottom lines
    viewport_width = vid_get_viewport_width();
    viewport_byte_width = vid_get_viewport_byte_width();
    viewport_yscale = vid_get_viewport_yscale();

	viewport_xoffset = vid_get_viewport_display_xoffset();
	viewport_yoffset = vid_get_viewport_display_yoffset();

    slice_height = viewport_height / EDGE_SLICES;
}

static void ensure_allocate_imagebuffer()
{
    if (edgebuf == NULL)
    {
        edgebuf = bv_create(viewport_height * viewport_width, 1);
        if (edgebuf != NULL)
            memset(edgebuf->ptr, 0, edgebuf->ptrLen);
    }
    if (conf.edge_overlay_filter && (smbuf == NULL))
    {
        smbuf = (unsigned char*)malloc(viewport_byte_width*3);
        if (smbuf != NULL)
            memset(smbuf, 0, viewport_byte_width*3);
        else
        {
            // Disable filtering if we do not have enough memory for it
            conf.edge_overlay_filter = 0;
        }
    }
}

static void reset_edge_overlay()
{
    if (smbuf != NULL)
    {
        free(smbuf);
        smbuf = NULL;
    }

    if (edgebuf != NULL)
    {
        gui_set_need_restore();     // Refresh display to restore Canon OSD
        bv_free(edgebuf);
        edgebuf = NULL;
    }

    fsm_state = EDGE_LIVE;
    slice = 0;

    // Clean up state saved in core CHDK
    module_save_edge(edgebuf, fsm_state);
}

static int is_buffer_ready()
{
    if (edgebuf == NULL) return 0;
    if (edgebuf->ptr == NULL) return 0; // this should never happen, but it does not hurt to check
    return 1;
}

// scans a filename for the number of the edge detection file it contains
static int get_edge_file_num(const char* fn)
{
    int num = 0;
    if( strncmp(fn,EDGE_FILE_PREFIX,sizeof(EDGE_FILE_PREFIX)-1) == 0 )
    {
        // has the correct beginning at least, now try to read as a number...
        fn += sizeof(EDGE_FILE_PREFIX);
        while( *fn == '0' ) // skip leading 0s
        {
            ++fn;
        }
        while( isdigit(*fn) )
        {
            num *= 10;
            num += *fn - '0';
            ++fn;
        }
        // ignore anything else after it, that is like the ending etc.
    }
    return num;
}

// saves the actual active overlay data to a file.
void save_edge_overlay(void)
{

    char fn[64];
    char msg[64];
    FILE *fd;
    DIR* d;
    int fnum = 0;
    int fr = 0;
    int zoom = 0;
    struct dirent* de;
    static struct utimbuf t;
    // nothing to save? then dont save

    if( !is_buffer_ready() )
    {
        draw_string(0, 0, "No overlay to save.", conf.osd_color);
        return;
    }

    zoom = shooting_get_zoom();

    // first figure out the most appropriate filename to use
    d = opendir(EDGE_SAVE_DIR);
    if( ! d )
    {
        return;
    }

    while( (de = readdir(d)) )
    {
        fr = get_edge_file_num(de->d_name);
        if( fr > fnum )
        {
            fnum = fr;
        }
    }
    ++fnum; // the highest is set, we use the next one
    get_viewport_size();
    // open the right file
    sprintf(fn, EDGE_SAVE_DIR "/" EDGE_FILE_FORMAT, fnum );
    fd = fopen(fn, "wb");
    if(fd !=NULL)
    {
        // write the data
        fwrite(edgebuf->ptr,edgebuf->ptrLen,1,fd);
        fwrite(&zoom,sizeof(zoom),1,fd);
        fclose(fd);
        t.actime = t.modtime = time(NULL);
        utime(fn, &t);
        sprintf(msg, "Saved as %s",fn);
        draw_string(0, 0, msg, conf.osd_color);
    }
    closedir(d);
}

// load the edge overlay from a file
void load_edge_overlay(const char* fn)
{
    FILE *fd;
    int zoom;

    get_viewport_size();
    ensure_allocate_imagebuffer( );
    fd = fopen(fn,"rb");
    if( fd != NULL )
    {
        int ret = fread(edgebuf->ptr,edgebuf->ptrLen,1,fd);
        int ret2 = fread (&zoom,sizeof(zoom),1,fd);
        fclose(fd);
        if( (ret == 1) && (ret2 == 1) )
        {
            fsm_state = EDGE_FROZEN;    // switch to "edge overlay frozen"-mode
            if (conf.edge_overlay_zoom)
            {
                shooting_set_zoom(zoom);
            }
        }
    }
}

static void average_filter_row(const unsigned char* ptrh1,  // previous row
                               unsigned char* smptr,        // write results here
                               int x, int x_max)
{
    const unsigned char* ptrh2 = ptrh1 + viewport_byte_width*viewport_yscale;  // current row
    const unsigned char* ptrh3 = ptrh2 + viewport_byte_width*viewport_yscale;  // next row

    for (; x<x_max; x+=6)
    {
        *(smptr + x + 1) = (*(ptrh1 + x - 1) +
                            *(ptrh1 + x + 1) +
                            *(ptrh1 + x + 3) +

                            *(ptrh2 + x - 1) +
                            *(ptrh2 + x + 1) +
                            *(ptrh2 + x + 3) +

                            *(ptrh3 + x - 1) +
                            *(ptrh3 + x + 1) +
                            *(ptrh3 + x + 3)) / 9u;

        *(smptr + x + 3) = (*(ptrh1 + x + 1) +
                            *(ptrh1 + x + 3) +
                            *(ptrh1 + x + 4) +

                            *(ptrh2 + x + 1) +
                            *(ptrh2 + x + 3) +
                            *(ptrh2 + x + 4) +

                            *(ptrh3 + x + 1) +
                            *(ptrh3 + x + 3) +
                            *(ptrh3 + x + 4)) / 9u;

        *(smptr + x + 4) = (*(ptrh1 + x + 3) +
                            *(ptrh1 + x + 4) +
                            *(ptrh1 + x + 5) +

                            *(ptrh2 + x + 3) +
                            *(ptrh2 + x + 4) +
                            *(ptrh2 + x + 5) +

                            *(ptrh3 + x + 3) +
                            *(ptrh3 + x + 4) +
                            *(ptrh3 + x + 5)) / 9u;

        *(smptr + x + 5) = (*(ptrh1 + x + 4) +
                            *(ptrh1 + x + 5) +
                            *(ptrh1 + x + 7) +

                            *(ptrh2 + x + 4) +
                            *(ptrh2 + x + 5) +
                            *(ptrh2 + x + 7) +

                            *(ptrh3 + x + 4) +
                            *(ptrh3 + x + 5) +
                            *(ptrh3 + x + 7)) / 9u;
    }

    // copy 2nd last column to last column to prevent vertical stripe artifact.
    smptr[x+1] = smptr[x-5];
    smptr[x+3] = smptr[x-3];
    smptr[x+4] = smptr[x-2];
    smptr[x+5] = smptr[x-1];
}

// Sobel edge detector
static int calc_edge_overlay()
{
    int shutter_fullpress = kbd_is_key_pressed(KEY_SHOOT_FULL);

    const unsigned char* img = vid_get_viewport_active_buffer();
    if (!img) return shutter_fullpress;

    const unsigned char*  ptrh1 = NULL;    // previous pixel line
    const unsigned char*  ptrh2 = NULL;    // current pixel line
    const unsigned char*  ptrh3 = NULL;    // next pixel line
    unsigned char*  smptr = NULL;    // pointer to line in smbuf
    int x, y, xdiv3;
    int conv1, conv2;

    const int y_min = camera_screen.edge_hmargin+ slice   *slice_height;
    const int y_max = camera_screen.edge_hmargin+(slice+1)*slice_height;
    const int x_min = 6;
    const int x_max = (viewport_width - 2) * 3;

    img += vid_get_viewport_image_offset();		// offset into viewport for when image size != viewport size (e.g. 16:9 image on 4:3 LCD)

    xoffset = 0;
    yoffset = 0;

    // Reserve buffers
    ensure_allocate_imagebuffer();
    if( !is_buffer_ready() ) return 0;

    // In every 6 bytes the Y of four pixels are described in the
    // viewport (UYVYYY format). For edge detection we only
    // consider the second in the current and the first
    // in the next pixel.

    // Clear all edges in the current slice
    int compressed_slice = edgebuf->ptrLen / EDGE_SLICES;
    memset(edgebuf->ptr + slice*compressed_slice, 0, compressed_slice);

    if (conf.edge_overlay_filter)
    {
        // Prefill smbuf with three lines of avergae-filtered data.
        // This looks much more complex then it actually is.
        // We really are just summing up nine pixels in a 3x3 box
        // and averaging the current pixel based on them. And
        // we do it 4 bytes at a time because of the UYVYYY format.
        for (y = -1; y <= 1; ++y)
        {
            shutter_fullpress |= kbd_is_key_pressed(KEY_SHOOT_FULL);

            ptrh1 = img + (y_min+y-1) * viewport_byte_width*viewport_yscale;
            smptr = smbuf + (y+1) * viewport_byte_width;

            average_filter_row(ptrh1, smptr, x_min, x_max);
        }
    }

    for (y = y_min; y < y_max; ++y)
    {
        shutter_fullpress |= kbd_is_key_pressed(KEY_SHOOT_FULL);

        if (conf.edge_overlay_filter)
        {
            // We need to shift up our smbuf one line,
            // and fill in the last line (which now empty)
            // with average-filtered data from img.
            // By storing only three lines of smoothed picture
            // in memory, we save memory.

            // Shift
            memcpy(smbuf, smbuf+viewport_byte_width, viewport_byte_width*2);

            // Filter new line
            ptrh1 = img + y * viewport_byte_width*viewport_yscale;
            smptr = smbuf + 2 * viewport_byte_width;
            average_filter_row(ptrh1, smptr, x_min, x_max);

            ptrh1 = smbuf;
        }
        else
        {
            ptrh1 = img + (y-1) * viewport_byte_width*viewport_yscale;
        }
        ptrh2 = ptrh1 + viewport_byte_width*viewport_yscale;
        ptrh3 = ptrh2 + viewport_byte_width*viewport_yscale;

        // Now we do sobel on the current line

        for (x = x_min, xdiv3 = x_min/3; x < x_max; x += 6, xdiv3 += 2)
        {
            // convolve vert (second Y)
            conv1 = *(ptrh1 + x + 1) * ( 1) +
                    *(ptrh1 + x + 4) * (-1) +

                    *(ptrh2 + x + 1) * ( 2) +
                    *(ptrh2 + x + 4) * (-2) +

                    *(ptrh3 + x + 1) * ( 1) +
                    *(ptrh3 + x + 4) * (-1);
            if  (conv1 < 0)     // abs()
                conv1 = -conv1;

            // convolve vert (first Y of next pixel)
            conv2 = *(ptrh1 + x + 1) * ( 1) +
                    *(ptrh1 + x + 3) * ( 2) +
                    *(ptrh1 + x + 4) * ( 1) +

                    *(ptrh3 + x + 1) * (-1) +
                    *(ptrh3 + x + 3) * (-2) +
                    *(ptrh3 + x + 4) * (-1);
            if  (conv2 < 0)     // abs()
                conv2 = -conv2;

            if (conv1 + conv2 > conf.edge_overlay_thresh)
            {
                bv_set(edgebuf, (y-camera_screen.edge_hmargin)*viewport_width + xdiv3, 1);
            }

            // Do it once again for the next 'pixel'

            // convolve vert (second Y)
            conv1 = *(ptrh1 + x + 5) * ( 1) +
                    *(ptrh1 + x + 9) * (-1) +

                    *(ptrh2 + x + 5) * ( 2) +
                    *(ptrh2 + x + 9) * (-2) +

                    *(ptrh3 + x + 5) * ( 1) +
                    *(ptrh3 + x + 9) * (-1);
            if  (conv1 < 0)     // abs()
                conv1 = -conv1;

            // convolve vert (first Y of next pixel)
            conv2 = *(ptrh1 + x + 5) * ( 1) +
                    *(ptrh1 + x + 7) * ( 2) +
                    *(ptrh1 + x + 9) * ( 1) +

                    *(ptrh3 + x + 5) * (-1) +
                    *(ptrh3 + x + 7) * (-2) +
                    *(ptrh3 + x + 9) * (-1);
            if  (conv2 < 0)     // abs()
                conv2 = -conv2;

            if (conv1 + conv2 > conf.edge_overlay_thresh)
            {
                bv_set(edgebuf, (y-camera_screen.edge_hmargin)*viewport_width + xdiv3+1, 1);
            }
        }   // for x
    }   // for y


//  For an even more improved edge overlay, enabling the following lines will
//  post-filter the results of the edge detection, removing false edge 'dots'
//  from the display. However, the speed hit is large. In the developer's opinion
//  this code is not needed, but if you want that additional quality and do not
//  care so much about performance, you can enable it.
//
//    if (conf.edge_overlay_filter)
//    {
//        // Here we do basic filtering on the detected edges.
//        // If a pixel is marked as edge but just a few of its
//        // neighbors are also edges, then we assume that the
//        // current pixel is just noise and delete the mark.
//
//        bit_vector_t* bv_tmp = bv_create(edgebuf->nElem, edgebuf->nBits);
//        if (bv_tmp != NULL)
//        {
//            memset(bv_tmp->ptr, 0, bv_tmp->ptrLen);
//
//            for (y = 1; y < viewport_height-1; ++y)
//            {
//                shutter_fullpress |= kbd_is_key_pressed(KEY_SHOOT_FULL);
//
//                for (x=12; x<(viewport_width - 4); ++x)
//                {
//                    int bEdge = bv_get(edgebuf, y*viewport_width + x);
//                    if (bEdge)
//                    {
//                        // Count the number of neighbor edges
//                        int sum =
//                            bv_get(edgebuf, (y-1)*viewport_width + (x-1)) +
//                            bv_get(edgebuf, (y-1)*viewport_width + (x)) +
//                            bv_get(edgebuf, (y-1)*viewport_width + (x+1)) +
//
//                            bv_get(edgebuf, (y)*viewport_width + (x-1)) +
////              bv_get(&edgebuf, (y)*viewport_width + (x)) + //  we only inspect the neighbors
//                            bv_get(edgebuf, (y)*viewport_width + (x+1)) +
//
//                            bv_get(edgebuf, (y+1)*viewport_width + (x-1)) +
//                            bv_get(edgebuf, (y+1)*viewport_width + (x)) +
//                            bv_get(edgebuf, (y+1)*viewport_width + (x+1));
//
//                        if (!conf.edge_overlay_show)
//                        {
//                            if (sum >= 5)    // if we have at least 5 neighboring edges
//                                bv_set(bv_tmp, y*viewport_width + x, 1);   // keep the edge
//                            // else
//                            // there is no need to delete because the buffer is already zeroed
//                        }
//                    }
//                }   // for x
//            }   // for y
//
//            // Swap the filtered edge buffer for the real one
//            bit_vector_t* swap_tmp = edgebuf;
//            edgebuf = bv_tmp;
//            bv_free(swap_tmp);
//        }   // NULL-check
//    }   // if filtering

    return shutter_fullpress;
}

static int draw_edge_overlay()
{
    int shutter_fullpress = kbd_is_key_pressed(KEY_SHOOT_FULL);

    int x, y;
    int x_off, y_off;

    const color cl = conf.edge_overlay_color;
    const int y_slice_min = camera_screen.edge_hmargin+ slice   *slice_height;
    const int y_slice_max = camera_screen.edge_hmargin+(slice+1)*slice_height;
    const int y_min = camera_screen.edge_hmargin;
    const int y_max = camera_screen.edge_hmargin+viewport_height;
    const int x_min = 2;
    const int x_max = (viewport_width - 2);

    if( !is_buffer_ready() ) return 0;

    for (y = y_slice_min; y < y_slice_max; ++y)
    {
        y_off = y + yoffset;
        
        shutter_fullpress |= kbd_is_key_pressed(KEY_SHOOT_FULL);

        if ((unsigned)(y_off-y_min) < (y_max-y_min)) // is the same as ((y_off > y_min) && (y_off < y_max)) // do not draw outside of allowed area
        {
            const int y_edgebuf = (y-y_min) * viewport_width;

            for (x = x_min; x < x_max; ++x)
            {
                x_off = x + xoffset;

                if ((unsigned)(x_off-x_min) < (x_max-x_min)) // is the same as  ((x_off > x_min) && (x_off < x_max)) // do not draw outside of allowed area
                {
                    // Draw a pixel to the screen wherever we detected an edge.
                    // If there is no edge based on the newest data, but there is one painted on the screen
                    // from previous calls, delete it from the screen.
                    const int bEdge = bv_get(edgebuf, y_edgebuf + x);
                    const int bDraw = bEdge || (draw_get_pixel(x_off+viewport_xoffset, y_off+viewport_yoffset) == conf.edge_overlay_color);
                    const color cl = bEdge ? conf.edge_overlay_color : 0;
                    if (bEdge || bDraw)
                        draw_pixel(x_off+viewport_xoffset, y_off+viewport_yoffset, cl);
                    
                }
            }   // for x
        }
    }   // for y


    // Drawing the overlay is over.
    // But as a finishing touch we clear up garbage on the screen
    // by clearing those parts that the overlay has left.

    if (xoffset != 0)
    {
        // Cleans up leftover from horizontal motion

        const int x_min_c = (xoffset < 0) ? x_max + xoffset : x_min;
        const int x_max_c = (xoffset > 0) ? x_min + xoffset : x_max;

        for (y = y_min; y < y_max; ++y)
        {
            for (x = x_min_c; x < x_max_c; ++x)
            {
                // if there is an edge drawn on the screen but there is no edge there based on the newest data, delete it from the screen
                if (draw_get_pixel(x+viewport_xoffset, y+viewport_yoffset) == cl)
                    draw_pixel(x+viewport_xoffset, y+viewport_yoffset, 0 );
            }
        }
    }

    if (yoffset != 0)
    {
        // Cleans up leftover from vertical motion

        const int y_min_c = (yoffset < 0) ? y_max + yoffset : y_min;
        const int y_max_c = (yoffset > 0) ? y_min + yoffset : y_max;

        for (y = y_min_c; y < y_max_c; ++y)
        {
            for (x = x_min; x < x_max; ++x)
            {
                // if there is an edge drawn on the screen but there is no edge there based on the newest data, delete it from the screen
                if (draw_get_pixel(x+viewport_xoffset, y+viewport_yoffset) == cl)
                    draw_pixel(x+viewport_xoffset, y+viewport_yoffset, 0 );
            }
        }
    }

    return shutter_fullpress;
}

static void set_offset_from_overlap()
{
    const int y_max = viewport_height;
    const int x_max = (viewport_width - 2);

    switch(conf.edge_overlay_pano)
    {
    case 0:     // pano off
        xoffset = 0;
        yoffset = 0;
        break;
    case 1:     // pano from left to right
        xoffset = -x_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 2:     // pano from top to bottom
        yoffset = -y_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 3:     // pano from right to left
        xoffset = x_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 4:     // pano from bottom to top
        yoffset = y_max*(100-conf.edge_overlay_pano_overlap)/100;
        break;
    case 5:     // free mode
    default:
        // free mode: change position with "ALT" and cursor
        // nothing to do here.
        break;
    }
}


// Main edge overlay function.
// It works by detecting edges using the Sobel operator
// (calc_edgeoverlay()), the detected edges are then stored into an
// array of 1-bit elements. A set bit indicates that there is an
// edge and that it should be drawn onto the overlay.
// When needed, the 1-bit edge buffer is drawn onto the screen
// (dynamically decompressing it) using draw_edge_overlay().
void edge_overlay()
{
    // Was the shutter fully pressed the last time we ran?
    // We use this to make sure that the user has released
    // the button before processing the next FullPress event.
    // This prevents switching FSM states more than once
    // per press.
    static int bFullPress_prev = 0;

    // Have we already started taking pictures in panorama mode?
    // We use this variable to be able to detect if panorama
    // mode has been turned off.
    static int bPanoInProgress = 0;

    // Precalculate some values to make the rest of the
    // code easier to read.
    int bFullPress = kbd_is_key_pressed(KEY_SHOOT_FULL);
    const int bHalfPress = camera_info.state.is_shutter_half_press;
    const int bPlayMode = camera_info.state.mode_play;
    const int bPanoramaMode = (conf.edge_overlay_pano != 0);
    const int bNeedHalfPress = (conf.edge_overlay_show != 1);
    const int bDisplayInPlay = (conf.edge_overlay_play == 1);
    const int bCanDisplay = (
                                (!bPlayMode && (bHalfPress || !bNeedHalfPress)) ||   // we have a HalfPress in rec-mode
                                ( bPlayMode && bDisplayInPlay)  // or we are in play-mode with the right settings
                            );

    if (bPanoInProgress && !bPanoramaMode)
    {
        // This means panorama mode has been recently
        // turned off in the menu. So let's release
        // Frozen mode for the user.
        reset_edge_overlay();
        bPanoInProgress = 0;
    }

    get_viewport_size();

    // For just two states a state machine is not actually needed.
    // But it is scalable in the future in case anybody
    // wants to extend the functionality of edge overlay.
    switch (fsm_state)
    {
    case EDGE_LIVE:
    {
        camera_info.state.edge_state_draw=0;
        // In this state we assume no edge overlay in memory,
        // but we are ready to create one if the user presses wishes so.

        int bRealtimeUpdate = bCanDisplay && (camera_info.state.gui_mode_alt || camera_info.state.gui_mode_none);
        if (bRealtimeUpdate)
        {
            // We try to detect button presses during the lengthy
            // calculations.
            bFullPress |= calc_edge_overlay();
            bFullPress |= draw_edge_overlay();
        }

        int bSwitch2Frozen = bFullPress && !bFullPress_prev && camera_info.state.gui_mode_none;
        if (bSwitch2Frozen)
        {
            // Switch to Frozen mode

            // Make sure we have one whole consistent frame
            for (slice = 0; slice < EDGE_SLICES; ++slice)
                calc_edge_overlay();

            set_offset_from_overlap();
            fsm_state = EDGE_FROZEN;
            bPanoInProgress = bPanoramaMode;
        }

        if (!bRealtimeUpdate && !bSwitch2Frozen)
        {
            // Nothing happens. So do nothing.
            // Or rather, we could clean up if we are that bored.
            reset_edge_overlay();
        }
        break;
    }
    case EDGE_FROZEN:
    {
        camera_info.state.edge_state_draw=1;
        // We have a stored edge overlay in memory and we display
        // it on screen in 'frozen' mode.

        // Move edge overlay around.
        if (camera_info.state.gui_mode_alt)
        {
            if (kbd_is_key_pressed(KEY_RIGHT))
                xoffset +=XINC;
            if (kbd_is_key_pressed(KEY_LEFT))
                xoffset -=XINC;
            if (kbd_is_key_pressed(KEY_DOWN))
                yoffset +=YINC;
            if (kbd_is_key_pressed(KEY_UP))
                yoffset -=YINC;
        }

        if (bCanDisplay && (camera_info.state.gui_mode_alt || camera_info.state.gui_mode_none))
        {
            // We try to detect button presses during the lengthy
            // calculations.
            bFullPress |= draw_edge_overlay();
            //draw_string(0, 0, "Frozen", conf.osd_color);
        }

        // In event of a FullPress, we either capture a new
        // overlay and stay frozen, OR we go back to live mode.
        if (bFullPress && !bFullPress_prev && camera_info.state.gui_mode_none)
        {
            // Possible mode switch
            if (bPanoramaMode)
            {
                // Make sure we have one whole consistent frame
                for (slice = 0; slice < EDGE_SLICES; ++slice)
                    calc_edge_overlay();

                set_offset_from_overlap();
                bPanoInProgress = 1;
            }
            else
                fsm_state = EDGE_LIVE;
        }

        break;
    }   // case
    }   // switch


    bFullPress_prev = bFullPress;

    if (++slice >= EDGE_SLICES)
        slice = 0;

}   // function


// =========  MODULE INIT =================

#include "module_def.h"

/***************** BEGIN OF AUXILARY PART *********************
ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
**************************************************************/

//---------------------------------------------------------
// PURPOSE:   Perform on-load initialisation
// RETURN VALUE: 1 error, 0 ok
//---------------------------------------------------------
int _module_loader( unsigned int* chdk_export_list )
{
    module_restore_edge((void**)&edgebuf, (int*)&fsm_state);
    return 0;
}


//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    // Save state info
    module_save_edge(edgebuf, fsm_state);

    // Module can be unloaded when menu exits
    // Free filter buffer
    if (smbuf != NULL)
    {
        free(smbuf);
        smbuf = NULL;
    }

    return 0;
}

int _module_can_unload()
{
    return conf.edge_overlay_enable == 0;
}

/******************** Module Information structure ******************/

libedgeovr_sym _libedgeovr = 
{
    {
         _module_loader, _module_unloader, _module_can_unload, 0, 0
    },

    edge_overlay,
    load_edge_overlay,
    save_edge_overlay,
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    EDGEOVERLAY_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Edge Overlay (dll)",// Module name
    (int32_t)"Implementation one of core modes",

    &_libedgeovr.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
