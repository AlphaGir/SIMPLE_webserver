#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#define MAXLINE 4096
/*1.建立连接　
 *2.创建http返回请求
 *3.如果没有该文件就返回４０４，有就显示．
 */
char *http_header = "HTTP/1.1 %d %s\r\n"
                                            "Content-Length: %d\r\n"
                                            "Content-Type: text/html\r\n"
                                            "Date:%s \r\n"
                                            "\r\n";

int main()
{
	int socke,fd;
	struct sockaddr_in serve;
	char buff[4096];
	char sendmsg[4096]
	int n;
	long timeval;
	if((socke =socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("socket:");

        memset(&serve,0,sizeof(serve));
	serve.sin_family=AF_INET;
	serve.sin_addr.s_addr=inet_addr("120.78.168.53");//htonl区别
	serve.sin_port=htons(80);

	if(bind(socke,(struct sockaddr*)&serve,sizeof(serve))==-1)
		perror("bind:");
	if(listen(socke,10)==-1)
		perror("no link:");
	printf("------------wait for client -----------\n");
	while(1)
	{
		if((fd=accept(socke,(struct sockaddr*)NULL,NULL))==-1)
		{
			perror("accept:");
			continue;
		}

		while((n=recv(fd,buff,MAXLINE,0)!=0)
		{
		printf("%s\n",buff);
		n=strlen(buff);
                 char *cp;
                cp=ctime(&timeval);
		if(buff[0]!='G'&&buff[1]!='E'&&buff[2]!='T')
                sprintf(sendmsg,http_header,400,"bad request",cp);
		send(fd,sendmsg,strlen(sendmsg),0);
		}

		//分割http请求消息．如果方法不是GET 403 看不懂你在说什么
		//                  如果请求的文件不存在 404
		//先完成上述 结合unix网络编程还有tcp/ip进一步完善比如io复用.
                //我要看线程崩溃

           


}
