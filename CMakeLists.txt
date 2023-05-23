cmake_minimum_required(VERSION 3.26)

project(dsa VERSION 1.0 DESCRIPTION "Data structures & algorithms in C.")

# utils
add_library(utils)
target_sources(utils
  PUBLIC
    src/utils/utils.h
  PRIVATE
    src/utils/utils.c
  )
target_include_directories(utils
  PUBLIC
    src/utils
  )

# single linked-list
add_library(list)
target_sources(list
  PUBLIC
    src/list/single/list.h
  PRIVATE
    src/list/single/list.c
  )
target_include_directories(list
  PUBLIC
    src/list/single
  )
# list depends on the utils
target_link_libraries(list PRIVATE utils)

# double linked-list
add_library(dlist)
target_sources(dlist
  PUBLIC
    src/list/double/dlist.h
  PRIVATE
    src/list/double/dlist.c
  )
target_include_directories(dlist
  PUBLIC
    src/list/double
  )
# dlist depends on the utils
target_link_libraries(dlist PRIVATE utils)

# circular linked-list
add_library(clist)
target_sources(clist
  PUBLIC
    src/list/circular/clist.h
  PRIVATE
    src/list/circular/clist.c
  )
target_include_directories(clist
  PUBLIC
    src/list/circular
  )
# clist depends on the utils
target_link_libraries(clist PRIVATE utils)

# stack
add_library(stack)
target_sources(stack
  PUBLIC
    src/stack/stack.h
  PRIVATE
    src/stack/stack.c
  )
target_include_directories(stack
  PUBLIC
    src/stack
  )
# stack depends on the linked-list
target_link_libraries(stack PRIVATE list)

# queue
add_library(queue)
target_sources(queue
  PUBLIC
    src/queue/queue.h
  PRIVATE
    src/queue/queue.c
  )
target_include_directories(queue
  PUBLIC
    src/queue
  )
# queue depends on the linked-list
target_link_libraries(queue PRIVATE list)

# set
add_library(set)
target_sources(set
  PUBLIC
    src/set/set.h
  PRIVATE
    src/set/set.c
  )
target_include_directories(set
  PUBLIC
    src/set
  )
# set depends on the linked-list
target_link_libraries(set PRIVATE list)

# binary search tree (in progress)
#add_library(bst)
#target_sources(bst
#  PUBLIC
#    src/tree/bst/bst.h
#  PRIVATE
#    src/tree/bst/bst.c
#  )
#target_include_directories(bst
#  PUBLIC
#    src/tree/bst
#  )

# avl search tree
add_library(avl)
target_sources(avl
  PUBLIC
    src/tree/avl/avl.h
  PRIVATE
    src/tree/avl/avl.c
  )
target_include_directories(avl
  PUBLIC
    src/tree/avl
  )
# clist depends on the utils
target_link_libraries(avl PRIVATE utils)

add_subdirectory(tests)
