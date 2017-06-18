#include <types.h>
#include <lib.h>
#include <file_manager.h>
#include <synch.h>

struct lock* lock;
struct vnode** file_index=NULL;

void file_index_init(void){
	int i;
	file_index=kmalloc(MAX_FD*sizeof(struct vnode*));
	for(i=3; i<MAX_FD; i++){
		file_index[i]=NULL;
	}
	lock=lock_create("file_index_lock");
}

int get_fd(struct vnode* vnode){
	int i;
	if(file_index==NULL)
		file_index_init();
	lock_acquire(lock);
	for(i=3; i<MAX_FD; i++){
		if(file_index[i]==NULL)
			break;
	}
	if(i==MAX_FD){
		lock_release(lock);
		return -1;
	}

	file_index[i]=vnode;
	lock_release(lock);
	return i;
}
