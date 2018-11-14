#include <stdio.h>

char *my_strcat(char *s1, const char *s2)
{
	int index = 0 ;
	int index2 = 0 ;
	while(s1[index]!='\0'){
		index++;
	}
	while(s1[index]!='\0' || s2[index2]!='\0'){
		s1[index] = s2[index2];
		index++;
		index2++;
	}
	return s1;
}
int my_strcmp(const char *s1, const char *s2)
{
	int c = 0;
	while(1){
		if (s1[c]=='\0' && s2[c]=='\0')
			return 0;
		if (s1[c]==s2[c]){
			c++;
		}
		else if (s1[c] > s2[c]){
			return 1;
		}
		else{
			return -1;
		}
	}
}

int main()
{
	char *str1 = "STARBUCKS";
	char str2[10] = "STAR";
	char *str3 = "BUCKS";

	printf("str1: %s\t\tstr2: %s\t\tstr3: %s\n", str1, str2, str3);
	printf("my_strcmp(str1,str3): %d\n", my_strcmp(str1,str3));
	printf("my_strcmp(str3,str2): %d\n", my_strcmp(str3,str2));

	my_strcat(str2,str3);

	printf("str1: %s\t\tstr2: %s\t\tstr3: %s\n", str1, str2, str3);
	printf("my_strcmp(str1,str2): %d\n", my_strcmp(str1,str2));
	
	return 0;
}