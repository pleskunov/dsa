#pragma once

#include <stdint.h>

#define DEF_MAX_CAPACITY 4 // in bytes

typedef struct {
  void      **elements;
  uint64_t  size;
  uint64_t  capacity;
} darray;

/*
  Allocates a new memory block to store dynamic array elements.

  Returns when the pointer to the dynamic array is NULL.

  By default, all fields are initialized. The function attempts to allocate 
  memory by calling malloc().

  If malloc() succeeds, the `elements` pointer will point to the first element, 
  and the `capacity` of the dynamic array will be updated accordingly.

  If malloc() fails, the `elements` pointer will be set to NULL, and both 
  `size` and `capacity` will be set to 0.
*/
void  allocate(darray *d, uint64_t capacity);

/*
  TODO
*/
void  reallocate_for(darray *d, uint64_t additional_size);

/*
  TODO
*/
void  set(darray *d, void *elmt, uint64_t idx);

/*
  Retrieves the element from the specified index `idx` of the dynamic array.

  Returns a pointer to the element at the given index.

  If the index is out of bounds, NULL is returned to indicate an invalid request.
*/
void* get(darray *d, uint64_t idx);


/*
  Inserts an element `elmt` at the specified index `idx` in the dynamic array.

  If the index is valid, the element is placed at the given index, and the array
  is updated accordingly (e.g., shifting elements if needed). If the index is 
  out of bounds, no changes are made to the array.
*/
void  insert_at_idx(darray *d, void *elmt, uint64_t idx);

/*
  TODO
*/
void  insert_first(darray *d, void *elmt);

/*
  TODO
*/
void  insert_last(darray *d, void *elmt);

/*
  TODO
*/
void* remove_at_idx(darray *d, uint64_t idx);

/*
  TODO
*/
void* remove_first(darray *d);

/*
  TODO
*/
void* remove_last(darray *d);
