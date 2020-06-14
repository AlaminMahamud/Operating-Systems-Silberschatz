#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


#define SIZE_IN_BYTES_OF_SHARED_MEM_OBJ 4096
#define SHARED_MEM_OBJ_NAME "OS"


void create_the_shared_memory_object(int * fd, char * name) {
	*fd = shm_open(name, O_CREAT | O_RDWR, 0666);
}


void configure_size_of_shared_mem_obj(int * fd, int * size) {
	ftruncate(*fd, *size);
}


void * memory_map_shared_mem_obj(int * fd, int * size) {
	return mmap(0, *size, PROT_WRITE, MAP_SHARED, *fd, 0);
}


void write_to_shared_mem_obj(void * ptr) {
	const char * message_0 = "HELLO";
	const char * message_1 = "WORLD";
	sprintf(ptr, "%s", message_0);
	ptr += strlen(message_0);
	sprintf(ptr, "%s", message_1);
	ptr += strlen(message_1);
}


int main() {
	const size_t size = SIZE_IN_BYTES_OF_SHARED_MEM_OBJ;
	const char * name = SHARED_MEM_OBJ_NAME;
	int shared_mem_file_descriptor;
	void * pointer_to_shared_mem_obj;
	
	create_the_shared_memory_object(&shared_mem_file_descriptor, name);
	configure_size_of_shared_mem_obj(&shared_mem_file_descriptor, &size);
	pointer_to_shared_mem_obj = memory_map_shared_mem_obj(&shared_mem_file_descriptor, &size);
	write_to_shared_mem_obj(pointer_to_shared_mem_obj);
	return 0;
}
