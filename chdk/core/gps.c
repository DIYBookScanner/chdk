/*-----------------------------------------------------------------------------------
**	$Id: gps.c, v 1.2 2012/01/05 genie01 Exp $
**---------------------------------------------------------------------------------*/

#include "camera_info.h"
#include "stdlib.h"
#include "properties.h"
#include "task.h"
#include "modes.h"
#include "debug_led.h"
#include "shutdown.h"
#include "sound.h"
#include "backlight.h"
#include "temperature.h"
#include "file_counter.h"
#include "gps.h"

#include "stddef.h"
#include "conf.h"
#include "string.h"
#include "keyboard.h"
#include "lang.h"
#include "levent.h"
#include "math.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_batt.h"
#include "gui_lang.h"
//----------------

// GPS - Sachen
#include "gps_math.h"
#include "gps_palette.h"
//----------------

// Forward reference
void anzeige_gps();
void anzeige_kompass();
void test_timezone();
void gpx_record();
void trackback();
char *load_bitmap(char *datei);
void anzeige_kompassnadel (int winkel, double s_w, double c_w, char *bitmap, int laenge, int m_x, int m_y, int offset_x, int offset_y, int f_v_1, int f_h_1, int f_v_2, int f_h_2);
void anzeige_kompassbild (char *bitmap1, int o_x, int o_y, int f_v_0, int f_h_0, int f_v_1, int f_h_1, int f_v_2, int f_h_2, int f_v_4, int f_h_4);

extern char * camera_jpeg_current_filename();
extern char * camera_jpeg_current_latitude();
extern char * camera_jpeg_current_longitude();
extern char * camera_jpeg_current_height();

extern int exit_gpx_record;
extern int exit_gps_kompass;
extern int exit_gps_navi;

int exit_gps_data=1;

int Taste_Funktion=0;
int Taste_Taste=0;
int Taste_Druck=0;
int Taste_press=0;
int test_einmal_timezone=0;

char g_d_tim[10];
char g_d_dat[12];
char g_d_tim_gps[10];
char g_d_dat_gps[12];
//int g_d_lat_ref;
//int g_d_lon_ref;

int bild_ohne_signal=0;
int zeit_bis_ende=0;
int g_d_stat;

double g_d_lat_nav=0.0;
double g_d_lon_nav=0.0;
double g_d_lat;
double g_d_lon;
double g_d_hei;

int anzeige_symbol=0;
int nav_home=0;


static t_regression_xy buffer1[50];
static t_regression_xy buffer2[50];
static t_regression_xy buffer3[50];

#define PI      (3.1415926535)
#define RHO     (180.0/3.1415926535)
#define EARTH   (40.e6/360.0)

typedef struct {
	double lat_w;
	double lon_w;
} t_geo;

typedef struct {
	double north;
	double east;
} t_rectangular;

typedef struct {
	double delta;
	double alpha;   // radian
} t_polar;

void
geodiff (t_geo * von, t_geo* nach, t_geo* delta) {
	delta->lat_w = nach->lat_w - von->lat_w;
	delta->lon_w = nach->lon_w - von->lon_w;
}

void
geo2rect (t_geo * g, t_rectangular* r, double lat_w) {
	r->north= g->lat_w * EARTH;
	r->east = g->lon_w * EARTH * cos(lat_w/RHO);
}

void
rect2polar (t_rectangular* r, t_polar* p) {
	p->delta = sqrt (r->north*r->north + r->east*r->east);
	p->alpha = arctan2 (r->east, r->north);
}

void
polar2rect (t_rectangular* r, t_polar* p) {
	r->east = sin(p->alpha) * p->delta;
	r->north= cos(p->alpha) * p->delta;
}

int
radian2deg (double alpha) {
	return (int) (alpha * RHO + 360.5) % 360;
}

typedef struct {
	t_regression lat_w;
	t_regression lon_w;
} t_georeg;

void
georegInit (t_georeg* reg, int size, t_regression_xy * buffer1, t_regression_xy * buffer2) {
	regressionInit (&reg->lat_w, size, buffer1);
	regressionInit (&reg->lon_w, size, buffer2);
}

void
georegAdd (t_georeg* reg, double time, t_geo* geo) {
	regressionAdd (&reg->lat_w, time, geo->lat_w);
	regressionAdd (&reg->lon_w, time, geo->lon_w);
}

void
georegActual (t_georeg* reg, t_geo* geo) {
	geo->lat_w = regressionActual (&reg->lat_w);
	geo->lon_w = regressionActual (&reg->lon_w);
}

void
georegChange (t_georeg* reg, t_geo* geo) {
	geo->lat_w = regressionChange (&reg->lat_w);
	geo->lon_w = regressionChange (&reg->lon_w);
}

void
readGps (t_geo * gps) {

	msleep((int)conf.gps_navi_time*1000); 		// Warte eine bestimmte Zeit
	gps->lat_w = g_d_lat;
	gps->lon_w = g_d_lon;
}

double jetzt;                                   // Sekundenuhr
t_geo gps;                                      // gemessene verrauschte Position
t_georeg georeg;                                // Regression fuer Istposition
t_geo ist;                                      // Ist-Position aus Regression
t_geo speed;                                    // Ist Geschwindigkeit in Grad/s
t_rectangular mspeed;                   		// Ist Geschwindigkeit in m/s (N/E)
t_polar pspeed;                                 // Ist Geschwindigkeit in m/s + Winkel
int marsch;                                     // Marschrichtung
t_geo soll;                                     // Soll-Position
t_geo delta;                                    // Entfernung zum Ziel (in Grad)
t_rectangular rdelta;                   		// Entfernung zum Ziel (metrisch N/E)
t_polar pdelta;                                 // Entfernung zum Ziel (metrisch+Winkel)
int peil;                                       // Peilung zum Ziel
int winkel;                                     // Winkel auf Anzeige von Marsch zum Ziel
t_regression deltareg;                  		// Gl?ttung und Geschwindigkeit


void gps_updateData()
{
    extern void GPS_UpdateData();
    GPS_UpdateData();
}

void gps_get_data(){

	if ((int)conf.gps_on_off ==0) {return; }

	tGPS gps;

	int tim00=0;
	int tim01=0;
	int tim02=0;
	int nm=1;
	unsigned long t;
	static struct tm *ttm;
	
	while ( nm==1 )
	{
		gps_updateData();
        get_property_case(camera_info.props.gps, &gps, sizeof(gps));

		t=time(NULL);
		ttm = localtime(&t);

//		g_d_lat_ref = gps.latitudeRef;
		g_d_lat=0.0;
		g_d_lat=(gps.latitude[0]/(gps.latitude[1]*1.0)) + (gps.latitude[2]/(gps.latitude[3]*60.0)) + (gps.latitude[4]/(gps.latitude[5]*3600.0));
		if (gps.latitudeRef[0]=='S') g_d_lat=-g_d_lat;

//		g_d_lon_ref=gps.longitudeRef;
		g_d_lon=0.0;
		g_d_lon=(gps.longitude[0]/(gps.longitude[1]*1.0)) + (gps.longitude[2]/(gps.longitude[3]*60.0)) + (gps.longitude[4]/(gps.longitude[5]*3600.0));
		if (gps.longitudeRef[0]=='W') g_d_lon=-g_d_lon;

		g_d_hei=0.0;
		g_d_hei=gps.height[0]/(gps.height[1]*1.0);

		sprintf(g_d_tim, "%02d:%02d:%02d", ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
		sprintf(g_d_dat, "%04d-%02d-%02d", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday);
		
		g_d_stat=0;
		if ((int)g_d_lat == 0) {g_d_stat = 0; }
		if ((int)g_d_lat != 0 && (int)g_d_hei == 0) {g_d_stat=1; }
		if ((int)g_d_lat != 0 && (int)g_d_hei != 0) {g_d_stat=2; }

		if (g_d_stat > 0)
		{
			tim00=(int)(gps.timeStamp[0]/gps.timeStamp[1]);
			tim01=(int)(gps.timeStamp[2]/gps.timeStamp[3]);
			tim02=(int)(gps.timeStamp[4]/gps.timeStamp[5]);
			sprintf(g_d_tim_gps, "%02d:%02d:%02d", tim00, tim01, tim02);

			sprintf(g_d_dat_gps, "%c%c%c%c-%c%c-%c%c",
			        gps.dateStamp[0],
			        gps.dateStamp[1],
			        gps.dateStamp[2],
			        gps.dateStamp[3],
			        gps.dateStamp[5],
			        gps.dateStamp[6],
			        gps.dateStamp[8],
			        gps.dateStamp[9]);

			if ((int)conf.gps_test_timezone == 1)
			{
				if (test_einmal_timezone==0)
				{
					test_timezone();
					test_einmal_timezone=1;
				}
			}
		}
		
		if ((int)conf.gps_show_symbol == 1)
		{
			if (anzeige_symbol==0)
			{
				CreateTask("ANZSYMBOL", 0x19, 0x500, anzeige_gps);
				anzeige_symbol=1;
			}
		}
		msleep(900);
		nm=(int)conf.gps_on_off;
	}
	test_einmal_timezone=0;
	anzeige_symbol=0;
	exit_gps_data=1;
	ExitTask();
}

void gps_startup()
{
	if (((int)conf.gps_on_off ==1) && (exit_gps_data==1))
    {
	    CreateTask("GPSDATA", 0x19, 0x400, gps_get_data);
		exit_gps_data=0;
	}
}

void write_timezone(){

	if ((int)conf.gps_on_off ==0) {return; }

	char vBuf[30];
	char timezone_name[30];

	if (g_d_stat !=0)
	{
		mkdir_if_not_exist("A/GPS");
		mkdir_if_not_exist("A/GPS/Timezone");
		sprintf(timezone_name, "A/GPS/Timezone/Timezone.txt");

		FILE* fp = fopen(timezone_name, "w");
		if( fp )
		{
			sprintf(vBuf, "%i\n", (long)(g_d_lat*10000000));
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "%i\n", (long)(g_d_lon*10000000));
			fwrite(vBuf, strlen(vBuf), 1, fp);
		}
		fclose(fp);
	}
	else
	{
		int zba;
		for(zba=5; zba>0; zba--)
		{
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_1));
			draw_txt_string(8, 8, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
			msleep(1000);
		}
	}
}

void write_home(){

	if ((int)conf.gps_on_off ==0) {return; }

	char vBuf[30];
	char home_name[30];

	if (g_d_stat !=0)
	{
		mkdir_if_not_exist("A/GPS");
		mkdir_if_not_exist("A/GPS/Navigation");
		sprintf(home_name, "A/GPS/Navigation/Home.txt");

		FILE* fp = fopen(home_name, "w");
		if( fp )
		{
			sprintf(vBuf, "%i\n", (long)(g_d_lat*10000000));
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "%i\n", (long)(g_d_lon*10000000));
			fwrite(vBuf, strlen(vBuf), 1, fp);
		}
		fclose(fp);
	}
	else
	{
		int zba;
		for(zba=5; zba>0; zba--)
		{
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_1));
			draw_txt_string(8, 8, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
			msleep(1000);
		}
	}
}

void test_timezone(){

	if ((int)conf.gps_on_off ==0) {return; }

	char text[2][30];
	char home_name[30];
	int zeitzone_1, zeitzone_2;
	char * succ;

	sprintf(home_name, "A/GPS/Timezone/Timezone.txt");

	FILE* fp = fopen(home_name, "r");
	if( fp )
	{
		fgets(text[1], 15, fp);
		fgets(text[2], 15, fp);
		fclose(fp);

		g_d_lat_nav = (strtol (text[1], &succ, 10 )) / 10000000.0;
		g_d_lon_nav = (strtol (text[2], &succ, 10 )) / 10000000.0;

		zeitzone_1 = (int)((g_d_lon_nav+7.5)/15);
		zeitzone_2 = (int)((g_d_lon+7.5)/15);

		if (zeitzone_1 != zeitzone_2)
		{
			char vBuf[256];
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_2));
			draw_txt_string(1, 13, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
			msleep(5000);
		}
	}
}

void anzeige_gps(){

	if ((int)conf.gps_on_off ==0) {return; }

	char *bitmap;
	bitmap = load_bitmap("A/CHDK/DATA/GPS_Sat.txt");

	if(bitmap)
	{
		int laenge1 = strlen(bitmap);
		int pos1=0;
		int mx1=0;
		int my1=0;
		int o_x1=270;
		int o_y1=0;
		int nm=1;
		int zp=1;

		int f_v_0;
		int f_h_0;
		int f_v_1;
		int f_h_1;
		int f_v_2;
		int f_h_2;
		int f_v_3;
		int f_h_3;
		int f_v_4;
		int f_h_4;

		while ( nm==1 )
		{
			mx1=0;
			my1=0;

			f_v_0=COLOR_GPS_TRANSPARENT;
			f_h_0=COLOR_GPS_TRANSPARENT;

			f_v_1=COLOR_GPS_GREEN;
			f_h_1=COLOR_GPS_GREEN;

			if (g_d_stat == 0)
			{
				f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
				f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
			}
			if (g_d_stat == 1)
			{
				f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
				f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
			}
			if (g_d_stat == 2)
			{
				f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
				f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
			}
			if (camera_info.state.mode_play)
			{
				int lati[6];
				memcpy((void*)lati, camera_jpeg_current_latitude(), sizeof(lati));
				double lat000=lati[0]/(lati[1]*1.0);
				double lat001=lati[2]/(lati[3]*60.0);
				double lat002=lati[4]/(lati[5]*3600.0);
				double lat0e=lat000+lat001+lat002;

				int hei[5];
				memcpy((void*)hei, camera_jpeg_current_height(), sizeof(hei));
				char vBuf0[10];
				char vBuf1[10];
				char vBuf2[]="-----m";
				sprintf(vBuf0, "%s",hei);
				sprintf(vBuf1, "%s",vBuf2);


				if ((int)lat0e == 0)
				{
					f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
					f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
				}
				else
				{
					f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
					f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
				}
				if ( strcmp(vBuf0, vBuf1) !=0 )
				{
					f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
					f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
				}
			}



			f_v_2=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;
			f_h_2=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;

			f_v_3=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
			f_h_3=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;

			f_v_4=(camera_info.state.mode_rec) ? COLOR_GPS_BLUE : COLOR_GPS_PLAY_BLUE;
			f_h_4=(camera_info.state.mode_rec) ? COLOR_GPS_BLUE : COLOR_GPS_PLAY_BLUE;

			for(pos1=0; pos1<laenge1; pos1++)
			{
				int data = bitmap[pos1];
				if (data == 48)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_0, f_h_0));
				}
				if (data == 49)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_1, f_h_1));
				}
				if (data == 50)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_2, f_h_2));
				}
				if (data == 51)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_3, f_h_3));
				}
				if (data == 52)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_4, f_h_4));
				}
				if (data == 10 || data == 13)
				{
					mx1=0;
					my1++;
					pos1++;
				}
				else
				{
					mx1++;
				}
			}
			nm=(int)conf.gps_show_symbol;
			msleep(1000);
			if (zp == 10)
			{
				zp=0;
			}
			zp++;
			if ((int)conf.gps_on_off ==0)
			{
				nm=0;
			}

		}
	}
	anzeige_symbol=0;
	ExitTask();
}

void anzeige_track(){

	if ((int)conf.gps_on_off ==0) {return; }

	char *bitmap;
	bitmap = load_bitmap("A/CHDK/DATA/GPS_Track_1.txt");
	char *bitmap1;
	bitmap1 = load_bitmap("A/CHDK/DATA/GPS_Track_2.txt");
	char *bitmap2;
	bitmap2 = load_bitmap("A/CHDK/DATA/GPS_Track_3.txt");

	if(bitmap)
	{
		int laenge1 = strlen(bitmap);
		int pos1=0;
		int mx1=0;
		int my1=0;
		int o_x1=315;
		int o_y1=0;
		int nmm=0;

		int f_v_0;
		int f_h_0;
		int f_v_1;
		int f_h_1;
		int f_v_2;
		int f_h_2;
		int f_v_3;
		int f_h_3;
		int f_v_4;
		int f_h_4;
		int f_v_5;
		int f_h_5;
		int blink=0;
		int data;

		while ( nmm == 0 )
		{
			mx1=0;
			my1=0;

			f_v_0=COLOR_GPS_TRANSPARENT;
			f_h_0=COLOR_GPS_TRANSPARENT;

			f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;
			f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;

			f_v_2=(camera_info.state.mode_rec) ? COLOR_GPS_BLUE : COLOR_GPS_PLAY_BLUE;
			f_h_2=(camera_info.state.mode_rec) ? COLOR_GPS_BLUE : COLOR_GPS_PLAY_BLUE;

			f_v_3=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
			f_h_3=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;

			f_v_4=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
			f_h_4=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;

			f_v_5=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
			f_h_5=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;

			for(pos1=0; pos1<laenge1; pos1++)
			{
				if ((blink==1) && (g_d_stat > 0))
				{
					data = bitmap1[pos1];
				}
				else
				{
					data = bitmap[pos1];
				}
				if ((blink==1) && (exit_gps_navi==0) && (g_d_stat > 0))
				{
					data = bitmap2[pos1];
				}
				if (data == 48)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_0, f_h_0));
				}
				if (data == 49)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_1, f_h_1));
				}
				if (data == 50)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_2, f_h_2));
				}
				if (data == 51)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_3, f_h_3));
				}
				if (data == 52)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_4, f_h_4));
				}
				if (data == 53)
				{
					draw_pixel(o_x1+mx1, o_y1+my1, MAKE_COLOR(f_v_5, f_h_5));
				}
				if (data == 10 || data == 13)
				{
					mx1=0;
					my1++;
					pos1++;
				}
				else
				{
					mx1++;
				}
			}

			msleep(1000);
			nmm=exit_gpx_record;
			if ((int)conf.gps_on_off ==0)
			{
				nmm=0;
			}

			if (blink==0)
			{
				blink=1;
			}
			else
			{
				blink=0;
			}

		}
	}
	ExitTask();
}

void gpx_bild_ohne_signal(){

	if ((int)conf.gps_on_off ==0) {return; }

	char vBuf[100];

	FILE *fd0;
	char w1[20];
	char w2[30];
	char w3[10];
	int o=1, p=1, q=0;
	int blo=0;
	unsigned long bat;
	int abbruch=0;
	Taste_Funktion=1;
	Taste_Taste=11;
	
	while ( zeit_bis_ende !=0 )
	{
		// Teste Akku
		if ( (((zeit_bis_ende) % 60)) == 0 )
		{
			bat=get_batt_perc();
			if (bat <= (int)conf.gps_batt)
			{
				int zba;
				for(zba=30; zba>0; zba--)
				{
					sprintf(vBuf, lang_str(LANG_MENU_GPS_t_3));
					draw_txt_string(0, 8, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
					sprintf(vBuf, lang_str(LANG_MENU_GPS_t_4),zba);
					draw_txt_string(0, 9, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
					if ( (((zba) % 2)) == 0 )
					{
						debug_led(0);
						if ((int)conf.gps_batt_warn == 1)
						{
							play_sound(6);
						}
					}
					else
					{
						debug_led(1);
					}
					msleep(1000);
				}
				bild_ohne_signal=0;
				camera_shutdown_in_a_second();
				ExitTask();
			}
		}

		// Abschaltautomatik abbrechen
		if (Taste_Druck == 1)
		{
			Taste_Druck=0;
			abbruch = 1;
			zeit_bis_ende = 3600;
			TurnOnBackLight();
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_5));
			int zba;
			for(zba=5; zba>0; zba--)
			{
				draw_txt_string(10, 7, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
				msleep(1000);
			}
		}

		if ( abbruch == 0)
		{

			//LED blinken
			if (q==0)
			{
				debug_led(0);
				q=1;
			}
			else
			{
				debug_led(1);
				q=0;
			}

			// Anzeige Countdown / Zeit bis Ende in mm:ss

			int s = (int)zeit_bis_ende;
			int minuten =  s / 60;
			s = s % 60;
			int sekunden = s;

			if ( (int)conf.gps_countdown==0 )
			{
				sprintf(vBuf, lang_str(LANG_MENU_GPS_t_6),minuten, sekunden);
			}
			else
			{
				sprintf(vBuf, " %01d:%02d",minuten, sekunden);
			}
			draw_txt_string(0, 1, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));

			// Display einschalten wenn Countdown < 30 Sekunden

			if ((blo==1) && (zeit_bis_ende <=30))
			{
				TurnOnBackLight();
			}

			// Piepsen < 3 Sekunden
//			if (zeit_bis_ende <=3)
//			{
//				if ((int)conf.gps_beep_warn == 1)
//				{
//					play_sound(6);
//				}
//			}

			// Countdown von vorne beginnen
			if ((blo==0) && (kbd_get_pressed_key() !=0))
			{
				zeit_bis_ende=(int)conf.gps_wait_for_signal;
				o=1;
				p=1;
			}

			// Countdown von vorne beginnen und Display einschalten
			if ((blo==1) && (kbd_get_pressed_key() !=0))
			{
				TurnOnBackLight();
//				shooting_set_zoom(zoom);
				blo=0;
				zeit_bis_ende=(int)conf.gps_wait_for_signal;
				o=1;
				p=1;
			}

			// In Play-Modus schalten
			if ((o == (int)conf.gps_rec_play_time) && ((int)conf.gps_rec_play_set == 1))
			{
				if (camera_info.state.mode_rec)
				{
//					zoom=lens_get_zoom_point();
					levent_set_play();
				}
			}

			// Hintergrundbeleuchtung abschalten
			if ((p == (int)conf.gps_play_dark_time) && ((int)conf.gps_play_dark_set == 1))
			{
				if (camera_info.state.mode_play)
				{
					TurnOffBackLight();
					blo=1;
				}
			}
		}


		if ( ((((int)conf.gps_2D_3D_fix) == 1) && (g_d_stat == 1)) || \
		     ((((int)conf.gps_2D_3D_fix) == 1) && (g_d_stat == 2)) || \
		     ((((int)conf.gps_2D_3D_fix) == 2) && (g_d_stat == 2)) || \
		     ((((int)conf.gps_2D_3D_fix) == 3) && (g_d_stat == 2)) || \
		     ((((int)conf.gps_2D_3D_fix) == 3) && (g_d_stat == 1) && (zeit_bis_ende < 3)) || \
		     ((((int)conf.gps_2D_3D_fix) == 0) && (zeit_bis_ende < 3)) )
		{
			TurnOnBackLight();
			msleep (1000);

			fd0 = fopen ( "A/GPS/Tagging/wp.tmp", "r" );

			do
			{
				fgets (w1, 15, fd0);
				fseek (fd0, 1, SEEK_CUR);
				fgets (w2, 23, fd0);
				fseek (fd0, 1, SEEK_CUR);
				fgets (w3, 1, fd0);

				char lat[40];
				char lon[40];
				char hei[40];

				char vBuf1[512];
				char bild_name[20];
				char wp_name[30];
				char gpx_name[30];
				char gpx_bild_name[20];
				unsigned long t;
				static struct tm *ttm;
				t=time(NULL);
				ttm = localtime(&t);

				sprintf(wp_name, "A/GPS/Tagging/%04d_%02d_%02d.wp", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday);
				sprintf(gpx_name, "A/GPS/Tagging/%04d_%02d_%02d.gpx", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday);

				sprintf(bild_name, "%s", w1);
				sprintf(gpx_bild_name, "%s", w1);

				sprintf(vBuf1, "%s;%s;%s;%s;%s;%s",
				        bild_name,
				        formatDouble (lat, g_d_lat, 0, 7),
				        formatDouble (lon, g_d_lon, 0, 7),
				        formatDouble (hei, g_d_hei, 0, 2),
				        w2,
				        w3);

				FILE* fp = fopen(wp_name, "a");

				if( fp )
				{
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
				}

				fclose(fp);

				fp = fopen(gpx_name, "r");
				if( fp == NULL)
				{
					fp = fopen(gpx_name, "a");
					if( fp )
					{
						sprintf(vBuf1, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
						fwrite(vBuf1, strlen(vBuf1), 1, fp);
						sprintf(vBuf1, "<gpx xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" version=\"1.1\" creator=\"CHDK-DE\" xmlns=\"http://www.topografix.com/GPX/1/1\">\n");
						fwrite(vBuf1, strlen(vBuf1), 1, fp);
						sprintf(vBuf1, "</gpx>");
						fwrite(vBuf1, strlen(vBuf1), 1, fp);
						fclose(fp);
					}
				}


				fp = fopen(gpx_name, "a");
				if( fp )
				{
					fseek (fp, -6, SEEK_END);

					sprintf(vBuf1, "   <wpt lat=\"%s\" lon=\"%s\">\n",formatDouble (lat, g_d_lat, 0, 7), formatDouble (lon, g_d_lon, 0, 7));
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "    <ele>%s</ele>\n",formatDouble (hei, g_d_hei, 0, 2));
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "    <time>%s</time>\n", w2);
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "    <gpst>%sT%sZ</gpst>\n", g_d_dat_gps, g_d_tim_gps);
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "    <temp>%i</temp>\n", (int)get_optical_temp());
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "    <name>%s</name>\n", gpx_bild_name);
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "   </wpt>\n");
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
					sprintf(vBuf1, "</gpx>");
					fwrite(vBuf1, strlen(vBuf1), 1, fp);
				}
				fclose(fp);
			}
			while (!feof(fd0));

			fclose (fd0);
			if ( abbruch == 0)
			{
				zeit_bis_ende=1;
			}

		}

		msleep(1000);
		o++;
		p++;
		if ((int)conf.gps_on_off ==0)
		{
			bild_ohne_signal=0;
			abbruch=0;
			Taste_Funktion=1;
			Taste_Taste=11;
			Taste_Druck=0;
			debug_led(0);
			o=1;
			p=1;
			q=0;
			blo=0;
			ExitTask();
		}

		zeit_bis_ende--;
	}
	
	int zba, zba1;
	int taste_press=0;
	
	if (abbruch == 0) 
		{
			for(zba=15; zba>0; zba--)
				{
					sprintf(vBuf, lang_str(LANG_MENU_GPS_t_4), zba);
					draw_txt_string(0, 2, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_BLUE));
					sprintf(vBuf, lang_str(LANG_MENU_GPS_t_18));
					draw_txt_string(0, 3, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
					play_sound(6);

					for(zba1=100; zba1>0; zba1--)
						{
							if (kbd_get_pressed_key() ==6)
								{
									TurnOnBackLight();
									bild_ohne_signal=0;
									abbruch=0;
									Taste_Funktion=1;
									Taste_Taste=11;
									Taste_Druck=0;
									debug_led(0);
									taste_press=0;
									o=1;
									p=1;
									q=0;
									blo=0;

									ExitTask();
								}
						msleep(2);
						}
				}
			if (taste_press==0)
				{
					camera_shutdown_in_a_second(); 
				}

		}

	TurnOnBackLight();
	bild_ohne_signal=0;
	abbruch=0;
	Taste_Funktion=0;
	Taste_Taste=0;
	Taste_Druck=0;
	debug_led(0);
	// Piepsen 5 Sekunden

	if ((int)conf.gps_beep_warn == 1)
	{
		for(zba=5; zba>0; zba--)
		{
			play_sound(6);
		}
	}
	ExitTask();

}

void wegpunkt(){

	if ((int)conf.gps_on_off ==0) {return; }

	char lat[40];
	char lon[40];
	char hei[40];

	char vBuf[512];
	char bild_name[20];
	char wp_name[30];
	char gpx_name[30];
	char gpx_bild_name[20];

	unsigned long t;
	static struct tm *ttm;
	t=time(NULL);
	ttm = localtime(&t);

	mkdir_if_not_exist("A/GPS");
	mkdir_if_not_exist("A/GPS/Tagging");
	sprintf(wp_name, "A/GPS/Tagging/%04d_%02d_%02d.wp", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday);
	sprintf(gpx_name, "A/GPS/Tagging/%04d_%02d_%02d.gpx", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday);
	sprintf(bild_name, "IMG_%04d.JPG", get_target_file_num());

	if ((g_d_stat >= ((int)conf.gps_2D_3D_fix)) || ((((int)conf.gps_2D_3D_fix) == 3) && (g_d_stat == 2)))
	{
		sprintf(vBuf, "%s;%s;%s;%s;%sT%sZ;%i\n",
		        bild_name,
		        formatDouble (lat, g_d_lat, 0, 7),
		        formatDouble (lon, g_d_lon, 0, 7),
		        formatDouble (hei, g_d_hei, 0, 2),
		        g_d_dat, g_d_tim,
		        get_optical_temp());

		FILE* fp = fopen(wp_name, "a");

		if( fp )
		{
			fwrite(vBuf, strlen(vBuf), 1, fp);
		}
		fclose(fp);

		fp = fopen(gpx_name, "r");
		if( fp == NULL)
		{
			fp = fopen(gpx_name, "a");
			if( fp )
			{
				sprintf(vBuf, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "<gpx xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" version=\"1.1\" creator=\"CHDK-DE\" xmlns=\"http://www.topografix.com/GPX/1/1\">\n");
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "</gpx>");
				fwrite(vBuf, strlen(vBuf), 1, fp);
				fclose(fp);
			}
		}


		sprintf(gpx_bild_name, "IMG_%04d.JPG", get_target_file_num());

		fp = fopen(gpx_name, "a");
		if( fp )
		{
			fseek (fp, -6, SEEK_END);

			sprintf(vBuf, "   <wpt lat=\"%s\" lon=\"%s\">\n",formatDouble (lat, g_d_lat, 0, 7), formatDouble (lon, g_d_lon, 0, 7));
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "    <ele>%s</ele>\n",formatDouble (hei, g_d_hei, 0, 2));
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "    <time>%sT%sZ</time>\n", g_d_dat, g_d_tim);
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "    <gpst>%sT%sZ</gpst>\n", g_d_dat_gps, g_d_tim_gps);
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "    <temp>%i</temp>\n", (int)get_optical_temp());
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "    <name>%s</name>\n", gpx_bild_name);
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "   </wpt>\n");
			fwrite(vBuf, strlen(vBuf), 1, fp);
			sprintf(vBuf, "</gpx>");
			fwrite(vBuf, strlen(vBuf), 1, fp);
		}
		fclose(fp);
	}
	else
	{
		sprintf(vBuf, "%s %sT%sZ %i\n",
		        bild_name,
		        g_d_dat, g_d_tim,
		        get_optical_temp());

		if (bild_ohne_signal==0)
		{
			FILE* fp = fopen("A/GPS/Tagging/wp.tmp", "w");

			if( fp )
			{
				fwrite(vBuf, strlen(vBuf), 1, fp);
			}
			fclose(fp);
			bild_ohne_signal=1;
			zeit_bis_ende=(int)conf.gps_wait_for_signal;
			CreateTask("BILDOHNESIGNAL", 0x19, 0x1000, gpx_bild_ohne_signal);
		}
		else
		{
			FILE* fp = fopen("A/GPS/Tagging/wp.tmp", "a");

			if( fp )
			{
				fwrite(vBuf, strlen(vBuf), 1, fp);
			}
			fclose(fp);
			zeit_bis_ende=(int)conf.gps_wait_for_signal;
		}
	}
}

void init_gpx_record_task(){

	if ((int)conf.gps_on_off ==0) {return; }

	CreateTask("GPSRECORD", 0x19, 0x800, gpx_record);

	if ((int)conf.gps_track_symbol==1)
	{
		CreateTask("TRACKSYMBOL", 0x19, 0x600, anzeige_track);
	}
}

void gpx_record(){

	if ((int)conf.gps_on_off ==0) {return; }

	char lat[40];
	char lon[40];
	char hei[40];
	char vBuf[512];
	int r=0;
	unsigned long t;
	char gpx_name[30];
	static struct tm *ttm;
	t=time(NULL);
	ttm = localtime(&t);

	mkdir_if_not_exist("A/GPS");
	mkdir_if_not_exist("A/GPS/Logging");
	sprintf(gpx_name, "A/GPS/Logging/%02d_%02d-%02d_%02d.gpx", ttm->tm_mon+1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min);

	FILE* fp = fopen(gpx_name, "w");
	if( fp )
	{
		sprintf(vBuf, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, "<gpx xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" version=\"1.1\" creator=\"CHDK-DE\" xmlns=\"http://www.topografix.com/GPX/1/1\">\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, " <metadata />\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, " <trk>\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, "  <name />\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, "  <cmt />\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, "  <trkseg>\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, "  </trkseg>\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, " </trk>\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
		sprintf(vBuf, "</gpx>\n");
		fwrite(vBuf, strlen(vBuf), 1, fp);
	}
	fclose(fp);
	int zae=1, zae_1=0, bat;
	while ( r==0 )
	{
		if (kbd_get_pressed_key() !=0)
		{
			TurnOnBackLight();
			zae_1=0;
		}

		zae_1++;
		if ((zae_1 == (int)conf.gps_rec_play_time_1) && ((int)conf.gps_rec_play_set_1 == 1))
		{
			if (camera_info.state.mode_rec)
			{
				levent_set_play();
			}
		}
		if ((zae_1 == (int)conf.gps_play_dark_time_1) && ((int)conf.gps_play_dark_set_1 == 1))
		{
			if (camera_info.state.mode_play)
			{
				TurnOffBackLight();
			}
		}
		if ( (((zae_1) % 2)) == 0 )
		{
			debug_led(0);
		}
		else
		{
			debug_led(1);
		}
		if ( (((zae * (int)conf.gps_track_time) % 60)) == 0 )
		{
			bat=get_batt_perc();
			if (bat <= (int)conf.gps_batt)
			{
				int zba;
				for(zba=30; zba>0; zba--)
				{
					sprintf(vBuf, lang_str(LANG_MENU_GPS_t_3));
					draw_txt_string(0, 8, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
					sprintf(vBuf, lang_str(LANG_MENU_GPS_t_4),zba);
					draw_txt_string(0, 9, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
					if ( (((zba) % 2)) == 0 )
					{
						debug_led(0);
						play_sound(6);
					}
					else
					{
						debug_led(1);
					}
					msleep(1000);
				}
				camera_shutdown_in_a_second();
				ExitTask();
			}
		}

		if (g_d_stat == 1 || g_d_stat == 2)
		{
			fp = fopen(gpx_name, "a");
			if( fp )
			{
				fseek (fp, -27, SEEK_END);
				sprintf(vBuf, "   <trkpt lat=\"%s\" lon=\"%s\">\n",formatDouble (lat, g_d_lat, 0, 7), formatDouble (lon, g_d_lon, 0, 7));
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "    <ele>%s</ele>\n",formatDouble (hei, g_d_hei, 0, 2));
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "    <time>%sT%sZ</time>\n", g_d_dat, g_d_tim);
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "   </trkpt>\n");
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "  </trkseg>\n");
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, " </trk>\n");
				fwrite(vBuf, strlen(vBuf), 1, fp);
				sprintf(vBuf, "</gpx>\n");
				fwrite(vBuf, strlen(vBuf), 1, fp);
			}
			fclose(fp);
		}
		msleep((int)conf.gps_track_time*1000);
		zae++;
		r=exit_gpx_record;
		if ((int)conf.gps_on_off ==0)
		{
			r=1;
		}

	}
	debug_led(0);
	ExitTask();

}

void gps_navigate_home(){

	if ((int)conf.gps_on_off ==0) {return; }

	char text[2][30];
	char home_name[30];
	char * succ;

	sprintf(home_name, "A/GPS/Navigation/Home.txt");

	FILE* fp = fopen(home_name, "r");
	if( fp )
	{
		fgets(text[1], 15, fp);
		fgets(text[2], 15, fp);
	}
    fclose(fp);

	g_d_lat_nav = (strtol (text[1], &succ, 10 )) / 10000000.0;
	g_d_lon_nav = (strtol (text[2], &succ, 10 )) / 10000000.0;

	if ((int)conf.gps_track_symbol==1)
	{
		CreateTask("TRACKSYMBOL", 0x19, 0x600, anzeige_track);
	}

	if ((int)g_d_lat_nav != 0)
	{
		exit_gps_kompass=0;
		init_gps_kompass_task();
		nav_home=1;
	}
	else
	{
		char vBuf[256];
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_7));
		draw_txt_string(0, 8, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
		msleep(5000);
		nav_home=0;
	}
}

void init_gps_trackback_task(){

	if ((int)conf.gps_on_off ==0) {return; }

	int lati[6];
	memcpy((void*)lati, camera_jpeg_current_latitude(), sizeof(lati));
	g_d_lat_nav=0.0;
	g_d_lat_nav=(lati[0]/(lati[1]*1.0)) + (lati[2]/(lati[3]*60.0)) + (lati[4]/(lati[5]*3600.0));

	int longi[6];
	memcpy((void*)longi, camera_jpeg_current_longitude(), sizeof(longi));
	g_d_lon_nav=0.0;
	g_d_lon_nav=(longi[0]/(longi[1]*1.0)) + (longi[2]/(longi[3]*60.0)) + (longi[4]/(longi[5]*3600.0));

	char bild[9];
	sprintf(bild, "%s", camera_jpeg_current_filename());
	bild[8] = '\0';

	if ((int)g_d_lat_nav != 0)
	{
		exit_gps_kompass=0;
		init_gps_kompass_task();
	}
	else
	{
		char vBuf[256];
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_8), bild);
		draw_txt_string(0, 8, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
		msleep(5000);
	}
}

void init_gps_kompass_task(){

	if ((int)conf.gps_on_off ==0) {return; }

	CreateTask("GPSKOMPASS", 0x19, 0x900, anzeige_kompass);
}

double gps_kurswinkel(int zaehler){

	if ((int)conf.gps_on_off ==0) {return 0; }

	char vBuf[512];
	int angle1=0;

	soll.lat_w = g_d_lat_nav;
	soll.lon_w = g_d_lon_nav;

	jetzt = (double) (zaehler);
	readGps                 (&gps);                                         // lese GPS (mit Rauschen)

	georegAdd               (&georeg, jetzt, &gps);                         // füttere die Regression
	georegActual    		(&georeg, &ist);                                // lese gemittelte Position
	georegChange    		(&georeg, &speed);                              // lese gemittelte Geschwindigkeit
	geo2rect                (&speed, &mspeed, ist.lat_w);           		// konvertiere nach m/s (je N/E)
	rect2polar              (&mspeed, &pspeed);                             // konvertiere in Richtung und Geschw.
	marsch = radian2deg 	(pspeed.alpha);                                 // Marschrichtung

	geodiff                 (&ist, &soll, &delta);                          // Entfernung in Grad (N/E)
	geo2rect                (&delta, &rdelta, ist.lat_w);           		// Entfernung in m (je N/E)
	rect2polar              (&rdelta, &pdelta);                             // Entfernung in m und Grad
	peil    = radian2deg 	(pdelta.alpha);                         	   	// Peilung zum Ziel
	winkel  = radian2deg 	(pdelta.alpha-pspeed.alpha);       				// Winkel gegenüber Marschrichtung

	regressionAdd   		(&deltareg, jetzt, pdelta.delta);       		// füttere die Regression

	double eta = regressionReverse (&deltareg, 0);          				// Ankunftszeit (bei akt. geschwindigkeit)
																			// bei Entfernen vom Ziel auch in der Vergangenheit
	double rest= eta - jetzt;                                               // Restzeit = Ankunftszeit - jetzt

	if (abs(regressionChange (&deltareg))<0.5 || rest < 5.0) rest = 0.0;

	if (exit_gps_navi == 0)
	{
		angle1=(int)winkel;
		char anz1[40];
		char anz2[40];
		char bild[9];

	if (camera_info.state.gui_mode_none)
	{
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_9), (int)pdelta.delta);
		draw_txt_string(16, 9, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_WHITE));
		
		int s = (int)rest;
		int stunden = s / 3600;
		s = s % 3600;
		int minuten =  s / 60;
		s = s % 60;
		int sekunden = s;
		
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_10), stunden, minuten, sekunden);
		draw_txt_string(16, 10, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_WHITE));

		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_11), formatDouble (anz1, (pspeed.delta * 3.6), 0, 1));
		draw_txt_string(16, 11, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_WHITE));
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_12), (int)marsch);
		draw_txt_string(16, 12, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_WHITE));
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_13), (int)winkel);
		draw_txt_string(16, 13, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_WHITE));

		if (nav_home==0)
		{
			sprintf(bild, "%s", camera_jpeg_current_filename());
            bild[8] = '\0';
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_14), bild);
			draw_txt_string(0, 1, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
		}
		if (nav_home==1)
		{
//			sprintf(bild, "%s", camera_jpeg_current_filename());
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_17));//, bild);
			draw_txt_string(0, 1, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
		}
		
		sprintf(vBuf, lang_str(LANG_MENU_GPS_t_15), formatDouble (anz1, g_d_lat_nav, 0, 7), formatDouble (anz2, g_d_lon_nav, 0, 7));
		draw_txt_string(0, 2, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
	}
		
	}
	else
	{
		angle1=(int)marsch;
		if (camera_info.state.gui_mode_none)
		{
			sprintf(vBuf, lang_str(LANG_MENU_GPS_t_16), (int)angle1);
			draw_txt_string(1, 13, vBuf, MAKE_COLOR(COLOR_GPS_TRANSPARENT, COLOR_GPS_RED));
		}
	}


	return angle1;

}

void anzeige_kompass(){

	if ((int)conf.gps_on_off ==0) {return; }

	#define BITMAP_WIDTH  61
	#define BITMAP_HEIGHT 61

	georegInit (&georeg, (int)conf.gps_kompass_smooth, buffer1, buffer2);
	regressionInit (&deltareg, 20, buffer3);

	char *bitmap;
	char *bitmap1;

	double gwinkel=0;
	double w=0.0;
	double c_w;
	double s_w;

	int rr=0;
	int n=0;
	int zaehler=0;
	int m=0;
	int alter_winkel=0;

	int offset_x = 32;
	int m_x = offset_x + 31;
	int offset_y = 150;		//128
	int m_y = offset_y + 31;

	int f_v_0=COLOR_GPS_TRANSPARENT;
	int f_h_0=COLOR_GPS_TRANSPARENT;

	int f_v_1=COLOR_GPS_BLUE;
	int f_h_1=COLOR_GPS_BLUE;

	int f_v_2=(camera_info.state.mode_rec) ? COLOR_GPS_WHITE : COLOR_GPS_PLAY_WHITE;
	int f_h_2=(camera_info.state.mode_rec) ? COLOR_GPS_WHITE : COLOR_GPS_PLAY_WHITE;

	int f_v_3=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;
	int f_h_3=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;

	int f_v_4=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;
	int f_h_4=(camera_info.state.mode_rec) ? COLOR_GPS_BLACK : COLOR_GPS_PLAY_BLACK;

	double alter_c_w=cos(0);
	double alter_s_w=sin(0);

	bitmap = load_bitmap("A/CHDK/DATA/GPS_Pfeil.txt");
	bitmap1 = load_bitmap("A/CHDK/DATA/GPS_Kreis.txt");
	int laenge = strlen(bitmap);

	while ( rr==0 )
	{
		gwinkel=gps_kurswinkel(zaehler);

		zaehler++;
		m=n;

		if ((int)gwinkel != 0) {m=gwinkel; }

		if (g_d_stat == 0 )
		{
			f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
			f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_RED : COLOR_GPS_PLAY_RED;
		}
		if (g_d_stat == 1 )
		{
			f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
			f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_YELLOW : COLOR_GPS_PLAY_YELLOW;
		}
		if (g_d_stat == 2 )
		{
			f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
			f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_GREEN : COLOR_GPS_PLAY_GREEN;
		}
		if (camera_info.state.gui_mode_none)
		{
			anzeige_kompassbild (bitmap1, offset_x - 27, offset_y -14, f_v_0, f_h_0, f_v_1, f_h_1, f_v_2, f_h_2, f_v_4, f_h_4);
		}
		if (g_d_stat == 2 )
		{
			f_v_1=(camera_info.state.mode_rec) ? COLOR_GPS_BLUE : COLOR_GPS_PLAY_BLUE;
			f_h_1=(camera_info.state.mode_rec) ? COLOR_GPS_BLUE : COLOR_GPS_PLAY_BLUE;
		}
		if (m>=0 && m<180)
		{
			w=(180-m)*3.141592653589793/180;
		}
		if (m >=180 && m<=360)
		{
			w=(540-m)*3.141592653589793/180;
		}

		c_w=cos(w);
		s_w=sin(w);
		
		if (camera_info.state.gui_mode_none)
		{
			anzeige_kompassnadel (alter_winkel, alter_s_w, alter_c_w, bitmap, laenge, m_x, m_y, offset_x, offset_y, f_v_0, f_h_0, f_v_0, f_h_0);
			anzeige_kompassnadel (m, s_w, c_w, bitmap, laenge, m_x, m_y, offset_x, offset_y, f_v_1, f_h_1, f_v_3, f_h_3);
		}
		alter_winkel=m;
		alter_c_w=cos(w);
		alter_s_w=sin(w);

		rr=exit_gps_kompass;
		if ((int)conf.gps_on_off ==0)
		{
			rr=1;
		}

	}
	nav_home=0;
	ExitTask();
}

char *load_bitmap(char *datei){

	if ((int)conf.gps_on_off ==0) {return 0; }

	FILE *fd;
	char *bitmap;
	int bitmap_size;
	size_t result;

	fd = fopen ( datei, "r" );

	fseek (fd, 0, SEEK_END);
	bitmap_size = ftell (fd);
	fseek (fd, 0, SEEK_SET);

	bitmap = (char*) malloc (sizeof(char)*bitmap_size);
	result = fread (bitmap,1,bitmap_size,fd);
	fclose (fd);

	return bitmap;

	free(bitmap);

}

void anzeige_kompassnadel (int winkel, double s_w, double c_w, char *bitmap, int laenge, int m_x, int m_y, int offset_x, int offset_y, int f_v_1, int f_h_1, int f_v_2, int f_h_2){

	if ((int)conf.gps_on_off ==0) {return; }

	if(bitmap)
	{
		int mx=0;
		int my=0;
		int px=0;
		int py=0;

		int pos=0;
		int x_n;
		int y_n;

		if (winkel==0 || winkel==360)
		{
			s_w = 0;
			c_w = -1;
		}

		if (winkel==270)
		{
			s_w = -1;
			c_w = 0;
		}

		for(pos=0; pos<laenge; pos++)
		{
			int data = bitmap[pos];
			if (data >= 49)
			{
				px=offset_x+mx;
				py=offset_y+my;

				x_n = m_x + Round(((c_w * (m_x - px)) + (s_w * (m_y - py))),2);
				y_n = m_y + Round(((c_w * (m_y - py)) - (s_w * (m_x - px))),2);

				if (data == 49)
				{
					draw_pixel(x_n, y_n, MAKE_COLOR(f_v_1, f_h_1));
				}
				if (data == 50)
				{
					draw_pixel(x_n, y_n, MAKE_COLOR(f_v_2, f_h_2));
				}
			}
			if (data == 10 || data == 13)
			{
				mx=0;
				my++;
				pos++;
			}
			else
			{
				mx++;
			}
		}

	}
}

void anzeige_kompassbild (char *bitmap1, int o_x, int o_y, int f_v_0, int f_h_0, int f_v_1, int f_h_1, int f_v_2, int f_h_2, int f_v_4, int f_h_4){

	if ((int)conf.gps_on_off ==0) {return; }

	if(bitmap1)
	{
		int laenge = strlen(bitmap1);
		int pos=0;
		int mx=0;
		int my=0;

		for(pos=0; pos<laenge; pos++)
		{
			int data = bitmap1[pos];
			if (data == 48)
			{
				draw_pixel(o_x+mx, o_y+my, MAKE_COLOR(f_v_0, f_h_0));
			}
			if (data == 49)
			{
				draw_pixel(o_x+mx, o_y+my, MAKE_COLOR(f_v_1, f_h_1));
			}
			if (data == 50)
			{
				draw_pixel(o_x+mx, o_y+my, MAKE_COLOR(f_v_2, f_h_2));
			}
			if (data == 51)
			{
				draw_pixel(o_x+mx, o_y+my, MAKE_COLOR(f_v_4, f_h_4));
			}
			if (data == 10 || data == 13)
			{
				mx=0;
				my++;
				pos++;
			}
			else
			{
				mx++;
			}
		}

	}
}

/*-----------------------------------------------------------------------------------
**	$Id: gps.c, v 1.2 2012/01/05 genie01 Exp $
**---------------------------------------------------------------------------------*/
