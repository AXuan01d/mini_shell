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

#define MAX_COMMAND_LEN 256
const char* prompt = "mshell>";

void parse_cmd(Job *job, char* buffer){
	char **args = (char**)malloc(100 * sizeof(char*) );  //初始化为100个字符串的字符串数组
	assert (args != NULL );
	char *str = strtok(buffer," ");       //空格分割
	args[0] = (char*)malloc(sizeof(char) * strlen(str));
//	printf("%s\n",str);               //第一个参数 (命令)
	strcpy(args[0], str);
	int i =1;
	char *tmp;
	while( (tmp = strtok(NULL," ")) != NULL ){
//		printf("%s\n",tmp);              
		args[i] = (char*)malloc(sizeof(char) * strlen(tmp));
		strcpy(args[i], tmp);
		++i;
	}
    args[i] = NULL;
	job->progs_num = 0;
	Program *prog = create_program(args);
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

void excute_cmd(Job *job){
	int i, j, find;
	for( i = 0; i < job->progs_num; ++i){        //该任务可能有多个参数
		find = 0;
		for( j = 0; j < MAX_NUM; ++j)
			if( !strcmp(job->progs[i].args[0], cmdName[j]) ){
				func[j]( &job->progs[i] );
				find = 1;
				break;       //匹配命令 退出该组参数
			}
		if(find)
			continue;
		pid_t pid = fork();
		if(pid < 0)
			perror("fork error");
		else if(pid == 0){   //子进程
			int k = 0;
			while(job->progs[i].args[k]!= NULL)
			printf("%s\n",job->progs[i].args[k++]);
			if( execvp(job->progs[i].args[0], job->progs[i].args ) < 0){   //新进程切换到指定命令
				perror("execvp error");
				exit(0);
			}
		}
		else {    //父进程等待
			waitpid(pid, NULL, WUNTRACED);
		}
		
	}
}

int main(){
	char buffer[MAX_COMMAND_LEN];
	ssize_t size = strlen(prompt);
	while(1){
		memset(buffer, 0 ,sizeof(buffer));
		write(STDOUT_FILENO, prompt, size);      //输出mshell提示前缀到屏幕
		int len = read(STDIN_FILENO, buffer, MAX_COMMAND_LEN);   //获取标准输入到buffer
		buffer[len-1] = '\0';
		if(strlen(buffer) > 0){
			Job *job = create_job(buffer);
			parse_cmd(job, buffer);       //将字符串解析为 字符串数组
			excute_cmd(job);
			destroy_job(job);
		}
	}
	return 0;
}
