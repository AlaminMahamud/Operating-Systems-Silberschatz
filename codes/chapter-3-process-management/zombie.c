#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t child_pid;
	child_pid = fork();
	if(child_pid < 0) {
		printf("Fork Error!\n");
	} else if (child_pid == 0) {
		exit(0);
	} else {
		wait();
		printf("Zombie\n");
		sleep(100);
		exit(0);
	}
}
