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


bool check_buffer_allocation_error(char * buffer){ 
    if (!buffer) {
        return true;
    }
    return false;
}


char * allocate_buffer(int current_buffersize) {
    char * buffer = malloc(sizeof(char) * current_buffersize);
    if (check_buffer_allocation_error(buffer)) {
        exit(EXIT_FAILURE);
    }
    return buffer;
}


char * reallocate_buffer(char * buffer, int * current_buffersize) {
    *current_buffersize += ASH_READ_LINE_BUFFERSIZE;
    buffer = realloc(buffer, *current_buffersize);
    if (check_buffer_allocation_error(buffer)) {
        exit(EXIT_FAILURE);
    }
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

    printf("--> %s\n", buffer);
    return buffer;
}

void ash_loop(void) {
    char *line;
    int status;

    do {
        line = ash_read_line();
        // status = ash_execute(line);
        free(line);
    } while(status);
}

int main() {
    ash_loop();
    return 0;
}