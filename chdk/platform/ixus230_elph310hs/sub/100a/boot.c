#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();

void taskHook(context_t **context)
{
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task;
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
}

/*---------------------------------------------------------------------
  Memory Map:
	0001900     MEMBASEADDR             start of data - used for initialized vars
	0010797???                          end of inited data
	0010798???                          start of bss - used for zeroed/uninited vars
	016E81F???                          end of bss
	016E820???  MEMISOSTART             start of our data / bss

	0400000                             raw buffers
	8000000                             end of raw buffers

	C0xxxxxx                            I/O

	FF000000    ROMBASEADDR             start of rom
	FFFFFFFF                            end of rom
----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) boot() {
    asm volatile (
            "	LDR	R1, =0xC0410000 \n"
            "	MOV	R0, #0 \n"
            "	STR	R0, [R1] \n"
            "	MOV	R1, #0x78 \n"
            "	MCR	p15, 0, R1, c1, c0 \n"
            "	MOV	R1, #0 \n"
            "	MCR	p15, 0, R1, c7, c10, 4 \n"
            "	MCR	p15, 0, R1, c7, c5 \n"
            "	MCR	p15, 0, R1, c7, c6 \n"
            "	MOV	R0, #0x3D \n"
            "	MCR	p15, 0, R0, c6, c0 \n"
            "	MOV	R0, #0xC000002F \n"
            "	MCR	p15, 0, R0, c6, c1 \n"
            "	MOV	R0, #0x35 \n"
            "	MCR	p15, 0, R0, c6, c2 \n"
            "	MOV	R0, #0x40000035 \n"
            "	MCR	p15, 0, R0, c6, c3 \n"
            "	MOV	R0, #0x80000017 \n"
            "	MCR	p15, 0, R0, c6, c4 \n"
            "	LDR	R0, =0xFF00002F \n"
            "	MCR	p15, 0, R0, c6, c5 \n"
            "	MOV	R0, #0x34 \n"
            "	MCR	p15, 0, R0, c2, c0 \n"
            "	MOV	R0, #0x34 \n"
            "	MCR	p15, 0, R0, c2, c0, 1 \n"
            "	MOV	R0, #0x34 \n"
            "	MCR	p15, 0, R0, c3, c0 \n"
            "	LDR	R0, =0x3333330 \n"
            "	MCR	p15, 0, R0, c5, c0, 2 \n"
            "	LDR	R0, =0x3333330 \n"
            "	MCR	p15, 0, R0, c5, c0, 3 \n"
            "	MRC	p15, 0, R0, c1, c0 \n"
            "	ORR	R0, R0, #0x1000 \n"
            "	ORR	R0, R0, #4 \n"
            "	ORR	R0, R0, #1 \n"
            "	MCR	p15, 0, R0, c1, c0 \n"
            "	MOV	R1, #0x80000006 \n"
            "	MCR	p15, 0, R1, c9, c1 \n"
            "	MOV	R1, #6 \n"
            "	MCR	p15, 0, R1, c9, c1, 1 \n"
            "	MRC	p15, 0, R1, c1, c0 \n"
            "	ORR	R1, R1, #0x50000 \n"
            "	MCR	p15, 0, R1, c1, c0 \n"
            "	LDR	R2, =0xC0200000 \n"
            "	MOV	R1, #1 \n"
            "	STR	R1, [R2, #0x10C] \n"
            "	MOV	R1, #0xFF \n"
            "	STR	R1, [R2, #0xC] \n"
            "	STR	R1, [R2, #0x1C] \n"
            "	STR	R1, [R2, #0x2C] \n"
            "	STR	R1, [R2, #0x3C] \n"
            "	STR	R1, [R2, #0x4C] \n"
            "	STR	R1, [R2, #0x5C] \n"
            "	STR	R1, [R2, #0x6C] \n"
            "	STR	R1, [R2, #0x7C] \n"
            "	STR	R1, [R2, #0x8C] \n"
            "	STR	R1, [R2, #0x9C] \n"
            "	STR	R1, [R2, #0xAC] \n"
            "	STR	R1, [R2, #0xBC] \n"
            "	STR	R1, [R2, #0xCC] \n"
            "	STR	R1, [R2, #0xDC] \n"
            "	STR	R1, [R2, #0xEC] \n"
            "	STR	R1, [R2, #0xFC] \n"
            "	LDR	R1, =0xC0400008 \n"
            "	LDR	R2, =0x430005 \n"
            "	STR	R2, [R1] \n"
            "	MOV	R1, #1 \n"
            "	LDR	R2, =0xC0243100 \n"
            "	STR	R2, [R1] \n"
            "	LDR	R2, =0xC0242010 \n"
            "	LDR	R1, [R2] \n"
            "	ORR	R1, R1, #1 \n"
            "	STR	R1, [R2] \n"
            "   LDR R0, =0xFF4973F0 \n" // diff from 100b - 0xFF497420
            "	LDR	R1, =0x1900 \n"
            "	LDR	R3, =0x102DC \n"
            "loc_FF00013C:\n"
            "	CMP	R1, R3 \n"
            "	LDRCC	R2, [R0], #4 \n"
            "	STRCC	R2, [R1], #4 \n"
            "	BCC	loc_FF00013C \n"
            "	LDR	R1, =0x181A9C \n"
            "	MOV	R2, #0 \n"
            "loc_FF000154:\n"
            "	CMP	R3, R1 \n"
            "	STRCC	R2, [R3], #4 \n"
            "	BCC	loc_FF000154 \n"
            //"	B	sub_FF000358 \n" // original
            "	B	sub_FF000358_my \n" // patched
    );
}

/*----------------------------------------------------------------------
	sub_FF000358_my
-----------------------------------------------------------------------*/
// FF000358
void __attribute__((naked,noinline)) sub_FF000358_my() {

    //http://chdk.setepontos.com/index.php/topic,4194.0.html
    *(int*)0x1938=(int)taskHook;
    *(int*)0x193C=(int)taskHook;
    //*(int*)0x1930=(int)taskHook;
    //*(int*)0x1934=(int)taskHook;

    // replacement of sub_FF025560 for correct power-on.
    *(int*)(0x2610) = (*(int*)0xC0220130)&1 ? 0x200000 : 0x100000;

    asm volatile (
            "	LDR	R0, =0xFF0003D0 \n"
            "	MOV	R1, #0 \n"
            "	LDR	R3, =0xFF000408 \n"
            "loc_FF000364:\n"
            "	CMP	R0, R3 \n"
            "	LDRCC	R2, [R0], #4 \n"
            "	STRCC	R2, [R1], #4 \n"
            "	BCC	loc_FF000364 \n"
            "	LDR	R0, =0xFF000408 \n"
            "	MOV	R1, #0x4B0 \n"
            "	LDR	R3, =0xFF00061C \n"
            "loc_FF000380:\n"
            "	CMP	R0, R3 \n"
            "	LDRCC	R2, [R0], #4 \n"
            "	STRCC	R2, [R1], #4 \n"
            "	BCC	loc_FF000380 \n"
            "	MOV	R0, #0xD2 \n"
            "	MSR	CPSR_cxsf, R0 \n"
            "	MOV	SP, #0x1000 \n"
            "	MOV	R0, #0xD3 \n"
            "	MSR	CPSR_cxsf, R0 \n"
            "	MOV	SP, #0x1000 \n"
            "	LDR	R0, =0x6C4 \n"
            "	LDR	R2, =0xEEEEEEEE \n"
            "	MOV	R3, #0x1000 \n"
            "loc_FF0003B4:\n"
            "	CMP	R0, R3 \n"
            "	STRCC	R2, [R0], #4 \n"
            "	BCC	loc_FF0003B4 \n"
            //"	BL	sub_FF0011B0 \n" // original
            "	BL	sub_FF0011B0_my \n" // patched
    );
}

/*----------------------------------------------------------------------
	sub_FF0011B0_my
-----------------------------------------------------------------------*/
// FF0011B0
void __attribute__((naked,noinline)) sub_FF0011B0_my() {
    asm volatile (
            "	STR	LR, [SP, #-4]! \n"
            "	SUB	SP, SP, #0x74 \n"
            "	MOV	R1, #0x74 \n"
            "	MOV	R0, SP \n"
            "   BL  sub_FF3A2D24 \n" // diff from 100b - sub_FF3A2D58
            "	MOV	R0, #0x57000 \n"
            "	STR	R0, [SP, #4] \n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
            "	LDR	R0, =0x181A9C \n" // use original heap offset since CHDK is loaded in high memory
#else
            "   LDR     R0, =new_sa \n" // otherwise use patched value
            "   LDR     R0, [R0] \n"
#endif
            "	LDR	R2, =0x36D788 \n"
            "	STR	R0, [SP, #8] \n"
            "	SUB	R0, R2, R0 \n"
            "	STR	R0, [SP, #0xC] \n"
            "	MOV	R0, #0x22 \n"
            "	STR	R0, [SP, #0x18] \n"
            "	MOV	R0, #0x72 \n"
            "	STR	R0, [SP, #0x1C] \n"
            "	LDR	R1, =0x375C00 \n"
            "	LDR	R0, =0x1CD \n"
            "	STR	R1, [SP] \n"
            "	STR	R0, [SP, #0x20] \n"
            "	MOV	R0, #0x96 \n"
            "	STR	R2, [SP, #0x10] \n"
            "	STR	R1, [SP, #0x14] \n"
            "	STR	R0, [SP, #0x24] \n"
            "	STR	R0, [SP, #0x28] \n"
            "	MOV	R0, #0x64 \n"
            "	STR	R0, [SP, #0x2C] \n"
            "	MOV	R0, #0 \n"
            "	STR	R0, [SP, #0x30] \n"
            "	STR	R0, [SP, #0x34] \n"
            "	MOV	R0, #0x10 \n"
            "	STR	R0, [SP, #0x5C] \n"
            "	MOV	R0, #0x800 \n"
            "	STR	R0, [SP, #0x60] \n"
            "	MOV	R0, #0xA0 \n"
            "	STR	R0, [SP, #0x64] \n"
            "	MOV	R0, #0x280 \n"
            "	STR	R0, [SP, #0x68] \n"
            //"	LDR	R1, =0xFF005F2C \n" // original
            "	LDR	R1, =sub_FF005F2C_my \n" // patched
            "   B       sub_FF00124C \n" // continue in firmware
    );
}

/*----------------------------------------------------------------------
	sub_FF005F2C_my
-----------------------------------------------------------------------*/
// FF005F2C
void __attribute__((naked,noinline)) sub_FF005F2C_my() {
    asm volatile (
            "	STMFD	SP!, {R4,LR} \n"
            "	BL	sub_FF000B28 \n"
            "	BL	sub_FF00A384 \n"
            "	CMP	R0, #0 \n"
            "	LDRLT	R0, =0xFF006040 \n" // *"dmSetup"
            "	BLLT	_err_init_task \n"
            "	BL	sub_FF005B64 \n"
            "	CMP	R0, #0 \n"
            "	LDRLT	R0, =0xFF006048 \n" // *"termDriverInit"
            "	BLLT	_err_init_task \n"
            "	LDR	R0, =0xFF006058 \n" // *"/_term"
            "	BL	sub_FF005C4C \n"
            "	CMP	R0, #0 \n"
            "	LDRLT	R0, =0xFF006060 \n" // *"termDeviceCreate"
            "	BLLT	_err_init_task \n"
            "	LDR	R0, =0xFF006058 \n" // *"/_term"
            "	BL	sub_FF003CA8 \n"
            "	CMP	R0, #0 \n"
            "	LDRLT	R0, =0xFF006074 \n" // *"stdioSetup"
            "	BLLT	_err_init_task \n"
            "	BL	sub_FF009CEC \n"
            "	CMP	R0, #0 \n"
            "	LDRLT	R0, =0xFF006080 \n" // *"stdlibSetup"
            "	BLLT	_err_init_task \n"
            "	BL	sub_FF001690 \n"
            "	CMP	R0, #0 \n"
            "	LDRLT	R0, =0xFF00608C \n" // *"armlib_setup"
            "	BLLT	_err_init_task \n"
            "	LDMFD	SP!, {R4,LR} \n"
            //"	B	sub_FF00FDA0 \n" // original
            "	B	sub_FF00FDA0_my \n" // patched
    );
}

/*----------------------------------------------------------------------
        sub_FF00FDA0_my
-----------------------------------------------------------------------*/
// FF00FDA0
void __attribute__((naked,noinline)) sub_FF00FDA0_my() {
    asm volatile (
            "	STMFD	SP!, {R4,LR} \n"
            "	BL	sub_FF025558 \n"
            //"	BL	sub_FF00FDB4 \n" // original taskcreate_Startup
            "	BL	taskcreate_Startup_my \n" // patched taskcreate_Startup
            "	MOV	R0, #0 \n"
            "	LDMFD	SP!, {R4,PC} \n"
    );
}

/*----------------------------------------------------------------------
	taskcreate_Startup_my
-----------------------------------------------------------------------*/
// FF00FDB4
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
    asm volatile (
            "	STMFD	SP!, {R3-R9,LR} \n"
            "	MOV	R6, #0 \n"
            "	BL	sub_FF02D710 \n"
            "	LDR	R9, =0xC0220000 \n"
            "	MOVS	R7, R0 \n"
            "	MOV	R8, #1 \n"
            "	BNE	loc_FF00FE18 \n"
            "	BL	sub_FF026F24 \n"
            "	CMP	R0, #0 \n"
            "	BEQ	loc_FF00FE18 \n"
            "	LDR	R0, [R9, #0x128] \n"
            "	BIC	R5, R8, R0 \n"
            "	LDR	R0, [R9, #0x12C] \n"
            "	BIC	R4, R8, R0 \n"
            "	BL	sub_FF02396C \n"
            "	CMP	R0, #1 \n"
            "	MOVEQ	R6, #1 \n"
            "	ORR	R0, R4, R5 \n"
            "	ORRS	R0, R0, R6 \n"
            "	BNE	loc_FF00FE28 \n"
            "	BL	sub_FF024634 \n"
            "	MOV	R0, #0x44 \n"
            "	STR	R0, [R9, #0x1C] \n"
            "	BL	sub_FF024824 \n"
            "loc_FF00FE14:\n"
            "	B	loc_FF00FE14 \n"
            "loc_FF00FE18:\n"
            "	LDR	R0, [R9, #0x12C] \n"
            "	BIC	R4, R8, R0 \n"
            "	LDR	R0, [R9, #0x128] \n"
            "	BIC	R5, R8, R0 \n"
            "loc_FF00FE28:\n"
            "	MOV	R3, R6 \n"
            "	MOV	R2, R7 \n"
            "	MOV	R1, R5 \n"
            "	MOV	R0, R4 \n"
            "	BL	sub_FF025560 \n" // see begining of sub_FF000358_my
            "	BL	sub_FF02555C \n"
            "	BL	sub_FF02B8DC \n"
            "	LDR	R1, =0x3CE000 \n"
            "	MOV	R0, #0 \n"
            "	BL	sub_FF02BD4C \n"
            "	BL	sub_FF02BAF4 \n"
            "	MOV	R3, #0 \n"
            "	STR	R3, [SP] \n"
            //"	LDR	R3, =0xFF00FD28 \n" // original
            "	LDR	R3, =task_Startup_my \n" // patched
            "   B       sub_FF00FE60 \n" // continue in firmware
    );
}

/*----------------------------------------------------------------------
	task_Startup_my
-----------------------------------------------------------------------*/
// FF00FD28
void __attribute__((naked,noinline)) task_Startup_my() {
    asm volatile (
            "	STMFD	SP!, {R4,LR} \n"
            "	BL	sub_FF0065DC \n"
            "	BL	sub_FF026668 \n"
            "	BL	sub_FF023EF0 \n"
            "	BL	sub_FF024270 \n"
            //"	BL	sub_FF02D758 \n"    // j_nullsub_???
            "	BL	sub_FF02D944 \n"
            "	BL	sub_FF024954 \n"
            "	BL	sub_FF02397C \n"
            "	MOV	R0, #1 \n"
            "	BL	sub_FF023E64 \n"
            //"	BL	sub_FF02D7EC \n" // skip starting diskboot.bin again
            "	BL	sub_FF02DAFC \n"
            "	BL	sub_FF022378 \n"
            "	BL	sub_FF02D974 \n"
            "	BL	sub_FF02B080 \n"
            "	BL	sub_FF02DB00 \n"
            //"	BL	sub_FF0253DC \n" // original *PhySw*
            "   BL      CreateTask_spytask \n" // added to create the Spytask
            "   BL      taskcreatePhySw_my \n" // patched taskcreate_PhySw()
            "   B       sub_FF00FD70 \n" // continue in firmware
    );
}

/*----------------------------------------------------------------------
	taskcreatePhySw_my ff0253dc
-----------------------------------------------------------------------*/
// FF0253DC
void __attribute__((naked,noinline)) taskcreatePhySw_my() {
    asm volatile (
            "	STMFD	SP!, {R3-R5,LR} \n"
            "	LDR	R4, =0x1C4C \n"
            "	LDR	R0, [R4, #4] \n"
            "	CMP	R0, #0 \n"
            "	BNE	sub_FF025410 \n"
            "	MOV	R3, #0 \n"
            "	STR	R3, [SP] \n"
            //"	LDR	R3, =0xFF0253A8 \n" // original
            "	LDR	R3, =mykbd_task \n" // patched
            //"	MOV	R2, #0x800 \n" // original
            "	MOV	R2, #0x2000 \n" // stack size for new task_PhySw so we don't have to do stack switch
            "	B	sub_FF025400 \n" // continue in firmware
    );
}

/*----------------------------------------------------------------------
	spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}

/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask() {
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

/*----------------------------------------------------------------------
	init_file_modules_task
-----------------------------------------------------------------------*/
// FF09301C
void __attribute__((naked,noinline)) init_file_modules_task() {
    asm volatile (
            "	STMFD	SP!, {R4-R6,LR} \n"
            "	BL	sub_FF08ABA0 \n"
            "	LDR	R5, =0x5006 \n"
            "	MOVS	R4, R0 \n"
            "	MOVNE	R1, #0 \n"
            "	MOVNE	R0, R5 \n"
            "	BLNE	sub_FF08EDF0 \n"
            "	BL	sub_FF08ABCC \n"
            "   BL      core_spytask_can_start\n" // added CHDK: Set "it's-safe-to-start"-Flag for spytask
            "   B       sub_FF09303C \n" // continue in firmware
    );
}
