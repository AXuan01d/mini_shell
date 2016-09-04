#include "execute.h"
#include "def.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int lastpid;
int open_max;

void forkexec(CMD* tcmd){
	pid_t pid;
	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid == 0){                     //创建子进程去执行第i个命令
		if( tcmd->fdin != 0)           //输入重定向
			dup2(tcmd->fdin, 0);      
		
		if(tcmd->fdout != 1)            //输出重定向
			dup2(tcmd->fdout, 1);
		int i;
		for(i = 3 ;i < open_max; ++i)     //关闭从父进程继承过来的多余文件描述符
			close(i);
		execvp(tcmd->args[0], tcmd->args);
		exit(EXIT_FAILURE);	            //execvp 正常执行不会返回
	}
	else                //父进程返回子进程id
		lastpid = pid;  
	
	
	return ;
}

int execute(){
	lastpid = -1;
	int i;
	int  fds[2];
/*	if(infile[0] != '\0'){                //有输入重定向的话打开输入文件
		fd = open(infile, W_RDONLY);
		dup2(fd, 0);
	} 
	if(outfile[0] != '\0'){
		if(append)
			fd = open(outfile, W_WRONLY|W_APPEND|W_CREAT|0777);	
		else 
			fd = open(outfile, W_WRONLY|W_TRUNC|W_CREAT|0777);	
		dup2(fd, 1);
	}*/
	for(i = 0; i < cmd_num; ++i){                  
		if(i < cmd_num -1){
			pipe(fds);                            // 创建管道让num个命令进行依次向后通信
			cmd[i].fdout = fds[1];
			cmd[i + 1].fdin = fds[0];
			open_max = open_max>fds[1]?open_max:fds[1];
		}
		forkexec(&cmd[i]);
		if(cmd[i].fdin != 0)
			close(cmd[i].fdin);
		if(cmd[i].fdout != 1)
			close(cmd[i].fdout);
	}
	while(wait(NULL) != lastpid); //父进程等到最后一个子进程结束为止
	return 0;
}


