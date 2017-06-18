#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <kern/fcntl.h>
#include <file_manager.h>

int sys_open(char* pathname, int flags, int* retval){
	int i;
	int result;
	struct vnode* v;
	if(pathname==NULL){
		*retval=-1;
		return ENOENT;
	}
	
	result = vfs_open(pathname, flags, 0, &v);
	if (result) {
		*retval=-1;
		return EACCES;
	}
	/*if((flags && (O_CREAT || O_EXCL)) == (O_CREAT || O_EXCL)){
		// close file
		*retval=-1;
		return EEXIST;
	}*/
	if((i=get_fd(v))==-1){
		*retval=-1;
		return EACCES;
	}
	
	*retval=i;
	
	return 0;
}
