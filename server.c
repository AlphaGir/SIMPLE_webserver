#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<signal.h>
#define MAXLINE 4096
/*1.建立连接　
 *2.创建http返回请求
 *3.如果没有该文件就返回４０４，有就显示．
 * 字符串拼接有毒 日了狗。。。。
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
   {printf("%d,child is dead",pid);}
   return ;
}
int main()
{
	int socke,fd;
	struct sockaddr_in serve;
	char buff[4096];
	char sendmsg[4096];
	int n;
	long timeval;
	if((socke =socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("socket:");

        bzero(&serve,sizeof(serve));
	serve.sin_family=AF_INET;
	serve.sin_addr.s_addr=inet_addr("172.18.212.186");//htonl区别
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
		if((fd=accept(socke,(struct sockaddr*)NULL,NULL))==-1)
		{
			perror("accept:")	;	exit(1);
		}
                if((pid=fork())==0)
                {
 //               printf("there is someone!!!\n");
		n=recv(fd,buff,MAXLINE,0);
               close(socke);
		printf("%s\n",buff);
		n=strlen(buff);
                char msg[30];char *cp;
                cp=ctime(&timeval);
		if(buff[0]!='G'&&buff[1]!='E'&&buff[2]!='T')
                {
                sprintf(sendmsg,http_header,400,"bad request",n,cp,"not found");
 //               printf("sendmsg:%s\n",sendmsg);
               // strcpy(msg,"<h1> 404 NOT FOUND </h1>");
   //             printf("msg:%s\n",msg);
                }
                else
                {
                   char *success="HELLO WORLD";
                   sprintf(sendmsg,http_header,200,"OK",11,success);
                  //strcat(sendmsg,success);
                   //strcpy(msg,success);
		}
               // send(fd,http1,strlen(http1),0);
               //msg="<h1> HHHHHHHH</h1>";
               send(fd,sendmsg,strlen(sendmsg),0);
                //printf("msg:%s\n",msg);
 //               sleep(100);
                close(fd);exit(0);
                }
                close(fd);
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
