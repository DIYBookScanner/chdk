EDI - README.TXT
'Emacs your camera!'

Documentation for version 2.7 based on documentation for 2.6.

0. ABOUT

    This is readme for EDI - Text editor written in Lua for CHDK. It's designed to give your camera possibility to edit text files (especially scripts) directly on camera.
    
    **** ATTENTION! ****
    Since version 2.6 EDI uses textbox() function which is currently aviable in experimental branch. Because of that 'new file' and 'Save as...' options can not be used in other branches (stable 1.0 and reyalp-flt as well). If 'new file' or 'Save as...' option is used in these branches an error occurs!

    While none of above functions is used, EDI 2.7 should work (althought it was not tested).

    

    WARNING!

    I've tested this script only on SX130IS with no problems. A few users were able to use it on other CHDK-supported cameras. Nevertheless THERE IS NO VARRANTY FOR THIS SOFTWARE, IT'S FREE AND MIGHT BE BUGGY. It's rather not likely, but still possible that it could damage file you are editing or even filesystem on SD card. This never happened, but who knows. USE THIS SCRIPT ON YOUR OWN RISK.

    SOME PARTS OF THIS DOCUMENTATION MIGHT BE OUTDATED OR CONTAIN BUGS.


1. INSTALLATION

    Just paste the file EDI.LUA on your SD card. EDI is instaled and ready to use!

    
    
2. USAGE

    2.1 Run
    
    To use EDI you have to run script EDI. Read more about runing scripts on CHDK wikia or forum.


    
    2.2 Select a file - filebrowser
    
    Once you run the script you'll see a file browser. You have to chose a file you want to edit. Just navigate using UP/DOWN and SET buttons as in normal CHDK filebrowser. If you selected a directory pressing SET will take you inside it. Special directory ".." moves you into the parent directory. If you press SET button with file selected this file will be opened.
    

    
    2.3 EDI
    
    When you have selected the file and pressed SET this file is opened. You can see a screen like this:
    
    
    ---------- EDI | FILENAME [S] ----------
    <Here you should
    see
    the content
    of a file
    ------------ [MOVE][1|][0,1] ------------
    
    First line is TOPBAR - it contains editor name (EDI), opened file name (in example: FILENAME) and saved indicator - [S] if file has not been changed since last save and [!] if there are some unsaved changes.

    Last line is STATUSBAR - it contains mode description (in example: MOVE) and other information depending on MODE. This will be described below.
    
    Between these lines there is a part of content of the file. You can see, that first line below TOPBAR begins with triangle (not really: "<" however, it's not possible to place triangle here). This triangle is the cursor - as in normal text editor. It indicates, where new letter/sign will be inserted or which letter/sign will be deleted.
    
    
    
    2.3.1 Modes
    
    - MOVE mode
    
    At the begining you are in MOVE mode. That means you are able to move cursor using UP/DOWN/LEFT/RIGHT buttons on your camera. Normally one press moves cursor one place left/right or one line up/down.
    
    Meaning of the keys in this mode:
    
    UP/DOWN/LEFT/RIGHT  - move the cursor, as described above.
    ZOOM_OUT/ZOOM_IN    - move the cursor 4 places left/right. Usefull if you want to edit something inside a long line.

    SHOOT_HALF          - change number of lines you'll move by one UP/DOWN press. The number is shown in STATUSBAR (first number after MOVE word). You can swich between 1, 4, 10 and 20 lines. It's usefull to move through long files. DO NOT PRESS SHOT_FULL unless you want to end the script!
    MENU                - open FILE MENU which is described below.
    SET                 - end MOVE mode and go into a WRITE mode.
    ERASE               - move to the begin of the file.

    SHOOT_FULL          - END THE SCRIPT WITHOUT ANY SAVES!!!
    
    - WRITE mode
    
    When you press SET being in MOVE mode you'll be taken to the WRITE mode. In this mode screen looks like this:
    
    
    ---------- EDI | FILENAME [S] ----------
    <Here you should
    see
    the content
    of a file
    ---- |abcdef|ghijkl|mnopqrs|tuvwxyz| ----
    
    TOPBAR looks just like in the MOVE mode, however, STATUSBAR has been changed.

    STATUSBAR in WRITE mode describes, which letters/digits are aviable under which keys. STATUSBAR like above means, that you are able to write lowercase letters as follows:
    
    press LEFT to get letters:  a, b, c, d, e, f
    press UP to get letters:    g, h, i, j, k, l
    press RIGHT to get letters: m, n, o, p, q, r, s
    press DOWN to get letters:  t, u, v, w, x, y, z
    
    When you press a key once you'll get first letter, twice - second and so on. If you need to write another letter just press different letter key. If you need a letter that is aviable under the same key as previous just press SET once and the key. This is just like writing SMS'es on mobile phone.
    
    You can change lowercase to uppercase by pressing SHOOT_HALF. Another SHOOT_HALF will change to digits and then back to the lowercase.
    
    However, ZOOM_IN/ZOOM_OUT works as spacebar/backspace you can also use ERASE key for both. While active write style is lowercase or digits the ERASE key works as spacebar, while write style is uppercase - it works as backspace. This might be usefull for non-zoom cameras
    
    Description of the keys meanings in the WRITE mode:
    
    LEFT       - a,b,c,d,e,f     or   A,B,C,D,E,F      or   1,2,3
    UP         - g,h,i,j,k,l     or   G,H,I,J,K,L      or   4,5,6
    DOWN       - m,n,o,p,q,r,s   or   M,N,O,P,Q,R,S    or   7,8,9
    RIGHT      - t,u,v,w,x,y,z   or   T,U,V,W,X,Y,Z    or   0,+,-,*,/,=
    
    ZOOM_IN    - spacebar
    ZOOM_OUT   - backspace
    ERASE      - in abc/123: spacebar; in ABC: backspace
    
    DISP       - open INSERT MENU - described below
    MENU       - open FILE MENU - described below.
    SHOOT_HALF - change between lowercase/uppercase/digits
    SET        - end WRITE mode and go into MOVE mode
    
    SHOOT_FULL - END THE SCRIPT WITHOUT ANY SAVES!!!
    
    
    
    2.3.2 INSERTION MENU
    
    This menu allows you to insert special characters or even words. This menu is aviable ONLY in WRITE mode by pressing DISP button. Once DISP is pressed you'll see screen like this:
    
    
    ------- Insert special char ------
    >newline<
     (  )  [  ]  {  }
     <  >  ,  '  :  ;
     _  +  -  /  \  =
     @  !  ?  #  "  .
     ~  &  *  |  ^  `
     ASCII code
     
     --------- SELECT-[1,1] ----------
    
    
    You can select the character you need by pressing LEFT/UP/RIGHT/DOWN buttons. When you press SET you'll return to the editor and selected character will appear in cursor place. You can select:
    
    - newline          - breaks line in cursor place (just like ENTER on PC keyboard)
    - ( [ @ $... etc.  - insert selected character
    - ASCII code       - you can load a character by it's ASCII code. If this option is active you'll be taken to the ASCII selection menu.
    
    You can also press DISP key again and go to the INSERT FUNCTION MENU, which is described below.
    
    If you want to leave INSERT MENU just press DISP (INSERT FUNCTION MENU will be opened) and DISP once again.
    
    
    
    2.3.3 INSERT FUNCTION MENU
    
    If you are in INSERT menu you can press DISP again and go to the INSERT FUNCTION MENU as described above. In this menu you'll see a screen like this:
    
    -------- Insert function --------
    >print    < shoot
     is_key     if
     then       end
     sleep      wait_click
     function   @title
     @param     @default
    
    --------- SELECT-[1,1] ----------
    
    
    You can select a word that will be inserted in cursor place just like character. It's usefull especially for scripts, so the most common functions are present here. Probably the list will be greater in future. Remember - this only inserts a selected word, there is no checking if this make any sens.
    
    If you like to leave INSERT FUNCTION MENU without inserting anything just press DISP.
    
    
    
    2.3.4 FILE MENU
    
    This menu is aviable everytime in all modes by pressing MENU key. In this file you can select items:
    
    - Save             - saves changes to file. Previous saved version is copied to backup file which has the same name but with .BAK extension. Note: if you save file two times the backup will contain previous saved version, NOT oryginal file!
    
    - Save and exit    - just save as above and exit the editor
    
    - Exit (no save!)  - exit without any saves! This can be also achieved by SHOOT_FULL
    
    - Clear whole file - removes whole content of file however, it will be done only on editor, not physical file untill you save changes.
    
    You can leave FILE MENU by pressing DISP or MENU key.
    
    
    
3. PARAMETERS
    
    You can set various parameters like in other scripts for CHDK. Read more how to set parameters for scripts on CHDK wikia or forum.
    
    Parameters that can be set for EDI:
    
    - Newline (1=Windows 2=Unix)  - set which style of newline coding should be used. Usually Unix uses one character (\n; "newline") to describe newline and Windows uses two characters (\r\n; "cariage return" and "newline"). If you set 1 EDI will paste both characters while "newline" is inserted. If you set 2 it will use only "newline" character. Note: this doesn't change existing newline characters!
    
    - Editor height               -.
                                    |- as named.
    - Editor width                -'
    
    
    
4. AUTHOR, LICENSE
    
    Author:     Pawel Tokarz aka Outslider
    License:    GPL v3+ as well as LGPL v3+
    
    Contact:    write all you want to write on CHDK forum. http://chdk.setepontos.com/index.php?topic=6465.0
    
    NO WARANTY! THIS SCRIPT CAN DO ANYTHING WITH YOUR CAMERA, MIGHT DELETE A FILE, MIGHT DAMAGE SD CARD AND MIGHT CAUSE YOUR CAMERA FLY AWAY AND EXPLODE AS WELL. This was never observed and it's unlikely, but still possible...
    USE ON YOUR OWN RISK!
    
    
