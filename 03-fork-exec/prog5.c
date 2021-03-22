#include <stdio.h>
#include <unistd.h>

int main() {
	puts("prog5 running");
	
	printf("PARENT: pid=%d\n", getpid());
	puts("PARENT: FORKING");
	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD : pid=%d (WITH PARENT: %d)\n", getpid(), getppid());
		puts("CHILD: EXEC");
		int res = execlp("./prog2", "prog2", NULL);
		puts("SHOULD NEVER RUN");
	} else {
		printf("PARENT: pid=%d (WITH CHILD : %d)\n", getpid(), pid);
		// should call waitpid
	}
	puts("SOME MESSAGE");
	
	return 0;
}
