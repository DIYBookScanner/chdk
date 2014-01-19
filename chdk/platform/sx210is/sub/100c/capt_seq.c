#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "stdlib.h"

static long *nrflag = (long*)0x75B0;  // -> ASM1989 08.21.2010 found at FF972F10



#include "../../../generic/capt_seq.c"

//ASM1989 Started  :FF87EB90
void __attribute__((naked,noinline)) capt_seq_task() {
 asm volatile (
                 "STMFD   SP!, {R3-R9,LR}\n"



                 "LDR     R6, =0x32B4\n"		// In sx200 was: 0x2B78
                 "LDR     R4, =0x3A5AC\n"		// In sx200 was: 0x15448
                 "MOV     R9, #1\n"
                 "MOV     R7, #0\n"
"loc_FF87EBA4:\n"
                 "LDR     R0, [R6,#4]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, SP\n"
                 "BL      sub_FF839B88\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF87EBD0\n"
                 "LDR     R1, =0x5BE\n"		// In sx200 was:0x588
                 "LDR     R0, =0xFF87E3B8\n"  //aSsshoottask_c
                 "BL      sub_FF81EB14\n"		//DebugAssert
                 "BL      sub_FF81EACC\n"		//eventproc_export_ExitTask
                 "LDMFD   SP!, {R3-R9,PC}\n"

"loc_FF87EBD0:\n"
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x21\n"		// In sx200 was:0x20
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FF87EE9C\n"
"loc_FF87EBE4:\n"
                 "B       loc_FF87EC6C\n"
"loc_FF87EBE8:\n"
                 "B       loc_FF87ECD0\n"
"loc_FF87EBEC:\n"
                 "B       loc_FF87ED0C\n"
"loc_FF87EBF0:\n"
                 "B       loc_FF87ED20\n"
"loc_FF87EBF4:\n"
                 "B       loc_FF87ED18\n"
"loc_FF87EBF8:\n"
                 "B       loc_FF87ED28\n"
"loc_FF87EBFC:\n"
                 "B       loc_FF87ED30\n"
"loc_FF87EC00:\n"
                 "B       loc_FF87ED38\n"
"loc_FF87EC04:\n"
                 "B       loc_FF87ED90\n"
"loc_FF87EC08:\n"
                 "B       loc_FF87EDB8\n"
"loc_FF87EC0C:\n"
                 "B       loc_FF87ED9C\n"
"loc_FF87EC10:\n"
                 "B       loc_FF87EDA8\n"
"loc_FF87EC14:\n"
                 "B       loc_FF87EDB0\n"
"loc_FF87EC18:\n"
                 "B       loc_FF87EDC0\n"
"loc_FF87EC1C:\n"
                 "B       loc_FF87EDC8\n"
"loc_FF87EC20:\n"
                 "B       loc_FF87EDD0\n"
"loc_FF87EC24:\n"
                 "B       loc_FF87EDD8\n"
"loc_FF87EC28:\n"
                 "B       loc_FF87EDE0\n"
"loc_FF87EC2C:\n"
                 "B       loc_FF87EDE8\n"
"loc_FF87EC30:\n"
                 "B       loc_FF87EDF0\n"
"loc_FF87EC34:\n"
                 "B       loc_FF87EDF8\n"
"loc_FF87EC38:\n"
                 "B       loc_FF87EE00\n"
"loc_FF87EC3C:\n"
                 "B       loc_FF87EE08\n"
"loc_FF87EC40:\n"
                 "B       loc_FF87EE14\n"
"loc_FF87EC44:\n"
                 "B       loc_FF87EE1C\n"
"loc_FF87EC48:\n"
                 "B       loc_FF87EE28\n"
"loc_FF87EC4C:\n"
                 "B       loc_FF87EE30\n"
"loc_FF87EC50:\n"
                 "B       loc_FF87EE38\n"
"loc_FF87EC54:\n"
                 "B       loc_FF87EE40\n"
"loc_FF87EC58:\n"
                 "B       loc_FF87EE48\n"
"loc_FF87EC5C:\n"
                 "B       loc_FF87EE50\n"
"loc_FF87EC60:\n"
                 "B       loc_FF87EE58\n"
"loc_FF87EC64:\n"
                 "B       loc_FF87EE64\n"
"loc_FF87EC68:\n"							//New in sx210
                 "B       loc_FF87EEA8\n"
"loc_FF87EC6C:\n"
                 "BL      sub_FF87F4C4\n"


               // "B      sub_FF87EC70\n"    DEBUG  TESTING GO BACK TO REAL CODE!!!

// TESTING DOSNT DO BAD NEITHER GOOD  LIKE IN SD1200 but seems to dont work too!!!
/*
"    STMFD   SP!, {R1-R12,LR}\n"
"    BL      captseq_hack_override_active\n" // returns 1 if tv or sv override in effect
"    LDMFD   SP!, {R1-R12,LR}\n"
"    STR     R0,[SP,#-4]!\n" // push return value
"    BL      shooting_expo_param_override\n" // saves all regs

"                BL      sub_FF87C4C0\n"

"    LDR     R0,[SP],#4\n" // pop override hack
"    CMP     R0, #1\n"
"    MOVEQ   R0, #0\n"
"    STREQ   R0, [R4,#0x24]\n"  // fixes overrides behavior at short shutter press
*/




                 "BL      shooting_expo_param_override\n"  // +
                 "BL      sub_FF87C4C0\n"

// copied over from SX10 don't know if we need it yet
 //  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!

                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press




 //  end of my code
                 "LDR     R0, [R4,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF87EEA8\n"
                 "BL      sub_FF87E090\n"
                 "MOV     R5, R0\n"
                 "LDR     R0, [R4,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF87ECB4\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF883D9C\n"
                 "TST     R0, #1\n"
                 "STRNE   R9, [R6,#0x10]\n"
                 "LDRNE   R0, [R5,#8]\n"
                 "ORRNE   R0, R0, #0x40000000\n"
                 "STRNE   R0, [R5,#8]\n"
                 "BNE     loc_FF87EEA8\n"
"loc_FF87ECB4:\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF87E470\n"
                 "MOV     R0, R5\n"


                 "BL      sub_FF972EFC_my\n"      // ASM1989 Done 03.09.10 In sx200 was: sub_FF93D388_my
//                 "BL      sub_FF972EFC\n"       ASM1989 Done 03.09.10 In sx200 was: sub_FF93D388_my
//TESTING OVERRIDES 18.09.10
//In sd1200 its not my ????
//                  "BL      sub_FF972EFC\n"
                 			                 // ------------------>
//in sd1200 its not here
                 "BL      capt_seq_hook_raw_here\n"      // +


                 "TST     R0, #1\n"
                 "STRNE   R9, [R6,#0x10]\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87ECD0:\n"
                 "LDR     R0, [R4,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87ECFC\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF883D9C\n"
                 "TST     R0, #1\n"
                 "LDRNE   R0, [SP]\n"
                 "MOVNE   R1, #1\n"
                 "LDRNE   R2, [R0,#0xC]\n"
                 "MOVNE   R0, #1\n"
                 "BNE     loc_FF87ED88\n"
"loc_FF87ECFC:\n"
                 "LDR     R0, [SP]\n"
                 "BL      sub_FF87E4E8_my\n"       // ASM1989 Done 03.09.10 In sx200 was: sub_FF862C18_my
          //       "BL      sub_FF87E4E8\n"        ASM1989 Done 03.09.10 In sx200 was: sub_FF862C18_my
                                           // ----------------->
"loc_FF87ED04:\n"
                 "STR     R7, [R4,#0x24]\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87ED0C:\n"                // IN sx20 there is another extra bl here
                 "MOV     R0, #1\n"
                 "BL      sub_FF87F768\n"		//LOCATION: SsPrepareSeq.c:0
                 "B       loc_FF87EEA8\n"
"loc_FF87ED18:\n"
                 "BL      sub_FF87F15C\n"
                 "B       loc_FF87ED04\n"
"loc_FF87ED20:\n"
// last call after shot, also called switching from play->shoot
                 "BL      sub_FF87F4A4\n"
                 "B       loc_FF87ED04\n"
"loc_FF87ED28:\n"
                 "BL      sub_FF87F4AC\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87ED30:\n"
                 "BL      sub_FF87F678\n"		//SsPrepareSeq.c__0
                 "B       loc_FF87ED94\n"
"loc_FF87ED38:\n"
                 "LDR     R5, [R0,#0xC]\n"
                 "BL      sub_FF87F4B4\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF971D04\n"
                 "TST     R0, #1\n"
                 "MOV     R8, R0\n"
                 "BNE     loc_FF87ED78\n"
                 "BL      sub_FF891200\n"



                 "STR     R0, [R5,#0x18]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF972E14\n"    // Flash and ISO Seams to crash here??
                 "MOV     R0, R5\n"
                 "BL      sub_FF9731AC\n"
                 "MOV     R8, R0\n"
                 "LDR     R0, [R5,#0x18]\n"
                 "BL      sub_FF891438\n"
"loc_FF87ED78:\n"
                 "BL      sub_FF87F4A4\n"
                 "MOV     R2, R5\n"
                 "MOV     R1, #9\n"
                 "MOV     R0, R8\n"
"loc_FF87ED88:\n"
                 "BL      sub_FF87CB20\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87ED90:\n"
// movie mode half press ?
                 "BL      sub_FF87F6E0\n"
"loc_FF87ED94:\n"
                 "BL      sub_FF87C4C0\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87ED9C:\n"
                 "LDR     R0, [R4,#0x54]\n"
                 "BL      sub_FF87FD30\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDA8:\n"
                 "BL      sub_FF87FFE8\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDB0:\n"
                 "BL      sub_FF880080\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDB8:\n"
                 "BL      sub_FF87F4A4\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDC0:\n"
                 "BL      sub_FF971F20\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDC8:\n"
                 "BL      sub_FF972134\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDD0:\n"
                 "BL      sub_FF9721BC\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDD8:\n"
                 "BL      sub_FF9722AC\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDE0:\n"							//new sx210
                 "BL      sub_FF97237C\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDE8:\n"
                 "MOV     R0, #0\n"
                 "B       loc_FF87EE0C\n"
"loc_FF87EDF0:\n"
                 "BL      sub_FF9727E8\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EDF8:\n"
                 "BL      sub_FF972884\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE00:\n"
                 "BL      sub_FF972964\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE08:\n"
                 "MOV     R0, #1\n"
"loc_FF87EE0C:\n"
                 "BL      sub_FF972698\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE14:\n"
                 "BL      sub_FF87F920\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE1C:\n"
                 "BL      sub_FF87F9C8\n"
                 "BL      sub_FF87EFD4\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE28:\n"
                 "BL      sub_FF9724F8\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE30:\n"
                 "BL      sub_FF9725C8\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE38:\n"
                 "BL      sub_FF87E348\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE40:\n"
                 "BL      sub_FF837804\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE48:\n"
                 "BL      sub_FF882220\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE50:\n"
                 "BL      sub_FF8822A8\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE58:\n"
// iso change
                 "BL      sub_FF882304\n"
                 "BL      sub_FF8822C4\n"
                 "B       loc_FF87EEA8\n"
"loc_FF87EE64:\n"							//diferent than sx200 & sx20
                 "MOV     R0, #1\n"
                 "BL      sub_FF973B6C\n"
                 "MOV     R0, #1\n"
                 "BL      sub_FF973CA0\n"
                 "LDRH    R0, [R4,#0x9C]\n"
                 "CMP     R0, #4\n"
                 "LDRNEH  R0, [R4]\n"
                 "SUBNE   R12, R0, #0x8200\n"
                 "SUBNES  R12, R12, #0x2A\n"
                 "BNE     loc_FF87EEA8\n"
                 "BL      sub_FF8822A8\n"
                 "BL      sub_FF882820\n"  //Error in function order call
                 "BL      sub_FF882728\n"
                 "B       loc_FF87EEA8\n"

"loc_FF87EE9C:\n"
                 "LDR     R1, =0x724\n"			//in sx200 was: 0x6C9
                 "LDR     R0, =0xFF87E3B8\n"		//aSsshoottask_c ; "SsShootTask.c"
                 "BL      sub_FF81EB14\n"		//DebugAssert
"loc_FF87EEA8:\n"
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0,#4]\n"
                 "LDR     R0, [R6]\n"
                 "BL      sub_FF888E00\n"
                 "LDR     R5, [SP]\n"
                 "LDR     R0, [R5,#8]\n"
                 "CMP     R0, #0\n"
                 "LDREQ   R1, =0x132\n"		// in sx200: 0x12B
                 "LDREQ   R0, =0xFF87E3B8\n"		//aSsshoottask_c ; "SsShootTask.c"
                 "BLEQ    sub_FF81EB14\n"		//DebugAssert
                 "STR     R7, [R5,#8]\n"
                 "B       loc_FF87EBA4\n"
	);
}		// ASM 1989  Done 03.09.10



//"BL      sub_FF87E4E8_my\n"        ASM1989 Done 03.09.10 In sx200 was: sub_FF862C18_my
void __attribute__((naked,noinline)) sub_FF87E4E8_my(){
 asm volatile(
                 "STMFD   SP!, {R3-R9,LR}\n"
                 "LDR     R4, [R0,#0xC]\n"
                 "LDR     R5, =0x3A5AC\n"		//Sx200:0x15448
                 "LDR     R0, [R4,#8]\n"
                 "LDR     R6, =0x420C\n"		//Sx200:0x420A
                 "ORR     R0, R0, #1\n"
                 "STR     R0, [R4,#8]\n"
                 "LDRH    R0, [R5]\n"
                 "LDR     R8, =0x32B4\n"		//Sx200:0x2B78
                 "MOV     R7, #0\n"
                 "CMP     R0, R6\n"
                 "BEQ     loc_FF87E58C\n"
                 "LDRH    R0, [R5,#0x9A]\n"		//Sx200:0x96
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF87E5EC\n"
                 "LDR     R0, [R4,#0xC]\n"
                 "CMP     R0, #1\n"
                 "BLS     loc_FF87E598\n"
                 "LDRH    R0, [R5,#0x98]\n"	//Sx200:0x94
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87E5EC\n"
                 "LDRH    R0, [R5,#0x94]\n"	//Sx200:0x90
                 "CMP     R0, #2\n"
                 "BNE     loc_FF87E5A4\n"
                 "BL      sub_FF87FA78\n"
                 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "BEQ     loc_FF87E58C\n"
                 "LDRH    R0, [R5,#0x9A]\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF87E5EC\n"
                 "LDR     R0, [R4,#0xC]\n"
                 "CMP     R0, #1\n"
                 "BLS     loc_FF87E598\n"
                 "LDRH    R0, [R5,#0x98]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87E5EC\n"
                 "LDRH    R0, [R5,#0x94]\n"
                 "CMP     R0, #2\n"
                 "BEQ     loc_FF87E5D0\n"
                 "B       loc_FF87E5A4\n"
"loc_FF87E58C:\n"
                 "LDRH    R0, [R5,#0x9A]\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF87E5EC\n"
"loc_FF87E598:\n"
                 "LDRH    R0, [R5,#0x98]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87E5EC\n"
"loc_FF87E5A4:\n"
                 "LDRH    R0, [R5,#0x94]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF87E5EC\n"
                 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "LDRNE   R0, [R4,#0xC]\n"
                 "CMPNE   R0, #1\n"
                 "BLS     loc_FF87E5EC\n"
                 "LDR     R0, [R4,#0x10]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF87E5EC\n"
"loc_FF87E5D0:\n"
                 "LDR     R3, =0x277\n"			//SX200 :0x262
                 "LDR     R2, =0xEA60\n"	//SX200 :0xEA60
                 "STR     R3, [SP]\n"
                 "LDR     R0, [R8]\n"
                 "LDR     R3, =0xFF87E3B8\n"		//aSsshoottask_c ; "SsShootTask.c"
                 "MOV     R1, #0x40000000\n"
                 "BL      sub_FF884110\n"
"loc_FF87E5EC:\n"
                 "BL      sub_FF87E348\n"
                 "LDR     R0, [R5,#0x24]\n"
                 "CMP     R0, #0\n"
                 "MOVEQ   R0, #2\n"
                 "BLEQ    sub_FF87AAA8\n"
                 "BL      sub_FF87F4B4\n"
                 "LDR     R0, [R5,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87E69C\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF973B6C\n"
                 "MOV     R0, #0\n"			//New sx210
                 "BL      sub_FF973CA0\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF87F8A8\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF971900\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF87E664\n"
                 "BL      sub_FF973BAC\n"
                 "BL      sub_FF973CE4\n"		//New sx210
                 "BL      sub_FF973D34\n"		//New sx210
                 "MOV     R0, R4\n"
                 "BL      sub_FF971A2C\n"		//LOCATION: SsPrePreSeq.c:0
                 "TST     R0, #1\n"
                 "MOVNE   R2, R4\n"
                 "LDMNEFD SP!, {R3-R9,LR}\n"
                 "MOVNE   R1, #1\n"
                 "BNE     sub_FF87CB20\n"       //LOCATION: SsPrePreSeq.c:0
                 "B       loc_FF87E678\n"
"loc_FF87E664:\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF9719A4\n"
                 "BL      sub_FF973BAC\n"
                 "BL      sub_FF973CE4\n"	//New sx210
                 "BL      sub_FF973D34\n"	//New sx210

"loc_FF87E678:\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF87E470\n"
                 "MOV     R0, R4\n"







                 // FLASH AND ISO CRASH HERE !!
                 "BL      sub_FF972E14\n"		//; LOCATION: SsCaptureSeq.c:1
               //  "BL      sub_FF972E14_my\n"		//; LOCATION: SsCaptureSeq.c:1
										//ASM1989 Testing ISO--->

                 //TESTING SOUND!!!
				 //              				"STMFD   SP!, {R3-R9,LR}\n"
				 //				 					"MOV     R0, #1\n"
				 //									 "LDR     R1, =0x400D\n"
				 //				                  "BL      sub_FF885CD0\n"
				 //                "LDMFD   SP!, {R3-R9,PC}\n"
				 ""
//Set Led for ever
				 /*ASM_SAFE(
				 "MOV     R0, #1\n"
				 "MOV     R1, #0\n"
				 "BL      sub_FF860FF8\n"
				 )*/

//BeepDrive for ever
/*
ASM_SAFE(
				 "MOV     R0, #1\n"
				 "MOV     R1, #3\n"
				 "BL      sub_FF96EAD8\n"
					"MOV     R1, #4\n"
				 "BL      sub_FF96EAD8\n"
				 "MOV     R1, #3\n"
				 "BL      sub_FF96EAD8\n"
				 "MOV     R1, #4\n"
				 "BL      sub_FF96EAD8\n"

)*/




                 "BL      sub_FF973948\n"		// LOCATION: SsShootLib.c:4096
                 "MOV     R0, R4\n"
// TL HERE DOSNT CRASH

                 "BL      sub_FF972EFC_my\n"      //ASM1989 03.09.10 old sx200:   sub_FF93D388_my        	SsCaptureSeq.c:1012
                                                  //----------->
//"BL      sub_FF972EFC\n"  // TESTING DONT USE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


                 "MOV     R7, R0\n"    //R5,R0 in sd980 ?
                "BL      capt_seq_hook_raw_here\n"      // +


                 "B       loc_FF87E6A8\n"
"loc_FF87E69C:\n"
                 "LDR     R0, [R8,#0x10]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R7, #0x1D\n"
"loc_FF87E6A8:\n"
                 "BL      sub_FF8822A8\n"
                 "BL      sub_FF8822F0\n"
                 "BL      sub_FF882330\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, R7\n"
                 "BL      sub_FF87CB20\n"			// LOCATION: SsShootCtrl.c:0
                 "BL      sub_FF973160\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "ORRNE   R0, R0, #0x2000\n"
                 "STRNE   R0, [R4,#8]\n"
                 "LDRH    R0, [R5,#0x9A]\n"
                 "CMP     R0, #3\n"
                 "BEQ     locret_FF87E700\n"
                 "LDRH    R0, [R5,#0x98]\n"
                 "CMP     R0, #0\n"
                 "LDREQH  R0, [R5,#0x94]\n"
                 "CMPEQ   R0, #2\n"
                 "MOVEQ   R0, R4\n"
                 "LDMEQFD SP!, {R3-R9,LR}\n"
                 "BEQ     sub_FF87FACC\n"
"locret_FF87E700:\n"
                 "LDMFD   SP!, {R3-R9,PC}\n"
 );
}// Finished 09.03.2010 ASM1989

//sub_FF972EFC_my\n"       In sx200 was: sub_FF93D388_my
//ASM1989 DONE
void __attribute__((naked,noinline)) sub_FF972EFC_my(){
 asm volatile(
                 "STMFD   SP!, {R0-R8,LR}\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FF973E70\n"
                 "LDR	  R1, =0xFFFFFFFF\n"     	//used the sx20 code,  in sx200:"MVN     R1, #0\n"
                 "BL      sub_FF888E34\n"
                 "LDR     R5, =0x75B0\n"				//SX200 : 0x6AD8
                 "LDR     R0, [R5,#0xC]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF972F4C\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF83A3D0\n"
                 "STR     R0, [R5,#0xC]\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =0xFF972A5C\n"
                 "LDR     R0, =0xFF973138\n"        //"ShutterSoundTask"
                 "MOV     R2, #0x400\n"
                 "MOV     R1, #0x17\n"
                 "BL      sub_FF83A39C\n"			//KernelCreateTask
"loc_FF972F4C:\n"
                 "MOV     R2, #4\n"
                 "ADD     R1, SP, #8\n"
                 "MOV     R0, #0x8A\n"
                 "BL      sub_FF891070\n"			//PT_GetPropertyCaseString
                 "TST     R0, #1\n"
                 //DEBUGIN 09.09.10 Detected some registry diferences, what do they do??
                 "MOVNE   R1, #0x3F4\n"				//SX200:0x3AE
                 "LDRNE   R0, =0xFF972CF4\n"		//aSscaptureseq_c ; "SsCaptureSeq.c"
                 "BLNE    sub_FF81EB14\n"			//DebugAssert
                 "LDR     R6, =0x3A678\n"			//SX200:0x1550C
                 "LDR     R7, =0x3A5AC\n"			//SX200:0x15448
                 "LDR     R3, [R6]\n"  //missing
                 "LDRSH   R2, [R6,#0xC]\n"			//New sx210
                 "LDRSH   R1, [R6,#0xE]\n"
                 "LDR     R0, [R7,#0x90]\n"		//SX200:0x8C
                 "BL      sub_FF93938C\n"
                 "BL      sub_FF866E94\n"		//LOCATION: Thermometer.c:0
                 "LDR     R3, =0x75B8\n"		//SX200:0x6AE0
                 "STRH    R0, [R4,#0xA4]\n"		//SX200:0x9C
                 "SUB     R2, R3, #4\n"
                 "STRD    R2, [SP]\n"
                 "MOV     R1, R0\n"
                 "LDRH    R0, [R7,#0x5C]\n"
                 "LDRSH   R2, [R6,#0xC]\n"
                 //END DEBUGIN 09.09.10 Detected some registry diferences
                 "SUB     R3, R3, #8\n"
                 "BL      sub_FF975A14\n"
//TESTing enable latter!
//                 "BL      wait_until_remote_button_is_released\n"
                 "BL      capt_seq_hook_set_nr\n"                     // +
                 "B       sub_FF972FB0\n"                             // continue function in firmware



                 //Testing New order, but no change, maybe that why overrides dont work??
/*                 "LDR     R0, [R4,#0x1C]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R0, #1\n"
                 "STRNE   R0, [R5]\n"
                 "LDR     R0, [R5]\n"
                 "MOV     R1, R0,LSL#16\n"
                 "LDRH    R0, [R7,#0x5C]\n"
                 "MOV     R1, R1,LSR#16\n"
                 "BL      sub_FF975B70\n"
                 "BL      wait_until_remote_button_is_released\n"
                 "BL      capt_seq_hook_set_nr\n"                     // +
                 "B       sub_FF972FD4\n"                             // continue function in firmware
*/

/*
                 "BL      wait_until_remote_button_is_released\n"
                 "BL      capt_seq_hook_set_nr\n"                     // +
                 "B       sub_FF972FB0\n"                             // continue function in firmware
                 */

 );
} // Finished 09.03.2010 ASM1989



// copied from FF8C475C     in sx200 was:FF8A2214
/*
***********************************************************
*/

void __attribute__((naked,noinline)) exp_drv_task(){
 asm volatile(
                "STMFD   SP!, {R4-R8,LR}\n"
                "SUB     SP, SP, #0x20\n"
                "LDR     R8, =0xBB8\n"
                "LDR     R7, =0x4B08\n"			//in sx200 was: 0x41F4
                "LDR     R5, =0x43B90\n"		//in sx200 was: 0x1A1B0
                "MOV     R0, #0\n"
                "ADD     R6, SP, #0x10\n"
                "STR     R0, [SP,#0xC]\n"
"loc_FF8C477C:\n"
                "LDR     R0, [R7,#0x20]\n"
                "MOV     R2, #0\n"
                "ADD     R1, SP, #0x1C\n"
                "BL      sub_FF839B88\n"
                "LDR     R0, [SP,#0xC]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FF8C47C8\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #0x14\n"			//in sx200 was:13,14,15,16
                "CMPNE   R0, #0x15\n"
                "CMPNE   R0, #0x16\n"
                "CMPNE   R0, #0x17\n"
                "BEQ     loc_FF8C492C\n"
                "CMP     R0, #0x29\n"			//sx200: 28
                "BEQ     loc_FF8C48B4\n"
                "ADD     R1, SP, #0xC\n"
                "MOV     R0, #0\n"
                "BL      sub_FF8C470C\n"
"loc_FF8C47C8:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R1, [R0]\n"
                "CMP     R1, #0x2F\n"		//sx200: 2D
                "BNE     loc_FF8C47F8\n"
                "LDR     R0, [SP,#0x1C]\n"
                "BL      sub_FF8C5AE0\n"
                "LDR     R0, [R7,#0x1C]\n"
                "MOV     R1, #1\n"
                "BL      sub_FF888E00\n"
                "BL      sub_FF81EACC\n"		// eventproc_export_ExitTask
                "ADD     SP, SP, #0x20\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF8C47F8:\n"
                "CMP     R1, #0x2E\n"		//sx200: 2C
                "BNE     loc_FF8C4814\n"
                "LDR     R2, [R0,#0x8C]!\n"	//sx200: 88
                "LDR     R1, [R0,#4]\n"
                "MOV     R0, R1\n"
                "BLX     R2\n"
                "B       loc_FF8C4D60\n"
"loc_FF8C4814:\n"
                "CMP     R1, #0x27\n"		//sx200: 26
                "BNE     loc_FF8C4864\n"
                "LDR     R0, [R7,#0x1C]\n"
                "MOV     R1, #0x80\n"
                "BL      sub_FF888E34\n"
                "LDR     R0, =0xFF8C0CA0\n"
                "MOV     R1, #0x80\n"
                "BL      sub_FF965340\n"
                "LDR     R0, [R7,#0x1C]\n"
                "MOV     R2, R8\n"
                "MOV     R1, #0x80\n"
                "BL      sub_FF888D40\n"
                "TST     R0, #1\n"
                "LDRNE   R1, =0xEE1\n"		//sx200:DD2
                "BNE     loc_FF8C4920\n"
"loc_FF8C4850:\n"
                "LDR     R1, [SP,#0x1C]\n"
                "LDR     R0, [R1,#0x90]\n"		//sx200: 8C
                "LDR     R1, [R1,#0x8C]\n"		//sx200: 88
                "BLX     R1\n"
                "B       loc_FF8C4D60\n"
"loc_FF8C4864:\n"
                "CMP     R1, #0x28\n"			//Sx200:27
                "BNE     loc_FF8C48AC\n"
                "ADD     R1, SP, #0xC\n"
                "BL      sub_FF8C470C\n"
                "LDR     R0, [R7,#0x1C]\n"
                "MOV     R1, #0x100\n"
                "BL      sub_FF888E34\n"
                "LDR     R0, =0xFF8C0CB0\n"
                "MOV     R1, #0x100\n"
                "BL      sub_FF965FE4\n"
                "LDR     R0, [R7,#0x1C]\n"
                "MOV     R2, R8\n"
                "MOV     R1, #0x100\n"
                "BL      sub_FF888D40\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF8C4850\n"
                "LDR     R1, =0xEEB\n"			//sx200: DDC
                "B       loc_FF8C4920\n"		//new sx210

//Not existing in sx210
/*
"loc_FF8A2360:\n"
                "LDR     R0, =0xFF89F134\n"
                "BL      sub_FF81B284\n"
                "B       loc_FF8A2308\n"*/


"loc_FF8C48AC:\n"
                "CMP     R1, #0x29\n"		//sx200: 28
                "BNE     loc_FF8C48C4\n"
"loc_FF8C48B4:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "ADD     R1, SP, #0xC\n"
                "BL      sub_FF8C470C\n"
                "B       loc_FF8C4850\n"
"loc_FF8C48C4:\n"
                "CMP     R1, #0x2C\n"		//sx200: 2B
                "BNE     loc_FF8C48DC\n"
                "BL      sub_FF8B3D48\n"
                "BL      sub_FF8B4968\n"
                "BL      sub_FF8B44CC\n"
                "B       loc_FF8C4850\n"
//New sx210 code
"loc_FF8C48DC:\n"
				"CMP     R1, #0x2D\n"
				"BNE     loc_FF8C492C\n"
				"LDR     R0, [R7,#0x1C]\n"
				"MOV     R1, #4\n"
				"BL      sub_FF888E34\n"
				"LDR     R1, =0xFF8C0CD0\n"
				"LDR     R0, =0xFFFFF400\n"
				"MOV     R2, #4\n"
				"BL      sub_FF8B37C4\n"
				"BL      sub_FF8B3A4C\n"		//LOCATION: Shutter.c:0
				"LDR     R0, [R7,#0x1C]\n"
				"MOV     R2, R8\n"
				"MOV     R1, #4\n"
				"BL      sub_FF888C5C\n"
				"TST     R0, #1\n"
				"BEQ     loc_FF8C4850\n"
				"LDR     R1, =0xF13\n"
"loc_FF8C4920:\n"
				"LDR     R0, =0xFF8C1310\n"		// aExpdrv_c
				"BL      sub_FF81EB14\n"		//DebugAssert
				"B       loc_FF8C4850\n"
 //end new sx210 code
"loc_FF8C492C:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "MOV     R4, #1\n"
                "LDR     R1, [R0]\n"
                "CMP     R1, #0x12\n"			//sx200: 11
                "CMPNE   R1, #0x13\n"				//sx200: 12
                "BNE     loc_FF8C499C\n"
                "LDR     R1, [R0,#0x7C]\n"
                "ADD     R1, R1, R1,LSL#1\n"
                "ADD     R1, R0, R1,LSL#2\n"
                "SUB     R1, R1, #8\n"
                "LDMIA   R1, {R2-R4}\n"
                "STMIA   R6, {R2-R4}\n"
                "BL      sub_FF8C30F4\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R1, [R0,#0x7C]\n"
                "LDR     R3, [R0,#0x8C]\n"		//88
                "LDR     R2, [R0,#0x90]\n"		//8C
                "ADD     R0, R0, #4\n"
                "BLX     R3\n"
                "LDR     R0, [SP,#0x1C]\n"
                "BL      sub_FF8C5E9C\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R1, [R0,#0x7C]\n"
                "LDR     R3, [R0,#0x94]\n"		//90
                "LDR     R2, [R0,#0x98]\n"		//94
                "ADD     R0, R0, #4\n"
                "BLX     R3\n"
                "B       loc_FF8C4CA0\n"
"loc_FF8C499C:\n"
                "CMP     R1, #0x14\n"		//13,14,15,16
                "CMPNE   R1, #0x15\n"
                "CMPNE   R1, #0x16\n"
                "CMPNE   R1, #0x17\n"
                "BNE     loc_FF8C4A54\n"
                "ADD     R3, SP, #0xC\n"
                "MOV     R2, SP\n"
                "ADD     R1, SP, #0x10\n"
                "BL      sub_FF8C3348\n"
                "CMP     R0, #1\n"
                "MOV     R4, R0\n"
                "CMPNE   R4, #5\n"
                "BNE     loc_FF8C49F0\n"
                "LDR     R0, [SP,#0x1C]\n"
                "MOV     R2, R4\n"
                "LDR     R1, [R0,#0x7C]!\n"
                "LDR     R12, [R0,#0x10]!\n"		//0xC
                "LDR     R3, [R0,#4]\n"
                "MOV     R0, SP\n"
                "BLX     R12\n"
                "B       loc_FF8C4A28\n"
"loc_FF8C49F0:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "CMP     R4, #2\n"
                "LDR     R3, [R0,#0x90]\n"		//8C
                "CMPNE   R4, #6\n"
                "BNE     loc_FF8C4A3C\n"
                "LDR     R12, [R0,#0x8C]\n"		//88
                "MOV     R0, SP\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BLX     R12\n"
                "LDR     R0, [SP,#0x1C]\n"
                "MOV     R2, SP\n"
                "ADD     R1, SP, #0x10\n"
                "BL      sub_FF8C4458\n"
"loc_FF8C4A28:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R2, [SP,#0xC]\n"
                "MOV     R1, R4\n"
                "BL      sub_FF8C46AC\n"
                "B       loc_FF8C4CA0\n"
"loc_FF8C4A3C:\n"
                "LDR     R1, [R0,#0x7C]\n"
                "LDR     R12, [R0,#0x8C]\n"		//88
                "ADD     R0, R0, #4\n"
                "MOV     R2, R4\n"
                "BLX     R12\n"
                "B       loc_FF8C4CA0\n"
"loc_FF8C4A54:\n"
                "CMP     R1, #0x23\n"			//22,23
                "CMPNE   R1, #0x24\n"
                "BNE     loc_FF8C4AA0\n"
                "LDR     R1, [R0,#0x7C]\n"
                "ADD     R1, R1, R1,LSL#1\n"
                "ADD     R1, R0, R1,LSL#2\n"
                "SUB     R1, R1, #8\n"
                "LDMIA   R1, {R2-R4}\n"
                "STMIA   R6, {R2-R4}\n"
                "BL      sub_FF8C23C8\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R1, [R0,#0x7C]\n"
                "LDR     R3, [R0,#0x8C]\n"		//88
                "LDR     R2, [R0,#0x90]\n"		//8C
                "ADD     R0, R0, #4\n"
                "BLX     R3\n"
                "LDR     R0, [SP,#0x1C]\n"
                "BL      sub_FF8C26C8\n"
                "B       loc_FF8C4CA0\n"
"loc_FF8C4AA0:\n"
                "ADD     R1, R0, #4\n"
                "LDMIA   R1, {R2,R3,R12}\n"
                "STMIA   R6, {R2,R3,R12}\n"
                "LDR     R1, [R0]\n"
                "CMP     R1, #0x26\n"		//sx200: 25
                "ADDLS   PC, PC, R1,LSL#2\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4ABC:\n"
                "B       loc_FF8C4B58\n"
"loc_FF8C4AC0:\n"
                "B       loc_FF8C4B58\n"
"loc_FF8C4AC4:\n"
                "B       loc_FF8C4B60\n"
"loc_FF8C4AC8:\n"
                "B       loc_FF8C4B68\n"
"loc_FF8C4ACC:\n"
                "B       loc_FF8C4B68\n"
"loc_FF8C4AD0:\n"
                "B       loc_FF8C4B68\n"
"loc_FF8C4AD4:\n"
                "B       loc_FF8C4B58\n"
"loc_FF8C4AD8:\n"
                "B       loc_FF8C4B60\n"
"loc_FF8C4ADC:\n"
                "B       loc_FF8C4B68\n"
"loc_FF8C4AE0:\n"
                "B       loc_FF8C4B68\n"
"loc_FF8C4AE4:\n"
                "B       loc_FF8C4B80\n"
"loc_FF8C4AE8:\n"
                "B       loc_FF8C4B80\n"
"loc_FF8C4AEC:\n"
                "B       loc_FF8C4C6C\n"
"loc_FF8C4AF0:\n"
                "B       loc_FF8C4C74\n"
"loc_FF8C4AF4:\n"
                "B       loc_FF8C4C74\n"
"loc_FF8C4AF8:\n"
                "B       loc_FF8C4C74\n"
"loc_FF8C4AFC:\n"
                "B       loc_FF8C4C74\n"
"loc_FF8C4B00:\n"
                "B       loc_FF8C4C7C\n"
"loc_FF8C4B04:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B08:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B0C:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B10:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B14:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B18:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B1C:\n"
                "B       loc_FF8C4B70\n"
"loc_FF8C4B20:\n"
                "B       loc_FF8C4B78\n"
"loc_FF8C4B24:\n"
                "B       loc_FF8C4B78\n"
"loc_FF8C4B28:\n"
                "B       loc_FF8C4B8C\n"
"loc_FF8C4B2C:\n"
                "B       loc_FF8C4B8C\n"
"loc_FF8C4B30:\n"
                "B       loc_FF8C4B94\n"
"loc_FF8C4B34:\n"
                "B       loc_FF8C4BC4\n"
"loc_FF8C4B38:\n"
                "B       loc_FF8C4BF4\n"
"loc_FF8C4B3C:\n"
                "B       loc_FF8C4C24\n"
"loc_FF8C4B40:\n"
                "B       loc_FF8C4C54\n"
"loc_FF8C4B44:\n"
                "B       loc_FF8C4C54\n"
"loc_FF8C4B48:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B4C:\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B50:\n"
                "B       loc_FF8C4C5C\n"
//new sx210 vs 200
"loc_FF8C4B54:\n"
                "B       loc_FF8C4C64\n"
//end new sx210

"loc_FF8C4B58:\n"
                "BL      sub_FF8C11B8\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B60:\n"
                "BL      sub_FF8C143C\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B68:\n"
                "BL      sub_FF8C1644\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B70:\n"
                "BL      sub_FF8C18BC\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B78:\n"
                "BL      sub_FF8C1AB4\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B80:\n"


                "BL      sub_FF8C1D70_my\n"     //ASM1989 In sx200 was:sub_FF89FB44_my
               			                //---------------->
//                "BL      sub_FF8C1D70\n"

                "MOV     R4, #0\n"
                "B       loc_FF8C4C80\n"

"loc_FF8C4B8C:\n"
                "BL      sub_FF8C1EB0\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4B94:\n"
                "LDRH    R1, [R0,#4]\n"
                "STRH    R1, [SP,#0x10]\n"
                "LDRH    R1, [R5,#2]\n"
                "STRH    R1, [SP,#0x12]\n"
                "LDRH    R1, [R5,#4]\n"
                "STRH    R1, [SP,#0x14]\n"
                "LDRH    R1, [R5,#6]\n"
                "STRH    R1, [SP,#0x16]\n"
                "LDRH    R1, [R0,#0xC]\n"
                "STRH    R1, [SP,#0x18]\n"
                "BL      sub_FF8C5B54\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4BC4:\n"
                "LDRH    R1, [R0,#4]\n"
                "STRH    R1, [SP,#0x10]\n"
                "LDRH    R1, [R5,#2]\n"
                "STRH    R1, [SP,#0x12]\n"
                "LDRH    R1, [R5,#4]\n"
                "STRH    R1, [SP,#0x14]\n"
                "LDRH    R1, [R5,#6]\n"
                "STRH    R1, [SP,#0x16]\n"
                "LDRH    R1, [R5,#8]\n"
                "STRH    R1, [SP,#0x18]\n"
                "BL      sub_FF8C5CB4\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4BF4:\n"
                "LDRH    R1, [R5]\n"
                "STRH    R1, [SP,#0x10]\n"
                "LDRH    R1, [R0,#6]\n"
                "STRH    R1, [SP,#0x12]\n"
                "LDRH    R1, [R5,#4]\n"
                "STRH    R1, [SP,#0x14]\n"
                "LDRH    R1, [R5,#6]\n"
                "STRH    R1, [SP,#0x16]\n"
                "LDRH    R1, [R5,#8]\n"
                "STRH    R1, [SP,#0x18]\n"
                "BL      sub_FF8C5D60\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4C24:\n"
                "LDRH    R1, [R5]\n"
                "STRH    R1, [SP,#0x10]\n"
                "LDRH    R1, [R5,#2]\n"
                "STRH    R1, [SP,#0x12]\n"
                "LDRH    R1, [R5,#4]\n"
                "STRH    R1, [SP,#0x14]\n"
                "LDRH    R1, [R5,#6]\n"
                "STRH    R1, [SP,#0x16]\n"
                "LDRH    R1, [R0,#0xC]\n"
                "STRH    R1, [SP,#0x18]\n"
                "BL      sub_FF8C5E00\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4C54:\n"
                "BL      sub_FF8C2204\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4C5C:\n"
                "BL      sub_FF8C27CC\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4C64:\n"
                "BL      sub_FF8C2A08\n"
                "B       loc_FF8C4C80\n"
"loc_FF8C4C6C:\n"
                "BL      sub_FF8C2B84\n"
                "B       loc_FF8C4C80\n"

//new in sx210
"loc_FF8C4C74:\n"
                "BL      sub_FF8C2D20\n"
                "B       loc_FF8C4C80\n"
//end new

"loc_FF8C4C7C:\n"
                "BL      sub_FF8C2E84\n"
"loc_FF8C4C80:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R1, [R0,#0x7C]\n"
                "LDR     R3, [R0,#0x8C]\n"
                "LDR     R2, [R0,#0x90]\n"
                "ADD     R0, R0, #4\n"
                "BLX     R3\n"
                "CMP     R4, #1\n"
                "BNE     loc_FF8C4CE8\n"
"loc_FF8C4CA0:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "MOV     R2, #0xC\n"
                "LDR     R1, [R0,#0x7C]\n"
                "ADD     R1, R1, R1,LSL#1\n"
                "ADD     R0, R0, R1,LSL#2\n"
                "SUB     R4, R0, #8\n"
                "LDR     R0, =0x43B90\n"		//sx200: 0x1A1B0
                "ADD     R1, SP, #0x10\n"
                "BL      sub_FFB5F82C\n"
                "LDR     R0, =0x43B9C\n"			//sx200: 0x1A1BC
                "MOV     R2, #0xC\n"
                "ADD     R1, SP, #0x10\n"
                "BL      sub_FFB5F82C\n"
                "LDR     R0, =0x43BA8\n"				//sx200: 0x1A1C8
                "MOV     R2, #0xC\n"
                "MOV     R1, R4\n"
                "BL      sub_FFB5F82C\n"
                "B       loc_FF8C4D60\n"
"loc_FF8C4CE8:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #0xB\n"
                "BNE     loc_FF8C4D30\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                "MOV     R3, #1\n"
                "MOV     R2, #1\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "BL      sub_FF8C0FC0\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                "MOV     R3, #1\n"
                "MOV     R2, #1\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "B       loc_FF8C4D5C\n"
"loc_FF8C4D30:\n"
                "MOV     R3, #1\n"
                "MOV     R2, #1\n"
                "MOV     R1, #1\n"
                "MOV     R0, #1\n"
                "STR     R3, [SP]\n"
                "BL      sub_FF8C0FC0\n"
                "MOV     R3, #1\n"
                "MOV     R2, #1\n"
                "MOV     R1, #1\n"
                "MOV     R0, #1\n"
                "STR     R3, [SP]\n"
"loc_FF8C4D5C:\n"
                "BL      sub_FF8C1100\n"
"loc_FF8C4D60:\n"
                "LDR     R0, [SP,#0x1C]\n"
                "BL      sub_FF8C5AE0\n"
                "B       loc_FF8C477C\n"
 );
} //ASM1989 09.04.10 done


void __attribute__((naked,noinline)) sub_FF8C1D70_my(){ // ASM1989 In sx200 was:sub_FF89FB44_my
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "LDR     R7, =0x4B08\n"			//in sx200 was: 0x41F4
                 "MOV     R4, R0\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R1, #0x3E\n"
                 "BL      sub_FF888E34\n"
                 "LDRSH   R0, [R4,#4]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF8C0D24\n"
                 "MOV     R6, R0\n"
                 "LDRSH   R0, [R4,#6]\n"
                 "BL      sub_FF8C0E34\n"
                 "LDRSH   R0, [R4,#8]\n"
                 "BL      sub_FF8C0E8C\n"
                 "LDRSH   R0, [R4,#0xA]\n"
                 "BL      sub_FF8C0EE4\n"
                 "LDRSH   R0, [R4,#0xC]\n"
                 "MOV     R1, #0\n"				// new in sx210
                 "BL      sub_FF8C0F3C\n"
                 "MOV     R5, R0\n"
                 "LDR     R0, [R4]\n"
                 "LDR     R8, =0x43BA8\n"		//in sx200 was: 0x1A1C8
                 "CMP     R0, #0xB\n"
                 "MOVEQ   R6, #0\n"
                 "MOVEQ   R5, #0\n"
                 "BEQ     loc_FF8C1E04\n"
                 "CMP     R6, #1\n"
                 "BNE     loc_FF8C1E04\n"
                 "LDRSH   R0, [R4,#4]\n"
                 "LDR     R1, =0xFF8C0C90\n"
                 "MOV     R2, #2\n"
                 "BL      sub_FF965618\n"
                 "STRH    R0, [R4,#4]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R7,#0x28]\n"
                 "B       loc_FF8C1E0C\n"
 "loc_FF8C1E04:\n"
                 "LDRH    R0, [R8]\n"
                 "STRH    R0, [R4,#4]\n"
 "loc_FF8C1E0C:\n"
                 "CMP     R5, #1\n"
                 "LDRNEH  R0, [R8,#8]\n"
                 "BNE     loc_FF8C1E28\n"
                 "LDRSH   R0, [R4,#0xC]\n"
                 "LDR     R1, =0xFF8C0D14\n"
                 "MOV     R2, #0x20\n"
                 "BL      sub_FF8C5B10\n"
 "loc_FF8C1E28:\n"
                 "STRH    R0, [R4,#0xC]\n"
                 "LDRSH   R0, [R4,#6]\n"

                 "BL      sub_FF8B3AB8_my\n"  //ASM1989 in sx200 was:sub_FF89141C_my
                                  //------------------>
//                 "BL      sub_FF8B3AB8\n"

                 "LDRSH   R0, [R4,#8]\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF8B4214\n"
                 "MOV     R1, #0\n"
                 "ADD     R0, R4, #8\n"
                 "BL      sub_FF8B429C\n"
                 "LDRSH   R0, [R4,#0xE]\n"
                 "BL      sub_FF8BBF28\n"
                 "LDR     R4, =0xBB8\n"
                 "CMP     R6, #1\n"
                 "BNE     loc_FF8C1E80\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #2\n"
                 "BL      sub_FF888D40\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x5A7\n"				//in sx200: 0x583
                 "LDRNE   R0, =0xFF8C1310\n"		//aExpdrv_c   ; "ExpDrv.c"
                 "BLNE    sub_FF81EB14\n"			//DebugAssert
 "loc_FF8C1E80:\n"
                 "CMP     R5, #1\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #0x20\n"
                 "BL      sub_FF888D40\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x5AC\n"			//in sx200:0x588
                 "LDRNE   R0, =0xFF8C1310\n"		//aExpdrv_c   ; "ExpDrv.c"
                 "LDMNEFD SP!, {R4-R8,LR}\n"
                 "BNE     sub_FF81EB14\n"			//DebugAsser
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}  //Done asm1989 09.04.10


void __attribute__((naked,noinline)) sub_FF8B3AB8_my(){ // ASM1989 in sx200 was:sub_FF89141C_my
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "LDR     R5, =0x47FC\n"			//in sx200:0x3EF0
                 "MOV     R4, R0\n"
                 "LDR     R0, [R5,#4]\n"
                 "CMP     R0, #1\n"
                 "LDRNE   R1, =0x146\n"			//in sx200:140
                 "LDRNE   R0, =0xFF8B38BC\n"	//aShutter_c  ; "Shutter.c"
                 "BLNE    sub_FF81EB14\n"		//DebugAssert
                 "CMN     R4, #0xC00\n"
                 "LDREQSH R4, [R5,#2]\n"
                 "CMN     R4, #0xC00\n"
                 "MOVEQ   R1, #0x14C\n"			//in sx200:146
                 "LDREQ   R0, =0xFF8B38BC\n"	//aShutter_c  ; "Shutter.c"
                 "STRH    R4, [R5,#2]\n"
                 "BLEQ    sub_FF81EB14\n"		//DebugAssert
                 "MOV     R0, R4\n"

//                 "BL      sub_FFA2260C\n"    // in sx200:FF9D8170       9.9.10 REMOVE LATER when apesux is set !!!
                 "BL      apex2us\n"
// +
                "MOV     R4, R0\n"

//                        "BL      sub_FF8F9AF4\n"         //     nullsub_72       REMOVE LATER when apesux is set !!!
            //     "BL      nullsub_72\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF904E1C\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x151\n"			//in sx200:14B
                 "LDMNEFD SP!, {R4-R6,LR}\n"
                 "LDRNE   R0, =0xFF8B38BC\n"	//aShutter_c  ; "Shutter.c"
                 "BNE     sub_FF81EB14\n"		//DebugAssert
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}   //Done asm1989 09.04.10

//Trying to fix the ISO and Flash Crash incomplete fails maybe due to fault code!!
void __attribute__((naked,noinline)) sub_FF972E14_my(){
 asm volatile(
		"STMFD	SP!, {R3-R7,LR}\n"
		"LDR	R4, =0x3A678\n"
		"LDR	R1, [R0,#8]\n"
		"LDR	R2, [R4]\n"
		"LDR	R7, =0x420C\n"
		"LDR	R6, =0x3A5AC\n"
		"LDR	R5, =0x75D4\n"
		"CMP	R2, #0\n"
		"BEQ	loc_FF972E98\n"
		"ORR	R1, R1,	#0x20\n"
		"STR	R1, [R0,#8]\n"
		"LDR	R0, [R0,#0x18]\n"
		"LDR	R1, =0xF973234\n"
		"MOV	R2, #2\n"
		"BL	sub_FF8DC748\n"			//MainFlash.c

"		LDR	R0, [R4,#0x14]\n"
"		CMP	R0, #0\n"
"		BNE	loc_FF972E6C\n"
"		LDRH	R0, [R6]\n"
"		CMP	R0, R7\n"
"		MOVNE	R0, #5\n"
"		STRNE	R0, [R5]\n"
"loc_FF972E6C:\n"
"		BL	sub_FF973E70\n"
"		LDR	R3, =0x3C1\n"
"		LDR	R2, =0x3A98\n"
"		STR	R3, [SP]\n"
"		LDR	R3, =0xFF972CF4\n"  //aSscaptureseq_c
"		MOV	R1, #2\n"
"		BL	sub_FF884110\n"
"		TST	R0, #1\n"
"		BEQ	locret_FF972EF8\n"
"		LDR	R1, =0x3C2\n"
"		B	loc_FF972EF0\n"
"loc_FF972E98:\n"
"		ORR	R1, R1,	#0x10\n"
"		STR	R1, [R0,#8]\n"
"		LDR	R0, =0xFF973234\n"
"		MOV	R1, #1\n"
"		BL	sub_FF847894\n"  //ExpCtrl_FixExposure
"		LDR	R0, [R4,#0x10]\n"
"		CMP	R0, #0\n"
"		BNE	loc_FF972EC8\n"
"		LDRH	R0, [R6]\n"
"		CMP	R0, R7\n"
"		MOVNE	R0, #2\n"
"		STRNE	R0, [R5]\n"
"loc_FF972EC8:\n"
"		BL	sub_FF973E70\n"
"		LDR	R3, =0x3D2\n"
"		LDR	R2, =0xEA60\n"
"		STR	R3, [SP]\n"
"		LDR	R3, =0xFF972CF4\n"   //aSscaptureseq_c
"		MOV	R1, #1\n"
"		BL	sub_FF884110\n"
"		TST	R0, #1\n"
"		BEQ	locret_FF972EF8\n"
"		LDR	R1, =0x3D3\n"
"loc_FF972EF0:\n"
"		LDR	R3, =0xFF972CF4\n" //aSscaptureseq_c
"		BL	sub_FF81EB14\n"  //DebugAssert
"locret_FF972EF8:\n"
"		LDMFD	SP!, {R3-R7,PC}\n"


 );
}   //Done asm1989 09.04.10




//Set Led for ever
				 /*ASM_SAFE(
				 "MOV     R0, #1\n"
				 "MOV     R1, #0\n"
				 "BL      sub_FF860FF8\n"
				 )*/

//BeepDrive for ever
/*
ASM_SAFE(
				 "MOV     R0, #1\n"
				 "MOV     R1, #3\n"
				 "BL      sub_FF96EAD8\n"
					"MOV     R1, #4\n"
				 "BL      sub_FF96EAD8\n"
				 "MOV     R1, #3\n"
				 "BL      sub_FF96EAD8\n"
				 "MOV     R1, #4\n"
				 "BL      sub_FF96EAD8\n"

)*/
