
// Firmware file handling for Canon camera firmware dumps
// Note: only supports DryOS based cameras and ARM32 code.

/*
    General Notes:
        uint32_t values are addresses (as seen in the Camera)
        int values are indexes into the 'buf' array containing the firmware dump
        e.g. for a firmware dump that loads at address 0xFF810000, then
             the 'base' value will be 0xFF810000.
             the corresponding 'index' value is 0.
             address 0xFF810004 has an index of 1, etc.
 
        Access to the firmware dump info should be via tha functions listed, not by
        direct access to the 'buf' array. This ensures that access is correct for
        cameras with and 'alt' base address, and when firmware code is copied to RAM
 */

// Stores a range of valid data in the firmware dump (used to skip over empty blocks)
typedef struct bufrange {
    uint32_t *p;
    int off;
    int len;
    struct bufrange* next;
} BufRange;

#define OS_DRYOS    0
#define OS_VXWORKS  1

// Firmware storage and information
typedef struct {
    uint32_t        *buf;               // Firmware data
    BufRange        *br, *last;         // Valid ranges

    int             os_type;            // 0 = DryOS, 1 = VxWorks

    uint32_t        base;               // Base address of the firmware in the camera
    uint32_t        memisostart;        // Start address of the Canon heap memory (where CHDK is loaded)
    int             size;               // Size of the firmware (as loaded from the dump)
    int             fsize;              // Size of the firmware (as determined from the start address)
    int             cam_idx;            // Index of the camera name in the firmware
    uint32_t        pid_adr;            // Address of the camera ID in the firmware
	int			    dryos_ver;          // DryOS version number
    char            *dryos_ver_str;     // DryOS version string
    char            *firmware_ver_str;  // Camera firmware version string
    char            *fw_build_date;     // Firmware build date
    char            *fw_build_time;     // Firmware build time
    int             fwver_idx;          // Index of camera firmware version string
    int             pid;                // Camera ID
    int             maxram;             // How much memory does the camera have
	char		    *cam;               // Pointer to camera name string
    char            *ksys;              // Pointer to encryption key
    int             ksys_idx;           // Index of the encryption key in the firmware dump
    int             dancing_bits;       // Dancing Bits number for the encryption key
    int             dancing_bits_idx;   // Index of the dancing bits data in the firmware dump
    uint32_t        data_start;         // Start of DATA section in RAM
    uint32_t        data_init_start;    // Start of initialisation section for DATA in ROM
    int             data_len;           // Length of data section

    // Alt copy of ROM in RAM (DryOS R50, R51)
    uint32_t        *buf2;          // pointer to loaded FW data that is copied
    uint32_t        base2;          // RAM address copied to
    uint32_t        base_copied;    // ROM address copied from
    int             size2;          // Block size copied (in words)

    // Alt copy of ROM (DryOS R51 - only seen on S110 so far)
    uint32_t        alt_base;       // Alternative base address

    // Values loaded from stubs & other files
    stub_values     *sv;
} firmware;

// Load a firmware file
void load_firmware(firmware *fw, const char *filename, const char *base_addr, const char *alt_base_addr, int os_type);

// Functions for analysing a firmware dump

// Check if index value is valid
int idx_valid(firmware *fw, int i);

// Convert index to address and vice-versa
uint32_t idx2adr(firmware *fw, int idx);
int adr2idx(firmware *fw, uint32_t adr);
char* adr2ptr(firmware *fw, uint32_t adr);

void set_ignore_errors(int n);
uint32_t* fwadr(firmware *fw, int i);
// Get a 32 bit value from the dump at the specified index
uint32_t fwval(firmware *fw, int i);
// Extract the source register, destination register or operand2 from the instruction at the specified index
int fwRd(firmware *fw, int i);
int fwRn(firmware *fw, int i);
int fwOp2(firmware *fw, int i);

// Follow a branch (or BL) instruction to get to the called address
int idxFollowBranch(firmware *fw, int fidx, int offset);
uint32_t followBranch(firmware *fw, uint32_t fadr, int offset);
uint32_t followBranch2(firmware *fw, uint32_t fadr, int offset);

// Extract operand from LDR, ADR, or data processing instructions
uint32_t LDR2adr(firmware *fw, int offset);
uint32_t LDR2idx(firmware *fw, int offset);
uint32_t LDR2val(firmware *fw, int offset);
uint32_t ADR2adr(firmware *fw, int offset);
uint32_t ALUop2(firmware *fw, int offset);
uint32_t ALUop2a(firmware *fw, int offset);

// Test instruction at specfied index
int isLDR_PC(firmware *fw, int offset);
int isLDR_SP(firmware *fw, int offset);
int isLDR_PC_cond(firmware *fw, int offset);
int isADR_PC(firmware *fw, int offset);
int isADR_PC_cond(firmware *fw, int offset);
int isLDMFD(firmware *fw, int offset);
int isLDMFD_PC(firmware *fw, int offset);
int isLDR(firmware *fw, int offset);
int isLDR_cond(firmware *fw, int offset);
int isADR(firmware *fw, int offset);
int isSTMFD(firmware *fw, int offset);
int isSTMFD_LR(firmware *fw, int offset);
int isSTR(firmware *fw, int offset);
int isSTR_cond(firmware *fw, int offset);
int isBX(firmware *fw, int offset);
int isBX_LR(firmware *fw, int offset);
int isBL(firmware *fw, int offset);
int isBL_cond(firmware *fw, int offset);
int isB(firmware *fw, int offset);
int isBorBL(firmware *fw, int offset);
int isCMP(firmware *fw, int offset);
int isMOV(firmware *fw, int offset);
int isMOV_immed(firmware *fw, int offset);

// Find a string in the firmware dump
int find_str(firmware *fw, char *str);
// Find the next instruction of a specified type starting at idx within len instructions
int find_inst(firmware *fw, int (*inst)(firmware*,int), int idx, int len);
// Find the previous instruction of a specified type starting at idx within len instructions
int find_inst_rev(firmware *fw, int (*inst)(firmware*,int), int idx, int len);
// Find the Nth instruction of a specified type starting at idx within len instructions
int find_Nth_inst(firmware *fw, int (*inst)(firmware*,int), int idx, int len, int N);
// Find the Nth previous instruction of a specified type starting at idx within len instructions
int find_Nth_inst_rev(firmware *fw, int (*inst)(firmware*,int), int idx, int len, int N);

// Find the first or next reference to a specified string in the dump
int find_strptr_ref(firmware *fw, char *str);
int find_str_ref(firmware *fw, char *str);
int find_nxt_str_ref(firmware *fw, int str_adr, int ofst);

// Find a B or BL instruction that calls/jumps to the 'v1' address
int find_BL(firmware *fw, int k, uint32_t v1, uint32_t v2);
int find_B(firmware *fw, int k, uint32_t v1, uint32_t v2);

// Search the firmware dump calling the 'func' code to see if the current location matches what we are looking for
int search_fw(firmware *fw, int (*func)(firmware*, int, uint32_t, uint32_t), uint32_t v1, uint32_t v2, int len);
int search_fw_bytes(firmware *fw, int (*func)(firmware*, int));
