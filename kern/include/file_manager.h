#define MAX_FD 100
#include <vfs.h> /* maybe not necessary */
#include <vnode.h>
#include <uio.h>

extern struct vnode** file_index;
void file_index_init(void);
int get_fd(struct vnode* vnode);
