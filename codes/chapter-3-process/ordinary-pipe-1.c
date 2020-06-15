#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


typedef int bool;
#define true 1
#define false 0

#define SUCCESS 0
#define FAILED 1

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

#define PIPE_CREATION_FAILED_STATUS -1

#define is_fork_failed(pid) pid < 0
#define is_child_process(pid) pid == 0
#define is_parent_process(pid) pid > 0


bool create_a_pipe(int fd[]) {
	if(pipe(fd) == PIPE_CREATION_FAILED_STATUS) {
		fprintf(stderr, "Pipe Failed");
		return false;
	}
	
	return true;
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
	pid_t pid;
	int file_descriptor[2];

	if(!create_a_pipe(file_descriptor)) return FAILED;

	pid = fork_a_child_process();
    	
	if(is_fork_failed(pid)) {
		fork_error_handling();
		return FAILED;
	} else if(is_child_process(pid)) {
		child_process(pid, file_descriptor);
	} else if(is_parent_process(pid)) {
		parent_process(pid, file_descriptor);
	}
    	
	return SUCCESS;
}
