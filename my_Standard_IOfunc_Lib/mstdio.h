#ifndef __MSTDIO_H__
#define __MSTDIO_H__

#include <sys/types.h>
#define MEOF    -1

enum mode{READ, WRITE, APPEND};

typedef struct
{
	int _fd;
	char *_buff;
	char *_nextc;
	int _mode;
	off_t _left;
}MFILE;

extern MFILE* mfopen(const char* const path, const char* const mode);
extern int mfclose(MFILE *fp);

extern void mfflush(MFILE *fp);                     //刷新文件
extern MFILE* mfdopen(int fd, const char *mode);   //将文件号转为文件指针


extern int mfgetc(MFILE *fp);
extern int mfputc(int character, MFILE *fp);
extern int mungetc(int character, MFILE *fp);       //撤回一个字符

extern char* mfgets(char *buff, int size, MFILE *fp); 
extern int   mfputs(char *buff, MFile *fp);

extern size_t mfread (void *buff, size_t size, size_t counter, MFILE *fp);
extern size_t mfwirte(void *buff, size_t size, size_t counter, MFILE *fp);

extern int M



#endif

