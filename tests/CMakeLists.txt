set(CMAKE_BUILD_TYPE Debug)

# single linked-list test
add_executable(test-list test-list.c)
target_link_libraries(test-list PRIVATE list)

# double linked-list test
add_executable(test-dlist test-dlist.c)
target_link_libraries(test-dlist PRIVATE dlist)

# circular linked-list test
add_executable(test-clist test-clist.c)
target_link_libraries(test-clist PRIVATE clist)

# stack test
add_executable(test-stack test-stack.c)
target_link_libraries(test-stack PRIVATE stack list)

# queue test
add_executable(test-queue test-queue.c)
target_link_libraries(test-queue PRIVATE queue list)

# set test
add_executable(test-set test-set.c)
target_link_libraries(test-set PRIVATE set list)

# avl binary tree test
add_executable(test-avl test-avl.c)
target_link_libraries(test-avl PRIVATE avl)
