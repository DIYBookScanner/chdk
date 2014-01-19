PLATFORMID=12838

# Force EXMEM on for a800 - not enough heap to work in low memory
override OPT_EXMEM_MALLOC=1
override OPT_CHDK_IN_EXMEM=1

PLATFORMOS=dryos

 

# size of memory region for CHDK
RESTARTSTART=0x50000

# Base address 0xFFC00000 for A
ROMBASEADDR=0xFFC00000

# de stubs_entry.S e em 0xFFC66958 (0x12000000 => 0x2000000 - 1)
MAXRAMADDR = 0x01ffffff

EXMEM_BUFFER_SIZE=0xA0000  # 40000=256KB, 80000=512KB, A0000=640kb, C0000=768KB, 100000=1MB - colado de IXUS220
EXMEM_HEAP_SKIP=0
ifdef OPT_CHDK_IN_EXMEM
   MEMISOSTART=0x1F5FFE0  # MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else					#265kb=79467E0, 512kb=79067E0, 640kb=78E67E0
# ROM:FFC0014C (ok)
   MEMISOSTART=0x13A700 #Valor Original
endif

# type of diskboot encoding: undefined = none; 1 = original; 2 = sx200, d10; 3 = ixus200...
# Dancing Bits
NEED_ENCODED_DISKBOOT=6

# FIR (requires correct keys in platform/fi2.inc)
KEYSYS=d4c

PLATFORMOSVER=47
