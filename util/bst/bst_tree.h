#ifndef _BST_TREE_H
#define _BST_TREE_H

typedef int key_t;

typedef struct bst_t_ bst_t;

typedef int (*cmp_t)(key_t *key1, key_t *key2);

typedef int (*walk_cb_t)(bst_t tree, key_t key, void *value, void *arg);


bst_t *bst_create();

void bst_destroy(bst_t *tree);

void *bst_search(bst_t tree, key_t key);

int bst_insert(bst_t tree, key_t key, void *value);

void *bst_delete(bst_t tree, key_t key);

int bst_walk(bst_t tree, walk_cb_t walk, void *arg);

void *bst_mininum(bst_t tree);

void *bst_maxinum(bst_t tree);

void *bst_successor(bst_t tree);

void *bst_predecessor(bst_t tree);

#endif

