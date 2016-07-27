#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char* argv[]){
	int fd =open( argv[2], O_WRONLY);
	if( fd<0)
		perror("open error");

	lseek(fd, 0L, SEEK_END);

	sleep(10);

	size_t size = strlen(argv[1])*sizeof(char);
	if(write(fd, argv[1], size) != size){
		perror("write error\n");
		exit(1);
	}

	return 0;
}
