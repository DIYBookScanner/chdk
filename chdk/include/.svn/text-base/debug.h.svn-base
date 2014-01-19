#ifndef DEBUG_H
#define DEBUG_H


// 1 mean do logging and profiling, 0 mean release version
#define DEBUG_LOGS 1
#define DEBUG_PROF 0

// Simple logger functions

void debug_open( char* filefmt);
void debug_flush( int forcesave );
void debug_close();
void debug_print( char* str );
void debug_print_int( char *fmt, int val );
void debug_print_float( char *fmt, float val );

// Profiler functions

void debug_profiler_start();
void debug_profiler_resume();
void debug_profiler_stop();
void debug_profiler_flush(int forcesave);

void debug_profiler(const char* filename,int line, const char* function, const char* arg);
void debug_profiler_print(const char* str);

#ifdef DEBUG_LOGS
#define DOPEN(s) debug_open(s)
#define DCLOSE debug_close()
#define DLOG_STR(s) debug_print(s)
#define DLOG_INT(s,v) debug_print_int(s,v)
#define DLOG_FLOAT(s,v) debug_print_float(s,v)
#define DLOG_FLUSH debug_flush(1)
#else
#define DOPEN(s)
#define DCLOSE 
#define DLOG_STR(s) 
#define DLOG_INT(s,v) 
#define DLOG_FLOAT(s,v)
#define DLOG_FLUSH
#endif

#ifdef DEBUG_PROF
#define PROFILER(s) debug_profiler(__FILE__, __LINE__, __FUNCTION__, s) 
#define PROFILERSTR(s) debug_profiler_print(s)
#define PROFILERB(a) debug_profiler(__FILE__, __LINE__, __FUNCTION__, "b " #a) 
#define PROFILERE(a) debug_profiler(__FILE__, __LINE__, __FUNCTION__, "e " #a)
#else
#define PROFILER(s)
#define PROFILERSTR(s) 
#define PROFILERB(a) 
#define PROFILERE(a) 

#endif

// Usage sample           PROFILERB(gui_redraw); 

#endif
