#ifndef LOCKHEAD
#define LOCKHEAD

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

extern int lock_reg(int fd, int cmd, short type, off_t offset,
		short whence, off_t length);

#define READ_LOCKW(fd, offset, whence, length) \
	 lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, length)
#define READ_LOCK(fd, offset, whence, length) \
	 lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, length)

#define WRITE_LOCKW(fd, offset, whence, length) \
	 lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, length)
#define WRITE_LOCK(fd, offset, whence, length) \
	 lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, length)

#define UNLOCK(fd, offset, whence, length) \
	 lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, length)

#endif






