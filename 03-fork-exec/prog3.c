#include <stdio.h>
#include <unistd.h>

int main() {
	puts("prog3 running");
	
	printf("PARENT: pid=%d\n", getpid());
	puts("PARENT: FORKING");
	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD : pid=%d (WITH PARENT: %d)\n", getpid(), getppid());
	} else {
		printf("PARENT: pid=%d (WITH CHILD : %d)\n", getpid(), pid);
	}
	puts("SOME MESSAGE");
	
	return 0;
}