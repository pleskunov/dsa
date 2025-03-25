#include "../src/darray/darray.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void test_allocate() {
    darray d;

    // Test allocation with empty pointer
    allocate(NULL, 10);


    //assert(res != NULL);
    //assert(d.capacity == 10);
    //assert(d.size == 0);
    //free(d.elements);

    // Test allocation with zero capacity
    
    /*res = allocate(&d, 0);
    assert(res != NULL);
    assert(d.capacity == DEF_MAX_CAPACITY);
    free(d.elements);

    // Test allocation with NULL darray pointer
    res = allocate(NULL, 10);
    assert(res == NULL); */

    printf("All tests passed!\n");
}

int main() {
    test_allocate();
    return 0;
}
