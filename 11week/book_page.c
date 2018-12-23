#include <stdio.h>
#include <string.h>
int *book_page(int n, int *r){
	int count;
	int a,q;
	for(q=0 ;q<10;q++){
		r[q] = 0;
	}
	for(int i=1;i<=n;i++){
		a =i;
		while(a!=0){
			r[a%10] +=1;
			a /= 10;
		}
	}
	return r;
}

int main(){
	FILE *fp;
	int n, r[10];
	fp = fopen("input.txt", "r");
	while(fscanf(fp, "%d", &n) == 1){
		book_page(n,r);
		printf("\n The result for \"%d\"is \n",n);
		for (int i=0;i<10;i++) printf("r[%d]: %-4d",i,r[i]);
		printf("\n");
	}
	fclose(fp);

	return 0;
}
//for(int i = 1; i<=n ;i++){
	// 	int mid = i;
	// 	while(mid!=0){
	// 		a = mid % 10;
	// 		q =0;
	// 		while(1){
	// 			if(a==array[q]){
	// 				r[q] = r[q] + 1;
	// 				mid = mid / 10;
	// 				break;
	// 			}
	// 			else{
	// 				q++;
	// 			}
	// 		}
	// 	}
	// }
