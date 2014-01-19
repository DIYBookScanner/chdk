// A2100IS 1.00A
/*
###########################################################
###########################################################
#############[ NO SD CARD CODE INSERTED!!!! ]##############
#############[ Movie function still commented ]############
###########################################################
###########################################################
*/
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"
#include "gui.h"
#include "../../../../core/gui_draw.h"

// Firmware difference now set to FFEEA000 - mostly free area

const char * const new_sa = &_end;

#define LED_PWR 0xC0220014      // A2100IS Green - power led 
#define LED_DP 0xC0220018		// A2100IS Blue - Direct Print led 
#define LED_AF 0xC022000C		// A2100IS Red - AutoFocus led 
#define DELAY 5000000

// volatile long *p1 = (void*)LED_PWR;
// volatile long *p2 = (void*)LED_DP;
// int counter;	
// // DEBUG: blink led
// counter = DELAY; *p1 = 0x46;*p2 = 0x46;  while (counter--) { asm("nop\n nop\n"); };
// counter = DELAY; *p1 = 0x44;*p2 = 0x44;  while (counter--) { asm("nop\n nop\n"); }; 

// while(1){
// asm volatile ("LDR R5, =0xC0220018\n MOV R6, #0x46\n STR R6,[R5]\n");
// counter = 2000000; while (counter--) { asm("nop\n nop\n"); };
// asm volatile ("LDR R5, =0xC0220018\n MOV R6, #0x44\n STR R6,[R5]\n");
// counter = 2000000; while (counter--) { asm("nop\n nop\n"); };
// msleep(10);
// }


// debug:
// volatile asm(
// "LDR R10, =0xC0220018\n"
// "MOV R11, 0x46\n"
// "STR R10,R11\n"
// );

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();


void __attribute__((naked,noinline)) task_blinker() {

int pwr_led_count = 0 ;
int blue_led_count = 0 ;
int gui_mode, gui_mode_flag = GUI_MODE_NONE ;

volatile long *pwr_LED = (void*)LED_PWR; 
volatile long *blue_LED = (void*)LED_DP; 

		_SleepTask(2000);

		while(1){
		
			gui_mode = gui_get_mode() ;
			
			if(( (gui_mode == GUI_MODE_ALT)  && (gui_mode_flag != GUI_MODE_ALT) ) || ( (gui_mode == GUI_MODE_NONE)  && (gui_mode_flag != GUI_MODE_NONE) ) )
			{
				gui_mode_flag = gui_mode ;
				blue_led_count = 10 ;
				*blue_LED = 0x46;				
			}			
			if ( blue_led_count > 0 )
			{
				if ( --blue_led_count == 0 )
				{
					*blue_LED = 0x44;
				}
			}
			
			if ( pwr_led_count == 2 )
			{
				*pwr_LED = 0x44;				
			}
			if ( --pwr_led_count <= 0 )
			{
				pwr_led_count = 20 ;
				*pwr_LED = 0x46;				
			}
			
			_SleepTask(100);
		}
};

void CreateTask_Blinker() {

        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};

// taskCreateHook - semi adapted
void taskCreateHook(int *p) { 
	p-=17;
	
	if (p[0]==0xffc6036c)  p[0]=(int)init_file_modules_task; //
// 	if (p[0]==0xffcf8660)  p[0]=(int)movie_record_task;	
	if (p[0]==0xffc48f48)  p[0]=(int)capt_seq_task;
	if (p[0]==0xffc7ddf0)  p[0]=(int)exp_drv_task; //ROM:FFC7DDF0 ; LOCATION: ExpDrv.c:3536
}

// taskCreateHook2 - adapted
void taskCreateHook2(int *p) { 
	p-=17;
	if (p[0]==0xffc6036c)  p[0]=(int)init_file_modules_task;
	if (p[0]==0xffc48f48)  p[0]=(int)capt_seq_task;
	if (p[0]==0xffc7ddf0)  p[0]=(int)exp_drv_task; 
} 

// boot() adapted - copied from FW and changed last B
void __attribute__((naked,noinline)) boot(  ) { 
volatile long *p1 = (void*)LED_PWR;
volatile long *p2 = (void*)LED_DP;
int counter;	
// // DEBUG: blink led
// counter = 2000000; *p1 = 0x46;*p2 = 0x46;  while (counter--) { asm("nop\n nop\n"); };
// counter = 2000000; *p1 = 0x44;*p2 = 0x44;  while (counter--) { asm("nop\n nop\n"); };
// msleep(200);
// counter = 2000000; *p1 = 0x46;*p2 = 0x46;  while (counter--) { asm("nop\n nop\n"); };
// counter = 2000000; *p1 = 0x44;*p2 = 0x44;  while (counter--) { asm("nop\n nop\n"); }; 

asm volatile (
	"LDR     R1, =0xC0410000\n"
	"MOV     R0, #0\n"
	"STR     R0, [R1]\n"
	"MOV     R1, #0x78\n"
	"MCR     p15, 0, R1,c1,c0\n"
	"MOV     R1, #0\n"
	"MCR     p15, 0, R1,c7,c10, 4\n"
"loc_FFC00028:\n" //                            ; DATA XREF: ROM:off_FFFF06CCo\n"
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
	"LDR     R0, =0xFFED7374\n" // Firmware Difference, link to empty part or ROM
	"LDR     R1, =0x1900\n"		// MEMBASE\n"
	"LDR     R3, =0xB1F8\n"

"loc_FFC0013C:\n" //                            ; CODE XREF: ROM:FFC00148j\n"
	"CMP     R1, R3\n"
	"LDRCC   R2, [R0],#4\n"
	"STRCC   R2, [R1],#4\n"
	"BCC     loc_FFC0013C\n"
	"LDR     R1, =0x12EDB4\n"	//MEMISOSTART Addr\n"
	"MOV     R2, #0\n"

"loc_FFC00154:\n" //                            ; CODE XREF: ROM:FFC0015Cj\n"
	"CMP     R3, R1\n"
	"STRCC   R2, [R3],#4\n"
	"BCC     loc_FFC00154\n"
	"B       sub_FFC001A0_my\n"

                   
	);
	
	
}

//sub_FFC001A0_my - adapted - passed (before asm)
void __attribute__((naked,noinline)) sub_FFC001A0_my(  ) { 

    *(int*)0x1930=(int)taskCreateHook; 
    *(int*)0x1934=(int)taskCreateHook2; 
    *(int*)0x1938=(int)taskCreateHook; 		

// ROM: FFC30468                 LDR     R0, =0xC0220118 	
// Power ON/OFF detection  G10 @FF84A8D0   replacement  for correct power-on.
//ROM: FFC30448                 LDR     R4, =0x2230
*(int*)(0x2230+0x04)= (*(int*)0xC0220118)&1 ? 0x100000 : 0x200000; // replacement  for correct power-on.

asm volatile (
"loc_FFC001A0:\n" //                            ; CODE XREF: ROM:FFC00160j\n"
	"LDR     R0, =0xFFC00218\n"
	"MOV     R1, #0\n"
	"LDR     R3, =0xFFC00250\n"
"loc_FFC001AC:\n" //                            ; CODE XREF: ROM:FFC001B8j\n"
	"CMP     R0, R3\n"
	"LDRCC   R2, [R0],#4\n"
	"STRCC   R2, [R1],#4\n"
	"BCC     loc_FFC001AC\n"
	"LDR     R0, =0xFFC00250\n"
	"MOV     R1, #0x4B0\n"
	"LDR     R3, =0xFFC00464\n"
"loc_FFC001C8:\n" //                            ; CODE XREF: ROM:FFC001D4j\n"
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
//	"LDR     R0, =loc_FFC0020C\n" //for some reason - can't compile with "undefined reference to `loc_FFC0020C'"
	"LDR     R0, =0xFFC0020C\n"
	"LDR     R2, =0xEEEEEEEE\n"
	"MOV     R3, #0x1000\n"
"loc_FFC001FC:\n" //                            ; CODE XREF: ROM:FFC00204j\n"
	"CMP     R0, R3\n"
	"STRCC   R2, [R0],#4\n"
	"BCC     loc_FFC001FC\n"
	"BL      sub_FFC00FC4_my\n"
  //----------->                    
	);
}


//** sub_FFC00FC4_my  @ 0xFFC00FC4 
//sub_FFC00FC4_my - adapted - not passing completely
void __attribute__((naked,noinline)) sub_FFC00FC4_my(  ) { 
asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"SUB     SP, SP, #0x74\n"
	"MOV     R0, SP\n"
	"MOV     R1, #0x74\n"
	"BL      sub_FFE6D060\n"
	"MOV     R0, #0x53000\n"
	"STR     R0, [SP,#4]\n"
	//"LDR     R0, =0x12EDB4\n"   		// -
"	LDR     R0, =new_sa\n"      // +
"	LDR     R0, [R0]\n"         // +
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
	"LDR     R1, =sub_FFC04D38_my\n" //+ ---------->
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
	"BL      sub_FFC02D68\n"
	"ADD     SP, SP, #0x74\n"
	"LDR     PC, [SP],#4\n"   
	);
	
	
		
}

//** sub_FFC04D38  @ 0xFFC04D38 
//sub_FFC04D38_my - adapted - tested
void __attribute__((naked,noinline)) sub_FFC04D38_my(  ) { 
asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"BL      sub_FFC00954\n"
	"BL      sub_FFC090B4\n"
	"CMP     R0, #0\n"
	"LDRLT   R0, =0xFFC04E4C\n"
	"BLLT    sub_FFC04E2C\n"
	"BL      sub_FFC04974\n"
	"CMP     R0, #0\n"
	"LDRLT   R0, =0xFFC04E54\n"
	"BLLT    sub_FFC04E2C\n"
	"LDR     R0, =0xFFC04E64\n" //      ; "/_term"\n"
	"BL      sub_FFC04A5C\n"
	"CMP     R0, #0\n"
	"LDRLT   R0, =0xFFC04E6C\n" // ; "termDeviceCreate"\n"
	"BLLT    sub_FFC04E2C\n"
	"LDR     R0, =0xFFC04E64\n" //      ; "/_term"\n"
	"BL      sub_FFC03578\n"
	"CMP     R0, #0\n"
	"LDRLT   R0, =0xFFC04E80\n"
	"BLLT    sub_FFC04E2C\n"
	"BL      sub_FFC08BCC\n"
	"CMP     R0, #0\n"
	"LDRLT   R0, =0xFFC04E8C\n"
	"BLLT    sub_FFC04E2C\n"
	"BL      sub_FFC014A8\n"
	"CMP     R0, #0\n"
	"LDRLT   R0, =0xFFC04E98\n"
	"BLLT    sub_FFC04E2C\n"
	"LDMFD   SP!, {R4,LR}\n"
"	B		taskcreate_Startup_my\n" //---------->                                     
	);
}

//** taskcreate_Startup_my  @ 0xFFC0C260 
//taskcreate_Startup_my - adapted - tested
void __attribute__((naked,noinline)) taskcreate_Startup_my(  ) { 
asm volatile (
	"STMFD   SP!, {R3,LR}\n"
	"BL      sub_FFC117B4\n"
	"BL      sub_FFC186D8\n"
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
"loc_FFC0C298:\n"               //             ; CODE XREF: taskcreate_Startup:loc_FFC0C298j
	"B       loc_FFC0C298\n"
"loc_FFC0C29C:\n"                 //           ; CODE XREF: taskcreate_Startup+10j
//	"BL      sub_FFC117BC // removed for corrected power-on/off button operation see boot() function  
	"BL      sub_FFC117B8\n"
	"BL      sub_FFC16994\n"
	"LDR     R1, =0x34E000\n"
	"MOV     R0, #0\n"
	"BL      sub_FFC16DDC\n"
	"BL      sub_FFC16B88\n"		//__KerSys.c__548 ; LOCATION: KerSys.c:548
	"MOV     R3, #0\n"
	"STR     R3, [SP]\n"
	"LDR     R3, =task_Startup_my\n" //+ -----------> \n"
	"MOV     R2, #0\n"
	"MOV     R1, #0x19\n"
	"LDR     R0, =0xFFC0C2E4\n"
	"BL      sub_FFC0AFAC\n"	// eventproc_export_CreateTask ; LOCATION: KerTask.c:163\n"
	"MOV     R0, #0\n"
	"LDMFD   SP!, {R12,PC}\n"
	);
}


//** task_Startup_my  @ 0xFFC0C1FC
//task_Startup_my - adapted - tested
void __attribute__((naked,noinline)) task_Startup_my(  ) { 
//	*((volatile int *) LED_PWR) = 0x46;
asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"BL      sub_FFC05394\n"	// taskcreate_ClockSave\n"
	"BL      sub_FFC128A0\n"
	"BL      sub_FFC10B28\n"
	"BL      sub_FFC18718\n"	//j_nullsub_246\n"
	"BL      sub_FFC188FC\n"
 //	"BL      sub_FFC187AC\n" // // Skip starting diskboot.bin again  \n"
	"BL      sub_FFC18A98\n"
	"BL      sub_FFC0FB94\n"
	"BL      sub_FFC1892C\n"
	"BL      sub_FFC15F94\n"
	"BL      sub_FFC18A9C\n"
//ROM: FFC0C22C                 BL      taskcreate_PhySw\n"
	);		 
	CreateTask_spytask();	// +
  CreateTask_PhySw(); 	// +
	CreateTask_Blinker();	// +
    asm volatile (	 
	"BL      sub_FFC146C0\n"
	"BL      sub_FFC18AB4\n"
	"BL      sub_FFC0EFB4\n"	// nullsub_2\n"
	"BL      sub_FFC104B0\n"
	"BL      sub_FFC184BC\n"	// taskcreate_Bye\n"
	"BL      sub_FFC10AD8\n"
	"BL      sub_FFC103D4\n"	// __LowBat.c__2 ; LOCATION: LowBat.c:2\n"
	"BL      sub_FFC0FBC8\n"
	"BL      sub_FFC194FC\n"
	"BL      sub_FFC103AC\n"
	"LDMFD   SP!, {R4,LR}\n"
	"B       sub_FFC054B4\n"	//__MLHClock.c__0 ; LOCATION: MLHClock.c:0\n"
	);
}

void __attribute__((naked,noinline)) busy_loop() {  // loop hack that allows startup with battery door open
  asm volatile (
"		STMFD   SP!, {R4-R6,LR} \n"
"		LDR     R0, =0x400000 \n"
"loop1: \n"
"		nop\n"
"       SUBS   R0,R0,#1 \n"
"		BNE    loop1 \n"
"       LDMFD   SP!, {R4-R6,PC} \n"
		);
}

void CreateTask_spytask() { 

        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


//G10 ** CreateTask_PhySw  @ 0xFF8218CC 
//a2100  ** ROM:FFC116B0 taskcreate_PhySw @ oxFFC116B0
//CreateTask_PhySw - adapted except mykbd_task ? - tested
void __attribute__((naked,noinline)) CreateTask_PhySw(  ) { 
asm volatile (
	"STMFD   SP!, {R3-R5,LR}\n"
	"LDR     R4, =0x1C18\n"
	"LDR     R0, [R4,#0x10]\n"
	"CMP     R0, #0\n"
	"BNE     loc_FFC116E4\n"
	"MOV     R3, #0\n"
	"STR     R3, [SP]\n"
//ROM: FFC116CC                 ADR     R3, task_PhySw
//ROM: FFC116D0                 MOV     R2, #0x800
//"                 LDR     R3, =task_PhySw\n"
"	LDR     R3, =mykbd_task\n"  // task_phySw
"	MOV     R2, #0x2000\n"		// greater Stacksize    
	"MOV     R1, #0x17\n"
	"LDR     R0, =0xFFC118B8\n"      // ; "PhySw"
	"BL      sub_FFC16BDC\n"	// KernelCreateTask\n" ; LOCATION: KernelMisc.c:19
	"STR     R0, [R4,#0x10]\n"
"loc_FFC116E4:\n"	//                            ; CODE XREF: taskcreate_PhySw+10j
	"BL      sub_FFC576E0\n"
	"BL      sub_FFC333C8\n" // IsFactoryMode\n"
	"CMP     R0, #0\n"
	"LDREQ   R1, =0xC670\n"
	"LDMEQFD SP!, {R3-R5,LR}\n"
	"BEQ     sub_FFC57668\n" 		// eventproc_export_OpLog.Start\n"
	"LDMFD   SP!, {R3-R5,PC}\n"
	);
}


//G10 ** init_file_modules_task  @ 0xFF882EA8 
//A2100 ** FFC6036C task_InitFileModules
//init_file_modules_task - adapted - tested
void __attribute__((naked,noinline)) init_file_modules_task(  ) { 
asm volatile (
	"STMFD   SP!, {R4-R6,LR}\n"
	"BL      sub_FFC59AF0\n"
	"LDR     R5, =0x5006\n"
	"MOVS    R4, R0\n"
	"MOVNE   R1, #0\n"
	"MOVNE   R0, R5\n"
	"BLNE    sub_FFC5C1B8\n"	//eventproc_export_PostLogicalEventToUI
//ROM: FFC60388                 BL      sub_FFC59B1C
//"	BL      sub_FFC59B1C_my\n"    //----------->
"	BL      sub_FFC59B1C\n"    //-----------> // Temporary tries to load SD
"	BL      core_spytask_can_start\n"      // +   

// jump back to FW:
"	LDR     PC, =0xFFC6038C\n"
// <---------------

	"CMP     R4, #0\n"
	"MOVEQ   R0, R5\n"
	"LDMEQFD SP!, {R4-R6,LR}\n"
	"MOVEQ   R1, #0\n"
	"BEQ     sub_FFC5C1B8\n" 	//eventproc_export_PostLogicalEventToUI
	"LDMFD   SP!, {R4-R6,PC}\n"              
	);
}


//G10 ** sub_FFC59B1C_my  @ 0xFF878098 
//A2100IS task_InitFileModules @ 0xFFC59B1C - tested
void __attribute__((naked,noinline)) sub_FFC59B1C_my(  ) {
asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"MOV     R0, #3\n"
//ROM: FFC59B24                 BL      sub_FFC3E874__Mounter.c__0 ; LOCATION: Mounter.c:0
	"BL      sub_FFC3E874_my\n" // ---------->
	"BL      sub_FFCD8FB8\n"	// nullsub_91
	"LDR     R4, =0x2B6C\n"
	"LDR     R0, [R4,#4]\n"
	"CMP     R0, #0\n"
	"BNE     loc_FFC59B54\n"
	"BL      sub_FFC3DC38\n"
	"BL      sub_FFCCF580\n"
	"BL      sub_FFC3DC38\n"
	"BL      sub_FFC3A09C\n"
	"BL      sub_FFC3DB38\n"
	"BL      sub_FFCCF644\n"
"loc_FFC59B54:\n" //                           ; CODE XREF: sub_FFC59B1C+1Cj
	"MOV     R0, #1\n"
	"STR     R0, [R4]\n"
	"LDMFD   SP!, {R4,PC}\n"   
	);
}


//** sub_FFC3E874_my  @ 0xFFC3E874 
//sub_FFC3E874_my - adapted - not passing sub_FFC3E320_my
void __attribute__((naked,noinline)) sub_FFC3E874_my(  ) {
asm volatile (
	"STMFD   SP!, {R4-R8,LR}\n"
	"MOV     R6, R0\n"
	"BL      sub_FFC3E7DC\n"	// __Mounter.c__0 ; LOCATION: Mounter.c:0\n"
	"LDR     R1, =0xE618\n"
	"MOV     R5, R0\n"
	"ADD     R4, R1, R0,LSL#7\n"
	"LDR     R0, [R4,#0x70]\n"
	"CMP     R0, #4\n"
	"LDREQ   R1, =0x6D8\n"
	"LDREQ   R0, =0xFFC3E300\n"
	"BLEQ    sub_FFC0B284\n"
	"MOV     R1, R6\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC3E248\n" 	// __Mounter.c__0 ; LOCATION: Mounter.c:0\n"
	"LDR     R0, [R4,#0x38]\n"
	"BL      sub_FFC3EDA0\n"
	"CMP     R0, #0\n"
	"STREQ   R0, [R4,#0x70]\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC3E320_my\n" // camera doesn't pass this function, lets' debug it step by step
	"MOV     R0, R5\n"
	//	"BL      sub_FFC3E614\n" // most sutable replacement // ----------> [tried_#1 - doesn't work]
	"BL      sub_FFC3E614_my\n"
	"MOV     R7, R0\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC3E678\n"	// __Mounter.c__7 ; LOCATION: Mounter.c:7\n"
	"LDR     R1, [R4,#0x3C]\n"
	"AND     R2, R7, R0\n"
	"CMP     R1, #0\n"
	"MOV     R0, #0\n"
	"MOVEQ   R0, #0x80000001\n"
	"BEQ     loc_FFC3E91C\n"
	"LDR     R3, [R4,#0x2C]\n"
	"CMP     R3, #2\n"
	"MOVEQ   R0, #4\n"
	"CMP     R1, #5\n"
	"ORRNE   R0, R0, #1\n"
	"BICEQ   R0, R0, #1\n"
	"CMP     R2, #0\n"
	"BICEQ   R0, R0, #2\n"
	"ORREQ   R0, R0, #0x80000000\n"
	"BICNE   R0, R0, #0x80000000\n"
	"ORRNE   R0, R0, #2\n"
"loc_FFC3E91C:\n"	//                            ; CODE XREF: _sub_FFC3E874__Mounter.c__0+78j\n"
	"CMP     R6, #7\n"
	"STR     R0, [R4,#0x40]\n"
	"LDMNEFD SP!, {R4-R8,PC}\n"
	"MOV     R0, R6\n"
	"BL      sub_FFC3E82C\n"
	"CMP     R0, #0\n"
	"LDMEQFD SP!, {R4-R8,LR}\n"
	"LDREQ   R0, =0xFFC3EB18\n"
	"BEQ     sub_FFC015A8\n"	// qPrintf\n"
	"LDMFD   SP!, {R4-R8,PC}\n"    
	);
}

//** sub_FFC3E320  @ 0xFFC3E320 - killer function
void __attribute__((naked,noinline)) sub_FFC3E320_my(  ) {
asm volatile (
	"LDR     R1, =0xE618\n"
	"STMFD   SP!, {R4-R6,LR}\n"
	"ADD     R4, R1, R0,LSL#7\n"
	"LDR     R0, [R4,#0x70]\n"
	"TST     R0, #1\n"
	"LDMNEFD SP!, {R4-R6,PC}\n" // passing this
	"LDR     R6, [R4,#0x38]\n"
	"BL      sub_FFC3B714\n" // __NewCatFsIO.c__116 ; LOCATION: NewCatFsIO.c:116\n"
	"LDR     R0, [R4,#0x38]\n"
	"BL      sub_FFC3EDA0\n" // passing this 
	"CMP     R0, #0\n"
	"MOV     R5, #5\n"
	"STREQ   R5, [R4,#0x3C]\n" // passing
	"BEQ     loc_FFC3E39C\n" // passing
//	"BL      sub_FFC3F570\n" // -> Killer function, seems like it disable SD
	"BL      sub_FFC3F658\n"//not getting even here 
	"CMP     R0, #0\n"
	"STREQ   R5, [R4,#0x3C]\n"
	"BEQ     loc_FFC3E390\n"
	"LDR     R1, [R4,#0x5C]\n"
	"MOV     R0, R6\n"
	"BLX     R1\n"
	"CMP     R0, #0\n"
	"STR     R0, [R4,#0x3C]\n"
	"LDRNE   R0, [R4,#0x70]\n"
	"ORRNE   R0, R0, #1\n"
	"STRNE   R0, [R4,#0x70]\n"
	"LDMNEFD SP!, {R4-R6,PC}\n"
"loc_FFC3E390:\n" // never get here 
	"LDR     R0, [R4,#0x60]\n"
	"CMP     R0, #0\n"
	"BLXNE   R0\n"
"loc_FFC3E39C:\n"
	"LDMFD   SP!, {R4-R6,LR}\n"
	"B       sub_FFC3F600\n"
);
}
//** sub_FFC3E614_my  @ 0xFFC3E614 
//sub_FFC3E614_my - adapted - starting 
void __attribute__((naked,noinline)) sub_FFC3E614_my(  ) {
asm volatile (
	"STMFD   SP!, {R4-R6,LR}\n"
	"MOV     R5, R0\n"
	"LDR     R0, =0xE618\n"
	"ADD     R4, R0, R5,LSL#7\n"
	"LDR     R0, [R4,#0x70]\n"
	"TST     R0, #2\n"
	"MOVNE   R0, #1\n"
	"LDMNEFD SP!, {R4-R6,PC}\n"
	"LDR     R0, [R4,#0x38]\n"
	"MOV     R1, R5\n"
	"BL      sub_FFC3E3A4\n"	//	__Mounter.c__0 ; LOCATION: Mounter.c:0
//	"BL      sub_FFC3E3A4_my\n"	// most suitable	//--------->
	"CMP     R0, #0\n"
	"LDMEQFD SP!, {R4-R6,PC}\n"
	"LDR     R0, [R4,#0x38]\n"
	"MOV     R1, R5\n"
	"BL      sub_FFC3E510\n"	//	__Mounter.c__0 ; LOCATION: Mounter.c:0
	"CMP     R0, #0\n"
	"LDMEQFD SP!, {R4-R6,PC}\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC3DE30\n"
	"CMP     R0, #0\n"
	"LDRNE   R1, [R4,#0x70]\n"
	"ORRNE   R1, R1, #2\n"
	"STRNE   R1, [R4,#0x70]\n"
	"LDMFD   SP!, {R4-R6,PC}\n"
	);
}


//** sub_FFC3E3A4_my  @ 0xFFC3E3A4
//sub_FFC3E3A4_my - adapted - mostly
/*
void __attribute__((naked,noinline)) sub_FFC3E3A4_my(  ) { 
// volatile long *p1 = (void*)LED_PWR;
// volatile long *p2 = (void*)LED_DP;
// int counter;	
// // DEBUG: blink led
// counter = DELAY; *p1 = 0x46;*p2 = 0x46;  while (counter--) { asm("nop\n nop\n"); };
// counter = DELAY; *p1 = 0x44;*p2 = 0x44;  while (counter--) { asm("nop\n nop\n"); };  

asm volatile (
	"STMFD   SP!, {R4-R8,LR}\n"
	"MOV     R8, R0\n"
	"LDR     R0, =0xE618\n"
	"MOV     R7, #0\n"
	"ADD     R5, R0, R1,LSL#7\n"
	"LDR     R0, [R5,#0x3C]\n"
	"MOV     R6, #0\n"
	"CMP     R0, #7\n"
	"ADDLS   PC, PC, R0,LSL#2\n"
	"B       loc_FFC3E4F4\n"
"loc_FFC3E3CC:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j
	"B       loc_FFC3E404\n"
"loc_FFC3E3D0:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j
	"B       loc_FFC3E3EC\n"
"loc_FFC3E3D4:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j
	"B       loc_FFC3E3EC\n"
"loc_FFC3E3D8:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"B       loc_FFC3E3EC\n"
"loc_FFC3E3DC:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"B       loc_FFC3E3EC\n"
"loc_FFC3E3E0:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"B       loc_FFC3E4EC\n"
"loc_FFC3E3E4:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"B       loc_FFC3E3EC\n"
"loc_FFC3E3E8:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"B       loc_FFC3E3EC\n"
"loc_FFC3E3EC:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"MOV     R2, #0\n"
	"MOV     R1, #0x200\n"
	"MOV     R0, #2\n"
	"BL      sub_FFC53C30\n"
	"MOVS    R4, R0\n"
	"BNE     loc_FFC3E40C\n"
"loc_FFC3E404:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"MOV     R0, #0\n"
	"LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC3E40C:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+5Cj\n"
	"LDR     R12, [R5,#0x4C]\n"
	"MOV     R3, R4\n"
	"MOV     R2, #1\n"
	"MOV     R1, #0\n"
	"MOV     R0, R8\n"
	"BLX     R12\n"
	"CMP     R0, #1\n"
	"BNE     loc_FFC3E438\n"
	"MOV     R0, #2\n"
	"BL      sub_FFC53D7C\n"	// __ExMemMan.c__0 ; LOCATION: ExMemMan.c:0\n"
	"B       loc_FFC3E404\n"
"loc_FFC3E438:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+84j\n"
	"LDR     R1, [R5,#0x68]\n"
	"MOV     R0, R8\n"
//ROM: FFC3E440                 BLX     R1
//place code here
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
                "BNE     dg_sd_fat32\n"                // No, it isn't.
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
//ROM: FFC3E460                 LDRB    LR, [R4,#0x1FF]\n"
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
//ROM:F FC3E494                 LDRB    R12, [R4,#0x1FE]
//"	LDRB	R12, [R4, #0x1FE] \n"    	// replaced, see below 
"	LDRB    R12, [LR,#0x1FE]\n"			// New! First MBR signature byte (0x55)
"	LDRB    LR, [LR,#0x1FF]\n"			//      Last MBR signature byte (0xAA)	
	"MOV     R4, #0\n" 
	"BNE     loc_FFC3E4C4\n"
	"CMP     R0, R1\n"
	"BCC     loc_FFC3E4C4\n"
	"ADD     R2, R1, R3\n"
	"CMP     R2, R0\n"
	"CMPLS   R12, #0x55\n"
	"CMPEQ   LR, #0xAA\n"
	"MOVEQ   R7, R1\n"
	"MOVEQ   R6, R3\n"
	"MOVEQ   R4, #1\n"
"loc_FFC3E4C4:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+F8j\n"
	"MOV     R0, #2\n"
	"BL      sub_FFC53D7C\n"	// __ExMemMan.c__0 ; LOCATION: ExMemMan.c:0\n"
	"CMP     R4, #0\n"
	"BNE     loc_FFC3E500\n"
	"LDR     R1, [R5,#0x68]\n"
	"MOV     R7, #0\n"
	"MOV     R0, R8\n"
	"BLX     R1\n"
	"MOV     R6, R0\n"
	"B       loc_FFC3E500\n"
"loc_FFC3E4EC:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"MOV     R6, #0x40\n"
	"B       loc_FFC3E500\n"
"loc_FFC3E4F4:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+20j\n"
	"LDR     R1, =0x5C9\n"
	"LDR     R0, =0xFFC3E300\n" //  ; "Mounter.c"\n"
	"BL      sub_FFC0B284\n"
"loc_FFC3E500:\n" //                            ; CODE XREF: _sub_FFC3E3A4__Mounter.c__0+12Cj\n"
	"STR     R7, [R5,#0x44]!\n"
	"MOV     R0, #1\n"
	"STR     R6, [R5,#4]\n"
	"LDMFD   SP!, {R4-R8,PC}\n"                                 
	);
}
*/
//** sub_FFC3E510_my @ 0xFFC3E510
//
void __attribute__((naked,noinline)) sub_FFC3E510_my() {
/*asm volatile (

ROM:FFC3E510                 STMFD   SP!, {R4-R8,LR}
ROM:FFC3E514                 MOV     R7, R0
ROM:FFC3E518                 LDR     R0, =0xE618
ROM:FFC3E51C                 MOV     R6, R1
ROM:FFC3E520                 ADD     R4, R0, R1,LSL#7
ROM:FFC3E524                 LDR     R0, [R4,#0x3C]
ROM:FFC3E528                 MOV     R5, #0
ROM:FFC3E52C                 CMP     R0, #6
ROM:FFC3E530                 ADDLS   PC, PC, R0,LSL#2
ROM:FFC3E534                 B       loc_FFC3E5A0
ROM:FFC3E538 loc_FFC3E538                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E538                 B       loc_FFC3E60C
ROM:FFC3E53C loc_FFC3E53C                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E53C                 B       loc_FFC3E554
ROM:FFC3E540 loc_FFC3E540                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E540                 B       loc_FFC3E554
ROM:FFC3E544 loc_FFC3E544                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E544                 B       loc_FFC3E554
ROM:FFC3E548 loc_FFC3E548                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E548                 B       loc_FFC3E554
ROM:FFC3E54C loc_FFC3E54C                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E54C                 B       loc_FFC3E598
ROM:FFC3E550 loc_FFC3E550                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E550                 B       loc_FFC3E554
ROM:FFC3E554 loc_FFC3E554                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E554                 MOV     R2, #0
ROM:FFC3E558                 MOV     R1, #0x200
ROM:FFC3E55C                 MOV     R0, #2
ROM:FFC3E560                 BL      sub_FFC53C30
ROM:FFC3E564                 MOVS    R5, R0
ROM:FFC3E568                 BEQ     loc_FFC3E60C
ROM:FFC3E56C                 LDR     R12, [R4,#0x4C]
ROM:FFC3E570                 LDR     R1, [R4,#0x44]
ROM:FFC3E574                 MOV     R3, R5
ROM:FFC3E578                 MOV     R2, #1
ROM:FFC3E57C                 MOV     R0, R7
ROM:FFC3E580                 BLX     R12
ROM:FFC3E584                 CMP     R0, #1
ROM:FFC3E588                 BNE     loc_FFC3E5AC
ROM:FFC3E58C                 MOV     R0, #2
ROM:FFC3E590                 BL      _sub_FFC53D7C__ExMemMan.c__0 ; LOCATION: ExMemMan.c:0
ROM:FFC3E594                 B       loc_FFC3E60C
ROM:FFC3E598 loc_FFC3E598                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E598                 MOV     R0, #1
ROM:FFC3E59C                 LDMFD   SP!, {R4-R8,PC}
ROM:FFC3E5A0 loc_FFC3E5A0                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E5A0                 LDR     R1, =0x5F7
ROM:FFC3E5A4                 ADR     R0, aMounter_c  ; "Mounter.c"
ROM:FFC3E5A8                 BL      DebugAssert
ROM:FFC3E5AC loc_FFC3E5AC                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+78j
ROM:FFC3E5AC                 MOV     R1, R5
ROM:FFC3E5B0                 MOV     R0, R6
ROM:FFC3E5B4                 BL      sub_FFC3DEE4
ROM:FFC3E5B8                 MOV     R5, R0
ROM:FFC3E5BC                 MOV     R0, #2
ROM:FFC3E5C0                 BL      _sub_FFC53D7C__ExMemMan.c__0 ; LOCATION: ExMemMan.c:0
ROM:FFC3E5C4                 LDR     R1, [R4,#0x68]
ROM:FFC3E5C8                 MOV     R0, R7
ROM:FFC3E5CC                 BLX     R1
ROM:FFC3E5D0                 CMP     R5, #0
ROM:FFC3E5D4                 BEQ     loc_FFC3E600
ROM:FFC3E5D8                 LDR     R1, [R4,#0x44]
ROM:FFC3E5DC                 CMP     R1, R0
ROM:FFC3E5E0                 LDRLS   R2, =0xE698
ROM:FFC3E5E4                 ADDLS   R3, R6, R6,LSL#4
ROM:FFC3E5E8                 ADDLS   R2, R2, R3,LSL#2
ROM:FFC3E5EC                 LDRLS   R2, [R2,#0x18]
ROM:FFC3E5F0                 ADDLS   R1, R1, R2
ROM:FFC3E5F4                 CMPLS   R1, R0
ROM:FFC3E5F8                 STRLS   R2, [R4,#0x48]
ROM:FFC3E5FC                 BLS     loc_FFC3E598
ROM:FFC3E600 loc_FFC3E600                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+C4j
ROM:FFC3E600                 MOV     R1, #0
ROM:FFC3E604                 STR     R1, [R4,#0x44]!
ROM:FFC3E608                 STR     R0, [R4,#4]
ROM:FFC3E60C loc_FFC3E60C                            ; CODE XREF: _sub_FFC3E510__Mounter.c__0+20j
ROM:FFC3E60C                 MOV     R0, #0
ROM:FFC3E610                 LDMFD   SP!, {R4-R8,PC}

);
*/
}