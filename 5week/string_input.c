#include <stdio.h>

int main(void){
	char str[100] = {0,};
	printf("Initial str: %s\n\n", str);

	printf("Now starting the scanf function\n");
	printf("scanf input: ");
	scanf("%s", str);
	printf("scanf str: %s\n\n", str);

	printf("Now starting the gets function\n");
	printf("gets input: ");
	gets(str);
	printf("gets str: %s\n\n", str);

	printf("Now starting the fgets function\n");
	printf("fgets input:");
	fgets(str, sizeof(str), stdin);
	printf("fgets str: %s\n\n", str);

	return 0;
}