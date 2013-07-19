#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define slot_num sizeof(slot_size) / sizeof(slot_size[0])

static size_t slot_size[] = {
    /* primers */
    7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191,
    16381, 32749, 65521, 131071,
    /* switching to just 2^n-1, */
    262143, 524287, 1048575, 2097151, 4194303, 8388607,
    16777211, 33554431, 67108863, 134217727, 268435455,
    536870911, 1073741823, 2147483647
};

/* struct */
typedef struct hash_entry_t_ hash_entry_t;

struct hash_entry_t_ {
    hash_entry_t *next;
    const void *key;
    size_t key_len;
    void *value;
};

struct hash_t_ {
    hash_entry_t **slots;
    size_t used_slots;
    size_t slot_size_index;
};

/* internal functions */
static size_t hash_func(const void *key, size_t key_len)
{
    size_t i, hash = 0;
    const char *p = key;

    for (i = 0; i < key_len; ++i) {
        hash = (hash << 5) + hash + *p++;
    }

    return hash;
}

static int resize_up(hash_t *hash)
{
    size_t i, hash_val;
    hash_entry_t **new_slots, *e, *e_next;

    if (!hash) {
        return -1;
    }

    if (hash->slot_size_index == slot_num) {
        return 0;
    }
    ++hash->slot_size_index;

    new_slots = calloc(slot_size[hash->slot_size_index], sizeof(*new_slots));
    if (!new_slots) {
        return -1;
    }

    for (i = 0; i < slot_size[hash->slot_size_index-1]; ++i) {
        e = hash->slots[i];
        while (e) {
            hash_val = hash_func(e->key, e->key_len) %
                slot_size[hash->slot_size_index];
            e_next = e->next;
            e->next = new_slots[hash_val];
            new_slots[hash_val] = e;
            e = e_next;
        }
    }

    free(hash->slots);
    hash->slots = new_slots;

    return 0;
}

/* functions */
hash_t* hash_create(size_t size)
{
    hash_t *hash;

    hash = calloc(1, sizeof(*hash));
    if (!hash) {
        return NULL;
    }

    while (slot_size[hash->slot_size_index] < size &&
            hash->slot_size_index < slot_num - 1) {
        ++hash->slot_size_index;
    }
    hash->slots = calloc(slot_size[hash->slot_size_index], sizeof(*hash->slots));
    if (!hash->slots) {
        free(hash);
        return NULL;
    }

    return hash;
}

void hash_destroy(hash_t *hash)
{
    size_t i;
    hash_entry_t *e, *e_next;

    if (!hash) {
        return;
    }

    for (i = 0; i < slot_size[hash->slot_size_index]; ++i) {
        e = hash->slots[i];
        while (e) {
            e_next = e->next;
            free(e);
            e = e_next;
        }
    }
    free(hash->slots);
    free(hash);
}

void* hash_get(hash_t *hash, const void *key, size_t key_len)
{
    size_t hash_val;
    hash_entry_t *e;

    if (!hash || !key) {
        return NULL;
    }

    key_len = key_len ? key_len : strlen(key) + 1;
    hash_val = hash_func(key, key_len) % slot_size[hash->slot_size_index];
    e = hash->slots[hash_val];
    while (e) {
        if (e->key_len == key_len && memcmp(e->key, key, key_len) == 0) {
            return e->value;
        }
        e = e->next;
    }

    return NULL;
}

int hash_set(hash_t *hash, const void *key, size_t key_len, void *value)
{
    size_t hash_val;
    hash_entry_t *e, *e_new;

    if (!hash || !key) {
        return -1;
    }

    if (hash->used_slots * 2 > slot_size[hash->slot_size_index]) {
        if (resize_up(hash) != 0) {
            return -1;
        }
    }

    e_new = calloc(1, sizeof(*e_new));
    if (!e_new) {
        return -1;
    }

    key_len = key_len ? key_len : strlen(key) + 1;
    hash_val = hash_func(key, key_len) % slot_size[hash->slot_size_index];
    e = hash->slots[hash_val];

    e_new->next = e;
    e_new->key = key;
    e_new->key_len = key_len;
    e_new->value = value;
    hash->slots[hash_val] = e_new;
    ++hash->used_slots;

    return 0;
}

int hash_delete(hash_t *hash, const void *key, size_t key_len)
{
    hash_entry_t **e, *e_del;
    size_t hash_val;

    if (!hash || !key) {
        return -1;
    }

    key_len = key_len ? key_len : strlen(key) + 1;
    hash_val = hash_func(key, key_len) % slot_size[hash->slot_size_index];
    e = hash->slots + hash_val;

    while (*e) {
        if ((*e)->key_len == key_len && memcmp((*e)->key, key, key_len) == 0) {
            e_del = *e;
            *e = (*e)->next;
            free(e_del);
            --hash->used_slots;
            return 0;
        }
        e = &((*e)->next);
    }

    return -1;
}

int hash_walk(hash_t *hash, walk_cb_t walk, void *arg)
{
    int del;
    size_t i;
    hash_entry_t *e, *e_next;
    if (!hash || !walk) {
        return -1;
    }

    for (i = 0; i < slot_size[hash->slot_size_index]; ++i) {
        e = hash->slots[i];
        while (e) {
            e_next = e->next;
            walk(hash, (void *)e->key, e->key_len, e->value, arg);
            e = e_next;
        }
    }

    return 0;
}

