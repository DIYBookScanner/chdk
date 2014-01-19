#include "camera_info.h"
#include "stdlib.h"
#include "math.h"
#include "gps_math.h"

/*-----------------------------------------------------------------------------------
**	$Id: gps_math.c, v 1.1 2011/11/20 genie01 Exp $
**---------------------------------------------------------------------------------*/

int fac(int n){

	int i;
	int f=1;
	for (i=2; i<=n; i++) f*=i;
	return(f);
}

/* double arccos(double x, int n){

	double ergebnis;
	double ergebnis1;
	double i;
	double f1;
	double f2;
	double f3;
	double f4;
	double f5;

	ergebnis = x;
	ergebnis1 = 0.0;
	i = 1;

	do
	{
		f1=pow(2,n) * fac(n);
		f2=fac(2*n) / (pow(2,n) * fac(n));
		f3=f2/f1;
		f4=pow(x,((2*n)+1));
		f5=(2*n)+1;

		ergebnis1 = f3 * f4 / f5;
		ergebnis += ergebnis1;

		i+=1;
	} while( (--n) );

	ergebnis = (3.141592653589793 * 0.5) - ergebnis;

	return ergebnis;
}
*/

double arctan(double x, int n){

	double ergebnis=0.0;
	int Vorzeichen;
	int i;

	if (abs(x) < 1 )
	{
		ergebnis = x;
		Vorzeichen = 0;
		i = 3;

		do
		{
			Vorzeichen ^= 1;
			ergebnis += ((pow(x, i)/i) * ((Vorzeichen) ? -1.0 : +1.0));
			i+=2;
		} while( (--n) ); // solange Gliedanzahl nicht null ist
	}

	if (abs(x) >= 1 )
	{
		if (x<-1) {ergebnis = 3.141592653589793* -0.5; }
		if (x>=1) {ergebnis = 3.141592653589793*0.5; }
		Vorzeichen = 0;
		i = 1;

		do
		{
			Vorzeichen ^= 1;
			ergebnis += ((1/(i*pow(x,i))) * ((Vorzeichen) ? -1.0 : +1.0));
			i+=2;
		} while( (--n) ); // solange Gliedanzahl nicht null ist

	}
	return ergebnis;
}

double arctan2(double y, double x){

	double ergebnis;

	ergebnis = 2.0 * arctan((y / (sqrt(x*x+y*y)+x)),30);

	return ergebnis;
}

/*-----------------------------------------------------------------------------------
**	$Id: gps_math.c, v 1.1 2011/11/20 genie01 Exp $
**---------------------------------------------------------------------------------*/

double floor (double arg) {
/*-----------------------------------------------------------------------------------
**	$Id: ceilfloor.c,v 1.2 2011/10/09 14:37:33 wolf Exp wolf $
**---------------------------------------------------------------------------------*/
/*----------------------------------------------------------
**	Gr??te ganze Zahl kleiner oder gleich dem Argument
*---------------------------------------------------------*/

	long long trunc = (double) (long long) arg;
	return arg>=0 || trunc==arg ? trunc : trunc - 1.0;
}

double ceil (double arg) {
/*----------------------------------------------------------
**	Kleinste ganze Zahl gr??er oder gleich dem Argument
*---------------------------------------------------------*/
	long long trunc = (double) (long long) arg;
	return arg<=0 || trunc==arg ? trunc : trunc + 1.0;
/*-----------------------------------------------------------------------------------
**	$Id: ceilfloor.c,v 1.2 2011/10/09 14:37:33 wolf Exp wolf $
**---------------------------------------------------------------------------------*/
}

/*-----------------------------------------------------------------------------------
   $Id: format_double.c,v 1.11 2011/09/23 16:08:12 wolf Exp wolf $
   -----------------------------------------------------------------------------------*/

#define MAXDIGITS  (18)
#define quad    long long

#undef  USE_LLI

static double doubleExpTable [MAXDIGITS+1] = {
	1.0,
	10.0,
	100.0,
	1000.0,
	10000.0,
	100000.0,
	1000000.0,
	10000000.0,
	100000000.0,
	1000000000.0,
	10000000000.0,
	100000000000.0,
	1000000000000.0,
	10000000000000.0,
	100000000000000.0,
	1000000000000000.0,
	10000000000000000.0,
	100000000000000000.0,
	1000000000000000000.0
};

double Round(double Zahl, int Stellen){
	return floor(Zahl * doubleExpTable[Stellen] + 0.5) / doubleExpTable[Stellen];
}

static quad quadExpTable[MAXDIGITS+1] = {
	1LL,
	10LL,
	100LL,
	1000LL,
	10000LL,
	100000LL,
	1000000LL,
	10000000LL,
	100000000LL,
	1000000000LL,
	10000000000LL,
	100000000000LL,
	1000000000000LL,
	10000000000000LL,
	100000000000000LL,
	1000000000000000LL,
	10000000000000000LL,
	100000000000000000LL,
	1000000000000000000LL
};

static t_format_result staticBuffer;

static int min (int a, int b) {
	return a<b ? a : b;
}

const char* formatDouble (t_format_result result, double value, unsigned length, unsigned fractDigits) {

	char* sign = "";
	quad expanded;
	quad integer, fract;
	unsigned integerDigits;
	char* p;
	int shift = 0;
	int origLength = length;

#ifndef USE_LLI
	char fractbuffer [20];
#endif

	/*-----------------------
	*	default buffer
	*----------------------*/

	if (!result) result = staticBuffer;

	/*-----------------------
	*	sanity: length
	*----------------------*/

	if (length ==0          ) length = sizeof(t_format_result)-1;
	if (length < 3          ) length = 3;
	if (length > sizeof(t_format_result)-1) length = sizeof(t_format_result)-1;

	/*-----------------------
	*	sanity: fract
	*----------------------*/

	if (fractDigits > MAXDIGITS) fractDigits = MAXDIGITS;
	if (fractDigits > length-3 ) fractDigits = length - 3;
	integerDigits = length - fractDigits - 1;

	/*-----------------------
	*	abs
	*----------------------*/

	if (value < 0) {
		value = -value;
		sign  = "-";
	}

	/*-----------------------
	*	scale
	*----------------------*/

	value = value * (double) quadExpTable[fractDigits] + 0.5;

	while (value >= 9223372036854775807.0 && shift < fractDigits) {
		shift++;
		value *= 0.1;
	}

	/*-----------------------
	*	general overflow?
	*----------------------*/

	if (value >= 9223372036854775807.0) {
		sprintf (result, "%*s", length, "***");
		return result;
	}

	/*-----------------------
	*	int+fract
	*----------------------*/

	expanded = (quad) value;
	integer = expanded / quadExpTable[fractDigits-shift];
	fract   = expanded % quadExpTable[fractDigits-shift] * quadExpTable[shift];

	/*-----------------------
	*	fixed overflow
	*----------------------*/

	if (integer >= quadExpTable[min(*sign ? integerDigits-1 : integerDigits, MAXDIGITS)]) {
		sprintf (result, "%*s", length, "***");
		return result;
	}

	/*-----------------------
	*	format
	*----------------------*/

#ifdef USE_LLI
	if (!origLength) {
		sprintf (result, "%s%lli.%0*lli", sign, integer, fractDigits, fract);
		return result;
	}
	sprintf (result, "%*lli.%0*lli", integerDigits, integer, fractDigits, fract);
#else
	if (fractDigits >= 10) {
		sprintf (fractbuffer, "%0*li%09li", fractDigits-9,
		         (long) (fract/1000000000),
		         (long) (fract%1000000000));
	} else {
		sprintf (fractbuffer, "%0*li", fractDigits, (long) fract);
	}

	if (integer >= 1000000000ll) {
		if (!origLength) {
			sprintf (result, "%s%li%09li.%s", sign,
			         (long) (integer/1000000000),
			         (long) (integer%1000000000),
			         fractbuffer);
			return result;
		}
		sprintf (result, "%*li%09li.%s", integerDigits-9,
		         (long) (integer/1000000000),
		         (long) (integer%1000000000),
		         fractbuffer);
	} else {
		if (!origLength) {
			sprintf (result, "%s%li.%s", sign, (long) integer, fractbuffer);
			return result;
		}
		sprintf (result, "%*li.%s", integerDigits, (long) integer, fractbuffer);
	}
#endif

	if (*sign) {
		p = result;
		while (p[1]==' ') p++;
		p[0] = *sign;
	}

	return result;
}

/*-----------------------------------------------------------------------------------
   $Id: regression.c,v 1.3 2011/11/04 13:04:06 wolf Exp $
   -----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
*		Initialisieren des Kontrollblocks
*----------------------------------------------------------------------------------*/

void regressionInit (t_regression *rcb, int size, t_regression_xy buffer[]) {
	rcb->size       = size;
	rcb->values     = buffer;
	regressionReset (rcb);
}

/*-----------------------------------------------------------------------------------
*		Rücksetzen des Kontrollblocks
*----------------------------------------------------------------------------------*/

void regressionReset (t_regression *rcb) {
	int i;
	rcb->n          = 0;
	rcb->sx         = 0.0;
	rcb->sy         = 0.0;
	rcb->sxx        = 0.0;
	rcb->sxy        = 0.0;
	rcb->last_x     = 0.0;
	rcb->valid      = 0;
	rcb->s          = 0.0;
	rcb->t          = 0.0;
	rcb->index      = 0;
	for (i=0; i<rcb->size; i++) {
		rcb->values[i].x = 0;
		rcb->values[i].y = 0;
	}
}

/*-----------------------------------------------------------------------------------
*		Neues Datenpaar einarbeiten
*----------------------------------------------------------------------------------*/

void regressionAdd (t_regression *rcb, double x, double y) {

	/* entferne alten Wert */

	if (rcb->n >= rcb->size) {
		double old_x   = rcb->values[rcb->index].x;
		double old_y   = rcb->values[rcb->index].y;
		rcb->values[rcb->index].x = 0;
		rcb->values[rcb->index].y = 0;
		rcb->n          -= 1;
		rcb->sx         -= old_x;
		rcb->sy         -= old_y;
		rcb->sxx        -= old_x*old_x;
		rcb->sxy        -= old_x*old_y;
		rcb->valid      = 0;
		rcb->s          = 0.0;
		rcb->t          = 0.0;
	}

	if (rcb->n < rcb->size) {
		rcb->n          += 1;
		rcb->sx         += x;
		rcb->sy         += y;
		rcb->sxx        += x*x;
		rcb->sxy        += x*y;
		rcb->valid      = 0;
		rcb->s          = 0.0;
		rcb->t          = 0.0;
		rcb->last_x     = x;
		rcb->values[rcb->index].x = x;
		rcb->values[rcb->index].y = y;
		rcb->index = (rcb->index+1) % rcb->size;
	}
}

/*-----------------------------------------------------------------------------------
*		Regression berechnen
*----------------------------------------------------------------------------------*/

static void regressionCompute (t_regression *rcb) {

	double det;

	if (rcb->valid) return;
	rcb->valid = -1;

	det = rcb->n*rcb->sxx - rcb->sx*rcb->sx;

	/* TODO: hier m?glicherweise ein abs(det)<epsilon */
	if (det==0.0) return;

	rcb->s = (rcb->n * rcb->sxy - rcb->sx * rcb->sy ) / det;
	rcb->t = (rcb->sxx*rcb->sy  - rcb->sx * rcb->sxy) / det;
	rcb->valid = 1;
}

/*-----------------------------------------------------------------------------------
*		Uber Regression berechneter y-Wert zum letzten x-Wert
*----------------------------------------------------------------------------------*/

double regressionActual (t_regression *rcb) {
	regressionCompute (rcb);
	return rcb->last_x * rcb->s + rcb->t;
}

/*-----------------------------------------------------------------------------------
*		Uber Regression berechneter y-Wert zum angegeben x-Wert
*----------------------------------------------------------------------------------*/

double regressionForecast (t_regression *rcb, double x) {
	regressionCompute (rcb);
	return x * rcb->s + rcb->t;
}

/*-----------------------------------------------------------------------------------
*		Uber Regression berechneter x-Wert zum angegeben y-Wert
*----------------------------------------------------------------------------------*/

double regressionReverse (t_regression *rcb, double y) {
	regressionCompute (rcb);
	return rcb->s != 0.0 ? (y - rcb->t) / rcb->s : 1e9;
}

/*-----------------------------------------------------------------------------------
*		Steigung der Regressionsgrade, also ?nderung von y bei ?nderung von x
*----------------------------------------------------------------------------------*/

double regressionChange (t_regression *rcb) {
	regressionCompute (rcb);
	return rcb->s;
}

/*-----------------------------------------------------------------------------------
*	Qualit?t der Regression (0..1)
*	(vereinfachte Implementierung, liefert 1, wenn Regression verfügbar, 0 sonst)
*	(vollst?ndige Implementierung wird nachgeliefert)
*----------------------------------------------------------------------------------*/

double regressionQuality (t_regression *rcb) {
	regressionCompute (rcb);
	return rcb->valid==1 ? 1.0 : 0.0;
}

/*-----------------------------------------------------------------------------------
   $Id: regression.c,v 1.3 2011/11/04 13:04:06 wolf Exp $
   -----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
**	$Id: sincos.c,v 1.2 2011/10/08 14:53:25 wolf Exp $
**---------------------------------------------------------------------------------*/

extern double floor (double arg);
extern double sqrt (double arg);

/*---------------------------------------------------------------
**	Hilfsfunktionen mit eingeschr?nktem Wertebereich
**	-pi/4 .. +pi/4
**-------------------------------------------------------------*/

static double _sin (double arg) {
	double sum     = arg;
	double msqarg  = -arg*arg;
	double term    = arg;
	int i;
	/*------------------------------------------------------
	** für h?here Genauigkeit umgekehrte Reihenfolge!
	**----------------------------------------------------*/
	for (i=2; i<=14; i+=2) {
		term *= msqarg / (i*(i+1));
		sum  += term;
	}
	return sum;
}

static double _cos (double arg) {
	double s = _sin (arg);
	return sqrt (1.0 - s*s);
}

/*---------------------------------------------------------------
**	double hat 52 bit Genauigkeit,
**	daher Pi mit 16 Stellen
**-------------------------------------------------------------*/

#define PIBY2   (3.141592653589793 / 2.0)

/*---------------------------------------------------------------
**	Funktionen mit Wertebereich ungef?hr
**	-10^9 .. +10^9
**-------------------------------------------------------------*/

double sin (double phi) {
	long periode = (long) floor (phi / PIBY2 + 0.5);
	double reduced = phi - PIBY2 * periode;
	switch (periode&3) {
	default:
		return _sin (reduced);
	case 1:
		return _cos (reduced);
	case 2:
		return -_sin (reduced);
	case 3:
		return -_cos (reduced);
	}
}

double cos (double phi) {
	long periode = floor (phi / PIBY2 + 0.125);
	double reduced = phi - PIBY2 * periode;
	switch (periode&3) {
	default:
		return _cos (reduced);
	case 1:
		return -_sin (reduced);
	case 2:
		return -_cos (reduced);
	case 3:
		return _sin (reduced);
	}
}

/*-----------------------------------------------------------------------------------
**	$Id: sincos.c,v 1.2 2011/10/08 14:53:25 wolf Exp $
**---------------------------------------------------------------------------------*/
