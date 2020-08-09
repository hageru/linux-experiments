#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
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

	new_memory = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if(new_memory == (void *) -1) {
		err(EXIT_FAILURE, "mmap() failed");
	}

	printf("mmap() is suucess. %d MB is allocated.\n", ALLOC_SIZE/(1024*1024));
	printf("access to the memory area that is out of allocated area by mmap()\n");
	fflush(stdout);

	*(c_new_memory + ALLOC_SIZE + i) = 0;
}
