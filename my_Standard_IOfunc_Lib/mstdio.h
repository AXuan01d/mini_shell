#ifndef __MSTDIO_H__
#define __MSTDIO_H__

#include <sys/types.h>
#define MEOF    -1

enum mode{READ, WRITE, APPEND};

typedef struct
{
	int _fd;         
	char *_buff;     //缓存区首地址
	char *_nextc;    //下一个字符地址
	int _mode;      //读写模式
	off_t _left;    //缓存区剩余字符
}MFILE;

extern MFILE* mfopen(const char* const path, const char* const mode);
extern int mfclose(MFILE *fp);

extern void mfflush(MFILE *fp);                     //刷新文件
extern MFILE* mfdopen(int fd, const char *mode);   //将文件号转为文件指针


extern int mfgetc(MFILE *fp);
extern int mfputc(int character, MFILE *fp);
extern int mungetc(int character, MFILE *fp);       //撤回一个字符

extern char* mfgets(char *buff, int size, MFILE *fp); 
extern int   mfputs(char *buff, MFILE *fp);

extern size_t mfread (void *buff, size_t size, size_t counter, MFILE *fp);
extern size_t mfwirte(void *buff, size_t size, size_t counter, MFILE *fp);


#endif

