/*
 * CHDK code_gen
 *      automate generation of boot.c, capt_seq.c and movie_rec.c source files for CHDK
 *      based on chdk-dasm.c from CHDK-PT, created by waterwingz, with extensions from finsig_dryos.c
*
*   usage :- code_gen ROMBASE instructions_file firmware_dump_file
*
*   where:
*       ROMBASE = start address of the firmware in the camera
*       instructions_file   = filename of the instructions file used to generate the code files
*       firmware_dump_file  = filename of the camera firmware dump
*
*   If present the progam will also read stubs_entry.S and stubs_entry_2.S to get function names and addresses
*/

/*
    Notes.
    ======

    The purpose of this program is to generate the source code files used to boot CHDK and override / patch
    the default firmware behaviour. This is done by mimicing the normal camera startup code but with key
    elements replaced or changed to insert the CHDK code.

    A key component of this is to disassemble the firmware code, copy it to the CHDK source file, and then
    patch the necessary instructions for CHDK. This can be tedious and it is easy to make mistakes.

    CHDK-PT provides a GUI interface to examine and dump the firmware instructions in the correct format
    thus achieving the first two goals.

    This program aims to automate the third step of applying the patches and generating final source files.

    Note: this program is not magic - it will still require some digging into the camera firmware disassembly
    and finding functions and function lengths. It may help with the overall porting process, especially for
    a new firmware version for an existing camera port.
*/

/*
    Format of the instructions file used to generate the output code files.
    =======================================================================

    The input file is a series of instructions, one per line, that control the processing of this program.
    The instructions perform the following operations:
        - Open a new file for output
        - Close the output file
        - Copy lines from the instruction file directly to the output file unchanged
                e.g. to add header sections to .c files
        - Copy the contents of another file to the output file
                e.g. to store common code blocks in other source files
        - Begin disassembly of a new function
        - End function disassembly
        - Add the 'asm...' directive to the file to begin disassebled code
        - End the 'asm...' code block
        - Disassemble a block of code from the firmware into the output file
        - Skip over a block of firmware (e.g. DCD code)
        - Disassemble an instruction; but comment it out in the output file (including a comment for explanation)
        - Disassemble and patch an instruction that references another function
                e.g. convert BL sub_XXXXXXX to BL sub_XXXXXXXX_my
        - Disassemble and patch the immediate value in an instruction
                e.g. convert LDR R2, #0x800 to LDR R2, #0x2000
        - Generate a B instruction that jumps back to the firmware at the current address (continue execution in the firmware)

    Each line of the input file looks like:
        operation arguments
    Arguments are of the form:
        name
        value
        name value
        name=value
    The first form is used when no value is required, the second when a single argument is needed, and the third and fourth are equivalent.

    Note there is not much error checking so lines not formatted correctly may cause invalid results.
    
    Lines with unrecognised operations or blank lines are ignores - so you can document the instruction file.
    It is recommended to use C style single line comments (//) to document the file, multi line comments are not implemented.

    Notes:
        Operation and argument names are case sensitive.
        Optional arguments below are shown in square brackets.
        Alternate versions of an argument are shown with '|' seperating them.
        Arguments with spaces (e.g. comments) must be enclosed in double quotes.
        Numeric arguments can be entered as decimal or hex, hex arguments must begin with 0x.
        If no FILE instruction is active output is written to stdout

    The available operations and arguments are:
        FILE filename                               - opens a new file for output
        ENDFILE                                     - closes the current file
        LI 0|1                                      - enables (LI 1) or disables (LI 0) output of line numbers against disassembled firmware instructions 
                                                      useful when determining function length
        >>>                                         - copies all lines from the input file to the current output file until
                                                      a line beginning with '<<<' is found.
        >>> prelabel                                - as above, except the lines are copied before the 'loc_XXXXXXXX' label on the current instruction
                                                      if the current instruction address has a 'loc_XXXXXXXX' label (for branches, etc), the label is
                                                      normally written to the output file first.
                                                      the 'prelabel' argument causes the lines to be copied before the label.
        <<<                                         - ends the direct copy started above
        >>> file=filename                           - copies the contents of the named file to the output file (note no '<<<' is needed to end the copy)
        FUNC name=FuncName start=X [end=Y length=N] - starts a new function called 'FuncName' writing the prologue to the output file
                                                      
                                                      Note: one of 'end' or 'length' are required; but may be calculated (see below)
                                                      start = function start address in the firmware
                                                      end = address of the last instruciton in the function
                                                      length = number of instructions
                                                      If end is not supplied it is calculated from length & start
                                                      If length is not supplied it is calculated from end & start
                                                      Validation -> length == (end - start / 4) + 1;

                                                      If 'end' or 'length' are not initially supplied then the code will try and calculate them
                                                      - If the FUNC instructions are all fixed length (FW n, PATCHSUB, PATCHVAL, REM & SKIP) then the
                                                        length of each is totalled to calculate 'length'
                                                      - Otherwise (instructions includes 'FW $') the program searches for the next 'STMFD SP!,{...,LR}'
                                                        instruction. If found within 500 instructions it then searches back for the last instruction
                                                        that is either 'LDMFD SP!,{...,PC}', 'B', 'BX LR', or 'LDR PC,[SP,...]' (within the prev 50 instruction).
                                                        If found this instruction is considered the 'end' address.

        FUNC ref=N [end=Y length=N]                 - starts a new function; with the name and start address from a PATCHSUB (see below)
                                                      end and length rules as above
        FUNC sig=SigName [name=FuncName] [end=Y length=N]
                                                    - starts a new function. The address and name are looked up in the values
                                                      loaded from the stubs files. If supplied 'name' will override the function name from stubs.
                                                      end and length rules as above
        ENDFUNC                                     - ends the current function and writes the epiligue code
        ASM                                         - writes the 'asm...' stuff to begin assembly code in the .c source
        ENDASM                                      - ends the 'asm...' code block
        ENDASM prelabel                             - ends the 'asm...' code block
                                                      if there is a label for the next instruction output the label first
        FW                                          - disassemble a single instruction from the firmware to the output file at the current address
                                                      the initial start address is set by FUNC
                                                      the address is updated after each FW instruction by the number of instructions output
        FW n                                        - disassemble the next 'n' instructions to the output file. 
        FW $                                        - disassemble from the current address to the end of the function
        FW $-n                                      - disassemble from the current address to the end of the function - 'n' instructions
        FW [n|$|$-n] ^X                             - as above but reset the current disassembly address to X before disassembling anything
                                                      can be user to jump forward in the function.
                                                      X must be inside the function start - end range
        FW [n|$|$-n] -X                             - as above but reset the current function end address to X before disassembling anything
                                                      no idea if this is of any actual use.
                                                      X must be inside the function start - end range
        REM ["comment"]                             - Disassemble a single instruction; but comment it out in the output file
                                                      the optional comment is added to the output file (to explain if necessary)
        SKIP                                        - Updates the disassembly address by one instruction (skips over the instruction)
        SKIP n                                      - Updates the disassembly address by 'n' instructions (skips over the instructions)
        ->FW                                        - generates a 'B sub_XXXXXXXX' instruction to the current firmware address
                                                      used to jump back to the firmware to continue execution
        PATCHVAL value=N [comment="S"]              - disassembles a single instruction, replacing any immediate value in the instruction with N
                                                      comments are written that show the original value
                                                      e.g. can be used to convert
                                                            LDR R2, #0x800
                                                      to    LDR R2, #0x2000
                                                      if supplied the 'S' comment value is also written to the output
        PATCHSUB [comment="S"]                      - disassembles the next instruction, patching a function reference.
                                                      this changes sub_XXXXXXXX to sub_XXXXXXXX_my
                                                      e.g. convert
                                                            BL sub_FF811234
                                                      to    BL sub_FF811234_my
                                                      or convert
                                                            LDR R1, =sub_FF811234
                                                      to    LDR R1, =sub_FF811234_my
                                                      if supplied the 'S' comment value is also written to the output
        PATCHSUB name=FuncName [comment="S"]        - disassembles the next instruction, patching a function reference.
                                                      this changes sub_XXXXXXXX to FuncName
                                                      e.g. convert
                                                            BL sub_FF811234
                                                      to    BL FuncName
                                                      or convert
                                                            LDR R1, =sub_FF811234
                                                      to    LDR R1, =FuncName
                                                      if supplied the 'S' comment value is also written to the output
        PATCHSUB ref=N [name=FN] [comment="s"]      - as above, this disassembles and patches a function reference instruction
                                                      in addition this saves the function address and patched name to reference array at index 'N'
                                                      this can then be used in the 'FUNC ref=N' operation to retrieve the saved name and address
                                                      to begin a new function. This saves the effort of entering the name and address on the FUNC
                                                      line and makes the instructions more portable across firmware versions.
                                                      Up to 20 patch references can be saved.

    Some examples from the G12 port:

        FILE boot.c                                 - opens the boot.c file for output

        >>> file=../boot_hdr.c                      - copies the content of the common boot_hdr.c file to boot.c

        FUNC start=0xFF81000C length=86 name=boot   - begins disassebly of the boot loader at address FF81000C with a length of 86 instructions
        ASM                                         - adds the 'asm..' code
        FW $-1                                      - disassemble the firmware boot code up to, but not including, the last instruction
        PATCHSUB ref=0                              - disassemble the last instruction, with the function name patched
        ENDASM                                      - ends the 'asm...' code
        ENDFUNC                                     - ends the function (writes the epilogue)

        FUNC ref=0 length=27                        - starts the next function using the name and address saved in the PATCHSUB ref=0 above.
                                                    - this allows the instructions to be used on another port without entering new values
        >>>                                         - copy the lines below to the function (before the assembler code)

        	//http://chdk.setepontos.com/index.php/topic,4194.0.html
        	*(int*)0x1938=(int)taskHook;
        	*(int*)0x193C=(int)taskHook;
    
        	// replacement of sub_FF864BE0 for correct power-on.
        	*(int*)(0x25E0) = (*(int*)0xC0220108)&1 ? 0x100000 : 0x200000; 

        <<<                                         - stop copying
        ASM                                         - adds the 'asm..' code
        FW $-1                                      - disassemble the firmware boot code up to, but not including, the last instruction
        PATCHSUB ref=0                              - disassemble the last instruction, with the function name patched
                                                    - we reuse the same 'ref=0' since we are done with the previous values
        ENDASM                                      - ends the 'asm...' code
        ENDFUNC                                     - ends the function (writes the epilogue)

        ....

        FUNC ref=0 length=9
        ASM
        FW 7
        PATCHSUB name=mykbd_task                    - Patch a call so it now uses the CHDK kbd task
        PATCHVAL value=0x2000 comment="stack size for new task_PhySw"
                                                    - Patch the instruction that sets the kbd task stack size (with a comment)
        ->FW                                        - contine execution in the firmware
        ENDASM
        ENDFUNC

        ENDFILE                                     - close boot.c

        FILE movie_rec.c                            - open the movie_rec.c file

        ....

        FUNC sig=task_MovieRecord length=85 name=movie_record_task
                                                    - start the movie_record_task hook function, get the start address from stubs found
                                                      by finsig_dryos
        ASM
        FW 58
        >>>

        "    BL      unlock_optical_zoom\n"     // added to unlock the zoom

        <<<
        FW 3
        >>>

        "    LDR     R0, =0x7318-4\n" // <----   -4 //+ set in sub_FF9867F8 above
        "    BL      set_quality\n"                 //+ reset here to user value

        <<<
        FW $
        ENDASM
        ENDFUNC

        ....

        ENDFILE                                     - close movie_rec.c

    Another example of using multiple patch references (from the IXUS 310)

        ....

        FUNC ref=0 length=21                        - patched function using previously saved ref
        ASM
        FW 5
        PATCHSUB ref=0                              - we need to patch two functions inside this one, save the reference to the first
        FW
        PATCHSUB ref=1                              - and patch and save the reference to the second function
        FW $
        ENDASM
        ENDFUNC

        FUNC ref=0 length=67                        - now generate the code for the first patched function above
        ASM
        FW 37
        PATCHSUB ref=2                              - which calls a third one
        FW 12
        PATCHSUB                                    - this is the same function as the previous PATCHSUB so need to save the reference
        FW $
        ENDASM
        ENDFUNC

        FUNC ref=1 length=53                        - now generate the code for the second patch function above
        ASM
        FW $-3
        PATCHSUB
        FW $
        ENDASM
        ENDFUNC

        FUNC ref=2 length=1                         - and finally the code for the third function
                                                      note: we are not disassembling any of the firmware code for this function
                                                      instead we add some CHDK code, then jump directly to the original
                                                      firmware address.
                                                      In this case length=1 is required as length=0 is considered an error.
        ASM
        >>>
        "    STMFD   SP!, {R4,R5,LR} \n"
        "    BL      chdk_process_touch \n"
        "    LDMFD   SP!, {R4,R5,LR} \n"
        "    CMP     R0, #0 \n"
        "    BXNE    LR \n"
        <<<
        ->FW
        ENDASM
        ENDFUNC

        ....
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "stubs_load.h"
#include "firmware_load.h"
#include "chdk_dasm.h"

//------------------------------------------------------------------------------------------------------------

firmware    *fw;

//------------------------------------------------------------------------------------------------------------
// Parsing for instruction file
int largc;
char largs[20][256];
char *last_line;
char token[1024];

char* skip_space(char* c)
{
    while (*c && ((*c == ' ') || (*c == '\t') || (*c == '='))) c++;
    return c;
}

char* skip_token(char* c)
{
    while (*c && (*c != ' ') && (*c != '\t') && (*c != '=')) c++;
    return c;
}

char* skip_string(char* c)
{
    while (*c && (*c != '"')) c++;
    return c;
}

char* next_token(char *line)
{
    token[0] = 0;
    char *c = skip_space(line);
    char *n;
    if (*c)
    {
        if (*c == '"')
        {
            c++;
            n = skip_string(c);
            strncpy(token, c, n-c);
            token[n-c] = 0;
            return skip_space(n+1);
        }
        else
        {
            n = skip_token(c);
            strncpy(token, c, n-c);
            token[n-c] = 0;
            return skip_space(n);
        }
    }
    return c;
}

void parse_line(char *line)
{
    last_line = line;
    largc = 0;
    largs[largc][0] = 0;
    while (line && *line)
    {
        line = next_token(line);
        strcpy(largs[largc++], token);
    }
}

char* next_line(char *line)
{
    char *nxt = strchr(line,'\r');
    if (nxt != 0)
    {
        *nxt++ = 0;
        if (*nxt == '\n')
            nxt++;
    }
    else
    {
        nxt = strchr(line,'\n');
        if (nxt != 0)
            *nxt++ = 0;
    }
    return nxt;
}

void print_args()
{
    int n;
    for (n=0; n<largc; n++) fprintf(stderr,"\t%d %s\n",n,largs[n]);
}

//------------------------------------------------------------------------------------------------------------

// Globals used for instruction processing
FILE *outfile;
int direct_copy;
int in_func;

//------------------------------------------------------------------------------------------------------------

#define NULL_OP     0
#define FILE_OP     1
#define ENDFILE_OP  2
#define COPY_OP     3
#define COPY_LINE   4
#define FUNC_OP     5
#define ENDFUNC_OP  6
#define ASM_OP      7
#define ENDASM_OP   8
#define FW_OP       9
#define PATCHSUB_OP 10
#define PATCHVAL_OP 11
#define REM_OP      12
#define SKIP_OP     13
#define CONTFW_OP   14
#define LI_OP       15

typedef struct _op
{
    struct _op  *next;

    int         operation;
    char        *source;

    char        *name;
    char        *comment;
    int         prelabel;
    t_address   func_start;
    t_address   func_end;
    int         func_len;
    int         patch_ref;
    t_address   fw_start;
    t_address   fw_end;
    int         fw_func_end_offset;
    int         fw_is_func_end_offset;
    int         fw_len;
    t_address   patch_new_val;
    int         skip_len;
    int         li_state;
} op;

op *op_head, *op_tail, *cur_func;

void set_op_name(op *p, char *nm)
{
    if (nm)
    {
        p->name = malloc(strlen(nm)+1);
        strcpy(p->name,nm);
    }
    else
    {
        p->name = 0;
    }
}

void set_op_comment(op *p, char *s)
{
    if (s)
    {
        p->comment = malloc(strlen(s)+1);
        strcpy(p->comment,s);
    }
    else
    {
        p->comment = 0;
    }
}

op *new_op(int type)
{
    op *p = malloc(sizeof(op));

    p->operation = type;

    p->source = malloc(strlen(last_line)+1);
    strcpy(p->source,last_line);

    p->name = 0;
    p->comment = 0;
    p->prelabel = 0;
    p->func_start = 0;
    p->func_end = 0;
    p->func_len = 0;
    p->patch_ref = -1;
    p->fw_start = 0;
    p->fw_end = 0;
    p->fw_func_end_offset = 0;
    p->fw_is_func_end_offset = 0;
    p->fw_len = -1;
    p->patch_new_val = 0;
    p->skip_len = 0;
    p->li_state = 0;

    if (op_tail)
    {
        op_tail->next = p;
    }
    else
    {
        op_head = p;
    }

    op_tail = p;
    p->next = 0;

    return p;
}

void chk_args(int count, char *msg, op *p)
{
    if (largc != count+1)
    {
        fprintf(stderr,"ERROR - %s\n",msg);
        fprintf(stderr,"SOURCE - %s\n",p->source);
        exit(1);
    }
}

//------------------------------------------------------------------------------------------------------------

// Open an output file
void parse_FILE()
{
    op *p = new_op(FILE_OP);
    chk_args(1,"Missing FILE name",0);
    set_op_name(p,largs[1]);
}

// Close output file
void parse_ENDFILE()
{
    new_op(ENDFILE_OP);
}

// Direct copy input to output file
void parse_COPY()
{
    op *p = new_op(COPY_OP);
    int n;

    // Check if copy goes before or after the current instruction address label
    for (n=1; n<largc; n++)
    {
        if (strcmp(largs[n],"prelabel") == 0)
            p->prelabel = 1;
    }

    direct_copy = 1;

    // Check if the copy is from another source file - if so just copy that file
    for (n=1; n<largc; n++)
    {
        if (strcmp(largs[n],"file") == 0)
        {
            set_op_name(p,largs[++n]);
            direct_copy = 0;
        }
    }
}

// Start a new Function disassembly:
//  - sets up addresses & length
//  - does pass 1 & 2 of the disassembly to get the labels
//  - writes the function start to the source
void parse_FUNC()
{
    op *p = new_op(FUNC_OP);
    int n;

    for (n=1; n<largc; n++)
    {
        if (strcmp(largs[n], "name") == 0)
        {
            set_op_name(p,largs[++n]);
        }
        else if (strcmp(largs[n], "start") == 0)
        {
            p->func_start = strtoul(largs[++n],0,0);
        }
        else if (strcmp(largs[n], "end") == 0)
        {
            p->func_end = strtoul(largs[++n],0,0);
        }
        else if (strcmp(largs[n], "length") == 0)
        {
            p->func_len = strtoul(largs[++n],0,0);
        }
        else if (strcmp(largs[n], "ref") == 0)
        {
            p->patch_ref = strtol(largs[++n],0,0);
        }
        else if (strcmp(largs[n], "sig") == 0)
        {
            osig *sig = find_sig(fw->sv->stubs, largs[++n]);
            if (sig == 0) chk_args(-1,"Can't find firmware function for 'sig='",p);
            p->func_start = sig->val;
            p->name = sig->nm;
        }
        else
        {
            chk_args(-1,"Invalid FUNC argument",p);
        }
    }
}

// End function, writes the function end to the file
void parse_ENDFUNC()
{
    new_op(ENDFUNC_OP);
}

// Writes the 'asm...' stuff to the file
void parse_ASM()
{
    new_op(ASM_OP);
}

// Ends the 'asm...' block
void parse_ENDASM()
{
    op *p = new_op(ENDASM_OP);
    int n;

    // Check if copy goes before or after the current instruction address label
    for (n=1; n<largc; n++)
    {
        if (strcmp(largs[n],"prelabel") == 0)
            p->prelabel = 1;
    }
}

// Disassemble a block of firmware code to the file
void parse_FW()
{
    op *p = new_op(FW_OP);
    int n;

    for (n=1; n<largc; n++)
    {
        switch (largs[n][0])
        {
        case '^':
            p->fw_start = strtoul(largs[n]+1,0,0);
            break;
        case '-':
            p->fw_end = strtoul(largs[n]+1,0,0);
            break;
        case '$':
            p->fw_func_end_offset = strtol(largs[n]+1,0,0) * 4;
            p->fw_is_func_end_offset = 1;
            break;
        default:
            p->fw_len = strtoul(largs[n],0,0);
            if (p->fw_len == 0) p->fw_len++;
            break;
        }
    }

    if ((p->fw_start != 0) && (p->fw_end != 0))
        p->fw_len = (p->fw_end - p->fw_start) / 4 + 1;
}

// Disassemble and patch a single instruction that references another sub_XXXXXXXX
// The instruction can be B/BL/LDR etc.
void parse_PATCHSUB()
{
    op *p = new_op(PATCHSUB_OP);
    int n;

    for (n=1; n<largc; n++)
    {
        if (strcmp(largs[n], "name") == 0)
        {
            set_op_name(p,largs[++n]);
        }
        else if (strcmp(largs[n], "ref") == 0)
        {
            p->patch_ref = strtoul(largs[++n],0,0);
        }
        else if (strcmp(largs[n], "comment") == 0)
        {
            set_op_comment(p,largs[++n]);
        }
        else
        {
            chk_args(-1,"Invalid PATCHSUB argument",p);
        }
    }
}

// Disassemble and patch a single instruction, replacing an immediate value
void parse_PATCHVAL()
{
    op *p = new_op(PATCHVAL_OP);
    int n;

    for (n=1; n<largc; n++)
    {
        if (strcmp(largs[n], "value") == 0)
        {
            p->patch_new_val = strtoul(largs[++n],0,0);
        }
        else if (strcmp(largs[n], "comment") == 0)
        {
            set_op_comment(p,largs[++n]);
        }
        else
        {
            chk_args(-1,"Invalid PATCHVAL argument",p);
        }
    }
}

// Disassemble and comment out a single instruction
// An optional comment can be added to the line with the reason for removal
void parse_REM()
{
    op *p = new_op(REM_OP);

    if (largc > 1)
    {
            set_op_comment(p,largs[1]);
    }
}

// Skip N words in the firmware - used to skip over DCD in the middle of a function
void parse_SKIP()
{
    op *p = new_op(SKIP_OP);

    if (largc > 1)
        p->skip_len = strtol(largs[1],0,0);
    else
        p->skip_len = 1;
}

// Generate a B instruction to jump back to the firmware code at the current address
void parse_CONTFW()
{
    new_op(CONTFW_OP);
}

// Enable or disable line number output
void parse_LI()
{
    op *p = new_op(LI_OP);
    if (largc > 1)
        p->li_state = strtol(largs[1],0,0);
}

//------------------------------------------------------------------------------------------------------------

void op_prelabel(op *p)
{
    // If after then write label to output and remove from list (so it doesn't get written twice)
    if (in_func && (p->prelabel == 0) && (addr <= options.end_address))
    {
        if (l_search(branch_list, addr))
        {
            fprintf(outfile,"\n\"loc_%08X:\\n\"\n", addr) ;	
            l_remove(branch_list, addr);
        }
    }
}

// Direct copy input to output file
void op_COPY(op *p)
{
    int x;

    op_prelabel(p);

    // Check if the copy is from another source file - if so just copy that file
    if (p->name)
    {
        FILE *fp = fopen(p->name,"r");
        if (!fp)
        {
            fprintf(stderr,"Can't open file '%s'\n",p->name);
            exit(1);
        }

        char buf[1024];
        do
        {
            x = fread(buf,1,1024,fp);
            if (x > 0) fwrite(buf,1,x,outfile);
        } while (x > 0);

        fclose(fp);
        direct_copy = 0;
    }
}

// Start a new Function disassembly:
//  - sets up addresses & length
//  - does pass 1 & 2 of the disassembly to get the labels
//  - writes the function start to the source
void op_FUNC(op *p)
{
    char func_name[256];

    *func_name = 0;

    cur_func = p;

    if (p->name)
        strcpy(func_name, p->name);

    if (p->patch_ref >= 0)
    {
        p->func_start = patch_ref_address[p->patch_ref];
        strcpy(func_name, patch_ref_name[p->patch_ref]);
    }

    in_func = 1;

    if (p->func_start == 0) chk_args(-1,"Missing FUNC start address",p);

    if ((p->func_end == 0) && (p->func_len == 0))
    {
        op *n = p->next;
        int cont = 1;
        while (n && cont)
        {
            switch (n->operation)
            {
            case FW_OP:
                if (n->fw_is_func_end_offset)
                {
                    cont = 0;
                    p->func_len = 0;
                }
                else
                {
                    p->func_len += n->fw_len;
                }
                break;
            case PATCHSUB_OP:
            case PATCHVAL_OP:
            case REM_OP:
                p->func_len++;
                break;
            case SKIP_OP:
                p->func_len += n->skip_len;
                break;
            case ENDFUNC_OP:
                cont = 0;
                break;
            }
            n = n->next;
        }

        if (p->func_len == 0)
        {
            p->func_end = find_end(fw, p->func_start);
            if (p->func_end == 0)
                chk_args(-1,"Missing FUNC end address or length",p);
        }
    }

    if ((p->func_end == 0) && (p->func_len > 0))
        p->func_end = p->func_start + p->func_len * 4 - 4;
    if ((p->func_len == 0) && (p->func_end > 0))
        p->func_len = (p->func_end - p->func_start) / 4 + 1;
    if (p->func_end < p->func_start) chk_args(-1,"FUNC start > end",p);
    if (p->func_len != ((p->func_end - p->func_start) / 4 + 1)) chk_args(-1,"FUNC start/end/length mismatch",p);

    if (*func_name == 0)
        sprintf(func_name, "sub_%08X_my", p->func_start);

    options.start_address = p->func_start;
    options.end_address   = p->func_end;

    set_ignore_errors(1);
    options.flags |= disopt_remember_branches;
    disassemble1(fw, p->func_start, p->func_len);
    options.flags &= ~disopt_remember_branches;
    set_ignore_errors(0);

    fprintf(outfile,"\n/*************************************************************/");
    fprintf(outfile,"\n//** %s @ 0x%08X - 0x%08X, length=%d\n", func_name, p->func_start, last_used_addr, (last_used_addr - p->func_start) / 4 + 1 ) ;
    fprintf(outfile,"void __attribute__((naked,noinline)) %s() {\n", func_name);

    addr = p->func_start;
}

// Disassemble a block of firmware code to the file
void op_FW(op *p)
{
    t_address start_address = addr;
    t_address end_address = addr;

    if (p->fw_start > 0)
        start_address = p->fw_start;
    if (p->fw_end > 0)
        end_address = p->fw_end;
    if (p->fw_is_func_end_offset)
        end_address = cur_func->func_end + p->fw_func_end_offset;
    if (p->fw_len > 0)
        end_address = start_address + p->fw_len * 4 - 4;

    disassemble(fw, outfile, start_address, (end_address + 4 - start_address) / 4);
}

// Disassemble and patch a single instruction that references another sub_XXXXXXXX
// The instruction can be B/BL/LDR etc.
void op_PATCHSUB(op *p)
{
    patch_func_name = p->name;
    save_patch_ref = p->patch_ref;
    patch_comment = p->comment;
    if (patch_comment)
    {
        options.flags |= disopt_patch_comment;
    }

    options.flags |= disopt_patch_branch;
    disassemble(fw, outfile, addr, 1);
    options.flags &= ~(disopt_patch_branch|disopt_patch_comment);
}

// Disassemble and patch a single instruction, replacing an immediate value
void op_PATCHVAL(op *p)
{
    patch_new_val = p->patch_new_val;
    patch_comment = p->comment;
    if (patch_comment)
    {
        options.flags |= disopt_patch_comment;
    }

    options.flags |= disopt_patch_value;
    disassemble(fw, outfile, addr, 1);
    options.flags &= ~(disopt_patch_value|disopt_patch_comment);
}

// Disassemble and comment out a single instruction
// An optional comment can be added to the line with the reason for removal
void op_REM(op *p)
{
    patch_comment = p->comment;
    if (patch_comment)
    {
        options.flags |= disopt_patch_comment;
    }

    options.flags |= disopt_comment_lines;
    disassemble(fw, outfile, addr, 1);
    options.flags &= ~(disopt_comment_lines|disopt_patch_comment);
}

//------------------------------------------------------------------------------------------------------------

// Process operation on current line
void do_ops(op *p)
{
    switch (p->operation)
    {
    case FILE_OP:
        // Open an output file
        outfile = fopen(p->name, "w");
        fprintf(outfile, "/*\n * %s - auto-generated by CHDK code_gen.\n */\n", p->name);
        break;
    case ENDFILE_OP:
        // Close output file
        if (outfile != stdout)
        {
            fclose(outfile);
            outfile = stdout;
        }
        break;
    case COPY_OP:
        op_COPY(p);
        break;
    case COPY_LINE:
        fprintf(outfile, "%s\n", p->comment);
        break;
    case FUNC_OP:
        op_FUNC(p);
        break;
    case ENDFUNC_OP:
        // End function, writes the function end to the file
        fprintf(outfile,"}\n");
        in_func = 0;
        break;
    case ASM_OP:
        // Writes the 'asm...' stuff to the file
        fprintf(outfile,"asm volatile (\n");
        break;
    case ENDASM_OP:
        // Ends the 'asm...' block
        op_prelabel(p);
        fprintf(outfile,");\n");
        break;
    case FW_OP:
        op_FW(p);
        break;
    case PATCHSUB_OP:
        op_PATCHSUB(p);
        break;
    case PATCHVAL_OP:
        op_PATCHVAL(p);
        break;
    case REM_OP:
        op_REM(p);
        break;
    case SKIP_OP:
        // Skip N words in the firmware - used to skip over DCD in the middle of a function
        addr += (p->skip_len * 4);
        break;
    case CONTFW_OP:
        // Generate a B instruction to jump back to the firmware code at the current address
        if (options.flags & disopt_line_numbers) fprintf(outfile,"       ");
        fprintf(outfile,"\"    LDR     PC, =0x%08X \\n\"  // Continue in firmware\n",addr);
        break;
    case LI_OP:
        // set line number output state
        if (p->li_state != 0)
            options.flags |= disopt_line_numbers;
        else
            options.flags &= ~disopt_line_numbers;
        break;
    }
}

// Process an operation
int run_op(char *name, void (*func)())
{
    if (strcmp(largs[0], name) == 0)
    {
        func();
        return 1;
    }
    return 0;
}

// Pre-Process operation on current line
void parse_ops()
{
    if (largc > 0)
    {
        if (run_op("FILE",      parse_FILE))       return;
        if (run_op("ENDFILE",   parse_ENDFILE))    return;
        if (run_op(">>>",       parse_COPY))       return;
        if (run_op("FUNC",      parse_FUNC))       return;
        if (run_op("ENDFUNC",   parse_ENDFUNC))    return;
        if (run_op("ASM",       parse_ASM))        return;
        if (run_op("ENDASM",    parse_ENDASM))     return;
        if (run_op("FW",        parse_FW))         return;
        if (run_op("PATCHSUB",  parse_PATCHSUB))   return;
        if (run_op("PATCHVAL",  parse_PATCHVAL))   return;
        if (run_op("REM",       parse_REM))        return;
        if (run_op("SKIP",      parse_SKIP))       return;
        if (run_op("->FW",      parse_CONTFW))     return;
        if (run_op("LI",        parse_LI))         return;
    }
}

//------------------------------------------------------------------------------------------------------------

void usage(char *err)
{
    fprintf(stderr,"code_gen <base> <primary> [alt base] - Error = %s\n",err);
    exit(1);
}

op* last_op = 0;

void error(char *fmt, int n)
{
    if (last_op)
        fprintf(stderr,"Source --> %s\n",last_op->source);
    exit(1);
}

//------------------------------------------------------------------------------------------------------------

int main(int ac, const char * av[]) 
{
    // Check number of args
    if (ac < 4)
    {
        fprintf(stderr,"Usage: code_gen ROMBASE code_gen.txt PRIMARY.BIN [ALT_ROMBASE]\n");
        exit(1);
    }

    // Get ROMBASE value
    options.ROM_start = strtoul(av[1],0,0);
    if (options.ROM_start == 0)
    {
        fprintf(stderr,"Invalid ROMBASE.\n");
        exit(1);
    }

    // Get instruction file length
    struct stat st;
    if (stat(av[2],&st) != 0)
    {
        fprintf(stderr, "Failed to stat \"%s\".\n", av[2]);
        exit(1);
    }
    size_t len = st.st_size;

    // Open & read instruction file
    FILE *fp = fopen(av[2], "rb");
    if (!fp)
    {
        fprintf(stderr, "Failed to open \"%s\".\n", av[2]);
        exit(1);
    }

    // Allocate block for instruction file
    char *def = malloc(len+1);
    if (def == 0)
    {
        fprintf(stderr, "Not enough memory.\n");
        exit(1);
    }

    // Read instruction file
    size_t n = fread(def, 1, len, fp);
    def[n] = 0;
    fclose(fp);

    // Open Firmware dump file
    fw = malloc(sizeof(firmware));
    load_firmware(fw, av[3], av[1], (ac==5)?av[4]:0, OS_DRYOS);

    // Load function name/address values from stubs files
    fw->sv = new_stub_values();
    load_funcs(fw->sv, "funcs_by_name.csv");
    load_stubs(fw->sv, "stubs_entry.S", 0);
    load_stubs(fw->sv, "stubs_entry_2.S", 0);   // Load second so values override stubs_entry.S

    outfile = stdout;
    direct_copy = 0;
    in_func = 0;

    op_head = op_tail = 0;

    // Pre-Process
    char *line = def;
    while ((line != 0) && (*line != 0))
    {
        char *nxt = next_line(line);

        // Check if just copying from input file to output file
        if (direct_copy)
        {
            // Check if end of copy
            if (strncmp(line,"<<<",3) == 0)
            {
                direct_copy = 0;
            }
            else
            {
                op *p = new_op(COPY_LINE);
                set_op_comment(p,line);
            }
        }
        else
        {
            parse_line(line);
            parse_ops();
        }

        line = nxt;
    }

    // Process
    op *p = op_head;
    while (p)
    {
        last_op = p;
        do_ops(p);
        p = p->next;
    }

    if (outfile != stdout)
        fclose(outfile);

    return 0;
}
