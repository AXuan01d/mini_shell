#ifndef BUFFHEAD
#define BUFFHEAD

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern void copy(int fd1, int fd2);

#endif
