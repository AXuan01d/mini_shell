#include "execute.h"
#include "def.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int lastpid;

int forkexec(CMD* tcmd){
	pid_t pid;
	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid == 0){                     //创建子进程去执行第i个命令
		
		if( tcmd -> fdin != 0){           //输入重定向
			close(0);
			dup2(tcmd ->fdin, 0);      
		}
		if(tcmd -> fdout != 1){            //输出重定向
			close(1);
			dup2(tcmd -> fdout, 1);
		}
		execvp(tcmd->args[0], tcmd->args);
		exit(0);	
	}
	else {
		lastpid = pid;
	}
	
	return 0;
}

int execute(int cmd_num){
	lastpid = -1;
	int i;
	int fds[2];
	for(i = 0; i < cmd_num; ++i){                  
		if(i < cmd_num -1){
			pipe(fds);                            // 创建管道让num个命令进行依次向后通信
			cmd[i].fdout = fds[1];
			cmd[i + 1].fdin = fds[0];
			printf("%d %d\n", fds[0], fds[1]);
		}
	}
	forkexec(&cmd[i]);
	
	while(wait(0) != lastpid); 
	return 0;
}


