#include "sort.h"

void swap_original(char **p, char **q){
	char *tmp;

	tmp = *p;
	*p = *q;
	*q = tmp;
}


void swap(char **p, char **q){
	char *tmp;
	tmp = *p;
	realloc(*p,strlen(*q));
	*p = *q;
	realloc(*q,strlen(tmp));
	*q = tmp;
}



