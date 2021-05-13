#include "uthread.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define STACK_SIZE (8*4096)

struct uthread {
	uint64_t rsp;  // must be the first field ; used in context_switch
	void * stack;
	list_entry_t entry;
	void (*start_routine)(void *);
	void * arg;
};

typedef struct uthread_context {
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t rbx;
	uint64_t rbp;
	void (*ret_addr)();
} uthread_context_t;

void context_switch(uthread_t * currThread, uthread_t * nextThread);
void exit_switch(uthread_t * currThread, uthread_t * nextThread);

uthread_t * main_thread;
uthread_t * running_thread;
list_entry_t ready_queue;

uthread_t * extract_next_ready_thread() {
	return is_list_empty(&ready_queue) ?
		main_thread :
		container_of(remove_head_list(&ready_queue), uthread_t, entry);
}

void schedule() {
	context_switch(running_thread, extract_next_ready_thread());
}

void internal_start() {
	running_thread->start_routine(running_thread->arg);
	ut_exit();
}

void ut_exit() {
	exit_switch(running_thread, extract_next_ready_thread());
}

void ut_init() {
	init_list_head(&ready_queue);
}

void ut_end() {
	
}

void ut_run() {
	if (!is_list_empty(&ready_queue)) {
		uthread_t main_thread_obj;
		running_thread = main_thread = &main_thread_obj;
		schedule();
		//printf("exiting\n");
	}
}

uthread_t * ut_create(void (*start_routine)(void *), void * arg) {
	uthread_t * thread = (uthread_t *) malloc(sizeof (uthread_t));
	
	thread->stack = mmap(NULL, STACK_SIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	
	uthread_context_t * pctx =
		(uthread_context_t *)(
			(uint8_t *)thread->stack
			+ STACK_SIZE
			- sizeof (uthread_context_t)
		);
	pctx->rbp = 0;
	pctx->ret_addr = internal_start;
	thread->rsp = (uint64_t)pctx;
	thread->start_routine = start_routine;
	thread->arg = arg;
	
	insert_tail_list(&ready_queue, &(thread->entry));
	
	return thread;
}

void cleanup_thread(uthread_t * thread) {
	//printf("cleanup_thread\n");
	munmap(thread->stack, STACK_SIZE);
	free(thread);
}

void ut_yield() {
	if (!is_list_empty(&ready_queue)) {
		insert_tail_list(&ready_queue, &(running_thread->entry));
		schedule();
	}
}
