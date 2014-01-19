#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

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

//------------------------------------------------------------------------------------------------------------

void usage(char *err)
{
    fprintf(stderr,"gen_conf_lua conf.c conf_name start_value - Error = %s\n",err);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 4)
        usage("args");

    int start = strtoul(argv[3], NULL, 0);

    FILE *f = fopen(argv[1], "rb");

    if (f == NULL) usage("failed to open conf.c file");

    char conf_name[200];
    sprintf(conf_name, " %s[]", argv[2]);

    char line[1000];
    char nm[200];
    char val[200];
    int lastid = 0;
    int firstid = 0;
    char *s;
    int found = 0;

    printf("--[[\nGENERATED %s TABLE\n--]]\nreturn {\n _config_id=%d,\n", argv[2], start);

    while (read_line(f,line))
    {
        if (found)
        {
            s = strstr(line, "};");
            if (s != 0) break;

            int off = 10;
            s = strstr(line, "CONF_INFO(");
            if (s == 0) { off = 11; s = strstr(line, "CONF_INFO2("); }
            if (s != 0)
            {
                char *c = strstr(line, "//");
                if ((c == 0) || (c > s))
                {
                    s = get_str(s+off,val);
                    get_str(s,nm);
                    if (strcmp(nm+5,"script_allow_lua_native_calls") != 0)  // Exclude enabling native calls
                    {
                        lastid = atoi(val) + start;
                        if (firstid == 0)
                        {
                            firstid = lastid;
                            printf(" _first_entry=%d,\n", firstid);
                        }
                        printf(" %s=%d,\n", nm+5, lastid);
                    }
                }
            }
        }
        else
        {
            s = strstr(line, conf_name);
            if (s != 0) found = 1;
        }
    }

    printf(" _last_entry=%d\n}\n", lastid);

    return 0;
}

//------------------------------------------------------------------------------------------------------------
