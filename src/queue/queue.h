/* An implementation of the queue on top of linked list in C. */
#pragma once

#include <stdlib.h>
#include "../../src/list/single/list.h"

typedef List Queue;

/* Interface */

/* Add an element at the tail of the queue: 0 upon success; -1 otherwise. */
int queue_add(Queue *queue, const void *data);

/* Remove the element from the head of the queue: 0 upon success; -1 otherwise. */
int queue_rem(Queue *queue, void **data);

/* Initialize the queue. */
#define queue_init list_init

/* Destroy the queue. */
#define queue_destroy list_destroy

/* Data stored in the head element of the queue or NULL if the stack is empty. */
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

/* Number of elements in the queue. */
#define queue_size list_size
