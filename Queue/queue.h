#ifndef QUEUE_H
#define QUEUE_H

/* Queue's Nodes definition */
typedef struct QueueNode{
  void *data;
  struct QueueNode *next;
} QueueNode;

/* Queue's definition */
typedef struct Queue{
  QueueNode *front, *back;
  size_t size;
} Queue;

/* Bool (true/false) definition */
typedef enum{false=0, true} Bool;

/* Creates new QueueNode */
QueueNode* queue_node_new(void *data, QueueNode *next);

/* Frees QueueNode.
 * freeData: Function to free data. Case NULL -> doesn't free QueueNode's data
 * delNext: (true/false) -> (frees/doesn't free) the next QueueNode */
void queue_node_free(QueueNode *node, void (*freeData)(void *data), Bool freeNext);

/* Creates new Queue */
Queue* queue_new();

/* Clears entire Queue (remove Queue's QNodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free QueueNode's data */
void queue_clear(Queue *q, void (*freeData)(void *data));

/* Frees entire Queue (remove Queue and its QNodes from memory)
 * freeData: Function to free data. Case NULL -> doesn't free QueueNode's data */
void queue_free(Queue *q, void (*freeData)(void *data));

/* Verifies whether the Queue is empty */
Bool queue_is_empty(Queue *q);

/* Returns the element on Queue front */
void* queue_front(Queue *q);

/* Returns the element on Queue back */
void* queue_back(Queue *q);

/* Pushes data in the Queue */
void queue_push(Queue *q, void *data);

/* Removes the data on Queue front
 * freeData: Function to free data.
 *   - Case not NULL -> free QueueNode's data and returns NULL
 *   - Case NULL -> doesn't free QueueNode's data and returns the data */
void* queue_pop(Queue *q, void (*freeData)(void *data));

/* Prints entire Queue
 * printData -> function to print Queue's data
 * sep -> Separator between Queue's data */
void queue_print(Queue *q, void (*printData)(void *data), char *sep);

#endif