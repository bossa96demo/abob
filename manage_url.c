void set_url(char *str) { /* we set url for later use */
	//if (url != NULL) {			/* if url is occupied, delete it */
	//	free(url);
	//}
	//url = (char *)malloc(strlen(str) + 1);	/* allocate space for url   */
	//strcpy(url, str);			/* copy given string in url */
	strcpy(websites[++cur], str);
	wmax = wmax > cur ? wmax : cur;
}

char *get_url() { 	/* simply return url */
	if(cur < 0) return NULL;
	return websites[cur];
}
