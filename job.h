#ifndef __JOB_H__
#define __JOB_H__
#include<sys/types.h>

enum RedirectType{RdRead, RdWrite, RdAppend};   //重定向类型

typedef struct{
	enum	 RedirectType redirect;
	int		 fd;
}Redirection;

typedef struct{
	pid_t		pid;
	Redirection *redirects;
	int			redirect_num;
	char		**args;    //对应argv* []
}Program;

typedef struct{
	char       *cmd;         //命令名
	int        progs_num;    //一个程序可能对应多个（进程）
	Program    *progs;      
	pid_t	   pgid;       //进程组id
}Job;

extern Job* create_job(char *cmd);
extern void destroy_job(Job *job);

extern Program* create_program(char **arg);
extern void destroy_program(Program *prog);

extern int add_program(Job *job, Program *prog);

extern Redirection* create_redirect(int fd, enum RedirectType type);
extern void destroy_redirect(Redirection *r);

extern void add_redirection(Program *prog, Redirection *r);

#endif
