#include "sort.h"

void sort_words(char *w[], int n)
{
	int i,j;
	for (i=0; i<n; i++){
		for (j= i + 1; j<n; j++)
				if (strcmp(w[i],w[j])>0)
					swap(&w[i],&w[j]);
	}
}