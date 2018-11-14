#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, n ;
	printf("Some randomly distributed integers will be printed\n"
		"How many do you want to see?  \n");
	scanf("%d", &n);
	for (i=0;i<n;i++){
		if (i % 5 == 0)
			putchar('\n');
		printf("%12d", rand());
	}
	printf("\n\n");
	return 0;
}