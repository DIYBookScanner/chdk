#override OPT_EXMEM_MALLOC=1
#override OPT_CHDK_IN_EXMEM=1

# 0x3244 Found @ 0xfff40040
PLATFORMID=12869

PLATFORMOS=dryos

# size of memory region for CHDK
RESTARTSTART=0x50000

# points to the start of the memory pool used by the firmware
ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0xF8E67E0  # MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else
MEMISOSTART=0x193A24   # found @ 0xff00016f
endif

# start of firmware
ROMBASEADDR=0xFF000000

MAXRAMADDR = 0x0fffffff
EXMEM_BUFFER_SIZE=0xA0000  # now 654KB, 80000=512KB, A0000 =654KB, C0000=768KB, 100000=1MB
EXMEM_HEAP_SKIP=0x679800  # 0x50000000 - 0x4F986800  @FF07B064 - @FF07B068

# Found @ 0xffff3cf0
NEED_ENCODED_DISKBOOT=8

# Found @ 0xffff3ce0
KEYSYS=d4c

PLATFORMOSVER=50
