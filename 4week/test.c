#include <stdio.h>
#include <ctype.h>

int main(){
	char ch;
	int sum = 0;

	printf("Type the string\n");

	while(1){
		ch = getchar();
		if (ch == '\n') break;
		if(isalpha(ch)){
			if (islower(ch)){
				ch = toupper(ch);
				printf("%c",ch);
			}
			else {
				ch = tolower(ch);
				printf("%c",ch);
			}
		}
		if(isdigit(ch)){
			printf("%c",ch);
			sum += ch-48;
		}
		
	}
	printf("\nsum : %d\n",sum);

	return 0;
}