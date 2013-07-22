#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "ringbuf.h"

int main(int argc, char **argv)
{
    int i, j;
    size_t size;
    ringbuf_t *rb;

    srandom(time(0));
    size = random();
    size = random() % (1*1024*1024);
    printf("%ld\n", size);
    rb = ringbuf_create(size);
    assert(rb);

    for (j = 0; j < 3; ++j) {
        i = 0;
        while (ringbuf_unused(rb) >= sizeof(i)) {
            ++i;
            assert(ringbuf_write(rb, (char*)&i, sizeof(i)) == sizeof(i));
        }

        i = 0;
        char data[4];
        while(!ringbuf_empty(rb)) {
            ++i;
            assert(ringbuf_read(rb, data, sizeof(data)) == sizeof(data));
            assert(*((int*)data) == i);
        }
    }
    ringbuf_destroy(rb);

    return 0;
}
