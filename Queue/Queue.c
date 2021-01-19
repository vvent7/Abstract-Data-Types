#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"

QNode* QN_Create(void *data, QNode *next){
  QNode *node = (QNode*) malloc(sizeof(QNode));
  node->data = data; node->next = next;
  return node;
}

void QN_Free(QNode *node, void (*freeData)(void *data), bool freeNext){
  if(node==NULL) return;
  
  if(freeData) freeData(node->data);
  if(freeNext) QN_Free(node->next, freeData, freeNext);
  free(node);
}

Queue* Q_Create(){
  Queue *q = (Queue*) malloc(sizeof(Queue));
  q->front = q->back = NULL; q->size = 0;
  return q;
}

void Q_Clear(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  QN_Free(q->front, freeData, true);
  q->front = q->back = NULL; q->size = 0;
}

void Q_Free(Queue *q, void (*freeData)(void *data)){
  if(q==NULL) return;
  Q_Clear(q, freeData);
  free(q);
}

bool Q_IsEmpty(Queue *q){
  return (q==NULL || q->size==0);
}

void* Q_Front(Queue *q){
  return Q_IsEmpty(q) ? NULL : q->front->data;
}

void* Q_Back(Queue *q){
  return Q_IsEmpty(q) ? NULL : q->back->data;
}

//Pushes data in the Queue
void Q_Push(Queue *q, void *data){
  if(q==NULL) return;

  QNode *node = QN_Create(data, NULL);

  if(Q_IsEmpty(q))
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
void* Q_Pop(Queue *q, void (*freeData)(void *data)){
  if(Q_IsEmpty(q)) return NULL;

  QNode *node = q->front;
  void *d = node->data;

  q->front = q->front->next;
  if(q->front==NULL) q->back = NULL;
  q->size--;

  QN_Free(node, freeData, false);

  return freeData==NULL ? NULL : d;
}

/*Prints entire Queue
  printData -> function to print Queue's data
  sep -> Separator between Queue's data */
void Q_Print(Queue *q, void (*printData)(void *data), char *sep){
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