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
extern void task_FileWrite();

void taskHook(context_t **context)
{ 
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_RotaryEncoder)		tcb->entry = (void*)JogDial_task_my;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
    if(tcb->entry == (void*)task_FileWrite)         tcb->entry = (void*)filewritetask;
}

//** boot  @ 0xFF81000C 

void __attribute__((naked,noinline)) boot(  ) { 
asm volatile (

	// LED Test
	"LDR     R1, =0xC0220134\n"	// Orange LED
	"MOV     R0, #0x46\n"	
	"STR     R0, [R1]\n"
	"LDR     R1, =0xC0223030\n"	// AF LED
	"MOV     R0, #0x46\n"
	"STR     R0, [R1]\n"	
	"LDR     R0, =0x40000 \n"
"loop1: \n"
	"nop\n"
	"SUBS   R0,R0,#1 \n"
	"BNE    loop1 \n"	
	// End LED Test

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
"    LDR     R0, =0xFFC0281C \n" 

"    LDR     R1, =0x1900 \n" 
"    LDR     R3, =0x208F0 \n" 
"loc_FF81013C:\n"
"    CMP     R1, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF81013C \n" 
"    LDR     R1, =0x153E84 \n" 
"    MOV     R2, #0 \n" 
"loc_FF810154:\n"
"    CMP     R3, R1 \n" 
"    STRCC   R2, [R3], #4 \n" 
"    BCC     loc_FF810154 \n"            
"	B	sub_FF810354_my \n"		//---------->                 
	);
};

//** sub_FF810354_my  @ 0xFF810354 

void __attribute__((naked,noinline)) sub_FF810354_my(  ) { 
   *(int*)0x1938=(int)taskHook;
   *(int*)0x193C=(int)taskHook;

   // "correct power on" is to start in record mode if the power button is held down, on cameras that can start with play or power button. Otherwise CHDK always starts in play mode.
   // remove another line farther down too - see comments
   //*(int*)(0x25BC+4)= (*(int*)0xC0220134)&1 ? 0x2000000 : 0x1000000; // replacement of sub_FF8218C8 for correct power-on.

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
"	BL	sub_FF811178_my \n"   //------------>                     
	);
}

//** sub_FF811178_my  @ 0xFF811178 

void __attribute__((naked,noinline)) sub_FF811178_my(  ) { 
asm volatile (
"    STR     LR, [SP, #-4]! \n" 
"    SUB     SP, SP, #0x74 \n" 
"    MOV     R0, SP \n" 
"    MOV     R1, #0x74 \n" 
"    BL      sub_FFB3A5D8 \n" 

"    MOV     R0, #0x53000 \n" 
"    STR     R0, [SP, #4] \n" 
//"    LDR     R0, =0x153E84 \n" 
"    LDR     R0, =new_sa\n"        // +
"    LDR     R0, [R0]\n"           // + 
"    LDR     R2, =0x339C00 \n" 
"    LDR     R1, =0x3324A8 \n" 
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
"	LDR	R1, =sub_FF815E34_my\n"  //------------>       
"	B	sub_FF8111CC\n"			// Continue in firmware        
	);
}

//** sub_FF815E34_my  @ 0xFF815E34 

void __attribute__((naked,noinline)) sub_FF815E34_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF810B08 \n" 
"    BL      sub_FF81A148 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815F48 \n" 
"    BLLT    sub_FF815F28 \n" 
"    BL      sub_FF815A70 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815F50 \n" 
"    BLLT    sub_FF815F28 \n" 
"    LDR     R0, =0xFF815F60 \n" 
"    BL      sub_FF815B58 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815F68 \n" 
"    BLLT    sub_FF815F28 \n" 
"    LDR     R0, =0xFF815F60 \n" 
"    BL      sub_FF813BE0 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815F7C \n" 
"    BLLT    sub_FF815F28 \n" 
"    BL      sub_FF819B5C \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815F88 \n" 
"    BLLT    sub_FF815F28 \n" 
"    BL      sub_FF81165C \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815F94 \n" 
"    BLLT    sub_FF815F28 \n" 
"    LDMFD   SP!, {R4,LR} \n" 
"    B       taskcreate_Startup_my\n"                       
	);
};


//** taskcreate_Startup_my

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n" 
//"    BL      sub_FF833344 \n" 
"    BL      sub_FF83A224 \n" 
"    CMP     R0, #0 \n" 
"    BNE     loc_FF81F8B0 \n" 
"    LDR     R4, =0xC0220000 \n" 
"    LDR     R0, [R4, #0x12C] \n" 
"    TST     R0, #1 \n" 
"    MOVEQ   R0, #0x12C \n" 
"    BLEQ    sub_FF83865C \n" 
"    BL      sub_FF833340 \n" 
"    CMP     R0, #0 \n" 
"    BNE     loc_FF81F8B0 \n" 
"    BL      sub_FF8329DC \n" 
"    MOV     R0, #0x44 \n" 
"    STR     R0, [R4, #0x1C] \n" 
"    BL      sub_FF832BC8 \n" 
"loc_FF81F8AC:\n"
"    B       loc_FF81F8AC \n" 
"loc_FF81F8B0:\n"
"    BL      sub_FF83334C \n"  // remove for correct power-on on 'on/off' button (see note above).                      
//"    BL      sub_FF833348 \n" 
"    BL      sub_FF8384D4 \n" 
"    LDR     R1, =0x38E000 \n" 
"    MOV     R0, #0 \n" 
"    BL      sub_FF83891C \n" 
"    BL      sub_FF8386C8 \n" 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
"    LDR     R3, =task_Startup_my\n" // ->   
"    B       sub_FF81F8D8\n"		// Continue in firmware               
     );
}

//** task_Startup_my  @ 0xFF81F804 

void __attribute__((naked,noinline)) task_Startup_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF816490 \n" 
"    BL      sub_FF834440 \n" 
"    BL      sub_FF832670 \n" 
//"    BL      sub_FF83A264 \n" 
"    BL      sub_FF83A448 \n" 
//"    BL      sub_FF83A2F8 \n"      // start diskboot.bin
"    BL      sub_FF83A5F0 \n" 
"    BL      sub_FF83136C \n" 
"    BL      sub_FF83A478 \n" 
"    BL      sub_FF837C78 \n" 
"    BL      sub_FF83A5F4 \n" 
"    BL  CreateTask_spytask\n"		// + 
//"    BL      sub_FF833230 \n" 	// original taskcreate_PhySw  
"    BL      taskcreate_PhySw_my\n"	// +             
"    B       sub_FF81F838\n"		// Continue in firmware  
	);
}


//** taskcreatePhySw_my  @ 0xFF833230

void __attribute__((naked,noinline)) taskcreate_PhySw_my(  ) {
asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n" 
"    LDR     R4, =0x1C38 \n" 
"    LDR     R0, [R4, #0x10] \n" 
"    CMP     R0, #0 \n" 
"    BNE     sub_FF833264 \n"   	// jump to firmware address 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
//"    LDR     R3, =0xFF8331FC \n" 
//"    MOV     R2, #0x800 \n" 
"	LDR	R3, =mykbd_task\n"		// Changed                                     
"	MOV     R2, #0x2000\n"		// + stack size for new task_PhySw so we don't have to do stack switch
"	B       sub_FF833254 \n"    // Continue code            
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

///*----------------------------------------------------------------------

//** init_file_modules_task  @ 0xFF894500 

void __attribute__((naked,noinline)) init_file_modules_task(  ) { 
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n" 
"    BL      sub_FF8893E8 \n" 
"    LDR     R5, =0x5006 \n" 
"    MOVS    R4, R0 \n" 
"    MOVNE   R1, #0 \n" 
"    MOVNE   R0, R5 \n" 
"    BLNE    sub_FF88E804 \n"           
"	BL		sub_FF889414_my \n" //---------->  
"	BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask      
"	B	sub_FF894520\n"			// Continue in firmware               
	);
}

//** sub_FF889414_my  @ 0xFF889414 

void __attribute__((naked,noinline)) sub_FF889414_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    MOV     R0, #3 \n" 
"    BL      sub_FF86B730_my \n" //---------->    
"    B       sub_FF889420 \n"	// Continue in firmware                  
	);
}


//** sub_FF86B730_my  @ 0xFF86B730 

void __attribute__((naked,noinline)) sub_FF86B730_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n" 
"    MOV     R8, R0 \n" 
"    BL      sub_FF86B6B0 \n" 
"    LDR     R1, =0x49160 \n" 
"    MOV     R6, R0 \n" 
"    ADD     R4, R1, R0, LSL #7 \n" 
"    LDR     R0, [R4, #0x6C] \n" 
"    CMP     R0, #4 \n" 
"    LDREQ   R1, =0x804 \n" 
"    LDREQ   R0, =0xFF86B1FC \n" 
"    BLEQ    sub_FF81E88C \n" 
"    MOV     R1, R8 \n" 
"    MOV     R0, R6 \n" 
"    BL      sub_FF86AF50 \n" 
"    LDR     R0, [R4, #0x38] \n" 
"    BL      sub_FF86BD4C \n" 
"    CMP     R0, #0 \n" 
"    STREQ   R0, [R4, #0x6C] \n" 
"    MOV     R0, R6 \n" 
"    BL      sub_FF86AFE0 \n" 
"    MOV     R0, R6 \n" 
"    BL      sub_FF86B364_my \n"  //---------->     
"    B       sub_FF86B788\n"	  // Continue in firmware                 
	);
}


//** sub_FF86B364_my  @ 0xFF86B364 

void __attribute__((naked,noinline)) sub_FF86B364_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n" 
"    MOV     R5, R0 \n" 
"    LDR     R0, =0x49160 \n" 
"    ADD     R4, R0, R5, LSL #7 \n" 
"    LDR     R0, [R4, #0x6C] \n" 
"    TST     R0, #2 \n" 
"    MOVNE   R0, #1 \n" 
"    LDMNEFD SP!, {R4-R6,PC} \n" 
"    LDR     R0, [R4, #0x38] \n" 
"    MOV     R1, R5 \n"                            
"	BL	sub_FF86B060_my\n"  //---------->     
"	B	sub_FF86B390\n"		// Continue in firmware                   
	);
}


//** sub_FF86B060_my  @ 0xFF86B060 

void __attribute__((naked,noinline)) sub_FF86B060_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n" 
"    MOV     R9, R0 \n" 
"    LDR     R0, =0x49160 \n" 
"    MOV     R8, #0 \n" 
"    ADD     R5, R0, R1, LSL #7 \n" 
"    LDR     R0, [R5, #0x3C] \n" 
"    MOV     R7, #0 \n" 
"    CMP     R0, #7 \n" 
"    MOV     R6, #0 \n" 
"    ADDLS   PC, PC, R0, LSL #2 \n" 
"    B       loc_FF86B1B8 \n" 
"    B       loc_FF86B0C4 \n" 
"    B       loc_FF86B0AC \n" 
"    B       loc_FF86B0AC \n" 
"    B       loc_FF86B0AC \n" 
"    B       loc_FF86B0AC \n" 
"    B       loc_FF86B1B0 \n" 
"    B       loc_FF86B0AC \n" 
"    B       loc_FF86B0AC \n" 
"loc_FF86B0AC:\n"
"    MOV     R2, #0 \n" 
"    MOV     R1, #0x200 \n" 
"    MOV     R0, #2 \n" 
"    BL      sub_FF883468 \n" 
"    MOVS    R4, R0 \n" 
"    BNE     loc_FF86B0CC \n" 
"loc_FF86B0C4:\n"
"    MOV     R0, #0 \n" 
"    LDMFD   SP!, {R4-R10,PC} \n" 
"loc_FF86B0CC:\n"
"    LDR     R12, [R5, #0x50] \n" 
"    MOV     R3, R4 \n" 
"    MOV     R2, #1 \n" 
"    MOV     R1, #0 \n" 
"    MOV     R0, R9 \n" 
"    BLX     R12 \n" 
"    CMP     R0, #1 \n" 
"    BNE     loc_FF86B0F8 \n" 
"    MOV     R0, #2 \n" 
"    BL      sub_FF8835B4 \n" 
"    B       loc_FF86B0C4 \n" 
"loc_FF86B0F8:\n"
"    LDR     R1, [R5, #0x64] \n" 
"    MOV     R0, R9 \n" 
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
//"    LDRB    LR, [R4, #0x1FF] \n" 
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
//"    LDRB    R12, [R4, #0x1FE] \n"      // -
"	LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
"	LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.
"    BNE     loc_FF86B184 \n" 
"    CMP     R0, R1 \n" 
"    BCC     loc_FF86B184 \n" 
"    ADD     R2, R1, R3 \n" 
"    CMP     R2, R0 \n" 
"    CMPLS   R12, #0x55 \n" 
"    CMPEQ   LR, #0xAA \n" 
"    MOVEQ   R7, R1 \n" 
"    MOVEQ   R6, R3 \n" 
"    MOVEQ   R4, #1 \n" 
"    BEQ     loc_FF86B188 \n" 
"loc_FF86B184:\n"
"    MOV     R4, R8 \n" 
"loc_FF86B188:\n"
"    MOV     R0, #2 \n" 
"    BL      sub_FF8835B4 \n" 
"    CMP     R4, #0 \n" 
"    BNE     loc_FF86B1C4 \n" 
"    LDR     R1, [R5, #0x64] \n" 
"    MOV     R7, #0 \n" 
"    MOV     R0, R9 \n" 
"    BLX     R1 \n" 
"    MOV     R6, R0 \n" 
"    B       loc_FF86B1C4 \n" 
"loc_FF86B1B0:\n"
"    MOV     R6, #0x40 \n" 
"    B       loc_FF86B1C4 \n" 
"loc_FF86B1B8:\n"
"    LDR     R1, =0x568 \n" 
"    LDR     R0, =0xFF86B1FC \n" 
"    BL      sub_FF81E88C \n" 
"loc_FF86B1C4:\n"
"    STR     R7, [R5, #0x44]! \n" 
"    STMIB   R5, {R6,R8} \n" 
"    MOV     R0, #1 \n" 
"    LDMFD   SP!, {R4-R10,PC} \n"         
	);
}


//** JogDial_task_my  @ 0xFF85AFB0 

void __attribute__((naked,noinline)) JogDial_task_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4-R11,LR} \n" 
"    SUB     SP, SP, #0x2C \n" 
"    BL      sub_FF85B358 \n" 
"    LDR     R1, =0x23E4 \n" 
"    LDR     R8, =0xFFB40564 \n" 

"    MOV     R0, #0 \n" 
"    ADD     R2, SP, #0x14 \n" 
"    ADD     R3, SP, #0x18 \n" 
"    ADD     R10, SP, #0xC \n" 
"    ADD     R9, SP, #0x10 \n" 
"    MOV     R7, #0 \n" 
"loc_FF85AFDC:\n"
"    ADD     R3, SP, #0x18 \n" 
"    ADD     R12, R3, R0, LSL #1 \n" 
"    ADD     R2, SP, #0x14 \n" 
"    STRH    R7, [R12] \n" 
"    ADD     R12, R2, R0, LSL #1 \n" 
"    STRH    R7, [R12] \n" 
"    STR     R7, [R9, R0, LSL #2] \n" 
"    STR     R7, [R10, R0, LSL #2] \n" 
"    ADD     R0, R0, #1 \n" 
"    CMP     R0, #1 \n" 
"    BLT     loc_FF85AFDC \n" 
"loc_FF85B008:\n"
"    LDR     R0, =0x23E4 \n" 
"    MOV     R2, #0 \n" 
"    LDR     R0, [R0, #8] \n" 
"    ADD     R1, SP, #4 \n" 
"    BL      sub_FF837F08 \n" 
"    TST     R0, #1 \n" 
"    LDRNE   R1, =0x226 \n" 
"    LDRNE   R0, =0xFF85B28C \n" 
"    BLNE    sub_FF81E88C \n" 
"    LDR     R0, [SP, #4] \n" 
"    AND     R4, R0, #0xFF \n" 
"    AND     R0, R0, #0xFF00 \n" 
"    CMP     R0, #0x100 \n" 
"    BEQ     loc_FF85B08C \n" 
"    CMP     R0, #0x200 \n" 
"    BEQ     loc_FF85B0C4 \n" 
"    CMP     R0, #0x300 \n" 
"    BEQ     loc_FF85B2D8 \n" 
"    CMP     R0, #0x400 \n" 
"    BNE     loc_FF85B008 \n" 
"    CMP     R4, #0 \n" 
"    LDRNE   R1, =0x2CA \n" 
"    LDRNE   R0, =0xFF85B28C \n" 
"    BLNE    sub_FF81E88C \n" 
"    LDR     R2, =0xFFB40550 \n" 

"    ADD     R0, R4, R4, LSL #2 \n" 
"    LDR     R1, [R2, R0, LSL #2] \n" 
"    STR     R7, [R1] \n" 
"    MOV     R1, #1 \n" 
"    ADD     R0, R2, R0, LSL #2 \n" 
"loc_FF85B080:\n"
"    LDR     R0, [R0, #8] \n" 
"    STR     R1, [R0] \n" 
"    B       loc_FF85B008 \n" 
"loc_FF85B08C:\n"
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      sub_FF83865C\n"//sleep
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
"    LDR     R5, =0x23F4 \n" 
"    LDR     R0, [R5, R4, LSL #2] \n" 
"    BL      sub_FF838EA0 \n" 
"    LDR     R2, =0xFF85AF3C \n" 
"    ADD     R1, R2, #0 \n" 
"    ORR     R3, R4, #0x200 \n" 
"    MOV     R0, #0x28 \n" 
"    BL      sub_FF838DBC \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R10, R4, LSL #2] \n" 
"    BEQ     loc_FF85B008 \n" 
"    LDR     R1, =0x23B \n" 
"    B       loc_FF85B27C \n" 
"loc_FF85B0C4:\n"
"    LDR     R1, =0xFFB40550 \n" 

"    ADD     R0, R4, R4, LSL #2 \n" 
"    STR     R0, [SP, #0x28] \n" 
"    ADD     R0, R1, R0, LSL #2 \n" 
"    STR     R0, [SP, #0x24] \n" 
"    LDR     R0, [R0, #4] \n" 
"    LDR     R0, [R0] \n" 
"    MOV     R2, R0, ASR #0x10 \n" 
"    ADD     R0, SP, #0x18 \n" 
"    ADD     R0, R0, R4, LSL #1 \n" 
"    STR     R0, [SP, #0x20] \n" 
"    STRH    R2, [R0] \n" 
"    ADD     R0, SP, #0x14 \n" 
"    ADD     R0, R0, R4, LSL #1 \n" 
"    STR     R0, [SP, #0x1C] \n" 
"    LDRSH   R3, [R0] \n" 
"    SUB     R0, R2, R3 \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF85B234 \n" 
"    MOV     R1, R0 \n" 
"    RSBLT   R0, R0, #0 \n" 
"    MOVLE   R5, #0 \n" 
"    MOVGT   R5, #1 \n" 
"    CMP     R0, #0xFF \n" 
"    BLS     loc_FF85B150 \n" 
"    CMP     R1, #0 \n" 
"    RSBLE   R0, R3, #0xFF \n" 
"    ADDLE   R0, R0, #0x7F00 \n" 
"    ADDLE   R0, R0, R2 \n" 
"    RSBGT   R0, R2, #0xFF \n" 
"    ADDGT   R0, R0, #0x7F00 \n" 
"    ADDGT   R0, R0, R3 \n" 
"    ADD     R0, R0, #0x8000 \n" 
"    ADD     R0, R0, #1 \n" 
"    EOR     R5, R5, #1 \n" 
"loc_FF85B150:\n"
"    STR     R0, [SP, #8] \n" 
"    LDR     R0, [R9, R4, LSL #2] \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF85B1A0 \n" 
"    LDR     R1, =0xFFB40548 \n" 

"    ADD     R1, R1, R4, LSL #3 \n" 
"    LDR     R1, [R1, R5, LSL #2] \n" 
"    CMP     R1, R0 \n" 
"    BEQ     loc_FF85B1BC \n" 
"    ADD     R11, R4, R4, LSL #1 \n" 
"    ADD     R6, R8, R11, LSL #2 \n" 
"    LDRB    R0, [R6, #9] \n" 
"    CMP     R0, #1 \n" 
"    LDREQ   R0, [R6, #4] \n" 
"    BLEQ    sub_FF890684 \n" 
"    LDRB    R0, [R6, #8] \n" 
"    CMP     R0, #1 \n" 
"    BNE     loc_FF85B1BC \n" 
"    LDR     R0, [R8, R11, LSL #2] \n" 
"    B       loc_FF85B1B8 \n" 
"loc_FF85B1A0:\n"
"    ADD     R0, R4, R4, LSL #1 \n" 
"    ADD     R1, R8, R0, LSL #2 \n" 
"    LDRB    R1, [R1, #8] \n" 
"    CMP     R1, #1 \n" 
"    BNE     loc_FF85B1BC \n" 
"    LDR     R0, [R8, R0, LSL #2] \n" 
"loc_FF85B1B8:\n"
"    BL      sub_FF890684 \n" 
"loc_FF85B1BC:\n"
"    LDR     R0, =0xFFB40548 \n" 

"    LDR     R1, [SP, #8] \n" 
"    ADD     R6, R0, R4, LSL #3 \n" 
"    LDR     R0, [R6, R5, LSL #2] \n" 
"    BL      sub_FF890590 \n" 
"    LDR     R0, [R6, R5, LSL #2] \n" 
"    STR     R0, [R9, R4, LSL #2] \n" 
"    LDR     R0, [SP, #0x20] \n" 
"    LDR     R1, [SP, #0x1C] \n" 
"    LDRH    R0, [R0] \n" 
"    STRH    R0, [R1] \n" 
"    ADD     R0, R4, R4, LSL #1 \n" 
"    ADD     R0, R8, R0, LSL #2 \n" 
"    LDRB    R0, [R0, #9] \n" 
"    CMP     R0, #1 \n" 
"    BNE     loc_FF85B234 \n" 
"    LDR     R5, =0x23F4 \n" 
"    LDR     R0, [R5, R4, LSL #2] \n" 
"    BL      sub_FF838EA0 \n" 
"    LDR     R2, =0xFF85AF48 \n" 
"    ADD     R1, R2, #0 \n" 
"    ORR     R3, R4, #0x300 \n" 
"    MOV     R0, #0x1F4 \n" 
"    BL      sub_FF838DBC \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R5, R4, LSL #2] \n" 
"    LDRNE   R0, =0xFF85B28C \n" 
"    MOVNE   R1, #0x2A4 \n" 
"    BLNE    sub_FF81E88C \n" 
"loc_FF85B234:\n"
"    ADD     R0, R4, R4, LSL #1 \n" 
"    ADD     R0, R8, R0, LSL #2 \n" 
"    LDRB    R0, [R0, #0xA] \n" 
"    CMP     R0, #1 \n" 
"    BNE     loc_FF85B2BC \n" 
"    LDR     R0, =0x23E4 \n" 
"    LDR     R0, [R0, #0xC] \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF85B2BC \n" 
"    LDR     R2, =0xFF85AF3C \n" 
"    ADD     R1, R2, #0 \n" 
"    ORR     R3, R4, #0x400 \n" 
"    BL      sub_FF838DBC \n" 
"    TST     R0, #1 \n" 
"    CMPNE   R0, #0x15 \n" 
"    STR     R0, [R10, R4, LSL #2] \n" 
"    BEQ     loc_FF85B008 \n" 
"    LDR     R1, =0x2AF \n" 
"loc_FF85B27C:\n"
"    LDR     R0, =0xFF85B28C \n" 
"    BL      sub_FF81E88C \n" 
"    B       loc_FF85B008 \n" 
"loc_FF85B2BC:\n"
"    LDR     R1, =0xFFB40550 \n" 

"    LDR     R0, [SP, #0x28] \n" 
"    LDR     R0, [R1, R0, LSL #2] \n" 
"    STR     R7, [R0] \n" 
"    LDR     R0, [SP, #0x24] \n" 
"    MOV     R1, #1 \n" 
"    B       loc_FF85B080 \n" 
"loc_FF85B2D8:\n"
"    LDR     R0, [R9, R4, LSL #2] \n" 
"    CMP     R0, #0 \n" 
"    MOVEQ   R1, #0x2BC \n" 
"    LDREQ   R0, =0xFF85B28C \n" 
"    BLEQ    sub_FF81E88C \n" 
"    ADD     R0, R4, R4, LSL #1 \n" 
"    ADD     R0, R8, R0, LSL #2 \n" 
"    LDR     R0, [R0, #4] \n" 
"    BL      sub_FF890684 \n" 
"    STR     R7, [R9, R4, LSL #2] \n" 
"    B       loc_FF85B008 \n"                  
	);
}
