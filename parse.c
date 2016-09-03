#include "parse.h"
#include "def.h"
#include "init.h"
#include <stdio.h>

/*
int backgnd;
char infile[MAXNAME+1];
char outfile[MAXNAME+1];
char cmdLine[MAXLEN+1];
char tempLine[MAXLEN+1];
CMD cmd[PIPELINE];
*/
char *temp;

int read_cmd(){
	if(fgets(cmdLine, MAXLEN, stdin) == NULL){  //CTRL+D
		return -1;
	}
	return 0;
}

const char* parse_cmd(const char* t, int num){                //读取一条完整指令放在cmd[num]
	//printf("该行的第%d条命令\n", num+1);

	char *st;                   //一个字符串
	int cnt = 0;
	while(t != NULL){
		st = temp;
		while(*t != ' ' && *t != '\t' && *t != '\n' && *t != '\0' && *t != '>' && *t != '<' && *t != '|' && *t != '&')
			*(temp++) = *(t++);
		*(temp++) = '\0';
		//printf(" %s \n",st);
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
		//printf("ch = %c\n", ch);
		return ++p;
	}
	return p;                                       
}

const char* getFileName(const char* s, char *t){                //保存文件名字符串
	while(*s == ' ' || *s == '\t')
		++s;
	if(*s == '|' || *s == '>' || *s == '&' || *s == '\0' || *s == '\n')
		return NULL;
	while(*s == '_' || (*s > 'a' && *s <'z') ||(*s > 'A' && *s <'Z') ||  (*s > '0' && *s <'9') || *s == '.')
		*t++ = *s++;
	*t = '\0';
	return s;
}


int parse(){                             //输入行 分词  存储在CMD的数组中  返回命令数量
	//cat < in.txt | wc -l | cat > out.txt                     ok
    //cat<in.txt|wc -l|cat>out.txt&                            ok
	char *p = cmdLine;
	const char *t;
	int cmd_num = 0;
	temp = tempLine;            //全局变量  templine存储分割后的字符串常量  (args的指针没有分配内存 直接指向tempLine里的串)
	cmd_num = 0;

	t = parse_cmd(p, cmd_num++);                          //1 解析第一个命令到cmd[0]

	Find = 0;
	t = check_symbol(t, '<');                             //2 第一个检查输入重定向符<  
	if(Find){
		if( (t = getFileName(t, infile)) == NULL)	      //3 重定向文件
			perror("get in file error");
	}
	
	int i;
	for(i = 1; i<PIPELINE; ++i){               //最多pipeline个命令
		Find = 0;
		t = check_symbol(t, '|');                         // 4 中间检查管道符
		if(Find)
			t = parse_cmd(t, cmd_num++);                  // 5 存储管道命令
	}

	Find = 0;
	t = check_symbol(t, '>');                             // 6 再检查输出重定向符
	if(Find){
		Find = 0;
		t = check_symbol(t, '>');
		if(Find) append = 1;                              // 6.5 判断追加方式重定向
		if( (t = getFileName(t, outfile)) == NULL)	      // 7  输出重定向文件
			perror("get out file error");
	}
	//printf("in file:%s\n outfile:%s\n",infile, outfile);

	Find = 0;
	t = check_symbol(t, '&');                                 // 8 最后检查后台运行符
	if(Find)
		backgnd = 1;

	Find = 0;
	check_symbol(t, '\n');
	if(Find)
		return cmd_num;
	return -1;
}
