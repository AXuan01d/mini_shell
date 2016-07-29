#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include "mstdio.h"

#define BUFFER_LEN 4096

MFILE* mfopen(const char* const path, const char* const mode){
	int fd;
	if( !strcmp(mode, "r") )
		fd = open(path, O_RDONLY);
	else if( !strcmp(mode, "w") )
		fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0777);
	else if( !strcmp(mode, "a") )
		fd = open(path, O_WRONLY|O_CREAT|O_APPEND, 0777);
	else 
		return NULL;
	
	if( fd <0 )
		return NULL;

	return mfdopen(fd, mode);
}

int mfclose(MFILE *fp){
	mfflush(fp);
	int res = close(fp->_fd);
	free(fp->_buff);
	free(fp);
	return res;
}

void mfflush(MFILE *fp){                     //刷新文件/清除缓存
	if(fp->_mode = READ){
		fp->_nextc = fp->_buff;             //丢掉缓存区中的内容
		fp->_left = 0;
	}
	else {                        //写入或追加写入
		write(fp->_fd, fp->_buff, BUFFER_LEN - fp->_left );        //将缓存区写到文件
		fp->_nextc = fp->_buff;
		fp->_left = BUFFER_LEN;
	}
}

MFILE* mfdopen(int fd, const char *mode){         //将文件号转为文件指针
	MFILE *fp = (MFILE*)malloc(sizeof(MFILE));
	assert(fp != NULL);
	fp->_buff = (char*)malloc(BUFFER_LEN);
	fp->_fd = fd;
	fp->_nextc = fp->_buff;
	if(!strcmp(mode, "r") ){
		fp->_mode = READ;
		fp->_left = 0;
	}
	else if(!strcmp(mode, "w") ){
		fp->_mode = WRITE;
		fp->_left = BUFFER_LEN;
	}
	else if( !strcmp(mode, "a") ){
		fp->_mode = APPEND;
		fp->_left = BUFFER_LEN;
	}
	return fp;
}

int mfgetc(MFILE *fp){
	assert(fp->_mode == READ);
	//缓存剩余0个字符,再从文件中读取一批新的数据到缓存
	if(fp->_left == 0){
        ssize_t size = read(fp->_fd, fp->_buff, BUFFER_LEN);
		assert( size >= 0);
		if(size == 0)
			return MEOF;
		fp->_nextc = fp->_buff;
		fp->_left = size;
	}
	int ch = *(fp->_nextc);
	++(fp->_nextc);
	--(fp->_left);
	return ch;
}
int mfputc(int character, MFILE *fp){
	assert(fp->_mode == WRITE || fp->_mode == APPEND );
	//缓存区剩余0个字符,将所有缓存区内容写入文件
	if(fp->_left == 0){
		if( write(fp->_fd, fp->_buff, BUFFER_LEN) !=BUFFER_LEN)
			return 0;
		fp->_nextc = fp->_buff;
		fp->_left = BUFFER_LEN;
	}
	*(fp->_nextc) = (char)character;
	++fp->_nextc;
	--fp->_left;
	return 1;
}
int mungetc(int character, MFILE *fp){       //撤回一个字符
	assert(fp->_mode == READ);
    assert(fp->_left < BUFFER_LEN);
	++fp->_left;
	--fp->_nextc;
	*(fp->_nextc) = (char)character;
	return 1;
}


char* mfgets(char *buff, int size, MFILE *fp){
	assert(fp->_mode == READ);
	char *p = buff;
	char ch;
	while( (--size)>0 && (ch = mfgetc(fp)) != MEOF){
		
		*p = ch;
		p++;
		if(ch == '\n')
			break;
	}
	*p = '\0';
	if( p == buff && ch == MEOF)
		return NULL;
	return buff;
}
int mfputs(char *buff, MFILE *fp){
	assert(fp->_mode == WRITE || fp->_mode == APPEND);
	char ch;
	while(ch = *buff){
		++buff;
		mfputc(ch, fp);
	}
	if(ch == 0)
		return MEOF;
    return 0;
}

size_t mfread (void *buff, size_t size, size_t counter, MFILE *fp){
	
}


size_t mfwirte(void *buff, size_t size, size_t counter, MFILE *fp){

}







