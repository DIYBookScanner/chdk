#ifndef FILEUTIL_H
#define FILEUTIL_H

//-------------------------------------------------------------------

// fileutil.c functions

typedef int (*callback_process_file)(char* buf, int size);

extern int process_file(const char *filename, callback_process_file callback, int add0);
extern char* load_file(const char* name, int* size, int add0);

extern int load_int_value_file(const char* filename, int* value_p);
extern void save_int_value_file(const char* filename, int value);

//-------------------------------------------------------------------

#endif
