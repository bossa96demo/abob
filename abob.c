/*
 * Main script
 */

#include "abob.h"			/* move declarations to another file */

/* include other files */
#include "request.c"			/* requesting html and validating urls */
#include "html.c"			/* only max is able to understand this */
#include "manage_url.c"			/* tools to work with current url */
#include "start_page.c"			/* basic welcome page */
#include "prompt_mode.c"		/* working with prompt */

int main(){
	int ch;
	initscr();
	noecho(); 		/* turning off echoing input */
	curs_set(0);		/* turning off cursor */
	refresh();		/* refresh to see changes */
	open_start();		/* opening welcome page	*/


	do{					/* processing input */
		ch = getch();

		switch(ch){
			case ':': 		/* enter prompt mode*/
				open_prompt();
				break;
			case 'y':		/* yank current url */
				clear();
				printw("Your clipboard is %s", get_url());
				refresh();
				break;
			case 'i':		/* enter insert mode */
				open_insert();
				break;
			case 't':		/* delete? */
				open_tabs();
				break;
			case 9: /* tab key */	/* scroll tabs */
				scroll_tabs();
				open_tabs();
				wcenter(stdscr, 5, websites[cur]);
				break;
			default:
				break;
		}
		upd_tab_bar(); /* after each action update/add tabs */
	}while(true);

	endwin();				/* nothing will go here */
	return 0;
}

void open_insert(){
	ins = newwin(0, 0, 0, 0);
	if (check_win(ins)) return;
	
	curs_set(1);	/* turning cursor on while in insert mode */
	wrefresh(ins);
	for (;;) {
	    int ch = getch();
	    waddch(ins, ch);
	    switch(ch){
		case 27:/* escape button */
		    clear(); refresh(); 
		    curs_set(0);return; /* exit insert mode */
		default:
		    break;
	     }
	     wrefresh(ins);
	}
	clear();
       	refresh();
	curs_set(0);
}

/* some web stuff, added by max */
void tag_callback(char *tagname){
	printf("%s", tagname); 
}


void render_website(char *url){
	wprintw(web_wins[cur], "rendering %s", url);
	char *html = request(url);
	parse(html, *tag_callback);
}

void open_website(char *site){
	web_wins[cur] = newwin(0, 0, 1, 0); /* everything but first line of screen */
	if (check_win(web_wins[cur])) return;

	int validity = validate_url(site);
	if (validity){
		wprintw(web_wins[cur], "Opening %s...", site);
		wrefresh(web_wins[cur]);
		render_website(site);
		set_url(site);
	} else {
		wclear(web_wins[cur]);
		wprintw(web_wins[cur], "Error: Url %s is not valid!", site);
		wrefresh(web_wins[cur]);
	}
}
/* end of web stuff */

void open_tabs(){
	t_bar = newwin(1, 0, 0, 0); 		/* first line of screen */
	if (check_win(t_bar)) return;
	wclear(t_bar);

	int i = -1;
	for (i = 0; i <= wmax; i++){ 		/* for every website url */
	    wprintw(t_bar, "| ");
	    if (i == cur) {
		wattron(t_bar, A_STANDOUT);	 /* highlight current website */ 
		wprintw(t_bar, "%s", websites[i]); /* print its name */
		wattroff(t_bar, A_STANDOUT);
		waddch(t_bar, ' ');
	    } else {
		wprintw(t_bar, "%s", websites[i]);
		waddch(t_bar, ' ');
	    }
	}
	i == 0 ? : waddstr(t_bar, "|");
	/* if no websites opened, do not print closing '|' */
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
	char* space_ptr = strstr(text, " "); 	/* set pointer for first space */
	if(space_ptr == NULL) return ""; 	/* if nothing after space, exit */
	space_ptr++;				/* do not include space */
	return space_ptr;			/* finally return */
}
bool check_win(WINDOW *win){
	if(win == NULL){
	    addstr("Error while allocating memory for window");
	    endwin();
	    return true;
	} else {
	    return false;
	}
}

void upd_tab_bar(){
	open_tabs();
	touchwin(t_bar);
	wrefresh(t_bar);
}

void scroll_tabs(void){
	/* 
	 * simple loop:
	 * if it hasn't reached it limits, add 1
	 * else go to the beginning 
	 */
	if(cur < wmax){
	    cur++;
	} else {
	    cur = 0;
	}
}
