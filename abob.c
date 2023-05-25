#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "abob.h"

char *get_thing_after_space(char *text);

int main(){
	int ch;
	initscr();
	noecho(); 	// turning off echoing input
	curs_set(0);
	refresh();
	open_start();	// opening welcome page

	do{					/* processing input */
		ch = getch();
		touchwin(stdscr);
		refresh();
		if(ch == ':') open_prompt();	/* if user enters command mode */
		else if(ch == 'y'){		/* if user yanks we copy the url*/
			clear();
			printw("Your clipboard is %s", get_url());
			refresh();
		}else{				/* else printing abob */
			clear();
			addstr("ABOB");
			refresh();
		}
	}while(true);

	endwin();				/* nothing will go here */
	return 0;
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
        wprintw(website, "You have opened %s", site);

	touchwin(website);
	wrefresh(website);
}
void open_start(){
	int height, width, y;

	if((start = newwin(0,0,0,0)) == NULL){
		addstr("Error while allocating memory");
		endwin();
		return;
	}


	getmaxyx(start, height, width);
	y = height >> 1;

	wcenter(start, y-2, "Welcome to abob");
	wcenter(start, y-1, "ABOB - Another Buggy, Open Browser");
	wcenter(start, y-0, "");
	wcenter(start, y+1, "version 0.0.0.5");
	wcenter(start, y+2, "type :o<enter> to open a website\n");

        touchwin(start);
	wrefresh(start);
}
void open_prompt(){
	int height, width;
	getmaxyx(stdscr, height, width);

	if((prompt = newwin(1, 0, height - 1, 0)) == NULL){
		addstr("Error while allocating memory");
		endwin();
		return;
	}
	curs_set(1);	// turning cursor on while in prompt mode

	waddstr(prompt, ":");

        touchwin(prompt);
	wrefresh(prompt);
	
	echo();		// add echo so user will be able to see his commands
	char all[256];
	wgetnstr(prompt, all, 256); // input commands from user
	

	// if user doesn't enter anything programm will crash
	if(strlen(all) == 0) 
	{ curs_set(0); noecho(); return; } /* check if so, emergency exit */

	char *content = get_thing_after_space(all);	// get what goes after command
	char *cmd = strtok(all, " ");			// get command that user inputed
	
	//addstr(cmd);
	//addstr(content);

	if(strcmp(cmd, "o") == 0 && content[0] != '\0'){// open website on command 'o'
		open_website(content);
	}else if(strcmp(cmd, "q") == 0){		// on q we quit the programm
		exit(0);
	}else if(strcmp(cmd, "help") == 0){		// display start page on help
		open_start();
	}else{
		wclear(prompt);
		waddstr(prompt, "command not found");
		wrefresh(prompt);
	}

	curs_set(0);	// turning off cursor
	noecho();	// turn off echo 
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

void set_url(char *str) { // we set url for later use, such as copying and saving it
	if (url != NULL) {			//if url is occupied, delete it
		free(url);
	}
	url = (char *)malloc(strlen(str) + 1);	// allocate space for url
	strcpy(url, str);			// copy given string in url
}

char *get_url() { //simply return url
	return url;
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
