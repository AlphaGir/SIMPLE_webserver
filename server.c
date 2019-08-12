#include<fcntl.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<signal.h>
#include"aw.h"
//extern char **environ;
#define MAXLINE 4096
extern void useit(int f,char *uri);
extern int fd1;
/*1.建立连接　
 *2.创建http返回请求
 *3.如果没有该文件就返回４０４，有就显示．
 */
char *http1 = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length: 11\r\nServer: mengkang\r\n\r\nhello world";
char *http_header = "HTTP/1.1 %d %s\r\n"
                    "Content-Length: %d\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "%s"                   
;

void sig_child(int signo)
{
   int pid;
   int state;
   while((pid=waitpid(-1,(int *)0,WNOHANG))>0)
   //printf("%d,child is dead",pid);
   return ;
}
int main(int arg,char *argv[])
{
	int socke,fd1;
	struct sockaddr_in serve;
	struct sockaddr_in client_name;
    socklen_t  client_name_len = sizeof(client_name);
	char buff1[12580];
	//char buff2[12580];//
	//char sendmsg[4096];
	int n,ret;
	int on=1;
        ret = setsockopt( socke, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
	if((socke =socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("socket:");

        bzero(&serve,sizeof(serve));
	serve.sin_family=AF_INET;
	serve.sin_addr.s_addr=inet_addr("127.0.0.1");//htonl区别//172.18.212.186
	serve.sin_port=htons(80);
	if ((setsockopt(socke, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
    {
        perror("setsockopt failed");
    }

	if((bind(socke,(struct sockaddr*)&serve,sizeof(serve)))<0)
		{
                   perror("bind:");
                   exit(1);
                }
	if(listen(socke,10)==-1)
		perror("no link:");
        signal(SIGCHLD,sig_child);
	printf("------------wait for client -----------\n");
        int pid;
       
	while(1)
	{
		if((fd1=accept(socke,(struct sockaddr *)&client_name,
                &client_name_len))==-1)
		{
			perror("accept:")	;
		}
                if((pid=fork())==0)
                {
 //               printf("there is someone!!!\n");
		n=recv(fd1,buff1,333,0);//分析请求。//静态请求 直接返回，动态请求 读取 执行 返回执行结果
                useit(fd1,buff1);
                //send(fd1,buff2,strlen(buff2),0);
                close(socke);
                close(fd1);
		exit(0);
                }
                close(fd1);
         }
}

