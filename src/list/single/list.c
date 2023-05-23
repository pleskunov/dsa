#include <stdlib.h>
#include <string.h>
#include "list.h"

void list_init(List *list, void (*destroy)(void* data)) {
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
  return;
}

void list_destroy(List *list) {
  void *data;

  /* Remove each element from the list. */
  while (list_size(list) > 0) {
    if (list_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL) {
      /* Call a user-defined function to free dynamically allocated data. */
      list->destroy(data);
    }
  }
  /* Clear the structure as a precaution. */
  memset(list, 0, sizeof(List));

  return;
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
  ListElmt *new_element;

  new_element = (ListElmt *)malloc(sizeof(ListElmt));
  if (new_element == NULL) {
    return -1;
  }

  new_element->data = (void *)data;

  if (element == NULL) {
    /* Insert the element at the head of the list. */

    if (list_size(list) == 0) {
      list->tail = new_element;
    }

    new_element->next = list->head;
    list->head = new_element;
  }
  else {
    /* Insert the element somewhere else than at the head of the list. */

    if (element->next == NULL) {
      list->tail = new_element;
    }

    new_element->next = element->next;
    element->next = new_element;
  }

  list->size++;
  return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
  ListElmt *old_element;

  /* Removal from an empty list is not allowed. */
  if (list_size(list) == 0) {
    return -1;
  }

  if (element == NULL) {
    /* Remove the element from the head of the list. */
    *data = list->head->data;

    old_element = list->head;
    list->head = list->head->next;

    if (list_size(list) == 1) {
      list->tail = NULL;
    }
  }
  else {
    /* Remove the element from somewhere else than the head of the list. */
    *data = element->next->data;

    old_element = element->next;
    element->next = element->next->next;

    if (element->next == NULL) {
      list->tail = element;
    }
  }

  free(old_element);

  list->size--;
  return 0;
}
