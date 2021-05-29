#include <unistd.h>
#include <stdio.h>

#include <pthread.h>
#include "queue.h"

#define N 100000

void * source_thread(void * arg) {
	queue_t * queue = (queue_t *)arg;
	for (int i = 0; i < N; ++i) {
		int * pi = (int *)malloc(sizeof(int));
		*pi = i;
		queue_put(queue, pi);
		usleep(1);
	}
	return NULL;
}

int main() {

	pthread_t thread1, thread2;
	
	queue_t queue;
	
	queue_init(&queue);

	puts(":: START ::");
	
	pthread_create(&thread1, NULL, source_thread, &queue);
	pthread_create(&thread2, NULL, source_thread, &queue);

	for (int i = 0; i < N*2; ) {
		int * pi = (int *)queue_get(&queue);
		if (pi) {
			// pi...
			free(pi);
			++i;
			putchar('.');
		} else {
			putchar('_');
		}
	}

	puts(":: DONE ::");

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	puts(":: END ::");

	return 0;
}
