#include"aw.h"
/*
 AW OPERATION
 EW OPERATION
 */
extern char **environ;
 int codetype;//编码
 char last[1024];//发送消息
 char msg[10];//编码解释
 char path[100];//路径
 char v1[100];
 char value1[200];
 char v2[100];
 char value2[200];
 int filed1;
 char buff[1024];
 char buff2[1024];//
 int is_static;
 struct stat sbuf;
void wrong(int fd2);
void getdynamic(int fd1);
void getstatic(int fd1);
void cutout(char *uri,int begin,int end,char *ret)
{
     int i=0;
     int j=0;
     int s,e;
     for(;i<strlen(uri);i++)
     {
         if(uri[i]==begin)
         {
                 s=i;
         }
         if(uri[i]==end&&end!='\0')
          {
                  e=i;
                  if(s<e)
                  break;
          }
     }
     if(end=='\0')
     {
	     int len=strlen(uri)-s;
	     char ss[len];
	     memcpy(ret,uri+s+1,len-1);
	     ret[len]='\0';//
     }
     else
     {
          int len=e-s;
          memcpy(ret,uri+s+1,len-1);
          ret[len]='\0';
     }

 }

void useit(int fd1,char* url)//获取返回的响应报文
{
   int i;
   char uri[100];
   char method[5];
   char version[10];
   char buff2[12580];
   char p1[300]="./";
   sscanf(url,"%s %s %s",method,uri,version);
   printf("uri:%s method:%s version:%s\n",uri,method,version);
   if(strcmp(method,"GET")!=0&&strcmp(method,"POST")!=0)
     {
       codetype=err(4,msg);
       wrong(fd1);
       return;
     }
   else
     {
            if(!strstr(uri,"cgi"))//静态资源
            {
	      is_static=1;
              strcpy(path,uri);
              getstatic(fd1);
            }
            else
            {
	     is_static=0;
	     cutout(uri,'/','?',path);
             strcat(p1,path);
	     strcpy(path,p1);
             cutout(uri,'?','=',v1);
             cutout(uri,'=','&',value1);
             cutout(uri,'&','=',v2);
             cutout(uri,'=','\0',value2);
             getdynamic(fd1);
	     return ;
            }
     }
}
void getdynamic(int fd1)
{
    char *str=value1;
    strcat(str,value2);
    if(stat(path,&sbuf)<0)
    {
                codetype=err(2,msg);
		wrong(fd1);
                return;
    }

    if(!(S_ISREG(sbuf.st_mode))||!(S_IXUSR&sbuf.st_mode))
    {
                codetype=err(3,msg);
		wrong(fd1);
		return;
    }
    char *data;
    int pid;
    int trans[2];
    if((pipe(trans))<0)
	{
		perror("pipe:");
	}
    if((pid=fork())<0)
	{
		perror("fork:");
	}

    if(pid==0)
    {
	  dup2(trans[0],0);
	  dup2(trans[1],1);
	  close(trans[0]);
          setenv("QUERY_STRING",value1,1);
	  execl(path,NULL);
    }
    else
    {
    close(trans[1]);
    char c;
	    while(read(trans[0],last,1024));
            printf("Last:%s\n",last);
	    codetype=err(1,msg);
            sprintf(buff2,"HTTP/1.1 %d %s\r\n",codetype,msg);
            sprintf(buff2, "%sContent-Length: %d\r\n",buff2,strlen(last));
            sprintf(buff2, "%sContent-Type:text/html,charset:utf-8;\r\n",buff2);
            sprintf(buff2,"%sConnection：Keep-alive\r\n\r\n",buff2);
            sprintf(buff2,"%s%s",buff2,last);
            send(fd1,buff2,strlen(buff2),0);
            wait(0);	
    }
    
}
void wrong(int fd2)
{
                 sprintf(buff2,"HTTP/1.1 %d %s\r\n",codetype,msg);
                 sprintf(buff2, "%sContent-Length: %d\r\n",buff2,0);
                 sprintf(buff2, "%sContent-Type:text/html\r\n\r\n",buff2);
                 send(fd2,buff2,strlen(buff2),0);
}
void getstatic(int fd1)
{
	int fd;
	if(strcmp(path,"/")==0)
	{
		if((fd=open("./index.html",O_RDONLY))!=-1)
		{
			while(read(fd,buff,1024)>0)
			strcpy(last,buff);
			close(fd);
			codetype=err(1,msg);
                        sprintf(buff2,"HTTP/1.1 %d %s\r\n",codetype,msg);
			sprintf(buff2, "%sContent-Length: %d\r\n",buff2,strlen(last));
                        sprintf(buff2, "%sContent-Type:text/html,charset:utf-8;\r\n\r\n",buff2);
                        sprintf(buff2,"%s%s",buff2,last);
			send(fd1,buff2,strlen(buff2),0);
			return ;
		}
	}
	if(stat(path,&sbuf)<0)
	{
		codetype=err(2,msg);
		wrong(fd1);
		return;
	}
	if(!(S_ISREG(sbuf.st_mode))||!(S_IRUSR&sbuf.st_mode))
	{
		codetype=err(3,msg);
		wrong(fd1);
		return ;
	}
	if((fd=open(path,O_RDONLY))!=-1)
	{
		while(read(fd,buff,1024)>0);
		strcpy(last,buff);
		close(fd);
		codetype=err(1,msg);
                sprintf(buff2,"HTTP/1.1 %d %s\r\n",codetype,msg);
                sprintf(buff2, "%sContent-Length: %d\r\n",buff2,strlen(last));
                sprintf(buff2, "%sContent-Type:text/html,charset:utf-8\r\n\r\n",buff2);
                sprintf(buff2,"%s%s",buff2,last);
		send(fd1,buff2,strlen(buff2),0);
		return;
	}
}
int err(int f,char *ret)
{
   switch(f)
   {
     case 1: f=200;strcpy(ret,"ok");break;
     case 2: f=404;strcpy(ret,"not found");break;
     case 3: f=403;strcpy(ret,"fobbiden permission");break;
     case 4: f=501;strcpy(ret,"not implement");break;
   }
   return f;
}

