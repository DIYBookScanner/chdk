#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_spytask();
void boot();
void capt_seq_task();

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
void task_JogDial_my();

void taskHook(context_t **context) { 
 task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

// physw is done directly to avoid wasting stack space
// if(!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task; 
 if(tcb->entry == task_CaptSeq)         tcb->entry = (void*)capt_seq_task; 
 if(tcb->entry == task_InitFileModules) tcb->entry = (void*)init_file_modules_task;
 if(tcb->entry == task_MovieRecord)     tcb->entry = (void*)movie_record_task;
 if(tcb->entry == task_ExpDrv)          tcb->entry = (void*)exp_drv_task;
 if(tcb->entry == (void*)0xFF844220)           tcb->entry = (void*)task_JogDial_my;
}

#define DEBUG_LED ((unsigned volatile *)0xC0220130) // green?
#define GREEN_LED ((unsigned volatile *)0xC0220134) // red?
//0xc0220018: ixus110 sd power?

void boot() {
    asm volatile(
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
      "    LDR     R0, =0xffb7df64 \n" 
      "    LDR     R1, =0x1900 \n" 
      "    LDR     R3, =0xD7E4 \n" 
"loc_FF81013C:\n"
      "    CMP     R1, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_FF81013C \n" 
      "    LDR     R1, =0x148428 \n" 
      "    MOV     R2, #0 \n" 
"loc_FF810154:\n"
      "    CMP     R3, R1 \n" 
      "    STRCC   R2, [R3], #4 \n" 
      "    BCC     loc_FF810154 \n" 
    );

    *(int*)0x1934=(int)taskHook;

    // Search on 0x12345678 finds function called by sub_FF8439F4, values found there OK ?
    *(int*)(0x22CC)= (*(int*)0xC0220080)&1 ? 0x400000 : 0x200000; 

    // jump to init-sequence that follows the data-copy-routine 
    asm volatile ("B      sub_FF8101A0_my\n");
}

void __attribute__((naked,noinline)) sub_FF8101A0_my() {
        asm volatile (
"                LDR     R0, =0xFF810218\n" // exception handler code
"                MOV     R1, #0\n"
"                LDR     R3, =0xFF810250\n"
"loc_FF8101AC:\n"
"                CMP     R0, R3\n"          // load exception vector
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FF8101AC\n"
"                LDR     R0, =0xFF810250\n"
"                MOV     R1, #0x4B0\n"
"                LDR     R3, =0xFF810464\n"
"loc_FF8101C8:\n"
"                CMP     R0, R3\n"          // copy IRQ handler to ITCM starting at 0x4b0, 532 bytes up to 0x6C4
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FF8101C8\n"
"                MOV     R0, #0xD2\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = IRQ, ints disabled
"                MOV     SP, #0x1000\n"     // irq mode SP
"                MOV     R0, #0xD3\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = Super, ints disabled
"                MOV     SP, #0x1000\n"     // super mode SP
"                LDR     R0, =0x6C4\n"
"                LDR     R2, =0xEEEEEEEE\n"
"                MOV     R3, #0x1000\n"
"loc_FF8101FC:\n"
"                CMP     R0, R3\n"          // clear ITCM 0x6C4-end with EEEEEEEE
"                STRCC   R2, [R0],#4\n"
"                BCC     loc_FF8101FC\n"
"                BL      sub_FF810FC4_my\n" //->
        );
}


void __attribute__((naked,noinline)) sub_FF810FC4_my(  ) {
asm volatile (
      "    STR     LR, [SP, #-4]! \n" 
      "    SUB     SP, SP, #0x74 \n" 
      "    MOV     R0, SP \n" 
      "    MOV     R1, #0x74 \n" 
      "    BL      sub_FFAE9474 \n" 
      "    MOV     R0, #0x53000 \n" 
      "    STR     R0, [SP, #4] \n" 
#ifdef CHDK_NOT_IN_CANON_HEAP
      "    LDR     R0, =0x148428 \n" 
#else
      "LDR     R0, =new_sa\n"
      "LDR     R0, [R0]\n"
#endif
      "    LDR     R2, =0x2F9C00 \n" 
      "    LDR     R1, =0x2F24A8 \n" 
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
      "    LDR     R1, =sub_FF814D38_my \n" 
      "LDR     PC, =0xFF811018\n" // jump back to original FW
/*      "    STR     R0, [SP, #0x20] \n" 
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
      "    BL      sub_FF812D68 \n" 
      "    ADD     SP, SP, #0x74 \n" 
      "    LDR     PC, [SP], #4 \n" */
      );
}

void __attribute__((naked,noinline)) sub_FF814D38_my() {
    asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                BL      sub_FF810954\n"
"                BL      sub_FF8190B4\n" // dmSetup
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E4C\n"    // "dmSetup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                BL      sub_FF814974\n"
"                CMP     R0, #0\n"
"                LDRLT   R0,=0xFF814E54\n" // "termDriverInit"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                LDR     R0, =0xFF814E64\n"      // "/_term"
"                BL      sub_FF814A5C\n" // termDeviceCreate
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E6C\n" // "termDeviceCreate"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                LDR     R0, =0xFF814E64\n"      // "/_term"
"                BL      sub_FF813578\n" // stdioSetup
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E80\n" // "stdioSetup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                BL      sub_FF818BCC\n"
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E8C\n" // "stdlibSetup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                BL      sub_FF8114A8\n"
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E98\n" // "armlib_setup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                LDMFD   SP!, {R4,LR}\n"
"                B       taskcreate_Startup_my\n" //sub_FF81C260
    );
}

void __attribute__((naked,noinline)) taskcreate_Startup_my() { //sub_FF81C260
    asm volatile (
      "    STMFD   SP!, {R3,LR} \n" 
//      "    BL      sub_FF821BA4 \n"   //- nullsub
      "    BL      sub_FF828D20 \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF81C298 \n" 
      "    BL      sub_FF821BA0 \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF81C298 \n" 
      "    BL      sub_FF821248 \n" 
      "    LDR     R1, =0xC0220000 \n" 
      "    MOV     R0, #0x44 \n" 
      "    STR     R0, [R1, #0x1C] \n" 
      "    BL      sub_FF821438 \n" 
"loc_FF81C294:\n"
      "    B       loc_FF81C294 \n" 
"loc_FF81C298:\n"
//      "    BL      sub_FF821BAC \n"   //- for correct power on
//      "    BL      sub_FF821BA8 \n"   //- nullsub
      "    BL      sub_FF826FD8 \n" 
      "    LDR     R1, =0x34E000 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_FF827420 \n" 
      "    BL      sub_FF8271CC \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
      "    LDR     R3, =task_Startup_my\n"  //sub_FF81C1FC
      "    MOV     R2, #0 \n" 
      "    MOV     R1, #0x19 \n" 
      "    LDR     R0, =0xFF81C2E0 \n" 
      "    BL      sub_FF81AFAC \n" 
      "    MOV     R0, #0 \n" 
      "    LDMFD   SP!, {R12,PC} \n" 
    );
}

void CreateTask_blinker();

void __attribute__((naked,noinline)) task_Startup_my(  ) {  //sub_FF81C1FC
asm volatile (
      "    STMFD   SP!, {R4,LR} \n"
      "    BL      sub_FF815394 \n"
      "    BL      sub_FF822C88 \n"
      "    BL      sub_FF820F04 \n"
//      "    BL      sub_FF828D60 \n"   //- nullsub
      "    BL      sub_FF828F44 \n"
//      "    BL      sub_FF828DF4 \n"   //- init sd, start diskboot
      "    BL      CreateTask_spytask\n"//+
      "    BL      sub_FF8290EC \n"
      "    BL      sub_FF81FB90 \n"
      "    BL      sub_FF828F74 \n"
      "    BL      sub_FF8265D8 \n"
      "    BL      sub_FF8290F0 \n"
      "    BL      taskcreatePhySw_my\n"// sub_FF821A94
      "    LDR PC, =0xff81c230\n"       //+ jump back to ROM
/*      "    BL      sub_FF824AC8 \n"
      "    BL      sub_FF829108 \n"
      "    BL      sub_FF81EFB0 \n"
      "    BL      sub_FF820808 \n"
      "    BL      sub_FF828AFC \n"
      "    BL      sub_FF820EB4 \n"
      "    BL      sub_FF820714 \n"
      "    BL      sub_FF81FBC4 \n"
      "    BL      sub_FF829BCC \n"
      "    BL      sub_FF8206EC \n"
      "    LDMFD   SP!, {R4,LR} \n"
      "    B       sub_FF8154B4 \n"*/
    );
}

void __attribute__((naked,noinline)) taskcreatePhySw_my() {  //sub_FF821A94
asm volatile (
      "    STMFD   SP!, {R3-R5,LR} \n"
      "    LDR     R4, =0x1C28 \n"
      "    LDR     R0, [R4, #0x10] \n"
      "    CMP     R0, #0 \n"
      "    BNE     loc_FF821AC8 \n"
      "    MOV     R3, #0 \n"
      "    STR     R3, [SP] \n"
      "    LDR     R3, =mykbd_task\n"     // 0xFF821A60
//      "    MOV     R2, #0x800 \n"       //- original stack size
      "    MOV     R2, #0x2000 \n"        //+ new stack size
      "    MOV     R1, #0x17 \n"
      "    LDR     R0, =0xFF821C98 \n"    // "PhySw"
      "    BL      sub_FF827220 \n"
      "    STR     R0, [R4, #0x10] \n"
"loc_FF821AC8:\n"
      "    BL      sub_FF84431C \n"
      "    BL      sub_FF86DA80 \n"
      "    BL      sub_FF847864 \n"
      "    CMP     R0, #0 \n"
      "    LDREQ   R1, =0xEC84 \n"
      "    LDMEQFD SP!, {R3-R5,LR} \n"
      "    BEQ     sub_FF86DA08 \n"
      "    LDMFD   SP!, {R3-R5,PC} \n"
    );
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

void __attribute__((naked,noinline)) init_file_modules_task() {  //sub_FF87AAC0
asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n"
      "    BL      sub_FF86FE90 \n"
      "    LDR     R5, =0x5006 \n"
      "    MOVS    R4, R0 \n"
      "    MOVNE   R1, #0 \n"
      "    MOVNE   R0, R5 \n"
      "    BLNE    sub_FF874D2C \n"
      "    BL      sub_FF86FEBC_my \n"          // ->
      "    BL      core_spytask_can_start\n"    // + safe to start spytask
      "    CMP     R4, #0 \n"                   // rom:ff87aae0
      "    MOVEQ   R0, R5 \n"
      "    LDMEQFD SP!, {R4-R6,LR} \n"
      "    MOVEQ   R1, #0 \n"
      "    BEQ     sub_FF874D2C \n"
      "    LDMFD   SP!, {R4-R6,PC} \n"
    );
}

void __attribute__((naked,noinline)) sub_FF86FEBC_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4,LR} \n"
      "    MOV     R0, #3 \n"
      "    BL      sub_FF853244_my \n"  //->
      "    LDR PC, =0xff86fecc\n"
/*      "    BL      sub_FF8FF418 \n" //nullsub
      "    LDR     R4, =0x2D04 \n"  // rom:ff86fecc
      "    LDR     R0, [R4, #4] \n"
      "    CMP     R0, #0 \n"
      "    BNE     loc_FF86FEF4 \n"
      "    BL      sub_FF852608 \n"
      "    BL      sub_FF8F2828 \n"
      "    BL      sub_FF852608 \n"
      "    BL      sub_FF84E65C \n"
      "    BL      sub_FF852508 \n"
      "    BL      sub_FF8F28F4 \n"
"loc_FF86FEF4:\n"
      "    MOV     R0, #1 \n"
      "    STR     R0, [R4] \n"
      "    LDMFD   SP!, {R4,PC} \n"*/
      );
}


void __attribute__((naked,noinline)) sub_FF853244_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4-R8,LR} \n"
      "    MOV     R6, R0 \n"
      "    BL      sub_FF8531AC \n"
      "    LDR     R1, =0x113DC \n"
      "    MOV     R5, R0 \n"
      "    ADD     R4, R1, R0, LSL #7 \n"
      "    LDR     R0, [R4, #0x70] \n"
      "    CMP     R0, #4 \n"
      "    LDREQ   R1, =0x6D8 \n"
      "    LDREQ   R0, =0xFF852CD0 \n"
      "    BLEQ    sub_FF81B284 \n"
      "    MOV     R1, R6 \n"
      "    MOV     R0, R5 \n"
      "    BL      sub_FF852C18 \n"
      "    LDR     R0, [R4, #0x38] \n"
      "    BL      sub_FF853770 \n"
      "    CMP     R0, #0 \n"
      "    STREQ   R0, [R4, #0x70] \n"
      "    MOV     R0, R5 \n"
      "    BL      sub_FF852CF0 \n"
      "    MOV     R0, R5 \n"
      "    BL      sub_FF852FE4_my \n"  //->
      "    LDR PC, =0xff85329c\n"       //+ jump back to ROM
/*      "    MOV     R7, R0 \n"         //rom:ff85329c
      "    MOV     R0, R5 \n"
      "    BL      sub_FF853048 \n"
      "    LDR     R1, [R4, #0x3C] \n"
      "    AND     R2, R7, R0 \n"
      "    CMP     R1, #0 \n"
      "    MOV     R0, #0 \n"
      "    MOVEQ   R0, #0x80000001 \n"
      "    BEQ     loc_FF8532EC \n"
      "    LDR     R3, [R4, #0x2C] \n"
      "    CMP     R3, #2 \n"
      "    MOVEQ   R0, #4 \n"
      "    CMP     R1, #5 \n"
      "    ORRNE   R0, R0, #1 \n"
      "    BICEQ   R0, R0, #1 \n"
      "    CMP     R2, #0 \n"
      "    BICEQ   R0, R0, #2 \n"
      "    ORREQ   R0, R0, #0x80000000 \n"
      "    BICNE   R0, R0, #0x80000000 \n"
      "    ORRNE   R0, R0, #2 \n"
"loc_FF8532EC:\n"
      "    CMP     R6, #7 \n"
      "    STR     R0, [R4, #0x40] \n"
      "    LDMNEFD SP!, {R4-R8,PC} \n"
      "    MOV     R0, R6 \n"
      "    BL      sub_FF8531FC \n"
      "    CMP     R0, #0 \n"
      "    LDMEQFD SP!, {R4-R8,LR} \n"
      "    LDREQ   R0, =0xFF8534E8 \n"
      "    BEQ     sub_FF8115A8 \n"
      "    LDMFD   SP!, {R4-R8,PC} \n"*/
      );
}

void __attribute__((naked,noinline)) sub_FF852FE4_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n"
      "    MOV     R5, R0 \n"
      "    LDR     R0, =0x113DC \n"
      "    ADD     R4, R0, R5, LSL #7 \n"
      "    LDR     R0, [R4, #0x70] \n"
      "    TST     R0, #2 \n"
      "    MOVNE   R0, #1 \n"
      "    LDMNEFD SP!, {R4-R6,PC} \n"
      "    LDR     R0, [R4, #0x38] \n"
      "    MOV     R1, R5 \n"
      "    BL      sub_FF852D74_my \n"      //->
      "    LDR PC, =0xff853010\n"           //+ jump back to ROM
/*      "    CMP     R0, #0 \n"             //rom:ff853010
      "    LDMEQFD SP!, {R4-R6,PC} \n"
      "    LDR     R0, [R4, #0x38] \n"
      "    MOV     R1, R5 \n"
      "    BL      sub_FF852EE0 \n"
      "    CMP     R0, #0 \n"
      "    LDMEQFD SP!, {R4-R6,PC} \n"
      "    MOV     R0, R5 \n"
      "    BL      sub_FF852800 \n"
      "    CMP     R0, #0 \n"
      "    LDRNE   R1, [R4, #0x70] \n"
      "    ORRNE   R1, R1, #2 \n"
      "    STRNE   R1, [R4, #0x70] \n"
      "    LDMFD   SP!, {R4-R6,PC} \n"*/
    );
}


void __attribute__((naked,noinline)) sub_FF852D74_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4-R8,LR} \n"
      "    MOV     R8, R0 \n"
      "    LDR     R0, =0x113DC \n"
      "    MOV     R7, #0 \n"
      "    ADD     R5, R0, R1, LSL #7 \n"
      "    LDR     R0, [R5, #0x3C] \n"
      "    MOV     R6, #0 \n"
      "    CMP     R0, #7 \n"
      "    ADDLS   PC, PC, R0, LSL #2 \n"
      "    B       loc_FF852EC4 \n"
      "    B       loc_FF852DD4 \n"
      "    B       loc_FF852DBC \n"
      "    B       loc_FF852DBC \n"
      "    B       loc_FF852DBC \n"
      "    B       loc_FF852DBC \n"
      "    B       loc_FF852EBC \n"
      "    B       loc_FF852DBC \n"
      "    B       loc_FF852DBC \n"
"loc_FF852DBC:\n"
      "    MOV     R2, #0 \n"
      "    MOV     R1, #0x200 \n"
      "    MOV     R0, #2 \n"
      "    BL      sub_FF869F88 \n"
      "    MOVS    R4, R0 \n"
      "    BNE     loc_FF852DDC \n"
"loc_FF852DD4:\n"
      "    MOV     R0, #0 \n"
      "    LDMFD   SP!, {R4-R8,PC} \n"
"loc_FF852DDC:\n"
      "    LDR     R12, [R5, #0x4C] \n"
      "    MOV     R3, R4 \n"
      "    MOV     R2, #1 \n"
      "    MOV     R1, #0 \n"
      "    MOV     R0, R8 \n"
      "    BLX     R12 \n"
      "    CMP     R0, #1 \n"
      "    BNE     loc_FF852E08 \n"
      "    MOV     R0, #2 \n"
      "    BL      sub_FF86A0D4 \n"
      "    B       loc_FF852DD4 \n"
"loc_FF852E08:\n"
      "    LDR     R1, [R5, #0x68] \n"
      "    MOV     R0, R8 \n"
      "    BLX     R1 \n"
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
        "BNE     dg_sd_fat32\n"                // No, it isn't. Loop again.
        "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
        "CMPNE   R2, #0x80\n"
        "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                               // This partition is valid, it's the first one, bingo!
        "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.

   "dg_sd_fat32_end:\n"
        // End of DataGhost's FAT32 autodetection code
      "    LDRB    R1, [R4, #0x1C9] \n"
      "    LDRB    R3, [R4, #0x1C8] \n"
      "    LDRB    R12, [R4, #0x1CC] \n"
      "    MOV     R1, R1, LSL #0x18 \n"
      "    ORR     R1, R1, R3, LSL #0x10 \n"
      "    LDRB    R3, [R4, #0x1C7] \n"
      "    LDRB    R2, [R4, #0x1BE] \n"
//      "    LDRB    LR, [R4, #0x1FF] \n"       //-
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
//      "    LDRB    R12, [R4, #0x1FE] \n"      //-
      "    LDRB    R12, [LR,#0x1FE]\n"          //+
      "    LDRB    LR, [LR,#0x1FF]\n"           //+
      "    MOV     R4, #0 \n"
      "    BNE     loc_FF852E94 \n"
      "    CMP     R0, R1 \n"
      "    BCC     loc_FF852E94 \n"
      "    ADD     R2, R1, R3 \n"
      "    CMP     R2, R0 \n"
      "    CMPLS   R12, #0x55 \n"
      "    CMPEQ   LR, #0xAA \n"
      "    MOVEQ   R7, R1 \n"
      "    MOVEQ   R6, R3 \n"
      "    MOVEQ   R4, #1 \n"
"loc_FF852E94:\n"
      "    MOV     R0, #2 \n"
      "    BL      sub_FF86A0D4 \n"
      "    CMP     R4, #0 \n"
      "    BNE     loc_FF852ED0 \n"
      "    LDR     R1, [R5, #0x68] \n"
      "    MOV     R7, #0 \n"
      "    MOV     R0, R8 \n"
      "    BLX     R1 \n"
      "    MOV     R6, R0 \n"
      "    B       loc_FF852ED0 \n"
"loc_FF852EBC:\n"
      "    MOV     R6, #0x40 \n"
      "    B       loc_FF852ED0 \n"
"loc_FF852EC4:\n"
      "    LDR     R1, =0x5C9 \n"
      "    LDR     R0, =0xFF852CD0 \n"
      "    BL      sub_FF81B284 \n"
"loc_FF852ED0:\n"
      "    STR     R7, [R5, #0x44]! \n"
      "    MOV     R0, #1 \n"
      "    STR     R6, [R5, #4] \n"
      "    LDMFD   SP!, {R4-R8,PC} \n"
      );
}


void __attribute__((naked,noinline)) task_JogDial_my(  ) {
asm volatile (
      "    STMFD   SP!, {R3-R11,LR} \n" 
      "    BL      sub_FF8443D0 \n" 
      "    LDR     R11, =0x80000B01 \n" 
      "    LDR     R8, =0xFFAEEB9C \n" 
      "    LDR     R7, =0xC0240000 \n" 
      "    LDR     R6, =0x22DC \n" 
      "    MOV     R9, #1 \n" 
      "    MOV     R10, #0 \n" 
"loc_FF844240:\n"
      "    LDR     R3, =0x1BB \n" 
      "    LDR     R0, [R6, #0xC] \n" 
      "    LDR     R2, =0xFF844478 \n" 
      "    MOV     R1, #0 \n" 
      "    BL      sub_FF827308 \n" 
      "    MOV     R0, #0x28 \n" 
      "    BL      _SleepTask \n" 
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n"
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------ 
      "    LDR     R0, [R7, #0x104] \n" 
      "    MOV     R0, R0, ASR #0x10 \n" 
      "    STRH    R0, [R6] \n" 
      "    LDRSH   R2, [R6, #2] \n" 
      "    SUB     R1, R0, R2 \n" 
      "    CMP     R1, #0 \n" 
      "    BEQ     loc_FF844304 \n" 
      "    MOV     R5, R1 \n" 
      "    RSBLT   R5, R5, #0 \n" 
      "    MOVLE   R4, #0 \n" 
      "    MOVGT   R4, #1 \n" 
      "    CMP     R5, #0xFF \n" 
      "    BLS     loc_FF8442B8 \n" 
      "    CMP     R1, #0 \n" 
      "    RSBLE   R1, R2, #0xFF \n" 
      "    ADDLE   R1, R1, #0x7F00 \n" 
      "    ADDLE   R0, R1, R0 \n" 
      "    RSBGT   R0, R0, #0xFF \n" 
      "    ADDGT   R0, R0, #0x7F00 \n" 
      "    ADDGT   R0, R0, R2 \n" 
      "    ADD     R5, R0, #0x8000 \n" 
      "    ADD     R5, R5, #1 \n" 
      "    EOR     R4, R4, #1 \n" 
"loc_FF8442B8:\n"
      "    LDR     R0, [R6, #0x14] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FF8442FC \n" 
      "    LDR     R0, [R6, #0x1C] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FF8442E4 \n" 
      "    LDR     R1, [R8, R4, LSL #2] \n" 
      "    CMP     R1, R0 \n" 
      "    BEQ     loc_FF8442EC \n" 
      "    LDR     R0, =0xB01 \n" 
      "    BL      sub_FF876C58 \n" 
"loc_FF8442E4:\n"
      "    MOV     R0, R11 \n" 
      "    BL      sub_FF876C58 \n" 
"loc_FF8442EC:\n"
      "    LDR     R0, [R8, R4, LSL #2] \n" 
      "    MOV     R1, R5 \n" 
      "    STR     R0, [R6, #0x1C] \n" 
      "    BL      sub_FF876B88 \n" 
"loc_FF8442FC:\n"
      "    LDRH    R0, [R6] \n" 
      "    STRH    R0, [R6, #2] \n" 
"loc_FF844304:\n"
      "    STR     R10, [R7, #0x100] \n" 
      "    STR     R9, [R7, #0x108] \n" 
      "    LDR     R0, [R6, #0x10] \n" 
      "    CMP     R0, #0 \n" 
      "    BLNE    _SleepTask \n" 
      "    B       loc_FF844240 \n" 
    );
}

#if 0
const unsigned ledlist[]={
	0xC0220130, // green?
	0xC0220134, // red?
};
// shamelessly stolen from s5 for debugging
extern void msleep(int x);
void __attribute__((noinline)) task_blinker() {
        int ledstate;

        int counter = 0;

        int *led = (void*) ledlist[0];
		int i_led = 0;

        int *anypointer;       // multi-purpose pointer to poke around in memory
        int v1, v2, v3, v4;    // multi-purpose vars

        ledstate = 0;   // init: led off
        *led = 0x46;      // led on

        while (1) {

                if (ledstate == 1) {    // toggle LED
                        ledstate = 0;
                        *led = 0x44;      // LED off
						led=(void *)ledlist[(++i_led)%2];
                        //core_test(1);
                } else {
                        ledstate = 1;
                        *led = 0x46;      // LED on
                        //core_test(0);
                }

                if (counter == 2) {
                        //dump_chdk();
                        //gui_init();
                        //_ExecuteEventProcedure("UIFS_WriteFirmInfoToFile");
                        //_UIFS_WriteFirmInfoToFile(0);
                }

                if (counter == 10) {
                        //draw_txt_string(2, 2, "test");
                }

                msleep(500);
                counter++;
        }
};

void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};
#endif

