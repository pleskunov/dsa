#include <stdio.h>
#include <stdlib.h>
#include "../src/set/set.h"
#include "../src/utils/utils.h"

void print_set(Set* set);

int main(void) {

  int array1[] = {2, 5, 8, 9};
  int array2[] = {6, 5, 3, 4};
  int array3[] = {2, 8, 5, 9, 6};

  int n = 2;
  int i;

  Set Set1, Set2, Set3;
  Set UnionSet, IntersectionSet, DiffSet;

  printf("Initializing Elements sets... ");
  set_init(&Set1, match, destroy);
  set_init(&Set2, match, destroy);
  set_init(&Set3, match, destroy);
  printf("Done.\n");
  printf("Initializing Union, Intersection and Difference Sets... ");
  set_init(&UnionSet, match, destroy);
  set_init(&IntersectionSet, match, destroy);
  set_init(&DiffSet, match, destroy);
  printf("Done.\n");
  printf("\n");

  printf("Set1 size: %d elements.\n", set_size(&Set1));
  printf("Set2 size: %d elements.\n", set_size(&Set2));
  printf("Set3 size: %d elements.\n", set_size(&Set3));
  printf("\n");
  printf("Union Set size: %d elements.\n", set_size(&UnionSet));
  printf("Intersection Set size: %d elements.\n", set_size(&IntersectionSet));
  printf("Difference Set size: %d elements.\n", set_size(&DiffSet));
  printf("\n");

  printf("Inserting elements to Set 1... ");
  for (i = 0; i < (sizeof(array1)/sizeof(array1[0])); i++) {
    set_insert(&Set1, &array1[i]);
  }
  printf("Done.\n");

  printf("Set 1: [ ");
  print_set(&Set1);
  printf("]\n");

  printf("Inserting elements to Set 2... ");
  for (i = 0; i < (sizeof(array2)/sizeof(array2[0])); i++) {
    set_insert(&Set2, &array2[i]);
  }
  printf("Done.\n");

  printf("Set 2: [ ");
  print_set(&Set2);
  printf("]\n");
  
  printf("Inserting elements to Set 3... ");
  for (i = 0; i < (sizeof(array3)/sizeof(array3[0])); i++) {
    set_insert(&Set3, &array3[i]);
  }
  printf("Done.\n");

  printf("Set 3: [ ");
  print_set(&Set3);
  printf("]\n");
  printf("\n");

  printf("Set1 size: %d elements.\n", set_size(&Set1));
  printf("Set2 size: %d elements.\n", set_size(&Set2));
  printf("Set3 size: %d elements.\n", set_size(&Set3));
  printf("\n");
  printf("Union Set size: %d elements.\n", set_size(&UnionSet));
  printf("Intersection Set size: %d elements.\n", set_size(&IntersectionSet));
  printf("Difference Set size: %d elements.\n", set_size(&DiffSet));
  printf("\n");

  printf("Building Union, Intersection and Difference Sets... ");
  set_union(&UnionSet, &Set1, &Set2);
  set_intersection(&IntersectionSet, &Set1, &Set2);
  set_difference(&DiffSet, &Set1, &Set2);
  printf("Done.\n");

  printf("Union of Set 1 & 2: [ ");
  print_set(&UnionSet);
  printf("]\n");
  
  printf("Intersection of Set 1 & 2: [ ");
  print_set(&IntersectionSet);
  printf("]\n");

  printf("Difference of Set 1 & 2: [ ");
  print_set(&DiffSet);
  printf("]\n");
  printf("\n");

  printf("Testing if an element is member of a set... \n");
  if (set_is_member(&Set1, &n)) {
    printf("%d is a member of 1 set\n", n);
  }
  if (set_is_member(&Set2, &n)) {
    printf("%d is a member of 2 set\n", n);
  }
  if (set_is_member(&Set3, &n)) {
    printf("%d is a member of 3 set\n", n);
  }
  printf("\n");

  printf("Set equality test... ");
  if (set_is_equal(&Set1, &Set2)) {
    printf("Set 1 is equal to Set 2.\n");
  }
  else {
    printf("Not equal.");
  }
  printf("\n");

  printf("Subset test... ");
  if (set_is_subset(&Set1, &Set3)) {
    printf("Yes");
  }
  else {
    printf("No");
  }

  printf("\n");

  /*
  printf("Destroyig Sets... ");
  set_destroy(&Set1);
  set_destroy(&Set2);
  set_destroy(&Set3);
  set_destroy(&UnionSet);
  set_destroy(&IntersectionSet);
  set_destroy(&DiffSet);
  */

    /* call a destroy frunction from struct */
    //MyList->destroy(&a, &b);

    /* this op could be handled by external function in list.c */
    //ListElmt* new_element;
    //new_element = (ListElmt *)malloc(sizeof(ListElmt));

    //if (new_element == NULL)
        //return EXIT_FAILURE;

    //new_element->data = (void *)data;

    /* 
    remove an element from the list

    we create new double void ptr because it is what remove
    function expects as an arg

    list_rem_func will assign the address of data of the 
    element removed to our double pointer x

    *x = &data

    in order to get the data, we should double dereference x
    casting it to the type of data we expect to retrieve
    */
  /*  
  void **data;
    *data = SecondElmt;
    set_remove(MyFirstSet, data);
    printf("This is first set after deleting %d\n", **(int **)data);
*/
    /* always keep track of those */
    return EXIT_SUCCESS;
}

void print_set(Set* set) {
  ListElmt *element;
  element = set->head;
  while (element != NULL) {
    printf("%d ", *(int*)(element->data));
    element = element->next;
  }
}
