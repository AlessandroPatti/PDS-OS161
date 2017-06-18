#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <file_manager.h>

int sys_close(int fd){
	if(fd<3)
		return EBADF;
	if(file_index[fd]==NULL)
		return EIO;
	vfs_close(file_index[fd]);
	file_index[fd]=NULL;
	return 0;
}
