#include "func.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

