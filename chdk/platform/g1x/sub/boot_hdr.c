#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_FileWrite();

void __attribute__((naked,noinline)) taskHook(context_t **context)
{ 
    asm volatile("STMFD   SP!, {R0-R12,LR}\n");     // G1X crashes without this
    
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_RotaryEncoder)		tcb->entry = (void*)JogDial_task_my;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
    if(tcb->entry == (void*)task_FileWrite)         tcb->entry = (void*)filewritetask;

    asm volatile("LDMFD   SP!, {R0-R12,PC}\n");     // G1X crashes without this
}

/*----------------------------------------------------------------------
	CreateTask --> core_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask()
{
	_CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

///*----------------------------------------------------------------------
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
short *jog_position;

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/
