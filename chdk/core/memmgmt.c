#include "platform.h"
#include "stdlib.h"
#include "core.h"
#include "conf.h"
#include "gui_draw.h"

//----------------------------------------------------------------------------
// Memory wrappers

extern void *suba_init(void *heap, unsigned size, unsigned rst, unsigned mincell);
extern void *suba_alloc(void *heap, unsigned size, unsigned zero);
extern int suba_free(void *heap, void *p);

//----------------------------------------------------------------------------
// Manage block of memory controlled by suba
typedef struct
{
    void    *heap;
    void    *start;
    void    *end;
    int     size;
} chdk_heap;

static void chdk_heap_init(chdk_heap *h)
{
    h->heap = 0;
    h->start = 0;
    h->end = 0;
    h->size = 0;
}

static void chdk_heap_create(chdk_heap *h, void *mem, int size, int chdk_in_heap, int heap_testing)
{
    if (h)
    {
        if (chdk_in_heap)
        {
		    // If loading CHDK into heap then move heap start past the end of CHDK
		    // and reduce available space by CHDK size (MEMISOSIZE)
		    // round MEMISOSIZE up to next 4 byte boundary if needed (just in case)
		    h->start = mem + ((camera_info.memisosize+3)&0xFFFFFFFC);
		    h->size = size - ((camera_info.memisosize+3)&0xFFFFFFFC);
        }
        else
        {
		    // Set start & size based on requested values
		    h->start = mem;
		    h->size = size;
        }

		h->end = h->start + h->size;

        if (heap_testing)
        {
		    // For testing exmem allocated memory for corruption from normal camera operations
		    // set the above #define. This will allocate the memory; but won't use it (exmem_heap is set to 0)
		    // Instead all the memory is filled with the guard value below.
		    // In gui_draw_debug_vals_osd (gui.c) the memory is tested for the guard value and if any
		    // corruption has occurred then info about the memory locations that were altered is displayed
            // Note: do not use heap_testing and chdk_in_heap at the same time
		    unsigned long *p;
		    for (p=(unsigned long*)h->start; p<(unsigned long*)h->end; p++) *p = 0xDEADBEEF;
        }
        else
        {
    		// Normal operation, use the suba allocation system to manage the memory block
	    	h->heap = suba_init(h->start,h->size,1,8);
        }
    }
}

static void* chdk_malloc(chdk_heap *h, unsigned size)
{
    if (h && h->heap)
	    return suba_alloc(h->heap,size,0);
    return 0;
}

static int chdk_free(chdk_heap *h, void *p)
{
    if (h && h->heap && (p >= h->start) && (p < h->end))
    {
        suba_free(h->heap,p);
        return 1;
    }
    return 0;
}

// Use suba functions to fill meminfo structure to match firmware GetMemInfo function
static int chdk_meminfo(chdk_heap *h, cam_meminfo *camera_meminfo)
{
    if (h && h->heap)
    {
	    extern void suba_getmeminfo(void*, int*, int*, int*, int*, int*, int*);

        camera_meminfo->start_address        = (int)h->start;
        camera_meminfo->end_address          = (int)h->end;
        camera_meminfo->total_size           = h->size;
        suba_getmeminfo(h->heap,
                        &camera_meminfo->allocated_size, &camera_meminfo->allocated_peak, &camera_meminfo->allocated_count,
                        &camera_meminfo->free_size, &camera_meminfo->free_block_max_size, &camera_meminfo->free_block_count);

        return 1;   // return success
    }
    else
    {
        memset(camera_meminfo, 0, sizeof(cam_meminfo));
        return 0;
    }
}

#if defined(OPT_EXMEM_TESTING) || defined(OPT_ARAM_TESTING)
static void chdk_testing(chdk_heap *h)
{
    // If defined the heap memory is allocated; but not used for CHDK.
    // It is filled with a guard value which is checked here
    // Any corruption is reported, otherwise 'OK' is displayed on screen (along with the heap memory start address).

    // check heap allocated memory for corruption
    unsigned long* p = (unsigned long*)h->start;
    unsigned long *f = 0, *l = 0;
    long cnt = 0;
    while (p < (unsigned long*)h->end)
    {
        if (p[0] != 0xDEADBEEF)
        {
            l = p;
            if (f == 0) f = p;
            cnt++;
        }
        p++;
    }
    char osd_buf[40];
    if (cnt != 0)
    {
        sprintf(osd_buf, "s:%8x e:%8x", h->start, h->end);
        draw_txt_string(2, 12, osd_buf, conf.osd_color);
        sprintf(osd_buf, "f:%8x l:%8x c:%d", f, l, cnt);
    }
    else
    {
        sprintf(osd_buf, "OK 0x%x", h->start);
    }
    draw_txt_string(2, 13, osd_buf, conf.osd_color);
    // end of check	
}
#endif

//----------------------------------------------------------------------------
#ifdef OPT_EXMEM_MALLOC
// I set this up to 16 mb and it still booted...
#ifndef EXMEM_HEAP_SKIP
#define EXMEM_HEAP_SKIP 0
#endif
#ifndef EXMEM_BUFFER_SIZE
#define EXMEM_BUFFER_SIZE (1024*1024*2) // default size if not specified by camera
#endif
#define EXMEM_HEAP_SIZE (EXMEM_BUFFER_SIZE+EXMEM_HEAP_SKIP)	// desired space + amount to skip for the movie buffers (if needed)
#endif

static chdk_heap exmem_heap;

#if defined(OPT_EXMEM_TESTING)
void exmem_testing()
{
    chdk_testing(&exmem_heap);
}
#endif

void exmem_malloc_init()
{
    chdk_heap_init(&exmem_heap);
#ifdef OPT_EXMEM_MALLOC
#ifndef OPT_CHDK_IN_EXMEM
#define OPT_CHDK_IN_EXMEM 0
#endif
#ifndef OPT_EXMEM_TESTING
#define OPT_EXMEM_TESTING 0
#endif
	// pool zero is EXMEM_RAMDISK on d10
    extern void *exmem_alloc(int pool_id,int size,int unk,int unk2); 
	void *mem = exmem_alloc(0,EXMEM_HEAP_SIZE,0,0);
	if (mem)
    {
        chdk_heap_create(&exmem_heap, mem, EXMEM_BUFFER_SIZE, OPT_CHDK_IN_EXMEM, OPT_EXMEM_TESTING);
	}
#endif
}

// Use suba functions to fill meminfo structure to match firmware GetMemInfo function
int GetExMemInfo(cam_meminfo *camera_meminfo)
{
    return chdk_meminfo(&exmem_heap, camera_meminfo);
}

//----------------------------------------------------------------------------

static chdk_heap aram_heap;

#if defined(OPT_ARAM_TESTING)
void aram_testing()
{
    chdk_testing(&aram_heap);
}
#endif

void aram_malloc_init()
{
    chdk_heap_init(&aram_heap);
#ifdef OPT_ARAM_MALLOC
#ifndef OPT_CHDK_IN_ARAM
#define OPT_CHDK_IN_ARAM 0
#endif
#ifndef OPT_ARAM_TESTING
#define OPT_ARAM_TESTING 0
#endif
    chdk_heap_create(&aram_heap, (void*)ARAM_HEAP_START, ARAM_HEAP_SIZE, OPT_CHDK_IN_ARAM, OPT_ARAM_TESTING);
#endif
}

// Use suba functions to fill meminfo structure to match firmware GetMemInfo function
int GetARamInfo(cam_meminfo *camera_meminfo)
{
    return chdk_meminfo(&aram_heap, camera_meminfo);
}

//----------------------------------------------------------------------------
static void combine_meminfo(cam_meminfo *combined,cam_meminfo *m)
{
    combined->total_size += m->total_size;
    if(m->free_block_max_size > combined->free_block_max_size)
    {
        combined->free_block_max_size = m->free_block_max_size; 
    }
    combined->free_size += m->free_size;
    combined->free_block_count += m->free_block_count;
    combined->allocated_size += m->allocated_size;
    combined->allocated_peak += m->allocated_peak;
    combined->allocated_count += m->allocated_count;
}

// Build a combined meminfo from available heaps
// free block max size is the single largest free block
// other fields are total, or zero where it doesn't make sense to combine
void GetCombinedMemInfo(cam_meminfo *camera_meminfo)
{
    // get system meminfo, should always be available
    GetMemInfo(camera_meminfo);
// some fields are set to -1 for vxworks cams
#if !defined(CAM_DRYOS)
    camera_meminfo->allocated_peak = 0;
    camera_meminfo->total_size = 0;
#ifdef CAM_NO_MEMPARTINFO
    // a more useful base value than 0
    camera_meminfo->free_size = camera_meminfo->free_block_max_size;
    camera_meminfo->free_block_count = 0;
    camera_meminfo->allocated_size = 0;
    camera_meminfo->allocated_count = 0;
#endif
#endif

    // these don't make sense to combine
    camera_meminfo->start_address = camera_meminfo->end_address = 0;

    cam_meminfo m;
    if(GetARamInfo(&m)) {
        combine_meminfo(camera_meminfo,&m);
    }
    if(GetExMemInfo(&m)) {
        combine_meminfo(camera_meminfo,&m);
    }
}

void *malloc(long size)
{
    extern void *canon_malloc(long size);

    void *p = chdk_malloc(&aram_heap,size);

    if (p == 0)
        p = chdk_malloc(&exmem_heap,size);

    if (p == 0)
        p = canon_malloc(size);

    return p;
}

void free(void *p)
{
    extern void canon_free(void *p);

    if (!chdk_free(&aram_heap,p))
	    if (!chdk_free(&exmem_heap,p))
            canon_free(p);
}

