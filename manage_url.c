void set_url(char *str) { /* we set url for later use */
	if (url != NULL) {			/* if url is occupied, delete it */
		free(url);
	}
	url = (char *)malloc(strlen(str) + 1);	/* allocate space for url   */
	strcpy(url, str);			/* copy given string in url */
	strcpy(websites[cur_web], str);
	cur_web++;
}

char *get_url() { 	//simply return url
	return url;
}
