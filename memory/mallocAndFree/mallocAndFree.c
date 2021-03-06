#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

#define BUFFER_SIZE 1000
#define ALLOC_SIZE (100*1024*1024) // 100MB
#define INTERVAL 1 // 1 sec

static char command[BUFFER_SIZE];

int getMemory();

int main() {
	pid_t pid;
	pid = getpid();

	for(;;) {
		getMemory(pid);
		sleep(INTERVAL);
	}
}

int getMemory(pid_t pid) {
	void *new_memory;
	char *c_new_memory;
	int i; 

	snprintf(command, BUFFER_SIZE, "cat /proc/%d/status | grep -e 'VmSize' -e 'VmRSS'", pid);

	// allocated by malloc()
	new_memory = malloc(ALLOC_SIZE);
	if(new_memory == NULL) {
		err(EXIT_FAILURE, "malloc() failed");
	}

	c_new_memory = (char *)new_memory;

	for(i = 0; i < ALLOC_SIZE; i++) {
		*(c_new_memory + i) = 0;
	}

	printf("malloc() is suucess. %d MB is allocated.\n", ALLOC_SIZE/(1024*1024));
	system(command);printf("\n");

	// released by free()
	free(new_memory);
	printf("free() is suucess. %d MB is allocated.\n", ALLOC_SIZE/(1024*1024));
	system(command);printf("\n");
	
	fflush(stdout);
}
