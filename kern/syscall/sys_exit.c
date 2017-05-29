#include <types.h>
#include <thread.h>
#include <proc.h>
#include <syscall.h>
#include <current.h>

int sys_exit(int err_code){
	struct proc *proc = curproc;
	curthread->err_code=err_code;
	proc_remthread(curthread);
	proc_destroy(proc);
	thread_exit();
	return 0;
}
