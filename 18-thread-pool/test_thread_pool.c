#include <stdio.h>
#include "thread_pool.h"

#define NTHREADS 3

void test_task(void * arg) {
	const char * msg = (const char *)arg;
	puts(msg);
	usleep(1);
}

int main() {
	thread_pool_t tp;
	
	thread_pool_init(&tp, NTHREADS);
	
	thread_pool_submit(&tp, test_task, "msg01");
	thread_pool_submit(&tp, test_task, "msg02");
	thread_pool_submit(&tp, test_task, "msg03");
	thread_pool_submit(&tp, test_task, "msg04");
	thread_pool_submit(&tp, test_task, "msg05");
	thread_pool_submit(&tp, test_task, "msg06");
	thread_pool_submit(&tp, test_task, "msg07");
	thread_pool_submit(&tp, test_task, "msg08");

	sleep(8); // don't do this at home

	// thread_pool_cleanup(&tp);
	return 0;
}
