#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_grid.h"
#include "fileutil.h"

#include "module_def.h"

//-------------------------------------------------------------------
#define GRID_REDRAW_INTERVAL        4

//-------------------------------------------------------------------
typedef enum {
    GRID_ELEM_LINE,
    GRID_ELEM_RECT,
    GRID_ELEM_FILLED_RECT,
    GRID_ELEM_ELLIPSE,
    GRID_ELEM_FILLED_ELLIPSE,
} grid_elem_type;

struct gline {
    grid_elem_type      type;
    coord               x0,y0,x1,y1;
    color               clf, clb;
    struct gline        *next;
};

static int interval = GRID_REDRAW_INTERVAL;
static struct gline *head=NULL, *top=NULL;
static const char *grid_default =
    "@title Default grid\n"
    "@line 0,79,359,79,17\n"
    "@line 0,160,359,160,17\n";

//-------------------------------------------------------------------
static void grid_lines_free_data() {
    struct gline  *ptr = head, *prev;

    while (ptr) {
        prev=ptr;
        ptr=ptr->next;
        free(prev);
    }
    head=top=NULL;
}

//-------------------------------------------------------------------
static void process_title(const char *title) {
    register const char *ptr = title;
    register int i=0;

    while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
    while (i<(sizeof(conf.grid_title)-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n') {
        conf.grid_title[i]=ptr[i];
        ++i;
    }
    conf.grid_title[i]=0;
}

//-------------------------------------------------------------------
static void process_element(const char *str, int n, grid_elem_type type) {
    register const char *ptr = str;
    char *nptr;
    register int i;
    long nums[6];
    struct gline  *gptr;

    for (i=0; i<(sizeof(nums)/sizeof(nums[0])) && i<n; ++i) {
        while (ptr[0]==' ' || ptr[0]=='\t' || ptr[0]==',') ++ptr; // whitespaces
        nums[i] = strtol(ptr, &nptr, 0);
        if (nptr == ptr) { // error
            return;
        } else {
            ptr = nptr;
        }
    }

    gptr = malloc(sizeof(struct gline));
   
    if (gptr) {
      gptr->type=type;
      gptr->x0=nums[0];  gptr->y0=nums[1];
      gptr->x1=nums[2];  gptr->y1=nums[3];
      gptr->clf=nums[4]; gptr->clb=nums[5];
      if (!head) head=gptr;
      if (top) top->next=gptr;
      gptr->next=NULL;
      top=gptr;
    }
}

//-------------------------------------------------------------------
static int parse_grid_file(char *ptr, int size)
{
    if (size > 0)
    {
        grid_lines_free_data();

        while (ptr[0])
        {
            while (ptr[0]==' ' || ptr[0]=='\t') ++ptr; // whitespaces
            if (ptr[0]=='@')
            {
                if (strncmp("@title", ptr, 6)==0) {
                    ptr+=6;
                    process_title(ptr);
                } else if (strncmp("@line", ptr, 5)==0) {
                    ptr+=5;
                    process_element(ptr, 5, GRID_ELEM_LINE);
                } else if (strncmp("@rectf", ptr, 6)==0) {
                    ptr+=6;
                    process_element(ptr, 6, GRID_ELEM_FILLED_RECT);
                } else if (strncmp("@rect", ptr, 5)==0) {
                    ptr+=5;
                    process_element(ptr, 5, GRID_ELEM_RECT);
                } else if (strncmp("@elpsf", ptr, 6)==0) {
                    ptr+=6;
                    process_element(ptr, 5, GRID_ELEM_FILLED_ELLIPSE);
                } else if (strncmp("@elps", ptr, 5)==0) {
                    ptr+=5;
                    process_element(ptr, 5, GRID_ELEM_ELLIPSE);
                }
            }
            while (ptr[0] && ptr[0]!='\n') ++ptr; // unless end of line
            if (ptr[0]) ++ptr;
        }
    }

    return size;
}

//-------------------------------------------------------------------
void grid_lines_load(const char *fn)
{
    if (process_file(fn, parse_grid_file, 1) > 0)
    {
        char* c = strrchr(fn, '/');
        strncpy(conf.grid_title, (c)?c+1:fn, sizeof(conf.grid_title));
        conf.grid_title[sizeof(conf.grid_title)-1] = 0;

        strcpy(conf.grid_lines_file, fn);
    }
}

//-------------------------------------------------------------------
void gui_grid_draw_osd(int force)
{
    if (camera_info.state.mode_rec_or_review && conf.show_grid_lines)
    {
        struct gline  *ptr;

        if (force || --interval==0) {
            for (ptr=head; ptr; ptr=ptr->next) {
                switch (ptr->type) {
                    case GRID_ELEM_LINE:
                        draw_line(ptr->x0, ptr->y0, ptr->x1, ptr->y1, (conf.grid_force_color)?conf.grid_color:ptr->clf);
                        break;
                    case GRID_ELEM_RECT:
                        draw_rect(ptr->x0, ptr->y0, ptr->x1, ptr->y1, (conf.grid_force_color)?conf.grid_color:ptr->clf);
                        break;
                    case GRID_ELEM_FILLED_RECT:
                        draw_filled_rect(ptr->x0, ptr->y0, ptr->x1, ptr->y1, (conf.grid_force_color)?conf.grid_color:MAKE_COLOR(ptr->clb, ptr->clf));
                        break;
                    case GRID_ELEM_ELLIPSE:
                        draw_ellipse(ptr->x0, ptr->y0, (unsigned int)(ptr->x1), (unsigned int)(ptr->y1), (conf.grid_force_color)?conf.grid_color:ptr->clf);
                        break;
                    case GRID_ELEM_FILLED_ELLIPSE:
                        draw_filled_ellipse(ptr->x0, ptr->y0, (unsigned int)(ptr->x1), (unsigned int)(ptr->y1), (conf.grid_force_color)?conf.grid_color:MAKE_COLOR(ptr->clf, 0));
                        break;
                }
            }
            interval = GRID_REDRAW_INTERVAL;
        }
    }
}

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

//---------------------------------------------------------
// PURPOSE:   Perform on-load initialisation
// RETURN VALUE: 1 error, 0 ok
//---------------------------------------------------------
int _module_loader( unsigned int* chdk_export_list )
{
    grid_lines_load(conf.grid_lines_file);
    return 0;
}

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    grid_lines_free_data();
    return 0;
}

int _module_can_unload()
{
    return conf.show_grid_lines == 0;
}

/******************** Module Information structure ******************/

libgrids_sym _libgrids =
{
    {
         _module_loader, _module_unloader, _module_can_unload, 0, 0
    },

    gui_grid_draw_osd,
    grid_lines_load
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    GUI_GRID_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Grids (dll)",	    // Module name
    (int32_t)"Grid Display",

    &_libgrids.base,

    CONF_VERSION,               // CONF version
    ANY_VERSION,                // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
