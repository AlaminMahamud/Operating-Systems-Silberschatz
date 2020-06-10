#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int value = 5;
	
int main() {
	pid_t pid;
	if((pid = fork()) < 0 ){
		printf("Fork Error\n");
	} else if (pid == 0) {
		value += 15;
		printf("CHILD :%d\n", value);
	} else {
		wait(NULL);
		printf("PARENT: %d\n", value);
	}
	
	printf("PID: %d\n", getpid());
	printf("Value: %d\n", value);
	return 0;
}
