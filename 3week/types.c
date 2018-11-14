#include <stdio.h>

int main(){

	printf("The size of some fundamental types. \n\n");
	printf("char:%3lu byte\n", sizeof(char));
	printf("short:%3lu byte\n", sizeof(short));
	printf("int:%3lu byte\n", sizeof(int));
	printf("unsigned:%3lu byte\n", sizeof(unsigned));
	printf("float:%3lu byte\n", sizeof(float));
	printf("double:%3lu byte\n", sizeof(double));
	printf("long double:%3lu byte\n", sizeof(long double));

}