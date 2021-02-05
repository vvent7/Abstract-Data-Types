#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

#define _VEC_GROWTH_FACTOR 2

typedef struct VectorHeader{
  size_t size, capacity;
} VectorHeader;

#ifndef MIN
  #define MIN(x, y) (x<y ? x : y)
#endif

//Defines Vector's type (int, double, float, boolean, etc...);
#define Vector(type) type**

//Creates the vector and returns its generic address (pointer to array / pointer to pointer)
Vector(void) vector_create();

//Verifies whether the Vector is invalid
#define vector_is_valid(vec) (vec!=NULL && (*vec)!=NULL)

//Returns Vector's Header Address
#define vector_header(vec) (vector_is_valid(vec) ? ((VectorHeader*)(*vec))-1 : NULL)

//Returns Vector's Size
#define vector_size(vec) (vector_is_valid(vec) ? vector_header(vec)->size : (size_t)0)

//Returns Vector's Total Capacity
#define vector_capacity(vec) (vector_is_valid(vec) ? vector_header(vec)->capacity : (size_t)0)

//Sets Vector's Size
#define vector_set_size(vec, size)                               \
  do{                                                            \
    VectorHeader *vh = vector_header(vec);                       \
    size_t new_size = size;                                      \
    if(vh!=NULL && size>=0 && new_size!=vector_size(vec)){       \
      if(new_size > vh->capacity){                               \
        size_t new_cap = vh->capacity;                           \
        while(new_size > new_cap) new_cap *= _VEC_GROWTH_FACTOR; \
        vector_set_capacity(vec, new_cap);                       \
        vh = vector_header(vec);                                 \
      }                                                          \
      vector_header(vec)->size = new_size;                       \
    }                                                            \
  }while(0)

//Sets Vector's Capacity
#define vector_set_capacity(vec, cap)                                                       \
  do{                                                                                       \
    VectorHeader *vh = vector_header(vec);                                                  \
    size_t new_cap = cap;                                                                   \
    if(vh!=NULL && (int)cap>=0 && new_cap!=vh->capacity){                                   \
      vh = realloc(vector_header(vec), sizeof(VectorHeader) + sizeof((*vec)[0]) * new_cap); \
      (*vec) = (void*) (vh+1);                                                              \
      vh->capacity = new_cap;                                                               \
      vh->size = MIN(vh->capacity, vh->size);                                               \
    }                                                                                       \
  }while(0)

//Verifies whether the Vector is empty.
#define vector_empty(vec) (vector_size(vec)==0)

//Clears Vector's content
#define vector_clear(vec) vector_set_capacity(vec, 0)

//Frees all memory associated with the vector
#define vector_free(vec)                 \
  do{                                    \
    free(vector_header(vec)); free(vec); \
  }while(0)

#define vector_insert(vec, index, data)                                    \
  do{                                                                      \
    VectorHeader *vh = vector_header(vec);                                 \
    size_t ind = index;                                                    \
    if(vh!=NULL && (int)index>=0 && ind<=vh->size){                        \
      if(vh->capacity<=vh->size){                                          \
        vector_set_capacity(vec, (vh->capacity==0 ? 1 : vh->capacity*2));  \
        vh = vector_header(vec);                                           \
      }                                                                    \
      memmove((*vec)+ind+1, (*vec)+ind, sizeof((*vec)[0])*(vh->size-ind)); \
      (*vec)[ind] = data;                                                  \
      vh->size++;                                                          \
    }                                                                      \
  }while(0)

#define vector_push_back(vec, data) vector_insert(vec, vector_size(vec), data)

#endif