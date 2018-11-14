int main(){

	int i;
	init_stack();

	printf( "\nPush 5, 4, 7 ,8, 2, 1");
	push(5);
	push(4);
	push(7);
	push(8);
	push(2);
	push(1);
	print_stack();

	printf("\npop");
	i = pop();
	print_stack();
	printf("\n popped value is %d\n", i);

	printf("\nPush, 3,2,5,7,2")
	push(3);
	push(2);
	push(5);
	push(7);
	push(2);
	print_stack();

	printf("Now Stack is full, push 3");
	push(3);
	print_stack();

	printf("\nInitalize stack");
	init_stack();
	printf("\nNow Stack is full, push 3");
	push(3);
	print_stack();

	printf("\nInitalize stack");
	init_stack();
	print_stack();

	printf("\nNoew Stack is empty, pop");
	i = pop();
	print_stack();
	printf("\n popped value is %d\n", i);
}