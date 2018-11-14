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
int main()
{
	char *str1 = "STARBUCKS";
	char str2[10] = "STAR";
	char *str3 = "BUCKS";
	my_strcat(str2,str3);
	printf("%s\n",str2);
		return 0;
}

