#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "slist.h"

#define TAM 15
#define LIM 101

void printData(void *x){
  if(x==NULL) printf("NULL");
  else printf("%d", *((int*)x));
}

void freeData(void *x){
  printf("Removing %d from memory.\n", *((int*)x));
  free(x);
}

int main(){
  SinglyList *ls = slist_new();
  SinglyNode *node;
  int *a[TAM];
  size_t i;

  srand(time(NULL));

  printf("=====Inserting in the SinglyList=====\n");
  for(i=0;i<TAM;i++){
    a[i] = malloc(sizeof(int));
    *(a[i]) = rand() % LIM;
    printf("%d inserted\n", *(a[i]));
    ls->push_back(ls, a[i]);
  }
  
  printf("\n");
  for(i=0;i<ls->size;i++){
    if(i!=0) printf(" ");
    printData(ls->get_data(ls, i));
  }

  printf("\n\n=====Removing erasing from memory=====\n");
  node = ls->erase_n(ls, ls->size/4, ls->size/2, freeData);
  printf("Element that followed the last element erased: "); printData(node ? node->data : NULL);
  printf("\nList (Size = %lu): ", ls->size); ls->print(ls, printData, " ");
  printf("\nFront: "); printData(ls->front(ls)); printf("\nBack: "); printData(ls->back(ls));

  printf("\n\n=====Removing without erasing from memory=====\n");
  node = ls->erase_n(ls, ls->size/4, ls->size/2, NULL);
  printf("List (Size = %lu): ", ls->size); ls->print(ls, printData, " ");

  printf("\n\n=====Clearing and erasing from memory=====\n");
  ls->clear(ls, freeData);
  printf("List (Size = %lu): ", ls->size); ls->print(ls, printData, " ");

  if(ls->front(ls) == NULL && ls->back(ls)==NULL && ls->at(ls, 0)==NULL) printf("\nAll cleared\n");
  else printf("\nError when clearing.\n");

  return 0;
}