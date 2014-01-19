#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "asmsafe.h" //For debug purpose, it is required to use ASM_SAFE macro

const char * const new_sa = &_end;

/* Our stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);


void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();
