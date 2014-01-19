#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();

void taskHook(context_t **context)
{ 
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)   tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_RotaryEncoder)     tcb->entry = (void*)JogDial_task_my;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
}

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) boot() {
asm volatile (
"    LDR     R1, =0xC0410000 \n" 
"    MOV     R0, #0 \n" 
"    STR     R0, [R1] \n" 
"    MOV     R1, #0x78 \n" 
"    MCR     p15, 0, R1, c1, c0 \n" 
"    MOV     R1, #0 \n" 
"    MCR     p15, 0, R1, c7, c10, 4 \n" 
"    MCR     p15, 0, R1, c7, c5 \n" 
"    MCR     p15, 0, R1, c7, c6 \n" 
"    MOV     R0, #0x3D \n" 
"    MCR     p15, 0, R0, c6, c0 \n" 
"    MOV     R0, #0xC000002F \n" 
"    MCR     p15, 0, R0, c6, c1 \n" 
"    MOV     R0, #0x37 \n" 
"    MCR     p15, 0, R0, c6, c2 \n" 
"    MOV     R0, #0x40000037 \n" 
"    MCR     p15, 0, R0, c6, c3 \n" 
"    MOV     R0, #0x80000017 \n" 
"    MCR     p15, 0, R0, c6, c4 \n" 
"    LDR     R0, =0xFF00002F \n" 
"    MCR     p15, 0, R0, c6, c5 \n" 
"    LDR     R0, =0xD000002B \n" 
"    MCR     p15, 0, R0, c6, c7 \n" 
"    MOV     R0, #0x34 \n" 
"    MCR     p15, 0, R0, c2, c0 \n" 
"    MOV     R0, #0x34 \n" 
"    MCR     p15, 0, R0, c2, c0, 1 \n" 
"    MOV     R0, #0x34 \n" 
"    MCR     p15, 0, R0, c3, c0 \n" 
"    LDR     R0, =0x33333330 \n" 
"    MCR     p15, 0, R0, c5, c0, 2 \n" 
"    LDR     R0, =0x33333330 \n" 
"    MCR     p15, 0, R0, c5, c0, 3 \n" 
"    MRC     p15, 0, R0, c1, c0 \n" 
"    ORR     R0, R0, #0x1000 \n" 
"    ORR     R0, R0, #4 \n" 
"    ORR     R0, R0, #1 \n" 
"    MCR     p15, 0, R0, c1, c0 \n" 
"    MOV     R1, #0x80000006 \n" 
"    MCR     p15, 0, R1, c9, c1 \n" 
"    MOV     R1, #6 \n" 
"    MCR     p15, 0, R1, c9, c1, 1 \n" 
"    MRC     p15, 0, R1, c1, c0 \n" 
"    ORR     R1, R1, #0x50000 \n" 
"    MCR     p15, 0, R1, c1, c0 \n" 
"    LDR     R2, =0xC0200000 \n" 
"    MOV     R1, #1 \n" 
"    STR     R1, [R2, #0x10C] \n" 
"    MOV     R1, #0xFF \n" 
"    STR     R1, [R2, #0xC] \n" 
"    STR     R1, [R2, #0x1C] \n" 
"    STR     R1, [R2, #0x2C] \n" 
"    STR     R1, [R2, #0x3C] \n" 
"    STR     R1, [R2, #0x4C] \n" 
"    STR     R1, [R2, #0x5C] \n" 
"    STR     R1, [R2, #0x6C] \n" 
"    STR     R1, [R2, #0x7C] \n" 
"    STR     R1, [R2, #0x8C] \n" 
"    STR     R1, [R2, #0x9C] \n" 
"    STR     R1, [R2, #0xAC] \n" 
"    STR     R1, [R2, #0xBC] \n" 
"    STR     R1, [R2, #0xCC] \n" 
"    STR     R1, [R2, #0xDC] \n" 
"    STR     R1, [R2, #0xEC] \n" 
"    STR     R1, [R2, #0xFC] \n" 
"    LDR     R1, =0xC0400008 \n" 
"    LDR     R2, =0x430005 \n" 
"    STR     R2, [R1] \n" 
"    MOV     R1, #1 \n" 
"    LDR     R2, =0xC0243100 \n" 
"    STR     R2, [R1] \n" 
"    LDR     R2, =0xC0242010 \n" 
"    LDR     R1, [R2] \n" 
"    ORR     R1, R1, #1 \n" 
"    STR     R1, [R2] \n" 
"    LDR     R0, =0xFF64BE5C \n" 
"    LDR     R1, =0x1900 \n" 
"    LDR     R3, =0x148A8 \n" 
"loc_FF000144:\n"
"    CMP     R1, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF000144 \n" 
"    LDR     R1, =0x195D34 \n" 
"    MOV     R2, #0 \n" 
"loc_FF00015C:\n"
"    CMP     R3, R1 \n" 
"    STRCC   R2, [R3], #4 \n" 
"    BCC     loc_FF00015C \n" 
"    B       sub_FF000364_my \n"  // -->
    );
}


void __attribute__((naked,noinline)) sub_FF000364_my() {

	//http://chdk.setepontos.com/index.php/topic,4194.0.html
	*(int*)0x1938=(int)taskHook;
	*(int*)0x193C=(int)taskHook; // need this for startup in Playback mode (otherwise init_file_modules_task doesn't hook properly)

	*(int*)(0x26E0+0x4) = (*(int*)0xC022F48C)&4 ? 0x200000 : 0x100000;

asm volatile (
"    LDR     R0, =0xFF0003DC \n" 
"    MOV     R1, #0 \n" 
"    LDR     R3, =0xFF000414 \n" 
"loc_FF000370:\n"
"    CMP     R0, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF000370 \n" 
"    LDR     R0, =0xFF000414 \n" 
"    MOV     R1, #0x4B0 \n" 
"    LDR     R3, =0xFF000628 \n" 
"loc_FF00038C:\n"
"    CMP     R0, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF00038C \n" 
"    MOV     R0, #0xD2 \n" 
"    MSR     CPSR_cxsf, R0 \n" 
"    MOV     SP, #0x1000 \n" 
"    MOV     R0, #0xD3 \n" 
"    MSR     CPSR_cxsf, R0 \n" 
"    MOV     SP, #0x1000 \n" 
"    LDR     R0, =0x6C4 \n" 
"    LDR     R2, =0xEEEEEEEE \n" 
"    MOV     R3, #0x1000 \n" 
"loc_FF0003C0:\n"
"    CMP     R0, R3 \n" 
"    STRCC   R2, [R0], #4 \n" 
"    BCC     loc_FF0003C0 \n" 
"    BL      sub_FF0011BC_my \n" //--> 
    );
}

void __attribute__((naked,noinline)) sub_FF0011BC_my() {
asm volatile (
"    STR     LR, [SP, #-4]! \n" 
"    SUB     SP, SP, #0x74 \n" 
"    MOV     R1, #0x74 \n" 
"    MOV     R0, SP \n" 
"    BL      sub_FF44E0E0 \n" 
"    MOV     R0, #0x67000 \n" 
"    STR     R0, [SP, #4] \n" 
#if defined(CHDK_NOT_IN_CANON_HEAP)
"    LDR     R0, =0x195D34 \n"  // use original heap offset since CHDK is loaded in high memory
#else
"    LDR     R0, =new_sa\n"   // otherwise use patched value
"    LDR     R0, [R0]\n"      // 
#endif
"    LDR     R2, =0x55D788 \n" 
"    STR     R0, [SP, #8] \n" 
"    SUB     R0, R2, R0 \n" 
"    STR     R0, [SP, #0xC] \n" 
"    MOV     R0, #0x22 \n" 
"    STR     R0, [SP, #0x18] \n" 
"    MOV     R0, #0x72 \n" 
"    STR     R0, [SP, #0x1C] \n" 
"    LDR     R1, =0x565C00 \n" 
"    LDR     R0, =0x1CD \n" 
"    STR     R1, [SP] \n" 
"    STR     R0, [SP, #0x20] \n" 
"    MOV     R0, #0x96 \n" 
"    STR     R2, [SP, #0x10] \n" 
"    STR     R1, [SP, #0x14] \n" 
"    STR     R0, [SP, #0x24] \n" 
"    STR     R0, [SP, #0x28] \n" 
"    MOV     R0, #0x64 \n" 
"    STR     R0, [SP, #0x2C] \n" 
"    MOV     R0, #0 \n" 
"    STR     R0, [SP, #0x30] \n" 
"    STR     R0, [SP, #0x34] \n" 
"    MOV     R0, #0x10 \n" 
"    STR     R0, [SP, #0x5C] \n" 
"    MOV     R0, #0x800 \n" 
"    STR     R0, [SP, #0x60] \n" 
"    MOV     R0, #0xA0 \n" 
"    STR     R0, [SP, #0x64] \n" 
"    MOV     R0, #0x280 \n" 
"    STR     R0, [SP, #0x68] \n" 
"    LDR     R1, =sub_FF005F38_my \n" //-->
"    MOV     R2, #0 \n" 
"    MOV     R0, SP \n" 
"    BL      sub_FF0034D0 \n" 
"    ADD     SP, SP, #0x74 \n" 
"    LDR     PC, [SP], #4 \n" 
    );
}


void __attribute__((naked,noinline)) sub_FF005F38_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF000B34 \n" 
"    BL      sub_FF00A390 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF00604C \n" 
"    BLLT    sub_FF00602C \n" 
"    BL      sub_FF005B70 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF006054 \n" 
"    BLLT    sub_FF00602C \n" 
"    LDR     R0, =0xFF006064 \n" 
"    BL      sub_FF005C58 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF00606C \n" 
"    BLLT    sub_FF00602C \n" 
"    LDR     R0, =0xFF006064 \n" 
"    BL      sub_FF003CB4 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF006080 \n" 
"    BLLT    sub_FF00602C \n" 
"    BL      sub_FF009CF8 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF00608C \n" 
"    BLLT    sub_FF00602C \n" 
"    BL      sub_FF00169C \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF006098 \n" 
"    BLLT    sub_FF00602C \n" 
"    LDMFD   SP!, {R4,LR} \n" 
//"    B       sub_FF00FDAC \n" 
"    B       taskcreate_Startup_my \n" // patched
	);
}
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
"    STMFD   SP!, {R3,LR} \n" 
"    BL      sub_FF02B598 \n" 
"    BL      sub_FF02B7B0 \n" 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
"    LDR     R3, =sub_FF00FD84_my \n" //-->
"    MOV     R2, #0x200 \n" 
"    MOV     R1, #0x19 \n" 
"    LDR     R0, =0xFF00FEBC \n" 
"    BL      sub_FF00EAF0 \n"
"    MOV     R0, #0 \n" 
"    LDMFD   SP!, {R3,PC} \n"
    );
}

void __attribute__((naked,noinline)) sub_FF00FD84_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF024AEC \n" 
"    BL      sub_FF025C00 \n" 
"    BL      sub_FF023768 \n" 
"    BL      sub_FF02D9CC \n" 
"    BL      sub_FF023EDC \n" 
"    BL      sub_FF022C24 \n" 
"    BL      sub_FF022BB0 \n" 
"    LDMFD   SP!, {R4,LR} \n" 
"    B       sub_FF00FDDC_my \n" //-->
	);
}

void __attribute__((naked,noinline)) sub_FF00FDDC_my() {
asm volatile (
"    STMFD   SP!, {R3-R7,LR} \n" 
"    MOV     R6, #0 \n" 
"    BL      sub_FF02D73C \n" 
"    MOVS    R7, R0 \n" 
"    BNE     loc_FF00FE48 \n" 
"    BL      sub_FF0264BC \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF00FE48 \n" 
"    MOV     R0, #0x37 \n" 
"    BL      sub_FF02BC18 \n" 
"    RSBS    R5, R0, #1 \n" 
"    MOVCC   R5, #0 \n" 
"    MOV     R0, #0x36 \n" 
"    BL      sub_FF02BC18 \n" 
"    RSBS    R4, R0, #1 \n" 
"    MOVCC   R4, #0 \n" 
"    BL      sub_FF022BD8 \n" 
"    CMP     R0, #1 \n" 
"    MOVEQ   R6, #1 \n" 
"    ORR     R0, R4, R5 \n" 
"    ORRS    R0, R0, R6 \n" 
"    BNE     loc_FF00FE68 \n" 
"    BL      sub_FF0238F0 \n" 
"    LDR     R1, =0x83DC00 \n" 
"    MOV     R0, #0x54 \n" 
"    BL      sub_FF02BC08 \n" 
"loc_FF00FE44:\n"
"    B       loc_FF00FE44 \n" 
"loc_FF00FE48:\n"
"    MOV     R0, #0x36 \n" 
"    BL      sub_FF02BC18 \n" 
"    RSBS    R4, R0, #1 \n" 
"    MOVCC   R4, #0 \n" 
"    MOV     R0, #0x37 \n" 
"    BL      sub_FF02BC18 \n" 
"    RSBS    R5, R0, #1 \n" 
"    MOVCC   R5, #0 \n" 
"loc_FF00FE68:\n"
"    MOV     R3, R6 \n" 
"    MOV     R2, R7 \n" 
"    MOV     R1, R5 \n" 
"    MOV     R0, R4 \n" 
//"    BL      sub_FF024AF4 \n" // power button & startup, see sub_FF000364_my
"    BL      sub_FF024AF0 \n" 
"    BL      sub_FF02B598 \n" 
"    LDR     R1, =0x5CE000 \n" 
"    MOV     R0, #0 \n" 
"    BL      sub_FF02BA08 \n" 
"    BL      sub_FF02B7B0 \n" 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
//"    LDR     R3, =0xFF00FD34 \n" 
"    LDR     R3, =task_Startup_my \n" // -->
"    MOV     R2, #0 \n" 
"    MOV     R1, #0x19 \n" 
"    LDR     R0, =0xFF00FED0 \n" 
"    BL      sub_FF00EAF0 \n" 
"    MOV     R0, #0 \n" 
"    LDMFD   SP!, {R3-R7,PC} \n" 
	);
}

void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF0065E8 \n" 
//"    BL      sub_FF02D7E0 \n" // NULLSUB
//"    BL      sub_FF02D874 \n" // don't start DISKBOOT.BIN again
"    BL      sub_FF02DB88 \n" 
"    BL      sub_FF02D9FC \n" 
"    BL      sub_FF02AD3C \n"
"    BL      sub_FF02DB8C \n" 
//"    BL      sub_FF02496C \n" // PhySw
"    BL      CreateTask_spytask \n" // added
"    BL      taskcreatePhySw_my \n"  // we do this here rather than hook so we don't waste the original stack
"    BL      sub_FF028504 \n" 
"    BL      sub_FF02DBA4 \n" 
"    BL      sub_FF0217BC \n" 

"    BL      sub_FF02250C \n"
"    BL      sub_FF02D40C \n" 
"    BL      sub_FF022B64 \n" 
"    BL      sub_FF0224A8 \n" 
"    BL      sub_FF02E830 \n" 
"    BL      sub_FF02246C \n" 
"    LDMFD   SP!, {R4,LR} \n" 
"    B       sub_FF006708 \n"
     );
}

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n" 
"    LDR     R4, =0x1C3C \n" 
"    LDR     R0, [R4, #4] \n" 
"    CMP     R0, #0 \n" 
"    BNE     loc_FF0249A0 \n" 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
//"    LDR     R3, =0xFF024938 \n" 
//"    MOV     R2, #0x800 \n" 
"    LDR     R3, =mykbd_task \n" // task_PhySw
"    MOV     R2, #0x2000 \n" // stack size for new task_PhySw so we don't have to do stack switch
"    MOV     R1, #0x17 \n" 
"    LDR     R0, =0xFF024BEC \n" 
"    BL      sub_FF02B808 \n" 
"    STR     R0, [R4, #4] \n" 
"loc_FF0249A0:\n"
"    BL      sub_FF0595A4 \n" 
"    BL      sub_FF08FBB8 \n" 
"    BL      sub_FF02640C \n" 
"    CMP     R0, #0 \n" 
"    BNE     loc_FF0249C0 \n" 
"    LDR     R1, =0x386C8 \n" 
"    MOV     R0, #0 \n" 
"    BL      sub_FF08FB28 \n" 
"loc_FF0249C0:\n"
"    LDMFD   SP!, {R3-R5,PC} \n" 
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
void __attribute__((naked,noinline)) init_file_modules_task() {
    asm volatile(
"    STMFD   SP!, {R4-R6,LR} \n" 
"    BL      sub_FF092164 \n" 
"    LDR     R5, =0x5006 \n" 
"    MOVS    R4, R0 \n" 
"    MOVNE   R1, #0 \n" 
"    MOVNE   R0, R5 \n" 
"    BLNE    sub_FF096768 \n" 
"    BL      sub_FF092190 \n" 
"    BL      core_spytask_can_start\n"      // CHDK: Set "it's-safe-to-start" flag for spytask
"    CMP     R4, #0 \n" 
"    LDMNEFD SP!, {R4-R6,PC} \n" 
"    MOV     R0, R5 \n" 
"    LDMFD   SP!, {R4-R6,LR} \n" 
"    MOV     R1, #0 \n" 
"    B       sub_FF096768 \n" 
    );
}

/*----------------------------------------------------------------------
	Jogdial
*/
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
short *jog_position;

// Firmware version @ ff05927c
void __attribute__((naked,noinline)) JogDial_task_my() {
asm volatile (
"    STMFD   SP!, {R4-R11,LR} \n" 
"    SUB     SP, SP, #0x24 \n" 
"    BL      sub_FF059610 \n" 
"    LDR     R12, =0x2700 \n" 
"    LDR     R6, =0xFF4538CC \n" 
"    MOV     R0, #0 \n" 
// Save pointer for kbd.c routine - like sx40hs
" ADD R10, SP, #0x10 \n"
" LDR R9, =jog_position \n"
" STR R10, [R9] \n"
// -- 
"    ADD     R10, SP, #8 \n" 
"    ADD     R9, SP, #0x10 \n" 
"loc_FF05929C:\n"
"    ADD     R2, SP, #0x1C \n" 
"    MOV     R1, #0 \n" 
"    ADD     R4, R2, R0, LSL #1 \n" 
"    ADD     R3, SP, #0x18 \n" 
"    STRH    R1, [R4] \n" 
"    ADD     R4, R3, R0, LSL #1 \n" 
"    STRH    R1, [R4] \n" 
"    STR     R1, [R9, R0, LSL #2] \n" 
"    STR     R1, [R10, R0, LSL #2] \n" 
"    ADD     R0, R0, #1 \n" 
"    CMP     R0, #2 \n" 
"    BLT     loc_FF05929C \n" 
"loc_FF0592CC:\n"
"    LDR     R0, =0x2700 \n" 
"    MOV     R2, #0 \n" 
"    LDR     R0, [R0, #8] \n" 
"    MOV     R1, SP \n" 
"    BL      sub_FF02AFD0 \n" 
"    CMP     R0, #0 \n" 
"    LDRNE   R1, =0x256 \n" 
"    LDRNE   R0, =0xFF05952C \n" 
"    BLNE    sub_FF00EDC8 \n" 
"    LDR     R0, [SP] \n" 
"    AND     R4, R0, #0xFF \n" 
"    AND     R0, R0, #0xFF00 \n" 
"    CMP     R0, #0x100 \n" 
"    BEQ     loc_FF05933C \n" 
"    CMP     R0, #0x200 \n" 
"    BEQ     loc_FF059374 \n" 
"    CMP     R0, #0x300 \n" 
"    BEQ     loc_FF059574 \n" 
"    CMP     R0, #0x400 \n" 
"    BNE     loc_FF0592CC \n" 
"    CMP     R4, #0 \n" 
"    LDRNE   R1, =0x2E1 \n" 
"    LDRNE   R0, =0xFF05952C \n" 
"    BLNE    sub_FF00EDC8 \n" 
"    RSB     R0, R4, R4, LSL #3 \n" 
"    LDR     R0, [R6, R0, LSL #2] \n" 
"loc_FF059334:\n"
"    BL      sub_FF0595F4 \n" 
"    B       loc_FF0592CC \n" 
"loc_FF05933C:\n"
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n" //sleep
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
"    LDR     R0, =0x2710 \n" 
"    LDR     R0, [R0, R4, LSL #2] \n" 
"    BL      sub_FF02C1F4 \n" 
"    LDR     R2, =0xFF0591C8 \n" 
"    ORR     R3, R4, #0x200 \n" 
"    ADD     R1, R2, #0 \n" 
"    MOV     R0, #0x28 \n" 
"    BL      sub_FF02C110 \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R10, R4, LSL #2] \n" 
"    BEQ     loc_FF0592CC \n" 
"    MOV     R1, #0x268 \n" 
"    B       loc_FF059518 \n" 
"loc_FF059374:\n"
"    RSB     R5, R4, R4, LSL #3 \n" 
"    LDR     R0, [R6, R5, LSL #2] \n" 
"    LDR     R1, =0xC0240000 \n" 
"    ADD     R0, R1, R0, LSL #8 \n" 
"    LDR     R0, [R0, #0x104] \n" 
"    MOV     R1, R0, ASR #0x10 \n" 
"    ADD     R0, SP, #0x1C \n" 
"    ADD     R11, R0, R4, LSL #1 \n" 
"    ADD     R0, SP, #0x18 \n" 
"    ADD     R0, R0, R4, LSL #1 \n" 
"    STRH    R1, [R11] \n" 
"    STR     R0, [SP, #0x20] \n" 
"    LDRSH   R3, [R0] \n" 
"    SUB     R2, R1, R3 \n" 
"    CMP     R2, #0 \n" 
"    BNE     loc_FF0593F8 \n" 
"    LDR     R0, [R9, R4, LSL #2] \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF0594D4 \n" 
"    LDR     R7, =0x2710 \n" 
"    LDR     R0, [R7, R4, LSL #2] \n" 
"    BL      sub_FF02C1F4 \n" 
"    LDR     R2, =0xFF0591D4 \n" 
"    ORR     R3, R4, #0x300 \n" 
"    ADD     R1, R2, #0 \n" 
"    MOV     R0, #0x1F4 \n" 
"    BL      sub_FF02C110 \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R7, R4, LSL #2] \n" 
"    BEQ     loc_FF0594D4 \n" 
"    LDR     R1, =0x281 \n" 
"    B       loc_FF0594CC \n" 
"loc_FF0593F8:\n"
"    MOV     R0, R2 \n" 
"    RSBLT   R0, R0, #0 \n" 
"    MOVLE   R7, #0 \n" 
"    MOVGT   R7, #1 \n" 
"    CMP     R0, #0xFF \n" 
"    BLS     loc_FF059434 \n" 
"    LDR     R0, =0x7FFF \n" 
"    CMP     R2, #0 \n" 
"    SUBLE   R0, R0, R3 \n" 
"    ADDLE   R0, R0, R1 \n" 
"    SUBGT   R0, R0, R1 \n" 
"    ADDGT   R0, R0, R3 \n" 
"    MVN     R1, #0x8000 \n" 
"    SUB     R0, R0, R1 \n" 
"    EOR     R7, R7, #1 \n" 
"loc_FF059434:\n"
"    STR     R0, [SP, #4] \n" 
"    LDR     R0, [R9, R4, LSL #2] \n" 
"    CMP     R0, #0 \n" 
"    ADDEQ   R0, R6, R5, LSL #2 \n" 
"    LDREQ   R0, [R0, #8] \n" 
"    BEQ     loc_FF05946C \n" 
"    ADD     R8, R6, R5, LSL #2 \n" 
"    ADD     R1, R8, R7, LSL #2 \n" 
"    LDR     R1, [R1, #0x10] \n" 
"    CMP     R1, R0 \n" 
"    BEQ     loc_FF059470 \n" 
"    LDR     R0, [R8, #0xC] \n" 
"    BL      sub_FF0249C4 \n" 
"    LDR     R0, [R8, #8] \n" 
"loc_FF05946C:\n"
"    BL      sub_FF0249C4 \n" 
"loc_FF059470:\n"
"    ADD     R0, R6, R5, LSL #2 \n" 
"    ADD     R7, R0, R7, LSL #2 \n" 
"    LDR     R0, [R7, #0x10] \n" 
"    LDR     R1, [SP, #4] \n" 
"    BL      sub_FF0249D4 \n" 
"    LDR     R0, [R7, #0x10] \n" 
"    LDR     R7, =0x2710 \n" 
"    STR     R0, [R9, R4, LSL #2] \n" 
"    LDRH    R1, [R11] \n" 
"    LDR     R0, [SP, #0x20] \n" 
"    STRH    R1, [R0] \n" 
"    LDR     R0, [R7, R4, LSL #2] \n" 
"    BL      sub_FF02C1F4 \n" 
"    LDR     R2, =0xFF0591D4 \n" 
"    ORR     R3, R4, #0x300 \n" 
"    ADD     R1, R2, #0 \n" 
"    MOV     R0, #0x1F4 \n" 
"    BL      sub_FF02C110 \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R7, R4, LSL #2] \n" 
"    BEQ     loc_FF0594D4 \n" 
"    LDR     R1, =0x2C3 \n" 
"loc_FF0594CC:\n"
"    LDR     R0, =0xFF05952C \n" 
"    BL      sub_FF00EDC8 \n" 
"loc_FF0594D4:\n"
"    ADD     R0, R6, R5, LSL #2 \n" 
"    LDR     R0, [R0, #0x18] \n" 
"    CMP     R0, #1 \n" 
"    BNE     loc_FF05956C \n" 
"    LDR     R0, =0x2700 \n" 
"    LDR     R0, [R0, #0xC] \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF05956C \n" 
"    LDR     R2, =0xFF0591C8 \n" 
"    ORR     R3, R4, #0x400 \n" 
"    ADD     R1, R2, #0 \n" 
"    BL      sub_FF02C110 \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R10, R4, LSL #2] \n" 
"    BEQ     loc_FF0592CC \n" 
"    LDR     R1, =0x2CA \n" 
"loc_FF059518:\n"
"    LDR     R0, =0xFF05952C \n" 
"    BL      sub_FF00EDC8 \n" 
"    B       loc_FF0592CC \n" 
"loc_FF05956C:\n"
"    LDR     R0, [R6, R5, LSL #2] \n" 
"    B       loc_FF059334 \n" 
"loc_FF059574:\n"
"    LDR     R0, [R9, R4, LSL #2] \n" 
"    CMP     R0, #0 \n" 
"    MOVEQ   R1, #0x2D4 \n" 
"    LDREQ   R0, =0xFF05952C \n" 
"    BLEQ    sub_FF00EDC8 \n" 
"    RSB     R0, R4, R4, LSL #3 \n" 
"    ADD     R0, R6, R0, LSL #2 \n" 
"    LDR     R0, [R0, #0xC] \n" 
"    BL      sub_FF0249C4 \n" 
"    MOV     R0, #0 \n" 
"    STR     R0, [R9, R4, LSL #2] \n" 
"    B       loc_FF0592CC \n" 
	);

}
/*-----------------------------------------------------------------------*/
