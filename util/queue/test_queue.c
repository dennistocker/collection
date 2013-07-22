#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

int main(int argc, char **argv)
{
    int ret;
    size_t i;
    void *data;
    queue_t *q;

    q = queue_create();
    for (i = 0; i < 100; ++i) {
        ret = queue_push(q, (void*)i);
    }
    while (queue_size(q)) {
        data = queue_peek(q);
        printf("peek: %ld\n", (size_t)data);

        data = queue_pop(q);
        printf("pop: %ld\n", (size_t)data);
    }
    queue_destroy(q);

    return 0;
}
