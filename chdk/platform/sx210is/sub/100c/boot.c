#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"
//#include "stdlib.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

void JogDial_task_my(void);

const char * const new_sa = &_end;

void taskHook(context_t **context) {

task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

if(!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task;  //JHARP - Verified name - Sept 5, 2010
if(!_strcmp(tcb->name, "CaptSeqTask"))     tcb->entry = (void*)capt_seq_task; //JHARP - Verified name - Sept 5, 2010
if(!_strcmp(tcb->name, "InitFileModules")) tcb->entry = (void*)init_file_modules_task; //JHARP - Verified name - Sept 5, 2010
if(!_strcmp(tcb->name, "MovieRecord"))     tcb->entry = (void*)movie_record_task; //JHARP - Verified name - Sept 5, 2010
if(!_strcmp(tcb->name, "ExpDrvTask"))      tcb->entry = (void*)exp_drv_task; //JHARP - Verified name - Sept 5, 2010
if(!_strcmp(tcb->name, "RotarySw"))        tcb->entry = (void*)JogDial_task_my; //JHARP - Must verify the code in use - Sept 5, 2010

}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};






void __attribute__((naked,noinline)) boot() {
    asm volatile (
				 //"B		  sub_FF81000C\n"
                 "LDR     R1, =0xC0410000\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R1]\n"
                 "MOV     R1, #0x78\n"
                 "MCR     p15, 0, R1,c1,c0\n"			// control reg
                 "MOV     R1, #0\n"
                 "MCR     p15, 0, R1,c7,c10, 4\n"		// drain write buffer
                 "MCR     p15, 0, R1,c7,c5\n"			// flush instruction cache
                 "MCR     p15, 0, R1,c7,c6\n"				// flush data cache
                 "MOV     R0, #0x3D\n"					// size 2GB base 0x00000000
                 "MCR     p15, 0, R0,c6,c0\n"			// protection region 0
                 "MOV     R0, #0xC000002F\n"			// size 16M base 0xc0000000
                 "MCR     p15, 0, R0,c6,c1\n"
                 "MOV     R0, #0x33\n"					// size 128M base 0x00000000 (s90 is 64M)
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000033\n"			// size 128M base 0x40000000 (s90 is 64M)
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"			// size  4k base 0x80000000
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFF80002D\n"			// size  8M base 0xff800000
                 "MCR     p15, 0, R0,c6,c5\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0, 1\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c3,c0\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 2\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 3\n"
                 "MRC     p15, 0, R0,c1,c0\n"
                 "ORR     R0, R0, #0x1000\n"
                 "ORR     R0, R0, #4\n"
                 "ORR     R0, R0, #1\n"
                 "MCR     p15, 0, R0,c1,c0\n"
                 "MOV     R1, #0x80000006\n"
                 "MCR     p15, 0, R1,c9,c1\n"
                 "MOV     R1, #6\n"
                 "MCR     p15, 0, R1,c9,c1, 1\n"
                 "MRC     p15, 0, R1,c1,c0\n"
                 "ORR     R1, R1, #0x50000\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "LDR     R2, =0xC0200000\n"
                 "MOV     R1, #1\n"
                 "STR     R1, [R2,#0x10C]\n"
                 "MOV     R1, #0xFF\n"
                 "STR     R1, [R2,#0xC]\n"
                 "STR     R1, [R2,#0x1C]\n"
                 "STR     R1, [R2,#0x2C]\n"
                 "STR     R1, [R2,#0x3C]\n"
                 "STR     R1, [R2,#0x4C]\n"
                 "STR     R1, [R2,#0x5C]\n"
                 "STR     R1, [R2,#0x6C]\n"
                 "STR     R1, [R2,#0x7C]\n"
                 "STR     R1, [R2,#0x8C]\n"
                 "STR     R1, [R2,#0x9C]\n"
                 "STR     R1, [R2,#0xAC]\n"
                 "STR     R1, [R2,#0xBC]\n"
                 "STR     R1, [R2,#0xCC]\n"
                 "STR     R1, [R2,#0xDC]\n"
                 "STR     R1, [R2,#0xEC]\n"
                 "STR     R1, [R2,#0xFC]\n"
                 "LDR     R1, =0xC0400008\n"
                 "LDR     R2, =0x430005\n"
                 "STR     R2, [R1]\n"
                 "MOV     R1, #1\n"
                 "LDR     R2, =0xC0243100\n"
                 "STR     R2, [R1]\n"
                 "LDR     R2, =0xC0242010\n"
                 "LDR     R1, [R2]\n"
                 "ORR     R1, R1, #1\n"
                 "STR     R1, [R2]\n"
                 "LDR     R0, =0xFFC2FA94\n"    // ASM1989 -> In sx200 was:  "LDR     R0, =0xFFB91B18\n"
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0xFA80\n"		// ASM1989 -> In sx200 was:  "LDR     R3, =0xDBCC\n"
    "loc_FF81013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF81013C\n"
                 "LDR     R1, =0x152728\n"  	// ASM1989 -> In sx200 was:  "LDR     R1, =0x12351C\n"
                 "MOV     R2, #0\n"
    "loc_FF810154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FF810154\n"
                 "B       sub_FF810354_my\n"   // ASM1989 -> In sx200 was:  "B       sub_FF8101A0_my\n"
                                                 //---------->
    );
}


void __attribute__((naked,noinline)) sub_FF810354_my() { // ASM1989 -> In sx200 was:  sub_FF8101A0_my
   // ASM1989 -> Need to review all the task creationhooks

   *(int*)0x1934=(int)taskHook;   //was 1934 in sx200 if 1938 hangs
   *(int*)0x1938=(int)taskHook;
//UNABLE TO FIND THIS YET
//   *(int*)0x1930=(int)taskCreateHook3; //  don't know why but movie will only work with 1930 and card lock only with 1934 - 1938
//  OLD SX200
//   *(int*)(0x24C0+4)= (*(int*)0xC0220128)&1 ? 0x2000000 : 0x1000000; // replacement of sub_FF821BD4 for correct power-on.
// NEW SX210
     *(int*)(0x24B4)= (*(int*)0xC022010C)&1 ? 0x400000 : 0x200000; // // ASM1989 -> values for this found at: FF861488 in sx210, in sx200 at: FF847A08


   asm volatile (
                 "LDR     R0, =0xFF8103CC\n"        // ASM1989 -> In sx200 was: "LDR     R0, =0xFF810218\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFF810404\n"        // ASM1989 -> In sx200 was: "LDR     R3, =0xFF810250\n"
"loc_FF810360:\n"									 // ASM1989 -> In sx200 was: "loc_FF8101AC:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF810360\n"        // ASM1989 -> In sx200 was: "BCC     loc_FF8101AC\n"
                 "LDR     R0, =0xFF810404\n"     // ASM1989 -> In sx200 was:  "LDR     R0, =0xFF810250\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFF810618\n"     // ASM1989 -> In sx200 was:   "LDR     R3, =0xFF810464\n"
"loc_FF81037C:\n"									 // ASM1989 -> In sx200 was: "loc_FF8101C8:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF81037C\n"     // ASM1989 -> In sx200 was:  "BCC     loc_FF8101C8\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"       //ASM1989 left the same as other cameras, but in the firmare points to FF8103C0
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
"loc_FF8103B0:\n"									 // ASM1989 -> In sx200 was: "loc_FF8101FC:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FF8103B0\n"     // ASM1989 -> In sx200 was:  "BCC     loc_FF8101FC\n"
                 "BL      sub_FF811198_my\n"  // ASM1989 -> In sx200 was: "BL      sub_FF810FC4_my\n"
                 							  //------------>



"loc_FF810218:\n"									 // ASM1989 -> In sx200 was: "loc_FF81020C:\n"
                 "ANDEQ   R0, R0, R4,ASR#13\n"
"loc_FF8103C4:\n"									 // ASM1989 -> In sx200 was: "loc_FF810210:\n"
                 "ANDEQ   R0, R0, R0,ROR R6\n"
"loc_FF8103C8:\n"									 // ASM1989 -> In sx200 was: "loc_FF810214:\n"
                 "ANDEQ   R0, R0, R4,ROR R6\n"
"loc_FF8103CC:\n"									 // ASM1989 -> In sx200 was: "loc_FF810218:\n"
                 "NOP\n"
                 "LDR     PC, =0xFF810618\n"		 // ASM1989 -> In sx200 was:  "LDR     PC, =0xFF810464\n"
     );
}

void __attribute__((naked,noinline)) sub_FF811198_my() { // ASM1989 -> In sx200 was: sub_FF810FC4_my
     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFB5FA88\n"		 // ASM1989 -> In sx200 was: "sub_FFAF8D3C\n"
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
               //  "LDR     R0, =0x0x152728\n" // In sx200 : 12351C
                 "LDR     R0, =new_sa\n"        // +
                 "LDR     R0, [R0]\n"           // +
                 "LDR     R2, =0x339C00\n"	      // ASM1989 -> In sx200 was: "LDR     R2, =0x2F9C00\n"
                 "LDR     R1, =0x3324A8\n"        // ASM1989 -> In sx200 was: "LDR     R1, =0x2F24A8\n"
                 "STR     R0, [SP,#8]\n"
                 "SUB     R0, R1, R0\n"
                 "ADD     R3, SP, #0xC\n"
                 "STR     R2, [SP]\n"
                 "STMIA   R3, {R0-R2}\n"
                 "MOV     R0, #0x22\n"
                 "STR     R0, [SP,#0x18]\n"
                 "MOV     R0, #0x68\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "LDR     R0, =0x19B\n"
                 "LDR     R1, =sub_FF815E58_my\n"   // ASM1989 -> In sx200 was:"LDR     R1, =sub_FF814D38_my\n"
                 									//------------>
                 "STR     R0, [SP,#0x20]\n"
                 "MOV     R0, #0x96\n"
                 "STR     R0, [SP,#0x24]\n"
                 "MOV     R0, #0x78\n"
                 "STR     R0, [SP,#0x28]\n"
                 "MOV     R0, #0x64\n"
                 "STR     R0, [SP,#0x2C]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [SP,#0x30]\n"
                 "STR     R0, [SP,#0x34]\n"
                 "MOV     R0, #0x10\n"
                 "STR     R0, [SP,#0x5C]\n"
                 "MOV     R0, #0x800\n"
                 "STR     R0, [SP,#0x60]\n"
                 "MOV     R0, #0xA0\n"
                 "STR     R0, [SP,#0x64]\n"
                 "MOV     R0, #0x280\n"
                 "STR     R0, [SP,#0x68]\n"
                 "MOV     R0, SP\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF813404\n"        // ASM1989 -> In sx200 was:   "sub_FF812D68\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
     );
}



void __attribute__((naked,noinline)) sub_FF815E58_my() {// ASM1989 -> In sx200 was: sub_FF814D38_my(
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF810B20\n"       // ASM1989 -> In sx200 was:  "sub_FF810954\n"
                 "BL      sub_FF81A244\n"       // ASM1989 -> In sx200 was: "sub_FF8190B4\n"    dmSetup
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815F6C\n"    // ASM1989 -> In sx200 was: "LDRLT   R0, =0xFF814E4C\n"  // "dmSetup"
                 "BLLT    sub_FF815F4C\n"       // ASM1989 -> In sx200 was:  "BLLT    sub_FF814E2C\n"  err_init_task
                 "BL      sub_FF815A94\n"      // ASM1989 -> In sx200 was: "sub_FF814974\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815F74\n"    // ASM1989 -> In sx200 was: "LDRLT   R0, =0xFF814E54\n"     // "termDriverInit"
                 "BLLT    sub_FF815F4C\n"	   // ASM1989 -> 	err_init_task
                 "LDR     R0, =0xFF815F84\n"   // ASM1989 -> In sx200 was: "LDR     R0, =0xFF814E64\n"  // "/_term"
                 "BL      sub_FF815B7C\n"	   // ASM1989 -> In sx200 was:  "sub_FF814A5C\n"  termDeviceCreate
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815F8C\n"   // ASM1989 -> In sx200 was:  FF814E6C // "termDeviceCreate"
                 "BLLT    sub_FF815F4C\n"       // ASM1989 -> err_init_task
                 "LDR     R0, =0xFF815F84\n"   // ASM1989 -> "/_term"
                 "BL      sub_FF813BF0\n"		// ASM1989 -> In sx200 was: FF813578    stdioSetup
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815FA0\n"    // ASM1989 -> In sx200 was: FF814E80 // "stdioSetup"
                 "BLLT    sub_FF815F4C\n"       // ASM1989 -> err_init_task
                 "BL      sub_FF819C3C\n"		// ASM1989 -> In sx200 was: FF818BCC
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815FAC\n"    // ASM1989 -> In sx200 was: FF814E8C // "stdlibSetup"
                 "BLLT    sub_FF815F4C\n"       // ASM1989 -> err_init_task
                 "BL      sub_FF81167C\n"		// ASM1989 -> In sx200 was:  FF8114A8
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815FB8\n"    // ASM1989 -> In sx200 was: FF814E98// "armlib_setup"
                 "BLLT    sub_FF815F4C\n"       // ASM1989 -> err_init_task
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n" // ASM1989 -> In sx200 at FF81C260

                 							//---------->  In sx210 at FF81FAF0

        );
};


// ASM1989 -> Here starts the diferences with SX200

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (

                 "STMFD   SP!, {R3-R5,LR}\n"		// ASM1989 -> In sx200 was:"STMFD   SP!, {R3,LR}\n"
                 "BL      sub_FF834410\n"         //ASM1989 -> j_nullsub_231 in sx200 j_nullsub_239
                 "BL      sub_FF83BF28\n"		// ASM1989 -> In sx200 was: FF829050
                 "CMP     R0, #0\n"

                "BNE     loc_FF81FB44\n"		// ASM1989 -> In sx200 was: FF81C298


                 "BL      sub_FF835C04\n"		// ASM1989 -> In sx200 was: FF821BC8
                 "CMP     R0, #0\n"

// Here are diferences with the sx200 code
                "BEQ     loc_FF81FB44\n"		// ASM1989 -> In sx200 was: "BNE     loc_FF81FB44\n"
                 // old SX200 code : "BL      sub_FF8212BC\n"
                 "LDR     R4, =0xC0220000\n"	// ASM1989 -> In sx200 was:    "LDR     R1, =0xC0220000\n"
                 "LDR     R0, [R4,#0xCC]\n"           // ASM1989 -> In sx200 was: "MOV     R0, #0x44\n"
                 //New for sx210
                 "TST     R0, #1\n"
				 "MOVEQ   R0, #0x12C\n"




 				"BLEQ    sub_FF83A2DC\n"   //ASM1989 ->  eventproc_export_SleepTask
				"BL      sub_FF83440C\n"
				"CMP     R0, #0\n"
				"BNE     loc_FF81FB44\n"
				"BL      sub_FF833AA4\n"
				"MOV     R0, #0x44\n"
				"STR     R0, [R4,#0x1C]\n"
				"BL      sub_FF833C90\n"
"loc_FF81FB40:\n"
				"B       loc_FF81FB40\n"


"loc_FF81FB44:\n"
				//"BL      sub_FF834418\n" // ASM1989 -> -- replaced for power button startup

				"BL      sub_FF834414\n"//ASM1989 ->  j_nullsub_232
				"BL      sub_FF83A154\n"

				"LDR     R1, =0x38E000\n"
				"MOV     R0, #0\n"

				"BL      sub_FF83A59C\n"
				"BL      sub_FF83A348\n"  //ASM1989 -> sub_FF83A348__KerSys.c__548
				"MOV     R3, #0\n"

				"STR     R3, [SP]\n"  //ASM1989 ->Modified to match equal as sx200
				"LDR     R3, =task_Startup_my\n" //  ASM1989 -> original is FF81FA8C   task_Startup   // LDR instead of ADR
                //---------------->

				"MOV     R2, #0\n"
				"MOV     R1, #0x19\n"
				"LDR     R0, =0xFF81FB8C\n"  //aStartup  // LDR instead of ADR


				"BL      sub_FF81E83C\n"  //eventproc_export_CreateTask
				"MOV     R0, #0\n"
				"LDMFD   SP!, {R3-R5,PC}\n"



//OLD SX200
/*
                 "BL      sub_FF8214A8\n"
"loc_FF81C294:\n"
                 "B       loc_FF81C294\n"
"loc_FF81C298:\n"
      //           "BL      sub_FF821BD4\n"       // -- replaced for power button startup
                 "BL      sub_FF821BD0\n"        // j_nullsub_240
                 "BL      sub_FF827308\n"
                 "LDR     R1, =0x34E000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF827750\n"
                 "BL      sub_FF8274FC\n"     // _sub_FF8274FC__KerSys.c__548
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"    //---------------->
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFF81C2E0\n"   // "Startup"
                 "BL      sub_FF81AFAC\n"      // eventproc_export_CreateTask
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R12,PC}\n" */
     );
}



// ASM1989 25.8.2010

void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF81650C\n"     //ASM1989 -> taskcreate_ClockSave   in sx200 FF815394
                 "BL      sub_FF83550C\n"	 //ASM1989 -> In sx200 was: FF822CB0
                 "BL      sub_FF833728\n"    //ASM1989 -> In sx200 was: FF820F70
                 "BL      sub_FF83BF68\n"    //ASM1989 ->  j_nullsub_235 in sx200 was: FF829090
                 "BL      sub_FF83C154\n"	//ASM1989 -> In sx200 was: FF829274

            //     "BL      sub_FF83BFFC\n"    // start diskboot.bin ASM1989 -> In sx200 was:  FF829124

                 "BL      sub_FF83C2F8\n"		//ASM1989 -> In sx200 was: FF829418
                 "BL      sub_FF8322F4\n"	//ASM1989 -> In sx200 was: FF81FB90
                 "BL      sub_FF83C184\n"	//ASM1989 -> In sx200 was: FF8292A4
                 "BL      sub_FF8398F8\n"	//ASM1989 -> In sx200 was: FF826908
                 "BL      sub_FF83C2FC\n"	//ASM1989 -> In sx200 was: FF82941C

//"BL debug_blink\n"
//"BL debug_blink\n"
//"BL debug_blink\n"
//"BL debug_blink\n"

// If uncommented reboots why??

               "BL      CreateTask_spytask\n"    // +
								//---------------->

//"BL debug_blink\n"
                 "BL      sub_FF8342F4\n"   // taskcreate_PhySw //ASM1989 -> In sx200 was: FF821AC4
                 "BL      sub_FF8378B0\n"	//ASM1989 -> In sx200 was: FF824B14

                 "BL      sub_FF83C314\n"	//ASM1989 -> In sx200 was: FF829434
                 "BL      sub_FF8316B8\n"   //ASM1989 -> In sx200 was: FF81EFB0 // nullsub_2
                 "BL      sub_FF833178\n"   //ASM1989 -> In sx200 was: FF82087C // sx210: sub_FF833178__Battery.c__0
                 "BL      sub_FF83BD00\n"   //ASM1989 -> In sx200 was: FF828E2C// taskcreate_Bye
                 "BL      sub_FF8336DC\n"   //ASM1989 -> In sx200 was: FF820F20
                 "BL      sub_FF833114\n"   //ASM1989 -> In sx200 was: FF820788 // taskcreate_TempCheck in sx200
                 "BL      sub_FF832328\n"	//ASM1989 -> In sx200 was: FF81FBC4


                 "BL      sub_FF83CD78\n"	//ASM1989 -> In sx200 was: FF829F18
                 "BL      sub_FF8330EC\n"	//ASM1989 -> In sx200 was: FF820760
// Reaches ok here OK
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF81662C\n"   //ASM1989 -> In sx200 was:FF8154B4  // _sub_FF81662C__MLHClock.c__992


     );
}



// debug use only
int debug_blink(int save_R0) {
	int i;
	*((volatile int *) 0xC0220130) = 0x46; // Turn on Print LED
	for (i=0; i<800000; i++) // Wait a while
		{
     		asm volatile ( "nop\n" );
		}
	*((volatile int *) 0xC0220130) = 0x44; // Turn off LED
	for (i=0; i<800000; i++) // Wait a while
		{
    		asm volatile ( "nop\n" );
		}
	return save_R0;
};




void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
// "BL debug_blink\n"


               "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF89193C\n"   //ASM1989 -> In sx200 was: FF874B88
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FF8953D8\n"    //ASM1989 -> eventproc_export_PostLogicalEventToUI In sx200 was:  FF879A54

               "BL      sub_FF891968_my\n" //ASM1989 -> In sx200 was:  FF874BB4

                 //---------->

                 "BL      core_spytask_can_start\n"      // CHDK: Set "it's-safe-to-start"-Flag for spytask
                 "CMP     R4, #0\n"
                 "MOVEQ   R0, R5\n"
                 "LDMEQFD SP!, {R4-R6,LR}\n"
                 "MOVEQ   R1, #0\n"
                 "BEQ     sub_FF8953D8\n"   //ASM1989 -> eventproc_export_PostLogicalEventToUI In sx200 was:  FF879A54
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}






void __attribute__((naked,noinline)) sub_FF891968_my() {  //ASM1989 -> In sx200 was:  FF874BB4
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF87343C_my\n"  //ASM1989 -> In sx200 was: FF857704
              					               //----------->

                 "BL      sub_FF951620\n"       //ASM1989 -> nullsub_109 In sx200 was: FF91572C // nullsub_99
                 "LDR     R4, =0x3680\n"		//ASM1989 -> In sx200 was: 0x2F04
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF8919A0\n"		//ASM1989 -> In sx200 was: FF874BEC
                 "BL      sub_FF872684\n"		//ASM1989 -> In sx200 was: FF856AC8
                 "BL      sub_FF9443A4\n"		//ASM1989 -> In sx200 was: FF909DC4
                 "BL      sub_FF872684\n"		//ASM1989 -> In sx200 was: FF856AC8
                 "BL      sub_FF86EAA8\n"		//ASM1989 -> In sx200 was: FF852B1C
                 "BL      sub_FF872584\n"		//ASM1989 -> In sx200 was: FF8569C8
                 "BL      sub_FF944440\n"		//ASM1989 -> In sx200 was: FF909E90
 "loc_FF8919A0:\n"								//ASM1989 -> In sx200 was: FF874BEC
                 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}


void __attribute__((naked,noinline)) sub_FF87343C_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"					//ASM1989 -> In sx200 was: "MOV     R6, R0\n"
                 "BL      sub_FF8733BC\n"             //ASM1989 ->  LOCATION: Mounter.c:0 In sx200 was: FF85766C
                 "LDR     R1, =0x39390\n"			//ASM1989 -> In sx200 was: 0x11840
                 "MOV     R6, R0\n"					//ASM1989 -> In sx200 was: "MOV     R5, R0\n"
                 "ADD     R4, R1, R0,LSL#7\n"
                 "LDR     R0, [R4,#0x6C]\n"		   //ASM1989 -> In sx200 was: 0x70
                 "CMP     R0, #4\n"
                 "LDREQ   R1, =0x83F\n"				//ASM1989 -> In sx200 was: 0x6D8
                 "LDREQ   R0, =0xFF872EFC\n"    //  ; "Mounter.c" //ASM1989 -> In sx200 was:  FF857190
                 "BLEQ    sub_FF81EB14\n"      //ASM1989 -> In sx200 was:FF81B284  // DebugAssert
                 "MOV     R1, R8\n"				//ASM1989 -> In sx200 was:  "MOV     R1, R6\n"
                 "MOV     R0, R6\n"				//ASM1989 -> In sx200 was:  "MOV     R0, R5\n"
                 "BL      sub_FF872C74\n"      //  ASM1989 -> In sx200 was: FF857508 LOCATION: Mounter.c:0
                 "LDR     R0, [R4,#0x38]\n"		//  ASM1989 -> In sx200 was: LDR     R6, [R4,#0x3C]
                 "BL      sub_FF873ADC\n"		//  ASM1989 -> In sx200 was: FF857C30
                 "CMP     R0, #0\n"
                 "STREQ   R0, [R4,#0x6C]\n"	//  ASM1989 -> In sx200 was: 0x70
                 "MOV     R0, R6\n"				//ASM1989 -> In sx200 was:  "MOV     R0, R5\n"  ??????
                 "BL      sub_FF872D04\n"		//ASM1989 -> In sx200 was: FF8571B0
                 "MOV     R0, R6\n"				//ASM1989 -> In sx200 was:  "MOV     R0, R5\n"??????
                "BL      sub_FF873064_my\n"   //  ASM1989 -> In sx200 was:  FF8574A4_my
                                                // ------------------->




                 "MOV     R5, R0\n"				//ASM1989 -> In sx200 was:  "MOV     R7, R0\n"
                 "MOV     R0, R6\n"				//ASM1989 -> In sx200 was:  "MOV     R0, R5\n"??????
                 "BL      sub_FF873294\n"          //   LOCATION: Mounter.c:0 ASM1989 -> In sx200 was: FF857508
                 "LDR     R6, [R4,#0x3C]\n"      //ASM1989 -> In sx200 was:  "LDR     R1, [R4,#0x3C]\n"
                 "AND     R7, R5, R0\n"      //ASM1989 -> In sx200 was:  "AND     R2, R7, R0\n"
                 "CMP     R6, #0\n"           //ASM1989 -> In sx200 was:   "CMP     R1, #0\n"
                 "LDR     R1, [R4,#0x38]\n"          //ASM1989 -> In sx200 was:   "MOV     R0, #0\n"
                 "MOVEQ   R0, #0x80000001\n"
                 "MOV     R5, #0\n"				//ASM1989 -> New in sx210

                 "BEQ     loc_FF8734EC\n"		 //ASM1989 -> In sx200 was: FF8577AC
                 "LDR     R3, [R4,#0x2C]\n"
                 "MOV     R0, R1\n"
                 "BL      sub_FF8727EC\n"		//ASM1989 -> New in sx210  why ????????
                 "CMP     R0, #0\n"		      //ASM1989 -> In sx200 was:  "CMP     R3, #2\n"
                 "MOVNE   R5, #4\n"			//ASM1989 -> In sx200 was:   "MOVEQ   R0, #4\n"
                 "CMP     R6, #5\n"			//ASM1989 -> In sx200 was:  "CMP     R1, #5\n"
                 "ORRNE   R0, R5, #1\n"		//ASM1989 -> In sx200 was: R0, R0
                 "BICEQ   R0, R5, #1\n"		//ASM1989 -> In sx200 was: R0, R0
                 "CMP     R7, #0\n"			//ASM1989 -> In sx200 was: R2
                 "BICEQ   R0, R0, #2\n"
                 "ORREQ   R0, R0, #0x80000000\n"
                 "BICNE   R0, R0, #0x80000000\n"
                 "ORRNE   R0, R0, #2\n"
 "loc_FF8734EC:\n"								//ASM1989 -> In sx200 was: FF8577AC
                 "CMP     R8, #7\n"						//ASM1989 -> In sx200 was: R6
                 "STR     R0, [R4,#0x40]\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "MOV     R0, R8\n"				//ASM1989 -> In sx200 was: R6
                 "BL      sub_FF87340C\n"		//ASM1989 -> In sx200 was:
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R8,LR}\n"
                 "LDREQ   R0, =0xFF873538\n"     //ASM1989 -> In sx200 was:"LDREQ   R0, =0xFF8579A8\n"   // ; "EMEM MOUNT ERROR!!!"
                 "BEQ     sub_FF81177C\n"        //ASM1989 -> In sx200 was:  FF8115A8// qPrintf
                 "LDMFD   SP!, {R4-R8,PC}\n"

 );
}





void __attribute__((naked,noinline)) sub_FF873064_my() {  //  ASM1989 -> In sx200 was:  FF8574A4_my
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R5, R0\n"
                 "LDR     R0, =0x39390\n"       //ASM1989 -> In sx200 was:  0x11840
                 "ADD     R4, R0, R5,LSL#7\n"
                 "LDR     R0, [R4,#0x6C]\n"     //ASM1989 -> In sx200 was:  0x70
                 "TST     R0, #2\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R5\n"
                 "BL      sub_FF872D84_my\n"    //ASM1989 -> Mounter.c__0 In sx200 was:     sub_FF857234_my
                 			                 // ------------------>
                 "CMP     R0, #0\n"
                  							//In sx200 there was: "LDMEQFD SP!, {R4-R6,PC}\n"
                 "LDRNE   R0, [R4,#0x38]\n"		//ASM1989 -> In sx200 was: LDR
                 "MOVNE   R1, R5\n"				//ASM1989 -> In sx200 was: MOV
                 "BLNE    sub_FF872F20\n"     //ASM1989 -> In sx200 was: "sub_FF8573A0\n"  //Mounter.c:0
                 // New in sx210
                 "LDR     R2, =0x39410\n"
                 "ADD     R1, R5, R5,LSL#4\n"
                 "LDR     R1, [R2,R1,LSL#2]\n"
                 "CMP     R1, #4\n"
                 "BEQ     loc_FF8730C4\n"
                 // sx200 shared code
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF87287C\n"		//ASM1989 -> In sx200 was:FF856CC0

"loc_FF8730C4:\n"								    // New in sx210
                 "CMP     R0, #0\n"
                 "LDRNE   R1, [R4,#0x6C]\n"	//ASM1989 -> In sx200 was:  0x70
                 "ORRNE   R1, R1, #2\n"
                 "STRNE   R1, [R4,#0x6C]\n"    //ASM1989 -> In sx200 was:  0x70
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

//Next step "THE BEAST":



void __attribute__((naked,noinline)) sub_FF872D84_my() { //ASM1989 -> Mounter.c__0 In sx200 was:     sub_FF857234_my
 asm volatile(
                 "STMFD   SP!, {R4-R10,LR}\n"		//ASM1989 -> In sx200 was: "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R9, R0\n"					//ASM1989 -> In sx200 was:  R8
                 "LDR     R0, =0x39390\n"				//ASM1989 -> In sx200 was: 0x11840
                 "MOV     R8, #0\n"				//ASM1989 -> In sx200 was:  R7
                 "ADD     R5, R0, R1,LSL#7\n"
                 "LDR     R0, [R5,#0x3C]\n"
                 "MOV     R7, #0\n"				//ASM1989 -> In sx200 was:  R6
                 "CMP     R0, #7\n"
                 "MOV     R6, #0\n"	            // New in sx210
                 "ADDLS   PC, PC, R0,LSL#2\n"
/*
//OLD SX200 block

                 "B       loc_FF857384\n"
"loc_FF85725C:\n"
                 "B       loc_FF857294\n"
"loc_FF857260:\n"
                 "B       loc_FF85727C\n"
"loc_FF857264:\n"
                 "B       loc_FF85727C\n"
"loc_FF857268:\n"
                 "B       loc_FF85727C\n"
"loc_FF85726C:\n"
                 "B       loc_FF85727C\n"
"loc_FF857270:\n"
                 "B       loc_FF85737C\n"
"loc_FF857274:\n"
                 "B       loc_FF85727C\n"
"loc_FF857278:\n"
                 "B       loc_FF85727C\n"
"loc_FF85727C:\n"
*/
                 "B       loc_FF872EDC\n"
"loc_FF872DB0:\n"
                 "B       loc_FF872DE8\n"
"loc_FF872DB4:\n"
                 "B       loc_FF872DD0\n"
"loc_FF872DB8:\n"
                 "B       loc_FF872DD0\n"
"loc_FF872DBC:\n"
                 "B       loc_FF872DD0\n"
"loc_FF872DC0:\n"
                 "B       loc_FF872DD0\n"
"loc_FF872DC4:\n"
                 "B       loc_FF872ED4\n"
"loc_FF872DC8:\n"
                 "B       loc_FF872DD0\n"
"loc_FF872DCC:\n"
                 "B       loc_FF872DD0\n"
"loc_FF872DD0:\n"

										// ; jumptable FF872DA8 entries 1-4,6,7
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF88B9EC\n"	//ASM1989 -> In sx200 was:FF86EC80
                 "MOVS    R4, R0\n"
                 "BNE     loc_FF872DF0\n"	//ASM1989 -> In sx200 was:FF85729C
"loc_FF872DE8:\n"							//ASM1989 -> In sx200 was:FF857294
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R10,PC}\n" //ASM1989 -> In sx200 was:"LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF872DF0:\n"							 //ASM1989 -> In sx200 was:FF85729C
                 "LDR     R12, [R5,#0x50]\n"	 //ASM1989 -> In sx200 was:0x4C
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R9\n"				 //ASM1989 -> In sx200 was:"MOV     R0, R8\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF872E1C\n"	 //ASM1989 -> In sx200 :FF8572C8
                 "MOV     R0, #2\n"
                 "BL      sub_FF88BB38\n"       // ASM1989 -> In sx200 :FF86EDCC//__ExMemMan.c__0 ; LOCATION: ExMemMan.c:0
                 "B       loc_FF872DE8\n"      //ASM1989 -> In sx200 :FF857294
"loc_FF872E1C:\n"						      //ASM1989 -> In sx200 :FF8572C8
                 "LDR     R1, [R5,#0x64]\n"   //ASM1989 -> In sx200 :0x68
                 "MOV     R0, R9\n"				//ASM1989 -> In sx200 was:"MOV     R0, R8\n"
                 "BLX     R1\n"

//Allready inserted code

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

                 "LDRB    R1, [R4,#0x1C9]\n"
                 "LDRB    R3, [R4,#0x1C8]\n"
                 "LDRB    R12, [R4,#0x1CC]\n"
                 "MOV     R1, R1,LSL#24\n"
                 "ORR     R1, R1, R3,LSL#16\n"
                 "LDRB    R3, [R4,#0x1C7]\n"
                 "LDRB    R2, [R4,#0x1BE]\n"
            //     "LDRB    LR, [R4,#0x1FF]\n"          //remains commented as in sx200
                 "ORR     R1, R1, R3,LSL#8\n"
                 "LDRB    R3, [R4,#0x1C6]\n"
                 "CMP     R2, #0\n"
                 "CMPNE   R2, #0x80\n"
                 "ORR     R1, R1, R3\n"
                 "LDRB    R3, [R4,#0x1CD]\n"
                 "MOV     R3, R3,LSL#24\n"
                 "ORR     R3, R3, R12,LSL#16\n"
                 "LDRB    R12, [R4,#0x1CB]\n"
                 "ORR     R3, R3, R12,LSL#8\n"
                 "LDRB    R12, [R4,#0x1CA]\n"
                 "ORR     R3, R3, R12\n"
          //       "LDRB    R12, [R4,#0x1FE]\n"			//remains commented as in sx200
          												// Left as in sx200
                 "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
                 "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.

                 // "MOV     R4, #0\n"    //ASM1989 -> It was not present in sx210 ??



                 "BNE     loc_FF872EA8\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FF872EA8\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R7, R1\n"
                 "MOVEQ   R6, R3\n"
                 "MOVEQ   R4, #1\n"
                 "BEQ     loc_FF872EAC\n"      //ASM1989 -> New  In sx210
"loc_FF872EA8:\n"                 			//ASM1989 -> New  In sx210
				"MOV     R4, R8\n"			//ASM1989 -> New  In sx210
"loc_FF872EAC:\n"                            //ASM1989 -> In sx200: FF857354   //Mounter.c__0+F8j
                 "MOV     R0, #2\n"
                 "BL      sub_FF88BB38\n"    //ASM1989 -> In sx200:FF86EDCC  // LOCATION: ExMemMan.c
                 "CMP     R4, #0\n"
                 "BNE     loc_FF872EE8\n"	//ASM1989 -> In sx200:FF857390
                 "LDR     R1, [R5,#0x64]\n" //ASM1989 -> In sx200:0x68
                 "MOV     R7, #0\n"
                 "MOV     R0, R9\n"			//ASM1989 -> In sx200:"MOV     R0, R8\n"
                 "BLX     R1\n"
                 "MOV     R6, R0\n"
                 "B       loc_FF872EE8\n"	 //ASM1989 -> In sx200:FF857390
"loc_FF872ED4:\n"                            //ASM1989 -> In sx200: FF85737C
                 "MOV     R6, #0x40\n"
                 "B       loc_FF872EE8\n"		//ASM1989 -> In sx200:FF857390
"loc_FF872EDC:\n"                            //ASM1989 -> In sx200: FF857384
                 "LDR     R1, =0x597\n"       //ASM1989 -> In sx200:0x5C9
                 "LDR     R0, =0xFF872EFC\n"     ///ASM1989 -> In sx200:FF857190 //"Mounter.c"
                 "BL      sub_FF81EB14\n"        ///ASM1989 -> In sx200:FF81B284 // DebugAssert
"loc_FF872EE8:\n"                                //ASM1989 -> In sx200:FF857390
                 "STR     R7, [R5,#0x44]!\n"
                 "STMIB   R5, {R6,R8}\n"
                 "MOV     R0, #1\n"
                 "LDMFD   SP!, {R4-R10,PC}\n"




                //OLD SX200 3 last lines
                /*
                "MOV     R0, #1\n"
                 "STR     R6, [R5,#4]\n"
                 "LDMFD   SP!, {R4-R8,PC}\n" */
 );
}

// ASM1989 base From the sd980 since it uses rotary too code from sx210 at FF862024
void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n"
                "SUB     SP, SP, #0x2C\n"
                "BL      sub_FF862410\n"
                "LDR     R1, =0x24C8\n"	     // in sd980 was: 0x23E4
                "LDR     R9, =0xFFB65A50\n"
                "MOV     R0, #0\n"
                "ADD     R2, SP, #0x14\n"
                "ADD     R3, SP, #0x18\n"
                "ADD     R10, SP, #0xc\n"
                "ADD     R8, SP, #0x10\n"
                "MOV     R7, #0\n"

"loc_FF862050:\n"
                "ADD     R3, SP, #0x18\n"
                "ADD     R12, R3, R0,LSL#1\n"
                "ADD     R2, SP, #0x14\n"
                "STRH    R7, [R12]\n"
                "ADD     R12, R2, R0,LSL#1\n"
                "STRH    R7, [R12]\n"
                "STR     R7, [R8,R0,LSL#2]\n"
                "STR     R7, [R10,R0,LSL#2]\n"
                "ADD     R0, R0, #1\n"
                "CMP     R0, #1\n"
                "BLT     loc_FF862050\n"

"loc_FF86207C:\n"

                "LDR     R0, =0x24C8\n"			// in sd980 was: 0x23E4
                "MOV     R2, #0\n"
                "LDR     R0, [R0,#8]\n"
                "ADD     R1, SP, #0x4\n"
                "BL      sub_FF839B88\n"
                "TST     R0, #1\n"
                "LDRNE   R1, =0x25C\n"			// in sd980 was: 0x226
                "LDRNE   R0, =0xFF862348\n"		//; "JogDial.c"
                "BLNE    sub_FF81EB14\n"		//DebugAssert
                "LDR     R0, [SP,#0x4]\n"
                "AND     R4, R0, #0xFF\n"
                "AND     R0, R0, #0xFF00\n"
                "CMP     R0, #0x100\n"
                "BEQ     loc_FF862100\n"
                "CMP     R0, #0x200\n"
                "BEQ     loc_FF862138\n"
                "CMP     R0, #0x300\n"
                "BEQ     loc_FF862394\n"
                "CMP     R0, #0x400\n"
                "BNE     loc_FF86207C\n"
                "CMP     R4, #0\n"
                "LDRNE   R1, =0x30E\n"		// in sd980 was: 0x2CA
                "LDRNE   R0, =0xFF862348\n"		//; "JogDial.c"
                "BLNE    sub_FF81EB14\n"		//DebugAssert
                "LDR     R2, =0xFFB65A3C\n"
                "ADD     R0, R4, R4,LSL#2\n"
                "LDR     R1, [R2,R0,LSL#2]\n"
                "STR     R7, [R1]\n"
                "MOV     R1, #1\n"
                "ADD     R0, R2, R0,LSL#2\n"

"loc_FF8620F4:\n"
                "LDR     R0, [R0,#8]\n"
                "STR     R1, [R0]\n"
                "B       loc_FF86207C\n"		// in sd980 was:

"loc_FF862100:\n"
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      sub_FF83A2DC\n"   //sleep ASM1989 for sx210
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
                "LDR     R5, =0x24D8\n"				// in sd980 was:0x23F4
                "LDR     R0, [R5,R4,LSL#2]\n"
                "BL      sub_FF83AB20\n"/*
//------------------  added code ---------------------  Allready commented from the sd980 port
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                //"BL      sub_FF838DBC\n"//sleep
                "BL      sub_FF83865C\n"//sleep
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
*/
                "LDR     R2, =0xFF861F8C\n"
                "ADD     R1, R2, #0\n"
                "ORR     R3, R4, #0x200\n"
                "MOV     R0, #0x28\n"
                "BL      sub_FF83AA3C\n"
                "TST     R0, #1\n"
                "CMPNE   R0, #0x15\n"
                "STR     R0, [R10,R4,LSL#2]\n"
                "BEQ     loc_FF86207C\n"
                "LDR     R1, =0x271\n"			// in sd980 was 0x23B
                "B       loc_FF862338\n"

"loc_FF862138:\n"
                "LDR     R1, =0xFFB65A3C\n"
                "ADD     R0, R4, R4,LSL#2\n"
                "STR     R0, [SP,#0x28]\n"
                "ADD     R0, R1, R0,LSL#2\n"
                "STR     R0, [SP,#0x24]\n"
                "LDR     R0, [R0,#4]\n"
                "LDR     R0, [R0]\n"
                "MOV     R2, R0,ASR#16\n"
                "ADD     R0, SP, #0x18\n"
                "ADD     R0, R0, R4,LSL#1\n"
                "STR     R0, [SP,#0x20]\n"
                "STRH    R2, [R0]\n"
                "ADD     R0, SP, #0x14\n"
                "ADD     R0, R0, R4,LSL#1\n"
                "STR     R0, [SP,#0x1c]\n"
                "LDRSH   R3, [R0]\n"
                "SUB     R0, R2, R3\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF8621C8\n"
                // chages from here from sd980 code
                "CMP     R0, #0\n"
                "BEQ     loc_FF8622F0\n"
                "LDR     R5, =0x24D8\n"
                "LDR     R0, [R5,R4,LSL#2]\n"
                "BL      sub_FF83AB20\n"
                "LDR     R2, =0xFF861F98\n"
                "ADD     R1, R2, #0\n"
                "ORR     R3, R4, #0x300\n"
                "MOV     R0, #0x1F4\n"
                "BL      sub_FF83AA3C\n"
                "TST     R0, #1\n"
                "CMPNE   R0, #0x15\n"
                "STR     R0, [R5,R4,LSL#2]\n"
                "BEQ     loc_FF8622F0\n"
                "LDR     R1, =0x28E\n"
                "B       loc_FF8622E8\n"
      			//end of changes from sd980 original
"loc_FF8621C8:\n"
                "MOV     R1, R0\n"
                "RSBLT   R0, R0, #0\n"
                "MOVLE   R5, #0\n"
                "MOVGT   R5, #1\n"
                "CMP     R0, #0xFF\n"
                "BLS     loc_FF862208\n"
                "CMP     R1, #0\n"
                "RSBLE   R0, R3, #0xFF\n"
                "ADDLE   R0, R0, #0x7F00\n"
                "ADDLE   R0, R0, R2\n"
                "RSBGT   R0, R2, #0xFF\n"
                "ADDGT   R0, R0, #0x7F00\n"
                "ADDGT   R0, R0, R3\n"
                "ADD     R0, R0, #0x8000\n"
                "ADD     R0, R0, #1\n"
                "EOR     R5, R5, #1\n"

"loc_FF862208:\n"
                "STR     R0, [SP,#0x8]\n"
                "LDR     R0, [R8,R4,LSL#2]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FF862258\n"
                "LDR     R1, =0xFFB65A34\n"
                "ADD     R1, R1, R4,LSL#3\n"
                "LDR     R1, [R1,R5,LSL#2]\n"
                "CMP     R1, R0\n"
                "BEQ     loc_FF862274\n"
                "ADD     R11, R4, R4,LSL#1\n"
                "ADD     R6, R9, R11,LSL#2\n"
                "LDRB    R0, [R6,#9]\n"
                "CMP     R0, #1\n"
                "LDREQ   R0, [R6,#4]\n"
                "BLEQ    sub_FF897278\n"
                "LDRB    R0, [R6,#8]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FF862274\n"
                "LDR     R0, [R9,R11,LSL#2]\n"
                "B       loc_FF862270\n"

"loc_FF862258:\n"
                "ADD     R0, R4, R4,LSL#1\n"
                "ADD     R1, R9, R0,LSL#2\n"
                "LDRB    R1, [R1,#8]\n"
                "CMP     R1, #1\n"
                "BNE     loc_FF862274\n"
                "LDR     R0, [R9,R0,LSL#2]\n"

"loc_FF862270:\n"
                "BL      sub_FF897278\n"

"loc_FF862274:\n"
                "LDR     R0, =0xFFB65A34\n"
                "LDR     R1, [SP,#0x8]\n"
                "ADD     R6, R0, R4,LSL#3\n"
                "LDR     R0, [R6,R5,LSL#2]\n"
                "BL      sub_FF8971A8\n"
                "LDR     R0, [R6,R5,LSL#2]\n"
                "STR     R0, [R8,R4,LSL#2]\n"
                "LDR     R0, [SP,#0x20]\n"
                "LDR     R1, [SP,#0x1c]\n"
                "LDRH    R0, [R0]\n"
                "STRH    R0, [R1]\n"
                "ADD     R0, R4, R4,LSL#1\n"
                "ADD     R0, R9, R0,LSL#2\n"
                "LDRB    R0, [R0,#9]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FF8622F0\n"
                "LDR     R5, =0x24D8\n"   // in sd980 was: 0x23F4
                "LDR     R0, [R5,R4,LSL#2]\n"
                "BL      sub_FF83AB20\n"
                "LDR     R2, =0xFF861F98\n"  //LOCATION: JogDial.c:824
                "ADD     R1, R2, #0\n"
                "ORR     R3, R4, #0x300\n"
                "MOV     R0, #0x1F4\n"
                "BL      sub_FF83AA3C\n"
                "TST     R0, #1\n"
                "CMPNE   R0, #0x15\n"
                "STR     R0, [R5,R4,LSL#2]\n"
                //Diferences from sd980
                "BEQ     loc_FF8622F0\n"
                "MOV     R1, #0x2E8\n"
                ""
 "loc_FF8622E8:\n"
 				"LDR     R0, =0xFF862348\n"  // "JogDial.c"
 				"BL      sub_FF81EB14\n"		//DebugAssert"

 				 //End Diferences from sd980
"loc_FF8622F0:\n"

                "ADD     R0, R4, R4,LSL#1\n"
                "ADD     R0, R8, R0,LSL#2\n"
                "LDRB    R0, [R0,#0xA]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FF862378\n"
                "LDR     R0, =0x24C8\n"
                "LDR     R0, [R0,#0xC]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FF862378\n"
                "LDR     R2, =0xFF861F8C\n"
                "ADD     R1, R2, #0\n"
                "ORR     R3, R4, #0x400\n"
                "BL      sub_FF83AA3C\n"
                "TST     R0, #1\n"
                "CMPNE   R0, #0x15\n"
                "STR     R0, [R10,R4,LSL#2]\n"
                "BEQ     loc_FF86207C\n"
                "LDR     R1, =0x2F3\n"

"loc_FF862338:\n"
                "LDR     R0, =0xFF862348\n"  // "JogDial.c"
                "BL      sub_FF81EB14\n"		//DebugAssert"
                "B       loc_FF86207C\n"

"loc_FF862378:\n"
                "LDR     R1, =0xFFB65A3C\n"
                "LDR     R0, [SP,#0x28]\n"
                "LDR     R0, [R1,R0,LSL#2]\n"
                "STR     R7, [R0]\n"
                "LDR     R0, [SP,#0x24]\n"
                "MOV     R1, #1\n"
                "B       loc_FF8620F4\n"

"loc_FF862394:\n"
                "LDR     R0, [R9,R4,LSL#2]\n"
                "CMP     R0, #0\n"
                "MOVEQ   R1, #0x2BC\n"
                "LDREQ   R0, =0xFF862348\n"  // "JogDial.c"
                "BLEQ    sub_FF81EB14\n"		//DebugAssert"
                "ADD     R0, R4, R4,LSL#1\n"
                "ADD     R0, R9, R0,LSL#2\n"
                "LDR     R0, [R0,#4]\n"
                "BL      sub_FF897278\n"
                "STR     R7, [R8,R4,LSL#2]\n"
                "B       loc_FF86207C\n"

 );
}



/*

void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile(
                 "STMFD   SP!, {R3-R11,LR}\n"
                 "BL      sub_FF84871C\n"        // __JogDial.c__416 ; LOCATION: JogDial.c:416
                 "LDR     R11, =0x80000B01\n"
                 "LDR     R8, =0xFFAFE608\n"
                 "LDR     R7, =0xC0240000\n"
                 "LDR     R6, =0x24E4\n"
                 "MOV     R9, #1\n"
                 "MOV     R10, #0\n"
"loc_FF84858C:\n"
                 "LDR     R3, =0x1BB\n"
                 "LDR     R0, [R6,#0xC]\n"
                 "LDR     R2, =0xFF8487C4\n"     // "JogDial.c"
                 "MOV     R1, #0\n"
                 "BL      sub_FF827638\n"
                 "MOV     R0, #0x28\n"
                 "BL      sub_FF827490\n"        // eventproc_export_SleepTask ; LOCATION: KerSys.c:0
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
                 "LDR     R0, [R7,#0x104]\n"
                 "MOV     R0, R0,ASR#16\n"
                 "STRH    R0, [R6]\n"
                 "LDRSH   R2, [R6,#2]\n"
                 "SUB     R1, R0, R2\n"
                 "CMP     R1, #0\n"
                 "BEQ     loc_FF848650\n"
                 "MOV     R5, R1\n"
                 "RSBLT   R5, R5, #0\n"
                 "MOVLE   R4, #0\n"
                 "MOVGT   R4, #1\n"
                 "CMP     R5, #0xFF\n"
                 "BLS     loc_FF848604\n"
                 "CMP     R1, #0\n"
                 "RSBLE   R1, R2, #0xFF\n"
                 "ADDLE   R1, R1, #0x7F00\n"
                 "ADDLE   R0, R1, R0\n"
                 "RSBGT   R0, R0, #0xFF\n"
                 "ADDGT   R0, R0, #0x7F00\n"
                 "ADDGT   R0, R0, R2\n"
                 "ADD     R5, R0, #0x8000\n"
                 "ADD     R5, R5, #1\n"
                 "EOR     R4, R4, #1\n"
"loc_FF848604:\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF848648\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF848630\n"
                 "LDR     R1, [R8,R4,LSL#2]\n"
                 "CMP     R1, R0\n"
                 "BEQ     loc_FF848638\n"
                 "LDR     R0, =0xB01\n"
                 "BL      sub_FF87B9B8\n"
"loc_FF848630:\n"
                 "MOV     R0, R11\n"
                 "BL      sub_FF87B9B8\n"
"loc_FF848638:\n"
                 "LDR     R0, [R8,R4,LSL#2]\n"
                 " MOV     R1, R5\n"
                 "STR     R0, [R6,#0x1C]\n"
                 "BL      sub_FF87B8E8\n"
"loc_FF848648:\n"
                 "LDRH    R0, [R6]\n"
                 "STRH    R0, [R6,#2]\n"
"loc_FF848650:\n"
                 "STR     R10, [R7,#0x100]\n"
                 "STR     R9, [R7,#0x108]\n"
                 "LDR     R0, [R6,#0x10]\n"
                 "CMP     R0, #0\n"
                 "BLNE    sub_FF827490\n"        // eventproc_export_SleepTask ; LOCATION: KerSys.c:0
                 "B       loc_FF84858C\n"
 );
}


*/

