#ifndef _HASH_H
#define _HASH_H

#include <stdlib.h>

typedef struct hash_t_ hash_t;


typedef int (*walk_cb_t)(hash_t *hash, void *key, size_t key_len, void *value, void *arg);


hash_t * hash_create(size_t size);

void hash_destroy(hash_t *hash);

void * hash_get(hash_t *hash, const void *key, size_t key_len);

int hash_set(hash_t *hash, const void *key, size_t key_len, void *value);

int hash_delete(hash_t *hash, const void *key, size_t key_len);

int hash_walk(hash_t *hash, walk_cb_t walk, void *arg);

#endif
