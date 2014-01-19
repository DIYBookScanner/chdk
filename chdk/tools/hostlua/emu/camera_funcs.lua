local camera_funcs = {}
-- keys
function camera_funcs.shoot()
    if camera_state.raw > 0 then
        camera_state.tick_count = camera_state.tick_count + 3000
    else
        camera_state.tick_count = camera_state.tick_count + 1000
    end
    camera_state.image_counter = camera_state.image_counter + 1
end

function camera_funcs.press(s)
        print(">press<", s)
end

function camera_funcs.release(s)
        print(">release<", s)
        if s == "shoot_full" or s == "shoot_full_only" then
            camera_state.image_counter = camera_state.image_counter + 1
        end
end

function camera_funcs.click(s)
        print(">click<", s)
        if s == "shoot_full" or s == "shoot_full_only" then
            camera_state.image_counter = camera_state.image_counter + 1
        end
end

function camera_funcs.wheel_left()
        print(">wheel left<")
end

function camera_funcs.wheel_right()
        print(">wheel right<")
end

function camera_funcs.wait_click(n)
        print(">wait click<", n)
end

function camera_funcs.is_key()
        -- needs logic
end

function camera_funcs.is_pressed()
        -- needs logic
end

-- exposure
function camera_funcs.get_av96()
    return camera_state.av96
end

function camera_funcs.get_bv96()
    return camera_state.bv96
end

function camera_funcs.get_tv96()
    return camera_state.tv96
end

function camera_funcs.get_sv96()
    return camera_state.sv96
end

function camera_funcs.get_nd_present()
    return 0
end

function camera_funcs.set_nd_filter(n)
    camera_state.nd=n
end

function camera_funcs.get_ev()
    return camera_state.ev96
end

function camera_funcs.set_ev(n)
    camera_state.ev96=n
end

function camera_funcs.set_tv96_direct(n)
    camera_state.tv96=n
end

function camera_funcs.set_av96_direct(n)
    camera_state.av96=n
end

function camera_funcs.set_tv96(n)
    camera_state.tv96=n
end

function camera_funcs.set_av96(n)
    camera_state.av96=n
end

function camera_funcs.set_sv96(n)
    camera_state.sv96=n
end

function camera_funcs.get_iso_mode()
    return 0
end

function camera_funcs.get_iso_market()
    return 0
end

function camera_funcs.set_iso_mode(n)
    -- needs logic
end

function camera_funcs.set_iso_real(n)
    -- needs logic
end

-- raw
function camera_funcs.set_raw(n)
    if n == 0 or n == 1 then camera_state.raw = n end
end

function camera_funcs.get_raw()
    return camera_state.raw
end

function camera_funcs.get_raw_count()
    return 100
end

function camera_funcs.get_IS_mode()
    return camera_state.IS_mode
end


-- script status
function camera_funcs.sleep(n)
    camera_state.tick_count=camera_state.tick_count+n
end

function camera_funcs.get_tick_count()
    return camera_state.tick_count
end

function camera_funcs.autostarted()
    return camera_state.autostart
end

function camera_funcs.get_day_seconds()
    local H=os.date("%H")*60*60
    local M=os.date("%M")*60
    local S=os.date("%S")
    return H+M+S
end

function camera_funcs.get_time(c)
  if c=="D" then 
    return os.date("%d")
  elseif c=="M" then 
    return os.date("%m")
  elseif c=="Y" then 
    return os.date("%Y")
  elseif c=="h" then
    return os.date("%H")
  elseif c=="m" then
    return os.date("%M")
  elseif c=="s" then
    return os.date("%S")
  else 
    return 9999
  end
end

-- sd card
function camera_funcs.get_disk_size()
    return camera_state.disk_size
end

function camera_funcs.get_free_disk_space(n)
    return 1000000
end

-- text console
function camera_funcs.cls()
    print(">delete screen<")
end

function camera_funcs.print_screen(n)
    if n == 0 or n == false then
        print(">write log file off<")
    elseif n == -1000 then
        print(">write log file append<")
    else
        print(">write log file on<")
    end
end

function camera_funcs.set_console_layout(n, m, o, p)
    print(">change console layout<", n, m, o, p)
end

function camera_funcs.console_redraw()
    print(">redraw console<")
end

function camera_funcs.set_console_autoredraw(n)
    print(">redraw console<", n)
end

function camera_funcs.draw_string(col,row,msg,c1,c2)
    print("draw string @ " .. col..":"..row.." Colors:"..c1..":","Msg> "..msg)
end

-- lens & focus
function camera_funcs.get_focus()
    return camera_state.focus
end

function camera_funcs.set_focus(n)
    camera_state.focus=n
end

function camera_funcs.get_focus_mode()
    return camera_state.f_mode
end

function camera_funcs.get_dofinfo()
    return {
            hyp_valid = true,
            focus_valid = true,
            aperture = 2679,
            coc = 5,
            focal_length = 5800,
            eff_focal_length = 35000,
            focus = 200,
            near = 135,
            far = 3400,
            dof = 3400 - 135,
            hyp_dist = 2517,
            min_stack_dist = 100
    }
end

function camera_funcs.get_zoom_steps()
    return camera_state.zoom_steps
end

function camera_funcs.get_zoom()
    return camera_state.zoom
end

function camera_funcs.set_zoom(n)
    camera_state.zoom=n
end

function camera_funcs.set_aflock(n)
    if n == 1 then print(">aflock on<") end
    if n == 0 then print(">aflock off<") end
end

--camera
function camera_funcs.shutdown()
    print("shutdown camera ...")
end

function camera_funcs.get_propset()
    return camera_state.propset
end

function camera_funcs.get_prop(prop)
    return camera_state.props[prop]
end

function camera_funcs.set_prop(prop, val)
    camera_state.props[prop]=val
end

-- return 1 or 0, depending on system clock... a quick&dirty simulation for shooting process
-- TODO could / should base on shoot(), shoot_full etc
function camera_funcs.get_shooting()
    if os.date("%S")%3 == 1 then 
        return true
    else
        return false
    end
end

function camera_funcs.get_temperature(n)
    return 40
end

function camera_funcs.peek(n)
    return 0
end

function camera_funcs.get_buildinfo()
    return {
            platform="PC",
            platsub="sub",
            version="PC Emulation CHDK",
            build_number="999",
            build_revision="5555";
            build_date=os.date("%x"),
            build_time=os.date("%X"),
            os="vxworks",
            platformid=0xDEADBEEF,
    }
end

function camera_funcs.get_vbatt()
    return 3000
end

function camera_funcs.get_jpg_count()
    return 1000
end

function camera_funcs.get_image_dir()
    return "A/DCIM/100CANON"
end

function camera_funcs.get_exp_count()
    return camera_state.image_counter
end

function camera_funcs.play_sound(n)
    print("beep", n)
end

function camera_funcs.set_led(n, s)
    if s == 1 then print("LED", n, "on") end
    if s == 0 then print("LED", n, "off") end
end

function camera_funcs.set_backlight(n)
    if n == 1 then print(">Backlight on<") end
    if n == 0 then print(">Backlight off<") end
end

function camera_funcs.get_mode()
    return camera_state.rec, camera_state.vid, camera_state.mode
end

function camera_funcs.set_record(n)
    if n == 1  or n == true then
        camera_state.rec = true
        print("record mode")
    elseif n == 0  or n == false then
        camera_state.rec = false
        print("play mode")
    end
end

function camera_funcs.get_drive_mode()
    return camera_state.drive
end

function camera_funcs.get_flash_mode()
    return camera_state.flash
end

-- motion detection
function camera_funcs.md_detect_motion()
    return 1
end

-- histogram
function camera_funcs.shot_histo_enable(s)
    local x=n
end

function camera_funcs.get_histo_range(n1,n2)
    return 100
end

return camera_funcs
