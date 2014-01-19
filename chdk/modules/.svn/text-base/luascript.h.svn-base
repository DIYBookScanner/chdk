#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include "../lib/lua/lua.h"

extern lua_State* L;
extern lua_State* Lt;

#define SET_STR_FIELD( KEY, VAL ) \
  lua_pushstring( L, VAL ); \
  lua_setfield( L, -2, KEY )

#define SET_INT_FIELD( KEY, VAL ) \
  lua_pushnumber( L, VAL ); \
  lua_setfield( L, -2, KEY )

#define SET_BOOL_FIELD( KEY, VAL ) \
  lua_pushboolean( L, VAL ); \
  lua_setfield( L, -2, KEY )

#include "script_api.h"

#endif
