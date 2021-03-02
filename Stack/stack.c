#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

StackNode* stack_node_new(void *data, StackNode *next){
  StackNode *node = (StackNode*) malloc(sizeof(StackNode));
  node->data = data; node->next = next;
  node->free = stack_node_free;
  return node;
}

void stack_node_free(StackNode *node, void (*freeData)(void *data), unsigned short freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) stack_node_free(node->next, freeData, freeNext);
  free(node);
}

Stack* stack_new(){
  Stack *st = (Stack*) malloc(sizeof(Stack));
  st->topNd = NULL; st->size = 0;

  st->clear = stack_clear;
  st->free = stack_free;
  st->empty = stack_empty;
  st->top = stack_top;
  st->push = stack_push;
  st->pop = stack_pop;
  st->print = stack_print;

  return st;
}

void stack_clear(Stack *st, void (*freeData)(void *data)){
  if(st==NULL) return;
  stack_node_free(st->topNd, freeData, 1);
  st->topNd = NULL; st->size = 0;
}

void stack_free(Stack *st, void (*freeData)(void *data)){
  if(st==NULL) return;
  stack_clear(st, freeData);
  free(st);
}

unsigned short stack_empty(Stack *st){
  return (st==NULL || st->size==0);
}

void* stack_top(Stack *st){
  return stack_empty(st) ? NULL : st->topNd->data;
}

void stack_push(Stack *st, void *data){
  StackNode *node;

  if(st==NULL) return;

  node = stack_node_new(data, st->topNd);
  st->topNd = node; st->size++;
}

void* stack_pop(Stack *st, void (*freeData)(void *data)){
  StackNode *node;
  void *d;

  if(stack_empty(st)) return NULL;

  node = st->topNd;
  d = node->data;

  st->topNd = node->next; st->size--;
  stack_node_free(node, freeData, 0);

  return freeData ? NULL : d;
}

void stack_print(Stack *st, void (*printData)(void *data), char *sep){
  StackNode *node;

  if(st==NULL || printData==NULL) return;
  if(st->size==0){
    printf("Empty Stack"); return;
  }

  for(node = st->topNd;node!=NULL;node=node->next){
    if(node!=st->topNd) printf("%s", sep);
    printData(node->data);
  }
}