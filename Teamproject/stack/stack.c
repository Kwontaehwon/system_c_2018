#include <stdio.h>
#define STACK_SIZE 100

int stack[STACK_SIZE];
int top = -1;

void push(int index){
   if (top >= STACK_SIZE-1) printf("StackOverflow error\n");
   else {
      printf("stack_push %d\n",index);
      stack[++top] = index;
   }

}
int pop(){
   if (top == -1){
      printf("StackUnderflow error\n");
      return 0;
   }
   else{
      printf("stack_pop %d\n",stack[top]);
      top--;
      return 0;
   }
}

int topvalue(){
      if (top == -1){
      printf("stack is empty\n");
      return 0;
   }
   else{
      return stack[top];
   }
}
void stackprint(){
   int i;
   if (top == -1){
      printf("stack is empty\n");
      return;
   }
   else{
      printf("STACK = ");
      for (i = top; i>=0 ; i--){
	        if (i==0){
	        printf("%d ]\n",stack[i]);
	        }
	        else{
	        printf("%d ",stack[i]);
	        }
        }
    }
}


int main(int argc, char *argv[]){
   int stacktop;
   stackprint();
   push(1);
   stackprint();
   push(2);
   stackprint();
   push(3);
   stackprint();
   pop();
   stackprint();
   stacktop = topvalue();
   printf("stacktop is %d\n",stacktop);
   return 0;
}
