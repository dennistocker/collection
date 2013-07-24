#ifndef _RINGBUF_H
#define _RINGBUF_H

#include <stdlib.h>

typedef struct ringbuf_t_ {
    size_t len;
    size_t start;
    size_t end;
    char buf[0];
} ringbuf_t;


ringbuf_t * ringbuf_create(size_t size);

void ringbuf_destroy(ringbuf_t *rb);


ssize_t ringbuf_read(ringbuf_t *rb, char *target, size_t len);

ssize_t ringbuf_write(ringbuf_t *rb, const char *data, size_t len);


static inline void ringbuf_clear(ringbuf_t *rb)
{
    rb->start = rb->end = 0;
}

static inline size_t ringbuf_used(ringbuf_t *rb)
{
    return (rb->len + rb->end - rb->start) % rb->len;
}

static inline size_t ringbuf_unused(ringbuf_t *rb)
{
    return (rb->len + rb->start - rb->end - 1) % rb->len;
}

static inline int ringbuf_empty(ringbuf_t *rb)
{
    return rb->start == rb->end;
}

static inline int ringbuf_full(ringbuf_t *rb)
{
    return (rb->end + 1) % rb->len == rb->start;
}


#endif
