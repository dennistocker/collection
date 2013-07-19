#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct queue_t_ queue_t;

typedef struct queue_node_t_ queue_node_t;


queue_t * queue_create(void);

void queue_destroy(queue_t *q);

int queue_push(queue_t *q, void *data);

void * queue_pop(queue_t *q);

void * queue_peek(queue_t *q);

int queue_size(queue_t *q);

#endif
