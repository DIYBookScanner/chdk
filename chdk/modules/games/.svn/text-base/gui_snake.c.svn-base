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
int gui_snake_kbd_process();
void gui_snake_draw();

gui_handler GUI_MODE_SNAKE = 
    /*GUI_MODE_SNAKE*/  { GUI_MODE_MODULE, gui_snake_draw, gui_snake_kbd_process, gui_game_menu_kbd_process, GUI_MODE_FLAG_NODRAWRESTORE };

//-------------------------------------------------------------------
#define SNAKE_MAX_LENGTH 0xF0
#define SNAKE_ELEMENT_SIZE 8
#define RING_WIDTH 42
#define RING_HEIGHT 24
enum{
  DIR_LEFT = 0,
  DIR_RIGHT,
  DIR_UP,
  DIR_DOWN
};
unsigned char ring[RING_WIDTH][RING_HEIGHT];
unsigned short snake_head;
unsigned short snake_tail;
unsigned char snake[SNAKE_MAX_LENGTH][2];
unsigned int points;
unsigned char level;
unsigned char direction;
char str_buf[40];

const unsigned char labyrinth[4][RING_HEIGHT][RING_WIDTH] = {
    {
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     },
    {
     "##########################################",
     "#                                        #",
     "#                                        #",
     "#                                        #",
     "#     ############                       #",
     "#                #                       #",
     "#                #                       #",
     "#                #########################",
     "#                #                       #",
     "#                #                       #",
     "#                #                       #",
     "#                        ######          #",
     "#                        #    #          #",
     "#            #############    #          #",
     "#           #                 #          #",
     "#          #                  #          #",
     "#         #                   #          #",
     "#        #                    #          #",
     "#       #                     #          #",
     "#       #                     #          #",
     "#                             #          #",
     "#                             #          #",
     "#                             #          #",
     "##########################################",
     },

    {
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                  ##########              ",
     "                           #              ",
     "                           #              ",
     "                           #              ",
     "                    ########              ",
     "                    #                     ",
     "                    #                     ",
     "                    #                     ",
     "                    #                     ",
     "                                          ",
     "                    #                     ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     "                                          ",
     },

    {
     "                                          ",
     "                  #                       ",
     "                  #                       ",
     "                  #                       ",
     "     ##########################           ",
     "                           #              ",
     "                           #              ",
     "            ##########     #              ",
     "    #                      ####           ",
     "    #                                     ",
     "    #                                     ",
     "    #                                     ",
     "    #                                     ",
     "    #                                     ",
     "    #################            #        ",
     "                                 #        ",
     "            #                    #        ",
     "     ########                    #        ",
     "                                 #        ",
     "       ###########################        ",
     "                                 #        ",
     "                                 #        ",
     "                                 #        ",
     "                                          ",
     },
};

const char head[8][8] = {
  "     GG ",
  "    GBBG",
  "    G BG",
  " GGGGGGG",
  "RGGGGGGG",
  " GGGGGGG",
  "        ",
  "        ",
};

const char tail[8][8] = {
  "        ",
  "        ",
  "        ",
  "G GGG GG",
  "GGGGGGGG",
  "GGG GGG ",
  "        ",
  "        ",
};

const char tail2[8][8] = {
  "        ",
  "        ",
  "        ",
  " GG     ",
  "GGGG    ",
  "GGGGG   ",
  "  GGG   ",
  "  GG    ",
};

const char apple[8][8] = {
  "        ",
  " GGGB   ",
  "GGG B   ",
  " G RRR  ",
  "  RRRRR ",
  "  RRRRR ",
  "  RRRRR ",
  "   RRR  ",
};

const char wall[8][8] = {
  "OOOOO OO",
  "OOOOO OO",
  "        ",
  "OO OOOOO",
  "OO OOOOO",
  "        ",
  "OOOOO OO",
  "OOOOO OO",
};

static void draw_element(int x,int y,const char element[8][8],char angle){
  x = x * SNAKE_ELEMENT_SIZE;
  y = y * SNAKE_ELEMENT_SIZE;
  int xx,yy;
  for(xx=0;xx<SNAKE_ELEMENT_SIZE;xx++)
    for(yy=0;yy<SNAKE_ELEMENT_SIZE;yy++){
      char c = COLOR_RED;
      char col = 0;

      if(angle == 0) col = element[yy][xx];
      if(angle == 1) col = element[xx][7-yy];
      if(angle == 2) col = element[xx][yy];
      if(angle == 3) col = element[yy][7-xx];
      if(angle == 4) col = element[7-xx][yy];
      switch(col){
        case 'R': c = COLOR_RED; break;
        case 'G': c = COLOR_GREEN; break;
        case 'B': c = COLOR_BLACK; break;
        case 'b': c = COLOR_BLUE; break;
        case 'Y': c = COLOR_YELLOW; break;
        case 'O': c = 0x28; break;
        default: c = COLOR_WHITE; break;
      };
      draw_pixel( x+xx, y+yy, c );
    }
}



static void load_laby(int num){
  int x,y;
  for(x=0;x<RING_WIDTH;x++)
    for(y=0;y<RING_HEIGHT;y++){
      ring[x][y] = labyrinth[num][y][x];
      if(ring[x][y] != ' '){
        draw_element(x,y,wall,0);
      }else{
        draw_filled_rect(x * SNAKE_ELEMENT_SIZE,
                         y * SNAKE_ELEMENT_SIZE,
                         x * SNAKE_ELEMENT_SIZE+SNAKE_ELEMENT_SIZE-1,
                         y * SNAKE_ELEMENT_SIZE+SNAKE_ELEMENT_SIZE-1, MAKE_COLOR(COLOR_WHITE,COLOR_WHITE));
      }
    }
}

static void snake_generate_apple()
{
  int x,y,i;
  while(1)
  {
    randomagain:
    x = rand() % RING_WIDTH;
    y = rand() % RING_HEIGHT;
    if(ring[x][y] != ' ') continue;
    i = snake_tail;
    while(1){
      if(snake[i][0] == x && snake[i][1] == y) goto randomagain;
      if(i == snake_head) break;
      i = (i+1)%SNAKE_MAX_LENGTH;
    }
    draw_element(x,y,apple,0);
    ring[x][y] = 1;
    break;
  }
}

static void game_over();

static void snake_start(){
  int i;
  load_laby(rand()%4);
  snake_head = 3;
  snake_tail = 0;
  level = 5;
  points = 0;
  for(i=snake_tail;i<snake_head;i++){
    snake[i][0] = 2+i;
    snake[i][1] = 2;
    draw_filled_rect(snake[i][0] * SNAKE_ELEMENT_SIZE,
                     snake[i][1] * SNAKE_ELEMENT_SIZE,
                     snake[i][0] * SNAKE_ELEMENT_SIZE+SNAKE_ELEMENT_SIZE-1,
                     snake[i][1] * SNAKE_ELEMENT_SIZE+SNAKE_ELEMENT_SIZE-1, MAKE_COLOR(COLOR_WHITE,COLOR_RED));
  }
  direction = DIR_RIGHT;
  for(i=0;i<10;i++)
    snake_generate_apple();
}


static void game_over(){
    draw_filled_rect(0,0,camera_screen.width,camera_screen.height, COLOR_WHITE);
    sprintf(str_buf,"Points: %d",points);
    draw_string(0,0,str_buf, MAKE_COLOR(COLOR_WHITE, COLOR_BLUE));
    msleep(3000);
    snake_start();
}

int gui_snake_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
        case KEY_UP:
            if(direction != DIR_DOWN) direction = DIR_UP;
            break;
        case KEY_DOWN:
            if(direction != DIR_UP) direction = DIR_DOWN;
            break;
        case KEY_LEFT:
                if(direction != DIR_RIGHT) direction = DIR_LEFT;
            break;
        case KEY_RIGHT:
                if(direction != DIR_LEFT) direction = DIR_RIGHT;
            break;
        case KEY_SET:
             
             
            break;
        case KEY_ERASE:
        case KEY_DISPLAY:
            break;
    }
    return 0;
}

void gui_snake_draw() {
  unsigned short new_head;
  unsigned short new_tail;
  unsigned short new_cord;
  char game_over_flag = 0,draw_head,clear_tail,draw_points=1;
  unsigned char prevdir = direction;
  unsigned int i;
    new_head = (snake_head+1)%SNAKE_MAX_LENGTH;
    new_tail = (snake_tail+1)%SNAKE_MAX_LENGTH;
    draw_head = 1;
    clear_tail = 1;
    if(direction == DIR_RIGHT){
      new_cord = (snake[snake_head][0]+1)%RING_WIDTH;
      snake[new_head][0] = new_cord;
      snake[new_head][1] = snake[snake_head][1];
    }
    if(direction == DIR_LEFT){
      new_cord = snake[snake_head][0]-1;
      if(new_cord == 0xFFFF) new_cord = RING_WIDTH-1;
      snake[new_head][0] = new_cord;
      snake[new_head][1] = snake[snake_head][1];
    }
    if(direction == DIR_UP){
      new_cord = snake[snake_head][1]-1;
      if(new_cord == 0xFFFF) new_cord = RING_HEIGHT-1;
      snake[new_head][0] = snake[snake_head][0];
      snake[new_head][1] = new_cord;
    }
    if(direction == DIR_DOWN){
      new_cord = (snake[snake_head][1]+1)%RING_HEIGHT;
      snake[new_head][0] = snake[snake_head][0];
      snake[new_head][1] = new_cord;
    }

    i = snake_tail;
    while(1){
      if(snake[i][0] == snake[new_head][0] && snake[i][1] == snake[new_head][1]){
        game_over_flag = 1;
        break;
      }
      if(i == snake_head) break;
      i = (i+1)%SNAKE_MAX_LENGTH;
    }

    if(ring[snake[new_head][0]][snake[new_head][1]] == 1){
      ring[snake[new_head][0]][snake[new_head][1]] = ' ';
      snake_generate_apple();
      points+=level;
      draw_points = 1;
      if((new_head+1)%SNAKE_MAX_LENGTH != snake_tail){
        new_tail = snake_tail;
        clear_tail = 0;
      }
    }else if(ring[snake[new_head][0]][snake[new_head][1]] != ' '){
      game_over_flag = 1;
    }
    if(draw_head){
      if(direction == DIR_UP) draw_element(snake[new_head][0],snake[new_head][1],head,2);   //up
      if(direction == DIR_LEFT) draw_element(snake[new_head][0],snake[new_head][1],head,0);  //left
      if(direction == DIR_DOWN) draw_element(snake[new_head][0],snake[new_head][1],head,1);  //down
      if(direction == DIR_RIGHT) draw_element(snake[new_head][0],snake[new_head][1],head,3);  //right

      new_cord = snake_head-1;
      if(new_cord == 0xFFFF) new_cord = SNAKE_MAX_LENGTH-1;
      if(snake[new_cord][0] > snake[new_head][0] && snake[new_cord][1] > snake[new_head][1] && direction == DIR_UP) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,2);
      else if(snake[new_cord][0] > snake[new_head][0] && snake[new_cord][1] > snake[new_head][1] && direction == DIR_LEFT) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,0);
      else if(snake[new_cord][0] < snake[new_head][0] && snake[new_cord][1] > snake[new_head][1] && direction == DIR_UP) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,4);
      else if(snake[new_cord][0] < snake[new_head][0] && snake[new_cord][1] > snake[new_head][1] && direction == DIR_RIGHT) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,3);
      else if(snake[new_cord][0] < snake[new_head][0] && snake[new_cord][1] < snake[new_head][1] && direction == DIR_RIGHT) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,2);
      else if(snake[new_cord][0] < snake[new_head][0] && snake[new_cord][1] < snake[new_head][1] && direction == DIR_DOWN) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,0);
      else if(snake[new_cord][0] > snake[new_head][0] && snake[new_cord][1] < snake[new_head][1] && direction == DIR_LEFT) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,4);
      else if(snake[new_cord][0] > snake[new_head][0] && snake[new_cord][1] < snake[new_head][1] && direction == DIR_DOWN) draw_element(snake[snake_head][0],snake[snake_head][1],tail2,3);
      else if(prevdir == direction && (direction == DIR_RIGHT || direction == DIR_LEFT)) draw_element(snake[snake_head][0],snake[snake_head][1],tail,0);
      else if(prevdir == direction && (direction == DIR_UP || direction == DIR_DOWN)) draw_element(snake[snake_head][0],snake[snake_head][1],tail,1);
    }
    prevdir = direction;
    if(clear_tail){
        draw_filled_rect(snake[snake_tail][0] * SNAKE_ELEMENT_SIZE,
                         snake[snake_tail][1] * SNAKE_ELEMENT_SIZE,
                         snake[snake_tail][0] * SNAKE_ELEMENT_SIZE+SNAKE_ELEMENT_SIZE-1,
                         snake[snake_tail][1] * SNAKE_ELEMENT_SIZE+SNAKE_ELEMENT_SIZE-1, COLOR_WHITE);
    }
    snake_head = new_head;
    snake_tail = new_tail;
    msleep(100);
    if(game_over_flag){
      game_over();
      game_over_flag = 0;
    }
    if(draw_points){
      draw_points = 0;
      sprintf(str_buf,"Points: %d",points);
      draw_string(10,220,str_buf, MAKE_COLOR(COLOR_WHITE, COLOR_BLUE));
    }
}

int gui_snake_init() {
    draw_filled_rect(0,0,camera_screen.width,camera_screen.height, COLOR_WHITE);
    snake_start();
	gui_set_mode(&GUI_MODE_SNAKE);
    return 1;
}

int basic_module_init() {
  return gui_snake_init();
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

    (int32_t)"Snake",			// Module name
    (int32_t)"Game",

    &_librun.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
