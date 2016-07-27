#include "lock_head.h"

int lock_reg(int fd, int cmd, short type, off_t offset, 
		short whence, off_t length){
	struct flock flock = {type, offset, whence, length};
//	flock.l_type = type;
//	flock.l_start = offset;
//	flock.l_whence = whence;
//	flock.l_len = length;
	if( fcntl(fd, cmd, &flock) <0 ){
		perror("ohehehe\n");
		return 0;
	}
	return 1;
}
