#include <stdio.h>
#include <stdlib.h>

#include "../src/list/single/list.h"
#include "../src/utils/utils.h"

void list_info(List *list);

int main(void) {

  int values[] = {10, 4, 6, 8, 9, 80, 288};
  int status = 0;
  int l = sizeof(values)/sizeof(values[0]);
  ListElmt *element;
  void **value = (void **)malloc(sizeof(int));
  List* MyList;

  MyList = (List *)malloc(sizeof(List));
  if (MyList == NULL) {
    printf("Unable to allocate memory for the list!\n");
    return EXIT_FAILURE;
  }

  // Test list_init()
  printf("Initilizing the list...\n");
  list_init(MyList, destroy);

  // Tests macro: list_size, list_head and list_tail
  list_info(MyList);

  // Test list_ins_next()
  printf("Inserting %d elements into the list...\n", l);
  for (int i = 0; i < l; i++) {
    if (status != 0) {
      printf("Insert operation has failed!\n");
      break;
    }

    if (i == 0) {
      printf("Adding element %d (%d) to the list!\n", i, values[i]);
      status = list_ins_next(MyList, NULL, (values + i));
      element = MyList->head;
    }
    else {
      printf("Adding element %d (%d) to the list!\n", i, values[i]);
      status = list_ins_next(MyList, element, (values + i));
      element = element->next;
    }
  }

  list_info(MyList);

  // Test list_rem_next()
  printf("Deleting %d elements from the list...\n", l);
  for (int j = 0; j < l; j++) {
    status = list_rem_next(MyList, NULL, value);
    printf("Element %d is deleted from the list!\n", **(int **)value);
  }

  list_info(MyList);

  // Tests list_destroy()
  printf("Destroying the list...\n");
  list_destroy(MyList);
  free(MyList);

  return EXIT_SUCCESS;
}

void list_info(List *list) {
  printf("\n\n");
  printf("* * * BEGIN LLIST INFO * * *");
  printf("\nSize:\t%d", list_size(list));
  printf("\nHead:\t%p", list_head(list));
  printf("\nTail:\t%p", list_tail(list));
  printf("\n* * * END LLIST INFO * * *");
  printf("\n\n");
}
