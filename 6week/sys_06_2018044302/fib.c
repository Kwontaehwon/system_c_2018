#include <stdio.h>

int fib(int);

int main(){
	int n,i;
	printf("Type fibonacci number: ");
	scanf("%d", &n);

	if (n < 1 ){
		printf("Integer n must be 1 at least.\n");
		return 1;
	}
	printf("%dth fibonacci number is %d\n", n , fib(n));

	return 0;
}

int fib(int num)
{
	if (num == 1 || num == 2)
		return 1;
	else
		return fib(num-1) + fib(num-2);
}