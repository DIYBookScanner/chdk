#include "lolevel.h"
#include "platform.h"

//
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {

    asm volatile(
        //@0xFF024D94
                "STMFD   SP!, {R1-R7,LR}\n"
                "MOV     R5, #0\n"
            //  "BL      _kbd_read_keys\n"       // replaces kbd_fetch_data()
                "BL      my_kbd_read_keys\n"     // +
                "B       _kbd_p1_f_cont\n"       // continue
    );

    return 0;   // shut up the compiler
}
