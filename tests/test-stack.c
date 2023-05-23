#include <stdio.h>
#include <stdlib.h>
#include "../src/stack/stack.h"
#include "../src/utils/utils.h"

void stack_info(Stack *stack);

int main(void) {

  int values[] = {10, 4, 6, 8};
  int status = 0;
  int l = sizeof(values)/sizeof(values[0]);
  void **value = (void **)malloc(sizeof(int));
  int stack_top_value;
  void *stack_top_ptr = &stack_top_value;

  Stack *MyStack;
  MyStack = (Stack *)malloc(sizeof(Stack));
  if (MyStack == NULL) {
    printf("Unable to allocate memory for the list!\n");
    return EXIT_FAILURE;
  }

  printf("Initilizing the stack...\n");
  stack_init(MyStack, destroy);

  stack_info(MyStack);

  for (int i = 0; i < l; i++) {
    if (status != 0) {
      printf("Push operation has failed\n");
      break;
    }
    printf("Pushing %d to the stack...\n", *(values + i));
    status = stack_push(MyStack, (values + i));
    stack_top_ptr = stack_peek(MyStack);
    printf("%d is now on top of the stack.\n", *(int *)stack_top_ptr);
  }

  stack_info(MyStack);

  for (int j = 0; j < l; j++) {
    if (status != 0) {
      printf("Pop operation has failed\n");
      break;
    }
    status = stack_pop(MyStack, value);
    printf("Popping %d from the stack...\n", **(int **)value);
  }

  stack_info(MyStack);

  printf("Destroying the stack...\n");
  stack_destroy(MyStack);
  free(MyStack);
  free(value);

  return EXIT_SUCCESS;
}

void stack_info(Stack *stack) {
  printf("\n\n");
  printf("* * * BEGIN STACK INFO * * *");
  printf("\nSize:\t%d", stack_size(stack));
  printf("\n* * * END STACK INFO * * *");
  printf("\n\n");
}
