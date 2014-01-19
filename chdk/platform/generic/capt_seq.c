// generic capt_seq fuctions
#include "asmsafe.h"
#include "conf.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

// some cams use different values
// note: many cams ROM also accepts a value of 3, meaning unknown
#ifndef NR_ON
#define NR_ON (2)
#endif
#ifndef NR_OFF
#define NR_OFF (1)
#endif

static long raw_save_stage;

#include "remotecap_core.h"

void __attribute__((naked,noinline)) capt_seq_hook_raw_here()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");

#ifdef PAUSE_FOR_FILE_COUNTER
    // Some cameras need a slight delay for the file counter to be updated correctly
    // before raw_savefile tries to get the file name & directory.
    // Add '#define PAUSE_FOR_FILE_COUNTER 100' in the camera firmware capt_seq.c file.
    // The value can be adjusted as needed for different cameras.

    if ((conf.save_raw && is_raw_enabled()) // Only delay if RAW enabled (prevents slowdown in HQ burst mode)
        || (remotecap_get_target()) //... or if remote shooting is active
    )
    {
        int fc = get_file_counter();
        int tc = get_tick_count() + PAUSE_FOR_FILE_COUNTER;
        while ((get_file_counter() == fc) && (get_tick_count() < tc)) {
            _SleepTask(10);
        }
    }
#endif

    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available(); //notifies spytask in core/main.c
    while (raw_save_stage != RAWDATA_SAVED){
    _SleepTask(10);
    }
 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

// wrapper function to store status on stack as this routine is called from assembly code in capt_seq_task()

void __attribute__((naked,noinline)) wait_until_remote_button_is_released(  ) 
{ 
asm volatile (
ASM_SAFE("BL _wait_until_remote_button_is_released\n")
 "	BX      LR \n"
	) ;
}


void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}

#if defined(USE_STUBS_NRFLAG)
extern long _nrflag;
#define set_nrflag(n)   _nrflag = n
#else
#define set_nrflag(n)   *nrflag = n
#endif

void __attribute__((naked,noinline)) capt_seq_hook_set_nr()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");
    switch (conf.raw_nr){
    case NOISE_REDUCTION_AUTO_CANON:
        // leave it alone
#if defined(NR_AUTO)			// If value defined store it (e.g. for G12 & SX30 need to reset back to 0 to enable auto)
        set_nrflag(NR_AUTO);
#endif
        break;
    case NOISE_REDUCTION_OFF:
        set_nrflag(NR_OFF);
        break;
    case NOISE_REDUCTION_ON:
        set_nrflag(NR_ON);
        break;
    };

 camera_info.state.shutter_open_time = _time((void*)0);
 camera_info.state.shutter_open_tick_count = get_tick_count();

 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

