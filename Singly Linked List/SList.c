#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SList.h"

SNode* SN_Create(void *data, SNode *next){
  SNode *node = (SNode*) malloc(sizeof(SNode));
  node->data = data; node->next = next;
  return node;
}

void SN_Free(SNode *node, bool freeData, bool freeNext){
  if(node==NULL) return;
  
  if(freeData) free(node->data);
  if(freeNext) SN_Free(node->next, freeData, freeNext);
  free(node);
}

SList* SL_Create(){
  SList *ls = (SList*) malloc(sizeof(SList));
  ls->begin = ls->end=NULL; ls->size=0;
  return ls;
}

void SL_Clear(SList *ls, bool freeData){
  if(ls==NULL) return;
  SN_Free(ls->begin, freeData, true);
  ls->begin = ls->end = NULL; ls->size = 0;
}

void SL_Free(SList *ls, bool freeData){
  if(ls==NULL) return;
  SL_Clear(ls, freeData);
  free(ls);
}

bool SL_IsEmpty(SList *ls){
  return ls==NULL ? false : ls->size==0;
}

SNode* SL_GetPreNode(SList *ls, int index){
  if(ls==NULL || index<=0 || index>ls->size) return NULL;

  SNode *aux = ls->begin;
  while(--index>0) aux = aux->next;
  return aux;
}

void* SL_Get(SList *ls, int index){
  if(ls==NULL || index<0 || index>=ls->size) return NULL;

  return SL_GetPreNode(ls, index+1)->data;
}

bool SL_InsertIndex(SList *ls, void *data, int index){
  if(ls==NULL || index<0 || index>ls->size) return false;

  SNode *node;

  if(index==0){
    node = SN_Create(data, ls->begin);
    ls->begin = node;
    if(SL_IsEmpty(ls)) ls->end = node;
  }
  else{
    SNode *aux = SL_GetPreNode(ls, index);
    node = SN_Create(data, aux->next);
    aux->next = node;
    if(aux==ls->end) ls->end = node;
  }

  ls->size++;

  return true;
}

bool SListInsertBegin(SList *ls, void *data){
  return ls==NULL ? false : SL_InsertIndex(ls, data, 0);
}

bool SL_InsertEnd(SList *ls, void *data){
  return ls==NULL ? false : SL_InsertIndex(ls, data, ls->size);
}

bool SL_DeleteIndex(SList *ls, int index, bool freeData){
  if(ls==NULL || SL_IsEmpty(ls) || index<0 || index>=ls->size) return false;

  ls->size--;

  SNode *node;
  
  if(index==0){
    node = ls->begin;
    ls->begin = ls->begin->next;
    if(SL_IsEmpty(ls)) ls->end = NULL;
  }
  else{
    SNode *aux = SL_GetPreNode(ls, index);

    node = aux->next;
    aux->next = node->next;

    if(node==ls->end) ls->end = aux;
  }

  SN_Free(node, freeData, false);

  return true;
}

bool SL_DeleteBegin(SList *ls, bool freeData){
  return ls==NULL ? false : SL_DeleteIndex(ls, 0, freeData);
}

bool SL_DeleteEnd(SList *ls, bool freeData){
  return ls==NULL ? false : SL_DeleteIndex(ls, ls->size, freeData);
}


void SL_Print(SList *ls, void (*printData)(void *data), char *sep){
  if(ls==NULL || printData==NULL) return;
  if(ls->size==0){
    printf("Lista vazia"); return;
  }

  SNode *node;
  for(node = ls->begin;node!=NULL;node=node->next){
    if(node!=ls->begin) printf("%s", sep);
    printData(node->data);
  }
}