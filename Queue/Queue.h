#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/*OBS:
  QN / QNode -> Queue Node
  Q -> Queue */

//Queue's Nodes definition
typedef struct QNode{
  void *data;
  struct QNode *next;
} QNode;

//Queue's definition
typedef struct{
  QNode *front, *back;
  int size;
} Queue;

//Creates new QNode
QNode* QN_Create(void *data, QNode *next);

/* Frees QNode.
  freeData: Function to free data. Case NULL -> doesn't free QNode's data
  delNext: (true/false) -> (frees/doesn't free) the next QNode*/
void QN_Free(QNode *node, void (*freeData)(void *data), bool freeNext);

//Creates new Queue
Queue* Q_Create();

/*Clears entire Queue (remove Queue's QNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free QNode's data*/
void Q_Clear(Queue *q, void (*freeData)(void *data));

/*Frees entire Queue (remove Queue and its QNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free QNode's data*/
void Q_Free(Queue *q, void (*freeData)(void *data));

//Verifies whether the Queue is empty
bool Q_IsEmpty(Queue *q);

//Returns the element on Queue front
void* Q_Front(Queue *q);

//Returns the element on Queue back
void* Q_Back(Queue *q);

//Pushes data in the Queue
void Q_Push(Queue *q, void *data);

/*Removes the data on Queue front
  freeData: Function to free data.
    - Case not NULL -> free QNode's data and returns NULL
    - Case NULL -> doesn't free QNode's data and returns the data*/
void* Q_Pop(Queue *q, void (*freeData)(void *data));

/*Prints entire Queue
  printData -> function to print Queue's data
  sep -> Separator between Queue's data */
void Q_Print(Queue *q, void (*printData)(void *data), char *sep);

#endif