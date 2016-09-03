#include "init.h"
#include "def.h"
#include <string.h>
#include <signal.h>
#include <stdio.h>

void sig_func(int sig){
	if(sig == SIGINT){
		printf("\n[minishell]$");
		fflush(stdout);
	}
}

void setup(){
	signal(SIGINT, sig_func);  //ctrl+c 重新输入
	signal(SIGQUIT, SIG_IGN);   //忽视ctrl+ '/'
}

void init(){
	append = 0;
	backgnd = 0;
	memset(infile, 0, sizeof(infile));
	memset(outfile, 0, sizeof(outfile));
	memset(cmdLine, 0, sizeof(cmdLine));
	memset(cmd, 0, sizeof(cmd));
}
