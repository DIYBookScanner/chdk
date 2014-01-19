#include "conf.h"

void change_video_tables(int a, int b){
}


void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// ASM1989, rereview 19.09.10 FF96E110
void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
                 "STMFD   SP!, {R2-R8,LR}\n"
                 "LDR     R8, =0x4B2\n"			// In sx200:0x442
                 "LDR     R7, =0x2710\n"		// In sx200:0x2710
                 "LDR     R4, =0x71D0\n"		// In sx200:0x6588
                 "MOV     R6, #0\n"
                 "MOV     R5, #1\n"
"loc_FF96E128:\n"
                 "LDR     R0, [R4,#0x1C]\n"		// In sx200:0x18
                 "MOV     R2, #0\n"
                 "ADD     R1, SP, #4\n"
                 "BL      sub_FF839B88\n"
                 "LDR     R0, [R4,#0x24]\n"		// In sx200:0x20
                 "CMP     R0, #0\n"
                 "BNE     loc_FF96E1F8\n"
                 "LDR     R0, [SP,#4]\n"
                 "LDR     R1, [R0]\n"
                 "SUB     R1, R1, #2\n"
                 "CMP     R1, #0x9\n"
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E15C:\n"
                 "B       loc_FF96E1AC\n"
"loc_FF96E160:\n"
                 "B       loc_FF96E1CC\n"
"loc_FF96E164:\n"
                 "B       loc_FF96E1DC\n"
"loc_FF96E168:\n"
                 "B       loc_FF96E1E4\n"
"loc_FF96E16C:\n"
                 "B       loc_FF96E1B4\n"
"loc_FF96E170:\n"
                 "B       loc_FF96E1EC\n"
"loc_FF96E174:\n"
                 "B       loc_FF96E1BC\n"
"loc_FF96E178:\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E17C:\n"
                 "B       loc_FF96E1F4\n"
"loc_FF96E180:\n"
                 "B       loc_FF96E184\n"
"loc_FF96E184:\n"
                 "LDR     R0, =0xFF96DE54\n"		//nullsub_318
                 "STR     R6, [R4,#0x38]\n"		//Sx200:0x34
                 "STR     R0, [R4,#0xA8]\n"		//Sx200:0x9C
                 "LDR     R2, =0xFF96D37C\n"
                 "LDR     R1, =0x9817C\n"		//Sx200:4C6D8
                 "LDR     R0, =0xFF96D460\n"
                 "STR     R6, [R4,#0x28]\n"		//Sx200:24
                 "BL      sub_FF850ED8\n"
                 "STR     R5, [R4,#0x3C]\n"		//Sx200:38
                 "B       loc_FF96E1F8\n"
"loc_FF96E1AC:\n"
            //     "BL      unlock_optical_zoom\n" 		  -----------> inserted to unlock the zoom, dont need in sx210
                 "BL      sub_FF96DF5C\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E1B4 :\n"
                 "BL      sub_FF96DAE0_my\n"             // in sx200:sub_FF937C70_my
                 								//----------------->
                 "B       loc_FF96E1F8\n"
"loc_FF96E1BC:\n"
                 "LDR     R1, [R0,#0x18]\n"
                 "LDR     R0, [R0,#4]\n"
                 "BL      sub_FFABBB18\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E1CC:\n"
                 "LDR     R0, [R4,#0x3C]\n"
                 "CMP     R0, #5\n"
                 "STRNE   R5, [R4,#0x2C]\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E1DC:\n"
                 "BL      sub_FF96D7DC\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E1E4:\n"
                 "BL      sub_FF96D4AC\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E1EC:\n"
                 "BL      sub_FF96D308\n"
                 "B       loc_FF96E1F8\n"
"loc_FF96E1F4:\n"
                 "BL      sub_FF96E360\n"
"loc_FF96E1F8:\n"
                 "LDR     R1, [SP,#4]\n"
                 "LDR     R3, =0xFF96D194\n"		//aMovierecorder_
                 "STR     R6, [R1]\n"
                 "STR     R8, [SP]\n"
                 "LDR     R0, [R4,#0x20]\n"
                 "MOV     R2, R7\n"
                 "BL      sub_FF83A4DC\n"
                 "B       loc_FF96E128\n"
 );
}  //asm1989 05.09.10 done

void __attribute__((naked,noinline)) sub_FF96DAE0_my(){      // in sx200:sub_FF937C70_my
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "SUB     SP, SP, #0x40\n"    //sx200:44
                 "MOV     R7, #0\n"
                 "LDR     R6, =0x71D0\n"	   //sx200:6588
                 "MOV     R4, R0\n"
                 "STR     R7, [SP,#0x30]\n"   //0x58+var_28
                 "STR     R7, [SP,#0x28]\n"   //#0x58+var_30
                 "LDR     R0, [R6,#0x3C]\n"
                 "MOV     R8, #4\n"
                 "CMP     R0, #3\n"
                 "STREQ   R8, [R6,#0x3C]\n"
                 "LDR     R0, [R6,#0xA8]\n"
		         "BLX 	  R0\n"
                 "LDR     R0, [R6,#0x3C]\n"
                 "CMP     R0, #4\n"
                 "BNE     loc_FF96DC4C\n"
                 "ADD     R3, SP, #0x28\n"  //0x58+var_30
                 "ADD     R2, SP, #0x2C\n"  //#0x58+var_2C
                 "ADD     R1, SP, #0x30\n"  //0x58+var_28
                 "ADD     R0, SP, #0x34\n"  //0x58+var_24
                 "BL      sub_FFABBBB4\n"
                 "CMP     R0, #0\n"
                 "MOV     R5, #1\n"
                 "BNE     loc_FF96DB5C\n"
                 "LDR     R1, [R6,#0x2C]\n"
                 "CMP     R1, #1\n"
                 "BNE     loc_FF96DC54\n"
                 "LDR     R1, [R6,#0x60]\n"
                 "LDR     R2, [R6,#0x40]\n"
                 "CMP     R1, R2\n"
                 "BCC     loc_FF96DC54\n"

"loc_FF96DB5C:\n"
                 "CMP     R0, #0x80000001\n"
                 "STREQ   R8, [R6,#0x64]\n"
                 "BEQ     loc_FF96DB94\n"
                 "CMP     R0, #0x80000003\n"
                 "STREQ   R5, [R6,#0x64]\n"
                 "BEQ     loc_FF96DB94\n"
                 "CMP     R0, #0x80000005\n"
                 "MOVEQ   R0, #2\n"
                 "BEQ     loc_FF96DB90\n"
                 "CMP     R0, #0x80000007\n"
                 "STRNE   R7, [R6,#0x64]\n"
                 "BNE     loc_FF96DB94\n"
                 "MOV     R0, #3\n"
"loc_FF96DB90:\n"
                 "STR     R0, [R6,#0x64]\n"
"loc_FF96DB94:\n"
                 "LDR     R0, =0x981B0\n"   //SX200:4C70C
                 "LDR     R0, [R0,#8]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF96DBAC\n"
                 "BL      sub_FF8659EC\n"
                 "B       loc_FF96DBB0\n"

"loc_FF96DBAC:\n"
                 "BL      sub_FF96D308\n"
"loc_FF96DBB0:\n"
                 "LDR     R0, [R4,#0x1C]\n"
                 "ADD     R4, SP, #0x18\n"   //0x58+var_40
                 "ADD     R3, SP, #0x38\n"   //0x58+var_20
                 "MVN     R2, #1\n"
                 "MOV     R1, #0\n"
                 "STMIA   R4, {R0-R3}\n"
                 "ADD     R1, SP, #0x3C\n"		//0x58+var_1C
                 "ADD     R4, SP, #8\n"		//0x58+var_50
                 "MOV     R0, #0\n"
                 "LDRD    R2, [R6,#0x78]\n"
                 "STMIA   R4, {R0-R3}\n"
                 "MOV     R3, #0\n"
                 "MOV     R2, #0x40\n"
                 "STRD    R2, [SP]\n"
                 "LDR     R3, =0x981C8\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FFA74800\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "LDR     R1, [R6,#0x58]\n"
                 "BL      sub_FF839FA4\n"  //eventproc_export_TakeSemaphore
                 "CMP     R0, #9\n"
                 "BNE     loc_FF96DC1C\n"
//sx210 new stuff

"loc_FF96DC0C:\n"
                 "BL      sub_FFABC088\n"
                 "MOV     R0, #1\n"
                 "STR     R5, [R6,#0x3C]\n"
                 "B       loc_FF96DD74\n"
"loc_FF96DC1C:\n"
                 "LDR     R0, [SP,#0x38]\n"		 //0x58+var_20  (Was wrong)
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF96DC38\n"

"loc_FF96DC28:\n"
                 "BL      sub_FFABC088\n"
				 "MOV     R0, #1\n"
                 "STR     R5, [R6,#0x3C]\n"
       			 "B       loc_FF96DDA0\n"
"loc_FF96DC38:\n"
                 "MOV     R0, #1\n"
                 "BL      sub_FFA748A4\n"
                 "BL      sub_FFA74900\n"
                 "MOV     R0, #5\n"
                 "STR     R0, [R6,#0x3C]\n"
"loc_FF96DC4C:\n"
                 "ADD     SP, SP, #0x40\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
   //end of sx210 new stuff

"loc_FF96DC54:\n"
                 "LDR     R12, [SP,#0x30]\n"		//0x58+var_28
                 "CMP     R12, #0\n"
                 "BEQ     loc_FF96DDFC\n"
                 "STR     R5, [R6,#0x30]\n"
                 "LDR     R0, [R6,#0x60]\n"
                 "LDR     R8, [R4,#0xC]\n"
                 "CMP     R0, #0\n"
                 "LDRNE   LR, [SP,#0x34]\n"		//58+var_24
                 "BNE     loc_FF96DCFC\n"
                 "LDR     R0, [R4,#0x1C]\n"
                 "LDR     R1, [R4,#0x20]\n"
                 "ADD     R3, SP, #0x38\n"			//0x58+var_20
                 "MVN     R2, #0\n"
                 "ADD     LR, SP, #0x18\n"		//0x58+var_40
                 "STMIA   LR, {R0-R3}\n"
                 "LDRD    R2, [R6,#0x78]\n"
                 "LDR     R0, [SP,#0x28]\n"		//0x58+var_30
                 "ADD     R1, SP,#0x3C\n"		//x58+var_1C
                 "ADD     LR, SP,#8\n"			//0x58+var_50
                 "STMIA   LR, {R0-R3}\n"
                 "LDR     R3, [SP,#0x2C]\n"		//0x58+var_2C
                 "STR     R12, [SP]\n"
                 "STR     R3, [SP,#4]\n"		//0x58+var_58+4
                 "LDMIB   R4, {R0,R1}\n"
                 "LDR     R3, [SP,#0x34]\n"		//0x58+var_24
                 "MOV     R2, R8\n"
                 "BL      sub_FFA74800\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "LDR     R1, [R6,#0x58]\n"
                 "BL      sub_FF839FA4\n"  //eventproc_export_TakeSemaphore
                 "CMP     R0, #9\n"
                 "BEQ     loc_FF96DC0C\n"
                 "LDR     R0, [SP,#0x38]\n"		//0x58+var_20
                 "CMP     R0, #0\n"
                 "BNE     loc_FF96DC28\n"
                 "MOV     R0, #1\n"
                 "BL      sub_FFA748A4\n"
                 "LDR     R0, [SP,#0x3C]\n"		//0x58+var_1C
                 "LDR     R1, [SP,#0x34]\n"		//0x58+var_24
                 "ADD     LR, R1, R0\n"
                 "LDR     R1, [SP,#0x30]\n"		//0x58+var_28
                 "SUB     R12, R1, R0\n"
"loc_FF96DCFC:\n"
                "LDR     R2, [R6,#0x5C]\n"
				"LDR     R0, [R4,#0x1C]\n"
				"LDR     R1, [R4,#0x20]\n"
				"ADD     R3, SP, #0x38\n"		//0x58+var_20
				"STR     R1, [SP,#0x1C]\n"		//0x58+var_3C
				"STR     R3, [SP,#0x24]\n"		//0x58+var_34
				"STR     R2, [SP,#0x20]\n"	   //0x58+var_38
				"STR     R0, [SP,#0x18]\n"		//0x58+var_40
				"LDRD    R2, [R6,#0x78]\n"
				"LDR     R0, [SP,#0x28]\n"		//0x58+var_30
				"STR     R3, [SP,#0x14]\n"		//0x58+var_44
				"LDR     R3, [SP,#0x2C]\n"		//0x58+var_2C
				"ADD     R1, SP, #0x3C\n"		//0x58+var_1C
				"STR     R2, [SP,#0x10]\n"		//0x58+var_48
				"STR     R3, [SP,#0x4]\n"		//#0x58+var_58+4
				"STR     R1, [SP,#0xC]\n"		//0x58+var_4C
				"STR     R12, [SP]\n"		   //0x58+var_58
				"STR     R0, [SP,#0x8]\n"		//0x58+var_50
				"LDMIB   R4, {R0,R1}\n"
				"MOV     R3, LR\n"
				"MOV     R2, R8\n"
				"BL      sub_FFA74800\n"
				"LDR     R0, [R6,#0x14]\n"
				"LDR     R1, [R6,#0x58]\n"
				"BL      sub_FF839FA4\n"  //eventproc_export_TakeSemaphore
				"CMP     R0, #9\n"
				"BNE     loc_FF96DD88\n"
				"BL      sub_FFABC088\n"
				"MOV     R0, #0\n"
				"STR     R5, [R6,#0x3C]\n"
"loc_FF96DD74:\n"
                 "BL      sub_FFA748A4\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF88BB38\n"  //; LOCATION: ExMemMan.c:0
                 "MOV     R0, #0x90000\n"
                 "B       loc_FF96DDB0\n"
"loc_FF96DD88:\n"
				 "LDR     R0, [SP,#0x38]\n"	//0x58+var_20
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF96DDC4\n"
                 "BL      sub_FFABC088\n"
                 "MOV     R0, #0\n"			// was wrong
				 "STR     R5, [R6,#0x3C]\n"
"loc_FF96DDA0:\n"
                 "BL      sub_FFA748A4\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF88BB38\n"  //; LOCATION: ExMemMan.c:0
                 "MOV     R0, #0xA0000\n"
"loc_FF96DDB0:\n"
				"BL      sub_FF897858\n"  //eventproc_export_HardwareDefect
				"LDR     R1, [R6,#0x98]!\n"
				"LDR     R0, [R6,#0xC]\n"
				"BLX     R1\n"
				"B       loc_FF96DC4C\n"

"loc_FF96DDC4:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FFA748A4\n"

                 "LDR     R0, [SP,#0x34]\n"			//0x58+var_24
                 "LDR     R1, [SP,#0x3C]\n"		//0x58+var_1C


                 "BL      sub_FFABBDE0\n"			//LOCATION: MovWriter.c:0
                 "LDR     R0, [R6,#0x5C]\n"
                 "LDR     R3, =0x724C\n"        // ---> -    in sx200:65F0
                 "ADD     R1, R0, #1\n"         //       |
                 "STR     R1, [R6,#0x5C]\n"     //       |
                 "STR     R3, [SP]\n"           //       |   0x58+var_58
                 "LDR     R0, [SP,#0x3C]\n"     //       |  0x58+var_1C
                 "SUB     R3, R3, #4\n"         // ---> -
                 "MOV     R2, #0xF\n"           //       |
                 "BL      sub_FFAB9F20\n"       //       |
                                                //       |
                 "LDR     R0, =0x724C-4\n"      // -<---     // +
                 "BL      set_quality\n"                     // +
"loc_FF96DDFC:\n"
                 "LDR     R0, [R6,#0x60]\n"
                 "ADD     R0, R0, #1\n"
                 "STR     R0, [R6,#0x60]\n"
                 "LDR     R1, [R6,#0x4C]\n"
                 "MUL     R0, R1, R0\n"
                 "LDR     R1, [R6,#0x48]\n"
                 "BL      sub_FFB61FF4\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FFABC0C0\n"
                 "LDR     R1, [R6,#0x80]\n"
                 "CMP     R1, R4\n"
                 "BNE     loc_FF96DE38\n"
                 "LDR     R0, [R6,#0x34]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF96DE4C\n"
"loc_FF96DE38:\n"
                 "LDR     R1, [R6,#0x8C]\n"
                 "MOV     R0, R4\n"
		     	 "BLX 	  R1\n"
                 "STR     R4, [R6,#0x80]\n"
                 "STR     R7, [R6,#0x34]\n"
"loc_FF96DE4C:\n"
                 "STR     R7, [R6,#0x30]\n"
                 "B       loc_FF96DC4C\n"
 );
}  //asm1989 05.09.10 done
