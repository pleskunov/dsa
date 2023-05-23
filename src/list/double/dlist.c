#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data)) {
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
  return;
}

void dlist_destroy(DList *list) {
  void *data;
  /* Remove each element from the list. */
  while (dlist_size(list) > 0) {
    if(dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destroy != NULL) {
      list->destroy(data);
    }
  }
  memset(list, 0, sizeof(DList));
  return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
  DListElmt *new_element;

  /* A NULL element is not allowed unless the list is empty. */
  if (element == NULL && dlist_size(list) != 0) {
    return -1;
  }

  new_element = (DListElmt *)malloc(sizeof(DListElmt));
  if (new_element == NULL) {
    return -1;
  }

  /* Insert a new element into the list. */
  new_element->data = (void *)data;

  if (dlist_size(list) == 0) {
    /* When the list is empty. */
    list->head = new_element;
    list->tail = new_element;

    list->head->prev = NULL;
    list->head->next = NULL;
  }
  else {
    /* When the list is not empty. */
    new_element->next = element->next;
    new_element->prev = element;

    if (element->next == NULL) {
      list->tail = new_element;
    }
    else {
      element->next->prev = new_element;
    }
    element->next = new_element;
  }
  list->size++;
  return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
  DListElmt *new_element;

  if (element == NULL && dlist_size(list) != 0) {
    return -1;
  }

  new_element = (DListElmt *)malloc(sizeof(DListElmt));
  if (new_element == NULL) {
    return -1;
  }

  new_element->data = (void *)data;

  if (dlist_size(list) == 0) {
    list->head = new_element;
    list->tail = new_element;

    list->head->prev = NULL;
    list->head->next = NULL;
  }
  else {
    new_element->next = element;
    new_element->prev = element->prev;

    if (element->prev == NULL) {
      list->head = new_element;
    }
    else {
      element->prev->next = new_element;
    }
    element->prev = new_element;
  }
  list->size++;
  return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data) {
  if (element == NULL || dlist_size(list) == 0) {
    return -1;
  }

  /* Remove the element from the list. */
  *data = element->data;

  if (element == list->head) {
    /* Remove the element from the head of the list. */
    list->head = element->next;

    if (list->head == NULL) {
      list->tail = NULL; // there are no elemets left
    }
    else {
      element->next->prev = NULL;
    }
  }
  else {
    /* Remove the element from other place than the head of the list. */
    element->prev->next = element->next;

    if (element->next == NULL) {
      list->tail = element->prev; // the last element is deleted
    }
    else {
      element->next->prev = element->prev;
    }
  }
  free(element);
  list->size--;
  return 0;
}
