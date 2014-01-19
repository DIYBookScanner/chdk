#include "lolevel.h"
#include "platform.h"
#include "core.h"

//From a1400 100b, by comparison to ixus140
static long *nrflag = (long*)(0xBFD4+0x4); // ffa94fb8, 4th arg to  sub_ff9f42a8
#define PAUSE_FOR_FILE_COUNTER 200  // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"
