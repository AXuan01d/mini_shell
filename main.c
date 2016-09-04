#include "init.h"
#include "parse.h"
#include "execute.h"
#include "def.h"
#include <stdio.h>

int cmd_num;
int backgnd;
int append;
char infile[MAXNAME+1];
char outfile[MAXNAME+1];
char cmdLine[MAXLEN+1];
char tempLine[MAXLEN+1];
CMD cmd[PIPELINE];

//cat < in.txt | wc -l | cat > out.txt                     ok
//cat<in.txt|wc -l|cat>out.txt&                            ok
void print_after_parse(){
	printf("共%d条命令\n", cmd_num);
	if(!cmd_num)
		return ;
	int i, cnt;
	for(i = 0; i < cmd_num; ++i){
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
	while(1){
		printf("[minishell]$");
		init();                           //1变量初始化
		if(read_cmd() == -1)              //2读取一行
			break;
		if(parse() == -1){        //3解析命令
			printf("输入有误 请重新输入\n");
			continue;
		}
		if(cmd_num == 0)
			continue;
	//	print_after_parse();           //检查解析结果
		execute();		                  //4执行命令
	}
	printf("\nminishell exited\n");
}

int main(void){
	setup();	                          //设置属性
	shell_loop();
	return 0;
}
