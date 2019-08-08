#ifndef _AW_H_
#define _AW_H_
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
extern int codetype;//编码
extern char sendmsg[4096];//发送消息
extern char msg[20];//编码解释
extern char path[100];//路径
extern char v1[100];
extern char value1[100];
extern char v2[100];
extern char value2[100];
extern int fd;
extern char buff[4096];
extern int is_static;
extern struct stat sbuf;

int err(int code,char *m);
void doit(char *url);
void getstatic();
void getdynamic();
void cutout(char *uri,int begin,int end,char *ret);
#endif
