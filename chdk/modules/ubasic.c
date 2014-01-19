#include "camera_info.h"
#include "stdlib.h"
#include "gui.h"

#include "script_api.h"
#include "module_def.h"

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

int ubasic_init(const char *program, int is_ptp);
int ubasic_run(void);
void ubasic_end(void);
void ubasic_set_variable(int varum, int value);
void ubasic_set_as_ret(int md_ret);
int jump_label(char * label);

static int ubasic_run_restore(void)             { return jump_label("restore"); }

// shoot hooks not supported in ubasic
static void ubasic_script_shoot_hook_run(int hook) { return; }
/******************** Module Information structure ******************/

libscriptapi_sym _libubasic =
{
    {
         0, 0, 0, 0, 0
    },

    ubasic_init,
    ubasic_run,
    ubasic_end,
    ubasic_set_variable,
    ubasic_set_as_ret,
    ubasic_run_restore,
    ubasic_script_shoot_hook_run,
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SCRIPT_API_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"uBasic",          // Module name
    (int32_t)"Run uBasic Scripts",

    &_libubasic.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    CAM_SENSOR_VERSION,         // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
