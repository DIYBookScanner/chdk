#include "conf.h"

/*
void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}
*/

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;


long def_table[24]={0x2000, 0x38D, 0x788, 0x5800, 0x9C5, 0x14B8, 0x10000, 0x1C6A, 0x3C45, 0x8000, 0xE35, 0x1E23,
           0x1CCD, -0x2E1, -0x579, 0x4F33, -0x7EB, -0xF0C, 0xE666, -0x170A, -0x2BC6, 0x7333, -0xB85, -0x15E3};

long table[24];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<24;i++) table[i]=(def_table[i]*a)/b; 
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};

void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
			"STMFD 	SP!, {R2-R8,LR}\n"
			"LDR 	R7, =0x2710\n"
			"LDR 	R4, =0x61A0\n"
			"MOV 	R6, #0\n"
			"MOV 	R5, #1\n"
				
		"loc_FFD14504:\n"		
			"LDR 	R0, [R4,#0x18]\n"
			"MOV 	R2, #0\n"
			"ADD 	R1, SP, #0x4\n"
			"BL 	sub_FFC1659C\n"
			"LDR 	R0, [R4,#0x20]\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFD145D4\n"
			"LDR 	R0, [SP,#0x4]\n"
			"LDR 	R1, [R0]\n"
			"SUB 	R1, R1, #2\n"
			"CMP 	R1, #9\n"
			"ADDLS 	PC, PC, R1,LSL#2\n"
			"B 	loc_FFD145D4\n"
				
		"loc_FFD14538:\n"
				"B	loc_FFD14588\n"

		"loc_FFD1453C:\n"
				"B	loc_FFD145A8\n"

		"loc_FFD14540:\n"
				"B	loc_FFD145B8\n"

		"loc_FFD14544:\n"
				"B	loc_FFD145C0\n"

		"loc_FFD14548:\n"
				"B	loc_FFD14590\n"

		"loc_FFD1454C:\n"
				"B	loc_FFD145C8\n"

		"loc_FFD14550:\n"
				"B	loc_FFD14598\n"

		"loc_FFD14554:\n"
				"B	loc_FFD145D4\n"

		"loc_FFD14558:\n"
				"B	loc_FFD145D0\n"

		"loc_FFD1455C:\n"
				"B	loc_FFD14560\n"
				
		"loc_FFD14560:\n"
				"LDR	R0, =0xFFD141FC\n"		// nullsub
				"STR	R6, [R4,#0x34]\n"
				"STR	R0, [R4,#0xA0]\n"
				"LDR	R0, =0xFFD13C80\n"
				"LDR	R2, =0xFFD13B9C\n"
				"LDR	R1, =0x4B5F4\n"
				"STR	R6, [R4,#0x24]\n"
				"BL		sub_FFC293B4\n"
				"STR	R5, [R4,#0x38]\n"
				"B		loc_FFD145D4\n"
				
		"loc_FFD14588:\n"		
// ok
            "BL     unlock_optical_zoom\n" 		//  -----------> inserted			
			"BL 	sub_FFD142F4\n"
			"B 		loc_FFD145D4\n"
				
		"loc_FFD14590:\n"					

			"BL 	sub_0xFFD13FFC_my\n"			// ------------> changed
			//"BL 	sub_FFD13FFC\n"
			"B 		loc_FFD145D4\n"
				
		"loc_FFD14598:\n"					
				
			"LDR 	R1, [R0,#0x10]\n"
			"LDR 	R0, [R0,#4]\n"
			"BL 	sub_FFE10550\n"				// AviWriter.c:705
			"B 		loc_FFD145D4\n"
				
		"loc_FFD145A8:\n"						
				
			"LDR 	R0, [R4,#0x38]\n"
			"CMP 	R0, #5\n"
			"STRNE 	R5, [R4,#0x28]\n"
			"B 		loc_FFD145D4\n"
				
		"loc_FFD145B8:\n"						
				
			"BL 	sub_FFD13E08\n"				// MovieRecorder.c:1606 (calls LiveImageTool.RealStopMjpegMaking
			"B 		loc_FFD145D4\n"
				
		"loc_FFD145C0:\n"					
				
			"BL 	sub_FFD13CCC\n"				// MovieRecorder.c:1492
			"B 		loc_FFD145D4\n"
				
		"loc_FFD145C8:\n"					
				
			"BL 	sub_FFD13B28\n"
			"B 		loc_FFD145D4\n"
				
		"loc_FFD145D0:\n"		
								
			"BL 	sub_FFD14740\n"				// MovieRecorder.c:1250
				
		"loc_FFD145D4:\n"				
			"LDR 	R1, [SP,#4]\n"
			"LDR 	R3, =0x330\n"
			"STR 	R6, [R1]\n"
			"STR 	R3, [SP,#0]\n"
			"LDR 	R0, [R4,#0x1C]\n"
			"LDR    R3, =0xFFD13988\n"
			"MOV 	R2, R7\n"
			"BL 	sub_FFC16EF0\n"
			"B 		loc_FFD14504\n"
 );
}

void __attribute__((naked,noinline)) sub_0xFFD13FFC_my(){ 
 asm volatile(
			"STMFD 	SP!, {R4-R8,LR}\n"
			"SUB 	SP, SP, #0x40\n"			
			"MOV 	R6, #0\n"
			"LDR 	R5, =0x61A0\n"
			"MOV 	R4, R0\n"
			"STR 	R6, [SP,#0x30]\n"
			"STR 	R6, [SP,#0x28]\n"
			"LDR 	R0, [R5,#0x38]\n"
			"MOV 	R8, #4\n"
			"CMP 	R0, #3\n"
			"STREQ 	R8, [R5,#0x38]\n"
			"LDR 	R0, [R5,#0xA0]\n"
			"BLX 	R0\n"			// seems to compile fine with gcc (?)
			"LDR 	R0, [R5,#0x38]\n"
			"CMP 	R0, #4\n"
			"BNE 	loc_FFD140D4\n"
			"ADD 	R3, SP, #0x28\n"
			"ADD 	R2, SP, #0x2C\n"	// was wrong (0x24), corrected.
			"ADD 	R1, SP, #0x30\n"
			"ADD 	R0, SP, #0x34\n"
			"BL 	sub_FFE106E4\n"
			"CMP 	R0, #0\n"
			"MOV 	R7, #1\n"
			"BNE 	loc_FFD14078\n"
			"LDR 	R1, [R5,#0x28]\n"
			"CMP 	R1, #1\n"
			"BNE 	loc_FFD140DC\n"
			"LDR 	R1, [R5,#0x50]\n"
			"LDR 	R2, [R5,#0x3C]\n"
			"CMP 	R1, R2\n"
			"BCC 	loc_FFD140DC\n"
				
		"loc_FFD14078:\n"		
			"CMP 	R0, #0x80000001\n"
			"STREQ 	R8, [R5,#0x54]\n"
			"BEQ 	loc_FFD140B0\n"
			"CMP 	R0, #0x80000003\n"
			"STREQ 	R7, [R5,#0x54]\n"
			"BEQ 	loc_FFD140B0\n"
			"CMP 	R0, #0x80000005\n"
			"MOVEQ 	R0, #2\n"
			"BEQ 	loc_FFD140AC\n"
			"CMP 	R0, #0x80000007\n"
			"STRNE 	R6, [R5,#0x54]\n"
			"BNE 	loc_FFD140B0\n"
			"MOV 	R0, #3\n"
				
		"loc_FFD140AC:\n"		
			"STR 	R0, [R5,#0x54]\n"
				
		"loc_FFD140B0:\n"		
				
			"LDR 	R0, =0x4B624\n"
			"LDR 	R0, [R0,#8]\n"
			"CMP 	R0, #0\n"
			"BEQ 	loc_FFD140C8\n"
			"BL 	sub_FFC38408\n"
			"B 		loc_FFD140CC\n"
				
		"loc_FFD140C8:\n"		
			"BL 	sub_FFD13B28\n"
				
		"loc_FFD140CC:\n"		
			"MOV 	R0, #5\n"
			"STR 	R0, [R5,#0x38]\n"
				
		"loc_FFD140D4:\n"		
				
			"ADD 	SP, SP, #0x40\n"
			"LDMFD 	SP!, {R4-R8,PC}\n"
				
		"loc_FFD140DC:\n"		
			"LDR 	LR, [SP,#0x30]\n"
			"CMP 	LR, #0\n"
			"BEQ 	loc_FFD141A4\n"
			"STR 	R7, [R5,#0x2C]\n"
			"LDR 	R0, [R5,#0x6C]\n"
			"LDR 	R1, [R4,#0x14]\n"
			"LDR 	R2, [R4,#0x18]\n"
			"LDR 	R12, [R4,#0xC]\n"
			"ADD 	R3, SP, #0x38\n"
			"ADD 	R8, SP, #0x14\n"
			"STMIA 	R8, {R0-R3}\n"
			"LDR 	R3, [R5,#0x58]\n"
			"ADD 	R2, SP, #0x3C\n"
			"ADD 	R8, SP, #0x8\n"
			"LDRD 	R0, [SP,#0x28]\n"			
			"STMIA 	R8, {R0,R2,R3}\n"
			"STR 	R1, [SP,#0x4]\n"
			"STR 	LR, [SP,#0x0]\n"
			"LDMIB 	R4, {R0,R1}\n"
			"LDR 	R3, [SP,#0x34]\n"
			"MOV 	R2, R12\n"
			"BL 	sub_FFDE0EF4\n"
			"LDR 	R0, [R5,#0x10]\n"
			"MOV 	R1, #0x3E8\n"
			"BL 	sub_FFC169B8\n"
			"CMP 	R0, #9\n"
			"BNE 	loc_FFD14158\n"
			"BL 	sub_FFE10CC0\n"
			"MOV 	R0, #0x90000\n"
			"STR 	R7, [R5,#0x38]\n"
			"B 		loc_FFD14170\n"
				
		"loc_FFD14158:\n"
			"LDR 	R0, [SP,#0x38]\n"
			"CMP 	R0, #0\n"
			"BEQ 	loc_FFD14178\n"
			"BL 	sub_FFE10CC0\n"
			"MOV 	R0, #0xA0000\n"
			"STR 	R7, [R5,#0x38]\n"
				
		"loc_FFD14170:\n"
			"BL 	sub_FFC660FC\n"
			"B 		loc_FFD140D4\n"
				
		"loc_FFD14178:\n"
			"BL 	sub_FFDE0FB8\n"
			"LDR 	R0, [SP,#0x34]\n"
			"LDR 	R1, [SP,#0x3C]\n"
			"BL 	sub_FFE10A68\n"
			"LDR 	R0, [R5,#0x4C]\n"
			"LDR 	R1, =0x620C\n"
			"ADD 	R0, R0, #1\n"
			"STR 	R0, [R5,#0x4C]\n"
			"LDR 	R0, [SP,#0x3C]\n"
			"MOV 	R2, #0\n"			
			"BL 	sub_FFE0E8E0_my\n"		// changed
			
		"loc_FFD141A4:\n"		
			"LDR 	R0, [R5,#0x50]\n"
			"ADD 	R0, R0, #1\n"
			"STR 	R0, [R5,#0x50]\n"
			"LDR 	R1, [R5,#0x78]\n"
			"MUL 	R0, R1, R0\n"
			"LDR 	R1, [R5,#0x74]\n"
			"BL 	sub_FFE92664\n"
			"MOV 	R4, R0\n"
			"BL 	sub_FFE10CF8\n"
			"LDR 	R1, [R5,#0x70]\n"
			"CMP 	R1, R4\n"
			"BNE 	loc_FFD141E0\n"
			"LDR 	R0, [R5,#0x30]\n"
			"CMP 	R0, #1\n"
			"BNE 	loc_FFD141F4\n"
				
		"loc_FFD141E0:\n"
			"LDR 	R1, [R5,#0x84]\n"
			"MOV 	R0, R4\n"
			"BLX 	R1\n"
			"STR 	R4, [R5,#0x70]\n"
			"STR 	R6, [R5,#0x30]\n"
				
		"loc_FFD141F4:\n"		
			"STR 	R6, [R5,#0x2C]\n"
			"B 	loc_FFD140D4\n"
 );
}

void __attribute__((naked,noinline)) sub_FFE0E8E0_my(){ 
 asm volatile(
		"STMFD 	SP!, {R4-R8,LR} \n"	
		"LDR 	R4, =0x96E4\n"
		"LDR 	LR, [R4]\n"
		"LDR 	R2, [R4,#8]\n"
		"CMP 	LR, #0\n"
		"LDRNE 	R3, [R4,#0xC]\n"
		"MOV 	R5, R2\n"
		"CMPNE 	R3, #1\n"
		"MOVEQ 	R2, #0\n"
		"STREQ 	R0, [R4]\n"
		"STREQ 	R2, [R4,#0xC]\n"
		"BEQ 	loc_FFE0E9AC\n"
		"LDR 	R3, [R4,#4]\n"
//"LDR 	R7, =0xFFEE015C \n"
		"LDR 	R7, =table\n"			// -----> changed
		"ADD 	R12, R3, R3,LSL#1\n"
		"LDR 	R3, [R7,R12,LSL#2]\n"
		"ADD 	R6, R7, #0x30\n"
		"LDR 	R8, [R6,R12,LSL#2]\n"
		"SUB 	R3, LR, R3\n"
		"CMP 	R3, #0\n"
		"SUB 	LR, LR, R8\n"
		"BLE 	loc_FFE0E968\n"
		"ADD 	R12, R7, R12,LSL#2\n"
		"LDR 	LR, [R12,#4]\n"
		"CMP 	LR, R3\n"
		"ADDGE 	R2, R2, #1\n"
		"BGE 	loc_FFE0E95C\n"
		"LDR 	R12, [R12,#8]\n"
		"CMP 	R12, R3\n"
		"ADDLT 	R2, R2, #3\n"
		"ADDGE 	R2, R2, #2\n"
		
"loc_FFE0E95C:\n"
		// number of entries in the table? if >= 26, set to 25
//	"CMP 	R2, #0x17 \n"
//	"MOVGE 	R2, #0x16 \n"
		"CMP     R2, #0x1A\n"   // ---------> changed
		"MOVGE   R2, #0x19\n"   // ---------> changed
		"B 	loc_FFE0E99C\n"
		
"loc_FFE0E968:\n"		
		"CMP 	LR, #0\n"
		"BGE 	loc_FFE0E99C\n"
		"ADD 	R3, R6, R12,LSL#2\n"
		"LDR 	R12, [R3,#4]\n"
		"CMP 	R12, LR\n"
		"SUBLE 	R2, R2, #1\n"
		"BLE 	loc_FFE0E994\n"
		"LDR 	R3, [R3,#8]\n"
		"CMP 	R3, LR\n"
		"SUBGT 	R2, R2, #3\n"
		"SUBLE 	R2, R2, #2\n"

"loc_FFE0E994:\n"
		"CMP 	R2, #0\n"
		"MOVLT 	R2, #0\n"
		
"loc_FFE0E99C:\n"		
		"CMP 	R2, R5\n"
		"STRNE 	R2, [R4,#8]\n"
		"MOVNE 	R2, #1\n"
		"STRNE 	R2, [R4,#0xC]\n"
		
"loc_FFE0E9AC:\n"		
//"LDR 	R2, =0xFFEE0100 \n"			
		"LDR 	R2, =CompressionRateTable\n"			//----------> changed
		"LDR 	R3, [R4,#8] \n"
		"LDR 	R2, [R2,R3,LSL#2] \n"

		"LDR     R3, =video_mode\n"      // --------> inserted
		"LDR     R3, [R3]\n"             // --------> inserted
		"LDR     R3, [R3]\n"             // --------> inserted
		"CMP     R3, #1\n"               // --------> inserted
		"LDREQ   R3, =video_quality\n"   // --------> inserted    
		"LDREQ   R3, [R3]\n"             // --------> inserted     
		"LDREQ   R2, [R3]\n"             // --------> inserted     
		"STR 	R2, [R1] \n"
		"STR 	R0, [R4] \n"

		"BL      mute_on_zoom\n"         // --------> inserted 

		"LDMFD 	SP!, {R4-R8,PC} \n"
		);
} 
