#pragma once

#include <stdlib.h>
#include <pthread.h>
#include "list.h"

typedef struct queue {
	pthread_mutex_t lock;   // mutex: sincronização de dados
	pthread_cond_t waiters; // condition variable: sincronização de controlo 
	list_entry_t head;
	size_t size;
} queue_t;

void queue_init(queue_t * queue);
void queue_cleanup(queue_t * queue);

void   queue_put(queue_t * queue, void * item);
void * queue_get(queue_t * queue);

INLINE
size_t queue_size(queue_t * queue) {
	size_t size;
	pthread_mutex_lock(&queue->lock);
	{
		size = queue->size;
	}
	pthread_mutex_unlock(&queue->lock);
	return size;
}
