#include <stdio.h>
#define MAXSTRING 100

int main(void){
	char fname[MAXSTRING];
	int c;
	FILE *ifp;

	fprintf(stderr, "Input a filename : ");
	scanf("%s", fname);
	ifp = fopen(fname, "r");
	fseek(ifp,0,SEEK_END);
	fseek(ifp,-1,SEEK_CUR);
	while (ftell(ifp) > 0){
		c = getc(ifp);
		putchar(c);
		fseek(ifp,-2,SEEK_CUR);
	}
	putchar('\n');

	fclose(ifp);

	return 0;
}