#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 50
#define N       300

void error_exit_calloc_failed(void);
void error_exit_too_many_words(void);
void error_exit_word_too_long(void);
void sort_words(char *w[], int n);
void swap(char **p, char **q);
void wrt_words(char *w[], int n);