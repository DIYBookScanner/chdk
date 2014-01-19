#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "stdlib.h"

static long *nrflag = (long*)(0x89D4+0x8);  // sx220 FF190524 + 8 
#define NR_AUTO (0)							// have to explictly reset value back to 0 to enable auto
#define PAUSE_FOR_FILE_COUNTER 100          // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated

#include "../../../generic/capt_seq.c"

//SX220 Funnel: Started  :FF077628
void __attribute__((naked,noinline)) capt_seq_task() {
 
 asm volatile (

                 "STMFD   SP!, {R3-R9,LR}\n"
                 "LDR     R5, =0x3EB1C\n"
                 "LDR     R7, =0x3E94\n"
                 "MOV     R6, #0\n"

 "loc_FF077638:\n"                            
                 "LDR     R0, [R7,#4]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, SP\n"
                 "BL      sub_FF02AD50\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF077664\n"
                 "LDR     R1, =0x47A\n"
                 "LDR     R0, =0xFF077054\n"
                 "BL      sub_FF00EC88\n"
                 "BL      sub_FF00EC40\n"
                 "LDMFD   SP!, {R3-R9,PC}\n"

 "loc_FF077664:\n"                           
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x27\n"
                 "ADDCC   PC, PC, R1,LSL#2\n"
                 "B       loc_FF0778E4\n"

 "loc_FF077678:\n"                           
                 "B       loc_FF077714\n"

 "loc_FF07767C:\n"                           
                 "B       loc_FF07772C\n"

 "loc_FF077680:\n"                            
                 "B       loc_FF077764\n"

 "loc_FF077684:\n"                           
                 "B       loc_FF077778\n"

 "loc_FF077688:\n"                           
                 "B       loc_FF077770\n"

 "loc_FF07768C:\n"                           
                 "B       loc_FF077784\n"

 "loc_FF077690:\n"                            
                 "B       loc_FF07778C\n"

 "loc_FF077694:\n"                            
                 "B       loc_FF077794\n"

 "loc_FF077698:\n"                           
                 "B       loc_FF0777B0\n"

 "loc_FF07769C:\n"                           
                 "B       loc_FF0777F0\n"

 "loc_FF0776A0:\n"                           
                 "B       loc_FF0777BC\n"

 "loc_FF0776A4:\n"                            
                 "B       loc_FF0777C8\n"

 "loc_FF0776A8:\n"                           
                 "B       loc_FF0777D0\n"

 "loc_FF0776AC:\n"                           
                 "B       loc_FF0777D8\n"

 "loc_FF0776B0:\n"                           
                 "B       loc_FF0777E0\n"

 "loc_FF0776B4:\n"                           
                 "B       loc_FF0777E8\n"

 "loc_FF0776B8:\n"                            
                 "B       loc_FF0777F8\n"

 "loc_FF0776BC:\n"                           
                 "B       loc_FF077800\n"

 "loc_FF0776C0:\n"                           
                 "B       loc_FF077808\n"

 "loc_FF0776C4:\n"                           
                 "B       loc_FF077810\n"

 "loc_FF0776C8:\n"                            
                 "B       loc_FF077818\n"

 "loc_FF0776CC:\n"                            
                 "B       loc_FF077820\n"

 "loc_FF0776D0:\n"                            
                 "B       loc_FF077828\n"

 "loc_FF0776D4:\n"                           
                 "B       loc_FF077830\n"

 "loc_FF0776D8:\n"                           
                 "B       loc_FF077838\n"

 "loc_FF0776DC:\n"                           
                 "B       loc_FF077840\n"

 "loc_FF0776E0:\n"                           
                 "B       loc_FF07784C\n"

 "loc_FF0776E4:\n"                            
                 "B       loc_FF077854\n"

 "loc_FF0776E8:\n"                           
                 "B       loc_FF077860\n"

 "loc_FF0776EC:\n"                           
                 "B       loc_FF077868\n"

 "loc_FF0776F0:\n"                           
                 "B       loc_FF077870\n"

 "loc_FF0776F4:\n"                            
                 "B       loc_FF077878\n"

 "loc_FF0776F8:\n"                           
                 "B       loc_FF077880\n"

 "loc_FF0776FC:\n"                            
                 "B       loc_FF077888\n"

 "loc_FF077700:\n"                           
                 "B       loc_FF077890\n"

 "loc_FF077704:\n"                          
                 "B       loc_FF077898\n"

 "loc_FF077708:\n"                           
                 "B       loc_FF0778A0\n"

 "loc_FF07770C:\n"                            
                 "B       loc_FF0778AC\n"

 "loc_FF077710:\n"                            
                 "B       loc_FF0778F0\n"

 "loc_FF077714:\n"
                  
				 "BL	  shooting_expo_iso_override\n"	   // added
                 "BL      sub_FF077F04\n"
				 "BL      shooting_expo_param_override\n"  // added                 
 				 "BL      sub_FF074BC4\n"
				 
				 "MOV     R0, #0\n"							// added
				 "STR     R0, [R5,#0x28]\n"					// added, fixes overrides  behavior at short shutter press (from SX30)

//				 "LDR     R0, [R5,#0x28]\n"					// above two lines make this code redundant
//				 "CMP     R0, #0\n"							// above two lines make this code redundant
//				 "BLNE    sub_FF18D9B4\n"					// above two lines make this code redundant

                 "B       loc_FF0778F0\n"

 "loc_FF07772C:\n"                            
                 "LDR     R8, [R0,#0xC]\n"
                 "MOV     R0, R8\n"
				 // "BL      sub_FF18D790\n"    // SX220
				 "BL      sub_FF18D790_my\n"   // + patched
				 "BL      capt_seq_hook_raw_here\n"     //added
				 "MOV     R4, R0\n"
                 "MOV     R2, R8\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF07564C\n"
                 "TST     R4, #1\n"
                 "BNE     loc_FF07775C\n"
        		 "MOV     R0, R8\n"
				 "BL      sub_FF18D17C\n"
				 "B       loc_FF0778F0\n"

 "loc_FF07775C:\n"                           
                 "BL      sub_FF18D14C\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077764:\n"                            
                 "MOV     R0, #1\n"
                 "BL      sub_FF0781E4\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077770:\n"                            
                 "BL      sub_FF077B40\n"
                 "B       loc_FF07777C\n"

 "loc_FF077778:\n"                            
                 "BL      sub_FF077EE4\n"
				 
 "loc_FF07777C:\n"                            
                 "STR     R6, [R5,#0x28]\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077784:\n"                           
                 "BL      sub_FF077EEC\n"
                 "B       loc_FF0778F0\n"

 "loc_FF07778C:\n"                           
                 "BL      sub_FF0780D8\n"
                 "B       loc_FF0777B4\n"

 "loc_FF077794:\n"                            
                 "LDR     R4, [R0,#0xC]\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF18DA08\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #9\n"
                 "BL      sub_FF07564C\n"
                 "B       loc_FF0778F0\n"
 "loc_FF0777B0:\n"                           
                 "BL      sub_FF07814C\n"

 "loc_FF0777B4:\n"                            
                 "BL      sub_FF074BC4\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777BC:\n"                            
                 "LDR     R0, [R5,#0x58]\n"
                 "BL      sub_FF078A6C\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777C8:\n"                           
                 "BL      sub_FF078D38\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777D0:\n"                           
                 "BL      sub_FF078D9C\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777D8:\n"                            
                 "BL      sub_FF078F90\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777E0:\n"                           
                 "BL      sub_FF0793E0\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777E8:\n"                            
                 "BL      sub_FF079490\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777F0:\n"                           
                 "BL      sub_FF077EE4\n"
                 "B       loc_FF0778F0\n"

 "loc_FF0777F8:\n"                            
                 "BL      sub_FF18C288\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077800:\n"                           
                 "BL      sub_FF18C49C\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077808:\n"                           
                 "BL      sub_FF18C534\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077810:\n"                            
                 "BL      sub_FF18C620\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077818:\n"                           
                 "BL      sub_FF18C6F0\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077820:\n"                            
                 "MOV     R0, #0\n"
                 "B       loc_FF077844\n"

 "loc_FF077828:\n"                           
                 "BL      sub_FF18CB78\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077830:\n"                            
                 "BL      sub_FF18CC10\n"
                 "B       loc_FF0778F0\n"
 

 "loc_FF077838:\n"                           
                 "BL      sub_FF18CCF0\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077840:\n"                           
                 "MOV     R0, #1\n"

 "loc_FF077844:\n"                           
                 "BL      sub_FF18CA10\n"
                 "B       loc_FF0778F0\n"
  

 "loc_FF07784C:\n"                            
                 "BL      sub_FF078410\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077854:\n"                            
                 "BL      sub_FF078450\n"
                 "BL      sub_FF18E6BC\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077860:\n"                            
                 "BL      sub_FF18C874\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077868:\n"                           
                 "BL      sub_FF18C940\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077870:\n"                            
 
                 "BL      sub_FF18E788\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077878:\n"                           
                                        
                 "BL      sub_FF027EA8\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077880:\n"                           
                                       
                 "BL      sub_FF07B8D8\n"
                 "B       loc_FF0778F0\n"
 

 "loc_FF077888:\n"                          
                                      
 
                 "BL      sub_FF07B95C\n"
                 "B       loc_FF0778F0\n"

 "loc_FF077890:\n"                           
                                        
 
                 "BL      sub_FF18CE28\n"
                 "B       loc_FF0778F0\n"
 
 "loc_FF077898:\n"                                                                   
 
                 "BL      sub_FF18CE8C\n"
                 "B       loc_FF0778F0\n"
 
 "loc_FF0778A0:\n"                            
                                         
				
                 "BL      sub_FF07B9B8\n"
                 "BL      sub_FF07B978\n"
                 "B       loc_FF0778F0\n"
 

 "loc_FF0778AC:\n"                           
  
                 "MOV     R0, #1\n"
                 "BL      sub_FF18E1FC\n"
                 "MOV     R0, #1\n"
                 "BL      sub_FF18E330\n"
                 "LDRH    R0, [R5,#0xA0]\n"
                 "CMP     R0, #4\n"
                 "LDRNEH  R0, [R5]\n"
                 "SUBNE   R1, R0, #0x4200\n"
                 "SUBNES  R1, R1, #0x2A\n"
                 "BNE     loc_FF0778F0\n"
                 "BL      sub_FF07B95C\n"
                 "BL      sub_FF07BFA0\n"
                 "BL      sub_FF07BDDC\n"
                 "B       loc_FF0778F0\n"
 
 "loc_FF0778E4:\n"                            
                                 
                 "LDR     R1, =0x5DB\n"
                 "LDR     R0, =0xFF077054\n"
                 "BL      sub_FF00EC88\n"

 "loc_FF0778F0:\n"  
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0,#4]\n"
                 "LDR     R0, [R7]\n"
                 "BL      sub_FF0826C4\n"
                 "LDR     R4, [SP]\n"
                 "LDR     R0, [R4,#8]\n"
                 "CMP     R0, #0\n"
                 "LDREQ   R0, =0xFF077054\n"
                 "MOVEQ   R1, #0x118\n"
                 "BLEQ    sub_FF00EC88\n"
                 "STR     R6, [R4,#8]\n"
                 "B       loc_FF077638\n"


	);
}		

void __attribute__((naked,noinline)) sub_FF18D790_my(){
  
asm volatile(
				 "STMFD   SP!, {R3-R7,LR}\n"
                 "LDR     R5, =0x3EB1C\n"
                 "MOV     R4, R0\n"
                 "LDR     R0, [R5,#0x28]\n"
                 "LDR     R6, =0x420C\n"
                 "CMP     R0, #0\n"
                 "MOV     R7, #0\n"
                 "BNE     loc_FF18D820\n"
                 "LDR     R0, [R5,#0xC4]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF18D808\n"
                 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "LDRNEH  R0, [R5,#0x9E]\n"
                 "CMPNE   R0, #3\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "CMPNE   R0, #1\n"
                 "BLS     loc_FF18D7EC\n"
                 "BL      sub_FF022D5C\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF18D820\n"
                 "BL      sub_FF07D70C\n"
                 "B       loc_FF18D818\n"

 "loc_FF18D7EC:\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF07D6AC\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF18D820\n"
                 "BL      sub_FF18E078\n"
                 "BL      sub_FF07531C\n"
                 "B       loc_FF18D818\n"

 "loc_FF18D808:\n"                            
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF07D6AC\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF18D820\n"

 "loc_FF18D818:\n"                           
                                         
                 "MOV     R0, #1\n"
                 "LDMFD   SP!, {R3-R7,PC}\n"

 "loc_FF18D820:\n"                            
                                         
                 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "LDRNEH  R0, [R5,#0x9E]\n"
                 "CMPNE   R0, #3\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "CMPNE   R0, #1\n"
                 "BLS     loc_FF18D850\n"
                 "LDRH    R0, [R5,#0x9C]\n"
                 "CMP     R0, #0\n"
                 "LDREQH  R0, [R5,#0x98]\n"
                 "CMPEQ   R0, #2\n"
                 "BLEQ    sub_FF07851C\n"

 "loc_FF18D850:\n"                            
                 "LDRH    R1, [R5]\n"
                 "LDRH    R0, [R5,#0x9E]\n"
                 "CMP     R1, R6\n"
                 "BEQ     loc_FF18D890\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF18D8D0\n"
                 "LDR     R0, [R4,#8]\n"
                 "CMP     R0, #1\n"
                 "BLS     loc_FF18D898\n"
                 "LDRH    R0, [R5,#0x9C]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF18D8D0\n"
                 "LDRH    R0, [R5,#0x98]\n"
                 "CMP     R0, #2\n"
                 "BEQ     loc_FF18D8CC\n"
                 "B       loc_FF18D8A4\n"

 "loc_FF18D890:\n"                            
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF18D8D0\n"

 "loc_FF18D898:\n"                            
                 "LDRH    R0, [R5,#0x9C]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF18D8D0\n"

 "loc_FF18D8A4:\n"                            
                 "LDRH    R0, [R5,#0x98]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF18D8D0\n"
                 "CMP     R1, R6\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "CMPNE   R0, #1\n"
                 "BLS     loc_FF18D8D0\n"
                 "LDR     R0, [R4,#0xC]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF18D8D0\n"

 "loc_FF18D8CC:\n"                           
                 "BL      sub_FF18E7C0\n"

 "loc_FF18D8D0:\n"                            
                 "BL      sub_FF18E788\n"
                 "BL      sub_FF077EF4\n"
                 "LDR     R0, [R5,#0x28]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF18D99C\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF18D004\n"
				 "TST     R0, #1\n"
                 "LDMNEFD SP!, {R3-R7,PC}\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF18D468\n"
                 "BL      sub_FF18DFBC\n"
                 "LDR     R0, [R5,#0xC4]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF18D928\n"
				 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "LDRNEH  R0, [R5,#0x9E]\n"
                 "CMPNE   R0, #3\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "CMPNE   R0, #1\n"
                 "BHI     loc_FF18D930\n"

 "loc_FF18D928:\n"                           
                 "MOV     R0, #2\n"
                 "BL      sub_FF07EFE8\n"
     		     "BL      wait_until_remote_button_is_released\n"	// SX220 added
		         "BL      capt_seq_hook_set_nr\n"					// SX220 added

 "loc_FF18D930:\n"                            
				
				"LDRH    R0, [R5]\n"
                 "SUB     R1, R0, #0x4200\n"
                 "SUBS    R1, R1, #0x2D\n"
                 "BNE     loc_FF18D98C\n"
                 "MOV     R5, #1\n"
                 "MOV     R2, #2\n"
                 "MOV     R1, SP\n"
                 "ADD     R0, R2, #0x15C\n"
                 "STR     R5, [SP]\n"
                 "BL      sub_FF08A944\n"     //PT_GetPropertyCaseString
                 "TST     R0, #1\n"
                 "MOVNE   R1, #0xBC\n"
                 "LDRNE   R0, =0xFF18DAB8\n"  //; "SsCaptureSeq.c"
                 "BLNE    sub_FF00EC88\n"     //assert
                 "LDRH    R0, [SP]\n"
                 "CMP     R0, #1\n"
                 "BLS     loc_FF18D984\n"
				 "MOV     R0, R4\n"
                 "STR     R5, [R4,#0xE4]\n"
                 "BL      sub_FF305C60\n"
				 "B       loc_FF18D994\n"

 "loc_FF18D984:\n"                          
                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0xE4]\n"

 "loc_FF18D98C:\n"                           
                 "MOV     R0, R4\n"
                 "BL      sub_FF3058A0\n"

 "loc_FF18D994:\n"                          
 
 			    "MOV     R7, R0\n"
                "B       loc_FF18D9AC\n"

 "loc_FF18D99C:\n"                      
                 "LDR     R0, =0x8978\n"
                 "LDR     R0, [R0]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R7, #0x1D\n"

 "loc_FF18D9AC:\n"
                 "MOV     R0, R7\n"
                 "LDMFD   SP!, {R3-R7,PC}\n"
			);
} 

///////sx220 sub_FF0C3E54
void __attribute__((naked,noinline)) exp_drv_task(){
	asm volatile(
	                 "STMFD   SP!, {R4-R9,LR}\n"
				 "SUB     SP, SP, #0x24\n"
                 "LDR     R6, =0x57B0\n"
                 "LDR     R7, =0xBB8\n"
                 "LDR     R4, =0x5A5B4\n"
                 "MOV     R0, #0\n"
                 "ADD     R5, SP, #0x14\n"
                 "STR     R0, [SP,#0x10]\n"

 "loc_FF0C3E74:\n"                           
                 "LDR     R0, [R6,#0x20]\n"
                 "MOV     R2, #0\n"
                 "ADD     R1, SP, #0x20\n"
                 "BL      sub_FF02AD50\n"
                 "LDR     R0, [SP,#0x10]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF0C3EC0\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R0, [R0]\n"
                 "CMP     R0, #0x14\n"
                 "CMPNE   R0, #0x15\n"
                 "CMPNE   R0, #0x16\n"
                 "CMPNE   R0, #0x17\n"
                 "BEQ     loc_FF0C4020\n"
                 "CMP     R0, #0x29\n"
                 "BEQ     loc_FF0C3FA8\n"
                 "ADD     R1, SP, #0x10\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF0C3E04\n"

 "loc_FF0C3EC0:\n"                            
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x2F\n"
                 "BNE     loc_FF0C3EEC\n"
                 "BL      sub_FF0C5280\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF0826C4\n"
                 "BL      sub_FF00EC40\n"
                 "ADD     SP, SP, #0x24\n"
                 "LDMFD   SP!, {R4-R9,PC}\n"
 

 "loc_FF0C3EEC:\n"                            
                 "CMP     R1, #0x2E\n"
                 "BNE     loc_FF0C3F08\n"
                 "LDR     R2, [R0,#0x8C]!\n"
                 "LDR     R1, [R0,#4]\n"
                 "MOV     R0, R1\n"
                 "BLX     R2\n"
                 "B       loc_FF0C44B0\n"
 

 "loc_FF0C3F08:\n" 
                 "CMP     R1, #0x27\n"
                 "BNE     loc_FF0C3F58\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R1, #0x80\n"
                 "BL      sub_FF0826F8\n"
                 "LDR     R0, =0xFF0BF0D8\n"
                 "MOV     R1, #0x80\n"
                 "BL      sub_FF17E248\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R2, R7\n"
                 "MOV     R1, #0x80\n"
                 "BL      sub_FF082604\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x1756\n"
                 "BNE     loc_FF0C4014\n"

 "loc_FF0C3F44:\n"
                 "LDR     R1, [SP,#0x20]\n"
                 "LDR     R0, [R1,#0x90]\n"
                 "LDR     R1, [R1,#0x8C]\n"
                 "BLX     R1\n"
                 "B       loc_FF0C44B0\n"
 

 "loc_FF0C3F58:\n"                           
                 "CMP     R1, #0x28\n"
                 "BNE     loc_FF0C3FA0\n"
                 "ADD     R1, SP, #0x10\n"
                 "BL      sub_FF0C3E04\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R1, #0x100\n"
                 "BL      sub_FF0826F8\n"
                 "LDR     R0, =0xFF0BF0E8\n"
                 "MOV     R1, #0x100\n"
                 "BL      sub_FF17EB70\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R2, R7\n"
                 "MOV     R1, #0x100\n"
                 "BL      sub_FF082604\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF0C3F44\n"
                 "LDR     R1, =0x1760\n"
                 "B       loc_FF0C4014\n"
 

 "loc_FF0C3FA0:\n"                            
                 "CMP     R1, #0x29\n"
                 "BNE     loc_FF0C3FB8\n"

 "loc_FF0C3FA8:\n"                           
                 "LDR     R0, [SP,#0x20]\n"
                 "ADD     R1, SP, #0x10\n"
                 "BL      sub_FF0C3E04\n"
                 "B       loc_FF0C3F44\n"
 

 "loc_FF0C3FB8:\n"                           
                 "CMP     R1, #0x2C\n"
                 "BNE     loc_FF0C3FD0\n"
                 "BL      sub_FF0B0A18\n"
                 "BL      sub_FF0B1688\n"
                 "BL      sub_FF0B1200\n"
                 "B       loc_FF0C3F44\n"
 

 "loc_FF0C3FD0:\n"
                 "CMP     R1, #0x2D\n"
                 "BNE     loc_FF0C4020\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R1, #4\n"
                 "BL      sub_FF0826F8\n"
                 "LDR     R1, =0xFF0BF108\n"
                 "LDR     R0, =0xFFFFF400\n"
                 "MOV     R2, #4\n"
                 "BL      sub_FF0B048C\n"
                 "BL      sub_FF0B071C\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "MOV     R2, R7\n"
                 "MOV     R1, #4\n"
                 "BL      sub_FF082520\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF0C3F44\n"
                 "LDR     R1, =0x1788\n"

 "loc_FF0C4014:\n"
                 "LDR     R0, =0xFF0BF8A8\n"
                 "BL      sub_FF00EC88\n"
                 "B       loc_FF0C3F44\n"
 

 "loc_FF0C4020:\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "MOV     R8, #1\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x12\n"
                 "CMPNE   R1, #0x13\n"
                 "BNE     loc_FF0C4088\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "ADD     R1, R1, R1,LSL#1\n"
                 "ADD     R1, R0, R1,LSL#2\n"
                 "SUB     R1, R1, #8\n"
                 "LDMIA   R1, {R2,R3,R9}\n"
                 "STMIA   R5, {R2,R3,R9}\n"
                 "BL      sub_FF0C215C\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R3, [R0,#0x8C]\n"
                 "LDR     R2, [R0,#0x90]\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "BL      sub_FF0C5694\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R2, [R0,#0x98]\n"
                 "LDR     R3, [R0,#0x94]\n"
                 "B       loc_FF0C439C\n"
 

 "loc_FF0C4088:\n"                            
                 "CMP     R1, #0x14\n"
                 "CMPNE   R1, #0x15\n"
                 "CMPNE   R1, #0x16\n"
                 "CMPNE   R1, #0x17\n"
                 "BNE     loc_FF0C4140\n"
                 "ADD     R3, SP, #0x10\n"
                 "ADD     R2, SP, #4\n"
                 "ADD     R1, SP, #0x14\n"
                 "BL      sub_FF0C23C4\n"
                 "CMP     R0, #1\n"
                 "MOV     R9, R0\n"
                 "CMPNE   R9, #5\n"
                 "BNE     loc_FF0C40DC\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "MOV     R2, R9\n"
                 "LDR     R1, [R0,#0x7C]!\n"
                 "LDR     R12, [R0,#0x10]!\n"
                 "LDR     R3, [R0,#4]\n"
                 "ADD     R0, SP, #4\n"
                 "BLX     R12\n"
                 "B       loc_FF0C4114\n"
 

 "loc_FF0C40DC:\n"                           
                 "LDR     R0, [SP,#0x20]\n"
                 "CMP     R9, #2\n"
                 "LDR     R3, [R0,#0x90]\n"
                 "CMPNE   R9, #6\n"
                 "BNE     loc_FF0C4128\n"
                 "LDR     R12, [R0,#0x8C]\n"
                 "MOV     R2, R9\n"
                 "MOV     R1, #1\n"
                 "ADD     R0, SP, #4\n"
                 "BLX     R12\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "ADD     R2, SP, #4\n"
                 "ADD     R1, SP, #0x14\n"
                 "BL      sub_FF0C3B50\n"

 "loc_FF0C4114:\n"                            
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R2, [SP,#0x10]\n"
                 "MOV     R1, R9\n"
                 "BL      sub_FF0C3DA4\n"
                 "B       loc_FF0C43A4\n"
 

 "loc_FF0C4128:\n"                            
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R12, [R0,#0x8C]\n"
                 "MOV     R2, R9\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R12\n"
                 "B       loc_FF0C43A4\n"
 

 "loc_FF0C4140:\n"                           
                 "CMP     R1, #0x23\n"
                 "CMPNE   R1, #0x24\n"
                 "BNE     loc_FF0C418C\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "ADD     R1, R1, R1,LSL#1\n"
                 "ADD     R1, R0, R1,LSL#2\n"
                 "SUB     R1, R1, #8\n"
                 "LDMIA   R1, {R2,R3,R9}\n"
                 "STMIA   R5, {R2,R3,R9}\n"
                 "BL      sub_FF0C0F4C\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R3, [R0,#0x8C]\n"
                 "LDR     R2, [R0,#0x90]\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "BL      sub_FF0C1438\n"
                 "B       loc_FF0C43A4\n"
 

 "loc_FF0C418C:\n"                            
                 "ADD     R1, R0, #4\n"
                 "LDMIA   R1, {R2,R3,R9}\n"
                 "STMIA   R5, {R2,R3,R9}\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x27\n"
                 "ADDCC   PC, PC, R1,LSL#2\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C41A8:\n"                            
                 "B       loc_FF0C4244\n"


 "loc_FF0C41AC:\n"                            
                 "B       loc_FF0C4244\n"
 

 "loc_FF0C41B0:\n"                            
                 "B       loc_FF0C424C\n"
 

 "loc_FF0C41B4:\n"                           
                 "B       loc_FF0C4254\n"
 

 "loc_FF0C41B8:\n"                            
                 "B       loc_FF0C4254\n"
 

 "loc_FF0C41BC:\n"                            
                 "B       loc_FF0C4254\n"
 

 "loc_FF0C41C0:\n"                            
                 "B       loc_FF0C4244\n"
 

 "loc_FF0C41C4:\n"                            
                 "B       loc_FF0C424C\n"
 

 "loc_FF0C41C8:\n"                            
                 "B       loc_FF0C4254\n"
 

 "loc_FF0C41CC:\n"                           
                 "B       loc_FF0C4254\n"
 

 "loc_FF0C41D0:\n"                           
                 "B       loc_FF0C426C\n"
 

 "loc_FF0C41D4:\n"                           
                 "B       loc_FF0C426C\n"
 

 "loc_FF0C41D8:\n"                           
                 "B       loc_FF0C4378\n"
 

 "loc_FF0C41DC:\n"
                 "B       loc_FF0C4380\n"
 

 "loc_FF0C41E0:\n"
                 "B       loc_FF0C4380\n"
 

 "loc_FF0C41E4:\n"
                 "B       loc_FF0C4380\n"
 

 "loc_FF0C41E8:\n"
                 "B       loc_FF0C4380\n"
 

 "loc_FF0C41EC:\n"
                 "B       loc_FF0C4388\n"
 

 "loc_FF0C41F0:\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C41F4:\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C41F8:\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C41FC:\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C4200:\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C4204:\n"
                 "B       loc_FF0C438C\n"
 

 "loc_FF0C4208:\n"
                 "B       loc_FF0C425C\n"
 

 "loc_FF0C420C:\n"
                 "B       loc_FF0C4264\n"
 

 "loc_FF0C4210:\n"
                 "B       loc_FF0C4264\n"
 

 "loc_FF0C4214:\n"
                 "B       loc_FF0C4278\n"
 

 "loc_FF0C4218:\n"
                 "B       loc_FF0C4278\n"
 

 "loc_FF0C421C :\n"
                 "B       loc_FF0C4280\n"
 

 "loc_FF0C4220:\n"
                 "B       loc_FF0C42B8\n"

 "loc_FF0C4224:\n"
                 "B       loc_FF0C42F0\n"

 "loc_FF0C4228:\n"
                 "B       loc_FF0C4328\n"

 "loc_FF0C422C:\n"
                 "B       loc_FF0C4360\n"

 "loc_FF0C4230:\n"
                 "B       loc_FF0C4360\n"

 "loc_FF0C4234:\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4238:\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C423C:\n"
                 "B       loc_FF0C4368\n"

 "loc_FF0C4240 :\n"
                 "B       loc_FF0C4370\n"

 "loc_FF0C4244:\n"
                 "BL      sub_FF0BF6D4\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C424C:\n"
                 "BL      sub_FF0BF9D4\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4254:\n"
                 "BL      sub_FF0BFC3C\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C425C:\n"
                 "BL      sub_FF0BFEF0\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4264:\n"
                 "BL      sub_FF0C0108\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C426C:\n"
                 "BL      sub_FF0C05C4_my\n"   //SX220 patched
                 "MOV     R8, #0\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4278:\n"
                 "BL      sub_FF0C07A8\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4280:\n"
                 "LDRH    R1, [R0,#4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R4,#2]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R4,#4]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "LDRH    R1, [R4,#6]\n"
                 "STRH    R1, [SP,#0x1A]\n"
                 "LDRH    R1, [R0,#0xC]\n"
                 "STRH    R1, [SP,#0x1C]\n"
                 "LDRH    R1, [R4,#0xA]\n"
                 "STRH    R1, [SP,#0x1E]\n"
                 "BL      sub_FF0C5314\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C42B8:\n"
                 "LDRH    R1, [R0,#4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R4,#2]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R4,#4]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "LDRH    R1, [R4,#6]\n"
                 "STRH    R1, [SP,#0x1A]\n"
                 "LDRH    R1, [R4,#8]\n"
                 "STRH    R1, [SP,#0x1C]\n"
                 "LDRH    R1, [R4,#0xA]\n"
                 "STRH    R1, [SP,#0x1E]\n"
                 "BL      sub_FF0C5494\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C42F0:\n"
                 "LDRH    R1, [R4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R0,#6]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R4,#4]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "LDRH    R1, [R4,#6]\n"
                 "STRH    R1, [SP,#0x1A]\n"
                 "LDRH    R1, [R4,#8]\n"
                 "STRH    R1, [SP,#0x1C]\n"
                 "LDRH    R1, [R4,#0xA]\n"
                 "STRH    R1, [SP,#0x1E]\n"
                 "BL      sub_FF0C5548\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4328:\n"
                 "LDRH    R1, [R4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R4,#2]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R4,#4]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "LDRH    R1, [R4,#6]\n"
                 "STRH    R1, [SP,#0x1A]\n"
                 "LDRH    R1, [R0,#0xC]\n"
                 "STRH    R1, [SP,#0x1C]\n"
                 "LDRH    R1, [R4,#0xA]\n"
                 "STRH    R1, [SP,#0x1E]\n"
                 "BL      sub_FF0C55F0\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4360:\n"
                 "BL      sub_FF0C0D24\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4368:\n"
                 "BL      sub_FF0C153C\n"
                 "B       loc_FF0C438C\n"


 "loc_FF0C4370:\n"
                 "BL      sub_FF0C1A48\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4378:\n"
                 "BL      sub_FF0C1C28\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4380:\n"
                 "BL      sub_FF0C1DE4\n"
                 "B       loc_FF0C438C\n"

 "loc_FF0C4388:\n"
                 "BL      sub_FF0C1F54\n"

 "loc_FF0C438C:\n"
                 "LDR     R0, [SP,#0x20]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R2, [R0,#0x90]\n"
                 "LDR     R3, [R0,#0x8C]\n"

 "loc_FF0C439C:\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"

 "loc_FF0C43A4:\n"
                 "LDR     R1, [SP,#0x20]\n"
                 "LDR     R0, [R1]\n"
                 "CMP     R0, #0x10\n"
                 "BEQ     loc_FF0C43DC\n"
                 "BGT     loc_FF0C43CC\n"
                 "CMP     R0, #1\n"
                 "CMPNE   R0, #4\n"
                 "CMPNE   R0, #0xE\n"
                 "BNE     loc_FF0C43EC\n"
                 "B       loc_FF0C43DC\n"

 "loc_FF0C43CC:\n"
                 "CMP     R0, #0x13\n"
                 "CMPNE   R0, #0x17\n"
                 "CMPNE   R0, #0x1A\n"
                 "BNE     loc_FF0C43EC\n"

 "loc_FF0C43DC:\n"
                 "LDRH    R0, [R4]\n"
                 "STRH    R0, [SP,#0x14]\n"
                 "LDRH    R0, [R4,#8]\n"
                 "STRH    R0, [SP,#0x1C]\n"

 "loc_FF0C43EC:\n"
                 "CMP     R8, #1\n"
                 "BNE     loc_FF0C4438\n"
                 "LDR     R0, [R1,#0x7C]\n"
                 "MOV     R2, #0xC\n"
                 "ADD     R0, R0, R0,LSL#1\n"
                 "ADD     R0, R1, R0,LSL#2\n"
                 "SUB     R8, R0, #8\n"
                 "LDR     R0, =0x5A5B4\n"
                 "ADD     R1, SP, #0x14\n"
                 "BL      sub_FF3AB5DC\n"
                 "LDR     R0, =0x5A5C0\n"
                 "MOV     R2, #0xC\n"
                 "ADD     R1, SP, #0x14\n"
                 "BL      sub_FF3AB5DC\n"
                 "LDR     R0, =0x5A5CC\n"
                 "MOV     R2, #0xC\n"
                 "MOV     R1, R8\n"
                 "BL      sub_FF3AB5DC\n"
                 "B       loc_FF0C44B0\n"

 "loc_FF0C4438:\n"
                 "LDR     R0, [R1]\n"
                 "MOV     R3, #1\n"
                 "CMP     R0, #0xB\n"
                 "BNE     loc_FF0C447C\n"
                 "MOV     R2, #0\n"
                 "STRD    R2, [SP]\n"
                 "MOV     R2, R3\n"
                 "MOV     R1, R3\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF0BF4A8\n"
                 "MOV     R3, #1\n"
                 "MOV     R2, #0\n"
                 "STRD    R2, [SP]\n"
                 "MOV     R2, R3\n"
                 "MOV     R1, R3\n"
                 "MOV     R0, #0\n"
                 "B       loc_FF0C44AC\n"

 "loc_FF0C447C:\n"
                 "MOV     R2, #1\n"
                 "STRD    R2, [SP]\n"
                 "MOV     R3, R2\n"
                 "MOV     R1, R2\n"
                 "MOV     R0, R2\n"
                 "BL      sub_FF0BF4A8\n"
                 "MOV     R3, #1\n"
                 "MOV     R2, R3\n"
                 "MOV     R1, R3\n"
                 "MOV     R0, R3\n"
                 "STR     R3, [SP]\n"
                 "STR     R3, [SP,#4]\n"

 "loc_FF0C44AC:\n"
                 "BL      sub_FF0BF620\n"

 "loc_FF0C44B0:\n"
				 "LDR     R0, [SP,#0x20]\n"
                 "BL      sub_FF0C5280\n"
                 "B       loc_FF0C3E74\n"

	
	
	);


}


//SX220 sub_FF0C05C4_my
void __attribute__((naked,noinline)) sub_FF0C05C4_my(){
 
	asm volatile(
	
	             "STMFD   SP!, {R4-R8,LR}\n"
                 "LDR     R7, =0x57B0\n"
                 "MOV     R4, R0\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R1, #0x3E\n"
                 "BL      sub_FF0826F8\n"
                 "MOV     R2, #0\n"
                 "LDRSH   R0, [R4,#4]\n"
                 "MOV     R1, R2\n"
                 "BL      sub_FF0BF168\n"
                 "MOV     R5, R0\n"
                 "LDRSH   R0, [R4,#6]\n"
                 "BL      sub_FF0BF2B8\n"
                 "LDRSH   R0, [R4,#8]\n"
                 "BL      sub_FF0BF310\n"
                 "LDRSH   R0, [R4,#0xA]\n"
                 "BL      sub_FF0BF368\n"
                 "LDRSH   R0, [R4,#0xC]\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF0BF3C0\n"
                 "MOV     R6, R0\n"
                 "LDRSH   R0, [R4,#0xE]\n"
                 "BL      sub_FF0C52B0\n"
                 "LDR     R0, [R4]\n"
                 "LDR     R8, =0x5A5CC\n"
                 "CMP     R0, #0xB\n"
                 "MOVEQ   R5, #0\n"
                 "MOVEQ   R6, R5\n"
                 "BEQ     loc_FF0C0660\n"
                 "CMP     R5, #1\n"
                 "BNE     loc_FF0C0660\n"
                 "LDRSH   R0, [R4,#4]\n"
                 "LDR     R1, =0xFF0BF0C8\n"
                 "MOV     R2, #2\n"
                 "BL      sub_FF17E520\n"
                 "STRH    R0, [R4,#4]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R7,#0x28]\n"
                 "B       loc_FF0C0668\n"

 "loc_FF0C0660:\n"
                 "LDRH    R0, [R8]\n"
                 "STRH    R0, [R4,#4]\n"

 "loc_FF0C0668:\n"
                 "CMP     R6, #1\n"
                 "LDRNEH  R0, [R8,#8]\n"
                 "BNE     loc_FF0C0684\n"
                 "LDRSH   R0, [R4,#0xC]\n"
                 "LDR     R1, =0xFF0BF14C\n"
                 "MOV     R2, #0x20\n"
                 "BL      sub_FF0C52D0\n"

 "loc_FF0C0684:\n"
                 "STRH    R0, [R4,#0xC]\n"
                 "LDRSH   R0, [R4,#6]\n"
                 "BL      sub_FF0B0788_my\n"     //sx220 patched
                 "LDRSH   R0, [R4,#8]\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF0B0F40\n"
                 "MOV     R1, #0\n"
                 "ADD     R0, R4, #8\n"
                 "BL      sub_FF0B0FC8\n"
                 "LDRSH   R0, [R4,#0xE]\n"
                 "BL      sub_FF0B9F58\n"
                 "LDR     R4, =0xBB8\n"
                 "CMP     R5, #1\n"
                 "BNE     loc_FF0C06DC\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #2\n"
                 "BL      sub_FF082604\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x7E3\n"
                 "LDRNE   R0, =0xFF0BF8A8\n"
                 "BLNE    sub_FF00EC88\n"

 "loc_FF0C06DC:\n"
                 "CMP     R6, #1\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #0x20\n"
                 "BL      sub_FF082604\n"
                 "TST     R0, #1\n"
                 "LDMEQFD SP!, {R4-R8,PC}\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "LDR     R1, =0x7E8\n"
                 "LDR     R0, =0xFF0BF8A8\n"
                 "B       sub_FF00EC88\n"


	
	);
}	

//SX220 sub_FF0B0788_my
void __attribute__((naked,noinline)) sub_FF0B0788_my(){
 
	asm volatile(
	
	             "STMFD   SP!, {R4-R6,LR}\n"
                 "LDR     R5, =0x5458\n"
                 "MOV     R4, R0\n"
                 "LDR     R0, [R5,#4]\n"
                 "CMP     R0, #1\n"
                 "LDRNE   R1, =0x146\n"
                 "LDRNE   R0, =0xFF0B05C0\n"  //aShutter_c
                 "BLNE    sub_FF00EC88\n"    //ASSERT
                 "CMN     R4, #0xC00\n"
                 "LDREQSH R4, [R5,#2]\n"
                 "CMN     R4, #0xC00\n"
                 "MOVEQ   R1, #0x14C\n"
                 "LDREQ   R0, =0xFF0B05C0\n"   //aShutter_c
                 "STRH    R4, [R5,#2]\n"
                 "BLEQ    sub_FF00EC88\n"   //ASSERT
                 "MOV     R0, R4\n"
                 "BL      apex2us\n"   //SX220 patched
                 "MOV     R4, R0\n"
                 "BL      sub_FF104D38\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF112D6C\n"
                 "TST     R0, #1\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "LDMFD   SP!, {R4-R6,LR}\n"
                 "LDR     R1, =0x151\n"
                 "LDR     R0, =0xFF0B05C0\n"   //aShutter_c
                 "B       sub_FF00EC88\n"  //ASSERT
	
	);
 }
