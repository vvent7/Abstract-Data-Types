#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "slist.h"

SlNode* sln_new(void *data, SlNode *next){
  SlNode *node = (SlNode*) malloc(sizeof(SlNode));
  node->data = data; node->next = next;
  return node;
}

void sln_free(SlNode *node, void (*freeData)(void *data), bool freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) sln_free(node->next, freeData, freeNext);
  free(node);
}

SList* sl_new(){
  SList *ls = (SList*) malloc(sizeof(SList));
  ls->begin = ls->end=NULL; ls->size=0;
  return ls;
}

void sl_clear(SList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  sln_free(ls->begin, freeData, true);
  ls->begin = ls->end = NULL; ls->size = 0;
}

void sl_free(SList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  sl_clear(ls, freeData);
  free(ls);
}

bool sl_is_empty(SList *ls){
  return (ls==NULL || ls->size==0);
}

SlNode* sl_get_pre_node(SList *ls, int index){
  if(ls==NULL || index<=0 || index>ls->size) return NULL;

  SlNode *aux = ls->begin;
  while(--index>0) aux = aux->next;
  return aux;
}

void* sl_get(SList *ls, int index){
  if(ls==NULL || index<0 || index>=ls->size) return NULL;

  return sl_get_pre_node(ls, index+1)->data;
}

bool sl_insert_at(SList *ls, void *data, int index){
  if(ls==NULL || index<0 || index>ls->size) return false;

  SlNode *node;

  if(index==0){
    node = sln_new(data, ls->begin);
    ls->begin = node;
    if(sl_is_empty(ls)) ls->end = node;
  }
  else{
    SlNode *aux = sl_get_pre_node(ls, index);
    node = sln_new(data, aux->next);
    aux->next = node;
    if(aux==ls->end) ls->end = node;
  }

  ls->size++;

  return true;
}

bool sl_insert_begin(SList *ls, void *data){
  return ls==NULL ? false : sl_insert_at(ls, data, 0);
}

bool sl_insert_end(SList *ls, void *data){
  return ls==NULL ? false : sl_insert_at(ls, data, ls->size);
}

void* sl_delete_at(SList *ls, int index, void (*freeData)(void *data)){
  if(sl_is_empty(ls) || index<0 || index>=ls->size) return NULL;

  SlNode *node;
  
  if(index==0){
    node = ls->begin;
    ls->begin = ls->begin->next;
    if(ls->size==1) ls->end = NULL;
  }
  else{
    SlNode *aux = sl_get_pre_node(ls, index);

    node = aux->next;
    aux->next = node->next;

    if(node==ls->end) ls->end = aux;
  }

  void *d = node->data;
  sln_free(node, freeData, false);
  ls->size--;

  return freeData ? NULL : d;
}

void* sl_delete_begin(SList *ls, void (*freeData)(void *data)){
  return sl_is_empty(ls) ? NULL : sl_delete_at(ls, 0, freeData);
}

void* sl_delete_end(SList *ls, void (*freeData)(void *data)){
  return sl_is_empty(ls) ? NULL : sl_delete_at(ls, ls->size-1, freeData);
}

void sl_print(SList *ls, void (*printData)(void *data), char *sep){
  if(ls==NULL || printData==NULL) return;
  if(sl_is_empty(ls)){
    printf("Empty List"); return;
  }

  SlNode *node;
  for(node = ls->begin;node!=NULL;node=node->next){
    if(node!=ls->begin) printf("%s", sep);
    printData(node->data);
  }
}