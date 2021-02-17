#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

SinglyNode* snode_new(void *data, SinglyNode *next){
  SinglyNode *node = (SinglyNode*) malloc(sizeof(SinglyNode));
  node->data = data; node->next = next; node->free = _snode_free;
  return node;
}

void _snode_free(SinglyNode *node, void (*freeData)(void *data), unsigned short freeNext){
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

  ls->empty = _slist_empty;
  ls->front = _slist_front;
  ls->back = _slist_back;
  ls->push_front = _slist_push_front;
  ls->pop_front = _slist_pop_front;
  ls->push_back = _slist_push_back;
  ls->pop_back = _slist_pop_back;
  ls->pre_node = _slist_pre_node;
  ls->at = _slist_at;
  ls->get_data = _slist_get_data;
  ls->insert = _slist_insert;
  ls->erase = _slist_erase;
  ls->erase_n = _slist_erase_n;
  ls->clear = _slist_clear;
  ls->free = _slist_free;
  ls->print = _slist_print;

  return ls;
}

unsigned short _slist_empty(SinglyList *ls){
  return (ls==NULL || ls->size==0);
}

void* _slist_front(SinglyList *ls){
  return _slist_empty(ls) ? NULL : ls->first->data;
}

void* _slist_back(SinglyList *ls){
  return _slist_empty(ls) ? NULL : ls->last->data;
}

SinglyNode* _slist_push_front(SinglyList *ls, void *data){
  return ls==NULL ? NULL : _slist_insert(ls, data, 0);
}

void _slist_pop_front(SinglyList *ls, void (*freeData)(void *data)){
  if(!_slist_empty(ls)) _slist_erase(ls, 0, freeData);
}

SinglyNode* _slist_push_back(SinglyList *ls, void *data){
  return ls==NULL ? NULL : _slist_insert(ls, data, ls->size);
}

void _slist_pop_back(SinglyList *ls, void (*freeData)(void *data)){
  if(!_slist_empty(ls)) _slist_erase(ls, ls->size-1, freeData);
}

SinglyNode* _slist_pre_node(SinglyList *ls, size_t index){
  SinglyNode *aux;
  
  if(ls==NULL || index==0 || index>ls->size) return NULL;

  aux = ls->first;
  while(--index>0) aux = aux->next;
  return aux;
}

SinglyNode* _slist_at(SinglyList *ls, size_t index){
  return _slist_pre_node(ls, index+1);
}

void* _slist_get_data(SinglyList *ls, size_t index){
  SinglyNode *sn = ls->at(ls, index);
  return sn ? sn->data : NULL;
}

SinglyNode* _slist_insert(SinglyList *ls, void *data, size_t index){
  SinglyNode *node, *aux;

  if(ls==NULL || index>ls->size) return NULL;

  if(index==0){
    node = snode_new(data, ls->first);
    ls->first = node;
    if(_slist_empty(ls)) ls->last = node;
  }
  else{
    aux = _slist_pre_node(ls, index);
    node = snode_new(data, aux->next);
    aux->next = node;
    if(aux==ls->last) ls->last = node;
  }

  ls->size++;

  return node;
}

SinglyNode* _slist_erase_n(struct SinglyList *ls, size_t index, size_t n, void (*freeData)(void *data)){
  SinglyNode *preNd, *node, *nextNd;
  size_t i;

  if(_slist_empty(ls) || index>=ls->size) return NULL;

  n = MIN(ls->size-index, n);

  preNd = _slist_pre_node(ls, index);
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

SinglyNode* _slist_erase(SinglyList *ls, size_t index, void (*freeData)(void *data)){
  return _slist_erase_n(ls, index, 1, freeData);
}

void _slist_clear(SinglyList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  _snode_free(ls->first, freeData, 1);
  ls->first = ls->last = NULL; ls->size = 0;
}

void _slist_free(SinglyList *ls, void (*freeData)(void *data)){
  if(ls==NULL) return;
  _slist_clear(ls, freeData);
  free(ls);
}

void _slist_print(SinglyList *ls, void (*printData)(void *data), char *sep){
  SinglyNode *node;

  if(ls==NULL || printData==NULL) return;
  if(_slist_empty(ls)){
    printf("Empty List"); return;
  }
  
  for(node = ls->first;node!=NULL;node=node->next){
    if(node!=ls->first) printf("%s", sep);
    printData(node->data);
  }
}