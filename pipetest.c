/*
 *主要为了测试 pipe管道还有重定向dup2等
 * dup2(old ,new) 复制一个文件描述符返回新的文件描述符
 *
 */
#include<stdio.h>
#include<unistd.h>
int main()
{
	//主进程读取子进程的内容
	int trans[2];//trans[0]为读数据端的文件描述符 [1]为写数据端的文件描述符
	if(pipe(trans)<0)
	{
		perror("pipe:");
	}
	int pid;
	if((pid=fork())<0)
	{
		perror("fork;");
        }
	if(pid==0)
	{
	   dup2(trans[0],0);
	   close(trans[0]);
	   execl("./form_action1.cgi",NULL);
	}
	else
	{
		close(trans[1]);
		char c='c';
		while(read(trans[0],&c,1)>0)
		{
			printf("%c",c);
		}
		wait(0);
		
	}

}
