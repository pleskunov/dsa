/* The library of user-defined functions. */

#pragma once

#include <stdlib.h>

/* Default key comparisons. Format: <type> <name>match(void *key1, void *key2); */

/* Generic type example */
int match(const void *key1, const void *key2);

/* String keys. */
int str_match(void *key1, void *key2);

/* Integer keys. */
int int_match(void *key1, void *key2);

int int_is_equal(const void *key1, const void *key2);

  /* TODO */
void destroy(void* data);
