#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#define TRUE 1
#define FALSE 0
 typedef struct Node{
  char val;
  struct Node *next;
  struct Node *prev;
}Node;
 typedef struct {
  Node *head;
  int ssize;//스택의 길이(postfix용)
  int size; //연결리스트의 전체크기
  int size_1; //소수점 자리수 저장
  int size_2; //자연수 자리수 저장
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
  temp -> ssize = 0;
  temp -> head = NULL ;
  temp -> size = 0 ;
  temp -> size_1 = 0 ;
  temp -> size_2 = 0 ;
  temp -> swh = 0 ;
  temp -> i = 0 ;
  return temp;
}

void G_POP(DLL *stack, DLL *list_1);
void stack_append(DLL *list, Node *newnode);
void append(DLL *list, Node *newnode);
void print(DLL *list);
void postfix(DLL *list,DLL *list_1);
void getnumber(DLL *list);
void cal(DLL *list,DLL *stack_3);//기본적인 계산을 해주는 메인함수
void reverse(DLL *list, DLL *list_1);// 노드의 값을 반대로 다시 넣어주는 함수
int GreaterOpr(char opr1, char opr2);
void POP_all(DLL *stack, DLL *list_1);
void PushOrPop(DLL *stack, char input_opr, DLL *list_1);
void insert(DLL *list_1,DLL *list_3); // 계산한값과 기존에 있던 식을 합쳐주는 함수
void zero(DLL *stack_1, DLL *stack_2); // 소수점의 자릿수를 맞춰주는 함수
int insertAt(DLL *stack_3, int index, Node *newnode); // 특정 index에 노드를 삽입하는 함수
void copy_1(DLL *list_1 , DLL *list_3); //list_1에 list_3의 노드를 복사해주는 함수
int deleteAt(DLL *list, int index);
void delete_all(DLL *list1);// 노드를 전체 비워주는 함수
void size_check(DLL *list_1); // 총 길이를 재주는 함수
void plus_zero(DLL *list_3 ); // .1 -.1 인경우 .앞에 0을 추가해주는 함수
void write(DLL* list, FILE *ofp);
void free_1(DLL* stack);

long long getElapsedTime(unsigned int nFlag)
{
  const long long NANOS = 1000000000LL;
  static struct timespec startTS, endTS;
  static long long retDiff = 0;

  if (nFlag == 0) {
    retDiff = 0;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
      printf("Failed to call clock_gettime\n");
    }
  }
  else {
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
      printf("Failed to call clock_gettime\n");
    }
    retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
  }

  return retDiff;
}


int main(){
  getElapsedTime(0);
  DLL *list = newDLL(); // 입력을 받을 list
  DLL *list_2 = newDLL(); // 계산할 값을 넣어줄 list_2
  DLL *list_3 = newDLL(); // reverse한 값을 임시로 넣어줄 list_3
  getnumber(list); // 입력을 받아오는 함수
  DLL *list_1 = newDLL(); //후위표기법으로 바뀐값을 넣어줄 list_1
  postfix(list,list_1);  // 후위표기법으로 바뀐 list_1
  int a = list_1->i ;
  if(list-> swh == 2){ // -3+5 예제처리를 위해,맨앞에 -나온경우 나중에 -를 붙여줌.
    list-> swh = 0;
    insertAt(list_1,0,newnode('-'));
  }
  cal(list_1,list_2);  // 계산된 list_2
  reverse(list_2,list_3);
  for (int i = 1 ; i < a; i++){
    list_1 -> swh = 0; // 부호 변동을 방지
    list_2 -> swh = 0;
    list_3 -> swh = 0;
    insert(list_1,list_3); //list_1에 모든걸 저장
    size_check(list_1);
    size_check(list_3);
    delete_all(list_3);
    size_check(list_2);
    delete_all(list_2);
    cal(list_1,list_2);
    reverse(list_2,list_3);
    plus_zero(list_3);
  }
  printf("\nanswer\n");
  print(list_3);
  printf("Elapsed Time: %lld\n", getElapsedTime(1));
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
void zero(DLL *stack_1, DLL *stack_2 ){ // 소수점과 자연수의 자릿수를 맞춰줌.
  Node *curr = stack_1 ->head;
  Node *curr_1 = stack_2 ->head;
  DLL *stack_3 = newDLL(); // 임시로 값을 저장해둘 DLL ,무조건 stack_1이 큰수 이게

  int a = 0 ; // 소수점 자릿수 저장
  int b = 0 ; // 소수점 자릿수 저장
  int c = 0 ; // 자연수 자릿수 저장
  int d = 0 ; // 자연수 자릿수 저장
  int swh_1 = 0 ; //앞수에 마이너스가 들어왔을 경우, -를 빼주고 대신 표신
  int swh_2 = 0 ; //뒷수에 마이너스가 들어왔을 경우, -를 빼주고 대신 표신
  while(1){ //자연수자릿수 체크
    if(curr -> val == '.') break;
    else if (curr->val =='-')
    {
      swh_1 = 1;
      deleteAt(stack_1,0); //마이너스를 일단 삭제하고 나중에 붙여줌
      curr = curr->next;
    }
    else if ( curr -> next == NULL) {
      c++;
      break;
    }
    else{
      c++; // 자연수 자릿수
      curr = curr -> next;
    }
  }
  while(1){ //소수점자릿수 체크
    if (curr->next == NULL) break;
    else {
      a++;
      curr = curr -> next ;
    }
  }
  while(1){ //자연수자릿수 체크
    if(curr_1 -> val == '.') break;
    else if (curr_1->val =='-')
    {
      swh_2 = 1;
      deleteAt(stack_2,0); //일단삭제 하고 나중에 붙여줌
      curr_1 = curr_1->next;
    }
    else if (curr_1 ->next ==NULL){
      d++;
      break;
    }
    else{
      d++; // 자연수 자릿수
      curr_1 = curr_1 -> next;
    }
  }
  while(1){ //소수점 자릿수 체크
    if (curr_1->next == NULL) break;
    else {
      b++; //소수점 자릿수
      curr_1 = curr_1->next ;
    }
  }

  stack_1 -> size_2 = c; // 자연수 자릿수 저장
  stack_2 -> size_2 = d;
  if ( a == 0 && b != 0) { //한쪽은 소수고,한쪽은 정수 일경우
    append(stack_1,newnode('.'));
  }
  if ( b == 0 && a != 0 ) append(stack_2,newnode('.')); //한쪽은 소수고,한쪽은 정수 일경우
  if ( c > d ){ // 자연수자릿수를 맞춰주기 위함,앞수의 자연수 자리가 더 큰경우
    int f = c-d ; //0을 몇개를 넣을 것인가?
    for (int i = 0 ; i < f ; i++){
      insertAt(stack_2,0,newnode('0'));
    }
  }
  else if ( d > c ) { //자연수자릿수를 맞춰주기 위함,뒷수의 자연수 자리가 더 큰 경우
    int f = d - c;
    for (int i = 0 ; i < f ; i++ ){
      insertAt(stack_1,0,newnode('0'));
    }
  }

  if( a > b){ // 소수부분의 자릿수를 맞춰주기 위함
    int c =  a-b;
    for ( int i = 0 ; i < c ; i++){
      append(stack_2,newnode('0'));
    }
    stack_1 -> size_1 = a;
    stack_2 -> size_1 = a;
  }
  else if ( b > a){
    int c = b - a;
    for (int i = 0 ; i < c; i++ ){
      append(stack_1,newnode('0'));
    }
    stack_1 -> size_1 = b;
    stack_2 -> size_1 = b;
  }
  else {
    stack_1 -> size_1 = a;
    stack_1 -> size_1 = b;
  }
   if ( c < d){ // 뒷수가 더 큰수 일때
    int temp ; // -부호 붙여줄지 안붙여줄지 판단해주는 swh교체
    temp = swh_1 ;
    swh_1 = swh_2;
    swh_2 = temp;
    copy_1(stack_3,stack_1);
    delete_all(stack_1);
    copy_1(stack_1,stack_2);
    delete_all(stack_2);
    copy_1(stack_2,stack_3);
    delete_all(stack_3);
    stack_1 -> swh = 2; //앞수 뒷수가 바뀌었다는 표시
    stack_2 -> swh = 2; // 앞수 뒷수가 바뀌었다는 표시
  }
  else if (c == d){
    Node *curr_2 = stack_1 -> head;
    Node *curr_3 = stack_2 -> head;
    while(1){
      if (curr_2 ->val == '.' && curr_3 -> val =='.') {
        curr_2 = curr_2 -> next;
        curr_3 = curr_3 -> next;
      }
      int m = curr_2 -> val -48;
      int n = curr_3 -> val -48;
      if( n > m ){ // 뒷수가 더 큰수일때
        int temp ; // -부호 붙여줄지 안붙여줄지 판단해주는 swh교체
        temp = swh_1 ;
        swh_1 = swh_2;
        swh_2 = temp;
        copy_1(stack_3,stack_1);
        delete_all(stack_1);
        copy_1(stack_1,stack_2);
        delete_all(stack_2);
        copy_1(stack_2,stack_3);
        delete_all(stack_3);
        stack_1 -> swh = 2; //앞수 뒷수가 바뀌었다는 표시
        stack_2 -> swh = 2; //앞수 뒷수가 바뀌었다는 표시
        break;
      }
      if ( curr_2 -> next == NULL && curr_3 -> next ==NULL) break;
      curr_2 = curr_2 ->next;
      curr_3 = curr_3 ->next;
    }
  }
  if(swh_1 == 1) // 처음에 떼어둔 -를 붙여줌
  {
    insertAt(stack_1,0,newnode('-'));
    swh_1 = 0;
  }
  if(swh_2 == 1)
  {
    insertAt(stack_2,0,newnode('-'));
    swh_2= 0;
  }
}
void insert(DLL *list_1,DLL *list_3){ // 계산된 값을  원래 있던 후위표기법 식이랑 합침
  Node *curr = list_1->head ;
  Node *curr_1 = list_3->head ;
  int count = 0 ; // list_1의 총길이
  int count_1 = 0; //
  int count_2 = 0 ; // 처음지울 인뎃스번호
  int swh = 0; // -가 연산자가 아니고 부호표시를 해주는 것일때
   while(1)
   { //지울 연산자의 다음 포인터
    if ( curr -> val == '+' || curr->val == '*') //포인터가 연산자에 있음.
    {
      break;
    }
    else if( curr->val == '-' ){ // 연산자의 -인지,부호표시를 위한 -인지 확인 ex -3 5 - ,3 5 -
      if(curr->next == NULL || curr->next->val == ' ')
      {
        break;
      }
      else
      {
        curr = curr->next;
        swh = 1;
      }
    }
    else
    {
      curr = curr->next;
      count ++;
    }
  }
  curr = curr->prev ;
  curr = curr->prev ;
  count_1++;
  while(1)
  {
    if(curr->val == ' ')
    {
      count_1 ++;
      break;
    }
    curr = curr -> prev ;
    count_1++;
  }
  curr = curr->prev;

  //printf("\ncurr -> val : %c\n",curr->val);
  //printf("\ncount : %d count_1 : %d\n",count,count_1);
  while(1)
  {
    if(curr->val == ' ')
    {
      break;
    }
    else if (curr -> prev == NULL)
    {
      count_1++;
      break;
    }
    curr = curr -> prev ;
    count_1++;
  }
  count_2 = count - count_1 ; //처음에 지울 인덱스
  if (swh == 1) count_2 ++;  // -가 연산자가 아니고 부호표시를 해주는 것일때
  //printf("\ncount_2 : %d\n",count_2);
  count = count + 2;
  while(1) // curr의 헤드를 다시맨앞으로 보냄 1 3 3 * + 을 위해서 list_1->head -> val 로만 판단을해서
  {
    if(curr ->prev == NULL) break;
    curr = curr -> prev;
  }
  for (int i = 0 ; i < count_1+2; i++)
  {
    deleteAt(list_1,count_2);
  }
  while(1) // list_3의 노드를 가장 뒤로보내기
  {
    if(curr_1 -> next == NULL) break;
    curr_1 = curr_1 -> next;
  }
  insertAt(list_1,count_2,newnode(' '));
  while(1)
  {
    if(curr_1 ->prev  == NULL)
    {
      insertAt(list_1,count_2,newnode(curr_1->val));
      break;
    }
    insertAt(list_1,count_2,newnode(curr_1->val));
    curr_1 = curr_1 -> prev;
  }
  /*
  while(1) //curr이 free가 되지않아 계속 값이 남는다.
  {
    if ( curr -> val == '+' ||  curr -> val == '-' || curr -> val == '*')
    {
      deleteAt(list_1,count_2);
      break;
    }
      deleteAt(list_1,count_2);
      printf("\ncurr->val : %c\n",curr->val);
      deleteAt(list_1,count_2);
      printf("\ncurr->val : %c\n",curr->val);
      deleteAt(list_1,count_2);
      printf("\ncurr->val : %c\n",curr->val);
      deleteAt(list_1,count_2);
      printf("\ncurr->val : %c\n",curr->val);
      deleteAt(list_1,count_2);
      printf("\ncurr->val : %c\n",curr->val);
      break;
  }
  */
  //printf("\nlist_1\n");
  //print(list_1);

  //printf("\ncount : %d count_1 : %d\n",count,count_1);
}
void cal(DLL *list,DLL *stack_3){ // list는 후위표기법으로 바뀐식,stack_3는 답을 저장할 리스트
  DLL *stack_1 = newDLL(); // 숫자1
  DLL *stack_2 = newDLL(); // 숫자2
  Node *curr = list -> head ;
  int operator = 0 ; // 어떤 연산자인지 확인 + : 1, - : 2, * : 3
  while(1){ // + - 만날때 까지 노드움직임
    if( curr->val == '+' ){
      curr = curr->prev; 
      curr = curr->prev; 
      operator = 1;
      break;
    }
    else if(curr->val == '*')
    {
      curr = curr->prev;
      curr = curr->prev;
      operator = 3;
      break;
    }
    else if( curr->val == '-' ){ // 연산자의 -인지,부호표시를 위한 -인지 확인 ex -3 5 - ,3 5 -
      if(curr->next == NULL || curr->next->val == ' ') //연산자의 -
      {
        curr = curr->prev;
        curr = curr->prev;
        operator = 2;
        break;
      }
      curr = curr->next;
    }
    else{
      curr = curr->next;
    }
  }
  while(1){ //첫번째 인자수 맨앞 빈칸
    if( curr->prev == NULL)
    {

      break;
    }
    else if(curr->val == ' ')
    {
      curr = curr->next;
      break;
    }
    else{
      curr = curr->prev;
    }
  }
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
    if (curr -> val == ' ')
    {
      curr = curr->prev;
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  while(1){ //두번째수 앞 빈칸까지
    if( curr->val == ' ' ){
      curr = curr->next;
      break;
    }
    else if(curr->prev == NULL)
    {
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
    else
    {
      append(stack_1,newnode(curr->val));
      curr = curr->next;
    }
  }

  zero(stack_1,stack_2); //stack_1 이 더 큰값임.
  size_check(stack_1);
  size_check(stack_2);

// 큰수가 앞에 나온 상태. 

  if(stack_1->head->val == '-' && stack_2->head->val == '-' && operator == 1) //  -5 -3 + 인경우
  {
    deleteAt(stack_1,0);
    deleteAt(stack_2,0);
    stack_1 -> swh = 1; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 1;
  }
  else if(stack_1 -> head -> val =='-' && stack_2-> head -> val != '-' && operator == 1 ) // -5 3 + 인경우
  {
    deleteAt(stack_1,0);
    stack_1 -> swh = 1; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 1;
    operator = 2;
  }
  else if(stack_1 -> head -> val != '-' && stack_2-> head -> val == '-' && operator == 1 ) // 5 -3 + 인경우
  {
    deleteAt(stack_2,0);
    stack_1 -> swh = 0; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 0;
    operator = 2;
  }
  else if(stack_1 -> head -> val == '-' && stack_2-> head -> val == '-' && operator == 2 ) // -5 -3 - 인경우 ,
  {
    deleteAt(stack_1,0);
    deleteAt(stack_2,0);
    if(stack_1 -> swh == 2 && stack_2 -> swh == 2) // 스왑되었을때, , 처음입력들어오는 값이 -1-(-3)인경우,
    {
      stack_1 -> swh = 0;
      stack_2 -> swh = 0;
    }
    else
    {
      stack_1 -> swh = 1; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
      stack_2 -> swh = 1;
    }
  }
  else if(stack_1 -> head -> val == '-' && stack_2-> head -> val != '-' && operator == 2 ) // -5 3 - 인경우
  {
    deleteAt(stack_1,0);
    stack_1 -> swh = 1; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 1;
    operator = 1 ; // 연산자를 더하기로 바꿔줌
  }
  else if(stack_1 -> head -> val != '-' && stack_2-> head -> val == '-' && operator == 2 ) // 5 -3 - 인경우
  {
    deleteAt(stack_2,0);
    if(stack_1 -> swh == 2 && stack_2 -> swh == 2) // 스왑되었을때, , 처음입력들어오는 값이 -3 -5 인경우
    {
      stack_1 -> swh = 1;
      stack_2 -> swh = 1;
      operator = 1 ; // 연산자를 더하기로 바꿔줌
    }
    else
    {
    stack_1 -> swh = 0; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 0;
    operator = 1 ; // 연산자를 더하기로 바꿔줌
    }
  }
  else if(stack_1 -> head -> val == '-' && stack_2-> head -> val == '-' && operator == 3 ) // -5 -3 * 인경우
  {
    deleteAt(stack_1,0);
    deleteAt(stack_2,0);
    stack_1 -> swh = 0; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 0;
  }
  else if(stack_1 -> head -> val == '-' && stack_2-> head -> val != '-' && operator == 3 ) // -5 3 * 인경우
  {
    deleteAt(stack_1,0);
    stack_1 -> swh = 1; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 1;
  }
  else if(stack_1 -> head -> val != '-' && stack_2-> head -> val == '-' && operator == 3 ) // 5 -3 * 인경우
  {
    deleteAt(stack_2,0);
    stack_1 -> swh = 1; // 무조건 계산끝난뒤에 앞에 -를 붙여주는 swh = 1;
    stack_2 -> swh = 1;
  }
  // switch문 시작
  switch(operator)
  {
     case 1 :  // +계산
     {
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
              append(stack_3,newnode('1')); // ex) 99 + 1 = '1'00
              count = 0;
              }
             break;
            }
          } // while문
          int d = stack_1 ->size_1; // 소수점 자릿수를 저장

          if ( d > 0) insertAt(stack_3,d,newnode('.')); // 소수점 자릿수가 0보다 큰경우, . 을 삽입
          if ( stack_1 -> swh == 1) append(stack_3,newnode('-'));// -3 5 - 인경우
          stack_1 ->swh = 0;
          stack_2 ->swh = 0;
          stack_3 ->swh = 0;
          break;
    } // if +문에 걸림

    case 2 :  ////  -계산
    {
         Node *curr_1 = stack_1 ->head;
         Node *curr_2 = stack_2 ->head;
       while(1){ // 노드 끝까지 보냄
         if (curr_1->next == NULL) break;
         else curr_1 = curr_1 ->next;
        }
       while(1){ // 노드 끝까지 보냄
         if (curr_2 -> next == NULL) break;
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
         if ( d > 0) insertAt(stack_3,d,newnode('.'));
         Node *curr_3 = stack_3 -> head;
         /////// 자연수자리의 쓸데없는 0 삭제 ex -09라고 출력되는데 -9로 바꿔줌
         while(1){
           if (curr_3 -> next ==NULL) break;
           else curr_3 = curr_3 ->next;
         }
         while(1){
           if (curr_3 -> prev == NULL) break;
           if (curr_3 -> val != '0' ) break;
           else {
             if (curr_3 -> prev -> val != '.')
             {
               curr_3 = curr_3 -> prev;
               curr_3 ->next = NULL;
             }
             else break;
           }
         }
         ////// stack_3의 값이 -일경우
         if ( stack_1 -> swh == 1) append(stack_3,newnode('-'));
         else if ( stack_1 -> swh == 2 ) append(stack_3,newnode('-'));
         stack_1 ->swh = 0;
         stack_2 ->swh = 0;
         stack_3 ->swh = 0;
         break;
     }

    case  3 :  // *계산
    {
        Node *curr_1 = stack_1 -> head;
        Node *curr_2 = stack_2 -> head;

      if(stack_1->size_1 > 0)// 소수점의 인덱스 파악후 삭제
      {
        int a = 0;
        while(1)
        {
          if(curr_1->val =='.')
          {
            deleteAt(stack_1,a);
            deleteAt(stack_2,a);
            break;
          }
          curr_1 = curr_1 ->next;
          a++;
        }
      }
      DLL *stack_4 = newDLL(); //값을 임시 저장해둘 DLL
      DLL *stack_5 = newDLL(); //+계산을 후위표기법으로 하기위해 만든 DLL
      if( stack_3 -> head == NULL) append(stack_3,newnode('0')); // 답을 저장할 stack_3,처음일경우 NULL이기 때문에 0 을 넣어줌
      int count = 0 ; // 앞수 자릿수
      int count_1 = 0 ; // 뒷수 자릿수
      int count_2 = 0 ; // 곱하기 올림을 위해서
      while(1) // 앞수 노드 끝까지 보냄
      {
        if (curr_1->next == NULL) break;
        else curr_1 = curr_1 ->next;
      }

      while(1) // 뒷수 노드 끝까지 보냄
      {
        if (curr_2->next == NULL) break;
        else curr_2 = curr_2 ->next;
      }

      while(1) //더하기 계산
      {
          Node *curr_4 = stack_4 -> head;//값을 임시 저장해둘 DLL
          Node *curr_3 = stack_3 -> head;//답
          int a = curr_1 ->val - 48;
          int b = curr_2 ->val - 48;
          int c = a*b;
          c = c + count_2 ; // 그전에 계산한값에서 올려주는 수가 있을떄
          count_2 = 0; //올려줬으므로 초기화
          while(1) // 곱한값이 10의 자리를 넘어가는 경우
          {
              if ( c < 10) break;
              else
              {
                c = c - 10;
                count_2 ++;
              }
          }
          c = c + 48 ;
          append(stack_4,newnode(c));
          for (int i = 0 ; i < count ; i++) // 곱하는 앞수 자릿수가 일의자리가 아닌 십의자리 백의자리일떄,
          {
            insertAt(stack_4,0,newnode('0'));
          }
        reverse(stack_4,stack_5); //reverse한 값을 stack_5에 넣어줌
        delete_all(stack_4);
        append(stack_5,newnode(' '));  // 숫자 띄어쓰기
        while(1) // stack_3의 값을 stack_5(후위표기법) 에 저장, stack_3은 답을 저장하는 DLL
        {
          append(stack_5,newnode(curr_3-> val));
          if(curr_3 -> next == NULL)
          {
            break;
          }
          curr_3 = curr_3 -> next;
        }
          append(stack_5,newnode(' '));// 숫자 띄어쓰기 숫자 띄어쓰기
          append(stack_5,newnode('+'));// 숫자 띄어쓰기 숫자 띄어쓰기 +
          delete_all(stack_3); // stack_3의 값을 stack_5에 넣어주었으므로 비워줌
          cal(stack_5,stack_3); // 후위표기법으로 바뀐 stack_4을 전환한 식을 계산해주고 stack_3에 저장
          delete_all(stack_5); //stack_5은 끝났으므로 비워줌
          reverse(stack_3,stack_4); // stack_3 reverse를 해주기 위한 stack_4
          delete_all(stack_3); //stack_3에 계산된 값을 넣어주기위해서 비워줌
          copy_1(stack_3,stack_4); // reverse한 값을 다시 stack_3에 넣어줌
          delete_all(stack_4); // stack_4를 비워줌

          int swh_1 = 0 ; // curr_1(뒷수)을 맨뒤로 초기화 시켜주었다는 스위치, 앞수가 끝까지 연산되었기때문
          if( curr_1 ->prev == NULL)
          {
            count_1 ++; // 뒷수가 옮겨졌으니 0의 자릿수가 하나더 들어남
            count = count_1;

            if(curr_2 -> prev == NULL)
            {
              break; // 최종적으로 while을 나가는 식,즉 * 연산이 끝남
            }
            curr_2 = curr_2 -> prev; // 일의자리 다음에 십의자리를 더함
            while(1) //curr_1을 맨뒤로 초기화시켜줌
            {
              swh_1 = 1; // curr_1을 맨뒤로 초기화 시켜주었다는 스위치
              if(curr_1 -> next == NULL) break;;
              curr_1 = curr_1 -> next;
              if( c > 0 ) count_2 = count_2 * 10; // 56*67예제처리,넘어가는수가 있을때 뒷수의 연산이 끝났을떄
            }
          }
          if ( swh_1 != 1) // curr_1을 맨뒤로 초기화시켜주었기 때문에 할필요가없을때 를 위함.
          {
            curr_1 = curr_1 ->prev;
            count++;
            swh_1 = 0;
          }
      }  // 더하기 계산부분 끝남
// 끝.
      // 자릿숫커지는 경우 ex 55*3 = 165  여기에서의 1을 표현해주기 위함
      if (count_2 > 0)
      {

        count_2 = count_2 + 48;
        insertAt(stack_3,0,newnode(count_2));
      }
      int a = stack_1 ->size_1; // 소수점의 갯수
      if(a  > 0) // 마지막으로 소수점 삽입
      {
        int count = 1 ; // curr_3의 사이즈
        Node *curr_3 = stack_3->head ;
        while(1)
        {
          if (curr_3 -> next == NULL) break;
          curr_3 = curr_3 ->next;
          count++;
        }
        a = a*2; //소수점이 있을경우 , stack_1소수점의 수와 stack_2가 곱해지기 때문에 *2를 해준거임. ex) 1.1 * 1.1 = 1.21 > 소수점 자릿수 늘어남.
        insertAt(stack_3,count-a,newnode('.'));
      }
      if( stack_1 ->swh == 1) insertAt(stack_3,0,newnode('-')); //앞수가 -얐을경우
      while(1) // 필요없는 0의 자릿수를 지워주기위함.
      {
        if(stack_3->head -> val =='0' && stack_3->head->next == NULL) break; // 답인 0 인 경우를 위함
        if(stack_3 -> head -> val != '0') break;
        if(stack_3 -> head -> val == '0' && stack_3 -> head -> next -> val != '.')
        {
          deleteAt(stack_3,0);
        }
      }
      delete_all(stack_4);
      reverse(stack_3,stack_4); // 최종적으로 나오는 값이 reverse된 값이여야 하기때문에 reverse를 해줌.
      delete_all(stack_3);
      copy_1(stack_3,stack_4);
      delete_all(stack_4);
      break;
    }
    default :
      break;
  }// switch문에 걸림
}
void getnumber(DLL *list){
  int count = 0 ; //몇번 돌았나, -3+5 예제 처리를 위함.
  char temp;
  while(1){
    temp = getchar();
    if(temp == '\n') break;
    if ( temp == '+'|| temp == '-'|| temp == '*'|| temp == '/' )
    {
      if (count == 0) // 맨 앞에 부호가 들어올 경우.
      {   //기존에서 추가한 부분
          if ( temp == '+') {
            temp = getchar(); // 다음걸로 넘어감
            count ++;
          }
          if ( temp == '-') {
            list-> swh = 2;
            temp = getchar(); // 스위치 표시해주고 넘어감.
            count ++;
          }
      		if ( temp == '*') {
      			printf("ERROR: Worng Input !");
            exit(1);
      		}
      }
      append(list,newnode(temp));
      count ++;
    }
    else if (temp == '.' || temp =='('|| temp ==')') append(list,newnode(temp)); // . ( ) 일 경우.
    else if ( isblank(temp) ) count ++; // 빈칸일 경우
    else if ( isalpha(temp) ) { // 알파벳 일경우 예외처리
      printf(" Wrong Input ! ");
      exit(1);
    }
    else if ( isdigit(temp) ){ // 정수일 경우
      append(list,newnode(temp));
      count ++;
    }
    else { // 나머지
      printf(" Wrong Input ! ");
      exit(1);
    }
  }
}
 int GreaterOpr(char opr1, char opr2) // 연산자의 우선순위를 결정하는 함수
{
	if(opr1 == '*') {
		if (opr2 == '+' || opr2 == '-')
			return TRUE;
		else if (opr2 == '*')
			return TRUE;
		else if (opr2 == '(')
			return FALSE;
 	}
	else if (opr1 == '+' || opr1 == '-'){
		if (opr2 == '+' || opr2 == '-')
			return TRUE;
		else if(opr2 == '*'||opr2 == '(')
			return FALSE;
	}
	else if (opr1 == '(') {
		return FALSE;
	}
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
   list_1->i+=1;
   append(list_1,newnode(' '));
   break;
   }
   else{
     append(list_1, newnode(cur->val));
   list_1->i+=1;
   append(list_1,newnode(' '));
     cur = cur->prev;
   }
 }
 free(stack);
 stack = newDLL();
}
void G_POP(DLL *stack, DLL*list_1)
{
	Node *end = stack -> head;
	while (end -> next != NULL)
		end = end -> next;
	while (end -> val != '(') {
		append(list_1,newnode(end->val));
		list_1->i+=1;
		if (end->prev->val != '(')
			append(list_1,newnode(' '));
		end = end -> prev;
		end -> next = NULL;
		stack->ssize -= 1;
	}
	if (stack -> ssize == 1) {
		free(stack);
		stack = newDLL();
	}
	else {
		end = end -> prev;
		end -> next = NULL;
		stack -> ssize -= 1;
	}
}
void PushOrPop(DLL *stack, char input_opr, DLL *list_1)
{
 while (1) {
   int ssize = stack->ssize;
   if (ssize == 0) {
     stack_append(stack,newnode(input_opr));
     break;
   }
   else {
     Node *bigyo = stack->head;
     while (bigyo->next != NULL)
       bigyo = bigyo -> next;
     if (GreaterOpr(bigyo->val,input_opr) == FALSE){
       stack_append(stack,newnode(input_opr));
       break;
     }
     else {
       if (ssize == 1) {
         POP_all(stack,list_1);
         stack_append(stack,newnode(input_opr));
         break;
       }
       else if (ssize >= 2) {
         append(list_1,newnode(bigyo->val));
         list_1->i+=1;
         append(list_1,newnode(' '));
         bigyo=bigyo->prev;
         bigyo->next = NULL;
         stack ->ssize -= 1;
       }
     }
   }
 }
}
void postfix(DLL *list,DLL *list_1){
  DLL *stack = newDLL(); // 연산자 담아둘 스택
  Node *curr = list -> head ;
  while(1){
    if( curr -> next == NULL){
	  if (isdigit(curr->val)) { //마지막숫자 일 경우
    	  append(list_1,newnode(curr->val));
		    append(list_1,newnode(' '));
     	  break;
	  }
	  else if (curr->val == ')') {
		  Node *tail1 = list_1->head;
		  while (tail1->next != NULL)
			  tail1 = tail1 -> next;
		  if (tail1 -> val != ' ')
		  	append(list_1, newnode(' '));
		    G_POP(stack,list_1);
		    Node *tail2 = list_1->head;
		  while (tail2 -> next != NULL)
			  tail2 = tail2 -> next;
		  if (tail2 -> val != ' ')
		  	append(list_1,newnode(' ')); // 공백 연속 방지.
		  break;
	  }
  }
  else if( isdigit(curr->val) || curr->val == '.'){ // 숫자나 .이나오면 그냥 다 때려박음
      append(list_1,newnode(curr->val));
      if ( curr -> next == NULL) break;
      curr = curr -> next;
    }
	else if (curr -> val == ')') {
		Node *tail1 = list_1->head;
		while (tail1 -> next != NULL)
			tail1 = tail1 -> next;
		if (tail1 -> val != ' ')
			append(list_1, newnode(' ')); //공백 이쁘게.
		  G_POP(stack,list_1);
		curr = curr -> next;
	}
  else{//연산자들
	  if (curr->val == '(') {
		  PushOrPop(stack, curr->val, list_1);
		  curr = curr -> next;
		  if (curr -> val == '-') {
			  append(list_1,newnode('-'));
			  curr = curr -> next;
		  }
	  }
	  else {
		  Node *tail = list_1->head;
		  while (tail -> next != NULL)
			  tail = tail -> next;
		  if (tail -> val != ' ')
		  	append(list_1,newnode(' '));
    	  PushOrPop(stack, curr->val, list_1);
		  curr = curr -> next;
	  }
	}
  }
  if(stack->ssize >= 1) POP_all(stack,list_1);

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
void stack_append(DLL *list, Node *newnode) {
	Node *curr;
	if (list -> head == NULL)
		list -> head = newnode;
	else {
		curr = list->head;
		while (curr -> next != NULL)
			curr = curr -> next;
		newnode->prev = curr;
		curr->next = newnode;
	}
	list->ssize = list->ssize + 1;
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
      list->head->next->prev = list->head->prev;
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