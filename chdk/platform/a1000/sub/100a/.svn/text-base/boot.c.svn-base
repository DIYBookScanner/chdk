#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Our stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_blinker();
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();
void __attribute__((naked,noinline)) task_blinker();
extern void __attribute__((naked,noinline)) task_CaptSeqTask_my();
void dump_chdk();

////////////////////////////////////////////////////////////////////////////////
// Note to developers:
// The code below is just somewhat annotated in an attempt to figure out what
// the camera does. I left it in, it might be of some use to someone someday.
// Occasionally, I added the .ltorg directive, because the compiler/assembler
// isn't smart enough to place it somewhere sensible. Remember to bypass
// (B new_location) that directive if you really *MUST* place it in the middle
// of your code.
////////////////////////////////////////////////////////////////////////////////


void boot() {
//  long *canon_data_src = (void*)0xFFEEAFD0;
    long *canon_data_src = (void*)0xFFEEAFD0;		//** different than 1.00b
	
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xdf7c - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xdf7c; // just after data 
    long canon_bss_len = 0xd4ec8 - 0xdf7c; 

    long i;

    // Code taken from VxWorks CHDK. Changes CPU speed?
    asm volatile (

	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

    asm volatile ("B      sub_FFC001A4_my\n");
};

void __attribute__((naked,noinline)) sub_FFC001A4_my() {
     asm volatile (
		     "LDR     R0, =0xFFC0021C\n"
		     "MOV     R1, #0\n"
		     "LDR     R3, =0xFFC00254\n"
		     
	"loc_FFC001B0:\n"
		     "CMP     R0, R3\n"
		     "LDRCC   R2, [R0],#4\n"
		     "STRCC   R2, [R1],#4\n"
		     "BCC     loc_FFC001B0\n"
		     "LDR     R0, =0xFFC00254\n"
		     "MOV     R1, #0x4B0\n"
		     "LDR     R3, =0xFFC00468\n"
		     
	"loc_FFC001CC:\n"
		     "CMP     R0, R3\n"
		     "LDRCC   R2, [R0],#4\n"
		     "STRCC   R2, [R1],#4\n"
		     "BCC     loc_FFC001CC\n"
		     "MOV     R0, #0xD2\n"
		     "MSR     CPSR_cxsf, R0\n"
		     "MOV     SP, #0x1000\n"
		     "MOV     R0, #0xD3\n"
		     "MSR     CPSR_cxsf, R0\n"
		     "MOV     SP, #0x1000\n"
		     "LDR     R0, =0x6C4\n"
		     "LDR     R2, =0xEEEEEEEE\n"
		     "MOV     R3, #0x1000\n"
		     
	"loc_FFC00200:\n"
		     "CMP     R0, R3\n"
		     "STRCC   R2, [R0],#4\n"
		     "BCC     loc_FFC00200\n"
		     "BL      sub_FFC00F98_my\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC00F98_my() {
 
        asm volatile (
		     "STR     LR, [SP,#-0x4]!\n"
		     "SUB     SP, SP, #0x74\n"
		     "MOV     R0, SP\n"
		     "MOV     R1, #0x74\n"
		     "BL      sub_FFE71838\n"
		     "MOV     R0, #0x53000\n"
		     "STR     R0, [SP,#0x74-0x70]\n"
	);
	asm volatile (
       		     "LDR     R0, =new_sa\n"
              	     "LDR     R0, [R0]\n"
        );

	asm volatile (
		     "LDR     R2, =0x279C00\n"
		     "LDR     R1, =0x2724A8\n"
		     "STR     R0, [SP,#0x74-0x6C]\n"
		     "SUB     R0, R1, R0\n"
		     "ADD     R3, SP, #0x74-0x68\n"
		     "STR     R2, [SP,#0x74-0x74]\n"
		     "STMIA   R3, {R0-R2}\n"
		     "MOV     R0, #0x22\n"
		     "STR     R0, [SP,#0x74-0x5C]\n"
		     "MOV     R0, #0x68\n"
		     "STR     R0, [SP,#0x74-0x58]\n"
		     "LDR     R0, =0x19B\n"
		     "LDR     R1, =sub_FFC04D90_my\n"
		     "STR     R0, [SP,#0x74-0x54]\n"
		     "MOV     R0, #0x96\n"
		     "STR     R0, [SP,#0x74-0x50]\n"
		     "MOV     R0, #0x78\n"
		     "STR     R0, [SP,#0x74-0x4C]\n"
		     "MOV     R0, #0x64\n"
		     "STR     R0, [SP,#0x74-0x48]\n"
		     "MOV     R0, #0\n"
		     "STR     R0, [SP,#0x74-0x44]\n"
		     "STR     R0, [SP,#0x74-0x40]\n"
		     "MOV     R0, #0x10\n"
		     "STR     R0, [SP,#0x74-0x18]\n"
		     "MOV     R0, #0x800\n"
		     "STR     R0, [SP,#0x74-0x14]\n"
		     "MOV     R0, #0xA0\n"
		     "STR     R0, [SP,#0x74-0x10]\n"
		     "MOV     R0, #0x280\n"
		     "STR     R0, [SP,#0x74-0xC]\n"
		     "MOV     R0, SP\n"
		     "MOV     R2, #0\n"
		     "BL      sub_FFC02D3C\n"
		     "ADD     SP, SP, #0x74\n"
		     "LDR     PC, [SP],#4\n"
     );
}


void __attribute__((naked,noinline)) sub_FFC04D90_my() {
        asm volatile (

              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FFC00944\n"
              "BL      sub_FFC09708\n"           // _dmSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EA4\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "BL      sub_FFC049B8\n"           // termDriverInit
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EAC\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "LDR     R0, =0xFFC04EBC\n"
              "BL      sub_FFC04AA0\n"           // termDeviceCreate
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EC4\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "LDR     R0, =0xFFC04EBC\n"
              "BL      sub_FFC0354C\n"           // stdioSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04ED8\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "BL      sub_FFC09290\n"           // stdlibSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EE4\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "BL      sub_FFC0147C\n"           // armlib_setup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EF0\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "LDMFD   SP!, {R4,LR}\n"
              //"B       sub_FFC0D9F0\n"         // CreateTaskStartup
              "B       sub_FFC0CD6C_my\n"        // +---------------------> Hook
        );
};

void __attribute__((naked,noinline)) sub_FFC0CD6C_my() {
     asm volatile (
          "STMFD   SP!, {R3,LR}\n"
	  "BL	   sub_FFC11198\n"
          "BL      sub_FFC18AE0\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC0CDA0\n"
          "BL      sub_FFC11194\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC0CDA0\n"
//	      "LDR	   R1, =0xC0022000\n"
          "LDR	R1, =0xC0220000 \n"       //** different than 1.00b     	  
          "MOV     R0, #0x44\n"
          "STR     R0, [R1,#0xA4]\n"
          "STR     R0, [R1,#0xA0]\n"

     "loc_FFC0CD9C:\n"
          "B       loc_FFC0CD9C\n"

     "loc_FFC0CDA0:\n"
          "BL      sub_FFC111A0\n"
	  "BL	   sub_FFC1119C\n"
          "BL      sub_FFC16E70\n"
          "LDR     R1, =0x2CE000\n"
          "MOV     R0, #0\n"
          "BL      sub_FFC170B8\n"
          "BL      sub_FFC17064\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP]\n"
          "LDR     R3, =sub_FFC0CD10_my\n"       // +---------------------> Hook
          "MOV     R2, #0\n"
          "MOV     R1, #0x19\n"
          "LDR     R0, =0xFFC0CDE8\n"
          "BL      sub_FFC0B8C0\n"               // CreateTask
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R12,PC}\n"
     ".ltorg\n"
     );
}
void __attribute__((naked,noinline)) sub_FFC0CD10_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FFC0515C\n"
          "BL      sub_FFC12304\n"
          "BL      sub_FFC10BE0\n"
	  "BL	   sub_FFC18B20\n"
          "BL      sub_FFC18CE8\n"
     );
     
     CreateTask_spytask();
     
     asm volatile (
          //"BL      sub_FFC18BA8\n"
          "BL      sub_FFC18EA0\n"
          "BL      sub_FFC18D38\n"
          "BL      sub_FFC16164\n"
	  "BL	   sub_FFC18EA4\n"
     );

     CreateTask_PhySw();
     //CreateTask_blinker();

     asm volatile (
	  //"BL	   sub_FFC11094\n"
          "BL      sub_FFC141EC_my\n"            // +---------------------> Hook (in capt_seq.c)
          //"BL      sub_FFC141EC\n"            // +---------------------> Hook (in capt_seq.c)
          "BL      sub_FFC18EBC\n"
	  "BL	   sub_FFC0FC08\n"
          "BL      sub_FFC10530\n"
          "BL      sub_FFC188C0\n"
          "BL      sub_FFC10B90\n"
          "BL      sub_FFC1044C\n"
          "BL      sub_FFC19944_my\n"            // +---> MAJOR HOOK (SDHC boot)
          "BL      sub_FFC10424\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FFC0505C\n"
     ".ltorg\n"
     );
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


void CreateTask_PhySw() {
        _CreateTask("PhySw", 0x2, 0x800, mykbd_task, 0);
};

void __attribute__((naked,noinline)) sub_FFC141EC_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "LDR     R4, =0x1BF8\n"
          "MOV     R0, #0\n"
          "MOV     R1, #4\n"
          "STR     R0, [R4,#0xC]\n"
          "BL      sub_FFC0BBF0\n"
          "STR     R0, [R4, #4]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #1\n"
          "BL      sub_FFC0BC14\n"
          "STR     R0, [R4,#8]\n"
	  "BL	   sub_FFC4EC00\n"
          "BL      sub_FFC4FC40\n"
          "BL      sub_FFC4DD20\n"
          "BL      sub_FFC4A028_my\n"               // Taskcreate_captseqtask called from this one
          "BL      sub_FFC4EECC\n"
//        "LDR     R0, [R4]\n"
          "LDR	R0, [R4, #4] \n"    	//** different than 1.00b  		  
          "LDMFD   SP!, {R4,LR}\n"
          "MOV     R1, #0x1000\n"
          "B       sub_FFC166AC\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC4A028_my() {
     asm volatile (
		     "STMFD   SP!, {R4,LR}\n"
		     "LDR     R4, =0x515C\n"
		     "LDR     R0, [R4]\n"
		     "CMP     R0, #0\n"
		     "BNE     loc_FFC4A094\n"
		     "BL      sub_FFC4D0E4\n"
		     "MOV     R1, #1\n"
		     "MOV     R0, #0\n"
		     "BL      sub_FFC0BC14\n"
		     "STR     R0, [R4,#8]\n"
		     "MOV     R0, #0\n"
		     "MOV     R1, #0\n"
		     "BL      sub_FFC0BBF0\n"
		     "STR     R0, [R4,#0xC]\n"
		     "BL      sub_FFC4A38C\n"
		     "BL      sub_FFC4A8E4\n"
		     "MOV     R0, #0\n"
		     "STR     R0, [R4,#4]\n"
		     "ADD     R0, R4, #0x10\n"
		     "MOV     R1, #0\n"
		     "STR     R1, [R0],#4\n"
		     "STR     R1, [R0]\n"
		     "BL      sub_FFC4AA74\n"
		     "BL      sub_FFC4F07C\n"
		     "BL      sub_FFC4D444\n"
		     "BL      sub_FFC4B46C_my\n"
		     "BL      sub_FFC4C344\n"
		     
	"loc_FFC4A094:\n"
		     "MOV     R0, #1\n"
		     "STR     R0, [R4]\n"
		     "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC4B46C_my() {
     asm volatile (
		     "STMFD   SP!, {R3-R5,LR}\n"
		     "LDR     R2, =0x18C1C\n"
		     "MOV     R0, #0\n"
		     "MOV     R1, #0\n"
	"loc_FFC4B47C:\n"
		     "ADD     R3, R2, R0,LSL#4\n"
		     "ADD     R0, R0, #1\n"
		     "CMP     R0, #5\n"
		     "STR     R1, [R3,#8]\n"
		     "BCC     loc_FFC4B47C\n"
		     "BL      sub_FFC4BEA8\n"
		     "BL      sub_FFD0CE1C\n"
		     "MOV     R1, #5\n"
		     "MOV     R0, #0\n"
		     "BL      sub_FFC0BBCC\n"
		     "LDR     R4, =0x5190\n"
		     "LDR     R1, =0x101DFF\n"
		     "STR     R0, [R4,#8]\n"
		     "MOV     R0, #0\n"
		     "BL      sub_FFC0BBF0\n"
		     "STR     R0, [R4,#4]\n"
		     "MOV     R0, #0\n"
		     "MOV     R1, #1\n"
		     "BL      sub_FFC0BC14\n"
		     "STR     R0, [R4,#0xC]\n"
		     "MOV     R3, #0\n"
		     "STR     R3, [SP]\n"
		     "LDR     R3, =task_CaptSeqTask_my\n"
		     "LDR     R0, =0xFFC4B6A8\n"
		     "MOV     R2, #0x1000\n"
		     "MOV     R1, #0x17\n"
		     "BL      sub_FFC0BB98\n"
		     "LDMFD   SP!, {R3-R5,PC}\n"

     );
}


/////////////////////////////////////////////////////////////////////////////////////
// Major SDHC boot fix hook starts here
//
// Paths that certainly do not (by itself) get the SDHC booting going:
// sub_FFC1E570 -> sub_FFC14D18 -> sub_FFC14A60 -> sub_FFC6BF78 (entire 'right subtree')
// sub_FFC1E570 -> sub_FFC1E120 -> sub_FFC6AC88 -> sub_FFC6A340 -> sub_FFC6BF78 (shortest path (subroutine-count-wise) through 'left subtree')
// sub_FFC1E570 -> sub_FFC1E120 -> sub_FFC6AC88 -> sub_FFC6A80C -> sub_FFC6A340 -> sub_FFC6BF78 (sub_FFC6A80C does not appear to be called)
// 
// Unexplored:
// sub_FFC1E570 -> sub_FFC1E120 -> sub_FFC6BD48 -> sub_FFC6BB94 -> sub_FFC6AC88 ->              -> sub_FFC6A340 -> sub_FFC6BF78
//                                                                              -> sub_FFC6A80C ->
//
// Final, working path:
// sub_FFC1E570 -> sub_FFC1E120 -> sub_FFC6BD48 -> sub_FFC6BB94 -> sub_FFC6AC88 -> sub_FFC6A340 -> sub_FFC6BF78
//
// That's the 'tree'-part, the rest of the subroutines are just straight on down, no junctions.
// -> sub_FFC6BF28 -> sub_FFC64FDC -> sub_FFC46910 -> sub_FFC4674C -> sub_FFC465E4
/////////////////////////////////////////////////////////////////////////////////////

void __attribute__((naked,noinline)) sub_FFC19944_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FFC5D7AC\n"
          "BL      sub_FFC34778\n"
          "CMP     R0, #1\n"
          "BNE     loc_FFC19964\n"
          "BL      sub_FFC607DC\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FFC34804\n"

     "loc_FFC19964:\n"
          "BL      sub_FFC5F974\n"
          "LDR     R4, =0x1D10\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "LDMNEFD SP!, {R4,PC}\n"
          "MOV     R1, #0\n"
          "LDR     R0, =sub_FFC194A0_my\n"       // +----> Hook for SDHC booting
          "BL      sub_FFC5BC6C\n"
          "STR     R0, [R4,#4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC194A0_my() {
     asm volatile (
          "STMFD   SP!, {R3-R11,LR}\n"
          "LDR     R6, =0x1D10\n"
          "MOV     R5, R1\n"
          "LDR     R0, [R6,#0x14]\n"
          "MOV     R4, R3\n"
          "CMP     R0, #1\n"
          "BNE     loc_FFC194C4\n"
          "BL      sub_FFC5E014\n"
          "B       loc_FFC1954C\n"

     "loc_FFC194C4:\n"
          "LDR     R10, =0x1167\n"
          "MOV     R7, #0\n"
          "CMP     R5, R10\n"
          "MOV     R8, #1\n"
	  "ADD	   R9, R10, #1\n"
          "BEQ     loc_FFC1980C\n"
          "BGT     loc_FFC19610\n"
          "LDR     R12, =0x10AD\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FFC198AC\n"
          "BGT     loc_FFC19594\n"
	  "LDR	   R12, =0x1003\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FFC19890\n"
          "BGT     loc_FFC19554\n"
          "SUB     R12, R5, #0x800\n"
          "SUBS    R12, R12, #3\n"
          "BEQ     loc_FFC19724\n"
          "SUB     R12, R5, #0x800\n"
          "SUBS    R12, R12, #0x158\n"
          "BEQ     loc_FFC19928\n"
          "LDR     R4, =0x9A3\n"
          "CMP     R5, R4\n"
	  "SUBNE   R12, R5, #0x900\n"
	  "SUBNES  R12, R12, #0xA5\n"
          "BNE     loc_FFC196F0\n"
          "LDR     R0, [R6,#0xC]\n"
          "SUB     R12, R0, #0x8000\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FFC1954C\n"
          "LDR     R0, =0x10A5\n"
          "BL      sub_FFC5CADC\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FFC1986C\n"

     "loc_FFC1954C:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FFC19554:\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0x5\n"
          "BEQ     loc_FFC1958C\n"
          "SUB     R12, R5, #0x1000\n"
          "LDR     R0, =0x10A3\n"
          "SUBS    R12, R12, #0xA9\n"
          "BEQ     loc_FFC198A0\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAA\n"
          "BNE     loc_FFC196F0\n"
          "BL      sub_FFC5CADC\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC1954C\n"

     "loc_FFC19588:\n"
          "BL      sub_FFC19D20\n"

     "loc_FFC1958C:\n"
          "MOV     R1, R4\n"
          "B       loc_FFC19878\n"

     "loc_FFC19594:\n"
     	"LDR     R12, =0x10B2\n"
	"CMP     R5, R12\n"
	"LDREQ   R0, =0x1008\n"
	"MOVEQ   R1, R4\n"
	"BEQ     loc_FFC19898\n"
	"BGT     loc_FFC195D4\n"
	"SUB     R12, R5, #0x1000\n"
	"SUBS    R12, R12, #0xAE\n"
	"BEQ     loc_FFC19588\n"
	"SUB     R12, R5, #0x1000\n"
	"SUBS    R12, R12, #0xAF\n"
	"BEQ     loc_FFC198AC\n"
	"SUB     R12, R5, #0x1000\n"
	"SUBS    R12, R12, #0xB0\n"
	"BEQ     loc_FFC19588\n"
	"B       loc_FFC196F0\n"

      "loc_FFC195D4:\n"
	"SUB     R12, R5, #0x1100\n"
	"SUBS    R12, R12, #0x62\n"
	"BEQ     loc_FFC19880\n"
	"SUB     R12, R5, #0x1100\n"
	"SUBS    R12, R12, #0x63\n"
	"MOVEQ   R1, #0\n"
	"MOVEQ   R0, #0x82\n"
	"BEQ     loc_FFC19608\n"
	"SUB     R12, R5, #0x1100\n"
	"SUBS    R12, R12, #0x65\n"
	"BNE     loc_FFC196F0\n"
	"MOV     R1, #0\n"
	"MOV     R0, #0x83\n"

      "loc_FFC19608:\n"
	"BL      sub_FFC61E54\n"
	"B       loc_FFC1954C\n"

      "loc_FFC19610:\n"
	"LDR     R11, =0x201B\n"
	"LDR     R0, =0x1D10\n"
	"ADD     R12, R11, #2\n"
	"LDR     R1, [R0,#0x20]\n"
	"CMP     R5, R12\n"
	"SUB     R10, R11, #0x17\n"
	"BEQ     loc_FFC198F4\n"
	"BGT     loc_FFC1969C\n"
	"CMP     R5, R10\n"
	"MOV     R0, R10\n"
	"BEQ     loc_FFC19900\n"
	"BGT     loc_FFC19664\n"
	"CMP     R5, R9\n"
	"BEQ     loc_FFC1980C\n"
	"LDR     R8, =0x116A\n"
	"CMP     R5, R8\n"
	"BEQ     loc_FFC19858\n"
	"SUB     R12, R5, #0x2000\n"
	"SUBS    R12, R12, #2\n"
	"BNE     loc_FFC196F0\n"
	"B       loc_FFC198F4\n"

      "loc_FFC19664:\n"
	"SUB     R12, R5, #0x2000\n"
	"SUBS    R12, R12, #5\n"
	"BEQ     loc_FFC198F4\n"
	"LDR     R2, =0x1D10\n"
	"SUB     R12, R5, #0x2000\n"
	"LDR     R2, [R2,#0x10]\n"
	"SUBS    R12, R12, #0x19\n"
	"BEQ     loc_FFC198D8\n"
	"CMP     R5, R11\n"
	"BNE     loc_FFC196F0\n"
	"CMP     R2, #1\n"
	"BNE     loc_FFC1958C\n"
	"BL      sub_FFC5E048\n"
	"B       loc_FFC1954C\n"

      "loc_FFC1969C:\n"
	"LDR     R12, =0x3111\n"
	"CMP     R5, R12\n"
	"BEQ     loc_FFC1958C\n"
	"BGT     loc_FFC196D0\n"
	"LDR     R0, =0x2027\n"
	"CMP     R5, R0\n"
	"BEQ     loc_FFC198B8\n"
	"SUB     R12, R5, #0x3000\n"
	"SUBS    R12, R12, #6\n"
	"SUBNE   R12, R5, #0x3000\n"
	"SUBNES  R12, R12, #0x110\n"
	"BEQ     loc_FFC1958C\n"
	"B       loc_FFC196F0\n"

      "loc_FFC196D0:\n"
	"CMP     R5, #0x3140\n"
	"BEQ     loc_FFC1991C\n"
	"SUB     R12, R5, #0x3200\n"
	"SUBS    R12, R12, #1\n"
	"BEQ     loc_FFC19874\n"
	"SUB     R12, R5, #0x3200\n"
	"SUBS    R12, R12, #2\n"
	"BEQ     loc_FFC1958C\n"

      "loc_FFC196F0:\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC19D50\n"
	"CMP     R0, #0\n"
	"BEQ     loc_FFC19874\n"
	"LDR     R0, =0x1061\n"
	"CMP     R5, R0\n"
	"BEQ     loc_FFC198E8\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC19D50\n"
	"CMP     R0, #0\n"
	"LDRNE   R0, =0x1065\n"
//	"MOV  R0, #-1\n"
    "MVNEQ	R0, #0 \n"       //** different than 1.00b     	
	"B       loc_FFC198E8\n"

      "loc_FFC19724:\n"
	"MOV     R4, #1\n"
	"MOV     R0, #2\n"
	"BL      sub_FFC5D840\n"
	"CMP     R0, #1\n"
	"MOVEQ   R4, #2\n"
	"MOV     R0, R4\n"
	"BL      sub_FFC107A4\n"
	"CMP     R0, #0\n"
	"STRNE   R8, [R6,#0x14]\n"
	"BNE     loc_FFC1977C\n"
	"BL      sub_FFC63488\n"
	"BL      sub_FFC611C0\n"
	"BL      sub_FFC61D7C\n"
	"BL      sub_FFC60A78\n"
	"BL      sub_FFC62398\n"
	"CMP     R0, #0\n"
	"BEQ     loc_FFC197EC\n"
	"BL      sub_FFC19150\n"
	"BL      sub_FFC621F4\n"
	"MOV     R1, R0\n"
	"MOV     R0, R10\n"
	"BL      sub_FFC5C45C\n"

      "loc_FFC1977C:\n"
	"MOV     R0, R7\n"
	"LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FFC197EC:\n"
          "BL      sub_FFC1477C\n"
          "CMP     R0, #1\n"
          "LDRNE   R0, =0x310B\n"
          "LDREQ   R0, =0x310C\n"
          "MOV     R1, #0\n"
          "BL      sub_FFC5C45C\n"
          "BL      sub_FFC604A4_my\n"            // +----> Hook for SDHC booting
          "B       loc_FFC1977C\n"

      "loc_FFC1980C:\n"
	  "MOV     R1, #0\n"
          "MOV     R0, #0x53\n"
	  "STR     R8, [R6,#0x10]\n"
	  "BL      sub_FFC676C4\n"
	  "LDR     R0, [R6,#0x20]\n"
	  "LDR     R4, =0x4508\n"
	  "CMP     R0, #0\n"
	  "BEQ     loc_FFC19840\n"
	  "BL      sub_FFC5E048\n"
	  "B       loc_FFC1984C\n"


      "loc_FFC19834:\n"
	  "MOV     R0, R4\n"
	  "BL      sub_FFC48CA8\n"
	  "B       loc_FFC1954C\n"

      "loc_FFC19840:\n"
	  "BL      sub_FFC6143C\n"
	  "BL      sub_FFC613A0\n"
	  "BL      sub_FFC144A8\n"

       "loc_FFC1984C:\n"
	  "CMP     R5, R9\n"
	  "BNE     loc_FFC1954C\n"
	  "B       loc_FFC19834\n"

       "loc_FFC19858:\n"
	  "MOV     R0, #1\n"
	  "BL      sub_FFC5E174\n"
	  "LDR     R0, =0x1005\n"
	  "MOV     R1, R8\n"
	  "B       loc_FFC19898\n"
	"loc_FFC1986C:\n"
	  "CMP     R5, R4\n"
	  "STREQ   R8, [R6,#0x30]\n"
       "loc_FFC19874:\n"
	  "MOV     R1, #0\n"
       "loc_FFC19878:\n"
	  "MOV     R0, R5\n"
	  "B       loc_FFC19898\n"
	"loc_FFC19880:\n"
	  "BL      sub_FFC6559C\n"
	  "CMP     R0, #0\n"
	  "BLNE    sub_FFC643F0\n"
	  "B       loc_FFC1958C\n"
	"loc_FFC19890:\n"
	  "BL      sub_FFC19404\n"
	  "MOV     R1, R4\n"
	"loc_FFC19898:\n"
	  "BL      sub_FFC5F6C0_my\n"
	  "LDMFD   SP!, {R3-R11,PC}\n"
	"loc_FFC198A0:\n"
	  "BL      sub_FFC5CADC\n"
	  "CMP     R0, #0\n"
	  "BNE     loc_FFC1954C\n"
	"loc_FFC198AC:\n"
	  "MOV     R0, R5\n"
	  "BL      sub_FFC1921C\n"
	  "LDMFD   SP!, {R3-R11,PC}\n"
	"loc_FFC198B8:\n"
	  "MOV     R1, #0\n"
	  "BL      sub_FFC5F6C0_my\n"
	  "MOV     R1, #0\n"
	  "MOV     R0, R11\n"
	  "BL      sub_FFC5F6C0_my\n"
	  "MOV     R1, #0\n"
	  "MOV     R0, R10\n"
	  "B       loc_FFC198EC\n"
	"loc_FFC198D8:\n"
	  "CMP     R1, #0\n"
	  "BEQ     loc_FFC1954C\n"
	  "CMP     R2, #0\n"
	  "BNE     loc_FFC1954C\n"
	"loc_FFC198E8:\n"
	  "MOV     R1, #0\n"
	"loc_FFC198EC:\n"
	  "BL      sub_FFC5F6C0_my\n"
	  "B       loc_FFC1954C\n"
	"loc_FFC198F4:\n"
	  "STR     R7, [R6,#0x20]\n"
	  "BL      sub_FFC19B1C\n"
	  "B       loc_FFC1958C\n"
	"loc_FFC19900:\n"
	  "STR     R7, [R6,#0x20]\n"
	  "BL      sub_FFC19B1C\n"
	  "LDR     R0, [R6,#0x10]\n"
	  "CMP     R0, #1\n"
	  "BNE     loc_FFC1958C\n"
	  "BL      sub_FFC5E08C\n"
	  "B       loc_FFC1954C\n"
	"loc_FFC1991C:\n"
	  "CMP     R1, #0\n"
	  "BLEQ    sub_FFC19B1C\n"
	  "B       loc_FFC1954C\n"
	"loc_FFC19928:\n"
	  "TST     R4, #0x80000000\n"
	  "MOVNE   R0, #1\n"
	  "LDMNEFD SP!, {R3-R11,PC}\n"
	  "BL      sub_FFC668A4\n"
	  "CMP     R0, #0\n"
	  "BLEQ    sub_FFC16074\n"
	  "B       loc_FFC1954C\n"
     );
}
void __attribute__((naked,noinline)) sub_FFC604A4_my() {
     asm volatile (
		     "STMFD   SP!, {R4,LR}\n"
		     "BL      sub_FFC19ADC\n"
		     "MOV     R4, R0\n"
		     "BL      sub_FFC605C8\n"
		     "MOV     R0, R4\n"
		     "BL      sub_FFC60358\n"
		     "BL      sub_FFC19ADC\n"
		     "MOV     R4, R0\n"
		     "LDR     R0, =0x56AC\n"
		     "LDR     R0, [R0]\n"
		     "TST     R0, #1\n"
		     "TSTEQ   R0, #0x10\n"
		     "BEQ     loc_FFC604E4\n"
	"loc_FFC604D8:\n"
		     "MOV     R1, R4\n"
		     "MOV     R0, #2\n"
		     "B       loc_FFC60528\n"
	"loc_FFC604E4:\n"
		     "TST     R0, #0x40\n"
		     "BEQ     loc_FFC604F8\n"
	"loc_FFC604EC:\n"
		     "MOV     R1, R4\n"
		     "MOV     R0, #1\n"
		     "B       loc_FFC60528\n"
	"loc_FFC604F8:\n"
		     "TST     R0, #0x20\n"
		     "BEQ     loc_FFC60514\n"
		     "TST     R0, #0x4000\n"
		     "BNE     loc_FFC60514\n"
	"loc_FFC60508:\n"
		     "MOV     R1, R4\n"
		     "MOV     R0, #0\n"
		     "B       loc_FFC60528\n"
	"loc_FFC60514:\n"
		     "LDR     R1, =0x102\n"
		     "BICS    R1, R1, R0\n"
		     "BNE     loc_FFC60530\n"
		     "MOV     R1, R4\n"
		     "MOV     R0, #6\n"
	"loc_FFC60528:\n"
		     "LDMFD   SP!, {R4,LR}\n"
          	     "B       sub_FFC602F4_my\n"            // +----> Hook for SDHC booting
     "loc_FFC60530:\n"
          "TST     R0, #0x100\n"
          "BNE     loc_FFC604D8\n"
          "TST     R0, #0x4000\n"
          "TSTEQ   R0, #0x400\n"
          "BNE     loc_FFC604EC\n"
          "TST     R0, #0x200\n"
          "TSTEQ   R0, #2\n"
          "BNE     loc_FFC60508\n"
          "TST     R0, #0x40000\n"
          "BEQ     loc_FFC604D8\n"
          "TST     R0, #0x200000\n"
          "MOVEQ   R1, R4\n"
          "MOVEQ   R0, #1\n"
          "BLEQ    sub_FFC602F4_my\n"            // +----> Hook for SDHC booting
          "B       loc_FFC604D8\n"
     );
}


void __attribute__((naked,noinline)) sub_FFC602F4_my() {
     asm volatile (
		     "STMFD   SP!, {R4-R6,LR}\n"
		     "MOVS    R4, R0\n"
		     "MOV     R0, #1\n"
		     "MOV     R5, R1\n"
		     "BNE     loc_FFC60334\n"
		     "MOV     R1, #0\n"
		     "MOV     R0, #0\n"
		     "BL      sub_FFC5D7D0\n"
		     "BL      sub_FFC19ADC\n"
		     "SUB     R12, R0, #0x1000\n"
		     "SUBS    R12, R12, #0x5B\n"
		     "BNE     loc_FFC6032C\n"
		"loc_FFC60324:\n"
		     "BL      sub_FFC60228\n"
		     "B       loc_FFC6033C\n"
		"loc_FFC6032C:\n"
		     "BL      sub_FFC60288\n"
		     "B       loc_FFC6033C\n"
		"loc_FFC60334:\n"
		     "CMP     R4, #5\n"
		     "BEQ     loc_FFC60324\n"
		"loc_FFC6033C:\n"
		     "CMP     R0, #0\n"
		     "LDREQ   R5, =0x1162\n"
		     "MOVEQ   R4, #2\n"
		     "MOV     R0, R4\n"
		     "MOV     R1, R5\n"
		     "LDMFD   SP!, {R4-R6,LR}\n"
          "B       sub_FFC5F6C0_my\n"            // +----> Hook for SDHC booting
     );
}

void __attribute__((naked,noinline)) sub_FFC5F6C0_my() {
     asm volatile (
		     "STMFD   SP!, {R4-R8,LR}\n"
		     "MOV     R8, R1\n"
		     "MOV     R4, R0\n"
		     "BL      sub_FFC19B10\n"
		     "CMP     R0, #0\n"
		     "BNE     loc_FFC5F96C\n"
		     "MOV     R1, R8\n"
		     "MOV     R0, R4\n"
		     "BL      sub_FFC5E36C\n"
		     "LDR     R5, =0x55E0\n"
		     "MOV     R7, #1\n"
		     "LDR     R0, [R5,#0x10]\n"
		     "MOV     R6, #0\n"
		     "CMP     R0, #0x16\n"
		     "ADDLS   PC, PC, R0,LSL#2\n"
		     "B       loc_FFC5F96C\n"
	"loc_FFC5F700:\n"
		     "B       loc_FFC5F75C\n"
	"loc_FFC5F704:\n"
		     "B       loc_FFC5F778\n"
	"loc_FFC5F708:\n"
		     "B       loc_FFC5F7BC\n"
	"loc_FFC5F70C:\n"
		     "B       loc_FFC5F83C\n"
	"loc_FFC5F710:\n"
		     "B       loc_FFC5F84C\n"
	"loc_FFC5F714:\n"
		     "B       loc_FFC5F96C\n"
	"loc_FFC5F718:\n"
		     "B       loc_FFC5F96C\n"
	"loc_FFC5F71C:\n"
		     "B       loc_FFC5F8C8\n"
	"loc_FFC5F720:\n"
		     "B       loc_FFC5F76C\n"
	"loc_FFC5F724:\n"
		     "B       loc_FFC5F96C\n"
	"loc_FFC5F728:\n"
		     "B       loc_FFC5F8C8\n"
	"loc_FFC5F72C:\n"
		     "B       loc_FFC5F7B0\n"
	"loc_FFC5F730:\n"
		     "B       loc_FFC5F96C\n"
	"loc_FFC5F734:\n"
		     "B       loc_FFC5F96C\n"
	"loc_FFC5F738:\n"
		     "B       loc_FFC5F7C8\n"
	"loc_FFC5F73C:\n"
		     "B       loc_FFC5F7D4\n"
	"loc_FFC5F740:\n"
		     "B       loc_FFC5F80C\n"
	"loc_FFC5F744:\n"
		     "B       loc_FFC5F784\n"
	"loc_FFC5F748:\n"
		     "B       loc_FFC5F954\n"
	"loc_FFC5F74C:\n"
		     "B       loc_FFC5F8D4\n"
	"loc_FFC5F750:\n"
		     "B       loc_FFC5F904\n"
	"loc_FFC5F754:\n"
		     "B       loc_FFC5F904\n"
	"loc_FFC5F758:\n"
		     "B       loc_FFC5F858\n"
	"loc_FFC5F75C:\n"
		     "MOV     R1, R8\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
          	     "B       sub_FFC5EEF8_my\n"            // +----> Hook for SDHC booting
     "loc_FFC5F76C:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC60004\n"
	"loc_FFC5F778:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5EAB8\n"
	"loc_FFC5F784:\n"
		     "SUB     R12, R4, #0x1000\n"
		     "SUBS    R12, R12, #0xA5\n"
		     "STREQ   R7, [R5,#0x88]\n"
		     "BEQ     loc_FFC5F964\n"
		     "SUB     R12, R4, #0x3000\n"
		     "SUBS    R12, R12, #6\n"
		     "BNE     loc_FFC5F96C\n"
		     "MOV     R0, #0\n"
		     "BL      sub_FFC18FB4\n"
		     "BL      sub_FFC5FE6C\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F7B0:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5FEA4\n"
	"loc_FFC5F7BC:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5EC9C\n"
	"loc_FFC5F7C8:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5F2F4\n"
	"loc_FFC5F7D4:\n"
		     "SUB     R12, R4, #0x3200\n"
		     "SUBS    R12, R12, #2\n"
		     "BNE     loc_FFC5F96C\n"
		     "MOV     R0, #3\n"
		     "BL      sub_FFC5E250\n"
		     "MOV     R0, #8\n"
		     "BL      sub_FFC18F14\n"
		     "MOV     R1, #0\n"
		     "MOV     R0, #0x19\n"
		     "BL      sub_FFC270C8\n"
		     "BL      sub_FFC6143C\n"
		     "BL      sub_FFC616D8\n"
		     "BL      sub_FFC60AE8\n"
		     "B       loc_FFC5F964\n"
		     
	"loc_FFC5F80C:\n"
		     "SUB     R12, R4, #0x3300\n"
		     "SUBS    R12, R12, #1\n"
		     "BNE     loc_FFC5F96C\n"
		     "LDR     R0, =0x4010\n"
		     "STR     R6, [R5,#0x80]\n"
		     "BL      sub_FFC18F14\n"
		     "BL      sub_FFD6CD30\n"
		     "BL      sub_FFC61474\n"
		     "BL      sub_FFC60AE8\n"
		     "MOV     R0, #4\n"
		     "BL      sub_FFC5E250\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F83C:\n"
		     "MOV     R1, R8\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5F450\n"
	"loc_FFC5F84C:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5F550\n"
	"loc_FFC5F858:\n"
		     "LDR     R8, =0x1182\n"
		     "CMP     R4, R8\n"
		     "STREQ   R7, [R5,#0xB8]\n"
		     "BEQ     loc_FFC5F964\n"
		     "SUB     R12, R4, #0x1000\n"
		     "SUBS    R12, R12, #0x1AC\n"
		     "BEQ     loc_FFC5F8B0\n"
		     "SUB     R12, R4, #0x3000\n"
		     "SUBS    R12, R12, #0x224\n"
		     "BNE     loc_FFC5F96C\n"
		     "MOV     R0, #8\n"
		     "BL      sub_FFC18F14\n"
		     "MOV     R0, #3\n"
		     "BL      sub_FFC5E250\n"
		     "STR     R6, [R5,#0xBC]\n"
		     "LDR     R0, [R5,#0xB8]\n"
		     "CMP     R0, #0\n"
		     "MOVNE   R1, #0\n"
		     "MOVNE   R0, R8\n"
		     "STRNE   R6, [R5,#0xB8]\n"
		     "BLNE    sub_FFC5F450\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F8B0:\n"
		     "LDR     R0, [R5,#0xBC]\n"
		     "CMP     R0, #0\n"
		     "BNE     loc_FFC5F964\n"
		     "BL      sub_FFD6AF4C\n"
		     "STR     R7, [R5,#0xBC]\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F8C8:\n"
		     "MOV     R0, R4\n"
		     "LDMFD   SP!, {R4-R8,LR}\n"
		     "B       sub_FFC5F214\n"
	"loc_FFC5F8D4:\n"
		     "LDR     R12, =0x10B0\n"
		     "CMP     R4, R12\n"
		     "BEQ     loc_FFC5F900\n"
		     "BGT     loc_FFC5F90C\n"
		     "CMP     R4, #4\n"
		     "BEQ     loc_FFC5F934\n"
		     "SUB     R12, R4, #0x1000\n"
		     "SUBS    R12, R12, #0xAA\n"
		     "SUBNE   R12, R4, #0x1000\n"
		     "SUBNES  R12, R12, #0xAE\n"
		     "BNE     loc_FFC5F96C\n"
	"loc_FFC5F900:\n"
		     "BL      sub_FFC5DF30\n"
	"loc_FFC5F904:\n"
		     "MOV     R0, R6\n"
		     "LDMFD   SP!, {R4-R8,PC}\n"
	"loc_FFC5F90C:\n"
		     "SUB     R12, R4, #0x2000\n"
		     "SUBS    R12, R12, #4\n"
		     "BEQ     loc_FFC5F94C\n"
		     "SUB     R12, R4, #0x5000\n"
		     "SUBS    R12, R12, #1\n"
		     "SUBNE   R12, R4, #0x5000\n"
		     "SUBNES  R12, R12, #6\n"
		     "BNE     loc_FFC5F96C\n"
		     "BL      sub_FFC5EA10\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F934:\n"
		     "LDR     R0, [R5,#0x2C]\n"
		     "CMP     R0, #0\n"
		     "BNE     loc_FFC5F94C\n"
		     "BL      sub_FFC5FB1C\n"
		     "BL      sub_FFC143B4\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F94C:\n"
		     "BL      sub_FFC5DF6C\n"
		     "B       loc_FFC5F964\n"
	"loc_FFC5F954:\n"
		     "SUB     R12, R4, #0x3000\n"
		     "SUBS    R12, R12, #0x130\n"
		     "BNE     loc_FFC5F96C\n"
		     "BL      sub_FFC5E014\n"
	"loc_FFC5F964:\n"
		     "MOV     R0, #0\n"
		     "LDMFD   SP!, {R4-R8,PC}\n"
     "loc_FFC5F96C:\n"
          "MOV     R0, #1\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC5EEF8_my() {
     asm volatile (
		     "STMFD   SP!, {R4-R8,LR}\n"
		     "LDR     R7, =0x8002\n"
		     "LDR     R4, =0x55E0\n"
		     "CMP     R0, #2\n"
		     "MOV     R6, R1\n"
		     "MOV     R5, #1\n"
		     "BEQ     loc_FFC5EF84\n"
		     "BGT     loc_FFC5EF6C\n"
		     "CMP     R0, #0\n"
		     "BEQ     loc_FFC5EFB0\n"
		     "CMP     R0, #1\n"
		     "BNE     loc_FFC5F048\n"
		     "MOV     R0, #8\n"
		     "BL      sub_FFC5E250\n"
		     "BL      sub_FFC6070C\n"
		     "BL      sub_FFC6129C\n"
		     "LDR     R1, =0xFFC5F19C\n"
		     "MOV     R0, #0x60\n"
		     "BL      sub_FFC5673C\n"
		     "BL      sub_FFC606D0_my\n"            // +----> Hook for SDHC booting
		     "BL      sub_FFC607DC\n"
		     "BL      sub_FFC19A4C\n"
		     "LDR     R0, =0x4004\n"
		     "BL      sub_FFC18F14\n"
		     "LDR     R0, [R4,#0x68]\n"
		     "CMP     R0, #0\n"
		     "BNE     loc_FFC5F028\n"
		     "BL      sub_FFC1912C\n"
		     "B       loc_FFC5F02C\n"
	"loc_FFC5EF6C:\n"
		     "CMP     R0, #6\n"
		     "STREQ   R5, [R4,#0x28]\n"
		     "BEQ     loc_FFC5F03C\n"
		     "SUB     R12, R0, #0x2000\n"
		     "SUBS    R12, R12, #4\n"
		     "BNE     loc_FFC5F048\n"
	"loc_FFC5EF84:\n"
		     "SUB     R12, R6, #0x1100\n"
		     "SUBS    R12, R12, #0x62\n"
		     "BNE     loc_FFC5EFA0\n"
		     "MOV     R1, R7\n"
		     "MOV     R0, #0\n"
		     "BL      sub_FFC61E54\n"
		     "STR     R5, [R4,#0x60]\n"
	"loc_FFC5EFA0:\n"
		     "BL      sub_FFC6143C\n"
		     "BL      sub_FFC616D8\n"
		     "BL      sub_FFC5E9B0\n"
		     "B       loc_FFC5F040\n"
	"loc_FFC5EFB0:\n"
		     "MOV     R0, #7\n"
		     "BL      sub_FFC5E250\n"
		     "MOV     R0, R7\n"
		     "BL      sub_FFC18F14\n"
		     "BL      sub_FFC6070C\n"
		     "BL      sub_FFC6129C\n"
		     "LDR     R1, =0xFFC5F1AC\n"
		     "MOV     R0, #0x60\n"
		     "STR     R6, [R4,#0x18]\n"
		     "BL      sub_FFC5673C\n"
		     "LDR     R1, =0xFFC5F1B8\n"
		     "MOV     R0, #0x60\n"
		     "BL      sub_FFC5673C\n"
		     "STR     R5, [R4,#0x28]\n"
		     "BL      sub_FFC190BC\n"
		     "BL      sub_FFC18FDC\n"
		     "LDR     R0, [R4,#0x1C]\n"
		     "LDR     R1, [R4,#0x20]\n"
		     "ORRS    R0, R0, R1\n"
		     "BLNE    sub_FFC5FAF8\n"
		     "LDR     R0, [R4,#0x68]\n"
		     "CMP     R0, #0\n"
		     "BNE     loc_FFC5F014\n"
		     "BL      sub_FFC1912C\n"	//taskcreate_StartupImage
		     "B       loc_FFC5F01C\n"
	"loc_FFC5F014:\n"
		     "BL      sub_FFC14250\n"
		     "BL      sub_FFC19A84\n"
	"loc_FFC5F01C:\n"
		     "BL      sub_FFC606D0_my\n"            // +----> Hook for SDHC booting
		     "BL      sub_FFC60748\n"
		     "B       loc_FFC5F040\n"
	"loc_FFC5F028:\n"
		     "BL      sub_FFC14250\n"
	"loc_FFC5F02C:\n"
		     "BL      sub_FFC60778\n"
		     "LDR     R0, [R4,#0x30]\n"
		     "CMP     R0, #0\n"
		     "BEQ     loc_FFC5F040\n"
	"loc_FFC5F03C:\n"
		     "BL      sub_FFC5FB40\n"
	"loc_FFC5F040:\n"
		     "MOV     R0, #0\n"
		     "LDMFD   SP!, {R4-R8,PC}\n"
	"loc_FFC5F048:\n"
		     "MOV     R0, #1\n"
		     "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC606D0_my() {
     asm volatile (
//        "LDR     R0, =0x6380\n"
          "LDR	R0, =0x56B8 \n"      	//** different than 1.00b  
          "STMFD   SP!, {R3,LR}\n"
//        "LDR     R1, [R0,#0x10]\n"
//        "CMP     R1, #1\n"
//        "BEQ     locret_FFC60708\n"
          "LDR	R1, [R0, #4] \n"      	//** different than 1.00b                      
          "CMP	R1, #0 \n"         		//** different than 1.00b                        
          "BNE	locret_FFC60708 \n"     //** different than 1.00b   		  
          "MOV     R1, #1\n"
          "STR     R1, [R0,#0x4]\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP,#8-8]\n"
          "LDR     R3, =sub_FFC60680_my\n"       // +----> Hook for SDHC booting
          "MOV     R1, #0x19\n"
          "LDR     R0, =0xFFC60834\n"
          "MOV     R2, #0x1000\n"
          "BL      sub_FFC0B8C0\n"
     "locret_FFC60708:\n"
          "LDMFD   SP!, {R12,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC60680_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "BL      sub_FFC59D6C\n"
          "LDR     R5, =0x5006\n"
          "MOVS    R4, R0\n"
          "MOVNE   R1, #0\n"
          "MOVNE   R0, R5\n"
          "BLNE    sub_FFC5C45C\n"
          "BL      sub_FFC59D98_my\n"            // +----> Hook for SDHC booting

          "BL      core_spytask_can_start\n"     // +----> CHDK: Set "it's-safe-to-start"-Flag for spytask

          "CMP     R4, #0\n"
          "MOVEQ   R0, R5\n"
          "LDMEQFD SP!, {R4-R6,LR}\n"
          "MOVEQ   R1, #0\n"
          "BEQ     sub_FFC5C45C\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC59D98_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FFC3FC50_my\n"            // +----> Hook for SDHC booting
          "BL	sub_FFCE9F34 \n"    	//** different than 1.00b  - nullsub?  
          "LDR     R4, =0x5474\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC59DCC\n"
          "BL      sub_FFC3F118\n"
          "BL      sub_FFCDFCFC\n"
          "BL      sub_FFC3F118\n"
          "BL      sub_FFC3AFEC\n"
          "BL      sub_FFC3F018\n"
          "BL      sub_FFCDFDC8\n"
     "loc_FFC59DCC:\n"
          "MOV     R0, #1\n"
          "STR     R0, [R4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC3FC50_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "MOV     R6, #0\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3F710\n"
          "LDR     R4, =0x176A4\n"
          "MOV     R5, #0\n"
          "LDR     R0, [R4,#0x38]\n"
          "BL      sub_FFC40170\n"
          "CMP     R0, #0\n"
          "LDREQ   R0, =0x26F8\n"
          "STREQ   R5, [R0,#0x10]\n"
          "STREQ   R5, [R0,#0x14]\n"
          "STREQ   R5, [R0,#0x18]\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3F750\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3FA8C_my\n"            // +----> Hook for SDHC booting
          "MOV     R5, R0\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3FAF8\n" 
          "LDR     R1, [R4,#0x3C]\n"
          "AND     R2, R5, R0\n"
          "CMP     R1, #0\n"
          "MOV     R0, #0\n"
          "MOVEQ   R0, #0x80000001\n"
          "BEQ     loc_FFC3FCE4\n"
          "LDR     R3, [R4,#0x2C]\n"
          "CMP     R3, #2\n"
          "MOVEQ   R0, #4\n"
          "CMP     R1, #5\n"
          "ORRNE   R0, R0, #1\n"
          "BICEQ   R0, R0, #1\n"
          "CMP     R2, #0\n"
          "BICEQ   R0, R0, #2\n"
          "ORREQ   R0, R0, #0x80000000\n"
          "BICNE   R0, R0, #0x80000000\n"
          "ORRNE   R0, R0, #2\n"
     "loc_FFC3FCE4:\n"
          "STR     R0, [R4,#0x40]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC3FA8C_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "LDR     R5, =0x26F8\n"
          "MOV     R6, R0\n"
          "LDR     R0, [R5,#0x14]\n"
          "CMP     R0, #0\n"
          "MOVNE   R0, #1\n"
          "LDMNEFD SP!, {R4-R6,PC}\n"
          "MOV     R0, #0x17\n"
          "MUL     R1, R0, R6\n"
          "LDR     R0, =0x176A4\n"
          "ADD     R4, R0, R1,LSL#2\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          "BL      sub_FFC3F81C_my\n"            // +----> Hook for SDHC booting
          //"BL      sub_FFC3F81C\n"
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          "BL      sub_FFC3F984\n"
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3F318\n"
          "CMP     R0, #0\n"
          "MOVNE   R1, #1\n"
          "STRNE   R1, [R5,#0x14]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC3F81C_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "MOV     R8, R0\n"
          "MOV     R0, #0x17\n"
          "MUL     R1, R0, R1\n"
          "LDR     R0, =0x176A4\n"
          "MOV     R6, #0\n"
          "ADD     R7, R0, R1,LSL#2\n"
          "LDR     R0, [R7,#0x3C]\n"
          "MOV     R5, #0\n"
          "CMP     R0, #6\n"
          "ADDLS   PC, PC, R0,LSL#2\n"
          "B       loc_FFC3F968\n"
	"loc_FFC3F84C:\n"
	  "B       loc_FFC3F880\n"
	"loc_FFC3F850:\n"
	  "B       loc_FFC3F868\n"
	"loc_FFC3F854:\n"
	  "B       loc_FFC3F868\n"
	"loc_FFC3F858:\n"
	  "B       loc_FFC3F868\n"
	"loc_FFC3F85C:\n"
	  "B       loc_FFC3F868\n"
	"loc_FFC3F860:\n"
	  "B       loc_FFC3F960\n"
	"loc_FFC3F864:\n"
	  "B       loc_FFC3F868\n"
	"loc_FFC3F868:\n"
	  "MOV     R2, #0\n"
	  "MOV     R1, #0x200\n"
	  "MOV     R0, #2\n"
	  "BL      sub_FFC53DBC\n"
	  "MOVS    R4, R0\n"
	  "BNE     loc_FFC3F888\n"
	"loc_FFC3F880:\n"
	  "MOV     R0, #0\n"
	  "LDMFD   SP!, {R4-R8,PC}\n"
	"loc_FFC3F888:\n"
	  "LDR     R12, [R7,#0x4C]\n"
	  "MOV     R3, R4\n"
	  "MOV     R2, #1\n"
	  "MOV     R1, #0\n"
	  "MOV     R0, R8\n"

	 //"BLX     R12\n"
	  "MOV	   LR, PC\n"
	  "MOV	   PC, R12\n"

	  "CMP     R0, #1\n"
	  "BNE     loc_FFC3F8B4\n"
	  "MOV     R0, #2\n"
	  "BL      sub_FFC53F08\n"
	  "B       loc_FFC3F880\n"

     "loc_FFC3F8B4:\n"
          "MOV     R0, R8\n"
          "BL      sub_FFCF51D4\n"

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
          "LDRB    R1, [R4,#0x1C9]\n"            // 4th byte of LBA
          "LDRB    R3, [R4,#0x1C8]\n"            // 3rd byte of LBA
          "LDRB    R12, [R4,#0x1CC]\n"           // 3rd byte of partition length
          "MOV     R1, R1,LSL#24\n"              // Shift and...
          "ORR     R1, R1, R3,LSL#16\n"          // combine LBA bytes (endianness fix)
          "LDRB    R3, [R4,#0x1C7]\n"            // 2nd byte of LBA
          "LDRB    R2, [R4,#0x1BE]\n"            // Partition status (0x00=nonboot, 0x80=boot, other=bad)
          //"LDRB    LR, [R4,#0x1FF]\n"            // Last MBR signature byte (0xAA)
          "ORR     R1, R1, R3,LSL#8\n"           // Combine more LBA bytes
          "LDRB    R3, [R4,#0x1C6]\n"            // 1st byte of LBA
          "CMP     R2, #0\n"                     // Check partition status
          "CMPNE   R2, #0x80\n"                  // and again
          "ORR     R1, R1, R3\n"                 // Combine LBA into final value
          "LDRB    R3, [R4,#0x1CD]\n"            // 4th byte of partition length
          "MOV     R3, R3,LSL#24\n"              // Shift and...
          "ORR     R3, R3, R12,LSL#16\n"         // combine partition length bytes
          "LDRB    R12, [R4,#0x1CB]\n"           // 2nd byte of partition length
          "ORR     R3, R3, R12,LSL#8\n"          // Combine partition length bytes
          "LDRB    R12, [R4,#0x1CA]\n"           // 1st byte of partition length
          "ORR     R3, R3, R12\n"                // Combine partition length bytes into final value
          //"LDRB    R12, [R4,#0x1FE]\n"           // First MBR signature byte (0x55)
          "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
          "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.

          "MOV     R4, #0\n"                     // This value previously held a pointer to the partition table :(
          "BNE     loc_FFC3F93C\n"               // Jump out if the partition is malformed (partition status \'other\')
          "CMP     R0, R1\n"
          "BCC     loc_FFC3F93C\n"               // Jump out if R0 < R1 (probably checking for a valid LBA addr)
          "ADD     R2, R1, R3\n"                 // R2 = partition start address + length = partition end address
          "CMP     R2, R0\n"                     // Guess: CMPLS is used to check for an overflow, the partition end address cannot be negative.
          "CMPLS   R12, #0x55\n"                 // Check MBR signature with original offset
          "CMPEQ   LR, #0xAA\n"                  // Check MBR signature with original offset
          "MOVEQ   R6, R1\n"
          "MOVEQ   R5, R3\n"
          "MOVEQ   R4, #1\n"
     "loc_FFC3F93C:\n"
//        "MOV     R0, #3\n"
          "MOV     R0, #2 \n"
          "BL      sub_FFC53F08\n"
          "CMP     R4, #0\n"
          "BNE     loc_FFC3F974\n"
          "MOV     R6, #0\n"
          "MOV     R0, R8\n"
          "BL      sub_FFCF51D4\n"
          "MOV     R5, R0\n"
          "B       loc_FFC3F974\n"
     "loc_FFC3F960:\n"
          "MOV     R5, #0x40\n"
          "B       loc_FFC3F974\n"
     "loc_FFC3F968:\n"
          "LDR     R1, =0x37A\n"
          "LDR     R0, =0xFFC3F810\n"
          "BL      sub_FFC0BD98\n"
     "loc_FFC3F974:\n"
          "STR     R6, [R7,#0x44]!\n"
          "MOV     R0, #1\n"
          "STR     R5, [R7,#4]\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

////////////////////////////////////////////////////////////////////////////////
// SDHC HOOK ENDS HERE
////////////////////////////////////////////////////////////////////////////////

void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};


void __attribute__((naked,noinline)) task_blinker() {

		volatile long *p=(void*)0xC02200CC;
    
    int delay = 0x200000;
    int i;
    
		while(1){
			p[0]=0x46;
			for(i=0;i<delay;i++){
				asm ("nop\n");
				asm ("nop\n");
			}
			p[0]=0x44;
			for(i=0;i<delay;i++){
				asm ("nop\n");
				asm ("nop\n");
			}
	}
};

extern long _Fopen_Fut(const char *filename, const char *mode);
extern long _Fwrite_Fut(const void *buf, long elsize, long count, long f);
extern long Fread_Fut(void *buf, long elsize, long count, long f);
extern long Fseek_Fut(long file, long offset, long whence);
extern long _qDump(char* filename, long unused, long write_p2, long write_p3);
