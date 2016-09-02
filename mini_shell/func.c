#include "func.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char** environ;

void func_cd(Program* prog){
	if( chdir(prog->args[1])< 0)
		perror("cd error");
}

void func_pwd(Program* prog){
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	if(! getcwd(buffer, sizeof(buffer)) )
		perror("pwd error");
	printf("%s\n", buffer);
}

void func_exit(Program* prog){
	exit(0);
}


void func_env(Program* prog){
	int i = 0;
	char* str = environ[i];
	while(str != NULL){
		printf("%s\n", str);
		str = environ[i];
		++i;
	}
}

void func_export(Program* prog){
	if(prog->args[1] == NULL){
		fprintf(stderr, "export: invalid argument\n");
		return;
	}
	putenv(prog->args[1]);
}

//普通打印以及环境变量打印
void func_echo(Program* prog){
	char *str = prog->args[1];
	assert(str != NULL);
	
	if(str[0] == '$')
		printf("%s\n", getenv(str+1));
	else 
		printf("%s\n",str);
}

