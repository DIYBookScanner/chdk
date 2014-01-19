/*
 * Main elf2flt convertion processing
 *
 *  Target is modified BINARY FLAT
 *
 * 	(c)2011	Sergey Taranenko aka tsvstar
 *
 */

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "myio.h"
#include "elfflt.h"

#define DEBUGPRINTF(...) do {} while (0)

const int SYMB_SIZE = 60;

struct relevant_section bss, data, rodata, text;

const static unsigned char elf_magic_header[] =
  {0x7f, 0x45, 0x4c, 0x46,  /* 0x7f, 'E', 'L', 'F' */
   0x01,                    /* Only 32-bit objects. */
   0x01,                    /* Only LSB data. */
   0x01,                    /* Only ELF version 1. */
  };


/*  strtaboff   - fileoffset of .strtab section
    symtaboff   - fileoffset of .symtab section
    symtabsize - size of .symtab
*/
unsigned int /*short*/ symtaboff = 0, symtabsize;
unsigned int /*short*/ strtaboff = 0, strtabsize;


char* flat_buf;         // point to buffer of flat file
struct flat_hdr* flat;  // point to flat_buf, but casted to header

uint32_t flat_reloc_count;
reloc_record_t* flat_reloc;   // point to begining of relocation table in memory
reloc_record_t* flat_reloc_cur; // ptr to current reloc value (for write_allocate)

uint32_t flat_import_count;
import_record_t* flat_import_buf; // point to begining of import table in memory
import_record_t* flat_import_cur; // ptr to current import value (for write_import)

char* flag_sym_display=0;  // buffer of flags. [symidx]=0 not_showed_yet, 1 already_shown
int flag_unsafe_sym=0;      // =1 if one of imported symbol is from stoplist

/*---------------------------------------------------------------------------*/
static
struct relevant_section* find_section(int idx)
{
    if(idx == bss.number)
          return &bss;
    if(idx == data.number) 
          return &data;
    if(idx == text.number) 
          return &text;
    if(idx == rodata.number) 
          return &rodata;
    return NULL;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

static int last_found_symidx = -1;

static struct elf32_sym* 
  find_symbol(const char *symbol)
{
  static struct elf32_sym s;
  unsigned int a;
  char name[SYMB_SIZE];
  struct relevant_section *sect;
  int ret;
  
  last_found_symidx=-1;

  for(a = symtaboff; a < symtaboff + symtabsize; a += sizeof(s)) {
    ret = b_seek_read(a, (char *)&s, sizeof(s));
    if (ret < 0) return NULL;

    last_found_symidx++;
    if(s.st_name != 0) {
      ret = b_seek_read(strtaboff + s.st_name, name, sizeof(name));
	  name[sizeof(name)-1]=0;
      if (ret < 0) return NULL;
      
      if(strcmp(name, symbol) == 0) {
        sect = find_section(s.st_shndx);
        if (!sect)
          return NULL;
		return &s;
      }
    }
  }
  return NULL;
}

/*---------------------------------------------------------------------------*/
static uint32_t 
  find_symbol_inflat(const char *symbol, struct relevant_section *have_to_be_sect)
{
  struct elf32_sym* s;
  struct relevant_section *sect;

  s = find_symbol(symbol);
  if ( !s ) {
	if ( FLAG_WARNSYMBOL )
    	PRINTERR(stderr, "Warning: not found '%s' symbol\n", symbol);
    return 0;
  }
  sect = find_section(s->st_shndx);
  if ( sect==0 ) {
	if ( FLAG_WARNSYMBOL )
    	PRINTERR(stderr, "Warning: unknown section of '%s' symbol\n",symbol); 
    return 0;
  }
  if ( have_to_be_sect && have_to_be_sect->number != sect->number ) {
	if ( FLAG_WARNSYMBOL )
    	PRINTERR(stderr, "Warning: wrong section of '%s' symbol - %s while required %s\n", 
				symbol, sect->name, have_to_be_sect->name );
    return 0;
  }

  return sect->flat_offset + s->st_value;
}

/*---------------------------------------------------------------------------*/
static int
relocate_section( struct relevant_section* base_sect)
{
  /* section_beg_ptr added; runtime start address of current section */
  struct elf32_rela rela; /* Now used both for rel and rela data! */
  struct elf32_sym s;
  unsigned int a;
  char name[SYMB_SIZE];
  struct relevant_section *tgtsect;
  int ret;

  if ( FLAG_VERBOSE )
   	  printf(">> elf2flt: relocate %s\n", base_sect->name);

  if ( base_sect->size <= 0 )
    return ELFFLT_OK;
  
  int rel_size = sizeof(struct elf32_rel);
  unsigned int rel_section = base_sect->relaoff;
  unsigned int rel_sect_size = base_sect->relasize;

  int relidx=0;
  int rv = ELFFLT_OK;

  for(a = rel_section; a < rel_section + rel_sect_size; a += rel_size, relidx++) {
    ret = b_seek_read(a, (char *)&rela, rel_size);
	if ( FLAG_VERBOSE )
    	printf("rel_load %x: offs=0x%x, info=0x%x [type=%d]\n",a,rela.r_offset, rela.r_info, ELF32_R_TYPE(rela.r_info));
    if (ret < 0) return ELFFLT_INPUT_ERROR;

	int symidx = ELF32_R_SYM(rela.r_info);            
	if ( symidx*sizeof(struct elf32_sym) >= symtabsize ) {
        PRINTERR(stderr, "elf2flt unknown symbolidx #%d for relocation %s:%d\n", symidx, base_sect->name,relidx);
    	return ELFFLT_INPUT_ERROR;
	}
    ret = b_seek_read((symtaboff +
                     sizeof(struct elf32_sym) * symidx),
                    (char *)&s, sizeof(s));
    if (ret < 0) return ELFFLT_INPUT_ERROR;

    ret = b_seek_read( strtaboff + s.st_name, name, sizeof(name));
	name[sizeof(name)-1]=0;
    if (ret < 0) return ELFFLT_INPUT_ERROR;

	if ( s.st_shndx == 0 )
	{
	  if ( !flag_sym_display ) {
		int num_syms = 1+ symtabsize / sizeof(struct elf32_sym);
		flag_sym_display = malloc( num_syms);
		memset(flag_sym_display,0, num_syms);				
	  }

	  int importidx=find_import_symbol(name);
	  if (importidx==0 ) {
          if ( flag_sym_display[symidx] )
			continue;
          flag_sym_display[symidx]=1;

          PRINTERR(stderr, "elf2flt unknown symbol: '%s'\n", name);
          rv = ELFFLT_SYMBOL_NOT_FOUND;
		  continue;
      }
      if ( stoplist_check(name) )
	      { flag_unsafe_sym=1; }

      ret = apply_import( base_sect, &rela, importidx, &s, relidx);
      if (ret != ELFFLT_OK) return ret;
	}
	else
	{
      tgtsect = find_section( s.st_shndx );

      if ( !tgtsect ) {
          PRINTERR(stderr, "elf2flt unknown segment %d for name: '%s'\n", s.st_shndx, name);
          return ELFFLT_SEGMENT_NOT_FOUND;
      }

      ret = apply_realloc( base_sect, &rela, tgtsect, &s, relidx /*addr - symsect->address*/);
      if (ret != ELFFLT_OK) return ret;
    }
  }
  return rv;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
void dump_symtable()
{
  struct elf32_sym s;
  unsigned int a;
  int ret;
  
  printf("\n\nDump symbols [0x%x .. +0x%x]\n",symtaboff, symtabsize);
  for(a = symtaboff; a < symtaboff + symtabsize; a += sizeof(s)) 
  {
    ret = b_seek_read(a, (char *)&s, sizeof(s));
    if (ret < 0) return ;

    char name[SYMB_SIZE];
    memset(name,0, sizeof(name));    
    ret = b_seek_read(strtaboff + s.st_name, name, sizeof(name)-2);

    printf("SYMBOL %x [%02x: %-15s] - value=0x%x, size=%d, info=0x%x, section=%d\n", a, s.st_name, name, s.st_value, s.st_size, s.st_info, s.st_shndx);    
  }
}

void dump_section(char* name, unsigned char *ptr, int size )
{
    printf("\n\nDump %s",name);
    
    int i;
    for(i=0;i<size;i++)
    {
        if ((i % 16)==0 ) {printf("\n%06x:  ",i);}
        if ((i % 16)==8 ) {printf("| ");}
        printf("%02x ",ptr[i]);
    }
    printf("\n");
}

static 
void print_offs(char *prefix, int offs, char* postfix)
{
    int secoffs = 0;
    char* sect="unkn";
    
    if ( !offs ) {
        printf("%s 0x00000000 %s",prefix, postfix);
        return;
    }
    
    if ( offs >=flat->entry && offs<flat->data_start )
       { sect="text"; secoffs=flat->entry;}
    else if  ( offs >=flat->data_start && offs<flat->bss_start )
       { sect="data"; secoffs=flat->data_start;}
    else if  ( offs >=flat->bss_start && offs<flat->reloc_start )
       { sect="bss"; secoffs=flat->bss_start;}         
    printf("%s 0x%08x (%s+0x%08x)%s",prefix, offs,sect,offs-secoffs,postfix);
}


char* get_flat_string( int32_t offs )
{
   static char buf[200];

    if  ( offs <0 )
	{
		sprintf(buf," LANGID %d",-offs);
		return buf;
	}

    if  ( offs >=flat->bss_start || offs<flat->data_start )
	  return "";

	strncpy( buf, flat_buf+offs, sizeof(buf)-1);
	buf[sizeof(buf)-1]=0;
	return buf;
}


// Aligning up to int32 bound
static int
align4(int size)
{
    if  (size%4==0)
        return 0;
    return (4-size%4);
}


// Content of ____div0_from_arm
unsigned char div0_arm[12]  = { 0x00, 0xc0, 0x9f, 0xe5, 0x1c, 0xff, 0x2f, 0xe1, 0x00, 0x00, 0x00, 0x00 };
/*  2e0a90:	e59fc000 	ldr	ip, [pc, #0]	; 2e0a98 <____div0_from_arm+0x8>
  2e0a94:	e12fff1c 	bx	ip
  2e0a98:	002e0a8d 	.word	0x002e0a8d
*/

// Allow to replaced only at
uint32_t offs_div0_from_arm = 0;
uint32_t offs_divsi3_skip_div0_test = 0;
uint32_t offs__aeabi_uidiv = 0;

// GCC-LD do not produce ____div0_from_arm in -r mode and because this division work bad
// We add to the end of .text and replace __div0 for specific places with this value. 
int add_div0_arm()
{
  struct elf32_sym* s;
  int rv;
  int symidx;
  
  s = find_symbol("__div0");
  symidx = last_found_symidx;
  if ( !s) return ELFFLT_OK;

  if (s->st_shndx != text.number) {
	PRINTERR(stderr,"__div0 should be .text symbol\n");
	return ELFFLT_UNHANDLED_RELOC;
  }
  
  /*
  if  ( (text.size - s->st_value) != 3 ) {
	PRINTERR(stderr,"Warning! At %s __div0 is not on the end of .text. Doesn't check such case\n", filename_elf);
  }
  */


  // Prepare reloc used in added func
  struct elf32_rela rela;
  rela.r_info = symidx <<8;
  rela.r_info |= R_ARM_ABS32;   
  rela.r_offset = text.size+8;
  rela.r_addend = 0;

  // Append new func to the end of .text
  offs_div0_from_arm = text.size;
  memcpy( flat_buf+text.flat_offset+offs_div0_from_arm, div0_arm, sizeof(div0_arm) );
  text.size+=sizeof(div0_arm);

  // Apply reloc
  rv = apply_realloc( &text, &rela, &text, s, -1);

  // Detect allowed to patch points
  s = find_symbol(".divsi3_skip_div0_test");
  if ( s && s->st_shndx == text.number ) {
	 offs_divsi3_skip_div0_test = text.flat_offset + s->st_value + 0x114;
  }
  s = find_symbol("__aeabi_uidiv");
  if ( s && s->st_shndx == text.number ) {
	 offs__aeabi_uidiv = text.flat_offset + s->st_value + 0xec;
  }

  return rv;
}



/*---------------------------------------------------------------------------*/
int
elfloader_load(char* filename, char* fltfile)
{
  struct elf32_ehdr ehdr;
  struct elf32_shdr shdr;
  struct elf32_shdr strtable;
  unsigned int strs;
  unsigned int shdrptr;
  unsigned int nameptr;
  char name[12];
  
  int i;
  unsigned short shdrnum, shdrsize;

  int ret;

  /* Ensure that we have a correct and compatible ELF header. */
  ret = b_seek_read( 0, (char *)&ehdr, sizeof(ehdr));
  if (ret != sizeof(ehdr)) return ELFFLT_INPUT_ERROR;

  if(memcmp(ehdr.e_ident, elf_magic_header, sizeof(elf_magic_header)) != 0) {
    	PRINTERR(stderr, "ELF header problems\n");
    return ELFFLT_BAD_ELF_HEADER;
  }

  if ( FLAG_VERBOSE )
    	printf ("Grab section header\n");

  // Grab the section header.
  shdrptr = ehdr.e_shoff;
  ret = b_seek_read( shdrptr, (char *)&shdr, sizeof(shdr));
  if (ret != sizeof(shdr)) return ELFFLT_INPUT_ERROR;
  
  shdrsize = ehdr.e_shentsize;
  shdrnum = ehdr.e_shnum;

  if ( FLAG_VERBOSE )
    	printf ("Grab string table section\n");

  // Grab the string table section for the names of the sections. 
  ret = b_seek_read( ehdr.e_shoff + shdrsize * ehdr.e_shstrndx,
                             (char *)&strtable, sizeof(strtable));
  if (ret != sizeof(strtable)) return ELFFLT_INPUT_ERROR;
  strs = strtable.sh_offset;

  /* Parse segments headers to releavant_section entries.
		.text = actual code from the ELF file
		.data = initialized data
		.rodata = contains read-only data
		.bss = segment holds the size of the unitialized data segment
		.rel.text, .rel.data = relocation information for the contents 
					of the ".text" and ".data" segments, respectively.
		.symtab = symbol table for this file
		.strtab = points to the actual string names used by the symbol table.
  */


  // Zero size is indicator of unitialized (not found) section
  text.size = text.relasize = data.size = data.relasize =
    rodata.size = rodata.relasize = symtabsize = strtabsize = 0;

  bss.number = data.number = rodata.number = text.number = -1;
                
  shdrptr = ehdr.e_shoff;
  for(i = 0; i < shdrnum; ++i) {

    ret = b_seek_read( shdrptr, (char *)&shdr, sizeof(shdr));
	DEBUGPRINTF("==shdrptr=0x%x, sizeof=%d; size=0x%x\n",shdrptr,sizeof(shdr),shdrsize );
    if (ret != sizeof(shdr)) { PRINTERR(stderr, "input error at %s:%d :loaded%d",__FILE__,__LINE__,ret);return ELFFLT_INPUT_ERROR;}
    
    /* The name of the section is contained in the strings table. */
    nameptr = strs + shdr.sh_name;
	DEBUGPRINTF("==nameptr=%x(%x+%x), size=%d\n",nameptr,strs,shdr.sh_name,sizeof(name) );
    ret = b_seek_read( nameptr, name, sizeof(name));
    if (ret != sizeof(name)) {PRINTERR(stderr, "input error at %s:%d",__FILE__,__LINE__); return ELFFLT_INPUT_ERROR;}

	DEBUGPRINTF("==shdrptr=0x%x, sizeof=%d; size=0x%x\n",shdrptr,sizeof(shdr),shdrsize );
	if ( FLAG_DUMP_SECTIONS )
		printf ("Section #%d: %-15s [section header 0x%x, offset=0x%x, size %d, vma=0x%x]\n",i,name,shdrptr,
													shdr.sh_offset,shdr.sh_size, shdr.sh_addr);

    if(strncmp(name, ".text", 5) == 0) {
      text.number = i;
      text.offset = shdr.sh_offset;
      text.size = shdr.sh_size;
	  text.base_addr = shdr.sh_addr;
    } else if(strncmp(name, ".rel.text", 9) == 0) {
      text.relaoff = shdr.sh_offset;
      text.relasize = shdr.sh_size;
    } else if(strncmp(name, ".data", 5) == 0) {
      data.number = i;
      data.offset = shdr.sh_offset;
      data.size = shdr.sh_size;
	  data.base_addr = shdr.sh_addr;
    } else if(strncmp(name, ".rodata", 7) == 0) {
      rodata.number = i;
      rodata.offset = shdr.sh_offset;
      rodata.size = shdr.sh_size;
	  rodata.base_addr = shdr.sh_addr;
    } else if(strncmp(name, ".rel.rodata", 11) == 0) {
      rodata.relaoff = shdr.sh_offset;
      rodata.relasize = shdr.sh_size;
    } else if(strncmp(name, ".rel.data", 9) == 0) {
      data.relaoff = shdr.sh_offset;
      data.relasize = shdr.sh_size;
    } else if(strncmp(name, ".rela.", 6) == 0) {
      PRINTERR(stderr,"RELA relocs are not supported.");
      return ELFFLT_INPUT_ERROR;
    } else if(strncmp(name, ".symtab", 7) == 0) {
      symtaboff = shdr.sh_offset;
      symtabsize = shdr.sh_size;
    } else if(strncmp(name, ".strtab", 7) == 0) {
      strtaboff = shdr.sh_offset;
      strtabsize = shdr.sh_size;
    } else if(strncmp(name, ".bss", 4) == 0) {
      bss.size = shdr.sh_size;
      bss.number = i;
      bss.offset = 0;
    }

    shdrptr += shdrsize;
  }

  if(symtabsize == 0) {
    PRINTERR(stderr,"No symbol table found.");
    return ELFFLT_NO_SYMTAB;
  }
  if(strtabsize == 0) {
    PRINTERR(stderr,"No strings table found.");
    return ELFFLT_NO_STRTAB;
  }
  if(text.size == 0) {
    PRINTERR(stderr, "No .text segment found.");
  	return ELFFLT_NO_TEXT;
  }

  if ( (text.relasize + rodata.relasize+ data.relasize) <=0 ) {
      PRINTERR(stderr,"Found no reloc sections. Please link with -r -d options.\n");
      return ELFFLT_UNHANDLED_RELOC;
  }

  if (bss.size) {
    bss.address = (char *)malloc(bss.size);
    if (!bss.address) return ELFFLT_OUTPUT_ERROR;
  }
  if (data.size) {
    data.address = (char *)malloc(data.size);
    if (!data.address) return ELFFLT_OUTPUT_ERROR;
  }
  if (text.size) {
    text.address = (char *)malloc(text.size);
    if (!text.address) return ELFFLT_OUTPUT_ERROR;
  }
  if (rodata.size) {
    rodata.address =  (char *)malloc(rodata.size);
    if (!rodata.address) return ELFFLT_OUTPUT_ERROR;
  }

  rodata.name=".rodata";
  bss.name=".bss";
  text.name=".text";
  data.name=".data";



  b_seek_read(text.offset, text.address, text.size);
  b_seek_read(data.offset, data.address, data.size);
  b_seek_read(rodata.offset, rodata.address, rodata.size);

  if ( FLAG_DUMP_SOURCE ) {
    dump_section( text.name, (unsigned char *)text.address, text.size );
    dump_section( data.name, (unsigned char *)data.address, data.size );
    dump_section( rodata.name, (unsigned char *)rodata.address, rodata.size );
  }

  if ( FLAG_DUMP_SYMBOLS ) {
    dump_symtable();
  }

  if ( FLAG_DUMP_SYMBOLS || FLAG_DUMP_SOURCE || FLAG_VERBOSE )
	 printf("\n\n");

  if ( FLAG_VERBOSE )
   	 printf ("Prepare flat\n");

  int div0hack_size = sizeof(div0_arm);

  int flatmainsize = sizeof(struct flat_hdr)+text.size+div0hack_size+data.size+rodata.size+bss.size;  
  int flatrelocsize = text.relasize+rodata.relasize+data.relasize;


  // Take to account aligning to int32 each section  
  flatmainsize += align4(text.size) + align4(data.size) + align4(rodata.size) + align4(bss.size);
  
  flat_buf=malloc( flatmainsize+flatrelocsize );      
  if ( !flat_buf) { PRINTERR(stderr, "fail to malloc flat buf\n"); return ELFFLT_OUTPUT_ERROR;}
  memset(flat_buf, 0, flatmainsize+flatrelocsize);
  
  //import is subset of full reloc list, so same count is enough
  // but apply multiplier to take into account difference between sizeofs
  flat_import_buf=malloc( flatrelocsize* sizeof(import_record_t)/sizeof(reloc_record_t) );      		
  if ( !flat_import_buf) { PRINTERR(stderr, "fail to malloc flat import buf\n"); return ELFFLT_OUTPUT_ERROR;}
  memset(flat_import_buf, 0, flatrelocsize);

  // Fill flat with sections aligned to int32

  flat = (struct flat_hdr*) flat_buf;

  if ( FLAG_VERBOSE )
      printf(">>elf2flt: load segments\n");
  int offset=sizeof(struct flat_hdr);
  text.flat_offset = offset;
  memcpy( flat_buf+offset, text.address, text.size );
  DEBUGPRINTF("load .txt to %x (%x->%x)\n",offset,text.size,text.size+align4(text.size));
  offset+=text.size+div0hack_size+align4(text.size);


  rodata.flat_offset = offset;
  DEBUGPRINTF("load .rodata to %x (%x->%x)\n",offset,rodata.size,rodata.size+align4(rodata.size));
  memcpy( flat_buf+offset, rodata.address, rodata.size );
  offset+=rodata.size+align4(rodata.size);

  data.flat_offset = offset;
  DEBUGPRINTF("load .data to %x (%x->%x)\n",offset,data.size,data.size+align4(data.size));
  memcpy( flat_buf+offset, data.address, data.size );
  offset+=data.size+align4(data.size);

  bss.flat_offset = offset;
  DEBUGPRINTF(".bss to %x (%x->%x)\n",offset,bss.size,bss.size+align4(bss.size));
  DEBUGPRINTF("result=%x\n",  flatmainsize);

  // Initialize flat headers
  memcpy(flat->magic, FLAT_MAGIC_NUMBER, sizeof(flat->magic));       // Set magic (CHDK_FLAT)
  flat->rev = FLAT_VERSION;
  flat->entry = text.flat_offset;
  flat->data_start = rodata.flat_offset;
  flat->bss_start = bss.flat_offset;  
  flat->reloc_start = flatmainsize;
  flat_reloc_count = 0;

  flat->import_start = 0;
  flat_import_count = 0;
  
  flat_reloc = (reloc_record_t*)(flat_buf+flatmainsize);  
  flat_reloc_cur = flat_reloc;

  flat_import_cur = flat_import_buf;

  // _div0_arm hack
  add_div0_arm();

  flag_unsafe_sym = 0;

  // Do relocations
  ret = relocate_section( &text);
  if(ret != ELFFLT_OK)
      return ret;  
  ret = relocate_section( &rodata);
  if(ret != ELFFLT_OK)
      return ret;
  ret = relocate_section( &data);
  if(ret != ELFFLT_OK)
      return ret;

  if ( flag_unsafe_sym )
      return ELFFLT_UNSAFE_SYMBOL;

  flat->import_start = flat->reloc_start+flat_reloc_count*sizeof(reloc_record_t);

  // Init offsets to the entry symbols
                  
  if ( FLAG_VERBOSE )
   	  printf(">>elf2flt: lookup entry symbols\n");

  flat->_module_info_offset = find_symbol_inflat("_module_info", &data );
  if ( flat->_module_info_offset <=0 ) {
    PRINTERR(stderr, "No or invalid section of _module_info. This symbol should be initialized as ModuleInfo structure.\n");
    return ELFFLT_NO_MODULEINFO;
  }

  struct ModuleInfo* _module_info = (struct ModuleInfo*) (flat_buf + flat->_module_info_offset);
  if ( _module_info->magicnum != MODULEINFO_V1_MAGICNUM ) 
  {
    PRINTERR(stderr, "Wrong _module_info->magicnum value. Please check correct filling of this structure\n");
    return ELFFLT_NO_MODULEINFO;
  }
  if ( _module_info->sizeof_struct != sizeof(struct ModuleInfo) ) 
  {
    PRINTERR(stderr, "Wrong _module_info->sizeof_struct value. Please check correct filling of this structure\n");
    return ELFFLT_NO_MODULEINFO;
  }

  // Group import relocations
  //  Input = array of offset/index pairs - one for each address to be relocated to a core CHDK symbol
  //  Output = list of entries of the form:
  //        Index, Offset1 | (N<<24), Offset2, ..., OffsetN
  //  where each offset is a reference to the same core CHDK symbol
  uint32_t *new_import_buf = malloc(flat_import_count*3*sizeof(uint32_t));
  uint32_t new_import_cnt = 0;
  int process = 1;
  while (process)
  {
      process = 0;
      for (i=0; i<flat_import_count; i++)
      {
          if (flat_import_buf[i].offs != 0)
          {
              process = 1;
              int cnt = 0;
              uint32_t idx = flat_import_buf[i].importidx;
              new_import_buf[new_import_cnt++] = idx;
              int pcnt = new_import_cnt;
              int j;
              for (j=0; j<flat_import_count; j++)
              {
                  if (flat_import_buf[j].importidx == idx)
                  {
                      new_import_buf[new_import_cnt++] = flat_import_buf[j].offs;
                      flat_import_buf[j].offs = 0;
                      cnt++;
                  }
              }
              new_import_buf[pcnt] = (cnt << 24) | new_import_buf[pcnt];
          }
      }
  }

  flat->file_size = flat->import_start+new_import_cnt*sizeof(uint32_t);

  if ( FLAG_DUMP_FLT_HEADERS ) {
	printf("\nFLT Headers:\n");
	printf("->entry        0x%x (size %d)\n", flat->entry, flat->data_start - flat->entry );
	printf("->data_start   0x%x (size %d)\n", flat->data_start,  flat->bss_start - flat->data_start );
	printf("->bss_start    0x%x (size %d)\n", flat->bss_start,   flat->reloc_start - flat->bss_start );
	printf("->reloc_start  0x%x (size %d)\n", flat->reloc_start, flat_reloc_count*sizeof(reloc_record_t) );
	printf("->import_start 0x%x (size %d %d)\n", flat->import_start, flat->file_size-flat->import_start, flat_import_count*sizeof(import_record_t) );
    printf("\n");

	printf("\nModule info:\n");
	printf("->Module Name: %s\n", get_flat_string(_module_info->moduleName) );
	printf("->Module Ver: %d.%d\n", _module_info->module_version.major, _module_info->module_version.minor );

	char* branches_str[] = {"any branch","CHDK", "CHDK_DE", "CHDK_SDM", "PRIVATEBUILD"};
	int branch = (_module_info->chdk_required_branch>REQUIRE_CHDK_PRIVATEBUILD) ? 
						REQUIRE_CHDK_PRIVATEBUILD : _module_info->chdk_required_branch;
	printf("->Require: %s-build%d. ", branches_str[branch], _module_info->chdk_required_ver );
	if ( _module_info->chdk_required_platfid == 0 )
	  	printf("Any platform.\n");
	else
	  	printf(" Platform #%d only.\n", _module_info->chdk_required_platfid );
	printf("->Description: %s\n", get_flat_string(_module_info->description) );
	print_offs("->lib                 = ", (int)_module_info->lib,"\n");
	//print_offs("->_module_loader()    = ", (int)_module_info->loader,"\n");
	//print_offs("->_module_unloader()  = ", (int)_module_info->unloader,"\n");
	//print_offs("->_module_can_unload()= ", (int)_module_info->can_unload,"\n");
	//print_offs("->_module_exit_alt()  = ", (int)_module_info->exit_alt,"\n");
  }

  if ( FLAG_DUMP_FLAT ) {
    dump_section( "FLT_header", (unsigned char*)flat_buf, sizeof(struct flat_hdr) );
    dump_section( "FLT_text", (unsigned char*)flat_buf+flat->entry, flat->data_start-flat->entry );
    dump_section( "FLT_data", (unsigned char*)flat_buf+flat->data_start, flat->bss_start-flat->data_start);
    dump_section( "FLT_bss",  (unsigned char*)flat_buf+flat->bss_start, flat->reloc_start-flat->bss_start );

    printf("\nDump relocations 0x%x (size=%d):\n",flat->reloc_start,flat_reloc_count*sizeof(reloc_record_t));
    for( i = 0; i< flat_reloc_count; i++)
    {
        print_offs("Offs: ",*(int*)(flat_buf+flat->reloc_start+i*sizeof(reloc_record_t)), "\n");
    }

    printf("\nDump imports 0x%x (size=%d):\n",flat->import_start,new_import_cnt*sizeof(uint32_t));
    for (i = 0; i< new_import_cnt;)
    {
        uint32_t idx = new_import_buf[i++];
        int cnt = new_import_buf[i] >> 24;
        int j;
        for (j=0; j<cnt; j++)
        {
            uint32_t offs = new_import_buf[i++] & 0x00FFFFFF;
            print_offs((j==0)?"Offs: ":"      ",offs,"");
		    int addend = *(uint32_t*)(flat_buf+offs);
		    printf(" = sym_%08x[%s]+0x%x\n",idx,get_import_symbol(idx),addend);
        }
    }
  }

  int filesize = flat->file_size;

  printf("\n\nOutput file %s (size=%d bytes)\n",fltfile,filesize);

  int output_fd = open(fltfile,O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,0777);
  i = write(output_fd, flat_buf, flat->import_start);
  i = write(output_fd, new_import_buf, new_import_cnt*sizeof(uint32_t));
  close(output_fd);

  return ELFFLT_OK;
}
/*---------------------------------------------------------------------------*/
