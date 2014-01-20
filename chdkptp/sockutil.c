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

Simple utilities to make socket code platform independent
TODO might want to just use luasocket code
*/

#ifdef WIN32
// required for getaddrinfo, we don't support pre-XP anyway
#define WINVER 0x0502

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "sockutil.h"

static int initialized;
// TODO should probably return status
void sockutil_startup(void) {
	if(initialized)
		return;
#ifdef WIN32
	WSADATA wsaData;
	int r = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (r != 0) {
		printf("WSAStartup failed with error: %d\n", r);
		exit(1);
	}
#endif
	initialized = 1;
}

void sockutil_cleanup(void) {
	if(!initialized)
		return;
#ifdef WIN32
	WSACleanup();
#endif
}
int sockutil_errno(void) {
#ifdef WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

// could use FormatMessage but this is quick
#ifdef WIN32
typedef struct {
	int n;
	const char *s;
} error_list_t;
#define ERROR_DEF(n) {n,#n},
static error_list_t error_list[] = {
	ERROR_DEF(WSA_INVALID_HANDLE)
	ERROR_DEF(WSA_NOT_ENOUGH_MEMORY)
	ERROR_DEF(WSA_INVALID_PARAMETER)
	ERROR_DEF(WSA_OPERATION_ABORTED)
	ERROR_DEF(WSA_IO_INCOMPLETE)
	ERROR_DEF(WSA_IO_PENDING)
	ERROR_DEF(WSAEINTR)
	ERROR_DEF(WSAEBADF)
	ERROR_DEF(WSAEACCES)
	ERROR_DEF(WSAEFAULT)
	ERROR_DEF(WSAEINVAL)
	ERROR_DEF(WSAEMFILE)
	ERROR_DEF(WSAEWOULDBLOCK)
	ERROR_DEF(WSAEINPROGRESS)
	ERROR_DEF(WSAEALREADY)
	ERROR_DEF(WSAENOTSOCK)
	ERROR_DEF(WSAEDESTADDRREQ)
	ERROR_DEF(WSAEMSGSIZE)
	ERROR_DEF(WSAEPROTOTYPE)
	ERROR_DEF(WSAENOPROTOOPT)
	ERROR_DEF(WSAEPROTONOSUPPORT)
	ERROR_DEF(WSAESOCKTNOSUPPORT)
	ERROR_DEF(WSAEOPNOTSUPP)
	ERROR_DEF(WSAEPFNOSUPPORT)
	ERROR_DEF(WSAEAFNOSUPPORT)
	ERROR_DEF(WSAEADDRINUSE)
	ERROR_DEF(WSAEADDRNOTAVAIL)
	ERROR_DEF(WSAENETDOWN)
	ERROR_DEF(WSAENETUNREACH)
	ERROR_DEF(WSAENETRESET)
	ERROR_DEF(WSAECONNABORTED)
	ERROR_DEF(WSAECONNRESET)
	ERROR_DEF(WSAENOBUFS)
	ERROR_DEF(WSAEISCONN)
	ERROR_DEF(WSAENOTCONN)
	ERROR_DEF(WSAESHUTDOWN)
	ERROR_DEF(WSAETOOMANYREFS)
	ERROR_DEF(WSAETIMEDOUT)
	ERROR_DEF(WSAECONNREFUSED)
	ERROR_DEF(WSAELOOP)
	ERROR_DEF(WSAENAMETOOLONG)
	ERROR_DEF(WSAEHOSTDOWN)
	ERROR_DEF(WSAEHOSTUNREACH)
	ERROR_DEF(WSAENOTEMPTY)
	ERROR_DEF(WSAEPROCLIM)
	ERROR_DEF(WSAEUSERS)
	ERROR_DEF(WSAEDQUOT)
	ERROR_DEF(WSAESTALE)
	ERROR_DEF(WSAEREMOTE)
	ERROR_DEF(WSASYSNOTREADY)
	ERROR_DEF(WSAVERNOTSUPPORTED)
	ERROR_DEF(WSANOTINITIALISED)
	ERROR_DEF(WSAEDISCON)
	ERROR_DEF(WSAENOMORE)
	ERROR_DEF(WSAECANCELLED)
	ERROR_DEF(WSAEINVALIDPROCTABLE)
	ERROR_DEF(WSAEINVALIDPROVIDER)
	ERROR_DEF(WSAEPROVIDERFAILEDINIT)
	ERROR_DEF(WSASYSCALLFAILURE)
	ERROR_DEF(WSASERVICE_NOT_FOUND)
	ERROR_DEF(WSATYPE_NOT_FOUND)
	ERROR_DEF(WSA_E_NO_MORE)
	ERROR_DEF(WSA_E_CANCELLED)
	ERROR_DEF(WSAEREFUSED)
	ERROR_DEF(WSAHOST_NOT_FOUND)
	ERROR_DEF(WSATRY_AGAIN)
	ERROR_DEF(WSANO_RECOVERY)
	ERROR_DEF(WSANO_DATA)
	ERROR_DEF(WSA_QOS_RECEIVERS)
	ERROR_DEF(WSA_QOS_SENDERS)
	ERROR_DEF(WSA_QOS_NO_SENDERS)
	ERROR_DEF(WSA_QOS_NO_RECEIVERS)
	ERROR_DEF(WSA_QOS_REQUEST_CONFIRMED)
	ERROR_DEF(WSA_QOS_ADMISSION_FAILURE)
	ERROR_DEF(WSA_QOS_POLICY_FAILURE)
	ERROR_DEF(WSA_QOS_BAD_STYLE)
	ERROR_DEF(WSA_QOS_BAD_OBJECT)
	ERROR_DEF(WSA_QOS_TRAFFIC_CTRL_ERROR)
	ERROR_DEF(WSA_QOS_GENERIC_ERROR)
	ERROR_DEF(WSA_QOS_ESERVICETYPE)
	ERROR_DEF(WSA_QOS_EFLOWSPEC)
	ERROR_DEF(WSA_QOS_EPROVSPECBUF)
	ERROR_DEF(WSA_QOS_EFILTERSTYLE)
	ERROR_DEF(WSA_QOS_EFILTERTYPE)
	ERROR_DEF(WSA_QOS_EFILTERCOUNT)
	ERROR_DEF(WSA_QOS_EOBJLENGTH)
	ERROR_DEF(WSA_QOS_EFLOWCOUNT)
	ERROR_DEF(WSA_QOS_EUNKOWNPSOBJ)
	ERROR_DEF(WSA_QOS_EPOLICYOBJ)
	ERROR_DEF(WSA_QOS_EFLOWDESC)
	ERROR_DEF(WSA_QOS_EPSFLOWSPEC)
	ERROR_DEF(WSA_QOS_EPSFILTERSPEC)
	ERROR_DEF(WSA_QOS_ESDMODEOBJ)
	ERROR_DEF(WSA_QOS_ESHAPERATEOBJ)
	ERROR_DEF(WSA_QOS_RESERVED_PETYPE)
};
#endif

const char *sockutil_strerror(int err) {
#ifdef WIN32
	int i;
	for(i=0;i<sizeof(error_list)/sizeof(error_list_t);i++) {
		if(error_list[i].n==err) {
			return error_list[i].s;
		}
	}
	return "unknown error";
#else
	return strerror(err);
#endif
}

void sockutil_close(socket_t sock) {
#ifdef WIN32
	closesocket(sock);
#else
	close(sock);
#endif
}

