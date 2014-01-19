#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"
#include "clock.h"
#include "backlight.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_mbox.h"
#include "modes.h"

#include "module_def.h"

void gui_game_menu_kbd_process();
int gui_tetris_kbd_process();
void gui_tetris_draw();

gui_handler GUI_MODE_TETRIS = 
    /*GUI_MODE_TETRIS*/ { GUI_MODE_MODULE, gui_tetris_draw, gui_tetris_kbd_process, gui_game_menu_kbd_process, GUI_MODE_FLAG_NODRAWRESTORE };

#define BOARD_WIDTH     (10)
#define BOARD_HEIGHT    (22)
/* Initial time delay (in miliseconds) between falling moves */
#define INI_DELAY_FALL  (540)
/* Score points given by filled rows */
#define SCORE_1_FILLED_ROW  (40)
#define SCORE_2_FILLED_ROW  (100)
#define SCORE_3_FILLED_ROW  (300)
#define SCORE_4_FILLED_ROW  (1200)
/* Number of filled rows required to increase the game level */
#define FILLED_ROWS_FOR_LEVEL_UP    (10)
/* The falling delay is multiplied by this factor with every level up */
#define DELAY_FACTOR_FOR_LEVEL_UP   (0.9)

#define GAME_ERROR_NONE         (0)     /* Everything is OK, oh wonders!      */
#define GAME_ERROR_USER_QUITS   (1)     /* The user quits (bored?), our fail  */
#define GAME_ERROR_NO_MEMORY    (-1)    /* Not enough memory                  */
#define GAME_ERROR_NO_VIDEO     (-2)    /* Video system was not initialized   */
#define GAME_ERROR_NO_IMAGES    (-3)    /* Problem loading the image files    */
#define GAME_ERROR_ASSERT       (-100)  /* Something went very very wrong...  */

#define EVENT_NONE          (0)
#define EVENT_MOVE_DOWN     (1 << 1)
#define EVENT_MOVE_LEFT     (1 << 2)
#define EVENT_MOVE_RIGHT    (1 << 3)
#define EVENT_ROTATE_CW     (1 << 4)    /* rotate clockwise         */
#define EVENT_ROTATE_CCW    (1 << 5)    /* rotate counter-clockwise */
#define EVENT_DROP          (1 << 6)
#define EVENT_PAUSE         (1 << 7)
#define EVENT_RESTART       (1 << 8)
#define EVENT_SHOW_NEXT     (1 << 9)    /* toggle show next tetromino */
// Tetromino definitions (used as indexes: must be between 0-6)
#define TETROMINO_I     (0)
#define TETROMINO_O     (1)
#define TETROMINO_T     (2)
#define TETROMINO_S     (3)
#define TETROMINO_Z     (4)
#define TETROMINO_J     (5)
#define TETROMINO_L     (6)
/* Tetromino colors */
#define TETRIS_COLOR_CYAN      COLOR_SPLASH_PINK
#define TETRIS_COLOR_RED       COLOR_RED
#define TETRIS_COLOR_BLUE      COLOR_BLUE
#define TETRIS_COLOR_ORANGE    COLOR_WHITE
#define TETRIS_COLOR_GREEN     COLOR_GREEN
#define TETRIS_COLOR_YELLOW    COLOR_YELLOW
#define TETRIS_COLOR_PURPLE    COLOR_BLACK
#define EMPTY_CELL  (-1)
/* screen colors */
#define TETRIS_COLOR_BG        MAKE_COLOR(COLOR_GREY,COLOR_GREY)
#define TETRIS_COLOR_BOARD     MAKE_COLOR(COLOR_SPLASH_GREY,COLOR_SPLASH_GREY)

typedef struct StcTetramino {
    int cells[4][4];
    int x;
    int y;
    int size;
    int type;
} StcTetramino;

typedef struct StcPlatform StcPlatform;

typedef struct StcGame {
    int map[BOARD_WIDTH][BOARD_HEIGHT];

    StcTetramino nextBlock;     /* next tetromino               */
    StcTetramino fallingBlock;  /* current falling tetromino    */
    StcPlatform *platform;      /* platform hidden data         */
    int errorCode;              /* game error code              */
    long systemTime;            /* system time in miliseconds   */
    int delay;          /* delay time for falling tetrominoes   */
    int isOver;         /* 1 if the game is over, 0 otherwise   */
    int isPaused;       /* 1 if the game is paused, 0 otherwise */
    int showPreview;    /* 1 if we must show preview tetramino  */
    long lastFallTime;  /* last time the game moved the falling tetromino */

    int events;

    struct {
        long score;         /* user score for current game      */
        long high;          /* high score                       */
        int lines;          /* total number of lines cleared    */
        int totalPieces;    /* total number of tetraminoes used */
        int pieces[7];      /* number of tetraminoes per type   */
        int level;          /* current game level               */
    } stats;
} StcGame;
StcGame *createGame();
void deleteGame(StcGame *pGame);
int gameInit(StcGame *gameInstance);
void gameEnd(StcGame *gameInstance);
void gameUpdate(StcGame *gameInstance);


StcGame *game;


// No need to import such simple
long mkdir_if_not_exist(const char *dirname) 
{
    // Check if directory exists and create it if it does not.
    if (stat(dirname,0) != 0) return mkdir(dirname);
    return 0;   // Success
}


int platformInit(StcGame *gameInstance){ return GAME_ERROR_NONE;}
void platformEnd(StcGame *gameInstance){}

/* Read input device and notify game */
void platformReadInput(StcGame *gameInstance){}
#define PREVIEW_X 150
#define PREVIEW_Y 10
#define BOARD_X 10
#define BOARD_Y 10
#define TILE_SIZE 10
/* Render the state of the game */
int tmp[BOARD_WIDTH][BOARD_HEIGHT];
int tmp2[BOARD_WIDTH][BOARD_HEIGHT];

int prevNextBlockType = -1;
void platformRenderGame(StcGame *gameInstance){
    int i, j;

    for(i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j){
          tmp[i][j] = EMPTY_CELL;
          tmp2[i][j] = EMPTY_CELL;
        }
    }

    /* Draw preview block */
    if(game->nextBlock.type != prevNextBlockType){
        prevNextBlockType = game->nextBlock.type;
        for (i = 0; i < 4; ++i) {
            for (j = 0; j < 4; ++j) {
                if (game->nextBlock.cells[i][j] != EMPTY_CELL) {
                    draw_filled_rect(camera_screen.ts_button_border+PREVIEW_X + (TILE_SIZE * i),
                            PREVIEW_Y + (TILE_SIZE * j),
                            camera_screen.ts_button_border+PREVIEW_X + (TILE_SIZE * i)+TILE_SIZE-1,
                            PREVIEW_Y + (TILE_SIZE * j)+TILE_SIZE-1,
                             MAKE_COLOR(game->nextBlock.cells[i][j], game->nextBlock.cells[i][j]));
                }else{
                    draw_filled_rect(camera_screen.ts_button_border+PREVIEW_X + (TILE_SIZE * i),
                            PREVIEW_Y + (TILE_SIZE * j),
                            camera_screen.ts_button_border+PREVIEW_X + (TILE_SIZE * i)+TILE_SIZE-1,
                            PREVIEW_Y + (TILE_SIZE * j)+TILE_SIZE-1,
                            TETRIS_COLOR_BG);
                }
            }
        }
    }
    
    /* Draw the cells in the board */
    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j){
            if (game->map[i][j] != EMPTY_CELL) {
                tmp2[i][j] = game->map[i][j];
            }
        }
    }
    /* Draw falling tetromino */
    for (i = 0; i<4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (game->fallingBlock.cells[i][j] != EMPTY_CELL) {
              tmp[i+game->fallingBlock.x][j+game->fallingBlock.y] = game->fallingBlock.cells[i][j];
            }
        }
    }

    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j){
                    if(tmp[i][j] != EMPTY_CELL){
                    draw_filled_rect(camera_screen.ts_button_border+BOARD_X + (TILE_SIZE * i),
                            BOARD_Y + (TILE_SIZE * j),
                            camera_screen.ts_button_border+BOARD_X + (TILE_SIZE * i)+TILE_SIZE-1,
                            BOARD_Y + (TILE_SIZE * j)+TILE_SIZE-1,
                             MAKE_COLOR(tmp[i][j], tmp[i][j]));
                    }else if(tmp2[i][j] != EMPTY_CELL){
                    draw_filled_rect(camera_screen.ts_button_border+BOARD_X + (TILE_SIZE * i),
                            BOARD_Y + (TILE_SIZE * j),
                            camera_screen.ts_button_border+BOARD_X + (TILE_SIZE * i)+TILE_SIZE-1,
                            BOARD_Y + (TILE_SIZE * j)+TILE_SIZE-1,
                             MAKE_COLOR(tmp2[i][j], tmp2[i][j]));
                    }else{
                    draw_filled_rect(camera_screen.ts_button_border+BOARD_X + (TILE_SIZE * i),
                            BOARD_Y + (TILE_SIZE * j),
                            camera_screen.ts_button_border+BOARD_X + (TILE_SIZE * i)+TILE_SIZE-1,
                            BOARD_Y + (TILE_SIZE * j)+TILE_SIZE-1,
                             TETRIS_COLOR_BOARD);
                    }
        }
    }
    /* output game info */
    char str_buf[100];
    static struct tm *ttm;
    sprintf(str_buf,"High:    %5d",game->stats.high);
    draw_string(camera_screen.ts_button_border+150,35,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    sprintf(str_buf,"Points:  %5d",game->stats.score);
    draw_string(camera_screen.ts_button_border+150,55,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    sprintf(str_buf,"Lines:   %5d",game->stats.lines);
    draw_string(camera_screen.ts_button_border+150,75,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    sprintf(str_buf,"Level:   %5d",game->stats.level);
    draw_string(camera_screen.ts_button_border+150,95,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    sprintf(str_buf,"UP  -> Pause");
    draw_string(camera_screen.ts_button_border+150,135,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    sprintf(str_buf,"SET -> Rotate");
    draw_string(camera_screen.ts_button_border+150,155,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    ttm = get_localtime();
    sprintf(str_buf,"Time:    %2u:%02u", ttm->tm_hour, ttm->tm_min);
    draw_string(camera_screen.ts_button_border+150,195,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
    sprintf(str_buf,"Batt:     %3d%%", get_batt_perc());
    draw_string(camera_screen.ts_button_border+150,215,str_buf, MAKE_COLOR(TETRIS_COLOR_BG, COLOR_BLACK));
}

/* Return the current system time in milliseconds */
long platformGetSystemTime(){return get_tick_count();}

/* Set matrix elements to indicated value */
static void setMatrixCells(int *matrix, int width, int height, int value) {
    int i, j;
    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            *(matrix + i + (j * width)) = value;
        }
    }
}

/* Initialize tetromino cells for every tipe of tetromino */
static void setTetramino(int indexTetramino, StcTetramino *tetramino) {

    /* Initialize tetromino cells to empty cells */
    setMatrixCells(&tetramino->cells[0][0], 4, 4, EMPTY_CELL);

    /* Almost all the blocks have size 3 */
    tetramino->size = 3;

    /* Initial configuration from: http://www.tetrisconcept.com/wiki/index.php/SRS */
    switch (indexTetramino) {
    case TETROMINO_I:
        tetramino->cells[0][1] = TETRIS_COLOR_CYAN;
        tetramino->cells[1][1] = TETRIS_COLOR_CYAN;
        tetramino->cells[2][1] = TETRIS_COLOR_CYAN;
        tetramino->cells[3][1] = TETRIS_COLOR_CYAN;
        tetramino->size = 4;
        break;
    case TETROMINO_O:
        tetramino->cells[0][0] = TETRIS_COLOR_YELLOW;
        tetramino->cells[0][1] = TETRIS_COLOR_YELLOW;
        tetramino->cells[1][0] = TETRIS_COLOR_YELLOW;
        tetramino->cells[1][1] = TETRIS_COLOR_YELLOW;
        tetramino->size = 2;
        break;
    case TETROMINO_T:
        tetramino->cells[0][1] = TETRIS_COLOR_PURPLE;
        tetramino->cells[1][0] = TETRIS_COLOR_PURPLE;
        tetramino->cells[1][1] = TETRIS_COLOR_PURPLE;
        tetramino->cells[2][1] = TETRIS_COLOR_PURPLE;
        break;
    case TETROMINO_S:
        tetramino->cells[0][1] = TETRIS_COLOR_GREEN;
        tetramino->cells[1][0] = TETRIS_COLOR_GREEN;
        tetramino->cells[1][1] = TETRIS_COLOR_GREEN;
        tetramino->cells[2][0] = TETRIS_COLOR_GREEN;
        break;
    case TETROMINO_Z:
        tetramino->cells[0][0] = TETRIS_COLOR_RED;
        tetramino->cells[1][0] = TETRIS_COLOR_RED;
        tetramino->cells[1][1] = TETRIS_COLOR_RED;
        tetramino->cells[2][1] = TETRIS_COLOR_RED;
        break;
    case TETROMINO_J:
        tetramino->cells[0][0] = TETRIS_COLOR_BLUE;
        tetramino->cells[0][1] = TETRIS_COLOR_BLUE;
        tetramino->cells[1][1] = TETRIS_COLOR_BLUE;
        tetramino->cells[2][1] = TETRIS_COLOR_BLUE;
        break;
    case TETROMINO_L:
        tetramino->cells[0][1] = TETRIS_COLOR_ORANGE;
        tetramino->cells[1][1] = TETRIS_COLOR_ORANGE;
        tetramino->cells[2][0] = TETRIS_COLOR_ORANGE;
        tetramino->cells[2][1] = TETRIS_COLOR_ORANGE;
        break;
    }
    tetramino->type = indexTetramino;
}

/*  Start a new game */
static void startGame(StcGame *game) {
    int i;

    /* Initialize game data */
    game->errorCode = GAME_ERROR_NONE;
    game->systemTime = platformGetSystemTime();
    game->lastFallTime = game->systemTime;
    game->isOver = 0;
    game->isPaused = 0;
    game->showPreview = 1;
    game->events = EVENT_NONE;
    game->delay = INI_DELAY_FALL;
    /* Initialize game statistics */
    game->stats.score = 0;
    game->stats.lines = 0;
    game->stats.totalPieces = 0;
    game->stats.level = 0;
    for (i = 0; i < 7; ++i) {
        game->stats.pieces[i] = 0;
    }

    /* Initialize rand generator */
    srand(game->systemTime);

    /* Initialize game tile map */
    setMatrixCells(&game->map[0][0], BOARD_WIDTH, BOARD_HEIGHT, EMPTY_CELL);

    /* Initialize falling tetromino */
    setTetramino(rand() % 7, &game->fallingBlock);
    game->fallingBlock.x = (BOARD_WIDTH - game->fallingBlock.size) / 2;
    game->fallingBlock.y = 0;

    /* Initialize preview tetromino */
    setTetramino(rand() % 7, &game->nextBlock);
}

/* Create new game object */
StcGame *createGame() {
    /* Allocate space for our game object */
    StcGame *game = (StcGame *) malloc(sizeof(StcGame));
    return game;
}

/*
 * Initializes the game, if there are no problems returns GAME_ERROR_NONE.
 */
int gameInit(StcGame *game) {
    int errorCode;

    errorCode = platformInit(game);
    if (errorCode == GAME_ERROR_NONE) {
        startGame(game);
        return GAME_ERROR_NONE;
    }
    return errorCode;
};

void gameEnd(StcGame *game) {
    /* Free platform resources */
    platformEnd(game);
}

void deleteGame(StcGame *game) {
    free(game);
}

/*
 * Rotate falling tetromino. If there are no collisions when the
 * tetromino is rotated this modifies the tetramino's cell buffer.
 */
void rotateTetramino(StcGame *game, int clockwise) {
    int i, j;
    int rotated[4][4];  /* temporary array to hold rotated cells */

    /* If TETRAMINO_O is falling return immediately */
    if (game->fallingBlock.type == TETROMINO_O) {
        return; /* rotation doesn't require any changes */
    }

    /* Initialize rotated cells to blank */
    setMatrixCells(&rotated[0][0], 4, 4, EMPTY_CELL);

    /* Copy rotated cells to the temporary array */
    for (i = 0; i < game->fallingBlock.size; ++i) {
        for (j = 0; j < game->fallingBlock.size; ++j) {
            if (clockwise) {
                rotated[game->fallingBlock.size - j - 1][i] = game->fallingBlock.cells[i][j];
            } else {
                rotated[j][game->fallingBlock.size - i - 1] = game->fallingBlock.cells[i][j];
            }
        }
    }
    /* Check collision of the temporary array */
    for (i = 0; i < game->fallingBlock.size; ++i) {
        for (j = 0; j < game->fallingBlock.size; ++j) {
            if (rotated[i][j] != EMPTY_CELL) {
                /* Check collision with left, right or bottom borders of the map */
                if ((game->fallingBlock.x + i < 0) || (game->fallingBlock.x + i >= BOARD_WIDTH)
                        || (game->fallingBlock.y + j >= BOARD_HEIGHT)) {
                    return; /* there was collision therefore return */
                }
                /* Check collision with existing cells in the map */
                if (game->map[i + game->fallingBlock.x][j + game->fallingBlock.y] != EMPTY_CELL) {
                    return; /* there was collision therefore return */
                }
            }
        }
    }
    /* There are no collisions, replace tetramino cells with rotated cells */
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            game->fallingBlock.cells[i][j] = rotated[i][j];
        }
    }
}

/*
 * Check if tetromino will collide with something if it is moved in the requested direction.
 * If there are collisions returns 1 else returns 0.
 */
static int checkCollision(StcGame *game, int dx, int dy) {
    int newx, newy, i, j;

    newx = game->fallingBlock.x + dx;
    newy = game->fallingBlock.y + dy;

    for (i = 0; i < game->fallingBlock.size; ++i) {
        for (j = 0; j < game->fallingBlock.size; ++j) {
            if (game->fallingBlock.cells[i][j] != EMPTY_CELL) {
                /* Check the tetramino would be inside the left, right and bottom borders */
                if ((newx + i < 0) || (newx + i >= BOARD_WIDTH)
                    || (newy + j >= BOARD_HEIGHT)) {
                    return 1;
                }
                /* Check the tetromino won't collide with existing cells in the map */
                if (game->map[newx + i][newy + j] != EMPTY_CELL) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* Game scoring: http://www.tetrisconcept.com/wiki/index.php/Scoring */
static void onFilledRows(StcGame *game, int filledRows) {
    /* Update total number of filled rows */
    game->stats.lines += filledRows;

    /* Increase score accordingly to the number of filled rows */
    switch (filledRows) {
    case 1:
        game->stats.score += (SCORE_1_FILLED_ROW * (game->stats.level));
        break;
    case 2:
        game->stats.score += (SCORE_2_FILLED_ROW * (game->stats.level));
        break;
    case 3:
        game->stats.score += (SCORE_3_FILLED_ROW * (game->stats.level));
        break;
    case 4:
        game->stats.score += (SCORE_4_FILLED_ROW * (game->stats.level));
        break;
    default:
        game->errorCode = GAME_ERROR_ASSERT;    /* This can't happen */
    }
    /* Check if we need to update level */
    if (game->stats.lines >= FILLED_ROWS_FOR_LEVEL_UP * (game->stats.level)) {
        game->stats.level++;

        /* Increase speed for falling tetrominoes */
        game->delay *= DELAY_FACTOR_FOR_LEVEL_UP;
    }
}

/*
 * Move tetramino in direction especified by (x, y) (in tile units)
 * This function detects if there are filled rows or if the move 
 * lands a falling tetromino, also checks for game over condition.
 */
static void moveTetramino(StcGame *game, int x, int y) {
    int i, j, hasFullRow, numFilledRows;
    
    /* Check if the move would create a collision */
    if (checkCollision(game, x, y)) {
        /* In case of collision check if move was downwards (y == 1) */
        if (y == 1) {
            /* Check if collision occur when the falling
             * tetromino is in the 1st or 2nd row */
            if (game->fallingBlock.y <= 1) {
                game->isOver = 1;   /* if this happens the game is over */
            }
            else {
                /* The falling tetromino has reached the bottom,
                 * so we copy their cells to the board map */
                for (i = 0; i < game->fallingBlock.size; ++i) {
                    for (j = 0; j < game->fallingBlock.size; ++j) {
                        if (game->fallingBlock.cells[i][j] != EMPTY_CELL) {
                            game->map[game->fallingBlock.x + i][game->fallingBlock.y + j]
                                    = game->fallingBlock.cells[i][j];
                        }
                    }
                }

                /* Check if the landing tetromino has created full rows */
                numFilledRows = 0;
                for (j = 1; j < BOARD_HEIGHT; ++j) {
                    hasFullRow = 1;
                    for (i = 0; i < BOARD_WIDTH; ++i) {
                        if (game->map[i][j] == EMPTY_CELL) {
                            hasFullRow = 0;
                            break;
                        }
                    }
                    /* If we found a full row we need to remove that row from the map
                     * we do that by just moving all the above rows one row below */
                    if (hasFullRow) {
                        for (x = 0; x < BOARD_WIDTH; ++x) {
                            for (y = j; y > 0; --y) {
                                game->map[x][y] = game->map[x][y - 1];
                            }
                        }
                        numFilledRows++;    /* increase filled row counter */
                    }
                }

                /* Update game statistics */
                if (numFilledRows) {
                    onFilledRows(game, numFilledRows);
                }
                game->stats.totalPieces++;
                game->stats.pieces[game->fallingBlock.type]++;
                
                /* Use preview tetromino as falling tetromino.
                 * Copy preview tetramino for falling tetramino */
                for (i = 0; i < 4; ++i) {
                    for (j = 0; j < 4; ++j) {
                        game->fallingBlock.cells[i][j] = game->nextBlock.cells[i][j];
                    }
                }
                game->fallingBlock.size = game->nextBlock.size;
                game->fallingBlock.type = game->nextBlock.type;

                /* Reset position */
                game->fallingBlock.y = 0;
                game->fallingBlock.x = (BOARD_WIDTH - game->fallingBlock.size) / 2;

                /* Create next preview tetromino */
                setTetramino(rand() % 7, &game->nextBlock);
            }
        }
    }
    else {
        /* There are no collisions, just move the tetramino */
        game->fallingBlock.x += x;
        game->fallingBlock.y += y;
    }
}

/* Hard drop */
static void dropTetramino(StcGame *game) {
   int y;
   y = 1;
   /* Calculate number of cells to drop */
   while (!checkCollision(game, 0, y)) {
       y++;
   }
   moveTetramino(game, 0, y - 1);
}

/*
 * Main function game called every frame
 */
void gameUpdate(StcGame *game) {
    long sysTime;
    /* Read user input */
    platformReadInput(game);

    /* Update game state */
    if (game->isOver) {
		
		if (game->stats.score > game->stats.high) {
			game->stats.high = game->stats.score;
			FILE * f;
			long buf;
			buf = game->stats.score;

			mkdir_if_not_exist("A/CHDK/GAMES");
			f = fopen ( "A/CHDK/GAMES/TETRIS.SCO" , "wb" );
			fwrite (&buf , 1 , sizeof(buf) , f );
			fclose (f);
		}
			
		
        //if (game->events & EVENT_RESTART) {
		if (game->events & EVENT_PAUSE) {
		    
			//TurnOnBackLight();
			
            game->isOver = 0;
			startGame(game);
			
        }
    }
    else {
        sysTime = platformGetSystemTime();

        /* Always handle pause event */
        if (game->events & EVENT_PAUSE) {
            game->isPaused = !game->isPaused;
            game->events = EVENT_NONE;
        }

        /* Check if the game is paused */
        if (game->isPaused) {
            /* We achieve the effect of pausing the game
             * adding the last frame duration to lastFallTime */
            game->lastFallTime += (sysTime - game->systemTime);
        }
        else {
            if (game->events != EVENT_NONE) {
                if (game->events & EVENT_SHOW_NEXT) {
                    game->showPreview = !game->showPreview;
                }
                if (game->events & EVENT_DROP) {
                    dropTetramino(game);
                }
                if (game->events & EVENT_ROTATE_CW) {
                    rotateTetramino(game, 1);
                }
                if (game->events & EVENT_MOVE_RIGHT) {
                    moveTetramino(game, 1, 0);
                }
                else if (game->events & EVENT_MOVE_LEFT) {
                    moveTetramino(game, -1, 0);
                }
                if (game->events & EVENT_MOVE_DOWN) {
                    moveTetramino(game, 0, 1);
                }
                game->events = EVENT_NONE;
            }
            /* Check if it's time to move downwards the falling tetromino */
            if (sysTime - game->lastFallTime >= game->delay) {
                moveTetramino(game, 0, 1);
                game->lastFallTime = sysTime;
            }
        }
        game->systemTime = sysTime;
    }
    /* Draw game state */
    platformRenderGame(game);
}

void gui_tetris_init(){
    draw_filled_rect(camera_screen.ts_button_border+0,0,camera_screen.width-camera_screen.ts_button_border,camera_screen.height, TETRIS_COLOR_BG);
    draw_rect(camera_screen.ts_button_border+BOARD_X-1,BOARD_Y-1,camera_screen.ts_button_border+BOARD_WIDTH*TILE_SIZE+10,BOARD_HEIGHT*TILE_SIZE+10, COLOR_BLACK);
    game = createGame();
    gameInit(game);
  
    long buf;
    FILE *f;    

    f=fopen("A/CHDK/GAMES/TETRIS.SCO","rb");
    if(!f) {
        game->stats.high = 0;
    } else {
    
    fread( &buf, 1, sizeof( buf ), f );
    game->stats.high = buf; 
    
    }

    fclose (f);
    startGame(game);
}

int basic_module_init() {
  gui_set_mode(&GUI_MODE_TETRIS);
  gui_tetris_init();
  return 1;
}

void gui_tetris_draw(){
  gameUpdate(game);
}

int gui_tetris_kbd_process() {
        switch ( kbd_get_autoclicked_key() )
        {
            case KEY_UP:
            if ((game->isPaused) || (game->isOver)) {
                TurnOnBackLight();
            } else { TurnOffBackLight(); }
                game->events |= EVENT_PAUSE;
                break;
            case KEY_LEFT:
                game->events |= EVENT_MOVE_LEFT;
                break;
            case KEY_RIGHT:
                game->events |= EVENT_MOVE_RIGHT;
                break;
            case KEY_DOWN:
                game->events |= EVENT_MOVE_DOWN;
                break;
            //case KEY_SET:
            //game->events |= EVENT_RESTART;
            //break;
            case KEY_DISPLAY:
            case KEY_ERASE:
            case KEY_SET:
                game->events |= EVENT_ROTATE_CW;
                break;
            default:
                break;
        }
        return 0;
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

    (int32_t)"Tetris",			// Module name
    (int32_t)"Game",

    &_librun.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
