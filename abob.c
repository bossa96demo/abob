#include <ncurses.h>
#include <string.h>

void wcenter(WINDOW *win, int row, char *title);
void open_start();
void open_prompt();

WINDOW *start, *prompt;

int main(){
	int ch;
	int height, width, y;
	initscr();

	refresh();
	
	open_start();
	
	getmaxyx(start, height, width);
	y = height >> 1;
	wcenter(stdscr, y, "ABOB");
	
	refresh();
	noecho();

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	do{
		ch = getch();
		refresh();
		if(ch == ':') open_prompt();

	}while(true);


	//char cmd[256];

	//mvaddstr(height-1, 0, "Command: ");
	//getnstr(cmd, 255);
	
	//clear();


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
	wcenter(start, y-1, "version 0.0.0.4");
	wcenter(start, y,   "type :o<enter> to open a website\n");

        touchwin(start);

	wrefresh(start);
	getch();
        touchwin(stdscr);
	refresh();

}
void open_prompt(){
	int height, width, y;
	getmaxyx(stdscr, height, width);

	if((prompt = newwin(1, 0, height - 1, 0)) == NULL){
		addstr("Error while allocating memory");
		endwin();
		return;
	}

	wbkgd(prompt, COLOR_PAIR(1));

	waddstr(prompt, ":");

        touchwin(prompt);

	wrefresh(prompt);
	getch();
        touchwin(stdscr);
	refresh();

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
