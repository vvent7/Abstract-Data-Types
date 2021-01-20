#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

StNode* stn_new(void *data, StNode *next){
  StNode *node = (StNode*) malloc(sizeof(StNode));
  node->data = data; node->next = next;
  return node;
}

void stn_free(StNode *node, void (*freeData)(void *data), bool freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) stn_free(node->next, freeData, freeNext);
  free(node);
}

Stack* st_new(){
  Stack *st = (Stack*) malloc(sizeof(Stack));
  st->top = NULL; st->size = 0;
  return st;
}

void st_clear(Stack *st, void (*freeData)(void *data)){
  if(st==NULL) return;
  stn_free(st->top, freeData, true);
  st->top = NULL; st->size = 0;
}

void st_free(Stack *st, void (*freeData)(void *data)){
  if(st==NULL) return;
  st_clear(st, freeData);
  free(st);
}

bool st_is_empty(Stack *st){
  return (st==NULL || st->size==0);
}

void* st_top(Stack *st){
  return st_is_empty(st) ? NULL : st->top->data;
}

void st_push(Stack *st, void *data){
  if(st==NULL) return;

  StNode *node = stn_new(data, st->top);
  st->top = node; st->size++;
}

void* st_pop(Stack *st, void (*freeData)(void *data)){
  if(st_is_empty(st)) return NULL;

  StNode *node = st->top;
  void *d = node->data;

  st->top = node->next; st->size--;
  stn_free(node, freeData, false);

  return freeData ? NULL : d;
}

void st_print(Stack *st, void (*printData)(void *data), char *sep){
  if(st==NULL || printData==NULL) return;
  if(st->size==0){
    printf("Empty Stack"); return;
  }

  StNode *node;
  for(node = st->top;node!=NULL;node=node->next){
    if(node!=st->top) printf("%s", sep);
    printData(node->data);
  }
}