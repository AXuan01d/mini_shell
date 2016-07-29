#include "mstdio.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	MFILE* fp = mfopen(argv[1], "w");
	mfputs(argv[2], fp);
	mfclose(fp);	
	return 0;
}
