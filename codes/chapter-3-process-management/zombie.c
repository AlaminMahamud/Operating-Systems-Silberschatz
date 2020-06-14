#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t child_pid;
	int status;
	child_pid = fork();

	if(child_pid < 0) {
		printf("Fork Error!\n");
	} else if (child_pid == 0) {
		exit(0);
	} else {
		printf("Zombie\n");
		sleep(10);
        child_pid = wait(&status);
        if (WIFEXITED(status))
            fprintf(stderr, "\n\t[%d]\tProcess %d exited with status %d.\n",
                (int) getpid(), child_pid, WEXITSTATUS(status));
		exit(0);
	}
}
