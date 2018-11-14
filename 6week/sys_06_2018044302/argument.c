#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	int i;
	int sum = 0;

	if (argc <3) {
		printf("Too few argument(less than 3)\n");
		return 1;
	}
	for (i=0; i<argc; i++){
		printf("argv[%d] : %s\n",i,argv[i]);
		if (isdigit(*argv[i])){
			sum += atoi(argv[i]);
		}
	}
	printf("Sum o argument: %d\n", sum);
	return 0;
}