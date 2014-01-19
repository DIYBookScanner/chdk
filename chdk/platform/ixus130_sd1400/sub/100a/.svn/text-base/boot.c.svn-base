#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

extern void task_PhySw();
extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();

void taskHook(context_t **context)
{
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));
	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_PhySw)             tcb->entry = (void*)mykbd_task;
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task;
	if(tcb->entry == (void*)task_InitFileModules)   tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

void __attribute__((naked,noinline)) boot(  ) {
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
"    MOV     R0, #0x33 \n"
"    MCR     p15, 0, R0, c6, c2 \n"
"    MOV     R0, #0x40000033 \n"
"    MCR     p15, 0, R0, c6, c3 \n"
"    MOV     R0, #0x80000017 \n"
"    MCR     p15, 0, R0, c6, c4 \n"
"    LDR     R0, =0xFF80002D \n"
"    MCR     p15, 0, R0, c6, c5 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c2, c0 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c2, c0, 1 \n"
"    MOV     R0, #0x34 \n"
"    MCR     p15, 0, R0, c3, c0 \n"
"    LDR     R0, =0x3333330 \n"
"    MCR     p15, 0, R0, c5, c0, 2 \n"
"    LDR     R0, =0x3333330 \n"
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
"    LDR     R0, =0xFFBF837C \n"   // 1.00a
"    LDR     R1, =0x1900 \n"
"    LDR     R3, =0xEBD0 \n"
"loc_FF81013C:\n"
"    CMP     R1, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF81013C \n"
"    LDR     R1, =0x14FE20 \n"
"    MOV     R2, #0 \n"
"loc_FF810154:\n"
"    CMP     R3, R1 \n"
"    STRCC   R2, [R3], #4 \n"
"    BCC     loc_FF810154 \n"
"    B       sub_FF810354_my \n" //--------->
	);
};


void __attribute__((naked,noinline)) sub_FF810354_my(  ) {

  // Power Button detection (short press = playback mode, long press = record mode)
  // replacement for sub_ff834348
  *(int*)0x2480 = (*(int*)0xC0220128) & 1 ? 0x400000 : 0x200000;

  *(int*)0x1938 = (int)taskHook;

asm volatile (
"    LDR     R0, =0xFF8103CC \n"
"    MOV     R1, #0 \n"
"    LDR     R3, =0xFF810404 \n"
"loc_FF810360:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF810360 \n"
"    LDR     R0, =0xFF810404 \n"
"    MOV     R1, #0x4B0 \n"
"    LDR     R3, =0xFF810618 \n"
"loc_FF81037C:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF81037C \n"
"    MOV     R0, #0xD2 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    MOV     R0, #0xD3 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    LDR     R0, =0x6C4 \n"
"    LDR     R2, =0xEEEEEEEE \n"
"    MOV     R3, #0x1000 \n"
"loc_FF8103B0:\n"
"    CMP     R0, R3 \n"
"    STRCC   R2, [R0], #4 \n"
"    BCC     loc_FF8103B0 \n"
"    BL      sub_FF811198_my \n"  //-------------->
	);
}

void __attribute__((naked,noinline)) sub_FF811198_my(  ) {
asm volatile (
"    STR     LR, [SP, #-4]! \n"
"    SUB     SP, SP, #0x74 \n"
"    MOV     R0, SP \n"
"    MOV     R1, #0x74 \n"
"    BL      sub_FFB39910 \n"    // 1.00a
"    MOV     R0, #0x53000 \n"
"    STR     R0, [SP, #4] \n"
//"    LDR     R0, =0x14FE20 \n"
"    LDR     R0, =new_sa\n"        // + remove the line ^ if using these two
"    LDR     R0, [R0]\n"           // + this is related to chdk size
"    LDR     R2, =0x339C00\n"
"    LDR     R1, =0x3324A8\n"
"    STR     R0, [SP, #8] \n"
"    SUB     R0, R1, R0 \n"
"    ADD     R3, SP, #0xC \n"
"    STR     R2, [SP] \n"
"    STMIA   R3, {R0-R2} \n"
"    MOV     R0, #0x22 \n"
"    STR     R0, [SP, #0x18] \n"
"    MOV     R0, #0x68 \n"
"    STR     R0, [SP, #0x1C] \n"
"    LDR     R0, =0x19B \n"
"    LDR     R1, =sub_FF815E58_my \n" //---------->
"    STR     R0, [SP, #0x20] \n"
"    MOV     R0, #0x96 \n"
"    STR     R0, [SP, #0x24] \n"
"    MOV     R0, #0x78 \n"
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
"    MOV     R0, SP \n"
"    MOV     R2, #0 \n"
"    BL      sub_FF813404 \n"
"    ADD     SP, SP, #0x74 \n"
"    LDR     PC, [SP], #4 \n"
	);
}


void __attribute__((naked,noinline)) sub_FF815E58_my(  ) {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FF810B20 \n"
"    BL      sub_FF81A244 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF815F6C \n"
"    BLLT    sub_FF815F4C \n"
"    BL      sub_FF815A94 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF815F74 \n"
"    BLLT    sub_FF815F4C \n"
"    LDR     R0, =0xFF815F84 \n"
"    BL      sub_FF815B7C \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF815F8C \n"
"    BLLT    sub_FF815F4C \n"
"    LDR     R0, =0xFF815F84 \n"
"    BL      sub_FF813BF0 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF815FA0 \n"
"    BLLT    sub_FF815F4C \n"
"    BL      sub_FF819C3C \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF815FAC \n"
"    BLLT    sub_FF815F4C \n"
"    BL      sub_FF81167C \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF815FB8 \n"
"    BLLT    sub_FF815F4C \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       taskcreate_Startup_my\n" //-------->
	);
}


void __attribute__((naked,noinline)) taskcreate_Startup_my(  ) {
asm volatile (
"    STMFD   SP!, {R3,LR}\n"
"    BL      sub_FF834340\n"
"    BL      sub_FF83BA88\n"
"    CMP     R0, #0\n"
"    BNE     loc_FF81FB34 \n"
"    BL      sub_FF835B2C \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF81FB34 \n"
"    BL      sub_FF83433C \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF81FB34 \n"
"    BL      sub_FF8339DC \n"
"    LDR     R1, =0xC0220000 \n"
"    MOV     R0, #0x44 \n"
"    STR     R0, [R1, #0x1C] \n"
"    BL      sub_FF833BC8 \n"
"loc_FF81FB30:\n"
"    B       loc_FF81FB30 \n"
"loc_FF81FB34:\n"
//"    BL      sub_FF834348 \n"   // hijack power-on
"    BL      sub_FF834344 \n"
"    BL      sub_FF839CB0 \n"
"    LDR     R1, =0x38E000 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF83A0F8 \n"
"    BL      sub_FF839EA4 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =task_Startup_my \n"   //------->
"    MOV     R2, #0 \n"
"    MOV     R1, #0x19 \n"
"    LDR     R0, =0xFF81FB7C \n"
"    BL      sub_FF81E83C \n"
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R12,PC} \n"
   );
}

void __attribute__((naked,noinline)) taskcreate_PhySw_my() {
asm volatile(
"    STMFD   SP!, {R3-R5,LR} \n"
"    LDR     R4, =0x1C20 \n"
"    LDR     R0, [R4, #0x10] \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF834264 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3,  =mykbd_task\n"		// Changed
//"  MOV     R2, #0x800 \n"
"    MOV     R2, #0x2000\n"			// + stack size for new task_PhySw so we don't have to do stack switch
"    B       sub_FF834254\n"   //  continue in code
"loc_FF834264:\n"
"    BL      sub_FF834264 \n"    // continue in code
	);
}

void __attribute__((naked,noinline)) task_Startup_my(  ) {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FF81650C \n"
"    BL      sub_FF83543C \n"
"    BL      sub_FF833638 \n"
"    BL      sub_FF83BAC8 \n"
"    BL      sub_FF83BCB4 \n"
//"    BL      sub_FF83BB5C \n" // This should be the DISKBOOT start
"    BL      sub_FF83BE58 \n"
"    BL      sub_FF8322E4 \n"
"    BL      sub_FF83BCE4 \n"
"    BL      sub_FF839454 \n"
"    BL      CreateTask_spytask\n" // +
"    BL      sub_FF83BE5C \n"
//"  BL      sub_FF834230 \n"
"    BL      taskcreate_PhySw_my\n"	// +
"    BL      sub_FF8377A8 \n"
"    BL      sub_FF83BE74 \n"
"    BL      sub_FF8316A8 \n"
"    BL      sub_FF833090 \n"
"    BL      sub_FF83B860 \n"
"    BL      sub_FF8335EC \n"
"    BL      sub_FF83302C \n"
"    BL      sub_FF832318 \n"
"    BL      sub_FF83C8F4 \n"
"    BL      sub_FF833004 \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       sub_FF81662C \n"
     );
}

/*----------------------------------------------------------------------
	init_file_modules_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) init_file_modules_task(  ) {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    BL      sub_FF88CAC0 \n"    // 1.00a
"    LDR     R5, =0x5006 \n"
"    MOVS    R4, R0 \n"
"    MOVNE   R1, #0 \n"
"    MOVNE   R0, R5 \n"
"    BLNE    sub_FF8904CC \n"     // 1.00a
"    BL      sub_FF88CAEC_my \n"  // 1.00a  ----->
"    BL      core_spytask_can_start\n"	// added
"    CMP     R4, #0 \n"
"    MOVEQ   R0, R5 \n"
"    LDMEQFD SP!, {R4-R6,LR} \n"
"    MOVEQ   R1, #0 \n"
"    BEQ     sub_FF8904CC \n"     // 1.00a
"    LDMFD   SP!, {R4-R6,PC} \n"
	);
}


void __attribute__((naked,noinline)) sub_FF88CAEC_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    MOV     R0, #3 \n"
"    BL      sub_FF86F084_my \n"    //----->
"    BL      sub_FF93FFDC \n"     //  1.00a
"    LDR     R4, =0x2F54 \n"
"    LDR     R0, [R4, #4] \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF88CB24 \n"    // 1.00a
"    BL      sub_FF86E2CC \n"
"    BL      sub_FF9344A0 \n"    // 1.00a
"    BL      sub_FF86E2CC \n"
"    BL      sub_FF86A6F0 \n"
"    BL      sub_FF86E1CC \n"
"    BL      sub_FF93453C \n"    // 1.00a
"loc_FF88CB24:\n"                // 1.00a     
"    MOV     R0, #1 \n"
"    STR     R0, [R4] \n"
"    LDMFD   SP!, {R4,PC} \n"
	);
}


void __attribute__((naked,noinline)) sub_FF86F084_my(  ) {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R8, R0 \n"
"    BL      sub_FF86F004 \n"
"    LDR     R1, =0x38448 \n"
"    MOV     R6, R0 \n"
"    ADD     R4, R1, R0, LSL #7 \n"
"    LDR     R0, [R4, #0x6C] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R1, =0x85A \n"
"    LDREQ   R0, =0xFF86EB44 \n"
"    BLEQ    sub_FF81EB14 \n"
"    MOV     R1, R8 \n"
"    MOV     R0, R6 \n"
"    BL      sub_FF86E8BC \n"
"    LDR     R0, [R4, #0x38] \n"
"    BL      sub_FF86F724 \n"
"    CMP     R0, #0 \n"
"    STREQ   R0, [R4, #0x6C] \n"
"    MOV     R0, R6 \n"
"    BL      sub_FF86E94C \n"      
"    MOV     R0, R6 \n"
"    BL      sub_FF86ECAC_my \n"    //  ----->
"    MOV     R5, R0 \n"
"    MOV     R0, R6 \n"
"    BL      sub_FF86EEDC \n"
"    LDR     R6, [R4, #0x3C] \n"
"    AND     R7, R5, R0 \n"
"    CMP     R6, #0 \n"
"    LDR     R1, [R4, #0x38] \n"
"    MOVEQ   R0, #0x80000001 \n"
"    MOV     R5, #0 \n"
"    BEQ     loc_FF86F134 \n"
"    MOV     R0, R1 \n"
"    BL      sub_FF86E434 \n"
"    CMP     R0, #0 \n"
"    MOVNE   R5, #4 \n"
"    CMP     R6, #5 \n"
"    ORRNE   R0, R5, #1 \n"
"    BICEQ   R0, R5, #1 \n"
"    CMP     R7, #0 \n"
"    BICEQ   R0, R0, #2 \n"
"    ORREQ   R0, R0, #0x80000000 \n"
"    BICNE   R0, R0, #0x80000000 \n"
"    ORRNE   R0, R0, #2 \n"
"loc_FF86F134:\n"
"    CMP     R8, #7 \n"
"    STR     R0, [R4, #0x40] \n"
"    LDMNEFD SP!, {R4-R8,PC} \n"
"    MOV     R0, R8 \n"
"    BL      sub_FF86F054 \n"
"    CMP     R0, #0 \n"
"    LDMEQFD SP!, {R4-R8,LR} \n"
"    LDREQ   R0, =0xFF86F180 \n"
"    BEQ     sub_FF81177C \n"
"    LDMFD   SP!, {R4-R8,PC} \n"
	);
}

void __attribute__((naked,noinline)) sub_FF86ECAC_my(  ) {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    MOV     R5, R0 \n"
"    LDR     R0, =0x38448 \n"
"    ADD     R4, R0, R5, LSL #7 \n"
"    LDR     R0, [R4, #0x6C] \n"
"    TST     R0, #2 \n"
"    MOVNE   R0, #1 \n"
"    LDMNEFD SP!, {R4-R6,PC} \n"
"    LDR     R0, [R4, #0x38] \n"
"    MOV     R1, R5 \n"
"    BL      sub_FF86E9CC_my \n"     // ------>
"    CMP     R0, #0 \n"
"    LDRNE   R0, [R4, #0x38] \n"
"    MOVNE   R1, R5 \n"
"    BLNE    sub_FF86EB68 \n"
"    LDR     R2, =0x384C8 \n"
"    ADD     R1, R5, R5, LSL #4 \n"
"    LDR     R1, [R2, R1, LSL #2] \n"
"    CMP     R1, #4 \n"
"    BEQ     loc_FF86ED0C \n"
"    CMP     R0, #0 \n"
"    LDMEQFD SP!, {R4-R6,PC} \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF86E4C4 \n"
"loc_FF86ED0C:\n"
"    CMP     R0, #0 \n"
"    LDRNE   R1, [R4, #0x6C] \n"
"    ORRNE   R1, R1, #2 \n"
"    STRNE   R1, [R4, #0x6C] \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
	);
}


void __attribute__((naked,noinline)) sub_FF86E9CC_my(  ) {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R9, R0 \n"
"    LDR     R0, =0x38448 \n"
"    MOV     R8, #0 \n"
"    ADD     R5, R0, R1, LSL #7 \n"
"    LDR     R0, [R5, #0x3C] \n"
"    MOV     R7, #0 \n"
"    CMP     R0, #7 \n"
"    MOV     R6, #0 \n"
"    ADDLS   PC, PC, R0, LSL #2 \n"
"    B       loc_FF86EB24 \n"
"    B       loc_FF86EA30 \n"
"    B       loc_FF86EA18 \n"
"    B       loc_FF86EA18 \n"
"    B       loc_FF86EA18 \n"
"    B       loc_FF86EA18 \n"
"    B       loc_FF86EB1C \n"
"    B       loc_FF86EA18 \n"
"    B       loc_FF86EA18 \n"
"loc_FF86EA18:\n"
"    MOV     R2, #0 \n"
"    MOV     R1, #0x200 \n"
"    MOV     R0, #2 \n"
"    BL      sub_FF886B70 \n"   // 1.00a
"    MOVS    R4, R0 \n"
"    BNE     loc_FF86EA38 \n"
"loc_FF86EA30:\n"
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R4-R10,PC} \n"
"loc_FF86EA38:\n"
"    LDR     R12, [R5, #0x50] \n"
"    MOV     R3, R4 \n"
"    MOV     R2, #1 \n"
"    MOV     R1, #0 \n"
"    MOV     R0, R9 \n"
"    BLX     R12 \n"
"    CMP     R0, #1 \n"
"    BNE     loc_FF86EA64 \n"
"    MOV     R0, #2 \n"
"    BL      sub_FF886CBC \n"    // 1.00a
"    B       loc_FF86EA30 \n"
"loc_FF86EA64:\n"
"    LDR     R1, [R5, #0x64] \n"
"    MOV     R0, R9 \n"
"    BLX     R1 \n"

//------------------  begin added code ---------------
		"MOV   R1, R4\n"           //  pointer to MBR in R1
		"BL    mbr_read_dryos\n"   //  total sectors count in R0 before and after call

		// Start of DataGhost's FAT32 autodetection code
		// Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
		// According to the code below, we can use R1, R2, R3 and R12.
		// LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
		// that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
		"MOV     R12, R4\n"                    // Copy the MBR start address so we have something to work with
		"MOV     LR, R4\n"                     // Save old offset for MBR signature
		"MOV     R1, #1\n"                     // Note the current partition number
		"B       dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
   "dg_sd_fat32:\n"
		"CMP     R1, #4\n"                     // Did we already see the 4th partition?
		"BEQ     dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
		"ADD     R12, R12, #0x10\n"            // Second partition
		"ADD     R1, R1, #1\n"                 // Second partition for the loop
   "dg_sd_fat32_enter:\n"
		"LDRB    R2, [R12, #0x1BE]\n"          // Partition status
		"LDRB    R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
		"CMP     R3, #0xB\n"                   // Is this a FAT32 partition?
		"CMPNE   R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
		"BNE     dg_sd_fat32\n"                // No, it isn't.
		"CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
		"CMPNE   R2, #0x80\n"
		"BNE     dg_sd_fat32\n"                // Invalid, go to next partition
											   // This partition is valid, it's the first one, bingo!
		"MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.

   "dg_sd_fat32_end:\n"
		// End of DataGhost's FAT32 autodetection code
//------------------  end added code ---------------


"    LDRB    R1, [R4, #0x1C9] \n"
"    LDRB    R3, [R4, #0x1C8] \n"
"    LDRB    R12, [R4, #0x1CC] \n"
"    MOV     R1, R1, LSL #0x18 \n"
"    ORR     R1, R1, R3, LSL #0x10 \n"
"    LDRB    R3, [R4, #0x1C7] \n"
"    LDRB    R2, [R4, #0x1BE] \n"

//"    LDRB    LR, [R4, #0x1FF] \n" // delete for FAT32

"    ORR     R1, R1, R3, LSL #8 \n"
"    LDRB    R3, [R4, #0x1C6] \n"
"    CMP     R2, #0 \n"
"    CMPNE   R2, #0x80 \n"
"    ORR     R1, R1, R3 \n"
"    LDRB    R3, [R4, #0x1CD] \n"
"    MOV     R3, R3, LSL #0x18 \n"
"    ORR     R3, R3, R12, LSL #0x10 \n"
"    LDRB    R12, [R4, #0x1CB] \n"
"    ORR     R3, R3, R12, LSL #8 \n"
"    LDRB    R12, [R4, #0x1CA] \n"
"    ORR     R3, R3, R12 \n"

//"    LDRB    R12, [R4, #0x1FE] \n"    // delete for FAT32
"    LDRB    R12, [LR,#0x1FE]\n"        // New! First MBR signature byte (0x55)
"    LDRB    LR, [LR,#0x1FF]\n"         //      Last MBR signature byte (0xAA)

"    BNE     loc_FF86EAF0 \n"
"    CMP     R0, R1 \n"
"    BCC     loc_FF86EAF0 \n"
"    ADD     R2, R1, R3 \n"
"    CMP     R2, R0 \n"
"    CMPLS   R12, #0x55 \n"
"    CMPEQ   LR, #0xAA \n"
"    MOVEQ   R7, R1 \n"
"    MOVEQ   R6, R3 \n"
"    MOVEQ   R4, #1 \n"
"    BEQ     loc_FF86EAF4 \n"
"loc_FF86EAF0:\n"
"    MOV     R4, R8 \n"
"loc_FF86EAF4:\n"
"    MOV     R0, #2 \n"
"    BL      sub_FF886CBC \n"   // 1.00a
"    CMP     R4, #0 \n"
"    BNE     loc_FF86EB30 \n"
"    LDR     R1, [R5, #0x64] \n"
"    MOV     R7, #0 \n"
"    MOV     R0, R9 \n"
"    BLX     R1 \n"
"    MOV     R6, R0 \n"
"    B       loc_FF86EB30 \n"
"loc_FF86EB1C:\n"
"    MOV     R6, #0x40 \n"
"    B       loc_FF86EB30 \n"
"loc_FF86EB24:\n"
"    LDR     R1, =0x5B2 \n"
"    LDR     R0, =0xFF86EB44 \n"
"    BL      sub_FF81EB14 \n"
"loc_FF86EB30:\n"
"    STR     R7, [R5, #0x44]! \n"
"    STMIB   R5, {R6,R8} \n"
"    MOV     R0, #1 \n"
"    LDMFD   SP!, {R4-R10,PC} \n"
	);
}
