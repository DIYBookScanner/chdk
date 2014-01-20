/* this is just some proof of concept test code*/
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN

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

#define DEFAULT_BUFLEN 512
#define PTPIP_PORT "15740"

#define PTPIP_TYPE_INIT_CMD 0x1
#define PTPIP_TYPE_INIT_CMD_ACK 0x2
#define PTPIP_TYPE_INIT_EVENT 0x3
#define PTPIP_TYPE_INIT_EVENT_ACK 0x4
#define PTPIP_TYPE_INIT_FAIL 0x5
#define PTPIP_TYPE_REQ 0x6
#define PTPIP_TYPE_RESP 0x7

#include "ptp.h"

// guid for connection request, must be 16 bytes, values don't seem to matter
char my_guid[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xde,0xad,0xbe,0xef,0x12,0x34,0x56,0x78
};
// friendly name (i.e windows network name), in utf16 value doesn't seem to matter
char my_name[] = {
	'w',0x00,'h',0x00,'e',0x00,'e',0x00,0x00,0x00
};

char cam_guid[16];

typedef struct {
	socket_t sock;
	socket_t event_sock;
	uint32_t transaction_id;
	uint32_t session_id;
	uint32_t connection_id;
} PTPIPParams;

typedef struct __attribute__ ((__packed__)) {
	uint32_t length;
	uint32_t type;
	uint32_t dataphase;
	uint16_t code;
	uint32_t trans_id;
	struct {
		uint32_t param1;
		uint32_t param2;
		uint32_t param3;
		uint32_t param4;
		uint32_t param5;
	} params;
} PTPIPReq;

typedef struct __attribute__ ((__packed__)) {
	uint32_t length;
	uint32_t type;
	uint16_t code;
	uint32_t trans_id;
	struct {
		uint32_t param1;
		uint32_t param2;
		uint32_t param3;
		uint32_t param4;
		uint32_t param5;
	} params;
} PTPIPResp;

typedef struct  __attribute__ ((__packed__)) {
	uint32_t length;
	uint32_t type;
	uint32_t connection_id;
} PTPIPEventReq;

int init_connection(PTPIPParams *params,char *host,char *port) {
    socket_t sock = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

	sockutil_startup();

    memset( &hints, 0, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    int r = getaddrinfo(host, port, &hints, &result);
    if ( r != 0 ) {
        printf("getaddrinfo failed with error: %d\n", r);
		sockutil_cleanup();
        return 0;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a socket for the command channel
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == INVALID_SOCKET) {
            printf("socket failed with error: %d %s\n", sockutil_errno(),sockutil_strerror(sockutil_errno()));
            return 0;
        }

        // Connect to camera
        r = connect( sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (r == SOCKET_ERROR) {
            sockutil_close(sock);
            sock = INVALID_SOCKET;
            continue;
        }
        break;
    }
	params->sock = sock;


	printf("initializing command channel\n");
	char sendbuf[38];
	char *p = sendbuf;
	*(int *)p = 38; // length
	p+=4;
	*(int *)p = PTPIP_TYPE_INIT_CMD; // init command packet
	p+=4;
	memcpy(p,my_guid,sizeof(my_guid));
	p+=sizeof(my_guid);
	memcpy(p,my_name,sizeof(my_name));
	p+=sizeof(my_name);
	*(int *)p = 0x00010000;

    r = send( params->sock, sendbuf, sizeof(sendbuf), 0 );
    if (r == SOCKET_ERROR) {
        printf("send failed with error: %d %s\n", sockutil_errno(),sockutil_strerror(sockutil_errno()));
        return 0;
    }
    printf("Bytes Sent: %d\n", r);

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

	r = recv(params->sock, recvbuf, recvbuflen, 0);
	int len;
	if ( r > 0 ) {
		printf("Bytes received: %d\n", r);
		if( r >= 4) {
			len = *(int *)recvbuf;
			if(len != r) {
				printf("size %d != %d\n",len,r);
				return 0;
			}
			int rtype = *(int32_t *)(recvbuf + 4);
			printf("packet type %d\n",rtype);
			if(rtype != PTPIP_TYPE_INIT_CMD_ACK) {
				printf("not ack, aborting\n");
				return 0;
			}
			params->connection_id = *(uint32_t *)(recvbuf + 8);
			printf("connection num %d\n",params->connection_id);
		} else {
			printf("size %d < sizeof(int)",r);
			return 0;
		}
	} else if ( r == 0 ) {
		printf("Connection closed\n");
		return 0;
	} else {
		printf("recv failed with error: %d\n", sockutil_errno());
		return 0;
	}

	printf("initializing event channel\n");

	// event channel
    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a socket for the command channel
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == INVALID_SOCKET) {
            printf("socket failed with error: %d\n", sockutil_errno());
            return 0;
        }

        // Connect to camera
        r = connect( sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (r == SOCKET_ERROR) {
            sockutil_close(sock);
            sock = INVALID_SOCKET;
            continue;
        }
        break;
    }
	params->event_sock = sock;
    freeaddrinfo(result);

	PTPIPEventReq ereq;
	ereq.length=sizeof(ereq);
	ereq.type=PTPIP_TYPE_INIT_EVENT;
	ereq.connection_id = params->connection_id;

    r = send( params->event_sock, (char *)&ereq, sizeof(ereq), 0 );
    if (r == SOCKET_ERROR) {
        printf("send failed with error: %d\n", sockutil_errno());
        return 0;
    }
    printf("Bytes Sent: %d\n", r);

	r = recv(params->event_sock, recvbuf, recvbuflen, 0);
	if ( r > 0 ) {
		printf("Bytes received: %d\n", r);
		if( r >= 4) {
			len = *(int *)recvbuf;
			if(len != r) {
				printf("size %d != %d\n",len,r);
				return 0;
			}
			printf("packet type %d\n",*(int *)(recvbuf + 4));
			return 1;
		} else {
			printf("size %d < sizeof(int)",r);
			return 0;
		}
	} else if ( r == 0 ) {
		printf("Connection closed\n");
		return 0;
	} else {
		printf("recv failed with error: %d\n", sockutil_errno());
		return 0;
	}
	return 1;
}


uint16_t ptpip_sendreq(PTPIPParams *params, PTPContainer *ptp)
{
	PTPIPReq req;
	memset(&req,0,sizeof(req));
	req.length = sizeof(req) - 4*(5-ptp->Nparam);
	req.type = PTPIP_TYPE_REQ;
	req.dataphase = 0; // name from wireshark dissector, appears to be 0
						// even if there is a send or receive data phase
						// actual meaning unclear
	req.trans_id=ptp->Transaction_ID;
	req.code=ptp->Code;
	req.params.param1=ptp->Param1;
	req.params.param2=ptp->Param2;
	req.params.param3=ptp->Param3;
	req.params.param4=ptp->Param4;
	req.params.param5=ptp->Param5;

    int r = send( params->sock, (char *)&req, req.length, 0);
    if (r == SOCKET_ERROR) {
        printf("send_req send failed with error: %d\n", sockutil_errno());
        return PTP_ERROR_IO;
    }
	return PTP_RC_OK;
}

uint16_t ptpip_getresp(PTPIPParams *params, PTPContainer *ptp)
{
	PTPIPResp resp;
	memset(&resp,0,sizeof(resp));
	int r = recv(params->sock, (char *)&resp, sizeof(resp), 0);
	if ( r > 0 ) {
		printf("Bytes received: %d\n", r);
		if( r >= 4) {
			if(resp.length != r) {
				printf("size %d != %d\n",resp.length,r);
				return PTP_ERROR_IO;
			}
			printf("type %d\n",resp.type);
		} else {
			printf("size %d < sizeof(int)",r);
			return PTP_ERROR_IO;
		}
	} else if ( r == 0 ) {
		printf("Connection closed\n");
		return PTP_ERROR_IO;
	} else {
		printf("recv failed with error: %d\n", sockutil_errno());
		return PTP_ERROR_IO;
	}
	ptp->Code = resp.code;
	ptp->Transaction_ID = resp.trans_id;
	ptp->Param1 = resp.params.param1;
	ptp->Param2 = resp.params.param2;
	ptp->Param3 = resp.params.param3;
	ptp->Param4 = resp.params.param4;
	ptp->Param5 = resp.params.param5;
	ptp->Nparam = 5 - (sizeof(resp) - (resp.length))/4;
	return PTP_RC_OK;
}

uint16_t ptpip_transaction(PTPIPParams *params, PTPContainer *ptp, uint16_t flags, unsigned int sendlen, char**data)
{
	if ((params==NULL) || (ptp==NULL)) 
		return PTP_ERROR_BADPARAM;

	ptp->Transaction_ID=params->transaction_id++;
	ptp->SessionID=params->session_id;
	uint16_t ret = ptpip_sendreq(params,ptp);
	if(ret != PTP_RC_OK) {
		return ret;
	}
	// NO data phase support!
	ret = ptpip_getresp(params,ptp);
	return ret;
}


int main(int argc, char **argv) 
{
	PTPIPParams params;
    
    if (argc != 2) {
        printf("usage: %s <camera address>\n", argv[0]);
        return 1;
    }


    memset( &params, 0, sizeof(params) );

	if(!init_connection(&params,argv[1],PTPIP_PORT)) {
        sockutil_close(params.sock);
		sockutil_cleanup();
        return 1;
	}

	PTPContainer ptp;

	memset(&ptp,0,sizeof(ptp));
	ptp.Code=PTP_OC_OpenSession;
	ptp.Nparam=1;
	ptp.Param1=1;
	uint16_t r=ptpip_transaction(&params, &ptp, /*PTP_DP_NODATA*/0, 0, NULL);
	if ( r != PTP_RC_OK ) {
		printf("OpenSession failed 0x%x\n",r);
	} else {
		printf("OpenSession OK\n");
	}

	memset(&ptp,0,sizeof(ptp));
	ptp.Code=PTP_OC_CHDK;
	ptp.Nparam=1;
	ptp.Param1=PTP_CHDK_Version;
	r=ptpip_transaction(&params, &ptp, /*PTP_DP_NODATA*/0, 0, NULL);
	if ( r != PTP_RC_OK ) {
		printf("PTP_CHDK_Version failed 0x%x\n",r);
	} else {
		printf("chdk ver np=%d %d,%d\n",ptp.Nparam,ptp.Param1,ptp.Param2);
	}

    // cleanup
    sockutil_close(params.sock);
    sockutil_close(params.event_sock);
	sockutil_cleanup();

    return 0;
}
