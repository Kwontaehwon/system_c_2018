#include <stdio.h>
#include <ctype.h>

int main(){
	char ch;
	printf("Type character...\n");
	while (1) {
		ch = tolower(getchar());
		if (ch == 'q') break;
		switch (ch) {
			case 'a' :
				printf("You typed A.\n");
				break;
			case 'b' :
				printf("You typed B.\n");
				break;
			case 0x63 :
				printf("You typed C.\n");
				break;
			case 27:
				printf("You typed ESC\n");
				break;
		}
	}
}