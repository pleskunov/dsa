/* An implementation of the stack on top of linked list in C. */
#pragma once

#include <stdlib.h>

#include "../../src/list/single/list.h"

typedef List Stack;

/* Interface */

/* Push an element onto the stack: 0 upon success; -1 otherwise. */
int stack_push(Stack *stack, const void *data);

/* Pop the topmost element from the stack:  0 upon success; -1 otherwise. */
int stack_pop(Stack *stack, void **data);

/* Initialize the stack. */
#define stack_init list_init

/* Destroy the stack. */
#define stack_destroy list_destroy

/* Data stored in the topmost element of the stack or NULL if the stack is empty. */
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

/* Number of elements in the stack. */
#define stack_size list_size
