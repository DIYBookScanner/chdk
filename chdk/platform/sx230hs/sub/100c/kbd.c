#include "lolevel.h"
#include "platform.h"

// 
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
    
	asm volatile(
                "STMFD   SP!, {R1-R5,LR}\n"  
                "MOV     R5, #0\n"					
                "BL      my_kbd_read_keys\n"
                "B       _kbd_p1_f_cont\n"
    );
	
	return 0;
}
