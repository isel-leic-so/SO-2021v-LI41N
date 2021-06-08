#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <semaphore.h>

#define MEMCH_MAX_NAME_LEN 128

// NOTA: suporta 1 consumidor e 1 produtor em simultâneo
//       não suporta múltiplos consumidores e/ou produtores simultâneos
//
typedef struct memch {
	size_t elem_size; // size of each element
	size_t capacity;  // number of elements
	char name[MEMCH_MAX_NAME_LEN];

	sem_t has_space;
	sem_t has_items;

	atomic_long iput;
	atomic_long iget;

    // type_with_elem_size items[capacity];
	uint8_t items[1];
} memch_t;

memch_t * mc_create(size_t elem_size, size_t capacity, const char * name);

memch_t * mc_open(const char * name);

void mc_put(memch_t * mc, void * item);  // copy from item

void mc_get(memch_t * mc, void * item);  // copy to item

void mc_close(memch_t * mc);

void mc_destroy(memch_t * mc);
