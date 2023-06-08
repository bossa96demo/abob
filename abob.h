/*
 * File with all includes, functions and variables
 */

/* INCLUDES */ 

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


/* FUNCTIONS */

void open_start(void);				/* open start page */
void open_prompt(void);				/* open prompt */
void open_website(char *site);			/* open website based on its name */
void open_insert(void);				/* open insert mode */
void open_tabs(void);				/* display current tabs */

char *get_thing_after_space(char *text);	/* get string that goes after space */
bool check_win(WINDOW *win);			/* check for errors in given window */
void wcenter(WINDOW *win, int row, char *title);/* center text in given window */ 
void scroll_tabs(void);				/* scroll tab */
void upd_tab_bar(void);				/* update tab bar */

void set_url(char *str);			/* set url to given string */
char *get_url();				/* get url */

/* VARIABLES */

/* I need to redo this later, because overflow and else */
#define MAX_WEBSITES 42
char websites[MAX_WEBSITES][100];		/* array of websites url-s */
int cur = -1;					/* current website */
int wmax = -1; 					/* max amount of websites */

/* create start, prompt, array of websites, insert and tab_bar windows */
WINDOW *start, *prompt, *web_wins[MAX_WEBSITES], *ins, *t_bar;		
