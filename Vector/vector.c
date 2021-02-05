#include <stdlib.h>
#include "vector.h"


Vector(void) vector_create(){
  VectorHeader *vh = (VectorHeader*) malloc(sizeof(VectorHeader));
  vh->size = vh->capacity = 1;

  Vector(void) vec = (Vector(void)) malloc(sizeof(void*));
  *vec = (vh+1);

  return vec;
}