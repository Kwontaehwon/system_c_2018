#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	int i, n, seed;
	int count;
	seed = time(NULL);
	srand(seed);
	printf("Some randomly distributed integers will be printed\n"
		"How many do you want to see?  \n");
	scanf("%d", &n);
	count = 0;
	while (1) {
		count++;
		printf("%12d", rand());
		if (count == n) break;
		if (count % 5 != 0) continue;
		putchar('\n');
	}
	printf("\n\n");
	return 0;
}