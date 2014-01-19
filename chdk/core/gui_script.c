#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_menu.h"
#include "fileutil.h"

#include "script_api.h"
#include "gui_fselect.h"

// Forward reference
static void gui_update_script_submenu();

//-------------------------------------------------------------------

#define SCRIPT_DEFAULT_FILENAME     "A/SCRIPT.LUA"
#define SCRIPT_DATA_PATH            "A/CHDK/DATA/"
#define SCRIPT_DEFAULT_DIR          "A/CHDK/SCRIPTS/"

// Requested filename
enum FilenameMakeModeEnum {
    MAKE_PARAMSETNUM_FILENAME,      // "DATA/scriptname.cfg" -> cfg_name
    MAKE_PARAM_FILENAME             // "DATA/scriptname_%d" -> cfg_param_name
};

//-------------------------------------------------------------------

const char *script_source_str=NULL;         // ptr to content of script
static char cfg_name[100] = "\0";           // buffer to make cfg files name (paramsetnum, param_names)
static char cfg_param_name[100] = "\0";     // buffer to make cfg param files name (params, state_before_tmprun)

static const char *lua_script_default =
    "--[[\n"
    "@title Default Script\n"
    "]]\n"
#if defined(VER_CHDK)
    "chdk_def_lang=1\n"
#else
    "chdk_def_lang=2\n"
#endif
    "langs     = {}\n"
    "langs[1]  = {[\"name\"]=\"ENGLISH\",  [\"font_cp\"]=0,  [\"hint\"]=\"CHDK language changed to english\"}\n"
    "langs[2]  = {[\"name\"]=\"GERMAN\",   [\"font_cp\"]=2,  [\"hint\"]=\"CHDK-Sprache auf deutsch geändert\"}\n"
    "langs[13] = {[\"name\"]=\"RUSSIAN\",  [\"font_cp\"]=1,  [\"hint\"]=\"CHDK language changed to russian\"}\n"
    
    "function get_cam_language()\n"
        "local l\n"
        "if get_propset()==1 then\n"
            "l=get_prop(196)/256\n"
            "if l>7 then l=l+1 end\n"
            "if l>22 then l=l+1 end\n"
        "else\n"
            "l=get_prop(61)/256\n"
        "end\n"
        "return l+1\n"
    "end\n"
    
    "function get_chdk_language()\n"
        "local l=0\n"
        "local lf=get_config_value(64)\n"
        "if lf==\"\" then\n"
            "l=chdk_def_lang\n"
        "else\n"
            "for i,v in ipairs(langs) do\n"
                "if string.find(lf, v[\"name\"]..\".LNG\")~=nil then\n"
                    "l=i\n"
                    "break\n"
                "end\n"
            "end\n"
        "end\n"
        "return l\n"
    "end\n"
    
    "function file_exists(name)\n"
         "local f=io.open(name,\"r\")\n"
         "if f~=nil then io.close(f) return true else return false end\n"
    "end\n"
    
    
    "chdk_lang=get_chdk_language()\n"
    "cam_lang=get_cam_language()\n"
    
    "if cam_lang~=chdk_lang then\n"
        "if chdk_lang==0 or cam_lang==chdk_def_lang then\n"
            "set_config_value(64,\"\")\n"
            "set_config_value(65,langs[chdk_def_lang].font_cp)\n"
            "print(langs[chdk_def_lang].hint)\n"
        "elseif langs[cam_lang]~=nil then\n"
            "if file_exists(\"A/CHDK/LANG/\"..langs[cam_lang].name..\".LNG\") then\n"
                "set_config_value(64,\"A/CHDK/LANG/\"..langs[cam_lang].name..\".LNG\")\n"
                "set_config_value(65,langs[cam_lang].font_cp)\n"
                "print(langs[cam_lang].hint)\n"
            "else\n"
                "print(langs[cam_lang].name..\".LNG is missing\")\n"
            "end\n"
        "else\n"
            "print(\"unknown language id (\"..cam_lang..\")\")\n"
        "end\n"
    "else\n"
        "print(\";)\")\n"
    "end\n";

// ================ SCRIPT PARAMETERS ==========
char script_title[36];                                      // Title of current script

//
// 1. Values of script parameters are stored in conf.script_vars
// 2. Encoding scheme is: array[VAR-'a'] = value

#define MAX_PARAM_NAME_LEN  27
#define DEFAULT_PARAM_SET   10                              // Value of conf.script_param_set for 'Default' rather than saved parameters

char script_params[SCRIPT_NUM_PARAMS][MAX_PARAM_NAME_LEN+1];// Parameter title
static char script_param_order[SCRIPT_NUM_PARAMS];          // Ordered as_in_script list of variables ( [idx] = id_of_var )
                                                            // to display in same order in script
static int script_range_values[SCRIPT_NUM_PARAMS];          // Min/Max values for param validation
static char script_range_types[SCRIPT_NUM_PARAMS];          // Specifies if range values is signed (-9999-32767) or unsigned (0-65535)
                                                            // Note: -9999 limit on negative values is due to current gui_menu code (and because menu only displays chars)
static const char **script_named_values[SCRIPT_NUM_PARAMS]; // Array of list values for named parameters
static char script_named_counts[SCRIPT_NUM_PARAMS];         // Count of # of entries in each script_list_values array
static char *script_named_strings[SCRIPT_NUM_PARAMS];       // Base storage for named value string data
static int script_loaded_params[SCRIPT_NUM_PARAMS];         // Copy of original values of parameters 
                                                            // (detect are they changed or not)

//-------------------------------------------------------------------

const char* skip_whitespace(const char* p)  { while (*p==' ' || *p=='\t') p++; return p; }                                  // Skip past whitespace
const char* skip_token(const char* p)       { while (*p && *p!='\r' && *p!='\n' && *p!=' ' && *p!='\t') p++; return p; }    // Skip past current token value
const char* skip_toeol(const char* p)       { while (*p && *p!='\r' && *p!='\n') p++; return p; }                           // Skip to end of line
const char* skip_eol(const char *p)         { p = skip_toeol(p); if (*p == '\r') p++; if (*p == '\n') p++; return p; }      // Skip past end of line

//=======================================================
//             PROCESSING "@ACTION" FUNCTIONS
//=======================================================


//-------------------------------------------------------------------
static void process_title(const char *title)
{
    register const char *ptr = title;
    register int i=0;

    ptr = skip_whitespace(ptr);
    while (i<(sizeof(script_title)-1) && ptr[i] && ptr[i]!='\r' && ptr[i]!='\n')
    {
        script_title[i]=ptr[i];
        ++i;
    }
    script_title[i]=0;
}

//-------------------------------------------------------------------
// Process one entry "@param VAR TITLE" to check if it exists
//      param = ptr right after descriptor (should point to var)
// RETURN VALUE: 0 if not found, 1..26 = id of var
// Used to ensure that a param loaded from an old saved paramset does
// not overwrite defaults from script
//-------------------------------------------------------------------
static int check_param(const char *param)
{
    register const char *ptr = param;
    register int n=0, l;

    ptr = skip_whitespace(ptr);
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t'))
    {
        n = ptr[0]-'a';                                 // VAR
        ptr = skip_whitespace(ptr+2);                   // skip to TITLE
        l = skip_toeol(ptr) - ptr;                      // get length of TITLE
        if (l > MAX_PARAM_NAME_LEN)
            l = MAX_PARAM_NAME_LEN;
        if (l != strlen(script_params[n]))              // Check length matches existing TITLE length
            n = 0;
        else if (strncmp(ptr,script_params[n],l) != 0)  // Check that TITLE matches existing TITLE
            n = 0;
        else
            n++;
    }
    return n; // n=1 if '@param a' was processed, n=2 for 'b' ... n=26 for 'z'. n=0 if failed.
}

//-------------------------------------------------------------------
// Process one entry "@param VAR TITLE"
//      param = ptr right after descriptor (should point to var)
// RESULT: script_params[VAR] - parameter title
// RETURN VALUE: 0 if err, 1..26 = id of var
//-------------------------------------------------------------------
static int process_param(const char *param)
{
    register const char *ptr = param;
    register int n=0, l;

    ptr = skip_whitespace(ptr);
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t'))
    {
        n = ptr[0]-'a';
        ptr = skip_whitespace(ptr+2);
        l = skip_toeol(ptr) - ptr;                  // get length of TITLE
        if (l > MAX_PARAM_NAME_LEN)
            l = MAX_PARAM_NAME_LEN;
        strncpy(script_params[n],ptr,l);
        script_params[n][l] = 0;
        n++;
    }
    return n; // n=1 if '@param a' was processed, n=2 for 'b' ... n=26 for 'z'. n=0 if failed.
}

//-------------------------------------------------------------------
// Process one entry "@default VAR VALUE"
//      param = ptr right after descriptor (should point to var)
//-------------------------------------------------------------------
static void process_default(const char *param)
{
    register const char *ptr = param;
    register int n;

    ptr = skip_whitespace(ptr);
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t'))
    {
        n = ptr[0]-'a';
        ptr = skip_whitespace(ptr+2);
        conf.script_vars[n] = strtol(ptr, NULL, 0);
        script_loaded_params[n] = conf.script_vars[n];
    } // ??? else produce error message
}

//-------------------------------------------------------------------
// Process one entry "@range VAR MIN MAX"
//      param = ptr right after descriptor (should point to var)
//-------------------------------------------------------------------
static void process_range(const char *param)
{
    register const char *ptr = param;
    register int n;

    ptr = skip_whitespace(ptr);
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t'))
    {
        n = ptr[0]-'a';
        ptr = skip_whitespace(ptr+2);
        int min = strtol(ptr,NULL,0);
        ptr = skip_whitespace(skip_token(ptr));
        int max = strtol(ptr,NULL,0);
        script_range_values[n] = MENU_MINMAX(min,max);
        if ((min == 0) && (max == 1))
            script_range_types[n] = MENUITEM_BOOL;
        else if ((min >= 0) && (max >= 0)) 
            script_range_types[n] = MENUITEM_INT|MENUITEM_F_MINMAX|MENUITEM_F_UNSIGNED;
        else
            script_range_types[n] = MENUITEM_INT|MENUITEM_F_MINMAX;
    } // ??? else produce error message
}

//-------------------------------------------------------------------
// Process one entry "@values VAR A B C D ..."
//      param = ptr right after descriptor (should point to var)
//-------------------------------------------------------------------
static void process_values(const char *param)
{
    register const char *ptr = param;
    register int n;

    ptr = skip_whitespace(ptr);
    if (ptr[0] && (ptr[0]>='a' && ptr[0]<='a'+SCRIPT_NUM_PARAMS) && (ptr[1]==' ' || ptr[1]=='\t'))
    {
        n = ptr[0]-'a';
        ptr = skip_whitespace(ptr+2);
        int len = skip_toeol(ptr) - ptr;
        script_named_strings[n] = malloc(len+1);
        strncpy(script_named_strings[n], ptr, len);
        script_named_strings[n][len] = 0;

        const char *p = script_named_strings[n];
        int cnt = 0;
        while (*p)
        {
            p = skip_whitespace(skip_token(p));
            cnt++;
        }
        script_named_counts[n] = cnt;
        script_named_values[n] = malloc(cnt * sizeof(char*));

        p = script_named_strings[n];
        cnt = 0;
        while (*p)
        {
            script_named_values[n][cnt] = p;
            p = skip_token(p);
            if (*p)
            {
                *((char*)p) = 0;
                p = skip_whitespace(p+1);
            }
            cnt++;
        }
    } // ??? else produce error message
}

//=======================================================
//                 SCRIPT LOADING FUNCTIONS
//=======================================================

//-------------------------------------------------------------------
// PURPOSE: Parse script (script_source_str) for @xxx
// PARAMETERS:  fn - full path of script
// RESULTS:  script_title
//           script_params
//           script_params_order
//           script_loaded_params, conf.script_vars
//-------------------------------------------------------------------
static void script_scan(const char *fn)
{
    register const char *ptr = script_source_str;
    register int i, j=0, n;
    char *c;

    if ( !ptr ) { ptr = lua_script_default; }     // sanity check

    // Build title

    c=strrchr(fn, '/');
    strncpy(script_title, (c)?c+1:fn, sizeof(script_title));
    script_title[sizeof(script_title)-1]=0;

    // Reset everything

    for (i=0; i<SCRIPT_NUM_PARAMS; ++i)
    {
        conf.script_vars[i] = 0;
        script_loaded_params[i] = 0;
        script_params[i][0]=0;
        script_param_order[i]=0;
        script_range_values[i] = 0;
        if (script_named_values[i]) free(script_named_values[i]);
        script_named_values[i] = 0;
        if (script_named_strings[i]) free(script_named_strings[i]);
        script_named_strings[i] = 0;
        script_named_counts[i] = 0;
    }

    // Fillup order, defaults

    while (ptr[0])
    {
        ptr = skip_whitespace(ptr);
        if (ptr[0]=='@') {
            if (strncmp("@title", ptr, 6)==0)
            {
                process_title(ptr+6);
            }
            else if (strncmp("@param", ptr, 6)==0)
            {
                n = process_param(ptr+6); // n=1 if '@param a' was processed, n=2 for 'b' ... n=26 for 'z'. n=0 if failed.
                if (n>0 && n<=SCRIPT_NUM_PARAMS)
                {
                  script_param_order[j]=n;
                  j++;
                }
            }
            else if (strncmp("@default", ptr, 8)==0)
            {
                process_default(ptr+8);
            }
            else if (strncmp("@range", ptr, 6)==0)
            {
                process_range(ptr+6);
            }
            else if (strncmp("@values", ptr, 7)==0)
            {
                process_values(ptr+7);
            }
        }
        ptr = skip_eol(ptr);
    }
}

//-------------------------------------------------------------------
// PURPOSE:     Create cfg filename in buffer.
// PARAMETERS:  mode - what exact kind of cfg file name required
//                fn - full path of script  (optional. have no matter for some modes)
//                paramset - target paramset (optional)
// RESULT:  name at cfg_param_name or cfg_name (depending on mode)
//-------------------------------------------------------------------
void make_param_filename( enum FilenameMakeModeEnum mode, const char* fn, int paramset )
{
    char extbuf[5];
    char* tgt_buf;
    char* name = 0;
    
    // find name of script
    if (fn && fn[0]) 
    {
        name = strrchr( fn, '/' ); 
        if (name) name++; else name=(char*)fn;
    }

    // prepare base data to make
    switch ( mode )
    {
        case MAKE_PARAMSETNUM_FILENAME:
            tgt_buf = cfg_name;
            strcpy(extbuf,".cfg");
            break;            
        case MAKE_PARAM_FILENAME:
            tgt_buf = cfg_param_name;
            sprintf(extbuf,"_%d",paramset);
            break;            
        default:        // unknown mode
            return;
    }
    
    // make path
    strcpy(tgt_buf, SCRIPT_DATA_PATH);
    
    // add script filename
    char* tgt_name=tgt_buf+strlen(tgt_buf);
    strncpy( tgt_name, name, 12 );
    tgt_name[12] = 0;

    // find where extension start and replace it
    char* ext = strrchr(tgt_name, '.');
    if (!ext) ext=tgt_name+strlen(tgt_name);
    strcpy ( ext, extbuf );
}

//-------------------------------------------------------------------
// read last paramset num of script "fn" to conf.script_param_set
//-------------------------------------------------------------------
void get_last_paramset_num(const char *fn)
{
    // skip if internal script used
    if (fn == NULL || fn[0] == 0) return;

    make_param_filename( MAKE_PARAMSETNUM_FILENAME, fn, 0);
    if ( !load_int_value_file( cfg_name, &conf.script_param_set ) )
       conf.script_param_set = 0;
    if ((conf.script_param_set < 0) || (conf.script_param_set > 10))
       conf.script_param_set = 0;
    make_param_filename( MAKE_PARAM_FILENAME, fn, conf.script_param_set);
}

//-------------------------------------------------------------------
// PURPOSE:     Load parameters from paramset for script
// PARAMETERS:  fn - full path of script
//              paramset - num of loaded paramset (usually conf.script_param_set)
// RETURN:      1-succesfully applied, 0 - something was failed
//-------------------------------------------------------------------
int load_params_values(const char *fn, int paramset)
{
    // skip if internal script used
    if (fn == NULL || fn[0] == 0) return 0;
    // skip if 'default' parameters requested
    if (paramset == DEFAULT_PARAM_SET) return 0;
    
    if ((paramset < 0) || (paramset > 10)) paramset = 0;
    conf.script_param_set = paramset;
    make_param_filename( MAKE_PARAM_FILENAME, fn, paramset );

    char* buf = load_file(cfg_param_name, 0, 1);
    if (!buf)
        return 0;

    const char* ptr = buf;

    // Initial scan of saved paramset file
    // Ensure all saved params match defaults from script
    // If not assume saved file is invalid and don't load it
    //   may occur if script is changed, or file was saved by a different script with same name
    while (ptr[0]) 
    {
        ptr = skip_whitespace(ptr);
        if (ptr[0]=='@')
        {
            if (strncmp("@param", ptr, 6) == 0) 
            {
                if (!check_param(ptr+6))
                    return 0;
            }
        }
        ptr = skip_eol(ptr);
    }

    // All ok, reset and process file
    ptr = buf;

    while (ptr[0]) 
    {
        ptr = skip_whitespace(ptr);
        if (ptr[0]=='@')
        {
            // Already checked file, so only need to load the @default values
            // @param, @range & @values already set from script
            if (strncmp("@default", ptr, 8)==0)
            {
                process_default(ptr+8);
            }
        }
        ptr = skip_eol(ptr);
    }

    free(buf);

    return 1;
}


//-------------------------------------------------------------------
// PURPOSE:     Auxilary function.
//                Actually save param file
// PARAMETERS:  fn = name of target file (actually always cfg_param_name)
//-------------------------------------------------------------------
static void do_save_param_file(char* fn)
{
    int n;
    FILE *fd;
    char buf[250];

    fd = fopen(fn, "w");
    if (fd)
    {
        for(n = 0; n < SCRIPT_NUM_PARAMS; ++n)
        {
            if (script_params[n][0] != 0)
            {
                // Only need to save @param & @default info - @range & @values are only loaded from script header
                sprintf(buf,"@param %c %s\n@default %c %d\n",'a'+n,script_params[n],'a'+n,conf.script_vars[n]);
                fwrite(buf, strlen(buf), 1, fd);
            }
        }
        
        fclose(fd);
    }
}

//-------------------------------------------------------------------
// PURPOSE:     Save parameters to paramset for script
//                  Use: conf.script_file, conf.script_param_set
// PARAMETERS:  enforce = 1 mean save always
//                      = 0 mean save only if any values was changed
//                        (script_loaded_params[i] != conf.script_vars[i])
//
// NOTE:    1. create SCRIPT_DATA_PATH/scriptname.cfg 
//                      which store # of last saved paramset
//          2. create SCRIPT_DATA_PATH/scriptname_PARAMSETNUM 
//                      which param_str
//-------------------------------------------------------------------
void save_params_values( int enforce )
{
    if (conf.script_param_save && (conf.script_param_set != DEFAULT_PARAM_SET))
    {
        // Write paramsetnum file
        make_param_filename( MAKE_PARAMSETNUM_FILENAME, conf.script_file, 0);
        save_int_value_file( cfg_name, conf.script_param_set );

        int i, changed=0;

        // Check is anything changed since last time
        for(i = 0; i < SCRIPT_NUM_PARAMS; i++)
        {
            if (script_loaded_params[i] != conf.script_vars[i]) changed++;
            script_loaded_params[i] = conf.script_vars[i];
        }

        if (enforce || changed)
        {
            // Write parameters file
            make_param_filename( MAKE_PARAM_FILENAME, conf.script_file, conf.script_param_set);
            do_save_param_file(cfg_param_name);
        }
    }
}

//-------------------------------------------------------------------
// PURPOSE: Reset values of variables to default
//-------------------------------------------------------------------
void script_reset_to_default_params_values() 
{
    script_scan( conf.script_file );    // load all values from script
}

//-------------------------------------------------------------------
// PURPOSE: Load script to memory ( and free malloc previous if exists)
// PARAMETERS:  fn - full path of script
//
// RESULTS: conf.script_file
//          script_source_str - loaded script file content
//
// NOTES:  1. Try to load fn, if fn or file is empty - SCRIPT_DEFAULT_FILENAME, 
//                if default not exists - use builtin
//         2. Update conf.script_file, title, submenu
//-------------------------------------------------------------------
void script_load(const char *fn)
{
    char* buf;

    if(script_source_str && script_source_str != lua_script_default)
        free((void *)script_source_str);

    // if filename is empty, try to load default named script.
    // if no such one, lua_script_default will be used
    if ( !fn[0] )
    {
        buf = load_file(SCRIPT_DEFAULT_FILENAME, 0, 1);
        if ( buf )
            fn = SCRIPT_DEFAULT_FILENAME;
    }
    else
    {
        buf = load_file(fn, 0, 1);
    }

    if ( !buf )
    {
        // if failed to load - say "internal" and raise flag need update
        script_source_str = lua_script_default;
        conf.script_file[0] = 0;
    }
    else
    {
        // if ok - set pointers to script
        script_source_str = buf;
        strcpy(conf.script_file, fn);
    }

    get_last_paramset_num( conf.script_file );            // update data paths
    script_scan( conf.script_file );                      // re-fill @title/@names/@order/@range/@value + reset values to @default
    load_params_values( conf.script_file, conf.script_param_set );

    gui_update_script_submenu();
}

//-------------------------------------------------------------------

static const char* gui_script_param_set_enum(int change, int arg)
{
    static const char* modes[]={ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Default" };

    if (change != 0)
    {
        save_params_values(0);
        gui_enum_value_change(&conf.script_param_set,change,sizeof(modes)/sizeof(modes[0]));

        if ( !load_params_values(conf.script_file, conf.script_param_set) )
            script_reset_to_default_params_values();
        gui_update_script_submenu();
    }

    return modes[conf.script_param_set];
}

static const char* gui_script_param_save_enum(int change, int arg)
{
    static const char* modes[]={ "Off", "On" };

    if (conf.script_param_set != DEFAULT_PARAM_SET)
    {
        if (change != 0)
        {
            gui_enum_value_change(&conf.script_param_save,change,sizeof(modes)/sizeof(modes[0]));
            if (conf.script_param_save)
                save_params_values(0);
        }

        return modes[conf.script_param_save];
    }

    return modes[0];
}

static void gui_load_script_selected(const char *fn) {
    if (fn) {
        gui_menu_cancel_redraw();   // Stop menu redraw until after menu rebuilt from script params
        save_params_values(0);
        script_load(fn);
        gui_set_need_restore();
    }
}

static void gui_load_script(int arg) {
    libfselect->file_select(LANG_STR_SELECT_SCRIPT_FILE, conf.script_file, "A/CHDK/SCRIPTS", gui_load_script_selected);
}

static void gui_load_script_default(int arg) {
    script_reset_to_default_params_values();
    gui_update_script_submenu();
    save_params_values(1);
}

static const char* gui_script_autostart_modes[]=            { "Off", "On", "Once", "ALT"};


// Indexes into script_submenu_items array, if you add or remove entries adjust these
#define SCRIPT_SUBMENU_PARAMS_IDX   8       // First adjustable parameter entry
#define SCRIPT_SUBMENU_BOTTOM_IDX   34      // 'Back' entry

static CMenuItem script_submenu_items[] = {
    MENU_ITEM   (0x35,LANG_MENU_SCRIPT_LOAD,                MENUITEM_PROC,                      gui_load_script,            0 ),
    MENU_ITEM   (0x5f,LANG_MENU_SCRIPT_DELAY,               MENUITEM_INT|MENUITEM_F_UNSIGNED,   &conf.script_shoot_delay,   0 ),
    // remote autostart
    MENU_ENUM2  (0x5f,LANG_MENU_SCRIPT_AUTOSTART,           &conf.script_startup,               gui_script_autostart_modes ),
    MENU_ITEM   (0x5c,LANG_MENU_LUA_RESTART,                MENUITEM_BOOL,                      &conf.debug_lua_restart_on_error,   0 ),
    MENU_ITEM   (0x5d,LANG_MENU_SCRIPT_DEFAULT_VAL,         MENUITEM_PROC,                      gui_load_script_default,    0 ),
    MENU_ITEM   (0x5e,LANG_MENU_SCRIPT_PARAM_SET,           MENUITEM_ENUM,                      gui_script_param_set_enum,  0 ),
    MENU_ITEM   (0x5c,LANG_MENU_SCRIPT_PARAM_SAVE,          MENUITEM_ENUM,                      gui_script_param_save_enum, 0 ),
    MENU_ITEM   (0x0 ,(int)script_title,                    MENUITEM_SEPARATOR,                 0,                          0 ),

    // SCRIPT_NUM_PARAMS entries - filled in at runtime
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),
    MENU_ITEM   (0x0 ,0, 0, 0, 0 ),

    MENU_ITEM   (0x51,LANG_MENU_BACK,                       MENUITEM_UP,                        0,                          0 ),
    {0}
};

CMenu script_submenu = {0x27,LANG_MENU_SCRIPT_TITLE, script_submenu_items };

static void gui_update_script_submenu() 
{
    register int p, i;

    for (p=SCRIPT_SUBMENU_PARAMS_IDX, i=0; i<SCRIPT_NUM_PARAMS; ++i)
    {
        if (script_param_order[i])
        {
            int n = script_param_order[i]-1;

            script_submenu_items[p].symbol = 0x0;
            script_submenu_items[p].text = (int)script_params[n];
            script_submenu_items[p].type = MENUITEM_INT|MENUITEM_SCRIPT_PARAM;
            script_submenu_items[p].value = &conf.script_vars[n];

            if (script_range_values[n] != 0)
            {
                script_submenu_items[p].type = script_range_types[n]|MENUITEM_SCRIPT_PARAM;
                script_submenu_items[p].arg = script_range_values[n];
            }
            else if (script_named_counts[n] != 0)
            {
                script_submenu_items[p].type = MENUITEM_ENUM2|MENUITEM_SCRIPT_PARAM;
                script_submenu_items[p].opt_len = script_named_counts[n];
                script_submenu_items[p].arg = (int)script_named_values[n];
            }

            ++p;
        }
    }

    // Fill in 'Back' button and terminator
    memset(&script_submenu_items[p],0,sizeof(CMenuItem)*2);
    script_submenu_items[p].symbol = 0x51;
    script_submenu_items[p].text = LANG_MENU_BACK;
    script_submenu_items[p].type = MENUITEM_UP;
}

//-------------------------------------------------------------------
