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

//** boot  @ 0xFFC0000C 

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
      "MOV     R0, #0x33 \n"
      "MCR     p15, 0, R0, c6, c2 \n"
      "MOV     R0, #0x40000033 \n"
      "MCR     p15, 0, R0, c6, c3 \n"
      "MOV     R0, #0x80000017 \n"
      "MCR     p15, 0, R0, c6, c4 \n"
      "LDR     R0, =0xFFC0002B \n"
      "MCR     p15, 0, R0, c6, c5 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c2, c0 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c2, c0, 1 \n"
      "MOV     R0, #0x34 \n"
      "MCR     p15, 0, R0, c3, c0 \n"
      "LDR     R0, =0x3333330 \n"
      "MCR     p15, 0, R0, c5, c0, 2 \n"
      "LDR     R0, =0x3333330 \n"
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
      "LDR     R0, =0xFFF1636C \n"
      "LDR     R1, =0x1900 \n"
      "LDR     R3, =0xB4B8 \n"
"loc_FFC0013C:\n"
      "CMP     R1, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FFC0013C \n"
      "LDR     R1, =0x12E9FC \n"
      "MOV     R2, #0 \n"
"loc_FFC00154:\n"
      "CMP     R3, R1 \n"
      "STRCC   R2, [R3], #4 \n"
      "BCC     loc_FFC00154 \n"
//      "B       sub_FFC00354 \n"  //original
      "B       sub_FFC00354_my \n" //patched
	);
}

//** sub_FFC00354_my  @ 0xFFC00354 

void __attribute__((naked,noinline)) sub_FFC00354_my(  ) { 
   //*(int*)0x1934=(int)taskHook;
   *(int*)0x1938=(int)taskHook;
   *(int*)(0x221c+4)= (*(int*)0xc0220024)&1 ? 0x200000 : 0x100000; // replacement for correct power-on. ffc477a0
asm volatile (
      "LDR     R0, =0xFFC003CC \n"
      "MOV     R1, #0 \n"
      "LDR     R3, =0xFFC00404 \n"
"loc_FFC00360:\n"
      "CMP     R0, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FFC00360 \n"
      "LDR     R0, =0xFFC00404 \n"
      "MOV     R1, #0x4B0 \n"
      "LDR     R3, =0xFFC00618 \n"
"loc_FFC0037C:\n"
      "CMP     R0, R3 \n"
      "LDRCC   R2, [R0], #4 \n"
      "STRCC   R2, [R1], #4 \n"
      "BCC     loc_FFC0037C \n"
      "MOV     R0, #0xD2 \n"
      "MSR     CPSR_cxsf, R0 \n"
      "MOV     SP, #0x1000 \n"
      "MOV     R0, #0xD3 \n"
      "MSR     CPSR_cxsf, R0 \n"
      "MOV     SP, #0x1000 \n"
      "LDR     R0, =0x6C4 \n"
      "LDR     R2, =0xEEEEEEEE \n"
      "MOV     R3, #0x1000 \n"
"loc_FFC003B0:\n"
      "CMP     R0, R3 \n"
      "STRCC   R2, [R0], #4 \n"
      "BCC     loc_FFC003B0 \n"
//      "BL      sub_FFC01198 \n"  //original
      "BL      sub_FFC01198_my \n" //patched
	);
}

//** sub_FFC01198_my  @ 0xFFC01198 

void __attribute__((naked,noinline)) sub_FFC01198_my(  ) { 
asm volatile (
      "STR     LR, [SP, #-4]! \n"
      "SUB     SP, SP, #0x74 \n"
      "MOV     R0, SP \n"
      "MOV     R1, #0x74 \n"
      "BL      sub_FFEA2FA0 \n"
      "MOV     R0, #0x53000 \n"
      "STR     R0, [SP, #4] \n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
      "LDR     R0, =0x12E9FC \n" // MEMISOSTART: Use original heap offset since CHDK is loaded in high memory
#else
                 "LDR     R0, =new_sa\n"        // + remove the line ^ if using these two
                 "LDR     R0, [R0]\n"           // + this is related to chdk size
#endif
      "LDR     R2, =0x2F9C00 \n"
      "LDR     R1, =0x2F24A8 \n"
      "STR     R0, [SP, #8] \n"
      "SUB     R0, R1, R0 \n"
      "ADD     R3, SP, #0xC \n"
      "STR     R2, [SP] \n"
      "STMIA   R3, {R0-R2} \n"
      "MOV     R0, #0x22 \n"
      "STR     R0, [SP, #0x18] \n"
      "MOV     R0, #0x68 \n"
      "STR     R0, [SP, #0x1C] \n"
      "LDR     R0, =0x19B \n"
//      "LDR     R1, =0xFFC05E58 \n"     //original
      "LDR     R1, =sub_FFC05E58_my \n"  //patched
      "STR     R0, [SP, #0x20] \n"
      "MOV     R0, #0x96 \n"
      "STR     R0, [SP, #0x24] \n"
      "MOV     R0, #0x78 \n"
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
      "MOV     R0, SP \n"
      "MOV     R2, #0 \n"
      "BL      sub_FFC03404 \n"
      "ADD     SP, SP, #0x74 \n"
      "LDR     PC, [SP], #4 \n"
	);
}


//** sub_FFC05E58_my  @ 0xFFC05E58 

void __attribute__((naked,noinline)) sub_FFC05E58_my(  ) { 
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FFC00B20 \n"
      "BL      sub_FFC0A244 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFFC05F6C \n"
      "BLLT    sub_FFC05F4C \n"
      "BL      sub_FFC05A94 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFFC05F74 \n"
      "BLLT    sub_FFC05F4C \n"
      "LDR     R0, =0xFFC05F84 \n"
      "BL      sub_FFC05B7C \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFFC05F8C \n"
      "BLLT    sub_FFC05F4C \n"
      "LDR     R0, =0xFFC05F84 \n"
      "BL      sub_FFC03BF0 \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFFC05FA0 \n"
      "BLLT    sub_FFC05F4C \n"
      "BL      sub_FFC09C3C \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFFC05FAC \n"
      "BLLT    sub_FFC05F4C \n"
      "BL      sub_FFC0167C \n"
      "CMP     R0, #0 \n"
      "LDRLT   R0, =0xFFC05FB8 \n"
      "BLLT    sub_FFC05F4C \n"
      "LDMFD   SP!, {R4,LR} \n"
//      "B       sub_FFC0FAF0 \n"       //original
      "B       taskcreate_Startup_my\n" //patched
	);
}

//** taskcreate_Startup_my  @ 0xFFC0FAF0 

void __attribute__((naked,noinline)) taskcreate_Startup_my(  ) { 
asm volatile (
      "STMFD   SP!, {R3,LR} \n"
      "BL      sub_FFC24318 \n"
      "BL      sub_FFC2B704 \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FFC0FB34 \n"
      "BL      sub_FFC25B08 \n"
      "CMP     R0, #0 \n"
      "BEQ     loc_FFC0FB34 \n"
      "BL      sub_FFC24314 \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FFC0FB34 \n"
      "BL      sub_FFC239E4 \n"
      "LDR     R1, =0xC0220000 \n"
      "MOV     R0, #0x44 \n"
      "STR     R0, [R1, #0x1C] \n"
      "BL      sub_FFC23BD0 \n"
"loc_FFC0FB30:\n"
      "B       loc_FFC0FB30 \n"
"loc_FFC0FB34:\n"
      //"BL      sub_FFC24320 \n"      // hijack power-on
      "BL      sub_FFC2431C \n"
      "BL      sub_FFC29938 \n"
      "LDR     R1, =0x34E000 \n"
      "MOV     R0, #0 \n"
      "BL      sub_FFC29D80 \n"
      "BL      sub_FFC29B2C \n"
      "MOV     R3, #0 \n"
      "STR     R3, [SP] \n"
      //"LDR     R3, =0xFFC0FA8C \n"
      "LDR     R3, =task_Startup_my\n"  //-------->
      "MOV     R2, #0 \n"
      "MOV     R1, #0x19 \n"
      "LDR     R0, =0xFFC0FB7C \n"
      "BL      sub_FFC0E83C \n"
      "MOV     R0, #0 \n"
      "LDMFD   SP!, {R12,PC} \n"
	);
}

//** taskcreate_PhySw_my  @ 0xFFC24208

void __attribute__((naked,noinline)) taskcreate_PhySw_my() {
asm volatile (
      "STMFD   SP!, {R3-R5,LR} \n"
      "LDR     R4, =0x1C20 \n"
      "LDR     R0, [R4, #0x10] \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FFC2423C \n"
      "MOV     R3, #0 \n"
      "STR     R3, [SP] \n"
      //"LDR     R3, =0xFFC241D4 \n"    //original
      "LDR     R3, =mykbd_task\n"		//patched
      //"MOV     R2, #0x800 \n"
      "MOV     R2, #0x2000\n"			// + stack size for new task_PhySw so we don't have to do stack switch
      "B       sub_FFC2422C\n"    // Continue code
"loc_FFC2423C:\n"
      "B       sub_FFC2423C\n"    // Continue code
	);
}

//** task_Startup_my  @ 0xFFC0FA8C

void __attribute__((naked,noinline)) task_Startup_my(  ) { 
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "BL      sub_FFC0650C \n"
      "BL      sub_FFC25418 \n"
      "BL      sub_FFC23638 \n"
      "BL      sub_FFC2B744 \n"
      "BL      sub_FFC2B930 \n"
      //"BL      sub_FFC2B7D8 \n"    //Disable DISKBOOT.BIN
      "BL      sub_FFC2BACC \n"
      "BL      sub_FFC222E4 \n"
      "BL      sub_FFC2B960 \n"
      "BL      sub_FFC290DC \n"
      "BL      CreateTask_spytask\n" // +
      "BL      sub_FFC2BAD0 \n"
//      "BL      sub_FFC24208 \n" //original taskcreate_PhySw()
      "BL      taskcreate_PhySw_my\n"	// +
      "BL      sub_FFC27744 \n"
      "BL      sub_FFC2BAE8 \n"
      "BL      sub_FFC216A8 \n"
      "BL      sub_FFC23090 \n"
      "BL      sub_FFC2B4E0 \n"
      "BL      sub_FFC235EC \n"
      "BL      sub_FFC2302C \n"
      "BL      sub_FFC22318 \n"
      "BL      sub_FFC2C528 \n"
      "BL      sub_FFC23004 \n"
      "LDMFD   SP!, {R4,LR} \n"
      "B       sub_FFC0662C \n"
	);
}


//** init_file_modules_task  @ 0xFFC77BA8 

void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
      "STMFD   SP!, {R4-R6,LR} \n"
      "BL      sub_FFC71478 \n"
      "LDR     R5, =0x5006 \n"
      "MOVS    R4, R0 \n"
      "MOVNE   R1, #0 \n"
      "MOVNE   R0, R5 \n"
      "BLNE    sub_FFC73D30 \n"
//      "BL      sub_FFC714A4 \n"  //original
      "BL      sub_FFC714A4_my \n"  //patched
      "BL      core_spytask_can_start\n"	// added
      "CMP     R4, #0 \n"
      "MOVEQ   R0, R5 \n"
      "LDMEQFD SP!, {R4-R6,LR} \n"
      "MOVEQ   R1, #0 \n"
      "BEQ     sub_FFC73D30 \n"
      "LDMFD   SP!, {R4-R6,PC} \n"
	);
}


//** sub_FFC714A4  @ 0xFFC714A4 

void __attribute__((naked,noinline)) sub_FFC714A4_my() {
asm volatile (
      "STMFD   SP!, {R4,LR} \n"
      "MOV     R0, #3 \n"
//      "BL      sub_FFC556EC \n"  //original
      "BL      sub_FFC556EC_my\n"  //patched
      "BL      sub_FFD04A78 \n"
      "LDR     R4, =0x2BD4 \n"
      "LDR     R0, [R4, #4] \n"
      "CMP     R0, #0 \n"
      "BNE     loc_FFC714DC \n"
      "BL      sub_FFC54934 \n"
      "BL      sub_FFCFB048 \n"
      "BL      sub_FFC54934 \n"
      "BL      sub_FFC513AC \n"
      "BL      sub_FFC54834 \n"
      "BL      sub_FFCFB0DC \n"
"loc_FFC714DC:\n"
      "MOV     R0, #1 \n"
      "STR     R0, [R4] \n"
      "LDMFD   SP!, {R4,PC} \n"
	);
}


//** sub_FFC556EC_my  @ 0xFFC556EC

void __attribute__((naked,noinline)) sub_FFC556EC_my() {
asm volatile (
      "STMFD   SP!, {R4-R8,LR} \n"
      "MOV     R8, R0 \n"
      "BL      sub_FFC5566C \n"
      "LDR     R1, =0x33940 \n"
      "MOV     R6, R0 \n"
      "ADD     R4, R1, R0, LSL #7 \n"
      "LDR     R0, [R4, #0x6C] \n"
      "CMP     R0, #4 \n"
      "LDREQ   R1, =0x817 \n"
      "LDREQ   R0, =0xFFC551AC \n"
      "BLEQ    sub_FFC0EB14 \n"        // DebugAssert
      "MOV     R1, R8 \n"
      "MOV     R0, R6 \n"
      "BL      sub_FFC54F24 \n"
      "LDR     R0, [R4, #0x38] \n"
      "BL      sub_FFC55D8C \n"
      "CMP     R0, #0 \n"
      "STREQ   R0, [R4, #0x6C] \n"
      "MOV     R0, R6 \n"
      "BL      sub_FFC54FB4 \n"
      "MOV     R0, R6 \n"
//      "BL      sub_FFC55314 \n"   //original
      "BL      sub_FFC55314_my \n"  //patched
      "MOV     R5, R0 \n"
      "MOV     R0, R6 \n"
      "BL      sub_FFC55544 \n"
      "LDR     R6, [R4, #0x3C] \n"
      "AND     R7, R5, R0 \n"
      "CMP     R6, #0 \n"
      "LDR     R1, [R4, #0x38] \n"
      "MOVEQ   R0, #0x80000001 \n"
      "MOV     R5, #0 \n"
      "BEQ     loc_FFC5579C \n"
      "MOV     R0, R1 \n"
      "BL      sub_FFC54A9C \n"
      "CMP     R0, #0 \n"
      "MOVNE   R5, #4 \n"
      "CMP     R6, #5 \n"
      "ORRNE   R0, R5, #1 \n"
      "BICEQ   R0, R5, #1 \n"
      "CMP     R7, #0 \n"
      "BICEQ   R0, R0, #2 \n"
      "ORREQ   R0, R0, #0x80000000 \n"
      "BICNE   R0, R0, #0x80000000 \n"
      "ORRNE   R0, R0, #2 \n"
"loc_FFC5579C:\n"
      "CMP     R8, #7 \n"
      "STR     R0, [R4, #0x40] \n"
      "LDMNEFD SP!, {R4-R8,PC} \n"
      "MOV     R0, R8 \n"
      "BL      sub_FFC556BC \n"
      "CMP     R0, #0 \n"
      "LDMEQFD SP!, {R4-R8,LR} \n"
      "LDREQ   R0, =0xFFC557E8 \n"      // "EMEM MOUNT ERROR"
      "BEQ     sub_FFC0177C \n"         // qPrintf
      "LDMFD   SP!, {R4-R8,PC} \n"
	);
}


//** sub_FFC55314_my  @ 0xFFC55314

void __attribute__((naked,noinline)) sub_FFC55314_my() {
asm volatile (
      "STMFD   SP!, {R4-R6,LR} \n"
      "MOV     R5, R0 \n"
      "LDR     R0, =0x33940 \n"
      "ADD     R4, R0, R5, LSL #7 \n"
      "LDR     R0, [R4, #0x6C] \n"
      "TST     R0, #2 \n"
      "MOVNE   R0, #1 \n"
      "LDMNEFD SP!, {R4-R6,PC} \n"
      "LDR     R0, [R4, #0x38] \n"
      "MOV     R1, R5 \n"
//      "BL      sub_FFC55034 \n"        //original
      "BL	sub_FFC55034_my \n"          // patched
      "CMP     R0, #0 \n"
      "LDRNE   R0, [R4, #0x38] \n"
      "MOVNE   R1, R5 \n"
      "BLNE    sub_FFC551D0 \n"
      "LDR     R2, =0x339C0 \n"
      "ADD     R1, R5, R5, LSL #4 \n"
      "LDR     R1, [R2, R1, LSL #2] \n"
      "CMP     R1, #4 \n"
      "BEQ     loc_FFC55374 \n"
      "CMP     R0, #0 \n"
      "LDMEQFD SP!, {R4-R6,PC} \n"
      "MOV     R0, R5 \n"
      "BL      sub_FFC54B2C \n"
"loc_FFC55374:\n"
      "CMP     R0, #0 \n"
      "LDRNE   R1, [R4, #0x6C] \n"
      "ORRNE   R1, R1, #2 \n"
      "STRNE   R1, [R4, #0x6C] \n"
      "LDMFD   SP!, {R4-R6,PC} \n"
	);
}


//** sub_FFC55034_my  @ 0xFFC55034

void __attribute__((naked,noinline)) sub_FFC55034_my() {
asm volatile (
      "STMFD   SP!, {R4-R10,LR} \n"
      "MOV     R9, R0 \n"
      "LDR     R0, =0x33940 \n"
      "MOV     R8, #0 \n"
      "ADD     R5, R0, R1, LSL #7 \n"
      "LDR     R0, [R5, #0x3C] \n"
      "MOV     R7, #0 \n"
      "CMP     R0, #7 \n"
      "MOV     R6, #0 \n"
      "ADDLS   PC, PC, R0, LSL #2 \n"
      "B       loc_FFC5518C \n"
      "B       loc_FFC55098 \n"
      "B       loc_FFC55080 \n"
      "B       loc_FFC55080 \n"
      "B       loc_FFC55080 \n"
      "B       loc_FFC55080 \n"
      "B       loc_FFC55184 \n"
      "B       loc_FFC55080 \n"
      "B       loc_FFC55080 \n"
"loc_FFC55080:\n"
      "MOV     R2, #0 \n"
      "MOV     R1, #0x200 \n"
      "MOV     R0, #2 \n"
      "BL      sub_FFC6B5D8 \n"
      "MOVS    R4, R0 \n"
      "BNE     loc_FFC550A0 \n"
"loc_FFC55098:\n"
      "MOV     R0, #0 \n"
      "LDMFD   SP!, {R4-R10,PC} \n"
"loc_FFC550A0:\n"
      "LDR     R12, [R5, #0x50] \n"
      "MOV     R3, R4 \n"
      "MOV     R2, #1 \n"
      "MOV     R1, #0 \n"
      "MOV     R0, R9 \n"
      "BLX     R12 \n"
      "CMP     R0, #1 \n"
      "BNE     loc_FFC550CC \n"
      "MOV     R0, #2 \n"
      "BL      sub_FFC6B724 \n"
      "B       loc_FFC55098 \n"
"loc_FFC550CC:\n"
      "LDR     R1, [R5, #0x64] \n"
      "MOV     R0, R9 \n"
      "BLX     R1 \n"
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

      "LDRB    R1, [R4, #0x1C9] \n"
      "LDRB    R3, [R4, #0x1C8] \n"
      "LDRB    R12, [R4, #0x1CC] \n"
      "MOV     R1, R1, LSL #0x18 \n"
      "ORR     R1, R1, R3, LSL #0x10 \n"
      "LDRB    R3, [R4, #0x1C7] \n"
      "LDRB    R2, [R4, #0x1BE] \n"
// "		LDRB	LR, [R4,#0x1FF]\n"       // replaced, see below
      "ORR     R1, R1, R3, LSL #8 \n"
      "LDRB    R3, [R4, #0x1C6] \n"
      "CMP     R2, #0 \n"
      "CMPNE   R2, #0x80 \n"
      "ORR     R1, R1, R3 \n"
      "LDRB    R3, [R4, #0x1CD] \n"
      "MOV     R3, R3, LSL #0x18 \n"
      "ORR     R3, R3, R12, LSL #0x10 \n"
      "LDRB    R12, [R4, #0x1CB] \n"
      "ORR     R3, R3, R12, LSL #8 \n"
      "LDRB    R12, [R4, #0x1CA] \n"
      "ORR     R3, R3, R12 \n"
//      "LDRB    R12, [R4, #0x1FE] \n"
	  "LDRB    R12, [LR,#0x1FE]\n"        //added First MBR signature byte (0x55)
      "LDRB    LR, [LR,#0x1FF]\n"         //added Last MBR signature byte (0xAA)
      "BNE     loc_FFC55158 \n"
      "CMP     R0, R1 \n"
      "BCC     loc_FFC55158 \n"
      "ADD     R2, R1, R3 \n"
      "CMP     R2, R0 \n"
      "CMPLS   R12, #0x55 \n"
      "CMPEQ   LR, #0xAA \n"
      "MOVEQ   R7, R1 \n"
      "MOVEQ   R6, R3 \n"
      "MOVEQ   R4, #1 \n"
      "BEQ     loc_FFC5515C \n"
"loc_FFC55158:\n"
      "MOV     R4, R8 \n"
"loc_FFC5515C:\n"
      "MOV     R0, #2 \n"
      "BL      sub_FFC6B724 \n"
      "CMP     R4, #0 \n"
      "BNE     loc_FFC55198 \n"
      "LDR     R1, [R5, #0x64] \n"
      "MOV     R7, #0 \n"
      "MOV     R0, R9 \n"
      "BLX     R1 \n"
      "MOV     R6, R0 \n"
      "B       loc_FFC55198 \n"
"loc_FFC55184:\n"
      "MOV     R6, #0x40 \n"
      "B       loc_FFC55198 \n"
"loc_FFC5518C:\n"
      "LDR     R1, =0x572 \n"
      "LDR     R0, =0xFFC551AC \n" // "Mounter.c"
      "BL      sub_FFC0EB14 \n"    // DebugAssert
"loc_FFC55198:\n"
      "STR     R7, [R5, #0x44]! \n"
      "STMIB   R5, {R6,R8} \n"
      "MOV     R0, #1 \n"
      "LDMFD   SP!, {R4-R10,PC} \n"
	);
}
