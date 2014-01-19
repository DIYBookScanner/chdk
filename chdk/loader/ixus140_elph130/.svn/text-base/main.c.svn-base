extern long *blob_chdk_core;
extern long blob_chdk_core_size;

#define DEBUG_LED ((volatile int *)0xC0223030) // AF, green not found
#define DELAY 500000

void __attribute__((noreturn)) my_restart() 
{
    // DEBUG: blink led
    /*
    int counter;

    while(1) {
    counter = DELAY; *DEBUG_LED = 0x46;  while (counter--) { asm("nop\n nop\n"); };
    counter = DELAY; *DEBUG_LED = 0x44;  while (counter--) { asm("nop\n nop\n"); };
    }
    */

    long *dst = (long*)MEMISOSTART;
    const long *src = blob_chdk_core;
    long length = (blob_chdk_core_size + 3) >> 2;

    if (src < dst && dst < src + length)
    {
        /* Have to copy backwards */
        src += length;
        dst += length;
        while (length--)  *--dst = *--src;
    }
    else
        while (length--)  *dst++ = *src++;

	// restart function
	// from sub_FF038240 via 0x12345678
    // note, the normal stores to a bunch of MMIOs do not appear to be present
  asm volatile (
	"MRS     R0, CPSR\n"
	"BIC     R0, R0, #0x3F\n"
	"ORR     R0, R0, #0xD3\n"
	"MSR     CPSR, R0\n"

	"MOV     R0, #0x78\n"
	"MCR     p15, 0, R0,c1,c0\n" // disable caches and TCM
	"MOV     R0, #0\n"
	"MCR     p15, 0, R0,c7,c10, 4\n" // drain write buffer
	"MCR     p15, 0, R0,c7,c5\n" // flush instruction cache
	"MCR     p15, 0, R0,c7,c6\n" // flushd data cache
	"MOV     R0, #0x80000006\n"
	"MCR     p15, 0, R0,c9,c1\n" // set data TCM at 0x80000000, 4kb
	"MCR     p15, 0, R0,c9,c1, 1\n" // instruction TCM (DDIO201D says should only write zero as base ...)
	"MRC     p15, 0, R0,c1,c0\n" // read control state
	"ORR     R0, R0, #0x50000\n" // enable both TCM
	"MCR     p15, 0, R0,c1,c0\n"
	"LDR     R0, =0x12345678\n"  // marker value stored in TCM
	"MOV     R1, #0x80000000\n"
	"STR     R0, [R1,#0xFFC]\n"
//	"LDR     R0, =loc_FF000000\n"
	"mov     R0, %0\n"
//	"LDMFD   SP!, {R4,LR}\n"
	"BX      R0\n"
	: : "r"(MEMISOSTART) : "memory","r0","r1","r2","r3","r4");

  while(1);
}

