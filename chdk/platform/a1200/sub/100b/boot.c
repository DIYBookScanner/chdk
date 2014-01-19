#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_PhySw();

#define LED_GR  0xC0220014      // green
#define LED_OR  0xC0220010      // orange
#define LED_AF  0xC022000C      // autofocus (front)

void taskHook(context_t **context) {

    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

    // Replace firmware task addresses with ours
    if(tcb->entry == (void*)task_PhySw)         tcb->entry = (void*)mykbd_task;
    if(tcb->entry == (void*)task_InitFileModules)       tcb->entry = (void*)init_file_modules_task;
    if(tcb->entry == (void*)task_MovieRecord)       tcb->entry = (void*)movie_record_task;
    if(tcb->entry == (void*)task_CaptSeq)           tcb->entry = (void*)capt_seq_task;
    if(tcb->entry == (void*)task_ExpDrv)            tcb->entry = (void*)exp_drv_task;
}

void __attribute__((naked,noinline)) boot(  ) {
    // FF81000C
   volatile int *p=(void*)LED_AF;
   *p=0x46;
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
      "    LDR     R0, =0xFFC2B8D4 \n"     // 1.00b
      "    LDR     R1, =0x1900 \n"
      "    LDR     R3, =0xECD8 \n"
"loc_FF81013C:\n"
      "    CMP     R1, R3 \n"
      "    LDRCC   R2, [R0], #4 \n"
      "    STRCC   R2, [R1], #4 \n"
      "    BCC     loc_FF81013C \n"
      "    LDR     R1, =0x16913C \n"
      "    MOV     R2, #0 \n"
"loc_FF810154:\n"
      "    CMP     R3, R1 \n"
      "    STRCC   R2, [R3], #4 \n"
      "    BCC     loc_FF810154 \n"
      "    B       sub_FF810358_my \n"              // ---> patched
    );
}

void __attribute__((naked,noinline)) sub_FF810358_my() {

    *(int*)0x1938=(int)taskHook;
    *(int*)0x193C=(int)taskHook;

        // sub_ff81fc58 + sub_0xff85f308
        if ((*(int*) 0xC0220118) & 1)                          // look at play switch
                *(int*)(0x24CC) = 0x200000;                    // start in play mode
        else
                *(int*)(0x24CC) = 0x100000;                    // start in rec mode


    // sub_FF810358
    asm volatile (
      "    LDR     R0, =0xFF8103D0 \n"
      "    MOV     R1, #0 \n"
      "    LDR     R3, =0xFF810408 \n"
"loc_FF810364:\n"
      "    CMP     R0, R3 \n"
      "    LDRCC   R2, [R0], #4 \n"
      "    STRCC   R2, [R1], #4 \n"
      "    BCC     loc_FF810364 \n"
      "    LDR     R0, =0xFF810408 \n"
      "    MOV     R1, #0x4B0 \n"
      "    LDR     R3, =0xFF81061C \n"
"loc_FF810380:\n"
      "    CMP     R0, R3 \n"
      "    LDRCC   R2, [R0], #4 \n"
      "    STRCC   R2, [R1], #4 \n"
      "    BCC     loc_FF810380 \n"
      "    MOV     R0, #0xD2 \n"
      "    MSR     CPSR_cxsf, R0 \n"
      "    MOV     SP, #0x1000 \n"
      "    MOV     R0, #0xD3 \n"
      "    MSR     CPSR_cxsf, R0 \n"
      "    MOV     SP, #0x1000 \n"
      "    LDR     R0, =0x6C4 \n"
      "    LDR     R2, =0xEEEEEEEE \n"
      "    MOV     R3, #0x1000 \n"
"loc_FF8103B4:\n"
      "    CMP     R0, R3 \n"
      "    STRCC   R2, [R0], #4 \n"
      "    BCC     loc_FF8103B4 \n"
      "    BL      sub_FF8111B0_my \n"          //--------> doesn't return here - could be just a B ?

"loc_LOOPED:\n"                     // trap
    "   LDR     R0, =0xC0220010 \n"
    "   MOV     R1, #0x46 \n"
    "   STR     R1, [R0] \n"
    "   B       loc_LOOPED\n"

    );
}

void __attribute__((naked,noinline)) sub_FF8111B0_my(  ) {
    // FF8111B0
asm volatile (
      "    STR     LR, [SP, #-4]! \n"
      "    SUB     SP, SP, #0x74 \n"
      "    MOV     R1, #0x74 \n"
      "    MOV     R0, SP \n"
      "    BL      sub_FFB5288C \n"             // 1.00b
      "    MOV     R0, #0x53000 \n"
      "    STR     R0, [SP, #4] \n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
      "    LDR     R0, =0x16913C \n"            // use original heap offset since CHDK is loaded in high memory
#else
      "    LDR     R0, =new_sa \n"          // otherwise use patched value
      "    LDR     R0, [R0] \n"             //
#endif
      "    LDR     R2, =0x2F1F80 \n"
      "    STR     R0, [SP, #8] \n"
      "    SUB     R0, R2, R0 \n"
      "    STR     R0, [SP, #0xC] \n"
      "    MOV     R0, #0x22 \n"
      "    STR     R0, [SP, #0x18] \n"
      "    MOV     R0, #0x68 \n"
      "    STR     R0, [SP, #0x1C] \n"
      "    LDR     R1, =0x2F9C00 \n"
      "    LDR     R0, =0x19B \n"
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
      "    LDR     R1, =sub_FF815EE0_my \n"            // ---> patched
      "    MOV     R2, #0 \n"
      "    MOV     R0, SP \n"
      "    BL      sub_FF8134C4 \n"
      "    ADD     SP, SP, #0x74 \n"
      "    LDR     PC, [SP], #4 \n"
    );
}

void __attribute__((naked,noinline)) sub_FF815EE0_my(  ) {
    // FF815EE0
asm volatile (
      "    STMFD   SP!, {R4,LR} \n"
      "    BL      sub_FF810B28 \n"
      "    BL      sub_FF81A374 \n"
      "    CMP     R0, #0 \n"
      "    LDRLT   R0, =0xFF815FF4 \n"
      "    BLLT    sub_FF815FD4 \n"
      "    BL      sub_FF815B18 \n"
      "    CMP     R0, #0 \n"
      "    LDRLT   R0, =0xFF815FFC \n"
      "    BLLT    sub_FF815FD4 \n"
      "    LDR     R0, =0xFF81600C \n"
      "    BL      sub_FF815C00 \n"
      "    CMP     R0, #0 \n"
      "    LDRLT   R0, =0xFF816014 \n"
      "    BLLT    sub_FF815FD4 \n"
      "    LDR     R0, =0xFF81600C \n"
      "    BL      sub_FF813CA8 \n"
      "    CMP     R0, #0 \n"
      "    LDRLT   R0, =0xFF816028 \n"
      "    BLLT    sub_FF815FD4 \n"
      "    BL      sub_FF819D00 \n"
      "    CMP     R0, #0 \n"
      "    LDRLT   R0, =0xFF816034 \n"
      "    BLLT    sub_FF815FD4 \n"
      "    BL      sub_FF811690 \n"
      "    CMP     R0, #0 \n"
      "    LDRLT   R0, =0xFF816040 \n"
      "    BLLT    sub_FF815FD4 \n"
      "    LDMFD   SP!, {R4,LR} \n"
      "    B       taskcreate_Startup_my \n"        // ---> patched
    );
}

void __attribute__((naked,noinline)) taskcreate_Startup_my(  ) {
    // FF81FC58
asm volatile (
      "    STMFD   SP!, {R3-R9,LR} \n"
      "    MOV     R6, #0 \n"
      "    BL      sub_FF834038 \n"             // nullsub
      "    BL      sub_FF83BB9C \n"
      "    LDR     R9, =0xC0220000 \n"
      "    MOVS    R7, R0 \n"
      "    MOV     R8, #1 \n"
      "    BNE     loc_FF81FCC0 \n"
      "    BL      sub_FF83593C \n"
      "    CMP     R0, #0 \n"
      "    BEQ     loc_FF81FCC0 \n"
      "    LDR     R0, [R9, #0x11C] \n"
      "    BIC     R5, R8, R0 \n"
      "    LDR     R0, [R9, #0x118] \n"
      "    BIC     R4, R8, R0 \n"
      "    BL      sub_FF8333F0 \n"
      "    CMP     R0, #1 \n"
      "    MOVEQ   R6, #1 \n"
      "    ORR     R0, R4, R5 \n"
      "    ORRS    R0, R0, R6 \n"
      "    BNE     loc_FF81FCD0 \n"
      "    BL      sub_FF8336DC \n"
      "    MOV     R0, #0x44 \n"
      "    STR     R0, [R9, #0x80] \n"
      "    BL      sub_FF8338D0 \n"
"loc_FF81FCBC:\n"
      "    B       loc_FF81FCBC \n"
"loc_FF81FCC0:\n"
      "    LDR     R0, [R9, #0x118] \n"
      "    BIC     R4, R8, R0 \n"
      "    LDR     R0, [R9, #0x11C] \n"
      "    BIC     R5, R8, R0 \n"
"loc_FF81FCD0:\n"
      "    MOV     R3, R6 \n"
      "    MOV     R2, R7 \n"
      "    MOV     R1, R5 \n"
      "    MOV     R0, R4 \n"
  //  "    BL      sub_FF834040 \n"             // we must remove this for power-on mode handling to work
      "    BL      sub_FF83403C \n"             // nullsub
      "    BL      sub_FF839D6C \n"
      "    LDR     R1, =0x34E000 \n"
      "    MOV     R0, #0 \n"
      "    BL      sub_FF83A1DC \n"
      "    BL      sub_FF839F84 \n"
      "    MOV     R3, #0 \n"
      "    STR     R3, [SP] \n"
   // "    LDR     R3, =0xFF81FBF4 \n"          // deleted
      "    LDR     R3, =task_Startup_my \n"     //patched
      "    MOV     R2, #0 \n"
      "    MOV     R1, #0x19 \n"
      "    LDR     R0, =0xFF81FD2C \n"
      "    BL      sub_FF81E9B0 \n"
      "    MOV     R0, #0 \n"
      "    LDMFD   SP!, {R3-R9,PC} \n"
    );
}


void __attribute__((naked,noinline)) task_Startup_my(  ) {
    //FF81FBF4
asm volatile (
      "    STMFD   SP!, {R4,LR} \n"
      "    BL      sub_FF816588 \n"
      "    BL      sub_FF8351AC \n"
      "    BL      sub_FF833400 \n"
      "    BL      sub_FF83BBE4 \n"
      "    BL      sub_FF83BDD0 \n"
//    "    BL      sub_FF83BC78 \n"                 // skip starting diskboot.bin again
      "    BL      sub_FF83BF6C \n"
      "    BL      sub_FF832208 \n"
      "    BL      sub_FF83BE00 \n"
      "    BL      sub_FF839510 \n"
      "    BL      sub_FF83BF70 \n"
      "    BL      CreateTask_spytask \n"           // added
//    "    BL      sub_FF833F00 \n"             // deleted
      "    BL      taskcreatePhySw_my \n"           // patched
      "    BL      sub_FF8378AC \n"
      "    BL      sub_FF83BF88 \n"
      "    BL      sub_FF831600 \n"
      "    BL      sub_FF832E0C \n"
      "    BL      sub_FF83B958 \n"
      "    BL      sub_FF8333A0 \n"
      "    BL      sub_FF832DAC \n"
      "    BL      sub_FF83223C \n"
      "    BL      sub_FF83CA1C \n"
      "    BL      sub_FF832D70 \n"
      "    LDMFD   SP!, {R4,LR} \n"
      " STMFD   SP!, {R0,R1} \n"
      " LDR     R0, =0xC0220010 \n"
      " MOV     R1, #0x46 \n"
      " STR     R1, [R0] \n"
      " LDMFD   SP!, {R0,R1} \n"
      "    B       sub_FF8166A8 \n"                 // continue in firmware
    );
}

void __attribute__((naked,noinline)) taskcreatePhySw_my(  ) {
   // FF833F00
asm volatile (
      "    STMFD   SP!, {R3-R5,LR} \n"
      "    LDR     R4, =0x1C30 \n"
      "    LDR     R0, [R4, #4] \n"
      "    CMP     R0, #0 \n"
      "    BNE     sub_FF833F34 \n"             // so we can jump right back in to firmware later
      "    MOV     R3, #0 \n"
      "    STR     R3, [SP] \n"
      "    LDR     R3, =0xFF833ECC \n"
//    "    LDR  R3, =mykbd_task \n"         // task_PhySw, no need to replace 0xFF834214 manualy, defined in taskHook
//    "    MOV     R2, #0x800 \n"
      "    MOV     R2, #0x2000 \n"          // stack size for new task_PhySw so we don't have to do stack switch
      "    B       sub_FF833F24 \n"         // added, continue in firmware
    );
}

void CreateTask_spytask() {

        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

void __attribute__((naked,noinline)) init_file_modules_task() {
    // FF8928C0
    asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n"
      "    BL      sub_FF88A7C8 \n"
      "    LDR     R5, =0x5006 \n"
      "    MOVS    R4, R0 \n"
      "    MOVNE   R1, #0 \n"
      "    MOVNE   R0, R5 \n"
      "    BLNE    sub_FF88E65C \n"
      "    BL      sub_FF88A7F4 \n"
      "    BL      core_spytask_can_start \n"       // added, CHDK: Set "it's-safe-to-start"-Flag for spytask
      "    B       sub_FF8928E0 \n"         // added, continue in firmware
    );
}
