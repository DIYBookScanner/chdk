#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "viewport.h"
#include "ptp_chdk.h"
#include "live_view.h"

/*
send selected data for live view
returns 0 on error, total size on success
should only be called from ptp handler
*/
int live_view_get_data(ptp_data *data, int flags) {
    int vp_size = 0,bm_size = 0,pal_size = 0;
    lv_data_header *lv;
    lv_framebuffer_desc *vp;
    lv_framebuffer_desc *bm;

    // determine if we will send palette so it can go in one send
    if ( flags & LV_TFR_PALETTE ) // bitmap palette
    {
        // if no palette, will be set to zero
        pal_size = vid_get_palette_size();
    }
    
    // one contiguous buffer to allow a single send call
    int buf_size = sizeof(lv_data_header) + sizeof(lv_framebuffer_desc)*2 + pal_size;
    void *buf = malloc(buf_size);
    if(!buf) {
        return 0;
    }
    lv = buf;

    lv->vp_desc_start = sizeof(lv_data_header);
    lv->bm_desc_start = lv->vp_desc_start+sizeof(lv_framebuffer_desc);

    vp = buf + lv->vp_desc_start;
    bm = buf + lv->bm_desc_start;

    lv->version_major = LIVE_VIEW_VERSION_MAJOR;
    lv->version_minor = LIVE_VIEW_VERSION_MINOR;

    lv->lcd_aspect_ratio = vid_get_aspect_ratio();

    lv->palette_type = vid_get_palette_type();
    lv->palette_data_start = 0;


    vp->fb_type = LV_FB_YUV8;
    vp->buffer_width = vid_get_viewport_buffer_width_proper();

    vp->visible_width = vid_get_viewport_width_proper();
    vp->visible_height = vid_get_viewport_height_proper();

    vp->margin_left = vid_get_viewport_display_xoffset_proper();
    vp->margin_top = vid_get_viewport_display_yoffset_proper();

    // TODO returning margins from lib.c might be better
    // can end up with negative if size and offset sources don't update at exactly the same time
    vp->margin_right = vid_get_viewport_fullscreen_width() - vp->visible_width - vp->margin_left;
    vp->margin_bot = vid_get_viewport_fullscreen_height() - vp->visible_height - vp->margin_top;

    bm->fb_type = LV_FB_PAL8;
    bm->buffer_width = camera_screen.buffer_width;

    bm->margin_left = 0;
    bm->margin_top = 0;
    bm->margin_right = 0;
    bm->margin_bot = 0;

    bm->visible_width = camera_screen.physical_width;
    bm->visible_height = camera_screen.height;


    vp->data_start = 0;
    bm->data_start = 0;

    int total_size = buf_size;

    void *vp_fb = vid_get_viewport_active_buffer();
    // Add viewport details if requested, and not null
    if ( flags & LV_TFR_VIEWPORT && vp_fb) // live buffer
    {
        vp->data_start = total_size;
        vp_size = (vp->buffer_width*vp->visible_height*6)/4;
        total_size += vp_size;
        // offset to start of actual data
        vp_fb += vid_get_viewport_image_offset();
    }

    // Add bitmap details if requested
    if ( flags & LV_TFR_BITMAP ) // bitmap buffer
    {
        bm->data_start = total_size;
        bm_size = bm->buffer_width*bm->visible_height;
        total_size += bm_size;
    }

    // Add palette detals if requested and available
    if ( pal_size ) // bitmap palette
    {
        lv->palette_data_start = buf_size - pal_size;
        memcpy(buf + lv->palette_data_start,vid_get_bitmap_active_palette(),pal_size);
    }

    // Send header structure (along with total size to be sent)
    data->send_data(data->handle,(char*)buf,buf_size,total_size,0,0,0);

    // Send viewport data if requested
    if ( vp_size )
    {
        data->send_data(data->handle,vp_fb,vp_size,0,0,0,0);
    }

    // Send bitmap data if requested
    if ( bm_size )
    {
        data->send_data(data->handle,vid_get_bitmap_active_buffer(),bm_size,0,0,0,0);
    }

    free(buf);
    return total_size;
}
