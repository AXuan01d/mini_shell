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

//cat < in.txt | wc -l | cat > out.txt                     ok
//cat<in.txt|wc -l|cat>out.txt&                            ok
void print_after_parse(int num){
	printf("共%d条命令\n", num);
	int i, cnt;
	for(i = 0; i < num; ++i){
		cnt = 0;
		printf("第 %d 条命令 : ", i + 1);
		char *t = cmd[i].args[cnt];
		while(t != NULL	){
			printf(" [%s] ", t);
			t = cmd[i].args[++cnt];
		}
		printf("\n");
	}
	printf("infile : %s\n", infile);
	printf("outfile : %s\n", outfile);
	printf("后台运行   %s\n", backgnd?"是":"否");
	printf("追加重定向  %s\n", append?"是":"否");
	
}

void shell_loop(){
	int num;
	while(1){
		printf("[minishell]$");
		init();                           //变量初始化
		if(read_cmd() == -1)              //读命令
			break;
		if((num = parse()) == -1)                 //解析命令
			continue;
	//	print_after_parse(num);
	//	execute();		                  //执行命令
	}
	printf("\nminishell exited\n");
}

int main(void){
	setup();	                          //设置属性
	shell_loop();
	return 0;
}
