void display_start_page(){
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
