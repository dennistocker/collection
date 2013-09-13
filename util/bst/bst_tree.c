#include <stdlib.h>

#include "bst_tree.h"

typedef struct node_t_ node_t;

struct node_t_ {
    const void *key;
    void *value;
    node_t *l, *r;
};

struct bst_t_ {
    node_t *root;
    cmp_t cmp;
};


bst_t bst_create()
{
    bst_t tree;

    tree = calloc(1, sizeof(*tree));

    return tree;
}

void bst_destroy(bst_t tree)
{
    if (tree) {
        bst_destroy(tree->l);
        bst_destroy(tree->r);
        free(tree);
    }
}

void *bst_search(bst_t tree, key_t key)
{

}

int bst_insert(bst_t tree, key_t key, void *data)
{
}

void *bst_delete(bst_t tree, key_t key)
{

}

int bst_walk(bst_t tree, walk_cb_t walk, void *arg)
{

}

void *bst_mininum(bst_t tree)
{

}

void *bst_maxinum(bst_t tree)
{

}

void *bst_successor(bst_t tree)
{

}

void *bst_predecessor(bst_t tree)
{
}

