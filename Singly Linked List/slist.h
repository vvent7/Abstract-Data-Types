#ifndef SLIST_H
#define SLIST_H

/* Definition of SinglyList nodes */
typedef struct SinglyNode{
  void *data;
  struct SinglyNode *next;
} SinglyNode;

/* SinglyList definition */
typedef struct{
  SinglyNode *begin, *end;
  size_t size;
} SinglyList;

#ifndef _BOOLEAN
#define _BOOLEAN
  /* _boolean (true/false) definition */
  typedef enum{false=0, true} _boolean;
#endif

/* Create new SinglyNode */
SinglyNode* singly_node_new(void *data, SinglyNode *next);

/* Free SinglyNode.
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode's data
 * delNext: true->free next Nodes, false->doesn't free next Nodes */
void singly_node_free(SinglyNode *node, void (*freeData)(void *data), _boolean freeNext);

/* Create new SinglyList */
SinglyList* singly_list_new();

/* Clear entire SinglyList (remove SinglyList Nodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode's data */
void singly_list_clear(SinglyList *ls, void (*freeData)(void *data));

/* Free entire SinglyList (remove SinglyList and its Nodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode's data */
void singly_list_free(SinglyList *ls, void (*freeData)(void *data));

/* Verify whether the list is empty */
_boolean singly_list_empty(SinglyList *ls);

/* Get previous node to a specific index in SinglyList. Complexity: O(index-1) */
SinglyNode* singly_list_pre_node(SinglyList *ls, size_t index);

/* Get SinglyList data at specific index. Complexity: O(index) */
void* singly_list_at(SinglyList *ls, size_t index);

/* Insert data at specific SinglyList index */
SinglyNode* singly_list_insert(SinglyList *ls, void *data, size_t index);

/* Insert data at SinglyList begin */
SinglyNode* singly_list_push_front(SinglyList *ls, void *data);

/* Insert data at SinglyList end */
SinglyNode* singly_list_push_back(SinglyList *ls, void *data);

/* Delete node at specific SinglyList index
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode's data */
void* singly_list_erase(SinglyList *ls, size_t index, void (*freeData)(void *data));

/* Delete node at SinglyList begin
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode's data */
void* singly_list_pop_front(SinglyList *ls, void (*freeData)(void *data));

/* Delete node at SinglyList end
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode's data */
void* singly_list_pop_back(SinglyList *ls, void (*freeData)(void *data));

/* Print entire SinglyList
 * printData -> function to print SinglyList data
 * sep -> Separator between SinglyList data */
void singly_list_print(SinglyList *ls, void (*printData)(void *data), char *sep);

#endif