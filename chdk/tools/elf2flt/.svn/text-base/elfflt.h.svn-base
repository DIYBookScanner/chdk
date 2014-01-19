#ifndef __ELFFLT_H__
#define __ELFFLT_H__

#include <unistd.h>
#include "elf.h"
#define USE_INT32_FOR_PTRS      // To avoid pointer size issues in structs in flt.h
#include "flt.h"

#define ELFFLT_OK                  0
#define ELFFLT_BAD_ELF_HEADER      1
#define ELFFLT_NO_SYMTAB           2
#define ELFFLT_NO_STRTAB           3
#define ELFFLT_NO_TEXT             4
#define ELFFLT_SYMBOL_NOT_FOUND    5
#define ELFFLT_SEGMENT_NOT_FOUND   6
#define ELFFLT_NO_MODULEINFO       7
#define ELFFLT_UNHANDLED_RELOC     8
#define ELFFLT_OUTOF_RANGE         9
#define ELFFLT_INPUT_ERROR         10
#define ELFFLT_OUTPUT_ERROR        11
#define ELFFLT_UNSAFE_SYMBOL       12

/**
 * \brief      Load and relocate an ELF file.
 */
int elfloader_load(char* filename, char* fltfile );


struct relevant_section {
  unsigned char number;     //#of section
  uint32_t offset;      	//start offset in .elf file
  char *address;            //ptr in memory

  int size;
  char *name;           //name
  uint32_t base_addr;   //start addr in arm-objdump (to compare)
  uint32_t flat_offset; //start offset in .flt file
  
  uint32_t relaoff;		// fileoffset of related relocation section
  uint32_t relasize;	// size of related relocation section
};

extern struct relevant_section bss, data, rodata, text;

extern char* flat_buf;
extern struct flat_hdr* flat;

typedef uint32_t reloc_record_t;

extern uint32_t flat_reloc_count;
extern reloc_record_t *flat_reloc;
extern reloc_record_t *flat_reloc_cur;

typedef struct
{
    uint32_t offs;			// offset of changed record from begin of flat
	uint32_t importidx;     // index of symbol in chdk_export_table
} import_record_t;

extern uint32_t flat_import_count;
extern import_record_t* flat_import_buf; // point to begining of import table in memory
extern import_record_t* flat_import_cur; // ptr to current import value (for write_import)

extern unsigned int strtaboff;
extern unsigned int symtaboff;


int apply_realloc( struct relevant_section* base_sect, 
		   struct elf32_rela *rela, 
		   struct relevant_section* tgt_sect, 
		   struct elf32_sym *sym,
           int symidx
		 );

int apply_import( struct relevant_section* base_sect, 
		   struct elf32_rela *rela, 
		   int importidx, 
		   struct elf32_sym *sym,
           int symidx
		 );

#endif /* __ELFFLT_H__ */

