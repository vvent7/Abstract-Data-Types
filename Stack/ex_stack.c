#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define TAM 15
#define LIM 101

void printData(void *x){
  if(x==NULL) printf("NULL");
  else printf("%d", *((int*)x));
}

void freeData(void *x){
  printf("Removing from memory.\n");
  free(x);
}

int main(){
  Stack *st = stack_new();
  int *a[TAM], i, *aux, half = TAM/2;

  srand(time(NULL));

  printf("Inserting in the Stack:\n");
  for(i=0;i<TAM;i++){
    a[i] = malloc(sizeof(int));
    *(a[i]) = rand() % LIM;
    printf("%d inserted\n", *(a[i]));
    st->push(st, a[i]);
  }

  printf("\n"); st->print(st, printData, " ");

  printf("\n\nRemove without erasing from memory:\n");
  for(i=0;i<half;i++){
    if((aux = st->pop(st, NULL))!=NULL) printf("Pop return: %d\n", *aux);
    else printf("Pop didn't return anything.\n");
  }

  printf("\n"); st->print(st, printData, " ");

  printf("\n\nRemove erasing from memory:\n");
  for(i=half;i<TAM;i++){
    if((aux = st->pop(st, freeData))!=NULL) printf("Pop return: %d\n", *aux);
    else printf("Pop didn't return anything.\n");
  }

  printf("\n"); st->print(st, printData, " "); printf("\n");

  return 0;
}