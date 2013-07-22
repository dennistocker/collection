#include <stdlib.h>
#include "queue.h"

#define QUEUE_CACHE_LIMIT 1024

struct queue_node_t_ {
    queue_node_t *next;
    void *data;
};

struct queue_t_ {
    int size;
    int csize;
    queue_node_t *tail;
    queue_node_t *ctail;
};

static queue_node_t * get_cache_node(queue_t *q)
{
    queue_node_t *node;

    if (!q || !q->csize) {
        return NULL;
    }

    node = q->ctail->next;
    if (q->csize == 1) {
        q->ctail = NULL;
    } else {
        q->ctail->next = node->next;
    }
    --q->csize;

    return node;
}

static int save_cache_node(queue_t *q, queue_node_t *node)
{
    if (!q || !node) {
        return -1;
    }

    if (q->csize >= QUEUE_CACHE_LIMIT - 1) {
        free(node);
        return 0;
    }

    if (q->csize == 0) {
        node->next = node;
    } else {
        node->next = q->ctail->next;
        q->ctail->next = node;
    }
    q->ctail = node;
    ++q->csize;

    return 0;
}

queue_t * queue_create(void)
{
    queue_t *q;

    q = calloc(1, sizeof(*q));

    return q;
}

void queue_destroy(queue_t *q)
{
    queue_node_t *node;

    if (!q) {
        return;
    }

    while (q->size) {
        node = q->tail;
        q->tail = q->tail->next;
        free(node);
        --q->size;
    }

    while (q->csize) {
        node = q->ctail;
        q->ctail = q->ctail->next;
        free(node);
        --q->csize;
    }
    free(q);
}

int queue_push(queue_t *q, void *data)
{
    queue_node_t *node = NULL;

    if (!q) {
        return -1;
    }

    if (q->csize) {
        node = get_cache_node(q);
    } else {
        node = calloc(1, sizeof(*node));
    }
    if (!node) {
        return -1;
    }

    node->data = data;
    if (!q->size) {
        node->next = node;
    } else {
        node->next = q->tail->next;
        q->tail->next = node;
    }
    q->tail = node;
    ++q->size;

    return 0;
}

void * queue_pop(queue_t *q)
{
    void *data;
    queue_node_t *node;

    if (!q || !q->size) {
        return NULL;
    }

    node = q->tail->next;
    data = node->data;
    if (q->size == 1) {
        q->tail = NULL;
    } else {
        q->tail->next = node->next;
    }
    --q->size;
    save_cache_node(q, node);

    return data;
}

void * queue_peek(queue_t *q)
{
    if (!q || !q->size) {
        return NULL;
    }
    return q->tail->next->data;
}

int queue_size(queue_t *q)
{
    return q ? q->size : 0;
}

