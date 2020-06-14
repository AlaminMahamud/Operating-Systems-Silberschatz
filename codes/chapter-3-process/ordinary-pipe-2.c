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


int fork_error_handling(pid_t pid) {
	if(pid < 0) {
		printf(stderr, "Fork Failed");
		return 1;
	}
	
	return 0;
}


void parent_process(pid_t pid, int fd[]) {
	if(pid > 0) {
		close(fd[READ_END]);
		char write_msg[BUFFER_SIZE] = "Greetings";	
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		close(fd[WRITE_END]);
	}		
}


void child_process(pid_t pid, int fd[]) {
	if(pid == 0) {
		close(fd[WRITE_END]);
		char read_msg[BUFFER_SIZE];
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("Read -> %s\n", read_msg);	
		close(fd[READ_END]);
	}
}


int main(void) {
	int file_descriptor[2];
	pid_t pid;

	if(create_a_pipe(file_descriptor)) return 1;
	
	pid = fork_a_child_process();
	fork_error_handling(pid);
	child_process(pid, file_descriptor);
	parent_process(pid, file_descriptor);
	
	return 0;
}
