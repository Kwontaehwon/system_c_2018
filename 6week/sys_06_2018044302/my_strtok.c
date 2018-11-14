#include <stdio.h>

int main()
{
	char str[100] = {0, };
	int i,len = 0;
	for (i=1;i<35;i++) {
		len += sprintf(str + len, "%d" ,i);
	}
	for (i=0;str[i]!='\0';i++) {
		if (str[i] == '0') {
			printf("\n");
		}
		else{
			printf("%c", str[i]);
		}
	}
	printf("\n");
		return 0;
}
