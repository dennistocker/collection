#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

typedef ringbuf_t_ {
    size_t len;
    size_t start;
    size_t end;
    char buf[];
} ringbuf_t;


ringbuf_t * ringbuf_create(size_t size);

void ringbuf_destroy(ringbuf_t *rb);


int ringbuf_read(ringbuf_t *rb, char *target, size_t len);

int ringbuf_write(ringbuf_t *rb, const char *data, size_t len);

void ringbuf_clear(ringbuf_t *rb);


size_t ringbuf_used(ringbuf_t *rb);

size_t ringbuf_free(ringbuf_t *rb);

int ringbuf_empty(ringbuf_t *rb);

int ringbuf_full(ringbuf_t *rb);


static inline void ringbuf_clear(ringbuf_t *rb)
{
    rb->start = rb->end = 0;
}

static inline size_t ringbuf_used(ringbuf_t *rb)
{
    return (rb->len + rb->end - rb->start) % rb->len;
}

static inline size_t ringbuf_free(ringbuf_t *rb)
{
    return (rb->len + rb->start - rb->end) % rb->len;
}

static inline int ringbuf_empty(ringbuf_t *rb)
{
    return !(ringbuf_free(rb));
}

static inline int ringbuf_full(ringbuf_t *rb)
{
    return !(ringbuf_used(rb));
}


#endif
