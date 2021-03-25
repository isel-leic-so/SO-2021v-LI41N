#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	puts("prog5 running");
	
	printf("PARENT: pid=%d\n", getpid());
	puts("PARENT: FORKING");
	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD : pid=%d (WITH PARENT: %d)\n", getpid(), getppid());
	
		sleep(15);

		puts("CHILD: EXEC");
		int res = execlp("./prog2", "prog2", NULL);
		puts("SHOULD NEVER RUN");
	} else {
		printf("PARENT: pid=%d (WITH CHILD : %d)\n", getpid(), pid);
		
		// sleep(60);
		exit(0);

		printf("PARENT: waiting for child\n");
		int res;
		waitpid(pid, &res, 0);
		printf("PARENT: child ended with value %d\n", res);

		if (WIFEXITED(res)) {
			printf("PARENT: child exited with value %d\n", WEXITSTATUS(res));
		} else {
			printf("PARENT: child terminated abnormally\n");
		}
	}
	
	return 0;
}
