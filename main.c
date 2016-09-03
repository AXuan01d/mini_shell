#include "init.h"
#include "parse.h"
#include "execute.h"
#include "def.h"
#include <stdio.h>

int backgnd;
int append;
char infile[MAXNAME+1];
char outfile[MAXNAME+1];
char cmdLine[MAXLEN+1];
char tempLine[MAXLEN+1];
CMD cmd[PIPELINE];


void shell_loop(){
	int num;
	while(1){
		printf("[minishell]$");
		init();                           //变量初始化
		if(read_cmd() == -1)              //读命令
			break;
		if(parse() == -1)                 //解析命令
			continue;
		print_after_parse();
	//	execute();		                  //执行命令
	}
	printf("\nminishell exited\n");
}

int main(void){
	setup();	                          //设置属性
	shell_loop();
	return 0;
}
