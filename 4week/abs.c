#include <stdio.h>

int main(){
	int num, abs;
	printf("Type an interger: ");
	scanf("%d", &num);

	num >= 0 ? printf("positive\n") : printf("negative\n");
	abs = num >= 0 ? num : num * -1;
	printf("abs: %d\n", abs);

	return 0;

}