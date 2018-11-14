#include <stdio.h>
#include <string.h> // strcat, strcmp , strcpy, strlen

int main(){
	char str1[10];
	strcpy(str1, "STAR");
	char *str2 = "BUCKS";
	printf("str1: %s\t\tstr2: %s\n\n", str1, str2);

	printf("Do strcat(str1, str2)\n");
	strcat(str1, str2);
	printf("str1: %s\t\tstr2: %s\n\n", str1,str2);
	printf("strlen(str1): %lu\t\tstrlen(str2): %lu\n\n",
	 strlen(str1), strlen(str2));

	printf("str1[3] string: %s\t char : %c\n\n", &str1[3], str1[3]);
	printf("str1[9] string: %s\t char : %c\n\n", &str1[9], str1[9]);

	printf("Do strcmp(str1, str2)\n");
	if (strcmp(str1, str2) == 0 )
		printf("str1 is equal to str2!\n");
	else
		printf("str1 is not equal to str2...\n");

	return 0;
}