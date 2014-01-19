/*
limathlib.c,v 1.1
integer based trigonometric mathematics
all values scaled by 1000 (imath.scale)

(c)2012 rudi from CHDK[-DE] forum
License GPL 2.0
*/

#include "stdlib.h"
#include "math.h"

#define limathlib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"
#include "cordic_math.h"

LUALIB_API double intToFloat(int val) {
    return FLOAT(INT2FIXED(val));
}

LUALIB_API int floatToInt(double val) {
    return FIXED2INTR(FIXED(val));
}

static int imath_muldiv (lua_State *L) {
    int c = luaL_checknumber(L, 3);
    if (c == 0) luaL_error(L, "divide by 0");
    lua_pushnumber(L, muldivScaled(luaL_checknumber(L, 1),
        luaL_checknumber(L, 2), c));
    return 1;
}

static int imath_mul (lua_State *L) {
    lua_pushnumber(L, muldivScaled(luaL_checknumber(L, 1),
        luaL_checknumber(L, 2), INT_SCALE));
    return 1;
}

static int imath_div (lua_State *L) {
    int c = luaL_checknumber(L, 2);
    if (c == 0) luaL_error(L, "divide by 0");
    lua_pushnumber(L, muldivScaled(INT_SCALE, luaL_checknumber(L, 1), c));
    return 1;
}

// RAD
static int imath_sinr (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(sinr(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_cosr (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(cosr(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_tanr (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(tanr(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_recr (lua_State *L) {
    fixed px, py;
    recr(INT2FIXED(luaL_checknumber(L, 1)),
        INT2FIXED(luaL_checknumber(L, 2)), &px, &py);
    lua_pushnumber(L, FIXED2INTR(px));
    lua_pushnumber(L, FIXED2INTR(py));
    return 2;
}

static int imath_asinr (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(asinr(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_acosr (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(acosr(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_atanr (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(atanr(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_polr (lua_State *L) {
    fixed r, theta;
    polr(INT2FIXED(luaL_checknumber(L, 1)),
        INT2FIXED(luaL_checknumber(L, 2)), &r, &theta);
    lua_pushnumber(L, FIXED2INTR(r));
    lua_pushnumber(L, FIXED2INTR(theta));
    return 2;
}

// DEG
static int imath_sind (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(sind(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_cosd (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(cosd(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_tand (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(tand(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_recd (lua_State *L) {
    fixed px, py;
    recd(INT2FIXED(luaL_checknumber(L, 1)),
        INT2FIXED(luaL_checknumber(L, 2)), &px, &py);
    lua_pushnumber(L, FIXED2INTR(px));
    lua_pushnumber(L, FIXED2INTR(py));
    return 2;
}

static int imath_asind (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(asind(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_acosd (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(acosd(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_atand (lua_State *L) {
    lua_pushnumber(L, FIXED2INTR(atand(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_pold (lua_State *L) {
    fixed r, theta;
    pold(INT2FIXED(luaL_checknumber(L, 1)),
        INT2FIXED(luaL_checknumber(L, 2)), &r, &theta);
    lua_pushnumber(L, FIXED2INTR(r));
    lua_pushnumber(L, FIXED2INTR(theta));
    return 2;
}

static int imath_deg (lua_State *L) {
    lua_pushnumber(L, floatToInt(intToFloat(luaL_checknumber(L, 1)) * 180 / M_PI));
    return 1;
}

static int imath_rad (lua_State *L) {
    lua_pushnumber(L, floatToInt(intToFloat(luaL_checknumber(L, 1)) * M_PI / 180));
    return 1;
}

static int imath_log (lua_State *L) {
    lua_pushnumber(L, floatToInt(log(intToFloat(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_log2 (lua_State *L) {
    lua_pushnumber(L, floatToInt(log2(intToFloat(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_log10 (lua_State *L) {
    lua_pushnumber(L, floatToInt(log10(intToFloat(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_pow (lua_State *L) {
    lua_pushnumber(L, floatToInt(pow(intToFloat(luaL_checknumber(L, 1)),
        intToFloat(luaL_checknumber(L, 2)))));
    return 1;
}

static int imath_sqrt (lua_State *L) {
    lua_pushnumber(L, floatToInt(sqrt(intToFloat(luaL_checknumber(L, 1)))));
    return 1;
}

//additional math
static int imath_int (lua_State *L) {
    lua_pushnumber(L, FIXED2INT(fint(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_frac (lua_State *L) {
    lua_pushnumber(L, luaL_checknumber(L, 1) - FIXED2INT(fint(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_ceil (lua_State *L) {
    lua_pushnumber(L, FIXED2INT(fceil(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_floor (lua_State *L) {
    lua_pushnumber(L, FIXED2INT(ffloor(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static int imath_round (lua_State *L) {
    lua_pushnumber(L, FIXED2INT(fround(INT2FIXED(luaL_checknumber(L, 1)))));
    return 1;
}

static const luaL_Reg imathlib[] = {
    {"muldiv", imath_muldiv},
    {"mul",    imath_mul},
    {"div",    imath_div},
    {"sinr",   imath_sinr},
    {"cosr",   imath_cosr},
    {"tanr",   imath_tanr},
    {"recr",   imath_recr},
    {"asinr",  imath_asinr},
    {"acosr",  imath_acosr},
    {"atanr",  imath_atanr},
    {"polr",   imath_polr},
    {"sind",   imath_sind},
    {"cosd",   imath_cosd},
    {"tand",   imath_tand},
    {"recd",   imath_recd},
    {"asind",  imath_asind},
    {"acosd",  imath_acosd},
    {"atand",  imath_atand},
    {"pold",   imath_pold},
    {"deg",    imath_deg},
    {"rad",    imath_rad},
    {"log",    imath_log},
    {"log2",   imath_log2},
    {"log10",  imath_log10},
    {"pow",    imath_pow},
    {"sqrt",   imath_sqrt},
    {"int",    imath_int},
    {"frac",   imath_frac},
    {"ceil",   imath_ceil},
    {"floor",  imath_floor},
    {"round",  imath_round},
    {NULL, NULL}
};


/*
** Open imath library
*/
LUALIB_API int luaopen_imath (lua_State *L) {
    luaL_register(L, LUA_IMATHLIBNAME, imathlib);

    lua_pushnumber(L, INT_SCALE);
    lua_setfield(L, -2, "scale");
    lua_pushnumber(L, FIXED2INTR(FULL_CIRCLE[RAD]));
    lua_setfield(L, -2, "pi2");
    lua_pushnumber(L, FIXED2INTR(HALF_CIRCLE[RAD]));
    lua_setfield(L, -2, "pi");
    lua_pushnumber(L, FIXED2INTR(QUART_CIRCLE[RAD]));
    lua_setfield(L, -2, "pi_2");

    return 1;
}
