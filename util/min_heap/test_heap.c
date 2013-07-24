#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "min_heap.h"

int compare(const void *node1, const void *node2)
{
    return ((size_t)node1 - (size_t)node2);
}

int main(int argc, char **argv)
{
    size_t i;
    min_heap_t *h;

    srandom(time(0));

    h = min_heap_create(10, compare);
    assert(h);
    for (i = 0; i < 100; ++i) {
        size_t data = random() % 10000;
        printf("push: %zd\n", data);
        min_heap_push(h, (void*)data);
    }

    min_heap_dump(h);

    while (min_heap_used(h)) {
        printf("pop: %zd\n", min_heap_pop(h));
    }
    printf("size: %zd\n", min_heap_size(h));
    min_heap_destroy(h);

    return 0;
}
