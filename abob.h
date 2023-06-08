#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void wcenter(WINDOW *win, int row, char *title);// to center text in given window 
void open_start();				// to open start window
void open_prompt();				// to open prompt
void open_website();				// to open website
char *get_thing_after_space(char *text);	// you give string, you get thing after space
void set_url(char *str);			// set url to given string
char *get_url();				// get url
void open_insert(void);
void manage_tabs(void);
void check_win(WINDOW *win);


#define MAX_WEBSITES 42
char websites[MAX_WEBSITES][100];		// array of websites
int cur = -1, wmax = -1;

WINDOW *start, *prompt, *web_wins[MAX_WEBSITES], *ins, *t_bar;		
/* create start, prompt, array of websites, insert and tab_bar windows */
char *url;
