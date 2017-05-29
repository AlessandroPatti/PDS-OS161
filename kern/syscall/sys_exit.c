#include <types.h>
#include <thread.h>
#include <proc.h>
#include <syscall.h>
#include <current.h>

int sys_exit(int err_code){
	struct proc *proc = curproc;
	curthread->err_code=err_code;
	proc->err_code=err_code;
	proc_remthread(curthread);
	if(proc->wait_on==0)
		proc_destroy(proc);
	else{   
		lock_acquire(proc->wait_lock);
		cv_broadcast(proc->wait_cv, proc->wait_lock);
		lock_release(proc->wait_lock);
	}
	thread_exit();
	return 0;
}
