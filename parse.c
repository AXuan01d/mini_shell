#include "parse.h"
#include "def.h"
#include "init.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int backgnd;
int cmd_num;
char infile[MAXNAME+1];
char outfile[MAXNAME+1];
char cmdLine[MAXLEN+1];
char tempLine[MAXLEN+1];
CMD cmd[PIPELINE];

void shell_loop(){
	while(1){
		printf("[minishell]$");
		init();
		if(read_cmd() == -1)
			break;
		parse();
	//	execute();		
	}
	printf("\nminishell exited\n");
}

int read_cmd(){
	if(fgets(cmdLine, MAXLEN, stdin) == NULL){  //CTRL+D
		return -1;
	}
	return 0;
}

const char* parse_cmd(const char* t, char* p, int num){                //读取一条完整指令放在cmd[num]
	char *st;                   //一个字符串
	int cnt = 0;
	while(t != NULL){
		st = p;
		while(*t != ' ' && *t != '\t' && *t != '\n' && *t != '\0' && *t != '>' && *t != '<' && *t != '|' && *t != '&')
			*(p++) = *(t++);
		*(p++) = '\0';
		printf(" %s \n",st);
		cmd[num].args[cnt++] = st;
		while(*t == ' ' || *t == '\t')
			++t;
		if(*t =='\n' || *t == '\0' || *t == '|' || *t =='<' || *t == '>' || *t == '&')              //碰到各种符号跳出
			break;
	}
	return t;
}

int Find;
const char* check_symbol(const char *p, const char ch){   // 检查是否有符号ch
	while( *p == ' ' || *p == '\t')
		++p;	
	if(*p == ch){
		Find = 1;	
		return ++p;
	}
	return p;                                       
}

const char* getFileName(const char* s, char *t){                //保存文件名字符串
	while(*s == ' ' || *s == '\t')
		++s;
	if(*s == '|' || *s == '>' || *s == '&' || *s == '\0' || *s == '\n')
		return NULL;
	while(*s == '_' || (*s > 'a' && *s <'z') ||(*s > 'A' && *s <'Z') ||  (*s > '0' && *s <'9') )
		*t++ = *s++;
	*t = '\0';
	return s;
}


int parse(){                             //输入行 分词  存储在CMD的数组中 
	char *p = cmdLine;
	const char *t;
	char *s = tempLine;            //存储字符串常量  (args的指针没有分配内存 直接指向tempLine里的串)
	t = parse_cmd(p, s, 0);        // 解析第一个命令到cmd[0]
	Find = 0;
	t = check_symbol(t, '<');      // 检查重定向符<  
	if(Find == 1){
		if( (t = getFileName(t, infile)) == NULL)	      //重定向文件
			perror("get in file error");
	}
	
		
	Find = 0;
	t = check_symbol(t, '>');
	if(Find == 1){
		if( (t = getFileName(t, outfile)) == NULL)	      //重定向文件
			perror("get out file error");
	}
	printf("%s %s\n",infile, outfile);
	return 0;
}

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
