#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);


void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();


#if 0
void blink_blue(int duration)
{
  int i;

  *((volatile long *) 0xc0220084) = 0x46; // Turn on LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }   
   
  *((volatile long *) 0xc0220084) = 0x44; // Turn off LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }
}

void blink_orange(int duration) //
{
  int i;

  *((volatile long *) 0xc0220090) = 0x46; // Turn on LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }   
   
  *((volatile long *) 0xc0220090) = 0x44; // Turn off LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }
}

void blink()
{
    blink_blue(10000000);
    blink_orange(10000000);
    blink_blue(10000000);
}
#endif

void boot()
{
    long *canon_data_src = (void*)0xFFE8A3C0; //
    long *canon_data_dst = (void*)MEMBASEADDR;
    long *canon_bss_start = (void*)0x11010; // just after data
    long canon_data_len = 0x11010 - MEMBASEADDR; //
    long canon_bss_len = MEMISOSTART - 0x11010; //
    long i;

    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    h_usrInit();
}


void h_usrInit()
{
    asm volatile ( //@ffc019e0
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FFC019BC\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFE6E024\n"     //unknown_libname_773 ; "Canon A-Series Firmware"
	"BL      sub_FFE5A6FC\n"     //excVecInit
	"BL      sub_FFC01218\n"
	"BL      sub_FFC0177C\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}//

void  h_usrKernelInit()
{
//    blink();
    asm volatile ( //@ffc01798
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFE6E524\n"    //classLibInit
	"BL      sub_FFE83810\n"    //taskLibInit
	"LDR     R3, =0xFFA4\n"
	"LDR     R2, =0x9B540\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x9EE30\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFE7C660\n"   //qInit
	"LDR     R3, =0xFF64\n"
	"LDR     R0, =0x1082C\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFE7C660\n"   //qInit
	"LDR     R3, =0x10020\n"
	"LDR     R0, =0x9EE04\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFE7C660\n"   //qInit
	"BL      sub_FFE88390\n"   //workQInit
	"BL      sub_FFC01304\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
    );
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFE80A50\n"  //kernelInit
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );
}


void  h_usrRoot()
{
    asm volatile ( //@ffc01ac0
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FFC01A24\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFE746A0\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFE75118\n"
	"BL      sub_FFC0183C\n"
	"BL      sub_FFC01758\n"
	"MOV     R0, #50\n"
	"BL      sub_FFE770BC\n"
	"BL      sub_FFC01A68\n"
	"BL      sub_FFC01A48\n"
	"BL      sub_FFC01A94\n"
	"BL      sub_FFE7697C\n"
	"BL      sub_FFC01A18\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();
    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FFC013C0\n"
    );
}//
