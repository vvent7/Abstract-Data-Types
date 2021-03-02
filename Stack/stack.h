#ifndef STACK_H
#define STACK_H

/* Stack's Nodes definition */
typedef struct StackNode{
  void *data;
  struct StackNode *next;

   void (*free)(struct StackNode *this, void (*freeData)(void *data), unsigned short freeNext);
} StackNode;

/* Stack's definition */
typedef struct Stack{
  size_t size;
  StackNode *topNd;

  void (*clear)(struct Stack *this, void (*freeData)(void *data));
  void (*free)(struct Stack *this, void (*freeData)(void *data));
  unsigned short (*empty)(struct Stack *this);
  void* (*top)(struct Stack *this);
  void (*push)(struct Stack *this, void *data);
  void* (*pop)(struct Stack *this, void (*freeData)(void *data));
  void (*print)(struct Stack *this, void (*printData)(void *data), char *sep);
} Stack;

/* Create new StackNode */
StackNode* stack_node_new(void *data, StackNode *next);

/* Free StackNode.
 * freeData: Function to free data. Case NULL -> doesn't free StackNode's data
 * freeNext: (true(1)/false(0)) -> (frees/doesn't free) the next StackNode */
void stack_node_free(StackNode *node, void (*freeData)(void *data), unsigned short freeNext);

/* Create new Stack */
Stack* stack_new();

/* Clear entire Stack (remove Stack's StNodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free StackNode's data */
void stack_clear(Stack *st, void (*freeData)(void *data));

/* Free entire Stack (remove Stack and its StNodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free StackNode's data */
void stack_free(Stack *st, void (*freeData)(void *data));

/* Verify whether the Stack is empty */
unsigned short stack_empty(Stack *st);

/* Returns the element on Stack top */
void* stack_top(Stack *st);

/* Push data on Stack top */
void stack_push(Stack *st, void *data);

/* Remove the data on Stack top
 * freeData: Function to free data.
 *   - Case not NULL -> free StackNode's data and returns NULL
 *   - Case NULL -> doesn't free StackNode's data and returns the data */
void* stack_pop(Stack *st, void (*freeData)(void *data));

/* Print entire Stack
 * printData -> function to print Stack's data
 * sep -> Separator between Stack's data */
void stack_print(Stack *st, void (*printData)(void *data), char *sep);

#endif