/*
 *
 * Copyright (C) 2010-2012 <reyalp (at) gmail dot com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
misc helper functions to simplify lua API code
*/
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "luautil.h"
/*
functions to get fields from a table at a specified stack index, similar to luaL_check* and luaL_opt*
throw error on incorrect type, return C value and pop off the stack
*/
void *lu_table_checkudata(lua_State *L, int narg, const char *fname, const char *tname) {
	lua_getfield(L, narg, fname);
	void *r = luaL_checkudata(L,-1,tname);
	lua_pop(L,1);
	return r;
}

void *lu_table_optudata(lua_State *L, int narg, const char *fname, const char *tname, void *d) {
	void *r;
	lua_getfield(L, narg, fname);
	if(lua_isnil(L,-1)) {
		r=d;
	}
	else {
		r = luaL_checkudata(L,-1,tname);
	}
	lua_pop(L,1);
	return r;
}


lua_Number lu_table_checknumber(lua_State *L, int narg, const char *fname) {
	lua_getfield(L, narg, fname);
	lua_Number r = luaL_checknumber(L,-1);
	lua_pop(L,1);
	return r;
}

lua_Number lu_table_optnumber(lua_State *L, int narg, const char *fname, lua_Number d) {
	lua_getfield(L, narg, fname);
	lua_Number r = luaL_optnumber(L,-1,d);
	lua_pop(L,1);
	return r;
}

/*
const char *lu_table_checkstring(lua_State *L, int narg, const char *fname) {
	lua_getfield(L, narg, fname);
	const char *r = luaL_checkstring(L,-1);
	lua_pop(L,1);
	return r;
}
*/
int lu_table_checkoption(lua_State *L, int narg, const char *fname, const char *def, const char *lst[]) {
	lua_getfield(L, narg, fname);
	int r = luaL_checkoption(L,-1, def, lst);
	lua_pop(L,1);
	return r;
}

const char *lu_table_optlstring(lua_State *L, int narg, const char *fname, const char *d, size_t *l) {
	lua_getfield(L, narg, fname);
	const char *r = luaL_optlstring(L,-1,d,l);
	lua_pop(L,1);
	return r;
}

