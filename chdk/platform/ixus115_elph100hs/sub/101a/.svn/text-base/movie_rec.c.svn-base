#include "conf.h"

void change_video_tables(int a, int b){
}


void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

//elph100 sub_FF982008
void __attribute__((naked,noinline)) movie_record_task(){
	asm volatile(

	             "STMFD   SP!, {R2-R10,LR}\n"
                 "LDR     R6, =0xFF980D78\n"	//nullsub_263
                 "LDR     R7, =sub_FF981A60_my\n"    //elph100 patched
                 "LDR     R4, =0x6D10\n"
                 "LDR     R9, =0x67F\n"
                 "LDR     R10, =0x2710\n"
                 "MOV     R8, #1\n"
                 "MOV     R5, #0\n"
 "loc_FF982028:\n"
                 "LDR     R0, [R4,#0x24]\n"
                 "MOV     R2, #0\n"
                 "ADD     R1, SP, #4\n"
                 "BL      sub_FF83B068\n"
                 "LDR     R0, [R4,#0x2C]\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R0, [R4,#0xC]\n"
                 "CMPNE   R0, #2\n"
                 "LDRNE   R0, [R4,#0x44]\n"
                 "CMPNE   R0, #6\n"
                 "BNE     loc_FF982164\n"
                 "LDR     R0, [SP,#4]\n"
                 "LDR     R1, [R0]\n"
                 "SUB     R1, R1, #2\n"
                 "CMP     R1, #0xD\n"
                 "ADDCC   PC, PC, R1,LSL#2\n"
                 "B       loc_FF982164\n"


 "loc_FF98206C:\n"
                 "B       loc_FF982104\n"


 "loc_FF982070:\n"
                 "B       loc_FF982128\n"


 "loc_FF982074:\n"
                 "B       loc_FF982138\n"


 "loc_FF982078:\n"
                 "B       loc_FF982140\n"


 "loc_FF98207C:\n"
                 "B       loc_FF982148\n"


 "loc_FF982080:\n"
                 "B       loc_FF982150\n"


 "loc_FF982084:\n"
                 "B       loc_FF98210C\n"


 "loc_FF982088:\n"
                 "B       loc_FF982158\n"


 "loc_FF98208C:\n"
                 "B       loc_FF982118\n"


 "loc_FF982090:\n"
                 "B       loc_FF982164\n"


 "loc_FF982094:\n"
                 "B       loc_FF982160\n"


 "loc_FF982098:\n"
                 "B       loc_FF9820D0\n"


 "loc_FF98209C:\n"
                 "B       loc_FF9820A0\n"

 "loc_FF9820A0:\n"

                 "STR     R5, [R4,#0x40]\n"
                 "STR     R5, [R4,#0x30]\n"
                 "STR     R5, [R4,#0x34]\n"
                 "STRH    R5, [R4,#6]\n"
                 "STR     R6, [R4,#0xD8]\n"
                 "STR     R7, [R4,#0xF0]\n"
                 "LDR     R0, [R4,#0xC]\n"
                 "ADD     R0, R0, #1\n"
                 "STR     R0, [R4,#0xC]\n"
                 "MOV     R0, #6\n"
                 "STR     R0, [R4,#0x44]\n"
                 "B       loc_FF9820F0\n"


 "loc_FF9820D0:\n"


                 "STR     R5, [R4,#0x40]\n"
                 "STR     R5, [R4,#0x30]\n"
                 "STR     R6, [R4,#0xD8]\n"
                 "STR     R7, [R4,#0xF0]\n"
                 "LDR     R0, [R4,#0xC]\n"
                 "ADD     R0, R0, #1\n"
                 "STR     R0, [R4,#0xC]\n"
                 "STR     R8, [R4,#0x44]\n"

 "loc_FF9820F0:\n"
                 "LDR     R2, =0xFF9803C0\n"	//was LDR     R2, =sub_FF9803C0
                 "LDR     R1, =0xB2A28\n"
                 //"LDR     R0, =sub_FF9804D4\n"	//wtf?
				 "LDR     R0, =0xFF9804D4\n"
                 "BL      sub_FF854B04\n"
                 "B       loc_FF982164\n"


 "loc_FF982104:\n"

                 "BL      sub_FF981644\n"
                 "B       loc_FF982164\n"


 "loc_FF98210C:\n"


                 "LDR     R1, [R4,#0xF0]\n"
                 "BLX     R1\n"
                 "B       loc_FF982164\n"


 "loc_FF982118:\n"


                 "LDR     R1, [R0,#0x18]\n"
                 "LDR     R0, [R0,#4]\n"
                 "BL      sub_FFAE057C\n"  //1.01a
                 "B       loc_FF982164\n"


 "loc_FF982128:\n"


                 "LDR     R0, [R4,#0x44]\n"
                 "CMP     R0, #5\n"
                 "STRNE   R8, [R4,#0x34]\n"
                 "B       loc_FF982164\n"


 "loc_FF982138:\n"


                 "BL      sub_FF980A54\n"
                 "B       loc_FF982164\n"


 "loc_FF982140:\n"


                 "BL      sub_FF980774\n"
                 "B       loc_FF982164\n"


 "loc_FF982148:\n"


                 "BL      sub_FF98052C\n"
                 "B       loc_FF982164\n"


 "loc_FF982150:\n"


                 "BL      sub_FF980158\n"
                 "B       loc_FF982164\n"


 "loc_FF982158:\n"


                 "BL      sub_FF9800D8\n"
                 "B       loc_FF982164\n"


 "loc_FF982160:\n"


                 "BL      sub_FF9826B4\n"

 "loc_FF982164:\n"

                 "LDR     R1, [SP,#4]\n"
                 "LDR     R3, =0xFF97FE88\n"  //aMovierecorder_
                 "STR     R5, [R1]\n"
                 "STR     R9, [SP]\n"
                 "LDR     R0, [R4,#0x28]\n"
                 "MOV     R2, R10\n"
                 "BL      sub_FF83B9E0\n"
                 "B       sub_FF982028\n"


	);
}



//sub_FF981A60_my
void __attribute__((naked,noinline)) sub_FF981A60_my(){
	asm volatile(

	             "STMFD   SP!, {R4-R11,LR}\n"
                 "SUB     SP, SP, #0x64\n"
                 "MOV     R9, #0\n"
                 "LDR     R8, =0x6D10\n"
                 "STR     R9, [SP,#0x54]\n"
                 "STR     R9, [SP,#0x4C]\n"
                 "STR     R9, [R8,#0xDC]\n"
                 "STR     R9, [R8,#0xE0]\n"
                 "STR     R9, [R8,#0xE4]\n"
                 "MOV     R4, R0\n"
                 "STR     R9, [R8,#0xE8]\n"
                 "LDR     R0, [R8,#0x44]\n"
                 "MOV     R7, R9\n"
                 "CMP     R0, #3\n"
                 "MOVEQ   R0, #4\n"
                 "STREQ   R0, [R8,#0x44]\n"
                 "LDR     R0, [R8,#0xD8]\n"
                 "MOV     R5, #1\n"
                 "MOV     R6, R9\n"
                 "BLX     R0\n"
                 "LDR     R0, [R8,#0x44]\n"
                 "CMP     R0, #6\n"
                 "BEQ     loc_FF981AD0\n"
                 "LDR     R1, [R8,#0xC]\n"
                 "CMP     R1, #2\n"
                 "BNE     loc_FF981AF8\n"
                 "CMP     R0, #5\n"
                 "BEQ     loc_FF981B08\n"

 "loc_FF981AD0:\n"
                 "LDR     R2, =0xFF981934\n"
                 "LDR     R1, =0xFF981998\n"
                 "LDR     R0, =0xFF9819FC\n"
                 "MOV     R6, #1\n"
                 "ADD     R3, SP, #0x34\n"
                 "BL      sub_FF8559B0\n"
                 "LDR     R0, [R8,#0x44]\n"
                 "CMP     R0, #4\n"
                 "MOVNE   R5, #0\n"
                 "B       loc_FF981B18\n"

 "loc_FF981AF8:\n"
                 "CMP     R0, #4\n"
                 "BEQ     loc_FF981B18\n"
                 "CMP     R1, #2\n"
                 "BNE     loc_FF981B10\n"

 "loc_FF981B08:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF8559BC\n"

 "loc_FF981B10:\n"

                 "ADD     SP, SP, #0x64\n"
                 "LDMFD   SP!, {R4-R11,PC}\n"

 "loc_FF981B18:\n"

                 "LDRH    R0, [R8,#6]\n"
                 "CMP     R0, #3\n"
                 "BNE     loc_FF981B38\n"
                 "LDR     R0, [R8,#0x6C]\n"
                 "LDR     R1, [R8,#0xEC]\n"
                 "BL      sub_FFB9457C\n"  //1.01a
                 "CMP     R1, #0\n"
                 "MOVNE   R5, #0\n"

 "loc_FF981B38:\n"
                 "LDR     R0, [R8,#0x44]\n"
                 "CMP     R0, #6\n"
                 "CMPNE   R0, #1\n"
                 "CMPNE   R0, #3\n"
                 "BNE     loc_FF981B7C\n"
                 "CMP     R6, #1\n"
                 "CMPEQ   R5, #0\n"
                 "BNE     loc_FF981B7C\n"
                 "BL      sub_FF8559B4\n"
                 "LDR     R0, [R8,#0x18]\n"
                 "MOV     R1, #0x3E8\n"
                 "BL      sub_FF83B484\n"
                 "CMP     R0, #9\n"
                 "BNE     loc_FF981F84\n"
                 "MOV     R0, #0x90000\n"
                 "BL      sub_FF8999F0\n"
                 "B       loc_FF981B10\n"

 "loc_FF981B7C:\n"

                 "CMP     R5, #1\n"
                 "MOV     R10, #1\n"
                 "BNE     loc_FF981BA4\n"
                 "ADD     R3, SP, #0x4C\n"
                 "ADD     R2, SP, #0x50\n"
                 "ADD     R1, SP, #0x54\n"
                 "ADD     R0, SP, #0x58\n"
                 "BL      sub_FFAE06A4\n"  //1.01a
                 "MOVS    R9, R0\n"
                 "BNE     loc_FF981BC0\n"

 "loc_FF981BA4:\n"
                 "LDR     R0, [R8,#0x34]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF981D00\n"
                 "LDR     R0, [R8,#0x6C]\n"
                 "LDR     R1, [R8,#0x48]\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FF981D00\n"

 "loc_FF981BC0:\n"
                 "MOV     R0, R9\n"
                 "BL      sub_FF980EEC\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "CMP     R0, #2\n"
                 "BNE     loc_FF981C30\n"
                 "LDR     R0, =0xFF981928\n"	//was LDR     R0, =sub_FF981928
                 "MOV     R1, #0\n"
                 "BL      sub_FFA998AC\n"
                 "LDR     R2, [R8,#0x64]\n"
                 "ADD     R3, SP, #0x5C\n"
                 "STRD    R2, [SP,#0x28]\n"
                 "MOV     R2, #0x18\n"
                 "ADD     R1, SP, #0x34\n"
                 "ADD     R0, SP, #0x10\n"
                 "BL      sub_FFB94260\n"  //1.01a
                 "LDR     R1, [R8,#0x84]\n"
                 "LDR     R2, [R8,#0x88]\n"
                 "MOV    R3, #0xFFFFFFFE\n"
                 "ADD     R0, SP, #0x60\n"
                 "STMEA   SP, {R0-R3}\n"
                 "MOV     R3, #0\n"
                 "LDR     R0, =0xB2A74\n"
                 "MOV     R2, R3\n"
                 "MOV     R1, #0x40\n"
                 "BL      sub_FFA997F8\n"
                 "B       loc_FF981C88\n"

 "loc_FF981C28:\n"

                 "MOV     R1, #1\n"
                 "B       loc_FF981F14\n"

 "loc_FF981C30:\n"
                 "BL      loc_FF98278C\n"
                 "LDR     R2, [R8,#0x64]\n"
                 "ADD     R3, SP, #0x5C\n"
                 "MOV    R1, #0xFFFFFFFE\n"
                 "MOV     R0, #0\n"
                 "ADD     R5, SP, #0x1C\n"
                 "STMIA   R5, {R0-R3}\n"
                 "LDR     R3, [R4,#0x1C]\n"
                 "LDR     R1, [R8,#0x84]\n"
                 "LDR     R2, [R8,#0x88]\n"
                 "ADD     R0, SP, #0x60\n"
                 "ADD     R4, SP, #0xC\n"
                 "STMIA   R4, {R0-R3}\n"
                 "MOV     R3, #0\n"
                 "MOV     R1, #0x40\n"
                 "STMEA   SP, {R1,R3}\n"
                 "MOV     R2, #0\n"
                 "STR     R3, [SP,#8]\n"
                 "LDR     R3, =0xB2A74\n"
                 "MOV     R1, R2\n"
                 "MOV     R0, R2\n"
                 "BL      sub_FFA98154\n"

 "loc_FF981C88:\n"
                 "LDR     R0, [R8,#0x18]\n"
                 "LDR     R1, [R8,#0x60]\n"
                 "BL      sub_FF83B484\n"
                 "CMP     R0, #9\n"
                 "BEQ     loc_FF981C28\n"
                 "LDR     R0, [SP,#0x5C]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF981CB0\n"

 "loc_FF981CA8:\n"
                 "MOV     R1, #1\n"
                 "B       loc_FF981F2C\n"

 "loc_FF981CB0:\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "MOV     R4, #5\n"
                 "CMP     R0, #2\n"
                 "MOV     R0, #1\n"
                 "BNE     loc_FF981CEC\n"
                 "BL      sub_FFA9986C\n"
                 "BL      sub_FFA99894\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF8559BC\n"
                 "BL      sub_FF8559CC\n"
                 "STR     R4, [R8,#0x44]\n"
                 "BL      loc_FF98278C\n"
                 "BL      sub_FF855A28\n"
                 "STR     R10, [R8,#0x44]\n"
                 "B       loc_FF981CF8\n"

 "loc_FF981CEC:\n"
                 "BL      sub_FFA98204\n"
                 "BL      sub_FFA98250\n"
                 "STR     R4, [R8,#0x44]\n"

 "loc_FF981CF8:\n"
                 "STR     R7, [R8,#0x34]\n"
                 "B       loc_FF981B10\n"

 "loc_FF981D00:\n"

                 "CMP     R5, #1\n"
                 "BNE     loc_FF981F7C\n"
                 "STR     R10, [R8,#0x38]\n"
                 "LDR     R0, [R8,#0x6C]\n"
                 "LDR     R11, [R4,#0xC]\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R9, [SP,#0x58]\n"
                 "LDRNE   R10, [SP,#0x54]\n"
                 "BNE     loc_FF981E4C\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "CMP     R0, #2\n"
                 "BNE     loc_FF981DA4\n"
                 "LDR     R0, =0xFF981928\n"	//was LDR     R0, =sub_FF981928
                 "MOV     R1, #0\n"
                 "BL      sub_FFA998AC\n"
                 "LDR     R2, [R8,#0x64]\n"
                 "ADD     R3, SP, #0x5C\n"
                 "STRD    R2, [SP,#0x28]\n"
                 "MOV     R2, #0x18\n"
                 "ADD     R1, SP, #0x34\n"
                 "ADD     R0, SP, #0x10\n"
                 "BL      sub_FFB94260\n"  //1.01a
                 "LDR     R1, [R8,#0x84]\n"
                 "LDR     R2, [R8,#0x88]\n"
                 "MOV    R3, #0xFFFFFFFF\n"
                 "ADD     R0, SP, #0x60\n"
                 "STMEA   SP, {R0-R3}\n"
                 "LDR     R0, [SP,#0x58]\n"
                 "LDR     R1, [SP,#0x54]\n"
                 "LDR     R2, [SP,#0x50]\n"
                 "LDR     R3, [SP,#0x4C]\n"
                 "BL      sub_FFA997F8\n"
                 "LDR     R0, [R8,#0x18]\n"
                 "LDR     R1, [R8,#0x60]\n"
                 "BL      sub_FF83B484\n"
                 "CMP     R0, #9\n"
                 "BEQ     loc_FF981C28\n"
                 "LDR     R0, =0xFF980E54\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FFA998AC\n"
                 "B       loc_FF981E0C\n"

 "loc_FF981DA4:\n"
                 "LDR     R0, [R4,#0x20]\n"
                 "LDR     R2, [R8,#0x64]\n"
                 "ADD     R3, SP, #0x5C\n"
                 "MOV    R1, #0xFFFFFFFF\n"
                 "ADD     R9, SP, #0x1C\n"
                 "STMIA   R9, {R0-R3}\n"
                 "LDR     R3, [R4,#0x1C]\n"
                 "LDR     R1, [R8,#0x84]\n"
                 "LDR     R2, [R8,#0x88]\n"
                 "ADD     R0, SP, #0x60\n"
                 "ADD     R9, SP, #0xC\n"
                 "STMIA   R9, {R0-R3}\n"
                 "LDR     R1, [SP,#0x50]\n"
                 "LDR     R2, [SP,#0x54]\n"
                 "LDR     R3, [SP,#0x4C]\n"
                 "STMFA   SP, {R1,R3}\n"
                 "STR     R2, [SP]\n"
                 "LDMIB   R4, {R0,R1}\n"
                 "LDR     R3, [SP,#0x58]\n"
                 "MOV     R2, R11\n"
                 "BL      sub_FFA98154\n"
                 "LDR     R0, [R8,#0x18]\n"
                 "LDR     R1, [R8,#0x60]\n"
                 "BL      sub_FF83B484\n"
                 "CMP     R0, #9\n"
                 "BEQ     loc_FF981C28\n"

 "loc_FF981E0C:\n"
                 "LDR     R0, [SP,#0x5C]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF981CA8\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "CMP     R0, #2\n"
                 "MOV     R0, #1\n"
                 "BNE     loc_FF981E30\n"
                 "BL      sub_FFA9986C\n"
                 "B       loc_FF981E34\n"

 "loc_FF981E30:\n"
                 "BL      sub_FFA98204\n"

 "loc_FF981E34:\n"
                 "STR     R7, [R8,#0xE8]\n"
                 "LDR     R0, [SP,#0x60]\n"
                 "LDR     R1, [SP,#0x58]\n"
                 "ADD     R9, R1, R0\n"
                 "LDR     R1, [SP,#0x54]\n"
                 "SUB     R10, R1, R0\n"

 "loc_FF981E4C:\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "LDR     R2, [R8,#0x64]\n"
                 "CMP     R0, #2\n"
                 "ADD     R3, SP, #0x5C\n"
                 "BNE     loc_FF981EA4\n"
                 "STRD    R2, [SP,#0x28]\n"
                 "MOV     R2, #0x18\n"
                 "ADD     R1, SP, #0x34\n"
                 "ADD     R0, SP, #0x10\n"
                 "BL      sub_FFB94260\n"  //1.01a
                 "LDR     R1, [R8,#0x84]\n"
                 "LDR     R2, [R8,#0x88]\n"
                 "LDR     R3, [R8,#0x68]\n"
                 "ADD     R0, SP, #0x60\n"
                 "STMEA   SP, {R0-R3}\n"
                 "LDR     R2, [SP,#0x50]\n"
                 "LDR     R3, [SP,#0x4C]\n"
                 "MOV     R1, R10\n"
                 "MOV     R0, R9\n"
                 "BL      sub_FFA997F8\n"
                 "BL      sub_FF8559B4\n"
                 "B       loc_FF981EFC\n"

 "loc_FF981EA4:\n"
                 "LDR     R1, [R8,#0x68]\n"
                 "LDR     R0, [R4,#0x20]\n"
                 "STR     R1, [SP,#0x20]\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "STR     R2, [SP,#0x24]\n"
                 "STR     R3, [SP,#0x28]\n"
                 "LDR     R3, [R4,#0x1C]\n"
                 "LDR     R1, [R8,#0x84]\n"
                 "LDR     R2, [R8,#0x88]\n"
                 "ADD     R0, SP, #0x60\n"
                 "STR     R2, [SP,#0x14]\n"
                 "LDR     R2, [SP,#0x50]\n"
                 "STR     R1, [SP,#0x10]\n"
                 "STR     R3, [SP,#0x18]\n"
                 "LDR     R3, [SP,#0x4C]\n"
                 "STR     R0, [SP,#0xC]\n"
                 "STMFA   SP, {R2,R3}\n"
                 "STR     R10, [SP]\n"
                 "LDMIB   R4, {R0,R1}\n"
                 "MOV     R3, R9\n"
                 "MOV     R2, R11\n"
                 "BL      sub_FFA98154\n"

 "loc_FF981EFC:\n"
                 "LDR     R0, [R8,#0x18]\n"
                 "LDR     R1, [R8,#0x60]\n"
                 "BL      sub_FF83B484\n"
                 "CMP     R0, #9\n"
                 "BNE     loc_FF981F1C\n"
                 "MOV     R1, #0\n"

 "loc_FF981F14:\n"
                 "MOV     R0, #0x90000\n"
                 "B       loc_FF981F30\n"

 "loc_FF981F1C:\n"
                 "LDR     R0, [SP,#0x5C]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF981F38\n"
                 "MOV     R1, #0\n"

 "loc_FF981F2C:\n"
                 "MOV     R0, #0xA0000\n"

 "loc_FF981F30:\n"
                 "BL      sub_FF981268\n"
                 "B       loc_FF981B10\n"

 "loc_FF981F38:\n"
                 "LDR     R0, [R8,#0xC]\n"
                 "CMP     R0, #2\n"
                 "MOV     R0, #0\n"
                 "BNE     loc_FF981F50\n"
                 "BL      sub_FFA9986C\n"
                 "B       loc_FF981F54\n"

 "loc_FF981F50:\n"
                 "BL      sub_FFA98204\n"

 "loc_FF981F54:\n"
                 "LDR     R0, [SP,#0x58]\n"
                 "LDR     R1, [SP,#0x60]\n"
                 "BL      sub_FFAE0938\n"  //1.01a
                 "LDR     R0, [R8,#0x68]\n"
                 "LDR     R3, =0x6D98\n"      //6D98 - 4
                 "ADD     R1, R0, #1\n"
                 "STR     R1, [R8,#0x68]\n"
                 "LDR     R0, [SP,#0x60]\n"
                 "SUB     R2, R3, #4\n"       //-4
                 "BL      sub_FFADD14C\n" //1.01a

				 "LDR 		R0, =0x6D94 \n"			// added from s95 code. maybe not needed. was 0x71AC(71b0 - 4)
				 "BL		set_quality \n"			// added
				 "BL	unlock_optical_zoom\n"
 "loc_FF981F7C:\n"
                 "CMP     R6, #1\n"
                 "BNE     loc_FF981F90\n"

 "loc_FF981F84:\n"
                 "BL      sub_FF8559B8\n"
                 "MOV     R0, #1\n"
                 "BL      sub_FF8559BC\n"

 "loc_FF981F90:\n"
                 "CMP     R5, #1\n"
                 "LDRNEH  R0, [R8,#6]\n"
                 "CMPNE   R0, #3\n"
                 "BNE     loc_FF981B10\n"
                 "LDR     R0, [R8,#0x6C]\n"
                 "ADD     R0, R0, #1\n"
                 "STR     R0, [R8,#0x6C]\n"
                 "LDRH    R1, [R8,#6]\n"
                 "CMP     R1, #3\n"
                 "LDRNE   R1, [R8,#0x54]\n"
                 "LDREQ   R1, =0x3E9\n"
                 "MUL     R0, R1, R0\n"
                 "LDRNE   R1, [R8,#0x50]\n"
                 "LDREQ   R1, =0x1770\n"
                 "BL      sub_FFB9457C\n"  //1.01A
                 "MOV     R4, R0\n"
                 "BL      sub_FFAE0FC4\n"  //1.01A
                 "LDR     R0, [R8,#0x8C]\n"
                 "CMP     R0, R4\n"
                 "BNE     loc_FF981FEC\n"
                 "LDR     R0, [R8,#0x3C]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF982000\n"

 "loc_FF981FEC:\n"
                 "LDR     R1, [R8,#0xBC]\n"
                 "MOV     R0, R4\n"
                 "BLX     R1\n"
                 "STR     R4, [R8,#0x8C]\n"
                 "STR     R7, [R8,#0x3C]\n"

 "loc_FF982000:\n"
                 "STR     R7, [R8,#0x38]\n"
                 "B       loc_FF981B10\n"

 //added to fix compiler error
 "loc_FF98278C:\n"
                 "LDR     R0, =0xB2A5C\n"
                 "LDR     R0, [R0,#8]\n"
                 "CMP     R0, #0\n"
                 "BEQ     sub_FF9800D8\n"
                 "BNE     sub_FF866398\n"

	);
 }
