#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

SinglyNode* snode_new(void *data, SinglyNode *next){
  SinglyNode *node = (SinglyNode*) malloc(sizeof(SinglyNode));
  node->data = data; node->next = next; node->free = snode_free;
  return node;
}

void snode_free(SinglyNode *node, void (*freeData)(void *data), unsigned short freeNext){
  SinglyNode *nextNd;

  if(node==NULL) return;

  do{
    if(freeData) freeData(node->data);
    nextNd = node->next; free(node); node = nextNd;
  }while(node && freeNext); 
}

SinglyList* slist_new(){
  SinglyList *ls = (SinglyList*) malloc(sizeof(SinglyList));
  ls->first = ls->last=NULL; ls->size=0;

  ls->empty = slist_empty;
  ls->front = slist_front;
  ls->back = slist_back;
  ls->push_front = slist_push_front;
  ls->pop_front = slist_pop_front;
  ls->push_back = slist_push_back;
  ls->pop_back = slist_pop_back;
  ls->pre_node = slist_pre_node;
  ls->at = slist_at;
  ls->get_data = slist_get_data;
  ls->insert = slist_insert;
  ls->erase = slist_erase;
  ls->erase_n = slist_erase_n;
  ls->clear = slist_clear;
  ls->free = slist_free;
  ls->print = slist_print;

  return ls;
}

unsigned short slist_empty(SinglyList *ls){
  return (ls==NULL || ls->size==0);
}

void* slist_front(SinglyList *ls){
  return slist_empty(ls) ? NULL : ls->first->data;
}

void* slist_back(SinglyList *ls){
  return slist_empty(ls) ? NULL : ls->last->data;
}

SinglyNode* slist_push_front(SinglyList *ls, void *data){
  return ls==NULL ? NULL : slist_insert(ls, data, 0);
}

void slist_pop_front(SinglyList *ls, void (*freeData)(void *data)){
  if(!slist_empty(ls)) slist_erase(ls, 0, freeData);
}

SinglyNode* slist_push_back(SinglyList *ls, void *data){
  return ls==NULL ? NULL : slist_insert(ls, data, ls->size);
}

void slist_pop_back(SinglyList *ls, void (*freeData)(void *data)){
  if(!slist_empty(ls)) slist_erase(ls, ls->size-1, freeData);
}

SinglyNode* slist_pre_node(SinglyList *ls, size_t index){
  SinglyNode *aux;
  
  if(ls==NULL || index==0 || index>ls->size) return NULL;

  aux = ls->first;
  while(--index>0) aux = aux->next;
  return aux;
}

SinglyNode* slist_at(SinglyList *ls, size_t index){
  return slist_pre_node(ls, index+1);
}

void* slist_get_data(SinglyList *ls, size_t index){
  SinglyNode *sn = ls->at(ls, index);
  return sn ? sn->data : NULL;
}

SinglyNode* slist_insert(SinglyList *ls, void *data, size_t index){
  SinglyNode *node, *aux;

  if(ls==NULL || index>ls->size) return NULL;

  if(index==0){
    node = snode_new(data, ls->first);
    ls->first = node;
    if(slist_empty(ls)) ls->last = node;
  }
  else{
    aux = slist_pre_node(ls, index);
    node = snode_new(data, aux->next);
    aux->next = node;
    if(aux==ls->last) ls->last = node;
  }

  ls->size++;

  return node;
}

SinglyNode* slist_erase_n(struct SinglyList *ls, size_t index, size_t n, void (*freeData)(void *data)){
  SinglyNode *preNd, *node, *nextNd;
  size_t i;

  if(slist_empty(ls) || index>=ls->size) return NULL;

  n = MIN(ls->size-index, n);

  preNd = slist_pre_node(ls, index);
  node = preNd ? preNd->next : ls->first;

  for(i=0;i<n;i++){
    if(freeData) freeData(node->data);
    nextNd = node->next; free(node); node = nextNd;
  }

  if(preNd){
    if((preNd->next = node)==NULL)
      ls->last = preNd;
  }
  else if((ls->first = node)==NULL) ls->last = NULL;

  ls->size-=n;

  return node;
}

SinglyNode* slist_erase(SinglyList *ls, size_t index, void (*freeData)(void *data)){
  return slist_erase_n(ls, index, 1, freeData);
}

void slist_clear(SinglyList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  snode_free(ls->first, freeData, 1);
  ls->first = ls->last = NULL; ls->size = 0;
}

void slist_free(SinglyList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  slist_clear(ls, freeData);
  free(ls);
}

void slist_print(SinglyList *ls, void (*printData)(void *data), char *sep){
  SinglyNode *node;

  if(ls==NULL || printData==NULL) return;
  if(slist_empty(ls)){
    printf("Empty List"); return;
  }
  
  for(node = ls->first;node!=NULL;node=node->next){
    if(node!=ls->first) printf("%s", sep);
    printData(node->data);
  }
}