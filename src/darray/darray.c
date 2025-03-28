#include "darray.h"
#include "../error/err.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

_Noreturn static void custom_error_handler(const char *message) {
  fprintf(stdout, "[DARRAY_LIB]: %s\n", message);
  exit(EXIT_FAILURE);
}

void allocate(darray *d, uint64_t capacity) {
  #ifdef DEBUG
    set_error_callback(custom_error_handler, UNRECOVERABLE);
  #endif

  if (!d) {
    report_unrecoverable_error("allocate(__darray *d__, ...) : Pointer is set to NULL");
  }

  /* Initialize all fields first */
  d->elements = NULL;
  d->size = 0;
  d->capacity = 0;

  if (capacity == 0) {
    capacity = DEF_MAX_CAPACITY;
  }

  d->elements = (void **)malloc(capacity * sizeof(void *));
  if (!d->elements) {
    report_unrecoverable_error("allocate() : Cannot allocate memory!");
  } else {
    d->capacity = capacity;
  }

  return;
}

void reallocate_for(darray *d, uint64_t additional_size) {
  #ifdef DEBUG
    set_error_callback(custom_error_handler, UNRECOVERABLE);
    //set_error_callback(custom_error_handler);
  #endif

  uint64_t new_size = d->size + additional_size;

  if (new_size > d->capacity) {
    uint64_t old_capacity = d->capacity;
    uint64_t new_capacity = (old_capacity == 0) ? 1 : old_capacity;

    /* Double the capacity until it is sufficient */
    while (new_capacity < new_size) {
      new_capacity <<= 1;
    }

    void **new_array = (void **)realloc(d->elements, new_capacity * sizeof(void *));
    if (!new_array) {
      report_error("reallocate_for() : Reallocation has failed.");

      void **old_array = d->elements;

      /* Allocate a new memory block */
      void **new_array = (void **)malloc(new_capacity * sizeof(void *));
      if (!new_array) {
        report_unrecoverable_error("reallocate_for() : Cannot allocate memory!");
      }

      if (old_array) {
        memcpy(new_array, old_array, old_capacity * sizeof(void *));
      }

      /* Cleanup and update pointers */
      free(old_array);
      d->elements = new_array;
    } else {
      d->elements = new_array;
    }

    d->capacity = new_capacity;
  }

  return;
}

void set(darray *d, void *elmt, uint64_t idx) {
  if (idx > d->size) return; // out of bounds

  *(d->elements + idx) = elmt;

  return;
}

void* get(darray *d, uint64_t idx) {
  return (idx < d->size) ? *(d->elements + idx) : NULL;
}

void insert_at_idx(darray *d, void *elmt, uint64_t idx) {
  if (idx > d->size) return;

  reallocate_for(d, 1);

  for (void **p = d->elements + d->size; p > d->elements + idx; p--) {
    *(p) = *(p - 1);
  };

  *(d->elements + idx) = elmt;
  d->size++;

  return;
}

void insert_first(darray *d, void *elmt) {
  return insert_at_idx(d, elmt, 0);
}

void insert_last(darray *d, void *elmt) {
  return insert_at_idx(d, elmt, d->size);
}

void* remove_at_idx(darray *d, uint64_t idx) {
  if (idx >= d->size) return NULL; // out of bounds

  void *elmt = *(d->elements + idx);

  for (void **p = d->elements + idx + 1; p < d->elements + d->size; p++) {
    *(p - 1) = *p;
  }

  *(d->elements + d->size - 1) = NULL;
  d->size--;

  return elmt;
}

void* remove_first(darray *d) {
  return remove_at_idx(d, 0);
}

void* remove_last(darray *d) {
  return remove_at_idx(d, d->size - 1);
}
