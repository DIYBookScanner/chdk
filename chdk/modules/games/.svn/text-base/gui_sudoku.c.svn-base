/*	TODO:
	- draw_menu: put those Strings in an array!
	- somehow use the screenbuffer after a messagebox, so that nothing flickers?
	- draw_marker as a new draw function ->don't redraw entire field each time you move
	- adjustable Difficulty, maybe after optimization, because other START_NUMBERS are slower
	- compatibility with other cams?
	- highscore with time
	- battery and watch
*/

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
#include "fileutil.h"

#include "module_def.h"
#include "simple_module.h"

void gui_module_menu_kbd_process();
int gui_sudoku_kbd_process();
void gui_sudoku_draw();
void exit_sudoku();

gui_handler GUI_MODE_SUDOKU =
    /*GUI_MODE_SUDOKU*/  { GUI_MODE_MODULE, gui_sudoku_draw, gui_sudoku_kbd_process, gui_module_menu_kbd_process, GUI_MODE_FLAG_NODRAWRESTORE };

static int running = 0;

//-------------------------------------------------------------------
#define SUDOKU_BG_COLOR		MAKE_COLOR(COLOR_WHITE, COLOR_WHITE)
#define MARKER_COLOR		COLOR_HISTO_G_PLAY // green for all cameras in play mode
#define TEXT_COLOR			MAKE_COLOR(SUDOKU_BG_COLOR, COLOR_BLACK)
#define MARKER_TEXT_COLOR 	MAKE_COLOR(MARKER_COLOR, COLOR_WHITE)

#define MODE_VIEW			1
#define MODE_EDIT			2
#define MODE_MENU			4

//for drawing
#define BG					1
#define FIELD				2
#define MENU				4
#define PAD					8

#define START_NUMBERS		25
#define MAX_START_NUMBERS	32
#define MENU_ELEMENTS		8

//this program uses a flag-format because it's necessary to save more than
//one number in one array-Integer, f.e. for solving
//There are 3 functions: get_dec_num(int), one_plus_nums(int), is_one_num(int)
int flag[10]={0x0, 0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100};
			// 0    1   2   3   4    5    6    7    8     9
int xPos, yPos;
int xPosOld, yPosOld;
int fieldLineDistance;
int fieldLineLength;
int mode;  //MODE_VIEW, MODE_EDIT, MODE_MENU
int xFieldBorder;
int yFieldBorder;
int menuPos;
int draw;	//with flags, for drawing
int xPadStart, yPadStart, padLineDistance; //number pad X, Y and distance, for entering a number
int xPosPad, yPosPad;

int field[9][9];

//Will contain both numbers entered by the user and default numbers
int user[9][9];

//Here, the computer tries to solve sudokus
int mess[9][9];


/////////////////////Flag format specific functions///////////////////////////////

int get_dec_num(int number)
{
	int i;
	for (i=1; i<10; i++)
	{
		if (number&flag[i])return i;
	}
	return 0;
}

//Checks whether more than one flag(=number) is set
int one_plus_nums(int number)
{
	if (number==0)return 0;
	int counter=0;
	int i;
	for (i=1; i<10; i++)
	{
		if (number & flag[i])
		{
			if (counter==1)return 1;
			counter++;
		}
	}
	return 0;
}

//Checks, if one flag is set
int is_one_num(int number)
{
	if (number==0)return 0;
	int counter=0;
	int i;
	for (i=1; i<10; i++)
	{
		if (number & flag[i])
		{
			if (counter==1)return 0;
			counter++;
		}
	}
	return 1;
}


/////////////////////Draw functions/////////////////////////////////////////

void del_numpad()
{
	draw_filled_rect(xPadStart, yPadStart-padLineDistance, xPadStart+padLineDistance*3, yPadStart+padLineDistance*4, SUDOKU_BG_COLOR);
}

void draw_numpad()
{
	int i, y, x;
	static char str[16];
	del_numpad();

	//horizontal
	draw_line(xPadStart+padLineDistance, yPadStart-padLineDistance, xPadStart+2*padLineDistance, yPadStart-padLineDistance, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	for (i=0; i<4; i++)draw_line(xPadStart, yPadStart+padLineDistance*i, xPadStart+padLineDistance*3, yPadStart+padLineDistance*i, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));

	//vertical
	draw_line(xPadStart, yPadStart, xPadStart, yPadStart+3*padLineDistance, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xPadStart+padLineDistance, yPadStart-padLineDistance, xPadStart+padLineDistance, yPadStart+3*padLineDistance, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xPadStart+2*padLineDistance, yPadStart-padLineDistance, xPadStart+2*padLineDistance, yPadStart+3*padLineDistance, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xPadStart+3*padLineDistance, yPadStart, xPadStart+3*padLineDistance, yPadStart+3*padLineDistance, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));

	//numbers
	i=0;
	for (y=0; y<3; y++)for (x=0; x<3; x++)
	{
		i++;
		sprintf(str, "%i", i);
		draw_string(xPadStart+padLineDistance*x+(padLineDistance-FONT_WIDTH)/2, yPadStart+padLineDistance*y+(padLineDistance-FONT_HEIGHT)/2, str, MAKE_COLOR(SUDOKU_BG_COLOR, COLOR_BLACK));
	}
	sprintf(str, "%i", 0);
	draw_string(xPadStart+padLineDistance+(padLineDistance-FONT_WIDTH)/2, yPadStart+padLineDistance*(-1)+(padLineDistance-FONT_HEIGHT)/2, str, MAKE_COLOR(SUDOKU_BG_COLOR, COLOR_BLACK));

	//marker
	draw_rect(xPadStart+xPosPad*padLineDistance, yPadStart+yPosPad*padLineDistance, xPadStart+(xPosPad+1)*padLineDistance, yPadStart+(yPosPad+1)*padLineDistance, MAKE_COLOR(MARKER_COLOR, MARKER_COLOR));
	draw_rect(xPadStart+xPosPad*padLineDistance+1, yPadStart+yPosPad*padLineDistance+1, xPadStart+(xPosPad+1)*padLineDistance-1, yPadStart+(yPosPad+1)*padLineDistance-1, MAKE_COLOR(MARKER_COLOR, MARKER_COLOR));
	draw_rect(xPadStart+xPosPad*padLineDistance+2, yPadStart+yPosPad*padLineDistance+2, xPadStart+(xPosPad+1)*padLineDistance-2, yPadStart+(yPosPad+1)*padLineDistance-2, MAKE_COLOR(MARKER_COLOR, MARKER_COLOR));
}

int get_pad_num()
{
	if (xPosPad==1 && yPosPad==-1)return 0;
	else return flag[xPosPad+yPosPad*3+1];
}

void set_pad_num(int number)
{
	if (number==0)xPosPad=yPosPad=0;
	else
	{
		xPosPad=(number-1)%3;
		yPosPad=(number-1)/3;
	}
}

void draw_menu()
{
	int i;
	static char str[16];
	for (i=0; i<MENU_ELEMENTS; i++)
	{
		if (i==0) sprintf(str, " Check sudoku ");
		if (i==1) sprintf(str, " Solve sudoku ");
		if (i==2) sprintf(str, " New sudoku ");
		if (i==3) sprintf(str, " Enter sudoku ");
		if (i==5) sprintf(str, " Exit ");
		if (i==4) sprintf(str, " Info ");
		if (i==6) sprintf(str, " Save and Exit ");
		if (i==7) sprintf(str, " Del save game ");

		if (menuPos==i && mode==MODE_MENU) draw_string(camera_screen.width-(FONT_WIDTH*15), FONT_HEIGHT*(i+1)+i*3, str, MARKER_TEXT_COLOR);
		else draw_string(camera_screen.width-(FONT_WIDTH*15), FONT_HEIGHT*(i+1)+i*3, str, TEXT_COLOR);
	}
}

void draw_field()
{
	int i, x, y;
	static char str[16];

	//redraw last field to remove the marker
	draw_filled_rect(xFieldBorder+xPosOld*fieldLineDistance, yFieldBorder+yPosOld*fieldLineDistance, xFieldBorder+(xPosOld+1)*fieldLineDistance, yFieldBorder+(yPosOld+1)*fieldLineDistance, MAKE_COLOR(SUDOKU_BG_COLOR, COLOR_BLACK));
	xPosOld=xPos;
	yPosOld=yPos;

	//Lines
	for (i=0; i<10; ++i){
		//vertical lines
		draw_line(xFieldBorder+fieldLineDistance*i, yFieldBorder, xFieldBorder+fieldLineDistance*i, yFieldBorder+fieldLineLength, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
		//horizontal lines
		draw_line(xFieldBorder, yFieldBorder+fieldLineDistance*i, xFieldBorder+fieldLineLength, yFieldBorder+fieldLineDistance*i, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	}
	//draw thick vertical lines
	draw_line(xFieldBorder+fieldLineDistance*3-1, yFieldBorder, xFieldBorder+fieldLineDistance*3-1, yFieldBorder+fieldLineLength, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xFieldBorder+fieldLineDistance*3+1, yFieldBorder, xFieldBorder+fieldLineDistance*3+1, yFieldBorder+fieldLineLength, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));

	draw_line(xFieldBorder+fieldLineDistance*6-1, yFieldBorder, xFieldBorder+fieldLineDistance*6-1, yFieldBorder+fieldLineLength, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xFieldBorder+fieldLineDistance*6+1, yFieldBorder, xFieldBorder+fieldLineDistance*6+1, yFieldBorder+fieldLineLength, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));

	//draw thick horizontal lines
	draw_line(xFieldBorder, yFieldBorder+fieldLineDistance*3-1, xFieldBorder+fieldLineLength, yFieldBorder+fieldLineDistance*3-1, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xFieldBorder, yFieldBorder+fieldLineDistance*3+1, xFieldBorder+fieldLineLength, yFieldBorder+fieldLineDistance*3+1, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));

	draw_line(xFieldBorder, yFieldBorder+fieldLineDistance*6-1, xFieldBorder+fieldLineLength, yFieldBorder+fieldLineDistance*6-1, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
	draw_line(xFieldBorder, yFieldBorder+fieldLineDistance*6+1, xFieldBorder+fieldLineLength, yFieldBorder+fieldLineDistance*6+1, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));

	//cursor
	if (mode==MODE_VIEW){
		draw_rect(xFieldBorder+xPos*fieldLineDistance, yFieldBorder+yPos*fieldLineDistance, xFieldBorder+(xPos+1)*fieldLineDistance, yFieldBorder+(yPos+1)*fieldLineDistance, MAKE_COLOR(MARKER_COLOR, MARKER_COLOR));
		draw_rect(xFieldBorder+xPos*fieldLineDistance+1, yFieldBorder+yPos*fieldLineDistance+1, xFieldBorder+(xPos+1)*fieldLineDistance-1, yFieldBorder+(yPos+1)*fieldLineDistance-1, MAKE_COLOR(MARKER_COLOR, MARKER_COLOR));
		draw_rect(xFieldBorder+xPos*fieldLineDistance+2, yFieldBorder+yPos*fieldLineDistance+2, xFieldBorder+(xPos+1)*fieldLineDistance-2, yFieldBorder+(yPos+1)*fieldLineDistance-2, MAKE_COLOR(MARKER_COLOR, MARKER_COLOR));
	}
	if (mode==MODE_EDIT){
		draw_filled_ellipse(xFieldBorder+(xPos+1)*fieldLineDistance-fieldLineDistance/2, yFieldBorder+(yPos+1)*fieldLineDistance-fieldLineDistance/2, fieldLineDistance/2-3, fieldLineDistance/2-1, MAKE_COLOR(MARKER_COLOR, COLOR_RED));
		sprintf(str, "%i", get_dec_num(user[yPos][xPos]));
		draw_string(xFieldBorder+fieldLineDistance*xPos+(fieldLineDistance-FONT_WIDTH)/2, yFieldBorder+fieldLineDistance*yPos+(fieldLineDistance-FONT_HEIGHT)/2, str, MAKE_COLOR(MARKER_COLOR, COLOR_WHITE));
	}

	//Numbers
	for (y=0; y<9; y++){
		for (x=0; x<9; x++){
			/*im editmode wird an der cursorposition keine Zahl angezeigt, 0 wird auch nicht angezeigt*/
			if (user[y][x]==0) continue;
			if (mode==MODE_EDIT && x==xPos && y==yPos) continue;
			sprintf(str, "%i", get_dec_num(user[y][x]));
			if (field[y][x]!=0)
				draw_string(xFieldBorder+fieldLineDistance*x+(fieldLineDistance-FONT_WIDTH)/2, yFieldBorder+fieldLineDistance*y+(fieldLineDistance-FONT_HEIGHT)/2, str, MAKE_COLOR(SUDOKU_BG_COLOR, COLOR_BLACK));
			else draw_string(xFieldBorder+fieldLineDistance*x+(fieldLineDistance-FONT_WIDTH)/2, yFieldBorder+fieldLineDistance*y+(fieldLineDistance-FONT_HEIGHT)/2, str, MAKE_COLOR(SUDOKU_BG_COLOR, MARKER_COLOR));
		}
	}
}

//how to redraw without flickering?
void redraw()
{
	draw_filled_rect(0, 0, camera_screen.width, camera_screen.height, SUDOKU_BG_COLOR);
	draw_menu();
	draw_field();
	if (mode==MODE_EDIT)draw_numpad();
}

void gui_sudoku_draw()
{
	//battery and watch?
	if (draw&BG)redraw();
	else
	{
		if (draw&FIELD)draw_field();
		if (draw&MENU)draw_menu();
		if (draw&PAD)draw_numpad();
	}
	draw=0;
}


///////////////////////Sudoku logic/////////////////////////////////////////////

int sudoku_finished(int *pointer)	//Flag, for user and mess
{	//ist das Sudoku voll?
	int i;
	for (i=1; i<=81; i++)
	{
		if (*pointer==0 || one_plus_nums(*pointer))
			return 0;
		pointer++;
	}
	return 1;
}

//checks, that there are no duplicate numbers in row, column and squares
int sudoku_follows_rules(int *pointer)	//for user and mess
{
	int counter, chkflag, x, y, xs, ys, linenum, columnnum;

	//lines
	for (linenum=0; linenum<=8; linenum++)
	{
	for (chkflag=1; chkflag<10; chkflag++)
	{
		counter=0;
		for (x=0; x<=8; x++)
		{
			if (*(pointer+linenum*9+x)&flag[chkflag])
			{
				counter++;
				if (counter>1) return 0;
			}
		}
	}
	}


	//columns
	for (columnnum=0; columnnum<=8; columnnum++)
	{
		for (chkflag=1; chkflag<10; chkflag++)
		{
			counter=0;
			for (y=0; y<=8; y++)
			{
				if (*(pointer+y*9+columnnum)&flag[chkflag])
				{
					counter++;
					if (counter>1) return 0;
				}
			}
		}
	}


	//squares
	for (chkflag=1; chkflag<10; chkflag++)
	{
		//Select the square
		for (ys=0; ys<3; ys++)
		{
			for (xs=0; xs<3; xs++)
			{
				counter=0;
				//Check each number in that square
				for (y=ys*3; y<ys*3+3; y++)
				{
					for (x=xs*3; x<xs*3+3; x++)
					{
						if (*(pointer+y*9+x)&flag[chkflag])
						{
							counter++;
							if (counter>1)return 0;
						}
					}
				}
			}
		}
	}

	//Sudoku has right syntax when it didn't return before
	return 1;
}

//is the sudoku still right if i insert number at x, y?
//works with flags defined in flag[]
int sudoku_follows_rules_xy(int x, int y, int number)	//for field
{
	int yc, xc;
	for (xc=0; xc<9; xc++) if (field[y][xc]&(number)) return 0;
	for (yc=0; yc<9; yc++) if (field[yc][x]&(number)) return 0;

	//printf("xq=%d, yq=%d\n", xq, yq);
	for (yc = y/3 * 3; yc < y/3 * 3 + 3; yc++)
		for (xc = x/3 * 3; xc < x/3 * 3 + 3; xc++)
			if (field[yc][xc]& number) return 0;
	return 1;
}

//missing numbers in lines, columns and squares
//from the return number you can extract the missing numbers with & and flag[x], work in mess[][]
int get_missing_nums_line(int lineNum)	//Flag
{
	int returnnum=0;
	int x;
	for (x=0; x<9; x++)
	{
		if (is_one_num(mess[lineNum][x]))returnnum |= mess[lineNum][x];
	}
	return ~returnnum;
}

int get_missing_nums_column(int columnNumber)	//Flag
{
	int returnnum=0;
	int y;
	for (y=0; y<9; y++)
	{
		if (is_one_num(mess[y][columnNumber]))returnnum |= mess[y][columnNumber];
	}
	return ~returnnum;
}

int get_missing_nums_square(int squareX, int squareY)	//Flag
{
	int returnnum=0;
	int y, x;
	for (y=squareY*3; y<squareY*3+3; y++)
	{
		for (x=squareX*3; x<squareX*3+3; x++)
		{
			if (is_one_num(mess[y][x]))returnnum |= mess[y][x];
		}
	}
	return ~returnnum;
}

//The first solving algorithm:
//The missing numbers in each zone of a cell get AND-ed
//so that only the possible numbers are saved in each cell
//1234, 2345, 3456 -> 34
int sudoku_search_candidates()
{
	int temp, leftnums;
	int x, y, xs, ys;
	int change=0;
	//columns
	for (x=0; x<=8; x++)
	{
		leftnums=get_missing_nums_column(x);
		for (y=0; y<=8; y++)
		{
			if (one_plus_nums(mess[y][x]))
			{
				temp=mess[y][x];
				mess[y][x]&=leftnums;
				if (temp !=mess[y][x])
					change=1;
			}
		}
	}

	//squares
	for(xs=0; xs<3; xs++)for(ys=0; ys<3; ys++)
	{
		leftnums=get_missing_nums_square(xs, ys);
		for(x=xs*3; x<xs*3+3; x++)for (y=ys*3; y<ys*3+3; y++)
		{
			if (one_plus_nums(mess[y][x]))
			{
				temp=mess[y][x];
				mess[y][x]&=leftnums;
				if (temp != mess[y][x])
					change=1;
			}
		}
	}

	//lines
	for (y=0; y<9; y++)
	{
		leftnums=get_missing_nums_line(y);
		for (x=0; x<9; x++)
		{
			if (one_plus_nums(mess[y][x]))
			{
				temp=mess[y][x];
				mess[y][x]&=leftnums;
				if (temp != mess[y][x])
					change=1;
			}
		}
	}
	return change;
}

//Second solving function:
//It detects, if there is only one place where some number can be
//1234, 1234, 12345 -> 5 in the 3rd cell
int sudoku_insert_lonely_numbers()
{
	int x, y, xs, ys, num, count;
	int xtemp=0;
	int ytemp=0;
	int change=0;

	//check squares
	for (ys=0; ys<3; ys++) for (xs=0; xs<3;xs++)for (num=1; num<10; num++)
	{
			count=0;
			for (y=ys*3; y<ys*3+3; y++)	for (x=xs*3; x<xs*3+3; x++)
			{
				if (field[y][x] > 0 || mess[y][x]==0 || is_one_num(mess[y][x]))
					continue;
				else if (mess[y][x] & flag[num])
				{
					if (count == 1)
						goto nextnumS;
					else
					{
						count++;
						xtemp = x;
						ytemp = y;
					}
				}
			}
			if (count==1)
			{
				mess[ytemp][xtemp]=flag[num];
				change=1;
			}
			nextnumS:;
	}

	//check lines
	for (y=0; y<9; y++)for (num=1; num<10; num++)
	{
			count=0;
			for (x=0; x<9; x++)
			{
				if (field[y][x] > 0 || mess[y][x]==0 || is_one_num(mess[y][x]))
					continue;
				else if (mess[y][x] & flag[num])
				{
					if (count == 1)
						goto nextnumL;
					else
					{
						count++;
						xtemp = x;
						ytemp = y;
					}
				}
			}
			if (count==1)
			{
				mess[ytemp][xtemp]=flag[num];
				change=1;
			}
			nextnumL:;
	}

	//check columns
	for (x=0; x<9; x++)for (num=1; num<10; num++)
	{
			count=0;
			for (y=0; y<9; y++)
			{
				if (field[y][x] > 0 || mess[y][x]==0 || is_one_num(mess[y][x]))
					continue;
				else if (mess[y][x] & flag[num])
				{
					if (count == 1)
						goto nextnumC;
					else
					{
						count++;
						xtemp = x;
						ytemp = y;
					}
				}
			}
			if (count==1)
			{
				mess[ytemp][xtemp]=flag[num];
				change=1;
			}
			nextnumC:;
	}

	return change;
}

//Tries to solve the sudoku pointed at. Returns:
//1, if it does its job
//0, if it didn't complete the sudoku
//		This could be because we know not enough to solve it
//		or the algorithm is not intelligent enough to solve the sudoku.
//-1, if the sudoku can't be solved because of errors in the sudoku or in the algorithm ;(
int sudoku_solve(int *pointer)
{
	//copies array from *pointer in mess -> we're solving in mess[][]
	memcpy(mess, pointer, sizeof(mess));
	int change=0;
	int leftnums;
	int x, y;

	//fill empty cells
	for (y=0; y<=8; y++)
	{
		leftnums=get_missing_nums_line(y);
		for (x=0; x<=8; x++)if (mess[y][x]==0)mess[y][x]=leftnums;
	}

	//solve!!
	do
	{
		change=sudoku_search_candidates();
		if (!change)
		{
			if (!sudoku_follows_rules(*mess))return -1;
			else change=sudoku_insert_lonely_numbers();
		}
	}while(change);

	//now the code above has filled in every number it could think about
	if (sudoku_finished(*mess))
	{
		if (sudoku_follows_rules(*mess))
			return 1;
		else return -1;
	}
	else return 0;
}

//-------------------------------------------------------------------
//exchange-functions for sudoku_new(), operate on field[][]
//these exchanges will shuffle the sudoku, but won't influence
//solvability or create conflicts
void exchange_row(int r1, int r2)
{
	int temp, i;
	for (i=0; i<9; i++)
	{
		temp=field[r1][i];
		field[r1][i]=field[r2][i];
		field[r2][i]=temp;
	}
}

void exchange_column(int c1, int c2)
{
	int temp, i;
	for (i=0; i<9; i++)
	{
		temp=field[i][c1];
		field[i][c1]=field[i][c2];
		field[i][c2]=temp;
	}
}

void exchangeSquareRow(int sr1, int sr2)
{
	int i;
	for (i=0; i<3; i++)exchange_row(sr1*3+i, sr2*3+i);
}

void exchange_square_column(int sc1, int sc2)
{
	int i;
	for (i=0; i<3; i++)exchange_column(sc1*3+i, sc2*3+i);
}

//recursive function, tries to remove numbers until START_NUMBERS are reached
//If no solvable sudoku was found, the removed numbers are reinserted.
//count means the count of numbers still in the sudoku
//return value says, if a solvable sudoku was found.
int remove_nums(int count)
{
	int ry, rx;
	int temp;
	int foundone=0;
	while (!foundone)
	{
		ry=rand()%9;
		rx=rand()%9;
		if (field[ry][rx]!=0)
		{
			foundone=1;
			temp=field[ry][rx];
			field[ry][rx]=0;
		}
	}
	if (count>START_NUMBERS)
	{
		if (remove_nums(count-1)==1)return 1;
		else
		{
			field[ry][rx]=temp;
			if (count<=MAX_START_NUMBERS)return sudoku_solve(*field);
			else return -1;
		}
	}
	else if (count<=START_NUMBERS)
	{
		if (sudoku_solve(*field)==1)return 1;
		else
		{
			field[ry][rx]=temp;
			return -1;
		}
	}
	//the program shouldn't come to this point, but my compiler is always angry
	//because there's a missing return value...
	else return -1;
}

int sudoku_new(void)
{
	int foundone=0;
	int x, y, i, j;

	srand((unsigned)time(NULL));
	while (!foundone)
	{
		//reset field[][] to 0 everywhere
		for (x = 0; x < 9; x++) for (y = 0; y < 9; y++) field[y][x] = 0;

		//fill in the first line
		for (x=0; x<9; x++)field[0][x]=flag[x+1];

		//shuffling
		for (i=1; i<=10; i++)
		{
			int rdm1=rand()%9+1;
			int rdm2=rand()%9+1;
			if (rdm1==rdm2)rdm2=(rdm2+1)%9;
			rdm1=flag[rdm1];
			rdm2=flag[rdm2];

			for (j=0; j<9; j++)
			{
				if (field[0][j]==rdm1)field[0][j]=rdm2;
				else if (field[0][j]==rdm2)field[0][j]=rdm1;
			}
		}

		//now, we have to fill the rest of the cells
		//by repeating the pattern just created
		//we start at the second row
		int xnum=2;
		for (y=1; y<9; y++)
		{
			for (x=0; x<9; x++)
			{
				//%9 so it jumps from the end back to the beginning
				xnum=(xnum+1)%9;
				field[y][x]=field[0][xnum];
			}
			if ((y+1)%3==0)xnum=(xnum+4)%9;
			else xnum=(xnum+3)%9;
		}

		//Okay now, the field is filled with numbers.
		//Now shuffle them a bit so that it won't get too easy!
		int rdm1;
		int rdm2;
		int rdm3;
		for (i=1; i<=10; i++)
		{
			rdm1=rand()%3;
			rdm2=rand()%3;
			if (rdm1==rdm2)rdm2=(rdm2+1)%3;
			exchangeSquareRow(rdm1, rdm2);

			rdm1=rand()%3;
			rdm2=rand()%3;
			if (rdm1==rdm2)rdm2=(rdm2+1)%3;
			exchange_square_column(rdm1, rdm2);

			for (j=1; j<=3; j++)
			{
				rdm1=rand()%3;
				rdm2=rand()%3;
				//rdm3 defines in which 3 squares we are shuffling
				rdm3=rand()%3;
				if (rdm1==rdm2)rdm2=(rdm2+1)%3;
				exchange_row(rdm3*3+rdm1, rdm3*3+rdm2);

				rdm1=rand()%3;
				rdm2=rand()%3;
				rdm3=rand()%3;
				if (rdm1==rdm2)rdm2=(rdm2+1)%3;
				exchange_column(rdm3*3+rdm1, rdm3*3+rdm2);
			}
		}

		//a lot of times, we are not able to find the right numbers to remove,
		//then we just generate a new fully filled sudoku
		//74 tries to remove numbers before going to the next sudoku results in the best speed.
		for (i=1; i<=74; i++)
		{
			if (remove_nums(9*9)==1) {
				foundone=1;
				break;
			}
		}

	//end while(!foundone)
	}
	return 1;
}


///////////////////////////High level functions//////////////////////////////////

//Chooses, which action to execute in the menu
void sudoku_menu_execute()
{
	int y, x;
	switch (menuPos)
	{
		case 0:	//check Sudoku
			if (sudoku_follows_rules(&user[0][0]))	gui_mbox_init((int)"Tada!", (int)"0 mistakes!", MBOX_TEXT_CENTER, NULL);
			else gui_mbox_init((int)"Info", (int)"A number occurs twice", MBOX_TEXT_CENTER, NULL);
			break;
		case 1:	//solve Sudoku
			switch (sudoku_solve(&user[0][0]))
			{
				case 1:
					gui_mbox_init((int)"Info", (int)"Solved", MBOX_TEXT_CENTER, NULL);
					memcpy(user, mess, sizeof(user));	//copies mess[][] in user[][]
					break;
				case 0:
					gui_mbox_init((int)"Info", (int)"Not complete", MBOX_TEXT_CENTER, NULL);
					//copy only known numbers
					for (y=0; y<9; y++)	for (x=0; x<9; x++)	if (is_one_num(mess[y][x]))user[y][x]=mess[y][x];
					break;
				case -1:
					gui_mbox_init((int)"Info", (int)"Not solvable", MBOX_TEXT_CENTER, NULL);
					for (y=0; y<9; y++)	for (x=0; x<9; x++)	if (is_one_num(mess[y][x]))user[y][x]=mess[y][x];
					break;
			}
			break;
		case 2:	//new sudoku
			//sprintf(str, "%i tries", sudoku_new());
			//gui_mbox_init((int)"Info", (int)str, MBOX_TEXT_CENTER, NULL);
			sudoku_new();
			memcpy(user, field, sizeof(user));	//field in user kopieren
			break;
		case 3:	//own sudoku
			for (x = 0; x < 9; x++)for (y = 0; y < 9; y++)
			{
				field[y][x] = 0;
				user[y][x]=0;
			}
			break;
		case 4:	//Info
			gui_mbox_init((int)"Info", (int)("(c)Frank, 2012, V 0.5"), MBOX_TEXT_CENTER, NULL);
			break;
        case 5:
            exit_sudoku(0); //exit without save
            break;
        case 6:
            exit_sudoku(1); //save and exit
            break;
        case 7:
            if (stat("A/CHDK/GAMES/SUDOKU.SAV", 0)==0) {
                remove("A/CHDK/GAMES/SUDOKU.SAV");
            }
            break;
	}
	mode=MODE_VIEW;
}
//-------------------------------------------------------------------
//Which keys do what?
int gui_sudoku_kbd_process()
{
	int key=kbd_get_autoclicked_key();

	switch (key) {
		//Keys that are always the same
		case KEY_ZOOM_IN:
			if (mode==MODE_VIEW)mode=MODE_MENU;
			else mode=MODE_VIEW;
			draw|=FIELD|MENU;
			break;
		case KEY_ZOOM_OUT:
			mode=MODE_VIEW;
			draw|=FIELD|MENU;
			break;
		case KEY_ERASE:
		case KEY_SHOOT_HALF:
			if (mode & (MODE_VIEW | MODE_EDIT))
			{
				if (field[yPos][xPos]==0)user[yPos][xPos]=0;
				if (mode==MODE_EDIT)
				{
					mode=MODE_VIEW;
					del_numpad();
					xPosPad=1;
					yPosPad=1;
				}
				draw|=FIELD;
			}
			break;

		case KEY_DISPLAY:
			if (sudoku_follows_rules(*user) & sudoku_finished(*user)) gui_mbox_init((int)"Congratulations!", (int)"You did it!", MBOX_TEXT_CENTER, NULL);
			else if (sudoku_follows_rules(*user)) gui_mbox_init((int)"Info", (int)"Couldn't find a mistake", MBOX_TEXT_CENTER, NULL);
			else gui_mbox_init((int)"Info", (int)"There's something wrong here...", MBOX_TEXT_CENTER, NULL);
			draw|=BG;
			break;
	}
	switch (mode)
	{
		case MODE_VIEW:
			if (key & (KEY_UP | KEY_DOWN))
			{
				yPosOld=yPos;
				if (key==KEY_UP)yPos--;
				if (key==KEY_DOWN)yPos++;
				yPos=(yPos+9)%9;	//so that we don't get beyond the borders
				draw|=FIELD;
			}
			if (key & (KEY_LEFT | KEY_RIGHT))
			{
				xPosOld=xPos;
				if (key==KEY_LEFT)xPos--;
				if (key==KEY_RIGHT)xPos++;
				xPos=(xPos+9)%9;	//so that we don't get beyond the borders
				draw|=FIELD;
			}
			if (key==KEY_SET && field[yPos][xPos]==0)
			{
				mode=MODE_EDIT;
				if (user[yPos][xPos]==0)user[yPos][xPos]=get_pad_num();
				else set_pad_num(get_dec_num(user[yPos][xPos]));
				draw|=PAD|FIELD;
			}
		break;

		case MODE_EDIT:
			if (key &(KEY_LEFT | KEY_RIGHT) && yPosPad>=0)
			{
				if (key==KEY_LEFT)xPosPad--;
				if (key==KEY_RIGHT)xPosPad++;
				xPosPad=(xPosPad+3)%3;
				user[yPos][xPos]=get_pad_num();
				draw|=FIELD|PAD;
			}
			if (key &(KEY_UP | KEY_DOWN))
			{
				if (key==KEY_UP)yPosPad--;
				if (key==KEY_DOWN)yPosPad++;
				if (xPosPad==1)yPosPad=((yPosPad+5)%4)-1;
				else yPosPad=(yPosPad+3)%3;
				user[yPos][xPos]=get_pad_num();
				draw|=FIELD|PAD;
			}
			if (key==KEY_SET)
			{
				mode=MODE_VIEW;
				draw=FIELD;
				del_numpad();
				xPosPad=1;
				yPosPad=1;
				if (sudoku_finished(&user[0][0])){
					if (sudoku_follows_rules(&user[0][0]))
						gui_mbox_init((int)"Congratulations!", (int)"Everything's correct!", MBOX_TEXT_CENTER, NULL);
					else
						gui_mbox_init((int)"Info", (int)"There's something wrong here...", MBOX_TEXT_CENTER, NULL);
					draw|=BG;
				}
			}
		break;

		case MODE_MENU:  //Keys in Menumode
			key |= get_jogdial_direction();
			if (key & (KEY_UP | KEY_DOWN | JOGDIAL_LEFT | JOGDIAL_RIGHT))
			{
				if (key==KEY_UP || key==JOGDIAL_LEFT)menuPos--;
				if (key==KEY_DOWN || key==JOGDIAL_RIGHT)menuPos++;
				menuPos=(menuPos+MENU_ELEMENTS)%MENU_ELEMENTS;
				draw|=MENU;
			}
			switch (key) {
				case KEY_SET:
					sudoku_menu_execute();
					draw|=BG;
					break;
				case KEY_LEFT:
				case KEY_RIGHT:
					mode=MODE_VIEW;
					draw|=FIELD|MENU;
					break;
			}
		break;
	}
    return 0;
}
//-------------------------------------------------------------------

int gui_sudoku_init()
{
	int x, y;
	xFieldBorder=12;
	yFieldBorder=12;
	xPos=4;
	yPos=4;
	fieldLineDistance=(camera_screen.height-yFieldBorder*2)/9;
	fieldLineLength=fieldLineDistance*9;
	mode=MODE_VIEW;
	menuPos=0;
	padLineDistance=fieldLineDistance;
	//xPadStart=camera_screen.width*2/3+10;
	//xPadStart=camera_screen.width/2+10;
	xPadStart=xFieldBorder*3+fieldLineLength;
	yPadStart=xFieldBorder+padLineDistance*6;
	xPosPad=1;
	yPosPad=1;
	for (x = 0; x < 9; x++) for (y = 0; y < 9; y++)
	{
		field[y][x] = 0;
		user[y][x]=0;
	}
	draw|=BG;
	gui_sudoku_draw(0);

    char *buf = load_file("A/CHDK/GAMES/SUDOKU.SAV", 0, 0);
	if (buf) { //load last sudoku
        memcpy(user, buf, sizeof(user));
        memcpy(field, buf+sizeof(user), sizeof(field));
        free(buf);
	} else {
        sudoku_new();
        memcpy(user, field, sizeof(user));	//copies field[][] in user[][]
	}
	gui_mbox_init((int)"Congratulations!", (int)"Everything's correct!", MBOX_TEXT_CENTER, NULL);
	draw|=FIELD;
	gui_sudoku_draw(0);
	gui_set_mode(&GUI_MODE_SUDOKU);
	return 1;
}

void gui_module_menu_kbd_process()
{
	if (mode==MODE_VIEW)mode=MODE_MENU;
    else mode=MODE_VIEW;
    draw|=FIELD|MENU;
}

void exit_sudoku(int save)
{
    if (save!=0)
    {
        save = open("A/CHDK/GAMES/SUDOKU.SAV", O_WRONLY|O_CREAT|O_TRUNC, 0777);
        write(save, user, sizeof(user));
        write(save, field, sizeof(field));
        close(save);
    }
    running = 0;
    gui_default_kbd_process_menu_btn();
}

// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

int _run()
{
    if (!camera_info.state.mode_play)
    {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE, MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, 0);
    }
    else
    {
        running = 1;
        gui_sudoku_init();
    }

    return 0;
}

int _module_can_unload()
{
    return running == 0;
}

int _module_exit_alt()
{
    running = 0;
    return 0;
}

/*************** END OF AUXILARY PART *******************/

/******************** Module Information structure ******************/

libsimple_sym _librun =
{
    {
         0, 0, _module_can_unload, _module_exit_alt, _run
    }
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    SIMPLE_MODULE_VERSION,		// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"Sudoku",			// Module name
    (int32_t) "Game",

    &_librun.base,

    ANY_VERSION,                // CONF version
    CAM_SCREEN_VERSION,         // CAM SCREEN version
    ANY_VERSION,                // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};
