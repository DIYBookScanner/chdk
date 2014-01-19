/*-----------------------------------------------------------------------------------
**	$Id: gps.h, v 1.1 2011/11/20 genie01 Exp $
**---------------------------------------------------------------------------------*/
#ifndef __CHDK_GPS_H
#define __CHDK_GPS_H

// CHDK GPS interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

typedef struct {
    char    latitudeRef[4];
    int     latitude[6];
    char    longitudeRef[4];
    int     longitude[6];
    char    heightRef[4];
    int     height[2];
    int     timeStamp[6];
    char    status[2];
    char    mapDatum[7];
    char    dateStamp[11];
    char    unknown2[160];
} tGPS;

extern void gps_startup();
extern void write_timezone();
extern void write_home();
extern void gps_navigate_home();
extern void gpx_bild_ohne_signal();
extern void wegpunkt();
extern void init_gpx_record_task();
extern void init_gps_kompass_task();
extern void init_gps_trackback_task();

#endif

/*-----------------------------------------------------------------------------------
**	$Id: gps.h, v 1.1 2011/11/20 genie01 Exp $
**---------------------------------------------------------------------------------*/
