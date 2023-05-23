/* An implementation of the circular linked-list abstract data type in C. */
#pragma once

#include <stdlib.h>

typedef struct CListElmt_ {
  void                *data;
  struct CListElmt_   *next;
} CListElmt;

typedef struct CList_ {
  int         size;

  int         (*match)(const void *key1, const void *key2);
  void        (*destroy)(void *data);

  CListElmt   *head;
} CList;

/* Interface */

/* Initialize the linked list. */
void clist_init(CList *list, void (*destroy)(void *data));

/* Destroy the linked list. */
void clist_destroy(CList *list);

/* Insert a new element after the specified element: 0 upon success; -1 otherwise. */
int clist_ins_next(CList *list, CListElmt *element, const void *data);

/* Remove an element after the specified element: 0 upon success; -1 otherwise. */
int clist_rem_next(CList *list, CListElmt *element, void **data);

/* Number of elements in the list. */
#define clist_size(list) ((list)->size)

/* An element at the head of the list. */
#define clist_head(list) ((list)->head)

/* Data stored in the element. */
#define clist_data(element) ((element)->data)

/* An element that follows the specified element. */
#define clist_next(element) ((element)->next)
