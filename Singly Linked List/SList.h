#ifndef SLIST_H
#define SLIST_H

#include<stdbool.h>

typedef struct SNode{
  void *data;
  struct SNode *next;
} SNode;

typedef struct{
  SNode *begin, *end;
  int size;
} SList;

//Create new SNode
SNode* SNodeCreate(void *data, SNode *next);

/* Delete SNode.
  freeData: true->free SNode's data, false->don't free SNode's data
  delNext: true->free next SNodes, false->don't free next SNodes */
void SNodeFree(SNode *node, bool freeData, bool freeNext);

//Create new SList
SList* SListCreate();

/*Free entire SList (remove SList and its SNodes from memory)
  freeData: true->free SNode's data, false->don't free SNode's data */
void SListFree(SList *ls, bool freeData);

/*Clear entire SList (remove SList's SNodes from memory)
  freeData: true->free SNode's data, false->don't free SNode's data */
void SListClear(SList *ls, bool freeData);

//Verify whether the list is empty
bool SListIsEmpty(SList *ls);

//Insert data at specific SList's index
bool SListInsertIndex(SList *ls, void *data, int index);

//Insert data at SList's begin
bool SListInsertBegin(SList *ls, void *data);

//Insert data at SList's end
bool SListInsertEnd(SList *ls, void *data);

//Get SList's data at specific index
void* SListGet(SList *ls, int index);

#endif