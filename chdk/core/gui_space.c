#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "sd_card.h"
#include "gui_draw.h"
#include "gui_space.h"
//-------------------------------------------------------------------

static char osd_buf[32];

//-------------------------------------------------------------------

unsigned long get_space_perc() {
    return GetFreeCardSpaceKb()*100/GetTotalCardSpaceKb();
}

// Local variables used by various space display functions, setup in space_color
static color cl;
static coord xx, yy;
static int perc, width, height;

// Set up color and percent free variables for free space OSD
static void space_color()
{
    perc = get_space_perc();
    cl = conf.space_color;
    if (((conf.space_warn_type == 0) && (perc <= conf.space_perc_warn)) ||
        ((conf.space_warn_type == 1) && (GetFreeCardSpaceKb() <= conf.space_mb_warn*1024)))
    {
        cl = conf.osd_color_warn;
    }
}

// Setup position and size variables then draw free space bar, outer shape
static void spacebar_outer(OSD_pos pos, int w, int h)
{
    // Get color and percent free
    space_color();

    // space icon / bar position
    xx = pos.x;
    yy = pos.y;

    // space icon / bar size
    width = w;
    height = h;

    // Clamp co-ordinates to keep bar on screen
    if (xx > (camera_screen.width-width-4)) {
        xx = camera_screen.width-width-4;
    }
    if (yy > (camera_screen.height-height-4)) {
        yy = camera_screen.height-height-4;
    }

    draw_rect(xx, yy, xx+width+3, yy+height+3, COLOR_BLACK);     // Outer black rectangle
    draw_rect(xx+1, yy+1, xx+width+2, yy+height+2, cl);          // Inner white/red rectangle
}

static void gui_space_draw_spacebar_horizontal() {
    coord x;

    // Setup and draw outer shape
    spacebar_outer(conf.space_hor_pos, (camera_screen.width / (4 >> conf.space_bar_size)) - 4, conf.space_bar_width);

    // space bar fill
    x = width - ((perc*width)/100);
    if (x < 1) x = 1;
    if (x >= width) x = width;
    else draw_filled_rect(xx+x+2, yy+2, xx+width+1, yy+height+1, MAKE_COLOR(cl, cl));               // If not empty fill 'free' space area
    draw_filled_rect(xx+2, yy+2, xx+x+1, yy+height+1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_BLACK));  // fill 'used' space area
}

static void gui_space_draw_spacebar_vertical() {
    coord y;

    // Setup and draw outer shape
    spacebar_outer(conf.space_ver_pos, conf.space_bar_width, (camera_screen.height / (4 >> conf.space_bar_size)) - 4);

    // space bar fill
    y = height - ((perc*height)/100);
    if (y < 1) y = 1;
    if (y >= height) y = height;
    else draw_filled_rect(xx+2, yy+y+2, xx+width+1, yy+height+1, MAKE_COLOR(cl, cl));               // If not empty fill 'free' space area
    draw_filled_rect(xx+2, yy+2, xx+width+1, yy+y+1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_BLACK));   // fill 'used' space area
}

static void gui_space_draw_icon() {
    register coord xx, yy;

    xx = conf.space_icon_pos.x;
    yy = conf.space_icon_pos.y;

    space_color();

    draw_get_icon_colors();

    color cl1 = icon_green[0];
    color cl2 = icon_green[1];
    if (((conf.space_warn_type == 0) && (perc <= conf.space_perc_warn)) ||
        ((conf.space_warn_type == 1) && (GetFreeCardSpaceKb() <= conf.space_mb_warn*1024)))
    {
    cl1 = icon_red[0];
    cl2 = icon_red[1];
    } 
  
    //icon
    draw_hline(xx,    yy,    30,  icon_grey[2]);
    draw_vline(xx,    yy,    13,  icon_grey[2]);
    draw_vline(xx+31, yy,    19,  icon_grey[1]);
    draw_line(xx+1,   yy+13, xx+5, yy+17, icon_grey[1]);
    draw_hline(xx+6,  yy+18, 24,  icon_grey[1]);
           
    draw_filled_rect(xx+1,  yy+1,   xx+30,   yy+13,  MAKE_COLOR(icon_grey[0], icon_grey[0]));
    draw_filled_rect(xx+5,  yy+14,  xx+30,   yy+17,  MAKE_COLOR(icon_grey[0], icon_grey[0]));
    draw_filled_rect(xx+3,  yy+14,  xx+6,    yy+15,  MAKE_COLOR(icon_grey[0], icon_grey[0]));
    
    draw_filled_rect(xx+2,  yy+2,   xx+6,    yy+4,   MAKE_COLOR(icon_yellow[0], icon_yellow[0]));
    draw_filled_rect(xx+2,  yy+6,   xx+6,    yy+7,   MAKE_COLOR(icon_yellow[0], icon_yellow[0]));
    draw_filled_rect(xx+2,  yy+9,   xx+6,    yy+10,  MAKE_COLOR(icon_yellow[0], icon_yellow[0]));
    draw_filled_rect(xx+2,  yy+12,  xx+6,    yy+13,  MAKE_COLOR(icon_yellow[0], icon_yellow[0]));
    draw_filled_rect(xx+5,  yy+15,  xx+9,    yy+16,  MAKE_COLOR(icon_yellow[0], icon_yellow[0]));
    
    draw_hline(xx+8,  yy,    2, COLOR_TRANSPARENT);
    draw_hline(xx+11, yy,    3, COLOR_WHITE);
    draw_hline(xx+11, yy+18, 2, COLOR_TRANSPARENT);

    //fill icon
    draw_rect(xx+9,         yy+5,   xx+28,   yy+13,  cl1);
    draw_filled_rect(xx+27-(17*perc/100),    yy+6,   xx+27,   yy+12,   MAKE_COLOR(cl2, cl2));
}

//-------------------------------------------------------------------
static void gui_space_draw_value(int force)
{
    int offset = 0;

    space_color();

    if ((conf.show_partition_nr) && (get_part_count() > 1))
    {
        sprintf(osd_buf, "%1d:\0", get_active_partition());
        offset = 2;
    }

    if (is_partition_changed())
    {
        sprintf(osd_buf+offset, "???\0");
    }
    else
    {
        if (conf.space_perc_show || force)
        {
            sprintf(osd_buf+offset, "%3d%%\0", perc);
        }
        else if (conf.space_mb_show)
        {
            unsigned int freemb = GetFreeCardSpaceKb()/1024;
            if (freemb < 10000) sprintf(osd_buf+offset, "%4d%M\0",freemb);
            else sprintf(osd_buf+offset, "%4d%G\0",freemb/1024);   // if 10 GiB or more free, print in GiB instead of MiB
        }
    }

    draw_osd_string(conf.space_txt_pos, 0, 0, osd_buf, cl, conf.space_txt_scale);
}

//-------------------------------------------------------------------

void gui_space_draw_osd(int is_osd_edit)
{
    if (conf.space_icon_show || is_osd_edit)
        gui_space_draw_icon();

    if (conf.space_perc_show || conf.space_mb_show || is_osd_edit)
        gui_space_draw_value(is_osd_edit);

    if ((conf.space_bar_show == 1) || is_osd_edit)
        gui_space_draw_spacebar_horizontal();

    if (conf.space_bar_show == 2 || is_osd_edit)
        gui_space_draw_spacebar_vertical();
}
