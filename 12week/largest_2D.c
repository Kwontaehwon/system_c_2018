#include <stdio.h>
#include <stdlib.h>

void find_largest_smallest(int **a,int row_size,int col_size, int **largest, int **smallest){
	int i,j;
	**largest = a[0][0];
	**smallest = a[0][0];
	for (i=0;i<row_size;i++){
		for (j=0;j<col_size;j++){
			if(a[i][j] > **largest) **largest = a[i][j];
			else if(a[i][j] < **smallest) **smallest = a[i][j];
		}
	}
}

int main(){
	int *largest = (int *)malloc(sizeof(int));
	int *smallest = (int *)malloc(sizeof(int));
	int firstRow[] = {1,11,3,18,33};
	int secondRow[] = {-34,15,23,46,45};
	int thirdRow[] = {57,-13,-113,0,-57};

	int *a[] = {firstRow, secondRow, thirdRow};

	int row_size = sizeof(a)/sizeof(a[0]);
	int col_size = sizeof(firstRow)/sizeof(firstRow[0]);

	find_largest_smallest(a,row_size,col_size,&largest,&smallest);

	printf("The largest value in array a: %d\n", *largest);
	printf("The smallest value in array a: %d\n", *smallest);

	return 0;
}
