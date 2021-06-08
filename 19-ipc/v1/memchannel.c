#include <string.h>

#include "memchannel.h"
#include "shmem.h"

#define SEM_SHARED 1

memch_t * mc_create(size_t elem_size, size_t capacity, const char * name) {
	size_t items_total_size = elem_size * capacity;
	size_t mc_size = sizeof (memch_t) + items_total_size;  // offsetof(items, memch_t) + items_total_size;

	memch_t * mc = (memch_t *)shmem_create(name, mc_size);
	if (!mc) {
		return NULL;
	}
	
	mc->elem_size = elem_size;
	mc->capacity = capacity;
	strncpy(mc->name, name, MEMCH_MAX_NAME_LEN);
	mc->name[MEMCH_MAX_NAME_LEN - 1] = 0;

	sem_init(&(mc->has_items), SEM_SHARED, 0);
	sem_init(&(mc->has_space), SEM_SHARED, capacity);

	mc->iget = mc->iput = 0;

	return mc;
}

memch_t * mc_open(const char * name) {
	memch_t * mc = (memch_t *)shmem_open(name);
	return mc;
}

void mc_close(memch_t * mc) {
	size_t items_total_size = mc->elem_size * mc->capacity;
	size_t mc_size = sizeof (memch_t) + items_total_size;
	shmem_close(mc, mc_size);
}

void mc_destroy(memch_t * mc) {
	char name[MEMCH_MAX_NAME_LEN];
	strcpy(name, mc->name);
	sem_destroy(&(mc->has_items));
	sem_destroy(&(mc->has_space));
	size_t items_total_size = mc->elem_size * mc->capacity;
	size_t mc_size = sizeof (memch_t) + items_total_size;
	shmem_destroy(name, mc, mc_size);
}

void mc_put(memch_t * mc, void * item) {
	sem_wait(&(mc->has_space));
	long iput = atomic_fetch_add(&(mc->iput), 1) % mc->capacity;
	memcpy(mc->items + iput * mc->elem_size, item, mc->elem_size);
	sem_post(&(mc->has_items));
}

void mc_get(memch_t * mc, void * item) {
	sem_wait(&(mc->has_items));
	long iget = atomic_fetch_add(&(mc->iget), 1) % mc->capacity;
	memcpy(item, mc->items + iget * mc->elem_size, mc->elem_size);
	sem_post(&(mc->has_space));
}
