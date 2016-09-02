#ifndef DEF_H
#define DEF_H

#define MAXLEN 1024  //输入行最大长度
#define MAXARG 20    //每个命令参数的最大个数
#define PIPELINE 5   //一行最多5个命令(管道)
#define MAXNAME 100  //IO重定向文件的最大长度

typedef struct command{
	char *args[MAXARG+1];            //读入字符串 分词后的数组
	int fdin,fdout;
}CMD;

extern int backgnd;     //是否后台运行
extern int cmd_num;     //一行指令个数
extern char cmdLine[MAXLEN+1];       //读入的一行
extern char tempLine[MAXLEN+1];      //将读入的一行中的空格 tab 化为‘\0’再存储在其中
extern char infile[MAXNAME+1];       //输入重定向的文件
extern char outfile[MAXNAME+1];      //输出重定向的文件
extern CMD cmd[PIPELINE];                  

#endif //DEF_H
