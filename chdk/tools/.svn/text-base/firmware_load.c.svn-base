
// Firmware file handling for Canon camera firmware dumps
// Note: only supports DryOS based cameras and ARM32 code.
//       the cameras operate in little endian mode, this code assumes it will
//       be compiled and run on a little endian CPU.
//       It won't work on anything else.

//------------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "dancingbits.h"
#include "stubs_load.h"
#include "firmware_load.h"

//------------------------------------------------------------------------------------------------------------

// These must be supplied elsewhere
extern void error(char*, int);
extern void usage(char *err);

//------------------------------------------------------------------------------------------------------------

// Firmware handling

// Currently used by:
//      finsig_dryos.c for generating stubs_entry.S
//      code_gen.c for generating CHDK source code

// The firmware dump is loaded into an array of 'uint32_t' 32 bit unsigned integer values
// this simpifies the access and analysis of the data (all ARM32 instructions are 32 bits long and 32 bit aligned)

// The functions that analyse the firmware work with either memory addresses (uint32_t) or indexes (int)
// The indexes are to the memory array where the firmware is loaded.
// So for a firmware that loads at address 0xFF810000, the index of this instruction in the array will be 0.
// The index for 0xFF810004 = 1, etc.

// Functions take a pointer to a 'firmware' structure as the first parameter and operate on the contents
// of this structure. Can be used to load and compare multiple dumps.

//------------------------------------------------------------------------------------------------------------

// Most firmware dumps contain large blocks that have a value of only 0xFFFFFFFF.
// The BufRange structure and list stores the valid ranges so these empty blocks can be skipped when
// searching for stuff.

// Add a valid range to the list
void addBufRange(firmware *fw, int o, int l)
{
    BufRange *n = malloc(sizeof(BufRange));
    n->p = fw->buf + o;
    n->off = o;
    n->len = l;
    n->next = 0;
    if (fw->br == 0)
    {
        fw->br = n;
    }
    else
    {
        fw->last->next = n;
    }
    fw->last = n;
}

// Find valid ranges for the firmware dump
void findRanges(firmware *fw)
{
    int i, j, k;

    // Find all the valid ranges for checking (skips over large blocks of 0xFFFFFFFF)
    fw->br = 0; fw->last = 0;
    k = -1; j = 0;
    for (i = 0; i < fw->size; i++)
    {
        if (fw->buf[i] == 0xFFFFFFFF)   // Possible start of block to skip
        {
            if (k == -1)            // Mark start of possible skip block
            {
                k = i;
            }
        }
        else                        // Found end of block ?
        {
            if (k != -1)
            {
                if (i - k > 32)     // If block more than 32 words then we want to skip it
                {
                    if (k - j > 8)
                    {
                        // Add a range record for the previous valid range (ignore short ranges)
                        addBufRange(fw,j,k - j);
                    }
                    j = i;          // Reset valid range start to current position
                }
                k = -1;             // Reset marker for skip block
            }
        }
    }
    // Add range for last valid block
    if (k != -1)
    {
        if (k - j > 8)
        {
            addBufRange(fw,j,k - j);
        }
    }
    else
    {
        if (i - j > 8)
        {
            addBufRange(fw,j,i - j);
        }
    }
}

//------------------------------------------------------------------------------------------------------------

// Check if the supplied index 'i' is valid for the firmware dump
// Takes into account cameras with 'alternate' firmware base addresses (S110)
// and those that copy a block of the firmware code to RAM (DryOS 50 and up)

// Assumptions
//  The 'alternate' copy of the firmware is loaded at a higher address than the base copy
//      e.g. base address = 0xF8000000, alt address = 0xFF000000
//          --> i > fw->size
//  The firmware is always loaded at a memory address higher than the RAM that code is
//  copied to.
//          --> i < 0

int idx_valid(firmware *fw, int i)
{
    if ((i >= 0) && (i < fw->size))
        return 1;
    if ((fw->dryos_ver >= 51) && (fw->alt_base) && (i >= fw->size))
    {
        i = ((i * 4) - (fw->alt_base - fw->base)) / 4;
        if ((i >= 0) && (i < fw->size))
            return 1;
    }
    if (fw->dryos_ver >= 50)
    {
        i = ((i * 4) + (fw->base - fw->base2)) / 4;
        if ((i >= 0) && (i < fw->size2))
            return 1;
    }
    return 0;
}

// Convert an instruction index to a memory address (see above regarding RAM and 'alternate' values)
uint32_t idx2adr(firmware *fw, int idx)
{
    return fw->base + (idx << 2);
}

// Convert a memory address to an instruction index (see above regarding RAM and 'alternate' values)
int adr2idx(firmware *fw, uint32_t adr)
{
    if (adr < fw->base)
        return -((fw->base - adr) >> 2);
    else
        return (adr - fw->base) >> 2;
}

// Convert a memory address to a pointer into the firmware memory buffer
char* adr2ptr(firmware *fw, uint32_t adr)
{
    return ((char*)fw->buf) + (adr - fw->base);
}

//------------------------------------------------------------------------------------------------------------

static int ignore_errors = 0;

void set_ignore_errors(int n)
{
    ignore_errors = n;
}

// These functions should be used to get data & instructions in the firmware dump
// This will ensure that everything works correctly for code / data referenced in RAM
// or the 'alternate' base address for the firmware.

// Return a pointer to the instruction/data in the memory array at the specified index
// Takes care of converting RAM and 'alternate' indexes and addresses
uint32_t* fwadr(firmware *fw, int i)
{
    if ((i >= 0) && (i < fw->size))
        return &fw->buf[i];
    if ((fw->dryos_ver >= 51) && (fw->alt_base) && (i >= fw->size))
    {
        i = ((i * 4) - (fw->alt_base - fw->base)) / 4;
        if ((i >= 0) && (i < fw->size))
            return &fw->buf[i];
    }
    if ((fw->dryos_ver >= 50) && (i < 0))
    {
        i = ((i * 4) + (fw->base - fw->base2)) / 4;
        if ((i >= 0) && (i < fw->size2))
            return &fw->buf2[i];
    }
    if (ignore_errors)
    {
        return &fw->buf[0];
    }
    fprintf(stderr,"Invalid firmware offset %d.\n",i);
    error("\nInvalid firmware offset %d. Possible corrupt firmware or incorrect start address.\n",i);
    return 0;
}

// Return the instruction / data at the specified index
uint32_t fwval(firmware *fw, int i)
{
    return *fwadr(fw,i);
}

// Return the destination register of the instruction at the specified index
int fwRd(firmware *fw, int i)
{
    // Destination register - Rd
    return (*fwadr(fw,i) & 0x0000F000) >> 12;
}

// Return the source register of the instruction at the specified index
int fwRn(firmware *fw, int i)
{
    // Source register - Rn
    return (*fwadr(fw,i) & 0x000F0000) >> 16;
}

// Return the operand2 value of the instruction at the specified index
int fwOp2(firmware *fw, int i)
{
    // Operand2
    return (*fwadr(fw,i) & 0x00000FFF);
}

//------------------------------------------------------------------------------------------------------------

// decode LDR instruction at offset and return firmware address pointed to
uint32_t LDR2adr(firmware *fw, int offset)
{
    uint32_t inst = fwval(fw,offset);
    int offst = (inst & 0xFFF);
    uint32_t fadr = (inst & 0x00800000)?idx2adr(fw,offset+2)+offst:idx2adr(fw,offset+2)-offst;
    return fadr;
}

// decode LDR instruction at offset and return firmware buffer index of the new address
uint32_t LDR2idx(firmware *fw, int offset)
{
    return adr2idx(fw,LDR2adr(fw,offset));
}

// decode LDR instruction at offset and return firmware value stored at the address
uint32_t LDR2val(firmware *fw, int offset)
{
    return fwval(fw,adr2idx(fw,LDR2adr(fw,offset)));
}

//------------------------------------------------------------------------------------------------------------

// decode ADR instruction at offset and return firmware address pointed to
// NOT COMPLETE
uint32_t ADR2adr(firmware *fw, int offset)
{
    uint32_t inst = fwval(fw,offset);
    int rot = 32 - ((inst & 0xF00) >> 7);
    int offst = (inst & 0xFF) <<rot;
    uint32_t fadr = 0;
    switch (inst & 0x01E00000)
    {
        case 0x00400000:    // SUB
            fadr = idx2adr(fw,offset+2)-offst;
            break;
        case 0x00800000:    // ADD
            fadr = idx2adr(fw,offset+2)+offst;
            break;
        case 0x01A00000:    // MOV
            //fprintf(stderr,"***** ADR2adr MOV\n");
            break;
        case 0x01E00000:    // MVN
            //fprintf(stderr,"***** ADR2adr MVN\n");
            break;
    }
    return fadr;
}

// decode operand2 from ALU inst (not complete!)
uint32_t ALUop2(firmware *fw, int offset)
{
    uint32_t inst = fwval(fw,offset);
    int rot = 32 - ((inst & 0xF00) >> 7);
    int offst = (inst & 0xFF) <<rot;
    uint32_t fadr = 0;
    switch (inst & 0x03E00000)
    {
        case 0x02400000:    // SUB Immed
        case 0x02800000:    // ADD Immed
        case 0x03A00000:    // MOV Immed
        case 0x03C00000:    // BIC Immed
            fadr = offst;
            break;
    }
    return fadr;
}

// decode operand2 from ALU inst (not complete, try2 - based on chdk_dasm code)
uint32_t ALUop2a(firmware *fw, int offset)
{
    uint32_t inst = fwval(fw,offset);
    uint32_t rot = (inst>>7)&0x1e;
    uint32_t imm8 = inst & 0xff;
    uint32_t offst = (imm8>>rot) | (imm8<<(32-rot));
    uint32_t fadr = 0;
    switch (inst & 0x03E00000)
    {
        case 0x02400000:    // SUB Immed
        case 0x02800000:    // ADD Immed
        case 0x03A00000:    // MOV Immed
        case 0x03C00000:    // BIC Immed
            fadr = offst;
            break;
    }
    return fadr;
}

//------------------------------------------------------------------------------------------------------------

// Follow the B / BL / LDR PC instruction at the specified index and return the index of the new location
// Notes:
//      If offset == 0 returns the original index (fidx)
//      The B / BL instruction is at 'fidx + (offset & 0xFFFFFF) - 1'
//      The '(offset & 0xFF000000)' value is a mask that determines instruction matching
//          offset & 0xFF000000 == 0x00000000 --> match B only
//          offset & 0xFF000000 == 0x01000000 --> match B or BL
int idxFollowBranch(firmware *fw, int fidx, int offset)
{
    if (offset)
    {
        uint32_t msk = ~(offset & 0xFF000000);
        fidx += ((offset & 0x00FFFFFF) - 1);
        uint32_t inst = fwval(fw,fidx);
        if ((inst & (0xFF000000&msk)) == (0xEA000000&msk))  // Branch (B or BL depending on msk)
        {
            int o = inst & 0x00FFFFFF;
            if (o & 0x00800000) o |= 0xFF000000;
            fidx = fidx + o + 2;
        }
        else if ((inst & (0xFFFFF000)) == (0xE51FF000))     // LDR PC,=...
        {
            fidx = adr2idx(fw,LDR2val(fw,fidx));
        }
    }
    return fidx;
}

// Follow the B / BL / LDR PC instruction at the specified address and return the address of the new location
// Notes as per above.
uint32_t followBranch(firmware *fw, uint32_t fadr, int offset)
{
    if (offset)
    {
        uint32_t msk = ~(offset & 0xFF000000);
        uint32_t fidx = adr2idx(fw,fadr);  // function index
        fidx += ((offset & 0x00FFFFFF) - 1);
        uint32_t inst = fwval(fw,fidx);
        if ((inst & (0xFF000000&msk)) == (0xEA000000&msk))  // Branch (B or BL depending on msk)
        {
            int o = inst & 0x00FFFFFF;
            if (o & 0x00800000) o |= 0xFF000000;
            if (idx_valid(fw,fidx+o+2))
                fadr = idx2adr(fw,fidx+o+2);
        }
        else if ((inst & (0xFFFFF000)) == (0xE51FF000))     // LDR PC,=...
        {
            fadr = LDR2val(fw,fidx);
        }
    }
    return fadr;
}

// As above; but if offset == 1 then follow any branch at the new location
uint32_t followBranch2(firmware *fw, uint32_t fadr, int offset)
{
    fadr = followBranch(fw, fadr, offset);
    if ((offset & 0x00FFFFFF) == 1)
        fadr = followBranch(fw, fadr, offset);
    return fadr;
}

//------------------------------------------------------------------------------------------------------------

// These functions test the instruction at the supplied 'offset' index to see if they match specific types

// LDR Rx, =...
int isLDR_PC(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFE1F0000) == 0xE41F0000);
}

// LDRnn Rx, =...
int isLDR_PC_cond(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0x0E1F0000) == 0x041F0000);
}

// LDR Rx,[SP,...]
int isLDR_SP(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFFF0000) == 0xE59D0000);
}

// LDR
int isLDR(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFE100000) == 0xE4100000);
}

// LDRnn
int isLDR_cond(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0x0E100000) == 0x04100000);
}

// ADR Rx, value
int isADR_PC(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFE0F0000) == 0xE20F0000);
}

// ADRnn Rx, value
int isADR_PC_cond(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0x0E0F0000) == 0x020F0000);
}

// ADR or MOV
int isADR(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFE000000) == 0xE2000000);
}

// LDMFD
int isLDMFD(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFFF0000) == 0xE8BD0000);
}

// LDMFD SP!, {..., PC}
int isLDMFD_PC(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFFF8000) == 0xE8BD8000);
}

// STMFD SP!,
int isSTMFD(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFFF0000) == 0xE92D0000);
}

// STMFD SP!, {..,LR}
int isSTMFD_LR(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFFF4000) == 0xE92D4000);
}

// STR
int isSTR(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFE100000) == 0xE4000000);
}

// STRnn
int isSTR_cond(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0x0E100000) == 0x04000000);
}

// BX
int isBX(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFFFFFF0) == 0xE12FFF10);
}

// BX
int isBX_cond(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0x0FFFFFF0) == 0x012FFF10);
}

// BX LR
int isBX_LR(firmware *fw, int offset)
{
    return (fwval(fw,offset) == 0xE12FFF1E);
}

// BL
int isBL(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFF000000) == 0xEB000000);
}

// BLxx
int isBL_cond(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0x0F000000) == 0x0B000000);
}

// B
int isB(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFF000000) == 0xEA000000);
}

// B or BL
int isBorBL(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFE000000) == 0xEA000000);
}

// CMP
int isCMP(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFF00000) == 0xE3500000);
}

// MOV
int isMOV(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFF00000) == 0xE1A00000);
}

// MOV Rd, #
int isMOV_immed(firmware *fw, int offset)
{
    return ((fwval(fw,offset) & 0xFFF00000) == 0xE3A00000);
}

//------------------------------------------------------------------------------------------------------------

// Find the index of a string in the firmware
// Assumes the string starts on a 32bit boundary.
int find_str(firmware *fw, char *str)
{
    int nlen = strlen(str);
    uint32_t nm0 = *((uint32_t*)str);
    uint32_t *p;
    int j;

    BufRange *br = fw->br;
    while (br)
    {
        for (p = br->p, j = 0; j < br->len - nlen/4; j++, p++)
        {
            if ((nm0 == *p) && (memcmp(p+1,str+4,nlen-4) == 0))
            {
                return j+br->off;
            }
        }
        br = br->next;
    }

    return -1;
}

// Find the index of a string in the firmware, can start at any address
// returns firmware address, not index
uint32_t find_str_bytes(firmware *fw, char *str)
{
    BufRange *p = fw->br;
    while (p)
    {
        int k;
        for (k = p->off*4; k < (p->off + p->len)*4; k++)
        {
            if (strcmp(((char*)fw->buf)+k,str) == 0)
                return fw->base+k;
        }
        p = p->next;
    }

    return 0;
}

// Find the next instance of the instruction matched by the 'inst' function (from the isXXX functions above)
// Starts searching at 'idx' for a max of 'len' instructions
int find_inst(firmware *fw, int (*inst)(firmware*,int), int idx, int len)
{
    int k;
    for (k = idx; (k < fw->size) && (k < idx + len); k++)
    {
        if (inst(fw, k))
            return k;
    }
    return -1;
}

// Find the previous instance of the instruction matched by the 'inst' function (from the isXXX functions above)
// Starts searching at 'idx' for a max of 'len' instructions
int find_inst_rev(firmware *fw, int (*inst)(firmware*,int), int idx, int len)
{
    int k;
    for (k = idx; (k > 0) && (k > idx - len); k--)
    {
        if (inst(fw, k))
            return k;
    }
    return -1;
}

// Find the Nth instance of the instruction matched by the 'inst' function
// Modified version of find_inst()
int find_Nth_inst(firmware *fw, int (*inst)(firmware*,int), int idx, int len, int N)
{
    int k;
    for (k = idx; (k < fw->size) && (k < idx + len); k++)
    {
        if (inst(fw, k))
            N--;
        if (N <= 0)
            return k;
    }
    return -1;
}

// Find the Nth previous instance of the instruction matched by the 'inst' function
// Modified version of find_inst_rev()
int find_Nth_inst_rev(firmware *fw, int (*inst)(firmware*,int), int idx, int len, int N)
{
    int k;
    for (k = idx; (k > 0) && (k > idx - len); k--)
    {
        if (inst(fw, k))
            N--;
        if (N <= 0)
            return k;
    }
    return -1;
}

//------------------------------------------------------------------------------------------------------------

// Finds the first instance of an instruction that references a pointer to the specified string in the firmware.
//  e.g.
//          LDR R0, =p_str  <-- returns index of this instruction
//  p_str   DCD abcdef
//  abcdef  DCB "abcdef",0
int find_strptr_ref(firmware *fw, char *str)
{
    uint32_t sadr = find_str_bytes(fw, str);    // string address
    if (sadr > 0)
    {
        int k;
        for (k=0; k<fw->size; k++)
        {
            if (fwval(fw,k) == sadr)
            {
                uint32_t fadr = idx2adr(fw,k);  // string pointer address
                int j;
                for (j=0; j<fw->size; j++)
                {
                    if (isADR_PC_cond(fw,j) && (ADR2adr(fw,j) == fadr))
                    {
                        return j;
                    }
                    else if (isLDR_PC_cond(fw,j) && (LDR2val(fw,j) == fadr))
                    {
                        return j;
                    }
                }
            }
        }
    }
    return -1;
}

// Finds the first instance of an instruction that references the specified string in the firmware.
//  e.g.
//          LDR R0, =abcdef     <-- returns index of this instruction
//  abcdef  DCB "abcdef",0
int find_str_ref(firmware *fw, char *str)
{
    int k = find_str(fw, str);
    if (k >= 0)
    {
        uint32_t sadr = idx2adr(fw,k);        // string address
        for (k=0; k<fw->size; k++)
        {
            if (isADR_PC_cond(fw,k) && (ADR2adr(fw,k) == sadr))
            {
                return k;
            }
            else if (isLDR_PC_cond(fw,k) && (LDR2val(fw,k) == sadr))
            {
                return k;
            }
        }
    }
    return -1;
}

// Finds the next reference to a string
int find_nxt_str_ref(firmware *fw, int str_adr, int ofst)
{
    if (str_adr >= 0)
    {
        int k;
        uint32_t sadr = idx2adr(fw,str_adr);        // string address
        for (k=ofst+1; k<fw->size; k++)
        {
            if (isADR_PC_cond(fw,k) && (ADR2adr(fw,k) == sadr))
            {
                return k;
            }
            else if (isLDR_PC_cond(fw,k) && (LDR2val(fw,k) == sadr))
            {
                return k;
            }
        }
    }
    return -1;
}

//------------------------------------------------------------------------------------------------------------

// Checks if the instruction at index 'k' is a BL to address 'v1'
// Used with the 'search_fw' below
int find_BL(firmware *fw, int k, uint32_t v1, uint32_t v2)
{
    if (isBL(fw,k))
    {
        int n = idxFollowBranch(fw, k, 0x01000001);
        if (n == v1)
            return k;
    }
    return 0;
}

// Checks if the instruction at index 'k' is a BL to address 'v1'
// Used with the 'search_fw' below
int find_B(firmware *fw, int k, uint32_t v1, uint32_t v2)
{
    if (isB(fw,k))
    {
        int n = idxFollowBranch(fw, k, 0x00000001);
        if (n == v1)
            return k;
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------

// Search the firmware for something. The desired matching is performed using the supplied 'func' function.
// Continues searching until 'func' returns non-zero - then returns the value returned by 'func'
// otherwise returns 0.
// Uses the BufRange structs to speed up searching
int search_fw(firmware *fw, int (*func)(firmware*, int, uint32_t, uint32_t), uint32_t v1, uint32_t v2, int len)
{
    BufRange *p = fw->br;
    while (p)
    {
        int k;
        for (k = p->off; k <= p->off + p->len - len; k++)
        {
            int rv = func(fw,k,v1,v2);
            if (rv != 0)
                return rv;
        }
        p = p->next;
    }
    return 0;
}

// Search the firmware for something. The desired matching is performed using the supplied 'func' function.
// Continues searching until 'func' returns non-zero - then returns 1
// otherwise returns 0.
// Uses the BufRange structs to speed up searching
// Note: this version searches byte by byte in the firmware dump instead of by words
int search_fw_bytes(firmware *fw, int (*func)(firmware*, int))
{
    BufRange *p = fw->br;
    while (p)
    {
        int k;
        for (k = p->off*4; k < (p->off + p->len)*4; k++)
        {
            if (func(fw,k))
                return 1;
        }
        p = p->next;
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------

// Load the named firmware file, using the supplied base and alternate base addresses
// Once loaded searches the firmware for information
void load_firmware(firmware *fw, const char *filename, const char *base_addr, const char *alt_base_addr, int os_type)
{
    // Open file.
    FILE *f = fopen(filename, "rb");
    int i, j, k;

    if (f == NULL)
    {
        fprintf(stderr,"Error opening %s\n",filename);
        usage("firmware open");
    }

    fw->os_type = os_type;

    // File length
    fseek(f,0,SEEK_END);
    fw->size = (ftell(f)+3)/4;
    fseek(f,0,SEEK_SET);

    // Save base addresses
    fw->base = strtoul(base_addr, NULL, 0);
    if (alt_base_addr)
        fw->alt_base = strtoul(alt_base_addr, NULL, 0);
    else
        fw->alt_base = 0;

    // Max (old) sig size is 32, add extra space at end of buffer and fill with 0xFFFFFFFF
    // Allows sig matching past end of firmware without checking each time in the inner loop
    fw->buf = malloc((fw->size+32)*4);
    k = fread(fw->buf, 4, fw->size, f);
    fclose(f);

    // fill extra space in buffer
    memset(&fw->buf[fw->size],0xff,32*4);

    // Find all the valid ranges for checking (skips over large blocks of 0xFFFFFFFF)
    findRanges(fw);

    // Get DRYOS version
    fw->dryos_ver = 0;
    if (os_type == OS_DRYOS)
    {
        k = find_str(fw, "DRYOS version 2.3, release #");
        if (k != -1)
        {
            fw->dryos_ver = atoi(((char*)&fw->buf[k])+28);
            fw->dryos_ver_str = (char*)&fw->buf[k];
        }
    }

    // Get firmware version info
    fw->firmware_ver_str = 0;
    k = find_str(fw, "Firmware Ver ");
    if (os_type == OS_VXWORKS)
    {
        if (k < 0)
        {
            k = find_str(fw, "Firmware Version GM");    // ixus700
        }
        if (k < 0)
        {
            k = find_str(fw, "Firmware Version ");      // ixus30/40
        }
    }
    if (k != -1)
    {
        fw->firmware_ver_str = (char*)&fw->buf[k];
        fw->fwver_idx = k;
    }

    // Get camera name & platformid     ***** UPDATE for new each new DryOS version *****
    fw->fsize = -((int)fw->base)/4;
    if (fw->alt_base) fw->fsize = -((int)fw->alt_base)/4;
    fw->cam_idx = -1;
    fw->pid_adr = 0xffffffff;
    fw->cam = 0;
    fw->pid = 0;
    if (os_type == OS_DRYOS)
    {
        switch (fw->dryos_ver)
        {
            case 20:
            case 23:
            case 31:
            case 39:
                fw->cam_idx = adr2idx(fw,0xFFFE0110);
                fw->pid_adr = 0xFFFE0130;
                break;
            case 43:
            case 45:
                fw->cam_idx = adr2idx(fw,0xFFFE00D0);
                fw->pid_adr = 0xFFFE0130;
                break;
            case 47:
                fw->cam_idx = adr2idx(fw,(fw->base==0xFF000000)?0xFFF40170:0xFFFE0170);
                fw->pid_adr = (fw->base==0xFF000000)?0xFFF40040:0xFFFE0040;
                break;
            case 49:
            case 50:
            case 51:
            case 52:
                if (fw->alt_base)
                {
                    fw->cam_idx = adr2idx(fw,(fw->alt_base==0xFF000000)?0xFFF40190:0xFFFE0170);
                    fw->pid_adr = (fw->alt_base==0xFF000000)?0xFFF40040:0xFFFE0040;
                    if (idx_valid(fw,fw->cam_idx) && (strncmp((char*)fwadr(fw,fw->cam_idx),"Canon ",6) != 0))
                        fw->cam_idx = adr2idx(fw,(fw->alt_base==0xFF000000)?0xFFF40170:0xFFFE0170);
                }
                else
                {
                    fw->cam_idx = adr2idx(fw,(fw->base==0xFF000000)?0xFFF40190:0xFFFE0170);
                    fw->pid_adr = (fw->base==0xFF000000)?0xFFF40040:0xFFFE0040;
                    if (idx_valid(fw,fw->cam_idx) && (strncmp((char*)fwadr(fw,fw->cam_idx),"Canon ",6) != 0))
                        fw->cam_idx = adr2idx(fw,(fw->base==0xFF000000)?0xFFF40170:0xFFFE0170);
                }
                break;
        }
    }
    else
    {
        //                             IXUS 700    IXUS 30/40  IXUS 50     Other
        uint32_t vx_name_offsets[] = { 0xFFD70110, 0xFFD70120, 0xFFF80110, 0xFFFE0110 };
        uint32_t vx_pid_offsets[] =  { 0xFFD70130, 0xFFD7014E, 0xFFF80130, 0xFFFE0130 };
        for (i=0; i<sizeof(vx_name_offsets)/sizeof(vx_name_offsets[0]); i++)
        {
            int k = adr2idx(fw,vx_name_offsets[i]);
            if (idx_valid(fw,k) && (strncmp((char*)fwadr(fw,k),"Canon ",6) == 0))
            {
                fw->cam_idx = k;
                fw->pid_adr = vx_pid_offsets[i];
                break;
            }
        }
    }

    // Extact camera name if found
    if (idx_valid(fw,fw->cam_idx) && (strncmp((char*)fwadr(fw,fw->cam_idx),"Canon ",6) == 0))
    {
        fw->cam = (char*)fwadr(fw,fw->cam_idx);
    }

    // Set ID if found
    if (idx_valid(fw,adr2idx(fw,fw->pid_adr)) && (fw->pid_adr != 0xffffffff))
    {
        // get the correct halfword
        fw->pid = (fwval(fw,adr2idx(fw,fw->pid_adr)) >> ((fw->pid_adr & 2)?16:0)) & 0xFFFF;
    }

    // Calc MAXRAMADDR
    fw->maxram = 0;
    if (os_type == OS_DRYOS)
    {
        if (((fw->buf[0x10] & 0xFFFFFF00) == 0xE3A00000) && (fw->buf[0x11] == 0xEE060F12))
        {
            fw->maxram = (1 << (((fw->buf[0x10] & 0x3E) >> 1) + 1)) - 1;
        }
        else if (((fw->buf[0x14] & 0xFFFFFF00) == 0xE3A00000) && (fw->buf[0x15] == 0xEE060F12))
        {
            fw->maxram = (1 << (((fw->buf[0x14] & 0x3E) >> 1) + 1)) - 1;
        }
    }
    else if (os_type == OS_VXWORKS)
    {
        for (k=16; k<100; k++)
        {
            if ((fw->buf[k] & 0xFFFF0FFF) == 0xEE060F12) // mcr 15, 0, rx, cr6, cr2, {0}
            {
                fw->maxram = (1 << (((fw->buf[k-1] & 0x3E) >> 1) + 1)) - 1;
                break;
            }
        }
    }

    // Find MEMISOSTART
    fw->memisostart = 0;
    if (os_type == OS_DRYOS)
    {
        for (k=0; k<100; k++)
        {
            if (isLDR_PC(fw,k) && (LDR2val(fw,k) == 0x1900) && isLDR_PC(fw,k+6))
            {
                fw->memisostart = LDR2val(fw,k+6);
            }
        }
    }
    else if (os_type == OS_VXWORKS)
    {
        for (k=16; k<100; k++)
        {
            if (isMOV_immed(fw,k) && (ALUop2(fw,k) == 0x1900) && isLDR_PC(fw,k+11))
            {
                fw->memisostart = LDR2val(fw,k+11);
                // Find DATA section info
                if (isLDR_PC(fw,k-1) && isLDR_PC(fw,k-4) && ((fwval(fw,k-2) & 0xFFF0FFF0) == 0xE1500000))
                {
                    uint32_t fadr = LDR2val(fw,k-1);
                    uint32_t dadr = 0x1900;
                    uint32_t eadr = LDR2val(fw,k-4);
                    if ((fadr > fw->base) && (dadr < fw->base))
                    {
                        fw->data_start = dadr;
                        fw->data_init_start = fadr;
                        fw->data_len = eadr / 4;
                    }
                }
                break;
            }
            else if (isMOV_immed(fw,k) && (ALUop2(fw,k) == 0x1900) && isLDR_PC(fw,k-2) && isLDR_PC(fw,k-3))
            {
                // special case ixus30/40
                fw->maxram = 0x1FFFFFF; // 32MB, difficult to find
                fw->memisostart = 0x1900 + LDR2val(fw,k-3);
                // Find DATA section info
                fw->data_init_start = LDR2val(fw,k-2);
                fw->data_start = 0x1900;
                j = idxFollowBranch(fw, k+6, 1);
                if (j != k+6)
                {
                    k = idxFollowBranch(fw, j+1, 0x01000001);
                    if (k != j+1)
                    {
                        if ( isLDR_PC(fw,k+3) )
                        {
                            uint32_t eadr = LDR2val(fw,k+3);
                            if ( (eadr>0x1000) && (eadr< fw->memisostart - 0x1900) )
                            {
                                fw->data_len = (eadr - 0x1900) / 4;
                            }
                        }
                    }
                }
                break;
            }
            else if (isMOV_immed(fw,k) && (ALUop2(fw,k) == 0x1900) && isLDR_PC(fw,k-2) &&
                        ((fwval(fw,k-1) & 0xFFFF0F00) == 0xE50B0000) && isLDR_PC(fw,k+28) && isLDR_PC(fw,k+4)
                    )
            {
                // special case ixusW
                fw->memisostart = LDR2val(fw,k+28);
                // Find DATA section info
                fw->data_init_start = LDR2val(fw,k-2);
                fw->data_start = 0x1900;
                fw->data_len = (LDR2val(fw,k+4) - 0x1900) / 4;
                break;
            }
        }
    }

    // Find encryption key & dancing bits
    fw->ksys_idx = 0;
    fw->ksys = 0;
    fw->dancing_bits_idx = 0;
    fw->dancing_bits = 0;
    if (os_type == OS_DRYOS)
    {
        uint32_t ofst = adr2idx(fw,0xFFFF0000);    // Offset of area to find dancing bits
        if (idx_valid(fw,ofst) && isB(fw,ofst) && isLDR_PC(fw,ofst+1))
        {
            // Get KEYSYS value
            ofst = adr2idx(fw,LDR2val(fw,ofst+1));     // Address of firmware encryption key
            if (idx_valid(fw,ofst))
            {
                fw->ksys_idx = ofst;
                fw->ksys = "? Not found, possible new firmware encryption key.";
                switch (fwval(fw,ofst))
                {
                    // Note: only check first word of key (assumes Canon won't release a new key with the same initial value as an existing one)
                    // (Avoid storing full encryption key in this source code).
                    case 0x70726964:    fw->ksys = "d3   "; break;
                    case 0x646C726F:    fw->ksys = "d3enc"; break;
                    case 0x774D450B:    fw->ksys = "d4   "; break;
                    case 0x80751A95:    fw->ksys = "d4a  "; break;
                    case 0x76894368:    fw->ksys = "d4b  "; break;
                    case 0x50838EF7:    fw->ksys = "d4c  "; break;
                    case 0xCCE4D2E6:    fw->ksys = "d4d  "; break;
                }
            }

            // Get NEED_ENCODED_DISKBOOT value
            ofst = ofst + 4; // Address of dancing bits data (try after firmware key)
            if (idx_valid(fw,ofst))
            {
                for (i=0; i<VITALY && !fw->dancing_bits; i++)
                {
                    fw->dancing_bits = i+1;
                    for (j=0; j<8 && fw->dancing_bits; j++)
                    {
                        if ((fwval(fw,ofst+j) & 0xFF) != _chr_[i][j])
                        {
                            fw->dancing_bits = 0;
                        }
                    }
                }
                if (!fw->dancing_bits)
                {
                    // Try before firmware key
                    ofst = ofst - 12;
                    for (i=0; i<VITALY && !fw->dancing_bits; i++)
                    {
                        fw->dancing_bits = i+1;
                        for (j=0; j<8 && fw->dancing_bits; j++)
                        {
                            if ((fwval(fw,ofst+j) & 0xFF) != _chr_[i][j])
                            {
                                fw->dancing_bits = 0;
                            }
                        }
                    }
                }
                if (fw->dancing_bits != 0)
                {
                    // Make sure LoadBootFile actually fails on files that are not encoded
                    // E.G. G9 - will load and run an un-encoded DISKBOOT.BIN file
                    int need_dance = 1;
                    for (k = ofst; (k>adr2idx(fw,0xFFFF0000)) && need_dance; k--)
                    {
                        if (isLDR_PC(fw,k) && (LDR2val(fw,k) == idx2adr(fw,ofst)))
                        {
                            j = find_inst_rev(fw,isSTMFD_LR,k-1,10);
                            if (j >= 0)
                            {
                                uint32_t fadr = idx2adr(fw,j);
                                for (i=j-200; i<j+200 && need_dance; i++)
                                {
                                    if (isB(fw,i))
                                    {
                                        uint32_t badr = followBranch(fw,idx2adr(fw,i),1);
                                        if (badr == fadr)
                                        {
                                            int l;
                                            for (l=i-1; l>i-50; l--)
                                            {
                                                if (isLDR(fw,l) && isCMP(fw,l+1) && isBX_cond(fw,l+2))
                                                {
                                                    need_dance = 0;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (need_dance)
                        fw->dancing_bits_idx = ofst;
                    else
                        fw->dancing_bits = 0;
                }
            }
        }
    }

    int dx = 3;

    // DryOS R50/R51/R52 copies a block of ROM to RAM and then uses that copy
    // Need to allow for this in finding addresses
    // Seen on SX260HS
    if (fw->dryos_ver >= 50)
    {
        fw->buf2 = 0;
        fw->base2 = 0;
        fw->size2 = 0;

        // Try and find ROM address copied, and location copied to
        for (i=3; i<100; i++)
        {
            if (isLDR_PC(fw,i) && isLDR_PC(fw,i+1) && (isLDR_PC(fw,i+2)))
            {
                uint32_t fadr = LDR2val(fw,i);
                uint32_t dadr = LDR2val(fw,i+1);
                uint32_t eadr = LDR2val(fw,i+2);
                if ((fadr > fw->base) && (dadr < fw->base))
                {
                    fw->buf2 = &fw->buf[adr2idx(fw,fadr)];
                    fw->base2 = dadr;
                    fw->base_copied = fadr;
                    fw->size2 = (eadr - dadr) / 4;
                    dx = i+3;
                    break;
                }
            }
        }
    }

    // Find DATA section info
    if (os_type == OS_DRYOS)
    {
        for (i=dx; i<100; i++)
        {
            if (isLDR_PC(fw,i) && isLDR_PC(fw,i+1) && (isLDR_PC(fw,i+2)))
            {
                uint32_t fadr = LDR2val(fw,i);
                uint32_t dadr = LDR2val(fw,i+1);
                uint32_t eadr = LDR2val(fw,i+2);
                if ((fadr > fw->base) && (dadr < fw->base))
                {
                    fw->data_start = dadr;
                    fw->data_init_start = fadr;
                    fw->data_len = (eadr - dadr) / 4;
                    break;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------
