#include <stdio.h>

int main(){
	char ch_A = 'A';
	char ch_Z = 'Z';
	char ch_a = 'a';
	int count = ch_Z - ch_A + 1;
	int i;

	for (i=0; i<count ; i++) {
		printf("Uppercase char : %c \tint: %3d \thex: %x \t\tLowercase char: %c \tint: %3d \thex: %x \n", ch_A, ch_A, ch_A, ch_a, ch_a, ch_a);
		ch_a++;
		ch_A++;
	}
	return 0;
}