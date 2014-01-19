--[[
********************************
Licence: GPL
(c) 2009-2012 reyalp, rudi, msl, fbonomi
v 0.1
********************************

http://chdk.setepontos.com/index.php?topic=2929.0
based dummy.lua by fbonomi

Script to run CHDK lua scripts, emulating as much of the camera as required in lua
Should be used with lua from "hostlua" in the CHDK source tree
--]]
local usage_string=[[
usage: lua emu.lua <chdk_script> [-conf=<conf_script>] [-modroot=<cam module root>] [-a=X -b=Y ...]
    <chdk_script> is the script to be tested
    <conf_script> is a lua script customizing the test case
	<cam module root> is directory for emulated require to look for SCRIPTS and LUALIB
    -a=X etc set the corresponding script parameter to the given value
]]

-- global environment seen by chdk_script
local camera_env={
}
-- copy the global environment, before we add our own globals
for k,v in pairs(_G) do
    camera_env[k]=v;
end

-- table to track state used by emulated camera functions
-- global so it's accessible to camera funcs
camera_state={
    tick_count=0,               -- sleep, tick count
    image_counter=1000,         -- current image number (IMG_1000.JPG)
    raw=0,
    mem={},                     -- peek and poke
    av96=0,
    bv96=0,
    tv96=0,
    sv96=0,
    ev96=0,
    nd=0,
    disk_size=1024*1024*1024,
    propset=4,                  -- propset 1 - 5
    rec=false,
    vid=false,
    mode=1,
    drive=0,                    -- 0 = single 1 = continuous 2 = timer (on Digic 2) 3 = timer (on Digic 3,4,5)
    flash=0,                    -- 0 = flash auto, 1 = flash on, 2 = flash off
    focus=1000,
    f_mode=0,                   --focus mode, 0=auto, 1=MF, 3=inf., 4=macro, 5=supermacro
    zoom_steps=125,
    zoom=0,
    autostart=0,
    IS_mode=0,
	props={}, -- propcase values
}


-- TODO not used
local buttons={"up", "down", "left", "right", "set", "shoot_half", "shoot_full", "shoot_full_only", "zoom_in", "zoom_out", "menu", "display"}

-- fill propertycases
for i=0, 400 do
    camera_state.props[i]=0
end

-- root to search for camera modules
local camera_module_root = 'A/CHDK'

local camera_funcs=require'camera_funcs'

-- and tidy some things up
camera_env._G=camera_env
camera_env.arg=nil
camera_env.package = {
	loaded={}
}
-- mark stuff that would be loaded on cam as loaded
for i,k in ipairs({'string','debug','package','_G','io','table','math','coroutine','imath'}) do
	camera_env.package.loaded[k] = package.loaded[k]
end
-- make a version of require that runs the module in the camera environment
camera_env.require=function(mname)
	if camera_env.package.loaded[mname] then
		return camera_env.package.loaded[mname]
	end
	-- TODO CHDK now honors package.path, this only does defaults!
	local f=loadfile(camera_module_root..'/SCRIPTS/'..mname..'.lua')
	if not f then
		f=loadfile(camera_module_root..'/LUALIB/'..mname..'.lua')
	end
	if not f then
		error("camera module '"..tostring(mname).."' not found")
	end
	setfenv(f,camera_env)
	camera_env.package.loaded[mname]=f()
	return camera_env.package.loaded[mname]
end

local script_title

local script_params={
}

local header_item_funcs={
    title=function(line,line_num)
        local s=line:match("%s*@[Tt][Ii][Tt][Ll][Ee]%s*(.*)")
        if s then 
            if script_title then
                print("warning, extra @title line",line_num)
            else
                script_title = s
                print("title:",s)
            end
            return true
        end
    end,
    param=function(line,line_num)
        local param_name,param_desc=line:match("%s*@[Pp][Aa][Rr][Aa][Mm]%s*([A-Za-z])%s*(.*)")
        if param_name and param_desc then
            if not script_params[param_name] then
                script_params[param_name] = { desc=param_desc }
            elseif script_params[param_name].desc then
                print("warning, extra @param",param_name,"line",line_num)
            else
                script_params[param_name].desc = param_desc
            end
            print("param",param_name,param_desc)
            return true
        end
    end,
    default=function(line,line_num)
        local param_name,param_default=line:match("%s*@[Dd][Ee][Ff][Aa][Uu][Ll][Tt]%s*([A-Za-z])%s*([0-9]+)")
        if param_name and param_default then
            if not script_params[param_name] then
                script_params[param_name] = { default=param_default }
            elseif script_params[param_name].default then
                print("warning, extra @default",param_name,param_default,"line",line_num)
            else
                script_params[param_name].default = tonumber(param_default)
            end
            print("default",param_name,param_default)
            return true
        end
    end,
}

function parse_script_header(scriptname)
    local line_num
    line_num = 0
    for line in io.lines(scriptname) do 
        for k,f in pairs(header_item_funcs) do
            if f(line,line_num) then
                break
            end
        end
        line_num = line_num + 1
    end
    if not script_title then
        script_title="<no title>"
    end
    -- set the params to their default values
    for name,t in pairs(script_params) do
        if t.default then
            camera_env[name] = t.default
        else
            print("warning param",name,"missing default value")
            camera_env[name] = 0
        end
    end
end

function usage()
    error(usage_string,0)
end

chdk_script_name=arg[1]
if not chdk_script_name then
    usage()
end

parse_script_header(chdk_script_name)

local i=2
while arg[i] do
    local opt,val=arg[i]:match("-([%w_]+)=(.*)")
    if opt and val then
        opt=opt:lower()
        if opt == "conf" then
            print("conf =",val)
            conf_script=val
        elseif opt == "modroot" then
            print("modroot =",val)
            camera_module_root=val
        elseif opt:match("^%l$") then
            local n=tonumber(val)
            if n then
                print("param",opt,"=",val)
                camera_env[opt]=val
            else
                print("expected number for",opt,"not",val)
            end
        end
    else 
        print("bad arg",tostring(arg[i]))
    end
    i=i+1
end
if conf_script then
	dofile(conf_script)
end

-- import the base camera functions, after conf so it can modify
for k,v in pairs(camera_funcs) do
    camera_env[k]=v;
end

local chdk_script_f,err = loadfile(chdk_script_name)
if err then
    error("error loading " .. chdk_script_name .. " " .. err)
end
setfenv (chdk_script_f, camera_env)
local status,result = pcall(chdk_script_f)
if not status then
    error("error running " .. chdk_script_name .. " " .. result)
end
