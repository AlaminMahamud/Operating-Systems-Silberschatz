/*

Purpose: A Simple Shell
----------------------------------
takes input and echo them after splitting them into multiple tokens

Original Author - @dalmia
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1;
#define false 0;


# define ASH_READ_LINE_BUFFERSIZE 1024;
# define ASH_TOKEN_BUFFERSIZE 1024;
# define ASH_TOKEN_SEPARATOR " \t\r\n\a";


bool parent_and_child_process_not_concurrent = false;


int ash_cd(char **args);
int ash_help(char **args);
int ash_exit(char **args);


char *builtin_cmd[] = {
    "cd", "help", "exit"
};


size_t ash_number_of_builtin_cmd() {
    return sizeof(builtin_cmd) / sizeof(char *);
}


int (*builtin_func[]) (char **) = {
    ash_cd,
    ash_help,
    ash_exit
};


int ash_cd(char ** args) {
    if (args[1] == NULL)
        fprintf(stderr, "ash: I need the folder name to change directory\n");
    else 
        if(chdir(args[1]) != 0)
            perror("ash");

    return 1;
}


int ash_help(char **args) {
    printf("--> ASH Help:\n");
    printf("Type program names and arguments, and press enter.\n");
    printf("Append \"&\" after the arguments for concurrency between parent-child process.\n");
    printf("Copied from - @dalmia\n\n");
    printf("The following are built in:\n");
    
    int i;
    for(i = 0; i < ash_number_of_builtin_cmd(); i++){
        printf(" %s\n", builtin_cmd[i]);
    }

    return 1;
}


int ash_exit(char **args) {
    return 0;
}


void common_exit_strategy(void) {
    fprintf(stderr, "ash: allocation error\n");
    exit(EXIT_FAILURE);
}


void if_buffer_allocation_error_then_exit(char * buffer){ 
    if (!buffer)
        common_exit_strategy();
}


void if_token_buffer_allocation_error_than_exit(char ** buffer) {
    if(!buffer)
        common_exit_strategy();
}


char * allocate_buffer(int current_buffersize) {
    char * buffer = malloc(sizeof(char) * current_buffersize);
    if_buffer_allocation_error_then_exit(buffer);
    return buffer;
}


char ** allocate_buffer_for_tokens(int current_buffersize) {
    char ** tokens = malloc(sizeof(char *) * current_buffersize);
    if_token_buffer_allocation_error_than_exit(tokens);
    return tokens;
}


char * reallocate_buffer(char * buffer, int * current_buffersize) {
    *current_buffersize += ASH_READ_LINE_BUFFERSIZE;
    buffer = realloc(buffer, *current_buffersize);
    if_buffer_allocation_error_then_exit(buffer);
    return buffer;
}


char ** reallocate_buffer_for_tokens(char ** buffer, int * current_buffersize) {
    *current_buffersize += ASH_TOKEN_BUFFERSIZE;
    buffer = realloc(buffer, *current_buffersize);
    if_token_buffer_allocation_error_than_exit(buffer);
    return buffer;
}


void read_character(int * c, char * buffer, int * cursor_position, int * flag){
    *c = getchar();
    if (*c == EOF || *c == '\n') {
        buffer[*cursor_position] = '\0';
        *flag = 0;
        return;
    } else {
        buffer[*cursor_position] = *c;
    }
    (*cursor_position)++;
}


char * ash_read_line(void) {
    printf("$ ");
    int current_buffersize = ASH_READ_LINE_BUFFERSIZE;
    int cursor_position = 0;
    char * buffer = allocate_buffer(current_buffersize);

    int c;
    int flag = 1;
    while(flag) {
        read_character(&c, buffer, &cursor_position, &flag);
        if (cursor_position > current_buffersize) {
            buffer = reallocate_buffer(buffer, &current_buffersize);
        }
    }

    return buffer;
}

void walk_through_the_line_and_find_possible_token(char * line, char ** tokens, int * current_buffersize) {
    int position = 0;
    const char * delim = ASH_TOKEN_SEPARATOR;
    char * token = strtok(line, delim);
    while (token != NULL) {
        tokens[position++] = token;
        if (position > *current_buffersize)
            reallocate_buffer_for_tokens(tokens, current_buffersize);
        token = strtok(NULL, delim);
    }
    
    if(position > 0 && strcmp(tokens[position - 1], "&") == 0) {
        parent_and_child_process_not_concurrent = true;
        tokens[position - 1] = NULL;
    } else tokens[position] = NULL;
}


char ** tokenize_the_line(char * line) {
    int current_buffersize = ASH_TOKEN_BUFFERSIZE;
    char ** tokens = allocate_buffer_for_tokens(current_buffersize);
    walk_through_the_line_and_find_possible_token(line, tokens, &current_buffersize);
    return tokens;
}


void exec_child_process(char ** args) {
    if (execvp(args[0], args) == -1) perror("ash");
    exit(EXIT_FAILURE);
}


void exec_parent_process(char ** args, int * status, pid_t * pid, pid_t * wpid) {
    if(!parent_and_child_process_not_concurrent){
        do{
            *wpid =  waitpid(*pid, status, WUNTRACED);
        }while(!WIFEXITED(*status) && !WIFSIGNALED(*status));
    }
}

int ash_launch(char ** args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0) exec_child_process(args);
    else if(pid > 0) exec_parent_process(args, &status, &pid, &wpid);
    else perror("ash");

    parent_and_child_process_not_concurrent = false;
    return 1;
}


int ash_execute(char * line) {
    char ** tokens = tokenize_the_line(line);
    
    if(tokens[0] == NULL)
        return 1;

    int i;
    for (i = 0; i < ash_number_of_builtin_cmd(); i++) {
        if(strcmp(tokens[0], builtin_cmd[i]) == 0)
            return (*builtin_func[i])(tokens);
    }

    return ash_launch(tokens);
}


void ash_loop(void) {
    char *line;
    int status;

    do {
        line = ash_read_line();
        status = ash_execute(line);
        free(line);
    } while(status);
}


int main() {
    ash_loop();
    return 0;
}