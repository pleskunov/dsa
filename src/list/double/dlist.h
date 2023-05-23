/* An implementation of the double linked-list abstract data type in C. */

#pragma once

#include <stdlib.h>

typedef struct DListElmt_ {
  void                *data;
  struct DListElmt_   *prev;
  struct DListElmt_   *next;
} DListElmt;

typedef struct DList_ {
  int             size;

  int             (*match)(const void *key1, const void *key2);
  void            (*destroy)(void *data);

  DListElmt       *head;
  DListElmt       *tail;
} DList;

/* Interface */

/* Initialize the linked list. */
void dlist_init(DList *list, void (*destroy)(void *data));

/* Destroy the linked list. */
void dlist_destroy(DList *list);

/* Insert a new element after the specified element: 0 upon success; -1 otherwise. */
int dlist_ins_next(DList *list, DListElmt *element, const void *data);

/* Insert a new element before the specified element: 0 upon success; -1 otherwise. */
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);

/* Remove the specified element: 0 upon success; -1 otherwise. */
int dlist_remove(DList *list, DListElmt *element, void **data);

/* Number of elements in the list. */
#define dlist_size(list) ((list)->size)

/* An element at the head of the list. */
#define dlist_head(list) ((list)->head)

/* An element at the tail of the list. */
#define dlist_tail(list) ((list)->tail)

/* Check if the element is at the head of the list: 1 if true; 0 otherwise. */
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

/* Check if the element is at the tail of the list: 1 if true; 0 otherwise. */
#define dlsit_is_tail(element) ((element)->next == NULL ? 1 : 0)

/* Data stored in the element. */
#define dlsit_data(element) ((element)->data)

/* An element that follows the specified element. */
#define dlist_next(element) ((element)->next)

/* An element that preceeds the specified element. */
#define dlist_prev(element) ((element)->prev)
