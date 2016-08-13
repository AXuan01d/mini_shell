#include "job.h"
#include "func.h"
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define  FOREGROUD  0  //前台进程
#define  BACKGROUD  1  //后台进程
#define MAX_COMMAND_LEN 256    
const char* prompt = "mshell>";

void parse_cmd(Job *job, char* buffer, int* bg){
	char **args = (char**)calloc(100 , sizeof(char*) );  //初始化为100个字符串的字符串数组
	assert (args != NULL );
	char *str = strtok(buffer," ");       //空格分割
	args[0] = (char*)calloc(sizeof(char)+1, strlen(str));
//	printf("%s\n",str);               //第一个参数 (命令)
	strcpy(args[0], str);
	int i = 1;
	
	Redirection *rs[5];         //默认不超过5个重定向
	int redirect_num = 0;

	char *tmp,*file;

	*bg = FOREGROUD;
	while( (tmp = strtok(NULL," ")) != NULL ){        //解析命令后的所有字符串
//		printf("%s\n",tmp);              
		if(!strcmp(tmp, "&") ) {       //后台进程标志
			*bg = BACKGROUD;
			continue;
		}

		if(!strcmp(tmp, "<") ){     //输入重定向
			file = strtok(NULL, " ");
			if(file == NULL)
				continue;
			int fd = open(file, O_RDONLY);
			rs[redirect_num++] = create_redirect(fd, RdRead);
			continue;
		}
		if(!strcmp(tmp, ">") ){    //输出重定向
			file = strtok(NULL, " ");
			if(file == NULL)
				continue;
			int fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);
			rs[redirect_num++] = create_redirect(fd, RdWrite);
			continue;

		}
		if(!strcmp(tmp, ">>") ){     //附加重定向
			file = strtok(NULL, " ");
			if(file == NULL)
				continue;
			int fd = open(file, O_WRONLY|O_CREAT|O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO);
			rs[redirect_num++] = create_redirect(fd, RdAppend);
			continue;
		}

		args[i] = (char*)calloc(strlen(tmp)+1, sizeof(char) );
		strcpy(args[i], tmp);
		++i;
	}
	job->progs_num = 0;
	Program *prog = create_program(args);

	
	for(i = 0; i< redirect_num;i++){
		add_redirection(prog, rs[i]);
		destroy_redirect(rs[i]);
	}

	add_program(job, prog);
	int j;
	for (j = 0; j < i; ++j)
		free(args[j]);
	free(args);
	return;
}

char *cmdName[] = {"cd", "pwd", "exit", "env", "export", "echo"};                    //命令名
void (*func[])(Program* ) =  {func_cd, func_pwd, func_exit, func_env, func_export, func_echo};    //命令函数数组
const int MAX_NUM = 6;

void excute_cmd(Job *job, int bg){
	int i, j, find;
	for( i = 0; i < job->progs_num; ++i){        //该程序可能有多个进程
		find = 0;
		for( j = 0; j < MAX_NUM; ++j)
			if( !strcmp(job->progs[i].args[0], cmdName[j]) ){
				func[j]( &job->progs[i] );
				find = 1;
				break;       //匹配命令 退出该组参数
			}
		if(find)
			continue;
		pid_t pid = fork();                 //创建新进程完成其他指令
		if(pid < 0)
			perror("fork error");
		else if(pid == 0){                  //子进程
			if(i == 0){                                //一号进程设为进程组
				if(setpgid(getpid(), getpid())<0)
					perror("setpgid error");
				job->pgid = getpgid( getpid() );
			}
			else {                                   //进程组和一号进程一致
				if(setpgid(getpid(), job->pgid) < 0)
					perror("setpgid error2");
			}
			if( bg == FOREGROUD)
				tcsetpgrp(0, job->pgid);     // 前台进程组设为1号进程的进程组
	

			job->progs[i].pid = getpid();      
			
			int k, len = job->progs[i].redirect_num;
			for(k = 0; k < len; ++k){
			    if(job->progs[i].redirects[k].redirect == RdRead){
					if(dup2(job->progs[i].redirects[k].fd, STDIN_FILENO) != STDIN_FILENO)              //输入重定向到文件
						perror("dup2 error");
				}
				else{                                   //输出重定向到文件
					if(dup2(job->progs[i].redirects[k].fd, STDOUT_FILENO) != STDOUT_FILENO)          
						perror("dup2 error");
				}
			}	
					
			if( execvp(job->progs[i].args[0], job->progs[i].args ) < 0){   //新进程切换到指定命令
				perror("execvp error");
				exit(0);
			}
		}
		else {    
			/*
			父进程再来进程组一次
			 */
			if(bg == FOREGROUD)
				waitpid(-job->pgid, NULL, WUNTRACED);  //前台进程回收进程组所有子进程
			else 
				waitpid(-job->pgid, NULL, WNOHANG);  //后台运行

			//		waitpid(pid, NULL, WUNTRACED);
		}
		
	}
}

int main(){
	char buffer[MAX_COMMAND_LEN];
	ssize_t size = strlen(prompt);
	int bg;       //前台后台进程组标志
	while(1){
		memset(buffer, 0 ,sizeof(buffer));
		write(STDOUT_FILENO, prompt, size);      //输出mshell提示前缀到屏幕
		int len = read(STDIN_FILENO, buffer, MAX_COMMAND_LEN);   //获取标准输入到buffer
		buffer[len-1] = '\0';
		if(strlen(buffer) > 0){
			Job *job = create_job(buffer);
			parse_cmd(job, buffer, &bg);       //将字符串解析为 字符串数组
			excute_cmd(job, bg);
			destroy_job(job);
		}
	}
	return 0;
}
