/* ptpcam.h
 *
 * Copyright (C) 2001-2005 Mariusz Woloszyn <emsi@ipartners.pl>
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
#ifndef __PTPCAM_H__
#define __PTPCAM_H__

#define USB_BULK_READ usb_bulk_read
#define USB_BULK_WRITE usb_bulk_write

#define PTPIP_PORT_STR "15740"

/*
 * structures
 */

// connection data
// TODO might be more convenient to use this as the meta data and put in a pointer to PTPParams ?
// TODO - guess this is win only
#ifndef LIBUSB_PATH_MAX
#define LIBUSB_PATH_MAX (PATH_MAX + 1)
#endif
#define PTP_CON_USB 0
#define PTP_CON_TCP 1
typedef struct {
	usb_dev_handle* handle;
	int inep;
	int outep;
	int intep;
	char bus[LIBUSB_PATH_MAX]; // identifies what device this is for
	char dev[LIBUSB_PATH_MAX]; // note physical device on the same port doesn't necessarily get same bus/dev
} PTP_USB;

typedef struct {
	socket_t cmd_sock;
	socket_t event_sock;
	struct addrinfo *ai; // getaddrinfo result
	struct addrinfo *ai_con; // addr info selected for connection

	int connection_id;
	char cam_guid[16];
	// TODO 
	char host[LIBUSB_PATH_MAX];
	char port[LIBUSB_PATH_MAX];
} PTP_TCP;

typedef struct {
	// common connection state
	int con_type; 
	int script_id;
	int timeout;
	int connected; // soft check without actually trying to access connection
	// counters
	uint64_t write_count;
	uint64_t read_count;
	union {
		PTP_USB usb;
		PTP_TCP tcp;
	};
} PTP_CON_STATE;


/*
 * variables
 */

/* one global variable */
// TODO
extern short verbose;

/*
 * functions
 */

//void ptpcam_siginthandler(int signum);

void close_usb(PTP_CON_STATE* ptp_cs, struct usb_device* dev);
int init_ptp_usb (PTPParams* params, PTP_CON_STATE *cs, struct usb_device*);
void clear_stall(PTP_CON_STATE* ptp_cs);

int usb_get_endpoint_status(PTP_CON_STATE* ptp_cs, int ep, uint16_t* status);
int usb_clear_stall_feature(PTP_CON_STATE* ptp_cs, int ep);
void close_camera (PTP_CON_STATE *ptp_cs, PTPParams *params);
struct usb_device *find_device_by_path(const char *find_bus, const char *find_dev);
#endif /* __PTPCAM_H__ */
