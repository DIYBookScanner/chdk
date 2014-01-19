#ifndef FONT_H
#define FONT_H

// CHDK Font interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------
#define FONT_CP_WIN     0
#define FONT_CP_DOS     1

#define  FONT_CP_WIN_1250       0
#define  FONT_CP_WIN_1251       1
#define  FONT_CP_WIN_1252       2
#define  FONT_CP_WIN_1254       3
#define  FONT_CP_WIN_1257       4
/* 1253 (Greek) */
#define  FONT_CP_WIN_1253       5

//-------------------------------------------------------------------
// Format of header block for each character in the 'font_data' array
// This is immediately followed by 'size' bytes of character data.
typedef struct {
	unsigned char charcode[2];      // Don't change this to a short as the data is not aligned in memory
	unsigned char offset;
	unsigned char size;
} FontData;

//-------------------------------------------------------------------
extern void font_init();
extern void font_set(int codepage);
extern unsigned char *get_current_font_data(char ch);

extern int rbf_load_symbol(char *file);
extern void rbf_load_from_file(char *file, int codepage);
extern int rbf_font_height();
extern int rbf_symbol_height();
extern int rbf_char_width(int ch);
extern int rbf_symbol_width(int ch);
extern int rbf_str_width(const char *str);
extern void rbf_set_codepage(int codepage);
extern int rbf_draw_char(int x, int y, int ch, color cl);
extern int rbf_draw_symbol(int x, int y, int ch, color cl);
extern int rbf_draw_string(int x, int y, const char *str, color cl);
extern int rbf_draw_clipped_string(int x, int y, const char *str, color cl, int l, int maxlen);
extern int rbf_draw_string_len(int x, int y, int len, const char *str, color cl);
extern int rbf_draw_string_right_len(int x, int y, int len, const char *str, color cl);
extern int rbf_draw_menu_header(int x, int y, int len, char symbol, const char *str, color cl);
extern void rbf_enable_cursor(int s, int e);
extern void rbf_disable_cursor();

//-------------------------------------------------------------------
#endif

