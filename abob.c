#include <ncurses.h>
#include <string.h>

void wcenter(WINDOW *win, int row, char *title);
void open_start();
void open_prompt();
void open_website();

WINDOW *start, *prompt, *website;


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
	wcenter(start, y-1, "version 0.0.0.4");
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
	//wscanw(prompt, "%s", cmd);
	//char content[256];
	//wscanw(prompt, "d%s", content);
	//content = strtok(str, " ");
	//addstr(cmd);
	//addstr(content);
	char *content = strchr(all, ' ') + 1;
	char *cmd = strtok(all, " ");
	//addstr(cmd);
	//addstr("\n");
	//addstr(content);

	if(strcmp(cmd, "o") == 0){
		clear();
		printw("You have opened %s", content);
		refresh();
	}else{
		addch(cmd[1]);
	}
	/*
	if(after == ""){
		addch('w');
	}else{
		addch('t');
	}
	*/
	/*
	switch (before) {
		case "o":
			touchwin(stdscr);	
			refresh();
			break;
		default:
			break;
	}
	*/
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
