#include <ncurses.h>
#include <string.h>

void center(int row, char *title);

int main(){
	initscr();
	int height, width;
	getmaxyx(stdscr, height, width);
	int y = height >> 1;
	center(y-3, "welcome to abobr\n");
	center(y-2, "version 0.0.0.1\n");
	center(y-1, "press :o<enter> to open a website\n");
	center(y, "ABOB");

	refresh();
	getch();
	endwin();
	return 0;
}

void center(int row, char *title){
	int len, indent, y, width;
       	getmaxyx(stdscr, y, width);

	len = strlen(title);
	indent = width - len;
	indent /= 2;
	mvaddstr(row, indent, title);
	refresh();
}
