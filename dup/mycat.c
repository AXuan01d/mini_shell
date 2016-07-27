#include "buff_head.h"
int main(int argc, char * argv[]){
	int fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	
	int i;
	for(i = 1; i < argc; i++){
		fd_in = open(argv[i], O_RDONLY);
		if( fd_in < 0){
			perror("open error \n");
			continue;
		}
		copy(fd_in, fd_out);
		close(fd_in);
	}
	if(argc == 1)
		copy(fd_in, fd_out);
	return 0;
}
