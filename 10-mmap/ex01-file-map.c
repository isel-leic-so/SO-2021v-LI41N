#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	int fd = open(argv[1], O_RDWR);
	
	void * ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	printf("> File mapped at 0x%p\n\n", ptr);
	
	close(fd);
	
	puts(ptr);
	
	if (argc >= 3) {  // Adicionado após a aula: se passarem mais uma string como argumento,
		memcpy(ptr, argv[2], strlen(argv[2]));    // será escrita sobre o conteúdo original.
	}
	
	munmap(ptr, 4096);
	
	return 0;
}
