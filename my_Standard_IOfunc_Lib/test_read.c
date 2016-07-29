#include "mstdio.h"
#include <stdio.h>
#include <malloc.h>
int main(int argc, char* argv[]){
	MFILE *fp =mfopen(argv[1], "r");
    printf("first character: %c \n", mfgetc(fp));

	char *tmp = (char*)malloc(20);
	while(mfgets(tmp, 10, fp))
		printf("    %s   \n",tmp);
	mfclose(fp);
	return 0;
}
