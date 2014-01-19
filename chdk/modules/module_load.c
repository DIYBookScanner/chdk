/*
*   CHDK-FLAT Module System.  
*
*   (c)2011 Sergey Taranenko aka tsvstar
*
*   This is main file of module processing system. Module load/unload/service functions
*/

#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "console.h"

#include "keyboard.h"
#include "cache.h"
#include "clock.h"
#include "raw_buffer.h"
#include "shooting.h"
#include "autoiso.h"
#include "viewport.h"
#include "battery.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_osd.h"
#include "gui_usb.h"
#include "gui_batt.h"
#include "gui_mbox.h"
#include "gui_space.h"
#include "gui_menu.h"
#include "gui_user_menu.h"
#include "gui_lang.h"
#include "levent.h"
#include "sd_card.h"
#include "sound.h"
#include "temperature.h"
#include "meminfo.h"
#include "font.h"
#include "lang.h"
#include "properties.h"
#include "ptp_chdk.h"
#include "histogram.h"
#include "shot_histogram.h"
#include "action_stack.h"
#include "debug_led.h"
#include "raw.h"
#include "shutdown.h"
#include "modes.h"
#include "backlight.h"
#include "math.h"
#include "file_counter.h"
#include "lens.h"
#include "fileutil.h"
#include "task.h"
#include "callfunc.h"

#include "modules.h"
#include "module_load.h"
#include "module_exportlist.h"

extern unsigned _ExecuteEventProcedure(const char *name,...);

//********************************************************/

// GCC library functions for linking modules without including
// a copy of the GCC library in each module
// Don't need correct function signatures - only here to prevent compiler warnings
extern void __modsi3(void);
extern void __umodsi3(void);
extern void __divsi3(void);
extern void __udivsi3(void);
extern void __divsf3(void);
extern void __mulsf3(void);
extern void __divdf3(void);
extern void __muldf3(void);
extern void __floatunsisf(void);
extern void __fixunssfsi(void);
extern void __extendsfdf2(void);
extern void __truncdfsf2(void);
extern void __floatsidf(void);
extern void __floatsisf(void);
extern void __fixdfsi(void);
extern void __adddf3(void);
extern void __subdf3(void);
extern void __ltdf2(void);
extern void __gtdf2(void);
extern void __bswapsi2(void);

//********************************************************/

// Struct for symbol hash table entries
typedef struct
{
    uint32_t    hash;
    const void  *address;
} sym_hash;

// Symbol hash table for resolving exported symbol references
sym_hash symbol_hash_table[] =
{
    { EXPORTLIST_MAGIC_NUMBER, (void*)EXPORTLIST_LAST_IDX },
#include "module_hashlist.h"
};

//********************************************************/

typedef int (*_module_action_t)( struct flat_hdr* flat, void* relocbuf, uint32_t count );

//********************************************************/

#define BUFFER_FOR_READ_SIZE    4096
#define MODULES_PATH            "A/CHDK/MODULES"

//********************************************************/
//**    Small library for safe io to cacheable memory   **
//**  use smaller buffer then fopen so bigger could     **
//**  be loaded										    **
//********************************************************/

static char* buf_load=0;    // Also used for relocation & imports

int b_read(int fd, char* buf, int len)
{
    if (buf_load==0)
    {
        buf_load = umalloc( BUFFER_FOR_READ_SIZE );
        if (buf_load==0)
            return 0;
    }

    int loaded=0, now=1;

    while (now && loaded<len)
    {
        now = len-loaded;
        if ( now > BUFFER_FOR_READ_SIZE )
            now = BUFFER_FOR_READ_SIZE;

        now = read(fd,buf_load,now);

        memcpy(buf+loaded, buf_load, now);
        loaded+=now;
    }

    return loaded;
}

void b_close(int fd)
{
    if (fd >= 0)
        close(fd);

    if (buf_load)
        ufree(buf_load);
    buf_load=0;
}


//********************************************************/
//**       Auxilary module system functions             **
//********************************************************/

// array of loaded modules (hdr == NULL -> slot is empty)
static module_entry modules[MAX_NUM_LOADED_MODULES];

//-----------------------------------------------
// Cut module name to 11 sym
//-----------------------------------------------
static void flat_module_name_make( char* tgt, const char* name )
{
    char *p = strrchr(name,'/');
    strncpy(tgt, (p) ? p+1 : name, 12);
    tgt[11] = 0;
}

//-----------------------------------------------
// Do path to module
//-----------------------------------------------
static void flat_module_path_make( char* tgt, const char* name )
{
    // check is name absolute path
    if ( name[0]=='A' && name[1]=='/')
        strcpy(tgt,name);
    else
        sprintf(tgt,"%s/%s",MODULES_PATH,name);
}

//-----------------------------------------------
// PURPOSE: Find idx_loaded by module name or by module idx
// RETURN: -1 if module not loaded yet, otherwise idx in modules[]
//-----------------------------------------------
static int module_find(const char * name )
{
    char namebuf[12];
    int i = (uint32_t)name;

    // Check if given parameter is idx
    if (i < MAX_NUM_LOADED_MODULES)
        return (modules[i].hdr ? i : -1);

    flat_module_name_make(namebuf,name);

    for ( i=0; i<MAX_NUM_LOADED_MODULES; i++ ) 
    {
        if ( modules[i].hdr && !strcmp(namebuf, modules[i].modulename) )
        {
            return i;
        }
    }
    return -1;
}

//-----------------------------------------------
// Structures of relocation and importing
//---------------------------------------

// Rules how relocations works:
//  Relocation:
//  	*(flat_base+reloc[i]) += flat_base;
//  Import:
//    symidx = import[i].importidx
//	  *(flat_base+import[i].offs) += module_find_symbol_address(symidx)

static int module_do_relocations( struct flat_hdr* flat, void* relocbuf, uint32_t reloc_count )
{
    int i;
    unsigned char* buf = (unsigned char*)flat;
    uint32_t* rbuf = (uint32_t*)relocbuf;

    for ( i=0; i < reloc_count; i++ )
    {
        unsigned int offs = rbuf[i];
        //@tsv todo: if (offs>=flat->reloc_start) error_out_of_bound
        *(uint32_t*)(buf+offs) += (uint32_t)buf;
    }

    return 1;
}

// Find symbol address in array from hash id
static const void* module_find_symbol_address(uint32_t importid)
{
    // binary search (first entry is magic number & entry count)
    int min = 1, max = EXPORTLIST_LAST_IDX;
    do
    {
        int mid = (min + max) >> 1;
        if (importid == symbol_hash_table[mid].hash)
            return symbol_hash_table[mid].address;
        else if (importid > symbol_hash_table[mid].hash)
            min = mid + 1;
        else
            max = mid - 1;
    } while (min <= max);
    return 0;
}

static int module_do_imports( struct flat_hdr* flat, void* relocbuf, uint32_t import_count )
{
    int i;
    unsigned char* buf = (unsigned char*)flat;
    uint32_t* rbuf = (uint32_t*)relocbuf;

    for ( i=0; i < import_count; )
    {
        const void* importaddress = module_find_symbol_address(rbuf[i++]);
        if (importaddress == 0) return 0;

        int cnt = rbuf[i] >> 24;
        for (; cnt>0; cnt--)
        {
            uint32_t offs = rbuf[i++] & 0x00FFFFFF;
            uint32_t* ptr = (uint32_t*)( buf + offs );
            *ptr += (int)importaddress;
        }
    }  
    return 1;
}

// variables to quick error
static const char* module_filename;
static int module_fd;
static struct flat_hdr* flat_buf;

//-----------------------------------------------
static void moduleload_error(char* text, int value)
{
    if ( module_fd >=0 )
        b_close( module_fd);

    if ( flat_buf )
        free(flat_buf);

    //extern int console_is_inited();
    extern volatile int chdk_started_flag;
    if ( chdk_started_flag ) {
        char fmt[50];
        strcpy(fmt,"Fail to load %s: ");
        strcpy(fmt+17,text);

        char buf[100];
        sprintf(buf, fmt, module_filename, value);

        console_clear();
        console_add_line(buf);
        msleep(1000);
    }
}

//-----------------------------------------------
// return: 0 if error, otherwise ok
static int module_do_action( char* actionname, uint32_t offset, uint32_t count, uint32_t segment_size, _module_action_t func )
{
    if ( count > 0 ) 
    {
        if ( offset != lseek(module_fd, offset, SEEK_SET) )
        {
            moduleload_error("action %s",(int)actionname);
            return 0;
        }
        if ( segment_size != read(module_fd, buf_load, segment_size) )
        {
            moduleload_error("action %s", (int)actionname);
            return 0;
        }

        // make relocations
        if ( !func( flat_buf, (uint32_t*)buf_load, count ) )  
        {
            moduleload_error("bad import symbol",0);
            return 0;
        }
    }

    return 1;
}

static int alloc_reloc_buf(uint32_t reloc_size, uint32_t import_size)
{
    // Get larger size
    int sz = (reloc_size > import_size) ? reloc_size : import_size;

    if (sz > BUFFER_FOR_READ_SIZE)  // If larger than already allocated
    {
        if (buf_load) ufree(buf_load);
        buf_load = umalloc(sz);
        if ( buf_load == 0 )
        {
            moduleload_error("malloc",0);   
            return 0;
        }
    }

    return 1;
}

//********************************************************/
//**           Main module system functions             **
//********************************************************/

//-----------------------------------------------
// Logging

static void module_writeline(char *buf)
{
    if (conf.module_logging)
    {
        FILE *fp = fopen("A/MODULES.LOG","a");
        fwrite(buf,strlen(buf),1,fp);
        fclose(fp);
    }
}

static void module_log_hdr()
{
    static int hdr_logged = 0;

    if (conf.module_logging)
    {
        if (hdr_logged == 0)
        {
            hdr_logged = 1;

            time_t datetime;
            struct tm *ttm;
            char buf[100];

            datetime = time(NULL);
            ttm = localtime(&datetime);

            sprintf(buf, "Tick    ,Op,Address ,Name (%04d:%02d:%02d %02d:%02d:%02d)\n", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);

            module_writeline(buf);
        }
    }
}

void module_log_clear()
{
    remove("A/MODULES.LOG");
}

static void module_log_load(const char *name, void* adr)
{
    if (conf.module_logging)
    {
        char buf[100];
        sprintf(buf,"%8d,LD,%08x,%s\n",get_tick_count(),adr,name);

        module_log_hdr();
        module_writeline(buf);
    }
}

static void module_log_unload(char *name)
{
    if (conf.module_logging)
    {
        char buf[100];
        sprintf(buf,"%8d,UN,        ,%s\n",get_tick_count(),name);

        module_log_hdr();
        module_writeline(buf);
    }
}

//-----------------------------------------------
// PARAMETER:  name - filename of module
//             callback - function which bind/unbind chdk 
//         local pointers with module symbols.
//         Optional ( NULL - do not bind )
// RETURN:    -1 - failed, >=0 =idx of module
//-----------------------------------------------

// Bind loaded module to library pointer
static int bind_module( module_handler_t* hMod, void* module_lib )
{
    *hMod->lib = module_lib;

    // If unloading module, reset library to unloaded default
    if (*hMod->lib == 0)
        *hMod->lib = hMod->default_lib;

    return 0;
}

struct flat_hdr* module_preload(const char *name, _version_t ver)
{
    module_fd = -1;
    module_filename = name;
    flat_buf = 0;
    buf_load = 0;

    char path[60];
    struct flat_hdr flat;
    int size_flat;

    flat_module_path_make(path,module_filename);

    module_fd = open( path, O_RDONLY, 0777 );
    if ( module_fd <=0 )
    {
        moduleload_error("file not found",0);
        return 0;
    }

    // @tsv TODO - compare loaded with requested
    b_read( module_fd, (char*)&flat, sizeof(flat) );

    if ( flat.rev!=FLAT_VERSION || memcmp( flat.magic, FLAT_MAGIC_NUMBER, 4) )
    {
        moduleload_error("bad magicnum", 0);
        return 0;
    }

    size_flat = flat.reloc_start;

    flat_buf = (struct flat_hdr*)malloc( size_flat );
    if ( !flat_buf ) 
    {
        moduleload_error("malloc",0);
        return 0;
    }

    module_log_load(module_filename,flat_buf);

    if ( 0!= lseek(module_fd, 0, SEEK_SET) )
    {
        moduleload_error("read",0);
        return 0;
    }
    if ( size_flat != b_read(module_fd, (char*)flat_buf, size_flat) )
    {
        moduleload_error("read",0);
        return 0;
    }

    // Module info checks

    struct ModuleInfo *mod_info = flat_buf->_module_info = (struct ModuleInfo*)((unsigned int)flat_buf+flat_buf->_module_info_offset);

    if ( mod_info->magicnum != MODULEINFO_V1_MAGICNUM || mod_info->sizeof_struct != sizeof(struct ModuleInfo) )
    {
        moduleload_error("Malformed module info", 0 );
        return 0;
    }

    if ( mod_info->chdk_required_branch && mod_info->chdk_required_branch != CURRENT_CHDK_BRANCH )
    {
        moduleload_error("require different CHDK branch",0 );
        return 0;
    }

    if ( mod_info->chdk_required_ver > CHDK_BUILD_NUM) 
    {
        moduleload_error("require CHDK%05d", mod_info->chdk_required_ver);
        return 0;
    }

    if ( mod_info->chdk_required_platfid && mod_info->chdk_required_platfid != conf.platformid )
    {
        moduleload_error("require platfid %d", mod_info->chdk_required_platfid);
        return 0;
    }

	if ( !API_VERSION_MATCH_REQUIREMENT( mod_info->module_version, ver ) )
    {
        moduleload_error("incorrect module version", 0);
		return 0;
    }

	if ( !API_VERSION_MATCH_REQUIREMENT( conf.api_version, mod_info->conf_ver ) )
    {
        moduleload_error("incorrect CONF version", 0);
		return 0;
    }

	if ( !API_VERSION_MATCH_REQUIREMENT( camera_screen.api_version, mod_info->cam_screen_ver ) )
    {
        moduleload_error("incorrect CAM SCREEN version", 0);
		return 0;
    }

	if ( !API_VERSION_MATCH_REQUIREMENT( camera_sensor.api_version, mod_info->cam_sensor_ver ) )
    {
        moduleload_error("incorrect CAM SENSOR version", 0);
		return 0;
    }

	if ( !API_VERSION_MATCH_REQUIREMENT( camera_info.api_version, mod_info->cam_info_ver ) )
    {
        moduleload_error("incorrect CAM INFO version", 0);
		return 0;
    }

    // Make relocations

    int reloc_size = flat.import_start - flat.reloc_start;
    int reloc_count = reloc_size/sizeof(uint32_t);
    int import_size = flat.file_size - flat.import_start;
    int import_count = import_size/sizeof(uint32_t);

    if (!alloc_reloc_buf(reloc_size, import_size))
        return 0;
    if ( !module_do_action( "reloc", flat.reloc_start, reloc_count, reloc_size, module_do_relocations ) )
        return 0;
    if ( !module_do_action( "export", flat.import_start, import_count, import_size, module_do_imports ) )
        return 0;

    b_close( module_fd );
    module_fd = -1;

    // TODO these could be changed to operate on affected address ranges only
    // after relocating but before attempting to execute loaded code
    // clean data cache to ensure code is in main memory
    dcache_clean_all();
    // then flush instruction cache to ensure no addresses containing new code are cached
    icache_flush_all();

    return flat_buf;
}

static int _module_load(module_handler_t* hMod)
{
    int idx;

    // Check if module loaded
    idx = module_find(hMod->name);
    if ( idx>=0 )
        return idx;

    // Find empty slot   
    for ( idx=0; idx<MAX_NUM_LOADED_MODULES && modules[idx].hdr; idx++ );

    if  ( idx == MAX_NUM_LOADED_MODULES )
    {
        moduleload_error("%d already loaded",MAX_NUM_LOADED_MODULES);
        return -1;
    }

    if (module_preload(hMod->name, hMod->version) != 0)
    {
        // Module is valid. Finalize binding
        modules[idx].hdr = flat_buf;

        // store runtime params
        flat_module_name_make(modules[idx].modulename, module_filename);
        modules[idx].hMod = hMod;

        int bind_err = bind_module( hMod, flat_buf->_module_info->lib );

        if ( flat_buf->_module_info->lib->loader )
        {
            uint32_t x = flat_buf->_module_info->lib->loader();
            bind_err = bind_err || x;
        }

        if ( bind_err )
        {
            module_unload(module_filename);
            moduleload_error("chdk mismatch",0);
            return -1;
        }

        return idx;
    }

    return -1;
}

// Return: 0-fail, 1-ok
int module_load(module_handler_t* hMod)
{
    // Attempt to load module
    *hMod->lib = 0;
    _module_load(hMod);

    // If load succeeded return success
    if (*hMod->lib && (*hMod->lib != hMod->default_lib))
    {
        return 1;
    }

    // If load failed reset library to unloaded default
    if (*hMod->lib == 0)
        *hMod->lib = hMod->default_lib;

    // Failure
    return 0;
}

//-----------------------------------------------
// PURPOSE: 	run simple module "name"
// RETURN VALUE: passed from module. -1 if something was failed
//-----------------------------------------------
#define MAX_SIMPLE_MODULE   4

static int default_run0();
static int default_run1();
static int default_run2();
static int default_run3();

static libsimple_sym default_librun[MAX_SIMPLE_MODULE] =
{
    { { 0, 0, 0, 0, default_run0 } },
    { { 0, 0, 0, 0, default_run1 } },
    { { 0, 0, 0, 0, default_run2 } },
    { { 0, 0, 0, 0, default_run3 } }
};
static libsimple_sym* librun[MAX_SIMPLE_MODULE] = { &default_librun[0], &default_librun[1], &default_librun[2], &default_librun[3] };

static char h_name[4][32];

static module_handler_t h_run[MAX_SIMPLE_MODULE] =
{
    { (base_interface_t**)&librun[0], &default_librun[0].base, ANY_VERSION, h_name[0] },
    { (base_interface_t**)&librun[1], &default_librun[1].base, ANY_VERSION, h_name[1] },
    { (base_interface_t**)&librun[2], &default_librun[2].base, ANY_VERSION, h_name[2] },
    { (base_interface_t**)&librun[3], &default_librun[3].base, ANY_VERSION, h_name[3] }
};

static void module_run_error(int err, char *name)
{
    char buf[100];
    sprintf(buf, lang_str(err), name);
    gui_mbox_init(LANG_ERROR, (int)buf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}

static int default_run(int n)
{
    if (module_load(&h_run[n]))
    {
        if ((*h_run[n].lib)->run)
        {
            return (*h_run[n].lib)->run();
        }
        else
        {
            // Error - module does not support 'simple' mode
            module_run_error(LANG_MODULE_NOT_SIMPLE, h_run[n].name);
        }
    }

    return -1;
}

static int default_run0() { return default_run(0); }
static int default_run1() { return default_run(1); }
static int default_run2() { return default_run(2); }
static int default_run3() { return default_run(3); }

static int name_match(char *s, char *d)
{
    if ((s == 0) || (d == 0)) return 0;
    if (strlen(s) != strlen(d)) return 0;
    int i;
    for (i=0; i<strlen(s); i++)
        if (tolower(s[i]) != tolower(d[i])) return 0;
    return 1;
}

int module_run(char* name)
{
    // Get just name part - not full path
    char *s = strrchr(name,'/');
    if (s) name = s + 1;

    int i;
    for (i=0; i<MAX_SIMPLE_MODULE; i++)
    {
        // Check if module loaded (otherwise name not valid)
        if (*h_run[i].lib != h_run[i].default_lib)
        {
            if (name_match(name,h_run[i].name))
            {
                // Already loaded
                return (*h_run[i].lib)->run();
            }
        }
    }
    for (i=0; i<MAX_SIMPLE_MODULE; i++)
    {
        // Look for empty slot
        if (*h_run[i].lib == h_run[i].default_lib)
        {
            // Found space - run module
            strcpy(h_run[i].name,name);
            return (*h_run[i].lib)->run();
        }
    }

    // Error - no space
    module_run_error(LANG_MODULE_NO_SPACE, name);

    return -1;
}


//-----------------------------------------------
static void module_unload_idx(int idx)
{
    if ( idx>=0 )
    {
        module_log_unload(modules[idx].modulename);

        // Make finalization module
        if ( modules[idx].hdr->_module_info->lib->unloader )
            modules[idx].hdr->_module_info->lib->unloader();

        // Unbind pointers to module (chdk core callback)
        bind_module(modules[idx].hMod,0);

        // Free slot
        free ( modules[idx].hdr );
        modules[idx].hdr = 0;
    }
}

void module_unload(const char* name)
{
    module_unload_idx(module_find(name));
}

//-----------------------------------------------
// Warn modules when leaving <ALT>
//   1. Called when goto GUI_MODE_NONE
//   2. Tell all modules that we are leaving <ALT> mode
//-----------------------------------------------
void module_exit_alt()
{
    int idx;

    for( idx=MAX_NUM_LOADED_MODULES-1; idx>=0; idx--)
    {
        if ( modules[idx].hdr )
        {
            // Tell module we are leaving <ALT>
            if (modules[idx].hdr->_module_info->lib->exit_alt)
                modules[idx].hdr->_module_info->lib->exit_alt();
        }
    }     	  
}


//-----------------------------------------------
// Called on each tick to safe asynchronous unload module by its requests 
//-----------------------------------------------
void module_tick_unloader()
{
    int idx;

    for( idx=MAX_NUM_LOADED_MODULES-1; idx>=0; idx--)
    {
        if (modules[idx].hdr && modules[idx].hdr->_module_info->lib->can_unload)
        {
            // Ask module if it is safe to unload
            if (modules[idx].hdr->_module_info->lib->can_unload())
                module_unload_idx(idx);
        }
    }
}

module_entry* module_get_adr(unsigned int idx)
{
    if (idx < MAX_NUM_LOADED_MODULES)
        if (modules[idx].hdr)
            return &modules[idx];
    return 0;
}
