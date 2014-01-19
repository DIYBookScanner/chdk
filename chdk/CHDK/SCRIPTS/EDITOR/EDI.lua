--[[
@title EDI - text editor
@param n Newline  (0=Windows 1=Unix)
@default n 0
@values n Windows Unix
@param y Editor height
@default y 14
@range y 10 20
@param x Editor width
@default x 40
@range x 30 50
@param s Browser in SCRIPTS? (1=Yes)
@default s 1
@range s 0 1
@param a Write a new file?   (1=Yes)
@default a 0
@range a 0 1
@param b Do backups?          (0=No)
@default b 1
@range b 0 1
--@param z Has this camera zoom?(0=NO)
--@default z 1
--]]
--[[
    Version:    2.7
    Author:     Pawel Tokarz aka outslider
    License:    GPL 3+;see: http://www.gnu.org/licenses/gpl-3.0.html
                in order to use with GPL<3: You can also use it with GPL<3 software.

    ----------------------------------------------------------------
    |  This version requires CHDK with Virtual Keyboard module!!!  |
    ----------------------------------------------------------------

    Changelog for 2.x series:
    - 'new file' option added
    - empty file opening fixed (however really empty file can't be saved, it'll contain \n at least...)
    - usage of text_box() for 'save as...' and new file name (thx for TobiMarg, tsvstar, philmoz, msl and others)
    - some changes in menu() function
    - fixed bug while browser is closed
    - erase in MOVE mode jumps to the begin of the file
    - more staff added but might be not mentioned

    More info you can find on CHDK Forum http://chdk.setepontos.com/index.php?topic=6465.0
    
    additionally: the biggest file I successfully opened on SX130IS had 916 kB. Opening 962 kB file failed. Other cameras has different size of free memory, nevertheless opening average scripts as 5-10 kb shouldn't cause any problems.
--]]

-- CHECK GIVEN PARAMETERS --
if y<5 then y=5 end
if x<10 then x=10 end
--maximal x and y belong to the user

if n>1 then
    print("Newline setting incorrect")
    print("Using Unix style [\\n]")
    print("Press any key...")
    wait_click(0)
    n=1
    end
if n<0 then
    print("Newline setting incorrect")
    print("Using Windows style [\\r\\n]")
    print("Press any key...")
    wait_click(0)
    n=0
    end

if n==0 then CR="\r" end
if n==1 then CR="" end
-- /CHECK GIVEN PARAMETERS --

-- CONFIGURATION --
CONSOLE_HEIGHT=y
CONSOLE_WIDTH=x
PATH="A"  --where to open file_browser()?
EXIT=false
SAVED='S'              --is file saved?
MODE="MOVE"
WRITE_SUBMODE=1
JUMPS={1,4,10,20}
JUMP=1
POS_X=0
POS_Y=1
SHIFT_Y=0
SHIFT_X=0
LETTER_NR=1
WRITE_KEY=0
EDI_VERSION="2.5"
--which key does what?
FILE_MENU_BUTTON="menu"
INSERT_MENU_BUTTON="display"
CHANGE_SUBMODE_BUTTON="shoot_half"
KEYMAP={{{"a","b","c","d","e","f"},{"g","h","i","j","k","l"},{"m","n","o","p","q","r","s"},{"t","u","v","w","x","y","z"}},{{"A","B","C","D","E","F"},{"G","H","I","J","K","L"},{"M","N","O","P","Q","R","S"},{"T","U","V","W","X","Y","Z"}},{{"1","2","3"},{"4","5","6"},{"7","8","9"},{"0","+","-","*","/","="}}}
ERASE_AS_SPACE={true,false,true} --when ERASE_AS_SPACE[WRITE_SUBMODE]==true then ERASE works as a space, otherwise - as a backspace.
INSERT_MAP={{"newline"},{"(",")","[","]","{","}"},{"<",">",",","'",":",";"},{"_","+","-","/","\\","="},{"@","!","?","#","\"","."},{"~","&","*","|","^","`"},{"ASCII code"}}
FUNCTION_MAP={{"print","shoot"},{"is_key","if"},{"then","end"},{"sleep","wait_click"},{"function","@title"},{"@param","@default"},{"--[[","--]]"}}
FILE_MENU={{"Save"},{"Save and exit"},{"Save as..."},{"Exit (no save!)"},--[[{"Select..."},#for selecting]]{"Clear whole file"},{"About EDI"}}
TOPBAR="EDI - Text editor"
STATUSBAR="statbar"
FILENAME=""
FILE_CONTENT={}
KEYS_TABLE={"left","up","right","down","set","shoot_half","shoot_full","menu","display","erase","zoom_in","zoom_out"}
REPEATABLE_KEYS_TABLE={"left","up","right","down","zoom_out","zoom_in"}
SAVE_DIRS={{"A"},{"A/CHDK"},{"A/CHDK/SCRIPTS"},{"Cancel"}}
WAIT_TIME=0--#for selecting
DEBBUG="ok"
-- /CONFIGURATION --

function get_input(keys_table,repeatable_keys_table,wait_time,repeat_delay)
    PRESSED_KEY=nil
    if (wait_time==nil or wait_time<0) then wait_time=0 end
    for key_nr=1, table.getn(repeatable_keys_table) do
        if is_pressed(repeatable_keys_table[key_nr]) then PRESSED_KEY=repeatable_keys_table[key_nr]
            end
        end
    if PRESSED_KEY~=nil then
        repeat
            if get_tick_count()-PRESSED_TIME>350 then sleep(100);return PRESSED_KEY end 
            until not is_pressed(PRESSED_KEY)
        end
    wait_click(wait_time)
    PRESSED_TIME=get_tick_count()
    for key_nr=1, table.getn(keys_table) do
        if is_key(keys_table[key_nr]) then PRESSED_KEY=keys_table[key_nr];return keys_table[key_nr] end
        end
    return nil
    end

function new_file()
   FILE_CONTENT={""}
   FILE_LINESN=1
   end

function give_me_filename()
    dir_name=menu(SAVE_DIRS,CONSOLE_WIDTH,CONSOLE_HEIGHT,"select a directory",20,2)
    if (dir_name=="Cancel") then return(nil) end
    file_name=textbox("File name", "Enter file name", "new_file.txt", 16)
    if (file_name==nil or file_name=="") then FILENAME="new_file.txt" end
    out=dir_name.."/"..file_name
    FILENAME=file_name
    return out
    end

function mk_bar(text,width)
    return(string.sub(string.sub("------------------------ ",26-(width-string.len(text))/2,25)..text..string.sub(" ------------------------",1,(width-string.len(text))/2),1,width-1))
    end

function load_file()
    if s==1 then
        PATH="A/CHDK/SCRIPTS"
        end
    file=file_browser(PATH)
    if file==nil then
        print("No file selected!")
        restore()
    else
        for li=0,string.len(file) do
            char=string.sub(file,string.len(file)-li,string.len(file)-li)
            if char~="/" then
                FILENAME=char..FILENAME
                else break
                end
            end
        --lets try to load this file--
        file_h=io.open(file,"r")
        print("Loading, wait...")
        FILE_CONTENT={}
        line=1
        repeat
            FILE_CONTENT[line]=file_h:read("*line")
            FILE_LINESN=line-1
            line=line+1
            until FILE_CONTENT[line-1]==nil
        file_h:close()
        if FILE_CONTENT[1]==nil then FILE_CONTENT={""} end
        if FILE_LINESN==0 then FILE_LINESN=1 end
        end
    end

function edi_draw()
    if POS_Y>CONSOLE_HEIGHT-4+SHIFT_Y then SHIFT_Y=POS_Y-CONSOLE_HEIGHT+4 end
    if POS_Y<=SHIFT_Y then SHIFT_Y=POS_Y-1 end
    if POS_X>CONSOLE_WIDTH-4+SHIFT_X then SHIFT_X=POS_X-CONSOLE_WIDTH+4 end
    if POS_X<=SHIFT_X then SHIFT_X=POS_X end
    if SHIFT_X<0 then SHIFT_X=0 end
    if SHIFT_Y<0 then SHIFT_Y=0 end
    print(mk_bar(TOPBAR,CONSOLE_WIDTH))
    for line_nr=1, CONSOLE_HEIGHT-2 do
        if FILE_CONTENT[line_nr+SHIFT_Y]==nil then
            draw_line=""
        elseif line_nr+SHIFT_Y ~= POS_Y then
            draw_line=FILE_CONTENT[line_nr+SHIFT_Y]
        elseif line_nr+SHIFT_Y == POS_Y then
            draw_line=string.sub(FILE_CONTENT[line_nr+SHIFT_Y],1,POS_X).."\17"..string.sub(FILE_CONTENT[line_nr+SHIFT_Y],POS_X+1,string.len(FILE_CONTENT[line_nr+SHIFT_Y]))
            end
        draw_line=string.sub(draw_line,SHIFT_X,string.len(draw_line))
        if string.len(draw_line)>CONSOLE_WIDTH-2 then
            draw_line=string.sub(draw_line,1,CONSOLE_WIDTH-2).."\26"
            end
        print(draw_line)
        end
    print(mk_bar(STATUSBAR,CONSOLE_WIDTH))
    end

function edi_move()
    STATUSBAR="["..MODE.."]["..JUMPS[JUMP].."\18]["..POS_X..","..POS_Y.."/"..FILE_LINESN.."]"
    TOPBAR="EDI \6 "..FILENAME.." ["..SAVED.."] "..DEBBUG.." "
    edi_draw()
    input=get_input(KEYS_TABLE,REPEATABLE_KEYS_TABLE, WAIT_TIME)
    if input=="set" then MODE="WRITE" end
    if input=="up" then
        POS_Y=POS_Y-JUMPS[JUMP]
        if POS_Y<1 then POS_Y=table.getn(FILE_CONTENT) end
        if POS_X>string.len(FILE_CONTENT[POS_Y]) then POS_X=string.len(FILE_CONTENT[POS_Y]) end        
        end
    if input=="down" then
        POS_Y=POS_Y+JUMPS[JUMP]
        if POS_Y>FILE_LINESN then POS_Y=1 end
        if POS_X>string.len(FILE_CONTENT[POS_Y]) then POS_X=string.len(FILE_CONTENT[POS_Y]) end
        end
    if input=="left" then
        POS_X=POS_X-1
        if POS_X<0 and POS_Y>1 then POS_Y=POS_Y-1;POS_X=string.len(FILE_CONTENT[POS_Y])
        elseif POS_X<0 and POS_Y==1 then POS_Y=FILE_LINESN;POS_X=string.len(FILE_CONTENT[POS_Y]) end
        end
    if input=="right" then
        POS_X=POS_X+1
        if POS_X>string.len(FILE_CONTENT[POS_Y]) and POS_Y<FILE_LINESN then POS_Y=POS_Y+1;POS_X=0
        elseif POS_X>string.len(FILE_CONTENT[POS_Y]) and POS_Y>=FILE_LINESN then POS_Y=1;POS_X=0 end
        end
    if input=="zoom_in" then
        POS_X=POS_X+5
        if POS_X>string.len(FILE_CONTENT[POS_Y]) and POS_Y<FILE_LINESN then POS_Y=POS_Y+1;POS_X=0
        elseif POS_X>string.len(FILE_CONTENT[POS_Y]) and POS_Y>=FILE_LINESN then POS_Y=1;POS_X=0 end
        end
    if input=="zoom_out" then
        POS_X=POS_X-5
        if POS_X<0 and POS_Y>1 then POS_Y=POS_Y-1;POS_X=string.len(FILE_CONTENT[POS_Y])
        elseif POS_X<0 and POS_Y==1 then POS_Y=FILE_LINESN;POS_X=string.len(FILE_CONTENT[POS_Y]) end
        end
    if input=="erase" then
        POS_X=0
        POS_Y=1
        end
    if input==CHANGE_SUBMODE_BUTTON then JUMP=JUMP+1 end
    if JUMP>table.getn(JUMPS) then JUMP=1 end
    if input==FILE_MENU_BUTTON then
        todo=menu(FILE_MENU,CONSOLE_WIDTH,CONSOLE_HEIGHT,"File menu",nil,2)
        if todo=="Save" then save() end
        if todo=="Save as..." then save_as() end
        if todo=="Save and exit" then save();restore() end
        --if todo=="Select..." then MODE="SELECT" end #for selecting
        if todo=="Exit (no save!)" then restore() end
        if todo=="Clear whole file" then clear() end
        if todo=="About EDI" then about() end
        end
    end

function edi_write()
    delete=0
    write_mode_descript=""
    for li=1,table.getn(KEYMAP[WRITE_SUBMODE]) do
        write_mode_descript=write_mode_descript.."\6"
        for xi=1,table.getn(KEYMAP[WRITE_SUBMODE][li]) do
            write_mode_descript=write_mode_descript..KEYMAP[WRITE_SUBMODE][li][xi]
            end
        end
    write_mode_descript=write_mode_descript.."\6"
    STATUSBAR=write_mode_descript
    TOPBAR="EDI \6 "..FILENAME.." ["..SAVED.."] "..DEBBUG.." "
    insertion=""
    edi_draw()
    input=get_input(KEYS_TABLE,REPEATABLE_KEYS_TABLE,WAIT_TIME)
    if input==CHANGE_SUBMODE_BUTTON then
        WRITE_SUBMODE=WRITE_SUBMODE+1
        WRITE_KEY=0
        if WRITE_SUBMODE>table.getn(KEYMAP) then WRITE_SUBMODE=1 end
        end
    if input=="left" and WRITE_KEY==1 then LETTER_NR=LETTER_NR+1;delete=1;SAVED="!"
        elseif input=="left" and WRITE_KEY~=1 then LETTER_NR=1;WRITE_KEY=1;SAVED="!"
        elseif input=="up" and WRITE_KEY==2 then LETTER_NR=LETTER_NR+1;delete=1;SAVED="!"
        elseif input=="up" and WRITE_KEY~=2 then LETTER_NR=1;WRITE_KEY=2;SAVED="!"
        elseif input=="right" and WRITE_KEY==3 then LETTER_NR=LETTER_NR+1;delete=1;SAVED="!"
        elseif input=="right" and WRITE_KEY~=3 then LETTER_NR=1;WRITE_KEY=3;SAVED="!"
        elseif input=="down" and WRITE_KEY==4 then LETTER_NR=LETTER_NR+1;delete=1;SAVED="!"
        elseif input=="down" and WRITE_KEY~=4 then LETTER_NR=1;WRITE_KEY=4;SAVED="!"
        end
    if input=="zoom_in" or (input=="erase" and ERASE_AS_SPACE[WRITE_SUBMODE]==true) then WRITE_KEY=0;insertion=" ";SAVED="!" end
    if input=="zoom_out" or(input=="erase" and ERASE_AS_SPACE[WRITE_SUBMODE]~=true) then
        SAVED="!"
        if POS_X>0 then
            WRITE_KEY=0;delete=1
        elseif POS_X==0 and POS_Y>1 then
            POS_X=string.len(FILE_CONTENT[POS_Y-1])
            FILE_CONTENT[POS_Y-1]=FILE_CONTENT[POS_Y-1]..FILE_CONTENT[POS_Y]
            POS_Y=POS_Y-1
            for line=POS_Y+1,table.getn(FILE_CONTENT)-1 do
                FILE_CONTENT[line]=FILE_CONTENT[line+1]
                end
            FILE_CONTENT[FILE_LINESN]=nil
            FILE_LINESN=FILE_LINESN-1
            end
        end
    if WRITE_KEY~=0 and LETTER_NR~=0 then
        if LETTER_NR>table.getn(KEYMAP[WRITE_SUBMODE][WRITE_KEY]) then LETTER_NR=1 end
        insertion=KEYMAP[WRITE_SUBMODE][WRITE_KEY][LETTER_NR]
        SAVED="!"
        end
    if input=="set" and WRITE_KEY==0 then MODE="MOVE"
        elseif input=="set" and WRITE_KEY~=0 then WRITE_KEY=0;insertion=""
        end
    if input==INSERT_MENU_BUTTON then
        WRITE_KEY=0;insertion="";SAVED="!"
        insertion=menu(INSERT_MAP,CONSOLE_WIDTH,CONSOLE_HEIGHT,"Insert a special char",nil,2)
        if insertion==nil then insertion=menu(FUNCTION_MAP,CONSOLE_WIDTH,CONSOLE_HEIGHT,"Insert a function",10,2) end
        if insertion==nil then insertion="";SAVED="S" end
        if insertion=="newline" then
            insertion=""
            delete=0
            SAVED="!"
            for unline=0, FILE_LINESN-POS_Y+1 do
                FILE_CONTENT[FILE_LINESN+1-unline]=FILE_CONTENT[FILE_LINESN-unline]
                end
            FILE_CONTENT[POS_Y]=string.sub(FILE_CONTENT[POS_Y+1],1,POS_X)..CR
            FILE_CONTENT[POS_Y+1]=string.sub(FILE_CONTENT[POS_Y+1],POS_X+1,string.len(FILE_CONTENT[POS_Y+1]))
            POS_X=0;POS_Y=POS_Y+1;FILE_LINESN=FILE_LINESN+1
            end        
        if insertion=="ASCII code" then insertion=insert_ascii() end
        end
    if input==FILE_MENU_BUTTON then
        WRITE_KEY=0;insertion=""
        todo=menu(FILE_MENU,CONSOLE_WIDTH,CONSOLE_HEIGHT,"File menu",nil,2)
        if todo=="Save" then save() end
        if todo=="Save and exit" then save();restore() end
        if todo=="Save as..." then save_as() end
        if todo=="Exit (no save!)" then restore() end
        if todo=="Clear whole file" then clear() end
        if todo=="About EDI" then about() end
        end
    if input==nil then WRITE_KEY=0;insertion="" end
    FILE_CONTENT[POS_Y]=string.sub(FILE_CONTENT[POS_Y],1,POS_X-delete)..insertion..string.sub(FILE_CONTENT[POS_Y],POS_X+1,string.len(FILE_CONTENT[POS_Y]))
    POS_X=POS_X+string.len(insertion)-delete
    end

function insert_ascii()
    exit_loop=false
    code={0,0,0}
    pos=1
    mass="-"
    repeat
        print();print()
        print(mk_bar("Insert char by ASCII",CONSOLE_WIDTH))
        print();print()
        if pos==1 then code_string="\4"..code[1].." "..code[2].." "..code[3] end
        if pos==2 then code_string=" "..code[1].."\4"..code[2].." "..code[3] end
        if pos==3 then code_string=" "..code[1].." "..code[2].."\4"..code[3] end
        print("       Set ASCII code: "..code_string)
        print();print()
        print(mk_bar(mass,CONSOLE_WIDTH))
        for li=11, CONSOLE_HEIGHT do
            print()
            end
        input=get_input(KEYS_TABLE,REPEATABLE_KEYS_TABLE)
        if input=="right" then pos=pos+1 end
        if input=="left" then pos=pos-1 end
        if pos>3 then pos=1 end
        if pos<1 then pos=3 end
        if input=="up" then code[pos]=code[pos]+1 end
        if input=="down" then code[pos]=code[pos]-1 end
        if code[pos]>9 then code[pos]=0 end
        if code[pos]<0 then code[pos]=9 end
        ascii=code[1]*100+code[2]*10+code[3]
        --code 0 is legal, but this char makes all the chars after \0 invisible, so it's probably useless;this is just to avoid confusion.
        if ascii<256 and ascii>0 then mass="character: "..string.char(ascii) else mass="bad value" end
        if input=="set" then
            if ascii>255 or ascii<1 then mass="ASCII code must be in range 1-255!"
                else
                return string.char(ascii)
                end
            end
--        if input
        until exit_loop==true
    end

function menu(tab,width,height,header,item_width,top_lines)
    set_console_autoredraw(0)
    menu_pos_y=1
    menu_pos_x=1
    menu_shift=0
    exit_menu=false
    if header==nil then header="SELECT ITEM" end
    if height==nil then print("NO HEIGHT GIVEN!");sleep(3000);return false end
    if width==nil then print("NO WIDTH GIVEN!");sleep(3000);return false end
    if top_lines==nil then top_lines=0 end
    repeat
        if menu_pos_x<1 and menu_pos_y>1 then menu_pos_y=menu_pos_y-1;menu_pos_x=table.getn(tab[menu_pos_y]) end
        if menu_pos_x<1 and menu_pos_y<=1 then menu_pos_y=table.getn(tab);menu_pos_x=table.getn(tab[menu_pos_y]) end
        if menu_pos_y<1 then menu_pos_y=table.getn(tab) end
        if menu_pos_y>table.getn(tab) then menu_pos_y=1 end
        if menu_pos_x>table.getn(tab[menu_pos_y]) and menu_pos_y<table.getn(tab) then menu_pos_y=menu_pos_y+1;menu_pos_x=1 end
        if menu_pos_x>table.getn(tab[menu_pos_y]) and menu_pos_y>=table.getn(tab) then menu_pos_y=1;menu_pos_x=1 end
        if menu_pos_y>height-4+menu_shift then menu_shift=menu_pos_y-height+4 end
        if menu_pos_y<=menu_shift then menu_shift=menu_pos_y-1 end
        for line=0, top_lines do
            print("")
            end
        print(mk_bar(header,width))
        for line=1,--[[height-3-top_lines]] table.getn(tab) do
            if tab[line+menu_shift]==nil then
                draw_line=""
            elseif line+menu_shift==menu_pos_y then
                draw_line=""
                for place=1, table.getn(tab[line+menu_shift]) do
                    item=tab[line+menu_shift][place]
                    if item_width~=nil then item=item..string.sub("                         ",1,item_width-string.len(item)) end

                    if menu_pos_x~=place then draw_line=draw_line.." "..item.." " end
                    if menu_pos_x==place then draw_line=draw_line.."\16"..item.."\17" end
                    end
            elseif line+menu_shift~=menu_pos_y then
                draw_line=""
                for place=1, table.getn(tab[line+menu_shift]) do
                    item=tab[line+menu_shift][place]
                    if item_width~=nil then item=item..string.sub("                         ",1,item_width-string.len(item)) end
                    draw_line=draw_line.." "..item.." "
                    end
                end
            print(draw_line)
            end
        print(mk_bar("SELECT-["..menu_pos_x..","..menu_pos_y.."]",width))
        for line=0, height-4-top_lines-table.getn(tab) do
            print("")
            end
        input=get_input(KEYS_TABLE,REPEATABLE_KEYS_TABLE)
        if input=="up" then menu_pos_y=menu_pos_y-1 end
        if input=="down" then menu_pos_y=menu_pos_y+1 end
        if input=="left" then menu_pos_x=menu_pos_x-1 end
        if input=="right" then menu_pos_x=menu_pos_x+1 end
        if input=="set" then exit_menu=true;return tab[menu_pos_y][menu_pos_x] end
        if input==INSERT_MENU_BUTTON or input==FILE_MENU_BUTTON then exit_menu=true;return nil end
        until exit_menu==true
    end

function save()
    cls()
    console_redraw()
    print(mk_bar("Saving procedure...",CONSOLE_WIDTH))
    if (b~=0 and file~=nil) then
        print("--make a backup...")
        backup_file=file..".BAK"
        print("  *backup:",backup_file)
        print("--open files")
        file_h=io.open(file,"r")
        backup_file_h=io.open(backup_file,"w")
        if (not file_h or not backup_file_h) then
            print("Error opening files")
            print("Press any key")
            wait_click(0)
            return
            end
        for file_line in file_h:lines() do
            backup_file_h:write(file_line)
            backup_file_h:write("\n")
            end
        file_h:close()
        backup_file_h:close()
        print("--backup done")
        print()
        end
    if file==nil then file=give_me_filename() end
    if file==nil then return(nil) end
    print("--saving file")
    file_h=io.open(file,"w")
    if (not file_h) then
        print("Error opening files")
        print("Press any key")
        wait_click(0)
        return
        end
    for line_no,file_line in ipairs(FILE_CONTENT) do
        file_h:write(file_line)
        file_h:write("\n")
        end
    file_h:close()
    SAVED="S"
    print("The file has been saved")
    sleep(1200)
    end
    
function save_as()
    file_tmp=file
    file=nil
    save()
    if file==nil then file=file_tmp end
    end
    
function restore()
    cls()
    print("EDI has been terminated.")
    set_console_autoredraw(1)
    set_console_layout(0,0,25,5) -- Thx, msl!
    EXIT=true
    end
    
function clear()
    ans=menu({{"NO","YES"}},CONSOLE_WIDTH,CONSOLE_HEIGHT,"Are you sure?",5,2)
    if ans=="YES" then FILE_CONTENT={""};FILE_LINESN=1;POS_X=0;POS_Y=1;SAVED="!" end
    end
    
function about()
    cls()
    print("   ")
    print("   ")
    print(mk_bar("ABOUT EDI",CONSOLE_WIDTH))
    print("   ")
    print("  EDI - text editor for CHDK")
    print("   ")
    print("  Version: "..EDI_VERSION)
    print("  Author:  Pawel Tokarz")
    print("  Thanks:  waterwingz, truhli_fredy,")
    print("           philmoz, reyalp & others")
    print("   ")
    print("  More info in README.TXT file")
    print("")
    print(mk_bar("PRESS MENU",CONSOLE_WIDTH))
    for line=1,CONSOLE_HEIGHT-16 do print("") end
    exit_about=false
    repeat
        input=get_input(KEYS_TABLE,REPEATABLE_KEYS_TABLE)
        if input==FILE_MENU_BUTTON then exit_about=true end
        until(exit_about==true)
    end

function main_loop()
    DEBBUG=0
    insertion=""
    repeat
        DEBBUG=DEBBUG+1
        if MODE=="MOVE" --[[or MODE=="SELECT" #for selecting]] then edi_move() end
        if MODE=="WRITE" then edi_write() end
        until EXIT==true
    end

set_console_layout(0,0,CONSOLE_WIDTH,CONSOLE_HEIGHT)
set_console_autoredraw(0)
if a==1 then
    new_file()
    else
    load_file()
    end
if EXIT~=true then main_loop() end

