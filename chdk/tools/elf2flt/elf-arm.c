/*
 * Basic ARM relocation processing
 *
 * Based on Linux elfloader
 *
 * 	(c)2011	Sergey Taranenko aka tsvstar
 */
#include <stdlib.h>
#include <string.h>

#include "myio.h"
#include "elfflt.h"

extern uint32_t offs_divsi3_skip_div0_test;
extern uint32_t offs_div0_from_arm;
extern uint32_t offs__aeabi_uidiv;

int apply_realloc( struct relevant_section* base_sect, 
		   struct elf32_rela *rela, 
		   struct relevant_section* tgt_sect, 
		   struct elf32_sym *sym,
           	   int i             				// idx of symbol (for printf)
		   /*unsigned int tgtoffset*/)
{
  unsigned int type  = ELF32_R_TYPE(rela->r_info);
  uint32_t locoffset = base_sect->flat_offset + rela->r_offset;
  char*    loc       = (char*)(flat_buf + locoffset );
  uint32_t tgt_fulloffset = tgt_sect->flat_offset + sym->st_value;	// full offset in flat target symbol

  int relindex = tgt_sect->number;	// to printf: num of tgt segment
  char symbuf[30];
  char* symname="";			// to printf: name of symbol
  char* reloc_name="";
  int ret = b_seek_read(strtaboff + sym->st_name, symbuf, sizeof(symbuf));
  if (ret > 0) { symname=symbuf; symbuf[sizeof(symbuf)-1]=0; }


  int32_t offset;
  uint32_t upper, lower, sign, j1, j2;
  char* patch_name="";		// detected build-in function


  if (rela->r_offset > base_sect->size - sizeof(uint32_t)) {
            PRINTERR(stderr, "section %u(%s) reloc %u sym '%s': out of bounds relocation, offset %d size %u\n",
                    relindex, base_sect->name, i, symname,
                   rela->r_offset, base_sect->size);
            return ELFFLT_OUTOF_RANGE;
  }

  switch(type) {
    case R_ARM_ABS32:
    	{
      		uint32_t addend = *(uint32_t*)loc;
            *(uint32_t*)loc += tgt_fulloffset;

			if ( FLAG_DUMP_RELOC )
				printf( "R_ARM_ABS32: %p(%s+0x%x=%x): ptr=%x [%s+0x%x+0x%x] sym:%s\n", 
					base_sect->base_addr+rela->r_offset,  base_sect->name, rela->r_offset, locoffset,
					tgt_sect->base_addr + addend + sym->st_value,
					tgt_sect->name, sym->st_value, addend, symname
						);

            if ( FLAG_VERBOSE)            
               printf("=== flt%p(reloc+%x: %x): [%x]=0x%x\n",flat_reloc_cur, (char*)flat_reloc_cur-(char*)flat_reloc, (char*)flat_reloc_cur-flat_buf, locoffset, *(uint32_t*)loc);
      		*flat_reloc_cur = locoffset;
      		flat_reloc_cur++;
            flat_reloc_count++;
    	}
    	break;

      case R_ARM_THM_CALL:
//      case R_ARM_THM_JUMP24:	//not needed
              upper = *(uint16_t *)loc;
              lower = *(uint16_t *)(loc + 2);
      
              /*
               * 25 bit signed address range (Thumb-2 BL and B.W
               * instructions):
               *   S:I1:I2:imm10:imm11:0
               * where:
               *   S     = upper[10]   = offset[24]
               *   I1    = ~(J1 ^ S)   = offset[23]
               *   I2    = ~(J2 ^ S)   = offset[22]
               *   imm10 = upper[9:0]  = offset[21:12]
               *   imm11 = lower[10:0] = offset[11:1]
               *   J1    = lower[13]
               *   J2    = lower[11]
               */
              sign = (upper >> 10) & 1;
              j1 = (lower >> 13) & 1;
              j2 = (lower >> 11) & 1;
              offset = (sign << 24) | ((~(j1 ^ sign) & 1) << 23) |
                      ((~(j2 ^ sign) & 1) << 22) |
                      ((upper & 0x03ff) << 12) |
                      ((lower & 0x07ff) << 1);
              if (offset & 0x01000000)
                      offset -= 0x02000000;
              offset += tgt_fulloffset - locoffset;
      
              /*
               * For function symbols, only Thumb addresses are
               * allowed (no interworking).
               *
               * For non-function symbols, the destination
               * has no specific ARM/Thumb disposition, so
               * the branch is resolved under the assumption
               * that interworking is not required.
               */
                if ((ELF32_ST_TYPE(sym->st_info) == STT_FUNC &&
                      !(offset & 1)) ||
                  offset <= (int32_t)0xff000000 ||
                  offset >= (int32_t)0x01000000) {
                      PRINTERR(stderr, "section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
                              relindex, i, symname,
                             ELF32_R_TYPE(rela->r_info), locoffset,
                             sym->st_value);
                      return ELFFLT_OUTOF_RANGE;
              }
      
			  if ( FLAG_DUMP_RELOC )
	      		printf( "R_ARM_THM_CALL: %p(%s+0x%x=%x):  %04x %04x ptr=%x [loc%-d] sym:%s\n", 
					base_sect->base_addr+rela->r_offset,  base_sect->name, rela->r_offset, locoffset,
					upper, lower,
					tgt_sect->base_addr+rela->r_offset+offset, offset,
					symname);

              sign = (offset >> 24) & 1;
              j1 = sign ^ (~(offset >> 23) & 1);
              j2 = sign ^ (~(offset >> 22) & 1);
              *(uint16_t *)loc = (uint16_t)((upper & 0xf800) | (sign << 10) |
                                  ((offset >> 12) & 0x03ff));
              *(uint16_t *)(loc + 2) = (uint16_t)((lower & 0xd000) |
                                        (j1 << 13) | (j2 << 11) |
                                        ((offset >> 1) & 0x07ff));
              break;

      case R_ARM_PC24:
			  // R_ARM_PC24 is generated by Win arm-gcc. And in some buildin funcs change
				// this pointer to different function. This part is emulate this behaviour.

    	      patch_name=0;
			  if ( strcmp(symname,"__div0") == 0 )
              {
			      if ( locoffset == offs_divsi3_skip_div0_test )
				        patch_name=".divsi3_skip_div0_test";
			      else if ( locoffset == offs__aeabi_uidiv )
				        patch_name="__aeabi_uidiv";

			      if ( !patch_name ) {
					    PRINTERR( stderr, "%s is requested from unusual place .text+0x%x\n", reloc_name,locoffset-text.flat_offset);
					    return ELFFLT_UNHANDLED_RELOC;
			      }

			      // this is redirection to the new func
			      tgt_fulloffset = (text.flat_offset + offs_div0_from_arm);
                  // Falls through to next case - no break ***
              }

      case R_ARM_PLT32:
			// R_ARM_PLT32 is generated by linux arm-gcc and it doesn't change binary when instance into fixed adress

//      case R_ARM_CALL:		// not needed
//      case R_ARM_JUMP24:		// not needed

			  reloc_name = (type==R_ARM_PC24)?"R_ARM_PC24":"R_ARM_PLT32";

              offset = (*(uint32_t *)loc & 0x00ffffff) << 2;
              if (offset & 0x02000000)
                  offset -= 0x04000000;
      
              offset += tgt_fulloffset - locoffset;

/* it is possible to have offset close to upper border
              if (offset & 3 ||
                  offset <= (int32_t)0xfe000000 ||
                  offset >= (int32_t)0x02000000) {
                      PRINTERR(stderr, "section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
                             relindex, i, symname,
                             ELF32_R_TYPE(rela->r_info), locoffset,
                             tgt_fulloffset);
                return ELFFLT_OUTOF_RANGE;
              }
*/
     
              offset >>= 2;

              if ( FLAG_DUMP_RELOC )
              {
                  printf( "%s: %p(%s+0x%x=%x):  %08x ptr=%x [loc%-d] sym:%s\n", reloc_name,
                      base_sect->base_addr+rela->r_offset,  base_sect->name, rela->r_offset, locoffset,
                      *(uint32_t *)loc,
                      base_sect->base_addr+rela->r_offset+offset*4, offset*4,
                      symname);
                  if ((type==R_ARM_PC24) && patch_name)
                      printf( "...Patched 0x%x(__div0)->0x%x (__div0_from_arm) for %s\n",  sym->st_value, offs_div0_from_arm, patch_name);
              }

              *(uint32_t *)loc &= 0xff000000;
              *(uint32_t *)loc |= offset & 0x00ffffff;
              break;
	default:
		PRINTERR(stderr, "Unknown relocation type %d\n",type);
		return ELFFLT_UNHANDLED_RELOC;
	}
 
  return ELFFLT_OK;
}




int apply_import( struct relevant_section* base_sect, 
		   struct elf32_rela *rela, 
		   int importidx, 
		   struct elf32_sym *sym,
           int i
		 )
{
  unsigned int type  = ELF32_R_TYPE(rela->r_info);
  uint32_t locoffset = base_sect->flat_offset + rela->r_offset;
  char*    loc       = (char*)(flat_buf + locoffset );

  char symbuf[30];
  char* symname="";			// to printf: name of symbol
  int ret = b_seek_read(strtaboff + sym->st_name, symbuf, sizeof(symbuf));
  if (ret > 0) { symname=symbuf; symbuf[sizeof(symbuf)-1]=0; }

  switch(type) {
    case R_ARM_ABS32:
    	{
      		flat_import_cur->offs = locoffset;
      		flat_import_cur->importidx = importidx;

        	if ( FLAG_DUMP_RELOC )
				printf( "R_ARM_ABS32: %p(%s+0x%x=%x): import_value=%d (sym:%s)+0x%x %d\n", 
					base_sect->base_addr+rela->r_offset,  base_sect->name, rela->r_offset, locoffset,
					 importidx, symname, *(uint32_t*)loc, flat_import_count
						);
      		flat_import_cur++;
            flat_import_count++;
    	}
      	break;

	default:
		// Use only ABS32 because we can't be sure that module will be loaded not too far from core to PC24/THM_CALL
		PRINTERR(stderr, "Only R_ARM_ABS32 relocations could be processed as imported symbol (%s). Please compile with -mlong-call or use manual import\n",symname);
		return ELFFLT_UNHANDLED_RELOC;
  }
  return ELFFLT_OK;
}
