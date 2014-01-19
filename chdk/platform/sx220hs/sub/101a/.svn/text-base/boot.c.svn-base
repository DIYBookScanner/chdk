#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"
//#include "stdlib.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

const char * const new_sa = &_end;

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


void __attribute__((naked,noinline)) boot() {
    

	asm volatile (
	"loc_FF00000C:\n"		 
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
                 "MOV     R0, #0x35\n"					// SX220 size 128M base 0x00000000 (s90 is 64M)
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000035\n"			// SX220 size 128M base 0x40000000 (s90 is 64M)
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"			// size  4k base 0x80000000
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFF80002F\n"			// SX220 size  8M base 0xff800000
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
                 "LDR     R0, =0xFF4A9BBC\n"    //1.01A
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0x11B20\n"
    "loc_FF00013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF00013C\n"
	             "LDR     R1, =0x186AE4\n"
    			 "MOV     R2, #0\n"
    "loc_FF000154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FF000154\n"
    			 "B       sub_FF000358_my\n"    //patched
                                                 
    );
}


void __attribute__((naked,noinline)) sub_FF000358_my() {

   *(int*)0x1938=(int)taskHook;
   *(int*)0x193C=(int)taskHook; 
   
//Power-on FF00FCC0+FF055B3C
if ((*(int*) 0xC022012C) & 1)						// look at play switch //sx220 12C or D4
		*(int*)(0x25A0) = 0x200000;					// not pressed - start in play mode
	else
		*(int*)(0x25A0) = 0x100000;					// power pressed - start in rec mode

   asm volatile (
"loc_FF000358:\n"
				 "LDR     R0, =0xFF0003D0\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFF000408\n"
"loc_FF000364:\n"						
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF000364\n"
                 "LDR     R0, =0xFF000408\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFF00061C\n"
"loc_FF000380:\n"						
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF000380\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"				//patched
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
"loc_FF0003B4:\n"						
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FF0003B4\n"
                 "BL      sub_FF0011B0_my\n"		// patched
                 							  
"loc_FF0003C4:\n"								
                 "ANDEQ   R0, R0, R4,ASR#13\n"
"loc_FF0003C8:\n"								
                 "ANDEQ   R0, R0, R0,ROR R6\n"
"loc_FF0003CC:\n"								
                 "ANDEQ   R0, R0, R4,ROR R6\n"
"loc_FF8103D0:\n"								
                 "NOP\n"
                 "LDR     PC, =0xFF00061C\n"
     );
}

void __attribute__((naked,noinline)) sub_FF0011B0_my() {
    
	asm volatile (
	
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R1, #0x74\n"
                 "MOV     R0, SP\n"
                 "BL      sub_FF3AB8C0\n"  //1.01A
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
    #if defined(CHDK_NOT_IN_CANON_HEAP)
				 "LDR     R0, =0x186AE4\n"
	#else			 
                 "LDR     R0, =new_sa\n"		// added
				 "LDR	  R0, [R0]\n"			// added
	#endif			 
			     "LDR     R2, =0x371F80\n"
                 "STR     R0, [SP,#8]\n"
                 "SUB     R0, R2, R0\n"
                 "STR     R0, [SP,#0xC]\n"
                 "MOV     R0, #0x22\n"
                 "STR     R0, [SP,#0x18]\n"
                 "MOV     R0, #0x68\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "LDR     R1, =0x379C00\n"
                 "LDR     R0, =0x19B\n"
                 "STR     R1, [SP]\n"
                 "STR     R0, [SP,#0x20]\n"
                 "MOV     R0, #0x96\n"
                 "STR     R2, [SP,#0x10]\n"
                 "STR     R1, [SP,#0x14]\n"
                 "STR     R0, [SP,#0x24]\n"
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
                 "LDR     R1, =sub_FF005EE0_my\n"       //patched
                 "MOV     R2, #0\n"
                 "MOV     R0, SP\n"
                 "BL      sub_FF0034C4\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"				
 
                
     );
}

void __attribute__((naked,noinline)) sub_FF005EE0_my() {
     
	 asm volatile (
                "STMFD   SP!, {R4,LR}\n"
			    "BL      sub_FF000B28\n"
                "BL      sub_FF00A374\n"
			    "CMP     R0, #0\n"
				"LDRLT   R0, =0xFF005FF4\n"
				"BLLT    sub_FF005FD4\n"
 				"BL      sub_FF005B18\n"
                "CMP     R0, #0\n"
                "LDRLT   R0, =0xFF005FFC\n"
				"BLLT    sub_FF005FD4\n"
                "LDR     R0, =0xFF00600C\n"
                "BL      sub_FF005C00\n"
                "CMP     R0, #0\n"
                "LDRLT   R0, =0xFF006014\n"
				"BLLT    sub_FF005FD4\n"
                "LDR     R0, =0xFF00600C\n"
                "BL      sub_FF003CA8\n"
                "CMP     R0, #0\n"
				"LDRLT   R0, =0xFF006028\n"
				"BLLT    sub_FF005FD4\n"
                "BL      sub_FF009D00\n"
                "CMP     R0, #0\n"
				"LDRLT   R0, =0xFF006034\n"
                "BLLT    sub_FF005FD4\n"
                "BL      sub_FF001690\n"
                "CMP     R0, #0\n"
				"LDRLT   R0, =0xFF006040\n"
                "BLLT    sub_FF005FD4\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       taskcreate_Startup_my\n" //patched

        );
};


void __attribute__((naked,noinline)) taskcreate_Startup_my() {
//sub_FF00FC78

	asm volatile (
                 "STMFD   SP!, {R3-R9,LR}\n"
                 "MOV     R5, #0\n"
                 "BL      sub_FF024688\n"   //nulsub259
                 "BL      sub_FF02D148\n"
                 "LDR     R7, =0xC0220000\n"
                 "MOVS    R9, R0\n"
                 "MOV     R8, #1\n"
                 "BNE     loc_FF00FCF4\n"
                 "BL      loc_FF025F8C\n"  // SX220 added the entire code at the end because of compiler error. Funnel
				 "CMP     R0, #0\n"
                 "BEQ     loc_FF00FCF4\n"
                 "LDR     R0, [R7,#0xD4]\n"
                 "BICS    R4, R8, R0\n"
                 "BEQ     loc_FF00FCC0\n"
                 "MOV     R0, #0x12C\n"
                 "BL      sub_FF02B4E8\n"
                 "LDR     R0, [R7,#0xD4]\n"
                 "BIC     R4, R8, R0\n"
 "loc_FF00FCC0:\n"   
                 "LDR     R0, [R7,#0x12C]\n"
                 "BIC     R6, R8, R0\n"
                 "BL      sub_FF023888\n"
                 "CMP     R0, #1\n"
                 "MOVEQ   R5, #1\n"
                 "ORR     R0, R6, R4\n"
                 "ORRS    R0, R0, R5\n"
                 "BNE     loc_FF00FD04\n"
                 "BL      sub_FF023CB8\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R7,#0x1C]\n"
                 "BL      sub_FF023EAC\n"
 "loc_FF00FCF0:\n"                            
                 "B       loc_FF00FCF0\n"
 "loc_FF00FCF4:\n"                           
                 "LDR     R0, [R7,#0x12C]\n"
                 "BIC     R6, R8, R0\n"
                 "LDR     R0, [R7,#0xD4]\n"
                 "BIC     R4, R8, R0\n"
 "loc_FF00FD04:\n"
                 "MOV     R3, R5\n"
                 "MOV     R2, R9\n"
                 "MOV     R1, R4\n"
                 "MOV     R0, R6\n"
               //  "BL      sub_FF024690\n"      //we must remove this for power-on mode handling to work
                 "BL      sub_FF02468C\n"     	 //j_nullsub_260
                 "BL      sub_FF02B318\n"
                 "LDR     R1, =0x3CE000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF02B788\n"
                 "BL      sub_FF02B530\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"   //patched
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFF00FD64\n"   		// changed ADR to LDR; "Startup"
                 "BL      sub_FF00E9B0\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R3-R9,PC}\n"
	//added to fix compiler error
	"loc_FF025F8C:\n"
				 "LDR     R0, =0xFFF40100\n"
                 "LDRB    R0, [R0]\n"
                 "CMP     R0, #0\n"
                 "MOVEQ   R0, #1\n"
                 "MOVNE   R0, #0\n"
                 "BX      LR\n"

	
    );
}


// SX220 18.4.2011 - Funnel

void __attribute__((naked,noinline)) task_Startup_my() {

   asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF006588\n"
                 "BL      sub_FF0257FC\n"
                 "BL      sub_FF0238C4\n"
                 "BL      sub_FF02D190\n"       	//j_nullsub_263
                 "BL      sub_FF02D37C\n"
               //  "BL      sub_FF02D224\n"      	//SX220 start diskboot.bin
                 "BL      sub_FF02D528\n"
                 "LDR     R1, =0x30101\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF02A844\n"            //uClkEnabler_Dc
                 "LDR     R1, =0xC0220000\n"
                 "MOV     R0, #8\n"
                 "STR     R0, [R1,#0x9C]\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF02A574\n"
                 "BL      sub_FF022240\n"
                 "BL      sub_FF02D3AC\n"
                 "BL      sub_FF02AABC\n"
                 "BL      sub_FF02D52C\n"
				 "BL      CreateTask_spytask\n"        // added
			//	 "BL      sub_FF024524\n"
				 "BL	  taskcreatePhySw_my\n"        // patched			
                 "BL      sub_FF027F48\n"
                 "BL      sub_FF02D544\n"
                 "BL      sub_FF021638\n"              //nullsub_2
                 "BL      sub_FF0231D0\n"
                 "BL      sub_FF02CF08\n"
                 "BL      sub_FF023814\n"
                 "BL      sub_FF02316C\n"
                 "BL      sub_FF022274\n"
                 "BL      sub_FF02E108\n"
                 "BL      sub_FF023130\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF0066A8\n"
			

     );
}


void __attribute__((naked,noinline)) taskcreatePhySw_my() {
	
	asm volatile (
	
                 "STMFD   SP!, {R3-R5,LR}\n"
                 "LDR     R4, =0x1C40\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     sub_FF024558\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =mykbd_task\n" 	//task_PhySw
                 //"MOV     R2, #0x800\n"
				 "MOV     R2, #0x2000\n"   		//stack size for new task_PhySw so we don't have to do stack switch
				 "B		  sub_FF024548\n"  		//continue in fw
	
				);

				
}

/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


void __attribute__((naked,noinline)) init_file_modules_task() {

 asm volatile(
//FF095240
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF08B180\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FF08F3F4\n"
                 "BL      sub_FF08B1AC\n"
                 "BL      core_spytask_can_start\n"   //added CHDK: Set "it's-safe-to-start"-Flag for spytask

				 "B		  sub_FF095260\n"				 //continue in firmware
 );
}

// copied like in g12 and sx30, thx to philmoz
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
short *jog_position;

// In SX220 called RotaryEncoder FF05671C
void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R11,LR}\n"
                 "SUB     SP, SP, #0x1C\n"
                 "BL      sub_FF056ABC\n"
                 "LDR     R12, =0x25BC\n"
                 "LDR     R6, =0xFF3B19D4\n"  //1.01A
                 "MOV     R0, #0\n"
                 "ADD     R10, SP, #8\n"
                 "ADD     R9, SP, #0xC\n"
				 
				 // Save pointer for kbd.c routine
				 "LDR R2, =jog_position \n"
				 "STR R9, [R2] \n"            
				 
 "loc_FF05673C:\n"
                 "ADD     R2, SP, #0x14\n"
                 "MOV     R1, #0\n"
                 "ADD     R4, R2, R0,LSL#1\n"
                 "ADD     R3, SP, #0x10\n"
                 "STRH    R1, [R4]\n"
                 "ADD     R4, R3, R0,LSL#1\n"
                 "STRH    R1, [R4]\n"
                 "STR     R1, [R9,R0,LSL#2]\n"
                 "STR     R1, [R10,R0,LSL#2]\n"
                 "ADD     R0, R0, #1\n"
                 "CMP     R0, #1\n"
                 "BLT     loc_FF05673C\n"

 "loc_FF05676C:\n"
                 "LDR     R0, =0x25BC\n"
                 "MOV     R2, #0\n"
                 "LDR     R0, [R0,#8]\n"
                 "MOV     R1, SP\n"
                 "BL      sub_FF02AD50\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R1, =0x236\n"
                 "LDRNE   R0, =0xFF0569D4\n"
                 "BLNE    sub_FF00EC88\n"
                 "LDR     R0, [SP]\n"
                 "AND     R4, R0, #0xFF\n"
                 "AND     R0, R0, #0xFF00\n"
                 "CMP     R0, #0x100\n"
                 "BEQ     loc_FF0567DC\n"
                 "CMP     R0, #0x200\n"
                 "BEQ     loc_FF056814\n"
                 "CMP     R0, #0x300\n"
                 "BEQ     loc_FF056A1C\n"
                 "CMP     R0, #0x400\n"
                 "BNE     loc_FF05676C\n"
                 "CMP     R4, #0\n"
                 "LDRNE   R1, =0x2C1\n"
                 "LDRNE   R0, =0xFF0569D4\n"  //
                 "BLNE    sub_FF00EC88\n"
                 "RSB     R0, R4, R4,LSL#3\n"
                 "LDR     R0, [R6,R0,LSL#2]\n"

 "loc_FF0567D4:\n"
                 "BL      sub_FF056AA0\n"
                 "B       loc_FF05676C\n"
 "loc_FF0567DC:\n"
 
 //------------------  added code ---------------------
 "labelA:\n"
                 "LDR     R0, =jogdial_stopped\n"
                 "LDR     R0, [R0]\n"
                 "CMP     R0, #1\n"
                 "BNE     labelB\n"
                 "MOV     R0, #40\n"
                 "BL      sub_FF02B4E8\n"   //SX220 sleeptask
                 "B       labelA\n"
 "labelB:\n"
 //------------------  original code ------------------
    			 "LDR     R0, =0x25C8\n"		//=0xFF0569E4, changing all asc_... fixed the crash when rotating the wheel
                 "LDR     R0, [R0,R4,LSL#2]\n"
                 "BL      sub_FF02BCFC\n"
                 "LDR     R2, =0xFF056668\n"
                 "ORR     R3, R4, #0x200\n"
                 "ADD     R1, R2, #0\n"
                 "MOV     R0, #0x28\n"
                 "BL      sub_FF02BC18\n"
                 "TST     R0, #1\n"
                 "CMPNE   R0, #0x15\n"
                 "STR     R0, [R10,R4,LSL#2]\n"
                 "BEQ     loc_FF05676C\n"
                 "MOV     R1, #0x248\n"
                 "B       loc_FF0569C0\n"
 "loc_FF056814:\n"
                 "RSB     R5, R4, R4,LSL#3\n"
                 "LDR     R0, [R6,R5,LSL#2]\n"
                 "LDR     R1, =0xC0240000\n"
                 "ADD     R0, R1, R0,LSL#8\n"
                 "LDR     R0, [R0,#0x104]\n"
                 "MOV     R1, R0,ASR#16\n"
                 "ADD     R0, SP, #0x14\n"
                 "ADD     R11, R0, R4,LSL#1\n"
                 "ADD     R0, SP, #0x10\n"
                 "ADD     R0, R0, R4,LSL#1\n"
                 "STRH    R1, [R11]\n"
                 "STR     R0, [SP,#0x18]\n"
                 "LDRSH   R3, [R0]\n"
                 "SUB     R2, R1, R3\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF056898\n"
                 "LDR     R0, [R9,R4,LSL#2]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF05697C\n"
                 "LDR     R7, =0x25C8\n"			//=0xFF0569E4
                 "LDR     R0, [R7,R4,LSL#2]\n"
                 "BL      sub_FF02BCFC\n"
                 "LDR     R2, =0xFF056674\n"
                 "ORR     R3, R4, #0x300\n"
                 "ADD     R1, R2, #0\n"
                 "MOV     R0, #0x1F4\n"
                 "BL      sub_FF02BC18\n"
                 "TST     R0, #1\n"
                 "CMPNE   R0, #0x15\n"
                 "STR     R0, [R7,R4,LSL#2]\n"
                 "BEQ     loc_FF05697C\n"
                 "LDR     R1, =0x261\n"
                 "B       loc_FF056974\n"
 "loc_FF056898:\n"
                 "MOV     R0, R2\n"
                 "RSBLT   R0, R0, #0\n"
                 "MOVLE   R7, #0\n"
                 "MOVGT   R7, #1\n"
                 "CMP     R0, #0xFF\n"
                 "BLS     loc_FF0568D4\n"
                 "LDR     R0, =0x7FFF\n"
                 "CMP     R2, #0\n"
                 "SUBLE   R0, R0, R3\n"
                 "ADDLE   R0, R0, R1\n"
                 "SUBGT   R0, R0, R1\n"
                 "ADDGT   R0, R0, R3\n"
                 "MVN     R1, #0x8000\n"  //changed MOVL to MVN
				 "SUB     R0, R0, R1\n"
                 "EOR     R7, R7, #1\n"

 "loc_FF0568D4:\n"
                 "STR     R0, [SP,#4]\n"
                 "LDR     R0, [R9,R4,LSL#2]\n"
                 "CMP     R0, #0\n"
                 "ADDEQ   R0, R6, R5,LSL#2\n"
                 "LDREQ   R0, [R0,#8]\n"
                 "BEQ     loc_FF056910\n"
                 "ADD     R8, R6, R5,LSL#2\n"
                 "ADD     R1, R8, R7,LSL#2\n"
                 "LDR     R1, [R1,#0x10]\n"
                 "CMP     R1, R0\n"
                 "BEQ     loc_FF056918\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF0240E0\n"
                 "LDR     R0, [R8,#8]\n"

 "loc_FF056910:\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF0240E0\n"

 "loc_FF056918:\n"
                 "ADD     R0, R6, R5,LSL#2\n"
                 "ADD     R7, R0, R7,LSL#2\n"
                 "LDR     R0, [R7,#0x10]\n"
                 "LDR     R1, [SP,#4]\n"
                 "BL      sub_FF0240E0\n"
                 "LDR     R0, [R7,#0x10]\n"
                 "LDR     R7, =0x25C8\n"		//=0xFF0569E4
                 "STR     R0, [R9,R4,LSL#2]\n"
                 "LDRH    R1, [R11]\n"
                 "LDR     R0, [SP,#0x18]\n"
                 "STRH    R1, [R0]\n"
                 "LDR     R0, [R7,R4,LSL#2]\n"
                 "BL      sub_FF02BCFC\n"
                 "LDR     R2, =0xFF056674\n"
                 "ORR     R3, R4, #0x300\n"
                 "ADD     R1, R2, #0\n"
                 "MOV     R0, #0x1F4\n"
                 "BL      sub_FF02BC18\n"
                 "TST     R0, #1\n"
                 "CMPNE   R0, #0x15\n"
                 "STR     R0, [R7,R4,LSL#2]\n"
                 "BEQ     loc_FF05697C\n"
                 "LDR     R1, =0x2A3\n"

 "loc_FF056974:\n"
                 "LDR     R0, =0xFF0569D4\n"    //ADR to LDR + =
                 "BL      sub_FF00EC88\n"

 "loc_FF05697C:\n"
                 "ADD     R0, R6, R5,LSL#2\n"
                 "LDR     R0, [R0,#0x18]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF056A14\n"
                 "LDR     R0, =0x25BC\n"
                 "LDR     R0, [R0,#0x10]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF056A14\n"
                 "LDR     R2, =0xFF056668\n"
                 "ORR     R3, R4, #0x400\n"
                 "ADD     R1, R2, #0\n"
                 "BL      sub_FF02BC18\n"
                 "TST     R0, #1\n"
                 "CMPNE   R0, #0x15\n"
                 "STR     R0, [R10,R4,LSL#2]\n"
                 "BEQ     loc_FF05676C\n"
                 "LDR     R1, =0x2AA\n"

 "loc_FF0569C0:\n"
                 "LDR     R0, =0xFF0569D4\n"
                 "BL      sub_FF00EC88\n"
                 "B       loc_FF05676C\n"
 "loc_FF056A14:\n"
                 "LDR     R0, [R6,R5,LSL#2]\n"
                 "B       loc_FF0567D4\n"

 "loc_FF056A1C:\n"
                 "LDR     R0, [R9,R4,LSL#2]\n"
                 "CMP     R0, #0\n"
                 "MOVEQ   R1, #0x2B4\n"
                 "LDREQ   R0, =0xFF0569D4\n"
                 "BLEQ    sub_FF00EC88\n"
                 "RSB     R0, R4, R4,LSL#3\n"
                 "ADD     R0, R6, R0,LSL#2\n"
                 "LDR     R0, [R0,#0xC]\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF0240E0\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R9,R4,LSL#2]\n"
                 "B       loc_FF05676C\n"

 );
}


