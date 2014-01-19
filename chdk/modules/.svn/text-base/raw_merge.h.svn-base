#ifndef RAW_MERGE_H
#define RAW_MERGE_H

#include "flt.h"

#define RAW_OPERATION_SUM 0
#define RAW_OPERATION_AVERAGE 1

typedef struct 
{
    base_interface_t    base;

	int (*raw_merge_start)(int action);
	int (*raw_merge_add_file)(const char* filename);
	void (*raw_merge_end)(void);
	int (*raw_subtract)(const char *fromName, const char *fromDir, const char *subName, const char *subDir); 
} librawop_sym;

extern librawop_sym* librawop;

#endif
