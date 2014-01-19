/*
Arm cache control functions
TODO
Only valid on processors with cp15 (e.g. not s1)
*/

/*
get cache config word
*/
void __attribute__((naked,noinline)) cache_get_config(void) {
  asm volatile (
    "MRC    p15, 0, R0,c0,c0,1\n"
    "BX     LR\n"
  );
}

/*
get dcache size from word returned by get_config
*/
unsigned dcache_get_size(unsigned config) {
    unsigned sz = (config>>18) & 0xF;
    // shouldn't happen, s1 might not have cache but also doesn't have cp15
    if(sz == 0) {
        return 0;
    }
    // per ARM DDI 0201D Table 2-5 Cache size encoding
    // starts at 4kb = 3, each subsequent value is 2x
    return 0x200 << sz;
}

/*
flush (mark as invalid) entire instruction cache
*/
void __attribute__((naked,noinline)) icache_flush_all(void) {
  asm volatile (
    "MOV    r1, #0\n"
    "MCR    p15, 0, r1,c7,c5\n"
    "BX     LR\n"
  );
}

/*
clean (write all dirty) entire data cache
also drains write buffer (like canon code)
does *not* flush
*/
void __attribute__((naked,noinline)) dcache_clean_all(void) {
  asm volatile (
    "PUSH   {LR}\n"
    "BL     cache_get_config\n"
    "BL     dcache_get_size\n"
    "CMP    r0, #0\n"
    "BEQ    3f\n"
    // index limit (max index+1)
    // per ARM DDI 0201D 4kb = bits 9:5
    "LSR    r3, r0, #2\n" 
    "MOV    r1, #0\n"
"2:\n"
    "MOV    r0, #0\n"
"1:\n"
    "ORR    r2,r1,r0\n"
    "MCR    p15, 0, r2, c7, c10, 2\n" // clean line
    "ADD    r0, r0, #0x20\n" // next line
    "CMP    r0, r3\n" // segment complete ?
    "BNE    1b\n"
    "ADD    r1, r1,#0x40000000\n" // next segment
    "CMP    r1, #0\n"
    "BNE    2b\n"
    "MCR    p15, 0, r1, c7, c10, 4\n" // drain write buffer
"3:\n"
    "POP    {LR}\n"
    "BX     LR\n"
  );
}
