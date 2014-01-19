#ifndef SHUTDOWN_H
#define SHUTDOWN_H

// CHDK Shutdown / reboot interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

/*
 reboot, optionally loading a different binary
 see lib/armutil/reboot.c for documentation
*/
int reboot(const char *bootfile);           // ARM code
void camera_shutdown_in_a_second(void);
void disable_shutdown();
void enable_shutdown();
void __attribute__((noreturn)) shutdown();

#endif

