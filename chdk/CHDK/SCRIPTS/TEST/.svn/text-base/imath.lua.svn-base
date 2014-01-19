--[[
********************************************
Licence: GPL
(C)2012 rudi, Version: 0.2

imath library test
    integer based trigonometric functions
    use CORDIC algorithm
********************************************
@title imath functions V0.2
]]

-- Int2Str(value[,x10^dpow:default=0[, unit:string][, fix:number]])
function Int2Str(val, dpow, ...)
    local _dpow, _sign, _val, _unit, _fix = dpow or 0, (val < 0) and "-" or "", tostring(math.abs(val))
    for i = 1, select('#', ...) do
        local _arg = select(i, ...)
        if not _unit and type(_arg) == "string" and #_arg > 0 then _unit = _arg
        elseif not _fix and type(_arg) == "number" and _arg >= 0 then _fix = _arg
        end
    end
    _val = (_dpow < 0) and string.rep("0", 1 - #_val - _dpow) .. _val or _val .. string.rep("0", _dpow)
    local _int, _frac = string.match(_val, "^([%d]+)(" .. string.rep("%d", -_dpow) .. ")$")
    _frac = _fix and string.sub((_frac or "") .. string.rep("0", _fix), 1, _fix) or _frac
    _frac = (_frac and type(_frac) == "string" and #_frac > 0) and "." .. _frac or ""
    return  string.format("%s%s%s%s", _sign, _int, _frac, _unit or "")
end

function str1E3(val)
    return Int2Str(val, -3)
end

function str1E3f(val)
    return Int2Str(val, -3, 0)
end

function printf(...)
    print(string.format(...))
end

-- constants
scale = imath.scale

x = 4 * scale                                       -- 4.000
y = 3 * scale                                       -- 3.000
z = 2 * scale                                       -- 2.000
hyp = imath.sqrt(imath.mul(x, x) + imath.mul(y, y)) -- 5.000

phi_deg = 30 * scale                                -- 30 deg
phi_rad = imath.div(imath.pi_2, y)                  -- (PI/2)/3 equal 30 deg


-----MAIN-----
set_console_layout(0,0,40,12)


print("constants:")
printf("scale = %s", Int2Str(scale))
printf("2*PI = %s", str1E3(imath.pi2))
printf("PI = %s", str1E3(imath.pi))
printf("PI/2 = %s", str1E3(imath.pi_2))
print()
print("press key for page 2")
wait_click(0)
cls()
print("Scaled value basics:")
printf("%s * %s / %s = %s", str1E3f(hyp), str1E3f(x), str1E3f(y), str1E3(imath.muldiv(hyp, x, y)))
printf("%s * %s = %s", str1E3f(x), str1E3f(y), str1E3(imath.mul(x, y)))
printf("%s / %s = %s", str1E3f(hyp), str1E3f(x), str1E3(imath.div(hyp, x)))
printf("rad(%s) = %s", str1E3(phi_deg), str1E3(imath.rad(phi_deg)))
printf("deg(%s) = %s", str1E3(phi_rad), str1E3(imath.deg(phi_rad)))
print()
print("press key for page 3")
wait_click(0)
cls()
print("RAD trigonometry:")
-- sinr, cosr, tanr
sin_rad = imath.sinr(phi_rad)
cos_rad = imath.cosr(phi_rad)
tan_rad = imath.tanr(phi_rad)
printf("sinr(%s) = %s", str1E3(phi_rad), str1E3(sin_rad))
printf("cosr(%s) = %s", str1E3(phi_rad), str1E3(cos_rad))
printf("tanr(%s) = %s", str1E3(phi_rad), str1E3(tan_rad))
-- asinr, acosr, atanr
asin_rad = imath.asinr(sin_rad)
acos_rad = imath.acosr(cos_rad)
atan_rad = imath.atanr(tan_rad)
printf("asinr(%s) = %s", str1E3(sin_rad), str1E3(asin_rad))
printf("acosr(%s) = %s", str1E3(cos_rad), str1E3(acos_rad))
printf("atanr(%s) = %s", str1E3(tan_rad), str1E3(atan_rad))
--recr to polr
vektor, angel = imath.polr(x, y)
printf("recr(%s, %s) = polr(%s, %s)", str1E3(x), str1E3(y), str1E3(vektor), str1E3(angel))
--polr to recr
_x, _y = imath.recr(vektor, angel)
printf("polr(%s, %s) = recr(%s, %s)", str1E3(vektor), str1E3(angel), str1E3(_x), str1E3(_y))
print()
print("press key for page 4")
wait_click(0)
cls()
print("DEG trigonometry:")
-- sind, cosd, tand
sin_deg = imath.sind(phi_deg)
cos_deg = imath.cosd(phi_deg)
tan_deg = imath.tand(phi_deg)
printf("sind(%s) = %s", str1E3(phi_deg), str1E3(sin_deg))
printf("cosd(%s) = %s", str1E3(phi_deg), str1E3(cos_deg))
printf("tand(%s) = %s", str1E3(phi_deg), str1E3(tan_deg))
-- asind, acosd, atand
asin_deg = imath.asind(sin_deg)
acos_deg = imath.acosd(cos_deg)
atan_deg = imath.atand(tan_deg)
printf("asind(%s) = %s", str1E3(sin_deg), str1E3(asin_deg))
printf("acosd(%s) = %s", str1E3(cos_deg), str1E3(acos_deg))
printf("atand(%s) = %s", str1E3(tan_deg), str1E3(atan_deg))
--recd to pold
vektor, angel = imath.pold(x, y)
printf("recd(%s, %s) = pold(%s, %s)", str1E3(x), str1E3(y), str1E3(vektor), str1E3(angel))
--pold to recd
_x, _y = imath.recd(vektor, angel)
printf("pold(%s, %s) = recd(%s, %s)", str1E3(vektor), str1E3(angel), str1E3(_x), str1E3(_y))
print()
print("press key for page 5")
wait_click(0)
cls()
print("additional math page 1:")
val = x + 500   -- 4.500
printf("int(%s) = %s", str1E3(val), str1E3(imath.int(val)))
printf("frac(%s) = %s", str1E3(val), str1E3(imath.frac(val)))
printf("ceil(%s) = %s", str1E3(val), str1E3(imath.ceil(val)))
printf("floor(%s) = %s", str1E3(val), str1E3(imath.floor(val)))
printf("round(%s) = %s", str1E3(val), str1E3(imath.round(val)))
print()
print("press key for page 6")
wait_click(0)
cls()
print("additional math page 2:")
pow = imath.pow(z, x)
const_1E3 = 1000 * scale
printf("log(%s) = %s", str1E3(pow), str1E3(imath.log(pow)))
printf("log2(%s) = %s", str1E3(pow), str1E3(imath.log2(pow)))
printf("log10(%s) = %s", str1E3(const_1E3), str1E3(imath.log10(const_1E3)))
printf("pow(%s, %s) = %s", str1E3(z), str1E3(x), str1E3(pow))
printf("pow(%s, 1/%s) = %s", str1E3(pow), str1E3(x), str1E3(imath.pow(pow, imath.div(scale,x))))
printf("sqrt(%s) = %s", str1E3(pow), str1E3(imath.sqrt(pow)))
print()
print("press key for end")
wait_click(0)
cls()
