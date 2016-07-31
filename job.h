#ifndef __JOB_H__
#define __JOB_H__

typedef struct{
	char **args;
}Program;

typedef struct{
	char       *cmd;
	int        progs_num;
	Program    *progs;
}Job;

extern Job* create_job(char *cmd);
extern void destroy_job(Job *job);

extern Program* create_program(char **arg);
extern void destroy_program(Program *prog);

extern int add_program(Job *job, Program *prog);

#endif
