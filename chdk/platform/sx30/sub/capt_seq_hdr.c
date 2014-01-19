#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define USE_STUBS_NRFLAG 1  // see stubs_entry.S
#define NR_AUTO (0)         // have to explictly reset value back to 0 to enable auto

#include "../../../generic/capt_seq.c"
