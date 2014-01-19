#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "script.h"
#include "meminfo.h"
#include "cache.h"
#include "module_load.h"
#include "clock.h"
#include "cachebit.h"

// to keep format simple, we always write meminfo for each
// but can skip actual getmeminfo since call might crash on mem corruption
#define DBG_DUMP_FL_NOMEMINFO   0x1
#define DBG_DUMP_FL_NOEXMEMINFO 0x2

#define DBG_DUMP_VERSION        2 
// version 2 - added module info, tick, uncached bit, max_ram_addr, build_string
/*
dump debug info to a file
format
 header
 meminfo (camera heap, may be mostly -1 if meminfo not supported,0s if desabled)
 meminfo (exmem, 0s if exmem disabled)
 module info, length given by module_count * module_info_size
 stack dump (length in words given stack_count)
 user data (variable length given in user_data_len)
*/
typedef struct {
    int ver;
    int time;
    int tick;
    int platform_id;
    int romstart;    // could look up the following 3 manually but makes auto parsing easier
    int uncached_bit;
    int max_ram_addr;
    int text_start; // == _start
    int data_start; // == text_end
    int bss_start;  // == data_end
    int bss_end;    // == _end
    int module_count; // number of loaded modules
    int module_info_size; // dump version should change if this changes, but will keep the rest of dump readable if it doesn't 
    int sp;
    int stack_count; // number of words of stack dumped (not related to number of words in stack!)
    int user_val; // user_data address if not null, otherwise treat user_data_size as an arbitrary int and put it here
    int user_data_len;
    int flags;
    char build_string[100]; // "platform,sub,date,time,version,rev", oversized for simplicity
} dumpheader;

typedef struct {
    int index;
    module_entry m;
    struct flat_hdr h;
} mod_info;

// this does not describe the structure, just a convenient way to access uncached + use less memory
typedef union {
    dumpheader h;
    cam_meminfo m;
    mod_info mi;
} dumpinfo;

// number of words to dump -- could get initial SP from task
#define STACK_DUMP_COUNT 512


void dbg_dump_write(const char *dumpname,unsigned flags, int user_data_len, char *user_data) {
    static dumpinfo buf;
    // convenient access to uncached version
    dumpinfo *pb = ADR_TO_UNCACHED(&buf);
    
    // use open + uncached mem because we may not have enough memory for fopen
    int fd=open(dumpname, O_WRONLY|O_CREAT|O_TRUNC, 0777);
    if(fd >= 0) {
        int *sp;
        asm volatile( "MOV %0,SP\n" :"=r"(sp));
        pb->h.ver = DBG_DUMP_VERSION;
        pb->h.time = time(NULL);
        pb->h.tick = get_tick_count();
        pb->h.platform_id = conf.platformid;
        pb->h.romstart = camera_info.rombaseaddr;
        pb->h.uncached_bit = camera_info.cam_uncached_bit;
        pb->h.max_ram_addr = camera_info.maxramaddr;
        pb->h.text_start = camera_info.text_start;
        pb->h.data_start = camera_info.data_start;
        pb->h.bss_start = camera_info.bss_start;
        pb->h.bss_end = camera_info.bss_end;
        pb->h.sp = (int)sp;
        pb->h.stack_count = STACK_DUMP_COUNT;
        if(user_data) {
            pb->h.user_data_len = user_data_len;
            pb->h.user_val = (int)user_data;
        } else {
            pb->h.user_data_len = 0;
            pb->h.user_val = user_data_len;
        }

        pb->h.flags = flags;

        int m_count=0;
        // count so we can store it in the header
        int i;
        for(i=0;i<MAX_NUM_LOADED_MODULES;i++) {
            const module_entry *m = module_get_adr(i);
            if(m) {
                m_count++;
            }
        }
        pb->h.module_count = m_count;
        pb->h.module_info_size = sizeof(mod_info);
        sprintf(pb->h.build_string,"%s,%s,%s,%s,%s,%s", 
                camera_info.platform,
                camera_info.platformsub,
                camera_info.build_date,
                camera_info.build_time,
                camera_info.build_number,
                camera_info.build_svnrev);

        write(fd,&pb->h,sizeof(dumpheader));

        if(!(flags & DBG_DUMP_FL_NOMEMINFO)) {
            GetMemInfo(&pb->m);
        } else {
            memset(&pb->m,0,sizeof(cam_meminfo));
        }
        write(fd,&pb->m,sizeof(cam_meminfo));

        // if no exmem don't check
        memset(&pb->m,0,sizeof(cam_meminfo));
        if(!(flags & DBG_DUMP_FL_NOEXMEMINFO)) {
            GetExMemInfo(&pb->m);
        }
        write(fd,&pb->m,sizeof(cam_meminfo));

        // assume modules haven't gone away since count, might not be valid?
        for(i=0;i<MAX_NUM_LOADED_MODULES;i++) {
            const module_entry *m = module_get_adr(i);
            if(!m) {
                continue;
            }
            pb->mi.index = i;
            memcpy(&pb->mi.m,m,sizeof(module_entry));
            memcpy(&pb->mi.h,m->hdr,sizeof(struct flat_hdr));
            write(fd,&pb->mi,sizeof(mod_info));
        }

        // clean cache for write()
        dcache_clean_all();

        write(fd,ADR_TO_UNCACHED(sp),STACK_DUMP_COUNT*4);
        if(user_data_len && user_data) {
            // we assume user_data has been flushed out by preceding
            write(fd,ADR_TO_UNCACHED(user_data),user_data_len);
        }
        close(fd);
    } else {
        script_console_add_line( (long)"failed to open dump file" );
    }
}

void dbg_dump_assert(const char *dumpfile,const char *expr,const char *file,int line) {
    static char buf[128]; // could overflow if expr is long
    sprintf(buf,"ASSERT %s:%d %s",file,line,expr);
    script_console_add_line( (long)buf );
    dbg_dump_write(dumpfile,0,sizeof(buf),buf);
}
