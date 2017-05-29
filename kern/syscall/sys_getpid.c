#include <types.h>
#include <syscall.h>
#include <current.h>
#include <proc.h>

pid_t sys_getpid(void){
	return curproc->pid;
}
