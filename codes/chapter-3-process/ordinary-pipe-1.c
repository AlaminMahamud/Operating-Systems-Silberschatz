#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


typedef int bool;
#define true 1
#define false 0


#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1


#define IS_FORK_FAILED(pid) pid < 0
#define IS_CHILD_PROCESS(pid) pid == 0
#define IS_PARENT_PROCESS(pid) pid > 0


#define OS_PROCESS_STATUS_SUCCESS 0
#define OS_PROCESS_STATUS_FAILED 1


bool create_a_pipe(int fd[]) {
	if(pipe(fd) == -1) {
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
	int file_descriptor[2];
	pid_t pid;

	if(!create_a_pipe(file_descriptor)) return OS_PROCESS_STATUS_FAILED;

	pid = fork_a_child_process();
    	
	if(IS_FORK_FAILED(pid)) {
		fork_error_handling();
		return OS_PROCESS_STATUS_FAILED;
	} else if(IS_CHILD_PROCESS(pid)) {
		child_process(pid, file_descriptor);
	} else if(IS_PARENT_PROCESS(pid)) {
		parent_process(pid, file_descriptor);
	}
    	
	return OS_PROCESS_STATUS_SUCCESS;
}
