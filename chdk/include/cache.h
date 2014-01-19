#ifndef CACHE_H
#define CACHE_H

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

/*
arm cache control
*/
void icache_flush_all(void);
void dcache_clean_all(void);

#endif
