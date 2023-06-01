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


WINDOW *start, *prompt, *website, *ins;		// create start, prompt and website windows
char *url;
