/*=====================================================================================================
	chdk_dasm.c
	
	This sofware is provided "as is" with no warantee or representation of any "fitness for use"/
	
	This software contains code included under the license included below. The code was changed to
			- provide formatting compatible with gcc as used for CHDK development
			- provide a multi-pass approach was added to allow the generation and handling of labels.  
			- expanded command line options
			- correction to dissassembly bugs and added support for the STRD instruction.
			
	None of these modifications are the work of the original author.

	And if you are wondering,  the original dissassembler code appears to have been optimized to 
	run on an ARM process, which explains all the goofy use of left and right shifts.  Those compile
	nicely to a single instrucion on the ARM processor.
	
=====================================================================================================*/

/* disarm -- a simple disassembler for ARM instructions
 * (c) 2000 Gareth McCaughan
 *
 * This file may be distributed and used freely provided:
 * 1. You do not distribute any version that lacks this
 *    copyright notice (exactly as it appears here, extending
 *    from the start to the end of the C-language comment
 *    containing these words)); and,
 * 2. If you distribute any modified version, its source
 *    contains a clear description of the ways in which
 *    it differs from the original version, and a clear
 *    indication that the changes are not mine.
 * There is no restriction on your permission to use and
 * distribute object code or executable code derived from
 * this.
 *
 * The original version of this file (or perhaps a later
 * version by the original author) may or may not be
 * available at http://web.ukonline.co.uk/g.mccaughan/g/software.html .
 *
 * Share and enjoy!    -- g
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

declstruct(Instruction);

typedef enum {
    target_None,		/* instruction doesn't refer to an address */
    target_Data,		/* instruction refers to address of data */
    target_FloatS,	/* instruction refers to address of single-float */
    target_FloatD,	/* instruction refers to address of double-float */
    target_FloatE,	/* blah blah extended-float */
    target_FloatP,	/* blah blah packed decimal float */
    target_Code,		/* instruction refers to address of code */
    target_Unknown	/* instruction refers to address of *something* */
} eTargetType;

defstruct(Instruction) {
    char text[128];			/* the disassembled instruction */
    int undefined;			/* non-0 iff it's an undefined instr */
    int badbits;				/* non-0 iff something reserved has the wrong value */
    int oddbits;				/* non-0 iff something unspecified isn't 0 */
    int is_SWI;				/* non-0 iff it's a SWI */
    t_value swinum;		/* only set for SWIs */
    t_address target;			/* address instr refers to */
    eTargetType target_type;	/* and what we expect to be there */
    int offset;				/* offset from register in LDR or STR or similar */
    char * addrstart;			/* start of address part of instruction, or 0 */
    t_value instr ;				/* the raw instruction data */
};

char *patch_func_name;
t_address patch_new_val;
t_address patch_old_val;
char *patch_old_func_name;      // if old patched value found in stubs
int patch_ref_address[20];
char patch_ref_name[20][256];
int save_patch_ref;
char *patch_comment;

static char * reg_names[16] = {
    "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7",  "R8", "R9", "R10", "R11", "R12", "SP", "LR", "PC"
};

sDisOptions options = {
    disopt_CommaSpace|disopt_exclude_dcd,
    reg_names
};

/* Some important single-bit fields. */

#define Sbit	(1<<20)		/* set condition codes (data processing) */
#define Lbit	(1<<20)		/* load, not store (data transfer) */
#define Wbit	(1<<21)		/* writeback (data transfer) */
#define Bbit	(1<<22)		/* single byte (data transfer, SWP) */
#define Ubit	(1<<23)		/* up, not down (data transfer) */
#define Pbit	(1<<24)		/* pre-, not post-, indexed (data transfer) */
#define Ibit	(1<<25)		/* non-immediate (data transfer) */
/* immediate (data processing) */
#define SPSRbit	(1<<22)		/* SPSR, not CPSR (MRS, MSR) */

/* Some important 4-bit fields. */

#define RD(x)	((x)<<12)	/* destination register */
#define RN(x)	((x)<<16)	/* operand/base register */
#define CP(x)	((x)<<8)	/* coprocessor number */
#define RDbits	RD(15)
#define RNbits	RN(15)
#define CPbits	CP(15)
#define RD_is(x)	((instr&RDbits)==RD(x))
#define RN_is(x)	((instr&RNbits)==RN(x))
#define CP_is(x)	((instr&CPbits)==CP(x))

/* A slightly efficient way of telling whether two bits are the same
 * or not. It's assumed that a<b.
 */
#define BitsDiffer(a,b) ((instr^(instr>>(b-a)))&(1<<a))

//------------------------------------------------------------------------------------------------------------

/* -----------------------------------------------------------------
 * Linked List Routines
 * ----------------------------------------------------------------- */
 
struct lnode {					// linked list node - Storage memory address / memory data pairs
    struct lnode *next;
    t_address address;
    t_value data ;
}; 

struct llist {					// Head of linked list
    struct lnode *head;
    int size;
};

/* -----------------------------------------------------------------
 * struct llist * new_list(void)
 * ----------------------------------------------------------------- */
struct llist * new_list()
{ 
    struct llist *lst;

    lst = (struct llist *) malloc(sizeof(struct llist));
    if (lst == NULL) {
        printf("\n **new_list() : malloc error");
        return NULL;
    }
    lst->head = 0;
    lst->size = 0;

    return lst;
}

void free_list(struct llist *lst)
{
    if (lst)
    {
        struct lnode *p, *n;
        p = lst->head;
        while (p)
        {
            n = p->next;
            free(p);
            p = n;
        }
        free(lst);
    }
}

/* -----------------------------------------------------------------
 * struct new_node * new_node(void * item, t_value data)
 * ----------------------------------------------------------------- */
struct lnode * new_node(t_address address, t_value data) {
    struct lnode *node;

    node = (struct lnode *) malloc (sizeof (struct lnode));
    if (node == NULL) {
        printf("\n **new_node() : malloc error");
        return NULL;
    }
    node->address = address;
    node->data = data;
    node->next = 0;

    return node;
}  

/* -----------------------------------------------------------------
 * int l_search(struct llist *ls, void *address) {
 * ----------------------------------------------------------------- */
struct lnode * l_search(struct llist *ls, t_address address) {
    struct lnode *node;

    node = ls->head;
    while ( node != NULL && node->address != address ) {
        node = node->next ;
    }
    if (node == NULL) {
        return 0; /* 'item' not found */
    }

    return node;
}

/* -----------------------------------------------------------------
 * int l_insert(struct llist *ls, void *item)
 * ----------------------------------------------------------------- */
int l_insert(struct llist *ls, t_address address, t_value data)
{
    struct lnode *node;

    if( l_search(ls, address)) return -1 ;
    node = new_node(address, data);
    if (node == NULL) return 0;
    node->next = ls->head;
    ls->head = node;  
    (ls->size)++;

    return 1;
}

void l_remove(struct llist *ls, t_address addr)
{
    if (ls)
    {
        struct lnode *p, *l;
        l = 0;
        p = ls->head;
        while (p)
        {
            if (p->address == addr)
            {
                if (l)
                    l->next = p->next;
                else
                    ls->head = p->next;
                (ls->size)--;
                return;
            }
            l = p;
            p = p->next;
        }
    }
}
 
/* -----------------------------------------------------------------
 *  Create Linked Lists
 * ----------------------------------------------------------------- */
 
struct llist *dcd_list;				// create list of DCD addresses
struct llist *branch_list;			// create list of branch instruction target addresses

/* -----------------------------------------------------------------
 *  Dissassembler Code
 * ----------------------------------------------------------------- */

static void set_patch_old_values(t_address w, char *nm)
{
    patch_old_val = w;
    patch_old_func_name = nm;
}

extern void swiname(t_value, char *, size_t);

/* op = append(op,ip) === op += sprintf(op,"%s",ip),
 * except that it's faster.
 */
static char * append(char * op, const char *ip) {
    char c;
    while ((c=*ip++)!=0) *op++=c;
    return op;
}

/* op = xhex8(op,w) === op += sprintf(op,"&%08lX",w)
 */
static char * xhex8(char * op, t_value w)
{
    char *s = op;

    if (options.flags & disopt_patch_value)
    {
        set_patch_old_values(w, 0);
        w = patch_new_val;
    }

    if (options.flags & disopt_patch_branch)
    {
        set_patch_old_values(w, 0);
        if (patch_func_name)
            op += sprintf(op,"=%s",patch_func_name) ;
        else
        {
            if (options.flags & disopt_comment_lines)
                op += sprintf(op,"=_sub_%08X_my",w);     // prepend '_' to prevent sub from appearing in stubs_auto.S
            else
                op += sprintf(op,"=sub_%08X_my",w);
        }
        if (save_patch_ref >= 0)
        {
            *op = 0;
            patch_ref_address[save_patch_ref] = w;
            strcpy(patch_ref_name[save_patch_ref],s+1);
        }
    }
    else
        op += sprintf(op,"=0x%X",w) ;

    return op;
}

/* op = ahex8(op,w) === op += sprintf(op,"&%08lX",w)
  --> xhex hacked to insert addresses into linked list for use on pass 3
 */
static char * ahex8(char * op, t_value w)
{
    struct lnode * lptr ;
    lptr = l_search( dcd_list, w) ;  		// does this DCD address exist already ?

    if ( lptr ) w = lptr->data ;  					// dereference indirect address (typically pass 3)
    else	l_insert(dcd_list, w, 0) ;  	// add node if not found - typically on pass 1

    return xhex8(op, w);
}

/* op = yhex8(op,w) === op += sprintf(op,"&%08lX",w)
 */
static char * yhex8(char * op, t_value w)
{
    if (options.flags & disopt_patch_value)
    {
        set_patch_old_values(w, 0);
        w = patch_new_val;
    }
    op += sprintf(op,"0x%X",w) ;
    return op;
}

/* op = sub_hex8(op,w) === op += sprintf(op,"&%08lX",w), but faster.
 */
static char * sub_hex8(firmware *fw, char * op, t_value w)
{
    if (options.flags & disopt_remember_branches)
        l_insert(branch_list, w, 0) ;

    char *s = op;

    w = followBranch(fw,w,1);           // If call to Branch then follow branch
    osig *o = find_sig_val_by_type(fw->sv->stubs, w, TYPE_NHSTUB);

    if ((options.flags & disopt_patch_branch) && patch_func_name)
    {
        set_patch_old_values(w, (o) ? o->nm : 0);
        op += sprintf(op,"%s",patch_func_name);
    }
    else
    {
        if (o && !o->is_comment)
        {
            op += sprintf(op,"_%s",o->nm);
        }
        else
        {
            if (( w >= options.start_address )&&( w <= options.end_address ))
            {
                op += sprintf(op,"loc_%08X",w);
            }
            else
            {
                if (options.flags & disopt_comment_lines)
                    op += sprintf(op,"_sub_%08X",w);     // prevent sub from appearing in stubs_auto.S
                else
                {
                    // Get 1st instruction in sub_XXXXXXXX
                    t_value v = fwval(fw,adr2idx(fw,w));
                    if (v == 0xE12FFF1E)    // BX LR?
                    {
                        // Comment out 'nullsub' calls
                        op += sprintf(op,"_sub_%08X",w);
                        options.flags |= disopt_nullsub_call;
                    }
                    else
                    {
                        op += sprintf(op,"sub_%08X",w);
                        if (o && o->is_comment)
                        op += sprintf(op," /*_%s*/",o->nm);
                    }
                }
            }
            if (options.flags & disopt_patch_branch)
            {
                set_patch_old_values(w, 0);
                op += sprintf(op,"_my");
            }
        }
    }

    if ((save_patch_ref >= 0) && (options.flags & disopt_patch_branch))
    {
        *op = 0;
        patch_ref_address[save_patch_ref] = w;
        strcpy(patch_ref_name[save_patch_ref],s);
    }

    return op;
}

static char * sub_ahex8(firmware *fw, char * op, t_value w)
{
    struct lnode * lptr ;
    lptr = l_search( dcd_list, w) ;  		// does this DCD address exist already ?

    if ( !lptr )
        l_insert(dcd_list, w, 0) ;  	// add node if not found - typically on pass 1

    w = fwval(fw,adr2idx(fw,w));
    return sub_hex8(fw, op, w);
}

/* op = reg(op,'x',n) === op += sprintf(op,"x%lu",n&15).
 */
static char * reg(char * op, char c, t_value n) {
    *op++=c;
    n&=15;
    if (n>=10) { *op++='1'; n+='0'-10; } else n+='0';
    *op++=(char)n;

    return op;
}

/* op = num(op,n) appends n in decimal or &n in hex
 * depending on whether n<decmax. It's assumed that n>=0.
 */
static char * num(char * op, t_value w, int decmax)
{
    char tmpbuf[16] ;
    char * tptr ;
    tptr = tmpbuf ;

    if (options.flags & disopt_patch_value)
    {
        set_patch_old_values(w, 0);
        w = patch_new_val;
    }

    if ( w<decmax ) sprintf( tptr, "%d", w) ;
    else
    {
        if (w < 16)
            sprintf( tptr, "0x%X", w);
        else
            sprintf( tptr, "0x%X", w);
    }
    tptr = tmpbuf ;
    while(*tptr) *op++ = *tptr++ ;
    return op;
}

/* instr_disassemble
 * Disassemble a single instruction.
 *
 * args:   instr   a single ARM instruction
 *         addr    the address it's presumed to have come from
 *         opts    cosmetic preferences for our output
 *
 * reqs:   opts must be filled in right. In particular, it must contain
 *         a list of register names.
 *
 * return: a pointer to a structure containing the disassembled instruction
 *         and some other information about it.
 *
 *
 * This function proceeds in two phases. The first is very simple:
 * it works out what sort of instruction it's looking at and sets up
 * three strings:
 *   - |mnemonic|  (the basic mnemonic: LDR or whatever)
 *   - |flagchars| (things to go after the cond code: B or whatever)
 *   - |format|    (a string describing how to display the instruction)
 
 * The second phase consists of interpreting |format|, character by
 * character. Some characters (e.g., letters) just mean `append this
 * character to the output string'; some mean more complicated things
 * like `append the name of the register whose number is in bits 12..15'
 * or, worse, `append a description of the <op2> field'.
 *
 * I'm afraid the magic characters in |format| are rather arbitrary.
 * One criterion in choosing them was that they should form a contiguous
 * subrange of the character set! Sorry.
 *
 * Format characters:
 *
 *   \01..\05 copro register number from nybble (\001 == nybble 0, sorry)
 *   $        SWI number
 *   %        register set for LDM/STM (takes note of bit 22 for ^)
 *   &        address for B/BL
 *   '        ! if bit 21 set, else nothing (mnemonic: half a !)
 *   (        #regs for SFM (bits 22,15 = fpn, assumed already tweaked)
 *   )        copro opcode in bits 20..23 (for CDP)
 *   *        op2 (takes note of bottom 12 bits, and bit 25)
 *   +        FP register or immediate value: bits 0..3
 *   ,        comma or comma-space
 *   -        copro extra info in bits 5..7 preceded by , omitted if 0
 *   .        address in ADR instruction
 *   /        address for LDR/STR (takes note of bit 23 & reg in bits 16..19)
 *   0..4     register number from nybble
 *   5..9     FP register number from nybble
 *   :        copro opcode in bits 21..23 (for MRC/MCR)
 *   ;        copro number in bits 8..11
 *   =        32 constant (address or data)
 *
 * NB that / takes note of bit 22, too, and does its own ! when appropriate.
 *
 */


extern pInstruction instr_disassemble(firmware *fw, t_value instr, t_address addr, pDisOptions opts) {
    static char         flagchars[4];
    static sInstruction result;
    const char * mnemonic  = 0;
    char * flagp     = flagchars;
    const char * format    = 0;
    t_value         fpn;
    eTargetType  poss_tt = target_None;
    int is_v4 = 0;

    options.flags &= ~disopt_nullsub_call;

    /* PHASE 0. Set up default values for |result|. */

    fpn = ((instr>>15)&1) + ((instr>>21)&2);

    result.undefined =
        result.badbits =
        result.oddbits =
        result.instr =
        result.is_SWI = 0;
    result.target_type = target_None;
    result.offset = 0x80000000;
    result.addrstart = 0;

    /* PHASE 1. Decode and classify instruction. */
    static char _i_mul[4][6] = { "UMULL", "UMLAL", "SMULL", "SMLAL" };
    static char _i_ldr_str[2][4] = { "LDR", "STR" };
    static char _i_str_ldr[2][4] = { "STR", "LDR" };
    static char _i_stm_ldm[2][4] = { "STM", "LDM" };
    static char _i_stf_ldf[2][4] = { "STF", "LDF" };
    static char _i_stc_ldc[2][4] = { "STC", "LDC" };
    static char _i_sfm_lfm[2][4] = { "SFM", "LFM" };
    static char _i_b_bl[2][3] = { "B", "BL" };
    static char _i_alu[16][4] = {
        "AND","EOR","SUB","RSB","ADD","ADC","SBC","RSC",
        "TST","TEQ","CMP","CMN","ORR","MOV","BIC","MVN"
    };
    static char _i_cmf[4][5] = { "CMF","CNF","CMFE","CNFE" };
    static char _i_flt[6][4] = { "FLT","FIX","WFS","RFS","WFC","RFC" };
    static char _i_mcr_mrc[2][4] = { "MCR","MRC" };
    static char _i_copro[32][4] = {
        /* dyadics: */
        "ADF","MUF","SUF","RSF",
        "DVF","RDF","POW","RPW",
        "RMF","FML","FDV","FRD",
        "POL","***","***","***",
        /* monadics: */
        "MVF","MNF","ABS","RND",
        "SQT","LOG","LGN","EXP",
        "SIN","COS","TAN","ASN",
        "ACS","ATN","URD","NRM"
    };
    static char _i_lsl_lsr[4][4] = { "LSL","LSR","ASR","ROR" };
    static char _i_stk[4][2] = { "ED","EA","FD","FA" };
    static char _i_cond[16][2] = { "EQ","NE","CS","CC","MI","PL","VS","VC","HI","LS","GE","LT","GT","LE","AL","NV" };

    switch ((instr>>24)&15) {

    case 0:						/* multiply or data processing, or LDRH etc */
        if ((instr&(15<<4))!=(9<<4)) goto lMaybeLDRHetc;   // F0  90

        if (instr&(1<<23)) {			/* long multiply */
            mnemonic = _i_mul[(instr>>21)&3];
            format = "3,4,0,2";
        }
        else {						
            if (instr&(1<<22)) goto laUndefined;	/* "class C" */

            if (instr&(1<<21)) { 		/* short multiply */
                mnemonic = "MLA";
                format   = "4,0,2,3";
            }
            else {
                mnemonic = "MUL";
                format   = "4,0,2";
            }
        }
        if (instr&Sbit) *flagp++='S';
        break;

    case 1:					/* SWP or MRS/MSR or BX or data processing */
    case 3:

        if ((instr&0x0FF000F0)==0x01200010) {	  		/* BX */
            mnemonic = "BX";
            format = "0";
            break;
        }
        if ((instr&0x0FF000F0)==0x01200030) {	 	   /* BLX */
            mnemonic = "BLX";
            format = "0";
            break;
        }
        if ((instr&0x02B00FF0)==0x00000090) {        /* SWP */
            mnemonic = "SWP";
            format   = "3,0,[4]";
            if (instr&Bbit) *flagp++='B';
            break;
        }
        if ((instr&0x02BF0FFF)==0x000F0000) {        /* MRS */
            mnemonic = "MRS";
            format   = (instr&SPSRbit) ? "3,SPSR" : "3,CPSR";
            break;
        }

        if ((instr&0x0FB00010)==0x03200000) {      /* MSR psr<P=0/1...>,Rm */
            mnemonic = "MSR";
            format   = (instr&SPSRbit) ? "SPSR,0" : "CPSR,0";
            break;
        }

        if ((instr&0x0FB00010)==0x01200000) {     /* MSR {C,S}PSR_flag,op2 */
            mnemonic = "MSR";
            format   = (instr&SPSRbit) ? "SPSR_cxsf,*" : "CPSR_cxsf,*";
            if (!(instr&Ibit) && (instr&(15<<4)))
                goto lMaybeLDRHetc;
            break;
        }


lMaybeLDRHetc:			 										/* fall through here */
        if ( (instr&(14<<24))==0 && ((instr&(9<<4))==(9<<4)) ) 
        {  														/* Might well be LDRH or similar. */
            if ((instr&(Wbit+Pbit))==Wbit) goto lbUndefined;		/* "class E", case 1 */
            if ((instr&(Lbit+(1<<6)))==(1<<6)) 						/* is it LDRD/STRD or LDRSH/STRSH */
            {
                if ((instr&(1<<6))!=(1<<6)) 	goto lcUndefined ;
                mnemonic = _i_ldr_str[(instr & 0x0000020) >> 5];    /*  */
                if (instr&(1<<6)) *flagp++='D';
                format = "3,/";
                if (!(instr&(1<<22))) instr |= Ibit;
                is_v4=1;
            }
            else
            {
                mnemonic = _i_str_ldr[(instr&Lbit) >> 20];
                if (instr&(1<<6)) *flagp++='S';
                *flagp++ = (instr&(1<<5)) ? 'H' : 'B';   				/* fixed 2011/03/27 - B & H reversed */
                format = "3,/";									        /* aargh: */
                if (!(instr&(1<<22))) instr |= Ibit;
                is_v4=1;
            }
            break;
        }

    case 2:												      /* data processing */
        { t_value op21 = instr&(15<<21);
        if ((op21==(2<<21) || (op21==(4<<21)))				/* ADD or SUB */
            && ((instr&(RNbits+Ibit+Sbit))==RN(15)+Ibit)	/* imm, no S */
            /*&& ((instr&(30<<7))==0 || (instr&3))*/) {		/* normal rot */
                /* ADD ...,pc,#... or SUB ...,pc,#...: turn into ADR */
                mnemonic = "LDR";									//** 2011/03/27 changed from "ADR" to "LDR" for gcc assembler compatability 
                format   = "3,.";
                if ((instr&(30<<7))!=0 && !(instr&3)) result.oddbits=1;
                break;
        }
        if ((op21==(4<<21))				                    /* ADD */
            && ((instr&(Ibit))==Ibit)                    	/* imm */
            && ((instr&0xFFF)==0)                           /* 0 offset */
            ) {
                /* ADD Rn, Rd, #0 --> MOV */
                mnemonic = "MOV";
                format   = "3,4";
                if (instr&Sbit && (op21<(8<<21) || op21>=(12<<21))) *flagp++='S';
                break;
        }
        mnemonic = _i_alu[op21 >> 21];
        /* Rd needed for all but TST,TEQ,CMP,CMN (8..11) */
        /* Rn needed for all but MOV,MVN (13,15) */
        if (op21 < ( 8<<21)) format = "3,4,*";
        else if (op21 < (12<<21)) {
            format = "4,*";
            if (instr&RDbits) {
                if ((instr&Sbit) && RD_is(15))
                    *flagp++='P';
                else result.oddbits=1;
            }
            if (!(instr&Sbit)) goto ldUndefined;	/* CMP etc, no S bit */
        }
        else if (op21 & (1<<21)) {
            format = "3,*";
            if (instr&RNbits) result.oddbits=1;
        }
        else format = "3,4,*";
        if (instr&Sbit && (op21<(8<<21) || op21>=(12<<21))) *flagp++='S';
        }
        break;

    case 4:								     /* undefined or STR/LDR */
    case 5:
    case 6:
    case 7:
        if ((instr&Ibit) && (instr&(1<<4))) goto leUndefined;	/* "class A" */
        mnemonic = _i_str_ldr[(instr&Lbit) >> 20];
        format   = "3,/";
        if (instr&Bbit) *flagp++='B';
        if ((instr&(Wbit+Pbit))==Wbit) *flagp++='T';
        poss_tt = target_Data;
        break;

    case 8:												 /* STM/LDM */
    case 9:
        mnemonic = _i_stm_ldm[(instr&Lbit) >> 20];
        if (RN_is(13)) {							        /* r13, so treat as stack */
            t_value x = (instr&(3<<23)) >> 23;
            if (instr&Lbit) x^=3;
            {
                const char * foo = _i_stk[x];
                *flagp++ = *foo++;
                *flagp++ = *foo;
            }
        }
        else {									        /* not r13, so don't treat as stack */
            *flagp++ = (instr&Ubit) ? 'I' : 'D';
            *flagp++ = (instr&Pbit) ? 'B' : 'A';
        }
        format = "4',%";
        break;

    case 10:  											 /* B or BL */
    case 11:
        mnemonic = _i_b_bl[(instr&(1<<24))>>24];
        format   = "&";
        break;

    case 12:											/* STC or LDC */
    case 13:   
        if (CP_is(1)) {							        /* copro 1: FPU. This is STF or LDF. */
            mnemonic = _i_stf_ldf[(instr&Lbit) >> 20];
            format   = "8,/";
            *flagp++ = "SDEP"[fpn];
            poss_tt = (eTargetType)(target_FloatS+fpn);
        }
        else if (CP_is(2)) {						        /* copro 2: this is LFM or SFM. */
            mnemonic = _i_sfm_lfm[(instr&Lbit) >> 20];
            if (!fpn) fpn=4;
            if (RN_is(13) && BitsDiffer(23,24)) {
                if ((instr&255)!=fpn) goto lNonStackLFM;		/* r13 and U!=P, so treat as stack */
                if (BitsDiffer(20,24)) {		            	/* L != P, so FD */
                    *flagp++ = 'F'; *flagp++ = 'D';
                }
                else {							            /* L == P, so EA */
                    *flagp++ = 'E'; *flagp++ = 'A';
                }
                format = "8,(,[4]'";
            }
            else {
lNonStackLFM:											/* not r13 or U=P or wrong offset, so don't treat as stack */
                format = "8,(,/";
                poss_tt = target_FloatE;
            }
        }
        else {									        /* some other copro number: STC or LDC. */
            mnemonic = _i_stc_ldc[(instr&Lbit) >> 20];
            format   = ";,\004,/";
            if (instr&(1<<22)) *flagp++ = 'L';
            poss_tt = target_Unknown;
        }
        break;

    case 14:									   		/* CDP or MRC/MCR */
        if (instr&(1<<4)) {					 	   		/* MRC/MCR. */
            if (CP_is(1)) {						     		/* copro 1: FPU. */
                if ((instr&Lbit) && RD_is(15)) {         		/* MCR in FPU with Rd=r15: comparison (ugh) */
                    if (!(instr&(1<<23))) goto lfUndefined;		/* unused operation */
                    mnemonic = _i_cmf[(instr&(3<<21)) >> 21];
                    format   = "9,+";
                    if (instr&((1<<19)+(7<<5)))
                        result.badbits=1;							/* size,rmode reseved */
                }
                else {							            /* normal FPU MCR/MRC */
                    t_value op20 = instr&(15<<20);
                    if (op20>=6<<20) goto lgUndefined;
                    mnemonic = _i_flt[op20>>20];
                    if (op20==0) {					             /* FLT instruction */
                        format = "9,3";
                        { char c = "SDE*"[((instr>>7)&1) + ((instr>>18)&2)];
                        if (c=='*') goto lhUndefined; else *flagp++=c;
                        }
                        if (instr&15) result.oddbits=1;			/* Fm and const flag unused */
                    }
                    else {						              	/* not FLT instruction */
                        if (instr&((1<<7)+(1<<19)))
                            result.badbits=1;						/* size bits reserved */
                        if (op20==1<<20) {		                /* FIX instruction */
                            format = "3,+";
                            if (opts->flags&disopt_FIXS)
                                *flagp++ = "SDEP"[((instr>>7)&1) + ((instr>>18)&2)];
                            *flagp++ = "\0PMZ"[(instr&(3<<5))>>5];
                            if (instr&(7<<15)) result.oddbits=1;	/* Fn unused */
                            if (instr&(1<<3)) result.badbits=1;		/* no immediate consts */
                        }
                        else {					                /* neither FLT nor FIX */
                            format = "3";
                            if (instr&(3<<5)) result.badbits=1;		/* rmode reserved */
                            if (instr&(15+(7<<15))) result.oddbits=1; /* iFm, Fn unused */
                        }
                    }
                }
            }
            else {								          /* some other copro number. Not FPU. */
                mnemonic = _i_mcr_mrc[(instr&Lbit)>>20];
                format = ";,:,3,\005,\001-";
            }
        }
        else {								   			/* CDP. */
            if (CP_is(1)) {						    		/* copro 1: FPU. */
                mnemonic = _i_copro[
                          ((instr&(15<<20)) >> 20)			/* opcode   -> bits 5432 */
                        + ((instr&(1<<15)) >> 11)];			/* monadicP -> bit 6 */
                format = (instr&(1<<15)) ? "8,+" : "8,9,+";
                *flagp++ = "SDE*"[((instr>>7)&1) + ((instr>>18)&2)];
                *flagp++ = "\0PMZ"[(instr&(3<<5))>>5];        /* foregoing relies on this being the last flag! */
                if (*mnemonic=='*' || *flagchars=='*') goto liUndefined;
            }
            else {									          /* some other copro number. Not FPU. */
                mnemonic = "CDP";
                format   = ";,),\004,\005,\001-";
            }
        }
        break;
    case 15:										      /* SWI */
       // not used in Canon firmware, treat as data
       /*
       mnemonic = "SWI";
       format   = "$";
       break;
       */
       goto lUndefined;
      

/* Nasty hack: this is code that won't be reached in the normal
 * course of events, and after the last case of the switch is a
 * convenient place for it.
 */
laUndefined:
        strcpy(result.text, "Undefined instruction a");  	  goto lUndefined ;
lbUndefined:
        strcpy(result.text, "Undefined instruction b"); 	  goto lUndefined ;
lcUndefined:
        strcpy(result.text, "Undefined instruction c"); 	  goto lUndefined ;
ldUndefined:
        strcpy(result.text, "Undefined instruction d"); 	  goto lUndefined ;
leUndefined:
        strcpy(result.text, "Undefined instruction e");	 	  goto lUndefined ;
lfUndefined:
        strcpy(result.text, "Undefined instruction f"); 	  goto lUndefined ;
lgUndefined:
        strcpy(result.text, "Undefined instruction g"); 	  goto lUndefined ;
lhUndefined:
        strcpy(result.text, "Undefined instruction h"); 	  goto lUndefined ;
liUndefined:
        strcpy(result.text, "Undefined instruction i"); 	  goto lUndefined ;
ljUndefined:
        strcpy(result.text, "Undefined instruction j"); 	  goto lUndefined ;
lkUndefined:
        strcpy(result.text, "Undefined instruction k"); 	  goto lUndefined ;
llUndefined:
        strcpy(result.text, "Undefined instruction l"); 	  goto lUndefined ;
lUndefined:	  
        // treat every undefined instruction as data
        /*
        result.undefined = 1;
 	    result.instr = instr ;
        return &result;
        */
        result.badbits = 1;     // cause 'erroneous instructions' check below to convert this to data
        break;
    }

    if (result.oddbits || result.badbits) { // treat erroneous instructions as data
        result.instr = instr ;
        mnemonic = ".long";
        format = "=";
        instr = 14 << 28; // no condition code please, see below
        result.oddbits = result.badbits = 0; // no need for error display
        result.text[0] = flagchars[0] = 0;
    }

    *flagp=0;

    /* PHASE 2. Produce string. */

    { char * op = result.text;

    /* 2a. Mnemonic. */

    op = append(op,mnemonic);

    /* 2b. Condition code. */

    {
        t_value cond = instr>>28;
        if (cond!=14) {
            const char * ip = _i_cond[cond];
            *op++ = *ip++;
            *op++ = *ip;
        }
    }

    /* 2c. Flags. */

    { const char * ip = flagchars;
    while (*ip) *op++ = *ip++;
    }

    /* 2d. A tab character. */

    do {
        *op++ = ' ';
        *op = 0 ;
    } while ( strlen( result.text ) < 8 ) ;

    /* 2e. Other stuff, determined by format string. */

    { const char * ip = format;
    char c;

    char * * regnames = opts->regnames;
    t_value     oflags   = opts->flags;

    while ((c=*ip++) != 0) {
        switch(c) {
          case '=':
            if (((unsigned long)result.instr > (unsigned long)addr) && ((unsigned long)result.instr < (unsigned long)addr+0x1000)) { // looks like a jumptable
                result.addrstart = op;
                op = sub_hex8(fw, op, result.instr);
            }
            else {
                op = yhex8(op, result.instr);
            }
            break;
    case '$':
        result.is_SWI = 1;
        result.swinum = instr&0x00FFFFFF;
        result.addrstart = op;
        if (oflags&disopt_SWInames) {
            swiname(result.swinum, op, 128-(op-result.text));
            op += strlen(op);
        }
        else
            op += sprintf(op, "&%X", result.swinum);
        break;
    case '%':
        *op++='{';
        { t_value w = instr&0xFFFF;
        int i=0;
        while (w) {
            int j;
            while (!(w&(1ul<<i))) ++i;
            for (j=i+1; w&(1ul<<j); ++j) ;
            --j;
            /* registers [i..j] */
            op = append(op, regnames[i]);
            if (j-i) {
                *op++ = (j-i>1) ? '-' : ',';
                op = append(op, regnames[j]);
            }
            i=j; w=(w>>(j+1))<<(j+1);
            if (w) *op++=',';
        }
        }
        *op++='}';
        if (instr&(1<<22)) *op++='^';
        break;
    case '&':
        // address target = ((addr+8 + ((((int)instr)<<8)>>6)) & 0x03FFFFFC) | ( addr&0xFC000000) ;
        { t_address target = ((t_address) addr ) + 8 + ((t_address) ((((int)instr)<<8) >>6 )) ;
        result.addrstart = op;
        op = sub_hex8(fw, op, target);
        result.target_type = target_Code;
        result.target      = target;
        }
        break;
    case '\'':
lPling:
        if (instr&Wbit) *op++='!';
        break;
    case '(':
        *op++ = (char)('0'+fpn);
        break;
    case ')':
        { t_value w = (instr>>20)&15;
        if (w>=10) { *op++='1'; *op++=(char)('0'-10+w); }
        else *op++=(char)(w+'0');
        }
        break;

    case '*':
    case '.':
        if (instr&Ibit) {
            /* immediate constant */
            t_value imm8 = (instr&255);
            t_value rot  = (instr>>7)&30;
            //if (rot && !(imm8&3) && c=='*') {
            //  /* Funny immediate const. Guaranteed not '.', btw */
            //  *op++='#'; // *op++='&';
            //  *op++='0'; // added in 2.04 to indicate this is a hex value
            //  *op++='x'; //   ditto
            //  *op++="0123456789ABCDEF"[imm8>>4];
            //  *op++="0123456789ABCDEF"[imm8&15];
            //  *op++=',';
            //  op = num(op, rot, 10);
            //}
            //else {
            imm8 = (imm8>>rot) | (imm8<<(32-rot));
            if (c=='*') {
                *op++='#';
                if (imm8>256 && ((imm8&(imm8-1))==0)) {
                    /* only one bit set, and that later than bit 8.
                    * Represent as 1<<... .
                    */
                    //op = append(op,"1<<");
                    { int n=0;
                    while (!(imm8&15)) { n+=4; imm8=imm8>>4; }
                    /* Now imm8 is 1, 2, 4 or 8. */
                    n += (0x30002010 >> 4*(imm8-1))&15;
                    n= 1<<n ;
                    op = yhex8(op, n);
                    }

                }
                else {
                    if (((int)imm8)<0 && ((int)imm8)>-100) {
                        *op++='-'; imm8=-imm8;
                    }
                    op = num(op, imm8, 10);
                }
            }
            else {
                t_address a = addr+8;
                if (instr&(1<<22)) a-=imm8; else a+=imm8;
                result.addrstart=op;
                op = xhex8(op, a);
                result.target=a; result.target_type=target_Unknown;
            }
            //}
        }
        else {
            /* rotated register */
            const char * rot = _i_lsl_lsr[(instr&(3<<5)) >> 5];
            op = append(op, regnames[instr&15]);
            if (instr&(1<<4)) {
                /* register rotation */
                if (instr&(1<<7)) goto ljUndefined;
                *op++=','; if (oflags&disopt_CommaSpace) *op++=' ';
                op = append(op,rot); *op++=' ';
                op = append(op,regnames[(instr&(15<<8))>>8]);
            }
            else {
                /* constant rotation */
                t_value n = instr&(31<<7);
                if (!n) {
                    if (!(instr&(3<<5))) break;
                    else if ((instr&(3<<5))==(3<<5)) {
                        op = append(op, ",RRX");
                        break;
                    }
                    else n=32<<7;
                }
                *op++ = ','; if (oflags&disopt_CommaSpace) *op++=' ';
                op = num(append(append(op,rot),"#"),n>>7,32);
            }
        }
        break;
    case '+':
        if (instr&(1<<3)) {
            t_value w = instr&7;
            *op++='#';
            if (w<6) *op++=(char)('0'+w);
            else op = append(op, w==6 ? "0.5" : "10");
        }
        else {
            *op++='f';
            *op++=(char)('0'+(instr&7));
        }
        break;
    case ',':
        *op++=',';
        if (oflags&disopt_CommaSpace) *op++=' ';
        break;
    case '-':
        { t_value w = instr&(7<<5);
        if (w) {
            *op++=',';
            if (oflags&disopt_CommaSpace) *op++=' ';
            *op++ = (char)('0'+(w>>5));
        }
        }
        break;
    case '/':
        result.addrstart = op;
        *op++='[';

        op = append(op, regnames[(instr&RNbits)>>16]);

        if (!(instr&Pbit)) *op++=']';

        *op++=','; 

        if (oflags&disopt_CommaSpace) *op++=' ';

        /* For following, NB that bit 25 is always 0 for LDC, SFM etc */
        if (instr&Ibit) {
            /* shifted offset */
            if (!(instr&Ubit)) *op++='-';
            /* We're going to transfer to '*', basically. The stupid
            * thing is that the meaning of bit 25 is reversed there;
            * I don't know why the designers of the ARM did that.
            */
            instr ^= Ibit;
            if (instr&(1<<4)) {

                if (is_v4 && !(instr&(15<<8))) {
                    ip = (instr&Pbit) ? "0]" : "0";
                    break;
                }
            }
            /* Need a ] iff it was pre-indexed; and an optional ! iff
            * it's pre-indexed *or* a copro instruction,
            * except that FPU operations don't need the !. Bletch.
            */
            if (instr&Pbit) ip="*]'";
            else if (instr&(1<<27)) {
                if (CP_is(1) || CP_is(2)) {
                    if (!(instr&Wbit)) goto lkUndefined;
                    ip="*";
                }
                else ip="*'";
            }
            else ip="*";
        }
        else {
            /* immediate offset */
            t_value offset;
            if (instr&(1<<27)) {      /* LDF or LFM or similar */
                offset = (instr&255)<<2;
            }

            else if (is_v4) offset = (instr&15) + ((instr&(15<<8))>>4);
            else {            /* LDR or STR */
                offset = instr&0xFFF;
            }

            if ( offset == 0 ){
                if (oflags&disopt_CommaSpace) op-- ;
                op-- ; *op++=']'; goto lPling; }

            *op++='#';
            if (!(instr&Ubit)) 
            {
                if (offset) *op++='-';
                else result.oddbits=1;
                result.offset = -offset;
            }
            else result.offset = offset;

            op = num(op, offset, 10);
            if (RN_is(15) && (instr&Pbit)) 
            {
                /* Immediate, pre-indexed and PC-relative. Set target. */
                result.target_type = poss_tt;
                result.target      = (instr&Ubit) ? addr+8 + offset
                    : addr+8 - offset;
                if (!(instr&Wbit)) 
                {
                    /* no writeback, either. Use friendly form. */
                    if (RD_is(15))
                        op = sub_ahex8(fw, result.addrstart, result.target);
                    else
                    op = ahex8(result.addrstart, result.target);
                    break;
                }
            }
            if (instr&Pbit) { *op++=']'; goto lPling; }
            else if (instr&(1<<27)) {
                if (CP_is(1) || CP_is(2)) {
                    if (!(instr&Wbit)) goto llUndefined;
                }
                else goto lPling;
            }
        }
        break;

    case '0': case '1': case '2': case '3': case '4':
        op = append(op, regnames[(instr>>(4*(c-'0')))&15]);
        break;
    case '5': case '6': case '7': case '8': case '9':
        *op++='f';
        *op++=(char)('0' + ((instr>>(4*(c-'5')))&7));
        break;
    case ':':
        *op++ = (char)('0' + ((instr>>21)&7));
        break;
    case ';':
        op = reg(op, 'p', instr>>8);
        break;
    default:
        if (c<=5)
            op = reg(op, 'c', instr >> (4*(c-1)));
        else *op++ = c;
        }
    }
    *op=0;
    }
    }

    /* DONE! */

    return &result;
}

//------------------------------------------------------------------------------------------------------------
t_address addr, last_used_addr;

void disassemble1(firmware *fw, t_address start, t_value length)
{
    t_value w;

    free(dcd_list);
    dcd_list = new_list();
    free(branch_list);
    branch_list = new_list();

    // Do three passes; but don't generate any code
    int pass;
    for ( pass = 1 ; pass <=3 ; pass++ )
    {
        if ( pass == 2 ) 
        {
            struct lnode* lptr = dcd_list->head;
            while ( lptr != NULL  ) 
            {		
                addr = (t_address) lptr->address ;
                w = fwval(fw,adr2idx(fw,addr));
                lptr->data = w ;
                lptr = lptr->next ;
            }
        }
        else    // pass 1 & 3
        {
            addr = start ;
            t_value word_count = 0 ;

            while (word_count < length )
            {
                w = fwval(fw,adr2idx(fw,addr));
                instr_disassemble(fw, w, addr, &options);

                struct lnode* lptr = l_search(dcd_list,addr);
                if (!lptr) 
                    last_used_addr = addr;

                word_count++ ;
                addr += 4;
            }
        }
    }
}

void disassemble(firmware *fw, FILE *outfile, t_address start, t_value length)
{
    t_value w;

    int dcd_mode_on = 0;

    // Only need 1 pass here - assumes disassemble1 called previously
    addr = start ;
    t_value word_count = 0 ;

    while (word_count < length )
    {
        w = fwval(fw,adr2idx(fw,addr));

        pInstruction instr = instr_disassemble(fw, w, addr, &options);

        if (l_search(branch_list, addr))
        {
            fprintf(outfile,"\n\"loc_%08X:\\n\"\n", addr);
            dcd_mode_on = 0;
        }	
        struct lnode* lptr = l_search(dcd_list,addr);
        if ( lptr  || dcd_mode_on ) 
        {
            if ((options.flags & disopt_exclude_dcd) == 0)
                fprintf(outfile,"\"dword_%8.8X  DCD 0x%X \\n\"\n", addr , w);
            dcd_mode_on = 1;
            /*
            t_value aword ;
            int i ;
            unsigned char ch ;
            aword = lptr->data ;
            for ( i=0 ; i< 4 ; i++ )
            {
            ch = aword & 0xFF ;
            if ( (ch>=0x20) && ( ch < 0x80) ) fprintf(outfile," %c" , ch );
            else fprintf(outfile,"_" );
            aword = aword >> 8 ;
            }
            fprintf(outfile, "\n" ) ;
            */
        }	
        else 
        {
            if (instr->undefined || instr->badbits || instr->oddbits) {
                fprintf(outfile,"Error: ");
                if (instr->undefined) fprintf(outfile,"[---undefined instr---] 0x%8.8X     ", w);
                if (instr->badbits) fprintf(outfile,  "[---illegal bits---] 0x%8.8X        ", w);
                if (instr->oddbits) fprintf(outfile,  "[---unexpected bits---] 0x%8.8X     ", w);
                if ( !((instr->undefined) || (instr->badbits) || (instr->oddbits)) ) 
                    fprintf(outfile,  "[---unknown error---] 0x%8.8X       ", w);
                if ( options.flags & disopt_print_address_mode)
                {
                    fprintf(outfile,"// rom:%.8x  0x%8.8X \n", addr, w);
                }								
                else fprintf(outfile,"\n");													
            }
            else
            {
                strcat( instr->text, " \\n\"") ;
                if (options.flags & disopt_line_numbers) fprintf(outfile,"/*%3d*/",(addr - options.start_address) / 4 + 1);
                char *indent = "\"    ";
                if (options.flags & (disopt_comment_lines|disopt_nullsub_call))
                    indent = "//\"  ";
                if (options.flags & disopt_indent_mneumonics_mode)
                    fprintf(outfile,"      ");
                if (options.flags & disopt_print_address_mode)
                {
                    fprintf(outfile,"%s%-40s // rom:%.8x  0x%8.8X", indent, instr->text, addr, w);
                }								
                else fprintf(outfile,"%s%s", indent, instr->text);

                if ((options.flags & disopt_patch_branch) || (options.flags & disopt_patch_value))
                {
                    if (patch_old_func_name)
                        fprintf(outfile,"  // --> Patched. Old value = _%s.", patch_old_func_name);
                    else
                        fprintf(outfile,"  // --> Patched. Old value = 0x%X.", patch_old_val);
                    if ((options.flags & disopt_patch_comment) && patch_comment)
                    {
                        fprintf(outfile, " %s", patch_comment);
                    }
                }
                else if ((options.flags & disopt_patch_comment) && patch_comment)
                {
                    fprintf(outfile, "  // %s", patch_comment);
                }
                else if (options.flags & disopt_nullsub_call)
                {
                    fprintf(outfile,"  // --> Nullsub call removed.");
                }
                fprintf(outfile,"\n");
            }
        }

        word_count++ ;
        addr += 4;
    }
}

t_address find_end(firmware *fw, t_address start)
{
    int i;
    start = adr2idx(fw,start);
    for (i=0; i<500; i++, start++)
        if ((fwval(fw,start+1) & 0xFFFF4000) == 0xE92D4000)  // STMFD SP!, {...,LR}
        {
            int j;
            for (j=0; j<50; j++, start--)
            {
                if ((fwval(fw,start) & 0xFF000000) == 0xEA000000)  // B
                {
                    return idx2adr(fw,start);
                }
                if ((fwval(fw,start) & 0xFFFF8000) == 0xE8BD8000)  // LDMFD SP!, {...,PC}
                {
                    return idx2adr(fw,start);
                }
                if ((fwval(fw,start) & 0xFFFFFFF0) == 0xE12FFF10)  // BX
                {
                    return idx2adr(fw,start);
                }
                if ((fwval(fw,start) & 0xFFFFF000) == 0xE49DF000)  // LDR PC,[SP,...
                {
                    return idx2adr(fw,start);
                }
            }
            return 0;
        }
    return 0;
}

//------------------------------------------------------------------------------------------------------------

void swiname(t_value w, char * s, size_t sz) { return; }

//------------------------------------------------------------------------------------------------------------
