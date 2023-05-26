void set_url(char *str) { // we set url for later use, such as copying and saving it
	if (url != NULL) {			//if url is occupied, delete it
		free(url);
	}
	url = (char *)malloc(strlen(str) + 1);	// allocate space for url
	strcpy(url, str);			// copy given string in url
}

char *get_url() { 	//simply return url
	return url;
}
