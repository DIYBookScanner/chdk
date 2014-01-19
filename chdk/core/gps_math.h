#ifndef GPS_MATH_H
#define GPS_MATH_H

// Additional math functions for GPS

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

extern int fac(int n);
//extern double arccos(double x, int n);
extern double arctan(double x, int n);
extern double arctan2(double y, double x);
extern double Round(double Zahl, int Stellen);

/*-----------------------------------------------------------------------------------
**	$Id: ceilfloor.h,v 1.1 2011/10/08 18:04:26 wolf Exp $
**---------------------------------------------------------------------------------*/

extern double ceil (double phi);
extern double floor (double phi);

/*-----------------------------------------------------------------------------------
**	$Id: ceilfloor.h,v 1.1 2011/10/08 18:04:26 wolf Exp $
**---------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------
   $Id: format_double.h,v 1.3 2011/09/23 12:37:12 wolf Exp $
   -----------------------------------------------------------------------------------*/

/*
**	formatDouble:
**
**	result
**		Zeichenpuffer für das Ergebnis
**		es wird ein Zeiger auf dieses Array zurückgeliefert
**		NULL -> privates Array wird verwendet
**
**	value
**		Wert, der dargestellt werden soll
**
**	length
**		Gesamtl?nge des formatierten Wertes
**
**	fracDigits
**		Anzahl der Nachkommastellen
**
*/

typedef char t_format_result [40];

extern const char*
formatDouble (t_format_result result, double value, unsigned length, unsigned fracDigits);


/*-----------------------------------------------------------------------------------
   $Id: regression.h,v 1.3 2011/11/04 13:04:06 wolf Exp $
   -----------------------------------------------------------------------------------*/

/*
   Anzahl der "Stützstellen".
   Wenn nicht definiert, muss bei der Initialisierung des Kontrollblocks
   die Anzahl und ein Zeiger auf ein double-Array dieser Gr??e übergeben werden.
 */


/*
   Kontrollblock für die Berechnung
 */

typedef struct {
	double x;
	double y;
} t_regression_xy;

typedef struct {
	/* buffer */
	int size;
	t_regression_xy* values;
	/* storage */
	int index;
	/* sums */
	double n;
	double sx;
	double sy;
	double sxy;
	double sxx;
	double last_x;
	/* result */
	int valid;
	double s;
	double t;
} t_regression;


/*-----------------------------------------------------------------------------------
*		Initialisieren des Kontrollblocks
*----------------------------------------------------------------------------------*/

extern void
regressionInit (t_regression *rcb, int size, t_regression_xy buffer[]);

/*-----------------------------------------------------------------------------------
*		Rücksetzen des Kontrollblocks
*----------------------------------------------------------------------------------*/

extern void
regressionReset (t_regression *rcb);

/*-----------------------------------------------------------------------------------
*		Neues Datenpaar einarbeiten
*----------------------------------------------------------------------------------*/

extern void
regressionAdd (t_regression *rcb, double x, double y);

/*-----------------------------------------------------------------------------------
*		Uber Regression berechneter y-Wert zum letzten x-Wert
*----------------------------------------------------------------------------------*/

extern double
regressionActual (t_regression *rcb);

/*-----------------------------------------------------------------------------------
*		Uber Regression berechneter y-Wert zum angegeben x-Wert
*----------------------------------------------------------------------------------*/

extern double
regressionForecast (t_regression *rcb, double x);

/*-----------------------------------------------------------------------------------
*		Uber Regression berechneter x-Wert zum angegeben y-Wert
*----------------------------------------------------------------------------------*/

extern double
regressionReverse (t_regression *rcb, double y);

/*-----------------------------------------------------------------------------------
*		Steigung der Regressionsgrade, also ?nderung von y bei ?nderung von x
*----------------------------------------------------------------------------------*/

extern double
regressionChange (t_regression *rcb);

/*-----------------------------------------------------------------------------------
*		Qualit?t der Regression (0.0…1.0)
*----------------------------------------------------------------------------------*/

extern double
regressionQuality (t_regression *rcb);

/*-----------------------------------------------------------------------------------
   $Id: regression.h,v 1.3 2011/11/04 13:04:06 wolf Exp $
   -----------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------
**	$Id: sincos.h,v 1.2 2011/10/08 14:53:25 wolf Exp $
**---------------------------------------------------------------------------------*/

extern double
sin (double phi);

extern double
cos (double phi);

/*-----------------------------------------------------------------------------------
**	$Id: sincos.h,v 1.2 2011/10/08 14:53:25 wolf Exp $
**---------------------------------------------------------------------------------*/

#endif
