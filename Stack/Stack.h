#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

/*OBS:
  StN / StNode -> Stack Node
  St -> Stack */

//Stack's Nodes definition
typedef struct StNode{
  void *data;
  struct StNode *next;
} StNode;

//Stack's definition
typedef struct{
  StNode *top;
  int size;
} Stack;

//Create new StNode
StNode* StN_Create(void *data, StNode *next);

/* Free StNode.
  freeData: Function to free data. Case NULL -> doesn't free StNode's data
  delNext: (true/false) -> (frees/doesn't free) the next StNode*/
void StN_Free(StNode *node, void (*freeData)(void *data), bool freeNext);

//Create new Stack
Stack* St_Create();

/*Clear entire Stack (remove Stack's StNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free StNode's data*/
void St_Clear(Stack *st, void (*freeData)(void *data));

/*Free entire Stack (remove Stack and its StNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free StNode's data*/
void St_Free(Stack *st, void (*freeData)(void *data));

//Verify whether the Stack is empty
bool St_IsEmpty(Stack *st);

//Returns the element on Stack top
void* St_Top(Stack *st);

//Push data on Stack top
void St_Push(Stack *st, void *data);

/*Remove the data on Stack top
  freeData: Function to free data.
    - Case not NULL -> free StNode's data and returns NULL
    - Case NULL -> doesn't free StNode's data and returns the data*/
void* St_Pop(Stack *st, void (*freeData)(void *data));

/*Print entire Stack
  printData -> function to print Stack's data
  sep -> Separator between Stack's data */
void St_Print(Stack *st, void (*printData)(void *data), char *sep);

#endif