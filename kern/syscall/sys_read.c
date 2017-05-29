#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <kern/unistd.h>

int sys_read(int fd, void* buf, size_t buflen, int* retval){
	if(fd!=STDIN_FILENO){
		kprintf("Only stdio supported\n");
		return -1;
	}
	kgets((char*) buf, buflen);
	*retval=strlen(buf);
	return 0;
}
