#include <stdio.h>                                                   
#include <unistd.h>
#include <fcntl.h>

#include "myio.h"
#include "elfflt.h"

int FLAG_DUMP_SOURCE = 0;
int FLAG_DUMP_SYMBOLS = 0;
int FLAG_DUMP_RELOC = 0;
int FLAG_DUMP_FLT_HEADERS = 0;
int FLAG_DUMP_FLAT = 0;
int FLAG_VERBOSE = 0;
int FLAG_DUMP_SECTIONS = 0;
int FLAG_WARNSYMBOL=0;

char* filename_elf;
char* filename_flt;

int main(int argc, char **argv)
{

    if ( argc < 3 )
    {
        printf("elfflt.exe filename.elf filename.flt [-vefrhsS] [-iIMPORTFILE.TXT]\n");
		printf("  -iPATH/TO/exportlist.txt for list of imported symbols\n");
		printf("  -!PATH/TO/stoplist.txt for list of unsafe symbols\n");
		printf("  -e dump elf\n  -S show elf sections\n  -f dump flat\n  -r show relocations\n  -h show flat headers\n  -s dump elf symbols\n  -v verbose");
        return 1;
    }
    
    filename_elf = argv[1];
    filename_flt = argv[2];

	char* filename_import =0;
	char* filename_stoplist =0;

	int i;
	for(i=3;i<argc;i++)
	{
		if (argv[i][0]!='-') continue;
		switch ( argv[i][1] )
		{
		  case 'e': FLAG_DUMP_SOURCE = 1; break;
		  case 'S': FLAG_DUMP_SECTIONS = 1; break;
		  case 's': FLAG_DUMP_SYMBOLS = 1; break;
		  case 'r': FLAG_DUMP_RELOC = 1; break;
		  case 'h': FLAG_DUMP_FLT_HEADERS = 1; break;
		  case 'f': FLAG_DUMP_FLAT = 1; break;
		  case 'v': FLAG_VERBOSE = 1; break;
		  case 'i': filename_import = argv[i]+2; break; 
		  case '!': filename_stoplist = argv[i]+2; break;
		}
    }

    if (FLAG_VERBOSE)
		printf("elf2flt: %s -> %s\n", filename_elf, filename_flt);

    int rv;
    if ( (rv=b_file_preload(filename_elf)) <= 0 )
    {
        fprintf(stderr, "Error load file '%s': loaded %d\n",filename_elf,rv);
        return ELFFLT_INPUT_ERROR;
    }

	load_import(filename_import);
	load_stoplist(filename_stoplist);
      
    int err = elfloader_load(filename_elf, filename_flt);

	if ( err == ELFFLT_OUTPUT_ERROR || err == ELFFLT_INPUT_ERROR )
    	PRINTERR(stderr, "elf2flt: Internal error\n");

    return err;    
}
