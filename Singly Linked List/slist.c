#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

SinglyNode* singly_node_new(void *data, SinglyNode *next){
  SinglyNode *node = (SinglyNode*) malloc(sizeof(SinglyNode));
  node->data = data; node->next = next;
  return node;
}

void singly_node_free(SinglyNode *node, void (*freeData)(void *data), _boolean freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) singly_node_free(node->next, freeData, freeNext);
  free(node);
}

SinglyList* singly_list_new(){
  SinglyList *ls = (SinglyList*) malloc(sizeof(SinglyList));
  ls->begin = ls->end=NULL; ls->size=0;
  return ls;
}

void singly_list_clear(SinglyList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  singly_node_free(ls->begin, freeData, true);
  ls->begin = ls->end = NULL; ls->size = 0;
}

void singly_list_free(SinglyList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  singly_list_clear(ls, freeData);
  free(ls);
}

_boolean singly_list_empty(SinglyList *ls){
  return (ls==NULL || ls->size==0);
}

SinglyNode* singly_list_pre_node(SinglyList *ls, size_t index){
  SinglyNode *aux;
  
  if(ls==NULL || index==0 || index>ls->size) return NULL;

  aux = ls->begin;
  while(--index>0) aux = aux->next;
  return aux;
}

void* singly_list_at(SinglyList *ls, size_t index){
  if(ls==NULL || index>=ls->size) return NULL;

  return singly_list_pre_node(ls, index+1)->data;
}

SinglyNode* singly_list_insert(SinglyList *ls, void *data, size_t index){
  SinglyNode *node, *aux;

  if(ls==NULL || index>ls->size) return NULL;

  if(index==0){
    node = singly_node_new(data, ls->begin);
    ls->begin = node;
    if(singly_list_empty(ls)) ls->end = node;
  }
  else{
    aux = singly_list_pre_node(ls, index);
    node = singly_node_new(data, aux->next);
    aux->next = node;
    if(aux==ls->end) ls->end = node;
  }

  ls->size++;

  return node;
}

SinglyNode* singly_list_push_front(SinglyList *ls, void *data){
  return ls==NULL ? false : singly_list_insert(ls, data, 0);
}

SinglyNode* singly_list_push_back(SinglyList *ls, void *data){
  return ls==NULL ? false : singly_list_insert(ls, data, ls->size);
}

void* singly_list_erase(SinglyList *ls, size_t index, void (*freeData)(void *data)){
  SinglyNode *node, *aux;
  void *d;

  if(singly_list_empty(ls) || index>=ls->size) return NULL;
  
  if(index==0){
    node = ls->begin;
    ls->begin = ls->begin->next;
    if(ls->size==1) ls->end = NULL;
  }
  else{
    aux = singly_list_pre_node(ls, index);

    node = aux->next;
    aux->next = node->next;

    if(node==ls->end) ls->end = aux;
  }

  d = node->data;
  singly_node_free(node, freeData, false);
  ls->size--;

  return freeData ? NULL : d;
}

void* singly_list_pop_front(SinglyList *ls, void (*freeData)(void *data)){
  return singly_list_empty(ls) ? NULL : singly_list_erase(ls, 0, freeData);
}

void* singly_list_pop_back(SinglyList *ls, void (*freeData)(void *data)){
  return singly_list_empty(ls) ? NULL : singly_list_erase(ls, ls->size-1, freeData);
}

void singly_list_print(SinglyList *ls, void (*printData)(void *data), char *sep){
  SinglyNode *node;

  if(ls==NULL || printData==NULL) return;
  if(singly_list_empty(ls)){
    printf("Empty List"); return;
  }
  
  for(node = ls->begin;node!=NULL;node=node->next){
    if(node!=ls->begin) printf("%s", sep);
    printData(node->data);
  }
}