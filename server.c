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
extern void doit(char *uri);
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
/*void doit(char* url)
{
   
}*/
int handle_static(char *msg)//静态资源一般都直接返回
{

}
int handle_dynamic()
{
}
int main(int arg,char *argv[])
{
	int socke,fd1;
	struct sockaddr_in serve;
	char buff1[12580];
	char buff2[12580];//
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

	if(bind(socke,(struct sockaddr*)&serve,sizeof(serve))==-1)
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
		if((fd1=accept(socke,(struct sockaddr*)NULL,NULL))==-1)
		{
			perror("accept:")	;	exit(1);
		}
                if((pid=fork())==0)
                {
 //               printf("there is someone!!!\n");
		n=recv(fd1,buff1,333,0);//分析请求。//静态请求 直接返回，动态请求 读取 执行 返回执行结果

		//printf("url:%s",buff1);
                doit(buff1);
 		//printf("code:%d msg:%s len:%d last:%s",codetype,msg,strlen(last),last);               
                //sprintf(http_header,codetype,msg,strlen(last),last);
		//printf("static:%d",is_static);
		
		sprintf(buff2,"HTTP/1.1 %d %s\r\n",codetype,msg);
		/* "Content-Length: %d\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "%s"*/

		sprintf(buff2, "%sContent-Length: %d\r\n",buff2,strlen(last));
		sprintf(buff2, "%sContent-Type:text/html\r\n\r\n",buff2);
		sprintf(buff2,"%s%s",buff2,last);
		perror("sprintf:");
		printf("response:%s",buff2);
		perror("sprintf:");
                send(fd1,buff2,strlen(buff2),0);
                
		perror("send:");
               close(socke);
 //               sleep(100);
                close(fd1);exit(0);
                }
                close(fd1);
              //  exit(0);
           //     }
             }
                //close(socke);}
                }

                
          
		//分割http请求消息．如果方法不是GET 403 看不懂你在说什么
		//                  如果请求的文件不存在 404
		//先完成上述 结合unix网络编程还有tcp/ip进一步完善比如io复用.
                //我要看线程崩溃 已经崩溃了 区区多进程都没有搞定

           


//}
