/* This is a test driver program for the AVL trees tests. */
#include <stdio.h>
#include <stdlib.h>

#include "../src/tree/avl/avl.h"

void print_node_info(avl *node);

int main(int argc, char const *argv[]) {
  int vals[] = {44, 17, 62, 32, 50, 78, 48, 54, 88};

  printf("Initilizing...\n");

  avl *root = avl_create_empty_root(int_match);
  for (int i = 0; i < 9; i++) {
    root = avl_insert(root, vals + i, vals + i);
  }

  int val = 32;
  root = avl_remove(root, &val);

  avl_preorder_traverse(root, print_node_info);

  printf("Freeing...\n");
  avl_free_node(root);

  printf("Done!\n");

  return 0;
}

void print_node_info(avl *node) {
  printf("{ KEY %d: VALUE %d; HEIGHT %d; LNODE: %d; RNODE: %d; }\n",
         *((int *)node->key), *((int *)node->value),
         node->height,
         node->left ? *((int *)node->left->key) : -1,
         node->right ? *((int *)node->right->key) : -1);
}
