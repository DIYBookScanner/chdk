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

Simple utilities to make socket code more platform independent
*/

#ifndef SOCKUTIL_H
#define SOCKUTIL_H

#ifdef WIN32
typedef SOCKET socket_t;
#else
typedef int socket_t;
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif

void sockutil_startup(void);
void sockutil_cleanup(void);
int sockutil_errno(void);
const char *sockutil_strerror(int err);
void sockutil_close(socket_t sock);
#endif
