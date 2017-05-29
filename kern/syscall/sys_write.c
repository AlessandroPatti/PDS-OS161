#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <kern/unistd.h>

int sys_write(int fd, const void* buf, size_t buflen, int* retval){
	unsigned int i;
	if(fd!=STDOUT_FILENO){
		kprintf("Only stdio supported\n");
		return -1;
	}
	for(i=0; i<buflen; i++)
		kprintf("%c", *((char*)buf+i));
	*retval=buflen;
	return 0;
}
