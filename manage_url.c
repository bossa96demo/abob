void set_url(char *str) { /* we set url for later use */
	strcpy(websites[++cur], str); 	/* add to array the name of site */
	wmax = wmax > cur ? wmax : cur;	/* changing wmax if needed */
}
/*
 * if we change	"strcpy(websites[++cur], str);" 
 * for "cur++; strcpy(websites[cur], str);"
 * it won't work
 * i don't know why
 */


char *get_url(void) { 	/* simply return url */
	if(cur < 0) return NULL; 	/* if no url-s yet, prevent errors */
	return websites[cur];		/* else return url */
}
