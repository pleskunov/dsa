/* An implementation of the linked-list abstract data type in C. */

#pragma once

#include <stdlib.h>

/* A structure for the single linked-list elements. */
typedef struct ListElmt_ {
  void                *data;
  struct ListElmt_    *next;
} ListElmt;

/* A structure for the linked lists. */
typedef struct List_ {
  int         size;

  int         (*match)(const void *key1, const void *key2);
  void        (*destroy)(void *data);

  ListElmt    *head;
  ListElmt    *tail;
} List;

/* Interface */

/* Initialize the linked list. */
void list_init(List* list, void (*destroy)(void *data));

/* Destroy the linked list. */
void list_destroy(List* list);

/* Insert a new element just after the specified element: 0 upon success; -1 otherwise. */
int list_ins_next(List *list, ListElmt *element, const void *data);

/* Remove an element just after the specified element: 0 upon success; -1 otherwise. */
int list_rem_next(List *list, ListElmt *element, void **data);

/* Number of elements in the list. */
#define list_size(list) ((list)->size)

/* An element at the head of the list. */
#define list_head(list) ((list)->head)

/* An element at the tail of the list. */
#define list_tail(list) ((list)->tail)

/* Check if the element is at the head of the list: 1 if true; 0 otherwise. */
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

/* Check if the element is at the tail of the list: 1 if true; 0 otherwise. */
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

/* Data stored in the element. */
#define list_data(element) ((element)->data)

/* An element that follows the specified element. */
#define list_next(element) ((element)->next)
