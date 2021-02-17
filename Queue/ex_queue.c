#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "queue.h"

#define TAM 10
#define LIM 101

void printData(void *x){
  printf("%d", *((int*)x));
}

void freeData(void *x){
  printf("Removing from memory.\n");
  free(x);
}

int main(){
  Queue *q = queue_new();
  int *a[TAM], i, *aux, half = TAM/2;

  srand(time(NULL));

  printf("Inserting in the Queue:\n");
  for(i=0;i<TAM;i++){
    a[i] = malloc(sizeof(int));
    *(a[i]) = rand() % LIM;
    printf("%d inserted\n", *(a[i]));
    q->push(q, a[i]);
  }

  printf("\n"); q->print(q, printData, " ");

  printf("\n\nRemove without erasing from memory:\n");
  for(i=0;i<half;i++){
    if((aux = q->pop(q, NULL))!=NULL) printf("Pop return: %d\n", *aux);
    else printf("Pop didn't return anything.\n");
  }

  printf("\n"); q->print(q, printData, " ");

  printf("\n\nRemove erasing from memory:\n");
  for(i=0;i<half;i++){
    if((aux = q->pop(q, freeData))!=NULL) printf("Pop return: %d\n", *aux);
    else printf("Pop didn't return anything.\n");
  }

  printf("\n"); q->print(q, printData, " "); printf("\n");

  return 0;
}