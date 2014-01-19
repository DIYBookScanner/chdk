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
extern void task_PhySw();

void taskHook(context_t **context) {
    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

    if(tcb->entry == (void*)task_PhySw)            tcb->entry = (void*)mykbd_task;
    if(tcb->entry == (void*)task_CaptSeq)           tcb->entry = (void*)capt_seq_task;
    if(tcb->entry == (void*)task_InitFileModules)   tcb->entry = (void*)init_file_modules_task;
    if(tcb->entry == (void*)task_MovieRecord)       tcb->entry = (void*)movie_record_task;
    if(tcb->entry == (void*)task_ExpDrv)            tcb->entry = (void*)exp_drv_task;
}


//** boot  @ 0xFF00000C 

void __attribute__((naked,noinline)) boot(  ) { 
asm volatile (
      "LDR     R1, =0xC0410000 \n"
      "MOV     R0, #0 \n"
      "STR     R0, [R1] \n"
      "MOV     R1, #0x78 \n"
      "MCR     p15, 0, R1, c1, c0 \n"
      "MOV     R1, #0 \n"
      "MCR     p15, 0, R1, c7, c10, 4 \n"
      "MCR     p15, 0, R1, c7, c5 \n"
      "MCR     p15, 0, R1, c7, c6 \n"
      "MOV     R0, #0x3D \n"
      "MCR     p15, 0, R0, c6, c0 \n"
      "MOV     R0, #0xC000002F \n"
      "MCR     p15, 0, R0, c6, c1 \n"
      "MOV     R0, #0x37 \n"
      "MCR     p15, 0, R0, c6, c2 \n"
      "MOV     R0, #0x40000037 \n"
      "MCR     p15, 0, R0, c6, c3 \n"
      "MOV     R0, #0x80000017 \n"
      "MCR     p15, 0, R0, c6, c4 \n"
      "LDR     R0, =0xFF00002F \n"
      "MCR     p15, 0, R0, c6, c5 \n"
      "LDR     R0, =0xD000002B \n"
      "MCR     p15, 0, R0, c6, c7 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c2, c0 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c2, c0, 1 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c3, c0 \n"
      "LDR     R0, =0x33333330 \n"
      "MCR     p15, 0, R0, c5, c0, 2 \n"
      "LDR     R0, =0x33333330 \n"
      "MCR     p15, 0, R0, c5, c0, 3 \n"
      "MRC     p15, 0, R0, c1, c0 \n"
      "ORR     R0, R0, #0x1000 \n"
      "ORR     R0, R0, #4 \n"
      "ORR     R0, R0, #1 \n"
      "MCR     p15, 0, R0, c1, c0 \n"
      "MOV     R1, #0x80000006 \n"
      "MCR     p15, 0, R1, c9, c1 \n"
      "MOV     R1, #6 \n"
      "MCR     p15, 0, R1, c9, c1, 1 \n"
      "MRC     p15, 0, R1, c1, c0 \n"
      "ORR     R1, R1, #0x50000 \n"
      "MCR     p15, 0, R1, c1, c0 \n"
      "LDR     R2, =0xC0200000 \n"
      "MOV     R1, #1 \n"
      "STR     R1, [R2, #0x10C] \n"
      "MOV     R1, #0xFF \n"
      "STR     R1, [R2, #0xC] \n"
      "STR     R1, [R2, #0x1C] \n"
      "STR     R1, [R2, #0x2C] \n"
      "STR     R1, [R2, #0x3C] \n"
      "STR     R1, [R2, #0x4C] \n"
      "STR     R1, [R2, #0x5C] \n"
      "STR     R1, [R2, #0x6C] \n"
      "STR     R1, [R2, #0x7C] \n"
      "STR     R1, [R2, #0x8C] \n"
      "STR     R1, [R2, #0x9C] \n"
      "STR     R1, [R2, #0xAC] \n"
      "STR     R1, [R2, #0xBC] \n"
      "STR     R1, [R2, #0xCC] \n"
      "STR     R1, [R2, #0xDC] \n"
      "STR     R1, [R2, #0xEC] \n"
      "STR     R1, [R2, #0xFC] \n"
      "LDR     R1, =0xC0400008 \n"
      "LDR     R2, =0x430005 \n"
      "STR     R2, [R1] \n"
      "MOV     R1, #1 \n"
      "LDR     R2, =0xC0243100 \n"
      "STR     R2, [R1] \n"
      "LDR     R2, =0xC0242010 \n"
      "LDR     R1, [R2] \n"
      "ORR     R1, R1, #1 \n"
      "STR     R1, [R2] \n"
      "LDR     R0, =0xFF63CD08 \n"
      "LDR     R1, =0x685000 \n"
      "LDR     R3, =0x6946DC \n"
"loc_FF000144:\n"
      "CMP     R1, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF000144 \n"
      "LDR     R0, =0xFF62A9FC \n"
      "LDR     R1, =0x1900 \n"
      "LDR     R3, =0x13C0C \n"
"loc_FF000160:\n"
      "CMP     R1, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF000160 \n"
      "LDR     R1, =0x180998 \n"  //MEMISOSTART
      "MOV     R2, #0 \n"
"loc_FF000178:\n"
      "CMP     R3, R1 \n"
      "STRCC   R2, [R3], #4 \n"
      "BCC     loc_FF000178 \n"
//      "B       sub_FF00038C \n"//original
      "B       sub_FF00038C_my \n"//patched
	);
}

//** sub_FF00038C_my  @ 0xFF00038C 

void __attribute__((naked,noinline)) sub_FF00038C_my() {

   //http://chdk.setepontos.com/index.php/topic,4194.0.html
    *(int*)0x1938=(int)taskHook;            
    *(int*)0x193C=(int)taskHook;           

    // Replacement of sub_FF01E594
    // Power Button detection (short press = playback mode, long press = record mode)
    // C02200F8  ?? power up button -  Check this
    // 0x2580    ixus125 100d Found @ 0xff049bf0
//    if ((*(int*) 0xC02200F8) & 1)                 // look at power-on switch

    if ((*(int*) 0xC022C30C) & 1)     //???
            *(int*)(0x2580) = 0x200000;         // start in play mode
    else
            *(int*)(0x2580) = 0x100000;         // start in rec mode

asm volatile (
      "LDR     R0, =0xFF000404 \n"
      "MOV     R1, #0 \n"
      "LDR     R3, =0xFF00043C \n"
"loc_FF000398:\n"
      "CMP     R0, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF000398 \n"
      "LDR     R0, =0xFF00043C \n"
      "MOV     R1, #0x4B0 \n"
      "LDR     R3, =0xFF000650 \n"
"loc_FF0003B4:\n"
      "CMP     R0, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FF0003B4 \n"
      "MOV     R0, #0xD2 \n"
      "MSR     CPSR_cxsf, R0 \n"
      "MOV     SP, #0x1000 \n"
      "MOV     R0, #0xD3 \n"
      "MSR     CPSR_cxsf, R0 \n"
      "MOV     SP, #0x1000 \n"
      "LDR     R0, =0x6C4 \n"
      "LDR     R2, =0xEEEEEEEE \n"
      "MOV     R3, #0x1000 \n"
"loc_FF0003E8:\n"
      "CMP     R0, R3 \n"
      "STRCC   R2, [R0], #4 \n"
      "BCC     loc_FF0003E8 \n"
//      "BL      sub_FF0011E4 \n"//original
      "BL      sub_FF0011E4_my \n"//patched
	);
}

//** sub_FF0011E4_my  @ 0xFF0011E4

void __attribute__((naked,noinline)) sub_FF0011E4_my() {
asm volatile (
      "STR     LR, [SP, #-4]! \n"
      "SUB     SP, SP, #0x74 \n"
      "MOV     R1, #0x74 \n"
      "MOV     R0, SP \n"
      "BL      sub_00690448 \n"// RAM
      "MOV     R0, #0x67000 \n"
      "STR     R0, [SP, #4] \n"
//PATCH BEGIN
#if defined(CHDK_NOT_IN_CANON_HEAP)
      "LDR     R0, =0x180998 \n"// MEMISOSTART: Use original heap offset since CHDK is loaded in high memory 
#else
        "LDR     R0, =new_sa\n"	 //otherwise use patched value
        "LDR     R0, [R0]\n"
#endif
//PATCH END
      "LDR     R2, =0x55D440 \n"
      "STR     R0, [SP, #8] \n"
      "SUB     R0, R2, R0 \n"
      "STR     R0, [SP, #0xC] \n"
      "MOV     R0, #0x22 \n"
      "STR     R0, [SP, #0x18] \n"
      "MOV     R0, #0x7C \n"
      "STR     R0, [SP, #0x1C] \n"
      "LDR     R1, =0x565C00 \n"
      "LDR     R0, =0x1CD \n"
      "STR     R1, [SP] \n"
      "STR     R0, [SP, #0x20] \n"
      "MOV     R0, #0x96 \n"
      "STR     R2, [SP, #0x10] \n"
      "STR     R1, [SP, #0x14] \n"
      "STR     R0, [SP, #0x24] \n"
      "STR     R0, [SP, #0x28] \n"
      "MOV     R0, #0x64 \n"
      "STR     R0, [SP, #0x2C] \n"
      "MOV     R0, #0 \n"
      "STR     R0, [SP, #0x30] \n"
      "STR     R0, [SP, #0x34] \n"
      "MOV     R0, #0x10 \n"
      "STR     R0, [SP, #0x5C] \n"
      "MOV     R0, #0x800 \n"
      "STR     R0, [SP, #0x60] \n"
      "MOV     R0, #0xA0 \n"
      "STR     R0, [SP, #0x64] \n"
      "MOV     R0, #0x280 \n"
      "STR     R0, [SP, #0x68] \n"
//      "LDR     R1, =0xFF004284 \n"//original
      "LDR     R1, =sub_FF004284_my \n"//patched
      "MOV     R2, #0 \n"
      "MOV     R0, SP \n"
      "BL      sub_00686778 \n"
      "ADD     SP, SP, #0x74 \n"
      "LDR     PC, [SP], #4 \n"
	);
}

//** sub_FF004284_my  @ 0xFF004284 

void __attribute__((naked,noinline)) sub_FF004284_my() { 
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FF000B5C \n"
      "BL      sub_FF0053A8 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF004398 \n"
      "BLLT    _err_init_task \n"
      "BL      sub_FF003EBC \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF0043A0 \n"
      "BLLT    _err_init_task \n"
      "LDR     R0, =0xFF0043B0 \n"
      "BL      sub_FF003FA4 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF0043B8 \n"
      "BLLT    _err_init_task \n"
      "LDR     R0, =0xFF0043B0 \n"
      "BL      sub_FF0029C4 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF0043CC \n"
      "BLLT    _err_init_task \n"
      "BL      sub_FF004D44 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF0043D8 \n"
      "BLLT    _err_init_task \n"
      "BL      sub_FF0016C4 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFF0043E4 \n"
      "BLLT    _err_init_task \n"
      "LDMFD   SP!, {R4,LR} \n"
//      "B       sub_FF00B198 \n"//original
      "B       sub_FF00B198_my \n"//patched
	);
}

//** sub_FF00B198_my  @ 0xFF00B198

void __attribute__((naked,noinline)) sub_FF00B198_my() {
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FF01E58C \n"
//      "BL      loc_FF00B1AC \n"// original taskcreate_Startup
      "BL      taskcreate_Startup_my \n"//patched taskcreate_Startup
      "MOV     R0, #0 \n"
      "LDMFD   SP!, {R4,PC} \n"
    );
}

//** taskcreate_Startup_my  @ 0xFF00B1AC

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
      "STMFD   SP!, {R3-R7,LR} \n"
      "BL      sub_FF025F44 \n"
      "MOVS    R6, R0 \n"
      "BNE     loc_FF00B204 \n"
      "BL      sub_FF01FFE0 \n"
      "CMP     R0, #0 \n"
      "BEQ     loc_FF00B204 \n"
      "MOV     R0, #0x37 \n"
      "BL      sub_FF024518 \n"
      "RSBS    R5, R0, #1 \n"
      "MOVCC   R5, #0 \n"
      "MOV     R0, #0x36 \n"
      "BL      sub_FF024518 \n"
      "RSBS    R4, R0, #1 \n"
      "MOVCC   R4, #0 \n"
      "ORRS    R0, R4, R5 \n"
      "BNE     loc_FF00B224 \n"
      "BL      sub_FF01DA04 \n"
      "LDR     R1, =0x83DC00 \n"
      "MOV     R0, #0x54 \n"
      "BL      sub_FF024508 \n"
"loc_FF00B200:\n"
      "B       loc_FF00B200 \n"
"loc_FF00B204:\n"
      "MOV     R0, #0x36 \n"
      "BL      sub_FF024518 \n"
      "RSBS    R4, R0, #1 \n"
      "MOVCC   R4, #0 \n"
      "MOV     R0, #0x37 \n"
      "BL      sub_FF024518 \n"
      "RSBS    R5, R0, #1 \n"
      "MOVCC   R5, #0 \n"
"loc_FF00B224:\n"
      "MOV     R3, #0 \n"
      "MOV     R2, R6 \n"
      "MOV     R1, R5 \n"
      "MOV     R0, R4 \n"
//      "BL      sub_FF01E594 \n" // StartUp mode detection. We must remove this for power-on mode handling to work
      "BL      sub_FF01E590 \n"
      "BL      sub_0068C118 \n" //RAM
      "LDR     R1, =0x5CE000 \n"
      "MOV     R0, #0 \n"
      "BL      sub_FF024308 \n"
      "BL      sub_0068C330 \n" //RAM
      "MOV     R3, #0 \n"
      "STR     R3, [SP] \n"
//      "LDR     R3, =0xFF00B130 \n"//original
      "LDR     R3, =task_Startup_my \n"//patched
      "MOV     R2, #0 \n"
      "MOV     R1, #0x19 \n"
      "LDR     R0, =0xFF00B280 \n"
      "BL      _CreateTask \n"
      "MOV     R0, #0 \n"
      "LDMFD   SP!, {R3-R7,PC} \n"
	);
}

//** task_Startup_my  @ 0xFF00B130

void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FF0048C4 \n"//clocksave
      "BL      sub_FF01F6AC \n"
      "BL      sub_FF01D878 \n"
      "BL      sub_FF025F8C \n"
      "BL      sub_FF026178 \n"
//      "BL      sub_FF026020 \n"//disable Diskboot.bin
      "BL      sub_FF0262E4 \n"
      "BL      sub_FF0264B0 \n"
      "BL      sub_FF0262D8 \n"
      "BL      sub_FF0261A8 \n"
      "BL      sub_FF02423C \n"
      "BL      sub_FF0264B8 \n"
      "BL     CreateTask_spytask \n"		//added to create the Spytask
//      "BL      sub_FF01E438 \n"//original taskcreate_PhySw()
      "BL     taskcreatePhySw_my \n"		// patched taskcreate_PhySw()
      "BL      sub_FF022000 \n"
      "BL      sub_FF0264D0 \n"
      "BL      sub_FF01C4E8 \n"
      "BL      sub_FF01D1E8 \n"
      "BL      sub_FF025D04 \n"
      "BL      sub_FF01D82C \n"
      "BL      sub_FF01D184 \n"
      "BL      sub_FF0262DC \n"
      "BL      sub_FF0270F8 \n" //StartFactoryModeController
      "BL      sub_FF01D148 \n"
      "LDMFD   SP!, {R4,LR} \n"
      "B       sub_FF004A00 \n"
	);
}

//** taskcreatePhySw_my  @ 0xFF01E438

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
      "STMFD   SP!, {R3-R5,LR} \n"
      "LDR     R4, =0x1C20 \n"
      "LDR     R0, [R4, #4] \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FF01E46C \n"
      "MOV     R3, #0 \n"
      "STR     R3, [SP] \n"
//      "LDR     R3, =0xFF01E404 \n" //original
      "LDR     R3, =task_PhySw \n" //patched  task_PhySw
//      "MOV     R2, #0x800 \n"   //original
      "MOV     R2, #0x2000 \n"    // stack size for new task_PhySw so we don't have to do stack switch
      "MOV     R1, #0x17 \n"
      "LDR     R0, =0xFF01E68C \n"
      "BL      sub_0068ADD8 \n" //RAM
      "STR     R0, [R4, #4] \n"
"loc_FF01E46C:\n"
      "BL      sub_FF079654 \n"
      "BL      sub_FF01FF30 \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FF01E488 \n"
      "LDR     R1, =0x37BE8 \n"
      "MOV     R0, #0 \n"
      "BL      sub_FF0795C4 \n"
"loc_FF01E488:\n"
      "LDMFD   SP!, {R3-R5,PC} \n"
	);
}

void CreateTask_spytask() {

        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);                        
};

//** init_file_modules_task  @ 0xFF084030 

void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
      "STMFD   SP!, {R4-R6,LR} \n"
      "BL      sub_FF07BBBC \n"
      "LDR     R5, =0x5006 \n"
      "MOVS    R4, R0 \n"
      "MOVNE   R1, #0 \n"
      "MOVNE   R0, R5 \n"
      "BLNE    _PostLogicalEventToUI \n"
      "BL      sub_FF07BBE8 \n"
      "BL	   core_spytask_can_start \n" //added CHDK: Set "it's-safe-to-start"-Flag for spytask
      "CMP     R4, #0 \n"
      "LDMNEFD SP!, {R4-R6,PC} \n"
      "MOV     R0, R5 \n"
      "LDMFD   SP!, {R4-R6,LR} \n"
      "MOV     R1, #0 \n"
      "B       _PostLogicalEventToUI \n"
	);
}
