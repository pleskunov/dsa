#pragma once

#include "../../utils/utils.h"

/* Define structure for an AVL node. */
typedef struct avl_ {
  void            *key;
  void            *value;
  int             height;
  struct avl_     *left;
  struct avl_     *right;
  int             (*match)(void *key1, void *key2);
} avl;

/* Allocation */

/* Create a root node with the key and the value. */
avl *avl_create_root(void *key, void *value, int (*match)(void *key1, void *key2));

/* Create a root node with the null key and value. */
avl *avl_create_empty_root(int (*match)(void *key1, void *key2));

/* Helpers */

/* Find the smallest key in a subtree (in-order successor).  */
avl *avl_smallest_key(avl *root);

/* Get the height of a root. */
int avl_height(avl *root);

/* Calculate the balance factor of a root. */
int avl_balance_factor(avl *root);

/* Operations */

/* Insert a node into the AVL tree. */
avl *avl_insert(avl *root, void *key, void *value);

/* Remove a node from the AVL tree. */
avl *avl_remove(avl *root, void *key);

/* Insert a node into the BST tree. */
avl *bst_insert(avl *root, void *key, void *value);

/* Remove a node from the BST tree. */
avl *bst_remove(avl *root, void *key);

/* Rebalance the AVL tree. */
avl *avl_rebalance(avl *root);

/* Rotate right around a root */
avl *avl_rotate_right(avl *root);

/* Rotate left around a root */
avl *avl_rotate_left(avl *root);

/* Calcualte the height of a root considering the children's heights. */
void avl_recalc_height(avl *root);

/* Get the value stored with a key */
void* avl_get(avl* root, void* key);

/* Traversing */

/* Inorder */
void avl_inorder_traverse(avl *root, void (*visit)(avl *node));

/* Preorder */
void avl_preorder_traverse(avl *root, void (*visit)(avl *node));

/* Postorder */
void avl_postorder_traverse(avl *root, void (*visit)(avl *node));

/* Freeing */

/* Free memory allocated for the node. */
void avl_free_node(avl *node);

/* Free memory allocated for key, value, and the node. */
void avl_free_node_deep(avl *node);

/* Free memory allocated for the key. */
void avl_free_node_key(avl *node);

/* Free memory allocated for value and the node. */
void avl_free_node_value(avl *node);

/* Free memory allocated for the subtree. */
void avl_free_subtree(avl *root);

/* Free memory allocated for the subtree, including keys and values. */
void avl_free_subtree_deep(avl *root);

/* Free memory allocated for the subtree, including keys. */
void avl_free_subtree_key(avl *root);

/* Free memory allocated for the subtree, including values. */
void avl_free_subtree_value(avl *root);
