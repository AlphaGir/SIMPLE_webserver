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
int codetype;//编码
char sendmsg[4096];//发送消息
char msg[20];//编码解释
char path[100];//路径

int err(int code,char *m);
void doit(char *url);
void getstatic();
void getdynamic();
#endif
