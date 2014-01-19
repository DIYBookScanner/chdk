/*=====================================================================================================
	chdk_dasm.h
	
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

typedef unsigned int t_address;
typedef unsigned int t_value;

#define declstruct(name) typedef struct name s##name, * p##name
#define defstruct(name) struct name
#define defequiv(new,old) typedef struct old s##new, * p##new

declstruct(DisOptions);

#define disopt_SWInames                 0x001   /* use names, not &nnnn */
#define disopt_CommaSpace               0x002   /* put spaces after commas */
#define disopt_FIXS                     0x004   /* bogus FIX syntax for ObjAsm */
#define disopt_print_address_mode       0x008   /* output in plain mode - no address comments */
#define disopt_indent_mneumonics_mode   0x010   /* indent mneumonics additionally */
#define disopt_patch_comment            0x020   // add comment to patched instruction
#define disopt_exclude_dcd              0x040   // Don't write 'DCD' disassembly
#define disopt_nullsub_call             0x080   // Call to nullsub detected
#define disopt_patch_branch             0x100   // patch address in next instruction
#define disopt_patch_value              0x200   // patch value in next instruction
#define disopt_remember_branches        0x400   // enable/disable storing branch addresses
#define disopt_comment_lines            0x800   // enable/disable commenting out of instructions
#define disopt_line_numbers             0x1000  // print line number of firmware code

defstruct(DisOptions) {
    t_value flags;
    char * * regnames;                  /* pointer to 16 |char *|s: register names */
    t_address ROM_start;
    t_address ROM_end;
    t_address start_address;
    t_address end_address;
};

extern t_address addr, last_used_addr;
extern sDisOptions options;
extern struct llist *branch_list;
extern char *patch_func_name;
extern t_address patch_new_val;
extern t_address patch_old_val;
extern int patch_ref_address[20];
extern char patch_ref_name[20][256];
extern int save_patch_ref;
extern char *patch_comment;

struct lnode * l_search(struct llist *ls, t_address address);
void l_remove(struct llist *ls, t_address addr);
t_address find_end(firmware *fw, t_address start);
void disassemble1(firmware *fw, t_address start, t_value length);
void disassemble(firmware *fw, FILE *outfile, t_address start, t_value length);
