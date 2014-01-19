#ifndef LANG_H
#define LANG_H

// CHDK Language String interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------

extern void lang_init(int num);

extern void lang_load_from_file(const char *filename);
extern void lang_map_preparsed_from_mem( char* gui_lang_default, int num );

extern char* lang_str(int str);
extern unsigned int lang_strhash31(int langid);

//-------------------------------------------------------------------

#endif
