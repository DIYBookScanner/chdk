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
void *lu_table_checkudata(lua_State *L, int narg, const char *fname, const char *tname);

void *lu_table_optudata(lua_State *L, int narg, const char *fname, const char *tname, void *d);
lua_Number lu_table_checknumber(lua_State *L, int narg, const char *fname);
lua_Number lu_table_optnumber(lua_State *L, int narg, const char *fname, lua_Number d);
int lu_table_checkoption(lua_State *L, int narg, const char *fname, const char *def, const char *lst[]);
const char *lu_table_optlstring(lua_State *L, int narg, const char *fname, const char *d, size_t *l);
