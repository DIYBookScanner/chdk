#ifndef __PTP_CHDK_H
#define __PTP_CHDK_H

// CHDK PTP interface (CHDK specific stuff)

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

#include "ptp.h"

// PTP constants - only need to be defined in CHDK, not PC side
#define PTP_RC_OK 0x2001
#define PTP_RC_GeneralError 0x2002
#define PTP_RC_ParameterNotSupported 0x2006
#define PTP_RC_InvalidParameter 0x201D

typedef struct {
    int code;
    int sess_id;
    int trans_id;
    int num_param;
    int param1;
    int param2;
    int param3;
    int param4;
    int param5;
} PTPContainer;

typedef struct {
    int handle;
    int (*send_data)(int handle, const char *buf, int part_size, int total_size, int, int, int); // (0xFF9F525C), total_size should be 0 except for the first call
    int (*recv_data)(int handle, char *buf, int size, int, int); // (0xFF9F5500)
    int (*send_resp)(int handle, PTPContainer *resp, int zero); // (0xFF9F5688), ixus30/40 needs a third argument, which is always 0
    int (*get_data_size)(int handle); // (0xFF9F5830)
    int (*send_err_resp)(int handle, PTPContainer *resp); // (0xFF9F5784)
    int unknown1; // ???
    int (*f2)(); // ??? (0xFF8D5B24)
    int (*f3)(); // ??? (0xFF8D5B5C)
    // more??
} ptp_data;

typedef int (*ptp_handler)(int, ptp_data*, int, int, int, int, int, int, int, int);

int add_ptp_handler(int opcode, ptp_handler handler, int unknown);

typedef struct {
    unsigned size;
    unsigned script_id; // id of script message is to/from 
    unsigned type;
    unsigned subtype;
    char data[];
} ptp_script_msg;

int ptp_script_write_msg(ptp_script_msg *msg);
ptp_script_msg* ptp_script_read_msg(void);
ptp_script_msg* ptp_script_create_msg(unsigned type, unsigned subtype, unsigned datasize, const void *data);
int ptp_script_write_error_msg(unsigned errtype, const char *err);

#endif // __PTP_CHDK_H
