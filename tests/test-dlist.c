#include <stdio.h>
#include <stdlib.h>

#include "../src/list/double/dlist.h"
#include "../src/utils/utils.h"

void dlist_info(DList *list);

int main(void) {

  int values[] = {10, 4, 6, 8, 9, 80, 288};
  int add_elmt = 67;
  int *add_elmt_ptr = &add_elmt;
  int status = 0;
  int l = sizeof(values)/sizeof(values[0]);
  DListElmt *element, *next;
  void **value = (void **)malloc(sizeof(int));
  DList* MyList;

  MyList = (DList *)malloc(sizeof(DList));
  if (MyList == NULL) {
    printf("Unable to allocate memory for the list!\n");
    return EXIT_FAILURE;
  }

  // Test dlist_init()
  printf("Initilizing the list...\n");
  dlist_init(MyList, destroy);

  // Tests macro: dlist_size, dlist_head and dlist_tail
  dlist_info(MyList);

  // Test list_ins_next()
  printf("Inserting %d elements into the list...\n", l);
  for (int i = 0; i < l; i++) {
    if (status != 0) {
      printf("Insert operation has failed!\n");
      break;
    }

    if (i == 0) {
      printf("Adding element %d (%d) to the list!\n", i, values[i]);
      status = dlist_ins_next(MyList, NULL, (values + i));
      element = MyList->head;
    }
    else {
      printf("Adding element %d (%d) to the list!\n", i, values[i]);
      status = dlist_ins_next(MyList, element, (values + i));
      element = element->next;
    }
  }

  dlist_info(MyList);

  // Test dlist_ins_prev()
  printf("Inserting element %d before the last element the list...\n", add_elmt);
  status = dlist_ins_prev(MyList, MyList->tail, add_elmt_ptr);

  dlist_info(MyList);

  // Test dlist_remove()
  printf("Deleting %d elements from the list...\n", l);

  element = MyList->head;
  for (int j = 0; j < l + 1; j++) {
    next = element->next;
    status = dlist_remove(MyList, element, value);
    printf("Element %d is deleted from the list!\n", **(int **)value);
    element = next;
  }

  dlist_info(MyList);

  // Tests dlist_destroy()
  printf("Destroying the list...\n");
  dlist_destroy(MyList);
  free(MyList);

  return EXIT_SUCCESS;
}

void dlist_info(DList *list) {
  printf("\n\n");
  printf("* * * BEGIN LLIST INFO * * *");
  printf("\nSize:\t%d", dlist_size(list));
  printf("\nHead:\t%p", dlist_head(list));
  printf("\nTail:\t%p", dlist_tail(list));
  printf("\n* * * END LLIST INFO * * *");
  printf("\n\n");
}
