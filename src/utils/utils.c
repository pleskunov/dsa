#include <stdlib.h>
#include <string.h>
#include "utils.h"

int match(const void *key1, const void *key2) {
  return int_is_equal(key1, key2);
}

/* Default key comparisons. */

int str_match(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2);
}

int int_match(void *key1, void *key2) {
  int i1 = *((int *)key1);
  int i2 = *((int *)key2);

  if (i1 > i2) {
    return 1;
  }
  else if (i1 == i2) {
    return 0;
  }
  else {
    return -1;
  }
}

int int_is_equal(const void *key1, const void *key2) {
  int i1 = *((int *)key1);
  int i2 = *((int *)key2);
  if (i1 == i2) {
    return 1;
  }
  return 0;
}

void destroy(void* data) {
  return free(data);
}
