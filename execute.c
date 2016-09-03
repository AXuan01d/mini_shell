#include "execute.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int execute(){
	pid_t pid;
	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid == 0){                     //创建子进程去执行cmd命令
	//	if(execvp(cmd[0].args[0], cmd.args) == -1)
	//		perror("execvp error");
	}
	else {
		wait(0);
	}
	
	return 0;
}
