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
QNode* qn_new(void *data, QNode *next);

/* Frees QNode.
  freeData: Function to free data. Case NULL -> doesn't free QNode's data
  delNext: (true/false) -> (frees/doesn't free) the next QNode*/
void qn_free(QNode *node, void (*freeData)(void *data), bool freeNext);

//Creates new Queue
Queue* q_new();

/*Clears entire Queue (remove Queue's QNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free QNode's data*/
void q_clear(Queue *q, void (*freeData)(void *data));

/*Frees entire Queue (remove Queue and its QNodes from memory)
  freeData: Function to free data. Case NULL -> doesn't free QNode's data*/
void q_free(Queue *q, void (*freeData)(void *data));

//Verifies whether the Queue is empty
bool q_is_empty(Queue *q);

//Returns the element on Queue front
void* q_front(Queue *q);

//Returns the element on Queue back
void* q_back(Queue *q);

//Pushes data in the Queue
void q_push(Queue *q, void *data);

/*Removes the data on Queue front
  freeData: Function to free data.
    - Case not NULL -> free QNode's data and returns NULL
    - Case NULL -> doesn't free QNode's data and returns the data*/
void* q_pop(Queue *q, void (*freeData)(void *data));

/*Prints entire Queue
  printData -> function to print Queue's data
  sep -> Separator between Queue's data */
void q_print(Queue *q, void (*printData)(void *data), char *sep);

#endif