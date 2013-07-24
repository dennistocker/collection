#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include <stdlib.h>

typedef struct min_heap_t_ min_heap_t;

typedef int (*cmp_t)(const void *node1, const void *node2);


min_heap_t *min_heap_create(size_t size, cmp_t cmp);

void min_heap_destroy(min_heap_t *heap);

int min_heap_push(min_heap_t *heap, void *node);

void *min_heap_pop(min_heap_t *heap);

void min_heap_dump (min_heap_t *heap);

size_t min_heap_size(min_heap_t *heap);

size_t min_heap_used(min_heap_t *heap);

#endif

