#include "stdlib.h"
#include "lang.h"
#include "fileutil.h"

static char* preparsed_lang_default_start=0;
static char* preparsed_lang_default_end=0;            // @this is for correct detection which is in heap

// This is threshold to determine is this id in .lng or just string
#define MAX_LANGID 0x1000

//-------------------------------------------------------------------

static char** strings = NULL;        // string list (allocated at heap or mapped from gui_lang.c);
static int count = 0;                // current maximal string id (init at lang_init with GUI_LANG_ITEMS)

//-------------------------------------------------------------------
void lang_init(int num) {
    int i;
    char* str;

    if (strings) {
       for (i=0; i<count; ++i) {
           str=strings[i];
           if ( str && ( str<preparsed_lang_default_start || str>preparsed_lang_default_end ) )
               free(str);
    }

       free(strings);
       count = 0;
    }

    ++num;
    strings = malloc(num*sizeof(char*));
    if (strings) {
        memset(strings, 0, num*sizeof(char*));
        count = num;
    }

}

// add to string list string "str" with id "num"
//-------------------------------------------------------------------
static void lang_add_string(int num, const char *str) {
    int f=0;
    char *p;

    if (strings && num<count) {
    p = strings[num];
       if ( p && ( p<preparsed_lang_default_start || p>preparsed_lang_default_end ) )
           free( p );

       p = strings[num] = malloc(strlen(str)+1);
       if (p) {
           for (; *str; ++str) {
                if (f) {
                    if (*str == '"' || *str == '\\') *(p-1)=*str;
                    else if (*str == 'n') *(p-1)='\n';
                    else *p++=*str;
                    f = 0;
                } else {
                    *p++=*str;
                    if (*str == '\\') {
                        f = 1;
                    }
                }
           }
           *p=0;
       }
    }
}

// Parsing of loaded .lng file
// buf - source array (content of file.lng )
//-------------------------------------------------------------------
int lang_parse_from_mem(char *buf, int size) {
    char *p, *s, *e;
    int i;

	if  ( size <= 0 )
	  return 0;

    e = buf-1;
    while(e) {
        p = e+1;
        while (*p && (*p=='\r' || *p=='\n')) ++p; //skip empty lines
        i = strtol(p, &e, 0/*autodetect base oct-dec-hex*/);    // convert "*p" to long "i" and return pointer beyond to e
        if (e!=p) {
            p = e;
            e = strpbrk(p, "\r\n");        //break string with zero on \r|\n
            if (e) *e=0;

            while (*p && *p!='\"') ++p;    // cut string from "" if it exists
            if (*p) ++p;
            s = p;
            while (*p && (*p!='\"' || *(p-1)=='\\')) ++p;
            *p=0;

            lang_add_string(i, s);        // add string
        } else { //skip invalid line
            e = strpbrk(p, "\r\n");
            if (e) *e=0;
        }
    }
	return 1;
}

// This function have to be called before any other string load
//-------------------------------------------------------------------
void lang_map_preparsed_from_mem( char* gui_lang_default, int num )
{
    int i;
    char *p = gui_lang_default;

    preparsed_lang_default_start = p;
    lang_init( num );
    for ( i = 1; i<=num; i++ )
    {
        strings[i]=p;
        while (*p) p++;
        p++;
    }

    preparsed_lang_default_end = p;
}

//-------------------------------------------------------------------
void lang_load_from_file(const char *filename) {
    process_file(filename, lang_parse_from_mem, 1);
}


//-------------------------------------------------------------------
char* lang_str(int str) {
    if (str && str<MAX_LANGID) {
        return (strings && str<count && strings[str])?strings[str]:"";
    } else { // not ID, just char*
        return (char*)str;
    }
}

//-------------------------------------------------------------------
// make hash of string
unsigned int lang_strhash31(int langid)
{
    if ( langid<MAX_LANGID ) 
		return langid;

	unsigned char* str = (unsigned char*)langid;
	unsigned hash=0;
	for ( ; *str; str++ )
		hash = *str ^ (hash<<6) ^ (hash>>25);
	if ( hash<MAX_LANGID )
		hash |= (1<<31);
	return hash;
}
