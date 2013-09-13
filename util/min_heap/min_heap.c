#include <stdio.h>

#include "min_heap.h"

#define ALIGN_SIZE 8
#define ALIGN(x, n) (((x) + (n) - 1) & (~(n-1)))

struct min_heap_t_ {
    void **nodes;
    size_t size;
    size_t used;
    cmp_t cmp;
};

static inline int min_heap_reserve(min_heap_t *heap, size_t size)
{
    void *ptr;

    if (heap->size < size) {
        heap->size *= 2;
        if (heap->size < size) {
            heap->size = size;
        }
        ptr = realloc(heap->nodes, heap->size * sizeof(void*));
        if (!ptr) {
            return -1;
        } else {
            heap->nodes = ptr;
        }
    }

    return 0;
}

static inline void min_heap_shift_up(min_heap_t *heap, size_t index)
{
    size_t parent = (index - 1) / 2;
    void *node = heap->nodes[index];

    while (index && heap->cmp(node, heap->nodes[parent]) < 0) {
        heap->nodes[index] = heap->nodes[parent];
        index = parent;
        parent = (index - 1) / 2;
    }
    heap->nodes[index] = node;
}

static void min_heap_shift_down(min_heap_t *heap, size_t index)
{
    size_t child = 2 * (index + 1);
    void *node = heap->nodes[index];

    while (child <= heap->used) {
        if ((child == heap->used) ||
                (heap->cmp(heap->nodes[child-1], heap->nodes[child]) < 0)) {
            --child;
        }
        if (heap->cmp(node, heap->nodes[child]) < 0) {
            break;
        }
        heap->nodes[index] = heap->nodes[child];
        index = child;
        child = 2 * (index + 1);
    }
    heap->nodes[index] = node;
}

min_heap_t *min_heap_create(size_t size, cmp_t cmp)
{
    min_heap_t *heap;

    heap = calloc(1, sizeof(*heap));
    if (!heap) {
        return NULL;
    }
    size = ALIGN(size, ALIGN_SIZE);
    heap->nodes = calloc(size, sizeof(void*));
    if (!heap->nodes) {
        free(heap);
        return NULL;
    }
    heap->size = size;
    heap->used = 0;
    heap->cmp = cmp;

    return heap;
}

void min_heap_destroy(min_heap_t *heap)
{
    if (heap) {
        free(heap->nodes);
        free(heap);
    }
}

int min_heap_push(min_heap_t *heap, void *node)
{
    if (!heap || min_heap_reserve(heap, heap->used + 1) != 0) {
        return -1;
    }
    heap->nodes[heap->used++] = node;
    min_heap_shift_up(heap, heap->used - 1);

    return 0;
}

void *min_heap_pop(min_heap_t *heap)
{
    void *node= NULL;

    if (heap && heap->used > 0) {
        node = heap->nodes[0];
        heap->nodes[0] = heap->nodes[--heap->used];
        min_heap_shift_down(heap, 0);
    }

    return node;
}

void min_heap_dump(min_heap_t *heap)
{
    size_t i;

    if (!heap) {
        return;
    }

    printf("size: %zd\n", heap->size);
    printf("used: %zd\n", heap->used);
    for (i = 0; i < heap->used; ++i) {
        printf("%zd: %d\n", i, heap->nodes[i]);
    }
}

size_t min_heap_size(min_heap_t *heap)
{
    return heap ? heap->size : 0;
}

size_t min_heap_used(min_heap_t *heap)
{
    return heap ? heap->used : 0;
}
