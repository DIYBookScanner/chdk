#include "camera.h"
#include "lolevel.h"
#include "platform.h"
#include "raw_buffer.h"
#include "conf.h"
#include "math.h"
#include "levent.h"
#include "stdlib.h"
#include "ptp_chdk.h"

//----------------------------------------------------------------------------
// Char Wrappers

#if CAM_DRYOS
#define _U      0x01    /* upper */ 
#define _L      0x02    /* lower */ 
#define _D      0x04    /* digit */ 
#define _C      0x20    /* cntrl */ 
#define _P      0x10    /* punct */ 
#define _S      0x40    /* white space (space/lf/tab) */ 
#define _X      0x80    /* hex digit */ 
#define _SP     0x08    /* hard space (0x20) */ 
static int _ctype(int c,int t) {
    extern unsigned char ctypes[];  // Firmware ctypes table (in stubs_entry.S) 
    return ctypes[c&0xFF] & t;
}

int isdigit(int c) { return _ctype(c,_D); }
int isspace(int c) { return _ctype(c,_S); }
int isalpha(int c) { return _ctype(c,(_U|_L)); }
int isupper(int c) { return _ctype(c,_U); }
int islower(int c) { return _ctype(c,_L); }
int ispunct(int c) { return _ctype(c,_P); }
int isxdigit(int c) { return _ctype(c,(_X|_D)); }
int iscntrl(int c) { return _ctype(c,_C); }

int tolower(int c) { return isupper(c) ? c | 0x20 : c; }
int toupper(int c) { return islower(c) ? c & ~0x20 : c; }

#else	//!CAM_DRYOS

int isdigit(int c) { return _isdigit(c); }
int isspace(int c) { return _isspace(c); }
int isalpha(int c) { return _isalpha(c); }
int isupper(int c) { return _isupper(c); }
int islower(int c) { return _islower(c); }
int ispunct(int c) { return _ispunct(c); }
int isxdigit(int c) { return _isxdigit(c); }

// don't want to require the whole ctype table on vxworks just for this one
int iscntrl(int c) { return ((c >=0 && c <32) || c == 127); }

int tolower(int c) { return _tolower(c); }
int toupper(int c) { return _toupper(c); }

#endif

int isalnum(int c) { return (isdigit(c) || isalpha(c)); }

//----------------------------------------------------------------------------

void msleep(long msec)
{
    _SleepTask(msec);
}

#ifndef CAM_DRYOS
long task_lock()
{
    return _taskLock();
}

long task_unlock()
{
    return _taskUnlock();
}

const char *task_name(int id)
{
    return _taskName(id);
}

int task_id_list_get(int *idlist,int size)
{
    return _taskIdListGet(idlist,size);
}
#endif

long get_property_case(long id, void *buf, long bufsize)
{
    return _GetPropertyCase(id, buf, bufsize);
}

long set_property_case(long id, void *buf, long bufsize)
{
    return _SetPropertyCase(id, buf, bufsize);
}

// FlashParamsTable entries point to this structure
#if CAM_FLASHPARAMS_VERSION == 2
// ixus30_sd200, ixus40_sd300
typedef struct
{
    short   unk1;
    short   unk2;
    void*   data;   // Pointer to param data
    short   size;   // param size
    short   unk3;
    int     unk4;
    short   unk5;
    short   unk6;
} flashParam;
#else
// version 3 (every camera from 2005 on)
typedef struct
{
    void*   data;   // Pointer to param data
    short   unk1;
    short   size;   // param size
    short   unk2;
    short   unk3;
    short   unk4;
    char    unk5;
    char    unk6;
} flashParam;
#endif // CAM_FLASHPARAMS_VERSION

short get_parameter_size(long id)
{
    extern flashParam* FlashParamsTable[];

    if ((id >= 0) && (id < get_flash_params_count()))
        return FlashParamsTable[id]->size;

    return 0;
}

long get_parameter_data(long id, void *buf, long bufsize)
{
    return _GetParameterData(id|PARAMETER_DATA_FLAG, buf, bufsize);
}

long set_parameter_data(long id, void *buf, long bufsize)
{
    return _SetParameterData(id|PARAMETER_DATA_FLAG, buf, bufsize);
}

void mark_filesystem_bootable()
{
#ifdef  CAM_DRYOS_2_3_R47
    // DryOS release 47 (2011) no longer has the UpdateMBROnFlash function to write the master boot record on
    // the SD card. Instead it has seperate functions for writing the 'BOOTDISK' and 'SCRIPT' signatures to
    // the MBR. The firmware function also takes care of writing the bootdisk signature to the correct location
    // for FAT32 formatted cards.
    _MakeSDCardBootable(0);
#else
    _UpdateMBROnFlash(0, 0x40, "BOOTDISK");
#endif
}

void __attribute__((weak)) vid_bitmap_refresh()
{
    _RefreshPhysicalScreen(1);
}

long lens_get_zoom_pos()
{
    return _GetZoomLensCurrentPosition();
}

void lens_set_zoom_pos(long newpos)
{
}

long lens_get_zoom_point()
{
    return _GetZoomLensCurrentPoint();
}

void lens_set_zoom_point(long newpt)
{
    if (newpt < 0) {
        newpt = 0;
    } else if (newpt >= zoom_points) {
        newpt = zoom_points-1;
    }

#if defined(CAM_USE_ALT_SET_ZOOM_POINT)

	if (lens_get_zoom_point() != newpt)
	{
		// Get current digital zoom mode & state
		// state == 1 && mode == 0 --> Digital Zoom Standard
		int digizoom_mode, digizoom_state, digizoom_pos;
		get_property_case(PROPCASE_DIGITAL_ZOOM_MODE,&digizoom_mode,sizeof(digizoom_mode));
		get_property_case(PROPCASE_DIGITAL_ZOOM_STATE,&digizoom_state,sizeof(digizoom_state));
		get_property_case(PROPCASE_DIGITAL_ZOOM_POSITION,&digizoom_pos,sizeof(digizoom_pos));
		if ((digizoom_state == 1) && (digizoom_mode == 0) && (digizoom_pos != 0))
		{
			// reset digital zoom in case camera is in this zoom range
			extern void _PT_MoveDigitalZoomToWide();
			_PT_MoveDigitalZoomToWide();
		}

  #if defined(CAM_USE_ALT_PT_MoveOpticalZoomAt)
		// SX30 - _MoveZoomLensWithPoint crashes camera
		// _PT_MoveOpticalZoomAt works, and updates PROPCASE_OPTICAL_ZOOM_POSITION; but doesn't wait for zoom to finish
        // IXUS220, SX220/230 - _MoveZoomLensWithPoint does not notify the JPEG engine of the new focal length,
        //                      causing incorrect lens distortion fixes to be applied; _PT_MoveOpticalZoomAt works
		extern void _PT_MoveOpticalZoomAt(long*);
		_PT_MoveOpticalZoomAt(&newpt);
  #else
	    _MoveZoomLensWithPoint((short*)&newpt);
  #endif

		// have to sleep here, zoom_busy set in another task, without sleep this will hang
		while (zoom_busy) msleep(10);

		// g10,g12 & sx30 only use this value for optical zoom
		zoom_status=ZOOM_OPTICAL_MAX;

  #if !defined(CAM_USE_ALT_PT_MoveOpticalZoomAt) 
	    _SetPropertyCase(PROPCASE_OPTICAL_ZOOM_POSITION, &newpt, sizeof(newpt));
  #endif
	}
#else	// !(CAM_USE_ALT_SET_ZOOM_POINT)
    _MoveZoomLensWithPoint((short*)&newpt);

    // tight loop here hangs some cameras (the task that clears zoom_busy
    // is starved; seen at least on S95 and IXUS 220), so stick in a sleep
    while (zoom_busy) msleep(10);

    if (newpt==0) zoom_status=ZOOM_OPTICAL_MIN;
    else if (newpt >= zoom_points) zoom_status=ZOOM_OPTICAL_MAX;
    else zoom_status=ZOOM_OPTICAL_MEDIUM;
    _SetPropertyCase(PROPCASE_OPTICAL_ZOOM_POSITION, &newpt, sizeof(newpt));
#endif	// !(CAM_USE_ALT_SET_ZOOM_POINT)
}

void lens_set_zoom_speed(long newspd)
{
    if (newspd < 5) {
        newspd = 5;
    } else if (newspd > 100) {
        newspd = 100;
    }
    _SetZoomActuatorSpeedPercent((short*)&newspd);
}

void lens_set_focus_pos(long newpos)
{
    if (newpos >= MAX_DIST) newpos = INFINITY_DIST; // Set to infinity value that will work on all cameras
    _MoveFocusLensToDistance((short*)&newpos);
    while ((shooting_is_flash_ready()!=1) || (focus_busy)) msleep(10);
    newpos = _GetFocusLensSubjectDistance();
    _SetPropertyCase(PROPCASE_SUBJECT_DIST1, &newpos, sizeof(newpos));
    _SetPropertyCase(PROPCASE_SUBJECT_DIST2, &newpos, sizeof(newpos));
}

void play_sound(unsigned sound)
{
	static const int sounds[]={ 0x2001, //startup sound
                                0x2002, //shutter sound
                                0x2003, //button press sound
                                0x2004, //self-timer sound
                                0xC211, //short beep
                                50000,  // AF confirmation
                                0xC507, // error beep imo
                                0x400D, // LONG ERROR BEEP CONTINIUOUS- warning, cannot be stopped (yet)
                            };
    if(sound >= sizeof(sounds)/sizeof(sounds[0]))
        return;

    _PT_PlaySound(sounds[sound], 0);
}

long stat_get_vbatt()
{
    return _VbattGet();
}

int get_battery_temp()
{
    return _GetBatteryTemperature();
}

int get_ccd_temp()
{
    return _GetCCDTemperature();
}

int get_optical_temp()
{
    return _GetOpticalTemperature();
}

long get_tick_count()
{
long t;
#if !CAM_DRYOS
    _GetSystemTime(&t);
    return t;
#else
    return (int)_GetSystemTime(&t);
#endif
}

#if CAM_HAS_ND_FILTER
void PutInNdFilter()                { _PutInNdFilter(); }
void PutOutNdFilter()               { _PutOutNdFilter(); }
#endif

long GetCurrentAvValue()            { return _GetCurrentAvValue(); }
long IsStrobeChargeCompleted()      { return _IsStrobeChargeCompleted(); }
void SetCurrentCaptureModeType()    { _SetCurrentCaptureModeType(); }

#if CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
void UnsetZoomForMovie()            { _UnsetZoomForMovie(); }
#endif

#ifdef CAM_AV_OVERRIDE_IRIS_FIX
int MoveIrisWithAv(short *v)        { return _MoveIrisWithAv(v); }
#endif

#if CAM_EV_IN_VIDEO
void ExpCtrlTool_StartContiAE(int v1, int v2)   { _ExpCtrlTool_StartContiAE(v1,v2); }
void ExpCtrlTool_StopContiAE(int v1, int v2)    { _ExpCtrlTool_StopContiAE(v1, v2); }
short SetAE_ShutterSpeed(short *tv)             { return _SetAE_ShutterSpeed(tv); }
#endif

//----------------------------------------------------------------------------
// I/O wrappers

/*int creat (const char *name, int flags)
{
    return _creat(name, flags);
}*/

int open (const char *name, int flags, int mode )
{
#if !CAM_DRYOS
    // Adjust O_TRUNC and O_CREAT flags for VxWorks
    // Remove O_APPEND flag if present (not in VxWorks)
    flags = (flags & ~(O_TRUNC|O_CREAT|O_APPEND)) | ((flags & (O_TRUNC|O_CREAT)) << 1);
#else
    if(!name || name[0]!='A')
        return -1;
#endif
#if defined(CAM_STARTUP_CRASH_FILE_OPEN_FIX)	// enable fix for camera crash at startup when opening the conf / font files
												// see http://chdk.setepontos.com/index.php?topic=6179.0
	if (flags == O_RDONLY)						// At startup opening the conf / font files conflicts with Canon task if use _Open. Camera can randomly crash.
		return _open(name, flags, mode);
#endif
    return _Open(name, flags, mode);
}

int close (int fd)
{
    return _Close(fd);
}

int write (int fd, const void *buffer, long nbytes)
{
    return _Write(fd, buffer, nbytes);
}

int read (int fd, void *buffer, long nbytes)
{
    return _Read(fd, buffer, nbytes);
}

int lseek (int fd, long offset, int whence)
{
    return _lseek(fd, offset, whence); /* yes, it's lower-case lseek here since Lseek calls just lseek (A610) */
}

long mkdir(const char *dirname)
{
#ifdef MKDIR_RETURN_ONE_ON_SUCCESS
    // mkdir returns 1 on success, 0 on fail. So, values are inverted, to be compatible with previous versions
    if(_MakeDirectory_Fut(dirname,1)) return 0;
    else                              return 1;
#else
    return _MakeDirectory_Fut(dirname,-1); // meaning of second arg is not clear, firmware seems to use -1
#endif
}

long mkdir_if_not_exist(const char *dirname)
{
    // Check if directory exists and create it if it does not.
    if (stat(dirname,0) != 0) return mkdir(dirname);
    return 0;   // Success
}

int remove(const char *name)
{
#ifdef CAM_DRYOS_2_3_R39
    // For DryOS R39 and later need to check if 'name' is a file or directory
    // and call appropriate delete function.
    struct stat st;
    if (stat(name,&st) == 0)
    {
        if (st.st_attrib & DOS_ATTR_DIRECTORY)
        	return _DeleteDirectory_Fut(name);
        else
        	return _DeleteFile_Fut(name);
    }
    return -1;  // return fail - file / directory does not exist
#else
    return _DeleteFile_Fut(name);
#endif
}

//----------------------------------------------------------------------------
// directory wrappers

extern int   _closedir(void *d);
//extern void  _rewinddir(void *d);     // Not used

DIR *opendir(const char* name)
{
    // Create CHDK DIR structure
    DIR *dir = malloc(sizeof(DIR));
    // If malloc failed return failure
    if (dir == 0) return NULL;

    // Save camera internal DIR structure (we don't care what it is)
#if defined(CAM_DRYOS)
    extern void *_OpenFastDir(const char* name);
    dir->cam_DIR = _OpenFastDir(name);
#else
    extern void *_opendir(const char* name);
    dir->cam_DIR = _opendir(name);
#endif
    // Init readdir return value
    dir->dir.d_name[0] = 0;

    // If failed clean up and return failure
    if (!dir->cam_DIR)
    {
        free(dir);
        return NULL;
    }

    return dir;
}

#ifndef CAM_DRYOS

// Internal VxWorks dirent structure returned by readdir
struct __dirent
{
    char            d_name[100];
};

extern void *_readdir(void *d);

struct dirent* readdir(DIR *d)
{
    if (d && d->cam_DIR)
    {
        // Get next entry from firmware function
        struct __dirent *de = _readdir(d->cam_DIR);
        // Return next directory name if present, else return 0 (end of list)
        if (de)
        {
            strcpy(d->dir.d_name,de->d_name);
            return &d->dir;
        }
        else
        {
            d->dir.d_name[0] = 0;
        }
    }
    return NULL;
}

#else // dryos

extern int _ReadFastDir(void *d, void* dd); // DRYOS

struct dirent * readdir(DIR *d)
{
    if (d && d->cam_DIR)
    {
        _ReadFastDir(d->cam_DIR, d->dir.d_name);
        return d->dir.d_name[0]? &d->dir : NULL;
    }
    return NULL;
}

#endif // dryos dir functions

int closedir(DIR *d)
{
    int rv = -1;
    if (d && d->cam_DIR)
    {
        rv = _closedir(d->cam_DIR);
        // Mark closed (just in case)
        d->cam_DIR = 0;
        // Free allocated memory
        free(d);    
    }
    return rv;
}

//Not used
//void rewinddir(DIR *d)
//{
//    if (d && d->cam_DIR)
//    {
//        _rewinddir(d->cam_DIR);
//    }
//}

//-----------------------------------------------------------------------------------

// Internal camera firmare 'stat' structures

#if !CAM_DRYOS

struct	__stat  // VxWorks
{
    unsigned long	st_dev;		/* device ID number */
    unsigned long	st_ino;		/* file serial number */
    unsigned short	st_mode;	/* file mode (see below) */
    short		st_nlink;	/* number of links to file */
    short		st_uid;		/* user ID of file's owner */
    short		st_gid;		/* group ID of file's group */
    unsigned long	st_rdev;	/* device ID, only if special file */
    unsigned long	st_size;	/* size of file, in bytes */
    unsigned long	st_atime;	/* time of last access */
    unsigned long	st_mtime;	/* time of last modification */
    unsigned long	st_ctime;	/* time of last change of file status */
    long		st_blksize;
    long		st_blocks;
    unsigned char	st_attrib;	/* file attribute byte (dosFs only) */
    int			reserved1;	/* reserved for future use */
    int			reserved2;	/* reserved for future use */
    int			reserved3;	/* reserved for future use */
    int			reserved4;	/* reserved for future use */
    int			reserved5;	/* reserved for future use */
    int			reserved6;	/* reserved for future use */
};

#else

#ifndef CAM_DRYOS_2_3_R39

struct	__stat  // DryOS pre R39
    {
    unsigned long	st_dev;		//?
    unsigned long	st_ino;		//?
    unsigned short	st_mode;	//?
    short		st_nlink;	//?
    short		st_uid;		//?
    short		st_gid;		//?
    unsigned long	st_atime;	//?
    unsigned long	st_mtime;	//?
    unsigned long	st_ctime;	//?
    unsigned long	st_size;
    long		st_blksize;	//?
    long		st_blocks;	//?
    unsigned char	st_attrib;
    int			reserved1;	//
    int			reserved2;	//
    int			reserved3;	//
    int			reserved4;	//
    int			reserved5;	//
    int			reserved6;	//
};

#else

struct __stat   // DryOS post R39
{
    unsigned long	st_unknown_1;
    unsigned long	st_attrib;
    unsigned long	st_size;
    unsigned long	st_ctime;
    unsigned long	st_mtime;
    unsigned long	st_unknown_2;
};

#endif//CAM_DRYOS_2_3_R39

#endif//CAM_DRYOS

int stat(const char *name, struct stat *pStat)
{
    // sanity check. canon firmware hangup if start not from 'A/'
    if ( !name || (name[0] | 0x20)!='a' || name[1]!='/' ) return 1;

    // use temp __stat stucture to match camera firmware
    // and copy values across to output
    struct __stat lStat;
    int rv = _stat(name, &lStat);
    if (pStat)
    {
        if (rv == 0)
        {
            pStat->st_attrib = lStat.st_attrib;
            pStat->st_size = lStat.st_size;
            pStat->st_ctime = lStat.st_ctime;
            pStat->st_mtime = lStat.st_mtime;
        }
        else
        {
            memset( pStat, 0, sizeof(struct stat));
        }
    }
    return rv;
}

FILE *fopen(const char *filename, const char *mode) {
#ifdef CAM_DRYOS
    if(!filename || filename[0]!='A') {
        return NULL;
    }
#endif
    return (FILE *)_Fopen_Fut(filename,mode);
}

long fclose(FILE *f) {
    return _Fclose_Fut((long)f);
}

long fread(void *buf, long elsize, long count, FILE *f) {
    return _Fread_Fut(buf,elsize,count,(long)f);
}

long fwrite(const void *buf, long elsize, long count, FILE *f) {
    return _Fwrite_Fut(buf,elsize,count,(long)f);
}

long fseek(FILE *file, long offset, long whence) {
    return _Fseek_Fut((long)file,offset,whence);
}

long feof(FILE * file) {
    return _Feof_Fut((long)file);
}

long fflush(FILE * file) {
    return _Fflush_Fut((long)file);
}

char *fgets(char *buf, int n, FILE *f) {
    return _Fgets_Fut(buf,n,(int)f);
}

int rename(const char *oldname, const char *newname) {
 return _RenameFile_Fut(oldname, newname);
}

unsigned int GetFreeCardSpaceKb(void){
	return (_GetDrive_FreeClusters(0)*(_GetDrive_ClusterSize(0)>>9))>>1;
}

unsigned int GetTotalCardSpaceKb(void){
	return (_GetDrive_TotalClusters(0)*(_GetDrive_ClusterSize(0)>>9))>>1;
}

//----------------------------------------------------------------------------

int errnoOfTaskGet(int tid) {
#if !CAM_DRYOS
    return _errnoOfTaskGet(tid);
#else
    return 0;
#endif
}

//----------------------------------------------------------------------------
// String wrappers

long strlen(const char *s) {
    return _strlen(s);
}

int strcmp(const char *s1, const char *s2) {
    return _strcmp(s1, s2);
}

int strncmp(const char *s1, const char *s2, long n) {
    return _strncmp(s1, s2, n);
}

char *strchr(const char *s, int c) {
    return _strchr(s, c);
}

char *strcpy(char *dest, const char *src) {
    return _strcpy(dest, src);
}

char *strncpy(char *dest, const char *src, long n) {
    return _strncpy(dest, src, n);
}

char *strcat(char *dest, const char *app) {
    return _strcat(dest, app);
}

char *strrchr(const char *s, int c) {
    return _strrchr(s, c);
}

long strtol(const char *nptr, char **endptr, int base) {
    return _strtol(nptr, endptr, base);
}

unsigned long strtoul(const char *nptr, char **endptr, int base) {
#if CAM_DRYOS
    return (unsigned long)_strtolx(nptr, endptr, base, 0);
#else
    return _strtoul(nptr, endptr, base);
#endif
}

char *strpbrk(const char *s, const char *accept) {
#if !CAM_DRYOS
    return _strpbrk(s, accept);
#else
    const char *sc1,*sc2;

    for( sc1 = s; *sc1 != '\0'; ++sc1) {
     for( sc2 = accept; *sc2 != '\0'; ++sc2) {
      if (*sc1 == *sc2) return (char *) sc1;
     }
    }
return (void*)0;
#endif
}

char *strstr (const char *s1, const char *s2)
{
  const char *p = s1;
  const int len = _strlen (s2);

  for (; (p = _strchr (p, *s2)) != 0; p++)
  {
    if (_strncmp (p, s2, len) == 0)
      return (char *)p;
  }
  return (0);
}


//----------------------------------------------------------------------------

long sprintf(char *s, const char *st, ...)
{
    long res;
    __builtin_va_list va;
    __builtin_va_start(va, st);
    res = _vsprintf(s, st, va);
    __builtin_va_end(va);
    return res;
}

// strerror exists on vxworks cams,
// but it does about the same thing as this
const char *strerror(int en) {
#if !CAM_DRYOS
    static char msg[20];
    sprintf(msg,"errno 0x%X",en);
    return msg;
#else
    return "error";
#endif
}

//----------------------------------------------------------------------------
// Time wrappers

unsigned long time(unsigned long *timer) {
    return _time(timer);
}

int utime(const char *file, struct utimbuf *newTimes) {
#if !CAM_DRYOS
    return _utime(file, newTimes);
#else
    int res=0;
    int fd;
    fd = _open(file, 0, 0);

#ifdef CAM_DRYOS_2_3_R39
    if (fd>=0) {
        _close(fd);
        res=_SetFileTimeStamp(file, newTimes->modtime, newTimes->actime);
    }
#else
    if (fd>=0) {
        res=_SetFileTimeStamp(fd, newTimes->modtime, newTimes->actime);
        _close(fd);
    }
    // return value compatibe with utime: ok=0 fail=-1
#endif
    return (res)?0:-1;
#endif
}

struct tm *localtime(const time_t *_tod) {
#if !CAM_DRYOS
    return _localtime(_tod);
#else
    // for DRYOS cameras do something with this!  - sizeof(x[]) must be >= sizeof(struct tm) :  'static int x[9];'
    static int x[10];
    return _LocalTime(_tod, &x);
#endif
}

struct tm *get_localtime()
{
    time_t t = time(NULL);
    return localtime(&t);
}

long strftime(char *s, unsigned long maxsize, const char *format, const struct tm *timp) {
	return _strftime(s,maxsize,format,timp);
}

time_t mktime(struct tm *timp) {
#if !CAM_DRYOS
	return _mktime(timp);
#else
	int timp_ext[10]; // struct tm + a ptr
	_memcpy(timp_ext,timp,9*sizeof(int));
	timp_ext[9]=0;
	long retval = _mktime_ext(&timp_ext);
	_memcpy(timp,timp_ext,9*sizeof(int));
	return retval;
#endif
}

//----------------------------------------------------------------------------
// Math wrappers

double _log(double x) {
    return __log(x);
}

double _log10(double x) {
    return __log10(x);
}

double _pow(double x, double y) {
    return __pow(x, y);
}

double _sqrt(double x) {
    return __sqrt(x);
}

//----------------------------------------------------------------------------

#ifdef OPT_EXMEM_MALLOC
void *exmem_alloc(int pool_id,int size,int unk,int unk2)
{
    return _exmem_alloc(pool_id,size,unk,unk2);
}
#endif

void *canon_malloc(long size)
{
    return _malloc(size);
}

void canon_free(void *p)
{
    _free(p);
}

void *umalloc(long size) {
    return _AllocateUncacheableMemory(size);
}

void ufree(void *p) {
    return _FreeUncacheableMemory(p);
}

void *memcpy(void *dest, const void *src, long n) {
    return _memcpy(dest, src, n);
}

void *memset(void *s, int c, int n) {
    return _memset(s, c, n);
}

int memcmp(const void *s1, const void *s2, long n) {
    return _memcmp(s1, s2, n);
}

void *memchr(const void *s, int c, int n) {
#if !CAM_DRYOS
	return _memchr(s,c,n);
#else
	while (n-- > 0) {
		if (*(char *)s == c)
			return (void *)s;
		s++;
	}
	return (void *)0;
#endif
}

//----------------------------------------------------------------------------

void GetMemInfo(cam_meminfo *camera_meminfo)
{
// Use firmware GetMemInfo function to retrieve info about Canon heap memory allocation

#if defined(CAM_DRYOS)
    // Prior to dryos R39 GetMemInfo returns 9 values, after R39 it returns 10 (all but 1 are used in each case)
    int fw_info[10];
    extern void _GetMemInfo(int*);
    _GetMemInfo(fw_info);

#if defined(CAM_DRYOS_2_3_R39)
    // For newer dryos version copy all 9 used values to CHDK structure
    camera_meminfo->start_address        = fw_info[0];
    camera_meminfo->end_address          = fw_info[1];
    camera_meminfo->total_size           = fw_info[2];
    camera_meminfo->allocated_size       = fw_info[3];
    camera_meminfo->allocated_peak       = fw_info[4];
    camera_meminfo->allocated_count      = fw_info[5];
    camera_meminfo->free_size            = fw_info[6];
    camera_meminfo->free_block_max_size  = fw_info[7];
    camera_meminfo->free_block_count     = fw_info[8];
#else
    // For older dryos version copy 8 used values to CHDK structure and calculate missing value
    camera_meminfo->start_address        = fw_info[0];
    camera_meminfo->end_address          = fw_info[0] + fw_info[1];
    camera_meminfo->total_size           = fw_info[1];
    camera_meminfo->allocated_size       = fw_info[2];
    camera_meminfo->allocated_peak       = fw_info[3];
    camera_meminfo->allocated_count      = fw_info[4];
    camera_meminfo->free_size            = fw_info[5];
    camera_meminfo->free_block_max_size  = fw_info[6];
    camera_meminfo->free_block_count     = fw_info[7];
#endif
#else // vxworks
extern int sys_mempart_id;
    int fw_info[5];
    // -1 for invalid
    memset(camera_meminfo,0xFF,sizeof(cam_meminfo));
#ifdef CAM_NO_MEMPARTINFO
    camera_meminfo->free_block_max_size = _memPartFindMax(sys_mempart_id);
#else
    _memPartInfoGet(sys_mempart_id,fw_info);
    // TODO we could fill in start address from _start + MEMISOSIZE, if chdk not in exmem
    // these are guessed, look reasonable on a540
    camera_meminfo->free_size = fw_info[0];
    camera_meminfo->free_block_count = fw_info[1];
    camera_meminfo->free_block_max_size = fw_info[2];
    camera_meminfo->allocated_size = fw_info[3];
    camera_meminfo->allocated_count = fw_info[4];
#endif
#endif
}

//----------------------------------------------------------------------------

int rand(void) {
    return _rand();
}

void *srand(unsigned int seed) {
    return _srand(seed);
}

void qsort(void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2)) {
    _qsort(__base, __nelem, __size, __cmp);
}

static int shutdown_disabled = 0;
void disable_shutdown() {
    if (!shutdown_disabled) {
        _LockMainPower();
        shutdown_disabled = 1;
    }
}

void enable_shutdown() {
    if (shutdown_disabled) {
        _UnlockMainPower();
        shutdown_disabled = 0;
    }
}
void camera_shutdown_in_a_second(void){
int i;
//#if CAM_DRYOS
//#else
_SetAutoShutdownTime(1); // 1 sec
for (i=0;i<200;i++) _UnlockMainPower(); // set power unlock counter to 200 or more, because every keyboard function call try to lock power again ( if "Disable LCD off" menu is "alt" or "script").
//#endif
}

unsigned int GetJpgCount(void){
 return strtol(camera_jpeg_count_str(),((void*)0),0);
}

unsigned int GetRawCount(void){
 return GetFreeCardSpaceKb()/((camera_sensor.raw_size / 1024)+GetFreeCardSpaceKb()/GetJpgCount());
}

void EnterToCompensationEVF(void)
{
  _EnterToCompensationEVF();
}

void ExitFromCompensationEVF()
{
  _ExitFromCompensationEVF();
}

void TurnOnBackLight(void)
{
  _TurnOnBackLight();
}

void TurnOffBackLight(void)
{
  _TurnOffBackLight();
}

extern void gui_set_need_restore();

void TurnOnDisplay(void)
{
  _TurnOnDisplay();
  // required to re-draw the canon and CHDK UI after re-enabling display
  gui_set_need_restore() ;
}

void TurnOffDisplay(void)
{
  _TurnOffDisplay();
}

void DoAELock(void)
{
  _DoAELock();
}

void UnlockAE(void)
{
  _UnlockAE();
}

void DoAFLock(void)
{
  _DoAFLock();
}

void UnlockAF(void)
{
  _UnlockAF();
}

int EngDrvRead(int gpio_reg)
{
  return _EngDrvRead(gpio_reg);
}

#if CAM_MULTIPART

#define SECTOR_SIZE 512
static char *mbr_buf=(void*)0;
static unsigned long drive_sectors;

int is_mbr_loaded()
{
	return (mbr_buf == (void*)0) ? 0 : 1;
}

#ifndef	CAM_DRYOS

int mbr_read(char* mbr_sector, unsigned long drive_total_sectors, unsigned long *part_start_sector,  unsigned long *part_length){
// return value: 1 - success, 0 - fail
// called only in VxWorks

 int offset=0x10; // points to partition #2
 int valid;

 if ((mbr_sector[0x1FE]!=0x55) || (mbr_sector[0x1FF]!=0xAA)) return 0; // signature check

 mbr_buf=_AllocateUncacheableMemory(SECTOR_SIZE);
 _memcpy(mbr_buf,mbr_sector,SECTOR_SIZE);
 drive_sectors=drive_total_sectors;

 while(offset>=0) {

  *part_start_sector=(*(unsigned short*)(mbr_sector+offset+0x1C8)<<16) | *(unsigned short*)(mbr_sector+offset+0x1C6);
  *part_length=(*(unsigned short*)(mbr_sector+offset+0x1CC)<<16) | *(unsigned short*)(mbr_sector+offset+0x1CA);

  valid= (*part_start_sector) && (*part_length) &&
         (*part_start_sector<=drive_total_sectors) &&
         (*part_start_sector+*part_length<=drive_total_sectors) &&
         ((mbr_sector[offset+0x1BE]==0) || (mbr_sector[offset+0x1BE]==0x80)); // status: 0x80 (active) or 0 (non-active)

  if (valid && ((mbr_sector[0x1C2+offset]==0x0B) || (mbr_sector[0x1C2+offset]==0x0C))) break;   // FAT32 secondary partition

  offset-=0x10;

 }

 return valid;
}

#else

int mbr_read_dryos(unsigned long drive_total_sectors, char* mbr_sector ){
// Called only in DRYOS
 mbr_buf=_AllocateUncacheableMemory(SECTOR_SIZE);
 _memcpy(mbr_buf,mbr_sector,SECTOR_SIZE);
 drive_sectors=drive_total_sectors;
 return drive_total_sectors;
}

#endif

int get_part_count(void)
{
  unsigned long part_start_sector, part_length;
  char part_status, part_type;
  int i;
  int count=0;
  if (is_mbr_loaded())
  {
    for (i=0; i<=3;i++)
    {
      part_start_sector=(*(unsigned short*)(mbr_buf+i*16+0x1C8)<<16) | *(unsigned short*)(mbr_buf+i*16+0x1C6);
      part_length=(*(unsigned short*)(mbr_buf+i*16+0x1CC)<<16) | *(unsigned short*)(mbr_buf+i*16+0x1CA);
      part_status=mbr_buf[i*16+0x1BE];
      part_type=mbr_buf[0x1C2+i*16];
      if ( part_start_sector && part_length && part_type && ((part_status==0) || (part_status==0x80)) ) count++;
    }
  }
  return count;
}
int get_part_type()
{
  int partType = 0x00;
  if (is_mbr_loaded())
  {
    partType=mbr_buf[0x1C2+(get_active_partition()-1)*16];
  }
  return partType;
} 

static int boot_partition = 0;
static int partition_changed = 0;
int is_partition_changed()
{
  return partition_changed;
}

int swap_partitions(int new_partition)
{
  if (is_mbr_loaded())
  {
    int i,j,p;
    char c;
    
    int partition_count = get_part_count();
    int active_partition = get_active_partition();
    
    if(!boot_partition)
    {
      boot_partition = active_partition;
    }

    // wrong input
    if( new_partition > partition_count || new_partition <= 0 )
    {
      return 0;
    }
    partition_changed = (new_partition==boot_partition)?0:1;
    
    // rotate partitions till new_partition is found
    for(j=0;j<partition_count;++j)
    {
      if(new_partition == get_active_partition())
      {
        break;
      }
      for(i=0;i<16;i++)
      {
        c=mbr_buf[i+0x1BE];
        for(p=1; p<partition_count; ++p)
        {
          mbr_buf[i+(p-1)*16+0x1BE]=mbr_buf[i+p*16+0x1BE];
        }
        mbr_buf[i+(partition_count-1)*16+0x1BE]=c;
      }
    }
    _WriteSDCard(0,0,1,mbr_buf);
  }
  return 1;
}

unsigned char get_active_partition(void)
{
  unsigned int  partition_start[4];
  unsigned char partition_number = 1;
  int partition_count = get_part_count();
  int i;

  for( i=0; i<partition_count; ++i )
  {
    int a = mbr_buf[0x01C6+(i)*16];
    int b = mbr_buf[0x01C7+(i)*16];
    int c = mbr_buf[0x01C8+(i)*16];
    int d = mbr_buf[0x01C9+(i)*16];
    partition_start[i] = (((((d<<8) +c)<<8) +b)<<8) +a;
  }
  for( i=1; i<partition_count; ++i )
  {
    if(partition_start[i]<partition_start[0])
    {
      ++partition_number;
    }
  }
  return partition_number;
}

void create_partitions(void){
	if (is_mbr_loaded())
	{
	 unsigned long start, length;
	 char type;

	 _memset(mbr_buf,0,SECTOR_SIZE);

	 start=1; length=2*1024*1024/SECTOR_SIZE; //2 Mb
	 type=1; // FAT primary
	 mbr_buf[0x1BE + 4]=type;
	 mbr_buf[0x1BE + 8]=start;   mbr_buf[0x1BE + 9]=start>>8;   mbr_buf[0x1BE + 10]=start>>16;  mbr_buf[0x1BE + 11]=start>>24;
	 mbr_buf[0x1BE + 12]=length; mbr_buf[0x1BE + 13]=length>>8; mbr_buf[0x1BE + 14]=length>>16; mbr_buf[0x1BE + 15]=length>>24;

	 start=start+length; length=drive_sectors-start-1;
	 type=0x0B;  //FAT32 primary;
	 mbr_buf[0x1CE + 4]=type;
	 mbr_buf[0x1CE + 8]=start;   mbr_buf[0x1CE + 9]=start>>8;   mbr_buf[0x1CE + 10]=start>>16;  mbr_buf[0x1CE + 11]=start>>24;
	 mbr_buf[0x1CE + 12]=length; mbr_buf[0x1CE + 13]=length>>8; mbr_buf[0x1CE + 14]=length>>16; mbr_buf[0x1CE + 15]=length>>24;

	 mbr_buf[0x1FE]=0x55; mbr_buf[0x1FF]=0xAA; // signature;

	 _WriteSDCard(0,0,1,mbr_buf);
	}
}

#else

// Dummy for scripts if not implemented in camera
int swap_partitions(int new_partition) { return 0; }
int get_part_count(void) { return 1; }
int get_part_type() { return 0; }
unsigned char get_active_partition(void) { return 1; }
int is_partition_changed() { return 0; }

#endif

int mute_on_zoom(int x){
 static int old_busy=0;
 int busy=zoom_busy||focus_busy;
 if (old_busy!=busy) {
  if (busy) {
#if CAM_CAN_MUTE_MICROPHONE
   if (conf.mute_on_zoom) _TurnOffMic();
#endif
   }
   else {
#if CAM_CAN_MUTE_MICROPHONE
  if (conf.mute_on_zoom) _TurnOnMic();
#endif
#if CAM_EV_IN_VIDEO
  if (get_ev_video_avail()) set_ev_video_avail(0);
#endif
  }
  old_busy=busy;
 }
 return x; // preserve R0 if called from assembler
}


#if CAM_AF_SCAN_DURING_VIDEO_RECORD
void MakeAFScan(void){
 int a=0, save;
 if (zoom_busy || focus_busy) return;
 save=some_flag_for_af_scan;
 some_flag_for_af_scan=0;
#if CAM_AF_SCAN_DURING_VIDEO_RECORD == 2
 parameter_for_af_scan=3;
#endif
 _MakeAFScan(&a, 3);
 some_flag_for_af_scan=save;
#if CAM_RESET_AEL_AFTER_VIDEO_AF
 int ae_lock;
 get_property_case(PROPCASE_AE_LOCK,&ae_lock,sizeof(ae_lock));
 if (ae_lock == 0)						// AE not locked so ensure it is unlocked after re-focus
	 _ExpCtrlTool_StartContiAE(0,0);
 else									// AE locked before so re-lock after
	 _ExpCtrlTool_StopContiAE(0,0);
#else
 _ExpCtrlTool_StartContiAE(0,0);
#endif
}
#endif

long __attribute__((weak)) get_jogdial_direction(void)  { return 0; }
void __attribute__((weak)) JogDial_CW(void)     {}
void __attribute__((weak)) JogDial_CCW(void)    {}

#if defined (DNG_EXT_FROM)

#define DNG_EXT_TO ".DNG"

typedef int(*p_some_f)(char*, int);

extern p_some_f some_f_for_dng;  // camera variable!
extern char* second_ext_for_dng; // camera variable!

p_some_f default_some_f;
char *   default_second_ext;

int my_some_f(char *s, int x){
  char *f;
  f=strstr(s, DNG_EXT_FROM);
  if (f) _memcpy(f, DNG_EXT_TO, sizeof(DNG_EXT_TO)-1);
  return default_some_f(s, x);
}

void save_ext_for_dng(void){
 default_some_f=some_f_for_dng;
 default_second_ext=second_ext_for_dng;
}

void change_ext_to_dng(void){
 some_f_for_dng=my_some_f;
 second_ext_for_dng=DNG_EXT_TO;
}

void change_ext_to_default(void){
 some_f_for_dng=default_some_f;
 second_ext_for_dng=default_second_ext;
}

#endif


#if !CAM_DRYOS
static long drv_struct[16];
#endif

long dh_err()
{
    return -1;
}

#if !CAM_DRYOS
void drv_self_hide()
{
    long drvnum;

    drvnum = _iosDrvInstall(dh_err,dh_err,dh_err,dh_err,dh_err,dh_err,dh_err);
    if (drvnum >= 0)
	_iosDevAdd(drv_struct, "A/DISKBOOT.BIN", drvnum);
}

void drv_self_unhide()
{
 _iosDevDelete(drv_struct);
}
#endif

int  apex2us(int apex_tv){
#if CAM_EXT_TV_RANGE
/*
 Extended Tv, by barberofcivil, http://chdk.setepontos.com/index.php/topic,4392.0.html
 Explanation by reyalP:
 In every port, the original shutter overrides (as opposed to super long exposure) worked by
 setting the propcase values at some point after auto-exposure has happened (except in manual
 modes, where the manual control propcases may be used instead). The Canon code previously took
 these values unchanged for short exposures. In newer cameras, like on the SX10 / SD980, the value
 is changed, apparently some time after it has been retrieved from the propcase. We know this is
 the case, because the propcase value itself doesn't get clamped to the allowed range (if it did,
 barberofcivil's code wouldn't work).
*/
	short tv;
	tv = shooting_get_tv96();
	if (tv<-576 || tv!=apex_tv) return 1000000.0*pow(2.0, -tv/96.0);
	else return _apex2us(apex_tv);
#else
	return 0;
#endif
}

void PostLogicalEventForNotPowerType(unsigned id, unsigned x) {
	_PostLogicalEventForNotPowerType(id,x);
}

void PostLogicalEventToUI(unsigned id, unsigned x) {
	_PostLogicalEventToUI(id,x);
}

void SetLogicalEventActive(unsigned id, unsigned state) {
	_SetLogicalEventActive(id, state);
}

void SetScriptMode(unsigned mode) {
	_SetScriptMode(mode);
}

// TODO this belongs lib.c, but not all cameras include it
// same as bitmap width for most cameras, override in platform/sub/lib.c as needed
int __attribute__((weak)) vid_get_viewport_width() {
	return camera_screen.width;
}

// Physical width of viewport row in bytes
int __attribute__((weak)) vid_get_viewport_byte_width() {
	return 720 * 6 / 4;     // For most cameras viewport is 720 pixels wide, each group of 4 pixels uses 6 bytes (UYVYYY)
}

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int __attribute__((weak)) vid_get_viewport_yscale() {
	return 1;               // For most cameras viewport is 240 pixels high
}

// viewport x offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
int __attribute__((weak)) vid_get_viewport_xoffset() {
	return 0;
}

// viewport y offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
int __attribute__((weak)) vid_get_viewport_yoffset() {
	return 0;
}

// viewport display x offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
int __attribute__((weak)) vid_get_viewport_display_xoffset() {
	return vid_get_viewport_xoffset();
}

// viewport display y offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
int __attribute__((weak)) vid_get_viewport_display_yoffset() {
	return vid_get_viewport_yoffset();
}

// viewport image offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
// returns the byte offset into the viewport buffer where the image pixels start (to skip any black borders)
// see G12 port for sample implementation
int vid_get_viewport_image_offset() {
	return (vid_get_viewport_yoffset() * vid_get_viewport_byte_width() * vid_get_viewport_yscale()) + (vid_get_viewport_xoffset() * 3);
}

// viewport image offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
// returns the byte offset to skip at the end of a viewport buffer row to get to the next row.
// see G12 port for sample implementation
int vid_get_viewport_row_offset() {
	return (vid_get_viewport_byte_width() * vid_get_viewport_yscale()) - (vid_get_viewport_width() * 3);
}

// for cameras with two (or more?) RAW buffers this can be used to speed up DNG creation by
// calling reverse_bytes_order only once. Override in platform/sub/lib.c
char __attribute__((weak)) *hook_alt_raw_image_addr() {
	return hook_raw_image_addr();
}

void __attribute__((weak)) vid_turn_off_updates()
{
}

void __attribute__((weak)) vid_turn_on_updates()
{
}

// use _GetFocusLensSubjectDistance for this on dryos, vx functions are basically equivlent
// not used in CHDK currently for either OS
#ifdef CAM_DRYOS
long __attribute__((weak)) _GetCurrentTargetDistance()
{
	return _GetFocusLensSubjectDistance();
}
#endif

int add_ptp_handler(int opcode, ptp_handler handler, int unknown)
{
#ifdef CAM_CHDK_PTP
    return _add_ptp_handler(opcode,handler,unknown);
#else
    return 0;
#endif
}

int CreateTask (const char *name, int prio, int stack_size, void *entry)
{
    return _CreateTask(name, prio, stack_size, entry, 0);
}

void ExitTask()
{
    _ExitTask();
}

// TODO not in sigs for vx yet
#ifndef CAM_DRYOS
void __attribute__((weak)) _reboot_fw_update(const char *fw_update)
{
	return;
}
#endif

#ifdef CAM_DRYOS
int __attribute__((weak)) switch_mode_usb(int mode)
{
#ifdef CAM_CHDK_PTP
    if ( mode == 0 ) {
        _Rec2PB();
        _set_control_event(0x80000000|CAM_USB_EVENTID);
    } else if ( mode == 1 ) {
        _set_control_event(CAM_USB_EVENTID);
        _PB2Rec();
    } else return 0;
    return 1;
#else
  return 0;
#endif // CAM_CHDK_PTP
}

#else // vxworks
// this doesn't need any special functions so it's defined even without CHDK_CAM_PTP
int __attribute__((weak)) switch_mode_usb(int mode)
{
    if ( mode == 0 ) {
        // TODO should we revert scriptmode and/or levent? seems to work without
        levent_set_play();
    } else if ( mode == 1 ) {
#ifdef CAM_USB_EVENTID_VXWORKS
        _SetScriptMode(1); // needed to override event
        _SetLogicalEventActive(CAM_USB_EVENTID_VXWORKS,0); // set levent "ConnectUSBCable" inactive
#endif
        levent_set_record();
    } else return 0;
    return 1;
}
#endif // vxworks

/*
// this wrapper isn't currently needed
// 7 calls functions and sets some MMIOs, but doesn't disable caches and actually restart
// 3 skips one function call on some cameras, but does restart
void Restart(unsigned option) {
	_Restart(option);
}
*/

unsigned char SetFileAttributes(const char* fn, unsigned char attr)
{
#ifdef CAM_DRYOS_2_3_R39
    return _SetFileAttributes(fn, attr);
#else
    int fd;
    unsigned char ret = -1;
    
    fd = open(fn, 0, 0);
    if( fd ) {
        _SetFileAttributes(fd, attr);
        close(fd);
        ret = attr;
    }
    return ret;
#endif
}

// Default implementation of PTP live view functions.
// Override as needed for camera specific variations (see G12/SX30/IXUS310/SX130IS for working examples)

int __attribute__((weak)) vid_get_viewport_display_xoffset_proper() { return vid_get_viewport_display_xoffset()*2; }
int __attribute__((weak)) vid_get_viewport_display_yoffset_proper() { return vid_get_viewport_display_yoffset(); }
int __attribute__((weak)) vid_get_viewport_buffer_width_proper()    { return 720; }
int __attribute__((weak)) vid_get_viewport_width_proper()           { return vid_get_viewport_width()*2; }
int __attribute__((weak)) vid_get_viewport_height_proper()          { return 240; }
int __attribute__((weak)) vid_get_viewport_fullscreen_height()         { return 240; }
int __attribute__((weak)) vid_get_viewport_fullscreen_width()          { return vid_get_viewport_buffer_width_proper(); }

int __attribute__((weak)) vid_get_palette_type()                    { return 0; }       // 0 = no palette into, 1 = 16 x 4 byte AYUV values, 
                                                                                        // 2 = 16 x 4 byte AYUV (A = 0..3), 3 = 256 x 4 byte AYUV (A = 0..3)
int __attribute__((weak)) vid_get_palette_size()                    { return 0; }
int __attribute__((weak)) vid_get_aspect_ratio()                    { return 0; }       // 0 = 4:3, 1 = 16:9 LCD Aspect Ratio

void __attribute__((weak)) *vid_get_bitmap_active_buffer()
{
  return vid_get_bitmap_fb();   // *** does not get the active buffer! (override if active buffer can be determined)
}

void __attribute__((weak)) *vid_get_bitmap_active_palette()
{
  return 0; // return no palette info unless overridden
}

// Get active viewport buffer address based on PLAY/REC mode.
// Try to use 'live' buffer in REC mode if vid_get_viewport_live_fb is implemented
// can return NULL in plaback mode, if a video is selected
void *vid_get_viewport_active_buffer()
{
  void *p;

  if (camera_info.state.mode_play)
  {
    p = vid_get_viewport_fb_d();
  } else {
    p = vid_get_viewport_live_fb();
    if ( !p )
    {
      p = vid_get_viewport_fb();
    }
  }
  
  return p;
}

/*
 debug logging function that can be sent to various places
 body is ifdef'd inside the body to allow exporting to modules
 eventproc version may require System.Create()/SystemEventInit first
*/
void dbg_printf(char *fmt,...) {
#ifdef DEBUG_LOGGING
    char s[256];
    __builtin_va_list va;
    __builtin_va_start(va, fmt);
    _vsprintf(s, fmt, va);
    __builtin_va_end(va);

    // stdout - for use with uart redirection
    _ExecuteEventProcedure("Printf",s);
    // camera log - will show up in crash dumps, or in stdout on ShowCameraLog
    // _LogPrintf(0x120,s);

    // file TODO
#endif
}

#ifdef CAM_MISSING_RAND
/* Some cameras does not have srand()/rand() functions in firmware, and should be aded here.
E.G. a810/a2300
*/
static unsigned int random_variable;
void *_srand(unsigned int seed) {
    random_variable = seed;
    return (void *) &random_variable;
}

int _rand(void) {
    int value;
    value = random_variable*0x41C64E6D+0x3039;
    random_variable = value;
    value = (0x7FFF & (value>>0x10));
    return value;
};
#endif

/*
return the usb state as seen by the firmware (after any masking for remote)
TODO this should just check the modified physw bit, but would requires
kbd.c code for each camera
*/
extern int get_usb_bit();
int get_usb_bit_physw(void)
{
    return (conf.remote_enable == 0 && get_usb_bit());
}

