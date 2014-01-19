#include "stdlib.h"
#include "gui_mbox.h"
#include "gui.h"

static const char *cache_words_line_str(unsigned val) {
    switch(val) {
        case 2: return "8";
        default:
            return "Unknown";
    }
}

static const char *reg_sizes[] = {
    "4K", "8K", "16K", "32K", "64K", "128K", "256K", "512K", 
    "1M", "2M", "4M", "8M", "16M", "32M", "64M", "128M", "256M", "512M",
    "1G", "2G", "4G",
};

static const char *cache_tcm_size_str(unsigned val) {
    if (val == 0) 
        return "0";
    if (val < 3 || val > 11)
        return "invalid";
    return reg_sizes[val-3];
}


static const char *protreg_size_str(unsigned val) {
    if (val < 11 || val > 31)
        return "invalid";
    return reg_sizes[val - 11];
}

// "base" addresses actually overlap the rest of the register,
// because the lower 13 are implicitly zero due to alignment constraints
// here we return the actual address as a hex string
static const char *protreg_base_str(unsigned val) {
	static char str[11];
	sprintf(str,"0x%08X",val << 13);
	return str;
}


static const char *tcmcfg_size_str(unsigned val) {
    if ( val < 3 || val > 23 ) 
        return "invalid";
    return reg_sizes[val - 3];
}

static const char *regperm_str(unsigned val) {
    switch(val) {
        case 0: return "P:-- U:--";
        case 1: return "P:RW U:--";
        case 2: return "P:RW U:R-";
        case 3: return "P:RW U:RW";
        case 5: return "P:R- U:--";
        case 6: return "P:R- U:R-";
        default:
            return "P:?? U:??";
    }
}

struct cpuinfo_bitfield_desc_s {
    unsigned bits;
    const char *name;
    const char *(*desc_fn)(unsigned val);
};

struct cpuinfo_word_desc_s {
    const char *name;
    const struct cpuinfo_bitfield_desc_s *fields;
};

const struct cpuinfo_bitfield_desc_s cpuinf_id[] = {
    {4,"Revision"},
    {12,"Part"},
    {4,"ARM Arch"},
    {4,"Variant"},
    {8,"Implementor"},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_cachetype[] = {
    {2,"Icache words/line",cache_words_line_str},
    {1,"Icache absent"},
    {3,"Icache assoc"},
    {4,"Icache size",cache_tcm_size_str},
    {2,"Reserved0_2"},
    {2,"Dcache words/line",cache_words_line_str},
    {1,"Dcache absent"},
    {3,"Dcache assoc"},
    {4,"Dcache size",cache_tcm_size_str},
    {2,"Reserved1_2"},
    {1,"Harvard/unified"},
    {4,"Cache type"},
    {3,"Reserved2_3"},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_tcmtype[] = {
    {2,"Reserved0_2"},
    {1,"ITCM absent"},
    {3,"Reserved1_3"},
    {4,"ITCM size",cache_tcm_size_str},
    {4,"Reserved2_4"},
    {1,"DTCM absent"},
    {3,"Reserved3_2"},
    {4,"DTCM size",cache_tcm_size_str},
    {10,"Reserved4_10"},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_control[] = {
    {1,"Protect enable"},
    {1,"Reserved0_1"},
    {1,"Dcache enable"},
    {4,"Reserved1_4"},
    {1,"Big endian"},
    {4,"Reserved2_4"},
    {1,"Icache enable"},
    {1,"Alt vector"},
    {1,"Cache RRR"},
    {1,"Disble load TBIT"},
    {1,"DTCM enable"},
    {1,"DTCM mode"},
    {1,"ITCM enable"},
    {1,"ITCM mode"},
    {12,"Reserved3_12"},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_regbits[] = {
    {1,"Region 0"},
    {1,"Region 1"},
    {1,"Region 2"},
    {1,"Region 3"},
    {1,"Region 4"},
    {1,"Region 5"},
    {1,"Region 6"},
    {1,"Region 7"},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_protreg[] = {
    {1,"Enable"},
    {5,"Size",protreg_size_str},
    {7,"Undef0_7"},
    {19,"Base",protreg_base_str},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_regperms[] = {
    {4,"Region 0",regperm_str},
    {4,"Region 1",regperm_str},
    {4,"Region 2",regperm_str},
    {4,"Region 3",regperm_str},
    {4,"Region 4",regperm_str},
    {4,"Region 5",regperm_str},
    {4,"Region 6",regperm_str},
    {4,"Region 7",regperm_str},
    {}
};

const struct cpuinfo_bitfield_desc_s cpuinf_tcmcfg[] = {
    {1,"Reserved0_1"},
    {5,"Size",tcmcfg_size_str},
    {7,"Undef0_7"},
    {19,"Base",protreg_base_str},
    {}
};


const struct cpuinfo_word_desc_s cpuinfo_desc[]={
    {"ID", cpuinf_id },
    {"Cache type", cpuinf_cachetype },
    {"TCM type", cpuinf_tcmtype },
    {"Control", cpuinf_control },
    {"Protection Region 0",cpuinf_protreg },
    {"Protection Region 1",cpuinf_protreg },
    {"Protection Region 2",cpuinf_protreg },
    {"Protection Region 3",cpuinf_protreg },
    {"Protection Region 4",cpuinf_protreg },
    {"Protection Region 5",cpuinf_protreg },
    {"Protection Region 6",cpuinf_protreg },
    {"Protection Region 7",cpuinf_protreg },
    {"Region data perms",cpuinf_regperms },
    {"Region inst perms",cpuinf_regperms },
    {"DCache cfg", cpuinf_regbits },
    {"ICache cfg", cpuinf_regbits },
    {"Write buffer", cpuinf_regbits },
    {"DTCM cfg",cpuinf_tcmcfg },
    {"ITCM cfg",cpuinf_tcmcfg },
    {}
};

// note, this is how many we know, nothing to do with how many debug_read_cpuinfo knows
#define NUM_CPUINFO_WORDS ((sizeof(cpuinfo_desc)/sizeof(cpuinfo_desc[0])) - 1)

void cpuinfo_finish(unsigned dummy);
void cpuinfo_get_info(unsigned *results);

void cpuinfo_write_file(void) {
    unsigned cpuinfo[NUM_CPUINFO_WORDS];
    int i,j;
    unsigned fieldval,wordval;
    unsigned mask,bits;
    FILE *finfo;
    char buf[100];
    char *p;
    cpuinfo_get_info(cpuinfo);
    finfo=fopen("A/CPUINFO.TXT", "wb");
    for(i = 0; cpuinfo_desc[i].name; i++) {
        wordval = cpuinfo[i];
        sprintf(buf,"%-10s 0x%08X\n",cpuinfo_desc[i].name,wordval);
        fwrite(buf,1,strlen(buf),finfo);
        for(j=0; cpuinfo_desc[i].fields[j].name; j++) {
            p=buf;
            bits = cpuinfo_desc[i].fields[j].bits;
            mask = ~(0xFFFFFFFF << bits);
            fieldval = wordval & mask;
            p+=sprintf(p,"  %-20s 0x%X %d",cpuinfo_desc[i].fields[j].name,fieldval,fieldval);
            if(cpuinfo_desc[i].fields[j].desc_fn) {
                p+=sprintf(p," [%s]",cpuinfo_desc[i].fields[j].desc_fn(fieldval));
            }
            strcat(p,"\n");
            fwrite(buf,1,strlen(buf),finfo);
            wordval >>= bits;
        }
    }
    fclose(finfo);
    gui_mbox_init((int)"CPUINFO",(int)"Wrote A/CPUINFO.TXT",MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, cpuinfo_finish);
}

int basic_module_init() {
    cpuinfo_write_file();
    return 1;
}
// =========  MODULE INIT =================
#include "simple_module.c"
void cpuinfo_finish(unsigned dummy) {
    running=0;
}

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"CPU INFO",// Module name
    (int32_t)"Read CPU and cache information from CP15",

    &_librun.base,

    ANY_VERSION,                // CONF version
    ANY_VERSION,                // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/

