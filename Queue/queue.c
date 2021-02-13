#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

QueueNode* queue_node_new(void *data, QueueNode *next){
  QueueNode *node = (QueueNode*) malloc(sizeof(QueueNode));
  node->data = data; node->next = next;
  return node;
}

void queue_node_free(QueueNode *node, void (*freeData)(void *data), _boolean freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) queue_node_free(node->next, freeData, freeNext);
  free(node);
}

Queue* queue_new(){
  Queue *q = (Queue*) malloc(sizeof(Queue));
  q->front = q->back = NULL; q->size = 0;
  return q;
}

void queue_clear(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  queue_node_free(q->front, freeData, true);
  q->front = q->back = NULL; q->size = 0;
}

void queue_free(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  queue_clear(q, freeData);
  free(q);
}

_boolean queue_is_empty(Queue *q){
  return (q==NULL || q->size==0);
}

void* queue_front(Queue *q){
  return queue_is_empty(q) ? NULL : q->front->data;
}

void* queue_back(Queue *q){
  return queue_is_empty(q) ? NULL : q->back->data;
}

void queue_push(Queue *q, void *data){
  QueueNode *node;

  if(q==NULL) return;

  node = queue_node_new(data, NULL);

  if(queue_is_empty(q))
    q->front = q->back = node;
  else{
    q->back->next = node;
    q->back = node;
  }

  q->size++;
}

void* queue_pop(Queue *q, void (*freeData)(void *data)){
  QueueNode *node;
  void *d;

  if(queue_is_empty(q)) return NULL;

  node = q->front;
  d = node->data;

  q->front = q->front->next;
  if(q->front==NULL) q->back = NULL;
  q->size--;

  queue_node_free(node, freeData, false);

  return freeData ? NULL : d;
}

void queue_print(Queue *q, void (*printData)(void *data), char *sep){
  QueueNode *node;

  if(q==NULL || printData==NULL) return;
  if(queue_is_empty(q)){
    printf("Empty Queue"); return;
  }
  
  for(node = q->front;node!=NULL;node=node->next){
    if(node!=q->front) printf("%s", sep);
    printData(node->data);
  }
}