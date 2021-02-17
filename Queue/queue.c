#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

QueueNode* queue_node_new(void *data, QueueNode *next){
  QueueNode *node = (QueueNode*) malloc(sizeof(QueueNode));
  node->data = data; node->next = next; node->free = _queue_node_free;
  return node;
}

void _queue_node_free(QueueNode *node, void (*freeData)(void *data), unsigned short freeNext){
  QueueNode *nextNd;

  if(node==NULL) return;

  do{
    if(freeData) freeData(node->data);
    nextNd = node->next; free(node); node = nextNd;
  }while(node && freeNext); 
}

Queue* queue_new(){
  Queue *q = (Queue*) malloc(sizeof(Queue));
  q->frontNd = q->backNd = NULL; q->size = 0;

  q->clear = _queue_clear;
  q->free = _queue_free;
  q->empty = _queue_empty;
  q->front = _queue_front;
  q->back = _queue_back;
  q->push = _queue_push;
  q->pop = _queue_pop;
  q->print = _queue_print;

  return q;
}

void _queue_clear(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  _queue_node_free(q->frontNd, freeData, 1);
  q->frontNd = q->backNd = NULL; q->size = 0;
}

void _queue_free(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  _queue_clear(q, freeData);
  free(q);
}

unsigned short _queue_empty(Queue *q){
  return (q==NULL || q->size==0);
}

void* _queue_front(Queue *q){
  return _queue_empty(q) ? NULL : q->frontNd->data;
}

void* _queue_back(Queue *q){
  return _queue_empty(q) ? NULL : q->backNd->data;
}

void _queue_push(Queue *q, void *data){
  QueueNode *node;

  if(q==NULL) return;

  node = queue_node_new(data, NULL);

  if(_queue_empty(q))
    q->frontNd = q->backNd = node;
  else{
    q->backNd->next = node;
    q->backNd = node;
  }

  q->size++;
}

void* _queue_pop(Queue *q, void (*freeData)(void *data)){
  QueueNode *node;
  void *d;

  if(_queue_empty(q)) return NULL;

  node = q->frontNd;
  d = node->data;

  q->frontNd = q->frontNd->next;
  if(q->frontNd==NULL) q->backNd = NULL;
  q->size--;

  _queue_node_free(node, freeData, 0);

  return freeData ? NULL : d;
}

void _queue_print(Queue *q, void (*printData)(void *data), char *sep){
  QueueNode *node;

  if(q==NULL || printData==NULL) return;
  if(_queue_empty(q)){
    printf("Empty Queue"); return;
  }
  
  for(node = q->frontNd;node!=NULL;node=node->next){
    if(node!=q->frontNd) printf("%s", sep);
    printData(node->data);
  }
}