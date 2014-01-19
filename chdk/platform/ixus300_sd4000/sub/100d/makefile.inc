#0x31F7
PLATFORMID=12791

PLATFORMOS=dryos

    
MEMISOSTART=0x14B394    # ROM:FF81014C
ROMBASEADDR=0xFF810000    # 0xFF810000 for S-, SD-, and G- series

# EXMEM
# http://chdk.setepontos.com/index.php?topic=5980.msg63834#msg63834
# 128MB RAM (0x80000000)
# s: 7bfffe0 e: 7ffffe0 f: 7d08a00 l: 7ff1efc c: 748800
MAXRAMADDR=0x7ffffff    # ROM:FF88A424 0x48000000 - CAM_UNCACHED_BIT 0x40000000 = 0x80000000 - 1
EXMEM_BUFFER_SIZE=0x400000    # Amount of EXMEM memory to allocate for CHDK = 4MB
#EXMEM_BUFFER_SIZE=0x200000    # Amount of EXMEM memory to allocate for CHDK = 2MB
EXMEM_HEAP_SKIP=0x2F7600   # 0x8000000 (RAM) - 0x07D08A00 (Video Buffer Size) ~ 3MB

# type of diskboot encoding: undefined = none; 1 = original; 2 = sx200, d10; 3 = ixus200...
# Dancing Bits
NEED_ENCODED_DISKBOOT=4

# FIR (requires correct keys in platform/fi2.inc)
# FI2KEY: ROM:FFFF366C , Offset: 0x7E366C
# FI2IV: ROM:FFC15130 , Offset: 0x405130
KEYSYS=d4a

PLATFORMOSVER=43
