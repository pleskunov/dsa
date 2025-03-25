#pragma once

#include <stdint.h>

#define DEF_MAX_CAPACITY 4 // in bytes

typedef struct {
  void      **elements;
  uint64_t  size;
  uint64_t  capacity;
} darray;

void allocate(darray *d, uint64_t capacity);

void reallocate_for(darray *d, uint64_t additional_size);

void  set(darray *d, void *elmt, uint64_t idx);

void* get(darray *d, uint64_t idx);

void  insert_at_idx(darray *d, void *elmt, uint64_t idx);

void  insert_first(darray *d, void *elmt);

void  insert_last(darray *d, void *elmt);

void* remove_at_idx(darray *d, uint64_t idx);

void* remove_first(darray *d);

void* remove_last(darray *d);
