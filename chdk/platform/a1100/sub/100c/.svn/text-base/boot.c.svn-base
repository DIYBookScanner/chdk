#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_PhySw();

void taskHook(context_t **context) { 
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_PhySw)				tcb->entry = (void*)mykbd_task;
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	//if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	//if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
} 

void CreateTask_spytask() {

        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


void __attribute__((naked,noinline)) boot() {

    asm volatile (
                 "LDR     R1, =0xC0410000\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R1]\n"
                 "MOV     R1, #0x78\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "MOV     R1, #0\n"
                 "MCR     p15, 0, R1,c7,c10, 4\n"
" loc_FFC00028:\n"                                                    
                 "MCR     p15, 0, R1,c7,c5\n"
                 "MCR     p15, 0, R1,c7,c6\n"
                 "MOV     R0, #0x3D\n"
                 "MCR     p15, 0, R0,c6,c0\n"
                 "MOV     R0, #0xC000002F\n"
                 "MCR     p15, 0, R0,c6,c1\n"
                 "MOV     R0, #0x33\n"
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000033\n"
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFFC0002B\n"
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
                 "LDR     R0, =0xFFED53A0\n"
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0xB1B0\n"
 "loc_FFC0013C:\n"                          
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC0013C\n"
                 "LDR     R1, =0x12ED1C\n"
                 "MOV     R2, #0\n"
 "loc_FFC00154:\n"                           
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FFC00154\n"
               //  "B       loc_FFC001A0\n"
							"B	  sub_FFC001A0_my\n"
    );
};


void __attribute__((naked,noinline)) sub_FFC001A0_my() {

     //*(int*)0x1930=(int)taskHook;
     *(int*)0x1934=(int)taskHook;
     *(int*)0x1938=(int)taskHook;
	 
     *(int*)(0x2234)= (*(int*)0xC0220134)&1 ?0x200000 : 0x100000; // replacement of sub_FFC3040C for correct power-on.

      
   asm volatile (
                "LDR     R0, =0xFFC00218\n"
                 "MOV     R1, #0   \n"
                 "LDR     R3, =0xFFC00250\n"
 "loc_FFC001AC:\n"                           
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC001AC\n"
                 "LDR     R0, =0xFFC00250\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFFC00464\n"
 "loc_FFC001C8:\n"                        
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC001C8\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
 "loc_FFC001FC:\n"                        
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FFC001FC\n"
               //  "BL      sub_FFC00FC4\n"
                 "BL      sub_FFC00FC4_my\n" //-------->
     );
}
//----------------------------------------------------------------------------------------------------------------------------------to doing
void __attribute__((naked,noinline)) sub_FFC00FC4_my() {

     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"               
                "BL      sub_FFE6C5B0\n"       
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
             //    "LDR     R0, =0x12ED1C\n"
              // Replacement
 		           "LDR     R0, =new_sa\n"
   	              "LDR     R0, [R0]\n"
   	              
                 "LDR     R2, =0x2F9C00\n"
                 "LDR     R1, =0x2F24A8\n"
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
             //    "LDR     R1, =sub_FFC04D38\n"
                  "LDR     R1, =sub_FFC04D38_my\n"  //--------->
				 
				 "B       sub_FFC01018 \n"	// continue in firmware
     );
}

//需要修改
void __attribute__((naked,noinline)) sub_FFC04D38_my() {

        asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FFC00954\n"
                 "BL      sub_FFC090B4\n"
                 "CMP     R0, #0\n"
              //   "ADRLT   R0, sub_FFC04E4C\n"  //  ; "dmSetup"\n"
                 	"LDRLT     R0,=0xFFC04E4C\n"
                 "BLLT    sub_FFC04E2C\n"
                 "BL      sub_FFC04974\n"
                 "CMP     R0, #0\n"
             //    "ADRLT   R0, sub_FFC04E54\n"// ; "termDriverInit"\n"
                  	"LDRLT     R0,=0xFFC04E54\n"
                 "BLLT    sub_FFC04E2\n"
                // "ADR     R0, sub_FFC04E64\n"      //; "/_term"
                 "LDR     R0,=0xFFC04E64\n"
                 "BL      sub_FFC04A5C\n"
                 "CMP     R0, #0\n"
               //  "ADRLT   R0, sub_FFC04E6C \n"//; "termDeviceCreate"
                 "LDRLT     R0,=0xFFC04E6C\n"
                 "BLLT    sub_FFC04E2C\n"
              //   "ADR     R0, sub_FFC04E64 \n"    // ; "/_term"
                  "LDR     R0,=0xFFC04E64 \n"
                 "BL      sub_FFC03578\n"
                 "CMP     R0, #0\n"
               //  "ADRLT   R0, sub_FFC04E80\n" //; "stdioSetup"
                  "LDRLT     R0,=0xFFC04E80\n"
                 "BLLT    sub_FFC04E2C\n"
                 "BL      sub_FFC08BCC\n"
                 "CMP     R0, #0\n"
             //    "ADRLT   R0, sub_FFC04E8C\n" //; "stdlibSetup"
                   "LDRLT     R0,=0xFFC04E8C\n"
                 "BLLT    sub_FFC04E2C\n"
                 "BL      sub_FFC014A8\n"
                 "CMP     R0, #0\n"
              //   "ADRLT   R0, sub_FFC04E98\n" //; "armlib_setup"
                   "LDRLT     R0,=0xFFC04E98\n"
                 "BLLT    sub_FFC04E2C\n"
                 "LDMFD   SP!, {R4,LR}\n"
            //     "B       taskcreate_Startup\n"
                  "B       taskcreate_Startup_my\n" //-------->

        );
};

void __attribute__((naked,noinline)) taskcreate_Startup_my() {

     asm volatile (   
                "STMFD   SP!, {R3,LR}\n"
             //   "BL      j_nullsub_178\n"
                "BL      sub_FFC18680\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC0C29C\n"
                "BL      sub_FFC117B0\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC0C29C\n"
                "BL      sub_FFC10E84\n"
                "LDR     R1, =0xC0220000\n"
                "MOV     R0, #0x44\n"
                "STR     R0, [R1,#0x84]\n"
                "STR     R0, [R1,#0x80]\n"
                "BL      sub_FFC11074\n"
"loc_FFC0C298:\n"                          
                "B       loc_FFC0C298\n"
"loc_FFC0C29C:\n"                                             
             //   "BL      sub_FFC117BC\n"    // removed for correct power-on on 'on/off' button.
             //   "BL      j_nullsub_179\n"
                "BL      sub_FFC1693C\n"
                "LDR     R1, =0x34E000\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC16D84\n"
                "BL      sub_FFC16B30\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
              //  "ADR     R3, task_Startup\n"
                "LDR     R3, =task_Startup_my\n"  //-------->
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
            //    "ADR     R0, aStartup\n"    ; "Startup"
            		"LDR     R0,=0xFFC0C2E4\n"
                "BL      sub_FFC0AFAC\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
     );
}

void __attribute__((naked,noinline)) task_Startup_my() {
		
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FFC05394\n"
                 "BL      sub_FFC128A0\n"
                 "BL      sub_FFC10B28\n"
               //  "BL      j_nullsub_182\n"
                 "BL      sub_FFC188A4\n"
              //   "BL      sub_FFC18754\n"   // //start diskboot.bin, //StartDiskboot --> removed
                 "BL      sub_FFC18A40\n"
                 "BL      sub_FFC0FB94\n"
                 "BL      sub_FFC188D4\n"
                 "BL      sub_FFC15F3C\n"
                 "BL      sub_FFC18A44\n"
                  "BL 	CreateTask_spytask\n"    // <--- function added
                 "BL      sub_FFC116B0\n"     //taskcreate_PhySw
                 "BL      sub_FFC146BC\n"
                 "BL      sub_FFC18A5C\n"
              //   "BL      nullsub_2\n"
                 "BL      sub_FFC104B0\n"
                 "BL      sub_FFC18464\n"
                 "BL      sub_FFC10AD8\n"
                 "BL      sub_FFC103D4\n"
                 "BL      sub_FFC0FBC8\n"
                 "BL      sub_FFC194A4\n"
                 "BL      sub_FFC103AC\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FFC054B4\n"
     );
}

/*******************************************************************/

void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FFC59C9C\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FFC5C35C\n"
                 "BL      sub_FFC59CC8_my\n"             //------------->
             //   "BL      sub_FFC59CC8\n"
             "BL      core_spytask_can_start\n"      // + set "it's safe to start" flag for spytask
                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FFC5C35C\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC59CC8_my() {

 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "MOV     R0, #3\n"
                 //"BL      sub_FFC3E9BC\n"
                 "BL      sub_FFC3E9BC_my\n"    //---------->
               //  "BL      nullsub_64\n"
                 "LDR     R4, =0x2B70\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC59D00\n"
                 "BL      sub_FFC3DD80\n"
                 "BL      sub_FFCCF594\n"
                 "BL      sub_FFC3DD80\n"
                 "BL      sub_FFC3A1E4\n"
                 "BL      sub_FFC3DC80\n"
                 "BL      sub_FFCCF658\n"
 "loc_FFC59D00:\n"                           // ; CODE XREF: sub_FFC59CC8+1C
                 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"

 );
}


void __attribute__((naked,noinline)) sub_FFC3E9BC_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R6, R0\n"
                 "BL      sub_FFC3E924\n"
                 "LDR     R1, =0xE5D8\n"
                 "MOV     R5, R0\n"
                 "ADD     R4, R1, R0,LSL#7\n"
                 "LDR     R0, [R4,#0x70]\n"
                 "CMP     R0, #4\n"
                 "LDREQ   R1, =0x6D8\n"
               //  "ADREQ   R0, aMounter_c\n"//  ; "Mounter.c"
                 "LDREQ   R0,=0xFFC3E448\n"
                 "BLEQ    sub_FFC0B284\n"
                 "MOV     R1, R6\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC3E390\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "BL      sub_FFC3EEE8\n"
                 "CMP     R0, #0\n"
                 "STREQ   R0, [R4,#0x70]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC3E468\n"
                 "MOV     R0, R5\n"
               //  "BL      sub_FFC3E75C\n"
                "BL      sub_FFC3E75C_my\n"  //--------->
				
				 "B       sub_FFC3EA14 \n"	// continue in firmware
 );
}

void __attribute__((naked,noinline)) sub_FFC3E75C_my() {
 asm volatile(
                   "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R5, R0\n"
                 "LDR     R0, =0xE5D8\n"
                 "ADD     R4, R0, R5,LSL#7\n"
                 "LDR     R0, [R4,#0x70]\n"
                 "TST     R0, #2\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R5\n"
                // "BL      sub_FFC3E4EC\n"
                   "BL      sub_FFC3E4EC_my\n"  //--------->
				   
				 "B       sub_FFC3E788 \n"	// Continue in firmware
 );
}

void __attribute__((naked,noinline)) sub_FFC3E4EC_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"
                 "LDR     R0, =0xE5D8\n"
                 "MOV     R7, #0\n"
                 "ADD     R5, R0, R1,LSL#7\n"
                 "LDR     R0, [R5,#0x3C]\n"
                 "MOV     R6, #0\n"
                 "CMP     R0, #7\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FFC3E63C\n"
 "loc_FFC3E514:\n"                            
                 "B       loc_FFC3E54C\n"
 "loc_FFC3E518:\n"                            
                 "B       loc_FFC3E534\n"
 "loc_FFC3E51C:\n"                            
                 "B       loc_FFC3E534\n"
 "loc_FFC3E520:\n"     
					 "B       loc_FFC3E534\n"                       
 "loc_FFC3E524:\n"                            
                 "B       loc_FFC3E534\n"
 "loc_FFC3E528:\n"                            
                 "B       loc_FFC3E634\n"
 "loc_FFC3E52C:\n"                            
                 "B       loc_FFC3E534\n"
 "loc_FFC3E530:\n"                            
                "B       loc_FFC3E534\n"
 "loc_FFC3E534:\n"                                                                   
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC53D0C\n"
                 "MOVS    R4, R0\n"
                 "BNE     loc_FFC3E554\n"
 "loc_FFC3E54C:\n"                            
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FFC3E554:\n"                            
                 "LDR     R12, [R5,#0x4C]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FFC3E580\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC53E58\n"
                 "B       loc_FFC3E54C\n"
 "loc_FFC3E580:\n"                          
                 "LDR     R1, [R5,#0x68]\n"
                 "MOV     R0, R8\n"
                 "BLX     R1\n"
                 
          "MOV   R1, R4\n"           // + pointer to MBR in R1
		  "BL    mbr_read_dryos\n"   // + total sectors count in R0 before and after call                                             需要修改

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
             //    "LDRB    LR, [R4,#0x1FF]\n"
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
              //   "LDRB    R12, [R4,#0x1FE]\n"
               "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
                 "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.
                 "MOV     R4, #0\n"
                 "BNE     loc_FFC3E60C\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FFC3E60C\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R7, R1\n"
                 "MOVEQ   R6, R3\n"
                 "MOVEQ   R4, #1\n"
 "loc_FFC3E60C:\n"                          
                 "MOV     R0, #2\n"
                 "BL      sub_FFC53E58\n"
                 "CMP     R4, #0\n"
                 "BNE     loc_FFC3E648\n"
                 "LDR     R1, [R5,#0x68]\n"
                 "MOV     R7, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R1\n"
                 "MOV     R6, R0\n"
                 "B       loc_FFC3E648\n"
 "loc_FFC3E634:\n"                                                            
                 "MOV     R6, #0x40\n"
                 "B       loc_FFC3E648\n"
 "loc_FFC3E63C:\n"                                                                
                 "LDR     R1, =0x5C9\n"
                // "ADR     R0, aMounter_c\n"  ; "Mounter.c"
                "LDR    R0,=0xFFC3E448\n"
                 "BL      sub_FFC0B284\n"
 "loc_FFC3E648:\n"                                                            
                 "STR     R7, [R5,#0x44]!\n"
                 "MOV     R0, #1\n"
                 "STR     R6, [R5,#4]\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}



