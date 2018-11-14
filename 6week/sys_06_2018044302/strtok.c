#include <stdio.h>
#include <string.h>

int main()
{
	char str[100] = {0,};

	int i, len = 0;
	for ( i=1;i<35;i++){
		len += sprintf(str + len,"%d",i);
	}
	printf("str: %s\n",str);

	char *ptr = strtok(str,"0");
	while (ptr != NULL){
		printf("%s\n",ptr);
		ptr = strtok(NULL, "0");
	}

	return 0;
}
