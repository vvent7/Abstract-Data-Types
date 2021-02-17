#ifndef SLIST_H
#define SLIST_H

#ifndef MIN
  #define MIN(x, y) (x<y ? x : y)
#endif

/* Definition of SinglyList nodes */
typedef struct SinglyNode{
  void *data;
  struct SinglyNode *next;

  void (*free)(struct SinglyNode *this, void (*freeData)(void *data), unsigned short freeNext);
} SinglyNode;

/* SinglyList definition */
typedef struct SinglyList{
  size_t size;
  SinglyNode *first, *last;

  unsigned short (*empty)(struct SinglyList *this);
  void* (*front)(struct SinglyList *this);
  void* (*back)(struct SinglyList *this);
  SinglyNode* (*push_front)(struct SinglyList *this, void *data);
  void (*pop_front)(struct SinglyList *this, void (*freeData)(void *data));
  SinglyNode* (*push_back)(struct SinglyList *this, void *data);
  void (*pop_back)(struct SinglyList *this, void (*freeData)(void *data));
  SinglyNode* (*pre_node)(struct SinglyList *this, size_t index);
  SinglyNode* (*at)(struct SinglyList *this, size_t index);
  void* (*get_data)(struct SinglyList *this, size_t index);
  SinglyNode* (*insert)(struct SinglyList *this, void *data, size_t index);
  SinglyNode* (*erase)(struct SinglyList *this, size_t index, void (*freeData)(void *data));
  SinglyNode* (*erase_n)(struct SinglyList *this, size_t index, size_t n, void (*freeData)(void *data));
  void (*clear)(struct SinglyList *this, void (*freeData)(void *data));
  void (*free)(struct SinglyList *this, void (*freeData)(void *data));
  void (*print)(struct SinglyList *this, void (*printData)(void *data), char *sep);
} SinglyList;

/* OBS: for all functions with 'freeData' function:
 * freeData: Function to free data. Case NULL -> doesn't free SinglyNode data */

/* Create new SinglyNode */
SinglyNode* snode_new(void *data, SinglyNode *next);

/* Free SinglyNode.
 * freeNext: true(1)->free next Nodes, false(0)->doesn't free next Nodes */
void _snode_free(SinglyNode *node, void (*freeData)(void *data), unsigned short freeNext);

/* Create new SinglyList */
SinglyList* slist_new();

/* Verify whether the list is empty */
unsigned short _slist_empty(SinglyList *ls);

/* Returns first element */
void* _slist_front(SinglyList *ls);

/* Returns last element */
void* _slist_back(SinglyList *ls);

/* Insert data at SinglyList begin
 * Returns: SinglyNode created */
SinglyNode* _slist_push_front(SinglyList *ls, void *data);

/* Delete node at SinglyList begin */
void _slist_pop_front(SinglyList *ls, void (*freeData)(void *data));

/* Insert data at SinglyList end
 * Returns: SinglyNode created */
SinglyNode* _slist_push_back(SinglyList *ls, void *data);

/* Delete node at SinglyList end */
void _slist_pop_back(SinglyList *ls, void (*freeData)(void *data));

/* Returns previous node to a specific index in SinglyList. Complexity: O(index-1) */
SinglyNode* _slist_pre_node(SinglyList *ls, size_t index);

/* Returns SinglyNode at specific index. Complexity: O(index) */
SinglyNode* _slist_at(SinglyList *ls, size_t index);

/* Returns SinglyList data at specific index. Complexity: O(index) */
void* _slist_get_data(struct SinglyList *this, size_t index);

/* Insert data at specific SinglyList index
 * Returns: SinglyNode created */
SinglyNode* _slist_insert(SinglyList *ls, void *data, size_t index);

/* Delete node at specific SinglyList index
 * Returns: Element that followed the element erased */
SinglyNode* _slist_erase(SinglyList *ls, size_t index, void (*freeData)(void *data));

/* Delete N nodes starting at specific SinglyList index
 * Returns: Element that followed the last element erased */
SinglyNode* _slist_erase_n(struct SinglyList *this, size_t index, size_t n, void (*freeData)(void *data));

/* Clear entire SinglyList (remove SinglyList Nodes from memory) */
void _slist_clear(SinglyList *ls, void (*freeData)(void *data));

/* Free entire SinglyList (remove SinglyList and its Nodes from memory) */
void _slist_free(SinglyList *ls, void (*freeData)(void *data));

/* Print entire SinglyList
 * printData -> function to print SinglyList data
 * sep -> Separator between SinglyList data */
void _slist_print(SinglyList *ls, void (*printData)(void *data), char *sep);

#endif