#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


#define SIZE_IN_BYTES_OF_SHARED_MEM_OBJ 4096
#define SHARED_MEM_OBJ_NAME "OS"


void open_the_shared_memory_object(int * fd, char * name) {
	*fd = shm_open(name, O_RDONLY, 0666);
}


void * memory_map_shared_mem_obj(int * fd, int * size) {
	return mmap(0, *size, PROT_READ, MAP_SHARED, *fd, 0);
}


void read_from_shared_mem_obj(void * ptr) {
	printf("%s\n", (char *)ptr);
}


void remove_shared_mem_obj(const char * name) {
	shm_unlink(name);
}


int main() {
	const size_t size = SIZE_IN_BYTES_OF_SHARED_MEM_OBJ;
	const char * name = SHARED_MEM_OBJ_NAME;
	int shared_mem_file_descriptor;
	void * pointer_to_shared_mem_obj;
	
	open_the_shared_memory_object(&shared_mem_file_descriptor, name);
	pointer_to_shared_mem_obj = memory_map_shared_mem_obj(&shared_mem_file_descriptor, &size);
	read_from_shared_mem_obj(pointer_to_shared_mem_obj);
	remove_shared_mem_obj(name);
	return 0;
}
