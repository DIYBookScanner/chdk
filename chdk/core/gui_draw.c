#include "platform.h"
#include "stdlib.h"
#include "keyboard.h"
#include "touchscreen.h"
#include "conf.h"
#include "font.h"
#include "gui_draw.h"

//-------------------------------------------------------------------
void            (*draw_pixel_proc)(unsigned int offset, color cl);

#ifdef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY
extern char* bitmap_buffer[];
extern int active_bitmap_buffer;
#else
static char* frame_buffer[2];
#endif
//-------------------------------------------------------------------

static void draw_pixel_std(unsigned int offset, color cl)
{
#ifdef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY
	bitmap_buffer[active_bitmap_buffer][offset] = cl & 0xff;
#else
	frame_buffer[0][offset] = frame_buffer[1][offset] = cl & 0xff;
#endif
}

//-------------------------------------------------------------------
void draw_set_draw_proc(void (*pixel_proc)(unsigned int offset, color cl))
{
    draw_pixel_proc = (pixel_proc)?pixel_proc:draw_pixel_std;
}

//-------------------------------------------------------------------

#define GUARD_VAL   SCREEN_COLOR

void draw_set_guard()
{
#ifdef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY
    *((unsigned char*)(bitmap_buffer[0])) = GUARD_VAL;
    *((unsigned char*)(bitmap_buffer[1])) = GUARD_VAL;
#else
    *((unsigned char*)(frame_buffer[0])) = GUARD_VAL;
    *((unsigned char*)(frame_buffer[1])) = GUARD_VAL;
#endif
}

int draw_test_guard()
{
#ifdef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY
    if (*((unsigned char*)(bitmap_buffer[active_bitmap_buffer])) != GUARD_VAL) return 0;
#else
    if (*((unsigned char*)(frame_buffer[0])) != GUARD_VAL) return 0;
    if (*((unsigned char*)(frame_buffer[1])) != GUARD_VAL) return 0;
#endif
    return 1;
}

//-------------------------------------------------------------------
void draw_init()
{
#ifndef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY
    frame_buffer[0] = vid_get_bitmap_fb();
    frame_buffer[1] = frame_buffer[0] + camera_screen.buffer_size;
#endif
    draw_set_draw_proc(NULL);

    draw_set_guard();
}

// Restore CANON_OSD
//-------------------------------------------------------------------
void draw_restore()
{
    vid_bitmap_refresh();

    draw_set_guard();
#ifdef CAM_TOUCHSCREEN_UI
    redraw_buttons = 1;
#endif
}

//-------------------------------------------------------------------
void draw_pixel(coord x, coord y, color cl)
{
    // Make sure pixel is on screen. Skip top left pixel if screen erase detection is on to avoid triggering the detector.
    if ((x < 0) || (y < 0) || (x >= camera_screen.width) || (y >= camera_screen.height) || ((x == 0) && (y == 0))) return;
    else
    {
        register unsigned int offset = y * camera_screen.buffer_width + ASPECT_XCORRECTION(x);
        draw_pixel_proc(offset,   cl);
#if CAM_USES_ASPECT_CORRECTION
        draw_pixel_proc(offset+1, cl);  // Draw second pixel if screen scaling is needed
#endif
   }
}

//-------------------------------------------------------------------
color draw_get_pixel(coord x, coord y)
{
    if ((x < 0) || (y < 0) || (x >= camera_screen.width) || (y >= camera_screen.height)) return 0;
#ifdef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY
    return bitmap_buffer[0][y * camera_screen.buffer_width + ASPECT_XCORRECTION(x)];
#else
    return frame_buffer[0][y * camera_screen.buffer_width + ASPECT_XCORRECTION(x)];
#endif
}

//-------------------------------------------------------------------
#define swap(v1, v2)   {v1^=v2; v2^=v1; v1^=v2;}
//-------------------------------------------------------------------
void draw_line(coord x1, coord y1, coord x2, coord y2, color cl)
{
     unsigned char steep = abs(y2 - y1) > abs(x2 - x1);
     if (steep)
     {
         swap(x1, y1);
         swap(x2, y2);
     }
     if (x1 > x2)
     {
         swap(x1, x2);
         swap(y1, y2);
     }
     int deltax = x2 - x1;
     int deltay = abs(y2 - y1);
     int error = 0;
     int y = y1;
     int ystep = (y1 < y2)?1:-1;
     int x;
     for (x=x1; x<=x2; ++x)
     {
         if (steep) draw_pixel(y, x, cl);
         else draw_pixel(x, y, cl);
         error += deltay;
         if ((error<<1) >= deltax)
         {
             y += ystep;
             error -= deltax;
         }
     }
}

//-------------------------------------------------------------------
void draw_hline(coord x, coord y, int len, color cl)
{
    if ((y < 0) || (x >= camera_screen.width) || (y >= camera_screen.height)) return;
    if (x < 0) { len += x; x = 0; }
    if ((x + len) > camera_screen.width) len = camera_screen.width - x;
    register unsigned int offset = y * camera_screen.buffer_width + ASPECT_XCORRECTION(x);
    len = ASPECT_XCORRECTION(len);      // Scale the line length if needed
    for (; len>0; len--, offset++)
        draw_pixel_proc(offset, cl);
}

void draw_vline(coord x, coord y, int len, color cl)
{
    if ((x < 0) || (x >= camera_screen.width) || (y >= camera_screen.height)) return;
    if (y < 0) { len += y; y = 0; }
    if ((y + len) > camera_screen.height) len = camera_screen.height - y;
    for (; len>0; len--, y++)
        draw_pixel(x, y, cl);
}

//-------------------------------------------------------------------
typedef struct
{
    coord xMin, yMin, xMax, yMax;
} rectBox;

static int normalise(rectBox *r, coord x1, coord y1, coord x2, coord y2)
{
    // Normalise values
    if (x1>x2) {
        r->xMax=x1; r->xMin=x2;
    } else {
        r->xMin=x1; r->xMax=x2;
    }
    if (y1>y2) {
        r->yMax=y1; r->yMin=y2;
    } else {
        r->yMin=y1; r->yMax=y2;
    }

    // Check if completely off screen
    if ((r->xMax < 0) || (r->yMax < 0) || (r->xMin >= camera_screen.width) || (r->yMin >= camera_screen.height))
        return 0;
        
    return 1;
}

static void shrink(rectBox *r)
{
    r->xMin++; r->xMax--;
    r->yMin++; r->yMax--;
}

static void shift(rectBox *r)
{
    r->xMin++; r->xMax++;
    r->yMin++; r->yMax++;
}

static void draw_rectangle(rectBox r, color cl, int round) 
{
    // Clipping done in draw_hline and draw_vline
    draw_vline(r.xMin, r.yMin + round * 2, r.yMax - r.yMin - round * 4 + 1, cl);
    draw_vline(r.xMax, r.yMin + round * 2, r.yMax - r.yMin - round * 4 + 1, cl);
    draw_hline(r.xMin + 1 + round, r.yMin, r.xMax - r.xMin - round * 2 - 1, cl);
    draw_hline(r.xMin + 1 + round, r.yMax, r.xMax - r.xMin - round * 2 - 1, cl);
}

static void draw_rectangle_thick(rectBox r, color cl, int thickness, int round)
{
    int i;
    cl = FG_COLOR(cl);
    draw_rectangle(r,cl,round);
    for (i=1; i<thickness; i++)
    {
        shrink(&r);
        draw_rectangle(r,cl,0);
    }
}

static void fill_rect(rectBox r, color cl) 
{
    register coord y;
    
    // Clip values
    if (r.xMin < 0) r.xMin = 0;
    if (r.yMin < 0) r.yMin = 0;
    if (r.xMax >= camera_screen.width) r.xMax = camera_screen.width-1;
    if (r.yMax >= camera_screen.height) r.yMax = camera_screen.height-1;

    cl = BG_COLOR(cl);
    for (y = r.yMin; y <= r.yMax; ++y)
        draw_hline(r.xMin, y, r.xMax - r.xMin + 1, cl);
}

static void draw_filled_rectangle_thick(rectBox r, color cl, int thickness, int round)
{
    int i;
    draw_rectangle(r,FG_COLOR(cl),round);
    for (i=1; i<thickness; i++)
    {
        shrink(&r);
        draw_rectangle(r,FG_COLOR(cl),0);
    }
    shrink(&r);
    fill_rect(r, cl);
}

//-------------------------------------------------------------------
void draw_rect(coord x1, coord y1, coord x2, coord y2, color cl)
{
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_rectangle(r,FG_COLOR(cl),0);
}

void draw_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness)
{
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_rectangle_thick(r,FG_COLOR(cl),thickness,0);
}

void draw_rect_shadow(coord x1, coord y1, coord x2, coord y2, color cl, int thickness)
{
    int i;
    cl = FG_COLOR(cl);
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        for (i=0; i<thickness; i++)
        {
            draw_rectangle(r,cl,0);
            shift(&r);
        }
}

//-------------------------------------------------------------------
void draw_round_rect(coord x1, coord y1, coord x2, coord y2, color cl)
{ 
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_rectangle(r,FG_COLOR(cl),1);
} 

void draw_round_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness)
{ 
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_rectangle_thick(r,FG_COLOR(cl),thickness,1);
} 

//-------------------------------------------------------------------
void draw_filled_rect(coord x1, coord y1, coord x2, coord y2, color cl)
{
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_filled_rectangle_thick(r,cl,1,0);
}

void draw_filled_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness)
{
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_filled_rectangle_thick(r,cl,thickness,0);
}

//-------------------------------------------------------------------
void draw_filled_round_rect(coord x1, coord y1, coord x2, coord y2, color cl)
{ 
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_filled_rectangle_thick(r,cl,1,1);
} 

void draw_filled_round_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness)
{ 
    rectBox r;
    if (normalise(&r,x1,y1,x2,y2))
        draw_filled_rectangle_thick(r,cl,thickness,1);
} 

//-------------------------------------------------------------------
void draw_char(coord x, coord y, const char ch, color cl)
{
    FontData *f = (FontData*)get_current_font_data(ch);
    const unsigned char *sym = (unsigned char*)f + sizeof(FontData) - f->offset;
    int i, ii;

    // First draw blank lines at top
    for (i=0; i<f->offset; i++)
        draw_hline(x, y+i, FONT_WIDTH, BG_COLOR(cl));

    // Now draw character data
    for (; i<f->offset+f->size; i++)
    {
	    for (ii=0; ii<FONT_WIDTH; ii++)
        {
            draw_pixel(x+ii, y+i, (sym[i] & (0x80>>ii))? FG_COLOR(cl) : BG_COLOR(cl));
	    }
    }

    // Last draw blank lines at bottom
    for (; i<FONT_HEIGHT; i++)
        draw_hline(x, y+i, FONT_WIDTH, BG_COLOR(cl));
}

void draw_char_scaled(coord x, coord y, const char ch, color cl, int xsize, int ysize)
{
    color clf = MAKE_COLOR(FG_COLOR(cl),FG_COLOR(cl));
    color clb = MAKE_COLOR(BG_COLOR(cl),BG_COLOR(cl));

    FontData *f = (FontData*)get_current_font_data(ch);
    const unsigned char *sym = (unsigned char*)f + sizeof(FontData) - f->offset;
    int i, ii;

    // First draw blank lines at top
    for (i=0; i<f->offset; i++)
        draw_filled_rect(x,y+i*ysize,x+FONT_WIDTH*xsize-1,y+i*ysize+ysize-1,clb);

    // Now draw character data
    for (; i<(f->offset+f->size); i++)
    {
        unsigned char last = sym[i] & 0x80;
        int len = 1;
        for (ii=1; ii<FONT_WIDTH; ii++)
        {
            if (((sym[i] << ii) & 0x80) != last)
            {
                draw_filled_rect(x+(ii-len)*xsize,y+i*ysize,x+ii*xsize-1,y+i*ysize+ysize-1,(last)?clf:clb);
                last = (sym[i] << ii) & 0x80;
                len = 1;
            }
            else
            {
                len++;
            }
        }
        draw_filled_rect(x+(ii-len)*xsize,y+i*ysize,x+ii*xsize-1,y+i*ysize+ysize-1,(last)?clf:clb);
    }

    // Last draw blank lines at bottom
    for (; i<FONT_HEIGHT; i++)
        draw_filled_rect(x,y+i*ysize,x+FONT_WIDTH*xsize-1,y+i*ysize+ysize-1,clb);
}

//-------------------------------------------------------------------
void draw_string(coord x, coord y, const char *s, color cl)
{
    while(*s)
    {
	    draw_char(x, y, *s, cl);
	    s++;
	    x+=FONT_WIDTH;
	    if ((x>=camera_screen.width) && (*s))
        {
	        draw_char(x-FONT_WIDTH,y, '>', cl);
	        break;
	    }
    }
}

void draw_string_scaled(coord x, coord y, const char *s, color cl, int xsize, int ysize)
{
    while(*s)
    {
	    draw_char_scaled(x, y, *s, cl, xsize, ysize);
	    s++;
	    x+=FONT_WIDTH*xsize;
	    if ((x>=camera_screen.width) && (*s))
        {
	        draw_char_scaled(x-FONT_WIDTH*xsize,y, '>', cl, xsize, ysize);
	        break;
	    }
    }
}

void draw_osd_string(OSD_pos pos, int xo, int yo, char *s, color c, OSD_scale scale)
{
    if ((scale.x == 0) || (scale.y == 0) || ((scale.x == 1) && (scale.y == 1)))
        draw_string(pos.x+xo, pos.y+yo, s, c);
    else
        draw_string_scaled(pos.x+(xo*scale.x), pos.y+(yo*scale.y), s, c, scale.x, scale.y);
}

//-------------------------------------------------------------------
void draw_txt_rect(coord col, coord row, unsigned int length, unsigned int height, color cl)
{
    draw_rect(col*FONT_WIDTH, row*FONT_HEIGHT, (col+length)*FONT_WIDTH-1, (row+height)*FONT_HEIGHT-1, cl);
}

//-------------------------------------------------------------------
void draw_txt_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl)
{
    draw_rect(col*FONT_WIDTH-exp, row*FONT_HEIGHT-exp, (col+length)*FONT_WIDTH-1+exp, (row+height)*FONT_HEIGHT-1+exp, cl);
}

//-------------------------------------------------------------------
void draw_txt_filled_rect(coord col, coord row, unsigned int length, unsigned int height, color cl)
{
    draw_filled_rect(col*FONT_WIDTH, row*FONT_HEIGHT, (col+length)*FONT_WIDTH-1, (row+height)*FONT_HEIGHT-1, cl);
}

//-------------------------------------------------------------------
void draw_txt_filled_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl)
{
    draw_filled_rect(col*FONT_WIDTH-exp, row*FONT_HEIGHT-exp, (col+length)*FONT_WIDTH-1+exp, (row+height)*FONT_HEIGHT-1+exp, cl);
}

//-------------------------------------------------------------------
void draw_txt_string(coord col, coord row, const char *str, color cl)
{
    draw_string(col*FONT_WIDTH, row*FONT_HEIGHT, str, cl);
}

//-------------------------------------------------------------------
void draw_txt_char(coord col, coord row, const char ch, color cl)
{
    draw_char(col*FONT_WIDTH, row*FONT_HEIGHT, ch, cl);
}

//-------------------------------------------------------------------
void draw_circle(coord x, coord y, const unsigned int r, color cl)
{
    int dx = 0;
    int dy = r;
    int p=(3-(r<<1));

    do {
        draw_pixel((x+dx),(y+dy),cl);
        draw_pixel((x+dy),(y+dx),cl);
        draw_pixel((x+dy),(y-dx),cl);
        draw_pixel((x+dx),(y-dy),cl);
        draw_pixel((x-dx),(y-dy),cl);
        draw_pixel((x-dy),(y-dx),cl);
        draw_pixel((x-dy),(y+dx),cl);
        draw_pixel((x-dx),(y+dy),cl);

        ++dx;

        if (p<0) 
            p += ((dx<<2)+6);
        else {
            --dy;
            p += (((dx-dy)<<2)+10);
        }
    } while (dx<=dy);
}

//-------------------------------------------------------------------
void draw_ellipse(coord CX, coord CY, unsigned int XRadius, unsigned int YRadius, color cl)
{
    // Bresenham fast ellipse algorithm - http://homepage.smc.edu/kennedy_john/BELIPSE.PDF
    int X, Y;
    int XChange, YChange;
    int EllipseError;
    int TwoASquare, TwoBSquare;
    int StoppingX, StoppingY;
    TwoASquare = 2*XRadius*XRadius;
    TwoBSquare = 2*YRadius*YRadius;
    X = XRadius;
    Y = 0;
    XChange = YRadius*YRadius*(1-2*XRadius);
    YChange = XRadius*XRadius;
    EllipseError = 0;
    StoppingX = TwoBSquare*XRadius;
    StoppingY = 0;
    while ( StoppingX >= StoppingY ) 
    {
        draw_pixel(CX-X,CY-Y,cl);
        draw_pixel(CX-X,CY+Y,cl);
        draw_pixel(CX+X,CY-Y,cl);
        draw_pixel(CX+X,CY+Y,cl);
        Y++;
        StoppingY += TwoASquare;
        EllipseError += YChange;
        YChange += TwoASquare;
        if ((2*EllipseError + XChange) > 0 )
        {
            X--;
            StoppingX -= TwoBSquare;
            EllipseError += XChange;
            XChange += TwoBSquare;
        }
    }
    X = 0;
    Y = YRadius;
    XChange = YRadius*YRadius;
    YChange = XRadius*XRadius*(1-2*YRadius);
    EllipseError = 0;
    StoppingX = 0;
    StoppingY = TwoASquare*YRadius;
    while ( StoppingX <= StoppingY )
    {
        draw_pixel(CX-X,CY-Y,cl);
        draw_pixel(CX-X,CY+Y,cl);
        draw_pixel(CX+X,CY-Y,cl);
        draw_pixel(CX+X,CY+Y,cl);
        X++;
        StoppingX += TwoBSquare;
        EllipseError += XChange;
        XChange += TwoBSquare;
        if ((2*EllipseError + YChange) > 0 )
        {
            Y--;
            StoppingY -= TwoASquare;
            EllipseError += YChange;
            YChange += TwoASquare;
        }
    }
}

//-------------------------------------------------------------------
void draw_filled_ellipse(coord CX, coord CY, unsigned int XRadius, unsigned int YRadius, color cl)
{
    color cl_fill = MAKE_COLOR(BG_COLOR(cl), BG_COLOR(cl));

    // Bresenham fast ellipse algorithm - http://homepage.smc.edu/kennedy_john/BELIPSE.PDF
    int X, Y;
    int XChange, YChange;
    int EllipseError;
    int TwoASquare, TwoBSquare;
    int StoppingX, StoppingY;
    TwoASquare = 2*XRadius*XRadius;
    TwoBSquare = 2*YRadius*YRadius;
    X = XRadius;
    Y = 0;
    XChange = YRadius*YRadius*(1-2*XRadius);
    YChange = XRadius*XRadius;
    EllipseError = 0;
    StoppingX = TwoBSquare*XRadius;
    StoppingY = 0;
    while ( StoppingX >= StoppingY ) 
    {
        draw_hline(CX-X,CY-Y,X*2+1,cl_fill);
        draw_hline(CX-X,CY+Y,X*2+1,cl_fill);
        Y++;
        StoppingY += TwoASquare;
        EllipseError += YChange;
        YChange += TwoASquare;
        if ((2*EllipseError + XChange) > 0 )
        {
            X--;
            StoppingX -= TwoBSquare;
            EllipseError += XChange;
            XChange += TwoBSquare;
        }
    }
    X = 0;
    Y = YRadius;
    XChange = YRadius*YRadius;
    YChange = XRadius*XRadius*(1-2*YRadius);
    EllipseError = 0;
    StoppingX = 0;
    StoppingY = TwoASquare*YRadius;
    while ( StoppingX <= StoppingY )
    {
        X++;
        StoppingX += TwoBSquare;
        EllipseError += XChange;
        XChange += TwoBSquare;
        if ((2*EllipseError + YChange) > 0 )
        {
            draw_hline(CX-X,CY-Y,X*2+1,cl_fill);
            draw_hline(CX-X,CY+Y,X*2+1,cl_fill);
            Y--;
            StoppingY -= TwoASquare;
            EllipseError += YChange;
            YChange += TwoASquare;
        }
    }
}

//-------------------------------------------------------------------

const unsigned char const script_colors[NUM_SCRIPT_COLORS][2]  = {

    {COLOR_TRANSPARENT,         COLOR_TRANSPARENT},         //  1   trans
    {COLOR_BLACK,               COLOR_BLACK},               //  2   black
    {COLOR_WHITE,               COLOR_WHITE},               //  3   white
                                        
    {COLOR_ICON_PLY_RED,        COLOR_ICON_REC_RED},        //  4   red
    {COLOR_ICON_PLY_RED_DK,     COLOR_ICON_REC_RED_DK},     //  5   red_dark
    {COLOR_ICON_PLY_RED_LT,     COLOR_ICON_REC_RED_LT},     //  6   red_light
    {COLOR_ICON_PLY_GREEN,      COLOR_ICON_REC_GREEN},      //  7   green
    {COLOR_ICON_PLY_GREEN_DK,   COLOR_ICON_REC_GREEN_DK},   //  8   green_dark
    {COLOR_ICON_PLY_GREEN_LT,   COLOR_ICON_REC_GREEN_LT},   //  9   green_light
    {COLOR_HISTO_B_PLAY,        COLOR_HISTO_B},             //  10  blue
    {COLOR_HISTO_B_PLAY,        COLOR_HISTO_B},             //  11  blue_dark   - placeholder
    {COLOR_HISTO_B_PLAY,        COLOR_HISTO_B},             //  12  blue_light  - placeholder

    {COLOR_ICON_PLY_GREY,       COLOR_ICON_REC_GREY},       //  13  grey
    {COLOR_ICON_PLY_GREY_DK,    COLOR_ICON_REC_GREY_DK},    //  14  grey_dark
    {COLOR_ICON_PLY_GREY_LT,    COLOR_ICON_REC_GREY_LT},    //  15  grey_light

    {COLOR_ICON_PLY_YELLOW,     COLOR_ICON_REC_YELLOW},     //  16  yellow
    {COLOR_ICON_PLY_YELLOW_DK,  COLOR_ICON_REC_YELLOW_DK},  //  17  yellow_dark
    {COLOR_ICON_PLY_YELLOW_LT,  COLOR_ICON_REC_YELLOW_LT}   //  18  yellow_light
};

const unsigned char const module_colors[] = {
    SCREEN_COLOR		,
    COLOR_WHITE         ,
    COLOR_RED           ,
    COLOR_GREY          ,
    COLOR_GREEN         ,
    COLOR_BLUE_LT       ,
    COLOR_BLUE          ,
    COLOR_YELLOW        ,
    COLOR_BG            ,
    COLOR_FG            ,
    COLOR_SELECTED_BG   ,
    COLOR_SELECTED_FG   ,
    COLOR_ALT_BG        ,
    COLOR_SPLASH_RED    ,
    COLOR_SPLASH_PINK   ,
    COLOR_SPLASH_GREY   ,
    COLOR_HISTO_R       ,
    COLOR_HISTO_R_PLAY  ,
    COLOR_HISTO_B       ,
    COLOR_HISTO_G       ,
    COLOR_HISTO_G_PLAY  ,
    COLOR_HISTO_BG      ,
    COLOR_HISTO_RG      ,
    COLOR_HISTO_RB      ,
    COLOR_HISTO_RB_PLAY ,
    COLOR_HISTO_B_PLAY  ,
    COLOR_HISTO_BG_PLAY ,
    COLOR_HISTO_RG_PLAY ,
};

//-------------------------------------------------------------------

// Colors for icons
// 3 shades for each color
//  icon_xxx[0] = dark, icon_xxx[1] = medium, icon_xxx[2] = light
color icon_green[3], icon_red[3], icon_yellow[3], icon_grey[3];

void draw_get_icon_colors()
{
    if (camera_info.state.mode_rec)
    {
        icon_green[0]  = COLOR_ICON_REC_GREEN_DK;  icon_green[1]  = COLOR_ICON_REC_GREEN;  icon_green[2]  = COLOR_ICON_REC_GREEN_LT;
        icon_yellow[0] = COLOR_ICON_REC_YELLOW_DK; icon_yellow[1] = COLOR_ICON_REC_YELLOW; icon_yellow[2] = COLOR_ICON_REC_YELLOW_LT;
        icon_red[0]    = COLOR_ICON_REC_RED_DK;    icon_red[1]    = COLOR_ICON_REC_RED;    icon_red[2]    = COLOR_ICON_REC_RED_LT;
        icon_grey[0]   = COLOR_ICON_REC_GREY_DK;   icon_grey[1]   = COLOR_ICON_REC_GREY;   icon_grey[2]   = COLOR_ICON_REC_GREY_LT;
    }
    else
    {
        icon_green[0]  = COLOR_ICON_PLY_GREEN_DK;  icon_green[1]  = COLOR_ICON_PLY_GREEN;  icon_green[2]  = COLOR_ICON_PLY_GREEN_LT;
        icon_yellow[0] = COLOR_ICON_PLY_YELLOW_DK; icon_yellow[1] = COLOR_ICON_PLY_YELLOW; icon_yellow[2] = COLOR_ICON_PLY_YELLOW_LT;
        icon_red[0]    = COLOR_ICON_PLY_RED_DK;    icon_red[1]    = COLOR_ICON_PLY_RED;    icon_red[2]    = COLOR_ICON_PLY_RED_LT;
        icon_grey[0]   = COLOR_ICON_PLY_GREY_DK;   icon_grey[1]   = COLOR_ICON_PLY_GREY;   icon_grey[2]   = COLOR_ICON_PLY_GREY_LT;
    }
}
