#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1


int create_a_pipe(int fd[]) {
	if(pipe(fd) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	
	return 0;
}


pid_t fork_a_child_process(void) {
	return fork();
}


void fork_error_handling(void) {
	printf(stderr, "Fork Failed");
}


void parent_process(pid_t pid, int fd[]) {
	close(fd[READ_END]);
	char write_msg[BUFFER_SIZE] = "Greetings";	
	write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
	close(fd[WRITE_END]);
}


void child_process(pid_t pid, int fd[]) {
	close(fd[WRITE_END]);
	char read_msg[BUFFER_SIZE];
	read(fd[READ_END], read_msg, BUFFER_SIZE);
	printf("Read -> %s\n", read_msg);	
	close(fd[READ_END]);
}


int main(void) {
	int fd[2];
	pid_t pid;

	if(create_a_pipe(fd)) return 1;
	pid = fork_a_child_process();
    	
	if(pid < 0) {
		fork_error_handling();
		return 1;
	} else if(pid == 0) {
		child_process(pid, fd);
	} else {
		parent_process(pid, fd);
	}
    	
	return 0;
}
