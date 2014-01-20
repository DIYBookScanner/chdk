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

#ifndef LBUF_H
#define LBUF_H
#define LBUF_META "lbuf.lbuf_meta"
#define LBUF_METHODS "lbuf.lbuf_methods"
#define LBUF_FL_FREE 0x1
#define LBUF_FL_READONLY 0x2
typedef struct {
	unsigned len;
	unsigned flags;
	char *bytes;
} lBuf_t;
int lbuf_create(lua_State *L,void *data,unsigned len,unsigned flags);
lBuf_t* lbuf_getlbuf(lua_State *L,int i);
void lbuf_open(lua_State *L);
#endif

