#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

//IXUS 1000 102B
// mwvent82: taken from reference sub 100D and adjusted what needs to be adjusted
//           most location labels are left as 100D with the 'real' 102B locations commented in some cases

static long *nrflag = (long*)0xDDA8;  // -> ASM1989 11.06.2010 found at FFAE3478 in s95:FFAF9528  in sx210: FF972F10

#include "../../../generic/capt_seq.c"

//ASM1989 Started  :FF883630   in sx210: FF87EB90
void __attribute__((naked,noinline)) capt_seq_task() {
// _sub_FF88365C__SsShootTask.c__13 ROM FF88365C 00000274 R . . . . . .
 asm volatile (
                 "STMFD   SP!, {R3-R7,LR}\n"
                 "LDR     R7, =0x3474\n"		// In sx200 was: 0x2B78
                 "LDR     R4, =0x3C5E4\n"		// In sx200 was: 0x15448
                 "MOV     R6, #0\n"
"loc_FF883640:\n" // loc_FF88366C in 102B
                 "LDR     R0, [R7,#4]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, SP\n"
                 "BL      sub_FF83AE20\n" // same as 100D
                 "TST     R0, #1\n"
                 "BEQ     loc_FF88366C\n" // loc_FF883698 in 102B
                 "LDR     R1, =0x43F\n"
                 "LDR     R0, =0xFF8831C8\n"  //aSsshoottask_c // changed from 0xFF88319C in 100D
                 "BL      sub_FF81EB78\n"		//DebugAssert // unchanged from 100D
                 "BL      sub_FF81EB30\n"		//eventproc_export_ExitTask // unchanged from 100D
                 "LDMFD   SP!, {R3-R7,PC}\n"

"loc_FF88366C:\n" // loc_FF883698 in 102B
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x1F\n"
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FF883868\n" // loc_FF883894 in 102B

"loc_FF883680:\n" // loc_FF8836AC 
		"B	loc_FF883700\n" // loc_FF88372C
"loc_FF883684:\n" // loc_FF8836B0
		"B	loc_FF883718\n" // loc_FF883744 
"loc_FF883688:\n" // loc_FF8836B4
		"B	loc_FF883730\n" // loc_FF88375C
"loc_FF88368C:\n" // loc_FF8836B8
		"B	loc_FF883744\n" // loc_FF883770
"loc_FF883690:\n" // loc_FF8836BC
		"B	loc_FF88373C\n" // loc_FF883768
"loc_FF883694:\n" // loc_FF8836C0 
		"B	loc_FF883750\n" // loc_FF88377C
"loc_FF883698:\n" // loc_FF8836C4 
		"B	loc_FF883758\n" // loc_FF883784
"loc_FF88369C:\n" // loc_FF8836C8 
		"B	loc_FF883760\n" // loc_FF88378C
"loc_FF8836A0:\n" // loc_FF8836CC
		"B	loc_FF88376C\n" // loc_FF883798
"loc_FF8836A4:\n" // loc_FF8836D0
		"B	loc_FF883794\n" // loc_FF8837C0
"loc_FF8836A8:\n" // loc_FF8836D4
		"B	loc_FF883778\n" // loc_FF8837A4
"loc_FF8836AC:\n" // loc_FF8836D8
		"B	loc_FF883784\n" // loc_FF8837B0
"loc_FF8836B0:\n" // loc_FF8836DC
		"B	loc_FF88378C\n" // loc_FF8837B8
"loc_FF8836B4:\n" // loc_FF8836E0
		"B	loc_FF88379C\n" // loc_FF8837C8
"loc_FF8836B8:\n" // loc_FF8836E4
		"B	loc_FF8837A4\n" // loc_FF8837D0 
"loc_FF8836BC:\n" // loc_FF8836E8
		"B	loc_FF8837AC\n" // loc_FF8837D8 
"loc_FF8836C0:\n" // loc_FF8836EC 
		"B	loc_FF8837B4\n" // loc_FF8837E0
"loc_FF8836C4:\n" // loc_FF8836F0
		"B	loc_FF8837BC\n" // loc_FF8837E8
"loc_FF8836C8:\n" // loc_FF8836F4
		"B	loc_FF8837C8\n" // loc_FF8837F4
"loc_FF8836CC:\n" // loc_FF8836F8
		"B	loc_FF8837D0\n" // loc_FF8837FC
"loc_FF8836D0:\n" // loc_FF8836FC
		"B	loc_FF8837D8\n" // loc_FF883804
"loc_FF8836D4:\n" // loc_FF883700
		"B	loc_FF8837E0\n" // loc_FF88380C
"loc_FF8836D8:\n" // loc_FF883704
		"B	loc_FF8837E8\n" // loc_FF883814
"loc_FF8836DC:\n" // loc_FF883708
		"B	loc_FF8837F4\n" // loc_FF883820
"loc_FF8836E0:\n" // loc_FF88370C
		"B	loc_FF8837FC\n" // loc_FF883828
"loc_FF8836E4:\n" // loc_FF883710
		"B	loc_FF883804\n" // loc_FF883830
"loc_FF8836E8:\n" // loc_FF883714
		"B	loc_FF88380C\n" // loc_FF883838
"loc_FF8836EC:\n" // loc_FF883718 
		"B	loc_FF883814\n" // loc_FF883840
"loc_FF8836F0:\n" // loc_FF88371C
		"B	loc_FF88381C\n" // loc_FF883848 
"loc_FF8836F4:\n" // loc_FF883720
		"B	loc_FF883824\n" // loc_FF883850
"loc_FF8836F8:\n" // loc_FF883724
		"B	loc_FF883830\n" // loc_FF88385C
"loc_FF8836FC:\n" // loc_FF883728
		"B	loc_FF883874\n" // loc_FF8838A0
"loc_FF883700:\n" // loc_FF88372C
        "BL      shooting_expo_param_override\n"  // +       
        "BL      sub_FF883DB4\n" // changed from FF883D88 in 100D
        "BL      shooting_expo_param_override\n"  // +
        "BL      sub_FF880F50\n" // changed from FF880F24 in 100D

// copied over from SX10 don't know if we need it yet
 //  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!

                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press
 //  end of my code
                 "LDR     R0, [R4,#0x24]\n"
                 "CMP     R0, #0\n"

//TIL HERE ixus1000 then changes a lot !!!

//all this should not be here:

	//"BLNE    sub_FF98ADD4\n"  // This is a potential my sub  like the FF972EFC but starting some line earlier

     "BLNE    sub_FF98ADD4_my\n"  // This is a potential my sub  like the FF972EFC but starting some line earlier // sub_FF883DB4 in 102B
						//---------------->
//     "BL      capt_seq_hook_raw_here\n"      // +

	"B       loc_FF883874\n" // loc_FF8838A0 in 102B
"loc_FF883718:\n" // loc_FF883744 in 102B
	"LDRH    R1, [R4]\n"
	"SUB     R12, R1, #0x8200\n"
	"SUBS    R12, R12, #0x2E\n"
	"LDRNE   R0, [R0,#0xC]\n"
//	"BLNE    sub_FF98AB68\n"
    "BLNE    sub_FF98AB68_my\n"  // 100 D was 68 // _sub_FF98AC1C__SsCaptureSeq.c__195 in 102b
								//---------------->
//     "BL      capt_seq_hook_raw_here\n"      // +


	"B       loc_FF883874\n" // loc_FF8838A0 in 102B
"loc_FF883730:\n"  // loc_FF88375C in 102B
	"MOV     R0, #1\n"
	"BL      sub_FF884070\n" // changed from FF884044 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0 in 102B
"loc_FF88373C:\n" // loc_FF883768
	"BL      sub_FF883A54\n" // changed from FF883A28 in 100D
	"B       loc_FF883748\n" // loc_FF883774 in 102B
"loc_FF883744:\n" // loc_FF883770
	"BL      sub_FF883D94\n" // chnaged from sub_FF883D68 in 100D
"loc_FF883748:\n" // loc_FF883774 in 102B
	"STR     R6, [R4,#0x24]\n"
	"B       loc_FF883874\n" // loc_FF8838A0 in 100D
"loc_FF883750:\n" // loc_FF88377C in 102B
	"BL      sub_FF883D9C\n" // changed from sub_FF883D70 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0 in 102B

"loc_FF883758:\n" // loc_FF883784 in 102B
	"BL      sub_FF883F74\n" // changed from sub_FF883F48 in 100D
	"B       loc_FF883770\n" // loc_FF88379C in 102B
"loc_FF883760:\n" // loc_FF88378C
	"LDR     R0, [R0,#0xC]\n"
	"BL      sub_FF98AEE8\n" // changed from sub_FF98AE34 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF88376C:\n" // loc_FF883798
	"BL      sub_FF883FE0\n" // chnaged from sub_FF883FB4 in 100D
"loc_FF883770:\n" // loc_FF88379C  
	"BL      sub_FF880F50\n" // changed from sub_FF880F24 in 100D 
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883778:\n" // loc_FF8837A4
	"LDR     R0, [R4,#0x54]\n"
	"BL      sub_FF8846DC\n" // changed from sub_FF8846B0 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883784:\n" // loc_FF8837B0
	"BL      sub_FF884A78\n" // changed from sub_FF884A4C in 100D 
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF88378C:\n" // loc_FF8837B8
	"BL      sub_FF884ADC\n" // changed from sub_FF884AB0 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883794:\n" // loc_FF8837C0
	"BL      sub_FF883D94\n" // changed from sub_FF883D68 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF88379C:\n" // loc_FF8837C8
	"BL      sub_FF98A268\n" // changed from sub_FF98A1B4 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837A4:\n" // loc_FF8837D0
	"BL      sub_FF98A474\n" // sub_FF98A3C0 
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837AC:\n" // loc_FF8837D8
	"BL      sub_FF98A518\n" // changed from sub_FF98A464 in 100D 
	"B       loc_FF883874\n"  // loc_FF8838A0
"loc_FF8837B4:\n" // loc_FF8837E0
	"BL      sub_FF98A5E8\n" // changed from sub_FF98A534 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837BC:\n" // loc_FF8837E8
	"MOV     R0, #0\n"
	"BL      sub_FF98A848\n" // changed from sub_FF98A794 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837C8:\n" // loc_FF8837F4
	"BL      sub_FF98A9A4\n" // changed from sub_FF98A8F0 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837D0:\n" // loc_FF8837FC
	"BL      sub_FF98AA48\n" // changed from sub_FF98A994 in 100D
	"B       loc_FF883874\n"  // loc_FF8838A0
"loc_FF8837D8:\n" // loc_FF883804
	"BL      sub_FF98AB28\n" // changed from sub_FF98AA74 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837E0:\n" // loc_FF88380C 
	"BL      sub_FF884258\n" // sub_FF88422C
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837E8:\n" // loc_FF883814 
	"BL      sub_FF884304\n" // sub_FF8842D8
	"BL      sub_FF98BBA8\n" // sub_FF98BAF4
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837F4:\n" // loc_FF883820
	"BL      sub_FF98A6B4\n" // sub_FF98A600
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF8837FC:\n" // loc_FF883828
	"BL      sub_FF98A71C\n" // sub_FF98A668
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883804:\n" // loc_FF883830
	"BL      sub_FF98BC78\n" // sub_FF98BBC4
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF88380C:\n" // loc_FF883838
	"BL      sub_FF838C50\n" // unchanged from 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883814:\n" // loc_FF883840
	"BL      sub_FF886E18\n" // sub_FF886DEC
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF88381C:\n" // loc_FF883848
	"BL      sub_FF886EA0\n" // sub_FF886E74
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883824:\n" // loc_FF883850
	"BL      sub_FF886EFC\n" // sub_FF886ED0
	"BL      sub_FF886EBC\n" // sub_FF886E90
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883830:\n" // loc_FF88385C
	"MOV     R0, #1\n"
	"BL      sub_FF98B6E4\n" // sub_FF98B630
	"MOV     R0, #1\n"
	"BL      sub_FF98B814\n" // sub_FF98B760
	"LDRH    R0, [R4,#0x94]\n"
	"CMP     R0, #4\n"
	"LDRNEH  R0, [R4]\n"
	"SUBNE   R12, R0, #0x8200\n"
	"SUBNES  R12, R12, #0x2A\n"
	"BNE     loc_FF883874\n" // loc_FF8838A0 in 102B
	"BL      sub_FF886EA0\n" // changed from sub_FF886E74 in 100D
	"BL      sub_FF88740C\n" // changed from sub_FF8873E0 in 100D
	"BL      sub_FF88731C\n" // changed from sub_FF8872F0 in 100D
	"B       loc_FF883874\n" // loc_FF8838A0
"loc_FF883868:\n" // loc_FF883894 
	"LDR     R1, =0x591\n"
	"LDR     R0, =0xFF8831C8\n"  //aSsshoottask_c // changed from 0xFF88319C in 100D
	"BL      sub_FF81EB78\n"   //DebugAssert
"loc_FF883874:\n" // loc_FF8838A0
	"LDR     R0, [SP]\n"
	"LDR     R1, [R0,#4]\n"
	"LDR     R0, [R7]\n"
	"BL      sub_FF88DBB8\n" // changed from sub_FF88DB8C in 100D 
	"LDR     R5, [SP]\n"
	"LDR     R0, [R5,#8]\n"
	"CMP     R0, #0\n"
	"LDREQ   R1, =0x115\n"
	"LDREQ   R0, =0xFF8831C8\n"  //aSsshoottask_c "ADREQ   R0, aSsshoottask_c ; "SsShootTask.c // changed from 0xFF88319C in 100D
	"BLEQ    sub_FF81EB78\n"   //DebugAssert
	"STR     R6, [R5,#8]\n"
	"B       loc_FF883640\n" // loc_FF88366C in 102B






// looks like the nr stuff is sub_FFAE3304



	);
}		// ASM 1989  Done 11.11.10

//100F needs check


// For the 1st raw stuff
void __attribute__((naked,noinline)) sub_FF98ADD4_my() {
// sub_FF98AE88 in 102B
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"BL      sub_FF882E98\n" // changed from sub_FF882E6C in 100D
		"MOV     R4, R0\n"
		"LDR     R0, =0x3C5E4\n"
		"LDR     R5, =0x7C94\n"   //F: 0x7C94 // changed from 0x7C8C in 100D
		"LDR     R0, [R0,#0x24]\n"
		"MOV     R6, #1\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF98AE18\n"  //F: 1C // loc_FF98AECC in 102B
		"MOV     R0, #0xC\n"
		"BL      sub_FF888998\n" // changed from sub_FF88896C in 100D
		"TST     R0, #1\n"
		"STRNE   R6, [R5]\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x40000000\n"
		"STRNE   R0, [R4,#8]\n"
		"LDMNEFD SP!, {R4-R6,PC}\n"
"loc_FF98AE18:\n" // loc_FF98AECC in 102B
		"MOV     R0, R4\n"
		"BL      sub_FFAE2DF8\n"  //F: 0C // changed from sub_FFAE2D08 in 100D
		"MOV     R0, R4\n"
		//"BL      sub_FFAE37CC\n"  //F: D0
		"BL      sub_FFAE37CC_my\n" // sub_FFAE38BC in 102B
			//---------------->

//		"BL      capt_seq_hook_raw_here\n"		// added
		"TST     R0, #1\n"
		"TST     R0, #1\n"
		"STRNE   R6, [R5]\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
	);
}

//First BL for the nr stuff
void __attribute__((naked,noinline)) sub_FFAE37CC_my() {
	asm volatile (
		"STMFD   SP!, {R2-R8,LR}\n"
		"MOV     R6, R0\n"
		"BL      sub_FF98B9D8\n"  //f: 28 // 100D : sub_FF98B924
		//"MOVL    R1, 0xFFFFFFFF\n"
		"MVN     R1, #0 \n" // mwvent82: TODO NOT in 102B firware should I remove this?
		"BL      sub_FF88DBEC\n" // 100D: sub_FF88DBC0
		"LDR     R0, =0xFFAE3034\n"  //F: 48 100D: 0xFFAE2F44
		"MOV     R1, R6\n"
		"BL      sub_FF8C25D0\n" // 100D: sub_FF8C25A4
		"MOV     R0, R6\n"
		"BL      sub_FFAE2EFC\n"  //F: 10 // 100D: sub_FFAE2E0C
		"MOV     R0, R6\n"
//		"BL      sub_FFAE3304\n"  //F: 08
		"BL      sub_FFAE3304_my\n" // 102B : sub_FFAE33F4
		"B       sub_FFAE38EC\n"  // continue func in firmware needs to be tested // 100D: sub_FFAE37FC
			);
}


//NR stuff goes here needs to be tested
void __attribute__((naked,noinline)) sub_FFAE3304_my() {
// sub_FFAE33F4 in 102B
	asm volatile (
				"STMFD   SP!, {R0-R8,LR}\n"
				"MOV     R4, R0\n"
				"MOV     R0, #0\n"
				"MOV     R7, #1\n"
				"LDR     R5, =0x3C6B4\n"
				"STR     R7, [SP,#0x8]\n"
				"STR     R0, [SP,#0xC]\n"
				"LDR     R6, =0x3C5E4\n"
				"LDR     R3, [R5]\n"
				"LDRSH   R2, [R5,#0xC]\n"
				"LDRSH   R1, [R5,#0xE]\n"
				"LDR     R0, [R6,#0x88]\n"
				"BL      sub_FF945014\n" // 100D: sub_FF944FC8 
				"BL      sub_FF868328\n" //GetCCDTemperature 100D: sub_FF8682FC
				"LDR     R2, =0xDDA8\n"  //F:  DDB0
				"ADD     R3, SP, #0xC\n"
				"STRH    R0, [R4,#0xAC]\n"
				"STRD    R2, [SP]\n"
				"MOV     R1, R0\n"
				"LDRH    R0, [R6,#0x5C]\n"
				"LDRSH   R2, [R5,#0xC]\n"
				"ADD     R3, SP, #0x8\n"
				"BL      sub_FF98D61C\n"  //NRTable.c  F: 6C 100D: sub_FF98D568
				//TESTing enable latter!
				//                 "BL      wait_until_remote_button_is_released\n"
                 "BL      capt_seq_hook_set_nr\n"
                 "B       sub_FFAE3450\n" // continue function in firmware 100D: sub_FFAE3360
			);
}

// For the 2nd raw stuff
void __attribute__((naked,noinline)) sub_FF98AB68_my() {
// sub_FF98AC1C__SsCaptureSeq.c__195 in 102b
	asm volatile (
			"STMFD   SP!, {R3-R7,LR}\n"
			"LDR     R5, =0x3C5E4\n"
			"MOV     R4, R0\n"
			"LDR     R0, [R5,#0x24]\n"
			"LDR     R6, =0x820C\n"
			"CMP     R0, #0\n"
			"MOV     R7, #0\n"
			"BNE     loc_FF98AC14\n"   //F: 18 102B: loc_FF98ACC8
			"LDR     R0, [R5,#0xB8]\n"
			"CMP     R0, #1\n"
			"BNE     loc_FF98ABF0\n"  //F: F4 102B: loc_FF98ACA4
			"LDRH    R0, [R5]\n"
			"CMP     R0, R6\n"
			"LDRNEH  R0, [R5,#0x92]\n"
			"CMPNE   R0, #3\n"
			"LDRNE   R0, [R4,#0xC]\n"
			"CMPNE   R0, #1\n"
			"BLS     loc_FF98ABC4\n"  //F:C8 102B: loc_FF98AC78
			"BL      sub_FF833020\n" // unchanged from 100D
			"TST     R0, #1\n"
			"BEQ     loc_FF98AC14\n" //F: 18 102B: loc_FF98ACC8
			"BL      sub_FF8889F8\n" // 100D: sub_FF8889CC
			"B       loc_FF98AC00\n" //F: 04 ..... 102B: loc_FF98ACB4
"loc_FF98ABC4:\n" // loc_FF98AC78
			"MOV     R0, #0xC\n"
			"BL      sub_FF888998\n" // 100D: sub_FF88896C
			"TST     R0, #1\n"
			"BEQ     loc_FF98AC14\n" // 102B: loc_FF98ACC8
			"MOV     R2, R4\n"
			"MOV     R1, #1\n"
			"MOV     R0, #1\n"
			"BL      sub_FF881914\n" // 100D: sub_FF8818E8
			"BL      sub_FF98B56C\n" // 100D: sub_FF98B4B8 
			"BL      sub_FF88163C\n" // 100D: sub_FF881610
			"LDMFD   SP!, {R3-R7,PC}\n"
"loc_FF98ABF0:\n" // loc_FF98ACA4 
			"MOV     R0, #0xC\n"
			"BL      sub_FF888998\n" // 100D: sub_FF88896C
			"TST     R0, #1\n"
			"BEQ     loc_FF98AC14\n" // 102B: loc_FF98ACC8
"loc_FF98AC00:\n" // loc_FF98ACB4 
			"MOV     R2, R4\n"
			"MOV     R1, #1\n"
			"MOV     R0, #1\n"
			"BL      sub_FF881914\n" // 100D: sub_FF8818E8
			"LDMFD   SP!, {R3-R7,PC}\n"
"loc_FF98AC14:\n" // 102B: loc_FF98ACC8
			"LDR     R0, [R4,#8]\n"
			"ORR     R0, R0, #1\n"
			"STR     R0, [R4,#8]\n"
			"LDRH    R0, [R5]\n"
			"CMP     R0, R6\n"
			"BEQ     loc_FF98ACA0\n" // 102B: loc_FF98AD54
			"LDRH    R0, [R5,#0x92]\n"
			"CMP     R0, #3\n"
			"BEQ     loc_FF98ACE8\n" // 102B: loc_FF98AD9C
			"LDR     R0, [R4,#0xC]\n"
			"CMP     R0, #1\n"
			"BLS     loc_FF98ACAC\n" // 102B: loc_FF98AD60
			"LDRH    R0, [R5,#0x90]\n"
			"CMP     R0, #0\n"
			"BNE     loc_FF98ACE8\n" // 102B: loc_FF98AD9C
			"LDRH    R0, [R5,#0x8C]\n"
			"CMP     R0, #2\n"
			"BNE     loc_FF98ACB8\n" // 102B: loc_FF98AD6C
			"BL      sub_FF8843C8\n" // 100D: sub_FF88439C
			"LDRH    R0, [R5]\n"
			"CMP     R0, R6\n"
			"BEQ     loc_FF98ACA0\n" // 102B: loc_FF98AD54
			"LDRH    R0, [R5,#0x92]\n"
			"CMP     R0, #3\n"
			"BEQ     loc_FF98ACE8\n" // 102B: loc_FF98AD9C
			"LDR     R0, [R4,#0xC]\n"
			"CMP     R0, #1\n"
			"BLS     loc_FF98ACAC\n" // 102B: loc_FF98AD60
			"LDRH    R0, [R5,#0x90]\n"
			"CMP     R0, #0\n"
			"BNE     loc_FF98ACE8\n" // 102B: loc_FF98AD9C
			"LDRH    R0, [R5,#0x8C]\n"
			"CMP     R0, #2\n"
			"BEQ     loc_FF98ACE4\n" // 102B: loc_FF98AD98
			"B       loc_FF98ACB8\n" // 102B: loc_FF98AD6C
"loc_FF98ACA0:\n" // 102B: loc_FF98AD54
			"LDRH    R0, [R5,#0x92]\n"
			"CMP     R0, #3\n"
			"BEQ     loc_FF98ACE8\n" // loc_FF98AD9C
"loc_FF98ACAC:\n" // loc_FF98AD60
			"LDRH    R0, [R5,#0x90]\n"
			"CMP     R0, #0\n"
			"BNE     loc_FF98ACE8\n" // loc_FF98AD9C
"loc_FF98ACB8:\n" // loc_FF98AD6C
			"LDRH    R0, [R5,#0x8C]\n"
			"CMP     R0, #1\n"
			"BNE     loc_FF98ACE8\n" // loc_FF98AD9C
			"LDRH    R0, [R5]\n"
			"CMP     R0, R6\n"
			"LDRNE   R0, [R4,#0xC]\n"
			"CMPNE   R0, #1\n"
			"BLS     loc_FF98ACE8\n" // loc_FF98AD9C
			"LDR     R0, [R4,#0x10]\n"
			"CMP     R0, #1\n"
			"BNE     loc_FF98ACE8\n" // loc_FF98AD9C
"loc_FF98ACE4:\n" // loc_FF98AD98
			"BL      sub_FF98BCB0\n" // 100D: sub_FF98BBFC 
"loc_FF98ACE8:\n" // loc_FF98AD9C
			"BL      sub_FF98BC78\n" // 100D: sub_FF98BBC4
			"BL      sub_FF883DA4\n" // 100D: sub_FF883D78
			"LDR     R0, [R5,#0x24]\n"
			"CMP     R0, #0\n"
			"BNE     loc_FF98ADB4\n" // 102B: loc_FF98AE68
			"MOV     R0, R4\n"
			"BL      sub_FFAE2E70\n" // 100D: sub_FFAE2D80
			"TST     R0, #1\n"
			"LDMNEFD SP!, {R3-R7,PC}\n"
			"MOV     R0, R4\n"
			"BL      sub_FFAE330C\n" // 100D: sub_FFAE321C
			"BL      sub_FF98B4AC\n" // 100D: sub_FF98B3F8
			"LDR     R0, [R5,#0xB8]\n"
			"CMP     R0, #1\n"
			"BNE     loc_FF98AD40\n" // 102B: loc_FF98ADF4
			"LDRH    R0, [R5]\n"
			"CMP     R0, R6\n"
			"LDRNEH  R0, [R5,#0x92]\n"
			"CMPNE   R0, #3\n"
			"LDRNE   R0, [R4,#0xC]\n"
			"CMPNE   R0, #1\n"
			"BHI     loc_FF98AD48\n" // 102B: loc_FF98ADFC
"loc_FF98AD40:\n" // loc_FF98ADF4
			"MOV     R0, #2\n"
			"BL      sub_FF87F4D0\n" // 100D: sub_FF87F4A4
"loc_FF98AD48:\n" // loc_FF98ADFC
			"LDRH    R0, [R5]\n"
			"SUB     R12, R0, #0x8200\n"
			"SUBS    R12, R12, #0x2D\n"
			"BNE     loc_FF98ADA4\n" // 102B: loc_FF98AE58
			"MOV     R5, #1\n"
			"MOV     R2, #2\n"
			"ADD     R0, R2, #0x15C\n"
			"MOV     R1, SP\n"
			"STR     R5, [SP]\n"
			"BL      sub_FF895DE8\n"  //GetPropertyCase 100D: sub_FF895DBC
			"TST     R0, #1\n"
			"MOVNE   R1, #0xC3\n"
			"LDRNE	 R0, =0xFF98AFAC \n"		//ADRNE   R0, aSscaptureseq_c ; // 100D: 0xFF98AEF8
			"BLNE    sub_FF81EB78\n" 	//DebugAssert
			"LDRH    R0, [SP]\n"
			"CMP     R0, #1\n"
			"BLS     loc_FF98AD9C\n" // 102B: loc_FF98AE50
			"MOV     R0, R4\n"
			"STR     R5, [R4,#0xE4]\n"
			"BL      sub_FFAE3DCC\n"	//_SsGISCaptureSeq.c // 100D: sub_FFAE3CDC
			"B       loc_FF98ADAC\n" // 100D: loc_FF98AE60
"loc_FF98AD9C:\n" // loc_FF98AE50
			"MOV     R0, #0\n"
			"STR     R0, [R4,#0xE4]\n"
"loc_FF98ADA4:\n" // loc_FF98AE58
			"MOV     R0, R4\n"
			//"BL      sub_FFAE37CC\n"
		    "BL      sub_FFAE37CC_my\n" // sub_FFAE38BC in 102B
					//---------------->
			"BL      capt_seq_hook_raw_here\n"		// added
"loc_FF98ADAC:\n" // loc_FF98AE60
			"MOV     R7, R0\n"
			"B       loc_FF98ADC4\n" // loc_FF98AE78
"loc_FF98ADB4:\n" // loc_FF98AE68
			"LDR     R0, =0x7C94\n" // 100D: 0x7C8C
			"LDR     R0, [R0]\n"
			"CMP     R0, #0\n"
			"MOVNE   R7, #0x1D\n"
"loc_FF98ADC4:\n" // loc_FF98AE78
			"MOV     R1, R7\n"
			"MOV     R0, R4\n"
			"BL      sub_FFAE2FC4\n" // 100D: sub_FFAE2ED4
			"LDMFD   SP!, {R3-R7,PC}\n"
					);
}


//--------------------------- apexus stuff-------------------
//100D: FF8CCA88 102B: FF8CCAB4
void __attribute__((naked,noinline)) exp_drv_task() {
	asm volatile(
"		STMFD	SP!, {R4-R8,LR}\n"
"		SUB	SP, SP,	#0x20\n"
"		LDR	R8, =0xBB8\n"
"		LDR	R7, =0x4C6C\n"
"		LDR	R5, =0x58054\n"
"		MOV	R0, #0\n"
"		ADD	R6, SP,	#0x10\n"
"		STR	R0, [SP,#0xC]\n"
"loc_FF8CCAA8:\n"
"		LDR	R0, [R7,#0x20]\n"
"		MOV	R2, #0\n"
"		ADD	R1, SP,	#0x1C\n"
"		BL	sub_FF83AE20\n"  //__KerQueue.c__0 ; LOCATION: KerQueue.c:0 // unchanged in 102B
"		LDR	R0, [SP,#0xC]\n"
"		CMP	R0, #1\n"
"		BNE	loc_FF8CCAF4\n" // 102B: loc_FF8CCB20
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R0, [R0]\n"
"		CMP	R0, #0x14\n"
"		CMPNE	R0, #0x15\n"
"		CMPNE	R0, #0x16\n"
"		CMPNE	R0, #0x17\n"
"		BEQ	loc_FF8CCC58\n" // 102B: loc_FF8CCC84
"		CMP	R0, #0x29\n"
"		BEQ	loc_FF8CCBE0\n" // 102B: loc_FF8CCC0C
"		ADD	R1, SP,	#0xC\n"
"		MOV	R0, #0\n"
"		BL	sub_FF8CCA64\n"  //__ExpDrv.c__512 ; LOCATION: ExpDrv.c:512 100D: sub_FF8CCA38
"loc_FF8CCAF4:\n"  // loc_FF8CCB20
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R1, [R0]\n"
"		CMP	R1, #0x2F\n"
"		BNE	loc_FF8CCB24\n" // loc_FF8CCB50
"		LDR	R0, [SP,#0x1C]\n"
"		BL	sub_FF8CDE64\n"  //__ExpDrv.c__0 ; LOCATION: ExpDrv.c:0 100D: sub_FF8CDE38
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R1, #1\n"
"		BL	sub_FF88DBB8\n" // 100D: sub_FF88DB8C
"		BL	sub_FF81EB30\n" //ExitTask	; LOCATION: KerTask.c:0 // unchanged from 100D
"		ADD	SP, SP,	#0x20\n"
"		LDMFD	SP!, {R4-R8,PC}\n"
"loc_FF8CCB24:\n" // loc_FF8CCB50
"		CMP	R1, #0x2E\n"
"		BNE	loc_FF8CCB40\n" // loc_FF8CCB6C
"		LDR	R2, [R0,#0x8C]!\n"
"		LDR	R1, [R0,#4]\n"
"		MOV	R0, R1\n"
"		BLX	R2\n"
"		B	loc_FF8CD120\n" // loc_FF8CD14C
"loc_FF8CCB40:\n" // loc_FF8CCB6C
"		CMP	R1, #0x27\n"
"		BNE	loc_FF8CCB90\n" // loc_FF8CCBBC
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R1, #0x80\n"
"		BL	sub_FF88DBEC\n" // 100D: sub_FF88DBC0
"		LDR	R0, =0xFF8C8874\n" // 100D: 0xFF8C8848
"		MOV	R1, #0x80\n"
"		BL	sub_FF974480\n"  //__IrisController.c__116 ; LOCATION: IrisController.c:116 100D: sub_FF974434
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R2, R8\n"
"		MOV	R1, #0x80\n"
"		BL	sub_FF88DAF8\n"  //__KerFlag.c__0 ; LOCATION:	KerFlag.c:0 // 100D: sub_FF88DACC 
"		TST	R0, #1\n"
"		LDRNE	R1, =0x1089\n"
"		BNE	loc_FF8CCC4C\n" // loc_FF8CCC78
"loc_FF8CCB7C:\n" // loc_FF8CCBA8
"		LDR	R1, [SP,#0x1C]\n"
"		LDR	R0, [R1,#0x90]\n"
"		LDR	R1, [R1,#0x8C]\n"
"		BLX	R1\n"
"		B	loc_FF8CD120\n" // loc_FF8CD14C
"loc_FF8CCB90:\n" // loc_FF8CCBBC
"		CMP	R1, #0x28\n"
"		BNE	loc_FF8CCBD8\n" // loc_FF8CCC04
"		ADD	R1, SP,	#0xC\n"
"		BL	sub_FF8CCA64\n"  //__ExpDrv.c__512 ; LOCATION: ExpDrv.c:512 100D: sub_FF8CCA38
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R1, #0x100\n"
"		BL	sub_FF88DBEC\n" // 100D: sub_FF88DBC0
"		LDR	R0, =0xFF8C8884\n" // 100D: FF8C8858
"		MOV	R1, #0x100\n"
"		BL	sub_FF974E0C\n"  //__IrisController.c__0 ; LOCATION: IrisController.c:0 100D: sub_FF974DC4
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R2, R8\n"
"		MOV	R1, #0x100\n"
"		BL	sub_FF88DAF8\n"  //__KerFlag.c__0 ; LOCATION:	KerFlag.c:0 100D: sub_FF88DACC
"		TST	R0, #1\n"
"		BEQ	loc_FF8CCB7C\n" // loc_FF8CCBA8
"		LDR	R1, =0x1093\n"
"		B	loc_FF8CCC4C\n" // loc_FF8CCC78
"loc_FF8CCBD8:\n" // loc_FF8CCC04
"		CMP	R1, #0x29\n"
"		BNE	loc_FF8CCBF0\n" // loc_FF8CCC1C
"loc_FF8CCBE0:\n" // loc_FF8CCC0C
"		LDR	R0, [SP,#0x1C]\n"
"		ADD	R1, SP,	#0xC\n"
"		BL	sub_FF8CCA64\n" //__ExpDrv.c__512 ; LOCATION: ExpDrv.c:512 100D: sub_FF8CCA38
"		B	loc_FF8CCB7C\n" // loc_FF8CCBA8
"loc_FF8CCBF0:\n" // loc_FF8CCC1C
"		CMP	R1, #0x2C\n"
"		BNE	loc_FF8CCC08\n" // loc_FF8CCC34
"		BL	sub_FF8BA660\n"  //__Shutter.c__2 ; LOCATION:	Shutter.c:2 100D: sub_FF8BA634
"		BL	sub_FF8BB27C\n"  // __ImgPixel.c__272 ; LOCATION: ImgPixel.c:272 100D: sub_FF8BB250
"		BL	sub_FF8BADE8\n"  //__ImgGain.c__0 ; LOCATION:	ImgGain.c:0 100D: sub_FF8BADBC
"		B	loc_FF8CCB7C\n" // loc_FF8CCBA8
"loc_FF8CCC08:\n" // loc_FF8CCC34
"		CMP	R1, #0x2D\n"
"		BNE	loc_FF8CCC58\n" // loc_FF8CCC84
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R1, #4\n"
"		BL	sub_FF88DBEC\n" // 100D: sub_FF88DBC0
"		LDR	R1, =0xFF8C88A4\n" // 100D: FF8C8878
"		LDR	R0, =0xFFFFF400\n" // unchanged from 100D
"		MOV	R2, #4\n"
"		BL	sub_FF8BA0DC\n" // 100D: sub_FF8BA0B0
"		BL	sub_FF8BA364\n"  //__Shutter.c__0 ; LOCATION:	Shutter.c:0 100D: sub_FF8BA338
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R2, R8\n"
"		MOV	R1, #4\n"
"		BL	sub_FF88DA14\n"  // __KerFlag.c__0 ; LOCATION:	KerFlag.c:0 100D: sub_FF88D9E8
"		TST	R0, #1\n"
"		BEQ	loc_FF8CCB7C\n" // loc_FF8CCBA8
"		LDR	R1, =0x10BB\n"
"loc_FF8CCC4C:\n"
"		LDR	R0, =0xFF8C8F74\n"  //aExpdrv_c 100D: FF8C8F48
"		BL	sub_FF81EB78\n"  //DebugAssert
"		B	loc_FF8CCB7C\n" // loc_FF8CCBA8
"loc_FF8CCC58:\n" // loc_FF8CCC84
"		LDR	R0, [SP,#0x1C]\n"
"		MOV	R4, #1\n"
"		LDR	R1, [R0]\n"
"		CMP	R1, #0x12\n"
"		CMPNE	R1, #0x13\n"
"		BNE	loc_FF8CCCC8\n" // loc_FF8CCCF4
"		LDR	R1, [R0,#0x7C]\n"
"		ADD	R1, R1,	R1,LSL#1\n"
"		ADD	R1, R0,	R1,LSL#2\n"
"		SUB	R1, R1,	#8\n"
"		LDMIA	R1, {R2-R4}\n"
"		STMIA	R6, {R2-R4}\n"
"		BL	sub_FF8CB1EC\n"  // __ExpDrv.c__2 ; LOCATION: ExpDrv.c:2 100D: sub_FF8CB1C0
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R1, [R0,#0x7C]\n"
"		LDR	R3, [R0,#0x8C]\n"
"		LDR	R2, [R0,#0x90]\n"
"		ADD	R0, R0,	#4\n"
"		BLX	R3\n"
"		LDR	R0, [SP,#0x1C]\n"
"		BL	sub_FF8CE26C\n"  //__ExpDrv.c__0 ; LOCATION: ExpDrv.c:0 100D: sub_FF8CE240
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R1, [R0,#0x7C]\n"
"		LDR	R3, [R0,#0x94]\n"
"		LDR	R2, [R0,#0x98]\n"
"		ADD	R0, R0,	#4\n"
"		BLX	R3\n"
"		B	loc_FF8CD05C\n" // loc_FF8CD088
"loc_FF8CCCC8:\n" // loc_FF8CCCF4
"		CMP	R1, #0x14\n"
"		CMPNE	R1, #0x15\n"
"		CMPNE	R1, #0x16\n"
"		CMPNE	R1, #0x17\n"
"		BNE	loc_FF8CCD80\n" // loc_FF8CCDAC
"		ADD	R3, SP,	#0xC\n"
"		MOV	R2, SP\n"
"		ADD	R1, SP,	#0x10\n"
"		BL	sub_FF8CB458\n"   // __ExpDrv.c__3168 ;	LOCATION: ExpDrv.c:3168 100D: sub_FF8CB42C
"		CMP	R0, #1\n"
"		MOV	R4, R0\n"
"		CMPNE	R4, #5\n"
"		BNE	loc_FF8CCD1C\n" // loc_FF8CCD48
"		LDR	R0, [SP,#0x1C]\n"
"		MOV	R2, R4\n"
"		LDR	R1, [R0,#0x7C]!\n"
"		LDR	R12, [R0,#0x10]!\n"
"		LDR	R3, [R0,#4]\n"
"		MOV	R0, SP\n"
"		BLX	R12\n"
"		B	loc_FF8CCD54\n" // loc_FF8CCD80
"loc_FF8CCD1C:\n" // loc_FF8CCD48
"		LDR	R0, [SP,#0x1C]\n"
"		CMP	R4, #2\n"
"		LDR	R3, [R0,#0x90]\n"
"		CMPNE	R4, #6\n"
"		BNE	loc_FF8CCD68\n" // loc_FF8CCD94
"		LDR	R12, [R0,#0x8C]\n"
"		MOV	R0, SP\n"
"		MOV	R2, R4\n"
"		MOV	R1, #1\n"
"		BLX	R12\n"
"		LDR	R0, [SP,#0x1C]\n"
"		MOV	R2, SP\n"
"		ADD	R1, SP,	#0x10\n"
"		BL	sub_FF8CC7B0\n"  // __ExpDrv.c__0 ; LOCATION: ExpDrv.c:0 100D: sub_FF8CC784
"loc_FF8CCD54:\n"
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R2, [SP,#0xC]\n"
"		MOV	R1, R4\n"
"		BL	sub_FF8CCA04\n"  // __ExpDrv.c__2 ; LOCATION: ExpDrv.c:2 100D: sub_FF8CC9D8
"		B	loc_FF8CD05C\n" // loc_FF8CD088
"loc_FF8CCD68:\n" // loc_FF8CCD94
"		LDR	R1, [R0,#0x7C]\n"
"		LDR	R12, [R0,#0x8C]\n"
"		ADD	R0, R0,	#4\n"
"		MOV	R2, R4\n"
"		BLX	R12\n"
"		B	loc_FF8CD05C\n" // loc_FF8CD088
"loc_FF8CCD80:\n" // loc_FF8CCDAC 
"		CMP	R1, #0x23\n"
"		CMPNE	R1, #0x24\n"
"		BNE	loc_FF8CCDCC\n" // loc_FF8CCDF8
"		LDR	R1, [R0,#0x7C]\n"
"		ADD	R1, R1,	R1,LSL#1\n"
"		ADD	R1, R0,	R1,LSL#2\n"
"		SUB	R1, R1,	#8\n"
"		LDMIA	R1, {R2-R4}\n"
"		STMIA	R6, {R2-R4}\n"
"		BL	sub_FF8CA260\n"  // __ExpDrv.c__2064 ;	LOCATION: ExpDrv.c:2064 // 100D: sub_FF8CA234
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R1, [R0,#0x7C]\n"
"		LDR	R3, [R0,#0x8C]\n"
"		LDR	R2, [R0,#0x90]\n"
"		ADD	R0, R0,	#4\n"
"		BLX	R3\n"
"		LDR	R0, [SP,#0x1C]\n"
"		BL	sub_FF8CA6AC\n"  // __ExpDrv.c__0 ; LOCATION: ExpDrv.c:0 // 100D: sub_FF8CA680
"		B	loc_FF8CD05C\n" // loc_FF8CD088
"loc_FF8CCDCC:\n" // loc_FF8CCDF8
"		ADD	R1, R0,	#4\n"
"		LDMIA	R1, {R2,R3,R12}\n"
"		STMIA	R6, {R2,R3,R12}\n"
"		LDR	R1, [R0]\n"
"		CMP	R1, #0x26\n"
"		ADDLS	PC, PC,	R1,LSL#2\n"
// mwvent82: TODO comment all these 100D location labels with the real 102B firmware adddress altough its only academic 
"		B	loc_FF8CD03C\n"
"loc_FF8CCDE8:\n"
"		B	loc_FF8CCE84\n"
"loc_FF8CCDEC:\n"
"		B	loc_FF8CCE84\n"
"loc_FF8CCDF0:\n"
"		B	loc_FF8CCE8C\n"
"loc_FF8CCDF4:\n"
"		B	loc_FF8CCE94\n"
"loc_FF8CCDF8:\n"
"		B	loc_FF8CCE94\n"
"loc_FF8CCDFC:\n"
"		B	loc_FF8CCE94\n"
"loc_FF8CCE00:\n"
"		B	loc_FF8CCE84\n"
"loc_FF8CCE04:\n"
"		B	loc_FF8CCE8C\n"
"loc_FF8CCE08:\n"
"		B	loc_FF8CCE94\n"
"loc_FF8CCE0C:\n"
"		B	loc_FF8CCE94\n"
"loc_FF8CCE10:\n"
"		B	loc_FF8CCEAC\n"
"loc_FF8CCE14:\n"
"		B	loc_FF8CCEAC\n"
"loc_FF8CCE18:\n"
"		B	loc_FF8CD028\n"
"loc_FF8CCE1C:\n"
"		B	loc_FF8CD030\n"
"loc_FF8CCE20:\n"
"		B	loc_FF8CD030\n"
"loc_FF8CCE24:\n"
"		B	loc_FF8CD030\n"
"loc_FF8CCE28:\n"
"		B	loc_FF8CD030\n"
"loc_FF8CCE2C:\n"
"		B	loc_FF8CD038\n"
"loc_FF8CCE30:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE34:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE38:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE3C:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE40:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE44:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE48:\n"
"		B	loc_FF8CCE9C\n"
"loc_FF8CCE4C:\n"
"		B	loc_FF8CCEA4\n"
"loc_FF8CCE50:\n"
"		B	loc_FF8CCEA4\n"
"loc_FF8CCE54:\n"
"		B	loc_FF8CCEB8\n"
"loc_FF8CCE58:\n"
"		B	loc_FF8CCEB8\n"
"loc_FF8CCE5C:\n"
"		B	loc_FF8CCEC0\n"
"loc_FF8CCE60:\n"
"		B	loc_FF8CCEF8\n"
"loc_FF8CCE64:\n"
"		B	loc_FF8CCFA0\n"
"loc_FF8CCE68:\n"
"		B	loc_FF8CCFD8\n"
"loc_FF8CCE6C:\n"
"		B	loc_FF8CD010\n"
"loc_FF8CCE70:\n"
"		B	loc_FF8CD010\n"
"loc_FF8CCE74:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE78:\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCE7C:\n"
"		B	loc_FF8CD018\n"
"loc_FF8CCE80:\n"
"		B	loc_FF8CD020\n"
"loc_FF8CCE84:\n"
"		BL	sub_FF8C8DB4\n" //__ExpDrv.c__0 100D: sub_FF8C8D88
"		B	loc_FF8CD03C\n"
"loc_FF8CCE8C:\n"
"		BL	sub_FF8C90A4\n"  //__ExpDrv.c__0 100D: sub_FF8C9078
"		B	loc_FF8CD03C\n"
"loc_FF8CCE94:\n"
"		BL	sub_FF8C930C\n"  //__ExpDrv.c__9 100D: sub_FF8C92E0
"		B	loc_FF8CD03C\n"
"loc_FF8CCE9C:\n"
"		BL	sub_FF8C95C0\n"  //__ExpDrv.c__2 100D: sub_FF8C9594
"		B	loc_FF8CD03C\n"
"loc_FF8CCEA4:\n"
"		BL	sub_FF8C97D8\n" //__ExpDrv.c__0 100D: sub_FF8C97AC
"		B	loc_FF8CD03C\n"
"loc_FF8CCEAC:\n" // loc_FF8CCED8
//"		BL	sub_FF8C9AD0\n"   // the one to override------------------------------
"		BL	sub_FF8C9AD0_my\n"   // first step for apexus // 102B: sub_FF8C9AFC
							//----------------------->
"		MOV	R4, #0\n"
"		B	loc_FF8CD03C\n"
"loc_FF8CCEB8:\n"
"		BL	sub_FF8C9C44\n" // 100D: sub_FF8C9C18
"		B	loc_FF8CD03C\n"
"loc_FF8CCEC0:\n" // loc_FF8CCEEC
"		LDRH	R1, [R0,#4]\n"
"		STRH	R1, [SP,#0x10]\n"
"		LDRH	R1, [R5,#2]\n"
"		STRH	R1, [SP,#0x12]\n"
"		LDRH	R1, [R5,#4]\n"
"		STRH	R1, [SP,#0x14]\n"
"		LDRH	R1, [R5,#6]\n"
"		STRH	R1, [SP,#0x16]\n"
"		LDRH	R1, [R0,#0xC]\n"
"		STRH	R1, [SP,#0x18]\n"
"		LDRH	R1, [R5,#0xA]\n"
"		STRH	R1, [SP,#0x1A]\n"
"		BL	sub_FF8CDF64\n" // 100D: sub_FF8CDF38
"		B	loc_FF8CD03C\n" //  loc_FF8CD068
"loc_FF8CCEF8:\n" // loc_FF8CCF24
"		LDRH	R1, [R0,#4]\n"
"		STRH	R1, [SP,#0x10]\n"
"		LDRH	R1, [R5,#2]\n"
"		STRH	R1, [SP,#0x12]\n"
"		LDRH	R1, [R5,#4]\n"
"		STRH	R1, [SP,#0x14]\n"
"		LDRH	R1, [R5,#6]\n"
"		STRH	R1, [SP,#0x16]\n"
"		LDRH	R1, [R0,#8]\n"
"		STRH	R1, [SP,#0x18]\n"
"		LDRH	R1, [R5,#0xA]\n"
"		STRH	R1, [SP,#0x1A]\n"
"		BL	sub_FF8CE06C\n" // 100D: sub_FF8CE040
"		B	loc_FF8CD03C\n" // loc_FF8CD068


"loc_FF8CCFA0:\n" // loc_FF8CCFCC
"       LDRH    R1, [R5]\n"
"		STRH	R1, [SP,#0x10]\n"
"		LDRH	R1, [R5,#6]\n"
"		STRH	R1, [SP,#0x12]\n"
"		LDRH	R1, [R5,#4]\n"
"		STRH	R1, [SP,#0x14]\n"
"		LDRH	R1, [R5,#6]\n"
"		STRH	R1, [SP,#0x16]\n"
"		LDRH	R1, [R0,#8]\n"
"		STRH	R1, [SP,#0x18]\n"
"		LDRH	R1, [R5,#0xA]\n"
"		STRH	R1, [SP,#0x1A]\n"
"		BL	sub_FF8CE120\n" // 100D: sub_FF8CE0F4
"		B	loc_FF8CD03C\n" // loc_FF8CD068
"loc_FF8CCFD8:\n" // loc_FF8CD004
"       LDRH    R1, [R5]\n"
"		STRH	R1, [SP,#0x10]\n"
"		LDRH	R1, [R5,#2]\n"
"		STRH	R1, [SP,#0x12]\n"
"		LDRH	R1, [R5,#4]\n"
"		STRH	R1, [SP,#0x14]\n"
"		LDRH	R1, [R5,#6]\n"
"		STRH	R1, [SP,#0x16]\n"
"		LDRH	R1, [R0,#0xC]\n"
"		STRH	R1, [SP,#0x18]\n"
"		LDRH	R1, [R5,#0xA]\n"
"		STRH	R1, [SP,#0x1A]\n"
"		BL	sub_FF8CE1C8\n" // 100D: sub_FF8CE19C
"		B	loc_FF8CD03C\n" // loc_FF8CD068

"loc_FF8CD010:\n"
"		BL	sub_FF8CA038\n" // 100D: sub_FF8CA00C
"		B	loc_FF8CD03C\n"
"loc_FF8CD018:\n"
"		BL	sub_FF8CA7B0\n" // 100D: sub_FF8CA784
"		B	loc_FF8CD03C\n"
"loc_FF8CD020:\n"
"		BL	sub_FF8CAA4C\n" // 100D: sub_FF8CAA20
"		B	loc_FF8CD03C\n"
"loc_FF8CD028:\n"
"		BL	sub_FF8CAC2C\n" // 100D: sub_FF8CAC00
"		B	loc_FF8CD03C\n"
"loc_FF8CD030:\n"
"		BL	sub_FF8CADE8\n" // 100D: sub_FF8CADBC
"		B	loc_FF8CD03C\n"
"loc_FF8CD038:\n"
"		BL	sub_FF8CAFE4\n" // 100D: sub_FF8CAFB8
"loc_FF8CD03C:\n"
"		LDR	R0, [SP,#0x1C]\n"
"		LDR	R1, [R0,#0x7C]\n"
"		LDR	R3, [R0,#0x8C]\n"
"		LDR	R2, [R0,#0x90]\n"
"		ADD	R0, R0,	#4\n"
"		BLX	R3\n"
"		CMP	R4, #1\n"
"		BNE	loc_FF8CD0A4\n" // loc_FF8CD0D0
"loc_FF8CD05C:\n" // loc_FF8CD088
"		LDR	R0, [SP,#0x1C]\n"
"		MOV	R2, #0xC\n"
"		LDR	R1, [R0,#0x7C]\n"
"		ADD	R1, R1,	R1,LSL#1\n"
"		ADD	R0, R0,	R1,LSL#2\n"
"		SUB	R4, R0,	#8\n"
"		LDR	R0, =0x58054\n"
"		ADD	R1, SP,	#0x10\n"
"		BL	sub_FFB873EC\n" // 100D: sub_FFB872F4
"		LDR	R0, =0x58060\n"
"		MOV	R2, #0xC\n"
"		ADD	R1, SP,	#0x10\n"
"		BL	sub_FFB873EC\n" // 100D: sub_FFB872F4
"		LDR	R0, =0x5806C\n"
"		MOV	R2, #0xC\n"
"		MOV	R1, R4\n"
"		BL	sub_FFB873EC\n"  //F4 in 100F 100D: sub_FFB872F0
"		B	loc_FF8CD120\n" // 102B: loc_FF8CD14C
"loc_FF8CD0A4:\n"
"		LDR	R0, [SP,#0x1C]\n"
"		MOV	R3, #1\n"
"		LDR	R0, [R0]\n"
"		CMP	R0, #0xB\n"
"		BNE	loc_FF8CD0EC\n"
"		MOV	R2, #0\n"
"		STRD	R2, [SP]\n"
"		MOV	R2, #1\n"
"		MOV	R1, #1\n"
"		MOV	R0, #0\n"
"		BL	sub_FF8C8B94\n" // 100D: sub_FF8C8B68
"		MOV	R3, #1\n"
"		MOV	R2, #0\n"
"		STRD	R2, [SP]\n"
"		MOV	R2, #1\n"
"		MOV	R1, #1\n"
"		MOV	R0, #0\n"
"		B	loc_FF8CD11C\n" // loc_FF8CD148
"loc_FF8CD0EC:\n" // loc_FF8CD118
"		MOV	R2, #1\n"
"		STRD	R2, [SP]\n"
"		MOV	R3, #1\n"
"		MOV	R1, #1\n"
"		MOV	R0, #1\n"
"		BL	sub_FF8C8B94\n" // 100D: sub_FF8C8B68
"		MOV	R3, #1\n"
"		MOV	R2, #1\n"
"		MOV	R1, #1\n"
"		MOV	R0, #1\n"
"		STR	R3, [SP]\n"
"		STR	R3, [SP,#4]\n"
"loc_FF8CD11C:\n" // loc_FF8CD148 
"		BL	sub_FF8C8CFC\n" // sub_FF8C8CD0
"loc_FF8CD120:\n" // loc_FF8CD14C
"		LDR	R0, [SP,#0x1C]\n"
"		BL	sub_FF8CDE64\n" // 100D: sub_FF8CDE38
"		B	loc_FF8CCAA8\n" // loc_FF8CCAD4
					);
}

void __attribute__((naked,noinline)) sub_FF8C9AD0_my() {
// sub_FF8C9AFC in 102B fw
	asm volatile (
"		STMFD	SP!, {R4-R8,LR}\n"
"		LDR	R7, =0x4C6C\n"
"		MOV	R4, R0\n"
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R1, #0x3E\n"
"		BL	sub_FF88DBEC\n" // 100D: sub_FF88DBC0
"		LDRSH	R0, [R4,#4]\n"
"		MOV	R2, #0\n"
"		MOV	R1, #0\n"
"		BL	sub_FF8C88F8\n" // 100D: sub_FF8C88CC
"		MOV	R5, R0\n"
"		LDRSH	R0, [R4,#6]\n"
"		BL	sub_FF8C8A08\n" // 100D: sub_FF8C89DC
"		LDRSH	R0, [R4,#8]\n"
"		BL	sub_FF8C8A60\n" // 100D: sub_FF8C8A34
"		LDRSH	R0, [R4,#0xA]\n"
"		BL	sub_FF8C8AB8\n" // 100D: sub_FF8C8A8C
"		LDRSH	R0, [R4,#0xC]\n"
"		MOV	R1, #0\n"
"		BL	sub_FF8C8B10\n" // 100D: sub_FF8C8AE4
"		MOV	R6, R0\n"
"		LDRSH	R0, [R4,#0xE]\n"
"		BL	sub_FF8CDF04\n" // 100D: sub_FF8CDED8
"		LDR	R0, [R4]\n"
"		LDR	R8, =0x5806C\n" 
"		CMP	R0, #0xB\n"
"		MOVEQ	R5, #0\n"
"		MOVEQ	R6, #0\n"
"		BEQ	loc_FF8C9B6C\n" // loc_FF8C9B98
"		CMP	R5, #1\n"
"		BNE	loc_FF8C9B6C\n" // loc_FF8C9B98
"		LDRSH	R0, [R4,#4]\n"
"		LDR	R1, =0xFF8C8864\n" // 100D: 0xFF8C8838
"		MOV	R2, #2\n"
"		BL	sub_FF9747C8\n"  //__IrisController.c__190 ; LOCATION: IrisController.c:190 100D: sub_FF974780
"		STRH	R0, [R4,#4]\n"
"		MOV	R0, #0\n"
"		STR	R0, [R7,#0x28]\n"
"		B	loc_FF8C9B74\n" // loc_FF8C9BA0
"loc_FF8C9B6C:\n"
"		LDRH	R0, [R8]\n"
"		STRH	R0, [R4,#4]\n"
"loc_FF8C9B74:\n"
"		CMP	R6, #1\n"
"		LDRNEH	R0, [R8,#8]\n"
"		BNE	loc_FF8C9B90\n" // loc_FF8C9BBC
"		LDRSH	R0, [R4,#0xC]\n"
"		LDR	R1, =0xFF8C88E8\n" // 100D: FF8C88BC
"		MOV	R2, #0x20\n"
"		BL	sub_FF8CDEF4\n" // sub_FF8CDF20
"loc_FF8C9B90:\n" // loc_FF8C9BBC
"		STRH	R0, [R4,#0xC]\n"
"		LDRSH	R0, [R4,#6]\n"
//"		BL	sub_FF8BA3A4\n"  // last step __Shutter.c__0 ; LOCATION:	Shutter.c:0
"		BL	sub_FF8BA3A4_my\n" // sub_FF8BA3D0 in 102B
		//------------------------>
"B      sub_FF8C9BC8\n" // Continue function in firmware 100D: FF8C9B9C

/*
"		LDRSH	R0, [R4,#8]\n"
"		MOV	R1, #1\n"
"		BL	_sub_FF8BAB04__ImgGain.c__0 ; LOCATION:	ImgGain.c:0\n"
"		MOV	R1, #0\n"
"		ADD	R0, R4,	#8\n"
"		BL	_sub_FF8BAB8C__ImgGain.c__352 ;	LOCATION: ImgGain.c:352\n"
"		LDRSH	R0, [R4,#0xE]\n"
"		BL	_sub_FF8C37D0__BrtCrct.c__0 ; LOCATION:	BrtCrct.c:0\n"
"		LDR	R4, =0xBB8\n"
"		CMP	R5, #1\n"
"		BNE	loc_FF8C9BE8\n"
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R2, R4\n"
"		MOV	R1, #2\n"
"		BL	_sub_FF88DACC__KerFlag.c__0 ; LOCATION:	KerFlag.c:0\n"
"		TST	R0, #1\n"
"		LDRNE	R1, =0x61E\n"
"		ADRNE	R0, aExpdrv_c	; "ExpDrv.c"\n"
"		BLNE	DebugAssert\n"
"\n"
"loc_FF8C9BE8				; CODE XREF: _sub_FF8C9AD0__ExpDrv.c__2+F4j\n"
"		CMP	R6, #1\n"
"		LDMNEFD	SP!, {R4-R8,PC}\n"
"		LDR	R0, [R7,#0x1C]\n"
"		MOV	R2, R4\n"
"		MOV	R1, #0x20\n"
"		BL	_sub_FF88DACC__KerFlag.c__0 ; LOCATION:	KerFlag.c:0\n"
"		TST	R0, #1\n"
"		LDRNE	R1, =0x623\n"
"		LDRNE	R0, =aExpdrv_c\n"
"		LDMNEFD	SP!, {R4-R8,LR}\n"
"		BNE	DebugAssert\n"
"		LDMFD	SP!, {R4-R8,PC}\n"
*/

				);
}



void __attribute__((naked,noinline)) sub_FF8BA3A4_my() {
// sub_FF8BA3D0 in 102B
	asm volatile (
"		STMFD	SP!, {R4-R6,LR}\n"
"		LDR	R5, =0x4934\n"
"		MOV	R4, R0\n"
"		LDR	R0, [R5,#4]\n"
"		CMP	R0, #1\n"
"		LDRNE	R1, =0x146\n"
"		LDRNE	R0, =0xFF8BA1D4\n"  //	Shutter.c 100D: 0xFF8BA1A8
"		BLNE	sub_FF81EB78\n"  //DebugAssert
"		CMN	R4, #0xC00\n"
"		LDREQSH	R4, [R5,#2]\n"
"		CMN	R4, #0xC00\n"
"		MOVEQ	R1, #0x14C\n"
"		LDREQ	R0, =0xFF8BA1D4\n"  //	Shutter.c 100D: 0xFF8BA1A8
"		STRH	R4, [R5,#2]\n"
"		BLEQ	sub_FF81EB78\n"  //DebugAssert
"		MOV	R0, R4\n"
"		BL	apex2us\n"  //++ was sub_FFA34F70 in 102B fw
"		MOV	R4, R0\n"
"		BL	sub_FF9066C8\n"  //nullsub_68 100D: FF90667C
"		MOV	R0, R4\n"
"		BL	sub_FF910B44\n" // 100D : sub_FF910AF8
"		TST	R0, #1\n"
"		LDRNE	R1, =0x151\n"
"		LDMNEFD	SP!, {R4-R6,LR}\n"
"		LDRNE	R0, =0xFF8BA1D4\n"  //	Shutter.c 100D: 0xFF8BA1A8
"		BNE	sub_FF81EB78\n"  //DebugAssert
"		LDMFD	SP!, {R4-R6,PC}\n"

				);
}
