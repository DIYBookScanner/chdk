#include "camera.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "stdlib.h"

/* Ours stuff */
extern long link_bss_start;
extern long link_bss_end;
extern void boot();

static void core_hook_task_create(void *tcb)
{
}

static void core_hook_task_delete(void *tcb)
{
    char *name = (char*)(*(long*)((char*)tcb+0x34));
    if (strcmp(name,"tInitFileM")==0) core_spytask_can_start();
}


static int stop_hooking;

static void (*task_prev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);

static void (*init_file_modules_prev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);



void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}


static void task_start_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    _CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);

    task_prev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
}


static void remount_filesystem()
{
    _Unmount_FileSystem();
    _Mount_FileSystem();
}


static void init_file_modules_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    remount_filesystem();
    init_file_modules_prev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
}


static void capt_seq_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    capt_seq_task();
}


static void physw_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    mykbd_task();
}

static void movie_record_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    movie_record_task();
}

extern void task_JogDial_my();

static void task_JogDial_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    task_JogDial_my();
}

static int my_ncmp(const char *s1, const char *s2, long len)
{
    int i;
    for (i=0;i<len;i++){
	if (s1[i] != s2[i])
	    return 1;
    }
    return 0;
}

void createHook (void *pNewTcb)
{
    char *name = (char*)(*(long*)((char*)pNewTcb+0x34));
    long *entry = (long*)((char*)pNewTcb+0x74);

    // always hook first task creation
    // to create SpyProc
    if (!stop_hooking){
        task_prev = (void*)(*entry);
        *entry = (long)task_start_hook;
        stop_hooking = 1;
    } else {
        // hook/replace another tasks
        if (my_ncmp(name, "tPhySw", 6) == 0){
            *entry = (long)physw_hook;
        }
        
        if (my_ncmp(name, "tInitFileM", 10) == 0){
            init_file_modules_prev = (void*)(*entry);
        #if CAM_MULTIPART
            *entry = (long)init_file_modules_task;
        #else
            *entry = (long)init_file_modules_hook;
        #endif
        }
        
        if (my_ncmp(name, "tCaptSeqTa", 10) == 0){
            *entry = (long)capt_seq_hook;
        }
        
        if (my_ncmp(name, "tJogDial", 8) == 0){
            *entry = (long)task_JogDial_hook;
        }
        
        if (my_ncmp(name, "tMovieReco", 10) == 0){
        #if CAM_CHDK_HAS_EXT_VIDEO_MENU
            *entry = (long)movie_record_hook;
        #endif
        }
        
        #if CAM_EXT_TV_RANGE
        if (my_ncmp(name, "tExpDrvTas", 10) == 0){
            *entry = (long)exp_drv_task;
        }
        #endif
        
        core_hook_task_create(pNewTcb);
    }
}

void deleteHook (void *pTcb)
{
    core_hook_task_delete(pTcb);
}

void startup()
{
    long *bss = &link_bss_start;

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
        started();
        shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
        *bss++ = 0;

    boot();
}

/*********************************************************************/

long get_vbatt_min()
{
    return 6700;
}

long get_vbatt_max()
{
    return 8100;
}

// Focus length table in firmware @0xfffe41f4
#define NUM_FL      9   // 0 - 8, entries in firmware
#define NUM_DATA    3   // 3 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 5.8       28       ( 28/ 5.8) * 580 = 2800  (min FL)
// 20.7      100      (100/20.7) * 580 = 2800  (max FL)
#define CF_EFL      2800
#define	CF_EFL_DIV  580

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/CF_EFL_DIV;
}

int get_focal_length(int zp) {
    if (zp < 0) zp = 0;
    else if (zp >= NUM_FL) zp = NUM_FL-1;
    return focus_len_table[zp*NUM_DATA];
}

int get_zoom_x(int zp) {
    return get_focal_length(zp)*10/focus_len_table[0];
}

/*
playrec_mode:
3 when switched into play mode while in record mode
2 record mode
4 in recmode menu
5 when recmode overlay animation is activated by the jogdial
0 when switched on in play mode
*/
