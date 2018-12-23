#include <stdio.h>


void find_two_largest(int *a, int n, int *largest, int *sec_largest){
	int i;
	for (i=0;i<n;i++){
		if(a[i]>*largest){
			*sec_largest = *largest;
			*largest = *(a+i);
			continue;
		}
		if(a[i]>*sec_largest){
			*sec_largest = *(a+i);
		}
	}
}

int main(){
	int largest, sec_largest;
	int a[] = {1,11,3,18,8};

	int n = sizeof(a)/sizeof(a[0]);
	find_two_largest(a,n,&largest,&sec_largest);

	printf("The largest value in a[] :     %d\n", largest);
	printf("Second largest value in a[] :     %d\n", sec_largest);

	return 0;
}