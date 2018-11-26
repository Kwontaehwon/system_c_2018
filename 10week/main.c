#include "sort.h"

int main(void){
	char word[MAXWORD];
	char *w[N];
	int n;
	int i;

	for (i=0; scanf("%s", word) == 1; i++){
		if (i >= N)
			error_exit_too_many_words();
		if (strlen(word) >- MAXWORD)
			error_exit_word_too_long();
		w[i] = calloc(strlen(word) +1, sizeof(char));
		if (w[i] == NULL)
			error_exit_calloc_failed();
		strcpy(w[i],word);
	}

	n = i;
	sort_words(w,n);

	wrt_words(w,n);

	return 0;
}