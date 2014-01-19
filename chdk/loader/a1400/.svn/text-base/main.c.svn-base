extern long *blob_chdk_core;
extern long blob_chdk_core_size;

#define DEBUG_LED ((volatile int *)0xC0220120 ) // Green LED
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
    // from sub_ff831200 via 0x12345678
    // note, the normal stores to a bunch of MMIOs do not appear to be present
    asm volatile (
        "MRS     R0, CPSR\n"
        "BIC     R0, R0, #0x3F\n"
        "ORR     R0, R0, #0xD3\n"
        "MSR     CPSR, R0\n"

        "MOV     R0, #0x78 \n"
        "MCR     p15, 0, R0, c1, c0 \n"
        "MOV     R0, #0 \n"
        "MCR     p15, 0, R0, c7, c10, 4 \n"
        "MCR     p15, 0, R0, c7, c5 \n"
        "MCR     p15, 0, R0, c7, c6 \n"
        "MOV     R0, #0x80000006 \n"
        "MCR     p15, 0, R0, c9, c1 \n"
        "MCR     p15, 0, R0, c9, c1, 1 \n"
        "MRC     p15, 0, R0, c1, c0 \n"
        "ORR     R0, R0, #0x50000 \n"
        "MCR     p15, 0, R0, c1, c0 \n"
        "LDR     R0, =0x12345678 \n"  // marker value stored in TCM
        "MOV     R1, #0x80000000 \n"
        "STR     R0, [R1, #0xFFC] \n"
        //"LDR     R0, =0xFF810000 \n"     //original jump-vector
        "MOV     R0, %0\n"              // new jump-vector
        //"LDMFD   SP!, {R4,LR}\n"
        "BX      R0 \n"
	: : "r"(MEMISOSTART) : "memory","r0","r1","r2","r3","r4");

    while(1);
}

