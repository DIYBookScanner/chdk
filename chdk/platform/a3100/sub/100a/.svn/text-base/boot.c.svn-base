#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"
#include "dryos31.h"
#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)
const char * const new_sa = &_end;


// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
void task_CaptSeqTask_my();

void taskCreateHook(int *p) { 
p-=17;
if (p[0]==0xff886470)  p[0]=(int)init_file_modules_task;
if (p[0]==0xff86d6a0)  p[0]=(int)task_CaptSeqTask_my;
if (p[0]==0xff8aa748)  p[0]=(int)exp_drv_task;
if (p[0]==0xff92db3c)  p[0]=(int)movie_record_task;
}

void taskCreateHook2(int *p) { 
p-=17;
if (p[0]==0xff886470)  p[0]=(int)init_file_modules_task;
if (p[0]==0xff8aa748)  p[0]=(int)exp_drv_task;
}

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
      "    MOV     R0, #0x33 \n" 
      "    MCR     p15, 0, R0, c6, c2 \n" 
      "    LDR     R0, =0x10000033 \n" 
      "    MCR     p15, 0, R0, c6, c3 \n" 
      "    MOV     R0, #0x40000017 \n" 
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
      "    STR     R2, [R1] \n" 
      "    LDR     R2, =0xC0242010 \n" 
      "    LDR     R1, [R2] \n" 
      "    ORR     R1, R1, #1 \n" 
      "    STR     R1, [R2] \n" 
      "    LDR     R0, =0xFFB65644 \n" 
      "    LDR     R1, =0x1900 \n" 
      "    LDR     R3, =0xC4C8 \n" 
"loc_FF81013C:\n"
      "    CMP     R1, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_FF81013C \n" 
      "    LDR     R1, =0x1488E0 \n" 
      "    MOV     R2, #0 \n" 
"loc_FF810154:\n"
      "    CMP     R3, R1 \n" 
      "    STRCC   R2, [R3], #4 \n" 
      "    BCC     loc_FF810154 \n" 

        //"B       loc_FF810358\n"
		"B       sub_FF810358_my\n" // ---------------->
    );
};

void __attribute__((naked,noinline)) sub_FF810358_my() {
    *(int*)0x1930=(int)taskCreateHook; 
    *(int*)0x1934=(int)taskCreateHook2; 
    *(int*)0x1938=(int)taskCreateHook; 		
	
    /* Power ON/OFF detection */
     *(int*)(0x21B4)= (*(int*)0xC02200A8)&1 ? 0x200000 : 0x100000; // @ FF853F90 replacement  for correct power-on.

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
      //"    BL      loc_FF81119C \n"
        "BL      sub_FF81119C_my\n"
/*"loc_FFC003C4:\n"
        "ANDEQ   R0, R0, R4,ASR#13\n"
"loc_FFC003C8:\n"
        "ANDEQ   R0, R0, R0,ROR R6\n"
"loc_FFC003CC:\n"
        "ANDEQ   R0, R0, R4,ROR R6\n"
"loc_FFC003D0:\n"
        "NOP\n"
        "LDR     PC, =0xFFC0061C\n"*/
  );				
};


void __attribute__((naked,noinline)) sub_FF81119C_my() { 
        asm volatile (
      "    STR     LR, [SP, #-4]! \n" 
      "    SUB     SP, SP, #0x74 \n" 
      "    MOV     R0, SP \n" 
      "    MOV     R1, #0x74 \n" 
      "    BL      sub_FFAD5918 \n" 
      "    MOV     R0, #0x53000 \n" 
      "    STR     R0, [SP, #4] \n" 
        //      "    LDR     R0, =0x1488E0 \n"     // -
		 "LDR     R0, =new_sa\n"        // +
		 "LDR     R0, [R0]\n"           // +	

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
     // "    LDR     R1, =0xFF815E5C \n" 
        "LDR     R1, =sub_FF815E5C_my\n"
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
      "    BL      sub_FF813408 \n" 
      "    ADD     SP, SP, #0x74 \n" 
      "    LDR     PC, [SP], #4 \n" 
        );
}; 

void __attribute__((naked,noinline)) sub_FF815E5C_my() {
	asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    BL      sub_FF810B24 \n" 
      "    BL      sub_FF81A838 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFF815F70 \n" 
      "    BLLT    sub_FF815F50 \n" 
      "    BL      sub_FF815A98 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFF815F78 \n" 
      "    BLLT    sub_FF815F50 \n" 
      "    LDR     R0, =0xFF815F88 \n" 
      "    BL      sub_FF815B80 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFF815F90 \n" 
      "    BLLT    sub_FF815F50 \n" 
      "    LDR     R0, =0xFF815F88 \n" 
      "    BL      sub_FF813BF4 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFF815FA4 \n" 
      "    BLLT    sub_FF815F50 \n" 
      "    BL      sub_FF81A230 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFF815FB0 \n" 
      "    BLLT    sub_FF815F50 \n" 
      "    BL      sub_FF811680 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xFF815FBC \n" 
      "    BLLT    sub_FF815F50 \n" 
      "    LDMFD   SP!, {R4,LR} \n" 
     // "    B       sub_FF8205BC \n"
     "B       taskcreate_Startup_my\n" //---------->
        );
}; 



void __attribute__((naked,noinline)) taskcreate_Startup_my() {  // @ 0xFF8205BC
	asm volatile (	
      "    STMFD   SP!, {R3,LR} \n" 
      "    BL      sub_FF833A78 \n" 
      "    BL      sub_FF83B07C \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF8205F8 \n" 
      "    BL      sub_FF83526C \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FF8205F8 \n" 
      "    BL      sub_FF833A74 \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF8205F8 \n" 
      "    LDR     R1, =0xC0220000 \n" 
      "    MOV     R0, #0x44 \n" 
      "    STR     R0, [R1, #0x48] \n" 
"loc_FF8205F4:\n"
      "    B       loc_FF8205F4 \n" 
"loc_FF8205F8:\n"
        //"BL      sub_FF833A80\n" // removed, see boot() function
      "    BL      sub_FF833A7C \n" 
      "    BL      sub_FF8394A0 \n" 
      "    LDR     R1, =0x34E000 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_FF8396E8 \n" 
      "    BL      sub_FF839694 \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
      //"    LDR     R3, =0xFF820560 \n" 
      "    LDR     R3, =task_Startup_my\n" //+ ----------->
      "    MOV     R2, #0 \n" 
      "    MOV     R1, #0x19 \n" 
      "    LDR     R0, =0xFF820640 \n" 
      "    BL      sub_FF81F110 \n" 
      "    MOV     R0, #0 \n" 
      "    LDMFD   SP!, {R12,PC} \n" 
 );
}; 

void __attribute__((naked,noinline)) task_Startup_my() { // orig @ 0xFF820560
       	asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    BL      sub_FF816228 \n" 
      "    BL      sub_FF834B7C \n" 
      "    BL      sub_FF833414 \n" 
      "    BL      sub_FF83B0BC \n" 
      "    BL      sub_FF83B2A8 \n" 
      //"    BL      sub_FF83B150 \n"  // Skip starting diskboot.bin again
      "    BL      sub_FF83B444 \n" 
      "    BL      sub_FF83B2D8 \n" 
      "    BL      sub_FF838938 \n" 
      "    BL      sub_FF83B448 \n" 
      //"    BL      sub_FF833968 \n"
	);		 
	CreateTask_PhySw(); // +
	CreateTask_spytask();  // +
    asm volatile (	
      "    BL      sub_FF836EA8 \n" 
      "    BL      sub_FF83B460 \n" 
      "    BL      sub_FF8322BC \n" 
      "    BL      sub_FF832E6C \n" 
      "    BL      sub_FF83AE54 \n" 
      "    BL      sub_FF8333C8 \n" 
      "    BL      sub_FF832E08 \n" 
      "    BL      sub_FF83BF04 \n" 
      "    BL      sub_FF832DE0 \n" 
      "    LDMFD   SP!, {R4,LR} \n" 
      "    B       sub_FF816128 \n" 
	);
}; 

void CreateTask_spytask() { 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

void __attribute__((naked,noinline)) CreateTask_PhySw() { // orig @ 0xFF833968
       	asm volatile ( 
      "    STMFD   SP!, {R3-R5,LR} \n" 
      "    LDR     R4, =0x1BE4 \n" 
      "    LDR     R0, [R4, #0x10] \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF83399C \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
     // "    LDR     R3, =0xFF833934 \n" 
     // "    MOV     R2, #0x800 \n" 
        "LDR     R3, =mykbd_task\n"  // task_phySw
	"MOV     R2, #0x2000\n"		// greater Stacksize

      "    MOV     R1, #0x17 \n" 
      "    LDR     R0, =0xFF833B70 \n" 
      "    BL      sub_FF81F3E8 \n" 
      "    STR     R0, [R4, #0x10] \n" 
"loc_FF83399C:\n"
      "    BL      sub_FF87C45C \n" 
      "    BL      sub_FF8351E4 \n" 
      "    CMP     R0, #0 \n" 
      "    LDREQ   R1, =0x30120 \n" 
      "    LDMEQFD SP!, {R3-R5,LR} \n" 
      "    BEQ     sub_FF87C3E4 \n" 
      "    LDMFD   SP!, {R3-R5,PC} \n" 

	);
};

void __attribute__((naked,noinline)) init_file_modules_task() { // @ff886470
  asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n" 
      "    BL      sub_FF87E928 \n" 
      "    LDR     R5, =0x5006 \n" 
      "    MOVS    R4, R0 \n" 
      "    MOVNE   R1, #0 \n" 
      "    MOVNE   R0, R5 \n" 
      "    BLNE    sub_FF8822A8 \n" 
      //"    BL      sub_FF87E9A4 \n" 
        "BL      sub_FF87E954_my\n"
  		"BL      core_spytask_can_start\n"      // +

      "    CMP     R4, #0 \n" 
      "    MOVEQ   R0, R5 \n" 
      "    LDMEQFD SP!, {R4-R6,LR} \n" 
      "    MOVEQ   R1, #0 \n" 
      "    BEQ     sub_FF8822A8 \n" 
      "    LDMFD   SP!, {R4-R6,PC} \n" 
 );
}; 

void __attribute__((naked,noinline)) sub_FF87E954_my() { 
 asm volatile (

      "    STMFD   SP!, {R4,LR} \n" 
      "    MOV     R0, #3 \n" 
      //"    BL      sub_FF862D04 \n" 
      "    BL      sub_FF862D04_my \n" 

      "    BL      sub_FF916C14 \n" 
      "    LDR     R4, =0x2B9C \n" 
      "    LDR     R0, [R4, #4] \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF87E98C \n" 
      "    BL      sub_FF861F4C \n" 
      "    BL      sub_FF90B6CC \n" 
      "    BL      sub_FF861F4C \n" 
      "    BL      sub_FF85E370 \n" 
      "    BL      sub_FF861E4C \n" 
      "    BL      sub_FF90B768 \n" 
"loc_FF87E98C:\n"
      "    MOV     R0, #1 \n" 
      "    STR     R0, [R4] \n" 
      "    LDMFD   SP!, {R4,PC} \n" 
 );
}; 


void __attribute__((naked,noinline)) sub_FF862D04_my() {
 asm volatile (
      "    STMFD   SP!, {R4-R8,LR} \n" 
      "    MOV     R8, R0 \n" 
      "    BL      sub_FF862C84 \n" 
      "    LDR     R1, =0x348F0 \n" 
      "    MOV     R6, R0 \n" 
      "    ADD     R4, R1, R0, LSL #7 \n" 
      "    LDR     R0, [R4, #0x6C] \n" 
      "    CMP     R0, #4 \n" 
      "    LDREQ   R1, =0x83F \n" 
      "    LDREQ   R0, =0xFF8627C4 \n" 
      "    BLEQ    sub_FF81F5E8 \n" 
      "    MOV     R1, R8 \n" 
      "    MOV     R0, R6 \n" 
      "    BL      sub_FF86253C \n" 
      "    LDR     R0, [R4, #0x38] \n" 
      "    BL      sub_FF8633A4 \n" 
      "    CMP     R0, #0 \n" 
      "    STREQ   R0, [R4, #0x6C] \n" 
      "    MOV     R0, R6 \n" 
      "    BL      sub_FF8625CC \n" 
      "    MOV     R0, R6 \n" 
      //"    BL      sub_FF86292C \n" 
      "    BL      sub_FF86292C_my \n" 
      "    MOV     R5, R0 \n" 
      "    MOV     R0, R6 \n" 
      "    BL      sub_FF862B5C \n" 
      "    LDR     R6, [R4, #0x3C] \n" 
      "    AND     R7, R5, R0 \n" 
      "    CMP     R6, #0 \n" 
      "    LDR     R1, [R4, #0x38] \n" 
      "    MOVEQ   R0, #0x80000001 \n" 
      "    MOV     R5, #0 \n" 
      "    BEQ     loc_FF862DB4 \n" 
      "    MOV     R0, R1 \n" 
      "    BL      sub_FF8620B4 \n" 
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
"loc_FF862DB4:\n"
      "    CMP     R8, #7 \n" 
      "    STR     R0, [R4, #0x40] \n" 
      "    LDMNEFD SP!, {R4-R8,PC} \n" 
      "    MOV     R0, R8 \n" 
      "    BL      sub_FF862CD4 \n" 
      "    CMP     R0, #0 \n" 
      "    LDMEQFD SP!, {R4-R8,LR} \n" 
      "    LDREQ   R0, =0xFF862E00 \n" 
      "    BEQ     sub_FF811780 \n" 
      "    LDMFD   SP!, {R4-R8,PC} \n" 
 );
}; 

void __attribute__((naked,noinline)) sub_FF86292C_my() {

 asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n" 
      "    MOV     R5, R0 \n" 
      "    LDR     R0, =0x348F0 \n" 
      "    ADD     R4, R0, R5, LSL #7 \n" 
      "    LDR     R0, [R4, #0x6C] \n" 
      "    TST     R0, #2 \n" 
      "    MOVNE   R0, #1 \n" 
      "    LDMNEFD SP!, {R4-R6,PC} \n" 
      "    LDR     R0, [R4, #0x38] \n" 
      "    MOV     R1, R5 \n" 
      //"    BL      sub_FF86264C \n" 
      "    BL      sub_FF86264C_my \n" 
      "    CMP     R0, #0 \n" 
      "    LDRNE   R0, [R4, #0x38] \n" 
      "    MOVNE   R1, R5 \n" 
      "    BLNE    sub_FF8627E8 \n" 
      "    LDR     R2, =0x34970 \n" 
      "    ADD     R1, R5, R5, LSL #4 \n" 
      "    LDR     R1, [R2, R1, LSL #2] \n" 
      "    CMP     R1, #4 \n" 
      "    BEQ     loc_FF86298C \n" 
      "    CMP     R0, #0 \n" 
      "    LDMEQFD SP!, {R4-R6,PC} \n" 
      "    MOV     R0, R5 \n" 
      "    BL      sub_FF862144 \n" 
"loc_FF86298C:\n"
      "    CMP     R0, #0 \n" 
      "    LDRNE   R1, [R4, #0x6C] \n" 
      "    ORRNE   R1, R1, #2 \n" 
      "    STRNE   R1, [R4, #0x6C] \n" 
      "    LDMFD   SP!, {R4-R6,PC} \n" 
 );
};


void __attribute__((naked,noinline)) sub_FF86264C_my() {
 asm volatile (	
      "    STMFD   SP!, {R4-R10,LR} \n" 
      "    MOV     R9, R0 \n" 
      "    LDR     R0, =0x348F0 \n" 
      "    MOV     R8, #0 \n" 
      "    ADD     R5, R0, R1, LSL #7 \n" 
      "    LDR     R0, [R5, #0x3C] \n" 
      "    MOV     R7, #0 \n" 
      "    CMP     R0, #7 \n" 
      "    MOV     R6, #0 \n" 
      "    ADDLS   PC, PC, R0, LSL #2 \n" 
      "    B       loc_FF8627A4 \n" 
      "    B       loc_FF8626B0 \n" 
      "    B       loc_FF862698 \n" 
      "    B       loc_FF862698 \n" 
      "    B       loc_FF862698 \n" 
      "    B       loc_FF862698 \n" 
      "    B       loc_FF86279C \n" 
      "    B       loc_FF862698 \n" 
      "    B       loc_FF862698 \n" 
"loc_FF862698:\n"
      "    MOV     R2, #0 \n" 
      "    MOV     R1, #0x200 \n" 
      "    MOV     R0, #2 \n" 
      "    BL      sub_FF878B54 \n" 
      "    MOVS    R4, R0 \n" 
      "    BNE     loc_FF8626B8 \n" 
"loc_FF8626B0:\n"
      "    MOV     R0, #0 \n" 
      "    LDMFD   SP!, {R4-R10,PC} \n" 
"loc_FF8626B8:\n"
      "    LDR     R12, [R5, #0x50] \n" 
      "    MOV     R3, R4 \n" 
      "    MOV     R2, #1 \n" 
      "    MOV     R1, #0 \n" 
      "    MOV     R0, R9 \n" 
      "    BLX     R12 \n" 
      "    CMP     R0, #1 \n" 
      "    BNE     loc_FF8626E4 \n" 
      "    MOV     R0, #2 \n" 
      "    BL      sub_FF878CA0 \n" 
      "    B       loc_FF8626B0 \n" 
"loc_FF8626E4:\n"
      "    LDR     R1, [R5, #0x64] \n" 
      "    MOV     R0, R9 \n" 
      "    BLX     R1 \n" 
		
               "MOV   R1, R4\n"           //  pointer to MBR in R1
// 				"BL    mbr_read_dryos\n"   //  total sectors count in R0 before and after call

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

      "    LDRB    R1, [R4, #0x1C9] \n" 
      "    LDRB    R3, [R4, #0x1C8] \n" 
      "    LDRB    R12, [R4, #0x1CC] \n" 
      "    MOV     R1, R1, LSL #0x18 \n" 
      "    ORR     R1, R1, R3, LSL #0x10 \n" 
      "    LDRB    R3, [R4, #0x1C7] \n" 
      "    LDRB    R2, [R4, #0x1BE] \n" 
        //"LDRB    LR, [R4,#0x1FF]\n" // replaced, see below
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
        //"LDRB    R12, [R4,#0x1FE]\n" // replaced, see below
        "LDRB    R12, [LR,#0x1FE]\n"        // New! First MBR signature byte (0x55)
        "LDRB    LR, [LR,#0x1FF]\n"         //      Last MBR signature byte (0xAA)	
      "    BNE     loc_FF862770 \n" 
      "    CMP     R0, R1 \n" 
      "    BCC     loc_FF862770 \n" 
      "    ADD     R2, R1, R3 \n" 
      "    CMP     R2, R0 \n" 
      "    CMPLS   R12, #0x55 \n" 
      "    CMPEQ   LR, #0xAA \n" 
      "    MOVEQ   R7, R1 \n" 
      "    MOVEQ   R6, R3 \n" 
      "    MOVEQ   R4, #1 \n" 
      "    BEQ     loc_FF862774 \n" 
"loc_FF862770:\n"
      "    MOV     R4, R8 \n" 
"loc_FF862774:\n"
      "    MOV     R0, #2 \n" 
      "    BL      sub_FF878CA0 \n" 
      "    CMP     R4, #0 \n" 
      "    BNE     loc_FF8627B0 \n" 
      "    LDR     R1, [R5, #0x64] \n" 
      "    MOV     R7, #0 \n" 
      "    MOV     R0, R9 \n" 
      "    BLX     R1 \n" 
      "    MOV     R6, R0 \n" 
      "    B       loc_FF8627B0 \n" 
"loc_FF86279C:\n"
      "    MOV     R6, #0x40 \n" 
      "    B       loc_FF8627B0 \n" 
"loc_FF8627A4:\n"
      "    LDR     R1, =0x597 \n" 
      "    LDR     R0, =0xFF8627C4 \n" 
      "    BL      sub_FF81F5E8 \n" 
"loc_FF8627B0:\n"
      "    STR     R7, [R5, #0x44]! \n" 
      "    STMIB   R5, {R6,R8} \n" 
      "    MOV     R0, #1 \n" 
      "    LDMFD   SP!, {R4-R10,PC} \n" 

 );
}; 

