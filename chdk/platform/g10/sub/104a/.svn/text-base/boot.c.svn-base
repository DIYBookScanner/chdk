// G10 1.04a
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"
#include "gui.h"
#include "../../../../core/gui_draw.h"

const char * const new_sa = &_end;

#define LED_ISO  (void*) 0xC02200D0 // G10 ISO select dial LED
#define LED_DP   (void*) 0xC02200D4	// G10 direct print button LED
#define LED_ECL  (void*) 0xC02200D8 // G10 exposure compensation dial LED
#define LED_PWR  (void*) 0xC02200DC	// G10 power LED

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

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


void taskCreateHook(int *p) { 
	p-=17;
	
	if (p[0]==0xff882ea8)  p[0]=(int)init_file_modules_task; 
	if (p[0]==0xff862c0c)  p[0]=(int)movie_record_task;	
	if (p[0]==0xff866bfc)  p[0]=(int)capt_seq_task;
	if (p[0]==0xff8ab0e0)  p[0]=(int)exp_drv_task;
    if (p[0]==0xff84b23c)  p[0]=(int)JogDial_task_my;
}

void taskCreateHook2(int *p) { 
	p-=17;
	if (p[0]==0xff882ea8)  p[0]=(int)init_file_modules_task;
	if (p[0]==0xff8ab0e0)  p[0]=(int)exp_drv_task; 
}

void __attribute__((naked,noinline)) boot(  ) { 
asm volatile (
"	LDR	R1, =0xC0410000 \n"                  
"	MOV	R0, #0 \n"                           
"	STR	R0, [R1] \n"                         
"	MOV	R1, #0x78 \n"                        
"	MCR	p15, 0, R1, c1, c0 \n"               
"	MOV	R1, #0 \n"                           
"	MCR	p15, 0, R1, c7, c10, 4 \n"           
"	MCR	p15, 0, R1, c7, c5 \n"               
"	MCR	p15, 0, R1, c7, c6 \n"               
"	MOV	R0, #0x3D \n"                        
"	MCR	p15, 0, R0, c6, c0 \n"               
"	MOV	R0, #0xC000002F \n"                  
"	MCR	p15, 0, R0, c6, c1 \n"               
"	MOV	R0, #0x35 \n"                        
"	MCR	p15, 0, R0, c6, c2 \n"               
"	MOV	R0, #0x40000035 \n"                  
"	MCR	p15, 0, R0, c6, c3 \n"               
"	MOV	R0, #0x80000017 \n"                  
"	MCR	p15, 0, R0, c6, c4 \n"               
"	LDR	R0, =0xFF80002D \n"                  
"	MCR	p15, 0, R0, c6, c5 \n"               
"	MOV	R0, #0x34 \n"                        
"	MCR	p15, 0, R0, c2, c0 \n"               
"	MOV	R0, #0x34 \n"                        
"	MCR	p15, 0, R0, c2, c0, 1 \n"            
"	MOV	R0, #0x34 \n"                        
"	MCR	p15, 0, R0, c3, c0 \n"               
"	LDR	R0, =0x3333330 \n"                   
"	MCR	p15, 0, R0, c5, c0, 2 \n"            
"	LDR	R0, =0x3333330 \n"                   
"	MCR	p15, 0, R0, c5, c0, 3 \n"            
"	MRC	p15, 0, R0, c1, c0 \n"               
"	ORR	R0, R0, #0x1000 \n"                  
"	ORR	R0, R0, #4 \n"                       
"	ORR	R0, R0, #1 \n"                       
"	MCR	p15, 0, R0, c1, c0 \n"               
"	MOV	R1, #0x80000006 \n"                  
"	MCR	p15, 0, R1, c9, c1 \n"               
"	MOV	R1, #6 \n"                           
"	MCR	p15, 0, R1, c9, c1, 1 \n"            
"	MRC	p15, 0, R1, c1, c0 \n"               
"	ORR	R1, R1, #0x50000 \n"                 
"	MCR	p15, 0, R1, c1, c0 \n"               
"	LDR	R2, =0xC0200000 \n"                  
"	MOV	R1, #1 \n"                           
"	STR	R1, [R2, #0x10C] \n"                 
"	MOV	R1, #0xFF \n"                        
"	STR	R1, [R2, #0xC] \n"                   
"	STR	R1, [R2, #0x1C] \n"                  
"	STR	R1, [R2, #0x2C] \n"                  
"	STR	R1, [R2, #0x3C] \n"                  
"	STR	R1, [R2, #0x4C] \n"                  
"	STR	R1, [R2, #0x5C] \n"                  
"	STR	R1, [R2, #0x6C] \n"                  
"	STR	R1, [R2, #0x7C] \n"                  
"	STR	R1, [R2, #0x8C] \n"                  
"	STR	R1, [R2, #0x9C] \n"                  
"	STR	R1, [R2, #0xAC] \n"                  
"	STR	R1, [R2, #0xBC] \n"                  
"	STR	R1, [R2, #0xCC] \n"                  
"	STR	R1, [R2, #0xDC] \n"                  
"	STR	R1, [R2, #0xEC] \n"                  
"	STR	R1, [R2, #0xFC] \n"                  
"	LDR	R1, =0xC0400008 \n"                  
"	LDR	R2, =0x430005 \n"                    
"	STR	R2, [R1] \n"                         
"	MOV	R1, #1 \n"                           
"	LDR	R2, =0xC0243100 \n"                  
"	STR	R2, [R1] \n"                         
"	LDR	R2, =0xC0242010 \n"                  
"	LDR	R1, [R2] \n"                         
"	ORR	R1, R1, #1 \n"                       
"	STR	R1, [R2] \n"                         
"	LDR	R0, =0xFFBA0A1C \n" 	//* firmware difference        
"	LDR	R1, =0x1900 \n"      // MEMBASEADDR=0x1900                
"	LDR	R3, =0x10834 \n"                     
"loc_FF81013C:\n"
"	CMP	R1, R3 \n"                           
"	LDRCC	R2, [R0], #4 \n"                   
"	STRCC	R2, [R1], #4 \n"                   
"	BCC	loc_FF81013C \n"                     
"	LDR	R1, =0xEEECC \n"     // MEMISOSTART=0xEEECC              
"	MOV	R2, #0 \n"                           
"loc_FF810154:\n"
"	CMP	R3, R1 \n"                           
"	STRCC	R2, [R3], #4 \n"                   
"	BCC	loc_FF810154 \n"                     
"	B	sub_FF8101A0_my\n"                       
	);
}

void __attribute__((naked,noinline)) sub_FF8101A0_my(  ) { 

    *(int*)0x1930=(int)taskCreateHook; 
    *(int*)0x1934=(int)taskCreateHook2; 
    *(int*)0x1938=(int)taskCreateHook; 
	
// Power ON/OFF detection  G10 @FF84A8D0   replacement  for correct power-on.
*(int*)(0x25CC+0x04)= (*(int*)0xC02200F8)&1 ? 0x100000 : 0x200000; // replacement  for correct power-on.

asm volatile (
"	LDR	R0, =0xFF810218 \n"                  
"	MOV	R1, #0 \n"                           
"	LDR	R3, =0xFF810250 \n"                  
"loc_FF8101AC:\n"
"	CMP	R0, R3 \n"                           
"	LDRCC	R2, [R0], #4 \n"                   
"	STRCC	R2, [R1], #4 \n"                   
"	BCC	loc_FF8101AC \n"                     
"	LDR	R0, =0xFF810250 \n"                  
"	MOV	R1, #0x4B0 \n"                       
"	LDR	R3, =0xFF810464 \n"                  
"loc_FF8101C8:\n"
"	CMP	R0, R3 \n"                           
"	LDRCC	R2, [R0], #4 \n"                   
"	STRCC	R2, [R1], #4 \n"                   
"	BCC	loc_FF8101C8 \n"                     
"	MOV	R0, #0xD2 \n"                        
"	MSR	CPSR_cxsf, R0 \n"                    
"	MOV	SP, #0x1000 \n"                      
"	MOV	R0, #0xD3 \n"                        
"	MSR	CPSR_cxsf, R0 \n"                    
"	MOV	SP, #0x1000 \n"                      
"	LDR	R0, =0x6C4 \n"                       
"	LDR	R2, =0xEEEEEEEE \n"                  
"	MOV	R3, #0x1000 \n"                      
"loc_FF8101FC:\n"
"	CMP	R0, R3 \n"                           
"	STRCC	R2, [R0], #4 \n"                   
"	BCC	loc_FF8101FC \n"                     
"	BL	sub_FF810F94_my \n"  //----------->                    
	);
}


//** sub_FF810F94_my  @ 0xFF810F94 

void __attribute__((naked,noinline)) sub_FF810F94_my(  ) { 
asm volatile (
"	STR	LR, [SP, #-4]! \n"                   
"	SUB	SP, SP, #0x74 \n"                    
"	MOV	R0, SP \n"                           
"	MOV	R1, #0x74 \n"                        
"	BL	sub_FFB05284 \n" 	//* firmware difference                        
"	MOV	R0, #0x53000 \n"                     
"	STR	R0, [SP, #4] \n"                     
//"	LDR	R0, =0xEEECC \n"   		// -
"	LDR     R0, =new_sa\n"      // +
"	LDR     R0, [R0]\n"         // +		                   
"	LDR	R2, =0x379C00 \n"                    
"	LDR	R1, =0x3724A8 \n"                    
"	STR	R0, [SP, #8] \n"                     
"	SUB	R0, R1, R0 \n"                       
"	ADD	R3, SP, #0xC \n"                     
"	STR	R2, [SP] \n"                         
"	STMIA	R3, {R0-R2} \n"                    
"	MOV	R0, #0x22 \n"                        
"	STR	R0, [SP, #0x18] \n"                  
"	MOV	R0, #0x68 \n"                        
"	STR	R0, [SP, #0x1C] \n"                  
"	LDR	R0, =0x19B \n"                       
"	LDR	R1, =sub_FF814D8C_my \n"  //+ ---------->                
"	STR	R0, [SP, #0x20] \n"                  
"	MOV	R0, #0x96 \n"                        
"	STR	R0, [SP, #0x24] \n"                  
"	MOV	R0, #0x78 \n"                        
"	STR	R0, [SP, #0x28] \n"                  
"	MOV	R0, #0x64 \n"                        
"	STR	R0, [SP, #0x2C] \n"                  
"	MOV	R0, #0 \n"                           
"	STR	R0, [SP, #0x30] \n"                  
"	STR	R0, [SP, #0x34] \n"                  
"	MOV	R0, #0x10 \n"                        
"	STR	R0, [SP, #0x5C] \n"                  
"	MOV	R0, #0x800 \n"                       
"	STR	R0, [SP, #0x60] \n"                  
"	MOV	R0, #0xA0 \n"                        
"	STR	R0, [SP, #0x64] \n"                  
"	MOV	R0, #0x280 \n"                       
"	STR	R0, [SP, #0x68] \n"                  
"	MOV	R0, SP \n"                           
"	MOV	R2, #0 \n"                           
"	BL	sub_FF812D38 \n"                      
"	ADD	SP, SP, #0x74 \n"                    
"	LDR	PC, [SP], #4 \n"                     
	);
}

//** sub_FF814D8C_my  @ 0xFF814D8C 

void __attribute__((naked,noinline)) sub_FF814D8C_my(  ) { 
asm volatile (
"	STMFD	SP!, {R4,LR} \n"                   
"	BL	sub_FF810940 \n"                      
"	BL	sub_FF81901C \n"                      
"	CMP	R0, #0 \n"                           
"	LDRLT	R0, =0xFF814EA0 \n"                
"	BLLT	sub_FF814E80 \n"                    
"	BL	sub_FF8149B4 \n"                      
"	CMP	R0, #0 \n"                           
"	LDRLT	R0, =0xFF814EA8 \n"                
"	BLLT	sub_FF814E80 \n"                    
"	LDR	R0, =0xFF814EB8 \n"                  
"	BL	sub_FF814A9C \n"                      
"	CMP	R0, #0 \n"                           
"	LDRLT	R0, =0xFF814EC0 \n"                
"	BLLT	sub_FF814E80 \n"                    
"	LDR	R0, =0xFF814EB8 \n"                  
"	BL	sub_FF813548 \n"                      
"	CMP	R0, #0 \n"                           
"	LDRLT	R0, =0xFF814ED4 \n"                
"	BLLT	sub_FF814E80 \n"                    
"	BL	sub_FF818BA4 \n"                      
"	CMP	R0, #0 \n"                           
"	LDRLT	R0, =0xFF814EE0 \n"                
"	BLLT	sub_FF814E80 \n"                    
"	BL	sub_FF811478 \n"                      
"	CMP	R0, #0 \n"                           
"	LDRLT	R0, =0xFF814EEC \n"                
"	BLLT	sub_FF814E80 \n"                    
"	LDMFD	SP!, {R4,LR} \n"                   
"	B		taskcreate_Startup_my\n" //---------->                     
	);
}

//** taskcreate_Startup_my  @ 0xFF81C1A8 

void __attribute__((naked,noinline)) taskcreate_Startup_my(  ) { 
asm volatile (
"	STMFD	SP!, {R3,LR} \n"                   
"	BL	sub_FF8219D4 \n"                      
"	BL	sub_FF82A16C \n"                      
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF81C1EC \n"                     
"	BL	sub_FF823100 \n"                      
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF81C1EC \n"                     
"	BL	sub_FF8219D0 \n"                      
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF81C1EC \n"                     
"	BL	sub_FF821168 \n"                      
"	LDR	R1, =0xC0220000 \n"                  
"	MOV	R0, #0x44 \n"                        
"	STR	R0, [R1, #0x1C] \n"                  
"	BL	sub_FF821354 \n"        
"loc_FF81C1E8:\n"
"	B	loc_FF81C1E8 \n"                       
"loc_FF81C1EC:\n"
//"	BL	sub_FF8219DC \n"     // removed for corrected power-on/off button operation see boot() function                 
"	BL	sub_FF8219D8 \n"                      
"	BL	sub_FF8282FC \n"   		   
"	LDR	R1, =0x3CE000 \n"                    
"	MOV	R0, #0 \n"                           
"	BL	sub_FF828744 \n"                      
"	BL	sub_FF8284F0 \n"                      
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                         
//"	LDR	R3, =0xFF81C144 \n"
"	LDR	R3, =task_Startup_my\n" //+ ----------->                  
"	MOV	R2, #0 \n"                           
"	MOV	R1, #0x19 \n"                        
"	LDR	R0, =0xFF81C234 \n"                  
"	BL	sub_FF81AEF4 \n"                      
"	MOV	R0, #0 \n"                           
"	LDMFD	SP!, {R12,PC} \n"                  
	);
}


//** task_Startup_my  @ 0xFF81C144 

void __attribute__((naked,noinline)) task_Startup_my(  ) { 
	*((volatile int *) LED_PWR) = 0x46;
asm volatile (
"	STMFD	SP!, {R4,LR} \n"                   
"	BL	sub_FF8153CC \n"                      
"	BL	sub_FF822B38 \n"                      
"	BL	sub_FF820E28 \n"                      
"	BL	sub_FF82A1AC \n"                      
"	BL	sub_FF82A374 \n"                      
//"	BL	sub_FF82A234 \n" 	// Skip starting diskboot.bin again                      
"	BL	sub_FF82A52C \n"                      
"	BL	sub_FF81FAA0 \n"                      
"	BL	sub_FF82A3C4 \n"                      
"	BL	sub_FF8278FC \n"                      
"	BL	sub_FF82A530 \n"                      
//"	BL	sub_FF8218CC \n"   // taskcreate_PhySw    
	);		 
	CreateTask_spytask();	// +
    CreateTask_PhySw(); 	// +
	CreateTask_Blinker();	
    asm volatile (	                  
"	BL	sub_FF82503C \n"                      
"	BL	sub_FF82A548 \n"                      
"	BL	sub_FF81EF04 \n"                      
"	BL	busy_loop \n"   
"	BL	sub_FF820738 \n"                      
"	BL	sub_FF829F48 \n"                      
"	BL	sub_FF820DD8 \n"                      
"	BL	sub_FF820644 \n"                      
"	BL	sub_FF81FAD4 \n"                      
"	BL	sub_FF82B068 \n"                      
"	BL	sub_FF82061C \n"                      
"	LDMFD	SP!, {R4,LR} \n"                   
"	B	sub_FF815490 \n"                       
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


//** CreateTask_PhySw  @ 0xFF8218CC 

void __attribute__((naked,noinline)) CreateTask_PhySw(  ) { 
asm volatile (
"	STMFD	SP!, {R3-R5,LR} \n"                
"	LDR	R4, =0x1C20 \n"                      
"	LDR	R0, [R4, #0x10] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF821900 \n"                     
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                         
//"	LDR	R3, =0xFF821898 \n"                  
//"	MOV	R2, #0x800 \n"    
"	LDR     R3, =mykbd_task\n"  // task_phySw
"	MOV     R2, #0x2000\n"		// greater Stacksize    
"	MOV	R1, #0x17 \n"                        
"	LDR	R0, =0xFF821AD4 \n"                  
"	BL	sub_FF828544 \n"                      
"	STR	R0, [R4, #0x10] \n"                  
"loc_FF821900:\n"
"	BL	sub_FF84B338 \n"                      
"	BL	sub_FF875CBC \n"                      
"	BL	sub_FF8230A4 \n"                      
"	CMP	R0, #0 \n"                           
"	LDREQ	R1, =0x11CC4 \n"                   
"	LDMEQFD	SP!, {R3-R5,LR} \n"              
"	BEQ	sub_FF875BFC \n"                     
"	LDMFD	SP!, {R3-R5,PC} \n"                
	);
}


//** init_file_modules_task  @ 0xFF882EA8 

void __attribute__((naked,noinline)) init_file_modules_task(  ) { 
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	BL	sub_FF87806C \n"                      
"	LDR	R5, =0x5006 \n"                      
"	MOVS	R4, R0 \n"                          
"	MOVNE	R1, #0 \n"                         
"	MOVNE	R0, R5 \n"                         
"	BLNE	sub_FF87CD38 \n"                    
//"	BL	sub_FF878098 \n"  
"	BL      sub_FF878098_my\n"    //----------->
"	BL      core_spytask_can_start\n"      // +                    
"	CMP	R4, #0 \n"                           
"	MOVEQ	R0, R5 \n"                         
"	LDMEQFD	SP!, {R4-R6,LR} \n"              
"	MOVEQ	R1, #0 \n"                         
"	BEQ	sub_FF87CD38 \n"                     
"	LDMFD	SP!, {R4-R6,PC} \n"                
	);
}


//** sub_FF878098_my  @ 0xFF878098 

void __attribute__((naked,noinline)) sub_FF878098_my(  ) {
asm volatile (
"	STMFD	SP!, {R4,LR} \n"                   
//"	BL	sub_FF859C00 \n"       
"	BL  sub_FF859C00_my\n"  	// ---------->               
"	BL	sub_FF91F284 \n"     	// nullsub                 
"	LDR	R4, =0x585C \n"                      
"	LDR	R0, [R4, #4] \n"                     
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF8780CC \n"                     
"	BL	sub_FF8590C8 \n"                      
"	BL	sub_FF912FC0 \n"                      
"	BL	sub_FF8590C8 \n"                      
"	BL	sub_FF854F9C \n"                      
"	BL	sub_FF858FC8 \n"                      
"	BL	sub_FF91308C \n"                      
"loc_FF8780CC:\n"
"	MOV	R0, #1 \n"                           
"	STR	R0, [R4] \n"                         
"	LDMFD	SP!, {R4,PC} \n"                   
	);
}


//** sub_FF859C00_my  @ 0xFF859C00 

void __attribute__((naked,noinline)) sub_FF859C00_my(  ) {
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	MOV	R6, #0 \n"                           
"	MOV	R0, R6 \n"                           
"	BL	sub_FF8596C0 \n"                      
"	LDR	R4, =0x1A578 \n"                     
"	MOV	R5, #0 \n"                           
"	LDR	R0, [R4, #0x38] \n"                  
"	BL	sub_FF85A120 \n"                      
"	CMP	R0, #0 \n"                           
"	LDREQ	R0, =0x2A5C \n"                    
"	STREQ	R5, [R0, #0x10] \n"                
"	STREQ	R5, [R0, #0x14] \n"                
"	STREQ	R5, [R0, #0x18] \n"                
"	MOV	R0, R6 \n"                           
"	BL	sub_FF859700 \n"                      
"	MOV	R0, R6 \n"                           
//"	BL	sub_FF859A3C \n"
"	BL	sub_FF859A3C_my \n"    	// ---------->                                            
"	MOV	R5, R0 \n"                           
"	MOV	R0, R6 \n"                           
"	BL	sub_FF859AA8 \n"                      
"	LDR	R1, [R4, #0x3C] \n"                  
"	AND	R2, R5, R0 \n"                       
"	CMP	R1, #0 \n"                           
"	MOV	R0, #0 \n"                           
"	MOVEQ	R0, #0x80000001 \n"                
"	BEQ	loc_FF859C94 \n"                     
"	LDR	R3, [R4, #0x2C] \n"                  
"	CMP	R3, #2 \n"                           
"	MOVEQ	R0, #4 \n"                         
"	CMP	R1, #5 \n"                           
"	ORRNE	R0, R0, #1 \n"                     
"	BICEQ	R0, R0, #1 \n"                     
"	CMP	R2, #0 \n"                           
"	BICEQ	R0, R0, #2 \n"                     
"	ORREQ	R0, R0, #0x80000000 \n"            
"	BICNE	R0, R0, #0x80000000 \n"            
"	ORRNE	R0, R0, #2 \n"                     
"loc_FF859C94:\n"
"	STR	R0, [R4, #0x40] \n"                  
"	LDMFD	SP!, {R4-R6,PC} \n"                
	);
}

//** sub_FF859A3C_my  @ 0xFF859A3C 

void __attribute__((naked,noinline)) sub_FF859A3C_my(  ) {
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	LDR	R5, =0x2A5C \n"                      
"	MOV	R6, R0 \n"                           
"	LDR	R0, [R5, #0x14] \n"                  
"	CMP	R0, #0 \n"                           
"	MOVNE	R0, #1 \n"                         
"	LDMNEFD	SP!, {R4-R6,PC} \n"              
"	MOV	R0, #0x17 \n"                        
"	MUL	R1, R0, R6 \n"                       
"	LDR	R0, =0x1A578 \n"                     
"	ADD	R4, R0, R1, LSL #2 \n"               
"	LDR	R0, [R4, #0x38] \n"                  
"	MOV	R1, R6 \n"                           
//"	BL	sub_FF8597CC \n" 
"	BL	sub_FF8597CC_my \n"       	// ---------->                    
"	CMP	R0, #0 \n"                           
"	LDMEQFD	SP!, {R4-R6,PC} \n"              
"	LDR	R0, [R4, #0x38] \n"                  
"	MOV	R1, R6 \n"                           
"	BL	sub_FF859934 \n"                      
"	CMP	R0, #0 \n"                           
"	LDMEQFD	SP!, {R4-R6,PC} \n"              
"	MOV	R0, R6 \n"                           
"	BL	sub_FF8592C8 \n"                      
"	CMP	R0, #0 \n"                           
"	MOVNE	R1, #1 \n"                         
"	STRNE	R1, [R5, #0x14] \n"                
"	LDMFD	SP!, {R4-R6,PC} \n"                                      
	);
}


//** sub_FF86F1DC_my  @ 0xFF8597CC 

void __attribute__((naked,noinline)) sub_FF8597CC_my(  ) { 
asm volatile (
"	STMFD	SP!, {R4-R8,LR} \n"                
"	MOV	R8, R0 \n"                           
"	MOV	R0, #0x17 \n"                        
"	MUL	R1, R0, R1 \n"                       
"	LDR	R0, =0x1A578 \n"                     
"	MOV	R6, #0 \n"                           
"	ADD	R7, R0, R1, LSL #2 \n"               
"	LDR	R0, [R7, #0x3C] \n"                  
"	MOV	R5, #0 \n"                           
"	CMP	R0, #6 \n"                           
"	ADDLS	PC, PC, R0, LSL #2 \n"             
"	B	loc_FF859918 \n"                       
"	B	loc_FF859830 \n"                       
"	B	loc_FF859818 \n"                       
"	B	loc_FF859818 \n"                       
"	B	loc_FF859818 \n"                       
"	B	loc_FF859818 \n"                       
"	B	loc_FF859910 \n"                       
"	B	loc_FF859818 \n"    
"loc_FF859818:\n"
"	MOV	R2, #0 \n"                           
"	MOV	R1, #0x200 \n"                       
"	MOV	R0, #2 \n"                           
"	BL	sub_FF872014 \n"                      
"	MOVS	R4, R0 \n"                          
"	BNE	loc_FF859838 \n"                     
"loc_FF859830:\n"
"	MOV	R0, #0 \n"                           
"	LDMFD	SP!, {R4-R8,PC} \n"                
"loc_FF859838:\n"
"	LDR	R12, [R7, #0x4C] \n"                 
"	MOV	R3, R4 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #0 \n"                           
"	MOV	R0, R8 \n" 
                          
"	BLX	R12 \n"                              
"	CMP	R0, #1 \n"                           
"	BNE	loc_FF859864 \n"                     
"	MOV	R0, #2 \n"                           
"	BL	sub_FF872160 \n"                      
"	B	loc_FF859830 \n"                       
"loc_FF859864:\n"
"	MOV	R0, R8 \n"                           
"	BL	sub_FF92AC04 \n"  
                    
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
					
"	LDRB	R1, [R4, #0x1C9] \n"                
"	LDRB	R3, [R4, #0x1C8] \n"                
"	LDRB	R12, [R4, #0x1CC] \n"               
"	MOV	R1, R1, LSL #0x18 \n"                
"	ORR	R1, R1, R3, LSL #0x10 \n"            
"	LDRB	R3, [R4, #0x1C7] \n"                
"	LDRB	R2, [R4, #0x1BE] \n"                
//"	LDRB	LR, [R4, #0x1FF] \n"  		// replaced, see below               
"	ORR	R1, R1, R3, LSL #8 \n"               
"	LDRB	R3, [R4, #0x1C6] \n"                
"	CMP	R2, #0 \n"                           
"	CMPNE	R2, #0x80 \n"                      
"	ORR	R1, R1, R3 \n"                       
"	LDRB	R3, [R4, #0x1CD] \n"                
"	MOV	R3, R3, LSL #0x18 \n"                
"	ORR	R3, R3, R12, LSL #0x10 \n"           
"	LDRB	R12, [R4, #0x1CB] \n"               
"	ORR	R3, R3, R12, LSL #8 \n"              
"	LDRB	R12, [R4, #0x1CA] \n"               
"	ORR	R3, R3, R12 \n"  
//"	LDRB	R12, [R4, #0x1FE] \n"    	// replaced, see below 

"	LDRB    R12, [LR,#0x1FE]\n"			// New! First MBR signature byte (0x55)
"	LDRB    LR, [LR,#0x1FF]\n"			//      Last MBR signature byte (0xAA)	
          
"	MOV	R4, #0 \n"                           
"	BNE	loc_FF8598EC \n"                     
"	CMP	R0, R1 \n"                           
"	BCC	loc_FF8598EC \n"                     
"	ADD	R2, R1, R3 \n"                       
"	CMP	R2, R0 \n"                           
"	CMPLS	R12, #0x55 \n"                     
"	CMPEQ	LR, #0xAA \n"                      
"	MOVEQ	R6, R1 \n"                         
"	MOVEQ	R5, R3 \n"                         
"	MOVEQ	R4, #1 \n"                         
"loc_FF8598EC:\n"
"	MOV	R0, #2 \n"                           
"	BL	sub_FF872160 \n"                      
"	CMP	R4, #0 \n"                           
"	BNE	loc_FF859924 \n"                     
"	MOV	R6, #0 \n"                           
"	MOV	R0, R8 \n"                           
"	BL	sub_FF92AC04 \n"                      
"	MOV	R5, R0 \n"                           
"	B	loc_FF859924 \n"                       
"loc_FF859910:\n"
"	MOV	R5, #0x40 \n"                        
"	B	loc_FF859924 \n"                       
"loc_FF859918:\n"
"	LDR	R1, =0x37A \n"                       
"	LDR	R0, =0xFF8597C0 \n"                  
"	BL	sub_FF81B1CC \n"                      
"loc_FF859924:\n"
"	STR	R6, [R7, #0x44]! \n"                 
"	MOV	R0, #1 \n"                           
"	STR	R5, [R7, #4] \n"                     
"	LDMFD	SP!,{R4-R8,PC} \n"                                      
	);
}

//  JogDial_task_my - 0xFF84B23C

void __attribute__((naked,noinline)) JogDial_task_my(  ) {
asm volatile (
"	STMFD	SP!, {R3-R11,LR} \n"               
"	BL	sub_FF84B3EC \n"                      
"	LDR	R11, =0x80000B01 \n"                 
"	LDR	R8, =0xFFB0FAB0 \n"      //* firmware difference            
"	LDR	R7, =0xC0240000 \n"                  
"	LDR	R6, =0x25F0 \n"                      
"	MOV	R9, #1 \n"                           
"	MOV	R10, #0 \n"                          
"loc_FF84B25C:\n"
"	LDR	R3, =0x1AE \n"                       
"	LDR	R0, [R6, #0xC] \n"                   
"	LDR	R2, =0xFF84B494 \n"                  
"	MOV	R1, #0 \n"                           
"	BL	sub_FF82862C \n"                      
"	MOV	R0, #0x28 \n"                        
"	BL	sub_FF828484 \n"                      
//------------------  added code ---------------------
"sleep_loop:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     sleep_done\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n"
                "B       sleep_loop\n"
"sleep_done:\n"
//------------------  original code ------------------

"	LDR	R0, [R7, #0x104] \n"                 
"	MOV	R0, R0, ASR #0x10 \n"                
"	STRH	R0, [R6] \n"                        
"	LDRSH	R2, [R6, #2] \n"                   
"	SUB	R1, R0, R2 \n"                       
"	CMP	R1, #0 \n"                           
"	BEQ	loc_FF84B320 \n"                     
"	MOV	R5, R1 \n"                           
"	RSBLT	R5, R5, #0 \n"                     
"	MOVLE	R4, #0 \n"                         
"	MOVGT	R4, #1 \n"                         
"	CMP	R5, #0xFF \n"                        
"	BLS	loc_FF84B2D4 \n"                     
"	CMP	R1, #0 \n"                           
"	RSBLE	R1, R2, #0xFF \n"                  
"	ADDLE	R1, R1, #0x7F00 \n"                
"	ADDLE	R0, R1, R0 \n"                     
"	RSBGT	R0, R0, #0xFF \n"                  
"	ADDGT	R0, R0, #0x7F00 \n"                
"	ADDGT	R0, R0, R2 \n"                     
"	ADD	R5, R0, #0x8000 \n"                  
"	ADD	R5, R5, #1 \n"                       
"	EOR	R4, R4, #1 \n"                       
"loc_FF84B2D4:\n"
"	LDR	R0, [R6, #0x14] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF84B318 \n"                     
"	LDR	R0, [R6, #0x1C] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF84B300 \n"                     
"	LDR	R1, [R8, R4, LSL #2] \n"             
"	CMP	R1, R0 \n"                           
"	BEQ	loc_FF84B308 \n"                     
"	LDR	R0, =0xB01 \n"                       
"	BL	sub_FF87EC00 \n"                      
"loc_FF84B300:\n"
"	MOV	R0, R11 \n"                          
"	BL	sub_FF87EC00 \n"                      
"loc_FF84B308:\n"
"	LDR	R0, [R8, R4, LSL #2] \n"             
"	MOV	R1, R5 \n"                           
"	STR	R0, [R6, #0x1C] \n"                  
"	BL	sub_FF87EB30 \n"                      
"loc_FF84B318:\n"
"	LDRH	R0, [R6] \n"                        
"	STRH	R0, [R6, #2] \n"                    
"loc_FF84B320:\n"
"	STR	R10, [R7, #0x100] \n"                
"	STR	R9, [R7, #0x108] \n"                 
"	LDR	R0, [R6, #0x10] \n"                  
"	CMP	R0, #0 \n"                           
"	BLNE	sub_FF828484 \n"                    
"	B	loc_FF84B25C \n"                       
	);
}
