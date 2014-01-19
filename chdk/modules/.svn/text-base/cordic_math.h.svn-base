/*
CORDIC LIBRARY
integer based trigonometric mathematics
all values scaled by 100000 (CORDIC_SCALE)

based on http://www.andreadrian.de/c-workshop/index.html

(c)2012/2013 rudi from CHDK[-DE] forum
License GPL 2.0

trigonometric functions
    angle as DEG:
    sind, cosd, tand, asind, acosd, atand, recd, pold
    angle as RAD:
    sinr, cosr, tanr, asinr, acosr, atanr, recr, polr

additional functions
    integer calculation (a * b / c):
    fixed muldivScaled(fixed a , fixed b, fixed c)

additional math functions
    fixed fint(a)   get integer
    fixed fceil(a)  get largest previous integer
    fixed ffloor(a) get smallest following integer
    fixed fround(a) get nearest integer

all values in CORDIC routines are from type 'fixed' (4 byte integer)
    makros to convert values:
    FIXED(X) ...... convert double to cordic fixed
    FLOAT(X) ...... convert cordic fixed to double
    INT2FIXED(X) .. convert integer (value *1000) to cordic fixed
    INT2FIXEDR(X) . equal to INT2FIXED(X) with round
    FIXED2INT(X) .. convert cordic fixed to integer (value * 1000)
    FIXED2INTR(X) . equal to FIXED2INT(X) with round
*/

typedef long fixed;
typedef int int4b; //4 byte integer
enum fcordic {ROTATE, VECTOR};
typedef int fcordic;
enum tangle {RAD, DEG};
typedef int tangle;

enum {
    FRACTIONBITS = 17,
    N = 17,
    M = 9,
    CORDIC_SCALE = 1 << FRACTIONBITS,
    CORDIC_INTEGER = ~(CORDIC_SCALE - 1),
    INT_SCALE = 1000,
};

#include "limits.h"

#define FIXED(X)        (floatToFixed((X)))
#define FLOAT(X)        ((X) / (double)CORDIC_SCALE)
#define INT2FIXED(X)    (intToFixed((X), 0))
#define INT2FIXEDR(X)   (intToFixed((X), 1))
#define FIXED2INT(X)    (fixedToInt((X), 0))
#define FIXED2INTR(X)   (fixedToInt((X), 1))

//intern used functions
LUALIB_API void cordic(tangle t, fcordic f, fixed *x, fixed *y, fixed *z);
LUALIB_API fixed mulScaled(fixed a, fixed b);
LUALIB_API fixed divScaled(fixed a, fixed b);
LUALIB_API int convertToQ1(fixed *x, fixed *y);
LUALIB_API void convertFromQ1(fixed *x, fixed *y, int q);
LUALIB_API int rotateToQ1(tangle t, fixed *phi);
LUALIB_API void rotateFromQ1(tangle t, fixed *phi, int q);
LUALIB_API fixed cathetus(fixed x);
/* base CIRCULAR mode, ROTATE */
LUALIB_API void sincosCordic(tangle t, fixed phi, fixed *sinphi, fixed *cosphi);
/* base CIRCULAR mode, VECTOR */
LUALIB_API void atanhypCordic(tangle t, fixed px, fixed py, fixed *phi, fixed *hyp);
/* functions CIRCULAR mode, ROTATE */
LUALIB_API fixed sinCordic(tangle t, fixed phi);
LUALIB_API fixed cosCordic(tangle t, fixed phi);
LUALIB_API fixed tanCordic(tangle t, fixed phi);
LUALIB_API void recCordic(tangle t, fixed r, fixed theta, fixed *px, fixed *py);
/* functions CIRCULAR mode, VECTOR */
LUALIB_API fixed asinCordic(tangle t, fixed x);
LUALIB_API fixed acosCordic(tangle t, fixed x);
LUALIB_API fixed atanCordic(tangle t, fixed x);
LUALIB_API void polCordic(tangle t, fixed px, fixed py, fixed *r, fixed *theta);

// extern
// PI/2, PI, 2*PI
LUAI_DATA fixed FULL_CIRCLE[];
LUAI_DATA fixed HALF_CIRCLE[];
LUAI_DATA fixed QUART_CIRCLE[];
//used by macro
LUALIB_API fixed floatToFixed(double a);
LUALIB_API fixed intToFixed(int4b a, int round);
LUALIB_API int4b fixedToInt(fixed a, int round);
//additional
LUALIB_API fixed muldivScaled(fixed a, fixed b, fixed c);
// DEG
LUALIB_API fixed sind(fixed phi);
LUALIB_API fixed cosd(fixed phi);
LUALIB_API fixed tand(fixed phi);
LUALIB_API void recd(fixed r, fixed theta, fixed *px, fixed *py);
LUALIB_API fixed asind(fixed x);
LUALIB_API fixed acosd(fixed x);
LUALIB_API fixed atand(fixed x);
LUALIB_API void pold(fixed px, fixed py, fixed *r, fixed *theta);
// RAD
LUALIB_API fixed sinr(fixed phi);
LUALIB_API fixed cosr(fixed phi);
LUALIB_API fixed tanr(fixed phi);
LUALIB_API void recr(fixed r, fixed theta, fixed *px, fixed *py);
LUALIB_API fixed asinr(fixed x);
LUALIB_API fixed acosr(fixed x);
LUALIB_API fixed atanr(fixed x);
LUALIB_API void polr(fixed px, fixed py, fixed *r, fixed *theta);
//additional math
LUALIB_API fixed fint(fixed a);
LUALIB_API fixed fceil(fixed a);
LUALIB_API fixed ffloor(fixed a);
LUALIB_API fixed fround(fixed a);
