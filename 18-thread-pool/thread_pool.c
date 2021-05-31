#include "thread_pool.h"

typedef struct workitem {
	thread_pool_action_t action;
	void * arg;
} workitem_t;

static void * thread_pool_worker(void * arg) {
	thread_pool_t * tp = (thread_pool_t *)arg;
	for (;;) {
		workitem_t * item = (workitem_t *)queue_get(&tp->work_queue);
		
		thread_pool_action_t action = item->action;
		void * arg = item->arg;
		
		free(item);
		
		action(arg);
	}
	return NULL;
}

void thread_pool_init(thread_pool_t * tp, size_t nthreads) {
	queue_init(&tp->work_queue);
	tp->nthreads = nthreads;
	tp->threads = (pthread_t *)malloc(nthreads * sizeof (pthread_t));
	for (size_t i = 0; i < nthreads; ++i) {
		pthread_create(&tp->threads[i], NULL, thread_pool_worker, tp);
	}
}

void thread_pool_cleanup(thread_pool_t * tp) {
	// TO DO ...
	
	for (size_t i = 0; i < tp->nthreads; ++i) {
		pthread_join(tp->threads[i], NULL);
	}
	free(tp->threads);
	queue_cleanup(&tp->work_queue);
}

void thread_pool_submit(thread_pool_t * tp, thread_pool_action_t action, void * arg) {
	workitem_t * work_item = (workitem_t *)malloc(sizeof (workitem_t));
	work_item->action = action;
	work_item->arg = arg;
	queue_put(&tp->work_queue, work_item);
}

