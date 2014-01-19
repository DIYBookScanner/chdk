#ifndef STDLIB_H
#define STDLIB_H

// CHDK stdlib

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//==========================================================

#include "versions.h"

typedef struct
{
    unsigned short  major;
    unsigned short  minor;
} _version_t;

typedef int             coord;
typedef unsigned short  color;

#define MAKE_COLOR(bg, fg)  ((color)((((char)(bg))<<8)|((char)(fg))))
#define FG_COLOR(color)     ((unsigned char)(color & 0xFF))
#define BG_COLOR(color)     ((unsigned char)(color >> 8))

//==========================================================

#define NULL		((void*)0)

#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2
#define O_APPEND        8   // DryOS only, wrapper code will removed this for VxWorks so file will be overwritten instead of appended

// CHDK defined values - note does not match VxWorks values
// Values are corrected in 'open' function to match OS requirements
#define O_TRUNC         0x200
#define O_CREAT         0x100

// CHDK 'stat' structure - does not match VxWorks or DryOS internal structs
// Converted in stat function (generic/wrappers.c)
// This is the minimal set of values now available from the firmware
struct stat
{
    unsigned long	st_attrib;
    unsigned long	st_size;
    unsigned long	st_ctime;
    unsigned long	st_mtime;
};

extern int rand(void);
extern void* srand(unsigned int seed);

extern void qsort (void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2));

extern int isdigit(int c);
extern int isspace(int c);
extern int isalpha(int c);
extern int isupper(int c);
extern int islower(int c);
extern int ispunct(int c);
extern int isxdigit(int c);
extern int iscntrl(int c);
extern int isalnum(int c);

extern long sprintf(char *s, const char *st, ...);

extern long strlen(const char *s);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, long n);
extern char *strchr(const char *s, int c);
extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, long n);
extern char *strcat(char *dest, const char *app);
extern char *strrchr(const char *s, int c);
extern char *strpbrk(const char *s, const char *accept);
extern char *strstr(const char *s, const char *s2);

extern long strtol(const char *nptr, char **endptr, int base);
extern unsigned long strtoul(const char *nptr, char **endptr, int base);
#define atoi(n) strtol((n),NULL,0)

extern int tolower(int c);
extern int toupper(int c);

extern void *malloc(long size);
extern void free(void *p);
extern void *umalloc(long size);
extern void ufree(void *p);

extern void *memcpy(void *dest, const void *src, long n);
extern void *memset(void *s, int c, int n);
extern int memcmp(const void *s1, const void *s2, long n);
extern void *memchr(const void *s, int c, int n);

extern void SleepTask(long msec);
extern long taskLock();
extern long taskUnlock();

extern int creat (const char *name, int flags);
extern int open (const char *name, int flags, int mode );
extern int close (int fd);
extern int write (int fd, const void *buffer, long nbytes);
extern int read (int fd, void *buffer, long nbytes);
extern int lseek (int fd, long offset, int whence);
extern long mkdir(const char *dirname);
extern long mkdir_if_not_exist(const char *dirname);
extern int rename(const char *oldname, const char *newname);
extern int chdir(char *pathname);
extern int remove(const char *name);
extern int stat (const char *name, struct stat *pStat);

extern unsigned char SetFileAttributes(const char* fn, unsigned char attr);

// reverse engineered file struct. Appears to be valid for both vxworks and dryos
// don't use this directly unless you absolutely need to
// don't EVER try to create one yourself, as this isn't the full structure.
typedef struct FILE_S {
    int fd;         // used by Read/Write
    unsigned len;   // +4 verfied in Fseek_FileStream
    int unk0;       // +8
    unsigned pos;   // +0xC verified in Fseek_FileStream
    // unk1;        // +0x10 
    // unk2;        // +0x14
    // io_buf;      // +0x18 32k uncached allocated in Fopen_FileStream
    // unk3;        // +0x20 related to StartFileAccess_Sem
    // ...name
} FILE;

extern FILE *fopen(const char *filename, const char *mode);
extern long fclose(FILE *f);
extern long fread(void *buf, long elsize, long count, FILE *f);
extern long fwrite(const void *buf, long elsize, long count, FILE *f);
extern long fseek(FILE *file, long offset, long whence);
extern long fflush(FILE *file);
extern long feof(FILE *file);
extern long ftell(FILE *file);
extern char *fgets(char *buf, int n, FILE *f);

extern void msleep(long msec);
extern long task_lock();
extern long task_unlock();
extern const char *task_name(int id);
int task_id_list_get(int *idlist,int size);
extern const char *strerror(int num);
// on vxworks we could find the actual errno, but this is easier to automate sig
// doesn't exist on dryos, but we stub it
extern int errnoOfTaskGet(int tid);
#define errno (errnoOfTaskGet(0))

//-------------------------------------------------------------------------------------

#define DOS_ATTR_RDONLY         0x01            /* read-only file */
#define DOS_ATTR_HIDDEN         0x02            /* hidden file */
#define DOS_ATTR_SYSTEM         0x04            /* system file */
#define DOS_ATTR_VOL_LABEL      0x08            /* volume label (not a file) */
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
#define DOS_ATTR_ARCHIVE        0x20            /* file subject to archiving */

//-------------------------------------------------------------------------------------

// CHDK structs for opendir/readdir/closedir
// Conversion to/from camera specific versions done in wrapper code
struct dirent   // Returned from readdir
{
    char            d_name[100];    // We only use the name value
};

// Returned from opendir
typedef struct
{
    void            *cam_DIR;   // Camera specific internal DIR structure
    struct dirent   dir;        // Last info returned from readdir
} DIR;

extern DIR*           opendir (const char* name);
extern struct dirent* readdir (DIR*);
extern int            closedir (DIR*);
//extern void           rewinddir (DIR*);   // Not used

//-------------------------------------------------------------------------------------

struct tm
	{
	int tm_sec;	/* seconds after the minute	- [0, 59] */
	int tm_min;	/* minutes after the hour	- [0, 59] */
	int tm_hour;	/* hours after midnight		- [0, 23] */
	int tm_mday;	/* day of the month		- [1, 31] */
	int tm_mon;	/* months since January		- [0, 11] */
	int tm_year;	/* years since 1900	*/
	int tm_wday;	/* days since Sunday		- [0, 6] */
	int tm_yday;	/* days since January 1		- [0, 365] */
	int tm_isdst;	/* Daylight Saving Time flag */
	};

typedef unsigned long time_t;

extern struct tm * localtime(const time_t *_tod);
extern struct tm * get_localtime();

struct utimbuf {
    unsigned long actime;       /* set the access time */
    unsigned long modtime;      /* set the modification time */
};

extern int utime(const char *file, struct utimbuf *newTimes);
extern unsigned long time(unsigned long *timer);
extern long strftime(char *s, unsigned long maxsize, const char *format, const struct tm *timp);
extern time_t mktime(struct tm *timp);

extern int abs( int v );

#endif
