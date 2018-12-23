#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define TRUE 1
#define FALSE 0
 typedef struct Node{
  char val;
  struct Node *next;
  struct Node *prev;
}Node;
 typedef struct {
  Node *head;
  int size; // 노드의 전체 크기
  int size_1; // 소수점 자리수 저장
  int size_2; // 자연수 자리수 저장
  int swh ; // 여러가지 경우를 처리해주기위한 switch 넘버
  int i; // 연산자의 갯수
}DLL;
 Node *newnode(char c){
  Node *temp =(Node *)malloc(sizeof(Node));
  temp-> val = c;
  temp-> next = NULL;
  temp-> prev = NULL;
  return temp;
}
DLL *newDLL(){
  DLL *temp = (DLL *)malloc(sizeof(DLL));
  temp -> head = NULL ;
  temp -> size = 0 ;
  temp -> size_1 = 0 ;
  temp -> size_2 = 0 ;
  temp -> swh = 0 ;
  temp -> i = 0 ;
  return temp;
}
void append(DLL *list, Node *newnode);
void print(DLL *list);
void postfix(DLL *list,DLL *list_1);
void getnumber(DLL *list,FILE *ifp);
void cal(DLL *list,DLL *stack_3); //기본적인 계산을 해주는 메인함수
void reverse(DLL *list, DLL *list_1); // 노드의 값을 반대로 다시 넣어주는 함수
int GreaterOpr(char opr1, char opr2);
void POP_all(DLL *stack, DLL *list_1);
void PushOrPop(DLL *stack, char input_opr, DLL *list_1);
void insert(DLL *list_1,DLL *list_3); // 계산한값과 기존에 있던 식을 합쳐주는 함수
void zero(DLL *stack_1, DLL *stack_2 ); // 소수점의 자릿수과 자연수의 자릿수를 맞춰주는 함수, 자릿수를 맞춰주기위해 0으로 채움,그리고 큰수를 stack_1에 저장해줌
int insertAt(DLL *stack_3, int index, Node *newnode); // 특정 index에 노드를 삽입하는 함수
int insertAt_int(DLL *stack_3, int index, Node *newnode); // 자연수 부분에 자릿수를 맟춰주기위해 0을 넣어주는 함수
void copy_1(DLL *list_1 , DLL *list_3); //list_1에 list_3의 노드를 복사해주는 함수
int deleteAt(DLL *list, int index); //특정 index의 노드를 삭제하는 함수
void delete_all(DLL *list1); // 노드를 전체 비워주는 함수
void DEL_DLL(DLL *list_1);
void plus_change(DLL *list_1); // -3 5+ 인경우를 처리해주는 함수 -> 3 5 - 로 바꿔줌, 그리고 list_1->swh 의 값을 바꿔줌
void size_check(DLL *list_1); // size를 재주는 함수
void delete_par(DLL *list_1); // 후위표기법으로 바뀐식의 괄호를 없애주는 함수
void plus_zero(DLL *list_3 ); // 정답이 .1 -.1 인경우 .앞에 0을 추가해주는 함수
void write(DLL* list, FILE *ofp); // 계산 끝난 리스트를

 int main(){
  FILE *ifp, *ofp;
  ifp = fopen("input","r");
  ofp = fopen("outfile","w");
  DLL *list = newDLL(); // 입력을 받을 list
  getnumber(list,ifp); // 입력을 받아오는 함수
  int a = list -> i; // i => 연산자의 갯수
  DLL *list_1 = newDLL();//후위표기법으로 바뀐값을 넣어줄 list_1
  postfix(list,list_1); // 후위표기법으로 바뀐 list_1
  delete_par(list_1); // 괄호 삭제
  if(list-> swh == 2){ // 맨 앞에 마이너스 부호의 숫자가 나오는 경우 ex) -3+5 예제처리를 위해
    list-> swh = 0;
    insertAt(list_1,0,newnode('-'));
    plus_change(list_1);
  }
  DLL *list_2 = newDLL(); // 계산할 값을 넣어줄 list_2
  DLL *list_3 = newDLL();
  DLL *list_4 = newDLL();
  cal(list_1,list_2);  // 계산된 list_2
  reverse(list_2,list_3);
  plus_zero(list_3);
  for (int i = 1 ; i < a; i++){
    list_1 -> swh = 0;
    list_2 -> swh = 0;
    list_3 -> swh = 0;
    insert(list_1,list_3);
    size_check(list_1);
    delete_all(list_1);
    copy_1(list_1,list_3);
    plus_change(list_1);
    size_check(list_3);
    size_check(list_2);
    delete_all(list_3);
    delete_all(list_2);
    cal(list_1,list_2);
    reverse(list_2,list_3);
    plus_zero(list_3);
  }
  write(list_3,ofp);
  fclose(ifp);
  fclose(ofp);
 }

void size_check(DLL *list_1){ // 사이즈를 체크해주는 함수
  Node *curr = list_1-> head;
  list_1 -> size = 0 ;
  while(1){
    if (curr -> next == NULL){
      list_1 -> size = list_1 ->size + 1 ;
      break;
    }
    else {
      list_1 -> size = list_1 -> size + 1 ;
      curr = curr->next;
    }
  }
}
void plus_change(DLL *list_1){ // 앞의수가 -일경우 뒤에있는 +를 -로 바꿔주기 위한 함수
  Node *curr = list_1 -> head;
  if( curr->val == '-'){
    while(1){
      if (curr -> next == NULL) break;
        curr = curr->next;
      if (curr -> val == '+'){ // 
        curr -> val = '-';
        list_1 -> swh = 2;
        deleteAt(list_1,0);
        break;
      }
      else if(curr -> val == '-'){
          curr -> val = '+';
          deleteAt(list_1,0);
          list_1 -> swh = 3;
          break;
      }
    }
  }
}

void delete_all(DLL *list1){
  int a = list1->size;
  for(int i=0; i<a;i++)
    deleteAt(list1,0);
} // 노드를 비우기 위한 함수
void copy_1(DLL *list_1 , DLL *list_3){ // list_1 에 list_3에 값을 복사해줌.
  Node *curr = list_3 -> head;
  while(1){
    if (curr ->next == NULL){
      append(list_1,newnode(curr->val));
      break;
    }
    else{
      append(list_1,newnode(curr->val));
      curr = curr -> next;
    }
  }
}
void zero(DLL *stack_1, DLL *stack_2 ){ //소수점과 자연수의 자릿수를 맞춰줌.
  Node *curr = stack_1 ->head;
  Node *curr_1 = stack_2 ->head;
  DLL *stack_3 = newDLL(); // 임시로 값을 저장해둘 DLL ,무조건 stack_1이 큰수 이게
  int a = 0 ; // 소수점 자릿수 저장
  int b = 0 ; // 소수점 자릿수 저장
  int c = 0 ; // 자연수 자릿수 저장
  int d = 0 ; // 자연수 자릿수 저장
  while(1){ //stack_1의 자연수 자릿수 계산
    if(curr -> val == '.') break;
    else if ( curr -> next == NULL) {
      c++;
      break;
    }
    else{
      c++; // 자연수 자릿수
      curr = curr -> next;
    }
  }
  while(1){ //stack_1의 소수 자릿수 계산
    if (curr->next == NULL) break;
    else {
      a++;
      curr = curr -> next ;
    }
  }
  while(1){ //stack_2의 자연수 자릿수 계산
    if(curr_1 -> val == '.') break;
    else if (curr_1 ->next ==NULL){
      d++;
      break;
    }
    else{
      d++; // 자연수 자릿수
      curr_1 = curr_1 -> next;
    }
  }
  while(1){ //stack_2의 소수 자릿수 계산
    if (curr_1->next == NULL) break;
    else {
      b++; //소수점 자릿수
      curr_1 = curr_1->next ;
    }
  }
  stack_1 -> size_2 = c; // 자연수 자릿수 저장
  stack_2 -> size_2 = d;
  if ( a == 0 && b != 0) { // stack_1 정수 stack_2 소수
    append(stack_1,newnode('.'));
  }
  if ( b == 0 && a != 0 ) append(stack_2,newnode('.')); // stack_1 소수 stack_2 정수
  if ( c > d ){ // 앞수의 자연수 자리가 더 큰경우
    int f = c-d ; //0을 몇개를 넣을 것인가?
    for (int i = 0 ; i < f ; i++){
      insertAt_int(stack_2,0,newnode('0'));
    }
  }
  else if ( d > c ) { //뒷수의 자연수 자리가 더 큰 경우
    int f = d - c;
    for (int i = 0 ; i < f ; i++ ){
      insertAt_int(stack_1,0,newnode('0'));
    }
  }
  else{
  }
  if( a > b){ // stack_1 소수점 자리 갯수 > stack_2 소수점 자리 갯수
    int c = a-b; 
    for (int i = 0 ; i < c ; i++){ // 소숫점 자리의 갯수 차이 만큼 0을 넣어줌
      append(stack_2,newnode('0'));
    }
    stack_1 -> size_1 = a;
    stack_2 -> size_1 = a;
  }
  else if (b > a){
    int c = b - a;
    for (int i = 0 ; i < c; i++ ){ // 소숫점 자리의 갯수 차이 만큼 0을 넣어줌
      append(stack_1,newnode('0'));
    }
    stack_1 -> size_1 = b;
    stack_2 -> size_1 = b;
  }
  else {
    stack_1 -> size_1 = a;
    stack_1 -> size_1 = b;
  }
   if ( c< d){ // 뒷수가 더 큰수 일때 (swap 작업)
    copy_1(stack_3,stack_1);
    delete_all(stack_1);
    copy_1(stack_1,stack_2);
    delete_all(stack_2);
    copy_1(stack_2,stack_3);
    delete_all(stack_3);
    stack_1 -> swh = 1; // 앞의 수와 swap 됫다는 것을 알리는 표시 1
    stack_2 -> swh = 1; // 앞의 수와 swap 됫다는 것을 알리는 표시 2
  }
  else if (c == d){ // 자연수의 자릿수가 같다면 어떤 수가 더 큰수인지를 알때까지 반복.
    Node *curr_2 = stack_1 -> head;
    Node *curr_3 = stack_2 -> head;
    while(1){
      if (curr_2 ->val == '.' && curr_3 -> val =='.') {
        curr_2 = curr_2 -> next;
        curr_3 = curr_3 -> next;
      }
      int m = curr_2 -> val -48;
      int n = curr_3 -> val -48;
      if( n > m ){
        copy_1(stack_3,stack_1);
        delete_all(stack_1);
        copy_1(stack_1,stack_2);
        delete_all(stack_2);
        copy_1(stack_2,stack_3);
        delete_all(stack_3);
        stack_1 -> swh = 1;
        stack_2 -> swh = 1;
        break;
      }
      if ( curr_2 -> next == NULL && curr_3 -> next ==NULL) break;
      curr_2 = curr_2 ->next;
      curr_3 = curr_3 ->next;
    }
  }
}
void insert(DLL *list_1,DLL *list_3){ // 계산된 DLL에 원래 있던 후위표기법 식이랑 합침
  append(list_3,newnode(' '));
  Node *curr = list_1->head ;
  Node *curr_1 = list_3->head ;
   while(1){ //지울 연산자의 다음 포인터
    if ( curr -> val == '+' || curr ->val == '-' || curr->val == '*') {
      curr = curr->next;
      break;
    }
    else {
      curr = curr->next;
    }
  }
  while(1){
    if(curr_1 ->next  == NULL) break;
    else curr_1 = curr_1 ->next;
  }
  while(1){
    if (curr->next == NULL) {
      append(list_3,newnode(curr->val));
      break;
    }
    append(list_3,newnode(curr->val));
    curr = curr ->next;
  }
}
 void cal(DLL *list,DLL *stack_3){ // list는 후위표기법을 바뀐식 stack_3는 답을 저장할 리스트
  DLL *stack_1 = newDLL(); // 숫자1
  DLL *stack_2 = newDLL(); // 숫자2
  Node *curr = list -> head ;
  while(1){ // + - 만날때 까지 노드움직임
    if( curr->val == '+' || curr->val == '-'){
      curr = curr->prev;
      curr = curr->prev;
      break;
    }
    else{
      curr = curr->next;
    }
  }
  while(1){ //첫번째 인자수 맨앞 빈칸
    if( curr->prev == NULL || curr->val == ' '){
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  curr = curr->next;
  while(1){ //첫번째 수 저장
    if( curr->val == ' ' ){
      curr = curr->prev;
      break;
    }
    else{
      append(stack_2,newnode(curr->val));
      curr = curr->next;
    }
  }
  while(1){ //첫번째 수 넘어감
    if( curr -> val == ' ' || curr->prev == NULL){
      curr = curr->prev;
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  while(1){ //두번째수 앞 빈칸까지
    if( curr->val == ' ' || curr->prev == NULL){
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  while(1){ //두번째 수 저장
    if( curr->val == ' ' ){
      break;
    }
    else{
      append(stack_1,newnode(curr->val));
      curr = curr->next;
    }
  }

  zero(stack_1,stack_2);

  if (list -> swh == 2){ // 처음입력받을때 맨앞수에 -가있는 상태  ex) -3+5 
    stack_1-> swh = 2;
    stack_2 -> swh = 2;
    list -> swh = 0;
  }
  if ( list -> swh == 1){ // zero함수에서 stack_1 과 stack_2 가 스왑되었다는 상태
    stack_1-> swh = 1;
    stack_2 -> swh = 1;
    list -> swh = 0;
  }
  if ( list -> swh == 3){ // - - 끼리 더할때의 경우를 말해주는 상태 ex) list 가 -3 5- 형태일때 
    stack_1-> swh = 3;
    stack_2 -> swh = 3;
    list -> swh = 0;
  }
   while(1){ // +나 - 만날때 까지 노드움직임
    if (curr ->val == '+' || curr->val =='-' || curr->val == '*'){
      break;
    }
    else{
      curr = curr->next;
    }
  }
   if( curr ->val == '+' ){
    Node *curr_1 = stack_1 ->head;
    Node *curr_2 = stack_2 ->head;
     while(1){ // 노드 끝까지 보냄
      if (curr_1->next == NULL) break;
      else curr_1 = curr_1 ->next;
    }
    while(1){ // 노드 끝까지 보냄
      if (curr_2->next == NULL) break;
      else curr_2 = curr_2 ->next;
    }
    int count = 0 ; //올림을 할때 쓰기위함
    int a  = curr_1 -> val - 48 ;
    int b  = curr_2 -> val - 48 ;
    int c ;
     while (1){ // + 계산시작
      // 수가 끝낫을경우 0으로 처리
       if ( curr_1 ->val == '.') {
        curr_1 = curr_1 -> prev;
      }
      if ( curr_2 -> val == '.') {
        curr_2 = curr_2 -> prev;
      }
       a = curr_1 -> val - 48 ;
      b = curr_2 -> val - 48 ;
       c = a+b;
       if (count == 1){
        c++;
        count = 0 ;
        if ( c >= 10){
          c = c-10;
          count = 1;
        }
      }
      else {
        if ( c >= 10 ){
          c = c - 10;
          count = 1;
        }
      }
       if ( curr_1 != NULL) curr_1 = curr_1 ->prev;
      if ( curr_2 != NULL) curr_2 = curr_2 ->prev;

      c = c + 48;
      append(stack_3,newnode(c));
      if ( curr_1 == NULL && curr_2 == NULL){
        if ( count == 1){ // 수를 더해서 자리수가 올라갈경우
          append(stack_3,newnode('1'));
          count = 0 ;
          }
         break;
        }
      } // while문
      int d = stack_1 ->size_1;

      if ( d > 0) insertAt(stack_3,d,newnode('.'));
      if ( stack_1 -> swh == 1 ) stack_3 -> swh = stack_1 -> swh;
      if ( stack_1 -> swh == 3) append(stack_3,newnode('-'));// -3 5 - 인경우
      stack_1 ->swh = 0;
      stack_2 ->swh = 0;
      stack_3 ->swh = 0;
    } // if +문에 걸림

  //// -계산
    else if( curr ->val == '-' ){
     Node *curr_1 = stack_1 ->head;
     Node *curr_2 = stack_2 ->head;
   while(1){ // 노드 끝까지 보냄
     if (curr_1->next == NULL) break;
     else curr_1 = curr_1 ->next;
   }
   while(1){ // 노드 끝까지 보냄
     if (curr_2->next == NULL) break;
     else curr_2 = curr_2 ->next;
   }
     int count = 0 ;
     int a = curr_1 -> val - 48 ;
     int b = curr_2 -> val - 48 ;
     int c ;
   while(1){
     if ( curr_1 ->val == '.') {
       curr_1 = curr_1 -> prev;
     }
     if ( curr_2 -> val == '.') {
       curr_2 = curr_2 -> prev;
     }
     a = curr_1 -> val - 48 ;
     b = curr_2 -> val - 48 ;
     c = a-b;
     if (count == 1){
       c--;
       count = 0;
     }
     if (c< 0){
       c = c+10;
       count = 1;
     }
     if ( curr_1 != NULL) curr_1 = curr_1 ->prev;
     if ( curr_2 != NULL) curr_2 = curr_2 ->prev;
     c = c + 48;
     append(stack_3,newnode(c));
     if ( curr_1 == NULL && curr_2 == NULL){
         break;
        }
     }
     int d = stack_1 ->size_1;
     stack_3 -> swh = stack_1 -> swh;
     //printf("\n stack_3 -> swh : %d\n",stack_3 -> swh);
     //printf("\nd : %d\n",d);
     if ( d > 0) insertAt(stack_3,d,newnode('.'));
     Node *curr_3 = stack_3 -> head;
     /////// 자연수자리의 쓸데없는 0 삭제 ex -09라고 출력되는데 -9로 바꿔줌
     while(1){
       if (curr_3 -> next ==NULL) break;
       else curr_3 = curr_3 ->next;
     }
     while(1){
       if (curr_3 -> val != '0') break;
       else {
         curr_3 = curr_3 -> prev;
         curr_3 ->next = NULL;
       }
     }
     ////// stack_3의 값이 -일경우
     if ( stack_3 -> swh == 1) append(stack_3,newnode('-'));
     stack_1 ->swh = 0;
     stack_2 ->swh = 0;
     stack_3 ->swh = 0;
   }


}
 void getnumber(DLL *list,FILE *ifp){
  int count = 0 ; //몇번 돌았나, -3+5 예제 처리를 위함.
  char temp;
  while(1){
    temp = getc(ifp);
    if(temp == '\n') break;
    if ( temp == '.' || temp =='('|| temp ==')' || temp == '+'|| temp == '-'|| temp == '*'|| temp == '/' ){
      if (count == 0){   //기존에서 추가한 부분
        if ( temp == '+') {
          temp = getc(ifp);
          count++;
        }
        if ( temp == '-') { //맨 앞에 마이너스가 나오는 경우
          list-> swh = 2;
          temp = getc(ifp);
          count ++;
        }
      }
      if (temp == '+' || temp == '-' || temp == '*') list->i = list->i + 1; // 추가한 부분
      append(list,newnode(temp));
      count ++;
      ///////////////
      temp = getc(ifp);
      if (temp == '+' || temp == '-' || temp == '*') {
         printf("ERROR: Wrong Input !\n");
         exit(1);
      }
      else if ( isblank(temp) ) count ++;
      else if ( isalpha(temp) ) {
        printf("ERROR: Wrong Input !\n");
        exit(1);
      }
      else if ( isdigit(temp) ){
        append(list,newnode(temp));
        count ++;
      }
      else {
        printf("ERROR: Wrong Input !\n");
        exit(1);
      }
      //////////////
    }
    else if ( isblank(temp) ) count ++;
    else if ( isalpha(temp) ) {
      printf("ERROR: Wrong Input !\n");
      exit(1);
    }
    else if ( isdigit(temp) ){
      append(list,newnode(temp));
      count ++;
    }
    else {
      printf("ERROR: Wrong Input !\n");
      exit(1);
    }
  }
}
 int GreaterOpr(char opr1, char opr2) // 연산자의 우선순위를 결정하는 함수
{
	if(opr1 == '*') {
		if (opr2 == '+' || opr2 == '-' || opr2 == ')' )
			return TRUE;
		else if (opr2 == '*')
			return TRUE;
		else if (opr2 == '(')
			return FALSE;
 	}
	else if (opr1 == '+' || opr1 == '-'){
		if (opr2 == '+' || opr2 == '-'|| opr2 == ')')
			return TRUE;
		else if(opr2 == '*'||opr2 == '(')
			return FALSE;
	}
	else if (opr1 == '(') {
		if (opr2 == ')')
			return TRUE;
		else
			return FALSE;
	}
	else if (opr1 == ')')
		return TRUE;
}
 void POP_all(DLL *stack,DLL *list_1)
{
  Node *cur = stack->head;
  while(cur->next != NULL){
		cur = cur->next;
	}
  while(1){
    if( cur -> prev == NULL){
      append(list_1, newnode(cur->val));
      break;
    }
    else{
      append(list_1, newnode(cur->val));
      cur = cur->prev;
    }
  }
  free(stack);
  stack = newDLL();
}
 void PushOrPop(DLL *stack, char input_opr, DLL *list_1)
{
	while (1) {
		int ssize = stack->size;
		if (ssize == 0) {
			append(stack,newnode(input_opr));
			ssize+=1;
			break;
		}
		else {
			Node *bigyo = stack->head;
			while (bigyo->next != NULL)
				bigyo = bigyo -> next;
			if (GreaterOpr(bigyo->val,input_opr) == FALSE){
				append(stack,newnode(input_opr));
				ssize+=1;
				break;
			}
			else {
				if (ssize == 1) {
					POP_all(stack,list_1);
					append(stack,newnode(input_opr));
					ssize+=1;
					break;
				}
				else if (ssize >= 2) {
					append(list_1,newnode(bigyo->val));
					bigyo=bigyo->prev;
					bigyo->next = NULL;
					ssize -= 1;
				}
			}
		}
	}
}
void postfix(DLL *list,DLL *list_1){
  DLL *stack = newDLL(); // 연산자 담아둘 스택
  Node *curr = list -> head ;
  while(1){
    if( curr -> next == NULL){ //마지막숫자 일 경우
      append(list_1,newnode(curr->val));
      append(list_1,newnode(' '));
      break;
    }
    else if( isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음
      append(list_1,newnode(curr->val));
      if ( curr -> next == NULL) break;
      curr = curr -> next;
    }
    else{  // 연산자들
      append(list_1,newnode(' '));
      PushOrPop(stack, curr->val, list_1);
	  curr = curr -> next;
	  }
  }
  POP_all(stack,list_1);
}
void reverse(DLL *list, DLL *list_1){ //
  Node *curr = list->head;
  while(1){ // 노드를 끝까지 보냄
    if ( curr -> next == NULL) break;
    else curr = curr -> next;
  }
  while(1){
    if( curr -> prev == NULL){
       append(list_1,newnode(curr->val));
       break;
    }
    else {
      append(list_1,newnode(curr->val));
      curr = curr -> prev;
    }
  }
}
void append(DLL *list,Node *newnode){
  Node *curr ;
  if(list->head == NULL){
    list->head = newnode;
  }
  else{
    curr = list->head;
    while (curr ->next != NULL){
      curr = curr->next;
    }
    newnode->prev = curr;
    curr->next = newnode;
  }
  list->size = list->size + 1;
}
void print(DLL *list) {
	Node *curr = list->head;
	while (curr != NULL) {
		printf("%c",curr->val);
		curr = curr->next;
	}
}

void write(DLL *list,FILE *ofp){
  Node *curr = list->head;
  char c;
  while (curr != NULL) {
    c = curr->val;
    putc(c,ofp);
    curr = curr->next;
  }
}
int insertAt_int(DLL *list, int index, Node *newnode){
	int count = 0;
	Node *curr = list->head;
	if( index == 0 ){
		list->head = newnode;
		curr->prev = newnode;
		list->head->next = curr;
		return 0;
	}
	while(count != index){
		count++;
		curr = curr->next;
		if ( curr->next == NULL) break;
	}
	if(curr->next == NULL){
			newnode->prev = curr;
			curr->next = newnode;
			return 0;
	}
	newnode->prev = curr->prev;
	newnode->next = curr;
	curr->prev->next = newnode;
	curr->prev = newnode;
}
int insertAt(DLL *stack_3, int index, Node *newnode){ // 소수점 삽입을 위한 함수
	Node *curr = stack_3->head;
  int count = 0 ;
  if ( index < 0 ) {
		printf("INSERT ERROR: Out of Bound.\n");
		return 0;
		}
  if( index == 0 ){
		stack_3->head = newnode;
		curr->prev = newnode;
		stack_3->head->next = curr;
		return 0;
	}
  while(1){
    if(curr->next == NULL) {
      count++;
      break;
    }
    else {
      curr = curr->next;
      count ++;
    }
  }
  index = count - index;
  for (int i = 0 ; i < index ; i++){
    curr = curr->prev;
  }
	newnode->prev = curr;
	newnode->next = curr->next ;
  curr->next->prev = newnode;
	curr->next = newnode;
}
int deleteAt(DLL *list, int index){
   Node *curr = list->head;
   int count = 0;
   if(list->size >1){
   if (index == 0){
      list->head->next->prev = NULL;
      list ->head = list->head->next;
      list -> size = list -> size - 1;
      return 0;
   }
   while(count != index){
      count++;
      curr = curr->next;
      if(curr == NULL ) {
         printf("DELETE ERROR: Out of Bound.\n");
         return 0;
      }
   }
   if(count == index){
      if(curr->next == NULL){
         curr->prev->next = NULL;
         list -> size = list -> size - 1;
         return 0;
      }
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      list -> size = list -> size - 1;
   }
 }
 else{
  list->size = list-> size - 1;
  list->head->prev = NULL;
  list->head->next = NULL;
  list->head = NULL;
  }
}
void delete_par(DLL *list_1){ // 괄호 발견시 삭제
  Node *curr = list_1 -> head;
  if(curr -> val == ' ') deleteAt(list_1,0); // 공백있으면 삭제
  while(1){
    if(curr -> next == NULL) {
      if(curr->val == '(' ||curr->val ==')') {
        curr->prev->next = NULL;
      }
      break;
    }
    if(curr->val == '(' ||curr->val ==')' ) {
      curr-> prev ->next = curr->next;
      curr-> next ->prev = curr->prev;
    }
    curr = curr->next;
  }

}
void plus_zero(DLL *list_3 ){ //.앞에 0이없을경우 붙여줌
  Node *curr = list_3 ->head;
  while(1){
    if(curr->val =='.'){
      if (curr -> prev == NULL ) { //11.2-44.1+33인 경우 답이 .1 인경우
        insertAt(list_3,0,newnode('0'));
        break;
      }
      if(curr->prev ->val == '-'){ // 1-1.1 , 답이 -.1인 경우
        insertAt(list_3,1,newnode('0'));
      }
    }
    if (curr -> next == NULL) break;
    curr = curr->next;
  }
}