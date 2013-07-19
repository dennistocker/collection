#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "hash.h"

int walk(hash_t *hash, void *key, size_t key_len, void *value, void *arg)
{
    printf("key: %.*s\n", key_len, key);
    printf("value: %s\n", value);
    hash_delete(hash, key, key_len);
    free((void *)key);
    free(value);
}

int main(int argc, char **argv)
{
    int i, ret;
    hash_t *h;

    h = hash_create(100);
    assert(h);
    printf("set:\n");
    for (i = 0; i < 1000; ++i) {
        char *key = calloc(1, 10);
        char *value = calloc(1, 100);
        assert(key && value);
        snprintf(key, 10, "%d", i);
        snprintf(value, 100, "value-%d", i);
        printf("%s=>%s\n", key, value);
        ret = hash_set(h, key, 0, value);
        assert(ret == 0);
    }
    srand(time(NULL));
    printf("get:\n");
    for (i = 0; i < 100; ++i) {
        int index = random() % 2000;
        char key[10];
        snprintf(key, sizeof(key), "%d", index);
        char *value = hash_get(h, key, 0);
        printf("%s=>%s\n", key, value);
        char tmp[100];
        snprintf(tmp, sizeof(tmp), "value-%d", index);
        if (index >= 1000) {
            assert(!value);
        } else {
            assert(strcmp(value, tmp) == 0);
        }
    }
    printf("walk:\n");
    hash_walk(h, walk, NULL);
    hash_destroy(h);

    return 0;
}

