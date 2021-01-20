#ifndef SLIST_H
#define SLIST_H

#include<stdbool.h>

/*OBS:
  SN / SlNode -> Singly Node
  SL / SList -> Singly Linked List */

//SList's Nodes definition
typedef struct SlNode{
  void *data;
  struct SlNode *next;
} SlNode;

//SList's definition
typedef struct{
  SlNode *begin, *end;
  int size;
} SList;

//Create new SlNode
SlNode* sln_new(void *data, SlNode *next);

/* Free SlNode.
  freeData: Function to free data. Case NULL -> doesn't free SlNode's data
  delNext: true->free next SNodes, false->doesn't free next SNodes */
void sln_free(SlNode *node, void (*freeData)(void *data), bool freeNext);

//Create new SList
SList* sl_new();

/*Clear entire SList (remove SList's SNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free SlNode's data*/
void sl_clear(SList *ls, void (*freeData)(void *data));

/*Free entire SList (remove SList and its SNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free SlNode's data*/
void sl_free(SList *ls, void (*freeData)(void *data));

//Verify whether the list is empty
bool sl_is_empty(SList *ls);

//Get previous node to a specific index in SList. Complexity: O(index-1)
SlNode* sl_get_pre_node(SList *ls, int index);

//Get SList's data at specific index. Complexity: O(index)
void* sl_get(SList *ls, int index);

//Insert data at specific SList's index
bool sl_insert_at(SList *ls, void *data, int index);

//Insert data at SList's begin
bool sl_insert_begin(SList *ls, void *data);

//Insert data at SList's end
bool sl_insert_end(SList *ls, void *data);

/*Delete node at specific SList's index
  freeData: Function to free data. Case NULL -> doesn't free SlNode's data*/
void* sl_delete_at(SList *ls, int index, void (*freeData)(void *data));

/*Delete node at SList's begin
  freeData: Function to free data. Case NULL -> doesn't free SlNode's data*/
void* sl_delete_begin(SList *ls, void (*freeData)(void *data));

/*Delete node at SList's end
  freeData: Function to free data. Case NULL -> doesn't free SlNode's data*/
void* sl_delete_end(SList *ls, void (*freeData)(void *data));

/*Print entire SList
  printData -> function to print SList's data
  sep -> Separator between SList's data */
void sl_print(SList *ls, void (*printData)(void *data), char *sep);

#endif