#ifndef _AW_H_
#define _AW_H_
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<stdlib.h>

extern int codetype;//编码
extern char last[1024];
extern char msg[10];
extern char path[100];//路径
extern char v1[100];
extern char value1[200];
extern char v2[100];
extern char value2[200];
extern char buff[1024];
extern char buff2[1024];//
extern int is_static;
extern struct stat sbuf;
extern int err(int code,char *m);
extern void useit(int fd1,char *url);
extern void getstatic(int fd1);
extern void getdynamic(int fd1);
extern void cutout(char *uri,int begin,int end,char *ret);
#endif
