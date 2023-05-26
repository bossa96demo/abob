#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "abob.h"				// move garbage to another file
#include "request.c"				// requesting html and validating urls
#include "html.c"				// only max is able to understand this
#include "manage_url.c"				// tools to work with current url
#include "start_page.c"				// basic welcome page
#include "prompt_mode.c"			// working with prompt

int main(){
	int ch;
	initscr();
	noecho(); 				// turning off echoing input
	curs_set(0);				// turning off cursor
	refresh();
	display_start_page();			// opening welcome page

	do{					/* processing input */
		ch = getch();
		touchwin(stdscr);
		refresh();
		if(ch == ':') open_prompt();	/* if user enters command mode */
		else if(ch == 'y'){		/* if user yanks we copy the url*/
			clear();
			printw("Your clipboard is %s", get_url());
			refresh();
		}
		else{				
			clear();
			addstr("ABOB");
			refresh();
		}
	}while(true);

	endwin();				/* nothing will go here */
	return 0;
}

void tag_callback(char *tagname){
	printf("%s", tagname); 
}

void render_website(char *url){
	printf("rendering %s", url);
	char *html = request(url);
	parse(html, *tag_callback);
}

void open_website(char *site){
	noecho();
	clear();
	set_url(site);
	if((website = newwin(0, 0, 0, 0)) == NULL){
		addstr("Error while allocating memory");
		endwin();
		return;
	}

	refresh();
	int validity = validate_url(site);
	if (validity){
		wprintw(website, "Opening %s...", site);
		wrefresh(website);
		render_website(site);
	}
	else{
		wprintw(website, "Error: Url %s is not valid!", site);
	}

	touchwin(website);
	wrefresh(website);
}


void wcenter(WINDOW *win, int row, char *title){
	int len, indent, y, width;		
       	getmaxyx(win, y, width);		// getting max x and y of given window

	len = strlen(title);			// getting length on the given string
	indent = width - len;			/* counting how much space */
	indent /= 2;				/* will we need to retreat */
	mvwaddstr(win, row, indent, title);	// finally print message
	wrefresh(win);				// and refresh given window
}


char *get_thing_after_space(char *text){
	char* space_ptr = strstr(text, " ");
	if(space_ptr == NULL) return "";
	char* after_space_ptr = space_ptr + 1;
	int remaining_len = strlen(after_space_ptr);
	char* substr = malloc((remaining_len + 1) * sizeof(char));
	strcpy(substr, after_space_ptr);
	return substr;
	free(substr);
}
