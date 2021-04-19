#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	
	void * ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	printf("> Memory available at 0x%p\n\n", ptr);
	
	strcpy(ptr, "ISEL - LEIC - SO");
	
	puts(ptr);
	
	munmap(ptr, 4096);
	
	return 0;
}
