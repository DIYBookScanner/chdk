# 0x3240 Found @ 0xfff40040
PLATFORMID=12864

PLATFORMOS=dryos
PLATFORMOSVER=50

#override OPT_EXMEM_MALLOC=1
#override OPT_CHDK_IN_EXMEM=1

EXMEM_BUFFER_SIZE=0xA0000 # Amount of EXMEM memory to allocate for CHDK; 40000=256KB, 80000=512KB, A0000=640kb, C0000=768KB, 100000=1MB
EXMEM_HEAP_SKIP=0x679800  # 0x50000000 - 0x4F986800  size of video buffers in EXMEM area @FF0B1320 - @FF0B1324 ixus240 101a 

# points to the start of the memory pool used by the firmware
ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0x0F8E67E0  # MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else
MEMISOSTART=0x00281D28   # original non-exmem value ixus240
endif

# start of firmware
ROMBASEADDR=0xFF000000

MAXRAMADDR =0x0FFFFFFF

# Found @ 0xffff3cf4
KEYSYS = d4c

# Found @ 0xffff3d04
NEED_ENCODED_DISKBOOT = 8   
