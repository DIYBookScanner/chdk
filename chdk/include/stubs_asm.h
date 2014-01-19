// Common definitions for stubs_entry.S and stubs_entry_2.S macros

    .text

#define DEF(n,a) \
    .globl n; n = a

#if defined(OPT_FIRMWARE_PC24_CALL)

#define NHSTUB(name, addr)\
    .globl _##name ;\
    .weak _##name ;\
    _##name = ## addr

#define STUB(addr)\
    .globl sub_ ## addr ;\
    sub_ ## addr = 0x ## addr

#else

#define NHSTUB(name, addr)\
    .globl _##name ;\
    .weak _##name ;\
    _##name: ;\
	ldr  pc, = ## addr

#define STUB(addr)\
    .globl sub_ ## addr ;\
    sub_ ## addr: ;\
	ldr  pc, =0x ## addr

#endif

// Force finsig to ignore firmware version of a function - used when a custom
// version is provided that completely replaces firmware code.
//  e.g. IGNORE(MoveFocusLensToDistance) for a410 - alternate function supplied in focushack.c
#define IGNORE(name)
