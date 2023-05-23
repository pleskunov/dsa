#include "queue.h"

int queue_add(Queue *queue, const void *data) {
  return list_ins_next(queue, list_tail(queue), data);
}

int queue_rem(Queue *queue, void **data) {
  return list_rem_next(queue, NULL, data);
}
