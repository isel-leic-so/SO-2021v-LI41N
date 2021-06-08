#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MEMCH_MAX_NAME_LEN 128

typedef struct memch {
	size_t elem_size; // size of each element
	size_t capacity;  // number of elements
	
	size_t total_size;
	char   name[MEMCH_MAX_NAME_LEN];

	pthread_mutex_t lock;  // sincroniza��o de dados
	sem_t  has_space;      // sincroniza��o de controlo (espa�o livre)
	sem_t  has_items;      // sincroniza��o de controlo (objectos)

	size_t iput;
	size_t iget;

	// type_with_elem_size items[capacity];
	uint8_t items[1]; // must be the last field
} memch_t;

memch_t * mc_create(size_t elem_size, size_t capacity, const char * name);

memch_t * mc_open(const char * name);

void mc_put(memch_t * mc, void * item);  // copy from item

void mc_get(memch_t * mc, void * item);  // copy to item

void mc_close(memch_t * mc);

void mc_destroy(memch_t * mc);
