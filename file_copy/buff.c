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
int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "usage: %s asdasdasd \n",argv[0]);
		exit(1);
	}
	int fdin, fdout;
	fdin = open(argv[1], O_RDONLY);
	printf("file length = %ld\n", lseek(fdin, 20, SEEK_END));
	printf("file length = %ld\n", lseek(fdin, 0, SEEK_CUR));
	if(fdin<0){
		fprintf(stderr, "open error: %s\n",strerror(errno));
		exit(1);
	}
	printf("open file: %d\n", fdin);
	fdout = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,0777);
	if(fdin<0){
		fprintf(stderr, "open error: %s\n",strerror(errno));
		exit(1);
	}
	printf("open file: %d\n", fdout);
	copy(fdin, fdout);
	close(fdin);
	close(fdout);

	return 0;
}
	
