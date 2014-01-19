#ifndef CALLFUNC_H
#define CALLFUNC_H
/*
 call C function with argument list created at runtime.
 See lib/armutil/callfunc.S for documentation
*/
// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

unsigned call_func_ptr(void *func, const unsigned *args, unsigned n_args);
#endif // CALLFUNC_H
