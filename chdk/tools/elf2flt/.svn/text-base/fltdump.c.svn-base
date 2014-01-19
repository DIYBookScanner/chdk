/*
 */

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "myio.h"
#define USE_INT32_FOR_PTRS      // To avoid pointer size issues in structs in flt.h
#include "flt.h"

struct flat_hdr* flat;
unsigned char* flat_buf;
char* filename_elf="";
int FLAG_VERBOSE=0;
int FLAG_DUMP_FLAT=0;


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
void print_offs(char *prefix, int offs,char* postfix)
{
    int secoffs = 0;
    char* sect="unkn";
    
    if ( !offs ) {
        printf("%s 0x00000000\n",prefix);
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

	strncpy( buf, (char*)flat_buf+offs, sizeof(buf)-1);
	buf[sizeof(buf)-1]=0;
	return buf;
}

int main(int argc, char **argv)
{

    if ( argc < 2 )
    {
        printf("fltdump.exe filename.flt [-f]\n  -f = dump content of FLAT sections\n");
        return 1;
    }
    
    if ( argc > 2 && argv[2][0]=='-' && argv[2][1]=='f' )
	  { FLAG_DUMP_FLAT=1;}

    char* filename_flt = argv[1];

    int rv;
    if ( (rv=b_file_preload(filename_flt)) <= 0 )
    {
        fprintf(stderr, "Error load file '%s': loaded %d\n",filename_flt,rv);
        return 1;
    }


	flat = (struct flat_hdr*) b_get_buf();
	flat_buf = (unsigned char*)b_get_buf();

    char magic[5];          // "CFLA"
	memcpy(magic,flat->magic,4);
	magic[4]=0;


	printf("\nFLT Headers:\n");
	printf("->magic        %s (flat rev.%d)\n", magic, flat->rev );

	if ( memcmp(magic,FLAT_MAGIC_NUMBER,4) ) {
		printf("This is not CHDK-FLAT!\n");
		return 1;
	}	

	if ( flat->rev != FLAT_VERSION )
	{
		printf("Bad FLAT revision! It is %d while should be %d\n", flat->rev, FLAT_VERSION);
	}

	int flat_reloc_count;
	flat_reloc_count = (flat->import_start-flat->reloc_start)/sizeof(uint32_t);
	int flat_import_count;
	flat_import_count = (flat->file_size-flat->import_start)/sizeof(uint32_t);


	printf("->entry(.text) 0x%x (size %d)\n", flat->entry, flat->data_start - flat->entry );
	printf("->data_start   0x%x (size %d)\n", flat->data_start,  flat->bss_start - flat->data_start );
	printf("->bss_start    0x%x (size %d)\n", flat->bss_start, flat->reloc_start - flat->bss_start );
	printf("->reloc_start  0x%x (size %d)\n", flat->reloc_start, flat->import_start - flat->reloc_start );
	printf("->import_start 0x%x (size %d)\n", flat->import_start, flat->file_size - flat->import_start );
    printf("\n");

	if ( flat->rev == FLAT_VERSION )
	{
		struct ModuleInfo* _module_info = (struct ModuleInfo*)(flat_buf + flat->_module_info_offset);
		if ( _module_info->magicnum != MODULEINFO_V1_MAGICNUM ) 
		{
		  printf("Malformed module info - bad magicnum!\n");
		  return 1;
		}
		if ( _module_info->sizeof_struct != sizeof(struct ModuleInfo) ) 
		{
		  printf("Malformed module info - bad sizeof!\n");
		  return 1;
		}


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
		
	if ( !FLAG_DUMP_FLAT )
	  return 0;

    dump_section( "FLT_header", flat_buf, sizeof(struct flat_hdr) );
    dump_section( "FLT_text", flat_buf+flat->entry, flat->data_start-flat->entry );
    dump_section( "FLT_data", flat_buf+flat->data_start, flat->bss_start-flat->data_start);
    dump_section( "FLT_bss",  flat_buf+flat->bss_start, flat->reloc_start-flat->bss_start );

	int i;
    printf("\nDump relocations 0x%x (size=%d):\n",flat->reloc_start,flat_reloc_count*sizeof(uint32_t));
    for( i = 0; i< flat_reloc_count; i++)
        print_offs("Offs: ",*(int*)(flat_buf+flat->reloc_start+i*sizeof(uint32_t)),"\n");

    printf("\nDump imports 0x%x (size=%d):\n",flat->import_start,flat_import_count*sizeof(uint32_t));
    uint32_t *new_import_buf = (uint32_t*)(flat_buf+flat->import_start);
    for( i = 0; i< flat_import_count; i++)
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

	return 0;

}


