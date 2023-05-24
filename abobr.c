#include <ncurses.h>
#include <string.h>

void wcenter(WINDOW *win, int row, char *title);
void open_start();

WINDOW *start, *prompt, *help;

int main(){
	int ch;
	initscr();

	refresh();
	
	open_start();
	/* addstr("welcome\n");
	refresh();
	noecho();
	do{
		ch=getch();
		refresh();
		if(ch == '+') open_start();
		else addch(ch);
	} while(ch != '~');
	*/
	//char cmd[256];
	//while(getch() != '~'){}

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
	//printw("%d cols, %d rows", height, width);

	wcenter(start, y-4, "Welcome to abobr\n");
	wcenter(start, y-3, "ABOBR - A Better Open BRowser\n");
	wcenter(start, y-2, "\n");
	wcenter(start, y-1, "version 0.0.0.3\n");
	wcenter(start, y,   "type :o<enter> to open a website\n");

        touchwin(start);

	wrefresh(start);
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
