#include "camera_info.h"
#include "stdlib.h"
#include "gui.h"
#include "gui_draw.h"
#include "script.h"
#include "script_key_funcs.h"
#include "conf.h"
#include "shot_histogram.h"
#include "raw.h"
#include "levent.h"
#include "console.h"
#include "action_stack.h"
#include "ptp_chdk.h"
#include "lang.h"
#include "gui_lang.h"
#include "histogram.h"
#include "shooting.h"
#include "autoiso.h"
#include "remotecap.h"
#include "battery.h"
#include "temperature.h"
#include "backlight.h"
#include "keyboard.h"
#include "shutdown.h"
#include "sound.h"
#include "modes.h"
#include "sd_card.h"
#include "clock.h"
#include "lens.h"
#include "properties.h"
#include "file_counter.h"
#include "debug_led.h"
#include "meminfo.h"
#include "callfunc.h"

#include "script_api.h"
#include "curves.h"
#include "motion_detector.h"
#include "raw_merge.h"
#include "gui_fselect.h"
#include "gui_tbox.h"
#include "module_def.h"
#include "luascript.h"
#include "script_shoot_hook.h"

#include "../lib/lua/lualib.h"
#include "../lib/lua/lauxlib.h"
#include "../lib/lua/lstate.h"  // for L->nCcalls, baseCcalls

lua_State* L;
lua_State* Lt;

extern void register_lua_funcs( lua_State* L );

static int lua_script_is_ptp;
static int ptp_saved_alt_state;
static int run_first_resume; // 1 first 'resume', 0 = resuming from yield
static int run_start_tick; // tick count at start of this kbd_task iteration
static int run_hook_count; // number of calls to the count hook this kbd_task iteration
#define YIELD_CHECK_COUNT 100 // check for yield every N vm instructions
#define YIELD_MAX_COUNT_DEFAULT 25 // 25 checks = 2500 vm instructions
#define YIELD_MAX_MS_DEFAULT 10
static unsigned yield_max_count;
static unsigned yield_max_ms;
static int yield_hook_enabled;

static void lua_script_disable_yield_hook(void) {
    yield_hook_enabled = 0;
}
static void lua_script_enable_yield_hook(void) {
    yield_hook_enabled = 1;
}

// create a ptp message from the given stack index
// incompatible types will return a TYPE_UNSUPPORTED message
static ptp_script_msg *lua_create_usb_msg( lua_State* L, int index, unsigned msgtype) {
    // TODO maybe we should just pass the lua type constants
    unsigned datatype, datasize = 4;
    int ivalue = 0;
    void *data = &ivalue;
    int ltype = lua_type(L,index);
    switch(ltype) {
        case LUA_TNONE:
            return NULL; // nothing on the stack, no message generated
        break;
        case LUA_TNIL:
            datatype = PTP_CHDK_TYPE_NIL;
        break;
        case LUA_TBOOLEAN:
            datatype = PTP_CHDK_TYPE_BOOLEAN;
            ivalue = lua_toboolean(L,index);
        break;
        case LUA_TNUMBER:
            datatype = PTP_CHDK_TYPE_INTEGER;
            ivalue = lua_tonumber(L,index);
        break;
        case LUA_TSTRING:
            datatype = PTP_CHDK_TYPE_STRING;
            data = (char *)lua_tolstring(L,index,&datasize);
        break;
        // TODO this uses usb_msg_table_to_string to serialize the table
        // the default format is described in
        // http://chdk.setepontos.com/index.php?topic=4338.msg62606#msg62606
        // other formats can be implemented by overriding this function in your lua code
        case LUA_TTABLE: {
            int result;
            lua_script_disable_yield_hook(); // don't want to yield while converting
            lua_getglobal(L, "usb_msg_table_to_string"); // push function
            lua_pushvalue(L, index); // copy specified index to top of stack
            result = lua_pcall(L,1,1,0); // this will leave an error message as a string on the stack if call fails
            lua_script_enable_yield_hook();
            if( result ) {
                // if called from lua, throw a normal error
                if( msgtype == PTP_CHDK_S_MSGTYPE_USER ) {
                    luaL_error(L,lua_tostring(L,-1));
                    return NULL; // not reached
                } else { // if it's a return, convert the message to an ERR
                    msgtype = PTP_CHDK_S_MSGTYPE_ERR;
                    datatype = PTP_CHDK_S_ERRTYPE_RUN;
                    data = (char *)lua_tolstring(L,-1,&datasize);
                    break;
                }
            }
            // an empty table is returned as an empty string by default
            // a non-string should never show up here
            if ( !lua_isstring(L,-1) ) { 
                return NULL;
            }
            datatype = PTP_CHDK_TYPE_TABLE;
            data = (char *)lua_tolstring(L,-1,&datasize);
            lua_pop(L,1);
        }
        break;
        default:
            datatype = PTP_CHDK_TYPE_UNSUPPORTED;
            data = (char *)lua_typename(L,ltype); // return type name as message data
            datasize = strlen(data);
    }
    return ptp_script_create_msg(msgtype,datatype,datasize,data);
}

void lua_script_reset()
{
    script_shoot_hooks_reset();
    lua_close( L );
    L = 0;
}

void lua_script_error_ptp(int runtime, const char *err) {
    if(runtime) {
        ptp_script_write_error_msg(PTP_CHDK_S_ERRTYPE_RUN, err);
    } else {
        ptp_script_write_error_msg(PTP_CHDK_S_ERRTYPE_COMPILE, err);
        lua_script_reset();
    }
}

static void lua_count_hook(lua_State *L, lua_Debug *ar)
{
    run_hook_count++;
    if( L->nCcalls > L->baseCcalls || !yield_hook_enabled )
        return;
    if(run_hook_count >= yield_max_count || get_tick_count() - run_start_tick >= yield_max_ms)
        lua_yield( L, 0 );
}

int lua_script_error(lua_State *Lt,int runtime)
{
    const char *err = lua_tostring( Lt, -1 );

    if(err)
    {
        if(!*err)
        {
            script_console_add_line( (long)"ERROR: empty error message" );
        }
        else
        {
            script_console_add_line( (long)err );
        }
    }
    else
    {
        script_console_add_line( (long)"ERROR: NULL error message" );
    }

    if (lua_script_is_ptp)
    {
        lua_script_error_ptp(runtime,err);
    }
    else
    {
        if (runtime)
        {
            if(conf.debug_lua_restart_on_error) {
                script_end();
                script_start_gui(0);
                return SCRIPT_RUN_RUNNING;
            }
        }
        else // ensure lua_state is closed for compiletime errors
        {
            lua_script_reset();
        }
    }

    script_console_add_line(LANG_CONSOLE_TEXT_TERMINATED);
    return SCRIPT_RUN_ERROR;
}


// TODO more stuff from script.c should be moved here
void lua_script_finish(lua_State *L) 
{
    if(lua_script_is_ptp) {
        // send all return values as RET messages
        int i,end = lua_gettop(L);
        for(i=1;i<=end; i++) {
            ptp_script_msg *msg = lua_create_usb_msg(L,i,PTP_CHDK_S_MSGTYPE_RET);
            // if the queue is full return values will be silently discarded
            // incompatible types will be returned as TYPE_UNSUPPORTED to preserve expected number and order of return values
            if(msg) {
                ptp_script_write_msg(msg); 
                // create_usb_msg may convert the message to an error
                if(msg->type != PTP_CHDK_S_MSGTYPE_RET) {
                    break;
                }
            } else {
                ptp_script_write_error_msg(PTP_CHDK_S_ERRTYPE_RUN, "error creating return msg");
                break;
            }
        }
        if(!ptp_saved_alt_state) {
            exit_alt();
        }
    }
}

int lua_script_start( char const* script, int ptp )
{
    script_shoot_hooks_reset();
    lua_script_is_ptp = ptp;
    if(ptp) {
        ptp_saved_alt_state = (camera_info.state.gui_mode_alt);
        // put ui in alt state to allow key presses to be sent to script
        // just setting kbd_blocked leaves UI in a confused state
        if(!ptp_saved_alt_state) {
            enter_alt();
        }
    }
    L = lua_open();
    luaL_openlibs( L );
    register_lua_funcs( L );

    Lt = lua_newthread( L );
    lua_setfield( L, LUA_REGISTRYINDEX, "Lt" );
    if( luaL_loadstring( Lt, script ) != 0 )
    {
        lua_script_error(Lt,0);
        return 0;
    }
    lua_sethook(Lt, lua_count_hook, LUA_MASKCOUNT, YIELD_CHECK_COUNT );
    lua_script_enable_yield_hook();
    run_first_resume = 1;
    yield_max_count = YIELD_MAX_COUNT_DEFAULT;
    yield_max_ms = YIELD_MAX_MS_DEFAULT;
    return 1;
}

// run a timeslice of lua script
int lua_script_run(void)
{
    int Lres;
    int top;
    if (run_first_resume) {
        run_first_resume = 0;
        top = 0;
    } else {
        top = lua_gettop(Lt);
    }
    run_start_tick = get_tick_count();
    run_hook_count = 0;
    Lres = lua_resume( Lt, top );

    if (Lres == LUA_YIELD)
    {
        // yielded
    }
    else if (Lres != 0)
    {
        return lua_script_error(Lt,1);
    }
    else 
    {
        // finished normally, add ptp result
        lua_script_finish(Lt);
        // Display 'Finished message', unless running from PTP
        if (lua_script_is_ptp == 0)
            script_console_add_line(LANG_CONSOLE_TEXT_FINISHED);
        return SCRIPT_RUN_ENDED;
    }

    return SCRIPT_RUN_RUNNING;
}

// run the "restore" function at the end of a script
// Mimic uBasic logic, return 0 to trigger script interrupt immediately
int lua_run_restore()
{
	lua_getglobal(Lt, "restore");
	if (lua_isfunction(Lt, -1)) {
		if (lua_pcall( Lt, 0, 0, 0 )) {
			script_console_add_line( (long)lua_tostring( Lt, -1 ) );
		}
        if (lua_script_is_ptp == 0)
            script_console_add_line(LANG_CONSOLE_TEXT_FINISHED);
	}
    return 0;
}

// get key ID of key name at arg, throw error if invalid
static int lua_get_key_arg( lua_State * L, int narg )
{
    int k = script_keyid_by_name( luaL_checkstring( L, narg ) );
    if(!k) 
        luaL_error( L, "unknown key" );
    return k;
}

/*
  get a value where boolean or 0/!0 are accepted for on/off.
  normal lua toboolean will convert 0 to true, but ubasic and c users 
  will expect 0 to be off
  intentional HACK: numbers greater than 1 are returned as is
*/
static unsigned on_off_value_from_lua_arg( lua_State* L, int index)
{
  if( lua_isboolean(L,index) ) {
  	return lua_toboolean(L,index);
  }
  else {
  	return luaL_checknumber(L,index); 
  }
}

static int luaCB_set_curve_state( lua_State* L )
{
    libcurves->curve_set_mode(luaL_checknumber( L, 1 ));
    return 0;
}

static int luaCB_get_curve_state( lua_State* L )
{
    lua_pushnumber(L,conf.curve_enable);
    return 1;
}

static int luaCB_set_curve_file( lua_State* L )
{
    size_t l;
    const char *s = luaL_checklstring(L, 1, &l);
    libcurves->curve_set_file(s);
    return 0;
}

static int luaCB_get_curve_file( lua_State* L )
{
    lua_pushstring(L,conf.curve_file);
    return 1;
}

static int luaCB_set_aelock(lua_State* L) 
{
  int val = luaL_checknumber(L, 1);
  if (val>0) DoAELock();  // 1: enable AELock
  else UnlockAE();       // 0: disable unlock AE
  return 0;
}

static int luaCB_set_aflock(lua_State* L) 
{
  int val = luaL_checknumber(L, 1);
  if (val>0) DoAFLock();  // 1: enable AFLock
  else UnlockAF();       // 0: disable unlock AF
  return 0;
}


static int luaCB_shoot( lua_State* L )
{
  action_push_shoot(luaL_optnumber( L, 1, 1 ));
  return lua_yield( L, 0 );
}

// Process a sleep function from the stack
static int action_stack_AS_LUA_SLEEP()
{
    if (get_tick_count() >= action_top(2))
    {
        action_pop_func(1);
        return 1;
    }
    return 0;
}

static int sleep_delay(int delay)
{
    /* delay of -1 signals indefinite (actually 1 day) delay */
    if (delay == -1)
        delay = 86400000;

    if (delay > 0)
        return delay + get_tick_count();

    return 0;
}

static int luaCB_sleep( lua_State* L )
{
    int delay = sleep_delay(luaL_checknumber( L, 1 ));

    if (delay > 0)
    {
        action_push(delay);
        action_push_func(action_stack_AS_LUA_SLEEP);
    }

    return lua_yield( L, 0 );
}

// for press,release and click
static int luaCB_keyfunc( lua_State* L )
{
  void* func = lua_touserdata( L, lua_upvalueindex(1) );
  ((void(*)(long))func)( lua_get_key_arg( L, 1 ) );
  return lua_yield( L, 0 );
}

static int luaCB_cls( lua_State* L )
{
  console_clear();
  return 0;
}

static int luaCB_set_console_layout( lua_State* L )
{
  console_set_layout(luaL_checknumber( L, 1 ),luaL_checknumber( L, 2 ),luaL_checknumber( L, 3 ),luaL_checknumber( L, 4 ));
  return 0;
}

static int luaCB_set_console_autoredraw( lua_State* L )
{
  console_set_autoredraw(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_console_redraw( lua_State* L )
{
  console_redraw();
  return 0;
}

static int luaCB_get_partitionInfo( lua_State* L )
{
    if (camera_info.cam_has_multipart)
    {
      lua_createtable(L, 0, 4);
      SET_INT_FIELD("count",  get_part_count());
      SET_INT_FIELD("active", get_active_partition());
      SET_INT_FIELD("type",   get_part_type());
      SET_INT_FIELD("size",   GetTotalCardSpaceKb()>>10);
      return 1;
    }
    return 0;
}

static int luaCB_swap_partitions( lua_State* L )
{
    if (camera_info.cam_has_multipart)
    {
      int partNr;

      if( lua_gettop(L)==1 )
      {
        partNr = luaL_checknumber(L, 1);
      }
      else
      {
        int partCount = get_part_count();
        partNr = get_active_partition()+1;
        if( partNr > partCount ) partNr = 1;
      }
      lua_pushboolean(L, swap_partitions(partNr));
      return 1;
    }
    return 0;
}

static int luaCB_get_av96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_av96() );
  return 1;
}

static int luaCB_get_bv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_bv96() );
  return 1;
}

static int luaCB_get_day_seconds( lua_State* L )
{
    struct tm *ttm;
    ttm = get_localtime();
    lua_pushnumber( L, ttm->tm_hour * 3600 + ttm->tm_min * 60 + ttm->tm_sec );
    return 1;
}

static int luaCB_get_disk_size( lua_State* L )
{
  lua_pushnumber( L, GetTotalCardSpaceKb() );
  return 1;
}

static int luaCB_get_dofinfo( lua_State* L )
{
  shooting_update_dof_values();
  lua_createtable(L, 0, 12);
  SET_BOOL_FIELD("hyp_valid", (dof_values.hyperfocal_valid!=0));
  SET_BOOL_FIELD("focus_valid", (dof_values.distance_valid!=0));
  SET_INT_FIELD("aperture", dof_values.aperture_value);
  SET_INT_FIELD("coc", circle_of_confusion);
  SET_INT_FIELD("focal_length", dof_values.focal_length);
  SET_INT_FIELD("eff_focal_length", get_effective_focal_length(lens_get_zoom_point()));
  SET_INT_FIELD("focus", dof_values.subject_distance);
  SET_INT_FIELD("near", dof_values.near_limit);
  SET_INT_FIELD("far", dof_values.far_limit);
  SET_INT_FIELD("hyp_dist", dof_values.hyperfocal_distance);
  SET_INT_FIELD("dof", dof_values.depth_of_field);
  SET_INT_FIELD("min_stack_dist", dof_values.min_stack_distance);
  return 1;
}

static int luaCB_get_free_disk_space( lua_State* L )
{
  lua_pushnumber( L, GetFreeCardSpaceKb() );
  return 1;
}

static int luaCB_get_focus( lua_State* L )
{
  lua_pushnumber( L, shooting_get_subject_distance() );
  return 1;
}

static int luaCB_get_iso_market( lua_State* L )
{
  lua_pushnumber( L, shooting_get_iso_market() );
  return 1;
}

static int luaCB_get_iso_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_iso_mode() );
  return 1;
}

static int luaCB_get_iso_real( lua_State* L )
{
  lua_pushnumber( L, shooting_get_iso_real() );
  return 1;
}

static int luaCB_get_jpg_count( lua_State* L )
{
  lua_pushnumber( L, GetJpgCount() );
  return 1;
}

/*
val=get_prop(id)
get propcase value identified by id
the propcase is read as a short and sign extended to an int
*/
static int luaCB_get_prop( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop( luaL_checknumber( L, 1 ) ) );
  return 1;
}

/*
val=get_prop_str(prop_id,length)
get the value of a propertycase as a string
numeric values may be extracted using string.byte or or the binstr.lua module
returns the value as a string, or false if the underlying propcase call returned non-zero
*/
static int luaCB_get_prop_str( lua_State* L ) {
    void *buf;
    unsigned size;
    unsigned prop_id = luaL_checknumber( L, 1 );
    size = luaL_checknumber( L, 2 );
    buf = malloc(size);
    if(!buf) {
        return luaL_error( L, "malloc failed in luaCB_get_prop" );
    }
    if(get_property_case(prop_id,buf,size) == 0) {
        lua_pushlstring( L, buf, size );
    } else {
        lua_pushboolean( L, 0);
    }
    free(buf);
    return 1;
}

static int luaCB_get_raw_count( lua_State* L )
{
  lua_pushnumber( L, GetRawCount() );
  return 1;
}

static int luaCB_get_sv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_sv96_real() );
  return 1;
}

static int luaCB_get_tick_count( lua_State* L )
{
  lua_pushnumber( L, get_tick_count() );
  return 1;
}

static int luaCB_get_exp_count( lua_State* L )
{
  lua_pushnumber( L, get_exposure_counter() );
  return 1;
}

static int luaCB_get_image_dir( lua_State* L )
{
  char dir[32];
  get_target_dir_name(dir);
  lua_pushstring( L, dir );
  return 1;
}

static int luaCB_get_tv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_tv96() );
  return 1;
}

static int luaCB_get_user_av_id( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_av_id() );
  return 1;
}

static int luaCB_get_user_av96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_av96() );
  return 1;
}

static int luaCB_get_user_tv_id( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_tv_id() );
  return 1;
}

static int luaCB_get_user_tv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_tv96() );
  return 1;
}

static int luaCB_get_vbatt( lua_State* L )
{
  lua_pushnumber( L, stat_get_vbatt() );
  return 1;
}

static int luaCB_get_zoom( lua_State* L )
{
  lua_pushnumber( L, shooting_get_zoom() );
  return 1;
}

static int luaCB_get_parameter_data( lua_State* L )
{
  unsigned size;
  unsigned id = luaL_checknumber( L, 1 );
  unsigned val;

  size = get_parameter_size(id);
  if (size == 0) {
    // return nil
    return 0;
  }
  if (size >= 1 && size <= 4) {
    val = 0;
    get_parameter_data( id, &val, size );
    lua_pushlstring( L, (char *)&val, size );
    // for convenience, params that fit in a number are returned in one as a second result
    lua_pushnumber( L, val );
    return 2;
  }
  else {
    char *buf = malloc(size);
    if(!buf) {
      luaL_error( L, "malloc failed in luaCB_get_parameter_data" );
    }
    get_parameter_data( id, buf, size );
    lua_pushlstring( L, buf, size );
    free(buf);
    return 1;
  }
}

static int luaCB_get_flash_params_count( lua_State* L )
{
  lua_pushnumber( L, get_flash_params_count() );
  return 1;
}

static int luaCB_set_av96_direct( lua_State* L )
{
  shooting_set_av96_direct( luaL_checknumber( L, 1 ), shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

static int luaCB_set_av96( lua_State* L )
{
  shooting_set_av96( luaL_checknumber( L, 1 ), shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

static int luaCB_set_focus_interlock_bypass( lua_State* L )
{
    int mode = luaL_checknumber( L, 1 );

    set_focus_bypass(mode) ;

    return 0;
}

static int luaCB_set_focus( lua_State* L )
{
    int to = luaL_checknumber( L, 1 );

    if (camera_info.cam_has_manual_focus)
    {
        if (shooting_get_focus_mode() || camera_info.state.mode_video) shooting_set_focus(to, SET_NOW);
        else shooting_set_focus(to, SET_LATER);
    }
    else
    {
        if (shooting_get_common_focus_mode() || camera_info.state.mode_video) shooting_set_focus(to, SET_NOW);
        else shooting_set_focus(to, SET_LATER);    
    }
  return 0;
}

static int luaCB_set_iso_mode( lua_State* L )
{
  shooting_set_iso_mode( luaL_checknumber( L, 1 ) );
  return 0;
}

static int luaCB_set_iso_real( lua_State* L )
{
  shooting_set_iso_real( luaL_checknumber( L, 1 ),  shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

static int luaCB_set_led( lua_State* L )
{
  int to, to1, to2;
  to = luaL_checknumber( L, 1 );
  to1 = luaL_checknumber( L, 2 );
  to2 = 200;
  if( lua_isnumber( L, 3 ) )
    to2 = lua_tonumber( L, 3 );
  camera_set_led(to, to1, to2);
  return 0;
}

static int luaCB_set_nd_filter( lua_State* L )
{
  shooting_set_nd_filter_state( luaL_checknumber( L, 1 ), shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

/*
set_prop(id,value)
the value is treated as a short
*/
static int luaCB_set_prop( lua_State* L )
{
  shooting_set_prop(luaL_checknumber( L, 1 ), luaL_checknumber( L, 2 ));
  return 0;
}

/*
status=set_prop_str(prop_id,value)
set propertycase value as a string. Length is taken from the string
numeric propcase values may be assembled by setting byte values using string.char or the binstr module
status: boolean - true if the underlying propcase call returns 0, otherwise false
*/
static int luaCB_set_prop_str( lua_State *L ) {
    int prop_id;
    unsigned len;
    const char *str;
    prop_id = luaL_checknumber( L, 1 );
    str = luaL_checklstring( L, 2, &len );
    if(str && len > 0) {
        lua_pushboolean( L, (set_property_case(prop_id,(void *)str,len) == 0));
    } else {
        return luaL_error( L, "invalid value");
    }
    return 1;
}

static int luaCB_set_raw_nr( lua_State* L )
{
  conf.raw_nr = luaL_checknumber( L, 1 );
  return 0;
}

static int luaCB_get_raw_nr( lua_State* L )
{
  lua_pushnumber( L, conf.raw_nr );
  return 1;
}

static int luaCB_set_raw( lua_State* L )
{
  conf.save_raw = luaL_checknumber( L, 1 );
  return 0;
}

static int luaCB_get_raw( lua_State* L )
{
  lua_pushnumber( L, conf.save_raw );
  return 1;
}

static int luaCB_set_sv96( lua_State* L )
{
  shooting_set_sv96(luaL_checknumber( L, 1 ), shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

static int luaCB_set_tv96_direct( lua_State* L )
{
  shooting_set_tv96_direct(luaL_checknumber( L, 1 ), shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

static int luaCB_set_tv96( lua_State* L )
{
  shooting_set_tv96(luaL_checknumber( L, 1 ), shooting_in_progress()?SET_NOW:SET_LATER );
  return 0;
}

static int luaCB_set_user_av_by_id_rel( lua_State* L )
{
  shooting_set_user_av_by_id_rel(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_av_by_id( lua_State* L )
{
  shooting_set_user_av_by_id(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_av96( lua_State* L )
{
  shooting_set_user_av96(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_tv_by_id_rel( lua_State* L )
{
  shooting_set_user_tv_by_id_rel(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_tv_by_id( lua_State* L )
{
  shooting_set_user_tv_by_id(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_tv96( lua_State* L )
{
  shooting_set_user_tv96(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_zoom_speed( lua_State* L )
{
  shooting_set_zoom_speed(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_zoom_rel( lua_State* L )
{
  shooting_set_zoom_rel(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_zoom( lua_State* L )
{
  shooting_set_zoom(luaL_checknumber( L, 1 ));
  return 0;
}

// Wait for a button to be pressed and released (or the timeout to expire)
static int action_stack_AS_LUA_WAIT_CLICK()
{
    // Check key pressed or timeout
    if ((get_tick_count() >= action_top(2)) || camera_info.state.kbd_last_clicked)
    {
        // If timed out set key state to "no_key", otherwise key pressed so set last checked time
        if (!camera_info.state.kbd_last_clicked)
            camera_info.state.kbd_last_clicked=0xFFFF;
        else
            camera_info.state.kbd_last_checked_time = camera_info.state.kbd_last_clicked_time;

        action_pop_func(1);
        return 1;
    }

    return 0;
}

static int luaCB_wait_click( lua_State* L )
{
    int delay = luaL_optnumber( L, 1, 0 );
    if (delay == 0) delay = -1;
    delay = sleep_delay(delay);

    // Reset 'clicked' key if it has not changed since last time
    if (camera_info.state.kbd_last_clicked_time <= camera_info.state.kbd_last_checked_time)
    {
        camera_info.state.kbd_last_clicked = 0;
    }

    // Set up for wait or click testing
    action_push(delay);
    action_push_func(action_stack_AS_LUA_WAIT_CLICK);

    // Check for short delay or key already pressed by calling action stack routine once now
    if (action_stack_AS_LUA_WAIT_CLICK() == 0)
    {
        return lua_yield( L, 0 );
    }

    return 0;
}

static int luaCB_is_pressed( lua_State* L )
{
  lua_pushboolean( L, script_key_is_pressed(lua_get_key_arg( L, 1 )));
  return 1;
}

static int luaCB_is_key( lua_State* L )
{
  lua_pushboolean( L, script_key_is_clicked(lua_get_key_arg( L, 1 )));
  return 1;
}

static int luaCB_set_exit_key( lua_State* L )
{
  // TODO can't check if valid for this camera
  script_set_terminate_key(lua_get_key_arg( L, 1 ),luaL_checkstring( L, 1));
  return 0;
}

static int luaCB_wheel_right( lua_State* L )
{
  JogDial_CW();
  return 0;
}

static int luaCB_wheel_left( lua_State* L )
{
  JogDial_CCW();
  return 0;
}

static int luaCB_md_af_led_control( lua_State* L )
{
    camera_info.perf.md_af_on_delay = luaL_checknumber( L, 1 );
    camera_info.perf.md_af_on_time = luaL_checknumber( L, 2 );
    if ((camera_info.perf.md_af_on_time > 0) && (camera_info.cam_af_led >= 0))
        camera_info.perf.md_af_tuning = 1;        // Enable MD testing with AF LED
    else
        camera_info.perf.md_af_tuning = 0;        // Disable MD testing
    return 0;
}

static int luaCB_md_get_cell_diff( lua_State* L )
{
    lua_pushnumber( L, libmotiondetect->md_get_cell_diff(luaL_checknumber(L,1), luaL_checknumber(L,2)));
    return 1;
}


static int luaCB_md_get_cell_val( lua_State* L )
{
    lua_pushnumber( L, libmotiondetect->md_get_cell_val(luaL_checknumber(L,1), luaL_checknumber(L,2)));
    return 1;
}

static int luaCB_md_detect_motion( lua_State* L )
{
    int columns = (luaL_optnumber(L,1,6));
    int rows = (luaL_optnumber(L,2,4));
    int pixel_measure_mode = (luaL_optnumber(L,3,1));
    int detection_timeout = (luaL_optnumber(L,4,10000));
    int measure_interval = (luaL_optnumber(L,5,7));
    int threshold = (luaL_optnumber(L,6,10));
    int draw_grid = (luaL_optnumber(L,7,1));
    // arg 8 is the return value in ubasic. We
    // ignore it here. - AUJ
    int clipping_region_mode = (luaL_optnumber(L,9,0));
    int clipping_region_column1 = (luaL_optnumber(L,10,0));
    int clipping_region_row1 = (luaL_optnumber(L,11,0));
    int clipping_region_column2 = (luaL_optnumber(L,12,0));
    int clipping_region_row2 = (luaL_optnumber(L,13,0));
    int parameters = (luaL_optnumber(L,14,1));
    int pixels_step = (luaL_optnumber(L,15,6));
    int msecs_before_trigger = (luaL_optnumber(L,16,0));

    if (libmotiondetect->md_init_motion_detector(
        columns, rows, pixel_measure_mode, detection_timeout, 
        measure_interval, threshold, draw_grid,
        clipping_region_mode,
        clipping_region_column1, clipping_region_row1,
        clipping_region_column2, clipping_region_row2,
        parameters, pixels_step, msecs_before_trigger
        ))
        return lua_yield(L, 0);
    else
        return luaL_error( L, "md_init_motion_detector failed" );
}

static void return_string_selected(const char *str) {
    // Reconnect button input to script - will also signal action stack
    // that file browser / textbox is finished and return last selected file
    // to script caller
    camera_info.state.state_kbd_script_run = SCRIPT_STATE_RAN;

    // Push selected file as script return value
	lua_pushstring( Lt, (str && str[0])? str : NULL );
}

static int action_stack_AS_WAIT_MODULE()
{
    // state_kbd_script_run is set to 0 when the file browser is started from a Lua script
    // it is reset back to 1 when the file browser exits and control is returned back to
    // the script
    if (camera_info.state.state_kbd_script_run)
    {
        action_pop_func(0);
    }
    return 0;
}

static int luaCB_file_browser( lua_State* L ) {
    // Disconnect button input from script so buttons will work in file browser
    camera_info.state.state_kbd_script_run = SCRIPT_STATE_INACTIVE;
    // Push file browser action onto stack - will loop doing nothing until file browser exits
    action_push_func(action_stack_AS_WAIT_MODULE);
    // Switch to file browser gui mode. Path can be supplied in call or defaults to "A" (root directory).
    libfselect->file_select(LANG_STR_FILE_BROWSER, luaL_optstring( L, 1, "A" ), "A", return_string_selected);
    // Yield the script so that the action stack will process the AS_FILE_BROWSER action
    return lua_yield(L, 0);
}

static int luaCB_textbox( lua_State* L ) {
    // Disconnect button input from script so buttons will work in the textbox
    camera_info.state.state_kbd_script_run = SCRIPT_STATE_INACTIVE;
    // Switch to textbox gui mode. Text box prompt should be passed as param.
    int rv = libtextbox->textbox_init((int)luaL_optstring( L, 1, "Text box" ),   //title
        (int)luaL_optstring( L, 2, "Enter text" ), //message
        luaL_optstring( L, 3, ""  ),               //default string
        luaL_optnumber( L, 4, 30),                 //max size of a text
        return_string_selected, 0);
    if (rv)
    {
        // Push textbox action onto stack - will loop doing nothing until textbox exits
        action_push_func(action_stack_AS_WAIT_MODULE);
    }
    else
        return_string_selected(0);

    // Yield the script so that the action stack will process the AS_TEXTBOX action
    return lua_yield(L, 0);
}

// begin lua draw fuctions
static int get_color(int cl) {
    char out=0;                     //defaults to 0 if any wrong number

    if (cl<256)
        out=cl;
    else {
        if (cl-256<sizeof(script_colors)) {
            if(camera_info.state.mode_rec)
                out=script_colors[cl-256][1];
            else
                out=script_colors[cl-256][0];
        }
    }
    return out;
}

static int luaCB_draw_pixel( lua_State* L ) {
  coord x1=luaL_checknumber(L,1);
  coord y1=luaL_checknumber(L,2);
  color cl=get_color(luaL_checknumber(L,3));
  draw_pixel(x1,y1,cl);
  return 0;
}

static int luaCB_draw_line( lua_State* L ) {
  coord x1=luaL_checknumber(L,1);
  coord y1=luaL_checknumber(L,2);
  coord x2=luaL_checknumber(L,3);
  coord y2=luaL_checknumber(L,4);
  color cl=get_color(luaL_checknumber(L,5));
  draw_line(x1,y1,x2,y2,cl);
  return 0;
}

static int luaCB_draw_rect( lua_State* L ) {
  coord x1=luaL_checknumber(L,1);
  coord y1=luaL_checknumber(L,2);
  coord x2=luaL_checknumber(L,3);
  coord y2=luaL_checknumber(L,4);
  color cl=get_color(luaL_checknumber(L,5));
  int   th=luaL_optnumber(L,6,1);
  draw_rect_thick(x1,y1,x2,y2,cl,th);
  return 0;
}

static int luaCB_draw_rect_filled( lua_State* L ) {
  coord x1 =luaL_checknumber(L,1);
  coord y1 =luaL_checknumber(L,2);
  coord x2 =luaL_checknumber(L,3);
  coord y2 =luaL_checknumber(L,4);
  color clf=get_color(luaL_checknumber(L,5));
  color clb=get_color(luaL_checknumber(L,6));
  int   th =luaL_optnumber(L,7,1);
  clf=256*clb+clf;
  draw_filled_rect_thick(x1,y1,x2,y2,clf,th);
  return 0;
}

static int luaCB_draw_ellipse( lua_State* L ) {
  coord x1=luaL_checknumber(L,1);
  coord y1=luaL_checknumber(L,2);
  coord a=luaL_checknumber(L,3);
  coord b=luaL_checknumber(L,4);
  color cl=get_color(luaL_checknumber(L,5));
  draw_ellipse(x1,y1,a,b,cl);
  return 0;
}

static int luaCB_draw_ellipse_filled( lua_State* L ) {
  coord x1=luaL_checknumber(L,1);
  coord y1=luaL_checknumber(L,2);
  coord a=luaL_checknumber(L,3);
  coord b=luaL_checknumber(L,4);
  color cl=256*get_color(luaL_checknumber(L,5));
  draw_filled_ellipse(x1,y1,a,b,cl);
  return 0;
}

static int luaCB_draw_string( lua_State* L )
{
  coord x1 = luaL_checknumber(L,1);
  coord y1 = luaL_checknumber(L,2);
  const char *t = luaL_checkstring( L, 3 );
  color clf = get_color(luaL_checknumber(L,4));
  color clb = get_color(luaL_checknumber(L,5));
  int xsize = luaL_optnumber(L,6,1);
  int ysize = luaL_optnumber(L,7,xsize);
  
  if ((xsize <= 1) && (ysize <= 1))
    draw_string(x1, y1, t, MAKE_COLOR(clb,clf));
  else
    draw_string_scaled(x1, y1, t, MAKE_COLOR(clb,clf), xsize, ysize);
  
  return 0;
}

static int luaCB_draw_clear( lua_State* L ) {
  draw_restore();
  return 0;
}
// end lua draw functions

// bitmap dimensions, size matches coordinates of draw functions
static int luaCB_get_gui_screen_width( lua_State* L )
{
    lua_pushnumber( L, camera_screen.width );
    return 1;
}

static int luaCB_get_gui_screen_height( lua_State* L )
{
    lua_pushnumber( L, camera_screen.height );
    return 1;
}

static int luaCB_autostarted( lua_State* L )
{
  lua_pushboolean( L, camera_info.state.auto_started );
  return 1;
}

static int luaCB_get_autostart( lua_State* L )
{
  lua_pushnumber( L, conf.script_startup );
  return 1;
}

static int luaCB_set_autostart( lua_State* L )
{
  int to;
  to = luaL_checknumber( L, 1 );
  if ( to >= 0 && to <= 3 ) conf.script_startup = to;
  conf_save();
  return 0;
}

static int luaCB_get_usb_power( lua_State* L )
{
  lua_pushnumber( L, get_usb_power(luaL_optnumber( L, 1, 0 )) );
  return 1;
}

static int luaCB_enter_alt( lua_State* L )
{
  enter_alt();
  // if alt explicitly changed by script, set as 'saved' state
  if(lua_script_is_ptp) {
      ptp_saved_alt_state = 1;
  }
  return 0;
}

static int luaCB_exit_alt( lua_State* L )
{
  exit_alt();
  // if alt explicitly changed by script, set as 'saved' state
  if(lua_script_is_ptp) {
      ptp_saved_alt_state = 0;
  }
  return 0;
}

// optional parameter is 0 for soft shutdown (default) or 1 for hard/immediate
static int luaCB_shut_down( lua_State* L )
{
  if ( luaL_optnumber(L,1,0) == 1 )
  {
    shutdown();
  } else {
  camera_shutdown_in_a_second();
  }
  return 0;
}

static int luaCB_print_screen( lua_State* L )
{
  
  if (lua_isboolean( L, 1 ))
    script_print_screen_statement( lua_toboolean( L, 1 ) );
  else
    script_print_screen_statement( luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_get_movie_status( lua_State* L )
{
  lua_pushnumber( L, movie_status );
  return 1;
}

static int luaCB_set_movie_status( lua_State* L )
{
  switch(luaL_checknumber( L, 1 )) {
    case 1:
      if (movie_status == 4) {
        movie_status = 1;
      }
    break;
    case 2:
      if (movie_status == 1) {
        movie_status = 4;
      }
    break;
    case 3:
      if (movie_status == 1 || movie_status == 4) {
        movie_status = 5;
      }
    break;
  }
  return 0;
}

static int luaCB_get_video_button( lua_State* L )
{
  int to = (camera_info.cam_has_video_button) ? 1 : 0;
  lua_pushnumber( L, to );
  return 1;
}

static int luaCB_get_drive_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_drive_mode() );
  return 1;
}

static int luaCB_get_focus_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_real_focus_mode() );
  return 1;
}

static int luaCB_get_focus_state( lua_State* L )
{
  lua_pushnumber( L, shooting_get_focus_state() );
  return 1;
}

static int luaCB_get_focus_ok( lua_State* L )
{
  lua_pushnumber( L, shooting_get_focus_ok() );
  return 1;
}

static int luaCB_get_flash_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_flash_mode() );
  return 1;
}

static int luaCB_get_shooting( lua_State* L )
{
  lua_pushboolean( L, shooting_in_progress() );
  return 1;
}

static int luaCB_get_flash_ready( lua_State* L )
{
  lua_pushboolean( L, shooting_is_flash() );
  return 1;
}

static int luaCB_get_IS_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_is_mode() );
  return 1;
}

static int luaCB_get_orientation_sensor( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(camera_info.props.orientation_sensor) );
  return 1;
}

static int luaCB_get_zoom_steps( lua_State* L )
{
  lua_pushnumber( L, zoom_points );
  return 1;
}

static int luaCB_get_nd_present( lua_State* L )
{
  int to;
  if (camera_info.cam_has_nd_filter == 0)
  {
    to = 0;
  }
  else
  {
    if (camera_info.cam_has_iris_diaphragm == 0)
      to = 1;
    else
      to = 2;
  }
  lua_pushnumber( L, to );
  return 1;
}

static int luaCB_get_propset( lua_State* L )
{
  lua_pushnumber( L, camera_info.props.propset );
  return 1;
}

static int luaCB_get_ev( lua_State* L )
{
  lua_pushnumber( L, shooting_get_ev_correction1() );
  return 1;
}

static int luaCB_set_ev( lua_State* L )
{
  int to;
  to = luaL_checknumber( L, 1 );
  shooting_set_prop(camera_info.props.ev_correction_1, to);
  shooting_set_prop(camera_info.props.ev_correction_2, to);
  return 0;
}

static int luaCB_get_histo_range( lua_State* L )
{
  int from = (luaL_checknumber(L,1));
  int to = (luaL_checknumber(L,2));
  if (shot_histogram_isenabled()) lua_pushnumber( L, shot_histogram_get_range(from, to) );
  else lua_pushnumber( L, -1 ); // TODO should probably return nil 
  return 1;
}

static int luaCB_shot_histo_enable( lua_State* L )
{
  shot_histogram_set(luaL_checknumber( L, 1 ));
  return 0;
}

/*
histogram,total=get_live_histo()
returns a histogram of Y values from the viewport buffer (downsampled by HISTO_STEP_SIZE)
histogram[Y value] = count, so it is zero based unlike a normal lua array
total is the total number of pixels, may vary depending on viewport size
*/
static int luaCB_get_live_histo( lua_State* L )
{
  unsigned short *h = malloc(256*sizeof(short));
  if(!h) {
      return luaL_error(L,"malloc fail");
  }
  int total=live_histogram_read_y(h);
  lua_createtable(L, 0, 256);
  int i;
  for(i=0;i<256;i++) {
    lua_pushnumber(L,h[i]);
    lua_rawseti(L,-2,i);
  }
  free(h);
  lua_pushnumber(L,total);
  return 2;
}

static int luaCB_play_sound( lua_State* L )
{
  play_sound(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_get_temperature( lua_State* L )
{
  int which = (luaL_checknumber( L, 1 ));
  int temp = -100; // do something insane if users passes bad value
  switch (which)
  {
    case 0:
      temp = get_optical_temp(); 
      break;
    case 1:
      temp = get_ccd_temp(); 
      break;
    case 2:
      temp = get_battery_temp();
      break;
  }
  lua_pushnumber( L, temp );
  return 1;
}

static int luaCB_get_time( lua_State* L )
{
  int r = -1;
  static struct tm *ttm;
  ttm = get_localtime();
  const char *t = luaL_checkstring( L, 1 );
  if (strncmp("s", t, 1)==0) r = ( L, ttm->tm_sec );
  else if (strncmp("m", t, 1)==0) r = ( L, ttm->tm_min );
  else if (strncmp("h", t, 1)==0) r = ( L, ttm->tm_hour );
  else if (strncmp("D", t, 1)==0) r = ( L, ttm->tm_mday );
  else if (strncmp("M", t, 1)==0) r = ( L, ttm->tm_mon+1 );
  else if (strncmp("Y", t, 1)==0) r = ( L, 1900+ttm->tm_year );
  lua_pushnumber( L, r );
  return 1;
}
/*
  val=peek(address[,size])
  return the value found at address in memory, or nil if address or size is invalid
  size is optional 1=byte 2=halfword 4=word. defaults is 4
*/
static int luaCB_peek( lua_State* L )
{
  unsigned addr = luaL_checknumber(L,1);
  unsigned size = luaL_optnumber(L, 2, 4);
  switch(size) {
    case 1: 
      lua_pushnumber( L, *(unsigned char *)(addr) );
    break;
    case 2:
      if (addr & 0x1) {
        lua_pushnil(L);
      }
      else {
        lua_pushnumber( L, *(unsigned short *)(addr) );
      }
    break;
    case 4:
      if (addr & 0x3) {
        lua_pushnil(L);
      }
      else {
        lua_pushnumber( L, *(unsigned *)(addr) );
      }
    break;
    default:
      lua_pushnil(L);

  }
  return 1;
}

/*
  status=poke(address,value[,size])
  writes value to address in memory
  size is optional 1=byte 2=halfword 4=word. defaults is 4
  returns true, or nil if address or size is invalid
*/
static int luaCB_poke( lua_State* L )
{
  unsigned addr = luaL_checknumber(L,1);
  unsigned val = luaL_checknumber(L,2);
  unsigned size = luaL_optnumber(L, 3, 4);
  int status = 0;
  switch(size) {
    case 1: 
        *(unsigned char *)(addr) = (unsigned char)val;
        status=1;
    break;
    case 2:
      if (!(addr & 0x1)) {
        *(unsigned short *)(addr) = (unsigned short)val;
        status=1;
      }
    break;
    case 4:
      if (!(addr & 0x3)) {
        *(unsigned *)(addr) = val;
        status=1;
      }
    break;
  }
  if(status) {
    lua_pushboolean(L,1);
  }
  else {
    lua_pushnil(L);
  }
  return 1;
}

static int luaCB_bitand( lua_State* L )
{
  int v1 = (luaL_checknumber(L,1));
  int v2 = (luaL_checknumber(L,2));
  lua_pushnumber( L, v1 & v2 );
  return 1;
}

static int luaCB_bitor( lua_State* L )
{
  int v1 = (luaL_checknumber(L,1));
  int v2 = (luaL_checknumber(L,2));
  lua_pushnumber( L, v1 | v2 );
  return 1;
}

static int luaCB_bitxor( lua_State* L )
{
  int v1 = (luaL_checknumber(L,1));
  int v2 = (luaL_checknumber(L,2));
  lua_pushnumber( L, v1 ^ v2 );
  return 1;
}

static int luaCB_bitshl( lua_State* L )
{
  int val = (luaL_checknumber(L,1));
  unsigned shift = (luaL_checknumber(L,2));
  lua_pushnumber( L, val << shift );
  return 1;
}

static int luaCB_bitshri( lua_State* L )
{
  int val = (luaL_checknumber(L,1));
  unsigned shift = (luaL_checknumber(L,2));
  lua_pushnumber( L, val >> shift );
  return 1;
}

static int luaCB_bitshru( lua_State* L )
{
  unsigned val = (luaL_checknumber(L,1));
  unsigned shift = (luaL_checknumber(L,2));
  lua_pushnumber( L, val >> shift );
  return 1;
}

static int luaCB_bitnot( lua_State* L )
{
  unsigned val = (luaL_checknumber(L,1));
  lua_pushnumber( L, ~val );
  return 1;
}

static void set_string_field(lua_State* L, const char *key, const char *val)
{
  lua_pushstring(L, val);
  lua_setfield(L, -2, key);
}

static void set_number_field(lua_State* L, const char *key, int val)
{
  lua_pushnumber(L, val);
  lua_setfield(L, -2, key);
}

static int luaCB_get_buildinfo( lua_State* L )
{
  lua_createtable(L, 0, 9);
  set_string_field( L,"platform", camera_info.platform );
  set_string_field( L,"platsub", camera_info.platformsub );
  set_string_field( L,"version", camera_info.chdk_ver );
  set_string_field( L,"build_number", camera_info.build_number );
  set_string_field( L,"build_revision", camera_info.build_svnrev );
  set_string_field( L,"build_date", camera_info.build_date );
  set_string_field( L,"build_time", camera_info.build_time );
  set_string_field( L,"os", camera_info.os );
  set_number_field( L,"platformid", conf.platformid );
  return 1;
}

static int luaCB_get_mode( lua_State* L )
{
  lua_pushboolean( L, !camera_info.state.mode_play );
  lua_pushboolean( L, camera_info.state.mode_video );
  lua_pushnumber( L, camera_info.state.mode );
  return 3;
}

// TODO sanity check file ?
static int luaCB_set_raw_develop( lua_State* L )
{
  raw_prepare_develop(luaL_optstring( L, 1, NULL ), 0);
  return 0;
}

static int luaCB_raw_merge_start( lua_State* L )
{
    int op = luaL_checknumber(L,1);
    if ((op == RAW_OPERATION_SUM || op == RAW_OPERATION_AVERAGE))
    {
        lua_pushboolean(L, librawop->raw_merge_start(op));   
        return 1;
    }
    else {
        return luaL_argerror(L,1,"invalid raw merge op");
    }
}

// TODO sanity check file ? Get it from C
static int luaCB_raw_merge_add_file( lua_State* L )
{
    lua_pushboolean(L, librawop->raw_merge_add_file(luaL_checkstring( L, 1 )));
    return 1;
}

static int luaCB_raw_merge_end( lua_State* L )
{
    librawop->raw_merge_end();
    return 0;
}

// Enable/disable LCD back light (input argument 1/0)
static int luaCB_set_backlight( lua_State* L )
{
  int val = (luaL_checknumber(L,1));

  if (val > 0) TurnOnBackLight();
  else TurnOffBackLight();
  return 0;
}

// Enable/disable LCD display (input argument 1/0)
static int luaCB_set_lcd_display( lua_State* L )
{
  int val = (luaL_checknumber(L,1));

  if (val > 0) TurnOnDisplay();
  else TurnOffDisplay();
  return 0;
}

// Enable/disable CHDK <ALT> & scriptname OSD items (input argument 1/0)
static int luaCB_set_draw_title_line( lua_State* L )
{
  camera_info.state.osd_title_line= on_off_value_from_lua_arg(L,1);
  return 0;
}

// get CHDK <ALT> & scriptname OSD display state (input argument 1/0)
static int luaCB_get_draw_title_line( lua_State* L )
{
   lua_pushboolean( L, camera_info.state.osd_title_line  );
   return 1;
}

// get the string or number passed in index and return it as an event id
static unsigned levent_id_from_lua_arg( lua_State* L, int index)
{
  unsigned event_id;
  if (lua_type(L, index) == LUA_TSTRING) {
    const char *ev_name = lua_tostring(L, index);
  	event_id = levent_id_for_name(ev_name);
    if (event_id == 0) {
        return luaL_error( L, "bad event name '%s'", ev_name );
    }
  }
  // could check here if it is in the table, but even valid ones can crash
  // so we avoid searching the table if given a number
  else if (lua_type(L,index) == LUA_TNUMBER){
  	event_id = lua_tonumber(L,index);
  }
  else {
    return luaL_error( L, "expected event name or id" );
  }
  return event_id;
}


/*
  return the index of an event, given it's name or event id
*/
static unsigned levent_index_from_id_lua_arg( lua_State* L, int index )
{
  if (lua_type(L, index) == LUA_TSTRING) {
  	return levent_index_for_name(lua_tostring(L, index));
  }
  else if (lua_type(L,index) == LUA_TNUMBER){
  	return levent_index_for_id(lua_tonumber(L,index));
  }
  else {
    return luaL_error( L, "expected string or number" );
  }
}

/*
  name,id,param = get_levent_def(event)
  event is an event id (number) or name (string)
  returns nil if event is not found
*/
static int luaCB_get_levent_def( lua_State* L )
{
  unsigned event_index = levent_index_from_id_lua_arg(L,1);
  if (event_index == LEVENT_INVALID_INDEX) {
    lua_pushnil(L);
    return 1;
  }
  lua_pushstring(L, levent_table[event_index].name);
  lua_pushnumber(L, levent_table[event_index].id);
  lua_pushnumber(L, levent_table[event_index].param);
  return 3;
}

/*
  index=get_levent_index(event)
  event is an event id (number) or name (string)
  returns index or nil if not found
*/
static int luaCB_get_levent_index( lua_State* L )
{
  unsigned event_index = levent_index_from_id_lua_arg(L,1);
  if (event_index == LEVENT_INVALID_INDEX) {
    lua_pushnil(L);
  }
  else {
    lua_pushnumber(L, event_index);
  }
  return 1;
}

/*
  name,id,param = get_levent_def_by_index(event_index)
  event_index is number index into the event table
  returns nil if event is not found
*/
static int luaCB_get_levent_def_by_index( lua_State* L )
{
  unsigned i = luaL_checknumber(L,1);
  if(i >= levent_count()) {
  	lua_pushnil(L);
    return 1;
  }
  lua_pushstring(L, levent_table[i].name);
  lua_pushnumber(L, levent_table[i].id);
  lua_pushnumber(L, levent_table[i].param);
  return 3;
}

/*
  post_levent_*(event[,unk])
  post the event with PostLogicalEventToUI or PostLogicaEventForNotPowerType
  This sends the event. The difference between functions isn't clear.
  event is an event id (number) or name (string).
  unk is an optional number whose meaning is unknown, defaults to zero. 
    Based on code, other values would probably be a pointer.
	This is NOT the 3rd item in the event table.
*/
static int luaCB_post_levent_to_ui( lua_State* L )
{
  unsigned event_id,arg;

  event_id = levent_id_from_lua_arg(L,1);
  arg = luaL_optnumber(L, 2, 0);
  PostLogicalEventToUI(event_id,arg);
  return 0;
}

static int luaCB_post_levent_for_npt( lua_State* L )
{
  unsigned event_id,arg;

  event_id = levent_id_from_lua_arg(L,1);
  arg = luaL_optnumber(L, 2, 0);
  PostLogicalEventForNotPowerType(event_id,arg);
  return 0;
}

/*
  set_levent_active(event,state)
  event is an event id (number) or name (string)
  state is a numeric or boolean state. true or non zero numbers turn on zero, false or nil turn off
  exact meaning is unknown, but it has something to do with the delivery of the specified event.
*/
static int luaCB_set_levent_active( lua_State* L )
{
  unsigned event_id;
  unsigned state;

  event_id = levent_id_from_lua_arg(L,1);
  state = on_off_value_from_lua_arg(L,2);
  SetLogicalEventActive(event_id,state);
  return 0;
}

/*
  set_levent_script_mode(state)
  state is numeric or boolean state. true or non zero numbers turn on zero, false or nil turn off
  exact meaning is unknown, but it has something to do with the behavior of events and/or SetLogicalEventActive.
*/
static int luaCB_set_levent_script_mode( lua_State* L )
{
  SetScriptMode(on_off_value_from_lua_arg(L,1));
  return 0;
}

/* 
  result=set_capture_mode_canon(value)
  where value is a valid PROPCASE_SHOOTING_MODE value for the current camera
  result is true if the camera is in rec mode
*/
static int luaCB_set_capture_mode_canon( lua_State* L )
{
  int modenum = luaL_checknumber(L,1);
  // if the value as negative, assume it is a mistakenly sign extended PROPCASE_SHOOTING_MODE value
  if(modenum < 0) 
    modenum &= 0xFFFF;
  lua_pushboolean( L, shooting_set_mode_canon(modenum) );
  return 1;
}

/*
 result=set_capture_mode(modenum)
 where modenum is a valid CHDK modemap value
 result is true if modenum is a valid modemap value, otherwise false
*/
static int luaCB_set_capture_mode( lua_State* L )
{
  int modenum = luaL_checknumber(L,1);
  lua_pushboolean( L, shooting_set_mode_chdk(modenum) );
  return 1;
}

/*
 result=is_capture_mode_valid(modenum)
 where modenum is a valid CHDK modemap value
 result is true if modenum is a valid modemap value, otherwise false
*/
static int luaCB_is_capture_mode_valid( lua_State* L )
{
  int modenum = luaL_checknumber(L,1);
  lua_pushboolean( L, shooting_mode_chdk2canon(modenum) != -1 );
  return 1;
}

/* 
  set_record(state)
  if state is 0 (or false) the camera is set to play mode. If 1 or true, the camera is set to record mode.
  NOTE: this only begins the mode change. Script should wait until get_mode() reflects the change,
  before doing anything that requires the new mode. e.g.
  set_record(true)
  while not get_mode() do
  	sleep(10)
  end
  uses switch_mode_usb if required
*/
static int luaCB_set_record( lua_State* L )
{
  shooting_set_playrec_mode(on_off_value_from_lua_arg(L,1));
  return 0;
}

// switch mode (0 = playback, 1 = record)
// only for when USB is connected
static int luaCB_switch_mode_usb( lua_State* L )
{
  switch_mode_usb(luaL_checknumber(L,1));
  return 0;
}
 
/*
pack the lua args into a buffer to pass to the native code calling functions 
currently only handles strings/numbers
start is the stack index of the first arg
*/
static int pack_native_args( lua_State* L, unsigned start, unsigned *argbuf)
{
  unsigned i;
  unsigned end = lua_gettop(L);

  for(i = start; i <= end; i++,argbuf++) {
    if (lua_type(L, i) == LUA_TSTRING) {
        *argbuf=(unsigned)lua_tostring( L, i);
    }
    else if (lua_type(L, i) == LUA_TNUMBER) {
        *argbuf=lua_tonumber( L, i);
    }
    else {
      return 0;
    }
  }
  return 1;
}

/*
Native function call interface. Can be used to call canon eventprocs or arbitrary
pointers.

NOTE: this is preliminary, interface may change in later versions!
All arguments must be strings or numbers.
If the function expects to modify it's arguments via a pointer,
then you must provide a number that is a valid pointer. 

You can use the "AllocateMemory" eventproc to obtain buffers.

If the function tries to write to a string passed from lua, Bad Things may happen.

This is potentially dangerous, functions exist which can destroy the onboard firmware.
*/

/*
result=call_func_ptr(ptr,...)
ptr: address of a valid ARM or Thumb function, which uses the normal C calling convention.
result: R0 value after the call returns
*/
static int luaCB_call_func_ptr( lua_State* L)
{
    if (conf.script_allow_lua_native_calls)
    {
        unsigned *argbuf=NULL;
        unsigned n_args = lua_gettop(L)-1;
        void *fptr;

        fptr=(void *)luaL_checknumber( L, 1 );

        if (n_args)
        {
            argbuf=malloc(n_args * 4);
            if(!argbuf)
            {
                return luaL_error( L, "malloc fail" );
            }
            if(!pack_native_args(L, 2, argbuf))
            {
                free(argbuf);
                return luaL_error( L, "expected string or number" );
            }
        }
          
        lua_pushnumber( L, call_func_ptr(fptr, argbuf, n_args) );
        free(argbuf);
        return 1;
    }
    return luaL_error( L, "native calls disabled" );
}

/* 
Call an event procedure

result=call_event_proc("EventprocName",...)
result is the value returned by ExecuteEventProcedure, which is -1 if the eventproc is not found, 
or the eventproc return value (which could also be -1)
NOTE:
Many eventprocs are not registered by default, but can be loaded by calling another event proc
Some useful ones are
SystemEventInit
	includes AllocateMemory, FreeMemory, sprintf, memcpy, Fut functions, log ...
UI_RegistDebugEventProc
	includes capture mode functions, PTM_ functions and much more 
RegisterProductTestEvent
	includes PT_ functions

Others:
RegisterShootSeqEvent
RegisterNRTableEvent
*/

// grab from lowlevel
extern unsigned _ExecuteEventProcedure(const char *name,...);
static int luaCB_call_event_proc( lua_State* L )
{
    if (conf.script_allow_lua_native_calls)
    {
        const char *evpname;
        unsigned *argbuf;
        unsigned n_args = lua_gettop(L);

        evpname=luaL_checkstring( L, 1 );

        argbuf=malloc(n_args * 4);
        if (!argbuf)
        {
            return luaL_error( L, "malloc fail" );
        }

        // event proc name is first arg
        *argbuf = (unsigned)evpname;
  
        if(!pack_native_args(L,2,argbuf+1))
        {
            free(argbuf);
            return luaL_error( L, "expected string or number" );
        }
  
        lua_pushnumber( L, call_func_ptr(_ExecuteEventProcedure,argbuf,n_args) );
        free(argbuf);
        return 1;
    }
    return luaL_error( L, "native calls disabled" );
}

/*
result = reboot(["filename"])
returns false on failure, does not return on success
see lib/armutil/reboot.c for details
*/
static int luaCB_reboot( lua_State* L )
{
    lua_pushboolean(L, reboot(luaL_optstring( L, 1, NULL )));
    return 1;
}

static int luaCB_get_config_value( lua_State* L ) {
    unsigned int argc = lua_gettop(L);
    unsigned int id, i;
    int ret = 1;
    tConfigVal configVal;
    
    if( argc>=1 ) {
        id = luaL_checknumber(L, 1);
        switch( conf_getValue(id, &configVal) ) {
            case CONF_VALUE:
                lua_pushnumber(L, configVal.numb);
            break;
            case CONF_INT_PTR:
                lua_createtable(L, 0, configVal.numb);
                for( i=0; i<configVal.numb; i++ ) {
                    lua_pushinteger(L, configVal.pInt[i]);
                    lua_rawseti(L, -2, i+1);  //t[i+1]=configVal.pInt[i]
                }
            break;
            case CONF_CHAR_PTR:
                lua_pushstring(L, configVal.str);
            break;
            case CONF_OSD_POS:
                lua_pushnumber(L, configVal.pos.x);
                lua_pushnumber(L, configVal.pos.y); ret++;
            break;
            default:
                if( argc>=2) { //Default
                    ret = argc-1;
                } else {
                    lua_pushnil(L);
                }
            break;
        }
    } else {
        lua_pushnil(L);
    }
    return ret;
}

static int luaCB_set_config_value( lua_State* L ) {
    unsigned int argc = lua_gettop(L);
    unsigned int id, i, j;
    tConfigVal configVal = {0,0,0,0};  //initialize isXXX
    
    if( argc>=2 ) {
        id = luaL_checknumber(L, 1);
        for( i=2; i<=argc; i++) {
            switch( lua_type(L, i) ) {
                case LUA_TNUMBER:
                    if( !configVal.isNumb ) {
                        configVal.numb = luaL_checknumber(L, i);
                        configVal.isNumb++;
                    }
                    switch( configVal.isPos ) {
                        case 0: configVal.pos.x = luaL_checknumber(L, i); configVal.isPos++; break;
                        case 1: configVal.pos.y = luaL_checknumber(L, i); configVal.isPos++; break;
                    }
                break;
                case LUA_TSTRING:
                    if( !configVal.isStr ) {
                        configVal.str = (char*)luaL_checkstring(L, i);
                        configVal.isStr++;
                    }
                break;
                case LUA_TTABLE:
                    if( !configVal.isPInt ) {
                        configVal.numb = lua_objlen(L, i);
                        if( configVal.pInt ) {
                            free(configVal.pInt);
                            configVal.pInt = NULL;
                        }
                        configVal.pInt = malloc(configVal.numb*sizeof(int));
                        if( configVal.pInt ) {
                            for( j=1; j<=configVal.numb; j++) {
                                lua_rawgeti(L, i, j);
                                configVal.pInt[j-1] = lua_tointeger(L, -1);
                                lua_pop(L, 1);
                            }
                        }
                        configVal.isPInt++;
                    }
                break;
            }
        }
        lua_pushboolean(L, conf_setValue(id, configVal));
        if( configVal.pInt ) {
            free(configVal.pInt);
            configVal.pInt = NULL;
        }
    } else lua_pushboolean(L, 0);
    return 1;
}

static int luaCB_set_config_autosave( lua_State* L ) {
    conf_setAutosave(luaL_checknumber(L, 1));
    return 0;
}

static int luaCB_save_config_file( lua_State* L ) {
    lua_pushnumber(L, save_config_file(luaL_checknumber(L, 1), luaL_optstring(L, 2, NULL)));
    return 1;
}

static int luaCB_load_config_file( lua_State* L ) {
    lua_pushnumber(L, load_config_file(luaL_checknumber(L, 1), luaL_optstring(L, 2, NULL)));
    return 1;
}

static int luaCB_set_file_attributes( lua_State* L ) {
    unsigned int argc = lua_gettop(L);
    if( argc>=2 ) {
        lua_pushnumber(L, SetFileAttributes(luaL_checkstring(L, 1), luaL_checknumber(L, 2)));
    }
    return 1;
}

static int action_stack_AS_SCRIPT_READ_USB_MSG()
{
    ptp_script_msg *msg = ptp_script_read_msg();

    if ((get_tick_count() >= action_top(2)) || msg)
    {
        if (msg && msg->data)
        {
            lua_pushlstring(Lt,msg->data,msg->size);
        }
        else
        {
            lua_pushnil(Lt);
        }
        action_pop_func(1);
        return 1;
    }
    return 0;
}

static int action_stack_AS_SCRIPT_WRITE_USB_MSG()
{
    ptp_script_msg *msg = (ptp_script_msg *)action_top(2);

    int r = ptp_script_write_msg(msg);

    if ((get_tick_count() >= action_top(3)) || r)
    {
        lua_pushboolean(Lt,r);
        action_pop_func(2);
        return 1;
    }
    return 0;
}

/*
msg = read_usb_msg([timeout])
read a message from the CHDK ptp interface.
Returns the next available message as a string, or nil if no messages are available
If timeout is given and not zero, wait until a message is available or timeout expires
*/
static int luaCB_read_usb_msg( lua_State* L )
{
  int timeout = sleep_delay(luaL_optnumber(L,1,0));
  if (timeout > 0)
  {
    action_push(timeout);
    action_push_func(action_stack_AS_SCRIPT_READ_USB_MSG);
    return lua_yield( L, 0 );
  }
  ptp_script_msg *msg = ptp_script_read_msg();
  if(msg)
  {
    lua_pushlstring(L,msg->data,msg->size);
    free(msg);
    return 1;
  }
  lua_pushnil(L);
  return 1;
}

/*
status = write_usb_msg(msg,[timeout])
writes a message to the CHDK ptp interface
msg may be nil, boolean, number, string or table (table has some restrictions, will be converted to string)
returns true if the message was queued successfully, otherwise false
if timeout is set and not zero, wait until message is written or timeout expires
NOTE strings will not include a terminating NULL, must be handled by recipient
*/
static int luaCB_write_usb_msg( lua_State* L )
{
  ptp_script_msg *msg;
  int timeout = sleep_delay(luaL_optnumber(L,2,0));
  // TODO would it be better to either ignore this or return nil ?
  // a write_usb_msg(function_which_returns_no_value()) is an error in this case
  // replacing with nil might be more luaish
  if (lua_gettop(L) < 1)
  {
    return luaL_error(L,"missing argument");
  }
  msg=lua_create_usb_msg(L,1,PTP_CHDK_S_MSGTYPE_USER);
  // for user messages, trying to create a message from an incompatible type throws an error
  if (msg->subtype == PTP_CHDK_TYPE_UNSUPPORTED)
  {
    free(msg);
    return luaL_error(L,"unsupported type");
  }
  if (!msg)
  {
    return luaL_error(L,"failed to create message");
  }
  if (timeout)
  {
    action_push(timeout);
    action_push((int)msg);
    action_push_func(action_stack_AS_SCRIPT_WRITE_USB_MSG);
    return lua_yield( L, 0 );
  }
  lua_pushboolean(L,ptp_script_write_msg(msg)); 
  return 1;
}

/* helper for meminfo to set table field only if valid */
static void set_meminfo_num( lua_State* L,const char *name, int val) {
    if(val != -1) {
        set_number_field( L, name, val );
    }
}
/*
meminfo=get_meminfo([heapname])
get camera memory information
heapname="combined", "system", "aram" or "exmem" 
if not given, combined is returned
meminfo is false if the requested heapname isn't valid ("exmem" when exmem is not enabled, or unknown)
otherwise, a table of the form
meminfo = {
    name -- heapname, as above
    chdk_malloc -- bool, this is the heap used by CHDK for malloc
    chdk_start -- number, load address of CHDK
    chdk_size -- number, size of CHDK image
    -- all the following are numbers, will not be set if not available
    start_address
    end_address
    total_size
    allocated_size
    allocated_peak
    allocated_count
    free_size
    free_block_max_size
    free_block_count
}
NOTES
* under vxworks and cameras without GetMemInfo only the only valid fields
  for the system heap will be those defined by chdk and free_block_max_size
* the meaning of fields may not correspond exactly between exmem and system
*/
static int luaCB_get_meminfo( lua_State* L ) {
    // for memory info, duplicated from lowlevel
    extern const char _start;

    const char *heapname = luaL_optstring( L, 1, "combined" );
    cam_meminfo meminfo;
    if (strcmp(heapname,"combined") == 0) {
        GetCombinedMemInfo(&meminfo);
        meminfo.start_address=meminfo.end_address=-1; // not meaningful
    }
    else if (strcmp(heapname,"system") == 0)
    {
        GetMemInfo(&meminfo);
    }
    else if ((strcmp(heapname,"aram") == 0))
    {
        if(!GetARamInfo(&meminfo)) {
            lua_pushboolean(L,0);
            return 1;
        }
    }
    else if (strcmp(heapname,"exmem") == 0)
    {
        if(!GetExMemInfo(&meminfo)) {;
            lua_pushboolean(L,0);
            return 1;
        }
    }
    else
    {
        lua_pushboolean(L,0);
        return 1;
    }
    // adjust start and size, if CHDK is loaded at heap start
    if(meminfo.start_address == (int)(&_start)) {
        meminfo.start_address += camera_info.memisosize;
        meminfo.total_size -= camera_info.memisosize;
    }
    lua_createtable(L, 0, 13); // might not always use 13, but doesn't hurt
    set_string_field( L,"name", heapname );
    // CHDK allocates from all available heaps now
    lua_pushboolean( L, 1);
    lua_setfield(L, -2, "chdk_malloc");
    set_number_field( L, "chdk_start", (int)(&_start) );
    set_number_field( L, "chdk_size", camera_info.memisosize );
    set_meminfo_num( L, "start_address", meminfo.start_address );
    set_meminfo_num( L, "end_address", meminfo.end_address);
    set_meminfo_num( L, "total_size", meminfo.total_size);
    set_meminfo_num( L, "allocated_size", meminfo.allocated_size);
    set_meminfo_num( L, "allocated_peak", meminfo.allocated_peak);
    set_meminfo_num( L, "allocated_count", meminfo.allocated_count);
    set_meminfo_num( L, "free_size", meminfo.free_size);
    set_meminfo_num( L, "free_block_max_size", meminfo.free_block_max_size);
    set_meminfo_num( L, "free_block_count", meminfo.free_block_count);
    return 1;
}

/*
set scheduling parameters
old_max_count,old_max_ms=set_yield(max_count,max_ms)
*/
static int luaCB_set_yield( lua_State* L )
{
  lua_pushnumber(L,yield_max_count);
  lua_pushnumber(L,yield_max_ms);
  yield_max_count = luaL_optnumber(L,1,YIELD_MAX_COUNT_DEFAULT);
  yield_max_ms = luaL_optnumber(L,2,YIELD_MAX_MS_DEFAULT);
  return 2;
}

//static void register_func( lua_State* L, const char *name, void *func) {
//  lua_pushcfunction( L, func );
//  lua_setglobal( L, name );
//}
/*
get remote capture supported types
bitmask=get_usb_capture_support()
*/
static int luaCB_get_usb_capture_support( lua_State* L )
{
    lua_pushnumber(L,remotecap_get_target_support());
    return 1;
}

/*
status=init_usb_capture(bitmask[,startline, numlines])
bitmask = 0 clear usb capture mode

lines only applies to raw
startline defaults to 0
numlines defaults to full buffer
*/
static int luaCB_init_usb_capture( lua_State* L )
{
    int what=luaL_checknumber(L, 1);
    int startline=luaL_optnumber(L, 2, 0);
    int numlines=luaL_optnumber(L, 3, 0);
    lua_pushboolean(L,remotecap_set_target(what,startline,numlines));
    return 1;
}
/*
set_remotecap_timeout([timeout])
timeout:
number of milliseconds remote capture waits for data of each type to be downloaded
<=0 or no value resets to the default value
If any data type is not downloaded before the timeout expires, remote capture is canceled
and none of the subsequent data types will be returned
following a timeout, RemoteCaptureIsReady and RemoteCaptureGetData will behave as if
remote capture were not initialized
If the timeout expires while a transfer is in progress, an error will be generated
and the data may be incomplete or corrupt
*/
static int luaCB_set_usb_capture_timeout( lua_State* L )
{
    remotecap_set_timeout(luaL_optnumber(L,1,0));
    return 0;
}

//------------------------------------------------------------------------------------------
// APEX conversion functions

static int luaCB_iso_to_sv96( lua_State* L )
{
  lua_pushnumber(L, shooting_get_sv96_from_iso(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_sv96_to_iso( lua_State* L )
{
  lua_pushnumber(L, shooting_get_iso_from_sv96(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_iso_real_to_market( lua_State* L )
{
  lua_pushnumber(L, shooting_iso_real_to_market(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_iso_market_to_real( lua_State* L )
{
  lua_pushnumber(L, shooting_iso_market_to_real(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_sv96_real_to_market( lua_State* L )
{
  lua_pushnumber(L, shooting_sv96_real_to_market(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_sv96_market_to_real( lua_State* L )
{
  lua_pushnumber(L, shooting_sv96_market_to_real(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_aperture_to_av96( lua_State* L )
{
  lua_pushnumber(L, shooting_get_av96_from_aperture(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_av96_to_aperture( lua_State* L )
{
  lua_pushnumber(L, shooting_get_aperture_from_av96(luaL_checknumber(L, 1)));
  return 1;
}

static int luaCB_usec_to_tv96( lua_State* L )
{
  lua_pushnumber(L, shooting_get_tv96_from_shutter_speed((float)luaL_checknumber(L, 1)/1000000.0));
  return 1;
}

static int luaCB_tv96_to_usec( lua_State* L )
{
  lua_pushnumber(L, (int)(shooting_get_shutter_speed_from_tv96(luaL_checknumber(L, 1)) * 1000000.0 + 0.5));
  return 1;
}

static int luaCB_seconds_to_tv96( lua_State* L )
{
  lua_pushnumber(L, shooting_get_tv96_from_shutter_speed((float)luaL_checknumber(L, 1)/(float)luaL_checknumber(L, 2)));
  return 1;
}

//------------------------------------------------------------------------------------------
// Shoot hooks

/*
hook.set(timeout)
cause hook to block shooting process until timeout or script issues hook.continue
0 clears
*/
static int luaCB_shoot_hook_set( lua_State* L )
{
    int hook = lua_tonumber( L, lua_upvalueindex(1) );
    script_shoot_hook_set(hook,luaL_checknumber(L, 1));
    return 0;
}

/*
hook.is_ready()
returns true if the hooked task is in the hook
*/
static int luaCB_shoot_hook_is_ready( lua_State* L )
{
    int hook = lua_tonumber( L, lua_upvalueindex(1) );
    lua_pushboolean(L,script_shoot_hook_ready(hook));
    return 1;
}

/*
hook.continue()
allow the hooked task to leave the hook
*/
static int luaCB_shoot_hook_continue( lua_State* L )
{
    int hook = lua_tonumber( L, lua_upvalueindex(1) );
    script_shoot_hook_continue(hook);
    return 0;
}

/*
n=hook.count()
return the number of times the hook has been reached since script start
note: counts regardless of whether hook is enabled
*/
static int luaCB_shoot_hook_count( lua_State* L )
{
    int hook = lua_tonumber( L, lua_upvalueindex(1) );
    lua_pushnumber(L,script_shoot_hook_ready(hook));
    return 1;
}

//------------------------------------------------------------------------------------------

#define FUNC( X ) { #X,	luaCB_##X },
static const luaL_Reg chdk_funcs[] = {
    FUNC(shoot)
    FUNC(sleep)
    FUNC(cls)
    FUNC(set_console_layout)
    FUNC(set_console_autoredraw)
    FUNC(console_redraw)
    FUNC(get_av96)
    FUNC(get_bv96)
    FUNC(get_day_seconds)
    FUNC(get_disk_size)
    FUNC(get_dofinfo)
    FUNC(get_free_disk_space)
    FUNC(get_focus)
    FUNC(get_iso_market)
    FUNC(get_iso_mode)
    FUNC(get_iso_real)
    FUNC(get_jpg_count)
    FUNC(get_prop)
    FUNC(get_prop_str)
    FUNC(get_raw_count)
    FUNC(get_raw_nr)
    FUNC(get_raw)
    FUNC(get_sv96)
    FUNC(get_tick_count)
    FUNC(get_tv96)
    FUNC(get_user_av_id)
    FUNC(get_user_av96)
    FUNC(get_user_tv_id)
    FUNC(get_user_tv96)
    FUNC(get_vbatt)
    FUNC(get_zoom)
    FUNC(get_exp_count)
    FUNC(get_image_dir)
    FUNC(get_flash_params_count)
    FUNC(get_parameter_data)

    FUNC(set_av96_direct)
    FUNC(set_av96)
    FUNC(set_focus)
    FUNC(set_focus_interlock_bypass)
    FUNC(set_iso_mode)
    FUNC(set_iso_real)
    FUNC(set_led)
    FUNC(set_nd_filter)
    FUNC(set_prop)
    FUNC(set_prop_str)
    FUNC(set_raw_nr)
    FUNC(set_raw)
    FUNC(set_sv96)
    FUNC(set_tv96_direct)
    FUNC(set_tv96)
    FUNC(set_user_av_by_id_rel)
    FUNC(set_user_av_by_id)
    FUNC(set_user_av96)
    FUNC(set_user_tv_by_id_rel)
    FUNC(set_user_tv_by_id)
    FUNC(set_user_tv96)
    FUNC(set_zoom_speed)
    FUNC(set_zoom_rel)
    FUNC(set_zoom)

    FUNC(wait_click)
    FUNC(is_pressed)
    FUNC(is_key)
    FUNC(set_exit_key)
    FUNC(wheel_right)
    FUNC(wheel_left)
    FUNC(md_get_cell_diff)
    FUNC(md_get_cell_val)
    FUNC(md_detect_motion)
    FUNC(md_af_led_control)
    FUNC(autostarted)
    FUNC(get_autostart)
    FUNC(set_autostart)
    FUNC(get_usb_power)
    FUNC(enter_alt)
    FUNC(exit_alt)
    FUNC(shut_down)
    FUNC(print_screen)

    FUNC(get_partitionInfo)
    FUNC(swap_partitions)

    FUNC(get_focus_mode)
    FUNC(get_focus_state)
    FUNC(get_focus_ok)
    FUNC(get_propset)
    FUNC(get_zoom_steps)
    FUNC(get_drive_mode)
    FUNC(get_flash_mode)
    FUNC(get_shooting)
    FUNC(get_flash_ready)
    FUNC(get_IS_mode)
    FUNC(set_ev)
    FUNC(get_ev)
    FUNC(get_orientation_sensor)
    FUNC(get_nd_present)
    FUNC(get_movie_status)
    FUNC(set_movie_status)
    FUNC(get_video_button)
 
    FUNC(get_histo_range)
    FUNC(shot_histo_enable)
    FUNC(get_live_histo)
    FUNC(play_sound)
    FUNC(get_temperature)
    FUNC(peek)
    FUNC(poke)
    FUNC(bitand)
    FUNC(bitor)
    FUNC(bitxor)
    FUNC(bitshl)
    FUNC(bitshri)
    FUNC(bitshru)
    FUNC(bitnot)

    FUNC(get_time)

    FUNC(get_buildinfo)
    FUNC(get_mode)

    FUNC(set_raw_develop)
    // NOTE these functions normally run in the spytask.
    // called from lua they will run from kbd task instead
    FUNC(raw_merge_start)
    FUNC(raw_merge_add_file)
    FUNC(raw_merge_end)
    FUNC(set_backlight)
    FUNC(set_lcd_display)
    FUNC(set_draw_title_line)
    FUNC(get_draw_title_line)
    FUNC(set_aelock)
    FUNC(set_aflock)
    FUNC(set_curve_state)
    FUNC(get_curve_state)
    FUNC(set_curve_file)
    FUNC(get_curve_file)
    // get levent definition by name or id, nil if not found
    FUNC(get_levent_def)
    // get levent definition by index, nil if out of range
    FUNC(get_levent_def_by_index)
    // get levent index from name or ID
    FUNC(get_levent_index)
    FUNC(post_levent_to_ui)
    FUNC(post_levent_for_npt)
    FUNC(set_levent_active)
    FUNC(set_levent_script_mode)

    FUNC(set_capture_mode)
    FUNC(set_capture_mode_canon)
    FUNC(is_capture_mode_valid)

    FUNC(set_record)

    FUNC(switch_mode_usb)

    FUNC(call_event_proc)
    FUNC(call_func_ptr)
    FUNC(reboot)
    FUNC(get_config_value)
    FUNC(set_config_value)
    FUNC(set_config_autosave)
    FUNC(save_config_file)
    FUNC(load_config_file)
    FUNC(set_file_attributes)
    FUNC(get_meminfo)
    FUNC(file_browser)
    FUNC(textbox)
    FUNC(draw_pixel)
    FUNC(draw_line)
    FUNC(draw_rect)
    FUNC(draw_rect_filled)
    FUNC(draw_ellipse)
    FUNC(draw_ellipse_filled)
    FUNC(draw_clear)
    FUNC(draw_string)

    FUNC(get_gui_screen_width)
    FUNC(get_gui_screen_height)

    FUNC(set_yield)
    FUNC(read_usb_msg)
    FUNC(write_usb_msg)
    FUNC(get_usb_capture_support)
    FUNC(init_usb_capture)
    FUNC(set_usb_capture_timeout)

    FUNC(iso_to_sv96)
    FUNC(sv96_to_iso)
    FUNC(iso_real_to_market)
    FUNC(iso_market_to_real)
    FUNC(sv96_real_to_market)
    FUNC(sv96_market_to_real)
    FUNC(aperture_to_av96)
    FUNC(av96_to_aperture)
    FUNC(usec_to_tv96)
    FUNC(tv96_to_usec)
    FUNC(seconds_to_tv96)

    {NULL, NULL},
};

void register_shoot_hook_fn(lua_State* L, int hook, void *hook_fn, const char *name)
{
    lua_pushnumber( L, hook );
    lua_pushcclosure( L, hook_fn, 1 );
    lua_setfield( L, -2, name);
}

void register_shoot_hooks( lua_State* L )
{
    int i;
    for(i=0; i<SCRIPT_NUM_SHOOT_HOOKS;i++) {
        lua_createtable(L, 0, 4);
        register_shoot_hook_fn(L,i,luaCB_shoot_hook_set,"set");
//        register_shoot_hook_fn(L,i,luaCB_shoot_hook_wait_ready,"wait_ready");
        register_shoot_hook_fn(L,i,luaCB_shoot_hook_is_ready,"is_ready");
        register_shoot_hook_fn(L,i,luaCB_shoot_hook_continue,"continue");
        register_shoot_hook_fn(L,i,luaCB_shoot_hook_count,"count");
        lua_setglobal( L, shoot_hook_names[i] );
    }
}

void register_lua_funcs( lua_State* L )
{
  const luaL_reg *r;

  register_shoot_hooks( L );

  lua_pushlightuserdata( L, action_push_click );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "click" );

  lua_pushlightuserdata( L, action_push_press );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "press" );

  lua_pushlightuserdata( L, action_push_release );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "release" );

  for(r=chdk_funcs;r->name;r++) {
    lua_pushcfunction( L, r->func );
    lua_setglobal( L, r->name );
  }
   luaL_dostring(L,"function usb_msg_table_to_string(t)"
                    " local v2s=function(v)"
                        " local t=type(v)"
                        " if t=='string' then return v end"
                        " if t=='number' or t=='boolean' or t=='nil' then return tostring(v) end"
                        " return '' end"
                    " local r=''"
                    " for k,v in pairs(t) do"
                        " local s,vs=''"
                        " if type(v)=='table' then"
                            " for i=1,table.maxn(v) do"
                            " s=s..'\\t'..v2s(v[i]) end"
                        " else"
                            " vs=v2s(v)"
                            " if #vs then s=s..'\\t'..vs end"
                        " end"
                        " vs=v2s(k)"
                        " if #vs>0 and #s>0 then r=r..vs..s..'\\n' end"
                    " end"
                    " return r"
                   " end");

}

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

static void lua_set_variable(int varnum, int value)
{
    char var = 'a'+varnum;
    lua_pushlstring( L, &var, 1 );
    lua_pushnumber( L, value );
    lua_settable( L, LUA_GLOBALSINDEX );
}

static void lua_set_as_ret(int md_ret)                  { lua_pushnumber(Lt,md_ret); }

/******************** Module Information structure ******************/

libscriptapi_sym _liblua =
{
    {
         0, 0, 0, 0, 0
    },

    lua_script_start,
    lua_script_run,
    lua_script_reset,
    lua_set_variable,
    lua_set_as_ret,
    lua_run_restore,
    script_shoot_hook_run,
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SCRIPT_API_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Lua",             // Module name
    (int32_t)"Run Lua Scripts",

    &_liblua.base,

    CONF_VERSION,               // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    CAM_SENSOR_VERSION,         // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
