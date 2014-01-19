#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"
//#include "stdlib.h"


extern void task_FileWrite();

//IXUS 1000 100F

#define LED_PR 0xC0220138   // -> ASM1989 08.24.2010 found at  FF91E080  in sx200 was FF8E73D0
    void __attribute__((naked,noinline)) blink()
{
	volatile long *p=(void*)LED_PR;
	int i;
    int cnt =100;
	for(;cnt>0;cnt--){
		p[0]=0x46;

		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
		p[0]=0x44;
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
	}
	shutdown();
}

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
    if(tcb->entry == (void*)task_FileWrite)         tcb->entry = (void*)filewritetask;

}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


void __attribute__((naked,noinline)) boot() {
    asm volatile (
				 //"B		  sub_FF81000C\n" // work
                 "LDR R1, =0xC0410000\n"
				  "MOV R0, #0\n"
				  "STR R0, [R1]\n"
				  "MOV R1, #0x78\n"
				  "MCR p15, 0, R1,c1,c0\n"			// control reg
				  "MOV R1, #0\n"
				  "MCR p15, 0, R1,c7,c10, 4\n"		// drain write buffer
				  "MCR p15, 0, R1,c7,c5\n"			// flush instruction cache
				  "MCR p15, 0, R1,c7,c6\n"			// flush data cache
				  "MOV R0, #0x3D\n"					// size 2GB base 0x00000000
				  "MCR p15, 0, R0,c6,c0\n"
				  "MOV R0, #0xC000002F\n"			// size 16M base 0xc0000000
				  "MCR p15, 0, R0,c6,c1\n"
				  "MOV R0, #0x35\n"				     // size 128M base 0x00000000 (s90 is 64M)
				  "MCR p15, 0, R0,c6,c2\n"
				  "MOV R0, #0x40000035\n"			// size 128M base 0x40000000 (s90 is 64M)
				  "MCR p15, 0, R0,c6,c3\n"
				  "MOV R0, #0x80000017\n"			// size  4k base 0x80000000
				  "MCR p15, 0, R0,c6,c4\n"
				  "LDR R0, =0xFF80002D\n"			// size  8M base 0xff800000
				  "MCR p15, 0, R0,c6,c5\n"
				  "MOV R0, #0x34\n"
				  "MCR p15, 0, R0,c2,c0\n"
				  "MOV R0, #0x34\n"
				  "MCR p15, 0, R0,c2,c0, 1\n"
				  "MOV R0, #0x34\n"
				  "MCR p15, 0, R0,c3,c0\n"
				  "LDR R0, =0x3333330\n"
				  "MCR p15, 0, R0,c5,c0, 2\n"
				  "LDR R0, =0x3333330\n"
				  "MCR p15, 0, R0,c5,c0, 3\n"
				  "MRC p15, 0, R0,c1,c0\n"
				  "ORR R0, R0, #0x1000\n"
				  "ORR R0, R0, #4\n"
				  "ORR R0, R0, #1\n"
				  "MCR p15, 0, R0,c1,c0\n"
				  "MOV R1, #0x80000006\n"
				  "MCR p15, 0, R1,c9,c1\n"
				  "MOV R1, #6\n"
				  "MCR p15, 0, R1,c9,c1, 1\n"
				  "MRC p15, 0, R1,c1,c0\n"
				  "ORR R1, R1, #0x50000\n"
				  "MCR p15, 0, R1,c1,c0\n"
				  "LDR R2, =0xC0200000\n"
				  "MOV R1, #1\n"
				  "STR R1, [R2,#0x10C]\n"
				  "MOV R1, #0xFF\n"
				  "STR R1, [R2,#0xC]\n"
				  "STR R1, [R2,#0x1C]\n"
				  "STR R1, [R2,#0x2C]\n"
				  "STR R1, [R2,#0x3C]\n"
				  "STR R1, [R2,#0x4C]\n"
				  "STR R1, [R2,#0x5C]\n"
				  "STR R1, [R2,#0x6C]\n"
				  "STR R1, [R2,#0x7C]\n"
				  "STR R1, [R2,#0x8C]\n"
				  "STR R1, [R2,#0x9C]\n"
				  "STR R1, [R2,#0xAC]\n"
				  "STR R1, [R2,#0xBC]\n"
				  "STR R1, [R2,#0xCC]\n"
				  "STR R1, [R2,#0xDC]\n"
				  "STR R1, [R2,#0xEC]\n"
				  "STR R1, [R2,#0xFC]\n"
				  "LDR R1, =0xC0400008\n"
				  "LDR R2, =0x430005\n"
				  "STR R2, [R1]\n"
				  "MOV R1, #1\n"
				  "LDR R2, =0xC0243100\n"
				  "STR R2, [R1]\n"
				  "LDR R2, =0xC0242010\n"
				  "LDR R1, [R2]\n"
				  "ORR R1, R1, #1\n"
				  "STR R1, [R2]\n"
				  "LDR R0, =0xFFC56CD0\n"  // changed from 100 was  FFC56CC8
				  "LDR R1, =0x1900\n"
				  "LDR R3, =0x10728\n"  //changed from 100D
"loc_FF81013C:\n"

				  "CMP R1, R3\n"
				  "LDRCC R2, [R0],#4\n"
				  "STRCC R2, [R1],#4\n"
				  "BCC loc_FF81013C\n"
				  "LDR R1, =0x172BF8\n"
				  "MOV R2, #0\n"
"loc_FF810154:\n"
				  "CMP R3, R1\n"
				  "STRCC R2, [R3],#4\n"
				  "BCC loc_FF810154\n"
 				  "B sub_FF810354_my\n"
                            //---------->
      );
}


void __attribute__((naked,noinline)) sub_FF810354_my() { // ASM1989 -> In sx200 was:  sub_FF8101A0_my



   *(int*)0x1938=(int)taskHook;   //was 1934 in sx200 if 1938 hangs
   *(int*)0x193C=(int)taskHook;


	if ((*(int*) 0xC022010C) & 1)					// look at play switch
		*(int*)(0x254C) = 0x400000;					// start in play mode
	else
		*(int*)(0x254C) = 0x200000;					// start in rec mode

   asm volatile (
	     "LDR R0, =0xFF8103CC\n"
	   	 "MOV R1, #0\n"
	   	 "LDR R3, =0xFF810404\n"
"loc_FF810360:\n"
	   	 "CMP R0, R3\n"
	   	 "LDRCC R2, [R0],#4\n"
	   	 "STRCC R2, [R1],#4\n"
	   	 "BCC loc_FF810360\n"
	   	 "LDR R0, =0xFF810404\n"
	   	 "MOV R1, #0x4B0\n"
	   	 "LDR R3, =0xFF810618\n"
"loc_FF81037C:\n"
	   	 "CMP R0, R3\n"
	   	 "LDRCC R2, [R0],#4\n"
	   	 "STRCC R2, [R1],#4\n"
	   	 "BCC loc_FF81037C\n"
	   	 "MOV R0, #0xD2\n"
	   	 "MSR CPSR_cxsf, R0\n"
	   	 "MOV SP, #0x1000\n"
	   	 "MOV R0, #0xD3\n"
	   	 "MSR CPSR_cxsf, R0\n"
	   	 "MOV SP, #0x1000\n"
	   	 "LDR R0, =0x6C4\n"  // in 100D was: diferent  "LDR R0, =0xFF8103C0\n"
	   	 "LDR R2, =0xEEEEEEEE\n"
	   	 "MOV R3, #0x1000\n"
"loc_FF8103B0:\n"
	   	 "CMP R0, R3\n"
	   	 "STRCC R2, [R0],#4\n"
	   	 "BCC loc_FF8103B0\n"
	   	 "BL sub_FF811198_my\n"
 							//------------>

//this is not disasmbled in 100F asuming is like 100D

"loc_FF8103C0:\n"
	   	 "ANDEQ R0, R0, R4,ASR#13\n"
"loc_FF8103C4:\n"
	    	"ANDEQ R0, R0, R0,ROR R6\n"
"loc_FF8103C8:\n"
	    	"ANDEQ R0, R0, R4,ROR R6\n"
"loc_FF8103CC:\n"
   	 "NOP\n"
	 "LDR PC, =0xFF810618\n"
     );
}

void __attribute__((naked,noinline)) sub_FF811198_my() {
     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFB87550\n" // sub_FFB8754C 100D
                 //v4 stuff all copied from s95 its the same in principle
/*
                 "		MOV	R0, #0x53000 \n"
				 "		STR	R0, [SP,#4] \n"

				 //"		LDR	R0, =0x172BF8 \n"           // old code
				 "		LDR	R0, =new_sa \n"					// chdk patched
				 "		LDR R0, [R0] \n"                    // chdk patched

				 "		LDR	R1, =0x379C00 \n"
				 "		STR	R0, [SP,#8] \n"
				 "		RSB	R0, R0,	#0x1F80 \n"
				 "		ADD	R0, R0,	#0x370000 \n"
				 "		STR	R0, [SP,#0x0c] \n"
				 "		LDR	R0, =0x371F80 \n"
				 "		STR	R1, [SP,#0] \n"
				 "		STRD	R0, [SP,#0x10] \n"
				 "		MOV	R0, #0x22 \n"
				 "		STR	R0, [SP,#0x18] \n"
				 "		MOV	R0, #0x68 \n"
				 "		STR	R0, [SP,#0x1c] \n"
				 "		LDR	R0, =0x19B \n"

*/



                 //v3 stuff

                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
                 "LDR     R0, =new_sa\n"        // +
                 "LDR     R0, [R0]\n"           // +
                 //"LDR     R2, =0x172BF8\n"
                 "LDR     R1, =0x379C00\n"
                 "STR     R0, [SP,#8]\n"
                 //"SUB     R0, R1, R0\n"
                 "RSB     R0, R0, #0x1F80\n"   // new in this cam
                 "ADD     R0, R0, #0x370000\n" // new in this cam
                 "STR	  R0, [SP,#0x0c]\n"  //changed
                 "LDR     R0, =0x371F80\n"// new in this cam
				//copied from s95
				"STR	R1, [SP,#0] \n"
				"STRD	R0, [SP,#0x10] \n"
				"MOV	R0, #0x22 \n"
				"STR	R0, [SP,#0x18] \n"
				"MOV	R0, #0x68 \n"
				"STR	R0, [SP,#0x1c] \n"
				"LDR	R0, =0x19B \n"




                "LDR     R1, =sub_FF815EE0_my\n"  // chdk patched

			  //"LDR     R1, =0xFF815EE0\n"    // old code


                 									//------------>



                 "STR     R0, [SP,#0x20]\n"
                 "MOV     R0, #0x96\n"
                 "STR     R0, [SP,#0x24]\n"
                 //"MOV     R0, #0x78\n"      // looks like its not in 100F
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


/*
//copied from s95 // not work
"		MOV	R0, #0x96 \n"
"		STR	R0, [SP,#0x24] \n"
"		STR	R0, [SP,#0x28] \n"
"		MOV	R0, #0x64 \n"
"		STR	R0, [SP,#0x2c] \n"
"		MOV	R0, #0 \n"
"		STR	R0, [SP,#0x30] \n"
"		STR	R0, [SP,#0x34] \n"
"		MOV	R0, #0x10 \n"
"		STR	R0, [SP,#0x5c] \n"
"		MOV	R0, #0x800 \n"
"		STR	R0, [SP,#0x60] \n"
"		MOV	R0, #0xA0 \n"
"		STR	R0, [SP,#0x64] \n"
"		MOV	R0, #0x280 \n"
"		STR	R0, [SP,#0x68] \n"
"		MOV	R0, SP \n"
"		MOV	R2, #0 \n"
*/
                 "BL      sub_FF8134B8\n"

                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
     );
}

//Almost till here maybe checked

void __attribute__((naked,noinline)) sub_FF815EE0_my() {

     //v4 testing full s95 code
/*
     	asm volatile (
	 "		STMFD	SP!, {R4,LR} \n"
	 "		BL	sub_FF810B20 \n"
	 "		BL	sub_FF81A33C \n"				// dmSetup
	 "		CMP	R0, #0 \n"

	 //"		ADRLT	R0, aDmsetup \n"			// "dmSetup"
	 "		LDRLT	r0, =0xFF815FF4 \n"

	 "		BLLT	sub_FF815FD4 \n"			// err_init_task

	 "		BL	sub_FF815B1C \n"
	 "		CMP	R0, #0 \n"

	 //"		ADRLT	R0, aTermdriverinit \n"		// "termDriverInit"
	 "		LDRLT	R0, =0xFF815FFC \n"

	 "		BLLT	sub_FF815FD4 \n"			// err_init_task

	 //"		ADR	R0, a_term \n"					// "/_term"
	 "		LDR	R0, =0xFF81600C \n"

	 "		BL	sub_FF815C04 \n"				// termDeviceCreate
	 "		CMP	R0, #0 \n"

	 //"		ADRLT	R0, aTermdevicecrea \n"		// "termDeviceCreate"
	 "		LDRLT	R0, =0xFF816014 \n"

	 "		BLLT	sub_FF815FD4 \n"			// err_init_task

	 //"		ADR	R0, a_term \n"					// "/_term"
	 "		LDR	R0, =0xFF81600C \n"

	 "		BL	sub_FF813CA4 \n"
	 "		CMP	R0, #0 \n"

	 //"		ADRLT	R0, aStdiosetup \n"			// "stdioSetup"
	 "		LDRLT	R0, =0xFF816028 \n"

	 "		BLLT	sub_FF815FD4 \n"			// err_init_task
	 "		BL	sub_FF819CC4 \n"
	 "		CMP	R0, #0 \n"

	 //"		ADRLT	R0, aStdlibsetup \n"		// "stdlibSetup"
	 "		LDRLT	R0, =0xFF816034 \n"

	 "		BLLT	sub_FF815FD4 \n"			// err_init_task
	 "		BL	sub_FF81167C \n"
	 "		CMP	R0, #0 \n"

	 //"		ADRLT	R0, aArmlib_setup \n"		// "armlib_setup"
	 "		LDRLT	R0, =0xFF816040 \n"

	 "		BLLT	sub_FF815FD4 \n"			// err_init_task

	 "		LDMFD	SP!, {R4,LR} \n"

	 //"		B	sub_FF81FB54 \n"				// taskcreate_Startup
	 "		B	taskcreate_Startup_my \n"		// patched

	 "		MOV	R0, #0 \n"
	 "		LDMFD	SP!, {R3-R5,PC} \n"
	);
*/

     //v3

     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF810B20\n"
                 "BL      sub_FF81A33C\n"       // BL      dmSetup
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815FF4\n"    //Mising ; "dmSetup"
                 "BLLT    sub_FF815FD4\n"		 //Mising err_init_task
                 "BL      sub_FF815B1C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF815FFC\n"    // "termDriverInit"
                 "BLLT    sub_FF815FD4\n"	   // err_init_task
                 "LDR     R0, =0xFF81600C\n"   //  "/_term"
                 "BL      sub_FF815C04\n"	   // termDeviceCreate
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF816014\n"   //  "termDeviceCreate"
                 "BLLT    sub_FF815FD4\n"       // err_init_task
                 "LDR     R0, =0xFF81600C\n"   //  "/_term"
                 "BL      sub_FF813CA4\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF816028\n"    // "stdioSetup"
                 "BLLT    sub_FF815FD4\n"       // err_init_task
                 "BL      sub_FF819CC4\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF816034\n"    //"stdlibSetup"
                 "BLLT    sub_FF815FD4\n"       // err_init_task
                 "BL      sub_FF81167C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF816040\n"    // "armlib_setup"
                 "BLLT    sub_FF815FD4\n"       // err_init_task
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n" // ASM1989 -> at FF81FBA8
                 							//---------->
//copied from s95
"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R3-R5,PC} \n"

        );
};


// ASM1989 -> Here starts the diferences with SX200

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (

                 "STMFD   SP!, {R3-R5,LR}\n"
                 "BL      sub_FF8348CC\n"   //j_nullsub_267
                 "BL      sub_FF83D1D4\n"
                 "CMP     R0, #0\n"

                "BNE     loc_FF81FBFC\n"


                 "BL      sub_FF8370E8\n"
                 "CMP     R0, #0\n"
                "BEQ     loc_FF81FBFC\n"


                 "LDR     R4, =0xC0220000\n"



                 "LDR     R0, [R4,#0x120]\n"
                 "TST     R0, #1\n"
				 "MOVEQ   R0, #0x12C\n"




 				"BLEQ    sub_FF83B574\n"   //ASM1989 ->  eventproc_export_SleepTask



				"BL      sub_FF8348C8\n"
				"CMP     R0, #0\n"
				"BNE     loc_FF81FBFC\n"
				"BL      sub_FF833F34\n"
				"MOV     R0, #0x44\n"
				"STR     R0, [R4,#0x1C]\n"
				"BL      sub_FF834120\n"
"loc_FF81FBF8:\n"
				"B       loc_FF81FBF8\n"


"loc_FF81FBFC:\n"
				//"BL      sub_FF8348D4\n" // ASM1989 -> -- replaced for power button startup

				"BL      sub_FF8348D0\n"//ASM1989 ->  j_nullsub_268
				"BL      sub_FF83B3EC\n"

				"LDR     R1, =0x3CE000\n"
				"MOV     R0, #0\n"

				"BL      sub_FF83B834\n"
				"BL      sub_FF83B5E0\n"
				"MOV     R3, #0\n"

				"STR     R3, [SP]\n"

				"LDR     R3, =task_Startup_my\n" //  ASM1989 -> original is FF81FAF0  task_Startup   // LDR instead of ADR
                //---------------->
//ASM_SAFE("BL blink\n")
				"MOV     R2, #0\n"
				"MOV     R1, #0x19\n"
				"LDR     R0, =0xFF81FC60\n"  //aStartup  // LDR instead of ADR


				"BL      sub_FF81E8A0\n"  //eventproc_export_CreateTask
				"MOV     R0, #0\n"
				"LDMFD   SP!, {R3-R5,PC}\n"




     );
}

// TESTING S95 Code style


void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (

                 "STMFD SP!, {R4,LR}\n"

				 "BL sub_FF816594\n"  // taskcreate_ClockSave
				 "BL sub_FF835A30\n"
				 "BL sub_FF833B3C\n"
				 "BL sub_FF83D218\n"  	//j_nullsub_271
				 "BL sub_FF83D404\n"
//				 "BL sub_FF83D2AC\n" // start diskboot.bin
				 "BL sub_FF83D5AC\n"
				 "BL sub_FF81648C\n"
				 "BL sub_FF836754\n"
				 "LDR R1, =0x7C007C00\n"
				 "LDR R0, =0xC0F1800C\n"
				 "BL sub_FF835A3C\n"
				 "LDR R0, =0xC0F18010\n"
				 "MOV R1, #0\n"
//OK
				 "BL sub_FF835A3C\n"
				 "LDR R0, =0xC0F18018\n"
				 "MOV R1, #0\n"
				 "BL sub_FF835A3C\n"
				 "LDR R0, =0xC0F1801C\n"
				 "MOV R1, #0x1000\n"
				 "BL sub_FF835A3C\n"
				 "LDR R0, =0xC0F18020\n"
				 "MOV R1, #8\n"
				 "BL sub_FF835A3C\n"
//OK


				 "LDR R0, =0xC022D06C\n"
				 "MOV R1, #0xE000000\n"
				 "BL sub_FF835A3C\n"
				 "BL sub_FF8164CC\n"
//OK

				 "BL sub_FF8324F4\n"


//FAILS
//ASM_SAFE("BL blink\n")
				 "BL sub_FF83D434\n"





				 "BL sub_FF83AB90\n"
				 "BL sub_FF83D5B0\n"

              "BL      CreateTask_spytask\n"    // +
								//---------------->
                 "BL sub_FF834788\n"	//taskcreate_PhySw
);

//			CreateTask_PhySw();					// our keyboard task

//			CreateTask_spytask();				// chdk initialization


	//			 "BL      CreateTask_spytask\n"    // +
							            //---------------->


   asm volatile (


				 "BL sub_FF838CF0\n"
				 "BL sub_FF83D5C8\n"
				 "BL sub_FF8318F8\n"  //nullsub_2
				 "BL sub_FF8334A0\n"
				 "BL sub_FF83CF9C\n"  //taskcreate_Bye
				 "BL sub_FF833AF0\n"
				 "BL sub_FF83343C\n"	//taskcreate_BatteryTask
				 "BL sub_FF832528\n"
				 "BL sub_FF83E1D0\n"
				 "BL sub_FF8333F8\n"
				 "LDMFD SP!, {R4,LR}\n"
				 "B sub_FF8166B4\n"
     );
}


/*void __attribute__((naked,noinline)) CreateTask_PhySw() {
    asm volatile (
"		STMFD	SP!, {R3-R5,LR} \n"
"		LDR	R4, =0x1C34 \n"
"		LDR	R0, [R4,#0x10] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF8347BC \n"
"		MOV	R3, #0 \n"
"		STR	R3, [SP] \n"

//"		ADR	R3, task_PhySw \n"
//"		LDR R3, =sub_FF834754 \n"
//"		MOV	R2, #0x800 \n"

"		LDR	R3, =mykbd_task \n"				// PhySw Task patch
"		MOV	R2, #0x2000 \n"					// larger stack

"		MOV	R1, #0x17 \n"

//"		ADR	R0, aPhysw \n"
"		LDR	R0, =0xFF8349DC \n"				// "PhySw"

"		BL	sub_FF83B634 \n"				// KernelCreateTask
"		STR	R0, [R4,#0x10] \n"
"loc_FF8347BC: \n"
"		BL	sub_FF863968 \n"			//taskcreate_RotaryEncoder
"		BL	sub_FF8941DC \n"
"		BL	sub_FF837060 \n"			//IsFactoryMode
"		CMP	R0, #0 \n"
"		LDREQ	R1, =0x34414 \n"
"		LDMEQFD	SP!, {R3-R5,LR} \n"
"		BEQ	sub_FF894164 \n"				// eventproc_export_OpLog.Start
"		LDMFD	SP!, {R3-R5,PC} \n"
	);
}

*/

/*----------------------------------------------------------------------
	JogDial_task_my()

	Patched jog dial task  at FF86363C
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) JogDial_task_my() {
	asm volatile (
"		STMFD	SP!, {R4-R11,LR} \n"
"		SUB	SP, SP,	#0x1C \n"
"		BL	sub_FF863A68 \n"
"		LDR	R1, =0x2560 \n"
"		LDR	R6, =0xFFB8D5F4 \n"  //100D --- FFB8D5F0
"		MOV	R0, #0 \n"
"		ADD	R3, SP,	#0x10 \n"
"		ADD	R12, SP, #0x14 \n"
"		ADD	R10, SP, #0x08 \n"
"		MOV	R2, #0 \n"
"		ADD	R9, SP,	#0xC \n"

"loc_FF863668: \n"
"		ADD	R12, SP, #0x14 \n"
"		ADD	LR, R12, R0,LSL#1 \n"
"		MOV	R2, #0 \n"
"		ADD	R3, SP,	#0x10 \n"
"		STRH	R2, [LR] \n"
"		ADD	LR, R3,	R0,LSL#1 \n"
"		STRH	R2, [LR] \n"
"		STR	R2, [R9,R0,LSL#2] \n"
"		STR	R2, [R10,R0,LSL#2] \n"
"		ADD	R0, R0,	#1 \n"
"		CMP	R0, #2 \n"
"		BLT	loc_FF863668 \n"

"loc_FF863698: \n"
"		LDR	R0, =0x2560 \n"
"		MOV	R2, #0 \n"
"		LDR	R0, [R0,#0xC] \n"
"		MOV	R1, SP \n"
"		BL	sub_FF83AE20 \n"
"		CMP	R0, #0 \n"
"		LDRNE	R1, =0x262 \n"

//"		ADRNE	R0, 0xFF8638F8 \n"			// "RotaryEncoder.c"
"		LDRNE	R0, =0xFF8638F8 \n"			// "RotaryEncoder.c"

"		BLNE	sub_FF81EB78 \n"			// DebugAssert

//------------------  begin added code ---------------
"labelA:\n"
		"LDR     R0, =jogdial_stopped\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #1\n"
		"BNE     labelB\n"					// continue on if jogdial_stopped = 0
		"MOV     R0, #40\n"
		"BL      _SleepTask\n"				// jogdial_stopped=1 -- give time back to OS and suspend jogdial task
		"B       labelA\n"
"labelB:\n"
//------------------  end added code -----------------

"		LDR	R0, [SP] \n"
"		AND	R4, R0,	#0xFF \n"
"		AND	R0, R0,	#0xFF00 \n"
"		CMP	R0, #0x100 \n"
"		BEQ	loc_FF863708 \n"
"		CMP	R0, #0x200 \n"
"		BEQ	loc_FF863740 \n"
"		CMP	R0, #0x300 \n"
"		BEQ	loc_FF863938 \n"
"		CMP	R0, #0x400 \n"
"		BNE	loc_FF863698 \n"
"		CMP	R4, #0 \n"
"		LDRNE	R1, =0x2ED \n"

//"		ADRNE	R0, 0xFF8638F8 \n"			// "RotaryEncoder.c"
"		LDRNE	R0, =0xFF8638F8 \n"			// "RotaryEncoder.c"

"		BLNE	sub_FF81EB78 \n"			// DebugAssert
"		RSB	R0, R4,	R4,LSL#3 \n"
"		LDR	R0, [R6,R0,LSL#2] \n"

"loc_FF863700: \n"
"		BL	sub_FF863A40 \n"
"		B	loc_FF863698 \n"

"loc_FF863708: \n"
"		LDR	R7, =0x2570 \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83BDB8 \n"

//"		ADR	R2, 0xFF863588 \n"
"		LDR	R2, =0xFF863588 \n"

"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x200 \n"
"		MOV	R0, #0x28 \n"
"		BL	sub_FF83BCD4 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R10,R4,LSL#2] \n"
"		BEQ	loc_FF863698 \n"
"		MOV	R1, #0x274 \n"
"		B	loc_FF8638E4 \n"

"loc_FF863740: \n"
"		RSB	R5, R4,	R4,LSL#3 \n"
"		LDR	R0, [R6,R5,LSL#2] \n"
"		LDR	R1, =0xC0240104 \n"
"		LDR	R0, [R1,R0,LSL#8] \n"
"		MOV	R2, R0,ASR#16 \n"
"		ADD	R0, SP,	#0x14 \n"
"		ADD	R0, R0,	R4,LSL#1 \n"
"		STR	R0, [SP,#0x18] \n"
"		STRH	R2, [R0] \n"
"		ADD	R0, SP,	#0x10 \n"
"		ADD	R11, R0, R4,LSL#1 \n"
"		LDRSH	R3, [R11] \n"
"		SUB	R0, R2,	R3 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF8637C0 \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF8638A0 \n"
"		LDR	R7, =0x2570 \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83BDB8 \n"

//"		ADR	R2, 0xFF863594 \n"
"		LDR	R2, =0xFF863594 \n"

"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x300 \n"
"		MOV	R0, #0x1F4 \n"
"		BL	sub_FF83BCD4 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R7,R4,LSL#2] \n"
"		BEQ	loc_FF8638A0 \n"
"		LDR	R1, =0x28D \n"
"		B	loc_FF863898 \n"

"loc_FF8637C0: \n"
"		MOV	R1, R0 \n"
"		RSBLT	R0, R0,	#0 \n"
"		MOVLE	R7, #0 \n"
"		MOVGT	R7, #1 \n"
"		CMP	R0, #0xFF \n"
"		BLS	loc_FF863800 \n"
"		CMP	R1, #0 \n"
"		RSBLE	R0, R3,	#0xFF \n"
"		ADDLE	R0, R0,	#0x7F00 \n"
"		ADDLE	R0, R0,	R2 \n"
"		RSBGT	R0, R2,	#0xFF \n"
"		ADDGT	R0, R0,	#0x7F00 \n"
"		ADDGT	R0, R0,	R3 \n"
"		ADD	R0, R0,	#0x8000 \n"
"		ADD	R0, R0,	#1 \n"
"		EOR	R7, R7,	#1 \n"

"loc_FF863800: \n"
"		STR	R0, [SP,#0x04] \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		ADDEQ	R0, R6,	R5,LSL#2 \n"
"		LDREQ	R0, [R0,#8] \n"
"		BEQ	loc_FF863838 \n"
"		ADD	R8, R6,	R5,LSL#2 \n"
"		ADD	R1, R8,	R7,LSL#2 \n"
"		LDR	R1, [R1,#0x10] \n"
"		CMP	R1, R0 \n"
"		BEQ	loc_FF86383C \n"
"		LDR	R0, [R8,#0xC] \n"
"		BL	sub_FF89C2E4 \n"
"		LDR	R0, [R8,#8] \n"

"loc_FF863838: \n"
"		BL	sub_FF89C2E4 \n"

"loc_FF86383C: \n"
"		ADD	R0, R6,	R5,LSL#2 \n"
"		ADD	R7, R0,	R7,LSL#2 \n"
"		LDR	R0, [R7,#0x10] \n"
"		LDR	R1, [SP,#0x04] \n"
"		BL	sub_FF89C20C \n"
"		LDR	R0, [R7,#0x10] \n"
"		LDR	R7, =0x2570 \n"
"		STR	R0, [R9,R4,LSL#2] \n"
"		LDR	R0, [SP,#0x18] \n"
"		LDRH	R0, [R0] \n"
"		STRH	R0, [R11] \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83BDB8 \n"

//"		ADR	R2, 0xFF863594 \n"
"		LDR	R2, =0xFF863594 \n"

"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x300 \n"
"		MOV	R0, #0x1F4 \n"
"		BL	sub_FF83BCD4 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R7,R4,LSL#2] \n"
"		BEQ	loc_FF8638A0 \n"
"		LDR	R1, =0x2CF \n"

"loc_FF863898: \n"
//"		ADR	R0, 0xFF8638F8 \n"			// "RotaryEncoder.c"
"		LDR	R0, =0xFF8638F8 \n"			// "RotaryEncoder.c"

"		BL	sub_FF81EB78 \n"			// DebugAssert

"loc_FF8638A0: \n"
"		ADD	R0, R6,	R5,LSL#2 \n"
"		LDR	R0, [R0,#0x18] \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF863930 \n"
"		LDR	R0, =0x2560 \n"
"		LDR	R0, [R0,#0x14] \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF863930 \n"

//"		ADR	R2, 0xFF863588 \n"
"		LDR	R2, =0xFF863588 \n"

"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x400 \n"
"		BL	sub_FF83BCD4 \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R10,R4,LSL#2] \n"
"		BEQ	loc_FF863698 \n"
"		LDR	R1, =0x2D6 \n"

"loc_FF8638E4: \n"
//"		ADR	R0, 0xFF8638F8 \n"			// "RotaryEncoder.c"
"		LDR	R0, =0xFF8638F8 \n"			// "RotaryEncoder.c"

"		BL	sub_FF81EB78 \n"			// DebugAssert
"		B	loc_FF863698 \n"

		"NOP \n"


"loc_FF863930: \n"
"		LDR	R0, [R6,R5,LSL#2] \n"
"		B	loc_FF863700 \n"

"loc_FF863938: \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		MOVEQ	R1, #0x2E0 \n"

//"		ADREQ	R0, 0xFF8638F8 \n"			// "RotaryEncoder.c"
"		LDREQ	R0, =0xFF8638F8 \n"			// "RotaryEncoder.c"

"		BLEQ	sub_FF81EB78 \n"			// DebugAssert
"		RSB	R0, R4,	R4,LSL#3 \n"
"		ADD	R0, R6,	R0,LSL#2 \n"
"		LDR	R0, [R0,#0xC] \n"
"		BL	sub_FF89C2E4 \n"
"		MOV	R2, #0 \n"
"		STR	R2, [R9,R4,LSL#2] \n"
"		B	loc_FF863698 \n"
 );
};


//FILE INIT STUFF
void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
	 "STMFD   SP!, {R4-R6,LR}\n"
	 "BL      sub_FF896688\n"
	 "LDR     R5, =0x5006\n"
	 "MOVS    R4, R0\n"
	 "MOVNE   R1, #0\n"
	 "MOVNE   R0, R5\n"
	 "BLNE    sub_FF89A464\n"  //PostLogicalEventToUI
//	 "BL      sub_FF8966B4\n"
	 "BL      sub_FF8966B4_my\n"
	 //----------------------->
    "BL      core_spytask_can_start\n" // + safe to start spytask   S95 new stuff to speed up chdk load

	 "CMP     R4, #0\n"
	 "MOVEQ   R0, R5\n"
	 "LDMEQFD SP!, {R4-R6,LR}\n"
	 "MOVEQ   R1, #0\n"
	 "BEQ    sub_FF89A464\n"  //PostLogicalEventToUI
	 "LDMFD   SP!, {R4-R6,PC}\n"
	 );
};

void __attribute__((naked,noinline)) sub_FF8966B4_my() {
 asm volatile(
	 "STMFD   SP!, {R4,LR}\n"
	 "MOV     R0, #3\n"
//	 "BL      sub_FF87538C\n"	  //__Mounter.c__0
	 "BL      sub_FF87538C_my\n"	  //__Mounter.c__0

	 "B       sub_FF8966C0\n" // continue in firmware
	 );
};

void __attribute__((naked,noinline)) sub_FF87538C_my() {
 asm volatile(
	 	 "STMFD   SP!, {R4-R8,LR}\n"
	 	 "MOV     R8, R0\n"
	 	 "BL      sub_FF87530C\n" //__Mounter.c__0
	 	 "LDR     R1, =0x3A068\n"
	 	 "MOV     R6, R0\n"
	 	 "ADD     R4, R1, R0,LSL#7\n"
	 	 "LDR     R0, [R4,#0x6C]\n"
	 	 "CMP     R0, #4\n"
	 	 "LDREQ   R1, =0x83F\n"
	 	 "LDREQ   R0, =0xFF874E4C\n" //aMounter_c
	 	 "BLEQ    sub_FF81EB78\n"  //DebugAssert
	 	 "MOV     R1, R8\n"
	 	 "MOV     R0, R6\n"
	 	 "BL      sub_FF874BC0\n"
	 	 "LDR     R0, [R4,#0x38]\n"
	 	 "BL      sub_FF875A30\n"
	 	 "CMP     R0, #0\n"
	 	 "STREQ   R0, [R4,#0x6C]\n"
	 	 "MOV     R0, R6\n"
	 	 "BL      sub_FF874C50\n"
	 	 "MOV     R0, R6\n"
//	 	 "BL      sub_FF874FB4\n"
	 	 "BL      sub_FF874FB4_my\n"
	 	 //------------------->
	 	 "B       sub_FF8753E4 \n" //continue in firmware
	 	 );

	 };
void __attribute__((naked,noinline)) sub_FF874FB4_my() {
 asm volatile(
	 	 	 "STMFD   SP!, {R4-R6,LR}\n"
	 	 	 "MOV     R5, R0\n"
	 	 	 "LDR     R0, =0x3A068\n"
	 	 	 "ADD     R4, R0, R5,LSL#7\n"
	 	 	 "LDR     R0, [R4,#0x6C]\n"
	 	 	 "TST     R0, #2\n"
	 	 	 "MOVNE   R0, #1\n"
	 	 	 "LDMNEFD SP!, {R4-R6,PC}\n"
	 	 	 "LDR     R0, [R4,#0x38]\n"
	 	 	 "MOV     R1, R5\n"
//	 	 	 "BL      sub_FF874CD4\n"
	 	 	 "BL      sub_FF874CD4_my\n"
	 	 	            //------------------->

             "B      sub_FF874FE0\n"  //continue in firmware

	 	 	 );

	 };

void __attribute__((naked,noinline)) sub_FF874CD4_my() {
 asm volatile(
	 "		STMFD	SP!, {R4-R10,LR}\n"
	 "		MOV	R9, R0\n"
	 "		LDR	R0, =0x3A068\n"
	 "		MOV	R8, #0\n"
	 "		ADD	R5, R0,	R1,LSL#7\n"
	 "		LDR	R0, [R5,#0x3C]\n"
	 "		MOV	R7, #0\n"
	 "		CMP	R0, #7\n"
	 "		MOV	R6, #0\n"
	 "		ADDLS	PC, PC,	R0,LSL#2\n"
	 "		B	loc_FF874E2C\n"
	 "loc_FF874D00:\n"
	 "		B	loc_FF874D38\n"
	 "loc_FF874D04:\n"
	 "		B	loc_FF874D20\n"
	 "loc_FF874D08:\n"
	 "		B	loc_FF874D20\n"
	 "loc_FF874D0C:\n"
	 "		B	loc_FF874D20\n"
	 "loc_FF874D10:\n"
	 "		B	loc_FF874D20\n"
	 "loc_FF874D14:\n"
	 "		B	loc_FF874E24\n"
	 "loc_FF874D18:\n"
	 "		B	loc_FF874D20\n"
	 "loc_FF874D1C:\n"
	 "		B	loc_FF874D20\n"
"loc_FF874D20:\n"
	 "		MOV	R2, #0\n"
	 "		MOV	R1, #0x200\n"
	 "		MOV	R0, #2\n"
	 "		BL	sub_FF890738\n"
	 "		MOVS	R4, R0\n"
	 "		BNE	loc_FF874D40\n"
"loc_FF874D38:\n"
	 "		MOV	R0, #0\n"
	 "		LDMFD	SP!, {R4-R10,PC}\n"
"loc_FF874D40:\n"
	 "		LDR	R12, [R5,#0x50]\n"
	 "		MOV	R3, R4\n"
	 "		MOV	R2, #1\n"
	 "		MOV	R1, #0\n"
	 "		MOV	R0, R9\n"
	 "		BLX	R12\n"
	 "		CMP	R0, #1\n"
	 "		BNE	loc_FF874D6C\n"
	 "		MOV	R0, #2\n"
	 "		BL	sub_FF890888\n" //__ExMemMan.c__0 ; LOCATION: ExMemMan.c:0
	 "		B	loc_FF874D38\n"
"loc_FF874D6C:\n"
	 "		LDR	R1, [R5,#0x64]\n"
	 "		MOV	R0, R9\n"
	 "		BLX	R1\n"
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





	 "		LDRB	R1, [R4,#0x1C9]\n"
	 "		LDRB	R3, [R4,#0x1C8]\n"
	 "		LDRB	R12, [R4,#0x1CC]\n"
	 "		MOV	R1, R1,LSL#24\n"
	 "		ORR	R1, R1,	R3,LSL#16\n"
	 "		LDRB	R3, [R4,#0x1C7]\n"
	 "		LDRB	R2, [R4,#0x1BE]\n"
	 //"		LDRB	LR, [R4,#0x1FF]\n"     //remains commented as in sx200
	 "		ORR	R1, R1,	R3,LSL#8\n"
	 "		LDRB	R3, [R4,#0x1C6]\n"
	 "		CMP	R2, #0\n"
	 "		CMPNE	R2, #0x80\n"
	 "		ORR	R1, R1,	R3\n"
	 "		LDRB	R3, [R4,#0x1CD]\n"
	 "		MOV	R3, R3,LSL#24\n"
	 "		ORR	R3, R3,	R12,LSL#16\n"
	 "		LDRB	R12, [R4,#0x1CB]\n"
	 "		ORR	R3, R3,	R12,LSL#8\n"
	 "		LDRB	R12, [R4,#0x1CA]\n"
	 "		ORR	R3, R3,	R12\n"
	 //"		LDRB	R12, [R4,#0x1FE]\n"    //remains commented as in sx200
     // Left as in sx200
             "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
             "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.


	 "		BNE	loc_FF874DF8\n"
	 "		CMP	R0, R1\n"
	 "		BCC	loc_FF874DF8\n"
	 "		ADD	R2, R1,	R3\n"
	 "		CMP	R2, R0\n"
	 "		CMPLS	R12, #0x55\n"
	 "		CMPEQ	LR, #0xAA\n"
	 "		MOVEQ	R7, R1\n"
	 "		MOVEQ	R6, R3\n"
	 "		MOVEQ	R4, #1\n"
	 "		BEQ	loc_FF874DFC\n"
"loc_FF874DF8:\n"
	 "		MOV	R4, R8\n"
"loc_FF874DFC:\n"
	 "		MOV	R0, #2\n"
	 "		BL	sub_FF890888\n" //__ExMemMan.c__0 ; LOCATION: ExMemMan.c:0
	 "		CMP	R4, #0\n"
	 "		BNE	loc_FF874E38\n"
	 "		LDR	R1, [R5,#0x64]\n"
	 "		MOV	R7, #0\n"
	 "		MOV	R0, R9\n"
	 "		BLX	R1\n"
	 "		MOV	R6, R0\n"
	 "		B	loc_FF874E38\n"
"loc_FF874E24:\n"
	 "		MOV	R6, #0x40\n"
	 "		B	loc_FF874E38\n"
"loc_FF874E2C:\n"
	 "		LDR	R1, =0x597\n"
	 "		LDR	R0, =0xFF874E4C\n" //aMounter_c	; Mounter.c
	 "		BL	sub_FF81EB78\n" //DebugAssert

"loc_FF874E38:\n"
	 "		STR	R7, [R5,#0x44]!\n"
	 "		STMIB	R5, {R6,R8}\n"
	 "		MOV	R0, #1\n"
"		LDMFD	SP!, {R4-R10,PC}\n"

	          );

	 	 };
