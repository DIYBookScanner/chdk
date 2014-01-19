#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

#include "stubs_load.h"

//------------------------------------------------------------------------------------------------------------

// Functions for loading stubs and other source files, storing and searching for values contained within.

//------------------------------------------------------------------------------------------------------------

stub_values* new_stub_values()
{
    stub_values *p = malloc(sizeof(stub_values));
    p->stubs = 0;
    p->stubs_min = 0;
    p->modemap = 0;
    p->makevals = 0;
    p->min_focus_len = 0;
    p->max_focus_len = 0;
    return p;
}

//------------------------------------------------------------------------------------------------------------

// File parsing

static int read_line(FILE *f, char *buf)
{
    int eof = 0;
    int len = 0;
    while (1)
    {
        if (fread(buf,1,1,f) != 1) { eof = 1; break; }
        if ((*buf == 0x0A) || (*buf == 0x0D)) break;
        len++; 
        buf++;
    }
    *buf = 0;
    return (eof == 0) || (len > 0);
}

static char* get_str(char *s, char *d)
{
    while ((*s == ' ') || (*s == '\t') || (*s == ',')) s++;
    while (*s && (*s != ' ') && (*s != '\t') && (*s != ',') && (*s != '=') && (*s != ')'))
    {
        *d++ = *s++;
    }
	while (*s && (*s != ',') && (*s != '=') && (*s != ')'))
	{
		if (*s == '+')
		{
			*d++ = *s++;
			while ((*s == ' ') || (*s == '\t') || (*s == ',')) s++;
			while (*s && (*s != ' ') && (*s != '\t') && (*s != ',') && (*s != '=') && (*s != ')'))
			{
				*d++ = *s++;
			}
		}
		else s++;
	}
    *d = 0;
    return s;
}

// Add a new value to the list
static osig* add_sig(char *nm, char *val, osig **hdr, int is_comment)
{
    osig *p = malloc(sizeof(osig));
    strcpy(p->nm, nm);
	strcpy(p->sval, val);
    p->pct = 0;
    p->is_comment = is_comment;
    p->type = 0;
    p->nxt = *hdr;
    *hdr = p;

	uint32_t v = 0, n = 0;
	if ((strncmp(val,"0x",2) == 0) || (strncmp(val,"0X",2) == 0))
	{
		while (val)
		{
			sscanf(val,"%x",&n);
			v += n;
			val = strchr(val,'+');
			if (val) val++;
		}
	}
	else
	{
		sscanf(val,"%d",&v);
	}

	p->val = v;
    return p;
}

//------------------------------------------------------------------------------------------------------------

// Find an entry by name
osig* find_sig(osig* p, const char *nm)
{
    while (p)
    {
        if (strcmp(p->nm, nm) == 0) return p;
        p = p->nxt;
    }
    return 0;
}

// Find an entry by value
osig* find_sig_val(osig* p, uint32_t val)
{
    while (p)
    {
        if (p->val == val) return p;
        p = p->nxt;
    }
    return 0;
}

// Find an entry by value
osig* find_sig_val_by_type(osig* p, uint32_t val, int typ)
{
    while (p)
    {
        if ((p->val == val) && (p->type == typ)) return p;
        p = p->nxt;
    }
    return 0;
}

// Find a match (in case of multiple entries)
// returns first entry matching name & value, 
// or first entry matching name only (if value does not match),
// or 0 if no name match
osig* find_match(osig *p, const char *nm, uint32_t val)
{
    p = find_sig(p, nm);
    osig *f = p;
    while (p)
    {
        if (p->val == val)
            return p;
        p = find_sig(p->nxt, nm);
    }
    return f;
}

//------------------------------------------------------------------------------------------------------------

// Load a specified file.
// Add new entries the list pointer to by 'hdr'
void load_funcs(stub_values *sv, char *name)
{
    FILE *f = fopen(name, "rb");

    if (f == NULL) return;

    char line[500];
    char nm[100];
    char val[100];
    char *s;

    while (read_line(f,line))
    {
        s = get_str(line,val);
        get_str(s,nm);
        osig *p = add_sig(nm, val, &sv->stubs, 1);
        p->type = TYPE_NHSTUB;
        continue;
    }
}

// Load a specified file.
// If 'exclude_comments' is non-zero then commented lines are ignored.
// Add new entries the list pointer to by 'hdr'
static void load_stubs_file(char *name, int exclude_comments, osig **hdr)
{
    FILE *f = fopen(name, "rb");

    if (f == NULL) return;

    char line[500];
    char nm[100];
    char val[100];
    char *s;

    while (read_line(f,line))
    {
        int typ = TYPE_NHSTUB;
        int off = 7;
        s = strstr(line, "NHSTUB(");
        if (s == 0) { off = 7; s = strstr(line, "IGNORE("); typ = TYPE_IGNORE; }
        if (s == 0) { off = 6; s = strstr(line, "NSTUB("); }
        if (s == 0) { off = 4; s = strstr(line, "DEF("); typ = TYPE_DEF; }
        if (s != 0)
        {
            char *c = strstr(line, "//");
            if ((exclude_comments == 0) || (c == 0) || (c > s))
            {
                s = get_str(s+off,nm);
                if (typ != TYPE_IGNORE)
                    get_str(s,val);
                else
                    val[0] = 0;
                osig *p = add_sig(nm, val, hdr, ((c != 0) && (c <= s)) ? 1 : 0);
                p->type = typ;
                continue;
            }
        }
    }
}

// Load a specified stubs file.
void load_stubs(stub_values *sv, char *name, int exclude_comments)
{
    load_stubs_file(name, exclude_comments, &sv->stubs);
}

// Load the 'stubs_min.S' file
void load_stubs_min(stub_values *sv)
{
    load_stubs_file("stubs_min.S", 1, &sv->stubs_min);
}

// Load the MODEMAP from the shooting.c source file
void load_modemap(stub_values *sv)
{
    FILE *f = fopen("../../shooting.c", "rb");

    if (f == NULL) return;

    char line[500];
    char nm[100];
    char val[12];
	int found_modemap = 0;
    char *s;

    while (read_line(f,line))
    {
		if (found_modemap)
		{
			s = strstr(line, "};");
			if (s != 0) return;
			s = strstr(line, "MODE_");
			if (s != 0)
			{
				char *c = strstr(line, "//");
				if ((c == 0) || (c > s))
				{
					s = get_str(s,nm);
					get_str(s,val);
					add_sig(nm, val, &sv->modemap, 0);
				}
			}
		}
		else
		{
			s = strstr(line, "modemap[");
			if (s != 0) found_modemap = 1;
		}
    }
}

// Load the DNG lens info from the 'platform_camera.h' file.
void load_platform(stub_values *sv)
{
    FILE *f = fopen("../../platform_camera.h", "rb");

    if (f == NULL) return;

    char line[500];
    char val[12];
    char div[12];
    int v, d;
    char *s;

    while (read_line(f,line))
    {
		s = strstr(line, "CAM_DNG_LENS_INFO");
		if (s != 0)
		{
			char *c = strstr(line, "//");
			if ((c == 0) || (c > s))
			{
                s = strstr(line,"{")+1;
				s = get_str(s,val);
				s = get_str(s,div);
                v = atoi(val);
                d = atoi(div);
                sv->min_focus_len = (v * 1000) / d;
				s = get_str(s,val);
				s = get_str(s,div);
                v = atoi(val);
                d = atoi(div);
                sv->max_focus_len = (v * 1000) / d;
			}
		}
    }
}

// Load the build values from the makefile.inc source file
void load_makefile(stub_values *sv)
{
    FILE *f = fopen("makefile.inc", "rb");

    if (f == NULL) return;

    char line[500];
    char nm[100];
    char val[100];
    char *s;

    while (read_line(f,line))
    {
		s = strstr(line, "=");
		if (s != 0)
		{
            char *c = strstr(line, "#");
			if ((c == 0) || (c > s))
			{
                if (c) *c = 0;
				s = get_str(line,nm);
				get_str(s+1,val);
				add_sig(nm, val, &sv->makevals, 0);
			}
		}
    }
}

//------------------------------------------------------------------------------------------------------------
