/*
 * Service library of elf2flt 
 *
 * 	(c)2011	Sergey Taranenko aka tsvstar
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#include "myio.h"

static char* filebuf=0;
static int   filesize=0; 
static int   filecuridx=0;

/*---------------------------------------------------------------------------*/
int b_file_preload(char* filename)
{
	int fd;

    filesize=0;
    filecuridx=0;
    
    fd=open(filename, O_RDONLY|O_BINARY);
    if ( fd <=0 ) return 0;
    filesize = lseek(fd,0,SEEK_END);
	if ( FLAG_VERBOSE )
	    printf("File size=%d\n",filesize);
    filebuf=malloc(filesize);    
    if (!filebuf) return 0;

    int now=0, loaded =0; 
    if (lseek(fd, 0, SEEK_SET) != 0) return 0;
    do
    {
       now = read(fd, filebuf+loaded, filesize-loaded);
	   loaded+=now;
	} while (loaded<filesize && now);
         
    if ( loaded == filesize )
    	return loaded;
	return -loaded;
}

/*---------------------------------------------------------------------------*/
int b_read (int fd, void* buf, unsigned int count)
{
    if ( (filecuridx+count)> filesize)
        count = filesize - filecuridx;
    memcpy(buf, filebuf+filecuridx, count);
    filecuridx+=count;
    return count;
}

/*---------------------------------------------------------------------------*/
int b_seek(int fd, long offset, int whence)
{
    filecuridx = offset;
    if ( offset < 0 )
     { filecuridx = 0;}
    else if ( offset > filesize)
     { filecuridx = filesize;}
    return filecuridx;
}

/*---------------------------------------------------------------------------*/
int b_seek_read(unsigned int offset, char *buf, int len)
{
  if (b_seek(1, offset, SEEK_SET) != offset) return -1;
  return b_read(1, buf, len);
}

char* b_get_buf()
{
  return filebuf;
}


#define MAX_SYM 2048

static char* import_buf=0;
static char* import_syms[MAX_SYM];          // Symbol names in input file
static unsigned int import_hash[MAX_SYM];   // Symbol hash values in input file
static int import_counts=0;                 // # of symbols found
static int importfilesize=0;

int load_import(char* importfile)
{
	int fd;
	static char buf[10];

	import_counts=0;
	import_buf=buf;
	if ( !importfile )
	  return 0;

	fd=open(importfile, O_RDONLY|O_BINARY, 0777);

    if ( fd <=0 ) {
		PRINTERR(stderr,"No import file '%s' found\n",importfile);
		return 0;
	}
    importfilesize = lseek(fd,0,SEEK_END);
	if ( FLAG_VERBOSE )
    	printf("Import file '%s' size=%d\n",importfile, importfilesize);

    import_buf=malloc(importfilesize+1);    
    if (!import_buf) return 0;

    int now=0, loaded =0; 
 	if (lseek(fd, 0, SEEK_SET) != 0) return 0;
	do
	{ 
      now = read(fd, import_buf+loaded, importfilesize-loaded);
      loaded+=now;
    } while (loaded<importfilesize && now);

	import_buf[loaded]=0;
	close(fd);
       
    if ( loaded != importfilesize )
      return -loaded;

    // Input file contains symbol hash value (in hex), a space and then the symbol name
	// Parse the input file and build the symbol / hash table
	char* p=import_buf;
    char* s=p;
	for (;*p;p++) {
		if (*p==13) {
			PRINTERR(stderr,"Import file should have unix EOL format\n");
			import_counts=0;
			break;
		}

		if (*p==10) {
			*p=0;
            unsigned int h;
            sscanf(s,"%x ",&h);
            import_syms[import_counts] = s+9;
            import_hash[import_counts] = h;
			import_counts++;
            s = p + 1;
			continue;
		}
		
		//if (!((*p>='A' && *p<='Z') || 
		//	  (*p>='a' && *p<='z') || 
		//	  (*p>='0' && *p<='9') || 
		//	  *p=='_' ))
		//{
		//	PRINTERR(stderr,"Found '%c' sym. Import file should contain only symbol names. No spaces or other sym allowed\n",*p);
		//	break;
		//}
	}
	if ( FLAG_VERBOSE )
		printf("Import file has %d entries\n",import_counts);
	return loaded;
}

// Return: 0=not_found, otherwise return has value of symbol name
int find_import_symbol(char* sym)
{
  static const char prefix[] = "__imported_";
  static int prefixsize = sizeof(prefix);

	if (import_counts<=0)
		return 0;

	if (strlen(sym)==0)
		return 0;

	if ( !strncmp( sym, prefix, prefixsize ) )
	 { sym+=prefixsize; }

	int idx=0;

	for(;idx<import_counts;idx++) {
	  if (strcmp(sym,import_syms[idx]) == 0)
		return (import_hash[idx]);
	}
	return 0;
}

// Return symbol name by its hash value
char* get_import_symbol( unsigned symidx )
{
	int idx=0;

	for(;idx<symidx;idx++) {
      if (import_hash[idx] == symidx)
          return import_syms[idx];
	}

	return "";
}


//==========================================

struct StopListRecord {
	char* symbol;
	char* warning;
	void* next;	
};


char *stoplist_buf=0;
struct StopListRecord* stoplisthead=0;


int load_stoplist(char* stopfile)
{
	if ( !stopfile )
	  return 0;

	int fd=open(stopfile, O_RDONLY|O_BINARY, 0777);

    if ( fd <=0 ) {
		PRINTERR(stderr,"No stoplist file '%s' found\n",stopfile);
		return 0;
	}
    int stoplistfilesize = lseek(fd,0,SEEK_END);
	if ( FLAG_VERBOSE )
    	printf("Stoplist file '%s' size=%d\n",stopfile, stoplistfilesize);

    stoplist_buf=malloc(stoplistfilesize+1);    
    if (!stoplist_buf) return 0;

    int now=0, loaded =0; 
 	if (lseek(fd, 0, SEEK_SET) != 0) return 0;
	do
	{ 
      now = read(fd, stoplist_buf+loaded, stoplistfilesize-loaded);
      loaded+=now;
    } while (loaded<stoplistfilesize && now);

	stoplist_buf[loaded]=0;
	close(fd);
       
    if ( loaded != stoplistfilesize )
      return -loaded;

    // Parse
    struct StopListRecord record;
	char* sym=0, *finsym=0;
    char* cur=stoplist_buf;

    for ( ; cur<(stoplist_buf+stoplistfilesize); ) {
		for(;*cur==' '; cur++);	// skip spaces

		sym=cur;
		for(;*cur && *cur!=9 && *cur!=' ' && *cur!=0x0a; cur++);
		if ( cur==sym ) {
			for(;*cur && *cur!=10; cur++);
			if ( *cur==10) {cur++;}
			continue;
		}

		record.symbol = sym;	
		record.warning = "Error: unsafe symbol used. Please check stoplist";
		finsym=cur;
		for(;*cur && *cur!=9 && *cur!=0x0a; cur++);	// find \t

		if ( *cur==0 ) break;
		if ( *cur==9 ) {
			cur++;
			record.warning=cur;
		}
		
		for(;*cur && *cur!=10; cur++);		// find eol
		if ( *cur==0x0a && cur>stoplist_buf && *(cur-1)==0x0d)
			*(cur-1)=0;

		if (cur==record.warning)
			record.warning = "Error: unsafe symbol used. Please check stoplist";

		record.next=stoplisthead;
		stoplisthead = malloc (sizeof(struct StopListRecord));
		memcpy( stoplisthead, &record, sizeof(struct StopListRecord));

		if ( *cur!=0 ) { *cur=0; cur++;}
		*finsym = 0;

		if ( FLAG_VERBOSE )
			printf("Stop record: %s => %s\n",record.symbol, record.warning);
	}

	return loaded;
}

//return: 1 - found in stoplist, 0 - not found
int stoplist_check(char *sym)
{
	struct StopListRecord *cur;
  
	for ( cur = stoplisthead; cur; cur = cur->next ) {
		if ( !cur->symbol )
			continue;
		if ( !strcmp( sym, cur->symbol) ) {
			PRINTERR(stderr,"%s\n",cur->warning);
			cur->symbol = 0;  // mark that this symbol is already warned
			return 1;
		}
	}
	return 0;
}


//==========================================
void raise_error()
{
  static int flag =0;

  if (!flag)
	fprintf(stderr, "In file %s:\n", filename_elf);
  flag=1;
}
