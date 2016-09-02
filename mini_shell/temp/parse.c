#include "parse.h"
#include "def.h"
#include "init.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char cmdLine[MAXLEN+1];
char tempLine[MAXLEN+1];
CMD cmd;

void shell_loop(){
	while(1){
		printf("[minishell]$");
		init();
		if(read_cmd() == -1)
			break;
		parse();
		execute();		
	}
	printf("\nminishell exited\n");
}

int read_cmd(){
	if(fgets(cmdLine, MAXLEN, stdin) == NULL){  //CTRL+D
		return -1;
	}
	return 0;
}

int parse(){                             //输入行 分词  存储在CMD的数组中 
	char *t = cmdLine, *p = tempLine;
	char *st;
	int num = 0;
	while(t != NULL){
		st = p;
		while(*t != ' ' && *t != '\t' && *t != '\n' && *t != '\0')
			*(p++) = *(t++);
		*(p++) = '\0';
	//	printf(" %s \n",st);
		cmd.args[num++] = st;
		while(*t == ' ' || *t == '\t')
			++t;
		if(*t =='\n' || *t == '\0')
			break;
	}
	return 0;
}

int execute(){
	pid_t pid;
	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid == 0){                     //创建子进程去执行cmd命令
		if(execvp(cmd.args[0], cmd.args) == -1)
			perror("execvp error");
	}
	else {
		wait(0);
	}
	
	return 0;
}
