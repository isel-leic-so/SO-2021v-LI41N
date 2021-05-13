#include <stdio.h>
#include <stdlib.h>

#include "uthread.h"

void f1_1() {
	puts("T1: step 2");
	ut_yield();	
}

void f1_2() {
	f1_1();
	puts("T1: step 3");
}

void f1(void * arg) {
	puts("T1: step 1");
	ut_yield();
	f1_2();
}

void f2(void * arg) {
	puts("T2: hello world");
}

void f3(void * arg) {
	char * name = (char *)arg;
	printf("%s: step 1\n", name);
	ut_yield();
	printf("%s: step 2\n", name);
	ut_yield();
	printf("%s: step 3\n", name);
}

int main() {
	
	ut_init();
	
	ut_create(f1, NULL);
	ut_create(f2, NULL);
	ut_create(f3, "T3");
	ut_create(f3, "T4");
	ut_create(f3, "T5");
	ut_create(f3, "T6");
	
	puts(":: START ::");
	ut_run();

	puts(":: END ::");
	ut_end();

	return 1;
}
