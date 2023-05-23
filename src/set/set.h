#pragma once

#include <stdlib.h>
#include "../../src/list/single/list.h"

typedef List Set;

/* Initialize a new set. */
void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));

/* Destroy the set. */
#define set_destroy list_destroy

/* Insert a new member to a set. Returns 0 on success, 1 if member is already
in the set and -1 otherwise. */
int set_insert(Set *set, const void *data);

/* Remove a member, matching data from a set. Returns 0 on success, and -1
otherwise. */
int set_remove(Set *set, void **data);

/* Build a set that is the union of set1 and set2. Returns 0 on success, and -1
otherwise. Upon success, setu -> union set. */
int set_union(Set *setu, const Set *set1, const Set *set2);

/* Build a set that is the intersection of set1 and set2. Returns 0 on success,
and -1 otherwise. Upon success, seti -> intersection set. */
int set_intersection(Set *seti, const Set *set1, const Set *set2);

/* Build a set that is the difference of set1 and set2. Returns 0 on success,
and -1 otherwise. Upon success, setd -> difference set. */
int set_difference(Set *setd, const Set *set1, const Set *set2);

/* Check if data matches that of member in a set. Returns 1 if there is a match,
and 0 otherwise. */
int set_is_member(const Set *set, const void *data);

/* Check whether set1 is a subset of set2. Returns 1 if set1 is a subset of set2,
and 0 otherwise. */
int set_is_subset(const Set *set1, const Set *set2);

/* Check whether set1 is equal to set2. Returns 1 of both sets are equal, and 0
otherwise. */
int set_is_equal(const Set *set1, const Set *set2);

/* A macro that returns current size of a set. */
#define set_size(set) ((set)->size)
