#ifndef _IO_H_
#define _IO_H_
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include<string.h>
#define RIO_BUFSIZE 8192
 typedef struct {
    int rio_fd;                //与内部缓冲区关联的描述符
    int rio_cnt;               //缓冲区中剩下的字节数
    char *rio_bufptr;          //指向缓冲区中下一个未读的字节
    char rio_buf[RIO_BUFSIZE]; 
} rio_t;
void rio_readinitb(rio_t *rp, int fd);
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
#endif 
 




