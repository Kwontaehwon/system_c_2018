#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int cnt  = 0;

void move(int,char,char,char);
int get_n_from_user(void);

int main(){
	int n;
	n = get_n_from_user();
	assert(n > 0 && n < 7);
	move(n,'A','B','C');
	return 0;
}
void move(int n, char a, char b, char c){
	if (n==1) {
		cnt++;
		printf("%5d: %s%d%s%c%s%c \n",cnt, "Move disk",1, "from tower",a,"to tower", c);
	}
	else{
		move(n-1,a,c,b);
		cnt++;
		printf("%5d: %s%d%s%c%s%c \n",cnt, "Move disk",n, "from tower",a,"to tower", c);
		move(n-1,b,a,c);
	}
}
	
int get_n_from_user(void){
	int n;
	printf("%s",
		"---\n"
		"TOWER OF HANOI : \n"
		"\n"
		"Input n: ");
	if (scanf("%d", &n) != 1 || n < 1){
		printf("\nERROR: Positive integer not found - bye!\n\n");
		exit(1);
	}
	printf("\n");

	return n;
}