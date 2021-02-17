#ifndef QUEUE_H
#define QUEUE_H

/* Queue Nodes definition */
typedef struct QueueNode{
  void *data;
  struct QueueNode *next;
  
  void (*free)(struct QueueNode *this, void (*freeData)(void *data), unsigned short freeNext);
} QueueNode;

/* Queue definition */
typedef struct Queue{
  QueueNode *frontNd, *backNd;
  size_t size;

  void (*clear)(struct Queue *this, void (*freeData)(void *data));
  void (*free)(struct Queue *this, void (*freeData)(void *data));
  unsigned short (*empty)(struct Queue *this);
  void* (*front)(struct Queue *this);
  void* (*back)(struct Queue *this);
  void (*push)(struct Queue *this, void *data);
  void* (*pop)(struct Queue *this, void (*freeData)(void *data));
  void (*print)(struct Queue *this, void (*printData)(void *data), char *sep);
} Queue;

/* Creates new QueueNode */
QueueNode* queue_node_new(void *data, QueueNode *next);

/* Frees QueueNode.
 * freeData: Function to free data. Case NULL -> doesn't free QueueNode's data
 * freeNext: (true(1)/false(0)) -> (frees/doesn't free) the next QueueNode */
void _queue_node_free(QueueNode *node, void (*freeData)(void *data), unsigned short freeNext);

/* Creates new Queue */
Queue* queue_new();

/* Clears entire Queue (remove Queue's QNodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free QueueNode's data */
void _queue_clear(Queue *q, void (*freeData)(void *data));

/* Frees entire Queue (remove Queue and its QNodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free QueueNode's data */
void _queue_free(Queue *q, void (*freeData)(void *data));

/* Verifies whether the Queue is empty */
unsigned short _queue_empty(Queue *q);

/* Returns the element on Queue front */
void* _queue_front(Queue *q);

/* Returns the element on Queue back */
void* _queue_back(Queue *q);

/* Pushes data in the Queue */
void _queue_push(Queue *q, void *data);

/* Removes the data on Queue front
 * freeData: Function to free data.
 *   - Case not NULL -> free QueueNode's data and returns NULL
 *   - Case NULL -> doesn't free QueueNode's data and returns the data */
void* _queue_pop(Queue *q, void (*freeData)(void *data));

/* Prints entire Queue
 * printData -> function to print Queue's data
 * sep -> Separator between Queue's data */
void _queue_print(Queue *q, void (*printData)(void *data), char *sep);

#endif