#include <stdlib.h>
#include <string.h>

#include "avl.h"

/* Allocation */

avl *avl_create_root(void *key, void *value, int (*match)(void *key1, void *key2)) {
  avl *root;
  if ((root = (avl *)malloc(sizeof(avl))) == NULL) {
    return NULL;
  }

  root->key = key;
  root->value = value;
  root->height = 1; // initially a leaf node
  root->left = NULL;
  root->right = NULL;
  root->match = match;

  return root;
}

avl *avl_create_empty_root(int (*match)(void *key1, void *key2)) {
    return avl_create_root(NULL, NULL, match);
}

/* Helpers */

avl *avl_smallest_key(avl *root) {
  return root->left ? avl_smallest_key(root->left) : root;
}

int avl_height(avl *root) {
  return root ? root->height : 0;
}

int avl_balance_factor(avl *root) {
  return root ? avl_height(root->left) - avl_height(root->right) : 0;
}

/* Operations */

avl *avl_insert(avl *root, void *key, void *value) {
  /* 
  AVL extension to the BST insertion function:
  Insert as in BST, rebalance if necessary.
  */
  avl *new_root = bst_insert(root, key, value);
  new_root = avl_rebalance(new_root);
  return new_root;
}

avl *avl_remove(avl *root, void *key) {
  /* 
  AVL extension to the BST removal function:
  Remove as in BST, rebalance if necessary.
  */
  avl *new_root = bst_remove(root, key);
  new_root = avl_rebalance(new_root);
  return new_root;
}

avl *bst_insert(avl *root, void *key, void *value) {
  if (!root->key) {
    /* Null values, simply assign. */
    root->key = key;
    root->value = value;
    root->height = 1;
    return root;
  }

  if (root->match(key, root->key) < 0)
  {
    /* New key less than stored key, insert to the left. */
    if (root->left) {
      /* Traverse down */
      root->left = avl_insert(root->left, key, value);
    }
    else {
      /* Create new node. */
      root->left = avl_create_root(key, value, root->match);
    }
  }
  else {
    /* New key greater than or equal to stored key, insert to the right. */
    if (root->right) {
      /* Traverse down. */
      root->right = avl_insert(root->right, key, value);
    }
    else {
      /* Create a new node. */
      root->right = avl_create_root(key, value, root->match);
    }
  }
  avl_recalc_height(root);
  return root;
}

avl *bst_remove(avl *root, void *key) {
  int cmp = root->match(key, root->key);
  if (cmp < 0) {
    /* Target less than stored key, look left */
    if (root->left) {
      /* Traverse to the left, then recalculate heights */
      root->left = avl_remove(root->left, key);
      avl_recalc_height(root->left);
    }
  }
  else if (cmp > 0) {
    /* Target greater than stored key, look right */
    if (root->right) {
      /* Traverse to the right, then recalculate heights. */
      root->right = avl_remove(root->right, key);
      avl_recalc_height(root->right);
    }
  }
  else {
    /* Target key found. */

    /* Case 1: leaf node, simply delete.  */
    if (!root->left && !root->right) {
      free(root);
      return NULL;
    }

    /* Case 2: the node has one child, substitute with the child. */
    if (root->left && !root->right) {
      /* Only child is on the left. */
      avl *node = root->left;
      free(root);
      return node;
    }
    else if (!root->left && root->right) {
      /* Only child is on the right. */
      avl *node = root->right;
      free(root);
      return node;
    }

    /* 
    Case 3: the node has both children: 
    substitute with in-order successor,
    recursively delete the in-order successor from the right subtree.
    */
    avl *sub = avl_smallest_key(root->right);
    root->key = sub->key;
    root->value = sub->value;
    root = avl_remove(root->right, root->key);
  }
  avl_recalc_height(root);
  return root;
}

avl *avl_rebalance(avl *root) {
  int bf = avl_balance_factor(root);

  if (bf < -1 || bf > 1) {
    /* Case 1: left-Left, i.e. left heavy, left child is balanced or left heavy */
    if (bf > 1 && avl_balance_factor(root->left) >= 0) {
      /* Rotate right around the root. */
      root = avl_rotate_right(root);
    }
    /* Case 2: left-right, i.e. left heavy, left child is right heavy. */
    else if (bf > 1) {
      /* Rotate left around the left child. */
      root->left = avl_rotate_left(root->left);
      /* Now left-left, so rotate right around the root. */
      root = avl_rotate_right(root);
    }
    /* Case 3: right-right, i.e. right heavy, right child is balanced or right heavy. */
    else if (bf < -1 && avl_balance_factor(root->right) <= 0) {
      /* Roatate left around the root. */
      root = avl_rotate_left(root);
    }
    /* Case 4: right-left, i.e. right heavy, right child is left heavy. */
    else {
      /* Roatate right around the right child. */
      root->right = avl_rotate_right(root->right);
      /* Now right-right, so rotate left around the root. */
      root = avl_rotate_left(root);
    }
  }
  return root;
}

avl *avl_rotate_right(avl *root) {
  if (!root->left) {
    return root;
  }
  avl *new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;

  avl_recalc_height(root);
  avl_recalc_height(new_root);

  return new_root;
}

avl *avl_rotate_left(avl *root) {
  if (!root->right) {
    return root;
  }
  avl *new_root = root->right;
  root->right = new_root->left;
  new_root->left = root;

  avl_recalc_height(root);
  avl_recalc_height(new_root);

  return new_root;
}

void avl_recalc_height(avl *root) {
  if (root) {
    int left_height = avl_height(root->left);
    int right_height = avl_height(root->right);

    root->height = 1 + left_height > right_height ? left_height : right_height;
  }
}

void* avl_get(avl* root, void* key) {
  if (!root || !root->key) {
    return NULL;
  }

  char cmp = root->match(key, root->key);

  if (!cmp) {
    /* Key is found. */
    return root->value;
  }
  else if (cmp > 0) {
    /* Traverse to the right. */
    return root->right ? avl_get(root->right, key) : NULL;
  }
  else { // cmp < 0
    /* Traverse to the left. */
    return root->left ? avl_get(root->left, key) : NULL;
  }
}

/* Traversing */

void avl_inorder_traverse(avl *root, void (*visit)(avl *node)) {
  if (root->left) {
    avl_inorder_traverse(root->left, visit);
  }

  visit(root);

  if (root->right) {
    avl_inorder_traverse(root->right, visit);
  }
}

void avl_preorder_traverse(avl *root, void (*visit)(avl *node)) {
  visit(root);

  if (root->left) {
    avl_preorder_traverse(root->left, visit);
  }

  if (root->right) {
    avl_preorder_traverse(root->right, visit);
  }
}

void avl_postorder_traverse(avl *root, void (*visit)(avl *node)) {
  if (root->left) {
    avl_postorder_traverse(root->left, visit);
  }

  if (root->right) {
    avl_postorder_traverse(root->right, visit);
  }
  visit(root);
}

/* Freeing */

void avl_free_node(avl *node) {
  free(node);
}

void avl_free_node_deep(avl *node) {
  if (node) {
    if (node->key) {
      free(node->key);
    }

    if (node->value) {
      free(node->value);
    }

    free(node);
  }
}

void avl_free_node_key(avl *node) {
  if (node) {
    if (node->key) {
      free(node->key);
    }
    free(node);
  }
}

void avl_free_node_value(avl *node) {
  if (node) {
    if (node->value) {
      free(node->value);
    }
    free(node);
  }
}

void avl_free_subtree(avl *root) {
  return avl_postorder_traverse(root, avl_free_node);
}

void avl_free_subtree_deep(avl *root) {
  return avl_postorder_traverse(root, avl_free_node_deep);
}

void avl_free_subtree_key(avl *root) {
  return avl_postorder_traverse(root, avl_free_node_key);
}

void avl_free_subtree_value(avl *root) {
  return avl_postorder_traverse(root, avl_free_node_value);
}
