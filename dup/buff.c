#include "buff_head.h"
#define BUFFER_LEN 1024

void copy(int fd1, int fd2){
	char buffer[BUFFER_LEN];
	ssize_t nreads;
	while( ( nreads = read(fd1, buffer, BUFFER_LEN))!=0){
		if(nreads < 0){
			fprintf(stderr, "read error: %s\n", strerror(errno));
			exit(1);
		}
		else if( write(fd2, buffer, nreads) != nreads){
			fprintf(stderr, "read error:%s\n", strerror(errno));
			exit(1);
		}
	}
}
