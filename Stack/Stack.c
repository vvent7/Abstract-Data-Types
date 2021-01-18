#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Stack.h"

StNode* StN_Create(void *data, StNode *next){
  StNode *node = (StNode*) malloc(sizeof(StNode));
  node->data = data; node->next = next;
  return node;
}

void StN_Free(StNode *node, void (*freeData)(void *data), bool freeNext){
  if(node==NULL) return;
  
  if(freeData) free(node->data);
  if(freeNext) StN_Free(node->next, freeData, freeNext);
  free(node);
}

Stack* St_Create(){
  Stack *st = (Stack*) malloc(sizeof(Stack));
  st->size = 0; st->top = NULL;
  return st;
}

void St_Clear(Stack *st, void (*freeData)(void *data)){
  if(st==NULL) return;
  StN_Free(st->top, freeData, true);
  st->top = NULL; st->size = 0;
}

void St_Free(Stack *st, void (*freeData)(void *data)){
  if(st==NULL) return;
  St_Clear(st, freeData);
  free(st);
}

bool St_IsEmpty(Stack *st){
  return (st==NULL || st->size==0);
}

void* St_Top(Stack *st){
  return St_IsEmpty(st) ? NULL : st->top->data;
}

void St_Push(Stack *st, void *data){
  if(st==NULL) return;

  StNode *node = StN_Create(data, st->top);
  st->top = node; st->size++;
}

void* St_Pop(Stack *st, void (*freeData)(void *data)){
  if(St_IsEmpty(st)) return NULL;

  StNode *node = st->top;
  void *d = node->data;

  st->top = node->next; st->size--;
  StN_Free(node, freeData, false);

  return freeData==NULL ? NULL : d;
}

void St_Print(Stack *st, void (*printData)(void *data), char *sep){
  if(st==NULL || printData==NULL) return;
  if(st->size==0){
    printf("Pilha vazia"); return;
  }

  StNode *node;
  for(node = st->top;node!=NULL;node=node->next){
    if(node!=st->top) printf("%s", sep);
    printData(node->data);
  }
}