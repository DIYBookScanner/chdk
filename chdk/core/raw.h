#ifndef RAW_H
#define RAW_H

// CHDK Raw file saving interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------
#define RAW_PREFIX_IMG          0
#define RAW_PREFIX_CRW          1
#define RAW_PREFIX_SND          2

#define RAW_EXT_JPG             0
#define RAW_EXT_CRW             1
#define RAW_EXT_CR2             2
#define RAW_EXT_THM             3
#define RAW_EXT_WAV             4

//-------------------------------------------------------------------
extern void raw_process(void);
extern void raw_prepare_develop(const char* filename, int prompt);
extern int make_pixel_list(char * ptr, int size);
extern unsigned short get_raw_pixel(unsigned int x,unsigned  int y);
extern char* get_raw_image_addr(void);
extern void patch_bad_pixel(unsigned int x,unsigned  int y);
extern int raw_createfile(void);
extern void raw_closefile(int fd);

//-------------------------------------------------------------------
#endif
