#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;
int myFlag =0;

void taskHook(context_t **context) {
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	if(!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task; 
	if(!_strcmp(tcb->name, "CaptSeqTask"))     tcb->entry = (void*)capt_seq_task; 
	if(!_strcmp(tcb->name, "InitFileModules")) tcb->entry = (void*)init_file_modules_task;
	if(!_strcmp(tcb->name, "MovieRecord"))     tcb->entry = (void*)movie_record_task;
	if(!_strcmp(tcb->name, "ExpDrvTask"))      tcb->entry = (void*)exp_drv_task;
}

void CreateTask_spytask() {
	_CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

//ffc0000c
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
      "    MOV     R0, #0x31 \n" 		// memory region & size. bits 1 - 5 = size index, actual size = 2^(size index + 1) = 128MB (de IXUS220 - recalcular)
      "    MCR     p15, 0, R0, c6, c2 \n" 
      "    LDR     R0, =0x10000031 \n" 	// memory region & size. bits 1 - 5 = size index, actual size = 2^(size index + 1) = 128MB (...)
      "    MCR     p15, 0, R0, c6, c3 \n" 
      "    MOV     R0, #0x40000017 \n" 
      "    MCR     p15, 0, R0, c6, c4 \n" 
      "    LDR     R0, =0xFFC0002B \n" 
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
      "    MOV     R1, #0x40000006 \n" 
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
      "    STR     R2, [R1]\n"
	  
      "    LDR     R2, =0xC0242010 \n" 
      "    LDR     R1, [R2] \n" 
      "    ORR     R1, R1, #1 \n" 
      "    STR     R1, [R2] \n" 
      "    LDR     R0, =0xFFF0E278 \n" 
      "    LDR     R1, =0x1900 \n" 
      "    LDR     R3, =0xB3C8 \n" 
"loc_FFC0013C:\n"
      "    CMP     R1, R3 \n"  //Initialize Data with Rom values
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_FFC0013C \n" 
      "    LDR     R1, =0x13A700 \n" 
      "    MOV     R2, #0 \n" 
"loc_FFC00154:\n"
      "    CMP     R3, R1 \n"  //Zero initialization
      "    STRCC   R2, [R3], #4 \n" 
      "    BCC     loc_FFC00154 \n" 
    //"    B       sub_FFC0035C \n" 
	  "    B       sub_FFC0035C_my\n"//---------> patched
	);
};


long *blob_chdk_core;
long *blob_copy_and_reset;
long blob_chdk_core_size;
long blob_copy_and_reset_size;

void __attribute__((naked,noinline)) sub_FFC0035C_my() {
	*(int*)0x1938=(int)taskHook;	// ? compared to iXUS220 - a800(ffc00794) x ixus220 (ff810790:)
	*(int*)0x193C=(int)taskHook;	// ?

	// "correct power on" is to start in record mode if the power button is held down, on cameras that can start with play or power button. Otherwise CHDK always starts in play mode.
	//*(int*)(0x20F8)= (*(int*)0xC022005C) & 1 ? 0x4000000 : 0x2000000; // replacement of sub_FFC42F30 for correct power-on deA495.
	//A800 ffc4383c <= ffc2396c(Next to NotifyMask) <= ffc10730. Associated Modification in taskcreate_Startup_my (comment BL      sub_FFC2396C) - VERY IMPORTANT from Start of PORTING work
	*(int*)(0x20FC)= (*(int*)0xC022005C) & 1 ? 0x200000 : 0x100000; 

asm volatile (
      "    LDR     R0, =0xFFC003D4 \n" 
      "    MOV     R1, #0 \n" 
      "    LDR     R3, =0xFFC0040C \n" 
"loc_FFC00368:\n"
      "    CMP     R0, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_FFC00368 \n" 
      "    LDR     R0, =0xFFC0040C \n" 
      "    MOV     R1, #0x4B0 \n" 
      "    LDR     R3, =0xFFC00620 \n" 
"loc_FFC00384:\n"
      "    CMP     R0, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_FFC00384 \n" 
      "    MOV     R0, #0xD2 \n" 
      "    MSR     CPSR_cxsf, R0 \n" 
      "    MOV     SP, #0x1000 \n" 
      "    MOV     R0, #0xD3 \n" 
      "    MSR     CPSR_cxsf, R0 \n" 
      "    MOV     SP, #0x1000 \n" 
      "    LDR     R0, =0x6C4 \n" 
      "    LDR     R2, =0xEEEEEEEE \n" 
      "    MOV     R3, #0x1000 \n" 
"loc_FFC003B8:\n"
      "    CMP     R0, R3 \n" 
      "    STRCC   R2, [R0], #4 \n" 
      "    BCC     loc_FFC003B8 \n" 
      "    BL      sub_FFC011B4_my\n" //--------> doesn't return as 11b4_my doesn't	  
	);	
}

void __attribute__((naked,noinline)) sub_FFC011B4_my() {
asm volatile (
      "    STR     LR, [SP, #-4]! \n" 
      "    SUB     SP, SP, #0x74 \n" 
      "    MOV     R1, #0x74 \n" 
      "    MOV     R0, SP \n" 
      "    BL      sub_FFE99B44 \n" 
      "    MOV     R0, #0x53000 \n" 
      "    STR     R0, [SP, #4] \n" 
      //"    LDR     R0, =0x13A700 \n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
        "LDR     R0, =0x13a700\n" 			// use original heap offset since CHDK is loaded in high memory
#else
		"LDR     R0, =new_sa\n"				// + substitutes MEMISOSTART
		"LDR     R0, [R0]\n"				// +
#endif	  
      "    LDR     R2, =0x271F80 \n" 
      "    STR     R0, [SP, #8] \n" 
      "    SUB     R0, R2, R0 \n" 
      "    STR     R0, [SP, #0xC] \n" 
      "    MOV     R0, #0x22 \n" 
      "    STR     R0, [SP, #0x18] \n" 
      "    MOV     R0, #0x68 \n" 
      "    STR     R0, [SP, #0x1C] \n" 
      "    LDR     R1, =0x279C00 \n" 
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
      "    LDR     R1, =sub_FFC05EE4_my \n" 
      "    MOV     R2, #0 \n" 
      "    MOV     R0, SP \n" 
      "    BL      sub_FFC034C8 \n" 
      "    B       sub_FFC01250\n"
	);
}


void __attribute__((naked,noinline)) sub_FFC05EE4_my() {
asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    BL      sub_FFC00B2C \n" 
      "    BL      sub_FFC0A978 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFFC05FF8 \n" 
      "    BLLT    sub_FFC05FD8 \n" 
      "    BL      sub_FFC05B1C \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFFC06000 \n" 
      "    BLLT    sub_FFC05FD8 \n" 
      "    LDR     R0, =0xFFC06010 \n" 
      "    BL      sub_FFC05C04 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFFC06018 \n" 
      "    BLLT    sub_FFC05FD8 \n" 
      "    LDR     R0, =0xFFC06010 \n" 
      "    BL      sub_FFC03CAC \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFFC0602C \n" 
      "    BLLT    sub_FFC05FD8 \n" 
      "    BL      sub_FFC0A304 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFFC06038 \n" 
      "    BLLT    sub_FFC05FD8 \n" 
      "    BL      sub_FFC01694 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFFC06044 \n" 
      "    BLLT    sub_FFC05FD8 \n" 
      "    LDMFD   SP!, {R4,LR} \n" 
      "    B       taskcreate_Startup_my\n" //-------->
    );
};

//ffc10730:
void __attribute__((naked,noinline)) taskcreate_Startup_my() {//referenced to ixus220
asm volatile (
      "    STMFD   SP!, {R3-R9,LR} \n" 
      "    MOV     R6, #0 \n" 
    //"    BL      sub_FFC23964 \n" 
      "    BL      sub_FFC2B1CC \n" 
      "    LDR     R9, =0xC0220000 \n" 
      "    MOVS    R7, R0 \n" 
      "    MOV     R8, #1 \n" 
      "    BNE     loc_FFC10790 \n" 
      "    BL      sub_FFC25268 \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FFC10790 \n" 
      "    LDR     R0, [R9, #0x44] \n" 
      "    BIC     R5, R8, R0 \n" 
      "    LDR     R0, [R9, #0x5C] \n" 
      "    BIC     R4, R8, R0 \n" 
      "    BL      sub_FFC232AC \n" 
      "    CMP     R0, #1 \n" 
      "    MOVEQ   R6, #1 \n" 
      "    ORR     R0, R4, R5 \n" 
      "    ORRS    R0, R0, R6 \n" 
      "    BNE     loc_FFC107A0 \n" 
	  
      "    MOV     R0, #0x44 \n" 
      "    STR     R0, [R9, #0x20] \n" 
	  
"loc_FFC1078C:\n"
      "    B       loc_FFC1078C \n" 
"loc_FFC10790:\n"
      "    LDR     R0, [R9, #0x5C] \n" 
      "    BIC     R4, R8, R0 \n" 
      "    LDR     R0, [R9, #0x44] \n" 
      "    BIC     R5, R8, R0 \n" 
"loc_FFC107A0:\n"
      "    MOV     R3, R6 \n" 
      "    MOV     R2, R7 \n" 
      "    MOV     R1, R5 \n" 
      "    MOV     R0, R4 \n" 
    //"    BL      sub_FFC2396C \n" 
    //"    BL      sub_FFC23968 \n" 
      "    BL      sub_FFC29590 \n" 
      "    LDR     R1, =0x2CE000 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_FFC29800 \n" 
      "    BL      sub_FFC297A8 \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
    //"    LDR     R3, =0xFFC106D4 \n" 
      "    LDR     R3, =task_Startup_my \n"   	// --> patched
      "    B       sub_FFC107D8\n"	// --> continue in firmware	  
	);
}

void __attribute__((naked,noinline)) task_Startup_my() {
//ffc106d4
asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    BL      sub_FFC062B0 \n" 
      "    BL      sub_FFC24AD8 \n" 
      "    BL      sub_FFC232BC \n" 
      "    BL      sub_FFC2B214 \n" 
      "    BL      sub_FFC2B400 \n" 
    //"    BL      sub_FFC2B2A8 \n" 
      "    BL      sub_FFC2B59C \n" 
      "    BL      sub_FFC2B430 \n" 
      "    BL      sub_FFC28A24 \n" 
      "    BL      sub_FFC2B5A0 \n" 
      "    BL      CreateTask_spytask\n"
    //"    BL      sub_FFC2382C \n" 
      "    BL      taskcreate_PhySw_my\n"	
      "    BL      sub_FFC27168 \n" 
      "    BL      sub_FFC2B5B8 \n" 
    //"    BL      sub_FFC2221C \n" 
      "    BL      sub_FFC22CC4 \n"
      "    BL      sub_FFC2AF88 \n" 
      "    BL      sub_FFC2325C \n" 
      "    BL      sub_FFC22C64 \n" 
	  
      "    BL      sub_FFC2C130 \n" 
      "    BL      sub_FFC22C28 \n" 
      "    LDMFD   SP!, {R4,LR} \n" 
      "    B       sub_FFC061B0 \n" 
	);
}

// ROM:FFC2382C taskcreate_PhySw
void __attribute__((naked,noinline)) taskcreate_PhySw_my() {
asm volatile (
      "    STMFD   SP!, {R3-R5,LR} \n" 
      "    LDR     R4, =0x1BF8 \n" 
      "    LDR     R0, [R4, #4] \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     sub_FFC23860 \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
      "    LDR     R3, =mykbd_task\n" 		//------>
    //"    MOV     R2, #0x800 \n" 
      "    MOV     R2, #0x2000 \n" 
      "    B       sub_FFC23850\n"    // Continue Firmware code
	);
}

// ROM:ffc7387c task_InitFileModules
void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n" 
      "    BL      sub_FFC6C2C0 \n" 
      "    LDR     R5, =0x5006 \n" 
      "    MOVS    R4, R0 \n" 
      "    MOVNE   R1, #0 \n" 
      "    MOVNE   R0, R5 \n" 
      "    BLNE    sub_FFC6FB08 \n" 
      "    BL      sub_FFC6C2EC \n" 
	  
      "    BL      core_spytask_can_start\n"
       "   B       sub_FFC7389C\n"			// continues firmware code
	);
}


