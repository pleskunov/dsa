#include <stdio.h>
#include <stdlib.h>
#include "../src/list/circular/clist.h"
#include "../src/utils/utils.h"

void clist_info(CList *list);

int main(void) {

  int values[] = {10, 4, 6, 8, 9, 80, 288};
  int status = 0;
  int l = sizeof(values)/sizeof(values[0]);
  CListElmt *element;
  void **value = (void **)malloc(sizeof(int));
  CList* MyList;

  MyList = (CList *)malloc(sizeof(CList));
  if (MyList == NULL) {
    printf("Unable to allocate memory for the list!\n");
    return EXIT_FAILURE;
  }

  // Test clist_init()
  printf("Initilizing the list...\n");
  clist_init(MyList, destroy);

  // Tests macro: clist_size, clist_head and clist_tail
  clist_info(MyList);

  // Test clist_ins_next()
  printf("Inserting %d elements into the list...\n", l);
  for (int i = 0; i < l; i++) {
    if (status != 0) {
      printf("Insert operation has failed!\n");
      break;
    }

    if (i == 0) {
      printf("Adding element %d (%d) to the list!\n", i, values[i]);
      status = clist_ins_next(MyList, NULL, (values + i));
      element = MyList->head;
    }
    else {
      printf("Adding element %d (%d) to the list!\n", i, values[i]);
      status = clist_ins_next(MyList, element, (values + i));
      element = element->next;
    }
  }

  clist_info(MyList);

  // Test clist_rem_next()
  printf("Deleting %d elements from the list...\n", l);
  for (int j = 0; j < l; j++) {
    status = clist_rem_next(MyList, MyList->head, value);
    printf("Element %d is deleted from the list!\n", **(int **)value);
  }

  clist_info(MyList);

  // Tests clist_destroy()
  printf("Destroying the list...\n");
  clist_destroy(MyList);
  free(MyList);

  return EXIT_SUCCESS;
}

void clist_info(CList *list) {
  printf("\n\n");
  printf("* * * BEGIN LLIST INFO * * *");
  printf("\nSize:\t%d", clist_size(list));
  printf("\nHead:\t%p", clist_head(list));
  printf("\n* * * END LLIST INFO * * *");
  printf("\n\n");
}
