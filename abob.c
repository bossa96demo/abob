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
		
		/* tab bar */
		manage_tabs();
		touchwin(t_bar);
		wrefresh(t_bar);
		
		switch(ch){
			case ':':
				open_prompt();
				break;
			case 'y':
				clear();
				printw("Your clipboard is %s", get_url());
				refresh();
				break;
			case 'i':
				open_insert();
				break;
			case 't':
				manage_tabs();
				break;
			case 9: /* tab key */
				clear();
				addstr("ABOB");
				refresh();
			default:
				break;
		}
	}while(true);

	endwin();				/* nothing will go here */
	return 0;
}

void open_insert(){
	int ch, height, width;
	getmaxyx(stdscr, height, width);
	ins = newwin(0, 0, 0, 0);
	if(ins == NULL){
		addstr("Error while allocating memory");
		endwin();
		return;
	}
	curs_set(1);
	wrefresh(ins);
	for (;;) {
		ch = getch();
		waddch(ins, ch);
		switch(ch){
			case 27: // escape button
				clear(); refresh(); 
				return; break;
			default:
				break;
		}
		wrefresh(ins);
	}
	clear();
       	refresh();
	curs_set(0);
}

void tag_callback(char *tagname){
	printf("%s", tagname); 
}

void render_website(char *url){
	wprintw(web_wins[cur], "rendering %s", url);
	char *html = request(url);
	parse(html, *tag_callback);
}

void open_website(char *site){
	noecho();
	wclear(web_wins[cur]);

	web_wins[cur] = newwin(0, 0, 1, 0); /* everything but first line of screen */
	check_win(web_wins[cur]);
	refresh();
	int validity = validate_url(site);
	if (validity){
		wprintw(web_wins[cur], "Opening %s...", site);
		wrefresh(web_wins[cur]);
		render_website(site);
		set_url(site);
	}else{
		wprintw(web_wins[cur], "Error: Url %s is not valid!", site);
		wrefresh(web_wins[cur]);
	}

}

void manage_tabs(){
	t_bar = newwin(1, 0, 0, 0); /* first line of screen */
	check_win(t_bar);
	int i;
	for (i = 0; i <= cur; i++){
	    wprintw(t_bar, "| %s ", websites[i]);
	}
	i == 0 ? : waddch(t_bar, '|'); /* if no websites opened, do not print | */
	wrefresh(t_bar);
} 

void wcenter(WINDOW *win, int row, char *title){
	int len, indent, y, width;		
       	getmaxyx(win, y, width);		/* get coords of window */

	len = strlen(title);			/* getting len of the given string */
	indent = width - len;			/* counting how much space  */
	indent /= 2;				/* will we need to retreat  */
	mvwaddstr(win, row, indent, title);	/* finally print message    */
	wrefresh(win);				/* and refresh given window */
}


char *get_thing_after_space(char *text) {
	char* space_ptr = strstr(text, " "); 	/* if it works, it works */ 
	if(space_ptr == NULL) return ""; 	/* no matter at what cost */
	char* after_space_ptr = space_ptr + 1;
	int remaining_len = strlen(after_space_ptr);
	char* substr = malloc((remaining_len + 1) * sizeof(char));
	strcpy(substr, after_space_ptr);
	return substr;
	free(substr);
}
void check_win(WINDOW *win){
	if(win == NULL){
	    addstr("Error while allocating memory for window");
	    endwin();
	    return;
	}	
}
