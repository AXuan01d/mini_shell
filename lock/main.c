#include "lock_head.h"

int main(int argc, char* argv[]){
	
	ssize_t size = strlen(argv[1]);
	int fd =open(argv[2], O_WRONLY|O_CREAT);

	sleep(5);
	if( !strcmp("lock", argv[3])){
		WRITE_LOCKW(fd, 0, SEEK_SET, 0);
	printf("success1\n");
	printf("lock pid: %d\n", getpid());
	}
	char*p =argv[1];
	int i;
	for( i=0; i<size; i++){
		if(write(fd, (p+i), 1)==1)
			printf("%d success write one char\n",getpid());
		sleep(1);
	}

	if( !strcmp("unlock", argv[3])){
		UNLOCK(fd, 0, SEEK_SET, 0);
	printf("unlock sucess\n");
	printf("unlock pid %d\n",getpid());
	}
	

	return 0;
}
