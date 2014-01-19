#ifndef FILE_COUNTER_H
#define FILE_COUNTER_H

// CHDK Image file counter interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

long get_file_counter();
long get_exposure_counter();
long get_file_next_counter();
void get_target_dir_name(char*);
long get_target_file_num();

#endif

