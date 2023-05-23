#include <stdio.h>
#include <stdlib.h>
#include "../src/queue/queue.h"
#include "../src/utils/utils.h"

/* stack driver */
int main(void) {

  /* create some data to store in the list, 
  ints are the simplest ones */
  int* FirstElmt;
  if ((FirstElmt = (int *)malloc(sizeof(int))) == NULL)
    return EXIT_FAILURE;
  *FirstElmt = 2;

  int* SecondElmt;
  if ((SecondElmt = (int *)malloc(sizeof(int))) == NULL)
    return EXIT_FAILURE;
  *SecondElmt = 5;

  /* create a new stack */
  Queue* MyQueue;
  if ((MyQueue = (Queue *)malloc(sizeof(Queue))) == NULL)
    return EXIT_FAILURE;

  queue_init(MyQueue, destroy);

  queue_add(MyQueue, FirstElmt);

  int a;
  a = queue_size(MyQueue);
  printf("Size of the queue: %d\n", a);

  queue_add(MyQueue, SecondElmt);

  a = queue_size(MyQueue);
  printf("Size of the queue: %d\n", a);

  void *data;
  data = queue_peek(MyQueue);
  printf("%d is the first element in the queue\n", *(int *)data);

  void **x;
  queue_rem(MyQueue, x);
  printf("We removed %d from the queue\n", **(int **)x);

  a = queue_size(MyQueue);
  printf("Size of the queue: %d\n", a);

  queue_destroy(MyQueue);

  /* always keep track of those */
  free(FirstElmt);
  free(SecondElmt);
  free(MyQueue);

  return EXIT_SUCCESS;
}
