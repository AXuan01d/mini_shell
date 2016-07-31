#include "job.h"
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>


Job* create_job(char *cmd){
	Job *job = (Job*)malloc(sizeof(Job));
	assert(job != NULL);
	job->cmd = (char*)malloc(sizeof(char) * strlen(cmd));
	assert(job->cmd != NULL);
	strcpy(job->cmd, cmd);
	job->progs_num = 0;
	job->progs = NULL;
	return job;
}
void destroy_job(Job *job){
	assert(job != NULL);
	free(job->progs);
	free(job->cmd);
	free(job);
}

static int arg_num(char **arg){       //获取参数个数
	int i = 0;
	char *start = arg[0];
	while(start != NULL){
		++i;
		start = arg[i];
	}
	return i;
}

Program* create_program(char **arg){
	Program *prog = (Program*)malloc (sizeof(Program));
	assert(prog != NULL);
	int cnt = arg_num(arg);
	prog->args = (char**)calloc(cnt + 1, sizeof(char*) );
	int i;
	for( i = 0; i < cnt ; ++i){
		prog->args[i] = (char*)malloc(sizeof(char) * strlen(arg[i]) );
		assert(prog->args[i] != NULL);
		strcpy(prog->args[i], arg[i]);
	}
	prog->args[i] = NULL;
	return prog;
}
void destroy_program(Program *prog){
	assert(prog != NULL);
	int i =0;
	while( prog->args[i] != NULL){
		free(prog->args[i]);
		++i;
	}
	free(prog->args);
	free(prog);
}

int add_program(Job *job, Program *prog){
	Program *cp = (Program*)malloc(sizeof(Program) * (job->progs_num+1) );
	assert(cp != NULL);
	memcpy(cp, job->progs, sizeof(Program) * job->progs_num);   //将原结构体的数组拷贝过来
	cp[job->progs_num] = *prog;     //新的一组参数
	++job->progs_num;
	free(job->progs);
	job->progs = cp;
	return 1;

}

