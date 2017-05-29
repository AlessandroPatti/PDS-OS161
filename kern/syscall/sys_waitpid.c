#include <types.h>
#include <syscall.h>
#include <limits.h>
#include <kern/errno.h>
#include <current.h>
#include <proc.h>

pid_t sys_waitpid(pid_t pid, int* retval, int flags){
	KASSERT(pid<PID_MAX);
	KASSERT(pid>PID_MIN);

	if(proc_index[pid]==NULL){
		*retval=ECHILD;
		return -1;
	}

	/* implements here flags */
	(void) flags;

	*retval=wait_proc(proc_index[pid]);
	return 0;
}
