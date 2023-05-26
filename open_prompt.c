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
	{ curs_set(0); noecho(); return; } /* turn off prompt if there are 0 commands */

	char *content = get_thing_after_space(all);	// get what goes after command
	char *cmd = strtok(all, " ");			// get command that user inputed
	
	//addstr(cmd);
	//addstr(content);

	if(strcmp(cmd, "o") == 0 && content[0] != '\0'){// open website on command 'o'
		open_website(content);
	}else if(strcmp(cmd, "q") == 0){		// on q we quit the programm
		exit(0);
	}else if(strcmp(cmd, "help") == 0){		// display start page on help
		display_start_page();
	}else{
		wclear(prompt);
		waddstr(prompt, "command not found");
		wrefresh(prompt);
	}

	curs_set(0);	// turning off cursor
	noecho();	// turn off echo 
}