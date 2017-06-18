#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <kern/fcntl.h>
#include <file_manager.h>

int sys_remove(char* pathname){
	
	/* To be implemented*/
	(void) pathname;
	
	return 0;
}
