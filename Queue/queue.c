#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

QNode* qn_new(void *data, QNode *next){
  QNode *node = (QNode*) malloc(sizeof(QNode));
  node->data = data; node->next = next;
  return node;
}

void qn_free(QNode *node, void (*freeData)(void *data), bool freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) qn_free(node->next, freeData, freeNext);
  free(node);
}

Queue* q_new(){
  Queue *q = (Queue*) malloc(sizeof(Queue));
  q->front = q->back = NULL; q->size = 0;
  return q;
}

void q_clear(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  qn_free(q->front, freeData, true);
  q->front = q->back = NULL; q->size = 0;
}

void q_free(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  q_clear(q, freeData);
  free(q);
}

bool q_is_empty(Queue *q){
  return (q==NULL || q->size==0);
}

void* q_front(Queue *q){
  return q_is_empty(q) ? NULL : q->front->data;
}

void* q_back(Queue *q){
  return q_is_empty(q) ? NULL : q->back->data;
}

//Pushes data in the Queue
void q_push(Queue *q, void *data){
  if(q==NULL) return;

  QNode *node = qn_new(data, NULL);

  if(q_is_empty(q))
    q->front = q->back = node;
  else{
    q->back->next = node;
    q->back = node;
  }

  q->size++;
}

/*Removes the data on Queue top
  freeData: Function to free data.
    - Case not NULL -> free QNode's data and returns NULL
    - Case NULL -> doesn't free QNode's data and returns the data*/
void* q_pop(Queue *q, void (*freeData)(void *data)){
  if(q_is_empty(q)) return NULL;

  QNode *node = q->front;
  void *d = node->data;

  q->front = q->front->next;
  if(q->front==NULL) q->back = NULL;
  q->size--;

  qn_free(node, freeData, false);

  return freeData ? NULL : d;
}

/*Prints entire Queue
  printData -> function to print Queue's data
  sep -> Separator between Queue's data */
void q_print(Queue *q, void (*printData)(void *data), char *sep){
  if(q==NULL || printData==NULL) return;
  if(q->size==0){
    printf("Empty Queue"); return;
  }

  QNode *node;
  for(node = q->front;node!=NULL;node=node->next){
    if(node!=q->front) printf("%s", sep);
    printData(node->data);
  }
}