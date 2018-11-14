#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
   int val;
   struct Node *prev;
   struct Node *next;
} Node;

typedef struct {
   Node *head;
   int size;
} DLL;

Node *newnode(int n)
{
   Node *temp = (Node *)malloc(sizeof(Node));
   temp->val = n;
   temp->prev = NULL;
   temp->next = NULL;
   return temp;
}

DLL *newDLL(){
   DLL *temp = (DLL*)malloc(sizeof(DLL));
   temp->head = NULL;
   temp->size = 0;
   return temp;
}


void append(DLL *list, Node *newnode){
   list->size = list->size + 1; 
   if(list->head != NULL) newnode->prev = list->head; 
   if(list->head != NULL) list->head->next = newnode;
   list->head = newnode; 

}
void insertAt(DLL *list, int index, Node *newnode){
   int idx = list->size-1; 

   if(index > list->size || index < 0) printf("INSERT ERROR : Out of Bound\n");
   else{
      while(idx > index){ 
         if(list->head->prev != NULL) list->head = list->head->prev;
         idx--;
      }
      if(list->head->prev != NULL && list->head->next != NULL){
         list->head->prev->next = newnode;
         newnode->prev = list->head->prev;
         newnode->next = list->head;
         list->head->prev = newnode;
         list->head = newnode;
      } else if (list->head->prev == NULL) {
         list->head->prev = newnode;
         newnode->next = list->head;
         list->head = newnode;
      } else if (list->head->next == NULL) {
         list->head->next = newnode;
         newnode->prev = list->head;
         list->head = newnode;
      } else {
         printf("ERROR\n");
      }
      list->size = list->size + 1;
   }
}

void deleteAt(DLL *list, int index){
   int idx = list->size -1; 
   if(index >idx || index < 0) printf("DELETE ERROR : Out of Bound\n");
   else{
      while(idx > index){
         if(list->head->prev != NULL) list->head = list->head->prev;
         idx--;
      }
      if(list->head->prev != NULL && list->head->next != NULL) {
         list->head->prev->next = list->head->next;
         list->head->next->prev = list->head->prev;
      } else if (list->head->prev == NULL) {
         list->head->next->prev = NULL;
         list->head->next;
      } else if (list->head->next == NULL) {
         list->head->prev->next = NULL;
         list->head->prev;
      } else {
         printf("ERROR\n");
      }
      list->size = list->size - 1;
   }
}
void print_reverse(DLL *list){
   while(1){
      printf("[%d] ", list->head->val); 
      if(list->head->prev != NULL) list->head = list->head->prev;
      else break;
   }
   printf("\n");
}
void print(DLL *list){
   while(1){
      if(list->head->prev != NULL) list-> head = list->head->prev;
      else break;
   }
   while(1){
      printf("[%d] ", list->head->val);
      if(list->head->next != NULL) list->head = list->head->next;
      else break;
   }
   printf("\n");
}

int main() {
   DLL *list = newDLL();
   int i;
   for(i=1; i<6; i++){
      append(list, newnode(i));
   }
   print(list);

   deleteAt(list, -1);
   deleteAt(list, 5);
   deleteAt(list, 0);
   print(list);
   deleteAt(list, 2);
   print(list);
   deleteAt(list, 2);
   print(list);
   insertAt(list, -1, newnode(6));
   insertAt(list, 3, newnode(6));
   insertAt(list, 0, newnode(7));
   print(list);
   insertAt(list, 1, newnode(8));
   print(list);
   insertAt(list, 4, newnode(9));
   print(list);
   print_reverse(list);
   return 0;
}