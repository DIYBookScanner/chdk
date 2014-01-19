--[[
**********************************
Licence: GPL
(c) 2012, 2013 msl, rudi
v0.8
required CHDK 1.2 r.2453 or higher
**********************************
@title Twilight

@param a Current Date?
@default a 1
@range a 0 1

@param y Year
@default y 0
@values y 2012 2013 2014 2015 2016 2017 2018 2019 2020

@param m Month
@default m 0
@values m Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec

@param d Day
@default d 30
@range d 1 31

@param s Daylight Saving Time?
@default s 0
@range s 0 1
]]

--------------------GLOBALS----------------------

local SCALE = imath.scale
local PI = imath.pi
local muldiv = imath.muldiv
local mul = imath.mul
local div = imath.div
local sind = imath.sind
local cosd = imath.cosd
local acosd = imath.acosd
local NOON = 12*SCALE
local DAY = 2*NOON

--data
h1 =  -833 --sunset/sunrise h=-50'
h2 = -6000 --civil twilight h= -6°
DST = s --daylight save time
location = {}

--------------------GLOBAL FUNCTIONS-------------

-- Split string and write in array  -> string.split(string,delimiter)
function string:split(delimiter)
    local result, str = { }, (string.gsub(self, delimiter, ","))        -- change delimiter to defined char ","
    for part in string.gmatch(str.. ",", "([%s%wäöüßÄÖÜ-]+)"..",") do   --split on ","
        result[#result+1] = part
    end
    return result
end

-- remove leading & trailing spaces -> string.trim(string)
function string:trim()
    return (string.gsub(self, "^%s*(.-)%s*$", "%1"))
end

-- returns integer and fraction part
function dec(val, div)
    return val/div, math.abs(val%div)
end

-- decimal degrees to degrees and minutes
function dmsfmt(val, div)
    if type(val) == "number" then
        local h, r = dec(val, div)
        return h, (dec(r*60, div))
    elseif type(val) == "boolean" then
        if val then return "++", "++" else return "--", "--" end
    end
end

-- date functions
function get_day_of_year(dd, mm, yyyy)
    return os.date("*t",os.time{year=yyyy, month=mm, day=dd})["yday"]
end

function day_max(mm, yyyy)
    local dd = mm == 2 and 29 or 31
    return get_day_of_year(1, mm+1, yyyy)==get_day_of_year(dd, mm, yyyy) and dd-1 or dd
end

function trim_day(dd, mm, yyyy)
    local day_limit = day_max(mm, yyyy)
    return dd > day_limit and day_limit or dd
end

--------------------FUNCTIONS--------------------

-- sunrise/sunset/twilight calculation
function sun_times(lat, lon, h, doy, tz)
    --[[
    based on http://lexikon.astronomie.info/zeitgleichung/
    doy: number of the day in the current year
    h  : angle of the sun above the horizon in decimal form * imath.scale
    lat: latitude in decimal form * imath.scale   [-90000 < lat < 90000]
    lon: longitude in decimal form * imath.scale  [-180000 <= lon <= 180000]
    tz : time zone in decimal form * imath.scale
    return: sunrise, sunset, sun top in decimal form * imath.scale
        * sunrise, sunset in decimal form * imath.scale
            or false for polar night or true for midnight sun
        * sun top in decimal form * imath.scale
    ]]
    --time equation: WOZ - MOZ = -0.171*sind(deg(0.0337) * T + deg(0.465)) - 0.1299*sind(deg(0.01787) * T - deg(0.168))
    local WOZ, MOZ = mul(sind(1931*doy+26127), -171), mul(sind(1024*doy-9626), 130)
    --Suntop = 12 + timezone - longitude /15 - time equation
    local top = (NOON+tz-div(lon, 15*SCALE)-(WOZ-MOZ)+DAY)%DAY
    --declination_deg = deg(0.4095)*sind(deg(0.016906)*(T-80.086))
    local D = muldiv(sind(muldiv(96864, doy*1000-80086,100000)), 23462, 1000)
    -- time difference = 12*arccos((sin(h) - sin(B)*sin(declination)) / (cos(B)*cos(declination)))/Pi
    --   part 1: (sin(h) - sin(B)*sin(declination)) / (cos(B)*cos(declination))
    local geo_ref = div((sind(h)-mul(sind(lat), sind(D))), mul(cosd(lat), cosd(D)))
    -- midnight sun/polar night => type="boolean"; true for midnight sun
    local rising, setting = (geo_ref < 0), (geo_ref < 0)
    if math.abs(geo_ref) <= SCALE then
        --   part 2: time difference = 12*arccos(geo_ref)/Pi = 12*acosd(geo_ref)/180°
        local time_diff = acosd(geo_ref)/15
        rising, setting = (top-time_diff+DAY)%DAY, (top+time_diff+DAY)%DAY
    end
    return rising, setting, top
end

-- timezone functions
tz_tab = {-660, -600, -540, -480, -420, -360, -300, -240, -210, -180, -150, -120, -60,
    0, 60, 120, 180, 210, 240, 270, 300, 330, 345, 360, 390, 420, 480, 540, 570, 600, 660, 720, 765}

function get_tz_index(tz_min)
    local res
    for i = 14, tz_min < 0 and 1 or #tz_tab, tz_min < 0 and -1 or 1 do
        if tz_tab[i] == tz_min then res = i break end
    end
    return res
end

function get_tz_value(tzi, dst)
    return ((dst == 1 and 60 or 0)+tz_tab[tzi])*100/6
end

function get_tz_str(tzi)
    return (tz_tab[tzi]==0 and "\177" or tz_tab[tzi] > 0 and "+" or "")..string.format("%d:%02d", dec(tz_tab[tzi],60))
end

-- dataset functions
function insert_dataset(datatab, pos)
    if #datatab == 4 then
        pos = pos or #location+1
        location[pos] = {}
        location[pos].name = datatab[1]
        location[pos].lat  = datatab[2]
        location[pos].lon  = datatab[3]
        location[pos].tz   = datatab[4]
    end
end

-- read geo data from a file
function load_data(dfile, mode) --mode 0=overwrite, 1=append
    if os.stat(dfile) then
        local id = #location
        local id_start = id
        if mode == 0 then id = 0 end
        local file = io.open(dfile)
        for line in file:lines(dfile) do
            if not string.find(line, "#") then
                local array = string.split(line,";")
                if array and #array == 4 and type(array[1]) == "string" then
                    array[1] = string.trim(array[1])
                    array[2] = tonumber(array[2])
                    array[3] = tonumber(array[3])
                    array[4] = get_tz_index(tonumber(array[4]))
                    if (type(array[2]) == "number") and (array[2] < 900  or array[2] > -900)  and
                       (type(array[3]) == "number") and (array[3] <= 1800 or array[3] >= -1800) and
                       (type(array[4]) == "number") then
                        id = id+1
                        insert_dataset(array, id)
                    end
                end
            end
        end
        file:close()
        return true, id-id_start
    else
        return false
    end
end

function call_data()
    --data_file = "A/CHDK/DATA/geo_data.txt"
    cls()
    print("File browser will open.")
    print("Choose a file.")
    console_redraw()
    sleep(2000)
    cls()
    data_file = file_browser("A/CHDK/DATA")
    if data_file ~= nil then
        data, count = load_data(data_file)
    else
        data = false
    end
    if data == false then
        print("Could not load external data!")
    else
        print(count, "records are read.")
    end
    console_redraw()
    sleep(2000)
end

function restore()
    cls()
    set_console_layout(0,0,25,5)
    set_console_autoredraw(1)
end

--------------------MAIN-----------------------
if get_mode() == true then
    set_record(false)
    while get_mode() do sleep(10) end
end

if not load_data("A/CHDK/DATA/geo_data.txt", 0) then --load user data from file
    insert_dataset({"London", 513, 0, get_tz_index(0)}) -- location, latitude 51.3°, longitude 0.0°, time zone +/- 0 (values in minutes)
end
location_id = 1

--date
year  = a == 1 and tonumber(os.date("%Y")) or 2012+y
month = a == 1 and tonumber(os.date("%m")) or m+1
day   = a == 1 and tonumber(os.date("%d")) or trim_day(d, month, year)

--user interface
cls()
set_console_layout(5,3,40,14)
set_console_autoredraw(0)

line = "-----------------------------------" 
location_id = 1

while true do
    DoY = get_day_of_year(day, month, year)
    Tz = get_tz_value(location[location_id].tz, DST)
    Lat = location[location_id].lat
    Lat_str = string.format("%d.%d°", dec(Lat, 10))
    Lon = location[location_id].lon
    Lon_str = string.format("%d.%d°", dec(Lon, 10))
    Lat, Lon = Lat*100, Lon*100
    sunrise, sunset, suntop = sun_times(Lat, Lon, h1, DoY, Tz)
    dawn, dusk              = sun_times(Lat, Lon, h2, DoY, Tz)
    cls()
    print(string.format(" [\18] %s  TZ: %s", location[location_id].name, get_tz_str(location[location_id].tz)))
    print(string.format("     %s %s %02d.%02d.%4d", Lat_str, Lon_str, day, month, year))
    print(line)
    print(string.format("      civil dawn: %02d:%02d clock",dmsfmt(dawn, SCALE)))
    print(string.format("         sunrise: %02d:%02d clock",dmsfmt(sunrise, SCALE)))
    print(string.format("         sun top: %02d:%02d clock",dmsfmt(suntop, SCALE)))
    print(string.format("          sunset: %02d:%02d clock",dmsfmt(sunset, SCALE)))
    print(string.format("      civil dusk: %02d:%02d clock",dmsfmt(dusk, SCALE)))
    print(line)
    print(" [SET] load geo data   [MENU] end")
    console_redraw()
    wait_click(0)
    if     is_pressed("down") then
        location_id = location_id + 1
        if location_id > #location then location_id = 1 end
    elseif is_pressed("up") then
        location_id = location_id - 1
        if location_id < 1 then location_id = #location end
    elseif is_pressed("set") then call_data()
    elseif is_pressed("menu") then break
    end
end

restore()
