#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_mbox.h"
#include "modes.h"

#include "module_def.h"

void gui_game_menu_kbd_process();
int gui_mastermind_kbd_process();
void gui_mastermind_draw();

gui_handler GUI_MODE_MASTERMIND = 
    /*GUI_MODE_MASTERMIND*/ { GUI_MODE_MODULE, gui_mastermind_draw, gui_mastermind_kbd_process, gui_game_menu_kbd_process, GUI_MODE_FLAG_NODRAWRESTORE };

#define BORDER		 		20
#define RECT_SIZE	 		10
#define COLOR_LIGHT_GRAY 	MAKE_COLOR(COLOR_SPLASH_GREY,COLOR_SPLASH_GREY)
#define BK_COLOR	 		MAKE_COLOR(COLOR_GREY,COLOR_GREY)
#define TEXT_COLOR          MAKE_COLOR(COLOR_GREY,COLOR_BLACK)

int curr_x;
int curr_y;
int answer[4];
char colors[6];
int curr_color[4];
int GameGo;
static char buf[128];

static void guess_box(int pos, color col)
{
	draw_filled_rect(camera_screen.ts_button_border+100+(pos*10), BORDER+(2*curr_y*10)+2+2*curr_y, camera_screen.ts_button_border+100+(pos*10)+6, BORDER+(2*curr_y*10)+8+2*curr_y , MAKE_COLOR(col,col));
}

char WinQuary(){
	char pos=0;
	int i, j;
	
	for (i=0; i<4; i++)
    {
		if (answer[i] == curr_color[i])
        {
            guess_box(pos,COLOR_BLACK);
			pos++;
		}
	}
	
	if (pos == 4)
    {
		GameGo = 0;
		return 1;
	}
	
	for (i=0; i<4; i++)
    {
    	for (j=0; j<4; j++)
        {
		    if ((answer[i] == curr_color[j]) && (i != j))
            {
                guess_box(pos,COLOR_WHITE);
			    pos++;
            }
		}
	}

	if(curr_y==0)
    {
		GameGo = 0;
		return 2;
	}

	return 0;
}

char CanNext(){
	if (curr_color[0]==99 || curr_color[1]==99 || curr_color[2]==99 || curr_color[3]==99)
		return 0;
	else if (curr_color[0]==curr_color[1] || curr_color[0]==curr_color[2] || curr_color[0]==curr_color[3] ||
		     curr_color[1]==curr_color[2] || curr_color[1]==curr_color[3] || curr_color[2]==curr_color[3])
    {
		draw_string(camera_screen.ts_button_border+167, 130, lang_str(LANG_MENU_GAMES_DCOLOR), TEXT_COLOR);
		return 0;
	}
	return 1;
}

void CreateColorCombo(){
	char tmp=0;
	int i=0;
	
	for (i=0; i<4; i++) answer[i] = 99;
	i = 0;
	while (i<4)
    {
		tmp = rand() % 6;
		if (answer[0]!=tmp && answer[1]!=tmp && answer[2]!=tmp && answer[3]!=tmp)
        {
			answer[i] = tmp;
			i++;
		}
	}
}

int gui_mastermind_init() {
	int i,j;

	curr_x=0;
	curr_y=7;
	
	draw_filled_rect( 0, 0, camera_screen.width-1, camera_screen.height-1, BK_COLOR);

	for (i=0;i<4;i++)
		for (j=0;j<8;j++)
			draw_filled_rect(camera_screen.ts_button_border+BORDER+(2*i*10), BORDER+(2*j*10)+2*j, camera_screen.ts_button_border+BORDER+(2*i*10)+10, BORDER+(2*j*10)+2*j+10 , COLOR_LIGHT_GRAY);

	draw_filled_rect(camera_screen.ts_button_border+10, BORDER+(2*j*10)+2*j, camera_screen.ts_button_border+150,BORDER+(2*j*10)+2*j+1, MAKE_COLOR(COLOR_GREY,COLOR_WHITE));
	draw_filled_rect(camera_screen.ts_button_border+148, 10, camera_screen.ts_button_border+149,230, MAKE_COLOR(COLOR_GREY,COLOR_WHITE));
	draw_filled_rect(camera_screen.ts_button_border+151, 10, camera_screen.ts_button_border+152,230, MAKE_COLOR(COLOR_GREY,COLOR_WHITE));
	
	for (i=0; i<6;i++)
		draw_filled_rect(camera_screen.ts_button_border+BORDER+(2*(i+7)*10)+20, 40, camera_screen.ts_button_border+BORDER+(2*(i+7)*10)+35,55, MAKE_COLOR(colors[i],colors[i]));
		
	draw_filled_rect(camera_screen.ts_button_border+BORDER+(2*7*10)+20, 65, camera_screen.ts_button_border+BORDER+(2*7*10)+35,80, MAKE_COLOR(COLOR_BLACK,COLOR_BLACK));
	draw_string(camera_screen.ts_button_border+BORDER+(2*7*10)+50, 65 , lang_str(LANG_MENU_GAMES_RIGHT_PLACE), TEXT_COLOR);
	
	draw_filled_rect(camera_screen.ts_button_border+BORDER+(2*7*10)+20, 90, camera_screen.ts_button_border+BORDER+(2*7*10)+35,105, MAKE_COLOR(COLOR_WHITE,COLOR_WHITE));
	draw_string(camera_screen.ts_button_border+BORDER+(2*7*10)+50, 90 , lang_str(LANG_MENU_GAMES_C_IN_ANSWER), TEXT_COLOR);
					
	draw_string(camera_screen.ts_button_border+173, 20 , lang_str(LANG_MENU_GAMES_AC_COLORS), TEXT_COLOR);
		
	draw_string(camera_screen.ts_button_border+167, 200 , lang_str(LANG_MENU_GAMES_CURSOR1), TEXT_COLOR);
	draw_string(camera_screen.ts_button_border+167, 185 , lang_str(LANG_MENU_GAMES_CURSOR2), TEXT_COLOR);
	draw_string(camera_screen.ts_button_border+167, 170 , lang_str(LANG_MENU_GAMES_CURSOR3), TEXT_COLOR);

	for(i=0;i<4;i++) curr_color[i]=99;
	
    gui_set_mode(&GUI_MODE_MASTERMIND);
	return 1;
}

//-------------------------------------------------------------------
static void draw_box(color border)
{
    if (curr_color[curr_x] == 99) curr_color[curr_x] = 0;
    draw_filled_rect(camera_screen.ts_button_border+BORDER+(2*curr_x*10), BORDER+(2*curr_y*10)+2*curr_y, camera_screen.ts_button_border+BORDER+(2*curr_x*10)+10, BORDER+(2*curr_y*10)+2*curr_y+10 , MAKE_COLOR(colors[curr_color[curr_x]],border));
}

static void end_game(int msg)
{
    int i;
    draw_string(camera_screen.ts_button_border+198, 130 , lang_str(msg), TEXT_COLOR);
	for (i=0; i<4;i++)
	    draw_filled_rect(camera_screen.ts_button_border+BORDER+(2*i*10), 213, camera_screen.ts_button_border+BORDER+(2*i*10)+10,223,  MAKE_COLOR(colors[answer[i]],colors[answer[i]]));
}

static void chg_box(int inc_box, int inc_val)
{
    draw_box(colors[curr_color[curr_x]]);
    curr_x = (curr_x + inc_box) & 3;
    if (curr_color[curr_x] == 99) curr_color[curr_x] = 0;
    curr_color[curr_x] = (curr_color[curr_x] + inc_val);
    if (curr_color[curr_x] < 0) curr_color[curr_x] = 5;
    else if (curr_color[curr_x] > 5) curr_color[curr_x] = 0;
    draw_box(COLOR_BLACK);
}

int gui_mastermind_kbd_process() {
	int i=0;
	rand();
    long key = kbd_get_autoclicked_key();
    if (key)
    {
        if (GameGo == 1)
        {
            draw_string(camera_screen.ts_button_border+167, 130 , "                       ", TEXT_COLOR);
	        switch (kbd_get_autoclicked_key()) 
	        {
		        case KEY_SET:
			        if(CanNext())
                    {
				        if(WinQuary() == 1)
                        {
                            end_game(LANG_MENU_GAMES_RIGHT);
				        }
				        else if(WinQuary() == 2)
                        {
                            end_game(LANG_MENU_GAMES_GAME_OVER);
				        }
				        else
                        {
                            draw_box(colors[curr_color[curr_x]]);
					        for(i=0;i<4;i++) curr_color[i]=99;
					        curr_y--;
					        curr_x=0;
                            draw_box(COLOR_BLACK);
				        }
			        }
			        break;
		        case KEY_LEFT:
                    chg_box(-1,0);
			        break;
		        case KEY_RIGHT:
                    chg_box(1,0);
			        break;
		        case KEY_UP:
                    chg_box(0,1);
			        break;
		        case KEY_DOWN:
                    chg_box(0,-1);
			        break;
	        }
        }
        else if (key == KEY_SET)
        {
			gui_mastermind_init();
			CreateColorCombo();
            draw_box(COLOR_BLACK);
			GameGo=1;
        }
    }
    return 0;
}
//-------------------------------------------------------------------
void gui_mastermind_draw() {
    static struct tm *ttm;

    draw_txt_string(camera_screen.ts_button_border/FONT_WIDTH+15, 0, lang_str(LANG_MENU_GAMES_MASTERMIND), MAKE_COLOR(COLOR_GREY, COLOR_WHITE));

    ttm = get_localtime();
    sprintf(buf, "Time: %2u:%02u  Batt:%3d%%", ttm->tm_hour, ttm->tm_min, get_batt_perc());
    draw_txt_string((camera_screen.width-camera_screen.ts_button_border)/FONT_WIDTH-2-1-1-9-2-5-4, camera_screen.height/FONT_HEIGHT-1, buf, TEXT_COLOR);
}


int basic_module_init() {
	colors[0] = COLOR_HISTO_R_PLAY;
	colors[1] = COLOR_HISTO_G_PLAY;
	colors[2] = COLOR_HISTO_B_PLAY;
	colors[3] = COLOR_YELLOW;
	colors[4] = COLOR_WHITE;
	colors[5] = COLOR_BLACK;

	return gui_mastermind_init(); 
}

#include "simple_game.c"

/******************** Module Information structure ******************/

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    -LANG_MENU_GAMES_MASTERMIND,// Module name
    (int32_t)"Game",

    &_librun.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
