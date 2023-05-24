#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void wcenter(WINDOW *win, int row, char *title);
void open_start();
void open_prompt();
void open_website();
void set_local_clipboard(char *str);
char *get_local_clipboard();


WINDOW *start, *prompt, *website;
char *url;
char *local_clipboard;

int main(){
	int ch;
	int height, width, y;
	initscr();
	noecho();

	refresh();
	
	open_start();
	
	getmaxyx(start, height, width);
	y = height >> 1;
	wcenter(stdscr, y, "ABOB");
	
	refresh();

	do{
		ch = getch();
		refresh();
		if(ch == ':') open_prompt();
		else if(ch == 'y'){
			clear();
			printw("Your clipboard is %s", get_local_clipboard());
			refresh();
		}	

	}while(true);

	
	refresh();
	getch();
	endwin();
	return 0;
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

	wcenter(start, y-4, "Welcome to abob");
	wcenter(start, y-3, "ABOB - Another Buggy, Open Browser");
	wcenter(start, y-2, "");
	wcenter(start, y-1, "version 0.0.0.5");
	wcenter(start, y,   "type :o<enter> to open a website\n");

        touchwin(start);
	wrefresh(start);
	getch();
        touchwin(stdscr);
	refresh();

}
void open_prompt(){
	int height, width;
	getmaxyx(stdscr, height, width);

	if((prompt = newwin(1, 0, height - 1, 0)) == NULL){
		addstr("Error while allocating memory");
		endwin();
		return;
	}

	waddstr(prompt, ":");

        touchwin(prompt);
	wrefresh(prompt);
	
	echo();
	char all[256];
	wgetnstr(prompt, all, 256);
	char *content = strchr(all, ' ') + 1;
	char *cmd = strtok(all, " ");
	if(strcmp(cmd, "o") == 0){
		clear();
		printw("You have opened %s", content);
		url = content;
		set_local_clipboard(url);
		refresh();
	}else if(strcmp(cmd, "q") == 0){
		exit(0);
	}else if(strcmp(cmd, "y") == 0){
			}
	touchwin(stdscr);

	refresh();
	noecho();
}
void wcenter(WINDOW *win, int row, char *title){
	int len, indent, y, width;
       	getmaxyx(win, y, width);

	len = strlen(title);
	indent = width - len;
	indent /= 2;
	mvwaddstr(win, row, indent, title);
	wrefresh(win);
}



void set_local_clipboard(char *str) {
	if (local_clipboard != NULL) {
		free(local_clipboard);
	}
	local_clipboard = (char *)malloc(strlen(str) + 1);
	strcpy(local_clipboard, str);
}

char *get_local_clipboard() {
	return local_clipboard;
}


