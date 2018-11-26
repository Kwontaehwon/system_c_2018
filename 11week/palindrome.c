#include <stdio.h>
#include <string.h>

int isPalindrome(char *a){
	int i;
	int length = strlen(a)-1;
	for(i = 0; i<strlen(a)/2+1; i++){ // 0 1 2 3 4 5 stars 
		if(*(a+i)!=*(a+length-i)) return 0;
	}
	return 1;
}

int main(){
	char *str1 = "stars";
	char *str2 = "hello world";
	char *str3 = "v";
	char *str4 = "live on time,emit no evil";
	char *str5 = "step on no pets";

	printf("\"%s\" is %sa palindrome. \n", str1, isPalindrome(str1) ? "" : "NOT ");
	printf("\"%s\" is %sa palindrome. \n", str2, isPalindrome(str2) ? "" : "NOT ");
	printf("\"%s\" is %sa palindrome. \n", str3, isPalindrome(str3) ? "" : "NOT ");
	printf("\"%s\" is %sa palindrome. \n", str4, isPalindrome(str4) ? "" : "NOT ");
	printf("\"%s\" is %sa palindrome. \n", str5, isPalindrome(str5) ? "" : "NOT ");

}
