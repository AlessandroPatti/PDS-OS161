#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <file_manager.h>
#include <uio.h>
#include <proc.h>
#include <current.h>

int sys_write(int fd, const void* buf, size_t buflen, int* retval){
	struct iovec iov;
	struct uio u;
	int result; 
	/* STDIO */
	unsigned int i;
	if(fd==STDOUT_FILENO || fd==STDERR_FILENO){
		for(i=0; i<buflen; i++)
		kprintf("%c", *((char*)buf+i));
		*retval=buflen;
		return 0;
	}
	if(fd==STDIN_FILENO){		
		kprintf("Can't write to stdin");
		return -1;
	}
	/*
	kprintf("Only stdio supported\n");
	return -1;
	*/

	/* FILE */
	if(fd<3||fd>=MAX_FD){
		*retval=-1;
		return EBADF;
	}
	if(file_index==NULL){
		*retval=-1;
		return EBADF;
	}
	if(file_index[fd]==NULL){
		*retval=-1;
		return EBADF;
	}
	
	iov.iov_ubase = (userptr_t)buf;
	iov.iov_len = buflen;		 // length of the memory space
	u.uio_iov = &iov;
	u.uio_iovcnt = 1;
	u.uio_resid = buflen;          // amount to read from the file
	u.uio_offset = 0;
	u.uio_segflg = UIO_USERSPACE;
	u.uio_rw = UIO_WRITE;
	u.uio_space = curproc->p_addrspace;

	result = VOP_WRITE(file_index[fd], &u);
	
	if(result)
		return -1;
	*retval = buflen-u.uio_resid;
	return 0;
	
}
	
