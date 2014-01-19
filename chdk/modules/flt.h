#ifndef __FLT_H__
#define __FLT_H__

typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

//================= CFLT format header =====================

/*
	Structure of CFLAT v6 file:
	- flat_hdr
	- .text		[start from flt_hdr.entry]
    - .rodata	[start from flt_hdr.data_start]
    - .data
	- .bss		[start from flt_hdr.bss_start]
    - reloc_list [start from flt_hdr.reloc_start]
		* this is just array of offsets in flat
    - import_list  [start from flt_hdr.import_start]
		* this is array of import_record_t
*/

#define	FLAT_VERSION	    0x00000009L
#define FLAT_MAGIC_NUMBER   "CFLAT"

//================= FLAT Header structure ==============
/*
 * To make everything easier to port and manage cross platform
 * development,  all fields are in network byte order.
 */

// Module file header
// This is located at the start of the module file and is used to load the module
// into memory and perform any necessary relocations.
// Once loaded the _module_info pointer handles everything else.
struct flat_hdr {
    char magic[4];          // "CFLA"
  	uint32_t rev;          	// version (as above)
    uint32_t entry;         // Offset of start .text segment
    uint32_t data_start;    // Offset of data segment from beginning of file
    uint32_t bss_start;     // Offset of bss segment from beginning of file
                            // (It is assumed that data_end through bss_end forms the bss segment.)

    // Relocation info
    uint32_t reloc_start;   // Offset of relocation records from beginning of file
    uint32_t import_start;  // Offset of import section
    uint32_t file_size;     // size of file

    // Offset / Pointer to ModuleInfo structure
    union
    {
        uint32_t            _module_info_offset;    // Offset ModuleInfo from beginning of file
#if defined(USE_INT32_FOR_PTRS) // For elfflt.c on 64 bit Linux
	    uint32_t            _module_info;           // Ptr to ModuleInfo after relocation
#else
	    struct ModuleInfo*  _module_info;           // Ptr to ModuleInfo after relocation
#endif
    };
};

//================= Module information structure =====================

#define MODULEINFO_V1_MAGICNUM  0x023703e5

#define ANY_CHDK_BRANCH		0
#define REQUIRE_CHDK_MAIN   1
#define REQUIRE_CHDK_DE		2
#define REQUIRE_CHDK_SDM	3
#define REQUIRE_CHDK_PRIVATEBUILD	4

#define ANY_PLATFORM_ALLOWED	0

// Base module interface - once loaded into memory and any relocations done these
// functions provide the minimum interface to run the module code.
// Extend this interface for modules that need additional functions (e.g. libdng_sym in dng.h)
typedef struct
{
    int     (*loader)();        // loader function. Optional
                                // Should only perform initialisation that can be done module is first loaded.
    int     (*unloader)();      // unloader function. Optional
                                // Does any necessary clean up just prior to module being removed
    int     (*can_unload)();    // ask module if it is safe to unload. Optional
                                // Called each keyboard task tick to see if it is safe to unload the module
    int     (*exit_alt)();      // alert module that CHDK is leaving <ALT> mode. Optional
                                // If the module should be unloaded when <ALT> mode exits then this function
                                // should tell the module to return 'true' on the next call to can_unload
                                // This function should not do any cleanup or shutdown of the module
    int     (*run)();           // run module (for simple modules like games). Optional
                                // If not supplied the an extended interface is required to call module code
} base_interface_t;

// Module information structure
// Contains everything used to communicate with and run code in the module
struct ModuleInfo 
{
	uint32_t            magicnum;               // MODULEINFO_V1_MAGICNUM - sanity check when loading
	uint32_t            sizeof_struct;          // sizeof this struct - sanity check when loading
	_version_t          module_version;         // version of module - compared to version in module_handler_t
	uint32_t            chdk_required_branch;   // CHDK version checks
	uint32_t            chdk_required_ver;
	uint32_t            chdk_required_platfid;

	int32_t             moduleName;			    // pointer to string with module name or -LANG_ID
	int32_t             description;		    // pointer to string with module description (not currently used)

#if defined(USE_INT32_FOR_PTRS) // For elfflt.c on 64 bit Linux
    uint32_t            lib;
#else
    base_interface_t*   lib;                    // Pointer to interface library
#endif

    // Version checks (set to {0,0} to skip check)
    _version_t          conf_ver;               // CONF version (Conf structure in conf.h)
    _version_t          cam_screen_ver;         // CAM SCREEN version (camera_screen in camera_info.h)
    _version_t          cam_sensor_ver;         // CAM SENSOR version (camera_sensor in camera_info.h)
    _version_t          cam_info_ver;           // CAM INFO version (camera_info in camera_info.h)
};

#endif /* __FLT_H__ */

