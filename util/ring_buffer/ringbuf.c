#include <string.h>

#include "ringbuf.h"

#define MIN(a, b) (((a) <= (b)) ? (a) : (b))

ringbuf_t * ringbuf_create(size_t size)
{
    ringbuf_t *rb;

    if (!size) {
        return NULL;
    }
    rb = calloc(1, sizeof(*rb) + size + 1);
    if (!rb) {
        return NULL;
    }
    rb->len = size;

    return rb;
}

void ringbuf_destroy(ringbuf_t *rb)
{
    free(rb);
}

ssize_t ringbuf_read(ringbuf_t *rb, char *target, size_t len)
{
    size_t used, tail_len;

    if (!rb || !target) {
        return -1;
    }
    used = ringbuf_used(rb);
    len = MIN(len, used);
    tail_len = rb->len - rb->start + 1;
    tail_len = MIN(len, tail_len);
    memcpy(target, rb->buf + rb->start, tail_len);
    if (len - tail_len > 0) {
        memcpy(target + tail_len, rb->buf, len - tail_len);
    }
    rb->start = (rb->start + len) % rb->len;

    return len;
}

ssize_t ringbuf_write(ringbuf_t *rb, const char *data, size_t len)
{
    size_t unused, tail_len;

    if (!rb || !data) {
        return -1;
    }
    unused = ringbuf_unused(rb);
    len = MIN(len, unused);
    tail_len = rb->len - rb->end + 1;
    tail_len = MIN(len, tail_len);
    memcpy(rb->buf + rb->end, data, tail_len);
    if (len - tail_len > 0) {
        memcpy(rb->buf, data + tail_len, len - tail_len);
    }
    rb->end = (rb->end + len) % rb->len;

    return len;
}

